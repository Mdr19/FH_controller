/*
 * File: FHZN_obtain_FHZ3_model_nonzero.c
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
 * Arguments    : const emxArray_FHZ3_DataBuff *dataBuff
 *                const emxArray_FHZ3_Int *FHZ_intervals
 *                const emxArray_MFM_Struct *MFM_ident_models
 *                double intervals_nr
 *                double new_model_intervals
 *                double interval_len
 *                double *model_reidentified
 *                double *model_reidentified_op_int
 *                double *op_time
 *                emxArray_real_T *ni_min_opt
 *                double op_offset[5]
 *                double *model_diff_avg
 *                double *sp_diff_avg
 *                double model_inputs[3]
 *                emxArray_real_T *model_X0
 *                double *n
 *                double *m
 *                double *N
 *                double *M
 *                double *h
 * Return Type  : void
 */
void FHZN_obtain_FHZ3_model_nonzero(const emxArray_FHZ3_DataBuff *dataBuff,
  const emxArray_FHZ3_Int *FHZ_intervals, const emxArray_MFM_Struct
  *MFM_ident_models, double intervals_nr, double new_model_intervals, double
  interval_len, double *model_reidentified, double *model_reidentified_op_int,
  double *op_time, emxArray_real_T *ni_min_opt, double op_offset[5], double
  *model_diff_avg, double *sp_diff_avg, double model_inputs[3], emxArray_real_T *
  model_X0, double *n, double *m, double *N, double *M, double *h)
{
  int op_found;
  double signal_del;
  int i;
  int i8;
  int model_opt_nr;
  int op_interval;
  double original_model_diff;
  double sim_res_opt;
  double b_op_offset;
  boolean_T exitg1;
  double b_i;
  int j;
  emxArray_real_T *input_1_to_ident;
  double op_time_int;
  double size1;
  int b_n;
  emxArray_real_T *input_2_to_ident;
  emxArray_real_T *input_3_to_ident;
  emxArray_real_T *output_to_ident;
  emxArray_real_T *output_sp;
  double b_j;
  emxArray_int32_T *r6;
  double d8;
  double d9;
  int apnd;
  int cdiff;
  int ndbl;
  emxArray_real_T *b_input_1_to_ident;
  emxArray_real_T *t;
  emxArray_real_T *b_output_sp;
  emxArray_real_T *X0;
  double sp_diff;
  emxArray_real_T *ident_inputs;
  int ident_inputs_nr;
  double model_inputs_prop[3];
  static const signed char iv3[3] = { 1, 1, 0 };

  static const signed char iv4[3] = { 1, 0, 1 };

  static const signed char iv5[3] = { 0, 1, 1 };

  emxArray_real_T *A;
  emxArray_real_T *C;
  emxArray_real_T *B;
  emxArray_real_T *unusedU0;
  emxArray_real_T *b_ident_inputs;
  emxArray_real_T *b_t;
  emxArray_real_T *c_ident_inputs;
  emxArray_real_T *b_output_to_ident;
  static const double dv1[3] = { 1.0, 1.0, -1.0 };

  double sim_res;
  op_found = 0;
  *op_time = 0.0;
  signal_del = 0.0;
  for (i = 0; i < 3; i++) {
    model_inputs[i] = 0.0;
  }

  for (i = 0; i < 5; i++) {
    op_offset[i] = 0.0;
  }

  i8 = ni_min_opt->size[0];
  ni_min_opt->size[0] = 4;
  emxEnsureCapacity((emxArray__common *)ni_min_opt, i8, (int)sizeof(double));
  for (i8 = 0; i8 < 4; i8++) {
    ni_min_opt->data[i8] = 0.0;
  }

  model_opt_nr = -1;
  op_interval = 0;
  *model_reidentified_op_int = 0.0;
  *model_reidentified = 0.0;
  original_model_diff = 0.0;
  *model_diff_avg = 0.0;
  *sp_diff_avg = 0.0;
  i8 = model_X0->size[0];
  model_X0->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)model_X0, i8, (int)sizeof(double));
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
    i8 = (int)(intervals_nr + (1.0 - b_op_offset));
    i = 0;
    exitg1 = false;
    while ((!exitg1) && (i <= i8 - 1)) {
      b_i = b_op_offset + (double)i;
      if (FHZ_intervals->data[(int)b_i - 1].op_interval_possible) {
        op_found = 1;
        op_interval = (int)b_i;
        *op_time = FHZ_intervals->data[(int)b_i - 1].op_interval_time;
        signal_del = FHZ_intervals->data[(int)b_i - 1].model_del;
        exitg1 = true;
      } else {
        i++;
      }
    }
  }

  /* check input signals */
  if ((op_found != 0) && (intervals_nr >= new_model_intervals)) {
    b_op_offset = (intervals_nr - new_model_intervals) + 1.0;
    i8 = (int)(intervals_nr + (1.0 - b_op_offset));
    for (i = 0; i < i8; i++) {
      b_i = b_op_offset + (double)i;
      for (j = 0; j < 3; j++) {
        if (FHZ_intervals->data[(int)b_i - 1].model_inputs[j] >= 1.0) {
          model_inputs[j] = 1.0;
        }
      }

      original_model_diff += FHZ_intervals->data[(int)b_i - 1].model_diff;
    }
  }

  /* op_interval=op_interval+ident_offset_intervals; */
  /* op_time=250; */
  /* build signals for ident */
  if (sum(model_inputs) >= 2.0) {
    emxInit_real_T1(&input_1_to_ident, 1);
    op_time_int = *op_time - dataBuff->data[(int)((intervals_nr -
      new_model_intervals) + 1.0) - 1].time->data[0];
    size1 = new_model_intervals * interval_len;
    i8 = input_1_to_ident->size[0];
    input_1_to_ident->size[0] = (int)size1;
    emxEnsureCapacity((emxArray__common *)input_1_to_ident, i8, (int)sizeof
                      (double));
    b_n = (int)size1;
    for (i8 = 0; i8 < b_n; i8++) {
      input_1_to_ident->data[i8] = 0.0;
    }

    emxInit_real_T1(&input_2_to_ident, 1);
    i8 = input_2_to_ident->size[0];
    input_2_to_ident->size[0] = (int)size1;
    emxEnsureCapacity((emxArray__common *)input_2_to_ident, i8, (int)sizeof
                      (double));
    b_n = (int)size1;
    for (i8 = 0; i8 < b_n; i8++) {
      input_2_to_ident->data[i8] = 0.0;
    }

    emxInit_real_T1(&input_3_to_ident, 1);
    i8 = input_3_to_ident->size[0];
    input_3_to_ident->size[0] = (int)size1;
    emxEnsureCapacity((emxArray__common *)input_3_to_ident, i8, (int)sizeof
                      (double));
    b_n = (int)size1;
    for (i8 = 0; i8 < b_n; i8++) {
      input_3_to_ident->data[i8] = 0.0;
    }

    emxInit_real_T1(&output_to_ident, 1);
    i8 = output_to_ident->size[0];
    output_to_ident->size[0] = (int)size1;
    emxEnsureCapacity((emxArray__common *)output_to_ident, i8, (int)sizeof
                      (double));
    b_n = (int)size1;
    for (i8 = 0; i8 < b_n; i8++) {
      output_to_ident->data[i8] = 0.0;
    }

    emxInit_real_T1(&output_sp, 1);
    i8 = output_sp->size[0];
    output_sp->size[0] = (int)size1;
    emxEnsureCapacity((emxArray__common *)output_sp, i8, (int)sizeof(double));
    b_n = (int)size1;
    for (i8 = 0; i8 < b_n; i8++) {
      output_sp->data[i8] = 0.0;
    }

    b_j = 1.0;
    b_op_offset = (intervals_nr - new_model_intervals) + 1.0;
    i8 = (int)(intervals_nr + (1.0 - b_op_offset));
    i = 0;
    emxInit_int32_T(&r6, 2);
    while (i <= i8 - 1) {
      b_i = b_op_offset + (double)i;
      d8 = (b_j - 1.0) * interval_len + 1.0;
      d9 = interval_len * b_j;
      if (d8 > d9) {
        apnd = 0;
        cdiff = 0;
      } else {
        apnd = (int)d8 - 1;
        cdiff = (int)d9;
      }

      ndbl = r6->size[0] * r6->size[1];
      r6->size[0] = 1;
      r6->size[1] = cdiff - apnd;
      emxEnsureCapacity((emxArray__common *)r6, ndbl, (int)sizeof(int));
      b_n = cdiff - apnd;
      for (cdiff = 0; cdiff < b_n; cdiff++) {
        r6->data[r6->size[0] * cdiff] = apnd + cdiff;
      }

      b_n = r6->size[0] * r6->size[1];
      for (apnd = 0; apnd < b_n; apnd++) {
        input_1_to_ident->data[r6->data[apnd]] = dataBuff->data[(int)b_i - 1].
          input_1->data[apnd];
      }

      d8 = (b_j - 1.0) * interval_len + 1.0;
      d9 = interval_len * b_j;
      if (d8 > d9) {
        apnd = 0;
        cdiff = 0;
      } else {
        apnd = (int)d8 - 1;
        cdiff = (int)d9;
      }

      ndbl = r6->size[0] * r6->size[1];
      r6->size[0] = 1;
      r6->size[1] = cdiff - apnd;
      emxEnsureCapacity((emxArray__common *)r6, ndbl, (int)sizeof(int));
      b_n = cdiff - apnd;
      for (cdiff = 0; cdiff < b_n; cdiff++) {
        r6->data[r6->size[0] * cdiff] = apnd + cdiff;
      }

      b_n = r6->size[0] * r6->size[1];
      for (apnd = 0; apnd < b_n; apnd++) {
        input_2_to_ident->data[r6->data[apnd]] = dataBuff->data[(int)b_i - 1].
          input_2->data[apnd];
      }

      d8 = (b_j - 1.0) * interval_len + 1.0;
      d9 = interval_len * b_j;
      if (d8 > d9) {
        apnd = 0;
        cdiff = 0;
      } else {
        apnd = (int)d8 - 1;
        cdiff = (int)d9;
      }

      ndbl = r6->size[0] * r6->size[1];
      r6->size[0] = 1;
      r6->size[1] = cdiff - apnd;
      emxEnsureCapacity((emxArray__common *)r6, ndbl, (int)sizeof(int));
      b_n = cdiff - apnd;
      for (cdiff = 0; cdiff < b_n; cdiff++) {
        r6->data[r6->size[0] * cdiff] = apnd + cdiff;
      }

      b_n = r6->size[0] * r6->size[1];
      for (apnd = 0; apnd < b_n; apnd++) {
        input_3_to_ident->data[r6->data[apnd]] = dataBuff->data[(int)b_i - 1].
          input_3->data[apnd];
      }

      d8 = (b_j - 1.0) * interval_len + 1.0;
      d9 = interval_len * b_j;
      if (d8 > d9) {
        apnd = 0;
        cdiff = 0;
      } else {
        apnd = (int)d8 - 1;
        cdiff = (int)d9;
      }

      ndbl = r6->size[0] * r6->size[1];
      r6->size[0] = 1;
      r6->size[1] = cdiff - apnd;
      emxEnsureCapacity((emxArray__common *)r6, ndbl, (int)sizeof(int));
      b_n = cdiff - apnd;
      for (cdiff = 0; cdiff < b_n; cdiff++) {
        r6->data[r6->size[0] * cdiff] = apnd + cdiff;
      }

      b_n = r6->size[0] * r6->size[1];
      for (apnd = 0; apnd < b_n; apnd++) {
        output_to_ident->data[r6->data[apnd]] = dataBuff->data[(int)b_i - 1].
          output->data[apnd];
      }

      d8 = (b_j - 1.0) * interval_len + 1.0;
      d9 = interval_len * b_j;
      if (d8 > d9) {
        apnd = 0;
        cdiff = 0;
      } else {
        apnd = (int)d8 - 1;
        cdiff = (int)d9;
      }

      ndbl = r6->size[0] * r6->size[1];
      r6->size[0] = 1;
      r6->size[1] = cdiff - apnd;
      emxEnsureCapacity((emxArray__common *)r6, ndbl, (int)sizeof(int));
      b_n = cdiff - apnd;
      for (cdiff = 0; cdiff < b_n; cdiff++) {
        r6->data[r6->size[0] * cdiff] = apnd + cdiff;
      }

      b_n = r6->size[0] * r6->size[1];
      for (apnd = 0; apnd < b_n; apnd++) {
        output_sp->data[r6->data[apnd]] = dataBuff->data[(int)b_i - 1].
          sp_value->data[apnd];
      }

      b_j++;
      i++;
    }

    emxFree_int32_T(&r6);
    emxInit_real_T1(&b_input_1_to_ident, 1);
    i8 = b_input_1_to_ident->size[0];
    b_input_1_to_ident->size[0] = input_1_to_ident->size[0];
    emxEnsureCapacity((emxArray__common *)b_input_1_to_ident, i8, (int)sizeof
                      (double));
    b_n = input_1_to_ident->size[0];
    for (i8 = 0; i8 < b_n; i8++) {
      b_input_1_to_ident->data[i8] = input_1_to_ident->data[i8];
    }

    FHZN_shift_signal(b_input_1_to_ident, signal_del, input_1_to_ident);
    op_offset[0] = input_1_to_ident->data[(int)op_time_int - 1];
    op_offset[1] = input_2_to_ident->data[(int)op_time_int - 1];
    op_offset[2] = input_3_to_ident->data[(int)op_time_int - 1];
    op_offset[3] = output_to_ident->data[(int)op_time_int - 1];
    op_offset[4] = output_sp->data[(int)op_time_int - 1];

    /* offset minus */
    b_op_offset = op_offset[0];
    i8 = input_1_to_ident->size[0];
    emxEnsureCapacity((emxArray__common *)input_1_to_ident, i8, (int)sizeof
                      (double));
    b_n = input_1_to_ident->size[0];
    emxFree_real_T(&b_input_1_to_ident);
    for (i8 = 0; i8 < b_n; i8++) {
      input_1_to_ident->data[i8] -= b_op_offset;
    }

    b_op_offset = op_offset[1];
    i8 = input_2_to_ident->size[0];
    emxEnsureCapacity((emxArray__common *)input_2_to_ident, i8, (int)sizeof
                      (double));
    b_n = input_2_to_ident->size[0];
    for (i8 = 0; i8 < b_n; i8++) {
      input_2_to_ident->data[i8] -= b_op_offset;
    }

    b_op_offset = op_offset[2];
    i8 = input_3_to_ident->size[0];
    emxEnsureCapacity((emxArray__common *)input_3_to_ident, i8, (int)sizeof
                      (double));
    b_n = input_3_to_ident->size[0];
    for (i8 = 0; i8 < b_n; i8++) {
      input_3_to_ident->data[i8] -= b_op_offset;
    }

    b_op_offset = op_offset[3];
    i8 = output_to_ident->size[0];
    emxEnsureCapacity((emxArray__common *)output_to_ident, i8, (int)sizeof
                      (double));
    b_n = output_to_ident->size[0];
    for (i8 = 0; i8 < b_n; i8++) {
      output_to_ident->data[i8] -= b_op_offset;
    }

    b_op_offset = op_offset[4];
    i8 = output_sp->size[0];
    emxEnsureCapacity((emxArray__common *)output_sp, i8, (int)sizeof(double));
    b_n = output_sp->size[0];
    for (i8 = 0; i8 < b_n; i8++) {
      output_sp->data[i8] -= b_op_offset;
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
    i8 = t->size[0] * t->size[1];
    t->size[0] = 1;
    t->size[1] = b_n;
    emxEnsureCapacity((emxArray__common *)t, i8, (int)sizeof(double));
    if (b_n > 0) {
      t->data[0] = 0.0;
      if (b_n > 1) {
        t->data[b_n - 1] = apnd;
        i8 = b_n - 1;
        ndbl = i8 / 2;
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
    i8 = b_output_sp->size[0];
    b_output_sp->size[0] = output_sp->size[0];
    emxEnsureCapacity((emxArray__common *)b_output_sp, i8, (int)sizeof(double));
    b_n = output_sp->size[0];
    for (i8 = 0; i8 < b_n; i8++) {
      b_output_sp->data[i8] = output_sp->data[i8] - output_to_ident->data[i8];
    }

    emxInit_real_T1(&X0, 1);
    b_power(b_output_sp, X0);
    sp_diff = b_sum(X0);
    *sp_diff_avg = sp_diff / new_model_intervals;

    /* inputs_to_ident(:,1)=input_1_to_ident; */
    /* inputs_to_ident(:,2)=input_2_to_ident; */
    emxFree_real_T(&b_output_sp);
    emxInit_real_T(&ident_inputs, 2);
    if ((model_inputs[0] == 1.0) && (model_inputs[1] == 1.0) && (model_inputs[2]
         == 0.0)) {
      ndbl = input_1_to_ident->size[0];
      cdiff = input_2_to_ident->size[0];
      i8 = ident_inputs->size[0] * ident_inputs->size[1];
      ident_inputs->size[0] = 2;
      ident_inputs->size[1] = ndbl;
      emxEnsureCapacity((emxArray__common *)ident_inputs, i8, (int)sizeof(double));
      for (i8 = 0; i8 < ndbl; i8++) {
        ident_inputs->data[ident_inputs->size[0] * i8] = input_1_to_ident->
          data[i8];
      }

      for (i8 = 0; i8 < cdiff; i8++) {
        ident_inputs->data[1 + ident_inputs->size[0] * i8] =
          input_2_to_ident->data[i8];
      }

      ident_inputs_nr = 2;
      for (i8 = 0; i8 < 3; i8++) {
        model_inputs_prop[i8] = iv3[i8];
      }
    } else if ((model_inputs[0] == 1.0) && (model_inputs[1] == 0.0) &&
               (model_inputs[2] == 1.0)) {
      ndbl = input_1_to_ident->size[0];
      b_n = input_3_to_ident->size[0];
      i8 = ident_inputs->size[0] * ident_inputs->size[1];
      ident_inputs->size[0] = 2;
      ident_inputs->size[1] = ndbl;
      emxEnsureCapacity((emxArray__common *)ident_inputs, i8, (int)sizeof(double));
      for (i8 = 0; i8 < ndbl; i8++) {
        ident_inputs->data[ident_inputs->size[0] * i8] = input_1_to_ident->
          data[i8];
      }

      for (i8 = 0; i8 < b_n; i8++) {
        ident_inputs->data[1 + ident_inputs->size[0] * i8] =
          input_3_to_ident->data[i8];
      }

      ident_inputs_nr = 2;
      for (i8 = 0; i8 < 3; i8++) {
        model_inputs_prop[i8] = iv4[i8];
      }
    } else if ((model_inputs[0] == 0.0) && (model_inputs[1] == 1.0) &&
               (model_inputs[2] == 1.0)) {
      cdiff = input_2_to_ident->size[0];
      b_n = input_3_to_ident->size[0];
      i8 = ident_inputs->size[0] * ident_inputs->size[1];
      ident_inputs->size[0] = 2;
      ident_inputs->size[1] = cdiff;
      emxEnsureCapacity((emxArray__common *)ident_inputs, i8, (int)sizeof(double));
      for (i8 = 0; i8 < cdiff; i8++) {
        ident_inputs->data[ident_inputs->size[0] * i8] = input_2_to_ident->
          data[i8];
      }

      for (i8 = 0; i8 < b_n; i8++) {
        ident_inputs->data[1 + ident_inputs->size[0] * i8] =
          input_3_to_ident->data[i8];
      }

      ident_inputs_nr = 2;
      for (i8 = 0; i8 < 3; i8++) {
        model_inputs_prop[i8] = iv5[i8];
      }
    } else {
      ndbl = input_1_to_ident->size[0];
      cdiff = input_2_to_ident->size[0];
      b_n = input_3_to_ident->size[0];
      i8 = ident_inputs->size[0] * ident_inputs->size[1];
      ident_inputs->size[0] = 3;
      ident_inputs->size[1] = ndbl;
      emxEnsureCapacity((emxArray__common *)ident_inputs, i8, (int)sizeof(double));
      for (i8 = 0; i8 < ndbl; i8++) {
        ident_inputs->data[ident_inputs->size[0] * i8] = input_1_to_ident->
          data[i8];
      }

      for (i8 = 0; i8 < cdiff; i8++) {
        ident_inputs->data[1 + ident_inputs->size[0] * i8] =
          input_2_to_ident->data[i8];
      }

      for (i8 = 0; i8 < b_n; i8++) {
        ident_inputs->data[2 + ident_inputs->size[0] * i8] =
          input_3_to_ident->data[i8];
      }

      ident_inputs_nr = 3;
      for (i8 = 0; i8 < 3; i8++) {
        model_inputs_prop[i8] = 1.0;
      }
    }

    emxFree_real_T(&input_3_to_ident);
    emxFree_real_T(&input_2_to_ident);
    emxFree_real_T(&input_1_to_ident);
    i = 0;
    emxInit_real_T(&A, 2);
    emxInit_real_T(&C, 2);
    emxInit_real_T(&B, 2);
    emxInit_real_T(&unusedU0, 2);
    emxInit_real_T(&b_ident_inputs, 2);
    emxInit_real_T(&b_t, 2);
    emxInit_real_T(&c_ident_inputs, 2);
    emxInit_real_T(&b_output_to_ident, 2);
    while (i <= MFM_ident_models->size[0] - 1) {
      i8 = b_output_to_ident->size[0] * b_output_to_ident->size[1];
      b_output_to_ident->size[0] = 1;
      b_output_to_ident->size[1] = output_to_ident->size[0];
      emxEnsureCapacity((emxArray__common *)b_output_to_ident, i8, (int)sizeof
                        (double));
      b_n = output_to_ident->size[0];
      for (i8 = 0; i8 < b_n; i8++) {
        b_output_to_ident->data[b_output_to_ident->size[0] * i8] =
          output_to_ident->data[i8];
      }

      FHZN_MFM_model_ident_LSM(ident_inputs_nr, ident_inputs, b_output_to_ident,
        MFM_ident_models->data[i].h, MFM_ident_models->data[i].n,
        MFM_ident_models->data[i].m, MFM_ident_models->data[i].N,
        MFM_ident_models->data[i].M, output_sp);

      /* ni_min */
      if (FHZN_check_model_prop(output_sp, ident_inputs_nr, model_inputs_prop,
           MFM_ident_models->data[i].n, dv1)) {
        FHZN_get_MISO_model(output_sp, ident_inputs_nr, MFM_ident_models->data[i]
                            .n, MFM_ident_models->data[i].m, A, B, C, unusedU0);
        i8 = b_t->size[0] * b_t->size[1];
        b_t->size[0] = 1;
        b_t->size[1] = t->size[1];
        emxEnsureCapacity((emxArray__common *)b_t, i8, (int)sizeof(double));
        b_n = t->size[0] * t->size[1];
        for (i8 = 0; i8 < b_n; i8++) {
          b_t->data[i8] = t->data[i8];
        }

        i8 = c_ident_inputs->size[0] * c_ident_inputs->size[1];
        c_ident_inputs->size[0] = ident_inputs->size[1];
        c_ident_inputs->size[1] = ident_inputs->size[0];
        emxEnsureCapacity((emxArray__common *)c_ident_inputs, i8, (int)sizeof
                          (double));
        b_n = ident_inputs->size[0];
        for (i8 = 0; i8 < b_n; i8++) {
          ndbl = ident_inputs->size[1];
          for (apnd = 0; apnd < ndbl; apnd++) {
            c_ident_inputs->data[apnd + c_ident_inputs->size[0] * i8] =
              ident_inputs->data[i8 + ident_inputs->size[0] * apnd];
          }
        }

        c_FHZN_exact_state_observer_ini(A, B, C, b_t, c_ident_inputs,
          output_to_ident, X0);
        i8 = b_ident_inputs->size[0] * b_ident_inputs->size[1];
        b_ident_inputs->size[0] = ident_inputs->size[1];
        b_ident_inputs->size[1] = ident_inputs->size[0];
        emxEnsureCapacity((emxArray__common *)b_ident_inputs, i8, (int)sizeof
                          (double));
        b_n = ident_inputs->size[0];
        for (i8 = 0; i8 < b_n; i8++) {
          ndbl = ident_inputs->size[1];
          for (apnd = 0; apnd < ndbl; apnd++) {
            b_ident_inputs->data[apnd + b_ident_inputs->size[0] * i8] =
              ident_inputs->data[i8 + ident_inputs->size[0] * apnd];
          }
        }

        sim_res = c_FHZN_simulate_lsys_output_com(A, B, C, X0, b_ident_inputs,
          output_to_ident);
        if ((1 + i == 1) && (sim_res < original_model_diff)) {
          i8 = ni_min_opt->size[0];
          ni_min_opt->size[0] = output_sp->size[0];
          emxEnsureCapacity((emxArray__common *)ni_min_opt, i8, (int)sizeof
                            (double));
          b_n = output_sp->size[0];
          for (i8 = 0; i8 < b_n; i8++) {
            ni_min_opt->data[i8] = output_sp->data[i8];
          }

          sim_res_opt = sim_res;
          model_opt_nr = 0;
          i8 = model_X0->size[0];
          model_X0->size[0] = X0->size[0];
          emxEnsureCapacity((emxArray__common *)model_X0, i8, (int)sizeof(double));
          b_n = X0->size[0];
          for (i8 = 0; i8 < b_n; i8++) {
            model_X0->data[i8] = X0->data[i8];
          }
        } else {
          if ((1 + i > 1) && (sim_res < original_model_diff) && (sim_res <
               sim_res_opt)) {
            sim_res_opt = sim_res;
            i8 = ni_min_opt->size[0];
            ni_min_opt->size[0] = output_sp->size[0];
            emxEnsureCapacity((emxArray__common *)ni_min_opt, i8, (int)sizeof
                              (double));
            b_n = output_sp->size[0];
            for (i8 = 0; i8 < b_n; i8++) {
              ni_min_opt->data[i8] = output_sp->data[i8];
            }

            model_opt_nr = i;
            i8 = model_X0->size[0];
            model_X0->size[0] = X0->size[0];
            emxEnsureCapacity((emxArray__common *)model_X0, i8, (int)sizeof
                              (double));
            b_n = X0->size[0];
            for (i8 = 0; i8 < b_n; i8++) {
              model_X0->data[i8] = X0->data[i8];
            }
          }
        }
      }

      i++;
    }

    emxFree_real_T(&b_output_to_ident);
    emxFree_real_T(&c_ident_inputs);
    emxFree_real_T(&b_t);
    emxFree_real_T(&b_ident_inputs);
    emxFree_real_T(&unusedU0);
    emxFree_real_T(&B);
    emxFree_real_T(&C);
    emxFree_real_T(&A);
    emxFree_real_T(&X0);
    emxFree_real_T(&ident_inputs);
    emxFree_real_T(&t);
    emxFree_real_T(&output_sp);
    emxFree_real_T(&output_to_ident);
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
 * File trailer for FHZN_obtain_FHZ3_model_nonzero.c
 *
 * [EOF]
 */
