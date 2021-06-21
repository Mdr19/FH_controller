#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/neutrino.h>
#include <semaphore.h>
#include <mqueue.h>
#include <pthread.h>

#include "screen.h"
#include "tcpip_server.h"
#include "logger.h"

#include "data_struct.h"
#include "cyclic_buffer.h"

#include "FHZ3_model.h"
#include "FHZ4_model.h"

/*
 * Main project function
 */

data_struct* data_str;

int main(int argc, char *argv[]) {

	/* Copy */
    int copy;

    /* Init screen thread */
    init_screen();
    /* Init tcpip server */
	init_tcpip_server();
	/* Init logger thread */
	init_logger();
	/* Wait until servers create channels */
	//delay(1000);
	/* Start periodic task */
	//init_periodic();
	delay(1000);
	/* Start FHZ3 model task */
	init_FHZ3model();
	delay(1000);
	/* Start FHZ4 model task */
	init_FHZ4model();

	printf("Modified 23.05 \n");

	/* Get the char from keyboard and send it to keyboard thread */
	for (;;) {

		pthread_rwlock_rdlock(&lock);
		copy = setForQuit;
		pthread_rwlock_unlock(&lock);

		if (copy)
			break;
		delay(1000);
	}

  	/* Close logger thread */
	finalize_logger();

	return EXIT_SUCCESS;
}
