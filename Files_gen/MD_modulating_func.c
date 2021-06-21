/*
 * File: MD_modulating_func.c
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
#include "MD_modulating_func.h"
#include "FHZN_define_model_del_emxutil.h"
#include "power.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *t
 *                double h
 *                double N
 *                double M
 *                emxArray_real_T *y
 * Return Type  : void
 */
void MD_modulating_func(const emxArray_real_T *t, double h, double N, double M,
  emxArray_real_T *y)
{
  emxArray_real_T *b_h;
  int b_y;
  int loop_ub;
  emxArray_real_T *r0;
  emxInit_real_T(&b_h, 2);
  power(t, N, y);
  b_y = b_h->size[0] * b_h->size[1];
  b_h->size[0] = 1;
  b_h->size[1] = t->size[1];
  emxEnsureCapacity((emxArray__common *)b_h, b_y, (int)sizeof(double));
  loop_ub = t->size[0] * t->size[1];
  for (b_y = 0; b_y < loop_ub; b_y++) {
    b_h->data[b_y] = h - t->data[b_y];
  }

  emxInit_real_T(&r0, 2);
  power(b_h, M, r0);
  b_y = y->size[0] * y->size[1];
  y->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)y, b_y, (int)sizeof(double));
  b_y = y->size[0];
  loop_ub = y->size[1];
  loop_ub *= b_y;
  emxFree_real_T(&b_h);
  for (b_y = 0; b_y < loop_ub; b_y++) {
    y->data[b_y] *= r0->data[b_y];
  }

  emxFree_real_T(&r0);
}

/*
 * File trailer for MD_modulating_func.c
 *
 * [EOF]
 */
