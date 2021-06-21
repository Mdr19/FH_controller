/*
 * File: Mucon.c
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
#include "Mucon.h"
#include "FHZN_define_model_del_emxutil.h"
#include "lagc.h"
#include "inv.h"
#include "expm.h"
#include "sum.h"

/* Function Definitions */

/*
 * function for generating matrix M for
 * the constraints on the control signal
 * constraints are imposed on the zero time and tau time
 * delta-t is the sampling interval
 * Mu is for constraints to be imposed on the zero sample
 * Mu1 is for constraints to be imposed on tau time
 * Arguments    : const emxArray_real_T *p
 *                const emxArray_real_T *N
 *                double n_in
 *                double delta_t
 *                emxArray_real_T *Mu
 *                emxArray_real_T *Mu1
 * Return Type  : void
 */
void Mucon(const emxArray_real_T *p, const emxArray_real_T *N, double n_in,
           double delta_t, emxArray_real_T *Mu, emxArray_real_T *Mu1)
{
  emxArray_real_T *Al;
  emxArray_real_T *L0;
  double N_pa;
  int i43;
  int br;
  double cc;
  int k0;
  emxArray_int32_T *r20;
  double d14;
  emxArray_real_T *b_Al;
  emxArray_real_T *a;
  emxArray_real_T *L1;
  int m;
  int cr;
  int k;
  unsigned int a_idx_0;
  int ic;
  int ar;
  int ib;
  int ia;
  emxArray_real_T *b_a;
  emxArray_real_T *c_Al;
  emxArray_real_T *C;
  emxArray_real_T *b_C;
  emxArray_real_T *d_Al;
  emxArray_real_T *e_Al;
  emxInit_real_T(&Al, 2);
  emxInit_real_T1(&L0, 1);
  N_pa = c_sum(N);
  lagc(p->data[0], N->data[0], Al, L0);
  i43 = Mu->size[0] * Mu->size[1];
  Mu->size[0] = (int)n_in;
  Mu->size[1] = (int)N_pa;
  emxEnsureCapacity((emxArray__common *)Mu, i43, (int)sizeof(double));
  br = (int)n_in * (int)N_pa;
  for (i43 = 0; i43 < br; i43++) {
    Mu->data[i43] = 0.0;
  }

  br = L0->size[0];
  for (i43 = 0; i43 < br; i43++) {
    Mu->data[Mu->size[0] * i43] = L0->data[i43];
  }

  cc = N->data[0];

  /*  gdy wektor B ma wiêcej elementów */
  k0 = 1;
  emxInit_int32_T1(&r20, 1);
  while (k0 - 1 <= (int)(n_in + -1.0) - 1) {
    lagc(p->data[k0], N->data[k0], Al, L0);
    d14 = N->data[k0];
    i43 = r20->size[0];
    r20->size[0] = (int)floor(d14 - 1.0) + 1;
    emxEnsureCapacity((emxArray__common *)r20, i43, (int)sizeof(int));
    br = (int)floor(d14 - 1.0);
    for (i43 = 0; i43 <= br; i43++) {
      r20->data[i43] = (int)(cc + (1.0 + (double)i43)) - 1;
    }

    br = L0->size[0];
    for (i43 = 0; i43 < br; i43++) {
      Mu->data[k0 + Mu->size[0] * r20->data[i43]] = L0->data[i43];
    }

    cc += N->data[k0];
    k0++;
  }

  emxInit_real_T(&b_Al, 2);

  /*  constraints on second sample */
  lagc(p->data[0], N->data[0], Al, L0);
  i43 = b_Al->size[0] * b_Al->size[1];
  b_Al->size[0] = Al->size[0];
  b_Al->size[1] = Al->size[1];
  emxEnsureCapacity((emxArray__common *)b_Al, i43, (int)sizeof(double));
  br = Al->size[0] * Al->size[1];
  for (i43 = 0; i43 < br; i43++) {
    b_Al->data[i43] = Al->data[i43] * 0.1;
  }

  emxInit_real_T(&a, 2);
  expm(b_Al, a);
  emxFree_real_T(&b_Al);
  emxInit_real_T1(&L1, 1);
  if ((a->size[1] == 1) || (L0->size[0] == 1)) {
    i43 = L1->size[0];
    L1->size[0] = a->size[0];
    emxEnsureCapacity((emxArray__common *)L1, i43, (int)sizeof(double));
    br = a->size[0];
    for (i43 = 0; i43 < br; i43++) {
      L1->data[i43] = 0.0;
      m = a->size[1];
      for (cr = 0; cr < m; cr++) {
        L1->data[i43] += a->data[i43 + a->size[0] * cr] * L0->data[cr];
      }
    }
  } else {
    k = a->size[1];
    a_idx_0 = (unsigned int)a->size[0];
    i43 = L1->size[0];
    L1->size[0] = (int)a_idx_0;
    emxEnsureCapacity((emxArray__common *)L1, i43, (int)sizeof(double));
    m = a->size[0];
    cr = L1->size[0];
    i43 = L1->size[0];
    L1->size[0] = cr;
    emxEnsureCapacity((emxArray__common *)L1, i43, (int)sizeof(double));
    for (i43 = 0; i43 < cr; i43++) {
      L1->data[i43] = 0.0;
    }

    if (a->size[0] == 0) {
    } else {
      cr = 0;
      while ((m > 0) && (cr <= 0)) {
        for (ic = 1; ic <= m; ic++) {
          L1->data[ic - 1] = 0.0;
        }

        cr = m;
      }

      br = 0;
      cr = 0;
      while ((m > 0) && (cr <= 0)) {
        ar = -1;
        i43 = br + k;
        for (ib = br; ib + 1 <= i43; ib++) {
          if (L0->data[ib] != 0.0) {
            ia = ar;
            for (ic = 0; ic + 1 <= m; ic++) {
              ia++;
              L1->data[ic] += L0->data[ib] * a->data[ia];
            }
          }

          ar += m;
        }

        br += k;
        cr = m;
      }
    }
  }

  i43 = Mu1->size[0] * Mu1->size[1];
  Mu1->size[0] = (int)n_in;
  Mu1->size[1] = (int)N_pa;
  emxEnsureCapacity((emxArray__common *)Mu1, i43, (int)sizeof(double));
  br = (int)n_in * (int)N_pa;
  for (i43 = 0; i43 < br; i43++) {
    Mu1->data[i43] = 0.0;
  }

  emxInit_real_T(&b_a, 2);
  i43 = b_a->size[0] * b_a->size[1];
  b_a->size[0] = 1;
  b_a->size[1] = L1->size[0];
  emxEnsureCapacity((emxArray__common *)b_a, i43, (int)sizeof(double));
  br = L1->size[0];
  for (i43 = 0; i43 < br; i43++) {
    b_a->data[b_a->size[0] * i43] = L1->data[i43] - L0->data[i43];
  }

  emxInit_real_T(&c_Al, 2);
  i43 = c_Al->size[0] * c_Al->size[1];
  c_Al->size[0] = Al->size[1];
  c_Al->size[1] = Al->size[0];
  emxEnsureCapacity((emxArray__common *)c_Al, i43, (int)sizeof(double));
  br = Al->size[0];
  for (i43 = 0; i43 < br; i43++) {
    m = Al->size[1];
    for (cr = 0; cr < m; cr++) {
      c_Al->data[cr + c_Al->size[0] * i43] = Al->data[i43 + Al->size[0] * cr];
    }
  }

  inv(c_Al, Al);
  emxFree_real_T(&c_Al);
  emxInit_real_T(&C, 2);
  if ((b_a->size[1] == 1) || (Al->size[0] == 1)) {
    i43 = C->size[0] * C->size[1];
    C->size[0] = 1;
    C->size[1] = Al->size[1];
    emxEnsureCapacity((emxArray__common *)C, i43, (int)sizeof(double));
    br = Al->size[1];
    for (i43 = 0; i43 < br; i43++) {
      C->data[C->size[0] * i43] = 0.0;
      m = b_a->size[1];
      for (cr = 0; cr < m; cr++) {
        C->data[C->size[0] * i43] += b_a->data[b_a->size[0] * cr] * Al->data[cr
          + Al->size[0] * i43];
      }
    }
  } else {
    k = b_a->size[1];
    a_idx_0 = (unsigned int)Al->size[1];
    i43 = C->size[0] * C->size[1];
    C->size[0] = 1;
    C->size[1] = (int)a_idx_0;
    emxEnsureCapacity((emxArray__common *)C, i43, (int)sizeof(double));
    m = Al->size[1] - 1;
    i43 = C->size[0] * C->size[1];
    C->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)C, i43, (int)sizeof(double));
    br = C->size[1];
    for (i43 = 0; i43 < br; i43++) {
      C->data[C->size[0] * i43] = 0.0;
    }

    if (Al->size[1] == 0) {
    } else {
      for (cr = 1; cr - 1 <= m; cr++) {
        for (ic = cr; ic <= cr; ic++) {
          C->data[ic - 1] = 0.0;
        }
      }

      br = 0;
      for (cr = 0; cr <= m; cr++) {
        ar = -1;
        i43 = br + k;
        for (ib = br; ib + 1 <= i43; ib++) {
          if (Al->data[ib] != 0.0) {
            ia = ar;
            for (ic = cr; ic + 1 <= cr + 1; ic++) {
              ia++;
              C->data[ic] += Al->data[ib] * b_a->data[ia];
            }
          }

          ar++;
        }

        br += k;
      }
    }
  }

  br = C->size[1];
  for (i43 = 0; i43 < br; i43++) {
    Mu1->data[Mu1->size[0] * i43] = C->data[C->size[0] * i43] + L0->data[i43] *
      delta_t;
  }

  emxFree_real_T(&C);
  cc = N->data[0];

  /*  gdy wektor B ma wiêcej elementów */
  k0 = 1;
  emxInit_real_T(&b_C, 2);
  emxInit_real_T(&d_Al, 2);
  emxInit_real_T(&e_Al, 2);
  while (k0 - 1 <= (int)(n_in + -1.0) - 1) {
    lagc(p->data[k0], N->data[k0], Al, L0);
    i43 = e_Al->size[0] * e_Al->size[1];
    e_Al->size[0] = Al->size[0];
    e_Al->size[1] = Al->size[1];
    emxEnsureCapacity((emxArray__common *)e_Al, i43, (int)sizeof(double));
    br = Al->size[0] * Al->size[1];
    for (i43 = 0; i43 < br; i43++) {
      e_Al->data[i43] = Al->data[i43] * 0.1;
    }

    expm(e_Al, a);
    if ((a->size[1] == 1) || (L0->size[0] == 1)) {
      i43 = L1->size[0];
      L1->size[0] = a->size[0];
      emxEnsureCapacity((emxArray__common *)L1, i43, (int)sizeof(double));
      br = a->size[0];
      for (i43 = 0; i43 < br; i43++) {
        L1->data[i43] = 0.0;
        m = a->size[1];
        for (cr = 0; cr < m; cr++) {
          L1->data[i43] += a->data[i43 + a->size[0] * cr] * L0->data[cr];
        }
      }
    } else {
      k = a->size[1];
      a_idx_0 = (unsigned int)a->size[0];
      i43 = L1->size[0];
      L1->size[0] = (int)a_idx_0;
      emxEnsureCapacity((emxArray__common *)L1, i43, (int)sizeof(double));
      m = a->size[0];
      cr = L1->size[0];
      i43 = L1->size[0];
      L1->size[0] = cr;
      emxEnsureCapacity((emxArray__common *)L1, i43, (int)sizeof(double));
      for (i43 = 0; i43 < cr; i43++) {
        L1->data[i43] = 0.0;
      }

      if (a->size[0] == 0) {
      } else {
        cr = 0;
        while ((m > 0) && (cr <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            L1->data[ic - 1] = 0.0;
          }

          cr = m;
        }

        br = 0;
        cr = 0;
        while ((m > 0) && (cr <= 0)) {
          ar = -1;
          i43 = br + k;
          for (ib = br; ib + 1 <= i43; ib++) {
            if (L0->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                L1->data[ic] += L0->data[ib] * a->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          cr = m;
        }
      }
    }

    i43 = b_a->size[0] * b_a->size[1];
    b_a->size[0] = 1;
    b_a->size[1] = L1->size[0];
    emxEnsureCapacity((emxArray__common *)b_a, i43, (int)sizeof(double));
    br = L1->size[0];
    for (i43 = 0; i43 < br; i43++) {
      b_a->data[b_a->size[0] * i43] = L1->data[i43] - L0->data[i43];
    }

    i43 = d_Al->size[0] * d_Al->size[1];
    d_Al->size[0] = Al->size[1];
    d_Al->size[1] = Al->size[0];
    emxEnsureCapacity((emxArray__common *)d_Al, i43, (int)sizeof(double));
    br = Al->size[0];
    for (i43 = 0; i43 < br; i43++) {
      m = Al->size[1];
      for (cr = 0; cr < m; cr++) {
        d_Al->data[cr + d_Al->size[0] * i43] = Al->data[i43 + Al->size[0] * cr];
      }
    }

    inv(d_Al, Al);
    if ((b_a->size[1] == 1) || (Al->size[0] == 1)) {
      i43 = b_C->size[0] * b_C->size[1];
      b_C->size[0] = 1;
      b_C->size[1] = Al->size[1];
      emxEnsureCapacity((emxArray__common *)b_C, i43, (int)sizeof(double));
      br = Al->size[1];
      for (i43 = 0; i43 < br; i43++) {
        b_C->data[b_C->size[0] * i43] = 0.0;
        m = b_a->size[1];
        for (cr = 0; cr < m; cr++) {
          b_C->data[b_C->size[0] * i43] += b_a->data[b_a->size[0] * cr] *
            Al->data[cr + Al->size[0] * i43];
        }
      }
    } else {
      k = b_a->size[1];
      a_idx_0 = (unsigned int)Al->size[1];
      i43 = b_C->size[0] * b_C->size[1];
      b_C->size[0] = 1;
      b_C->size[1] = (int)a_idx_0;
      emxEnsureCapacity((emxArray__common *)b_C, i43, (int)sizeof(double));
      m = Al->size[1] - 1;
      i43 = b_C->size[0] * b_C->size[1];
      b_C->size[0] = 1;
      emxEnsureCapacity((emxArray__common *)b_C, i43, (int)sizeof(double));
      br = b_C->size[1];
      for (i43 = 0; i43 < br; i43++) {
        b_C->data[b_C->size[0] * i43] = 0.0;
      }

      if (Al->size[1] == 0) {
      } else {
        for (cr = 1; cr - 1 <= m; cr++) {
          for (ic = cr; ic <= cr; ic++) {
            b_C->data[ic - 1] = 0.0;
          }
        }

        br = 0;
        for (cr = 0; cr <= m; cr++) {
          ar = -1;
          i43 = br + k;
          for (ib = br; ib + 1 <= i43; ib++) {
            if (Al->data[ib] != 0.0) {
              ia = ar;
              for (ic = cr; ic + 1 <= cr + 1; ic++) {
                ia++;
                b_C->data[ic] += Al->data[ib] * b_a->data[ia];
              }
            }

            ar++;
          }

          br += k;
        }
      }
    }

    d14 = N->data[k0];
    i43 = r20->size[0];
    r20->size[0] = (int)floor(d14 - 1.0) + 1;
    emxEnsureCapacity((emxArray__common *)r20, i43, (int)sizeof(int));
    br = (int)floor(d14 - 1.0);
    for (i43 = 0; i43 <= br; i43++) {
      r20->data[i43] = (int)(cc + (1.0 + (double)i43)) - 1;
    }

    br = b_C->size[1];
    for (i43 = 0; i43 < br; i43++) {
      Mu1->data[k0 + Mu1->size[0] * r20->data[i43]] = b_C->data[b_C->size[0] *
        i43] + L0->data[i43] * delta_t;
    }

    cc += N->data[k0];
    k0++;
  }

  emxFree_real_T(&e_Al);
  emxFree_real_T(&d_Al);
  emxFree_real_T(&b_a);
  emxFree_real_T(&a);
  emxFree_int32_T(&r20);
  emxFree_real_T(&b_C);
  emxFree_real_T(&L0);
  emxFree_real_T(&Al);
  emxFree_real_T(&L1);
  i43 = Mu->size[0] * Mu->size[1];
  emxEnsureCapacity((emxArray__common *)Mu, i43, (int)sizeof(double));
  cr = Mu->size[0];
  m = Mu->size[1];
  br = cr * m;
  for (i43 = 0; i43 < br; i43++) {
    Mu->data[i43] *= delta_t;
  }
}

/*
 * File trailer for Mucon.c
 *
 * [EOF]
 */
