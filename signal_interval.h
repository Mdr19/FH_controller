#pragma once

//#include <stdbool.h>
#include "Files_gen/rtwtypes.h"

#define max_model_inputs 3

typedef struct signal_interval signal_interval;


struct signal_interval 
{
	unsigned int model_inputs[max_model_inputs];
	boolean_T op_interval_possible;
	unsigned int op_pos_time;
	unsigned int model_del;

	double sp_diff;
	double model_diff;
};

void display_signal_interval(signal_interval interval);

//int create_signal_interval(signal_interval* interval);
