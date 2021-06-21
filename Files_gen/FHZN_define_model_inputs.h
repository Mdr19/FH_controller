/*
 * File: FHZN_define_model_inputs.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __FHZN_DEFINE_MODEL_INPUTS_H__
#define __FHZN_DEFINE_MODEL_INPUTS_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern void FHZN_define_model_inputs(double inputs_nr, double corr_tr, double
  var_tr, const emxArray_real_T *input_signals, const emxArray_real_T
  *output_signal, emxArray_real_T *model_inputs, double *variance, double *corr);

#endif

/*
 * File trailer for FHZN_define_model_inputs.h
 *
 * [EOF]
 */
