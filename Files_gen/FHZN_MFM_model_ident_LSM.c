/*
 * File: FHZN_MFM_model_ident_LSM.c
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
#include "FHZN_MFM_model_ident_LSM.h"
#include "MD_modulating_func_d.h"
#include "FHZN_define_model_del_emxutil.h"
#include "conv.h"
#include "mldivide.h"
#include "MD_modulating_func.h"

/* Function Definitions */

/*
 * funkcja modulujaca identyfikacja
 * Arguments    : double inputs_nr
 *                const emxArray_real_T *u
 *                const emxArray_real_T *pv
 *                double h
 *                double n
 *                double m
 *                double N
 *                double M
 *                emxArray_real_T *ni_min
 * Return Type  : void
 */
void FHZN_MFM_model_ident_LSM(double inputs_nr, const emxArray_real_T *u, const
  emxArray_real_T *pv, double h, double n, double m, double N, double M,
  emxArray_real_T *ni_min)
{
  int br;
  double anew;
  double apnd;
  double ndbl;
  double cdiff;
  emxArray_real_T *current_out;
  int i5;
  int nm1d2;
  int k;
  emxArray_real_T *mod_func;
  int i6;
  emxArray_real_T *b_mod_func;
  int ar;
  int ib;
  double mtmp;
  int ix;
  boolean_T exitg1;
  double b_k;
  emxArray_real_T *mod_func_d;
  emxArray_real_T *current_u;
  emxArray_real_T *st;
  emxArray_real_T *s;
  emxArray_real_T *y_dot;
  emxArray_real_T *u_dot;
  emxArray_real_T *X;
  int i;
  emxArray_real_T *con;
  double y;
  emxArray_real_T *b_mod_func_d;
  int cnt;
  emxArray_int32_T *r5;
  emxArray_real_T *c_mod_func_d;
  emxArray_real_T *b_current_u;
  emxArray_real_T *d_mod_func_d;
  emxArray_real_T *c_current_u;
  emxArray_real_T *b_s;
  emxArray_real_T *b_st;
  int j;
  emxArray_real_T *b_X;
  emxArray_real_T *b_y;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  int b_m;
  int ic;
  int ia;
  emxArray_real_T *c_X;
  emxArray_real_T *b_ni_min;
  if (rtIsNaN(h)) {
    br = 1;
    anew = rtNaN;
    apnd = h;
  } else if (h < 0.0) {
    br = 0;
    anew = 0.0;
    apnd = h;
  } else if (rtIsInf(h)) {
    br = 1;
    anew = rtNaN;
    apnd = h;
  } else {
    anew = 0.0;
    ndbl = floor(h + 0.5);
    apnd = ndbl;
    cdiff = ndbl - h;
    if (fabs(cdiff) < 4.4408920985006262E-16 * h) {
      ndbl++;
      apnd = h;
    } else if (cdiff > 0.0) {
      apnd = ndbl - 1.0;
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      br = (int)ndbl;
    } else {
      br = 0;
    }
  }

  emxInit_real_T(&current_out, 2);
  i5 = current_out->size[0] * current_out->size[1];
  current_out->size[0] = 1;
  current_out->size[1] = br;
  emxEnsureCapacity((emxArray__common *)current_out, i5, (int)sizeof(double));
  if (br > 0) {
    current_out->data[0] = anew;
    if (br > 1) {
      current_out->data[br - 1] = apnd;
      i5 = br - 1;
      nm1d2 = i5 / 2;
      for (k = 1; k < nm1d2; k++) {
        current_out->data[k] = anew + (double)k;
        current_out->data[(br - k) - 1] = apnd - (double)k;
      }

      if (nm1d2 << 1 == br - 1) {
        current_out->data[nm1d2] = (anew + apnd) / 2.0;
      } else {
        current_out->data[nm1d2] = anew + (double)nm1d2;
        current_out->data[nm1d2 + 1] = apnd - (double)nm1d2;
      }
    }
  }

  emxInit_real_T(&mod_func, 2);
  MD_modulating_func(current_out, h, N, M, mod_func);
  if (2 > mod_func->size[1]) {
    i5 = 0;
    i6 = 0;
  } else {
    i5 = 1;
    i6 = mod_func->size[1];
  }

  emxInit_real_T(&b_mod_func, 2);
  ar = b_mod_func->size[0] * b_mod_func->size[1];
  b_mod_func->size[0] = 1;
  b_mod_func->size[1] = i6 - i5;
  emxEnsureCapacity((emxArray__common *)b_mod_func, ar, (int)sizeof(double));
  ib = i6 - i5;
  for (i6 = 0; i6 < ib; i6++) {
    b_mod_func->data[b_mod_func->size[0] * i6] = mod_func->data[i5 + i6];
  }

  i5 = mod_func->size[0] * mod_func->size[1];
  mod_func->size[0] = 1;
  mod_func->size[1] = b_mod_func->size[1];
  emxEnsureCapacity((emxArray__common *)mod_func, i5, (int)sizeof(double));
  ib = b_mod_func->size[1];
  for (i5 = 0; i5 < ib; i5++) {
    mod_func->data[mod_func->size[0] * i5] = b_mod_func->data[b_mod_func->size[0]
      * i5];
  }

  emxFree_real_T(&b_mod_func);
  nm1d2 = 1;
  br = mod_func->size[1];
  mtmp = mod_func->data[0];
  if (mod_func->size[1] > 1) {
    if (rtIsNaN(mod_func->data[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= br)) {
        nm1d2 = ix;
        if (!rtIsNaN(mod_func->data[ix - 1])) {
          mtmp = mod_func->data[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (nm1d2 < mod_func->size[1]) {
      while (nm1d2 + 1 <= br) {
        if (mod_func->data[nm1d2] > mtmp) {
          mtmp = mod_func->data[nm1d2];
        }

        nm1d2++;
      }
    }
  }

  i5 = mod_func->size[0] * mod_func->size[1];
  mod_func->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)mod_func, i5, (int)sizeof(double));
  nm1d2 = mod_func->size[0];
  ix = mod_func->size[1];
  ib = nm1d2 * ix;
  for (i5 = 0; i5 < ib; i5++) {
    mod_func->data[i5] /= mtmp;
  }

  if ((n >= m) || rtIsNaN(m)) {
    b_k = n;
  } else {
    b_k = m;
  }

  emxInit_real_T(&mod_func_d, 2);
  i5 = mod_func_d->size[0] * mod_func_d->size[1];
  mod_func_d->size[0] = (int)(b_k - 1.0);
  mod_func_d->size[1] = (int)(h + 1.0);
  emxEnsureCapacity((emxArray__common *)mod_func_d, i5, (int)sizeof(double));
  ib = (int)(b_k - 1.0) * (int)(h + 1.0);
  for (i5 = 0; i5 < ib; i5++) {
    mod_func_d->data[i5] = 0.0;
  }

  emxInit_real_T(&current_u, 2);
  i5 = current_u->size[0] * current_u->size[1];
  current_u->size[0] = (int)inputs_nr;
  current_u->size[1] = (int)(h + 1.0);
  emxEnsureCapacity((emxArray__common *)current_u, i5, (int)sizeof(double));
  ib = (int)inputs_nr * (int)(h + 1.0);
  for (i5 = 0; i5 < ib; i5++) {
    current_u->data[i5] = 0.0;
  }

  emxInit_real_T1(&st, 1);
  i5 = st->size[0];
  st->size[0] = (int)n;
  emxEnsureCapacity((emxArray__common *)st, i5, (int)sizeof(double));
  ib = (int)n;
  for (i5 = 0; i5 < ib; i5++) {
    st->data[i5] = 0.0;
  }

  emxInit_real_T1(&s, 1);
  i5 = s->size[0];
  s->size[0] = (int)m;
  emxEnsureCapacity((emxArray__common *)s, i5, (int)sizeof(double));
  ib = (int)m;
  for (i5 = 0; i5 < ib; i5++) {
    s->data[i5] = 0.0;
  }

  emxInit_real_T(&y_dot, 2);
  i5 = y_dot->size[0] * y_dot->size[1];
  y_dot->size[0] = (int)m;
  y_dot->size[1] = (int)((double)pv->size[1] - h);
  emxEnsureCapacity((emxArray__common *)y_dot, i5, (int)sizeof(double));
  ib = (int)m * (int)((double)pv->size[1] - h);
  for (i5 = 0; i5 < ib; i5++) {
    y_dot->data[i5] = 0.0;
  }

  emxInit_real_T(&u_dot, 2);
  i5 = u_dot->size[0] * u_dot->size[1];
  u_dot->size[0] = (int)(inputs_nr * n);
  u_dot->size[1] = (int)((double)pv->size[1] - h);
  emxEnsureCapacity((emxArray__common *)u_dot, i5, (int)sizeof(double));
  ib = (int)(inputs_nr * n) * (int)((double)pv->size[1] - h);
  for (i5 = 0; i5 < ib; i5++) {
    u_dot->data[i5] = 0.0;
  }

  emxInit_real_T(&X, 2);
  i5 = X->size[0] * X->size[1];
  X->size[0] = (int)((m - 1.0) + inputs_nr * n);
  X->size[1] = (int)((double)pv->size[1] - h);
  emxEnsureCapacity((emxArray__common *)X, i5, (int)sizeof(double));
  ib = (int)((m - 1.0) + inputs_nr * n) * (int)((double)pv->size[1] - h);
  for (i5 = 0; i5 < ib; i5++) {
    X->data[i5] = 0.0;
  }

  i = 0;
  emxInit_real_T(&con, 2);
  while (i <= (int)(b_k - 1.0) - 1) {
    y = 1.0 / mtmp;
    if (rtIsNaN(h)) {
      br = 1;
      anew = rtNaN;
      apnd = h;
    } else if (h < 0.0) {
      br = 0;
      anew = 0.0;
      apnd = h;
    } else if (rtIsInf(h)) {
      br = 1;
      anew = rtNaN;
      apnd = h;
    } else {
      anew = 0.0;
      ndbl = floor(h + 0.5);
      apnd = ndbl;
      cdiff = ndbl - h;
      if (fabs(cdiff) < 4.4408920985006262E-16 * h) {
        ndbl++;
        apnd = h;
      } else if (cdiff > 0.0) {
        apnd = ndbl - 1.0;
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        br = (int)ndbl;
      } else {
        br = 0;
      }
    }

    i5 = current_out->size[0] * current_out->size[1];
    current_out->size[0] = 1;
    current_out->size[1] = br;
    emxEnsureCapacity((emxArray__common *)current_out, i5, (int)sizeof(double));
    if (br > 0) {
      current_out->data[0] = anew;
      if (br > 1) {
        current_out->data[br - 1] = apnd;
        i5 = br - 1;
        nm1d2 = i5 / 2;
        for (k = 1; k < nm1d2; k++) {
          current_out->data[k] = anew + (double)k;
          current_out->data[(br - k) - 1] = apnd - (double)k;
        }

        if (nm1d2 << 1 == br - 1) {
          current_out->data[nm1d2] = (anew + apnd) / 2.0;
        } else {
          current_out->data[nm1d2] = anew + (double)nm1d2;
          current_out->data[nm1d2 + 1] = apnd - (double)nm1d2;
        }
      }
    }

    MD_modulating_func_d(1.0 + (double)i, current_out, h, N, M, con);
    ib = con->size[1];
    for (i5 = 0; i5 < ib; i5++) {
      mod_func_d->data[i + mod_func_d->size[0] * i5] = y * con->data[con->size[0]
        * i5];
    }

    i++;
  }

  if (2 > mod_func_d->size[1]) {
    i5 = 0;
    i6 = 0;
  } else {
    i5 = 1;
    i6 = mod_func_d->size[1];
  }

  emxInit_real_T(&b_mod_func_d, 2);
  ix = mod_func_d->size[0];
  ar = b_mod_func_d->size[0] * b_mod_func_d->size[1];
  b_mod_func_d->size[0] = ix;
  b_mod_func_d->size[1] = i6 - i5;
  emxEnsureCapacity((emxArray__common *)b_mod_func_d, ar, (int)sizeof(double));
  ib = i6 - i5;
  for (i6 = 0; i6 < ib; i6++) {
    for (ar = 0; ar < ix; ar++) {
      b_mod_func_d->data[ar + b_mod_func_d->size[0] * i6] = mod_func_d->data[ar
        + mod_func_d->size[0] * (i5 + i6)];
    }
  }

  i5 = mod_func_d->size[0] * mod_func_d->size[1];
  mod_func_d->size[0] = b_mod_func_d->size[0];
  mod_func_d->size[1] = b_mod_func_d->size[1];
  emxEnsureCapacity((emxArray__common *)mod_func_d, i5, (int)sizeof(double));
  ib = b_mod_func_d->size[1];
  for (i5 = 0; i5 < ib; i5++) {
    nm1d2 = b_mod_func_d->size[0];
    for (i6 = 0; i6 < nm1d2; i6++) {
      mod_func_d->data[i6 + mod_func_d->size[0] * i5] = b_mod_func_d->data[i6 +
        b_mod_func_d->size[0] * i5];
    }
  }

  emxFree_real_T(&b_mod_func_d);
  if ((u->size[0] == 0) || (u->size[1] == 0)) {
    br = 0;
  } else {
    nm1d2 = u->size[0];
    br = u->size[1];
    if (nm1d2 >= br) {
      br = nm1d2;
    }
  }

  cnt = 0;
  emxInit_int32_T1(&r5, 1);
  emxInit_real_T(&c_mod_func_d, 2);
  emxInit_real_T(&b_current_u, 2);
  emxInit_real_T(&d_mod_func_d, 2);
  emxInit_real_T(&c_current_u, 2);
  emxInit_real_T(&b_s, 2);
  emxInit_real_T(&b_st, 2);
  while (cnt <= br - 1) {
    if (1.0 + (double)cnt > h) {
      anew = (1.0 + (double)cnt) - h;
      if (anew > 1.0 + (double)cnt) {
        i5 = 0;
        i6 = 0;
      } else {
        i5 = (int)anew - 1;
        i6 = cnt + 1;
      }

      ar = current_out->size[0] * current_out->size[1];
      current_out->size[0] = 1;
      current_out->size[1] = i6 - i5;
      emxEnsureCapacity((emxArray__common *)current_out, ar, (int)sizeof(double));
      ib = i6 - i5;
      for (i6 = 0; i6 < ib; i6++) {
        current_out->data[current_out->size[0] * i6] = pv->data[i5 + i6];
      }

      for (i = 0; i < (int)inputs_nr; i++) {
        anew = (1.0 + (double)cnt) - h;
        if (anew > 1.0 + (double)cnt) {
          i5 = 1;
          i6 = 0;
        } else {
          i5 = (int)anew;
          i6 = cnt + 1;
        }

        ib = i6 - i5;
        for (i6 = 0; i6 <= ib; i6++) {
          current_u->data[i + current_u->size[0] * i6] = u->data[i + u->size[0] *
            ((i5 + i6) - 1)];
        }
      }

      /* IDENTYFIKACJA DLA DLUGIEGO OKNA */
      /* Wyjscie i jego pochodne */
      for (i = 0; i < (int)m; i++) {
        if (1.0 + (double)i == 1.0) {
          b_conv(current_out, mod_func, con);
          i5 = (int)floor((double)con->size[1] / 2.0);
          if (1 > i5) {
            i5 = 0;
          }

          i6 = con->size[0] * con->size[1];
          con->size[1] = i5;
          emxEnsureCapacity((emxArray__common *)con, i6, (int)sizeof(double));
          s->data[0] = con->data[i5 - 1];
        } else {
          ib = mod_func_d->size[1];
          i5 = c_mod_func_d->size[0] * c_mod_func_d->size[1];
          c_mod_func_d->size[0] = 1;
          c_mod_func_d->size[1] = ib;
          emxEnsureCapacity((emxArray__common *)c_mod_func_d, i5, (int)sizeof
                            (double));
          for (i5 = 0; i5 < ib; i5++) {
            c_mod_func_d->data[c_mod_func_d->size[0] * i5] = mod_func_d->data
              [((int)((1.0 + (double)i) - 1.0) + mod_func_d->size[0] * i5) - 1];
          }

          b_conv(current_out, c_mod_func_d, con);
          i5 = (int)floor((double)con->size[1] / 2.0);
          if (1 > i5) {
            i5 = 0;
          }

          i6 = con->size[0] * con->size[1];
          con->size[1] = i5;
          emxEnsureCapacity((emxArray__common *)con, i6, (int)sizeof(double));
          s->data[i] = con->data[i5 - 1];
        }
      }

      ib = y_dot->size[0];
      i5 = r5->size[0];
      r5->size[0] = ib;
      emxEnsureCapacity((emxArray__common *)r5, i5, (int)sizeof(int));
      for (i5 = 0; i5 < ib; i5++) {
        r5->data[i5] = i5;
      }

      i5 = (int)((1.0 + (double)cnt) - h) - 1;
      i6 = b_s->size[0] * b_s->size[1];
      b_s->size[0] = 1;
      b_s->size[1] = s->size[0];
      emxEnsureCapacity((emxArray__common *)b_s, i6, (int)sizeof(double));
      ib = s->size[0];
      for (i6 = 0; i6 < ib; i6++) {
        b_s->data[b_s->size[0] * i6] = s->data[i6];
      }

      ix = r5->size[0];
      for (i6 = 0; i6 < ix; i6++) {
        y_dot->data[r5->data[i6] + y_dot->size[0] * i5] = b_s->data[i6];
      }

      /* Sterowanie i opoznienia */
      for (i = 0; i < (int)inputs_nr; i++) {
        for (j = 0; j < (int)n; j++) {
          if (1.0 + (double)j == 1.0) {
            ib = current_u->size[1];
            i5 = c_current_u->size[0] * c_current_u->size[1];
            c_current_u->size[0] = 1;
            c_current_u->size[1] = ib;
            emxEnsureCapacity((emxArray__common *)c_current_u, i5, (int)sizeof
                              (double));
            for (i5 = 0; i5 < ib; i5++) {
              c_current_u->data[c_current_u->size[0] * i5] = current_u->data[i +
                current_u->size[0] * i5];
            }

            b_conv(c_current_u, mod_func, con);
            i5 = (int)floor((double)con->size[1] / 2.0);
            if (1 > i5) {
              i5 = 0;
            }

            i6 = con->size[0] * con->size[1];
            con->size[1] = i5;
            emxEnsureCapacity((emxArray__common *)con, i6, (int)sizeof(double));
            st->data[0] = con->data[i5 - 1];
          } else {
            ib = current_u->size[1];
            i5 = b_current_u->size[0] * b_current_u->size[1];
            b_current_u->size[0] = 1;
            b_current_u->size[1] = ib;
            emxEnsureCapacity((emxArray__common *)b_current_u, i5, (int)sizeof
                              (double));
            for (i5 = 0; i5 < ib; i5++) {
              b_current_u->data[b_current_u->size[0] * i5] = current_u->data[i +
                current_u->size[0] * i5];
            }

            ib = mod_func_d->size[1];
            i5 = d_mod_func_d->size[0] * d_mod_func_d->size[1];
            d_mod_func_d->size[0] = 1;
            d_mod_func_d->size[1] = ib;
            emxEnsureCapacity((emxArray__common *)d_mod_func_d, i5, (int)sizeof
                              (double));
            for (i5 = 0; i5 < ib; i5++) {
              d_mod_func_d->data[d_mod_func_d->size[0] * i5] = mod_func_d->data
                [((int)((1.0 + (double)j) - 1.0) + mod_func_d->size[0] * i5) - 1];
            }

            b_conv(b_current_u, d_mod_func_d, con);
            i5 = (int)floor((double)con->size[1] / 2.0);
            if (1 > i5) {
              i5 = 0;
            }

            i6 = con->size[0] * con->size[1];
            con->size[1] = i5;
            emxEnsureCapacity((emxArray__common *)con, i6, (int)sizeof(double));
            st->data[j] = con->data[i5 - 1];
          }
        }

        anew = ((1.0 + (double)i) - 1.0) * n + 1.0;
        ndbl = (1.0 + (double)i) * n;
        if (anew > ndbl) {
          i5 = 0;
          i6 = 0;
        } else {
          i5 = (int)anew - 1;
          i6 = (int)ndbl;
        }

        ar = r5->size[0];
        r5->size[0] = i6 - i5;
        emxEnsureCapacity((emxArray__common *)r5, ar, (int)sizeof(int));
        ib = i6 - i5;
        for (i6 = 0; i6 < ib; i6++) {
          r5->data[i6] = i5 + i6;
        }

        i5 = (int)((1.0 + (double)cnt) - h) - 1;
        i6 = b_st->size[0] * b_st->size[1];
        b_st->size[0] = 1;
        b_st->size[1] = st->size[0];
        emxEnsureCapacity((emxArray__common *)b_st, i6, (int)sizeof(double));
        ib = st->size[0];
        for (i6 = 0; i6 < ib; i6++) {
          b_st->data[b_st->size[0] * i6] = st->data[i6];
        }

        ix = r5->size[0];
        for (i6 = 0; i6 < ix; i6++) {
          u_dot->data[r5->data[i6] + u_dot->size[0] * i5] = b_st->data[i6];
        }
      }
    }

    cnt++;
  }

  emxFree_real_T(&b_st);
  emxFree_real_T(&b_s);
  emxFree_real_T(&c_current_u);
  emxFree_real_T(&d_mod_func_d);
  emxFree_real_T(&b_current_u);
  emxFree_real_T(&c_mod_func_d);
  emxFree_int32_T(&r5);
  emxFree_real_T(&con);
  emxFree_real_T(&s);
  emxFree_real_T(&current_u);
  emxFree_real_T(&mod_func);
  for (i = 0; i < (int)(m - 1.0); i++) {
    ib = y_dot->size[1] - 1;
    for (i5 = 0; i5 <= ib; i5++) {
      X->data[i + X->size[0] * i5] = y_dot->data[i + y_dot->size[0] * i5];
    }
  }

  b_k = 1.0;
  for (i = 0; i < (int)inputs_nr; i++) {
    for (j = 0; j < (int)n; j++) {
      i5 = (int)((b_k + m) - 1.0) - 1;
      ib = u_dot->size[1];
      i6 = (int)(((1.0 + (double)i) - 1.0) * n + (1.0 + (double)j));
      ar = current_out->size[0] * current_out->size[1];
      current_out->size[0] = 1;
      current_out->size[1] = ib;
      emxEnsureCapacity((emxArray__common *)current_out, ar, (int)sizeof(double));
      for (ar = 0; ar < ib; ar++) {
        current_out->data[current_out->size[0] * ar] = u_dot->data[(i6 +
          u_dot->size[0] * ar) - 1];
      }

      ib = current_out->size[1];
      for (i6 = 0; i6 < ib; i6++) {
        X->data[i5 + X->size[0] * i6] = current_out->data[current_out->size[0] *
          i6];
      }

      b_k++;
    }
  }

  emxFree_real_T(&current_out);
  emxFree_real_T(&u_dot);
  emxInit_real_T(&b_X, 2);
  i5 = b_X->size[0] * b_X->size[1];
  b_X->size[0] = X->size[1];
  b_X->size[1] = X->size[0];
  emxEnsureCapacity((emxArray__common *)b_X, i5, (int)sizeof(double));
  ib = X->size[0];
  for (i5 = 0; i5 < ib; i5++) {
    nm1d2 = X->size[1];
    for (i6 = 0; i6 < nm1d2; i6++) {
      b_X->data[i6 + b_X->size[0] * i5] = X->data[i5 + X->size[0] * i6];
    }
  }

  i5 = X->size[0] * X->size[1];
  X->size[0] = b_X->size[0];
  X->size[1] = b_X->size[1];
  emxEnsureCapacity((emxArray__common *)X, i5, (int)sizeof(double));
  ib = b_X->size[1];
  for (i5 = 0; i5 < ib; i5++) {
    nm1d2 = b_X->size[0];
    for (i6 = 0; i6 < nm1d2; i6++) {
      X->data[i6 + X->size[0] * i5] = b_X->data[i6 + b_X->size[0] * i5];
    }
  }

  emxFree_real_T(&b_X);
  ib = y_dot->size[1];
  nm1d2 = y_dot->size[0];
  i5 = st->size[0];
  st->size[0] = ib;
  emxEnsureCapacity((emxArray__common *)st, i5, (int)sizeof(double));
  for (i5 = 0; i5 < ib; i5++) {
    st->data[i5] = y_dot->data[(nm1d2 + y_dot->size[0] * i5) - 1];
  }

  emxFree_real_T(&y_dot);
  i5 = mod_func_d->size[0] * mod_func_d->size[1];
  mod_func_d->size[0] = X->size[1];
  mod_func_d->size[1] = X->size[0];
  emxEnsureCapacity((emxArray__common *)mod_func_d, i5, (int)sizeof(double));
  ib = X->size[0];
  for (i5 = 0; i5 < ib; i5++) {
    nm1d2 = X->size[1];
    for (i6 = 0; i6 < nm1d2; i6++) {
      mod_func_d->data[i6 + mod_func_d->size[0] * i5] = X->data[i5 + X->size[0] *
        i6];
    }
  }

  emxInit_real_T(&b_y, 2);
  if ((mod_func_d->size[1] == 1) || (X->size[0] == 1)) {
    i5 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = mod_func_d->size[0];
    b_y->size[1] = X->size[1];
    emxEnsureCapacity((emxArray__common *)b_y, i5, (int)sizeof(double));
    ib = mod_func_d->size[0];
    for (i5 = 0; i5 < ib; i5++) {
      nm1d2 = X->size[1];
      for (i6 = 0; i6 < nm1d2; i6++) {
        b_y->data[i5 + b_y->size[0] * i6] = 0.0;
        ix = mod_func_d->size[1];
        for (ar = 0; ar < ix; ar++) {
          b_y->data[i5 + b_y->size[0] * i6] += mod_func_d->data[i5 +
            mod_func_d->size[0] * ar] * X->data[ar + X->size[0] * i6];
        }
      }
    }
  } else {
    k = mod_func_d->size[1];
    unnamed_idx_0 = (unsigned int)mod_func_d->size[0];
    unnamed_idx_1 = (unsigned int)X->size[1];
    i5 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = (int)unnamed_idx_0;
    b_y->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)b_y, i5, (int)sizeof(double));
    b_m = mod_func_d->size[0];
    i5 = b_y->size[0] * b_y->size[1];
    emxEnsureCapacity((emxArray__common *)b_y, i5, (int)sizeof(double));
    ib = b_y->size[1];
    for (i5 = 0; i5 < ib; i5++) {
      nm1d2 = b_y->size[0];
      for (i6 = 0; i6 < nm1d2; i6++) {
        b_y->data[i6 + b_y->size[0] * i5] = 0.0;
      }
    }

    if ((mod_func_d->size[0] == 0) || (X->size[1] == 0)) {
    } else {
      ix = mod_func_d->size[0] * (X->size[1] - 1);
      nm1d2 = 0;
      while ((b_m > 0) && (nm1d2 <= ix)) {
        i5 = nm1d2 + b_m;
        for (ic = nm1d2; ic + 1 <= i5; ic++) {
          b_y->data[ic] = 0.0;
        }

        nm1d2 += b_m;
      }

      br = 0;
      nm1d2 = 0;
      while ((b_m > 0) && (nm1d2 <= ix)) {
        ar = 0;
        i5 = br + k;
        for (ib = br; ib + 1 <= i5; ib++) {
          if (X->data[ib] != 0.0) {
            ia = ar;
            i6 = nm1d2 + b_m;
            for (ic = nm1d2; ic + 1 <= i6; ic++) {
              ia++;
              b_y->data[ic] += X->data[ib] * mod_func_d->data[ia - 1];
            }
          }

          ar += b_m;
        }

        br += k;
        nm1d2 += b_m;
      }
    }
  }

  emxInit_real_T(&c_X, 2);
  i5 = c_X->size[0] * c_X->size[1];
  c_X->size[0] = X->size[1];
  c_X->size[1] = X->size[0];
  emxEnsureCapacity((emxArray__common *)c_X, i5, (int)sizeof(double));
  ib = X->size[0];
  for (i5 = 0; i5 < ib; i5++) {
    nm1d2 = X->size[1];
    for (i6 = 0; i6 < nm1d2; i6++) {
      c_X->data[i6 + c_X->size[0] * i5] = X->data[i5 + X->size[0] * i6];
    }
  }

  emxFree_real_T(&X);
  mldivide(b_y, c_X, mod_func_d);
  emxFree_real_T(&c_X);
  emxFree_real_T(&b_y);
  if ((mod_func_d->size[1] == 1) || (st->size[0] == 1)) {
    i5 = ni_min->size[0];
    ni_min->size[0] = mod_func_d->size[0];
    emxEnsureCapacity((emxArray__common *)ni_min, i5, (int)sizeof(double));
    ib = mod_func_d->size[0];
    for (i5 = 0; i5 < ib; i5++) {
      ni_min->data[i5] = 0.0;
      nm1d2 = mod_func_d->size[1];
      for (i6 = 0; i6 < nm1d2; i6++) {
        ni_min->data[i5] += mod_func_d->data[i5 + mod_func_d->size[0] * i6] *
          st->data[i6];
      }
    }
  } else {
    k = mod_func_d->size[1];
    unnamed_idx_0 = (unsigned int)mod_func_d->size[0];
    i5 = ni_min->size[0];
    ni_min->size[0] = (int)unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *)ni_min, i5, (int)sizeof(double));
    b_m = mod_func_d->size[0];
    ix = ni_min->size[0];
    i5 = ni_min->size[0];
    ni_min->size[0] = ix;
    emxEnsureCapacity((emxArray__common *)ni_min, i5, (int)sizeof(double));
    for (i5 = 0; i5 < ix; i5++) {
      ni_min->data[i5] = 0.0;
    }

    if (mod_func_d->size[0] == 0) {
    } else {
      nm1d2 = 0;
      while ((b_m > 0) && (nm1d2 <= 0)) {
        for (ic = 1; ic <= b_m; ic++) {
          ni_min->data[ic - 1] = 0.0;
        }

        nm1d2 = b_m;
      }

      br = 0;
      nm1d2 = 0;
      while ((b_m > 0) && (nm1d2 <= 0)) {
        ar = 0;
        i5 = br + k;
        for (ib = br; ib + 1 <= i5; ib++) {
          if (st->data[ib] != 0.0) {
            ia = ar;
            for (ic = 0; ic + 1 <= b_m; ic++) {
              ia++;
              ni_min->data[ic] += st->data[ib] * mod_func_d->data[ia - 1];
            }
          }

          ar += b_m;
        }

        br += k;
        nm1d2 = b_m;
      }
    }
  }

  emxFree_real_T(&st);
  emxFree_real_T(&mod_func_d);
  if (1.0 > m - 1.0) {
    ib = 0;
  } else {
    ib = (int)(m - 1.0);
  }

  if (m > ni_min->size[0]) {
    i5 = 1;
    i6 = 0;
  } else {
    i5 = (int)m;
    i6 = ni_min->size[0];
  }

  emxInit_real_T1(&b_ni_min, 1);
  ar = b_ni_min->size[0];
  b_ni_min->size[0] = ((ib + i6) - i5) + 2;
  emxEnsureCapacity((emxArray__common *)b_ni_min, ar, (int)sizeof(double));
  for (ar = 0; ar < ib; ar++) {
    b_ni_min->data[ar] = ni_min->data[ar];
  }

  b_ni_min->data[ib] = -1.0;
  nm1d2 = i6 - i5;
  for (i6 = 0; i6 <= nm1d2; i6++) {
    b_ni_min->data[(i6 + ib) + 1] = ni_min->data[(i5 + i6) - 1];
  }

  i5 = ni_min->size[0];
  ni_min->size[0] = b_ni_min->size[0];
  emxEnsureCapacity((emxArray__common *)ni_min, i5, (int)sizeof(double));
  ib = b_ni_min->size[0];
  for (i5 = 0; i5 < ib; i5++) {
    ni_min->data[i5] = b_ni_min->data[i5];
  }

  emxFree_real_T(&b_ni_min);
}

/*
 * funkcja modulujaca identyfikacja
 * Arguments    : const emxArray_real_T *u
 *                const emxArray_real_T *pv
 *                double h
 *                double n
 *                double m
 *                double N
 *                double M
 *                emxArray_real_T *ni_min
 * Return Type  : void
 */
void b_FHZN_MFM_model_ident_LSM(const emxArray_real_T *u, const emxArray_real_T *
  pv, double h, double n, double m, double N, double M, emxArray_real_T *ni_min)
{
  int ar;
  double anew;
  double apnd;
  double ndbl;
  double cdiff;
  emxArray_real_T *current_out;
  int i20;
  int nm1d2;
  int k;
  emxArray_real_T *mod_func;
  int i21;
  emxArray_real_T *b_mod_func;
  int br;
  int ib;
  double mtmp;
  int ix;
  boolean_T exitg1;
  double b_k;
  emxArray_real_T *mod_func_d;
  emxArray_real_T *current_u;
  emxArray_real_T *st;
  emxArray_real_T *s;
  emxArray_real_T *y_dot;
  emxArray_real_T *u_dot;
  emxArray_real_T *X;
  int i;
  emxArray_real_T *con;
  double y;
  emxArray_real_T *b_mod_func_d;
  int cnt;
  emxArray_int32_T *r12;
  emxArray_real_T *c_mod_func_d;
  emxArray_real_T *b_current_u;
  emxArray_real_T *d_mod_func_d;
  emxArray_real_T *c_current_u;
  emxArray_real_T *b_s;
  emxArray_real_T *b_st;
  int j;
  emxArray_real_T *b_X;
  emxArray_real_T *b_y;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  int b_m;
  int ic;
  int ia;
  emxArray_real_T *c_X;
  emxArray_real_T *b_ni_min;
  if (rtIsNaN(h)) {
    ar = 1;
    anew = rtNaN;
    apnd = h;
  } else if (h < 0.0) {
    ar = 0;
    anew = 0.0;
    apnd = h;
  } else if (rtIsInf(h)) {
    ar = 1;
    anew = rtNaN;
    apnd = h;
  } else {
    anew = 0.0;
    ndbl = floor(h + 0.5);
    apnd = ndbl;
    cdiff = ndbl - h;
    if (fabs(cdiff) < 4.4408920985006262E-16 * h) {
      ndbl++;
      apnd = h;
    } else if (cdiff > 0.0) {
      apnd = ndbl - 1.0;
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      ar = (int)ndbl;
    } else {
      ar = 0;
    }
  }

  emxInit_real_T(&current_out, 2);
  i20 = current_out->size[0] * current_out->size[1];
  current_out->size[0] = 1;
  current_out->size[1] = ar;
  emxEnsureCapacity((emxArray__common *)current_out, i20, (int)sizeof(double));
  if (ar > 0) {
    current_out->data[0] = anew;
    if (ar > 1) {
      current_out->data[ar - 1] = apnd;
      i20 = ar - 1;
      nm1d2 = i20 / 2;
      for (k = 1; k < nm1d2; k++) {
        current_out->data[k] = anew + (double)k;
        current_out->data[(ar - k) - 1] = apnd - (double)k;
      }

      if (nm1d2 << 1 == ar - 1) {
        current_out->data[nm1d2] = (anew + apnd) / 2.0;
      } else {
        current_out->data[nm1d2] = anew + (double)nm1d2;
        current_out->data[nm1d2 + 1] = apnd - (double)nm1d2;
      }
    }
  }

  emxInit_real_T(&mod_func, 2);
  MD_modulating_func(current_out, h, N, M, mod_func);
  if (2 > mod_func->size[1]) {
    i20 = 0;
    i21 = 0;
  } else {
    i20 = 1;
    i21 = mod_func->size[1];
  }

  emxInit_real_T(&b_mod_func, 2);
  br = b_mod_func->size[0] * b_mod_func->size[1];
  b_mod_func->size[0] = 1;
  b_mod_func->size[1] = i21 - i20;
  emxEnsureCapacity((emxArray__common *)b_mod_func, br, (int)sizeof(double));
  ib = i21 - i20;
  for (i21 = 0; i21 < ib; i21++) {
    b_mod_func->data[b_mod_func->size[0] * i21] = mod_func->data[i20 + i21];
  }

  i20 = mod_func->size[0] * mod_func->size[1];
  mod_func->size[0] = 1;
  mod_func->size[1] = b_mod_func->size[1];
  emxEnsureCapacity((emxArray__common *)mod_func, i20, (int)sizeof(double));
  ib = b_mod_func->size[1];
  for (i20 = 0; i20 < ib; i20++) {
    mod_func->data[mod_func->size[0] * i20] = b_mod_func->data[b_mod_func->size
      [0] * i20];
  }

  emxFree_real_T(&b_mod_func);
  nm1d2 = 1;
  ar = mod_func->size[1];
  mtmp = mod_func->data[0];
  if (mod_func->size[1] > 1) {
    if (rtIsNaN(mod_func->data[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= ar)) {
        nm1d2 = ix;
        if (!rtIsNaN(mod_func->data[ix - 1])) {
          mtmp = mod_func->data[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (nm1d2 < mod_func->size[1]) {
      while (nm1d2 + 1 <= ar) {
        if (mod_func->data[nm1d2] > mtmp) {
          mtmp = mod_func->data[nm1d2];
        }

        nm1d2++;
      }
    }
  }

  i20 = mod_func->size[0] * mod_func->size[1];
  mod_func->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)mod_func, i20, (int)sizeof(double));
  nm1d2 = mod_func->size[0];
  ix = mod_func->size[1];
  ib = nm1d2 * ix;
  for (i20 = 0; i20 < ib; i20++) {
    mod_func->data[i20] /= mtmp;
  }

  if ((n >= m) || rtIsNaN(m)) {
    b_k = n;
  } else {
    b_k = m;
  }

  emxInit_real_T(&mod_func_d, 2);
  i20 = mod_func_d->size[0] * mod_func_d->size[1];
  mod_func_d->size[0] = (int)(b_k - 1.0);
  mod_func_d->size[1] = (int)(h + 1.0);
  emxEnsureCapacity((emxArray__common *)mod_func_d, i20, (int)sizeof(double));
  ib = (int)(b_k - 1.0) * (int)(h + 1.0);
  for (i20 = 0; i20 < ib; i20++) {
    mod_func_d->data[i20] = 0.0;
  }

  emxInit_real_T(&current_u, 2);
  i20 = current_u->size[0] * current_u->size[1];
  current_u->size[0] = 2;
  current_u->size[1] = (int)(h + 1.0);
  emxEnsureCapacity((emxArray__common *)current_u, i20, (int)sizeof(double));
  ib = (int)(h + 1.0) << 1;
  for (i20 = 0; i20 < ib; i20++) {
    current_u->data[i20] = 0.0;
  }

  emxInit_real_T1(&st, 1);
  i20 = st->size[0];
  st->size[0] = (int)n;
  emxEnsureCapacity((emxArray__common *)st, i20, (int)sizeof(double));
  ib = (int)n;
  for (i20 = 0; i20 < ib; i20++) {
    st->data[i20] = 0.0;
  }

  emxInit_real_T1(&s, 1);
  i20 = s->size[0];
  s->size[0] = (int)m;
  emxEnsureCapacity((emxArray__common *)s, i20, (int)sizeof(double));
  ib = (int)m;
  for (i20 = 0; i20 < ib; i20++) {
    s->data[i20] = 0.0;
  }

  emxInit_real_T(&y_dot, 2);
  i20 = y_dot->size[0] * y_dot->size[1];
  y_dot->size[0] = (int)m;
  y_dot->size[1] = (int)((double)pv->size[1] - h);
  emxEnsureCapacity((emxArray__common *)y_dot, i20, (int)sizeof(double));
  ib = (int)m * (int)((double)pv->size[1] - h);
  for (i20 = 0; i20 < ib; i20++) {
    y_dot->data[i20] = 0.0;
  }

  emxInit_real_T(&u_dot, 2);
  i20 = u_dot->size[0] * u_dot->size[1];
  u_dot->size[0] = (int)(2.0 * n);
  u_dot->size[1] = (int)((double)pv->size[1] - h);
  emxEnsureCapacity((emxArray__common *)u_dot, i20, (int)sizeof(double));
  ib = (int)(2.0 * n) * (int)((double)pv->size[1] - h);
  for (i20 = 0; i20 < ib; i20++) {
    u_dot->data[i20] = 0.0;
  }

  emxInit_real_T(&X, 2);
  i20 = X->size[0] * X->size[1];
  X->size[0] = (int)((m - 1.0) + 2.0 * n);
  X->size[1] = (int)((double)pv->size[1] - h);
  emxEnsureCapacity((emxArray__common *)X, i20, (int)sizeof(double));
  ib = (int)((m - 1.0) + 2.0 * n) * (int)((double)pv->size[1] - h);
  for (i20 = 0; i20 < ib; i20++) {
    X->data[i20] = 0.0;
  }

  i = 0;
  emxInit_real_T(&con, 2);
  while (i <= (int)(b_k - 1.0) - 1) {
    y = 1.0 / mtmp;
    if (rtIsNaN(h)) {
      ar = 1;
      anew = rtNaN;
      apnd = h;
    } else if (h < 0.0) {
      ar = 0;
      anew = 0.0;
      apnd = h;
    } else if (rtIsInf(h)) {
      ar = 1;
      anew = rtNaN;
      apnd = h;
    } else {
      anew = 0.0;
      ndbl = floor(h + 0.5);
      apnd = ndbl;
      cdiff = ndbl - h;
      if (fabs(cdiff) < 4.4408920985006262E-16 * h) {
        ndbl++;
        apnd = h;
      } else if (cdiff > 0.0) {
        apnd = ndbl - 1.0;
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        ar = (int)ndbl;
      } else {
        ar = 0;
      }
    }

    i20 = current_out->size[0] * current_out->size[1];
    current_out->size[0] = 1;
    current_out->size[1] = ar;
    emxEnsureCapacity((emxArray__common *)current_out, i20, (int)sizeof(double));
    if (ar > 0) {
      current_out->data[0] = anew;
      if (ar > 1) {
        current_out->data[ar - 1] = apnd;
        i20 = ar - 1;
        nm1d2 = i20 / 2;
        for (k = 1; k < nm1d2; k++) {
          current_out->data[k] = anew + (double)k;
          current_out->data[(ar - k) - 1] = apnd - (double)k;
        }

        if (nm1d2 << 1 == ar - 1) {
          current_out->data[nm1d2] = (anew + apnd) / 2.0;
        } else {
          current_out->data[nm1d2] = anew + (double)nm1d2;
          current_out->data[nm1d2 + 1] = apnd - (double)nm1d2;
        }
      }
    }

    MD_modulating_func_d(1.0 + (double)i, current_out, h, N, M, con);
    ib = con->size[1];
    for (i20 = 0; i20 < ib; i20++) {
      mod_func_d->data[i + mod_func_d->size[0] * i20] = y * con->data[con->size
        [0] * i20];
    }

    i++;
  }

  if (2 > mod_func_d->size[1]) {
    i20 = 0;
    i21 = 0;
  } else {
    i20 = 1;
    i21 = mod_func_d->size[1];
  }

  emxInit_real_T(&b_mod_func_d, 2);
  ix = mod_func_d->size[0];
  br = b_mod_func_d->size[0] * b_mod_func_d->size[1];
  b_mod_func_d->size[0] = ix;
  b_mod_func_d->size[1] = i21 - i20;
  emxEnsureCapacity((emxArray__common *)b_mod_func_d, br, (int)sizeof(double));
  ib = i21 - i20;
  for (i21 = 0; i21 < ib; i21++) {
    for (br = 0; br < ix; br++) {
      b_mod_func_d->data[br + b_mod_func_d->size[0] * i21] = mod_func_d->data[br
        + mod_func_d->size[0] * (i20 + i21)];
    }
  }

  i20 = mod_func_d->size[0] * mod_func_d->size[1];
  mod_func_d->size[0] = b_mod_func_d->size[0];
  mod_func_d->size[1] = b_mod_func_d->size[1];
  emxEnsureCapacity((emxArray__common *)mod_func_d, i20, (int)sizeof(double));
  ib = b_mod_func_d->size[1];
  for (i20 = 0; i20 < ib; i20++) {
    nm1d2 = b_mod_func_d->size[0];
    for (i21 = 0; i21 < nm1d2; i21++) {
      mod_func_d->data[i21 + mod_func_d->size[0] * i20] = b_mod_func_d->data[i21
        + b_mod_func_d->size[0] * i20];
    }
  }

  emxFree_real_T(&b_mod_func_d);
  nm1d2 = u->size[1];
  if (2 >= nm1d2) {
    nm1d2 = 2;
  }

  if (u->size[1] == 0) {
    ar = 0;
  } else {
    ar = nm1d2;
  }

  cnt = 0;
  emxInit_int32_T1(&r12, 1);
  emxInit_real_T(&c_mod_func_d, 2);
  emxInit_real_T(&b_current_u, 2);
  emxInit_real_T(&d_mod_func_d, 2);
  emxInit_real_T(&c_current_u, 2);
  emxInit_real_T(&b_s, 2);
  emxInit_real_T(&b_st, 2);
  while (cnt <= ar - 1) {
    if (1.0 + (double)cnt > h) {
      anew = (1.0 + (double)cnt) - h;
      if (anew > 1.0 + (double)cnt) {
        i20 = 0;
        i21 = 0;
      } else {
        i20 = (int)anew - 1;
        i21 = cnt + 1;
      }

      br = current_out->size[0] * current_out->size[1];
      current_out->size[0] = 1;
      current_out->size[1] = i21 - i20;
      emxEnsureCapacity((emxArray__common *)current_out, br, (int)sizeof(double));
      ib = i21 - i20;
      for (i21 = 0; i21 < ib; i21++) {
        current_out->data[current_out->size[0] * i21] = pv->data[i20 + i21];
      }

      for (i = 0; i < 2; i++) {
        anew = (1.0 + (double)cnt) - h;
        if (anew > 1.0 + (double)cnt) {
          i20 = 1;
          i21 = 0;
        } else {
          i20 = (int)anew;
          i21 = cnt + 1;
        }

        ib = i21 - i20;
        for (i21 = 0; i21 <= ib; i21++) {
          current_u->data[i + current_u->size[0] * i21] = u->data[i + u->size[0]
            * ((i20 + i21) - 1)];
        }
      }

      /* IDENTYFIKACJA DLA DLUGIEGO OKNA */
      /* Wyjscie i jego pochodne */
      for (i = 0; i < (int)m; i++) {
        if (1.0 + (double)i == 1.0) {
          b_conv(current_out, mod_func, con);
          i20 = (int)floor((double)con->size[1] / 2.0);
          if (1 > i20) {
            i20 = 0;
          }

          i21 = con->size[0] * con->size[1];
          con->size[1] = i20;
          emxEnsureCapacity((emxArray__common *)con, i21, (int)sizeof(double));
          s->data[0] = con->data[i20 - 1];
        } else {
          ib = mod_func_d->size[1];
          i20 = c_mod_func_d->size[0] * c_mod_func_d->size[1];
          c_mod_func_d->size[0] = 1;
          c_mod_func_d->size[1] = ib;
          emxEnsureCapacity((emxArray__common *)c_mod_func_d, i20, (int)sizeof
                            (double));
          for (i20 = 0; i20 < ib; i20++) {
            c_mod_func_d->data[c_mod_func_d->size[0] * i20] = mod_func_d->data
              [((int)((1.0 + (double)i) - 1.0) + mod_func_d->size[0] * i20) - 1];
          }

          b_conv(current_out, c_mod_func_d, con);
          i20 = (int)floor((double)con->size[1] / 2.0);
          if (1 > i20) {
            i20 = 0;
          }

          i21 = con->size[0] * con->size[1];
          con->size[1] = i20;
          emxEnsureCapacity((emxArray__common *)con, i21, (int)sizeof(double));
          s->data[i] = con->data[i20 - 1];
        }
      }

      ib = y_dot->size[0];
      i20 = r12->size[0];
      r12->size[0] = ib;
      emxEnsureCapacity((emxArray__common *)r12, i20, (int)sizeof(int));
      for (i20 = 0; i20 < ib; i20++) {
        r12->data[i20] = i20;
      }

      i20 = (int)((1.0 + (double)cnt) - h) - 1;
      i21 = b_s->size[0] * b_s->size[1];
      b_s->size[0] = 1;
      b_s->size[1] = s->size[0];
      emxEnsureCapacity((emxArray__common *)b_s, i21, (int)sizeof(double));
      ib = s->size[0];
      for (i21 = 0; i21 < ib; i21++) {
        b_s->data[b_s->size[0] * i21] = s->data[i21];
      }

      ix = r12->size[0];
      for (i21 = 0; i21 < ix; i21++) {
        y_dot->data[r12->data[i21] + y_dot->size[0] * i20] = b_s->data[i21];
      }

      /* Sterowanie i opoznienia */
      for (i = 0; i < 2; i++) {
        for (j = 0; j < (int)n; j++) {
          if (1.0 + (double)j == 1.0) {
            ib = current_u->size[1];
            i20 = c_current_u->size[0] * c_current_u->size[1];
            c_current_u->size[0] = 1;
            c_current_u->size[1] = ib;
            emxEnsureCapacity((emxArray__common *)c_current_u, i20, (int)sizeof
                              (double));
            for (i20 = 0; i20 < ib; i20++) {
              c_current_u->data[c_current_u->size[0] * i20] = current_u->data[i
                + current_u->size[0] * i20];
            }

            b_conv(c_current_u, mod_func, con);
            i20 = (int)floor((double)con->size[1] / 2.0);
            if (1 > i20) {
              i20 = 0;
            }

            i21 = con->size[0] * con->size[1];
            con->size[1] = i20;
            emxEnsureCapacity((emxArray__common *)con, i21, (int)sizeof(double));
            st->data[0] = con->data[i20 - 1];
          } else {
            ib = current_u->size[1];
            i20 = b_current_u->size[0] * b_current_u->size[1];
            b_current_u->size[0] = 1;
            b_current_u->size[1] = ib;
            emxEnsureCapacity((emxArray__common *)b_current_u, i20, (int)sizeof
                              (double));
            for (i20 = 0; i20 < ib; i20++) {
              b_current_u->data[b_current_u->size[0] * i20] = current_u->data[i
                + current_u->size[0] * i20];
            }

            ib = mod_func_d->size[1];
            i20 = d_mod_func_d->size[0] * d_mod_func_d->size[1];
            d_mod_func_d->size[0] = 1;
            d_mod_func_d->size[1] = ib;
            emxEnsureCapacity((emxArray__common *)d_mod_func_d, i20, (int)sizeof
                              (double));
            for (i20 = 0; i20 < ib; i20++) {
              d_mod_func_d->data[d_mod_func_d->size[0] * i20] = mod_func_d->
                data[((int)((1.0 + (double)j) - 1.0) + mod_func_d->size[0] * i20)
                - 1];
            }

            b_conv(b_current_u, d_mod_func_d, con);
            i20 = (int)floor((double)con->size[1] / 2.0);
            if (1 > i20) {
              i20 = 0;
            }

            i21 = con->size[0] * con->size[1];
            con->size[1] = i20;
            emxEnsureCapacity((emxArray__common *)con, i21, (int)sizeof(double));
            st->data[j] = con->data[i20 - 1];
          }
        }

        anew = ((1.0 + (double)i) - 1.0) * n + 1.0;
        ndbl = (1.0 + (double)i) * n;
        if (anew > ndbl) {
          i20 = 0;
          i21 = 0;
        } else {
          i20 = (int)anew - 1;
          i21 = (int)ndbl;
        }

        br = r12->size[0];
        r12->size[0] = i21 - i20;
        emxEnsureCapacity((emxArray__common *)r12, br, (int)sizeof(int));
        ib = i21 - i20;
        for (i21 = 0; i21 < ib; i21++) {
          r12->data[i21] = i20 + i21;
        }

        i20 = (int)((1.0 + (double)cnt) - h) - 1;
        i21 = b_st->size[0] * b_st->size[1];
        b_st->size[0] = 1;
        b_st->size[1] = st->size[0];
        emxEnsureCapacity((emxArray__common *)b_st, i21, (int)sizeof(double));
        ib = st->size[0];
        for (i21 = 0; i21 < ib; i21++) {
          b_st->data[b_st->size[0] * i21] = st->data[i21];
        }

        ix = r12->size[0];
        for (i21 = 0; i21 < ix; i21++) {
          u_dot->data[r12->data[i21] + u_dot->size[0] * i20] = b_st->data[i21];
        }
      }
    }

    cnt++;
  }

  emxFree_real_T(&b_st);
  emxFree_real_T(&b_s);
  emxFree_real_T(&c_current_u);
  emxFree_real_T(&d_mod_func_d);
  emxFree_real_T(&b_current_u);
  emxFree_real_T(&c_mod_func_d);
  emxFree_int32_T(&r12);
  emxFree_real_T(&con);
  emxFree_real_T(&s);
  emxFree_real_T(&current_u);
  emxFree_real_T(&mod_func);
  for (i = 0; i < (int)(m - 1.0); i++) {
    ib = y_dot->size[1] - 1;
    for (i20 = 0; i20 <= ib; i20++) {
      X->data[i + X->size[0] * i20] = y_dot->data[i + y_dot->size[0] * i20];
    }
  }

  b_k = 1.0;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < (int)n; j++) {
      i20 = (int)((b_k + m) - 1.0) - 1;
      ib = u_dot->size[1];
      i21 = (int)(((1.0 + (double)i) - 1.0) * n + (1.0 + (double)j));
      br = current_out->size[0] * current_out->size[1];
      current_out->size[0] = 1;
      current_out->size[1] = ib;
      emxEnsureCapacity((emxArray__common *)current_out, br, (int)sizeof(double));
      for (br = 0; br < ib; br++) {
        current_out->data[current_out->size[0] * br] = u_dot->data[(i21 +
          u_dot->size[0] * br) - 1];
      }

      ib = current_out->size[1];
      for (i21 = 0; i21 < ib; i21++) {
        X->data[i20 + X->size[0] * i21] = current_out->data[current_out->size[0]
          * i21];
      }

      b_k++;
    }
  }

  emxFree_real_T(&current_out);
  emxFree_real_T(&u_dot);
  emxInit_real_T(&b_X, 2);
  i20 = b_X->size[0] * b_X->size[1];
  b_X->size[0] = X->size[1];
  b_X->size[1] = X->size[0];
  emxEnsureCapacity((emxArray__common *)b_X, i20, (int)sizeof(double));
  ib = X->size[0];
  for (i20 = 0; i20 < ib; i20++) {
    nm1d2 = X->size[1];
    for (i21 = 0; i21 < nm1d2; i21++) {
      b_X->data[i21 + b_X->size[0] * i20] = X->data[i20 + X->size[0] * i21];
    }
  }

  i20 = X->size[0] * X->size[1];
  X->size[0] = b_X->size[0];
  X->size[1] = b_X->size[1];
  emxEnsureCapacity((emxArray__common *)X, i20, (int)sizeof(double));
  ib = b_X->size[1];
  for (i20 = 0; i20 < ib; i20++) {
    nm1d2 = b_X->size[0];
    for (i21 = 0; i21 < nm1d2; i21++) {
      X->data[i21 + X->size[0] * i20] = b_X->data[i21 + b_X->size[0] * i20];
    }
  }

  emxFree_real_T(&b_X);
  ib = y_dot->size[1];
  nm1d2 = y_dot->size[0];
  i20 = st->size[0];
  st->size[0] = ib;
  emxEnsureCapacity((emxArray__common *)st, i20, (int)sizeof(double));
  for (i20 = 0; i20 < ib; i20++) {
    st->data[i20] = y_dot->data[(nm1d2 + y_dot->size[0] * i20) - 1];
  }

  emxFree_real_T(&y_dot);
  i20 = mod_func_d->size[0] * mod_func_d->size[1];
  mod_func_d->size[0] = X->size[1];
  mod_func_d->size[1] = X->size[0];
  emxEnsureCapacity((emxArray__common *)mod_func_d, i20, (int)sizeof(double));
  ib = X->size[0];
  for (i20 = 0; i20 < ib; i20++) {
    nm1d2 = X->size[1];
    for (i21 = 0; i21 < nm1d2; i21++) {
      mod_func_d->data[i21 + mod_func_d->size[0] * i20] = X->data[i20 + X->size
        [0] * i21];
    }
  }

  emxInit_real_T(&b_y, 2);
  if ((mod_func_d->size[1] == 1) || (X->size[0] == 1)) {
    i20 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = mod_func_d->size[0];
    b_y->size[1] = X->size[1];
    emxEnsureCapacity((emxArray__common *)b_y, i20, (int)sizeof(double));
    ib = mod_func_d->size[0];
    for (i20 = 0; i20 < ib; i20++) {
      nm1d2 = X->size[1];
      for (i21 = 0; i21 < nm1d2; i21++) {
        b_y->data[i20 + b_y->size[0] * i21] = 0.0;
        ix = mod_func_d->size[1];
        for (br = 0; br < ix; br++) {
          b_y->data[i20 + b_y->size[0] * i21] += mod_func_d->data[i20 +
            mod_func_d->size[0] * br] * X->data[br + X->size[0] * i21];
        }
      }
    }
  } else {
    k = mod_func_d->size[1];
    unnamed_idx_0 = (unsigned int)mod_func_d->size[0];
    unnamed_idx_1 = (unsigned int)X->size[1];
    i20 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = (int)unnamed_idx_0;
    b_y->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)b_y, i20, (int)sizeof(double));
    b_m = mod_func_d->size[0];
    i20 = b_y->size[0] * b_y->size[1];
    emxEnsureCapacity((emxArray__common *)b_y, i20, (int)sizeof(double));
    ib = b_y->size[1];
    for (i20 = 0; i20 < ib; i20++) {
      nm1d2 = b_y->size[0];
      for (i21 = 0; i21 < nm1d2; i21++) {
        b_y->data[i21 + b_y->size[0] * i20] = 0.0;
      }
    }

    if ((mod_func_d->size[0] == 0) || (X->size[1] == 0)) {
    } else {
      ix = mod_func_d->size[0] * (X->size[1] - 1);
      nm1d2 = 0;
      while ((b_m > 0) && (nm1d2 <= ix)) {
        i20 = nm1d2 + b_m;
        for (ic = nm1d2; ic + 1 <= i20; ic++) {
          b_y->data[ic] = 0.0;
        }

        nm1d2 += b_m;
      }

      br = 0;
      nm1d2 = 0;
      while ((b_m > 0) && (nm1d2 <= ix)) {
        ar = 0;
        i20 = br + k;
        for (ib = br; ib + 1 <= i20; ib++) {
          if (X->data[ib] != 0.0) {
            ia = ar;
            i21 = nm1d2 + b_m;
            for (ic = nm1d2; ic + 1 <= i21; ic++) {
              ia++;
              b_y->data[ic] += X->data[ib] * mod_func_d->data[ia - 1];
            }
          }

          ar += b_m;
        }

        br += k;
        nm1d2 += b_m;
      }
    }
  }

  emxInit_real_T(&c_X, 2);
  i20 = c_X->size[0] * c_X->size[1];
  c_X->size[0] = X->size[1];
  c_X->size[1] = X->size[0];
  emxEnsureCapacity((emxArray__common *)c_X, i20, (int)sizeof(double));
  ib = X->size[0];
  for (i20 = 0; i20 < ib; i20++) {
    nm1d2 = X->size[1];
    for (i21 = 0; i21 < nm1d2; i21++) {
      c_X->data[i21 + c_X->size[0] * i20] = X->data[i20 + X->size[0] * i21];
    }
  }

  emxFree_real_T(&X);
  mldivide(b_y, c_X, mod_func_d);
  emxFree_real_T(&c_X);
  emxFree_real_T(&b_y);
  if ((mod_func_d->size[1] == 1) || (st->size[0] == 1)) {
    i20 = ni_min->size[0];
    ni_min->size[0] = mod_func_d->size[0];
    emxEnsureCapacity((emxArray__common *)ni_min, i20, (int)sizeof(double));
    ib = mod_func_d->size[0];
    for (i20 = 0; i20 < ib; i20++) {
      ni_min->data[i20] = 0.0;
      nm1d2 = mod_func_d->size[1];
      for (i21 = 0; i21 < nm1d2; i21++) {
        ni_min->data[i20] += mod_func_d->data[i20 + mod_func_d->size[0] * i21] *
          st->data[i21];
      }
    }
  } else {
    k = mod_func_d->size[1];
    unnamed_idx_0 = (unsigned int)mod_func_d->size[0];
    i20 = ni_min->size[0];
    ni_min->size[0] = (int)unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *)ni_min, i20, (int)sizeof(double));
    b_m = mod_func_d->size[0];
    ix = ni_min->size[0];
    i20 = ni_min->size[0];
    ni_min->size[0] = ix;
    emxEnsureCapacity((emxArray__common *)ni_min, i20, (int)sizeof(double));
    for (i20 = 0; i20 < ix; i20++) {
      ni_min->data[i20] = 0.0;
    }

    if (mod_func_d->size[0] == 0) {
    } else {
      nm1d2 = 0;
      while ((b_m > 0) && (nm1d2 <= 0)) {
        for (ic = 1; ic <= b_m; ic++) {
          ni_min->data[ic - 1] = 0.0;
        }

        nm1d2 = b_m;
      }

      br = 0;
      nm1d2 = 0;
      while ((b_m > 0) && (nm1d2 <= 0)) {
        ar = 0;
        i20 = br + k;
        for (ib = br; ib + 1 <= i20; ib++) {
          if (st->data[ib] != 0.0) {
            ia = ar;
            for (ic = 0; ic + 1 <= b_m; ic++) {
              ia++;
              ni_min->data[ic] += st->data[ib] * mod_func_d->data[ia - 1];
            }
          }

          ar += b_m;
        }

        br += k;
        nm1d2 = b_m;
      }
    }
  }

  emxFree_real_T(&st);
  emxFree_real_T(&mod_func_d);
  if (1.0 > m - 1.0) {
    ib = 0;
  } else {
    ib = (int)(m - 1.0);
  }

  if (m > ni_min->size[0]) {
    i20 = 1;
    i21 = 0;
  } else {
    i20 = (int)m;
    i21 = ni_min->size[0];
  }

  emxInit_real_T1(&b_ni_min, 1);
  br = b_ni_min->size[0];
  b_ni_min->size[0] = ((ib + i21) - i20) + 2;
  emxEnsureCapacity((emxArray__common *)b_ni_min, br, (int)sizeof(double));
  for (br = 0; br < ib; br++) {
    b_ni_min->data[br] = ni_min->data[br];
  }

  b_ni_min->data[ib] = -1.0;
  nm1d2 = i21 - i20;
  for (i21 = 0; i21 <= nm1d2; i21++) {
    b_ni_min->data[(i21 + ib) + 1] = ni_min->data[(i20 + i21) - 1];
  }

  i20 = ni_min->size[0];
  ni_min->size[0] = b_ni_min->size[0];
  emxEnsureCapacity((emxArray__common *)ni_min, i20, (int)sizeof(double));
  ib = b_ni_min->size[0];
  for (i20 = 0; i20 < ib; i20++) {
    ni_min->data[i20] = b_ni_min->data[i20];
  }

  emxFree_real_T(&b_ni_min);
}

/*
 * File trailer for FHZN_MFM_model_ident_LSM.c
 *
 * [EOF]
 */
