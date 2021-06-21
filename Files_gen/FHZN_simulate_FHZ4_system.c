/*
 * File: FHZN_simulate_FHZ4_system.c
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
#include "FHZN_define_model_del_emxutil.h"
#include "FHZN_simulate_lsys_output_compare.h"
#include "sum.h"
#include "power.h"
#include "FHZN_exact_state_observer_final.h"
#include "FHZN_get_MISO_model.h"
#include "FHZN_shift_signal.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_FHZ4_DataBuff *dataBuff
 *                emxArray_real_T *params_vector
 *                const emxArray_real_T *op_offset
 *                emxArray_real_T *X0_prev
 *                double signal_del
 *                double interval_len
 *                double intervals_nr
 *                double obs_intervals
 *                double n
 *                double m
 *                double *model_diff
 *                double *sp_diff
 *                emxArray_real_T *X0
 * Return Type  : void
 */
void FHZN_simulate_FHZ4_system(const emxArray_FHZ4_DataBuff *dataBuff,
  emxArray_real_T *params_vector, const emxArray_real_T *op_offset,
  emxArray_real_T *X0_prev, double signal_del, double interval_len, double
  intervals_nr, double obs_intervals, double n, double m, double *model_diff,
  double *sp_diff, emxArray_real_T *X0)
{
  int ndbl;
  emxArray_real_T *b_X0_prev;
  int i47;
  double b_op_offset;
  emxArray_real_T *b_params_vector;
  emxArray_real_T *inputs_to_obs;
  double start_interval;
  emxArray_real_T *output_to_obs;
  double j;
  int i;
  emxArray_int32_T *r27;
  double b_i;
  int cdiff;
  int b_n;
  double d16;
  int apnd;
  emxArray_real_T *b_inputs_to_obs;
  emxArray_real_T *c_inputs_to_obs;
  emxArray_real_T *d_inputs_to_obs;
  emxArray_real_T *r28;
  emxArray_real_T *t;
  emxArray_real_T *A;
  emxArray_real_T *B;
  emxArray_real_T *C;
  emxArray_real_T *unusedU0;
  emxArray_real_T *output_signal;
  emxArray_real_T *b_output_signal;
  emxArray_real_T *e_inputs_to_obs;

  /* sp_diff=0; */
  if (1.0 > m - 1.0) {
    ndbl = 0;
  } else {
    ndbl = (int)(m - 1.0);
  }

  emxInit_real_T1(&b_X0_prev, 1);
  i47 = b_X0_prev->size[0];
  b_X0_prev->size[0] = ndbl;
  emxEnsureCapacity((emxArray__common *)b_X0_prev, i47, (int)sizeof(double));
  for (i47 = 0; i47 < ndbl; i47++) {
    b_X0_prev->data[i47] = X0_prev->data[i47];
  }

  i47 = X0_prev->size[0];
  X0_prev->size[0] = b_X0_prev->size[0];
  emxEnsureCapacity((emxArray__common *)X0_prev, i47, (int)sizeof(double));
  ndbl = b_X0_prev->size[0];
  for (i47 = 0; i47 < ndbl; i47++) {
    X0_prev->data[i47] = b_X0_prev->data[i47];
  }

  emxFree_real_T(&b_X0_prev);
  b_op_offset = m + 2.0 * n;
  if (1.0 > b_op_offset) {
    ndbl = 0;
  } else {
    ndbl = (int)b_op_offset;
  }

  emxInit_real_T1(&b_params_vector, 1);
  i47 = b_params_vector->size[0];
  b_params_vector->size[0] = ndbl;
  emxEnsureCapacity((emxArray__common *)b_params_vector, i47, (int)sizeof(double));
  for (i47 = 0; i47 < ndbl; i47++) {
    b_params_vector->data[i47] = params_vector->data[i47];
  }

  i47 = params_vector->size[0];
  params_vector->size[0] = b_params_vector->size[0];
  emxEnsureCapacity((emxArray__common *)params_vector, i47, (int)sizeof(double));
  ndbl = b_params_vector->size[0];
  for (i47 = 0; i47 < ndbl; i47++) {
    params_vector->data[i47] = b_params_vector->data[i47];
  }

  emxFree_real_T(&b_params_vector);
  emxInit_real_T(&inputs_to_obs, 2);
  start_interval = (intervals_nr - obs_intervals) + 1.0;
  i47 = inputs_to_obs->size[0] * inputs_to_obs->size[1];
  inputs_to_obs->size[0] = (int)(obs_intervals * interval_len);
  inputs_to_obs->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)inputs_to_obs, i47, (int)sizeof(double));
  ndbl = (int)(obs_intervals * interval_len) << 1;
  for (i47 = 0; i47 < ndbl; i47++) {
    inputs_to_obs->data[i47] = 0.0;
  }

  emxInit_real_T1(&output_to_obs, 1);
  i47 = output_to_obs->size[0];
  output_to_obs->size[0] = (int)(obs_intervals * interval_len);
  emxEnsureCapacity((emxArray__common *)output_to_obs, i47, (int)sizeof(double));
  ndbl = (int)(obs_intervals * interval_len);
  for (i47 = 0; i47 < ndbl; i47++) {
    output_to_obs->data[i47] = 0.0;
  }

  j = 1.0;
  i47 = (int)(intervals_nr + (1.0 - start_interval));
  i = 0;
  emxInit_int32_T(&r27, 2);
  while (i <= i47 - 1) {
    b_i = start_interval + (double)i;
    b_op_offset = (j - 1.0) * interval_len + 1.0;
    if (b_op_offset > interval_len * j) {
      cdiff = 0;
    } else {
      cdiff = (int)b_op_offset - 1;
    }

    ndbl = dataBuff->data[(int)b_i - 1].input_1->size[0];
    for (b_n = 0; b_n < ndbl; b_n++) {
      inputs_to_obs->data[cdiff + b_n] = dataBuff->data[(int)b_i - 1]
        .input_1->data[b_n];
    }

    b_op_offset = (j - 1.0) * interval_len + 1.0;
    if (b_op_offset > interval_len * j) {
      cdiff = 0;
    } else {
      cdiff = (int)b_op_offset - 1;
    }

    ndbl = dataBuff->data[(int)b_i - 1].input_2->size[0];
    for (b_n = 0; b_n < ndbl; b_n++) {
      inputs_to_obs->data[(cdiff + b_n) + inputs_to_obs->size[0]] =
        dataBuff->data[(int)b_i - 1].input_2->data[b_n];
    }

    b_op_offset = (j - 1.0) * interval_len + 1.0;
    d16 = interval_len * j;
    if (b_op_offset > d16) {
      cdiff = 0;
      b_n = 0;
    } else {
      cdiff = (int)b_op_offset - 1;
      b_n = (int)d16;
    }

    apnd = r27->size[0] * r27->size[1];
    r27->size[0] = 1;
    r27->size[1] = b_n - cdiff;
    emxEnsureCapacity((emxArray__common *)r27, apnd, (int)sizeof(int));
    ndbl = b_n - cdiff;
    for (b_n = 0; b_n < ndbl; b_n++) {
      r27->data[r27->size[0] * b_n] = cdiff + b_n;
    }

    ndbl = r27->size[0] * r27->size[1];
    for (cdiff = 0; cdiff < ndbl; cdiff++) {
      output_to_obs->data[r27->data[cdiff]] = dataBuff->data[(int)b_i - 1].
        output->data[cdiff];
    }

    j++;
    i++;
  }

  emxFree_int32_T(&r27);
  emxInit_real_T1(&b_inputs_to_obs, 1);

  /* { */
  /* for i=1:model_inputs_nr */
  /*     inputs_to_obs(:,i)=inputs_to_obs(:,i)-op_offset(i); */
  /* end */
  /* } */
  ndbl = inputs_to_obs->size[0];
  b_op_offset = op_offset->data[0];
  i47 = b_inputs_to_obs->size[0];
  b_inputs_to_obs->size[0] = ndbl;
  emxEnsureCapacity((emxArray__common *)b_inputs_to_obs, i47, (int)sizeof(double));
  for (i47 = 0; i47 < ndbl; i47++) {
    b_inputs_to_obs->data[i47] = inputs_to_obs->data[i47] - b_op_offset;
  }

  ndbl = b_inputs_to_obs->size[0];
  for (i47 = 0; i47 < ndbl; i47++) {
    inputs_to_obs->data[i47] = b_inputs_to_obs->data[i47];
  }

  emxFree_real_T(&b_inputs_to_obs);
  emxInit_real_T1(&c_inputs_to_obs, 1);
  ndbl = inputs_to_obs->size[0];
  b_op_offset = op_offset->data[1];
  i47 = c_inputs_to_obs->size[0];
  c_inputs_to_obs->size[0] = ndbl;
  emxEnsureCapacity((emxArray__common *)c_inputs_to_obs, i47, (int)sizeof(double));
  for (i47 = 0; i47 < ndbl; i47++) {
    c_inputs_to_obs->data[i47] = inputs_to_obs->data[i47 + inputs_to_obs->size[0]]
      - b_op_offset;
  }

  ndbl = c_inputs_to_obs->size[0];
  for (i47 = 0; i47 < ndbl; i47++) {
    inputs_to_obs->data[i47 + inputs_to_obs->size[0]] = c_inputs_to_obs->
      data[i47];
  }

  emxFree_real_T(&c_inputs_to_obs);
  emxInit_real_T1(&d_inputs_to_obs, 1);
  ndbl = inputs_to_obs->size[0];
  i47 = d_inputs_to_obs->size[0];
  d_inputs_to_obs->size[0] = ndbl;
  emxEnsureCapacity((emxArray__common *)d_inputs_to_obs, i47, (int)sizeof(double));
  for (i47 = 0; i47 < ndbl; i47++) {
    d_inputs_to_obs->data[i47] = inputs_to_obs->data[i47];
  }

  emxInit_real_T1(&r28, 1);
  FHZN_shift_signal(d_inputs_to_obs, signal_del, r28);
  ndbl = r28->size[0];
  emxFree_real_T(&d_inputs_to_obs);
  for (i47 = 0; i47 < ndbl; i47++) {
    inputs_to_obs->data[i47] = r28->data[i47];
  }

  b_op_offset = op_offset->data[2];
  i47 = output_to_obs->size[0];
  emxEnsureCapacity((emxArray__common *)output_to_obs, i47, (int)sizeof(double));
  ndbl = output_to_obs->size[0];
  for (i47 = 0; i47 < ndbl; i47++) {
    output_to_obs->data[i47] -= b_op_offset;
  }

  if (output_to_obs->size[0] - 1 < 0) {
    b_n = 0;
    apnd = output_to_obs->size[0] - 1;
  } else {
    ndbl = (int)floor(((double)output_to_obs->size[0] - 1.0) + 0.5);
    apnd = ndbl;
    cdiff = (ndbl - output_to_obs->size[0]) + 1;
    if (fabs(cdiff) < 4.4408920985006262E-16 * fabs((double)output_to_obs->size
         [0] - 1.0)) {
      ndbl++;
      apnd = output_to_obs->size[0] - 1;
    } else if (cdiff > 0) {
      apnd = ndbl - 1;
    } else {
      ndbl++;
    }

    if (ndbl >= 0) {
      b_n = ndbl;
    } else {
      b_n = 0;
    }
  }

  emxInit_real_T(&t, 2);
  i47 = t->size[0] * t->size[1];
  t->size[0] = 1;
  t->size[1] = b_n;
  emxEnsureCapacity((emxArray__common *)t, i47, (int)sizeof(double));
  if (b_n > 0) {
    t->data[0] = 0.0;
    if (b_n > 1) {
      t->data[b_n - 1] = apnd;
      i47 = b_n - 1;
      ndbl = i47 / 2;
      for (cdiff = 1; cdiff < ndbl; cdiff++) {
        t->data[cdiff] = cdiff;
        t->data[(b_n - cdiff) - 1] = apnd - cdiff;
      }

      if (ndbl << 1 == b_n - 1) {
        t->data[ndbl] = (double)apnd / 2.0;
      } else {
        t->data[ndbl] = ndbl;
        t->data[ndbl + 1] = apnd - ndbl;
      }
    }
  }

  emxInit_real_T(&A, 2);
  emxInit_real_T(&B, 2);
  emxInit_real_T(&C, 2);
  emxInit_real_T(&unusedU0, 2);
  b_FHZN_get_MISO_model(params_vector, n, m, A, B, C, unusedU0);
  b_FHZN_exact_state_observer_fin(A, B, C, t, inputs_to_obs, output_to_obs, X0);
  b_op_offset = ((double)inputs_to_obs->size[0] - interval_len) + 1.0;
  emxFree_real_T(&unusedU0);
  emxFree_real_T(&t);
  if (b_op_offset > inputs_to_obs->size[0]) {
    i47 = 0;
    cdiff = 0;
  } else {
    i47 = (int)b_op_offset - 1;
    cdiff = inputs_to_obs->size[0];
  }

  b_op_offset = ((double)output_to_obs->size[0] - interval_len) + 1.0;
  if (b_op_offset > output_to_obs->size[0]) {
    b_n = 0;
    apnd = 0;
  } else {
    b_n = (int)b_op_offset - 1;
    apnd = output_to_obs->size[0];
  }

  emxInit_real_T1(&output_signal, 1);
  ndbl = output_signal->size[0];
  output_signal->size[0] = apnd - b_n;
  emxEnsureCapacity((emxArray__common *)output_signal, ndbl, (int)sizeof(double));
  ndbl = apnd - b_n;
  for (apnd = 0; apnd < ndbl; apnd++) {
    output_signal->data[apnd] = output_to_obs->data[b_n + apnd];
  }

  emxInit_real_T1(&b_output_signal, 1);

  /* check the sp diff */
  /* for i=1:length(output_signal) */
  /*     sp_diff=sp_diff+(output_signal(i)-sp_signal(i))^2; */
  /* end */
  b_op_offset = op_offset->data[3];
  b_n = b_output_signal->size[0];
  b_output_signal->size[0] = output_signal->size[0];
  emxEnsureCapacity((emxArray__common *)b_output_signal, b_n, (int)sizeof(double));
  ndbl = output_signal->size[0];
  for (b_n = 0; b_n < ndbl; b_n++) {
    b_output_signal->data[b_n] = output_signal->data[b_n] - (dataBuff->data[(int)
      intervals_nr - 1].sp_value->data[b_n] - b_op_offset);
  }

  b_power(b_output_signal, r28);
  *sp_diff = b_sum(r28);
  b_n = output_to_obs->size[0];
  output_to_obs->size[0] = X0_prev->size[0];
  emxEnsureCapacity((emxArray__common *)output_to_obs, b_n, (int)sizeof(double));
  ndbl = X0_prev->size[0];
  emxFree_real_T(&b_output_signal);
  emxFree_real_T(&r28);
  for (b_n = 0; b_n < ndbl; b_n++) {
    output_to_obs->data[b_n] = X0_prev->data[b_n];
  }

  emxInit_real_T(&e_inputs_to_obs, 2);
  b_n = e_inputs_to_obs->size[0] * e_inputs_to_obs->size[1];
  e_inputs_to_obs->size[0] = cdiff - i47;
  e_inputs_to_obs->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)e_inputs_to_obs, b_n, (int)sizeof(double));
  for (b_n = 0; b_n < 2; b_n++) {
    ndbl = cdiff - i47;
    for (apnd = 0; apnd < ndbl; apnd++) {
      e_inputs_to_obs->data[apnd + e_inputs_to_obs->size[0] * b_n] =
        inputs_to_obs->data[(i47 + apnd) + inputs_to_obs->size[0] * b_n];
    }
  }

  emxFree_real_T(&inputs_to_obs);
  *model_diff = d_FHZN_simulate_lsys_output_com(A, B, C, output_to_obs,
    e_inputs_to_obs, output_signal);
  emxFree_real_T(&e_inputs_to_obs);
  emxFree_real_T(&C);
  emxFree_real_T(&B);
  emxFree_real_T(&A);
  emxFree_real_T(&output_signal);
  emxFree_real_T(&output_to_obs);
}

/*
 * File trailer for FHZN_simulate_FHZ4_system.c
 *
 * [EOF]
 */
