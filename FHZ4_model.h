#include "cyclic_buffer.h"
#include "FHZN_model.h"


#ifndef FHZ4_MODEL_H_
#define FHZ4_MODEL_H_



extern sem_t FHZ4_model_sem;
extern sem_t FHZ4_buff_sem;
extern cyclic_buffer* data_buff_Z4;
extern FHZN_model* FH_model_Z4;

//extern int FHZ4_chid;

extern unsigned int FHZ4_curr_interval;
extern unsigned int FHZ4_current_model_nr;
extern char buff_to_send_FHZ4[send_buffer_size];

int init_FHZ4model();


#endif /* FHZ4_MODEL_H_ */
