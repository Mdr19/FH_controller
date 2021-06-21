/*
 * File: FHZN_find_operating_point.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __FHZN_FIND_OPERATING_POINT_H__
#define __FHZN_FIND_OPERATING_POINT_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern void FHZN_find_operating_point(double threshold, double mean_interval,
  double h_lin, double m, double N_lin, double M_lin, const emxArray_real_T
  *current_out, double start_int_time, boolean_T *op_interval_possible, double
  *op_time);

#endif

/*
 * File trailer for FHZN_find_operating_point.h
 *
 * [EOF]
 */
