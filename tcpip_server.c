#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


#include <sys/neutrino.h>

#include "tcpip_server.h"
#include "FHZ3_model.h"
#include "FHZ4_model.h"

#include <math.h>
#include <stddef.h>
#include <string.h>
//#include "rt_nonfinite.h"
#include "rtwtypes.h"
//#include "FHZN_find_operating_point_types.h"
//

#include "cyclic_buffer.h"
#include "data_struct.h"
#include "FHZN_model.h"

#include "rt_nonfinite.h"

#define model_diff_tr 500
#define sp_diff_tr 1000

enum RCV_STATUS { IDLE = 0, SIGNAL_0, SIGNAL_1, SIGNAL_2, SIGNAL_3,  SIGNAL_4, SIGNAL_5, SIGNAL_6,
	SIGNAL_7, SIGNAL_8, SIGNAL_9, SIGNAL_10, IDENT, SEND_DATA_Z3, SEND_DATA_Z4, SIMULATION};

/* rwlock variable */
pthread_rwlock_t lock;

/* Global variable */
int setForQuit = 0;

int FHZ3conn_chid;
int FHZ4conn_chid;

unsigned int server_curr_interval = 0;

/* Logger thread prototype */
void *tServerThreadFunc(void *);

/* Thread variable */
pthread_t tServerThread;
/* Thread attributes structure */
pthread_attr_t aServerThreadAttr;

/**
 * Function crates server thread
 */
int init_tcpip_server() {

	int status;


	/* Set server scheduling policy to FIFO */
	pthread_attr_init(&aServerThreadAttr);
	pthread_attr_setschedpolicy(&aServerThreadAttr, SCHED_FIFO);

	/* Create server thread */
	if ((status = pthread_create( &tServerThread, NULL, tServerThreadFunc, &aServerThreadAttr))) {
		fprintf(stderr, "Cannot create thread.\n");
		return 0;
	}

	return 0;
}

/**
 * Server thread function
 */
void *tServerThreadFunc(void *cookie) {

	/* Scheduling policy: FIFO or RR */
	int policy;
	/* Structure of other thread parameters */
	struct sched_param param;
	/* Socket address structure */
	struct sockaddr_in socket_addr;
	/* Socket variable */
	int srv_socket;
	/* Buffer */
	//char buff[2000];
	//double buff_d[300];
	//double buff[100];
	//int value;

	//int rcv_state;

	int rcv_state;
	char buff[data_buffer_size];
	//char buff_to_send[send_buffer_size];

	//int FHZ4_pulse_rec=0;

	//double* buff_to_send_db;

	rcv_state = IDLE;
	double* wsk;

	//unsigned int FHZ3_current_model_nr = 0;
	//unsigned int FHZ4_current_model_nr = 0;



	data_struct* rcv_data_Z3 = DATA_STR_create(struct_capacity);
	//cyclic_buffer* data_buff_Z3 = BUFF_create(max_buffer_size);
	//FHZN_model* FH_model_Z3 = FH_ZONE_MODEL_create();

	data_struct* rcv_data_Z4 = DATA_STR_create(struct_capacity);
	//cyclic_buffer* data_buff_Z4 = BUFF_create(max_buffer_size);
	//FHZN_model* FH_model_Z4 = FH_ZONE_MODEL_create();

	/* Pulse data special structure */
	struct _pulse pdata;


	////////////////////////////////////////////////////////////////////////
	FHZ4conn_chid = ChannelCreate(0);
	printf("FHZ4conn: Channel created\n");
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	FHZ3conn_chid = ChannelCreate(0);
	printf("FHZ3conn: Channel created\n");
	////////////////////////////////////////////////////////////////////////



	/* Read modify and set new thread priority */
	pthread_getschedparam( pthread_self(), &policy, &param);
	param.sched_priority = sched_get_priority_max(policy);
	pthread_setschedparam( pthread_self(), policy, &param);

	/* Initialize socket variable */
	srv_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(srv_socket == -1) {
		fprintf(stderr, "Cannot create socket\n");
		return 0;
	}

	/* Initialize socket address to 0*/
	memset(&socket_addr, 0, sizeof(socket_addr));
	/* Set socket address parameters */
	socket_addr.sin_family = AF_INET;
	socket_addr.sin_port = htons(1100);
	socket_addr.sin_addr.s_addr = INADDR_ANY;

	/* Bind socket to socket address struct */
	if(bind(srv_socket, (struct sockaddr *)&socket_addr, sizeof(socket_addr)) == -1) {
		fprintf(stderr, "Cannot bind socket\n");
		close(srv_socket);
		return 0;
	}

	/* Start to listen on created socket */
	if(listen(srv_socket, 10) == -1) {
		fprintf(stderr, "Cannot start to listen\n");
		close(srv_socket);
		return 0;
	}

	printf("Server is waiting.\n");

	/* Wait until somebody open connection with you */
	int srv_connection = accept(srv_socket, NULL, NULL);

	/* Check if connection is OK */
	if(srv_connection < 0) {
		fprintf(stderr, "Accept connection failed\n");
		close(srv_socket);
		return 0;
	}



	for (;;) {
		/* Read what others want to tell you */

		switch (rcv_state)
		{
		case IDLE:

			//recv(srv_connection, buff, 2, NULL);
			recv(srv_connection, buff, 2, 0);

			if (buff[0] == 'q') {
				//pthread_rwlock_wrlock(&lock);
				printf("I get q\n");
				//setForQuit = 1;
				//pthread_rwlock_unlock(&lock);
			}
			else if (buff[0] == 'r') {
				printf("Srv connection: %d TCP/IP server: I have read string: %s\n", srv_connection, buff);
				//delay(1000);
				send(srv_connection, "a", 1, 0);
			}
			else if ((buff[0] == 'Z') && (buff[1] == 'N')) {
				rcv_state = SIGNAL_0;
			}
			else if ((buff[0] == 'M') && (buff[1] == '3')) {
				rcv_state = SEND_DATA_Z3;
			}
			else if ((buff[0] == 'M') && (buff[1] == '4')) {
				rcv_state = SEND_DATA_Z4;
			}
			else {
				printf("Srv connection: %d TCP/IP server: I have read string: %s\n", srv_connection, buff);
			}

			//rcv_state=IDLE;
			break;

		case SIGNAL_0:

			send(srv_connection, "time", 4, 0);

			for (int total = 0; total < sizeof(buff); )
			{
				int n = recv(srv_connection, buff + total, sizeof(buff) - total, 0);
				if (n < 0) break;
				total += n;
			}

			wsk = (double*)buff;
			DATA_STR_add_time(rcv_data_Z3, buff);
			DATA_STR_add_time(rcv_data_Z4, buff);
			rcv_state = SIGNAL_1;

			break;

		case SIGNAL_1:

			send(srv_connection, "pull", 4, 0);

			for (int total = 0; total < sizeof(buff); )
			{
				int n = recv(srv_connection, buff + total, sizeof(buff) - total, 0);
				if (n < 0) break;
				total += n;
			}

			wsk = (double*)buff;

			DATA_STR_add_pull(rcv_data_Z3, buff);
			DATA_STR_add_pull(rcv_data_Z4, buff);

			rcv_state = SIGNAL_2;
			break;

		case SIGNAL_2:

			send(srv_connection, "z3i1", 4, 0);

			for (int total = 0; total < sizeof(buff); )
			{
				int n = recv(srv_connection, buff + total, sizeof(buff) - total, 0);
				if (n < 0) break;
				total += n;
			}

			wsk = (double*)buff;
			DATA_STR_add_s1(rcv_data_Z3, buff);
			rcv_state = SIGNAL_3;

			break;

		case SIGNAL_3:

			send(srv_connection, "z3i2", 4, 0);

			for (int total = 0; total < sizeof(buff); )
			{
				int n = recv(srv_connection, buff + total, sizeof(buff) - total, 0);
				if (n < 0) break;
				total += n;
			}

			wsk = (double*)buff;
			DATA_STR_add_s2(rcv_data_Z3, buff);
			rcv_state = SIGNAL_4;

			break;

		case SIGNAL_4:

			send(srv_connection, "z3i3", 4, 0);

			for (int total = 0; total < sizeof(buff); )
			{
				int n = recv(srv_connection, buff + total, sizeof(buff) - total, 0);
				if (n < 0) break;
				total += n;
			}

			wsk = (double*)buff;
			DATA_STR_add_s3(rcv_data_Z3, buff);
			rcv_state = SIGNAL_5;

			break;

		case SIGNAL_5:

			send(srv_connection, "z3pv", 4, 0);

			for (int total = 0; total < sizeof(buff); )
			{
				int n = recv(srv_connection, buff + total, sizeof(buff) - total, 0);
				if (n < 0) break;
				total += n;
			}

			wsk = (double*)buff;
			DATA_STR_add_output(rcv_data_Z3, buff);
			rcv_state = SIGNAL_6;

			break;

		case SIGNAL_6:

			send(srv_connection, "z3sp", 4, 0);

			for (int total = 0; total < sizeof(buff); )
			{
				int n = recv(srv_connection, buff + total, sizeof(buff) - total, 0);
				if (n < 0) break;
				total += n;
			}

			wsk = (double*)buff;
			DATA_STR_add_sp(rcv_data_Z3, buff);

			BUFF_add(data_buff_Z3, rcv_data_Z3);

			rcv_state = SIGNAL_7;

			break;

		case SIGNAL_7:

			send(srv_connection, "z4i1", 4, 0);

			for (int total = 0; total < sizeof(buff); )
			{
				int n = recv(srv_connection, buff + total, sizeof(buff) - total, 0);
				if (n < 0) break;
				total += n;
			}

			wsk = (double*)buff;
			DATA_STR_add_s1(rcv_data_Z4,buff);

			rcv_state = SIGNAL_8;
			break;

		case SIGNAL_8:

			//printf("-----Current state SIGNAL_2\n");

			send(srv_connection, "z4i2", 4, 0);

			for (int total = 0; total < sizeof(buff); )
			{
				int n = recv(srv_connection, buff + total, sizeof(buff) - total, 0);
				//printf("After rec 0 %f \n", *((double*)buff));
				if (n < 0) break;
				total += n;
			}

			wsk = (double*)buff;

			DATA_STR_add_s2(rcv_data_Z4, buff);

			rcv_state = SIGNAL_9;
			break;

		case SIGNAL_9:

			send(srv_connection, "z4pv", 4, 0);

			for (int total = 0; total < sizeof(buff); )
			{
				int n = recv(srv_connection, buff + total, sizeof(buff) - total, 0);
				//printf("After rec 0 %f \n", *((double*)buff));
				if (n < 0) break;
				total += n;
			}

			wsk = (double*)buff;

			DATA_STR_add_output(rcv_data_Z4, buff);

			rcv_state = SIGNAL_10;
			break;

		case SIGNAL_10:

			send(srv_connection, "z4sp", 4, 0);

			for (int total = 0; total < sizeof(buff); )
			{
				int n = recv(srv_connection, buff + total, sizeof(buff) - total, 0);
				//printf("After rec 0 %f \n", *((double*)buff));
				if (n < 0) break;
				total += n;
			}

			wsk = (double*)buff;

			DATA_STR_add_sp(rcv_data_Z4, buff);

			sem_wait(&FHZ4_buff_sem);
			BUFF_add(data_buff_Z4, rcv_data_Z4);
			sem_post(&FHZ4_buff_sem);

			//DATA_STR_print(rcv_data_Z4);

			//DATA_STR_print_short(rcv_data_Z4);
			rcv_state = IDLE;

			server_curr_interval+=1;

			break;

		case SEND_DATA_Z3:

			MsgReceivePulse(FHZ3conn_chid, (void *)&pdata, sizeof(pdata), NULL);

			sem_wait(&FHZ3_buff_sem);
			send(srv_connection, buff_to_send_FHZ3, send_buffer_size, 0);
			sem_post(&FHZ3_buff_sem);

			rcv_state = IDLE;
			break;

		case SEND_DATA_Z4:

			MsgReceivePulse(FHZ4conn_chid, (void *)&pdata, sizeof(pdata), 0);

			sem_wait(&FHZ4_buff_sem);
			send(srv_connection, buff_to_send_FHZ4, send_buffer_size, 0);
			sem_post(&FHZ4_buff_sem);

			rcv_state = SIMULATION;
			break;

		case SIMULATION:

			send(srv_connection, "run", 3, 0);
			rcv_state = IDLE;
			break;

		default:
			rcv_state = IDLE;
			break;

		}

	}

	/* Shutdown connection */
	if (shutdown(srv_connection, SHUT_RDWR) == -1) {
		fprintf(stderr, "Cannot shutdown socket\n");
		close(srv_connection);
		return 0;
	}
	close(srv_connection);

	return 0;
}
