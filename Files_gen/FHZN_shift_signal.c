/*
 * File: FHZN_shift_signal.c
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
#include "FHZN_shift_signal.h"
#include "FHZN_define_model_del_emxutil.h"

/* Function Definitions */

/*
 * UNTITLED6 Summary of this function goes here
 *    Detailed explanation goes here
 * Arguments    : const emxArray_real_T *b_signal
 *                double signal_del
 *                emxArray_real_T *signal_shifted
 * Return Type  : void
 */
void FHZN_shift_signal(const emxArray_real_T *b_signal, double signal_del,
  emxArray_real_T *signal_shifted)
{
  unsigned int unnamed_idx_0;
  int i3;
  int loop_ub;
  double b_signal_shifted;
  int i4;
  emxArray_int32_T *r4;
  unnamed_idx_0 = (unsigned int)b_signal->size[0];
  i3 = signal_shifted->size[0];
  signal_shifted->size[0] = (int)unnamed_idx_0;
  emxEnsureCapacity((emxArray__common *)signal_shifted, i3, (int)sizeof(double));
  loop_ub = (int)unnamed_idx_0;
  for (i3 = 0; i3 < loop_ub; i3++) {
    signal_shifted->data[i3] = 0.0;
  }

  b_signal_shifted = (double)b_signal->size[0] - signal_del;
  if (1.0 > b_signal_shifted) {
    loop_ub = -1;
  } else {
    loop_ub = (int)b_signal_shifted - 1;
  }

  if (signal_del + 1.0 > (int)unnamed_idx_0) {
    i3 = 0;
  } else {
    i3 = (int)(signal_del + 1.0) - 1;
  }

  for (i4 = 0; i4 <= loop_ub; i4++) {
    signal_shifted->data[i3 + i4] = b_signal->data[i4];
  }

  if (1.0 > signal_del) {
    loop_ub = 0;
  } else {
    loop_ub = (int)signal_del;
  }

  emxInit_int32_T(&r4, 2);
  i3 = r4->size[0] * r4->size[1];
  r4->size[0] = 1;
  r4->size[1] = loop_ub;
  emxEnsureCapacity((emxArray__common *)r4, i3, (int)sizeof(int));
  for (i3 = 0; i3 < loop_ub; i3++) {
    r4->data[r4->size[0] * i3] = i3;
  }

  b_signal_shifted = signal_shifted->data[(int)(signal_del + 1.0) - 1];
  loop_ub = r4->size[0] * r4->size[1];
  for (i3 = 0; i3 < loop_ub; i3++) {
    signal_shifted->data[r4->data[i3]] = b_signal_shifted;
  }

  emxFree_int32_T(&r4);
}

/*
 * File trailer for FHZN_shift_signal.c
 *
 * [EOF]
 */
