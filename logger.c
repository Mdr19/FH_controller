#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/neutrino.h>
#include <mqueue.h>

#include "logger.h"

/* Logger thread prototype */
void *tLoggerThreadFunc(void *);

/* Mqueue variable */
mqd_t outputMQueue_FHZ3;
mqd_t outputMQueue_FHZ4;
/* Mqueue attributes structure */
struct	mq_attr outputMQueueAttr;
/* Thread variable */
pthread_t tLoggerThread;
/* Thread attributes structure */
pthread_attr_t aLoggerThreadAttr;


/**
 * Function crates logger thread
 */
int init_logger() {

	int status;

	/* Set logger scheduling policy to FIFO */
	pthread_attr_init(&aLoggerThreadAttr);
	pthread_attr_setschedpolicy(&aLoggerThreadAttr, SCHED_FIFO);

	/* Set Message Queue size */
	outputMQueueAttr.mq_maxmsg = 4096;
	outputMQueueAttr.mq_msgsize = sizeof(double);

	/* Create Message Queue */
	if ((outputMQueue_FHZ4 = mq_open("/outputMQ_FHZ4", O_CREAT | O_RDWR, 777, &outputMQueueAttr)) == -1) {
		fprintf(stderr, "Creation of the mqueueFHZ4 failed.\n");
		return 0;
	}

	/* Create Message Queue */
	if ((outputMQueue_FHZ3 = mq_open("/outputMQ_FHZ3", O_CREAT | O_RDWR, 777, &outputMQueueAttr)) == -1) {
		fprintf(stderr, "Creation of the mqueueFHZ3 failed.\n");
		return 0;
	}


	/* Create logger thread */
	if ((status = pthread_create( &tLoggerThread, NULL, tLoggerThreadFunc, &aLoggerThreadAttr))) {
		fprintf(stderr, "Cannot create thread.\n");
		return 0;
	}

	return 0;
}

/**
 * Finalize logger
 */
int finalize_logger() {

	/* Close Message Queue */
	mq_close(outputMQueue_FHZ3);
	mq_close(outputMQueue_FHZ4);

	return 0;
}

/**
 * Logger thread function
 */
void *tLoggerThreadFunc(void *cookie) {

	/* Output file descriptor */
	FILE * output_file;
	double i;

	/* Scheduling policy: FIFO or RR */
	int policy;
	/* Structure of other thread parameters */
	struct sched_param param;

	/* Read modify and set new thread priority */
	pthread_getschedparam( pthread_self(), &policy, &param);
	param.sched_priority = sched_get_priority_min(policy);
	pthread_setschedparam( pthread_self(), policy, &param);

	/* Set the fiel header */
	output_file = fopen("sim_result_FHZ4.txt", "w");
	//fprintf(output_file, "Inertial plant simulation result (Ts = 0.1): \n");
	fprintf(output_file, "FHZ4 model parameters: \n");
	fclose(output_file);

	output_file = fopen("sim_result_FHZ3.txt", "w");
	//fprintf(output_file, "Inertial plant simulation result (Ts = 0.1): \n");
	fprintf(output_file, "FHZ3 model parameters: \n");
	fclose(output_file);

	for (;;) {
		/* Wait until something will appears in queue */
		mq_receive(outputMQueue_FHZ4, (char *)&i, sizeof(double), NULL);

		/* Append file with new data */
		output_file = fopen("sim_result_FHZ4.txt", "a");
		fprintf(output_file, "%.10f\n", i);
		fclose(output_file);

		mq_receive(outputMQueue_FHZ3, (char *)&i, sizeof(double), NULL);

		/* Append file with new data */
		output_file = fopen("sim_result_FHZ3.txt", "a");
		fprintf(output_file, "%.10f\n", i);
		fclose(output_file);
	}

	return 0;
}
