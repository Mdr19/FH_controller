/*
 * File: cmpc_2.c
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
#include "cmpc_2.h"
#include "FHZN_define_model_del_emxutil.h"
#include "Iint.h"
#include "expm.h"
#include "lagc.h"
#include "mpower.h"
#include "eye.h"
#include "sum.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                const emxArray_real_T *Bd
 *                const emxArray_real_T *p
 *                const emxArray_real_T *N
 *                double Tp
 *                const emxArray_real_T *Q
 *                const emxArray_real_T *R
 *                boolean_T without_ff
 *                emxArray_real_T *Omega
 *                emxArray_real_T *Psi
 *                emxArray_real_T *Gamma
 *                emxArray_real_T *Al
 * Return Type  : void
 */
void cmpc_2(const emxArray_real_T *A, const emxArray_real_T *B, const
            emxArray_real_T *Bd, const emxArray_real_T *p, const emxArray_real_T
            *N, double Tp, const emxArray_real_T *Q, const emxArray_real_T *R,
            boolean_T without_ff, emxArray_real_T *Omega, emxArray_real_T *Psi,
            emxArray_real_T *Gamma, emxArray_real_T *Al)
{
  int n_in;
  int ixstart;
  int n;
  double ndbl;
  int ix;
  boolean_T exitg1;
  double tau_del;
  double anew;
  double apnd;
  double cdiff;
  emxArray_real_T *tau;
  int i30;
  int k;
  double N_pa;
  emxArray_real_T *S_in;
  emxArray_real_T *S_in_d;
  emxArray_real_T *S_sum_d;
  emxArray_real_T *R_L;
  double kk;
  int i;
  emxArray_real_T *b_R;
  int i31;
  int i32;
  int i33;
  int i34;
  int i35;
  int loop_ub;
  emxArray_real_T *L0;
  emxArray_real_T *b_A;
  emxArray_real_T *Eae;
  emxArray_real_T *b_Al;
  emxArray_real_T *Eap;
  emxArray_real_T *L;
  unsigned int Eap_idx_0;
  int m;
  int ic;
  int ar;
  int ib;
  int ia;
  emxArray_real_T *y;
  emxArray_real_T *b_B;
  boolean_T guard6 = false;
  emxArray_real_T *c_B;
  emxArray_real_T *d_B;
  emxArray_real_T *e_B;
  emxArray_real_T *b_y;
  double In_s;
  emxArray_real_T *c_y;
  emxArray_real_T *b_Bd;
  boolean_T guard5 = false;
  emxArray_real_T *c_Bd;
  emxArray_real_T *d_Bd;
  emxArray_real_T *e_Bd;
  emxArray_real_T *d_y;
  int jj;
  emxArray_real_T *e_y;
  emxArray_real_T *f_B;
  emxArray_real_T *c_Al;
  emxArray_real_T *g_B;
  emxArray_real_T *h_B;
  emxArray_real_T *i_B;
  emxArray_real_T *f_y;
  boolean_T guard4 = false;
  double In_e;
  emxArray_real_T *S_sum;
  emxArray_real_T *C;
  emxArray_real_T *b_C;
  emxArray_real_T *c_C;
  emxArray_real_T *d_C;
  emxArray_real_T *e_C;
  emxArray_real_T *f_C;
  emxArray_real_T *g_C;
  emxArray_real_T *h_C;
  emxArray_real_T *i_C;
  emxArray_real_T *b;
  emxArray_real_T *g_y;
  emxArray_real_T *h_y;
  emxArray_real_T *i_y;
  emxArray_real_T *r19;
  emxArray_real_T *d_Al;
  emxArray_real_T *e_Al;
  emxArray_real_T *b_S_sum;
  emxArray_real_T *b_S_in;
  emxArray_real_T *b_S_sum_d;
  emxArray_real_T *b_S_in_d;
  emxArray_real_T *c_S_sum;
  emxArray_real_T *c_S_in;
  boolean_T guard3 = false;
  unsigned int unnamed_idx_1;
  boolean_T guard2 = false;
  int b_kk;
  boolean_T guard1 = false;
  n_in = B->size[1] - 2;
  ixstart = 1;
  n = p->size[1];
  ndbl = p->data[0];
  if (p->size[1] > 1) {
    if (rtIsNaN(p->data[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(p->data[ix - 1])) {
          ndbl = p->data[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < p->size[1]) {
      while (ixstart + 1 <= n) {
        if (p->data[ixstart] > ndbl) {
          ndbl = p->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  tau_del = 0.001 / ndbl;
  if (rtIsNaN(tau_del) || rtIsNaN(Tp)) {
    n = 1;
    anew = rtNaN;
    apnd = Tp;
  } else if ((tau_del == 0.0) || ((0.0 < Tp) && (tau_del < 0.0)) || ((Tp < 0.0) &&
              (tau_del > 0.0))) {
    n = 0;
    anew = 0.0;
    apnd = Tp;
  } else if (rtIsInf(Tp)) {
    n = 1;
    anew = rtNaN;
    apnd = Tp;
  } else if (rtIsInf(tau_del)) {
    n = 1;
    anew = 0.0;
    apnd = Tp;
  } else {
    anew = 0.0;
    ndbl = floor(Tp / tau_del + 0.5);
    apnd = ndbl * tau_del;
    if (tau_del > 0.0) {
      cdiff = apnd - Tp;
    } else {
      cdiff = Tp - apnd;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * fabs(Tp)) {
      ndbl++;
      apnd = Tp;
    } else if (cdiff > 0.0) {
      apnd = (ndbl - 1.0) * tau_del;
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }
  }

  emxInit_real_T(&tau, 2);
  i30 = tau->size[0] * tau->size[1];
  tau->size[0] = 1;
  tau->size[1] = n;
  emxEnsureCapacity((emxArray__common *)tau, i30, (int)sizeof(double));
  if (n > 0) {
    tau->data[0] = anew;
    if (n > 1) {
      tau->data[n - 1] = apnd;
      i30 = n - 1;
      ixstart = i30 / 2;
      for (k = 1; k < ixstart; k++) {
        ndbl = (double)k * tau_del;
        tau->data[k] = anew + ndbl;
        tau->data[(n - k) - 1] = apnd - ndbl;
      }

      if (ixstart << 1 == n - 1) {
        tau->data[ixstart] = (anew + apnd) / 2.0;
      } else {
        ndbl = (double)ixstart * tau_del;
        tau->data[ixstart] = anew + ndbl;
        tau->data[ixstart + 1] = apnd - ndbl;
      }
    }
  }

  N_pa = c_sum(N);
  i30 = Omega->size[0] * Omega->size[1];
  Omega->size[0] = (int)N_pa;
  Omega->size[1] = (int)N_pa;
  emxEnsureCapacity((emxArray__common *)Omega, i30, (int)sizeof(double));
  n = (int)N_pa * (int)N_pa;
  for (i30 = 0; i30 < n; i30++) {
    Omega->data[i30] = 0.0;
  }

  i30 = Psi->size[0] * Psi->size[1];
  Psi->size[0] = (int)N_pa;
  Psi->size[1] = B->size[0];
  emxEnsureCapacity((emxArray__common *)Psi, i30, (int)sizeof(double));
  n = (int)N_pa * B->size[0];
  for (i30 = 0; i30 < n; i30++) {
    Psi->data[i30] = 0.0;
  }

  emxInit_real_T(&S_in, 2);
  i30 = S_in->size[0] * S_in->size[1];
  S_in->size[0] = B->size[0];
  S_in->size[1] = (int)N_pa;
  emxEnsureCapacity((emxArray__common *)S_in, i30, (int)sizeof(double));
  n = B->size[0] * (int)N_pa;
  for (i30 = 0; i30 < n; i30++) {
    S_in->data[i30] = 0.0;
  }

  emxInit_real_T(&S_in_d, 2);
  i30 = S_in_d->size[0] * S_in_d->size[1];
  S_in_d->size[0] = B->size[0];
  emxEnsureCapacity((emxArray__common *)S_in_d, i30, (int)sizeof(double));
  i30 = S_in_d->size[0] * S_in_d->size[1];
  S_in_d->size[1] = (int)N->data[0];
  emxEnsureCapacity((emxArray__common *)S_in_d, i30, (int)sizeof(double));
  n = B->size[0] * (int)N->data[0];
  for (i30 = 0; i30 < n; i30++) {
    S_in_d->data[i30] = 0.0;
  }

  emxInit_real_T(&S_sum_d, 2);
  i30 = S_sum_d->size[0] * S_sum_d->size[1];
  S_sum_d->size[0] = B->size[0];
  emxEnsureCapacity((emxArray__common *)S_sum_d, i30, (int)sizeof(double));
  i30 = S_sum_d->size[0] * S_sum_d->size[1];
  S_sum_d->size[1] = (int)N->data[0];
  emxEnsureCapacity((emxArray__common *)S_sum_d, i30, (int)sizeof(double));
  n = B->size[0] * (int)N->data[0];
  for (i30 = 0; i30 < n; i30++) {
    S_sum_d->data[i30] = 0.0;
  }

  i30 = Gamma->size[0] * Gamma->size[1];
  Gamma->size[0] = (int)N_pa;
  emxEnsureCapacity((emxArray__common *)Gamma, i30, (int)sizeof(double));
  i30 = Gamma->size[0] * Gamma->size[1];
  Gamma->size[1] = (int)N->data[0];
  emxEnsureCapacity((emxArray__common *)Gamma, i30, (int)sizeof(double));
  n = (int)N_pa * (int)N->data[0];
  for (i30 = 0; i30 < n; i30++) {
    Gamma->data[i30] = 0.0;
  }

  emxInit_real_T(&R_L, 2);
  eye(N_pa, N_pa, R_L);
  kk = 1.0;
  i = 0;
  emxInit_real_T(&b_R, 2);
  while (i <= n_in + 1) {
    ndbl = (kk - 1.0) + N->data[i];
    if (kk > ndbl) {
      i30 = 0;
      i31 = 0;
    } else {
      i30 = (int)kk - 1;
      i31 = (int)ndbl;
    }

    ndbl = (kk - 1.0) + N->data[i];
    if (kk > ndbl) {
      i32 = 0;
      i33 = 0;
    } else {
      i32 = (int)kk - 1;
      i33 = (int)ndbl;
    }

    ndbl = (kk - 1.0) + N->data[i];
    if (kk > ndbl) {
      i34 = 0;
    } else {
      i34 = (int)kk - 1;
    }

    ndbl = (kk - 1.0) + N->data[i];
    if (kk > ndbl) {
      i35 = 0;
    } else {
      i35 = (int)kk - 1;
    }

    ndbl = R->data[i + R->size[0] * i];
    ixstart = b_R->size[0] * b_R->size[1];
    b_R->size[0] = i31 - i30;
    b_R->size[1] = i33 - i32;
    emxEnsureCapacity((emxArray__common *)b_R, ixstart, (int)sizeof(double));
    n = i33 - i32;
    for (i33 = 0; i33 < n; i33++) {
      loop_ub = i31 - i30;
      for (ixstart = 0; ixstart < loop_ub; ixstart++) {
        b_R->data[ixstart + b_R->size[0] * i33] = ndbl * R_L->data[(i30 +
          ixstart) + R_L->size[0] * (i32 + i33)];
      }
    }

    n = b_R->size[1];
    for (i30 = 0; i30 < n; i30++) {
      loop_ub = b_R->size[0];
      for (i31 = 0; i31 < loop_ub; i31++) {
        R_L->data[(i34 + i31) + R_L->size[0] * (i35 + i30)] = b_R->data[i31 +
          b_R->size[0] * i30];
      }
    }

    kk += N->data[i];
    i++;
  }

  emxFree_real_T(&b_R);
  emxInit_real_T1(&L0, 1);
  emxInit_real_T(&b_A, 2);
  lagc(p->data[0], N->data[0], Al, L0);
  i30 = b_A->size[0] * b_A->size[1];
  b_A->size[0] = A->size[0];
  b_A->size[1] = A->size[1];
  emxEnsureCapacity((emxArray__common *)b_A, i30, (int)sizeof(double));
  n = A->size[0] * A->size[1];
  for (i30 = 0; i30 < n; i30++) {
    b_A->data[i30] = A->data[i30] * tau_del;
  }

  emxInit_real_T(&Eae, 2);
  emxInit_real_T(&b_Al, 2);
  expm(b_A, Eae);
  i30 = b_Al->size[0] * b_Al->size[1];
  b_Al->size[0] = Al->size[0];
  b_Al->size[1] = Al->size[1];
  emxEnsureCapacity((emxArray__common *)b_Al, i30, (int)sizeof(double));
  n = Al->size[0] * Al->size[1];
  emxFree_real_T(&b_A);
  for (i30 = 0; i30 < n; i30++) {
    b_Al->data[i30] = Al->data[i30] * tau_del;
  }

  emxInit_real_T(&Eap, 2);
  expm(b_Al, Eap);
  emxFree_real_T(&b_Al);
  emxInit_real_T1(&L, 1);
  if ((Eap->size[1] == 1) || (L0->size[0] == 1)) {
    i30 = L->size[0];
    L->size[0] = Eap->size[0];
    emxEnsureCapacity((emxArray__common *)L, i30, (int)sizeof(double));
    n = Eap->size[0];
    for (i30 = 0; i30 < n; i30++) {
      L->data[i30] = 0.0;
      loop_ub = Eap->size[1];
      for (i31 = 0; i31 < loop_ub; i31++) {
        L->data[i30] += Eap->data[i30 + Eap->size[0] * i31] * L0->data[i31];
      }
    }
  } else {
    k = Eap->size[1];
    Eap_idx_0 = (unsigned int)Eap->size[0];
    i30 = L->size[0];
    L->size[0] = (int)Eap_idx_0;
    emxEnsureCapacity((emxArray__common *)L, i30, (int)sizeof(double));
    m = Eap->size[0];
    ixstart = L->size[0];
    i30 = L->size[0];
    L->size[0] = ixstart;
    emxEnsureCapacity((emxArray__common *)L, i30, (int)sizeof(double));
    for (i30 = 0; i30 < ixstart; i30++) {
      L->data[i30] = 0.0;
    }

    if (Eap->size[0] == 0) {
    } else {
      ix = 0;
      while ((m > 0) && (ix <= 0)) {
        for (ic = 1; ic <= m; ic++) {
          L->data[ic - 1] = 0.0;
        }

        ix = m;
      }

      n = 0;
      ix = 0;
      while ((m > 0) && (ix <= 0)) {
        ar = 0;
        i30 = n + k;
        for (ib = n; ib + 1 <= i30; ib++) {
          if (L0->data[ib] != 0.0) {
            ia = ar;
            for (ic = 0; ic + 1 <= m; ic++) {
              ia++;
              L->data[ic] += L0->data[ib] * Eap->data[ia - 1];
            }
          }

          ar += m;
        }

        n += k;
        ix = m;
      }
    }
  }

  emxInit_real_T1(&y, 1);
  emxInit_real_T1(&b_B, 1);
  guard6 = false;
  if (Eae->size[1] == 1) {
    guard6 = true;
  } else {
    i30 = B->size[0];
    if (i30 == 1) {
      guard6 = true;
    } else {
      k = Eae->size[1];
      Eap_idx_0 = (unsigned int)Eae->size[0];
      i30 = y->size[0];
      y->size[0] = (int)Eap_idx_0;
      emxEnsureCapacity((emxArray__common *)y, i30, (int)sizeof(double));
      m = Eae->size[0];
      ixstart = y->size[0];
      i30 = y->size[0];
      y->size[0] = ixstart;
      emxEnsureCapacity((emxArray__common *)y, i30, (int)sizeof(double));
      for (i30 = 0; i30 < ixstart; i30++) {
        y->data[i30] = 0.0;
      }

      if (Eae->size[0] == 0) {
      } else {
        ix = 0;
        while ((m > 0) && (ix <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            y->data[ic - 1] = 0.0;
          }

          ix = m;
        }

        n = 0;
        ix = 0;
        while ((m > 0) && (ix <= 0)) {
          ar = 0;
          i30 = n + k;
          for (ib = n; ib + 1 <= i30; ib++) {
            if (B->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                y->data[ic] += B->data[ib] * Eae->data[ia - 1];
              }
            }

            ar += m;
          }

          n += k;
          ix = m;
        }
      }
    }
  }

  if (guard6) {
    n = B->size[0];
    i30 = b_B->size[0];
    b_B->size[0] = n;
    emxEnsureCapacity((emxArray__common *)b_B, i30, (int)sizeof(double));
    for (i30 = 0; i30 < n; i30++) {
      b_B->data[i30] = B->data[i30];
    }

    i30 = y->size[0];
    y->size[0] = Eae->size[0];
    emxEnsureCapacity((emxArray__common *)y, i30, (int)sizeof(double));
    n = Eae->size[0];
    for (i30 = 0; i30 < n; i30++) {
      y->data[i30] = 0.0;
      loop_ub = Eae->size[1];
      for (i31 = 0; i31 < loop_ub; i31++) {
        y->data[i30] += Eae->data[i30 + Eae->size[0] * i31] * b_B->data[i31];
      }
    }
  }

  emxFree_real_T(&b_B);
  emxInit_real_T(&c_B, 2);
  emxInit_real_T1(&d_B, 1);
  n = B->size[0];
  i30 = d_B->size[0];
  d_B->size[0] = n;
  emxEnsureCapacity((emxArray__common *)d_B, i30, (int)sizeof(double));
  for (i30 = 0; i30 < n; i30++) {
    d_B->data[i30] = -B->data[i30];
  }

  emxInit_real_T(&e_B, 2);
  emxInit_real_T(&b_y, 2);
  i30 = e_B->size[0] * e_B->size[1];
  e_B->size[0] = d_B->size[0];
  e_B->size[1] = L->size[0];
  emxEnsureCapacity((emxArray__common *)e_B, i30, (int)sizeof(double));
  n = d_B->size[0];
  for (i30 = 0; i30 < n; i30++) {
    loop_ub = L->size[0];
    for (i31 = 0; i31 < loop_ub; i31++) {
      e_B->data[i30 + e_B->size[0] * i31] = d_B->data[i30] * L->data[i31];
    }
  }

  emxFree_real_T(&d_B);
  i30 = b_y->size[0] * b_y->size[1];
  b_y->size[0] = y->size[0];
  b_y->size[1] = L0->size[0];
  emxEnsureCapacity((emxArray__common *)b_y, i30, (int)sizeof(double));
  n = y->size[0];
  for (i30 = 0; i30 < n; i30++) {
    loop_ub = L0->size[0];
    for (i31 = 0; i31 < loop_ub; i31++) {
      b_y->data[i30 + b_y->size[0] * i31] = y->data[i30] * L0->data[i31];
    }
  }

  emxFree_real_T(&y);
  i30 = c_B->size[0] * c_B->size[1];
  c_B->size[0] = e_B->size[0];
  c_B->size[1] = e_B->size[1];
  emxEnsureCapacity((emxArray__common *)c_B, i30, (int)sizeof(double));
  n = e_B->size[1];
  for (i30 = 0; i30 < n; i30++) {
    loop_ub = e_B->size[0];
    for (i31 = 0; i31 < loop_ub; i31++) {
      c_B->data[i31 + c_B->size[0] * i30] = e_B->data[i31 + e_B->size[0] * i30]
        + b_y->data[i31 + b_y->size[0] * i30];
    }
  }

  emxFree_real_T(&b_y);
  emxFree_real_T(&e_B);
  Iint(A, p->data[0], c_B, Eap);
  emxFree_real_T(&c_B);
  n = Eap->size[1];
  for (i30 = 0; i30 < n; i30++) {
    loop_ub = Eap->size[0];
    for (i31 = 0; i31 < loop_ub; i31++) {
      S_in->data[i31 + S_in->size[0] * i30] = Eap->data[i31 + Eap->size[0] * i30];
    }
  }

  In_s = 1.0;

  /*  diturbances */
  if (!without_ff) {
    emxInit_real_T1(&c_y, 1);
    emxInit_real_T1(&b_Bd, 1);
    guard5 = false;
    if (Eae->size[1] == 1) {
      guard5 = true;
    } else {
      i30 = Bd->size[0];
      if (i30 == 1) {
        guard5 = true;
      } else {
        k = Eae->size[1];
        Eap_idx_0 = (unsigned int)Eae->size[0];
        i30 = c_y->size[0];
        c_y->size[0] = (int)Eap_idx_0;
        emxEnsureCapacity((emxArray__common *)c_y, i30, (int)sizeof(double));
        m = Eae->size[0];
        ixstart = c_y->size[0];
        i30 = c_y->size[0];
        c_y->size[0] = ixstart;
        emxEnsureCapacity((emxArray__common *)c_y, i30, (int)sizeof(double));
        for (i30 = 0; i30 < ixstart; i30++) {
          c_y->data[i30] = 0.0;
        }

        if (Eae->size[0] == 0) {
        } else {
          ix = 0;
          while ((m > 0) && (ix <= 0)) {
            for (ic = 1; ic <= m; ic++) {
              c_y->data[ic - 1] = 0.0;
            }

            ix = m;
          }

          n = 0;
          ix = 0;
          while ((m > 0) && (ix <= 0)) {
            ar = 0;
            i30 = n + k;
            for (ib = n; ib + 1 <= i30; ib++) {
              if (Bd->data[ib] != 0.0) {
                ia = ar;
                for (ic = 0; ic + 1 <= m; ic++) {
                  ia++;
                  c_y->data[ic] += Bd->data[ib] * Eae->data[ia - 1];
                }
              }

              ar += m;
            }

            n += k;
            ix = m;
          }
        }
      }
    }

    if (guard5) {
      n = Bd->size[0];
      i30 = b_Bd->size[0];
      b_Bd->size[0] = n;
      emxEnsureCapacity((emxArray__common *)b_Bd, i30, (int)sizeof(double));
      for (i30 = 0; i30 < n; i30++) {
        b_Bd->data[i30] = Bd->data[i30];
      }

      i30 = c_y->size[0];
      c_y->size[0] = Eae->size[0];
      emxEnsureCapacity((emxArray__common *)c_y, i30, (int)sizeof(double));
      n = Eae->size[0];
      for (i30 = 0; i30 < n; i30++) {
        c_y->data[i30] = 0.0;
        loop_ub = Eae->size[1];
        for (i31 = 0; i31 < loop_ub; i31++) {
          c_y->data[i30] += Eae->data[i30 + Eae->size[0] * i31] * b_Bd->data[i31];
        }
      }
    }

    emxFree_real_T(&b_Bd);
    emxInit_real_T(&c_Bd, 2);
    emxInit_real_T1(&d_Bd, 1);
    n = Bd->size[0];
    i30 = d_Bd->size[0];
    d_Bd->size[0] = n;
    emxEnsureCapacity((emxArray__common *)d_Bd, i30, (int)sizeof(double));
    for (i30 = 0; i30 < n; i30++) {
      d_Bd->data[i30] = -Bd->data[i30];
    }

    emxInit_real_T(&e_Bd, 2);
    emxInit_real_T(&d_y, 2);
    i30 = e_Bd->size[0] * e_Bd->size[1];
    e_Bd->size[0] = d_Bd->size[0];
    e_Bd->size[1] = L->size[0];
    emxEnsureCapacity((emxArray__common *)e_Bd, i30, (int)sizeof(double));
    n = d_Bd->size[0];
    for (i30 = 0; i30 < n; i30++) {
      loop_ub = L->size[0];
      for (i31 = 0; i31 < loop_ub; i31++) {
        e_Bd->data[i30 + e_Bd->size[0] * i31] = d_Bd->data[i30] * L->data[i31];
      }
    }

    emxFree_real_T(&d_Bd);
    i30 = d_y->size[0] * d_y->size[1];
    d_y->size[0] = c_y->size[0];
    d_y->size[1] = L0->size[0];
    emxEnsureCapacity((emxArray__common *)d_y, i30, (int)sizeof(double));
    n = c_y->size[0];
    for (i30 = 0; i30 < n; i30++) {
      loop_ub = L0->size[0];
      for (i31 = 0; i31 < loop_ub; i31++) {
        d_y->data[i30 + d_y->size[0] * i31] = c_y->data[i30] * L0->data[i31];
      }
    }

    emxFree_real_T(&c_y);
    i30 = c_Bd->size[0] * c_Bd->size[1];
    c_Bd->size[0] = e_Bd->size[0];
    c_Bd->size[1] = e_Bd->size[1];
    emxEnsureCapacity((emxArray__common *)c_Bd, i30, (int)sizeof(double));
    n = e_Bd->size[1];
    for (i30 = 0; i30 < n; i30++) {
      loop_ub = e_Bd->size[0];
      for (i31 = 0; i31 < loop_ub; i31++) {
        c_Bd->data[i31 + c_Bd->size[0] * i30] = e_Bd->data[i31 + e_Bd->size[0] *
          i30] + d_y->data[i31 + d_y->size[0] * i30];
      }
    }

    emxFree_real_T(&d_y);
    emxFree_real_T(&e_Bd);
    Iint(A, p->data[0], c_Bd, Eap);
    emxFree_real_T(&c_Bd);
    n = Eap->size[1];
    for (i30 = 0; i30 < n; i30++) {
      loop_ub = Eap->size[0];
      for (i31 = 0; i31 < loop_ub; i31++) {
        S_in_d->data[i31 + S_in_d->size[0] * i30] = Eap->data[i31 + Eap->size[0]
          * i30];
      }
    }
  }

  /*  dla wektora B o kilku kolumnach */
  jj = 1;
  emxInit_real_T1(&e_y, 1);
  emxInit_real_T(&f_B, 2);
  emxInit_real_T(&c_Al, 2);
  emxInit_real_T1(&g_B, 1);
  emxInit_real_T1(&h_B, 1);
  emxInit_real_T(&i_B, 2);
  emxInit_real_T(&f_y, 2);
  while (jj - 1 <= n_in) {
    /* jj, n_in */
    lagc(p->data[jj], N->data[jj], Al, L0);
    i30 = c_Al->size[0] * c_Al->size[1];
    c_Al->size[0] = Al->size[0];
    c_Al->size[1] = Al->size[1];
    emxEnsureCapacity((emxArray__common *)c_Al, i30, (int)sizeof(double));
    n = Al->size[0] * Al->size[1];
    for (i30 = 0; i30 < n; i30++) {
      c_Al->data[i30] = Al->data[i30] * tau_del;
    }

    expm(c_Al, Eap);
    if ((Eap->size[1] == 1) || (L0->size[0] == 1)) {
      i30 = L->size[0];
      L->size[0] = Eap->size[0];
      emxEnsureCapacity((emxArray__common *)L, i30, (int)sizeof(double));
      n = Eap->size[0];
      for (i30 = 0; i30 < n; i30++) {
        L->data[i30] = 0.0;
        loop_ub = Eap->size[1];
        for (i31 = 0; i31 < loop_ub; i31++) {
          L->data[i30] += Eap->data[i30 + Eap->size[0] * i31] * L0->data[i31];
        }
      }
    } else {
      k = Eap->size[1];
      Eap_idx_0 = (unsigned int)Eap->size[0];
      i30 = L->size[0];
      L->size[0] = (int)Eap_idx_0;
      emxEnsureCapacity((emxArray__common *)L, i30, (int)sizeof(double));
      m = Eap->size[0];
      ixstart = L->size[0];
      i30 = L->size[0];
      L->size[0] = ixstart;
      emxEnsureCapacity((emxArray__common *)L, i30, (int)sizeof(double));
      for (i30 = 0; i30 < ixstart; i30++) {
        L->data[i30] = 0.0;
      }

      if (Eap->size[0] == 0) {
      } else {
        ix = 0;
        while ((m > 0) && (ix <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            L->data[ic - 1] = 0.0;
          }

          ix = m;
        }

        n = 0;
        ix = 0;
        while ((m > 0) && (ix <= 0)) {
          ar = 0;
          i30 = n + k;
          for (ib = n; ib + 1 <= i30; ib++) {
            if (L0->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                L->data[ic] += L0->data[ib] * Eap->data[ia - 1];
              }
            }

            ar += m;
          }

          n += k;
          ix = m;
        }
      }
    }

    guard4 = false;
    if (Eae->size[1] == 1) {
      guard4 = true;
    } else {
      i30 = B->size[0];
      if (i30 == 1) {
        guard4 = true;
      } else {
        k = Eae->size[1];
        Eap_idx_0 = (unsigned int)Eae->size[0];
        i30 = e_y->size[0];
        e_y->size[0] = (int)Eap_idx_0;
        emxEnsureCapacity((emxArray__common *)e_y, i30, (int)sizeof(double));
        m = Eae->size[0];
        ixstart = e_y->size[0];
        i30 = e_y->size[0];
        e_y->size[0] = ixstart;
        emxEnsureCapacity((emxArray__common *)e_y, i30, (int)sizeof(double));
        for (i30 = 0; i30 < ixstart; i30++) {
          e_y->data[i30] = 0.0;
        }

        if (Eae->size[0] == 0) {
        } else {
          ix = 0;
          while ((m > 0) && (ix <= 0)) {
            for (ic = 1; ic <= m; ic++) {
              e_y->data[ic - 1] = 0.0;
            }

            ix = m;
          }

          n = 0;
          ix = 0;
          while ((m > 0) && (ix <= 0)) {
            ar = 0;
            i30 = n + k;
            for (ib = n; ib + 1 <= i30; ib++) {
              if (B->data[ib + B->size[0] * jj] != 0.0) {
                ia = ar;
                for (ic = 0; ic + 1 <= m; ic++) {
                  ia++;
                  e_y->data[ic] += B->data[ib + B->size[0] * jj] * Eae->data[ia
                    - 1];
                }
              }

              ar += m;
            }

            n += k;
            ix = m;
          }
        }
      }
    }

    if (guard4) {
      n = B->size[0];
      i30 = g_B->size[0];
      g_B->size[0] = n;
      emxEnsureCapacity((emxArray__common *)g_B, i30, (int)sizeof(double));
      for (i30 = 0; i30 < n; i30++) {
        g_B->data[i30] = B->data[i30 + B->size[0] * jj];
      }

      i30 = e_y->size[0];
      e_y->size[0] = Eae->size[0];
      emxEnsureCapacity((emxArray__common *)e_y, i30, (int)sizeof(double));
      n = Eae->size[0];
      for (i30 = 0; i30 < n; i30++) {
        e_y->data[i30] = 0.0;
        loop_ub = Eae->size[1];
        for (i31 = 0; i31 < loop_ub; i31++) {
          e_y->data[i30] += Eae->data[i30 + Eae->size[0] * i31] * g_B->data[i31];
        }
      }
    }

    n = B->size[0];
    i30 = h_B->size[0];
    h_B->size[0] = n;
    emxEnsureCapacity((emxArray__common *)h_B, i30, (int)sizeof(double));
    for (i30 = 0; i30 < n; i30++) {
      h_B->data[i30] = -B->data[i30 + B->size[0] * jj];
    }

    i30 = i_B->size[0] * i_B->size[1];
    i_B->size[0] = h_B->size[0];
    i_B->size[1] = L->size[0];
    emxEnsureCapacity((emxArray__common *)i_B, i30, (int)sizeof(double));
    n = h_B->size[0];
    for (i30 = 0; i30 < n; i30++) {
      loop_ub = L->size[0];
      for (i31 = 0; i31 < loop_ub; i31++) {
        i_B->data[i30 + i_B->size[0] * i31] = h_B->data[i30] * L->data[i31];
      }
    }

    i30 = f_y->size[0] * f_y->size[1];
    f_y->size[0] = e_y->size[0];
    f_y->size[1] = L0->size[0];
    emxEnsureCapacity((emxArray__common *)f_y, i30, (int)sizeof(double));
    n = e_y->size[0];
    for (i30 = 0; i30 < n; i30++) {
      loop_ub = L0->size[0];
      for (i31 = 0; i31 < loop_ub; i31++) {
        f_y->data[i30 + f_y->size[0] * i31] = e_y->data[i30] * L0->data[i31];
      }
    }

    i30 = f_B->size[0] * f_B->size[1];
    f_B->size[0] = i_B->size[0];
    f_B->size[1] = i_B->size[1];
    emxEnsureCapacity((emxArray__common *)f_B, i30, (int)sizeof(double));
    n = i_B->size[1];
    for (i30 = 0; i30 < n; i30++) {
      loop_ub = i_B->size[0];
      for (i31 = 0; i31 < loop_ub; i31++) {
        f_B->data[i31 + f_B->size[0] * i30] = i_B->data[i31 + i_B->size[0] * i30]
          + f_y->data[i31 + f_y->size[0] * i30];
      }
    }

    Iint(A, p->data[jj], f_B, Eap);

    /* pierwsze wywo³anie Iinit */
    In_s += N->data[jj - 1];
    In_e = (In_s + N->data[jj]) - 1.0;
    if (In_s > In_e) {
      i30 = 0;
    } else {
      i30 = (int)In_s - 1;
    }

    n = Eap->size[1];
    for (i31 = 0; i31 < n; i31++) {
      loop_ub = Eap->size[0];
      for (i32 = 0; i32 < loop_ub; i32++) {
        S_in->data[i32 + S_in->size[0] * (i30 + i31)] = Eap->data[i32 +
          Eap->size[0] * i31];
      }
    }

    /* liczone tylko raz i siê nie zmienia - dla pojedynczego czasu h */
    /* if ~isempty(Bd) */
    /*     S_in_d(:,In_s:In_e)=zeros(size(Xd,1),In_e-In_s+1); */
    /* end */
    jj++;
  }

  emxFree_real_T(&f_y);
  emxFree_real_T(&i_B);
  emxFree_real_T(&h_B);
  emxFree_real_T(&g_B);
  emxFree_real_T(&c_Al);
  emxFree_real_T(&f_B);
  emxFree_real_T(&e_y);
  emxFree_real_T(&L);
  emxInit_real_T(&S_sum, 2);
  i30 = S_sum->size[0] * S_sum->size[1];
  S_sum->size[0] = S_in->size[0];
  S_sum->size[1] = S_in->size[1];
  emxEnsureCapacity((emxArray__common *)S_sum, i30, (int)sizeof(double));
  n = S_in->size[0] * S_in->size[1];
  for (i30 = 0; i30 < n; i30++) {
    S_sum->data[i30] = S_in->data[i30];
  }

  /* update w ka¿dej iteracji */
  if (!without_ff) {
    i30 = S_sum_d->size[0] * S_sum_d->size[1];
    S_sum_d->size[0] = S_in_d->size[0];
    S_sum_d->size[1] = S_in_d->size[1];
    emxEnsureCapacity((emxArray__common *)S_sum_d, i30, (int)sizeof(double));
    n = S_in_d->size[0] * S_in_d->size[1];
    for (i30 = 0; i30 < n; i30++) {
      S_sum_d->data[i30] = S_in_d->data[i30];
    }
  }

  i = 0;
  emxInit_real_T(&C, 2);
  emxInit_real_T(&b_C, 2);
  emxInit_real_T(&c_C, 2);
  emxInit_real_T(&d_C, 2);
  emxInit_real_T(&e_C, 2);
  emxInit_real_T(&f_C, 2);
  emxInit_real_T(&g_C, 2);
  emxInit_real_T(&h_C, 2);
  emxInit_real_T(&i_C, 2);
  emxInit_real_T(&b, 2);
  emxInit_real_T(&g_y, 2);
  emxInit_real_T(&h_y, 2);
  emxInit_real_T(&i_y, 2);
  emxInit_real_T(&r19, 2);
  emxInit_real_T(&d_Al, 2);
  emxInit_real_T(&e_Al, 2);
  emxInit_real_T(&b_S_sum, 2);
  emxInit_real_T(&b_S_in, 2);
  emxInit_real_T(&b_S_sum_d, 2);
  emxInit_real_T(&b_S_in_d, 2);
  emxInit_real_T(&c_S_sum, 2);
  emxInit_real_T(&c_S_in, 2);
  while (i <= tau->size[1] - 3) {
    lagc(p->data[0], N->data[0], Al, L0);
    i30 = d_Al->size[0] * d_Al->size[1];
    d_Al->size[0] = Al->size[0];
    d_Al->size[1] = Al->size[1];
    emxEnsureCapacity((emxArray__common *)d_Al, i30, (int)sizeof(double));
    n = Al->size[0] * Al->size[1];
    for (i30 = 0; i30 < n; i30++) {
      d_Al->data[i30] = Al->data[i30] * tau_del;
    }

    expm(d_Al, Eap);
    if (1.0 > N->data[0]) {
      n = 0;
    } else {
      n = (int)N->data[0];
    }

    if (1.0 > N->data[0]) {
      loop_ub = 0;
    } else {
      loop_ub = (int)N->data[0];
    }

    guard3 = false;
    if (Eae->size[1] == 1) {
      guard3 = true;
    } else {
      i30 = S_sum->size[0];
      if (i30 == 1) {
        guard3 = true;
      } else {
        k = Eae->size[1];
        Eap_idx_0 = (unsigned int)Eae->size[0];
        i30 = C->size[0] * C->size[1];
        C->size[0] = (int)Eap_idx_0;
        C->size[1] = n;
        emxEnsureCapacity((emxArray__common *)C, i30, (int)sizeof(double));
        m = Eae->size[0];
        i30 = C->size[0] * C->size[1];
        emxEnsureCapacity((emxArray__common *)C, i30, (int)sizeof(double));
        ix = C->size[1];
        for (i30 = 0; i30 < ix; i30++) {
          ixstart = C->size[0];
          for (i31 = 0; i31 < ixstart; i31++) {
            C->data[i31 + C->size[0] * i30] = 0.0;
          }
        }

        if ((Eae->size[0] == 0) || (n == 0)) {
        } else {
          ixstart = Eae->size[0] * (n - 1);
          ix = 0;
          while ((m > 0) && (ix <= ixstart)) {
            i30 = ix + m;
            for (ic = ix; ic + 1 <= i30; ic++) {
              C->data[ic] = 0.0;
            }

            ix += m;
          }

          n = 0;
          ix = 0;
          while ((m > 0) && (ix <= ixstart)) {
            ar = 0;
            i30 = n + k;
            for (ib = n; ib + 1 <= i30; ib++) {
              i31 = S_sum->size[0];
              if (S_sum->data[ib % i31 + S_sum->size[0] * (ib / i31)] != 0.0) {
                ia = ar;
                i31 = ix + m;
                for (ic = ix; ic + 1 <= i31; ic++) {
                  ia++;
                  i32 = S_sum->size[0];
                  C->data[ic] += S_sum->data[ib % i32 + S_sum->size[0] * (ib /
                    i32)] * Eae->data[ia - 1];
                }
              }

              ar += m;
            }

            n += k;
            ix += m;
          }
        }
      }
    }

    if (guard3) {
      ix = S_sum->size[0];
      i30 = b_S_sum->size[0] * b_S_sum->size[1];
      b_S_sum->size[0] = ix;
      b_S_sum->size[1] = n;
      emxEnsureCapacity((emxArray__common *)b_S_sum, i30, (int)sizeof(double));
      for (i30 = 0; i30 < n; i30++) {
        for (i31 = 0; i31 < ix; i31++) {
          b_S_sum->data[i31 + b_S_sum->size[0] * i30] = S_sum->data[i31 +
            S_sum->size[0] * i30];
        }
      }

      i30 = C->size[0] * C->size[1];
      C->size[0] = Eae->size[0];
      C->size[1] = b_S_sum->size[1];
      emxEnsureCapacity((emxArray__common *)C, i30, (int)sizeof(double));
      n = Eae->size[0];
      for (i30 = 0; i30 < n; i30++) {
        ix = b_S_sum->size[1];
        for (i31 = 0; i31 < ix; i31++) {
          C->data[i30 + C->size[0] * i31] = 0.0;
          ixstart = Eae->size[1];
          for (i32 = 0; i32 < ixstart; i32++) {
            C->data[i30 + C->size[0] * i31] += Eae->data[i30 + Eae->size[0] *
              i32] * b_S_sum->data[i32 + b_S_sum->size[0] * i31];
          }
        }
      }
    }

    mpower(Eap, (2.0 + (double)i) - 1.0, r19);
    i30 = b->size[0] * b->size[1];
    b->size[0] = r19->size[1];
    b->size[1] = r19->size[0];
    emxEnsureCapacity((emxArray__common *)b, i30, (int)sizeof(double));
    n = r19->size[0];
    for (i30 = 0; i30 < n; i30++) {
      ix = r19->size[1];
      for (i31 = 0; i31 < ix; i31++) {
        b->data[i31 + b->size[0] * i30] = r19->data[i30 + r19->size[0] * i31];
      }
    }

    if ((loop_ub == 1) || (b->size[0] == 1)) {
      n = S_in->size[0];
      i30 = b_S_in->size[0] * b_S_in->size[1];
      b_S_in->size[0] = n;
      b_S_in->size[1] = loop_ub;
      emxEnsureCapacity((emxArray__common *)b_S_in, i30, (int)sizeof(double));
      for (i30 = 0; i30 < loop_ub; i30++) {
        for (i31 = 0; i31 < n; i31++) {
          b_S_in->data[i31 + b_S_in->size[0] * i30] = S_in->data[i31 +
            S_in->size[0] * i30];
        }
      }

      i30 = b_C->size[0] * b_C->size[1];
      b_C->size[0] = b_S_in->size[0];
      b_C->size[1] = b->size[1];
      emxEnsureCapacity((emxArray__common *)b_C, i30, (int)sizeof(double));
      n = b_S_in->size[0];
      for (i30 = 0; i30 < n; i30++) {
        loop_ub = b->size[1];
        for (i31 = 0; i31 < loop_ub; i31++) {
          b_C->data[i30 + b_C->size[0] * i31] = 0.0;
          ix = b_S_in->size[1];
          for (i32 = 0; i32 < ix; i32++) {
            b_C->data[i30 + b_C->size[0] * i31] += b_S_in->data[i30 +
              b_S_in->size[0] * i32] * b->data[i32 + b->size[0] * i31];
          }
        }
      }
    } else {
      i30 = S_in->size[0];
      unnamed_idx_1 = (unsigned int)b->size[1];
      i31 = b_C->size[0] * b_C->size[1];
      b_C->size[0] = i30;
      b_C->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)b_C, i31, (int)sizeof(double));
      i30 = S_in->size[0];
      i31 = b_C->size[0] * b_C->size[1];
      emxEnsureCapacity((emxArray__common *)b_C, i31, (int)sizeof(double));
      n = b_C->size[1];
      for (i31 = 0; i31 < n; i31++) {
        ix = b_C->size[0];
        for (i32 = 0; i32 < ix; i32++) {
          b_C->data[i32 + b_C->size[0] * i31] = 0.0;
        }
      }

      i31 = S_in->size[0];
      if ((i31 == 0) || (b->size[1] == 0)) {
      } else {
        i31 = S_in->size[0];
        ixstart = i31 * (b->size[1] - 1);
        ix = 0;
        while ((i30 > 0) && (ix <= ixstart)) {
          i31 = ix + i30;
          for (ic = ix; ic + 1 <= i31; ic++) {
            b_C->data[ic] = 0.0;
          }

          ix += i30;
        }

        n = 0;
        ix = 0;
        while ((i30 > 0) && (ix <= ixstart)) {
          ar = 0;
          i31 = n + loop_ub;
          for (ib = n; ib + 1 <= i31; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              i32 = ix + i30;
              for (ic = ix; ic + 1 <= i32; ic++) {
                ia++;
                i33 = S_in->size[0];
                b_C->data[ic] += b->data[ib] * S_in->data[(ia - 1) % i33 +
                  S_in->size[0] * ((ia - 1) / i33)];
              }
            }

            ar += i30;
          }

          n += loop_ub;
          ix += i30;
        }
      }
    }

    n = C->size[1];
    for (i30 = 0; i30 < n; i30++) {
      loop_ub = C->size[0];
      for (i31 = 0; i31 < loop_ub; i31++) {
        S_sum->data[i31 + S_sum->size[0] * i30] = C->data[i31 + C->size[0] * i30]
          + b_C->data[i31 + b_C->size[0] * i30];
      }
    }

    if (!without_ff) {
      if (1.0 > N->data[0]) {
        n = 0;
      } else {
        n = (int)N->data[0];
      }

      if (1.0 > N->data[0]) {
        loop_ub = 0;
      } else {
        loop_ub = (int)N->data[0];
      }

      guard2 = false;
      if (Eae->size[1] == 1) {
        guard2 = true;
      } else {
        i30 = S_sum_d->size[0];
        if (i30 == 1) {
          guard2 = true;
        } else {
          k = Eae->size[1];
          Eap_idx_0 = (unsigned int)Eae->size[0];
          i30 = c_C->size[0] * c_C->size[1];
          c_C->size[0] = (int)Eap_idx_0;
          c_C->size[1] = n;
          emxEnsureCapacity((emxArray__common *)c_C, i30, (int)sizeof(double));
          m = Eae->size[0];
          i30 = c_C->size[0] * c_C->size[1];
          emxEnsureCapacity((emxArray__common *)c_C, i30, (int)sizeof(double));
          ix = c_C->size[1];
          for (i30 = 0; i30 < ix; i30++) {
            ixstart = c_C->size[0];
            for (i31 = 0; i31 < ixstart; i31++) {
              c_C->data[i31 + c_C->size[0] * i30] = 0.0;
            }
          }

          if ((Eae->size[0] == 0) || (n == 0)) {
          } else {
            ixstart = Eae->size[0] * (n - 1);
            ix = 0;
            while ((m > 0) && (ix <= ixstart)) {
              i30 = ix + m;
              for (ic = ix; ic + 1 <= i30; ic++) {
                c_C->data[ic] = 0.0;
              }

              ix += m;
            }

            n = 0;
            ix = 0;
            while ((m > 0) && (ix <= ixstart)) {
              ar = 0;
              i30 = n + k;
              for (ib = n; ib + 1 <= i30; ib++) {
                i31 = S_sum_d->size[0];
                if (S_sum_d->data[ib % i31 + S_sum_d->size[0] * (ib / i31)] !=
                    0.0) {
                  ia = ar;
                  i31 = ix + m;
                  for (ic = ix; ic + 1 <= i31; ic++) {
                    ia++;
                    i32 = S_sum_d->size[0];
                    c_C->data[ic] += S_sum_d->data[ib % i32 + S_sum_d->size[0] *
                      (ib / i32)] * Eae->data[ia - 1];
                  }
                }

                ar += m;
              }

              n += k;
              ix += m;
            }
          }
        }
      }

      if (guard2) {
        ix = S_sum_d->size[0];
        i30 = b_S_sum_d->size[0] * b_S_sum_d->size[1];
        b_S_sum_d->size[0] = ix;
        b_S_sum_d->size[1] = n;
        emxEnsureCapacity((emxArray__common *)b_S_sum_d, i30, (int)sizeof(double));
        for (i30 = 0; i30 < n; i30++) {
          for (i31 = 0; i31 < ix; i31++) {
            b_S_sum_d->data[i31 + b_S_sum_d->size[0] * i30] = S_sum_d->data[i31
              + S_sum_d->size[0] * i30];
          }
        }

        i30 = c_C->size[0] * c_C->size[1];
        c_C->size[0] = Eae->size[0];
        c_C->size[1] = b_S_sum_d->size[1];
        emxEnsureCapacity((emxArray__common *)c_C, i30, (int)sizeof(double));
        n = Eae->size[0];
        for (i30 = 0; i30 < n; i30++) {
          ix = b_S_sum_d->size[1];
          for (i31 = 0; i31 < ix; i31++) {
            c_C->data[i30 + c_C->size[0] * i31] = 0.0;
            ixstart = Eae->size[1];
            for (i32 = 0; i32 < ixstart; i32++) {
              c_C->data[i30 + c_C->size[0] * i31] += Eae->data[i30 + Eae->size[0]
                * i32] * b_S_sum_d->data[i32 + b_S_sum_d->size[0] * i31];
            }
          }
        }
      }

      mpower(Eap, (2.0 + (double)i) - 1.0, r19);
      i30 = b->size[0] * b->size[1];
      b->size[0] = r19->size[1];
      b->size[1] = r19->size[0];
      emxEnsureCapacity((emxArray__common *)b, i30, (int)sizeof(double));
      n = r19->size[0];
      for (i30 = 0; i30 < n; i30++) {
        ix = r19->size[1];
        for (i31 = 0; i31 < ix; i31++) {
          b->data[i31 + b->size[0] * i30] = r19->data[i30 + r19->size[0] * i31];
        }
      }

      if ((loop_ub == 1) || (b->size[0] == 1)) {
        n = S_in_d->size[0];
        i30 = b_S_in_d->size[0] * b_S_in_d->size[1];
        b_S_in_d->size[0] = n;
        b_S_in_d->size[1] = loop_ub;
        emxEnsureCapacity((emxArray__common *)b_S_in_d, i30, (int)sizeof(double));
        for (i30 = 0; i30 < loop_ub; i30++) {
          for (i31 = 0; i31 < n; i31++) {
            b_S_in_d->data[i31 + b_S_in_d->size[0] * i30] = S_in_d->data[i31 +
              S_in_d->size[0] * i30];
          }
        }

        i30 = d_C->size[0] * d_C->size[1];
        d_C->size[0] = b_S_in_d->size[0];
        d_C->size[1] = b->size[1];
        emxEnsureCapacity((emxArray__common *)d_C, i30, (int)sizeof(double));
        n = b_S_in_d->size[0];
        for (i30 = 0; i30 < n; i30++) {
          loop_ub = b->size[1];
          for (i31 = 0; i31 < loop_ub; i31++) {
            d_C->data[i30 + d_C->size[0] * i31] = 0.0;
            ix = b_S_in_d->size[1];
            for (i32 = 0; i32 < ix; i32++) {
              d_C->data[i30 + d_C->size[0] * i31] += b_S_in_d->data[i30 +
                b_S_in_d->size[0] * i32] * b->data[i32 + b->size[0] * i31];
            }
          }
        }
      } else {
        i30 = S_in_d->size[0];
        unnamed_idx_1 = (unsigned int)b->size[1];
        i31 = d_C->size[0] * d_C->size[1];
        d_C->size[0] = i30;
        d_C->size[1] = (int)unnamed_idx_1;
        emxEnsureCapacity((emxArray__common *)d_C, i31, (int)sizeof(double));
        i30 = S_in_d->size[0];
        i31 = d_C->size[0] * d_C->size[1];
        emxEnsureCapacity((emxArray__common *)d_C, i31, (int)sizeof(double));
        n = d_C->size[1];
        for (i31 = 0; i31 < n; i31++) {
          ix = d_C->size[0];
          for (i32 = 0; i32 < ix; i32++) {
            d_C->data[i32 + d_C->size[0] * i31] = 0.0;
          }
        }

        i31 = S_in_d->size[0];
        if ((i31 == 0) || (b->size[1] == 0)) {
        } else {
          i31 = S_in_d->size[0];
          ixstart = i31 * (b->size[1] - 1);
          ix = 0;
          while ((i30 > 0) && (ix <= ixstart)) {
            i31 = ix + i30;
            for (ic = ix; ic + 1 <= i31; ic++) {
              d_C->data[ic] = 0.0;
            }

            ix += i30;
          }

          n = 0;
          ix = 0;
          while ((i30 > 0) && (ix <= ixstart)) {
            ar = 0;
            i31 = n + loop_ub;
            for (ib = n; ib + 1 <= i31; ib++) {
              if (b->data[ib] != 0.0) {
                ia = ar;
                i32 = ix + i30;
                for (ic = ix; ic + 1 <= i32; ic++) {
                  ia++;
                  i33 = S_in_d->size[0];
                  d_C->data[ic] += b->data[ib] * S_in_d->data[(ia - 1) % i33 +
                    S_in_d->size[0] * ((ia - 1) / i33)];
                }
              }

              ar += i30;
            }

            n += loop_ub;
            ix += i30;
          }
        }
      }

      n = c_C->size[1];
      for (i30 = 0; i30 < n; i30++) {
        loop_ub = c_C->size[0];
        for (i31 = 0; i31 < loop_ub; i31++) {
          S_sum_d->data[i31 + S_sum_d->size[0] * i30] = c_C->data[i31 +
            c_C->size[0] * i30] + d_C->data[i31 + d_C->size[0] * i30];
        }
      }
    }

    In_s = 1.0;

    /*  dla wektora B o kilku kolumnach */
    for (b_kk = 1; b_kk - 1 <= n_in; b_kk++) {
      lagc(p->data[b_kk], N->data[b_kk], Al, L0);
      i30 = e_Al->size[0] * e_Al->size[1];
      e_Al->size[0] = Al->size[0];
      e_Al->size[1] = Al->size[1];
      emxEnsureCapacity((emxArray__common *)e_Al, i30, (int)sizeof(double));
      n = Al->size[0] * Al->size[1];
      for (i30 = 0; i30 < n; i30++) {
        e_Al->data[i30] = Al->data[i30] * tau_del;
      }

      expm(e_Al, Eap);
      In_s += N->data[b_kk - 1];
      In_e = (In_s + N->data[b_kk]) - 1.0;
      if (In_s > In_e) {
        i30 = 0;
        i31 = 0;
      } else {
        i30 = (int)In_s - 1;
        i31 = (int)In_e;
      }

      if (In_s > In_e) {
        i32 = 0;
        i33 = 0;
      } else {
        i32 = (int)In_s - 1;
        i33 = (int)In_e;
      }

      guard1 = false;
      if (Eae->size[1] == 1) {
        guard1 = true;
      } else {
        i34 = S_sum->size[0];
        if (i34 == 1) {
          guard1 = true;
        } else {
          k = Eae->size[1];
          Eap_idx_0 = (unsigned int)Eae->size[0];
          i34 = e_C->size[0] * e_C->size[1];
          e_C->size[0] = (int)Eap_idx_0;
          e_C->size[1] = i31 - i30;
          emxEnsureCapacity((emxArray__common *)e_C, i34, (int)sizeof(double));
          m = Eae->size[0];
          i34 = e_C->size[0] * e_C->size[1];
          emxEnsureCapacity((emxArray__common *)e_C, i34, (int)sizeof(double));
          n = e_C->size[1];
          for (i34 = 0; i34 < n; i34++) {
            loop_ub = e_C->size[0];
            for (i35 = 0; i35 < loop_ub; i35++) {
              e_C->data[i35 + e_C->size[0] * i34] = 0.0;
            }
          }

          if ((Eae->size[0] == 0) || (i31 - i30 == 0)) {
          } else {
            ixstart = Eae->size[0] * ((i31 - i30) - 1);
            ix = 0;
            while ((m > 0) && (ix <= ixstart)) {
              i31 = ix + m;
              for (ic = ix; ic + 1 <= i31; ic++) {
                e_C->data[ic] = 0.0;
              }

              ix += m;
            }

            n = 0;
            ix = 0;
            while ((m > 0) && (ix <= ixstart)) {
              ar = 0;
              i31 = n + k;
              for (ib = n; ib + 1 <= i31; ib++) {
                i34 = S_sum->size[0];
                if (S_sum->data[ib % i34 + S_sum->size[0] * (i30 + ib / i34)] !=
                    0.0) {
                  ia = ar;
                  i34 = ix + m;
                  for (ic = ix; ic + 1 <= i34; ic++) {
                    ia++;
                    i35 = S_sum->size[0];
                    e_C->data[ic] += S_sum->data[ib % i35 + S_sum->size[0] *
                      (i30 + ib / i35)] * Eae->data[ia - 1];
                  }
                }

                ar += m;
              }

              n += k;
              ix += m;
            }
          }
        }
      }

      if (guard1) {
        n = S_sum->size[0];
        i34 = c_S_sum->size[0] * c_S_sum->size[1];
        c_S_sum->size[0] = n;
        c_S_sum->size[1] = i31 - i30;
        emxEnsureCapacity((emxArray__common *)c_S_sum, i34, (int)sizeof(double));
        loop_ub = i31 - i30;
        for (i31 = 0; i31 < loop_ub; i31++) {
          for (i34 = 0; i34 < n; i34++) {
            c_S_sum->data[i34 + c_S_sum->size[0] * i31] = S_sum->data[i34 +
              S_sum->size[0] * (i30 + i31)];
          }
        }

        i30 = e_C->size[0] * e_C->size[1];
        e_C->size[0] = Eae->size[0];
        e_C->size[1] = c_S_sum->size[1];
        emxEnsureCapacity((emxArray__common *)e_C, i30, (int)sizeof(double));
        n = Eae->size[0];
        for (i30 = 0; i30 < n; i30++) {
          loop_ub = c_S_sum->size[1];
          for (i31 = 0; i31 < loop_ub; i31++) {
            e_C->data[i30 + e_C->size[0] * i31] = 0.0;
            ix = Eae->size[1];
            for (i34 = 0; i34 < ix; i34++) {
              e_C->data[i30 + e_C->size[0] * i31] += Eae->data[i30 + Eae->size[0]
                * i34] * c_S_sum->data[i34 + c_S_sum->size[0] * i31];
            }
          }
        }
      }

      mpower(Eap, (2.0 + (double)i) - 1.0, r19);
      i30 = b->size[0] * b->size[1];
      b->size[0] = r19->size[1];
      b->size[1] = r19->size[0];
      emxEnsureCapacity((emxArray__common *)b, i30, (int)sizeof(double));
      n = r19->size[0];
      for (i30 = 0; i30 < n; i30++) {
        loop_ub = r19->size[1];
        for (i31 = 0; i31 < loop_ub; i31++) {
          b->data[i31 + b->size[0] * i30] = r19->data[i30 + r19->size[0] * i31];
        }
      }

      if ((i33 - i32 == 1) || (b->size[0] == 1)) {
        n = S_in->size[0];
        i30 = c_S_in->size[0] * c_S_in->size[1];
        c_S_in->size[0] = n;
        c_S_in->size[1] = i33 - i32;
        emxEnsureCapacity((emxArray__common *)c_S_in, i30, (int)sizeof(double));
        loop_ub = i33 - i32;
        for (i30 = 0; i30 < loop_ub; i30++) {
          for (i31 = 0; i31 < n; i31++) {
            c_S_in->data[i31 + c_S_in->size[0] * i30] = S_in->data[i31 +
              S_in->size[0] * (i32 + i30)];
          }
        }

        i30 = f_C->size[0] * f_C->size[1];
        f_C->size[0] = c_S_in->size[0];
        f_C->size[1] = b->size[1];
        emxEnsureCapacity((emxArray__common *)f_C, i30, (int)sizeof(double));
        n = c_S_in->size[0];
        for (i30 = 0; i30 < n; i30++) {
          loop_ub = b->size[1];
          for (i31 = 0; i31 < loop_ub; i31++) {
            f_C->data[i30 + f_C->size[0] * i31] = 0.0;
            ix = c_S_in->size[1];
            for (i32 = 0; i32 < ix; i32++) {
              f_C->data[i30 + f_C->size[0] * i31] += c_S_in->data[i30 +
                c_S_in->size[0] * i32] * b->data[i32 + b->size[0] * i31];
            }
          }
        }
      } else {
        k = i33 - i32;
        i30 = S_in->size[0];
        unnamed_idx_1 = (unsigned int)b->size[1];
        i31 = f_C->size[0] * f_C->size[1];
        f_C->size[0] = i30;
        f_C->size[1] = (int)unnamed_idx_1;
        emxEnsureCapacity((emxArray__common *)f_C, i31, (int)sizeof(double));
        i30 = S_in->size[0];
        i31 = f_C->size[0] * f_C->size[1];
        emxEnsureCapacity((emxArray__common *)f_C, i31, (int)sizeof(double));
        n = f_C->size[1];
        for (i31 = 0; i31 < n; i31++) {
          loop_ub = f_C->size[0];
          for (i33 = 0; i33 < loop_ub; i33++) {
            f_C->data[i33 + f_C->size[0] * i31] = 0.0;
          }
        }

        i31 = S_in->size[0];
        if ((i31 == 0) || (b->size[1] == 0)) {
        } else {
          i31 = S_in->size[0];
          ixstart = i31 * (b->size[1] - 1);
          ix = 0;
          while ((i30 > 0) && (ix <= ixstart)) {
            i31 = ix + i30;
            for (ic = ix; ic + 1 <= i31; ic++) {
              f_C->data[ic] = 0.0;
            }

            ix += i30;
          }

          n = 0;
          ix = 0;
          while ((i30 > 0) && (ix <= ixstart)) {
            ar = 0;
            i31 = n + k;
            for (ib = n; ib + 1 <= i31; ib++) {
              if (b->data[ib] != 0.0) {
                ia = ar;
                i33 = ix + i30;
                for (ic = ix; ic + 1 <= i33; ic++) {
                  ia++;
                  i34 = S_in->size[0];
                  f_C->data[ic] += b->data[ib] * S_in->data[(ia - 1) % i34 +
                    S_in->size[0] * (i32 + (ia - 1) / i34)];
                }
              }

              ar += i30;
            }

            n += k;
            ix += i30;
          }
        }
      }

      if (In_s > In_e) {
        i30 = 0;
      } else {
        i30 = (int)In_s - 1;
      }

      n = e_C->size[1];
      for (i31 = 0; i31 < n; i31++) {
        loop_ub = e_C->size[0];
        for (i32 = 0; i32 < loop_ub; i32++) {
          S_sum->data[i32 + S_sum->size[0] * (i30 + i31)] = e_C->data[i32 +
            e_C->size[0] * i31] + f_C->data[i32 + f_C->size[0] * i31];
        }
      }
    }

    if (!without_ff) {
      i30 = Eap->size[0] * Eap->size[1];
      Eap->size[0] = S_sum->size[1];
      Eap->size[1] = S_sum->size[0];
      emxEnsureCapacity((emxArray__common *)Eap, i30, (int)sizeof(double));
      n = S_sum->size[0];
      for (i30 = 0; i30 < n; i30++) {
        loop_ub = S_sum->size[1];
        for (i31 = 0; i31 < loop_ub; i31++) {
          Eap->data[i31 + Eap->size[0] * i30] = S_sum->data[i30 + S_sum->size[0]
            * i31];
        }
      }

      if ((Eap->size[1] == 1) || (Q->size[0] == 1)) {
        i30 = g_y->size[0] * g_y->size[1];
        g_y->size[0] = Eap->size[0];
        g_y->size[1] = Q->size[1];
        emxEnsureCapacity((emxArray__common *)g_y, i30, (int)sizeof(double));
        n = Eap->size[0];
        for (i30 = 0; i30 < n; i30++) {
          loop_ub = Q->size[1];
          for (i31 = 0; i31 < loop_ub; i31++) {
            g_y->data[i30 + g_y->size[0] * i31] = 0.0;
            ix = Eap->size[1];
            for (i32 = 0; i32 < ix; i32++) {
              g_y->data[i30 + g_y->size[0] * i31] += Eap->data[i30 + Eap->size[0]
                * i32] * Q->data[i32 + Q->size[0] * i31];
            }
          }
        }
      } else {
        k = Eap->size[1];
        Eap_idx_0 = (unsigned int)Eap->size[0];
        unnamed_idx_1 = (unsigned int)Q->size[1];
        i30 = g_y->size[0] * g_y->size[1];
        g_y->size[0] = (int)Eap_idx_0;
        g_y->size[1] = (int)unnamed_idx_1;
        emxEnsureCapacity((emxArray__common *)g_y, i30, (int)sizeof(double));
        m = Eap->size[0];
        i30 = g_y->size[0] * g_y->size[1];
        emxEnsureCapacity((emxArray__common *)g_y, i30, (int)sizeof(double));
        n = g_y->size[1];
        for (i30 = 0; i30 < n; i30++) {
          loop_ub = g_y->size[0];
          for (i31 = 0; i31 < loop_ub; i31++) {
            g_y->data[i31 + g_y->size[0] * i30] = 0.0;
          }
        }

        if ((Eap->size[0] == 0) || (Q->size[1] == 0)) {
        } else {
          ixstart = Eap->size[0] * (Q->size[1] - 1);
          ix = 0;
          while ((m > 0) && (ix <= ixstart)) {
            i30 = ix + m;
            for (ic = ix; ic + 1 <= i30; ic++) {
              g_y->data[ic] = 0.0;
            }

            ix += m;
          }

          n = 0;
          ix = 0;
          while ((m > 0) && (ix <= ixstart)) {
            ar = 0;
            i30 = n + k;
            for (ib = n; ib + 1 <= i30; ib++) {
              if (Q->data[ib] != 0.0) {
                ia = ar;
                i31 = ix + m;
                for (ic = ix; ic + 1 <= i31; ic++) {
                  ia++;
                  g_y->data[ic] += Q->data[ib] * Eap->data[ia - 1];
                }
              }

              ar += m;
            }

            n += k;
            ix += m;
          }
        }
      }

      if ((g_y->size[1] == 1) || (S_sum_d->size[0] == 1)) {
        i30 = g_C->size[0] * g_C->size[1];
        g_C->size[0] = g_y->size[0];
        g_C->size[1] = S_sum_d->size[1];
        emxEnsureCapacity((emxArray__common *)g_C, i30, (int)sizeof(double));
        n = g_y->size[0];
        for (i30 = 0; i30 < n; i30++) {
          loop_ub = S_sum_d->size[1];
          for (i31 = 0; i31 < loop_ub; i31++) {
            g_C->data[i30 + g_C->size[0] * i31] = 0.0;
            ix = g_y->size[1];
            for (i32 = 0; i32 < ix; i32++) {
              g_C->data[i30 + g_C->size[0] * i31] += g_y->data[i30 + g_y->size[0]
                * i32] * S_sum_d->data[i32 + S_sum_d->size[0] * i31];
            }
          }
        }
      } else {
        k = g_y->size[1];
        Eap_idx_0 = (unsigned int)g_y->size[0];
        unnamed_idx_1 = (unsigned int)S_sum_d->size[1];
        i30 = g_C->size[0] * g_C->size[1];
        g_C->size[0] = (int)Eap_idx_0;
        g_C->size[1] = (int)unnamed_idx_1;
        emxEnsureCapacity((emxArray__common *)g_C, i30, (int)sizeof(double));
        m = g_y->size[0];
        i30 = g_C->size[0] * g_C->size[1];
        emxEnsureCapacity((emxArray__common *)g_C, i30, (int)sizeof(double));
        n = g_C->size[1];
        for (i30 = 0; i30 < n; i30++) {
          loop_ub = g_C->size[0];
          for (i31 = 0; i31 < loop_ub; i31++) {
            g_C->data[i31 + g_C->size[0] * i30] = 0.0;
          }
        }

        if ((g_y->size[0] == 0) || (S_sum_d->size[1] == 0)) {
        } else {
          ixstart = g_y->size[0] * (S_sum_d->size[1] - 1);
          ix = 0;
          while ((m > 0) && (ix <= ixstart)) {
            i30 = ix + m;
            for (ic = ix; ic + 1 <= i30; ic++) {
              g_C->data[ic] = 0.0;
            }

            ix += m;
          }

          n = 0;
          ix = 0;
          while ((m > 0) && (ix <= ixstart)) {
            ar = 0;
            i30 = n + k;
            for (ib = n; ib + 1 <= i30; ib++) {
              if (S_sum_d->data[ib] != 0.0) {
                ia = ar;
                i31 = ix + m;
                for (ic = ix; ic + 1 <= i31; ic++) {
                  ia++;
                  g_C->data[ic] += S_sum_d->data[ib] * g_y->data[ia - 1];
                }
              }

              ar += m;
            }

            n += k;
            ix += m;
          }
        }
      }

      i30 = Gamma->size[0] * Gamma->size[1];
      emxEnsureCapacity((emxArray__common *)Gamma, i30, (int)sizeof(double));
      ixstart = Gamma->size[0];
      ix = Gamma->size[1];
      n = ixstart * ix;
      for (i30 = 0; i30 < n; i30++) {
        Gamma->data[i30] += g_C->data[i30];
      }
    }

    i30 = Eap->size[0] * Eap->size[1];
    Eap->size[0] = S_sum->size[1];
    Eap->size[1] = S_sum->size[0];
    emxEnsureCapacity((emxArray__common *)Eap, i30, (int)sizeof(double));
    n = S_sum->size[0];
    for (i30 = 0; i30 < n; i30++) {
      loop_ub = S_sum->size[1];
      for (i31 = 0; i31 < loop_ub; i31++) {
        Eap->data[i31 + Eap->size[0] * i30] = S_sum->data[i30 + S_sum->size[0] *
          i31];
      }
    }

    if ((Eap->size[1] == 1) || (Q->size[0] == 1)) {
      i30 = h_y->size[0] * h_y->size[1];
      h_y->size[0] = Eap->size[0];
      h_y->size[1] = Q->size[1];
      emxEnsureCapacity((emxArray__common *)h_y, i30, (int)sizeof(double));
      n = Eap->size[0];
      for (i30 = 0; i30 < n; i30++) {
        loop_ub = Q->size[1];
        for (i31 = 0; i31 < loop_ub; i31++) {
          h_y->data[i30 + h_y->size[0] * i31] = 0.0;
          ix = Eap->size[1];
          for (i32 = 0; i32 < ix; i32++) {
            h_y->data[i30 + h_y->size[0] * i31] += Eap->data[i30 + Eap->size[0] *
              i32] * Q->data[i32 + Q->size[0] * i31];
          }
        }
      }
    } else {
      k = Eap->size[1];
      Eap_idx_0 = (unsigned int)Eap->size[0];
      unnamed_idx_1 = (unsigned int)Q->size[1];
      i30 = h_y->size[0] * h_y->size[1];
      h_y->size[0] = (int)Eap_idx_0;
      h_y->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)h_y, i30, (int)sizeof(double));
      m = Eap->size[0];
      i30 = h_y->size[0] * h_y->size[1];
      emxEnsureCapacity((emxArray__common *)h_y, i30, (int)sizeof(double));
      n = h_y->size[1];
      for (i30 = 0; i30 < n; i30++) {
        loop_ub = h_y->size[0];
        for (i31 = 0; i31 < loop_ub; i31++) {
          h_y->data[i31 + h_y->size[0] * i30] = 0.0;
        }
      }

      if ((Eap->size[0] == 0) || (Q->size[1] == 0)) {
      } else {
        ixstart = Eap->size[0] * (Q->size[1] - 1);
        ix = 0;
        while ((m > 0) && (ix <= ixstart)) {
          i30 = ix + m;
          for (ic = ix; ic + 1 <= i30; ic++) {
            h_y->data[ic] = 0.0;
          }

          ix += m;
        }

        n = 0;
        ix = 0;
        while ((m > 0) && (ix <= ixstart)) {
          ar = 0;
          i30 = n + k;
          for (ib = n; ib + 1 <= i30; ib++) {
            if (Q->data[ib] != 0.0) {
              ia = ar;
              i31 = ix + m;
              for (ic = ix; ic + 1 <= i31; ic++) {
                ia++;
                h_y->data[ic] += Q->data[ib] * Eap->data[ia - 1];
              }
            }

            ar += m;
          }

          n += k;
          ix += m;
        }
      }
    }

    if ((h_y->size[1] == 1) || (S_sum->size[0] == 1)) {
      i30 = h_C->size[0] * h_C->size[1];
      h_C->size[0] = h_y->size[0];
      h_C->size[1] = S_sum->size[1];
      emxEnsureCapacity((emxArray__common *)h_C, i30, (int)sizeof(double));
      n = h_y->size[0];
      for (i30 = 0; i30 < n; i30++) {
        loop_ub = S_sum->size[1];
        for (i31 = 0; i31 < loop_ub; i31++) {
          h_C->data[i30 + h_C->size[0] * i31] = 0.0;
          ix = h_y->size[1];
          for (i32 = 0; i32 < ix; i32++) {
            h_C->data[i30 + h_C->size[0] * i31] += h_y->data[i30 + h_y->size[0] *
              i32] * S_sum->data[i32 + S_sum->size[0] * i31];
          }
        }
      }
    } else {
      k = h_y->size[1];
      Eap_idx_0 = (unsigned int)h_y->size[0];
      unnamed_idx_1 = (unsigned int)S_sum->size[1];
      i30 = h_C->size[0] * h_C->size[1];
      h_C->size[0] = (int)Eap_idx_0;
      h_C->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)h_C, i30, (int)sizeof(double));
      m = h_y->size[0];
      i30 = h_C->size[0] * h_C->size[1];
      emxEnsureCapacity((emxArray__common *)h_C, i30, (int)sizeof(double));
      n = h_C->size[1];
      for (i30 = 0; i30 < n; i30++) {
        loop_ub = h_C->size[0];
        for (i31 = 0; i31 < loop_ub; i31++) {
          h_C->data[i31 + h_C->size[0] * i30] = 0.0;
        }
      }

      if ((h_y->size[0] == 0) || (S_sum->size[1] == 0)) {
      } else {
        ixstart = h_y->size[0] * (S_sum->size[1] - 1);
        ix = 0;
        while ((m > 0) && (ix <= ixstart)) {
          i30 = ix + m;
          for (ic = ix; ic + 1 <= i30; ic++) {
            h_C->data[ic] = 0.0;
          }

          ix += m;
        }

        n = 0;
        ix = 0;
        while ((m > 0) && (ix <= ixstart)) {
          ar = 0;
          i30 = n + k;
          for (ib = n; ib + 1 <= i30; ib++) {
            if (S_sum->data[ib] != 0.0) {
              ia = ar;
              i31 = ix + m;
              for (ic = ix; ic + 1 <= i31; ic++) {
                ia++;
                h_C->data[ic] += S_sum->data[ib] * h_y->data[ia - 1];
              }
            }

            ar += m;
          }

          n += k;
          ix += m;
        }
      }
    }

    i30 = Omega->size[0] * Omega->size[1];
    emxEnsureCapacity((emxArray__common *)Omega, i30, (int)sizeof(double));
    ixstart = Omega->size[0];
    ix = Omega->size[1];
    n = ixstart * ix;
    for (i30 = 0; i30 < n; i30++) {
      Omega->data[i30] += h_C->data[i30];
    }

    i30 = Eap->size[0] * Eap->size[1];
    Eap->size[0] = S_sum->size[1];
    Eap->size[1] = S_sum->size[0];
    emxEnsureCapacity((emxArray__common *)Eap, i30, (int)sizeof(double));
    n = S_sum->size[0];
    for (i30 = 0; i30 < n; i30++) {
      loop_ub = S_sum->size[1];
      for (i31 = 0; i31 < loop_ub; i31++) {
        Eap->data[i31 + Eap->size[0] * i30] = S_sum->data[i30 + S_sum->size[0] *
          i31];
      }
    }

    if ((Eap->size[1] == 1) || (Q->size[0] == 1)) {
      i30 = i_y->size[0] * i_y->size[1];
      i_y->size[0] = Eap->size[0];
      i_y->size[1] = Q->size[1];
      emxEnsureCapacity((emxArray__common *)i_y, i30, (int)sizeof(double));
      n = Eap->size[0];
      for (i30 = 0; i30 < n; i30++) {
        loop_ub = Q->size[1];
        for (i31 = 0; i31 < loop_ub; i31++) {
          i_y->data[i30 + i_y->size[0] * i31] = 0.0;
          ix = Eap->size[1];
          for (i32 = 0; i32 < ix; i32++) {
            i_y->data[i30 + i_y->size[0] * i31] += Eap->data[i30 + Eap->size[0] *
              i32] * Q->data[i32 + Q->size[0] * i31];
          }
        }
      }
    } else {
      k = Eap->size[1];
      Eap_idx_0 = (unsigned int)Eap->size[0];
      unnamed_idx_1 = (unsigned int)Q->size[1];
      i30 = i_y->size[0] * i_y->size[1];
      i_y->size[0] = (int)Eap_idx_0;
      i_y->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)i_y, i30, (int)sizeof(double));
      m = Eap->size[0];
      i30 = i_y->size[0] * i_y->size[1];
      emxEnsureCapacity((emxArray__common *)i_y, i30, (int)sizeof(double));
      n = i_y->size[1];
      for (i30 = 0; i30 < n; i30++) {
        loop_ub = i_y->size[0];
        for (i31 = 0; i31 < loop_ub; i31++) {
          i_y->data[i31 + i_y->size[0] * i30] = 0.0;
        }
      }

      if ((Eap->size[0] == 0) || (Q->size[1] == 0)) {
      } else {
        ixstart = Eap->size[0] * (Q->size[1] - 1);
        ix = 0;
        while ((m > 0) && (ix <= ixstart)) {
          i30 = ix + m;
          for (ic = ix; ic + 1 <= i30; ic++) {
            i_y->data[ic] = 0.0;
          }

          ix += m;
        }

        n = 0;
        ix = 0;
        while ((m > 0) && (ix <= ixstart)) {
          ar = 0;
          i30 = n + k;
          for (ib = n; ib + 1 <= i30; ib++) {
            if (Q->data[ib] != 0.0) {
              ia = ar;
              i31 = ix + m;
              for (ic = ix; ic + 1 <= i31; ic++) {
                ia++;
                i_y->data[ic] += Q->data[ib] * Eap->data[ia - 1];
              }
            }

            ar += m;
          }

          n += k;
          ix += m;
        }
      }
    }

    mpower(Eae, 2.0 + (double)i, b);
    if ((i_y->size[1] == 1) || (b->size[0] == 1)) {
      i30 = i_C->size[0] * i_C->size[1];
      i_C->size[0] = i_y->size[0];
      i_C->size[1] = b->size[1];
      emxEnsureCapacity((emxArray__common *)i_C, i30, (int)sizeof(double));
      n = i_y->size[0];
      for (i30 = 0; i30 < n; i30++) {
        loop_ub = b->size[1];
        for (i31 = 0; i31 < loop_ub; i31++) {
          i_C->data[i30 + i_C->size[0] * i31] = 0.0;
          ix = i_y->size[1];
          for (i32 = 0; i32 < ix; i32++) {
            i_C->data[i30 + i_C->size[0] * i31] += i_y->data[i30 + i_y->size[0] *
              i32] * b->data[i32 + b->size[0] * i31];
          }
        }
      }
    } else {
      k = i_y->size[1];
      Eap_idx_0 = (unsigned int)i_y->size[0];
      unnamed_idx_1 = (unsigned int)b->size[1];
      i30 = i_C->size[0] * i_C->size[1];
      i_C->size[0] = (int)Eap_idx_0;
      i_C->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)i_C, i30, (int)sizeof(double));
      m = i_y->size[0];
      i30 = i_C->size[0] * i_C->size[1];
      emxEnsureCapacity((emxArray__common *)i_C, i30, (int)sizeof(double));
      n = i_C->size[1];
      for (i30 = 0; i30 < n; i30++) {
        loop_ub = i_C->size[0];
        for (i31 = 0; i31 < loop_ub; i31++) {
          i_C->data[i31 + i_C->size[0] * i30] = 0.0;
        }
      }

      if ((i_y->size[0] == 0) || (b->size[1] == 0)) {
      } else {
        ixstart = i_y->size[0] * (b->size[1] - 1);
        ix = 0;
        while ((m > 0) && (ix <= ixstart)) {
          i30 = ix + m;
          for (ic = ix; ic + 1 <= i30; ic++) {
            i_C->data[ic] = 0.0;
          }

          ix += m;
        }

        n = 0;
        ix = 0;
        while ((m > 0) && (ix <= ixstart)) {
          ar = 0;
          i30 = n + k;
          for (ib = n; ib + 1 <= i30; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              i31 = ix + m;
              for (ic = ix; ic + 1 <= i31; ic++) {
                ia++;
                i_C->data[ic] += b->data[ib] * i_y->data[ia - 1];
              }
            }

            ar += m;
          }

          n += k;
          ix += m;
        }
      }
    }

    i30 = Psi->size[0] * Psi->size[1];
    emxEnsureCapacity((emxArray__common *)Psi, i30, (int)sizeof(double));
    ixstart = Psi->size[0];
    ix = Psi->size[1];
    n = ixstart * ix;
    for (i30 = 0; i30 < n; i30++) {
      Psi->data[i30] += i_C->data[i30];
    }

    i++;
  }

  emxFree_real_T(&c_S_in);
  emxFree_real_T(&c_S_sum);
  emxFree_real_T(&b_S_in_d);
  emxFree_real_T(&b_S_sum_d);
  emxFree_real_T(&b_S_in);
  emxFree_real_T(&b_S_sum);
  emxFree_real_T(&e_Al);
  emxFree_real_T(&d_Al);
  emxFree_real_T(&r19);
  emxFree_real_T(&i_y);
  emxFree_real_T(&h_y);
  emxFree_real_T(&g_y);
  emxFree_real_T(&b);
  emxFree_real_T(&i_C);
  emxFree_real_T(&h_C);
  emxFree_real_T(&g_C);
  emxFree_real_T(&f_C);
  emxFree_real_T(&e_C);
  emxFree_real_T(&d_C);
  emxFree_real_T(&c_C);
  emxFree_real_T(&b_C);
  emxFree_real_T(&C);
  emxFree_real_T(&L0);
  emxFree_real_T(&S_sum);
  emxFree_real_T(&Eap);
  emxFree_real_T(&Eae);
  emxFree_real_T(&S_sum_d);
  emxFree_real_T(&S_in_d);
  emxFree_real_T(&S_in);
  emxFree_real_T(&tau);
  i30 = Omega->size[0] * Omega->size[1];
  emxEnsureCapacity((emxArray__common *)Omega, i30, (int)sizeof(double));
  ixstart = Omega->size[0];
  ix = Omega->size[1];
  n = ixstart * ix;
  for (i30 = 0; i30 < n; i30++) {
    Omega->data[i30] = Omega->data[i30] * tau_del + R_L->data[i30];
  }

  emxFree_real_T(&R_L);
  i30 = Psi->size[0] * Psi->size[1];
  emxEnsureCapacity((emxArray__common *)Psi, i30, (int)sizeof(double));
  ixstart = Psi->size[0];
  ix = Psi->size[1];
  n = ixstart * ix;
  for (i30 = 0; i30 < n; i30++) {
    Psi->data[i30] *= tau_del;
  }

  i30 = Gamma->size[0] * Gamma->size[1];
  emxEnsureCapacity((emxArray__common *)Gamma, i30, (int)sizeof(double));
  ixstart = Gamma->size[0];
  ix = Gamma->size[1];
  n = ixstart * ix;
  for (i30 = 0; i30 < n; i30++) {
    Gamma->data[i30] *= tau_del;
  }
}

/*
 * File trailer for cmpc_2.c
 *
 * [EOF]
 */
