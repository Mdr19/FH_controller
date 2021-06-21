/*
 * File: FHZN_simulate_lsys_output_compare.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __FHZN_SIMULATE_LSYS_OUTPUT_COMPARE_H__
#define __FHZN_SIMULATE_LSYS_OUTPUT_COMPARE_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern double c_FHZN_simulate_lsys_output_com(const emxArray_real_T *A, const
  emxArray_real_T *B, const emxArray_real_T *C, emxArray_real_T *X0, const
  emxArray_real_T *input_signals, const emxArray_real_T *real_output);
extern double d_FHZN_simulate_lsys_output_com(const emxArray_real_T *A, const
  emxArray_real_T *B, const emxArray_real_T *C, emxArray_real_T *X0, const
  emxArray_real_T *input_signals, const emxArray_real_T *real_output);

#endif

/*
 * File trailer for FHZN_simulate_lsys_output_compare.h
 *
 * [EOF]
 */
