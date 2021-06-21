#ifndef LOGGER_H_
#define LOGGER_H_

/* Make mqueue of the logger public */
extern mqd_t outputMQueue_FHZ3;
extern mqd_t outputMQueue_FHZ4;

/* Function starts logger thread */
int init_logger();
/* Function close logger */
int finalize_logger();

#endif /* LOGGER_H_ */
