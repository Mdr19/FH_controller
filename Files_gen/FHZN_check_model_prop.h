/*
 * File: FHZN_check_model_prop.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __FHZN_CHECK_MODEL_PROP_H__
#define __FHZN_CHECK_MODEL_PROP_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern boolean_T FHZN_check_model_prop(const emxArray_real_T *params_vector,
  double model_inputs_nr, const double model_inputs[3], double n, const double
  input_signs[3]);
extern boolean_T b_FHZN_check_model_prop(const emxArray_real_T *params_vector,
  double n);

#endif

/*
 * File trailer for FHZN_check_model_prop.h
 *
 * [EOF]
 */
