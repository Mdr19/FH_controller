/*
 * File: FHZN_obtain_FHZ4_model_nonzero.c
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
#include "FHZN_exact_state_observer_initial.h"
#include "FHZN_get_MISO_model.h"
#include "FHZN_check_model_prop.h"
#include "FHZN_MFM_model_ident_LSM.h"
#include "sum.h"
#include "power.h"
#include "FHZN_shift_signal.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_FHZ4_DataBuff *dataBuff
 *                const emxArray_FHZ4_Int *FHZ_intervals
 *                const emxArray_MFM_Struct *MFM_ident_models
 *                double intervals_nr
 *                double new_model_intervals
 *                double interval_len
 *                double *model_reidentified
 *                double *model_reidentified_op_int
 *                double *op_time
 *                emxArray_real_T *ni_min_opt
 *                double op_offset[4]
 *                double *model_diff_avg
 *                double *sp_diff_avg
 *                emxArray_real_T *model_X0
 *                double *n
 *                double *m
 *                double *N
 *                double *M
 *                double *h
 * Return Type  : void
 */
void FHZN_obtain_FHZ4_model_nonzero(const emxArray_FHZ4_DataBuff *dataBuff,
  const emxArray_FHZ4_Int *FHZ_intervals, const emxArray_MFM_Struct
  *MFM_ident_models, double intervals_nr, double new_model_intervals, double
  interval_len, double *model_reidentified, double *model_reidentified_op_int,
  double *op_time, emxArray_real_T *ni_min_opt, double op_offset[4], double
  *model_diff_avg, double *sp_diff_avg, emxArray_real_T *model_X0, double *n,
  double *m, double *N, double *M, double *h)
{
  int op_found;
  double signal_del;
  signed char model_inputs[2];
  int apnd;
  int i23;
  int model_opt_nr;
  int op_interval;
  double original_model_diff;
  double sim_res_opt;
  double b_op_offset;
  boolean_T exitg1;
  double i;
  int j;
  emxArray_real_T *input_1_to_ident;
  double op_time_int;
  double size1;
  int ndbl;
  emxArray_real_T *input_2_to_ident;
  emxArray_real_T *output_to_ident;
  emxArray_real_T *output_sp;
  double b_j;
  emxArray_int32_T *r13;
  double d11;
  double d12;
  int cdiff;
  int b_n;
  emxArray_real_T *b_input_1_to_ident;
  emxArray_real_T *t;
  emxArray_real_T *b_output_sp;
  double sp_diff;
  emxArray_real_T *X0;
  emxArray_real_T *A;
  emxArray_real_T *B;
  emxArray_real_T *C;
  emxArray_real_T *unusedU0;
  emxArray_real_T *c_input_1_to_ident;
  emxArray_real_T *b_t;
  emxArray_real_T *d_input_1_to_ident;
  emxArray_real_T *e_input_1_to_ident;
  emxArray_real_T *b_output_to_ident;
  double sim_res;
  op_found = 0;
  *op_time = 0.0;
  signal_del = 0.0;
  for (apnd = 0; apnd < 2; apnd++) {
    model_inputs[apnd] = 0;
  }

  for (apnd = 0; apnd < 4; apnd++) {
    op_offset[apnd] = 0.0;
  }

  i23 = ni_min_opt->size[0];
  ni_min_opt->size[0] = 4;
  emxEnsureCapacity((emxArray__common *)ni_min_opt, i23, (int)sizeof(double));
  for (i23 = 0; i23 < 4; i23++) {
    ni_min_opt->data[i23] = 0.0;
  }

  model_opt_nr = -1;
  op_interval = 0;
  *model_reidentified_op_int = 0.0;
  *model_reidentified = 0.0;
  original_model_diff = 0.0;
  *model_diff_avg = 0.0;
  *sp_diff_avg = 0.0;
  i23 = model_X0->size[0];
  model_X0->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)model_X0, i23, (int)sizeof(double));
  model_X0->data[0] = 0.0;
  *n = 0.0;
  *m = 0.0;
  *N = 0.0;
  *M = 0.0;
  *h = 0.0;
  sim_res_opt = rtInf;

  /* find new operating point */
  if (intervals_nr >= new_model_intervals) {
    b_op_offset = (intervals_nr - new_model_intervals) + 1.0;
    i23 = (int)(intervals_nr + (1.0 - b_op_offset));
    apnd = 0;
    exitg1 = false;
    while ((!exitg1) && (apnd <= i23 - 1)) {
      i = b_op_offset + (double)apnd;
      if (FHZ_intervals->data[(int)i - 1].op_interval_possible) {
        op_found = 1;
        op_interval = (int)i;
        *op_time = FHZ_intervals->data[(int)i - 1].op_interval_time;
        signal_del = FHZ_intervals->data[(int)i - 1].model_del;
        exitg1 = true;
      } else {
        apnd++;
      }
    }
  }

  /* check input signals */
  if ((op_found != 0) && (intervals_nr >= new_model_intervals)) {
    b_op_offset = (intervals_nr - new_model_intervals) + 1.0;
    i23 = (int)(intervals_nr + (1.0 - b_op_offset));
    for (apnd = 0; apnd < i23; apnd++) {
      i = b_op_offset + (double)apnd;
      for (j = 0; j < 2; j++) {
        if (FHZ_intervals->data[(int)i - 1].model_inputs[j] >= 1.0) {
          model_inputs[j] = 1;
        }
      }

      original_model_diff += FHZ_intervals->data[(int)i - 1].model_diff;
    }
  }

  /* op_interval=op_interval+ident_offset_intervals; */
  /* op_time=250; */
  /* build signals for ident */
  if (model_inputs[0] + model_inputs[1] == 2) {
    emxInit_real_T1(&input_1_to_ident, 1);
    op_time_int = *op_time - dataBuff->data[(int)((intervals_nr -
      new_model_intervals) + 1.0) - 1].time->data[0];
    size1 = new_model_intervals * interval_len;
    i23 = input_1_to_ident->size[0];
    input_1_to_ident->size[0] = (int)size1;
    emxEnsureCapacity((emxArray__common *)input_1_to_ident, i23, (int)sizeof
                      (double));
    ndbl = (int)size1;
    for (i23 = 0; i23 < ndbl; i23++) {
      input_1_to_ident->data[i23] = 0.0;
    }

    emxInit_real_T1(&input_2_to_ident, 1);
    i23 = input_2_to_ident->size[0];
    input_2_to_ident->size[0] = (int)size1;
    emxEnsureCapacity((emxArray__common *)input_2_to_ident, i23, (int)sizeof
                      (double));
    ndbl = (int)size1;
    for (i23 = 0; i23 < ndbl; i23++) {
      input_2_to_ident->data[i23] = 0.0;
    }

    emxInit_real_T1(&output_to_ident, 1);
    i23 = output_to_ident->size[0];
    output_to_ident->size[0] = (int)size1;
    emxEnsureCapacity((emxArray__common *)output_to_ident, i23, (int)sizeof
                      (double));
    ndbl = (int)size1;
    for (i23 = 0; i23 < ndbl; i23++) {
      output_to_ident->data[i23] = 0.0;
    }

    emxInit_real_T1(&output_sp, 1);
    i23 = output_sp->size[0];
    output_sp->size[0] = (int)size1;
    emxEnsureCapacity((emxArray__common *)output_sp, i23, (int)sizeof(double));
    ndbl = (int)size1;
    for (i23 = 0; i23 < ndbl; i23++) {
      output_sp->data[i23] = 0.0;
    }

    b_j = 1.0;
    b_op_offset = (intervals_nr - new_model_intervals) + 1.0;
    i23 = (int)(intervals_nr + (1.0 - b_op_offset));
    apnd = 0;
    emxInit_int32_T(&r13, 2);
    while (apnd <= i23 - 1) {
      i = b_op_offset + (double)apnd;
      d11 = (b_j - 1.0) * interval_len + 1.0;
      d12 = interval_len * b_j;
      if (d11 > d12) {
        cdiff = 0;
        b_n = 0;
      } else {
        cdiff = (int)d11 - 1;
        b_n = (int)d12;
      }

      ndbl = r13->size[0] * r13->size[1];
      r13->size[0] = 1;
      r13->size[1] = b_n - cdiff;
      emxEnsureCapacity((emxArray__common *)r13, ndbl, (int)sizeof(int));
      ndbl = b_n - cdiff;
      for (b_n = 0; b_n < ndbl; b_n++) {
        r13->data[r13->size[0] * b_n] = cdiff + b_n;
      }

      ndbl = r13->size[0] * r13->size[1];
      for (cdiff = 0; cdiff < ndbl; cdiff++) {
        input_1_to_ident->data[r13->data[cdiff]] = dataBuff->data[(int)i - 1].
          input_1->data[cdiff];
      }

      d11 = (b_j - 1.0) * interval_len + 1.0;
      d12 = interval_len * b_j;
      if (d11 > d12) {
        cdiff = 0;
        b_n = 0;
      } else {
        cdiff = (int)d11 - 1;
        b_n = (int)d12;
      }

      ndbl = r13->size[0] * r13->size[1];
      r13->size[0] = 1;
      r13->size[1] = b_n - cdiff;
      emxEnsureCapacity((emxArray__common *)r13, ndbl, (int)sizeof(int));
      ndbl = b_n - cdiff;
      for (b_n = 0; b_n < ndbl; b_n++) {
        r13->data[r13->size[0] * b_n] = cdiff + b_n;
      }

      ndbl = r13->size[0] * r13->size[1];
      for (cdiff = 0; cdiff < ndbl; cdiff++) {
        input_2_to_ident->data[r13->data[cdiff]] = dataBuff->data[(int)i - 1].
          input_2->data[cdiff];
      }

      d11 = (b_j - 1.0) * interval_len + 1.0;
      d12 = interval_len * b_j;
      if (d11 > d12) {
        cdiff = 0;
        b_n = 0;
      } else {
        cdiff = (int)d11 - 1;
        b_n = (int)d12;
      }

      ndbl = r13->size[0] * r13->size[1];
      r13->size[0] = 1;
      r13->size[1] = b_n - cdiff;
      emxEnsureCapacity((emxArray__common *)r13, ndbl, (int)sizeof(int));
      ndbl = b_n - cdiff;
      for (b_n = 0; b_n < ndbl; b_n++) {
        r13->data[r13->size[0] * b_n] = cdiff + b_n;
      }

      ndbl = r13->size[0] * r13->size[1];
      for (cdiff = 0; cdiff < ndbl; cdiff++) {
        output_to_ident->data[r13->data[cdiff]] = dataBuff->data[(int)i - 1].
          output->data[cdiff];
      }

      d11 = (b_j - 1.0) * interval_len + 1.0;
      d12 = interval_len * b_j;
      if (d11 > d12) {
        cdiff = 0;
        b_n = 0;
      } else {
        cdiff = (int)d11 - 1;
        b_n = (int)d12;
      }

      ndbl = r13->size[0] * r13->size[1];
      r13->size[0] = 1;
      r13->size[1] = b_n - cdiff;
      emxEnsureCapacity((emxArray__common *)r13, ndbl, (int)sizeof(int));
      ndbl = b_n - cdiff;
      for (b_n = 0; b_n < ndbl; b_n++) {
        r13->data[r13->size[0] * b_n] = cdiff + b_n;
      }

      ndbl = r13->size[0] * r13->size[1];
      for (cdiff = 0; cdiff < ndbl; cdiff++) {
        output_sp->data[r13->data[cdiff]] = dataBuff->data[(int)i - 1].
          sp_value->data[cdiff];
      }

      b_j++;
      apnd++;
    }

    emxFree_int32_T(&r13);
    emxInit_real_T1(&b_input_1_to_ident, 1);
    i23 = b_input_1_to_ident->size[0];
    b_input_1_to_ident->size[0] = input_1_to_ident->size[0];
    emxEnsureCapacity((emxArray__common *)b_input_1_to_ident, i23, (int)sizeof
                      (double));
    ndbl = input_1_to_ident->size[0];
    for (i23 = 0; i23 < ndbl; i23++) {
      b_input_1_to_ident->data[i23] = input_1_to_ident->data[i23];
    }

    FHZN_shift_signal(b_input_1_to_ident, signal_del, input_1_to_ident);
    op_offset[0] = input_1_to_ident->data[(int)op_time_int - 1];
    op_offset[1] = input_2_to_ident->data[(int)op_time_int - 1];
    op_offset[2] = output_to_ident->data[(int)op_time_int - 1];
    op_offset[3] = output_sp->data[(int)op_time_int - 1];

    /* offset minus */
    b_op_offset = op_offset[0];
    i23 = input_1_to_ident->size[0];
    emxEnsureCapacity((emxArray__common *)input_1_to_ident, i23, (int)sizeof
                      (double));
    ndbl = input_1_to_ident->size[0];
    emxFree_real_T(&b_input_1_to_ident);
    for (i23 = 0; i23 < ndbl; i23++) {
      input_1_to_ident->data[i23] -= b_op_offset;
    }

    b_op_offset = op_offset[1];
    i23 = input_2_to_ident->size[0];
    emxEnsureCapacity((emxArray__common *)input_2_to_ident, i23, (int)sizeof
                      (double));
    ndbl = input_2_to_ident->size[0];
    for (i23 = 0; i23 < ndbl; i23++) {
      input_2_to_ident->data[i23] -= b_op_offset;
    }

    b_op_offset = op_offset[2];
    i23 = output_to_ident->size[0];
    emxEnsureCapacity((emxArray__common *)output_to_ident, i23, (int)sizeof
                      (double));
    ndbl = output_to_ident->size[0];
    for (i23 = 0; i23 < ndbl; i23++) {
      output_to_ident->data[i23] -= b_op_offset;
    }

    b_op_offset = op_offset[3];
    i23 = output_sp->size[0];
    emxEnsureCapacity((emxArray__common *)output_sp, i23, (int)sizeof(double));
    ndbl = output_sp->size[0];
    for (i23 = 0; i23 < ndbl; i23++) {
      output_sp->data[i23] -= b_op_offset;
    }

    if (output_to_ident->size[0] - 1 < 0) {
      b_n = 0;
      apnd = output_to_ident->size[0] - 1;
    } else {
      ndbl = (int)floor(((double)output_to_ident->size[0] - 1.0) + 0.5);
      apnd = ndbl;
      cdiff = (ndbl - output_to_ident->size[0]) + 1;
      if (fabs(cdiff) < 4.4408920985006262E-16 * fabs((double)
           output_to_ident->size[0] - 1.0)) {
        ndbl++;
        apnd = output_to_ident->size[0] - 1;
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
    i23 = t->size[0] * t->size[1];
    t->size[0] = 1;
    t->size[1] = b_n;
    emxEnsureCapacity((emxArray__common *)t, i23, (int)sizeof(double));
    if (b_n > 0) {
      t->data[0] = 0.0;
      if (b_n > 1) {
        t->data[b_n - 1] = apnd;
        i23 = b_n - 1;
        ndbl = i23 / 2;
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

    emxInit_real_T1(&b_output_sp, 1);

    /* check the sp diff */
    /* for i=1:length(output_to_ident) */
    /*     sp_diff=sp_diff+(output_sp(i)-output_to_ident(i))^2; */
    /* end */
    i23 = b_output_sp->size[0];
    b_output_sp->size[0] = output_sp->size[0];
    emxEnsureCapacity((emxArray__common *)b_output_sp, i23, (int)sizeof(double));
    ndbl = output_sp->size[0];
    for (i23 = 0; i23 < ndbl; i23++) {
      b_output_sp->data[i23] = output_sp->data[i23] - output_to_ident->data[i23];
    }

    b_power(b_output_sp, output_sp);
    sp_diff = b_sum(output_sp);
    *sp_diff_avg = sp_diff / new_model_intervals;

    /* inputs_to_ident(:,1)=input_1_to_ident; */
    /* inputs_to_ident(:,2)=input_2_to_ident; */
    apnd = 0;
    emxFree_real_T(&b_output_sp);
    emxInit_real_T1(&X0, 1);
    emxInit_real_T(&A, 2);
    emxInit_real_T(&B, 2);
    emxInit_real_T(&C, 2);
    emxInit_real_T(&unusedU0, 2);
    emxInit_real_T(&c_input_1_to_ident, 2);
    emxInit_real_T(&b_t, 2);
    emxInit_real_T(&d_input_1_to_ident, 2);
    emxInit_real_T(&e_input_1_to_ident, 2);
    emxInit_real_T(&b_output_to_ident, 2);
    while (apnd <= MFM_ident_models->size[0] - 1) {
      ndbl = input_1_to_ident->size[0];
      cdiff = input_2_to_ident->size[0];
      i23 = e_input_1_to_ident->size[0] * e_input_1_to_ident->size[1];
      e_input_1_to_ident->size[0] = 2;
      e_input_1_to_ident->size[1] = ndbl;
      emxEnsureCapacity((emxArray__common *)e_input_1_to_ident, i23, (int)sizeof
                        (double));
      for (i23 = 0; i23 < ndbl; i23++) {
        e_input_1_to_ident->data[e_input_1_to_ident->size[0] * i23] =
          input_1_to_ident->data[i23];
      }

      for (i23 = 0; i23 < cdiff; i23++) {
        e_input_1_to_ident->data[1 + e_input_1_to_ident->size[0] * i23] =
          input_2_to_ident->data[i23];
      }

      i23 = b_output_to_ident->size[0] * b_output_to_ident->size[1];
      b_output_to_ident->size[0] = 1;
      b_output_to_ident->size[1] = output_to_ident->size[0];
      emxEnsureCapacity((emxArray__common *)b_output_to_ident, i23, (int)sizeof
                        (double));
      ndbl = output_to_ident->size[0];
      for (i23 = 0; i23 < ndbl; i23++) {
        b_output_to_ident->data[b_output_to_ident->size[0] * i23] =
          output_to_ident->data[i23];
      }

      b_FHZN_MFM_model_ident_LSM(e_input_1_to_ident, b_output_to_ident,
        MFM_ident_models->data[apnd].h, MFM_ident_models->data[apnd].n,
        MFM_ident_models->data[apnd].m, MFM_ident_models->data[apnd].N,
        MFM_ident_models->data[apnd].M, output_sp);

      /* ni_min */
      if (b_FHZN_check_model_prop(output_sp, MFM_ident_models->data[apnd].n)) {
        b_FHZN_get_MISO_model(output_sp, MFM_ident_models->data[apnd].n,
                              MFM_ident_models->data[apnd].m, A, B, C, unusedU0);
        i23 = b_t->size[0] * b_t->size[1];
        b_t->size[0] = 1;
        b_t->size[1] = t->size[1];
        emxEnsureCapacity((emxArray__common *)b_t, i23, (int)sizeof(double));
        ndbl = t->size[0] * t->size[1];
        for (i23 = 0; i23 < ndbl; i23++) {
          b_t->data[i23] = t->data[i23];
        }

        ndbl = input_1_to_ident->size[0];
        cdiff = input_2_to_ident->size[0];
        i23 = d_input_1_to_ident->size[0] * d_input_1_to_ident->size[1];
        d_input_1_to_ident->size[0] = ndbl;
        d_input_1_to_ident->size[1] = 2;
        emxEnsureCapacity((emxArray__common *)d_input_1_to_ident, i23, (int)
                          sizeof(double));
        for (i23 = 0; i23 < ndbl; i23++) {
          d_input_1_to_ident->data[i23] = input_1_to_ident->data[i23];
        }

        for (i23 = 0; i23 < cdiff; i23++) {
          d_input_1_to_ident->data[i23 + d_input_1_to_ident->size[0]] =
            input_2_to_ident->data[i23];
        }

        d_FHZN_exact_state_observer_ini(A, B, C, b_t, d_input_1_to_ident,
          output_to_ident, X0);
        ndbl = input_1_to_ident->size[0];
        cdiff = input_2_to_ident->size[0];
        i23 = c_input_1_to_ident->size[0] * c_input_1_to_ident->size[1];
        c_input_1_to_ident->size[0] = ndbl;
        c_input_1_to_ident->size[1] = 2;
        emxEnsureCapacity((emxArray__common *)c_input_1_to_ident, i23, (int)
                          sizeof(double));
        for (i23 = 0; i23 < ndbl; i23++) {
          c_input_1_to_ident->data[i23] = input_1_to_ident->data[i23];
        }

        for (i23 = 0; i23 < cdiff; i23++) {
          c_input_1_to_ident->data[i23 + c_input_1_to_ident->size[0]] =
            input_2_to_ident->data[i23];
        }

        sim_res = d_FHZN_simulate_lsys_output_com(A, B, C, X0,
          c_input_1_to_ident, output_to_ident);
        if ((1 + apnd == 1) && (sim_res < original_model_diff)) {
          i23 = ni_min_opt->size[0];
          ni_min_opt->size[0] = output_sp->size[0];
          emxEnsureCapacity((emxArray__common *)ni_min_opt, i23, (int)sizeof
                            (double));
          ndbl = output_sp->size[0];
          for (i23 = 0; i23 < ndbl; i23++) {
            ni_min_opt->data[i23] = output_sp->data[i23];
          }

          sim_res_opt = sim_res;
          model_opt_nr = 0;
          i23 = model_X0->size[0];
          model_X0->size[0] = X0->size[0];
          emxEnsureCapacity((emxArray__common *)model_X0, i23, (int)sizeof
                            (double));
          ndbl = X0->size[0];
          for (i23 = 0; i23 < ndbl; i23++) {
            model_X0->data[i23] = X0->data[i23];
          }
        } else {
          if ((1 + apnd > 1) && (sim_res < original_model_diff) && (sim_res <
               sim_res_opt)) {
            sim_res_opt = sim_res;
            i23 = ni_min_opt->size[0];
            ni_min_opt->size[0] = output_sp->size[0];
            emxEnsureCapacity((emxArray__common *)ni_min_opt, i23, (int)sizeof
                              (double));
            ndbl = output_sp->size[0];
            for (i23 = 0; i23 < ndbl; i23++) {
              ni_min_opt->data[i23] = output_sp->data[i23];
            }

            model_opt_nr = apnd;
            i23 = model_X0->size[0];
            model_X0->size[0] = X0->size[0];
            emxEnsureCapacity((emxArray__common *)model_X0, i23, (int)sizeof
                              (double));
            ndbl = X0->size[0];
            for (i23 = 0; i23 < ndbl; i23++) {
              model_X0->data[i23] = X0->data[i23];
            }
          }
        }
      }

      apnd++;
    }

    emxFree_real_T(&b_output_to_ident);
    emxFree_real_T(&e_input_1_to_ident);
    emxFree_real_T(&d_input_1_to_ident);
    emxFree_real_T(&b_t);
    emxFree_real_T(&c_input_1_to_ident);
    emxFree_real_T(&unusedU0);
    emxFree_real_T(&C);
    emxFree_real_T(&B);
    emxFree_real_T(&A);
    emxFree_real_T(&X0);
    emxFree_real_T(&t);
    emxFree_real_T(&output_sp);
    emxFree_real_T(&output_to_ident);
    emxFree_real_T(&input_2_to_ident);
    emxFree_real_T(&input_1_to_ident);
    if (model_opt_nr + 1 > 0) {
      *model_reidentified = 1.0;
      *n = MFM_ident_models->data[model_opt_nr].n;
      *m = MFM_ident_models->data[model_opt_nr].m;
      *N = MFM_ident_models->data[model_opt_nr].N;
      *M = MFM_ident_models->data[model_opt_nr].M;
      *h = MFM_ident_models->data[model_opt_nr].h;
      *model_reidentified_op_int = op_interval;
      *model_diff_avg = sim_res_opt / new_model_intervals;
    }
  }
}

/*
 * File trailer for FHZN_obtain_FHZ4_model_nonzero.c
 *
 * [EOF]
 */
