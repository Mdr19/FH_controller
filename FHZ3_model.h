#include "cyclic_buffer.h"
#include "FHZN_model.h"


#ifndef FHZ3_MODEL_H_
#define FHZ3_MODEL_H_



extern sem_t FHZ3_model_sem;
extern sem_t FHZ3_buff_sem;
extern cyclic_buffer* data_buff_Z3;
extern FHZN_model* FH_model_Z3;

//extern int FHZ4_chid;

extern unsigned int FHZ3_curr_interval;
extern unsigned int FHZ3_current_model_nr;
extern char buff_to_send_FHZ3[send_buffer_size];

int init_FHZ3model();


#endif /* FHZ4_MODEL_H_ */
