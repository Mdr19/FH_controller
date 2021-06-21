/*
 * File: FHZN_find_operating_point.c
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
#include "MD_modulating_func_d.h"
#include "FHZN_define_model_del_emxutil.h"
#include "conv.h"
#include "mean.h"
#include "abs.h"
#include "MD_modulating_func.h"

/* Function Definitions */

/*
 * UNTITLED2 Summary of this function goes here
 *    Detailed explanation goes here
 * Arguments    : double threshold
 *                double mean_interval
 *                double h_lin
 *                double m
 *                double N_lin
 *                double M_lin
 *                const emxArray_real_T *current_out
 *                double start_int_time
 *                boolean_T *op_interval_possible
 *                double *op_time
 * Return Type  : void
 */
void FHZN_find_operating_point(double threshold, double mean_interval, double
  h_lin, double m, double N_lin, double M_lin, const emxArray_real_T
  *current_out, double start_int_time, boolean_T *op_interval_possible, double
  *op_time)
{
  int n;
  double anew;
  double apnd;
  double ndbl;
  double cdiff;
  emxArray_real_T *y;
  int i0;
  int nm1d2;
  int k;
  emxArray_real_T *mod_func_lin;
  emxArray_real_T *b_mod_func_lin;
  int loop_ub;
  double mtmp;
  boolean_T exitg2;
  emxArray_real_T *mod_func_d_lin;
  int i;
  emxArray_real_T *b;
  double b_y;
  emxArray_real_T *b_mod_func_d_lin;
  emxArray_real_T *s;
  int cnt1;
  unsigned int cnt2;
  emxArray_real_T *y_dot_lin;
  emxArray_real_T *current_out_lin;
  emxArray_real_T *con;
  emxArray_real_T *b_y_dot_lin;
  emxArray_real_T *c_y_dot_lin;
  emxArray_real_T *c_mod_func_d_lin;
  int exitg1;
  *op_interval_possible = false;
  *op_time = 0.0;
  if (rtIsNaN(h_lin)) {
    n = 1;
    anew = rtNaN;
    apnd = h_lin;
  } else if (h_lin < 0.0) {
    n = 0;
    anew = 0.0;
    apnd = h_lin;
  } else if (rtIsInf(h_lin)) {
    n = 1;
    anew = rtNaN;
    apnd = h_lin;
  } else {
    anew = 0.0;
    ndbl = floor(h_lin + 0.5);
    apnd = ndbl;
    cdiff = ndbl - h_lin;
    if (fabs(cdiff) < 4.4408920985006262E-16 * h_lin) {
      ndbl++;
      apnd = h_lin;
    } else if (cdiff > 0.0) {
      apnd = ndbl - 1.0;
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }
  }

  emxInit_real_T(&y, 2);
  i0 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n;
  emxEnsureCapacity((emxArray__common *)y, i0, (int)sizeof(double));
  if (n > 0) {
    y->data[0] = anew;
    if (n > 1) {
      y->data[n - 1] = apnd;
      i0 = n - 1;
      nm1d2 = i0 / 2;
      for (k = 1; k < nm1d2; k++) {
        y->data[k] = anew + (double)k;
        y->data[(n - k) - 1] = apnd - (double)k;
      }

      if (nm1d2 << 1 == n - 1) {
        y->data[nm1d2] = (anew + apnd) / 2.0;
      } else {
        y->data[nm1d2] = anew + (double)nm1d2;
        y->data[nm1d2 + 1] = apnd - (double)nm1d2;
      }
    }
  }

  emxInit_real_T(&mod_func_lin, 2);
  MD_modulating_func(y, h_lin, N_lin, M_lin, mod_func_lin);
  if (2 > mod_func_lin->size[1]) {
    i0 = 0;
    n = 0;
  } else {
    i0 = 1;
    n = mod_func_lin->size[1];
  }

  emxInit_real_T(&b_mod_func_lin, 2);
  k = b_mod_func_lin->size[0] * b_mod_func_lin->size[1];
  b_mod_func_lin->size[0] = 1;
  b_mod_func_lin->size[1] = n - i0;
  emxEnsureCapacity((emxArray__common *)b_mod_func_lin, k, (int)sizeof(double));
  loop_ub = n - i0;
  for (n = 0; n < loop_ub; n++) {
    b_mod_func_lin->data[b_mod_func_lin->size[0] * n] = mod_func_lin->data[i0 +
      n];
  }

  i0 = mod_func_lin->size[0] * mod_func_lin->size[1];
  mod_func_lin->size[0] = 1;
  mod_func_lin->size[1] = b_mod_func_lin->size[1];
  emxEnsureCapacity((emxArray__common *)mod_func_lin, i0, (int)sizeof(double));
  loop_ub = b_mod_func_lin->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    mod_func_lin->data[mod_func_lin->size[0] * i0] = b_mod_func_lin->
      data[b_mod_func_lin->size[0] * i0];
  }

  emxFree_real_T(&b_mod_func_lin);
  nm1d2 = 1;
  n = mod_func_lin->size[1];
  mtmp = mod_func_lin->data[0];
  if (mod_func_lin->size[1] > 1) {
    if (rtIsNaN(mod_func_lin->data[0])) {
      k = 2;
      exitg2 = false;
      while ((!exitg2) && (k <= n)) {
        nm1d2 = k;
        if (!rtIsNaN(mod_func_lin->data[k - 1])) {
          mtmp = mod_func_lin->data[k - 1];
          exitg2 = true;
        } else {
          k++;
        }
      }
    }

    if (nm1d2 < mod_func_lin->size[1]) {
      while (nm1d2 + 1 <= n) {
        if (mod_func_lin->data[nm1d2] > mtmp) {
          mtmp = mod_func_lin->data[nm1d2];
        }

        nm1d2++;
      }
    }
  }

  i0 = mod_func_lin->size[0] * mod_func_lin->size[1];
  mod_func_lin->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)mod_func_lin, i0, (int)sizeof(double));
  nm1d2 = mod_func_lin->size[0];
  k = mod_func_lin->size[1];
  loop_ub = nm1d2 * k;
  for (i0 = 0; i0 < loop_ub; i0++) {
    mod_func_lin->data[i0] /= mtmp;
  }

  emxInit_real_T(&mod_func_d_lin, 2);
  i0 = mod_func_d_lin->size[0] * mod_func_d_lin->size[1];
  mod_func_d_lin->size[0] = (int)(m - 1.0);
  mod_func_d_lin->size[1] = (int)(h_lin + 1.0);
  emxEnsureCapacity((emxArray__common *)mod_func_d_lin, i0, (int)sizeof(double));
  loop_ub = (int)(m - 1.0) * (int)(h_lin + 1.0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    mod_func_d_lin->data[i0] = 0.0;
  }

  i = 0;
  emxInit_real_T(&b, 2);
  while (i <= (int)(m - 1.0) - 1) {
    b_y = 1.0 / mtmp;
    if (rtIsNaN(h_lin)) {
      n = 1;
      anew = rtNaN;
      apnd = h_lin;
    } else if (h_lin < 0.0) {
      n = 0;
      anew = 0.0;
      apnd = h_lin;
    } else if (rtIsInf(h_lin)) {
      n = 1;
      anew = rtNaN;
      apnd = h_lin;
    } else {
      anew = 0.0;
      ndbl = floor(h_lin + 0.5);
      apnd = ndbl;
      cdiff = ndbl - h_lin;
      if (fabs(cdiff) < 4.4408920985006262E-16 * h_lin) {
        ndbl++;
        apnd = h_lin;
      } else if (cdiff > 0.0) {
        apnd = ndbl - 1.0;
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl;
      } else {
        n = 0;
      }
    }

    i0 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = n;
    emxEnsureCapacity((emxArray__common *)y, i0, (int)sizeof(double));
    if (n > 0) {
      y->data[0] = anew;
      if (n > 1) {
        y->data[n - 1] = apnd;
        i0 = n - 1;
        nm1d2 = i0 / 2;
        for (k = 1; k < nm1d2; k++) {
          y->data[k] = anew + (double)k;
          y->data[(n - k) - 1] = apnd - (double)k;
        }

        if (nm1d2 << 1 == n - 1) {
          y->data[nm1d2] = (anew + apnd) / 2.0;
        } else {
          y->data[nm1d2] = anew + (double)nm1d2;
          y->data[nm1d2 + 1] = apnd - (double)nm1d2;
        }
      }
    }

    MD_modulating_func_d(1.0 + (double)i, y, h_lin, N_lin, M_lin, b);
    loop_ub = b->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      mod_func_d_lin->data[i + mod_func_d_lin->size[0] * i0] = b_y * b->data
        [b->size[0] * i0];
    }

    i++;
  }

  emxFree_real_T(&b);
  if (2 > mod_func_d_lin->size[1]) {
    i0 = 0;
    n = 0;
  } else {
    i0 = 1;
    n = mod_func_d_lin->size[1];
  }

  emxInit_real_T(&b_mod_func_d_lin, 2);
  nm1d2 = mod_func_d_lin->size[0];
  k = b_mod_func_d_lin->size[0] * b_mod_func_d_lin->size[1];
  b_mod_func_d_lin->size[0] = nm1d2;
  b_mod_func_d_lin->size[1] = n - i0;
  emxEnsureCapacity((emxArray__common *)b_mod_func_d_lin, k, (int)sizeof(double));
  loop_ub = n - i0;
  for (n = 0; n < loop_ub; n++) {
    for (k = 0; k < nm1d2; k++) {
      b_mod_func_d_lin->data[k + b_mod_func_d_lin->size[0] * n] =
        mod_func_d_lin->data[k + mod_func_d_lin->size[0] * (i0 + n)];
    }
  }

  i0 = mod_func_d_lin->size[0] * mod_func_d_lin->size[1];
  mod_func_d_lin->size[0] = b_mod_func_d_lin->size[0];
  mod_func_d_lin->size[1] = b_mod_func_d_lin->size[1];
  emxEnsureCapacity((emxArray__common *)mod_func_d_lin, i0, (int)sizeof(double));
  loop_ub = b_mod_func_d_lin->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    nm1d2 = b_mod_func_d_lin->size[0];
    for (n = 0; n < nm1d2; n++) {
      mod_func_d_lin->data[n + mod_func_d_lin->size[0] * i0] =
        b_mod_func_d_lin->data[n + b_mod_func_d_lin->size[0] * i0];
    }
  }

  emxFree_real_T(&b_mod_func_d_lin);
  emxInit_real_T1(&s, 1);

  /* current_out=obj.signals_intervals(obj.current_interval).original_signals(end-2,1:end); */
  cnt1 = 1;
  cnt2 = 1U;
  i0 = s->size[0];
  s->size[0] = (int)m;
  emxEnsureCapacity((emxArray__common *)s, i0, (int)sizeof(double));
  loop_ub = (int)m;
  for (i0 = 0; i0 < loop_ub; i0++) {
    s->data[i0] = 0.0;
  }

  emxInit_real_T(&y_dot_lin, 2);
  i0 = y_dot_lin->size[0] * y_dot_lin->size[1];
  y_dot_lin->size[0] = (int)m;
  y_dot_lin->size[1] = current_out->size[0];
  emxEnsureCapacity((emxArray__common *)y_dot_lin, i0, (int)sizeof(double));
  loop_ub = (int)m * current_out->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    y_dot_lin->data[i0] = 0.0;
  }

  /*  zmiana 30.11.2020 */
  /* obj.signals_intervals(obj.current_interval).op_interval_possible=false; */
  emxInit_real_T1(&current_out_lin, 1);
  emxInit_real_T1(&con, 1);
  emxInit_real_T(&b_y_dot_lin, 2);
  emxInit_real_T(&c_y_dot_lin, 2);
  emxInit_real_T(&c_mod_func_d_lin, 2);
  do {
    exitg1 = 0;
    if (cnt1 < current_out->size[0]) {
      cnt1++;
      if (cnt1 > h_lin) {
        cnt2++;
        anew = (double)cnt1 - h_lin;
        if (anew > cnt1) {
          i0 = 0;
          n = 0;
        } else {
          i0 = (int)anew - 1;
          n = cnt1;
        }

        k = current_out_lin->size[0];
        current_out_lin->size[0] = n - i0;
        emxEnsureCapacity((emxArray__common *)current_out_lin, k, (int)sizeof
                          (double));
        loop_ub = n - i0;
        for (n = 0; n < loop_ub; n++) {
          current_out_lin->data[n] = current_out->data[i0 + n];
        }

        for (i = 0; i < (int)m; i++) {
          if (1.0 + (double)i == 1.0) {
            conv(current_out_lin, mod_func_lin, con);
            i0 = (int)floor((double)con->size[0] / 2.0);
            if (1 > i0) {
              i0 = 0;
            }

            n = con->size[0];
            con->size[0] = i0;
            emxEnsureCapacity((emxArray__common *)con, n, (int)sizeof(double));
            s->data[0] = con->data[i0 - 1];
          } else {
            loop_ub = mod_func_d_lin->size[1];
            i0 = c_mod_func_d_lin->size[0] * c_mod_func_d_lin->size[1];
            c_mod_func_d_lin->size[0] = 1;
            c_mod_func_d_lin->size[1] = loop_ub;
            emxEnsureCapacity((emxArray__common *)c_mod_func_d_lin, i0, (int)
                              sizeof(double));
            for (i0 = 0; i0 < loop_ub; i0++) {
              c_mod_func_d_lin->data[c_mod_func_d_lin->size[0] * i0] =
                mod_func_d_lin->data[((int)((1.0 + (double)i) - 1.0) +
                mod_func_d_lin->size[0] * i0) - 1];
            }

            conv(current_out_lin, c_mod_func_d_lin, con);
            i0 = (int)floor((double)con->size[0] / 2.0);
            if (1 > i0) {
              i0 = 0;
            }

            n = con->size[0];
            con->size[0] = i0;
            emxEnsureCapacity((emxArray__common *)con, n, (int)sizeof(double));
            s->data[i] = con->data[i0 - 1];
          }
        }

        /* y_dot_lin=[y_dot_lin s]; */
        loop_ub = s->size[0];
        for (i0 = 0; i0 < loop_ub; i0++) {
          y_dot_lin->data[i0 + y_dot_lin->size[0] * ((int)cnt2 - 1)] = s->
            data[i0];
        }

        if (cnt2 > mean_interval) {
          anew = (double)cnt2 - mean_interval;
          if (anew > cnt2) {
            i0 = 0;
            n = 0;
          } else {
            i0 = (int)anew - 1;
            n = (int)cnt2;
          }

          k = c_y_dot_lin->size[0] * c_y_dot_lin->size[1];
          c_y_dot_lin->size[0] = 1;
          c_y_dot_lin->size[1] = n - i0;
          emxEnsureCapacity((emxArray__common *)c_y_dot_lin, k, (int)sizeof
                            (double));
          loop_ub = n - i0;
          for (n = 0; n < loop_ub; n++) {
            c_y_dot_lin->data[c_y_dot_lin->size[0] * n] = y_dot_lin->data[1 +
              y_dot_lin->size[0] * (i0 + n)];
          }

          b_abs(c_y_dot_lin, y);
          if (mean(y) < threshold) {
            anew = (double)cnt2 - mean_interval;
            if (anew > cnt2) {
              i0 = 0;
              n = 0;
            } else {
              i0 = (int)anew - 1;
              n = (int)cnt2;
            }

            k = b_y_dot_lin->size[0] * b_y_dot_lin->size[1];
            b_y_dot_lin->size[0] = 1;
            b_y_dot_lin->size[1] = n - i0;
            emxEnsureCapacity((emxArray__common *)b_y_dot_lin, k, (int)sizeof
                              (double));
            loop_ub = n - i0;
            for (n = 0; n < loop_ub; n++) {
              b_y_dot_lin->data[b_y_dot_lin->size[0] * n] = y_dot_lin->data[2 +
                y_dot_lin->size[0] * (i0 + n)];
            }

            b_abs(b_y_dot_lin, y);
            if (mean(y) < threshold) {
              /* &&... */
              /* (mean(abs(y_dot_lin(4,end-mean_interval:end)))<threshold) %&&... */
              /* (mean(abs(y_dot_lin(5,end-mean_interval:end)))<threshold); */
              *op_interval_possible = true;
              *op_time = start_int_time + ((double)cnt1 - floor(mean_interval /
                2.0));
              exitg1 = 1;
            }
          }
        }
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  emxFree_real_T(&c_mod_func_d_lin);
  emxFree_real_T(&c_y_dot_lin);
  emxFree_real_T(&b_y_dot_lin);
  emxFree_real_T(&y);
  emxFree_real_T(&con);
  emxFree_real_T(&current_out_lin);
  emxFree_real_T(&y_dot_lin);
  emxFree_real_T(&s);
  emxFree_real_T(&mod_func_d_lin);
  emxFree_real_T(&mod_func_lin);
}

/*
 * File trailer for FHZN_find_operating_point.c
 *
 * [EOF]
 */
