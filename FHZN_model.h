#pragma once

#include <stdio.h>

#include "signal_interval.h"
#include "MFM_model.h"
#include "cyclic_buffer.h"

#include "rtwtypes.h"
#include <math.h>
#include <stddef.h>
#include <string.h>

//#include "main.h"

// gen
#include "rt_nonfinite.h"
#include "FHZN_define_model_del.h"
#include "FHZN_define_model_inputs.h"
#include "FHZN_find_operating_point.h"
#include "FHZN_obtain_FHZ4_model.h"
#include "FHZN_obtain_FHZ4_model_nonzero.h"
#include "FHZN_simulate_FHZ4_system.h"

#include "FHZN_obtain_FHZ3_model.h"
#include "FHZN_obtain_FHZ3_model_nonzero.h"
#include "FHZN_simulate_FHZ3_system.h"



#include "FHZN_obtain_MPC_model_FF.h"

// model del
#include "FHZN_define_model_del_terminate.h"
#include "FHZN_define_model_del_emxAPI.h"
#include "FHZN_define_model_del_initialize.h"

#define struct_capacity 250
#define FHZ3_model_inputs_nr 3
#define FHZ4_model_inputs_nr 2
#define FHZN_max_inputs 3

#define FHZ3_section_len 2272
#define FHZ4_section_len 1055

//#define data_buffer_size 2000

#define struct_capacity 250
#define FHZ4_model_inputs_nr 2

#define Laguerre_functions_nr 5
#define Laguerre_function_coef 0.6

#define MPC_Tp 75
#define MPC_h 0.1

#define FHZN_tr_diff 20000
#define FHZN_max_diff 500

//static emxArray_real_T* argInit_Unboundedx1_real_T(void);


typedef struct FHZN_model FHZN_model;

struct FHZN_model 
{
	unsigned int model_inputs[max_model_inputs];
	signal_interval signals_intervals[max_buffer_size];
	//MFM_model current_model_params;

	boolean_T model_identified;
	double* model_params;
	double* X0;
	double op_offset[FHZN_max_inputs +2];
	unsigned int current_model_size;
	unsigned int current_model_nr;

	double* Omega;
	double* Psi;
	double* Gamma;
	double* A;
	double* B;
	double* Bd;
	double* C;
	double* Ap;
	double* Lzerot;
	double* M;

	unsigned int tail;
	unsigned int head;
	unsigned int intervals_nr;
	unsigned int current_interval_nr;

	double op_time;
	unsigned int op_interval_nr;
};

FHZN_model* FH_ZONE_MODEL_create(void);
int FH_ZONE_MODEL_add_interval(FHZN_model* z_model, cyclic_buffer* buff);
void FH_ZONE_MODEL_print_intervals(FHZN_model* z_model);
void FH_ZONE_MODEL_print_current_model(FHZN_model* z_model);

double FH_ZONE_get_last_model_diff(FHZN_model* z_model, int intervals_nr);
double FH_ZONE_get_last_SP_diff(FHZN_model* z_model, int intervals_nr);

//double* FH_ZONE_prepare_data_to_send(FHZN_model* z_model);
void FH_ZONE_prepare_data_to_send(FHZN_model* z_model, double* data_to_send);


void FH_ZONE_MODEL_find_operating_point(FHZN_model* z_model, cyclic_buffer* buff);
void FH_ZONE_MODEL_define_model_delay(FHZN_model* z_model, cyclic_buffer* buff, double section_len);

void FH_ZONE_MODEL_define_model_inputs_Z3(FHZN_model* z_model, cyclic_buffer* buff);
void FH_ZONE_MODEL_ident_Z3(FHZN_model* z_model, cyclic_buffer* buff);
void FH_ZONE_MODEL_reident_Z3(FHZN_model* z_model, cyclic_buffer* buff);
void FH_ZONE_MODEL_simulate_output_Z3(FHZN_model* z_model, cyclic_buffer* buff);


void FH_ZONE_MODEL_define_model_inputs_Z4(FHZN_model* z_model, cyclic_buffer* buff);
void FH_ZONE_MODEL_ident_Z4(FHZN_model* z_model, cyclic_buffer* buff);
void FH_ZONE_MODEL_reident_Z4(FHZN_model* z_model, cyclic_buffer* buff);
void FH_ZONE_MODEL_simulate_output_Z4(FHZN_model* z_model, cyclic_buffer* buff);

void FH_ZONE_MODEL_obtain_MPC_model(FHZN_model* z_model, cyclic_buffer* buff);

