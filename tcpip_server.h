#ifndef TCPIP_SERVER_H_
#define TCPIP_SERVER_H_

/* rwlock variable */
extern pthread_rwlock_t lock;

/* Global variable */
extern int setForQuit;

extern int FHZ3conn_chid;
extern int FHZ4conn_chid;

extern unsigned int server_curr_interval;

int init_tcpip_server();

#endif /* TCPIP_SERVER_H_ */
