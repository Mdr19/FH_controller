# include <stdlib.h>
# include <stdio.h>

#include "signal_interval.h"

/*
int create_signal_interval(signal_interval* interval)
{
	for (int i = 0; i < 3; i++)
	{
		interval->model_inputs[i] = false;
	}

	interval->op_interval_possible = false;
}
*/

void display_signal_interval(signal_interval interval)
{
	printf("model inputs: ");

	for (int i = 0; i < max_model_inputs; i++)
	{
		printf("%d ", interval.model_inputs[i]);
	}

	printf(", op interval possible: %d, op interval time: %d,  interval delay: %d \n", interval.op_interval_possible,
		interval.op_pos_time, interval.model_del);
	//printf("%d \n", interval.op_interval_possible);
}