/*
 * File: FHZN_define_model_del.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "FHZN_define_model_del.h"
#include "FHZN_define_model_inputs.h"
#include "FHZN_find_operating_point.h"
#include "FHZN_obtain_FHZ3_model.h"
#include "FHZN_obtain_FHZ3_model_nonzero.h"
#include "FHZN_obtain_FHZ4_model.h"
#include "FHZN_obtain_FHZ4_model_nonzero.h"
#include "FHZN_obtain_MPC_model_FF.h"
#include "FHZN_simulate_FHZ3_system.h"
#include "FHZN_simulate_FHZ4_system.h"
#include "FHZN_define_model_del_rtwutil.h"

/* Function Definitions */

/*
 * UNTITLED4 Summary of this function goes here
 *    Detailed explanation goes here
 * Arguments    : const emxArray_real_T *pull_signal
 *                double section_len
 *                const double delay_poly[2]
 * Return Type  : double
 */
double FHZN_define_model_del(const emxArray_real_T *pull_signal, double
  section_len, const double delay_poly[2])
{
  double y;
  int k;
  if (pull_signal->size[0] == 0) {
    y = 0.0;
  } else {
    y = pull_signal->data[0];
    for (k = 2; k <= pull_signal->size[0]; k++) {
      y += pull_signal->data[k - 1];
    }
  }

  return rt_roundd_snf(section_len / (delay_poly[0] * (y / (double)
    pull_signal->size[0]) + delay_poly[1]));
}

/*
 * File trailer for FHZN_define_model_del.c
 *
 * [EOF]
 */
