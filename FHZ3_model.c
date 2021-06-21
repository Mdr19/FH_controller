#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/neutrino.h>
//#include <sys/netmgr.h>
#include <mqueue.h>

#include "logger.h"
#include "screen.h"
#include "FHZ3_model.h"

#include "cyclic_buffer.h"
#include "data_struct.h"
#include "FHZN_model.h"
#include "tcpip_server.h"

#define model_diff_tr 500
#define sp_diff_tr 1000


/* Thread function prototype */
void *tFHZ3modelThreadFunc(void *);
/* Channel ID */
int p2_chid;

sem_t FHZ3_model_sem;
sem_t FHZ3_buff_sem;

cyclic_buffer* data_buff_Z3;
FHZN_model* FH_model_Z3;

unsigned int FHZ3_curr_interval=0;
unsigned int FHZ3_current_model_nr = 0;
char buff_to_send_FHZ3[send_buffer_size];

/**
 * Function starts periodic thread
 */
int init_FHZ3model() {

	int status;

	/* Thread variable */
	pthread_t tFHZ3modelThread;
	/* Thread attributes variable */
	pthread_attr_t aFHZ3modelThreadAttr;
	/* Structure with time values */
	struct	itimerspec timerSpecStruct;
	/* Timer variable */
	timer_t	timerVar;
	/* Signal variable */
	struct	sigevent timerEvent;
	/* Connection ID */
	int p_coid;

	data_buff_Z3 = BUFF_create(max_buffer_size);
	FH_model_Z3 = FH_ZONE_MODEL_create();


	/* Initialize thread attributes structure - FIFO scheduling */
	pthread_attr_init(&aFHZ3modelThreadAttr);
	pthread_attr_setschedpolicy(&aFHZ3modelThreadAttr, SCHED_FIFO);

	/* Create thread */
	if ((status = pthread_create( &tFHZ3modelThread, NULL, tFHZ3modelThreadFunc, &aFHZ3modelThreadAttr))) {
		fprintf(stderr, "Cannot create thread.\n");
		return 0;
	}

	// Connect to channel
	p_coid = ConnectAttach(0, getpid(), p2_chid, 0, _NTO_COF_NOEVENT );
	if (p_coid == -1) {
		fprintf(stderr, "Couldn't connect to channel\n");
		return 0;
	}

	printf("Periodic: I'm attached\n");

	// Initialize event to send pulse
	SIGEV_PULSE_INIT( &timerEvent, p_coid, sched_get_priority_max(SCHED_FIFO), _PULSE_CODE_MAXAVAIL, 1);


	/* Create timer */
	if ((status = timer_create( CLOCK_REALTIME, &timerEvent, &timerVar))) {
		fprintf(stderr, "Error creating timer : %d\n", status);
		return 0;
	}

	/* Set up timer structure with time parameters */
	timerSpecStruct.it_value.tv_sec = 0;
	timerSpecStruct.it_value.tv_nsec = 100000000;
	timerSpecStruct.it_interval.tv_sec = 1;
	timerSpecStruct.it_interval.tv_nsec = 0; //100000000;

	/* Change timer parameters and run */
	timer_settime( timerVar, 0, &timerSpecStruct, NULL);

	return 0;
}


int initialize_FHZ3model() {

	int status;

	/* Initialize semaphores */
	if ((status = sem_init(&FHZ3_buff_sem, NULL, 1))) {
		fprintf(stderr, "Error creating semaphore : %d\n", status);
		return 0;
	}

	if ((status = sem_init(&FHZ3_model_sem, NULL, 1))) {
		fprintf(stderr, "Error creating semaphore : %d\n", status);
		return 0;
	}

	return 0;
}

/*
 *  Periodic thread function
 */
void *tFHZ3modelThreadFunc(void *cookie) {

	/* Screen connection ID */
	int s_coid;
	int srv_coid;

	/* Pulse data special structure */
	struct _pulse pdata;
	/* Scheduling policy: FIFO or RR */
	int policy;
	/* Structure of other thread parameters */
	struct sched_param param;

	/* Read modify and set new thread priority */
	pthread_getschedparam( pthread_self(), &policy, &param);
	param.sched_priority = sched_get_priority_max(policy);
	pthread_setschedparam( pthread_self(), policy, &param);

	/* Create new channel */
	//FHZ4_chid = ChannelCreate(0);
	//printf("FHZ4model: Channel created\n");

	p2_chid = ChannelCreate(0);
	printf("Periodic: Channel created\n");

	/* Initialize plant */
	initialize_FHZ3model();

	/* Wait until screen create channel */
	delay(1000);
	/* Connect to screen */

	s_coid = ConnectAttach(0, getpid(), s_chid, 0, _NTO_COF_NOEVENT);
	if (s_coid == -1) {
		fprintf(stderr, "Couldn't connect to channel\n");
		return 0;
	}


	/* Wait until screen create channel */
	delay(1000);
	/* Connect to screen */
	srv_coid = ConnectAttach(0, getpid(), FHZ3conn_chid, 0, _NTO_COF_NOEVENT);
	if (srv_coid == -1) {
		fprintf(stderr, "FHZ3 Couldn't connect to channel\n");
		return 0;
	}

	printf("FHZ3 I'm attached \n");

	/* Receive, identify and replay to message*/
	for (;;) {


		/* Wait until timer will send a pulse */
		MsgReceivePulse(p2_chid, (void *)&pdata, sizeof(pdata), NULL);

		//printf("FHZ4 model thread \n");

		if (FHZ3_curr_interval<server_curr_interval)
		{
			sem_wait(&FHZ3_buff_sem);
			FH_ZONE_MODEL_add_interval(FH_model_Z3, data_buff_Z3);
			FH_ZONE_MODEL_find_operating_point(FH_model_Z3, data_buff_Z3);
			FH_ZONE_MODEL_define_model_delay(FH_model_Z3, data_buff_Z3, FHZ3_section_len);
			FH_ZONE_MODEL_define_model_inputs_Z3(FH_model_Z3, data_buff_Z3);

			if (!FH_model_Z3->model_identified){
				FH_ZONE_MODEL_ident_Z3(FH_model_Z3, data_buff_Z3);
			}
			else {
				FH_ZONE_MODEL_simulate_output_Z3(FH_model_Z3, data_buff_Z3);
				if (FH_ZONE_get_last_model_diff(FH_model_Z3, 4)> model_diff_tr && FH_ZONE_get_last_SP_diff(FH_model_Z3, 4)> sp_diff_tr)
				{
					FH_ZONE_MODEL_reident_Z3(FH_model_Z3, data_buff_Z3);
				}
			}

			if (FH_model_Z3->current_model_nr != FHZ3_current_model_nr){
				FH_ZONE_MODEL_obtain_MPC_model(FH_model_Z3, data_buff_Z3);
			}

			FHZ3_current_model_nr = FH_model_Z3->current_model_nr;
			sem_post(&FHZ3_buff_sem);

			sem_wait(&FHZ3_model_sem);
			FH_ZONE_prepare_data_to_send(FH_model_Z3,(double*)buff_to_send_FHZ3);

			pthread_rwlock_wrlock(&lock);
			FHZ3_curr_interval=server_curr_interval;
			pthread_rwlock_unlock(&lock);

			mq_send(outputMQueue_FHZ3, (const char *)&FH_model_Z3->op_time, sizeof(double), 0);

			sem_post(&FHZ3_model_sem);

			printf("Sending pulse from Z3 \n");
			MsgSendPulse(srv_coid, sched_get_priority_min(SCHED_FIFO), _PULSE_CODE_MAXAVAIL, 0);
			MsgSendPulse(s_coid, sched_get_priority_min(SCHED_FIFO), _PULSE_CODE_MAXAVAIL, 3);

		}
	}

	return 0;
}

