/*
 * File: FHZN_obtain_FHZ4_model.c
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
#include "mod.h"
#include "FHZN_define_model_del_emxutil.h"
#include "FHZN_simulate_lsys_output_compare.h"
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
 *                double min_init_model_intervals
 *                double interval_len
 *                double *model_identified
 *                double *model_identified_op_int
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
void FHZN_obtain_FHZ4_model(const emxArray_FHZ4_DataBuff *dataBuff, const
  emxArray_FHZ4_Int *FHZ_intervals, const emxArray_MFM_Struct *MFM_ident_models,
  double intervals_nr, double min_init_model_intervals, double interval_len,
  double *model_identified, double *model_identified_op_int, double *op_time,
  emxArray_real_T *ni_min_opt, double op_offset[4], double *model_diff_avg,
  double *sp_diff_avg, emxArray_real_T *model_X0, double *n, double *m, double
  *N, double *M, double *h)
{
  int op_found;
  double op_interval;
  double signal_del;
  signed char model_inputs[2];
  int i;
  int i17;
  int model_opt_nr;
  double sim_res_opt;
  boolean_T exitg1;
  double b_i;
  int j;
  emxArray_real_T *input_1_to_ident;
  double size1;
  int loop_ub;
  emxArray_real_T *input_2_to_ident;
  emxArray_real_T *output_to_ident;
  emxArray_real_T *output_sp;
  emxArray_int32_T *r11;
  double b_op_offset;
  int i18;
  int i19;
  double d10;
  int input_2_to_ident_idx_0;
  emxArray_real_T *b_input_1_to_ident;
  emxArray_real_T *b_output_sp;
  double sp_diff;
  emxArray_real_T *A;
  emxArray_real_T *B;
  emxArray_real_T *C;
  emxArray_real_T *unusedU0;
  emxArray_real_T *X0;
  emxArray_real_T *c_input_1_to_ident;
  emxArray_real_T *d_input_1_to_ident;
  emxArray_real_T *b_output_to_ident;
  double sim_res;
  op_found = 0;
  *op_time = 0.0;
  op_interval = 0.0;
  signal_del = 0.0;
  for (i = 0; i < 2; i++) {
    model_inputs[i] = 0;
  }

  for (i = 0; i < 4; i++) {
    op_offset[i] = 0.0;
  }

  i17 = ni_min_opt->size[0];
  ni_min_opt->size[0] = 4;
  emxEnsureCapacity((emxArray__common *)ni_min_opt, i17, (int)sizeof(double));
  for (i17 = 0; i17 < 4; i17++) {
    ni_min_opt->data[i17] = 0.0;
  }

  model_opt_nr = -1;
  *model_identified = 0.0;
  *model_identified_op_int = 0.0;
  *model_diff_avg = 0.0;
  *sp_diff_avg = 0.0;
  i17 = model_X0->size[0];
  model_X0->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)model_X0, i17, (int)sizeof(double));
  model_X0->data[0] = 0.0;
  *n = 0.0;
  *m = 0.0;
  *N = 0.0;
  *M = 0.0;
  *h = 0.0;
  sim_res_opt = rtInf;

  /* find operating point */
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i <= (int)intervals_nr - 1)) {
    if (FHZ_intervals->data[i].op_interval_possible) {
      op_found = 1;
      *op_time = FHZ_intervals->data[i].op_interval_time;
      signal_del = FHZ_intervals->data[i].model_del;
      op_interval = 1.0 + (double)i;
      exitg1 = true;
    } else {
      i++;
    }
  }

  /* check input signals */
  if ((op_found != 0) && ((intervals_nr - op_interval) + 1.0 >=
                          min_init_model_intervals)) {
    i17 = (int)(intervals_nr + (1.0 - op_interval));
    for (i = 0; i < i17; i++) {
      b_i = op_interval + (double)i;
      for (j = 0; j < 2; j++) {
        if (FHZ_intervals->data[(int)b_i - 1].model_inputs[j] >= 1.0) {
          model_inputs[j] = 1;
        }
      }
    }
  }

  /* op_interval=op_interval+ident_offset_intervals; */
  /* op_time=250; */
  /* build signals for ident */
  if (model_inputs[0] + model_inputs[1] == 2) {
    emxInit_real_T1(&input_1_to_ident, 1);
    size1 = (intervals_nr - op_interval) * interval_len + (interval_len - b_mod(*
      op_time, interval_len));
    i17 = input_1_to_ident->size[0];
    input_1_to_ident->size[0] = (int)size1;
    emxEnsureCapacity((emxArray__common *)input_1_to_ident, i17, (int)sizeof
                      (double));
    loop_ub = (int)size1;
    for (i17 = 0; i17 < loop_ub; i17++) {
      input_1_to_ident->data[i17] = 0.0;
    }

    emxInit_real_T1(&input_2_to_ident, 1);
    i17 = input_2_to_ident->size[0];
    input_2_to_ident->size[0] = (int)size1;
    emxEnsureCapacity((emxArray__common *)input_2_to_ident, i17, (int)sizeof
                      (double));
    loop_ub = (int)size1;
    for (i17 = 0; i17 < loop_ub; i17++) {
      input_2_to_ident->data[i17] = 0.0;
    }

    emxInit_real_T1(&output_to_ident, 1);
    i17 = output_to_ident->size[0];
    output_to_ident->size[0] = (int)size1;
    emxEnsureCapacity((emxArray__common *)output_to_ident, i17, (int)sizeof
                      (double));
    loop_ub = (int)size1;
    for (i17 = 0; i17 < loop_ub; i17++) {
      output_to_ident->data[i17] = 0.0;
    }

    emxInit_real_T1(&output_sp, 1);
    i17 = output_sp->size[0];
    output_sp->size[0] = (int)size1;
    emxEnsureCapacity((emxArray__common *)output_sp, i17, (int)sizeof(double));
    loop_ub = (int)size1;
    for (i17 = 0; i17 < loop_ub; i17++) {
      output_sp->data[i17] = 0.0;
    }

    i17 = (int)(intervals_nr + (1.0 - op_interval));
    i = 0;
    emxInit_int32_T(&r11, 2);
    while (i <= i17 - 1) {
      b_i = op_interval + (double)i;
      if (b_i == op_interval) {
        b_op_offset = b_mod(*op_time, interval_len) + 1.0;
        if (b_op_offset > interval_len) {
          i18 = 1;
          i19 = 0;
        } else {
          i18 = (int)b_op_offset;
          i19 = (int)interval_len;
        }

        loop_ub = i19 - i18;
        for (i19 = 0; i19 <= loop_ub; i19++) {
          input_1_to_ident->data[i19] = dataBuff->data[(int)b_i - 1]
            .input_1->data[(i18 + i19) - 1];
        }

        b_op_offset = b_mod(*op_time, interval_len) + 1.0;
        if (b_op_offset > interval_len) {
          i18 = 1;
          i19 = 0;
        } else {
          i18 = (int)b_op_offset;
          i19 = (int)interval_len;
        }

        loop_ub = i19 - i18;
        for (i19 = 0; i19 <= loop_ub; i19++) {
          input_2_to_ident->data[i19] = dataBuff->data[(int)b_i - 1]
            .input_2->data[(i18 + i19) - 1];
        }

        b_op_offset = b_mod(*op_time, interval_len) + 1.0;
        if (b_op_offset > interval_len) {
          i18 = 1;
          i19 = 0;
        } else {
          i18 = (int)b_op_offset;
          i19 = (int)interval_len;
        }

        loop_ub = i19 - i18;
        for (i19 = 0; i19 <= loop_ub; i19++) {
          output_to_ident->data[i19] = dataBuff->data[(int)b_i - 1].output->
            data[(i18 + i19) - 1];
        }

        b_op_offset = b_mod(*op_time, interval_len) + 1.0;
        if (b_op_offset > interval_len) {
          i18 = 1;
          i19 = 0;
        } else {
          i18 = (int)b_op_offset;
          i19 = (int)interval_len;
        }

        loop_ub = i19 - i18;
        for (i19 = 0; i19 <= loop_ub; i19++) {
          output_sp->data[i19] = dataBuff->data[(int)b_i - 1].output->data[(i18
            + i19) - 1];
        }
      } else {
        b_op_offset = ((interval_len - b_mod(*op_time, interval_len)) + 1.0) +
          ((b_i - op_interval) - 1.0) * interval_len;
        d10 = (interval_len - b_mod(*op_time, interval_len)) + (b_i -
          op_interval) * interval_len;
        if (b_op_offset > d10) {
          i18 = 0;
          i19 = 0;
        } else {
          i18 = (int)b_op_offset - 1;
          i19 = (int)d10;
        }

        input_2_to_ident_idx_0 = r11->size[0] * r11->size[1];
        r11->size[0] = 1;
        r11->size[1] = i19 - i18;
        emxEnsureCapacity((emxArray__common *)r11, input_2_to_ident_idx_0, (int)
                          sizeof(int));
        loop_ub = i19 - i18;
        for (i19 = 0; i19 < loop_ub; i19++) {
          r11->data[r11->size[0] * i19] = i18 + i19;
        }

        loop_ub = r11->size[0] * r11->size[1];
        for (i18 = 0; i18 < loop_ub; i18++) {
          input_1_to_ident->data[r11->data[i18]] = dataBuff->data[(int)b_i - 1].
            input_1->data[i18];
        }

        b_op_offset = ((interval_len - b_mod(*op_time, interval_len)) + 1.0) +
          ((b_i - op_interval) - 1.0) * interval_len;
        d10 = (interval_len - b_mod(*op_time, interval_len)) + (b_i -
          op_interval) * interval_len;
        if (b_op_offset > d10) {
          i18 = 0;
          i19 = 0;
        } else {
          i18 = (int)b_op_offset - 1;
          i19 = (int)d10;
        }

        input_2_to_ident_idx_0 = r11->size[0] * r11->size[1];
        r11->size[0] = 1;
        r11->size[1] = i19 - i18;
        emxEnsureCapacity((emxArray__common *)r11, input_2_to_ident_idx_0, (int)
                          sizeof(int));
        loop_ub = i19 - i18;
        for (i19 = 0; i19 < loop_ub; i19++) {
          r11->data[r11->size[0] * i19] = i18 + i19;
        }

        loop_ub = r11->size[0] * r11->size[1];
        for (i18 = 0; i18 < loop_ub; i18++) {
          input_2_to_ident->data[r11->data[i18]] = dataBuff->data[(int)b_i - 1].
            input_2->data[i18];
        }

        b_op_offset = ((interval_len - b_mod(*op_time, interval_len)) + 1.0) +
          ((b_i - op_interval) - 1.0) * interval_len;
        d10 = (interval_len - b_mod(*op_time, interval_len)) + (b_i -
          op_interval) * interval_len;
        if (b_op_offset > d10) {
          i18 = 0;
          i19 = 0;
        } else {
          i18 = (int)b_op_offset - 1;
          i19 = (int)d10;
        }

        input_2_to_ident_idx_0 = r11->size[0] * r11->size[1];
        r11->size[0] = 1;
        r11->size[1] = i19 - i18;
        emxEnsureCapacity((emxArray__common *)r11, input_2_to_ident_idx_0, (int)
                          sizeof(int));
        loop_ub = i19 - i18;
        for (i19 = 0; i19 < loop_ub; i19++) {
          r11->data[r11->size[0] * i19] = i18 + i19;
        }

        loop_ub = r11->size[0] * r11->size[1];
        for (i18 = 0; i18 < loop_ub; i18++) {
          output_to_ident->data[r11->data[i18]] = dataBuff->data[(int)b_i - 1].
            output->data[i18];
        }

        b_op_offset = ((interval_len - b_mod(*op_time, interval_len)) + 1.0) +
          ((b_i - op_interval) - 1.0) * interval_len;
        d10 = (interval_len - b_mod(*op_time, interval_len)) + (b_i -
          op_interval) * interval_len;
        if (b_op_offset > d10) {
          i18 = 0;
          i19 = 0;
        } else {
          i18 = (int)b_op_offset - 1;
          i19 = (int)d10;
        }

        input_2_to_ident_idx_0 = r11->size[0] * r11->size[1];
        r11->size[0] = 1;
        r11->size[1] = i19 - i18;
        emxEnsureCapacity((emxArray__common *)r11, input_2_to_ident_idx_0, (int)
                          sizeof(int));
        loop_ub = i19 - i18;
        for (i19 = 0; i19 < loop_ub; i19++) {
          r11->data[r11->size[0] * i19] = i18 + i19;
        }

        loop_ub = r11->size[0] * r11->size[1];
        for (i18 = 0; i18 < loop_ub; i18++) {
          output_sp->data[r11->data[i18]] = dataBuff->data[(int)b_i - 1].
            sp_value->data[i18];
        }
      }

      i++;
    }

    emxFree_int32_T(&r11);
    emxInit_real_T1(&b_input_1_to_ident, 1);
    i17 = b_input_1_to_ident->size[0];
    b_input_1_to_ident->size[0] = input_1_to_ident->size[0];
    emxEnsureCapacity((emxArray__common *)b_input_1_to_ident, i17, (int)sizeof
                      (double));
    loop_ub = input_1_to_ident->size[0];
    for (i17 = 0; i17 < loop_ub; i17++) {
      b_input_1_to_ident->data[i17] = input_1_to_ident->data[i17];
    }

    FHZN_shift_signal(b_input_1_to_ident, signal_del, input_1_to_ident);
    op_offset[0] = input_1_to_ident->data[(int)*op_time - 1];
    op_offset[1] = input_2_to_ident->data[(int)*op_time - 1];
    op_offset[2] = output_to_ident->data[(int)*op_time - 1];
    op_offset[3] = output_sp->data[(int)*op_time - 1];

    /* offset minus */
    b_op_offset = op_offset[0];
    i17 = input_1_to_ident->size[0];
    emxEnsureCapacity((emxArray__common *)input_1_to_ident, i17, (int)sizeof
                      (double));
    loop_ub = input_1_to_ident->size[0];
    emxFree_real_T(&b_input_1_to_ident);
    for (i17 = 0; i17 < loop_ub; i17++) {
      input_1_to_ident->data[i17] -= b_op_offset;
    }

    b_op_offset = op_offset[1];
    i17 = input_2_to_ident->size[0];
    emxEnsureCapacity((emxArray__common *)input_2_to_ident, i17, (int)sizeof
                      (double));
    loop_ub = input_2_to_ident->size[0];
    for (i17 = 0; i17 < loop_ub; i17++) {
      input_2_to_ident->data[i17] -= b_op_offset;
    }

    b_op_offset = op_offset[2];
    i17 = output_to_ident->size[0];
    emxEnsureCapacity((emxArray__common *)output_to_ident, i17, (int)sizeof
                      (double));
    loop_ub = output_to_ident->size[0];
    for (i17 = 0; i17 < loop_ub; i17++) {
      output_to_ident->data[i17] -= b_op_offset;
    }

    b_op_offset = op_offset[3];
    i17 = output_sp->size[0];
    emxEnsureCapacity((emxArray__common *)output_sp, i17, (int)sizeof(double));
    loop_ub = output_sp->size[0];
    for (i17 = 0; i17 < loop_ub; i17++) {
      output_sp->data[i17] -= b_op_offset;
    }

    emxInit_real_T1(&b_output_sp, 1);

    /* check the sp diff */
    /* for i=1:length(output_to_ident) */
    /*     sp_diff=sp_diff+(output_sp(i)-output_to_ident(i))^2; */
    /* end */
    i17 = b_output_sp->size[0];
    b_output_sp->size[0] = output_sp->size[0];
    emxEnsureCapacity((emxArray__common *)b_output_sp, i17, (int)sizeof(double));
    loop_ub = output_sp->size[0];
    for (i17 = 0; i17 < loop_ub; i17++) {
      b_output_sp->data[i17] = output_sp->data[i17] - output_to_ident->data[i17];
    }

    b_power(b_output_sp, output_sp);
    sp_diff = b_sum(output_sp);
    *sp_diff_avg = sp_diff / ((intervals_nr - op_interval) + 1.0);

    /*  identify the model */
    /* inputs_to_ident=zeros(length(input_1_to_ident),model_inputs_nr); */
    /* inputs_to_ident(:,1)=input_1_to_ident; */
    /* inputs_to_ident(:,2)=input_2_to_ident; */
    i = 0;
    emxFree_real_T(&b_output_sp);
    emxInit_real_T(&A, 2);
    emxInit_real_T(&B, 2);
    emxInit_real_T(&C, 2);
    emxInit_real_T(&unusedU0, 2);
    emxInit_real_T1(&X0, 1);
    emxInit_real_T(&c_input_1_to_ident, 2);
    emxInit_real_T(&d_input_1_to_ident, 2);
    emxInit_real_T(&b_output_to_ident, 2);
    while (i <= MFM_ident_models->size[0] - 1) {
      loop_ub = input_1_to_ident->size[0];
      input_2_to_ident_idx_0 = input_2_to_ident->size[0];
      i17 = d_input_1_to_ident->size[0] * d_input_1_to_ident->size[1];
      d_input_1_to_ident->size[0] = 2;
      d_input_1_to_ident->size[1] = loop_ub;
      emxEnsureCapacity((emxArray__common *)d_input_1_to_ident, i17, (int)sizeof
                        (double));
      for (i17 = 0; i17 < loop_ub; i17++) {
        d_input_1_to_ident->data[d_input_1_to_ident->size[0] * i17] =
          input_1_to_ident->data[i17];
      }

      for (i17 = 0; i17 < input_2_to_ident_idx_0; i17++) {
        d_input_1_to_ident->data[1 + d_input_1_to_ident->size[0] * i17] =
          input_2_to_ident->data[i17];
      }

      i17 = b_output_to_ident->size[0] * b_output_to_ident->size[1];
      b_output_to_ident->size[0] = 1;
      b_output_to_ident->size[1] = output_to_ident->size[0];
      emxEnsureCapacity((emxArray__common *)b_output_to_ident, i17, (int)sizeof
                        (double));
      loop_ub = output_to_ident->size[0];
      for (i17 = 0; i17 < loop_ub; i17++) {
        b_output_to_ident->data[b_output_to_ident->size[0] * i17] =
          output_to_ident->data[i17];
      }

      b_FHZN_MFM_model_ident_LSM(d_input_1_to_ident, b_output_to_ident,
        MFM_ident_models->data[i].h, MFM_ident_models->data[i].n,
        MFM_ident_models->data[i].m, MFM_ident_models->data[i].N,
        MFM_ident_models->data[i].M, output_sp);

      /* ni_min */
      if (b_FHZN_check_model_prop(output_sp, MFM_ident_models->data[i].n)) {
        b_FHZN_get_MISO_model(output_sp, MFM_ident_models->data[i].n,
                              MFM_ident_models->data[i].m, A, B, C, unusedU0);
        i17 = X0->size[0];
        X0->size[0] = A->size[0];
        emxEnsureCapacity((emxArray__common *)X0, i17, (int)sizeof(double));
        loop_ub = A->size[0];
        for (i17 = 0; i17 < loop_ub; i17++) {
          X0->data[i17] = 0.0;
        }

        loop_ub = input_1_to_ident->size[0];
        input_2_to_ident_idx_0 = input_2_to_ident->size[0];
        i17 = c_input_1_to_ident->size[0] * c_input_1_to_ident->size[1];
        c_input_1_to_ident->size[0] = loop_ub;
        c_input_1_to_ident->size[1] = 2;
        emxEnsureCapacity((emxArray__common *)c_input_1_to_ident, i17, (int)
                          sizeof(double));
        for (i17 = 0; i17 < loop_ub; i17++) {
          c_input_1_to_ident->data[i17] = input_1_to_ident->data[i17];
        }

        for (i17 = 0; i17 < input_2_to_ident_idx_0; i17++) {
          c_input_1_to_ident->data[i17 + c_input_1_to_ident->size[0]] =
            input_2_to_ident->data[i17];
        }

        sim_res = d_FHZN_simulate_lsys_output_com(A, B, C, X0,
          c_input_1_to_ident, output_to_ident);

        /* sim_res */
        if (1 + i == 1) {
          i17 = ni_min_opt->size[0];
          ni_min_opt->size[0] = output_sp->size[0];
          emxEnsureCapacity((emxArray__common *)ni_min_opt, i17, (int)sizeof
                            (double));
          loop_ub = output_sp->size[0];
          for (i17 = 0; i17 < loop_ub; i17++) {
            ni_min_opt->data[i17] = output_sp->data[i17];
          }

          model_opt_nr = 0;
          i17 = model_X0->size[0];
          model_X0->size[0] = X0->size[0];
          emxEnsureCapacity((emxArray__common *)model_X0, i17, (int)sizeof
                            (double));
          loop_ub = X0->size[0];
          for (i17 = 0; i17 < loop_ub; i17++) {
            model_X0->data[i17] = X0->data[i17];
          }
        } else {
          if (sim_res < sim_res_opt) {
            sim_res_opt = sim_res;
            i17 = ni_min_opt->size[0];
            ni_min_opt->size[0] = output_sp->size[0];
            emxEnsureCapacity((emxArray__common *)ni_min_opt, i17, (int)sizeof
                              (double));
            loop_ub = output_sp->size[0];
            for (i17 = 0; i17 < loop_ub; i17++) {
              ni_min_opt->data[i17] = output_sp->data[i17];
            }

            model_opt_nr = i;
            i17 = model_X0->size[0];
            model_X0->size[0] = X0->size[0];
            emxEnsureCapacity((emxArray__common *)model_X0, i17, (int)sizeof
                              (double));
            loop_ub = X0->size[0];
            for (i17 = 0; i17 < loop_ub; i17++) {
              model_X0->data[i17] = X0->data[i17];
            }
          }
        }
      }

      i++;
    }

    emxFree_real_T(&b_output_to_ident);
    emxFree_real_T(&d_input_1_to_ident);
    emxFree_real_T(&c_input_1_to_ident);
    emxFree_real_T(&X0);
    emxFree_real_T(&unusedU0);
    emxFree_real_T(&C);
    emxFree_real_T(&B);
    emxFree_real_T(&A);
    emxFree_real_T(&output_sp);
    emxFree_real_T(&output_to_ident);
    emxFree_real_T(&input_2_to_ident);
    emxFree_real_T(&input_1_to_ident);
    if (model_opt_nr + 1 > 0) {
      *model_identified = 1.0;
      *n = MFM_ident_models->data[model_opt_nr].n;
      *m = MFM_ident_models->data[model_opt_nr].m;
      *N = MFM_ident_models->data[model_opt_nr].N;
      *M = MFM_ident_models->data[model_opt_nr].M;
      *h = MFM_ident_models->data[model_opt_nr].h;
      *model_identified_op_int = op_interval;
      *model_diff_avg = sim_res_opt / ((intervals_nr - op_interval) + 1.0);
    }
  }
}

/*
 * File trailer for FHZN_obtain_FHZ4_model.c
 *
 * [EOF]
 */
