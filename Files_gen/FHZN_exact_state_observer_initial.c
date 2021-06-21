/*
 * File: FHZN_exact_state_observer_initial.c
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
#include "FHZN_exact_state_observer_initial.h"
#include "FHZN_define_model_del_emxutil.h"
#include "expm.h"
#include "mldivide.h"
#include "trapz.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                const emxArray_real_T *C
 *                emxArray_real_T *t
 *                const emxArray_real_T *u
 *                const emxArray_real_T *y
 *                emxArray_real_T *X_0
 * Return Type  : void
 */
void c_FHZN_exact_state_observer_ini(const emxArray_real_T *A, const
  emxArray_real_T *B, const emxArray_real_T *C, emxArray_real_T *t, const
  emxArray_real_T *u, const emxArray_real_T *y, emxArray_real_T *X_0)
{
  emxArray_real_T *M0;
  int n;
  int i9;
  int nx;
  emxArray_real_T *G1_y;
  emxArray_real_T *G2_u;
  int i;
  emxArray_int32_T *r7;
  emxArray_real_T *b_C;
  emxArray_int32_T *r8;
  emxArray_real_T *b_y;
  emxArray_real_T *a;
  emxArray_real_T *c_y;
  emxArray_real_T *b;
  emxArray_real_T *b_A;
  emxArray_real_T *c_A;
  int ic;
  int i10;
  double b_t;
  int br;
  int ib;
  int k;
  unsigned int a_idx_0;
  unsigned int unnamed_idx_1;
  int m;
  int c;
  int ar;
  int ia;
  emxArray_real_T *M0_;
  emxArray_real_T *c_C;
  emxArray_real_T *d_y;
  emxArray_real_T *b_b;
  emxArray_real_T *x;
  emxArray_real_T *e_y;
  emxArray_real_T *f_y;
  emxArray_real_T *d_A;
  emxArray_real_T *c_t;
  emxArray_real_T *b_M0;
  emxArray_real_T *e_A;
  emxArray_real_T *g_y;
  emxArray_real_T *r9;
  emxArray_real_T *r10;
  emxInit_real_T2(&M0, 3);
  n = A->size[0];
  i9 = M0->size[0] * M0->size[1] * M0->size[2];
  M0->size[0] = t->size[1];
  M0->size[1] = A->size[0];
  M0->size[2] = A->size[0];
  emxEnsureCapacity((emxArray__common *)M0, i9, (int)sizeof(double));
  nx = t->size[1] * A->size[0] * A->size[0];
  for (i9 = 0; i9 < nx; i9++) {
    M0->data[i9] = 0.0;
  }

  emxInit_real_T(&G1_y, 2);
  i9 = G1_y->size[0] * G1_y->size[1];
  G1_y->size[0] = t->size[1] - 1;
  G1_y->size[1] = A->size[0];
  emxEnsureCapacity((emxArray__common *)G1_y, i9, (int)sizeof(double));
  nx = (t->size[1] - 1) * A->size[0];
  for (i9 = 0; i9 < nx; i9++) {
    G1_y->data[i9] = 0.0;
  }

  emxInit_real_T(&G2_u, 2);
  i9 = G2_u->size[0] * G2_u->size[1];
  G2_u->size[0] = t->size[1] - 1;
  G2_u->size[1] = A->size[0];
  emxEnsureCapacity((emxArray__common *)G2_u, i9, (int)sizeof(double));
  nx = (t->size[1] - 1) * A->size[0];
  for (i9 = 0; i9 < nx; i9++) {
    G2_u->data[i9] = 0.0;
  }

  i = 0;
  emxInit_int32_T1(&r7, 1);
  emxInit_real_T(&b_C, 2);
  emxInit_int32_T1(&r8, 1);
  emxInit_real_T(&b_y, 2);
  emxInit_real_T(&a, 2);
  emxInit_real_T(&c_y, 2);
  emxInit_real_T(&b, 2);
  emxInit_real_T(&b_A, 2);
  emxInit_real_T(&c_A, 2);
  while (i <= t->size[1] - 1) {
    nx = M0->size[1];
    i9 = r8->size[0];
    r8->size[0] = nx;
    emxEnsureCapacity((emxArray__common *)r8, i9, (int)sizeof(int));
    for (i9 = 0; i9 < nx; i9++) {
      r8->data[i9] = i9;
    }

    nx = M0->size[2];
    i9 = r7->size[0];
    r7->size[0] = nx;
    emxEnsureCapacity((emxArray__common *)r7, i9, (int)sizeof(int));
    for (i9 = 0; i9 < nx; i9++) {
      r7->data[i9] = i9;
    }

    i9 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = C->size[1];
    b_y->size[1] = C->size[1];
    emxEnsureCapacity((emxArray__common *)b_y, i9, (int)sizeof(double));
    nx = C->size[1];
    for (i9 = 0; i9 < nx; i9++) {
      ic = C->size[1];
      for (i10 = 0; i10 < ic; i10++) {
        b_y->data[i9 + b_y->size[0] * i10] = C->data[C->size[0] * i9] * C->
          data[C->size[0] * i10];
      }
    }

    b_t = t->data[i];
    i9 = c_A->size[0] * c_A->size[1];
    c_A->size[0] = A->size[1];
    c_A->size[1] = A->size[0];
    emxEnsureCapacity((emxArray__common *)c_A, i9, (int)sizeof(double));
    nx = A->size[0];
    for (i9 = 0; i9 < nx; i9++) {
      ic = A->size[1];
      for (i10 = 0; i10 < ic; i10++) {
        c_A->data[i10 + c_A->size[0] * i9] = A->data[i9 + A->size[0] * i10] *
          b_t;
      }
    }

    expm(c_A, a);
    if ((a->size[1] == 1) || (b_y->size[0] == 1)) {
      i9 = c_y->size[0] * c_y->size[1];
      c_y->size[0] = a->size[0];
      c_y->size[1] = b_y->size[1];
      emxEnsureCapacity((emxArray__common *)c_y, i9, (int)sizeof(double));
      nx = a->size[0];
      for (i9 = 0; i9 < nx; i9++) {
        ic = b_y->size[1];
        for (i10 = 0; i10 < ic; i10++) {
          c_y->data[i9 + c_y->size[0] * i10] = 0.0;
          br = a->size[1];
          for (ib = 0; ib < br; ib++) {
            c_y->data[i9 + c_y->size[0] * i10] += a->data[i9 + a->size[0] * ib] *
              b_y->data[ib + b_y->size[0] * i10];
          }
        }
      }
    } else {
      k = a->size[1];
      a_idx_0 = (unsigned int)a->size[0];
      unnamed_idx_1 = (unsigned int)b_y->size[1];
      i9 = c_y->size[0] * c_y->size[1];
      c_y->size[0] = (int)a_idx_0;
      c_y->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)c_y, i9, (int)sizeof(double));
      m = a->size[0];
      i9 = c_y->size[0] * c_y->size[1];
      emxEnsureCapacity((emxArray__common *)c_y, i9, (int)sizeof(double));
      nx = c_y->size[1];
      for (i9 = 0; i9 < nx; i9++) {
        ic = c_y->size[0];
        for (i10 = 0; i10 < ic; i10++) {
          c_y->data[i10 + c_y->size[0] * i9] = 0.0;
        }
      }

      if ((a->size[0] == 0) || (b_y->size[1] == 0)) {
      } else {
        c = a->size[0] * (b_y->size[1] - 1);
        nx = 0;
        while ((m > 0) && (nx <= c)) {
          i9 = nx + m;
          for (ic = nx; ic + 1 <= i9; ic++) {
            c_y->data[ic] = 0.0;
          }

          nx += m;
        }

        br = 0;
        nx = 0;
        while ((m > 0) && (nx <= c)) {
          ar = -1;
          i9 = br + k;
          for (ib = br; ib + 1 <= i9; ib++) {
            if (b_y->data[ib] != 0.0) {
              ia = ar;
              i10 = nx + m;
              for (ic = nx; ic + 1 <= i10; ic++) {
                ia++;
                c_y->data[ic] += b_y->data[ib] * a->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          nx += m;
        }
      }
    }

    i9 = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)b_A, i9, (int)sizeof(double));
    b_t = t->data[i];
    nx = A->size[0] * A->size[1];
    for (i9 = 0; i9 < nx; i9++) {
      b_A->data[i9] = A->data[i9] * b_t;
    }

    expm(b_A, b);
    if ((c_y->size[1] == 1) || (b->size[0] == 1)) {
      i9 = b_C->size[0] * b_C->size[1];
      b_C->size[0] = c_y->size[0];
      b_C->size[1] = b->size[1];
      emxEnsureCapacity((emxArray__common *)b_C, i9, (int)sizeof(double));
      nx = c_y->size[0];
      for (i9 = 0; i9 < nx; i9++) {
        ic = b->size[1];
        for (i10 = 0; i10 < ic; i10++) {
          b_C->data[i9 + b_C->size[0] * i10] = 0.0;
          br = c_y->size[1];
          for (ib = 0; ib < br; ib++) {
            b_C->data[i9 + b_C->size[0] * i10] += c_y->data[i9 + c_y->size[0] *
              ib] * b->data[ib + b->size[0] * i10];
          }
        }
      }
    } else {
      k = c_y->size[1];
      a_idx_0 = (unsigned int)c_y->size[0];
      unnamed_idx_1 = (unsigned int)b->size[1];
      i9 = b_C->size[0] * b_C->size[1];
      b_C->size[0] = (int)a_idx_0;
      b_C->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)b_C, i9, (int)sizeof(double));
      m = c_y->size[0];
      i9 = b_C->size[0] * b_C->size[1];
      emxEnsureCapacity((emxArray__common *)b_C, i9, (int)sizeof(double));
      nx = b_C->size[1];
      for (i9 = 0; i9 < nx; i9++) {
        ic = b_C->size[0];
        for (i10 = 0; i10 < ic; i10++) {
          b_C->data[i10 + b_C->size[0] * i9] = 0.0;
        }
      }

      if ((c_y->size[0] == 0) || (b->size[1] == 0)) {
      } else {
        c = c_y->size[0] * (b->size[1] - 1);
        nx = 0;
        while ((m > 0) && (nx <= c)) {
          i9 = nx + m;
          for (ic = nx; ic + 1 <= i9; ic++) {
            b_C->data[ic] = 0.0;
          }

          nx += m;
        }

        br = 0;
        nx = 0;
        while ((m > 0) && (nx <= c)) {
          ar = -1;
          i9 = br + k;
          for (ib = br; ib + 1 <= i9; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              i10 = nx + m;
              for (ic = nx; ic + 1 <= i10; ic++) {
                ia++;
                b_C->data[ic] += b->data[ib] * c_y->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          nx += m;
        }
      }
    }

    nx = r8->size[0];
    br = r7->size[0];
    for (i9 = 0; i9 < br; i9++) {
      for (i10 = 0; i10 < nx; i10++) {
        M0->data[(i + M0->size[0] * r8->data[i10]) + M0->size[0] * M0->size[1] *
          r7->data[i9]] = b_C->data[i10 + nx * i9];
      }
    }

    i++;
  }

  emxFree_real_T(&c_A);
  emxFree_real_T(&b_A);
  emxFree_real_T(&b_C);
  emxFree_int32_T(&r7);
  emxInit_real_T2(&M0_, 3);
  trapz(t, M0, M0_);

  /* M0= */
  i = 0;
  emxInit_real_T1(&c_C, 1);
  emxInit_real_T1(&d_y, 1);
  emxInit_real_T1(&b_b, 1);
  emxInit_real_T2(&x, 3);
  emxInit_real_T(&e_y, 2);
  emxInit_real_T(&f_y, 2);
  emxInit_real_T(&d_A, 2);
  emxInit_real_T(&c_t, 2);
  emxInit_real_T2(&b_M0, 3);
  emxInit_real_T(&e_A, 2);
  emxInit_real_T1(&g_y, 1);
  while (i <= t->size[1] - 2) {
    nx = G1_y->size[1];
    i9 = r8->size[0];
    r8->size[0] = nx;
    emxEnsureCapacity((emxArray__common *)r8, i9, (int)sizeof(int));
    for (i9 = 0; i9 < nx; i9++) {
      r8->data[i9] = i9;
    }

    nx = M0_->size[1] * M0_->size[2];
    i9 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = n;
    b_y->size[1] = n;
    emxEnsureCapacity((emxArray__common *)b_y, i9, (int)sizeof(double));
    for (k = 0; k + 1 <= nx; k++) {
      b_y->data[k] = M0_->data[k];
    }

    b_t = t->data[i];
    i9 = e_A->size[0] * e_A->size[1];
    e_A->size[0] = A->size[1];
    e_A->size[1] = A->size[0];
    emxEnsureCapacity((emxArray__common *)e_A, i9, (int)sizeof(double));
    nx = A->size[0];
    for (i9 = 0; i9 < nx; i9++) {
      ic = A->size[1];
      for (i10 = 0; i10 < ic; i10++) {
        e_A->data[i10 + e_A->size[0] * i9] = A->data[i9 + A->size[0] * i10] *
          b_t;
      }
    }

    expm(e_A, b);
    mldivide(b_y, b, a);
    i9 = b_b->size[0];
    b_b->size[0] = C->size[1];
    emxEnsureCapacity((emxArray__common *)b_b, i9, (int)sizeof(double));
    nx = C->size[1];
    for (i9 = 0; i9 < nx; i9++) {
      b_b->data[i9] = C->data[C->size[0] * i9];
    }

    if ((a->size[1] == 1) || (b_b->size[0] == 1)) {
      i9 = d_y->size[0];
      d_y->size[0] = a->size[0];
      emxEnsureCapacity((emxArray__common *)d_y, i9, (int)sizeof(double));
      nx = a->size[0];
      for (i9 = 0; i9 < nx; i9++) {
        d_y->data[i9] = 0.0;
        ic = a->size[1];
        for (i10 = 0; i10 < ic; i10++) {
          d_y->data[i9] += a->data[i9 + a->size[0] * i10] * b_b->data[i10];
        }
      }
    } else {
      k = a->size[1];
      a_idx_0 = (unsigned int)a->size[0];
      i9 = d_y->size[0];
      d_y->size[0] = (int)a_idx_0;
      emxEnsureCapacity((emxArray__common *)d_y, i9, (int)sizeof(double));
      m = a->size[0];
      nx = d_y->size[0];
      i9 = d_y->size[0];
      d_y->size[0] = nx;
      emxEnsureCapacity((emxArray__common *)d_y, i9, (int)sizeof(double));
      for (i9 = 0; i9 < nx; i9++) {
        d_y->data[i9] = 0.0;
      }

      if (a->size[0] == 0) {
      } else {
        nx = 0;
        while ((m > 0) && (nx <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            d_y->data[ic - 1] = 0.0;
          }

          nx = m;
        }

        br = 0;
        nx = 0;
        while ((m > 0) && (nx <= 0)) {
          ar = -1;
          i9 = br + k;
          for (ib = br; ib + 1 <= i9; ib++) {
            if (b_b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                d_y->data[ic] += b_b->data[ib] * a->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          nx = m;
        }
      }
    }

    b_t = y->data[i];
    i9 = g_y->size[0];
    g_y->size[0] = d_y->size[0];
    emxEnsureCapacity((emxArray__common *)g_y, i9, (int)sizeof(double));
    nx = d_y->size[0];
    for (i9 = 0; i9 < nx; i9++) {
      g_y->data[i9] = d_y->data[i9] * b_t;
    }

    nx = r8->size[0];
    for (i9 = 0; i9 < nx; i9++) {
      G1_y->data[i + G1_y->size[0] * r8->data[i9]] = g_y->data[i9];
    }

    if (1 + i > t->size[1]) {
      i9 = 1;
      i10 = 0;
    } else {
      i9 = i + 1;
      i10 = t->size[1];
    }

    if (1 + i > M0->size[0]) {
      ib = 1;
      ia = 0;
    } else {
      ib = i + 1;
      ia = M0->size[0];
    }

    nx = G2_u->size[1];
    ar = r8->size[0];
    r8->size[0] = nx;
    emxEnsureCapacity((emxArray__common *)r8, ar, (int)sizeof(int));
    for (ar = 0; ar < nx; ar++) {
      r8->data[ar] = ar;
    }

    nx = M0_->size[1] * M0_->size[2];
    ar = b_y->size[0] * b_y->size[1];
    b_y->size[0] = n;
    b_y->size[1] = n;
    emxEnsureCapacity((emxArray__common *)b_y, ar, (int)sizeof(double));
    for (k = 0; k + 1 <= nx; k++) {
      b_y->data[k] = M0_->data[k];
    }

    ar = c_t->size[0] * c_t->size[1];
    c_t->size[0] = 1;
    c_t->size[1] = (i10 - i9) + 1;
    emxEnsureCapacity((emxArray__common *)c_t, ar, (int)sizeof(double));
    nx = (i10 - i9) + 1;
    for (i10 = 0; i10 < nx; i10++) {
      c_t->data[c_t->size[0] * i10] = t->data[(i9 + i10) - 1];
    }

    nx = M0->size[1];
    ic = M0->size[2];
    i9 = b_M0->size[0] * b_M0->size[1] * b_M0->size[2];
    b_M0->size[0] = (ia - ib) + 1;
    b_M0->size[1] = nx;
    b_M0->size[2] = ic;
    emxEnsureCapacity((emxArray__common *)b_M0, i9, (int)sizeof(double));
    for (i9 = 0; i9 < ic; i9++) {
      for (i10 = 0; i10 < nx; i10++) {
        br = (ia - ib) + 1;
        for (ar = 0; ar < br; ar++) {
          b_M0->data[(ar + b_M0->size[0] * i10) + b_M0->size[0] * b_M0->size[1] *
            i9] = M0->data[(((ib + ar) + M0->size[0] * i10) + M0->size[0] *
                            M0->size[1] * i9) - 1];
        }
      }
    }

    trapz(c_t, b_M0, x);
    nx = x->size[1] * x->size[2];
    i9 = c_y->size[0] * c_y->size[1];
    c_y->size[0] = n;
    c_y->size[1] = n;
    emxEnsureCapacity((emxArray__common *)c_y, i9, (int)sizeof(double));
    for (k = 0; k + 1 <= nx; k++) {
      c_y->data[k] = x->data[k];
    }

    mldivide(b_y, c_y, a);
    i9 = d_A->size[0] * d_A->size[1];
    d_A->size[0] = A->size[0];
    d_A->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)d_A, i9, (int)sizeof(double));
    b_t = t->data[i];
    nx = A->size[0] * A->size[1];
    for (i9 = 0; i9 < nx; i9++) {
      d_A->data[i9] = -A->data[i9] * b_t;
    }

    expm(d_A, b);
    if ((a->size[1] == 1) || (b->size[0] == 1)) {
      i9 = e_y->size[0] * e_y->size[1];
      e_y->size[0] = a->size[0];
      e_y->size[1] = b->size[1];
      emxEnsureCapacity((emxArray__common *)e_y, i9, (int)sizeof(double));
      nx = a->size[0];
      for (i9 = 0; i9 < nx; i9++) {
        ic = b->size[1];
        for (i10 = 0; i10 < ic; i10++) {
          e_y->data[i9 + e_y->size[0] * i10] = 0.0;
          br = a->size[1];
          for (ib = 0; ib < br; ib++) {
            e_y->data[i9 + e_y->size[0] * i10] += a->data[i9 + a->size[0] * ib] *
              b->data[ib + b->size[0] * i10];
          }
        }
      }
    } else {
      k = a->size[1];
      a_idx_0 = (unsigned int)a->size[0];
      unnamed_idx_1 = (unsigned int)b->size[1];
      i9 = e_y->size[0] * e_y->size[1];
      e_y->size[0] = (int)a_idx_0;
      e_y->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)e_y, i9, (int)sizeof(double));
      m = a->size[0];
      i9 = e_y->size[0] * e_y->size[1];
      emxEnsureCapacity((emxArray__common *)e_y, i9, (int)sizeof(double));
      nx = e_y->size[1];
      for (i9 = 0; i9 < nx; i9++) {
        ic = e_y->size[0];
        for (i10 = 0; i10 < ic; i10++) {
          e_y->data[i10 + e_y->size[0] * i9] = 0.0;
        }
      }

      if ((a->size[0] == 0) || (b->size[1] == 0)) {
      } else {
        c = a->size[0] * (b->size[1] - 1);
        nx = 0;
        while ((m > 0) && (nx <= c)) {
          i9 = nx + m;
          for (ic = nx; ic + 1 <= i9; ic++) {
            e_y->data[ic] = 0.0;
          }

          nx += m;
        }

        br = 0;
        nx = 0;
        while ((m > 0) && (nx <= c)) {
          ar = -1;
          i9 = br + k;
          for (ib = br; ib + 1 <= i9; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              i10 = nx + m;
              for (ic = nx; ic + 1 <= i10; ic++) {
                ia++;
                e_y->data[ic] += b->data[ib] * a->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          nx += m;
        }
      }
    }

    if ((e_y->size[1] == 1) || (B->size[0] == 1)) {
      i9 = f_y->size[0] * f_y->size[1];
      f_y->size[0] = e_y->size[0];
      f_y->size[1] = B->size[1];
      emxEnsureCapacity((emxArray__common *)f_y, i9, (int)sizeof(double));
      nx = e_y->size[0];
      for (i9 = 0; i9 < nx; i9++) {
        ic = B->size[1];
        for (i10 = 0; i10 < ic; i10++) {
          f_y->data[i9 + f_y->size[0] * i10] = 0.0;
          br = e_y->size[1];
          for (ib = 0; ib < br; ib++) {
            f_y->data[i9 + f_y->size[0] * i10] += e_y->data[i9 + e_y->size[0] *
              ib] * B->data[ib + B->size[0] * i10];
          }
        }
      }
    } else {
      k = e_y->size[1];
      a_idx_0 = (unsigned int)e_y->size[0];
      unnamed_idx_1 = (unsigned int)B->size[1];
      i9 = f_y->size[0] * f_y->size[1];
      f_y->size[0] = (int)a_idx_0;
      f_y->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)f_y, i9, (int)sizeof(double));
      m = e_y->size[0];
      i9 = f_y->size[0] * f_y->size[1];
      emxEnsureCapacity((emxArray__common *)f_y, i9, (int)sizeof(double));
      nx = f_y->size[1];
      for (i9 = 0; i9 < nx; i9++) {
        ic = f_y->size[0];
        for (i10 = 0; i10 < ic; i10++) {
          f_y->data[i10 + f_y->size[0] * i9] = 0.0;
        }
      }

      if ((e_y->size[0] == 0) || (B->size[1] == 0)) {
      } else {
        c = e_y->size[0] * (B->size[1] - 1);
        nx = 0;
        while ((m > 0) && (nx <= c)) {
          i9 = nx + m;
          for (ic = nx; ic + 1 <= i9; ic++) {
            f_y->data[ic] = 0.0;
          }

          nx += m;
        }

        br = 0;
        nx = 0;
        while ((m > 0) && (nx <= c)) {
          ar = -1;
          i9 = br + k;
          for (ib = br; ib + 1 <= i9; ib++) {
            if (B->data[ib] != 0.0) {
              ia = ar;
              i10 = nx + m;
              for (ic = nx; ic + 1 <= i10; ic++) {
                ia++;
                f_y->data[ic] += B->data[ib] * e_y->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          nx += m;
        }
      }
    }

    nx = u->size[1];
    i9 = b_b->size[0];
    b_b->size[0] = nx;
    emxEnsureCapacity((emxArray__common *)b_b, i9, (int)sizeof(double));
    for (i9 = 0; i9 < nx; i9++) {
      b_b->data[i9] = u->data[i + u->size[0] * i9];
    }

    if ((f_y->size[1] == 1) || (b_b->size[0] == 1)) {
      i9 = c_C->size[0];
      c_C->size[0] = f_y->size[0];
      emxEnsureCapacity((emxArray__common *)c_C, i9, (int)sizeof(double));
      nx = f_y->size[0];
      for (i9 = 0; i9 < nx; i9++) {
        c_C->data[i9] = 0.0;
        ic = f_y->size[1];
        for (i10 = 0; i10 < ic; i10++) {
          c_C->data[i9] += f_y->data[i9 + f_y->size[0] * i10] * b_b->data[i10];
        }
      }
    } else {
      k = f_y->size[1];
      a_idx_0 = (unsigned int)f_y->size[0];
      i9 = c_C->size[0];
      c_C->size[0] = (int)a_idx_0;
      emxEnsureCapacity((emxArray__common *)c_C, i9, (int)sizeof(double));
      m = f_y->size[0];
      nx = c_C->size[0];
      i9 = c_C->size[0];
      c_C->size[0] = nx;
      emxEnsureCapacity((emxArray__common *)c_C, i9, (int)sizeof(double));
      for (i9 = 0; i9 < nx; i9++) {
        c_C->data[i9] = 0.0;
      }

      if (f_y->size[0] == 0) {
      } else {
        nx = 0;
        while ((m > 0) && (nx <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            c_C->data[ic - 1] = 0.0;
          }

          nx = m;
        }

        br = 0;
        nx = 0;
        while ((m > 0) && (nx <= 0)) {
          ar = -1;
          i9 = br + k;
          for (ib = br; ib + 1 <= i9; ib++) {
            if (b_b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                c_C->data[ic] += b_b->data[ib] * f_y->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          nx = m;
        }
      }
    }

    nx = r8->size[0];
    for (i9 = 0; i9 < nx; i9++) {
      G2_u->data[i + G2_u->size[0] * r8->data[i9]] = c_C->data[i9];
    }

    i++;
  }

  emxFree_real_T(&g_y);
  emxFree_real_T(&e_A);
  emxFree_real_T(&b_M0);
  emxFree_real_T(&c_t);
  emxFree_real_T(&d_A);
  emxFree_real_T(&f_y);
  emxFree_real_T(&b);
  emxFree_real_T(&e_y);
  emxFree_real_T(&x);
  emxFree_real_T(&c_y);
  emxFree_real_T(&b_b);
  emxFree_real_T(&a);
  emxFree_real_T(&d_y);
  emxFree_real_T(&b_y);
  emxFree_real_T(&c_C);
  emxFree_int32_T(&r8);
  emxFree_real_T(&M0_);
  emxFree_real_T(&M0);
  if (1 > t->size[1] - 1) {
    i9 = 0;
  } else {
    i9 = t->size[1] - 1;
  }

  emxInit_real_T(&r9, 2);
  emxInit_real_T(&r10, 2);
  i10 = t->size[0] * t->size[1];
  t->size[1] = i9;
  emxEnsureCapacity((emxArray__common *)t, i10, (int)sizeof(double));

  /* disp('X start'); */
  b_trapz(t, G1_y, r9);
  b_trapz(t, G2_u, r10);
  i9 = X_0->size[0];
  X_0->size[0] = r9->size[1];
  emxEnsureCapacity((emxArray__common *)X_0, i9, (int)sizeof(double));
  nx = r9->size[1];
  emxFree_real_T(&G2_u);
  emxFree_real_T(&G1_y);
  for (i9 = 0; i9 < nx; i9++) {
    X_0->data[i9] = r9->data[r9->size[0] * i9] + r10->data[r10->size[0] * i9];
  }

  emxFree_real_T(&r10);
  emxFree_real_T(&r9);
}

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                const emxArray_real_T *C
 *                emxArray_real_T *t
 *                const emxArray_real_T *u
 *                const emxArray_real_T *y
 *                emxArray_real_T *X_0
 * Return Type  : void
 */
void d_FHZN_exact_state_observer_ini(const emxArray_real_T *A, const
  emxArray_real_T *B, const emxArray_real_T *C, emxArray_real_T *t, const
  emxArray_real_T *u, const emxArray_real_T *y, emxArray_real_T *X_0)
{
  emxArray_real_T *M0;
  int n;
  int i24;
  int nx;
  emxArray_real_T *G1_y;
  emxArray_real_T *G2_u;
  int i;
  emxArray_int32_T *r14;
  emxArray_real_T *b_C;
  emxArray_int32_T *r15;
  emxArray_real_T *b_y;
  emxArray_real_T *a;
  emxArray_real_T *c_y;
  emxArray_real_T *b;
  emxArray_real_T *b_A;
  emxArray_real_T *c_A;
  int ic;
  int i25;
  double b_t;
  int br;
  int ib;
  int k;
  unsigned int a_idx_0;
  unsigned int unnamed_idx_1;
  int m;
  int c;
  int ar;
  int ia;
  emxArray_real_T *M0_;
  emxArray_real_T *c_C;
  emxArray_real_T *d_y;
  emxArray_real_T *b_b;
  emxArray_real_T *x;
  emxArray_real_T *e_y;
  emxArray_real_T *f_y;
  emxArray_real_T *d_A;
  emxArray_real_T *c_t;
  emxArray_real_T *b_M0;
  emxArray_real_T *e_A;
  emxArray_real_T *g_y;
  emxArray_real_T *r16;
  emxArray_real_T *r17;
  emxInit_real_T2(&M0, 3);
  n = A->size[0];
  i24 = M0->size[0] * M0->size[1] * M0->size[2];
  M0->size[0] = t->size[1];
  M0->size[1] = A->size[0];
  M0->size[2] = A->size[0];
  emxEnsureCapacity((emxArray__common *)M0, i24, (int)sizeof(double));
  nx = t->size[1] * A->size[0] * A->size[0];
  for (i24 = 0; i24 < nx; i24++) {
    M0->data[i24] = 0.0;
  }

  emxInit_real_T(&G1_y, 2);
  i24 = G1_y->size[0] * G1_y->size[1];
  G1_y->size[0] = t->size[1] - 1;
  G1_y->size[1] = A->size[0];
  emxEnsureCapacity((emxArray__common *)G1_y, i24, (int)sizeof(double));
  nx = (t->size[1] - 1) * A->size[0];
  for (i24 = 0; i24 < nx; i24++) {
    G1_y->data[i24] = 0.0;
  }

  emxInit_real_T(&G2_u, 2);
  i24 = G2_u->size[0] * G2_u->size[1];
  G2_u->size[0] = t->size[1] - 1;
  G2_u->size[1] = A->size[0];
  emxEnsureCapacity((emxArray__common *)G2_u, i24, (int)sizeof(double));
  nx = (t->size[1] - 1) * A->size[0];
  for (i24 = 0; i24 < nx; i24++) {
    G2_u->data[i24] = 0.0;
  }

  i = 0;
  emxInit_int32_T1(&r14, 1);
  emxInit_real_T(&b_C, 2);
  emxInit_int32_T1(&r15, 1);
  emxInit_real_T(&b_y, 2);
  emxInit_real_T(&a, 2);
  emxInit_real_T(&c_y, 2);
  emxInit_real_T(&b, 2);
  emxInit_real_T(&b_A, 2);
  emxInit_real_T(&c_A, 2);
  while (i <= t->size[1] - 1) {
    nx = M0->size[1];
    i24 = r15->size[0];
    r15->size[0] = nx;
    emxEnsureCapacity((emxArray__common *)r15, i24, (int)sizeof(int));
    for (i24 = 0; i24 < nx; i24++) {
      r15->data[i24] = i24;
    }

    nx = M0->size[2];
    i24 = r14->size[0];
    r14->size[0] = nx;
    emxEnsureCapacity((emxArray__common *)r14, i24, (int)sizeof(int));
    for (i24 = 0; i24 < nx; i24++) {
      r14->data[i24] = i24;
    }

    i24 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = C->size[1];
    b_y->size[1] = C->size[1];
    emxEnsureCapacity((emxArray__common *)b_y, i24, (int)sizeof(double));
    nx = C->size[1];
    for (i24 = 0; i24 < nx; i24++) {
      ic = C->size[1];
      for (i25 = 0; i25 < ic; i25++) {
        b_y->data[i24 + b_y->size[0] * i25] = C->data[C->size[0] * i24] *
          C->data[C->size[0] * i25];
      }
    }

    b_t = t->data[i];
    i24 = c_A->size[0] * c_A->size[1];
    c_A->size[0] = A->size[1];
    c_A->size[1] = A->size[0];
    emxEnsureCapacity((emxArray__common *)c_A, i24, (int)sizeof(double));
    nx = A->size[0];
    for (i24 = 0; i24 < nx; i24++) {
      ic = A->size[1];
      for (i25 = 0; i25 < ic; i25++) {
        c_A->data[i25 + c_A->size[0] * i24] = A->data[i24 + A->size[0] * i25] *
          b_t;
      }
    }

    expm(c_A, a);
    if ((a->size[1] == 1) || (b_y->size[0] == 1)) {
      i24 = c_y->size[0] * c_y->size[1];
      c_y->size[0] = a->size[0];
      c_y->size[1] = b_y->size[1];
      emxEnsureCapacity((emxArray__common *)c_y, i24, (int)sizeof(double));
      nx = a->size[0];
      for (i24 = 0; i24 < nx; i24++) {
        ic = b_y->size[1];
        for (i25 = 0; i25 < ic; i25++) {
          c_y->data[i24 + c_y->size[0] * i25] = 0.0;
          br = a->size[1];
          for (ib = 0; ib < br; ib++) {
            c_y->data[i24 + c_y->size[0] * i25] += a->data[i24 + a->size[0] * ib]
              * b_y->data[ib + b_y->size[0] * i25];
          }
        }
      }
    } else {
      k = a->size[1];
      a_idx_0 = (unsigned int)a->size[0];
      unnamed_idx_1 = (unsigned int)b_y->size[1];
      i24 = c_y->size[0] * c_y->size[1];
      c_y->size[0] = (int)a_idx_0;
      c_y->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)c_y, i24, (int)sizeof(double));
      m = a->size[0];
      i24 = c_y->size[0] * c_y->size[1];
      emxEnsureCapacity((emxArray__common *)c_y, i24, (int)sizeof(double));
      nx = c_y->size[1];
      for (i24 = 0; i24 < nx; i24++) {
        ic = c_y->size[0];
        for (i25 = 0; i25 < ic; i25++) {
          c_y->data[i25 + c_y->size[0] * i24] = 0.0;
        }
      }

      if ((a->size[0] == 0) || (b_y->size[1] == 0)) {
      } else {
        c = a->size[0] * (b_y->size[1] - 1);
        nx = 0;
        while ((m > 0) && (nx <= c)) {
          i24 = nx + m;
          for (ic = nx; ic + 1 <= i24; ic++) {
            c_y->data[ic] = 0.0;
          }

          nx += m;
        }

        br = 0;
        nx = 0;
        while ((m > 0) && (nx <= c)) {
          ar = -1;
          i24 = br + k;
          for (ib = br; ib + 1 <= i24; ib++) {
            if (b_y->data[ib] != 0.0) {
              ia = ar;
              i25 = nx + m;
              for (ic = nx; ic + 1 <= i25; ic++) {
                ia++;
                c_y->data[ic] += b_y->data[ib] * a->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          nx += m;
        }
      }
    }

    i24 = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)b_A, i24, (int)sizeof(double));
    b_t = t->data[i];
    nx = A->size[0] * A->size[1];
    for (i24 = 0; i24 < nx; i24++) {
      b_A->data[i24] = A->data[i24] * b_t;
    }

    expm(b_A, b);
    if ((c_y->size[1] == 1) || (b->size[0] == 1)) {
      i24 = b_C->size[0] * b_C->size[1];
      b_C->size[0] = c_y->size[0];
      b_C->size[1] = b->size[1];
      emxEnsureCapacity((emxArray__common *)b_C, i24, (int)sizeof(double));
      nx = c_y->size[0];
      for (i24 = 0; i24 < nx; i24++) {
        ic = b->size[1];
        for (i25 = 0; i25 < ic; i25++) {
          b_C->data[i24 + b_C->size[0] * i25] = 0.0;
          br = c_y->size[1];
          for (ib = 0; ib < br; ib++) {
            b_C->data[i24 + b_C->size[0] * i25] += c_y->data[i24 + c_y->size[0] *
              ib] * b->data[ib + b->size[0] * i25];
          }
        }
      }
    } else {
      k = c_y->size[1];
      a_idx_0 = (unsigned int)c_y->size[0];
      unnamed_idx_1 = (unsigned int)b->size[1];
      i24 = b_C->size[0] * b_C->size[1];
      b_C->size[0] = (int)a_idx_0;
      b_C->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)b_C, i24, (int)sizeof(double));
      m = c_y->size[0];
      i24 = b_C->size[0] * b_C->size[1];
      emxEnsureCapacity((emxArray__common *)b_C, i24, (int)sizeof(double));
      nx = b_C->size[1];
      for (i24 = 0; i24 < nx; i24++) {
        ic = b_C->size[0];
        for (i25 = 0; i25 < ic; i25++) {
          b_C->data[i25 + b_C->size[0] * i24] = 0.0;
        }
      }

      if ((c_y->size[0] == 0) || (b->size[1] == 0)) {
      } else {
        c = c_y->size[0] * (b->size[1] - 1);
        nx = 0;
        while ((m > 0) && (nx <= c)) {
          i24 = nx + m;
          for (ic = nx; ic + 1 <= i24; ic++) {
            b_C->data[ic] = 0.0;
          }

          nx += m;
        }

        br = 0;
        nx = 0;
        while ((m > 0) && (nx <= c)) {
          ar = -1;
          i24 = br + k;
          for (ib = br; ib + 1 <= i24; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              i25 = nx + m;
              for (ic = nx; ic + 1 <= i25; ic++) {
                ia++;
                b_C->data[ic] += b->data[ib] * c_y->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          nx += m;
        }
      }
    }

    nx = r15->size[0];
    br = r14->size[0];
    for (i24 = 0; i24 < br; i24++) {
      for (i25 = 0; i25 < nx; i25++) {
        M0->data[(i + M0->size[0] * r15->data[i25]) + M0->size[0] * M0->size[1] *
          r14->data[i24]] = b_C->data[i25 + nx * i24];
      }
    }

    i++;
  }

  emxFree_real_T(&c_A);
  emxFree_real_T(&b_A);
  emxFree_real_T(&b_C);
  emxFree_int32_T(&r14);
  emxInit_real_T2(&M0_, 3);
  trapz(t, M0, M0_);

  /* M0= */
  i = 0;
  emxInit_real_T1(&c_C, 1);
  emxInit_real_T1(&d_y, 1);
  emxInit_real_T1(&b_b, 1);
  emxInit_real_T2(&x, 3);
  emxInit_real_T(&e_y, 2);
  emxInit_real_T(&f_y, 2);
  emxInit_real_T(&d_A, 2);
  emxInit_real_T(&c_t, 2);
  emxInit_real_T2(&b_M0, 3);
  emxInit_real_T(&e_A, 2);
  emxInit_real_T1(&g_y, 1);
  while (i <= t->size[1] - 2) {
    nx = G1_y->size[1];
    i24 = r15->size[0];
    r15->size[0] = nx;
    emxEnsureCapacity((emxArray__common *)r15, i24, (int)sizeof(int));
    for (i24 = 0; i24 < nx; i24++) {
      r15->data[i24] = i24;
    }

    nx = M0_->size[1] * M0_->size[2];
    i24 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = n;
    b_y->size[1] = n;
    emxEnsureCapacity((emxArray__common *)b_y, i24, (int)sizeof(double));
    for (k = 0; k + 1 <= nx; k++) {
      b_y->data[k] = M0_->data[k];
    }

    b_t = t->data[i];
    i24 = e_A->size[0] * e_A->size[1];
    e_A->size[0] = A->size[1];
    e_A->size[1] = A->size[0];
    emxEnsureCapacity((emxArray__common *)e_A, i24, (int)sizeof(double));
    nx = A->size[0];
    for (i24 = 0; i24 < nx; i24++) {
      ic = A->size[1];
      for (i25 = 0; i25 < ic; i25++) {
        e_A->data[i25 + e_A->size[0] * i24] = A->data[i24 + A->size[0] * i25] *
          b_t;
      }
    }

    expm(e_A, b);
    mldivide(b_y, b, a);
    i24 = b_b->size[0];
    b_b->size[0] = C->size[1];
    emxEnsureCapacity((emxArray__common *)b_b, i24, (int)sizeof(double));
    nx = C->size[1];
    for (i24 = 0; i24 < nx; i24++) {
      b_b->data[i24] = C->data[C->size[0] * i24];
    }

    if ((a->size[1] == 1) || (b_b->size[0] == 1)) {
      i24 = d_y->size[0];
      d_y->size[0] = a->size[0];
      emxEnsureCapacity((emxArray__common *)d_y, i24, (int)sizeof(double));
      nx = a->size[0];
      for (i24 = 0; i24 < nx; i24++) {
        d_y->data[i24] = 0.0;
        ic = a->size[1];
        for (i25 = 0; i25 < ic; i25++) {
          d_y->data[i24] += a->data[i24 + a->size[0] * i25] * b_b->data[i25];
        }
      }
    } else {
      k = a->size[1];
      a_idx_0 = (unsigned int)a->size[0];
      i24 = d_y->size[0];
      d_y->size[0] = (int)a_idx_0;
      emxEnsureCapacity((emxArray__common *)d_y, i24, (int)sizeof(double));
      m = a->size[0];
      nx = d_y->size[0];
      i24 = d_y->size[0];
      d_y->size[0] = nx;
      emxEnsureCapacity((emxArray__common *)d_y, i24, (int)sizeof(double));
      for (i24 = 0; i24 < nx; i24++) {
        d_y->data[i24] = 0.0;
      }

      if (a->size[0] == 0) {
      } else {
        nx = 0;
        while ((m > 0) && (nx <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            d_y->data[ic - 1] = 0.0;
          }

          nx = m;
        }

        br = 0;
        nx = 0;
        while ((m > 0) && (nx <= 0)) {
          ar = -1;
          i24 = br + k;
          for (ib = br; ib + 1 <= i24; ib++) {
            if (b_b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                d_y->data[ic] += b_b->data[ib] * a->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          nx = m;
        }
      }
    }

    b_t = y->data[i];
    i24 = g_y->size[0];
    g_y->size[0] = d_y->size[0];
    emxEnsureCapacity((emxArray__common *)g_y, i24, (int)sizeof(double));
    nx = d_y->size[0];
    for (i24 = 0; i24 < nx; i24++) {
      g_y->data[i24] = d_y->data[i24] * b_t;
    }

    nx = r15->size[0];
    for (i24 = 0; i24 < nx; i24++) {
      G1_y->data[i + G1_y->size[0] * r15->data[i24]] = g_y->data[i24];
    }

    if (1 + i > t->size[1]) {
      i24 = 1;
      i25 = 0;
    } else {
      i24 = i + 1;
      i25 = t->size[1];
    }

    if (1 + i > M0->size[0]) {
      ib = 1;
      ia = 0;
    } else {
      ib = i + 1;
      ia = M0->size[0];
    }

    nx = G2_u->size[1];
    ar = r15->size[0];
    r15->size[0] = nx;
    emxEnsureCapacity((emxArray__common *)r15, ar, (int)sizeof(int));
    for (ar = 0; ar < nx; ar++) {
      r15->data[ar] = ar;
    }

    nx = M0_->size[1] * M0_->size[2];
    ar = b_y->size[0] * b_y->size[1];
    b_y->size[0] = n;
    b_y->size[1] = n;
    emxEnsureCapacity((emxArray__common *)b_y, ar, (int)sizeof(double));
    for (k = 0; k + 1 <= nx; k++) {
      b_y->data[k] = M0_->data[k];
    }

    ar = c_t->size[0] * c_t->size[1];
    c_t->size[0] = 1;
    c_t->size[1] = (i25 - i24) + 1;
    emxEnsureCapacity((emxArray__common *)c_t, ar, (int)sizeof(double));
    nx = (i25 - i24) + 1;
    for (i25 = 0; i25 < nx; i25++) {
      c_t->data[c_t->size[0] * i25] = t->data[(i24 + i25) - 1];
    }

    nx = M0->size[1];
    ic = M0->size[2];
    i24 = b_M0->size[0] * b_M0->size[1] * b_M0->size[2];
    b_M0->size[0] = (ia - ib) + 1;
    b_M0->size[1] = nx;
    b_M0->size[2] = ic;
    emxEnsureCapacity((emxArray__common *)b_M0, i24, (int)sizeof(double));
    for (i24 = 0; i24 < ic; i24++) {
      for (i25 = 0; i25 < nx; i25++) {
        br = (ia - ib) + 1;
        for (ar = 0; ar < br; ar++) {
          b_M0->data[(ar + b_M0->size[0] * i25) + b_M0->size[0] * b_M0->size[1] *
            i24] = M0->data[(((ib + ar) + M0->size[0] * i25) + M0->size[0] *
                             M0->size[1] * i24) - 1];
        }
      }
    }

    trapz(c_t, b_M0, x);
    nx = x->size[1] * x->size[2];
    i24 = c_y->size[0] * c_y->size[1];
    c_y->size[0] = n;
    c_y->size[1] = n;
    emxEnsureCapacity((emxArray__common *)c_y, i24, (int)sizeof(double));
    for (k = 0; k + 1 <= nx; k++) {
      c_y->data[k] = x->data[k];
    }

    mldivide(b_y, c_y, a);
    i24 = d_A->size[0] * d_A->size[1];
    d_A->size[0] = A->size[0];
    d_A->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)d_A, i24, (int)sizeof(double));
    b_t = t->data[i];
    nx = A->size[0] * A->size[1];
    for (i24 = 0; i24 < nx; i24++) {
      d_A->data[i24] = -A->data[i24] * b_t;
    }

    expm(d_A, b);
    if ((a->size[1] == 1) || (b->size[0] == 1)) {
      i24 = e_y->size[0] * e_y->size[1];
      e_y->size[0] = a->size[0];
      e_y->size[1] = b->size[1];
      emxEnsureCapacity((emxArray__common *)e_y, i24, (int)sizeof(double));
      nx = a->size[0];
      for (i24 = 0; i24 < nx; i24++) {
        ic = b->size[1];
        for (i25 = 0; i25 < ic; i25++) {
          e_y->data[i24 + e_y->size[0] * i25] = 0.0;
          br = a->size[1];
          for (ib = 0; ib < br; ib++) {
            e_y->data[i24 + e_y->size[0] * i25] += a->data[i24 + a->size[0] * ib]
              * b->data[ib + b->size[0] * i25];
          }
        }
      }
    } else {
      k = a->size[1];
      a_idx_0 = (unsigned int)a->size[0];
      unnamed_idx_1 = (unsigned int)b->size[1];
      i24 = e_y->size[0] * e_y->size[1];
      e_y->size[0] = (int)a_idx_0;
      e_y->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)e_y, i24, (int)sizeof(double));
      m = a->size[0];
      i24 = e_y->size[0] * e_y->size[1];
      emxEnsureCapacity((emxArray__common *)e_y, i24, (int)sizeof(double));
      nx = e_y->size[1];
      for (i24 = 0; i24 < nx; i24++) {
        ic = e_y->size[0];
        for (i25 = 0; i25 < ic; i25++) {
          e_y->data[i25 + e_y->size[0] * i24] = 0.0;
        }
      }

      if ((a->size[0] == 0) || (b->size[1] == 0)) {
      } else {
        c = a->size[0] * (b->size[1] - 1);
        nx = 0;
        while ((m > 0) && (nx <= c)) {
          i24 = nx + m;
          for (ic = nx; ic + 1 <= i24; ic++) {
            e_y->data[ic] = 0.0;
          }

          nx += m;
        }

        br = 0;
        nx = 0;
        while ((m > 0) && (nx <= c)) {
          ar = -1;
          i24 = br + k;
          for (ib = br; ib + 1 <= i24; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              i25 = nx + m;
              for (ic = nx; ic + 1 <= i25; ic++) {
                ia++;
                e_y->data[ic] += b->data[ib] * a->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          nx += m;
        }
      }
    }

    if ((e_y->size[1] == 1) || (B->size[0] == 1)) {
      i24 = f_y->size[0] * f_y->size[1];
      f_y->size[0] = e_y->size[0];
      f_y->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)f_y, i24, (int)sizeof(double));
      nx = e_y->size[0];
      for (i24 = 0; i24 < nx; i24++) {
        for (i25 = 0; i25 < 2; i25++) {
          f_y->data[i24 + f_y->size[0] * i25] = 0.0;
          ic = e_y->size[1];
          for (ib = 0; ib < ic; ib++) {
            f_y->data[i24 + f_y->size[0] * i25] += e_y->data[i24 + e_y->size[0] *
              ib] * B->data[ib + B->size[0] * i25];
          }
        }
      }
    } else {
      k = e_y->size[1];
      a_idx_0 = (unsigned int)e_y->size[0];
      i24 = f_y->size[0] * f_y->size[1];
      f_y->size[0] = (int)a_idx_0;
      f_y->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)f_y, i24, (int)sizeof(double));
      m = e_y->size[0];
      i24 = f_y->size[0] * f_y->size[1];
      f_y->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)f_y, i24, (int)sizeof(double));
      for (i24 = 0; i24 < 2; i24++) {
        nx = f_y->size[0];
        for (i25 = 0; i25 < nx; i25++) {
          f_y->data[i25 + f_y->size[0] * i24] = 0.0;
        }
      }

      if (e_y->size[0] == 0) {
      } else {
        nx = 0;
        while ((m > 0) && (nx <= m)) {
          i24 = nx + m;
          for (ic = nx; ic + 1 <= i24; ic++) {
            f_y->data[ic] = 0.0;
          }

          nx += m;
        }

        br = 0;
        nx = 0;
        while ((m > 0) && (nx <= m)) {
          ar = -1;
          i24 = br + k;
          for (ib = br; ib + 1 <= i24; ib++) {
            if (B->data[ib] != 0.0) {
              ia = ar;
              i25 = nx + m;
              for (ic = nx; ic + 1 <= i25; ic++) {
                ia++;
                f_y->data[ic] += B->data[ib] * e_y->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          nx += m;
        }
      }
    }

    a_idx_0 = (unsigned int)f_y->size[0];
    i24 = c_C->size[0];
    c_C->size[0] = (int)a_idx_0;
    emxEnsureCapacity((emxArray__common *)c_C, i24, (int)sizeof(double));
    m = f_y->size[0];
    nx = c_C->size[0];
    i24 = c_C->size[0];
    c_C->size[0] = nx;
    emxEnsureCapacity((emxArray__common *)c_C, i24, (int)sizeof(double));
    for (i24 = 0; i24 < nx; i24++) {
      c_C->data[i24] = 0.0;
    }

    if (f_y->size[0] == 0) {
    } else {
      nx = 0;
      while ((m > 0) && (nx <= 0)) {
        for (ic = 1; ic <= m; ic++) {
          c_C->data[ic - 1] = 0.0;
        }

        nx = m;
      }

      br = 0;
      nx = 0;
      while ((m > 0) && (nx <= 0)) {
        ar = -1;
        for (ib = br; ib + 1 <= br + 2; ib++) {
          if (u->data[i + u->size[0] * ib] != 0.0) {
            ia = ar;
            for (ic = 0; ic + 1 <= m; ic++) {
              ia++;
              c_C->data[ic] += u->data[i + u->size[0] * ib] * f_y->data[ia];
            }
          }

          ar += m;
        }

        br += 2;
        nx = m;
      }
    }

    nx = r15->size[0];
    for (i24 = 0; i24 < nx; i24++) {
      G2_u->data[i + G2_u->size[0] * r15->data[i24]] = c_C->data[i24];
    }

    i++;
  }

  emxFree_real_T(&g_y);
  emxFree_real_T(&e_A);
  emxFree_real_T(&b_M0);
  emxFree_real_T(&c_t);
  emxFree_real_T(&d_A);
  emxFree_real_T(&f_y);
  emxFree_real_T(&b);
  emxFree_real_T(&e_y);
  emxFree_real_T(&x);
  emxFree_real_T(&c_y);
  emxFree_real_T(&b_b);
  emxFree_real_T(&a);
  emxFree_real_T(&d_y);
  emxFree_real_T(&b_y);
  emxFree_real_T(&c_C);
  emxFree_int32_T(&r15);
  emxFree_real_T(&M0_);
  emxFree_real_T(&M0);
  if (1 > t->size[1] - 1) {
    i24 = 0;
  } else {
    i24 = t->size[1] - 1;
  }

  emxInit_real_T(&r16, 2);
  emxInit_real_T(&r17, 2);
  i25 = t->size[0] * t->size[1];
  t->size[1] = i24;
  emxEnsureCapacity((emxArray__common *)t, i25, (int)sizeof(double));

  /* disp('X start'); */
  b_trapz(t, G1_y, r16);
  b_trapz(t, G2_u, r17);
  i24 = X_0->size[0];
  X_0->size[0] = r16->size[1];
  emxEnsureCapacity((emxArray__common *)X_0, i24, (int)sizeof(double));
  nx = r16->size[1];
  emxFree_real_T(&G2_u);
  emxFree_real_T(&G1_y);
  for (i24 = 0; i24 < nx; i24++) {
    X_0->data[i24] = r16->data[r16->size[0] * i24] + r17->data[r17->size[0] *
      i24];
  }

  emxFree_real_T(&r17);
  emxFree_real_T(&r16);
}

/*
 * File trailer for FHZN_exact_state_observer_initial.c
 *
 * [EOF]
 */
