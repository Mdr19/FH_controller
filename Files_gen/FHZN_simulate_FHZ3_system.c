/*
 * File: FHZN_simulate_FHZ3_system.c
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
 * Arguments    : const emxArray_FHZ3_DataBuff *dataBuff
 *                emxArray_real_T *params_vector
 *                const double model_inputs[3]
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
void FHZN_simulate_FHZ3_system(const emxArray_FHZ3_DataBuff *dataBuff,
  emxArray_real_T *params_vector, const double model_inputs[3], const
  emxArray_real_T *op_offset, emxArray_real_T *X0_prev, double signal_del,
  double interval_len, double intervals_nr, double obs_intervals, double n,
  double m, double *model_diff, double *sp_diff, emxArray_real_T *X0)
{
  double current_inputs_nr;
  int loop_ub;
  emxArray_real_T *b_X0_prev;
  int i44;
  double b_op_offset;
  emxArray_real_T *b_params_vector;
  emxArray_real_T *inputs_to_obs;
  emxArray_real_T *output_to_obs;
  double j;
  int i;
  emxArray_int32_T *r21;
  int b_n;
  double d15;
  int apnd;
  emxArray_real_T *b_inputs_to_obs;
  int ndbl;
  emxArray_real_T *c_inputs_to_obs;
  emxArray_real_T *d_inputs_to_obs;
  emxArray_real_T *e_inputs_to_obs;
  emxArray_real_T *r22;
  emxArray_real_T *f_inputs_to_obs;
  int cdiff;
  emxArray_real_T *b_output_to_obs;
  emxArray_real_T *t;
  emxArray_real_T *obs_inputs;
  emxArray_real_T *g_inputs_to_obs;
  emxArray_real_T *h_inputs_to_obs;
  emxArray_real_T *i_inputs_to_obs;
  emxArray_real_T *j_inputs_to_obs;
  emxArray_real_T *k_inputs_to_obs;
  emxArray_real_T *l_inputs_to_obs;
  emxArray_real_T *m_inputs_to_obs;
  emxArray_real_T *n_inputs_to_obs;
  emxArray_real_T *o_inputs_to_obs;
  int b_loop_ub;
  emxArray_real_T *A;
  emxArray_real_T *B;
  emxArray_real_T *C;
  emxArray_real_T *unusedU0;
  emxArray_real_T *output_signal;
  emxArray_real_T *b_output_signal;
  emxArray_real_T *b_obs_inputs;
  current_inputs_nr = sum(model_inputs);
  if (1.0 > m - 1.0) {
    loop_ub = 0;
  } else {
    loop_ub = (int)(m - 1.0);
  }

  emxInit_real_T1(&b_X0_prev, 1);
  i44 = b_X0_prev->size[0];
  b_X0_prev->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)b_X0_prev, i44, (int)sizeof(double));
  for (i44 = 0; i44 < loop_ub; i44++) {
    b_X0_prev->data[i44] = X0_prev->data[i44];
  }

  i44 = X0_prev->size[0];
  X0_prev->size[0] = b_X0_prev->size[0];
  emxEnsureCapacity((emxArray__common *)X0_prev, i44, (int)sizeof(double));
  loop_ub = b_X0_prev->size[0];
  for (i44 = 0; i44 < loop_ub; i44++) {
    X0_prev->data[i44] = b_X0_prev->data[i44];
  }

  emxFree_real_T(&b_X0_prev);
  b_op_offset = m + current_inputs_nr * n;
  if (1.0 > b_op_offset) {
    loop_ub = 0;
  } else {
    loop_ub = (int)b_op_offset;
  }

  emxInit_real_T1(&b_params_vector, 1);
  i44 = b_params_vector->size[0];
  b_params_vector->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)b_params_vector, i44, (int)sizeof(double));
  for (i44 = 0; i44 < loop_ub; i44++) {
    b_params_vector->data[i44] = params_vector->data[i44];
  }

  i44 = params_vector->size[0];
  params_vector->size[0] = b_params_vector->size[0];
  emxEnsureCapacity((emxArray__common *)params_vector, i44, (int)sizeof(double));
  loop_ub = b_params_vector->size[0];
  for (i44 = 0; i44 < loop_ub; i44++) {
    params_vector->data[i44] = b_params_vector->data[i44];
  }

  emxFree_real_T(&b_params_vector);
  emxInit_real_T(&inputs_to_obs, 2);

  /* start_interval=intervals_nr-obs_intervals+1; */
  i44 = inputs_to_obs->size[0] * inputs_to_obs->size[1];
  inputs_to_obs->size[0] = (int)(intervals_nr * interval_len);
  inputs_to_obs->size[1] = 3;
  emxEnsureCapacity((emxArray__common *)inputs_to_obs, i44, (int)sizeof(double));
  loop_ub = (int)(intervals_nr * interval_len) * 3;
  for (i44 = 0; i44 < loop_ub; i44++) {
    inputs_to_obs->data[i44] = 0.0;
  }

  emxInit_real_T1(&output_to_obs, 1);
  i44 = output_to_obs->size[0];
  output_to_obs->size[0] = (int)(intervals_nr * interval_len);
  emxEnsureCapacity((emxArray__common *)output_to_obs, i44, (int)sizeof(double));
  loop_ub = (int)(intervals_nr * interval_len);
  for (i44 = 0; i44 < loop_ub; i44++) {
    output_to_obs->data[i44] = 0.0;
  }

  j = 1.0;
  i = 0;
  emxInit_int32_T(&r21, 2);
  while (i <= (int)intervals_nr - 1) {
    b_op_offset = (j - 1.0) * interval_len + 1.0;
    if (b_op_offset > interval_len * j) {
      i44 = 0;
    } else {
      i44 = (int)b_op_offset - 1;
    }

    loop_ub = dataBuff->data[i].input_1->size[0];
    for (b_n = 0; b_n < loop_ub; b_n++) {
      inputs_to_obs->data[i44 + b_n] = dataBuff->data[i].input_1->data[b_n];
    }

    b_op_offset = (j - 1.0) * interval_len + 1.0;
    if (b_op_offset > interval_len * j) {
      i44 = 0;
    } else {
      i44 = (int)b_op_offset - 1;
    }

    loop_ub = dataBuff->data[i].input_2->size[0];
    for (b_n = 0; b_n < loop_ub; b_n++) {
      inputs_to_obs->data[(i44 + b_n) + inputs_to_obs->size[0]] = dataBuff->
        data[i].input_2->data[b_n];
    }

    b_op_offset = (j - 1.0) * interval_len + 1.0;
    if (b_op_offset > interval_len * j) {
      i44 = 0;
    } else {
      i44 = (int)b_op_offset - 1;
    }

    loop_ub = dataBuff->data[i].input_3->size[0];
    for (b_n = 0; b_n < loop_ub; b_n++) {
      inputs_to_obs->data[(i44 + b_n) + (inputs_to_obs->size[0] << 1)] =
        dataBuff->data[i].input_3->data[b_n];
    }

    b_op_offset = (j - 1.0) * interval_len + 1.0;
    d15 = interval_len * j;
    if (b_op_offset > d15) {
      i44 = 0;
      b_n = 0;
    } else {
      i44 = (int)b_op_offset - 1;
      b_n = (int)d15;
    }

    apnd = r21->size[0] * r21->size[1];
    r21->size[0] = 1;
    r21->size[1] = b_n - i44;
    emxEnsureCapacity((emxArray__common *)r21, apnd, (int)sizeof(int));
    loop_ub = b_n - i44;
    for (b_n = 0; b_n < loop_ub; b_n++) {
      r21->data[r21->size[0] * b_n] = i44 + b_n;
    }

    loop_ub = r21->size[0] * r21->size[1];
    for (i44 = 0; i44 < loop_ub; i44++) {
      output_to_obs->data[r21->data[i44]] = dataBuff->data[i].output->data[i44];
    }

    j++;
    i++;
  }

  emxFree_int32_T(&r21);
  emxInit_real_T1(&b_inputs_to_obs, 1);

  /* { */
  /* for i=1:model_inputs_nr */
  /*     inputs_to_obs(:,i)=inputs_to_obs(:,i)-op_offset(i); */
  /* end */
  /* } */
  ndbl = inputs_to_obs->size[0];
  b_op_offset = op_offset->data[0];
  i44 = b_inputs_to_obs->size[0];
  b_inputs_to_obs->size[0] = ndbl;
  emxEnsureCapacity((emxArray__common *)b_inputs_to_obs, i44, (int)sizeof(double));
  for (i44 = 0; i44 < ndbl; i44++) {
    b_inputs_to_obs->data[i44] = inputs_to_obs->data[i44] - b_op_offset;
  }

  loop_ub = b_inputs_to_obs->size[0];
  for (i44 = 0; i44 < loop_ub; i44++) {
    inputs_to_obs->data[i44] = b_inputs_to_obs->data[i44];
  }

  emxFree_real_T(&b_inputs_to_obs);
  emxInit_real_T1(&c_inputs_to_obs, 1);
  ndbl = inputs_to_obs->size[0];
  b_op_offset = op_offset->data[1];
  i44 = c_inputs_to_obs->size[0];
  c_inputs_to_obs->size[0] = ndbl;
  emxEnsureCapacity((emxArray__common *)c_inputs_to_obs, i44, (int)sizeof(double));
  for (i44 = 0; i44 < ndbl; i44++) {
    c_inputs_to_obs->data[i44] = inputs_to_obs->data[i44 + inputs_to_obs->size[0]]
      - b_op_offset;
  }

  loop_ub = c_inputs_to_obs->size[0];
  for (i44 = 0; i44 < loop_ub; i44++) {
    inputs_to_obs->data[i44 + inputs_to_obs->size[0]] = c_inputs_to_obs->
      data[i44];
  }

  emxFree_real_T(&c_inputs_to_obs);
  emxInit_real_T1(&d_inputs_to_obs, 1);
  ndbl = inputs_to_obs->size[0];
  b_op_offset = op_offset->data[2];
  i44 = d_inputs_to_obs->size[0];
  d_inputs_to_obs->size[0] = ndbl;
  emxEnsureCapacity((emxArray__common *)d_inputs_to_obs, i44, (int)sizeof(double));
  for (i44 = 0; i44 < ndbl; i44++) {
    d_inputs_to_obs->data[i44] = inputs_to_obs->data[i44 + (inputs_to_obs->size
      [0] << 1)] - b_op_offset;
  }

  loop_ub = d_inputs_to_obs->size[0];
  for (i44 = 0; i44 < loop_ub; i44++) {
    inputs_to_obs->data[i44 + (inputs_to_obs->size[0] << 1)] =
      d_inputs_to_obs->data[i44];
  }

  emxFree_real_T(&d_inputs_to_obs);
  emxInit_real_T1(&e_inputs_to_obs, 1);
  loop_ub = inputs_to_obs->size[0];
  i44 = e_inputs_to_obs->size[0];
  e_inputs_to_obs->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)e_inputs_to_obs, i44, (int)sizeof(double));
  for (i44 = 0; i44 < loop_ub; i44++) {
    e_inputs_to_obs->data[i44] = inputs_to_obs->data[i44];
  }

  emxInit_real_T1(&r22, 1);
  FHZN_shift_signal(e_inputs_to_obs, signal_del, r22);
  loop_ub = r22->size[0];
  emxFree_real_T(&e_inputs_to_obs);
  for (i44 = 0; i44 < loop_ub; i44++) {
    inputs_to_obs->data[i44] = r22->data[i44];
  }

  b_op_offset = op_offset->data[3];
  i44 = output_to_obs->size[0];
  emxEnsureCapacity((emxArray__common *)output_to_obs, i44, (int)sizeof(double));
  loop_ub = output_to_obs->size[0];
  for (i44 = 0; i44 < loop_ub; i44++) {
    output_to_obs->data[i44] -= b_op_offset;
  }

  b_op_offset = ((double)inputs_to_obs->size[0] - obs_intervals * interval_len)
    + 1.0;
  if (b_op_offset > inputs_to_obs->size[0]) {
    i44 = 0;
    b_n = 0;
  } else {
    i44 = (int)b_op_offset - 1;
    b_n = inputs_to_obs->size[0];
  }

  emxInit_real_T(&f_inputs_to_obs, 2);
  apnd = f_inputs_to_obs->size[0] * f_inputs_to_obs->size[1];
  f_inputs_to_obs->size[0] = b_n - i44;
  f_inputs_to_obs->size[1] = 3;
  emxEnsureCapacity((emxArray__common *)f_inputs_to_obs, apnd, (int)sizeof
                    (double));
  for (apnd = 0; apnd < 3; apnd++) {
    loop_ub = b_n - i44;
    for (cdiff = 0; cdiff < loop_ub; cdiff++) {
      f_inputs_to_obs->data[cdiff + f_inputs_to_obs->size[0] * apnd] =
        inputs_to_obs->data[(i44 + cdiff) + inputs_to_obs->size[0] * apnd];
    }
  }

  i44 = inputs_to_obs->size[0] * inputs_to_obs->size[1];
  inputs_to_obs->size[0] = f_inputs_to_obs->size[0];
  inputs_to_obs->size[1] = 3;
  emxEnsureCapacity((emxArray__common *)inputs_to_obs, i44, (int)sizeof(double));
  for (i44 = 0; i44 < 3; i44++) {
    loop_ub = f_inputs_to_obs->size[0];
    for (b_n = 0; b_n < loop_ub; b_n++) {
      inputs_to_obs->data[b_n + inputs_to_obs->size[0] * i44] =
        f_inputs_to_obs->data[b_n + f_inputs_to_obs->size[0] * i44];
    }
  }

  emxFree_real_T(&f_inputs_to_obs);
  b_op_offset = ((double)output_to_obs->size[0] - obs_intervals * interval_len)
    + 1.0;
  if (b_op_offset > output_to_obs->size[0]) {
    i44 = 0;
    b_n = 0;
  } else {
    i44 = (int)b_op_offset - 1;
    b_n = output_to_obs->size[0];
  }

  emxInit_real_T1(&b_output_to_obs, 1);
  apnd = b_output_to_obs->size[0];
  b_output_to_obs->size[0] = b_n - i44;
  emxEnsureCapacity((emxArray__common *)b_output_to_obs, apnd, (int)sizeof
                    (double));
  loop_ub = b_n - i44;
  for (b_n = 0; b_n < loop_ub; b_n++) {
    b_output_to_obs->data[b_n] = output_to_obs->data[i44 + b_n];
  }

  i44 = output_to_obs->size[0];
  output_to_obs->size[0] = b_output_to_obs->size[0];
  emxEnsureCapacity((emxArray__common *)output_to_obs, i44, (int)sizeof(double));
  loop_ub = b_output_to_obs->size[0];
  for (i44 = 0; i44 < loop_ub; i44++) {
    output_to_obs->data[i44] = b_output_to_obs->data[i44];
  }

  emxFree_real_T(&b_output_to_obs);
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
  i44 = t->size[0] * t->size[1];
  t->size[0] = 1;
  t->size[1] = b_n;
  emxEnsureCapacity((emxArray__common *)t, i44, (int)sizeof(double));
  if (b_n > 0) {
    t->data[0] = 0.0;
    if (b_n > 1) {
      t->data[b_n - 1] = apnd;
      i44 = b_n - 1;
      ndbl = i44 / 2;
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

  emxInit_real_T(&obs_inputs, 2);
  emxInit_real_T1(&g_inputs_to_obs, 1);
  emxInit_real_T1(&h_inputs_to_obs, 1);
  emxInit_real_T1(&i_inputs_to_obs, 1);
  emxInit_real_T1(&j_inputs_to_obs, 1);
  emxInit_real_T1(&k_inputs_to_obs, 1);
  emxInit_real_T1(&l_inputs_to_obs, 1);
  emxInit_real_T1(&m_inputs_to_obs, 1);
  emxInit_real_T1(&n_inputs_to_obs, 1);
  emxInit_real_T1(&o_inputs_to_obs, 1);
  if ((model_inputs[0] == 1.0) && (model_inputs[1] == 1.0) && (model_inputs[2] ==
       0.0)) {
    loop_ub = inputs_to_obs->size[0];
    b_loop_ub = inputs_to_obs->size[0];
    ndbl = inputs_to_obs->size[0];
    i44 = n_inputs_to_obs->size[0];
    n_inputs_to_obs->size[0] = ndbl;
    emxEnsureCapacity((emxArray__common *)n_inputs_to_obs, i44, (int)sizeof
                      (double));
    for (i44 = 0; i44 < ndbl; i44++) {
      n_inputs_to_obs->data[i44] = inputs_to_obs->data[i44];
    }

    ndbl = inputs_to_obs->size[0];
    i44 = o_inputs_to_obs->size[0];
    o_inputs_to_obs->size[0] = ndbl;
    emxEnsureCapacity((emxArray__common *)o_inputs_to_obs, i44, (int)sizeof
                      (double));
    for (i44 = 0; i44 < ndbl; i44++) {
      o_inputs_to_obs->data[i44] = inputs_to_obs->data[i44 + inputs_to_obs->
        size[0]];
    }

    i44 = obs_inputs->size[0] * obs_inputs->size[1];
    obs_inputs->size[0] = loop_ub;
    obs_inputs->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)obs_inputs, i44, (int)sizeof(double));
    for (i44 = 0; i44 < loop_ub; i44++) {
      obs_inputs->data[i44] = n_inputs_to_obs->data[i44];
    }

    for (i44 = 0; i44 < b_loop_ub; i44++) {
      obs_inputs->data[i44 + obs_inputs->size[0]] = o_inputs_to_obs->data[i44];
    }
  } else if ((model_inputs[0] == 1.0) && (model_inputs[1] == 0.0) &&
             (model_inputs[2] == 1.0)) {
    loop_ub = inputs_to_obs->size[0];
    b_loop_ub = inputs_to_obs->size[0];
    ndbl = inputs_to_obs->size[0];
    i44 = l_inputs_to_obs->size[0];
    l_inputs_to_obs->size[0] = ndbl;
    emxEnsureCapacity((emxArray__common *)l_inputs_to_obs, i44, (int)sizeof
                      (double));
    for (i44 = 0; i44 < ndbl; i44++) {
      l_inputs_to_obs->data[i44] = inputs_to_obs->data[i44];
    }

    ndbl = inputs_to_obs->size[0];
    i44 = m_inputs_to_obs->size[0];
    m_inputs_to_obs->size[0] = ndbl;
    emxEnsureCapacity((emxArray__common *)m_inputs_to_obs, i44, (int)sizeof
                      (double));
    for (i44 = 0; i44 < ndbl; i44++) {
      m_inputs_to_obs->data[i44] = inputs_to_obs->data[i44 +
        (inputs_to_obs->size[0] << 1)];
    }

    i44 = obs_inputs->size[0] * obs_inputs->size[1];
    obs_inputs->size[0] = loop_ub;
    obs_inputs->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)obs_inputs, i44, (int)sizeof(double));
    for (i44 = 0; i44 < loop_ub; i44++) {
      obs_inputs->data[i44] = l_inputs_to_obs->data[i44];
    }

    for (i44 = 0; i44 < b_loop_ub; i44++) {
      obs_inputs->data[i44 + obs_inputs->size[0]] = m_inputs_to_obs->data[i44];
    }
  } else if ((model_inputs[0] == 0.0) && (model_inputs[1] == 1.0) &&
             (model_inputs[2] == 1.0)) {
    loop_ub = inputs_to_obs->size[0];
    b_loop_ub = inputs_to_obs->size[0];
    ndbl = inputs_to_obs->size[0];
    i44 = j_inputs_to_obs->size[0];
    j_inputs_to_obs->size[0] = ndbl;
    emxEnsureCapacity((emxArray__common *)j_inputs_to_obs, i44, (int)sizeof
                      (double));
    for (i44 = 0; i44 < ndbl; i44++) {
      j_inputs_to_obs->data[i44] = inputs_to_obs->data[i44 + inputs_to_obs->
        size[0]];
    }

    ndbl = inputs_to_obs->size[0];
    i44 = k_inputs_to_obs->size[0];
    k_inputs_to_obs->size[0] = ndbl;
    emxEnsureCapacity((emxArray__common *)k_inputs_to_obs, i44, (int)sizeof
                      (double));
    for (i44 = 0; i44 < ndbl; i44++) {
      k_inputs_to_obs->data[i44] = inputs_to_obs->data[i44 +
        (inputs_to_obs->size[0] << 1)];
    }

    i44 = obs_inputs->size[0] * obs_inputs->size[1];
    obs_inputs->size[0] = loop_ub;
    obs_inputs->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)obs_inputs, i44, (int)sizeof(double));
    for (i44 = 0; i44 < loop_ub; i44++) {
      obs_inputs->data[i44] = j_inputs_to_obs->data[i44];
    }

    for (i44 = 0; i44 < b_loop_ub; i44++) {
      obs_inputs->data[i44 + obs_inputs->size[0]] = k_inputs_to_obs->data[i44];
    }
  } else {
    loop_ub = inputs_to_obs->size[0];
    b_loop_ub = inputs_to_obs->size[0];
    ndbl = inputs_to_obs->size[0];
    cdiff = inputs_to_obs->size[0];
    i44 = g_inputs_to_obs->size[0];
    g_inputs_to_obs->size[0] = cdiff;
    emxEnsureCapacity((emxArray__common *)g_inputs_to_obs, i44, (int)sizeof
                      (double));
    for (i44 = 0; i44 < cdiff; i44++) {
      g_inputs_to_obs->data[i44] = inputs_to_obs->data[i44];
    }

    cdiff = inputs_to_obs->size[0];
    i44 = h_inputs_to_obs->size[0];
    h_inputs_to_obs->size[0] = cdiff;
    emxEnsureCapacity((emxArray__common *)h_inputs_to_obs, i44, (int)sizeof
                      (double));
    for (i44 = 0; i44 < cdiff; i44++) {
      h_inputs_to_obs->data[i44] = inputs_to_obs->data[i44 + inputs_to_obs->
        size[0]];
    }

    cdiff = inputs_to_obs->size[0];
    i44 = i_inputs_to_obs->size[0];
    i_inputs_to_obs->size[0] = cdiff;
    emxEnsureCapacity((emxArray__common *)i_inputs_to_obs, i44, (int)sizeof
                      (double));
    for (i44 = 0; i44 < cdiff; i44++) {
      i_inputs_to_obs->data[i44] = inputs_to_obs->data[i44 +
        (inputs_to_obs->size[0] << 1)];
    }

    i44 = obs_inputs->size[0] * obs_inputs->size[1];
    obs_inputs->size[0] = loop_ub;
    obs_inputs->size[1] = 3;
    emxEnsureCapacity((emxArray__common *)obs_inputs, i44, (int)sizeof(double));
    for (i44 = 0; i44 < loop_ub; i44++) {
      obs_inputs->data[i44] = g_inputs_to_obs->data[i44];
    }

    for (i44 = 0; i44 < b_loop_ub; i44++) {
      obs_inputs->data[i44 + obs_inputs->size[0]] = h_inputs_to_obs->data[i44];
    }

    for (i44 = 0; i44 < ndbl; i44++) {
      obs_inputs->data[i44 + (obs_inputs->size[0] << 1)] = i_inputs_to_obs->
        data[i44];
    }
  }

  emxFree_real_T(&o_inputs_to_obs);
  emxFree_real_T(&n_inputs_to_obs);
  emxFree_real_T(&m_inputs_to_obs);
  emxFree_real_T(&l_inputs_to_obs);
  emxFree_real_T(&k_inputs_to_obs);
  emxFree_real_T(&j_inputs_to_obs);
  emxFree_real_T(&i_inputs_to_obs);
  emxFree_real_T(&h_inputs_to_obs);
  emxFree_real_T(&g_inputs_to_obs);
  emxFree_real_T(&inputs_to_obs);
  emxInit_real_T(&A, 2);
  emxInit_real_T(&B, 2);
  emxInit_real_T(&C, 2);
  emxInit_real_T(&unusedU0, 2);
  FHZN_get_MISO_model(params_vector, current_inputs_nr, n, m, A, B, C, unusedU0);
  FHZN_exact_state_observer_final(A, B, C, t, obs_inputs, output_to_obs, X0);
  b_op_offset = ((double)obs_inputs->size[0] - interval_len) + 1.0;
  emxFree_real_T(&unusedU0);
  emxFree_real_T(&t);
  if (b_op_offset > obs_inputs->size[0]) {
    i44 = 0;
    b_n = 0;
  } else {
    i44 = (int)b_op_offset - 1;
    b_n = obs_inputs->size[0];
  }

  b_op_offset = ((double)output_to_obs->size[0] - interval_len) + 1.0;
  if (b_op_offset > output_to_obs->size[0]) {
    apnd = 0;
    cdiff = 0;
  } else {
    apnd = (int)b_op_offset - 1;
    cdiff = output_to_obs->size[0];
  }

  emxInit_real_T1(&output_signal, 1);
  ndbl = output_signal->size[0];
  output_signal->size[0] = cdiff - apnd;
  emxEnsureCapacity((emxArray__common *)output_signal, ndbl, (int)sizeof(double));
  loop_ub = cdiff - apnd;
  for (cdiff = 0; cdiff < loop_ub; cdiff++) {
    output_signal->data[cdiff] = output_to_obs->data[apnd + cdiff];
  }

  emxInit_real_T1(&b_output_signal, 1);

  /* check the sp diff */
  /* for i=1:length(output_signal) */
  /*     sp_diff=sp_diff+(output_signal(i)-sp_signal(i))^2; */
  /* end */
  b_op_offset = op_offset->data[4];
  apnd = b_output_signal->size[0];
  b_output_signal->size[0] = output_signal->size[0];
  emxEnsureCapacity((emxArray__common *)b_output_signal, apnd, (int)sizeof
                    (double));
  loop_ub = output_signal->size[0];
  for (apnd = 0; apnd < loop_ub; apnd++) {
    b_output_signal->data[apnd] = output_signal->data[apnd] - (dataBuff->data
      [(int)intervals_nr - 1].sp_value->data[apnd] - b_op_offset);
  }

  b_power(b_output_signal, r22);
  *sp_diff = b_sum(r22);
  apnd = output_to_obs->size[0];
  output_to_obs->size[0] = X0_prev->size[0];
  emxEnsureCapacity((emxArray__common *)output_to_obs, apnd, (int)sizeof(double));
  loop_ub = X0_prev->size[0];
  emxFree_real_T(&b_output_signal);
  emxFree_real_T(&r22);
  for (apnd = 0; apnd < loop_ub; apnd++) {
    output_to_obs->data[apnd] = X0_prev->data[apnd];
  }

  emxInit_real_T(&b_obs_inputs, 2);
  loop_ub = obs_inputs->size[1];
  apnd = b_obs_inputs->size[0] * b_obs_inputs->size[1];
  b_obs_inputs->size[0] = b_n - i44;
  b_obs_inputs->size[1] = loop_ub;
  emxEnsureCapacity((emxArray__common *)b_obs_inputs, apnd, (int)sizeof(double));
  for (apnd = 0; apnd < loop_ub; apnd++) {
    b_loop_ub = b_n - i44;
    for (cdiff = 0; cdiff < b_loop_ub; cdiff++) {
      b_obs_inputs->data[cdiff + b_obs_inputs->size[0] * apnd] =
        obs_inputs->data[(i44 + cdiff) + obs_inputs->size[0] * apnd];
    }
  }

  emxFree_real_T(&obs_inputs);
  *model_diff = c_FHZN_simulate_lsys_output_com(A, B, C, output_to_obs,
    b_obs_inputs, output_signal);
  emxFree_real_T(&b_obs_inputs);
  emxFree_real_T(&C);
  emxFree_real_T(&B);
  emxFree_real_T(&A);
  emxFree_real_T(&output_signal);
  emxFree_real_T(&output_to_obs);
}

/*
 * File trailer for FHZN_simulate_FHZ3_system.c
 *
 * [EOF]
 */
