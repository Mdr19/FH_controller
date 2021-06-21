#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/neutrino.h>

#include "screen.h"
#include "FHZ3_model.h"
#include "FHZ4_model.h"


/* Screen thread function prototype */
void *tScreenThreadFunc(void *);

/* Thread variable */
pthread_t tScreenThread;
/* Thread attributes */
pthread_attr_t aScreenThreadAttr;
/* Screen channel ID */
int s_chid;

/* Screen thread initialization function */
int init_screen() {

	int status;

	/* Set scheduling policy to FIFO */
	pthread_attr_init(&aScreenThreadAttr);
	pthread_attr_setschedpolicy(&aScreenThreadAttr, SCHED_FIFO);

	/* Create screen thread */
	if ((status = pthread_create(&tScreenThread, NULL, tScreenThreadFunc, &aScreenThreadAttr))) {
		fprintf(stderr, "Cannot create thread.\n");
		return 0;
	}

	return 0;
}

/*
 *  Screen thread function
 */
void *tScreenThreadFunc(void *cookie) {

	/* Pulse data special structure */
	struct _pulse pdata;
	/* Scheduling policy: FIFO or RR */
	int policy;
	/* Structure of other thread parameters */
	struct sched_param param;

	/* Read modify and set new thread priority */
	pthread_getschedparam( pthread_self(), &policy, &param);
	param.sched_priority = sched_get_priority_min(policy);
	pthread_setschedparam( pthread_self(), policy, &param);

	/* Create new channel */
	s_chid = ChannelCreate(0);
	printf("Screen: Channel created\n");

	/* Receive, identify and replay to message*/
	for (;;) {
		/* Wait until you get pulse */
		MsgReceivePulse(s_chid, (void *)&pdata, sizeof(pdata), NULL);

		if (pdata.value.sival_int==3){
		/* Put the input and output value to the screen */
			sem_wait(&FHZ3_model_sem);
			printf("####################### ZONE 3 #######################  \n");
			FH_ZONE_MODEL_print_current_model(FH_model_Z3);
			sem_post(&FHZ3_model_sem);
		}else if(pdata.value.sival_int==4){

			sem_wait(&FHZ4_model_sem);
			printf("####################### ZONE 4 #######################  \n");
			FH_ZONE_MODEL_print_current_model(FH_model_Z4);
			sem_post(&FHZ4_model_sem);
		}
		else{
			printf("--------------------------------------\n");
		}
	}

	return 0;
}
