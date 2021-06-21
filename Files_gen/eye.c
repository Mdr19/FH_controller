/*
 * File: eye.c
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
#include "eye.h"
#include "FHZN_define_model_del_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : double varargin_1
 *                double varargin_2
 *                emxArray_real_T *I
 * Return Type  : void
 */
void eye(double varargin_1, double varargin_2, emxArray_real_T *I)
{
  int d;
  int k;
  int loop_ub;
  if (varargin_1 <= varargin_2) {
    d = (int)varargin_1;
  } else {
    d = (int)varargin_2;
  }

  k = I->size[0] * I->size[1];
  I->size[0] = (int)varargin_1;
  I->size[1] = (int)varargin_2;
  emxEnsureCapacity((emxArray__common *)I, k, (int)sizeof(double));
  loop_ub = (int)varargin_1 * (int)varargin_2;
  for (k = 0; k < loop_ub; k++) {
    I->data[k] = 0.0;
  }

  if (d > 0) {
    for (k = 0; k + 1 <= d; k++) {
      I->data[k + I->size[0] * k] = 1.0;
    }
  }
}

/*
 * File trailer for eye.c
 *
 * [EOF]
 */
