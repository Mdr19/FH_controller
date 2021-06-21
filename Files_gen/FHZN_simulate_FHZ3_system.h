/*
 * File: FHZN_simulate_FHZ3_system.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __FHZN_SIMULATE_FHZ3_SYSTEM_H__
#define __FHZN_SIMULATE_FHZ3_SYSTEM_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern void FHZN_simulate_FHZ3_system(const emxArray_FHZ3_DataBuff *dataBuff,
  emxArray_real_T *params_vector, const double model_inputs[3], const
  emxArray_real_T *op_offset, emxArray_real_T *X0_prev, double signal_del,
  double interval_len, double intervals_nr, double obs_intervals, double n,
  double m, double *model_diff, double *sp_diff, emxArray_real_T *X0);

#endif

/*
 * File trailer for FHZN_simulate_FHZ3_system.h
 *
 * [EOF]
 */
