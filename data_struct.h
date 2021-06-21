#pragma once

#define data_buffer_size 2000
#define send_buffer_size 3000

typedef struct data_struct data_struct;

struct data_struct {
	//double test;
	//double test_2;
	unsigned int signals_len;
	double* input_signal_1;
	double* input_signal_2;
	double* input_signal_3;
	double* output_signal;
	double* sp_signal;
	double* pull_signal;
	double* time;
};

data_struct* DATA_STR_create(unsigned int capacity);
void DATA_STR_free(data_struct*);
int DATA_STR_init_random(data_struct* str);
void DATA_STR_print(const data_struct* str);
void DATA_STR_print_short(const data_struct* str);
data_struct DATA_STR_copy(const data_struct* original_str);
int DATA_STR_add_s1(data_struct* str, char* buff);
int DATA_STR_add_s2(data_struct* str, char* buff);
int DATA_STR_add_s3(data_struct* str, char* buff);
int DATA_STR_add_output(data_struct* str, char* buff);
int DATA_STR_add_sp(data_struct* str, char* buff);
int DATA_STR_add_pull(data_struct* str, char* buff);
int DATA_STR_add_time(data_struct* str, char* buff);