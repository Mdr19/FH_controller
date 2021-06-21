/*
 * File: FHZN_exact_state_observer_final.c
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
#include "FHZN_exact_state_observer_final.h"
#include "FHZN_define_model_del_emxutil.h"
#include "expm.h"
#include "mrdivide.h"
#include "trapz.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                const emxArray_real_T *C
 *                const emxArray_real_T *t
 *                const emxArray_real_T *u
 *                const emxArray_real_T *y
 *                emxArray_real_T *X_T
 * Return Type  : void
 */
void FHZN_exact_state_observer_final(const emxArray_real_T *A, const
  emxArray_real_T *B, const emxArray_real_T *C, const emxArray_real_T *t, const
  emxArray_real_T *u, const emxArray_real_T *y, emxArray_real_T *X_T)
{
  emxArray_real_T *M0;
  int n;
  int i45;
  int br;
  emxArray_real_T *G1_y;
  emxArray_real_T *G2_u;
  int i;
  emxArray_int32_T *r23;
  emxArray_real_T *b_C;
  emxArray_int32_T *r24;
  emxArray_real_T *b_y;
  emxArray_real_T *a;
  emxArray_real_T *b;
  emxArray_real_T *c_y;
  emxArray_real_T *b_A;
  emxArray_real_T *c_A;
  int ar;
  int i46;
  double b_t;
  int nx;
  int cr;
  int k;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  int m;
  int ic;
  int ib;
  int ia;
  emxArray_real_T *M0_;
  emxArray_real_T *c_C;
  emxArray_real_T *d_y;
  emxArray_real_T *e_y;
  emxArray_real_T *b_b;
  emxArray_real_T *x;
  emxArray_real_T *f_y;
  emxArray_real_T *g_y;
  emxArray_real_T *h_y;
  emxArray_real_T *d_A;
  emxArray_real_T *e_A;
  emxArray_real_T *c_t;
  emxArray_real_T *b_M0;
  emxArray_real_T *f_A;
  emxArray_real_T *g_A;
  emxArray_real_T *i_y;
  emxArray_real_T *r25;
  emxArray_real_T *r26;
  emxInit_real_T2(&M0, 3);
  n = A->size[0];
  i45 = M0->size[0] * M0->size[1] * M0->size[2];
  M0->size[0] = t->size[1];
  M0->size[1] = A->size[0];
  M0->size[2] = A->size[0];
  emxEnsureCapacity((emxArray__common *)M0, i45, (int)sizeof(double));
  br = t->size[1] * A->size[0] * A->size[0];
  for (i45 = 0; i45 < br; i45++) {
    M0->data[i45] = 0.0;
  }

  emxInit_real_T(&G1_y, 2);
  i45 = G1_y->size[0] * G1_y->size[1];
  G1_y->size[0] = y->size[0];
  G1_y->size[1] = A->size[0];
  emxEnsureCapacity((emxArray__common *)G1_y, i45, (int)sizeof(double));
  br = y->size[0] * A->size[0];
  for (i45 = 0; i45 < br; i45++) {
    G1_y->data[i45] = 0.0;
  }

  emxInit_real_T(&G2_u, 2);
  i45 = G2_u->size[0] * G2_u->size[1];
  G2_u->size[0] = y->size[0];
  G2_u->size[1] = A->size[0];
  emxEnsureCapacity((emxArray__common *)G2_u, i45, (int)sizeof(double));
  br = y->size[0] * A->size[0];
  for (i45 = 0; i45 < br; i45++) {
    G2_u->data[i45] = 0.0;
  }

  i = 0;
  emxInit_int32_T1(&r23, 1);
  emxInit_real_T(&b_C, 2);
  emxInit_int32_T1(&r24, 1);
  emxInit_real_T(&b_y, 2);
  emxInit_real_T(&a, 2);
  emxInit_real_T(&b, 2);
  emxInit_real_T(&c_y, 2);
  emxInit_real_T(&b_A, 2);
  emxInit_real_T(&c_A, 2);
  while (i <= t->size[1] - 1) {
    br = M0->size[1];
    i45 = r24->size[0];
    r24->size[0] = br;
    emxEnsureCapacity((emxArray__common *)r24, i45, (int)sizeof(int));
    for (i45 = 0; i45 < br; i45++) {
      r24->data[i45] = i45;
    }

    br = M0->size[2];
    i45 = r23->size[0];
    r23->size[0] = br;
    emxEnsureCapacity((emxArray__common *)r23, i45, (int)sizeof(int));
    for (i45 = 0; i45 < br; i45++) {
      r23->data[i45] = i45;
    }

    i45 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = C->size[1];
    b_y->size[1] = C->size[1];
    emxEnsureCapacity((emxArray__common *)b_y, i45, (int)sizeof(double));
    br = C->size[1];
    for (i45 = 0; i45 < br; i45++) {
      ar = C->size[1];
      for (i46 = 0; i46 < ar; i46++) {
        b_y->data[i45 + b_y->size[0] * i46] = C->data[C->size[0] * i45] *
          C->data[C->size[0] * i46];
      }
    }

    b_t = t->data[i];
    i45 = c_A->size[0] * c_A->size[1];
    c_A->size[0] = A->size[1];
    c_A->size[1] = A->size[0];
    emxEnsureCapacity((emxArray__common *)c_A, i45, (int)sizeof(double));
    br = A->size[0];
    for (i45 = 0; i45 < br; i45++) {
      ar = A->size[1];
      for (i46 = 0; i46 < ar; i46++) {
        c_A->data[i46 + c_A->size[0] * i45] = A->data[i45 + A->size[0] * i46] *
          b_t;
      }
    }

    expm(c_A, a);
    if ((a->size[1] == 1) || (b_y->size[0] == 1)) {
      i45 = c_y->size[0] * c_y->size[1];
      c_y->size[0] = a->size[0];
      c_y->size[1] = b_y->size[1];
      emxEnsureCapacity((emxArray__common *)c_y, i45, (int)sizeof(double));
      br = a->size[0];
      for (i45 = 0; i45 < br; i45++) {
        ar = b_y->size[1];
        for (i46 = 0; i46 < ar; i46++) {
          c_y->data[i45 + c_y->size[0] * i46] = 0.0;
          nx = a->size[1];
          for (cr = 0; cr < nx; cr++) {
            c_y->data[i45 + c_y->size[0] * i46] += a->data[i45 + a->size[0] * cr]
              * b_y->data[cr + b_y->size[0] * i46];
          }
        }
      }
    } else {
      k = a->size[1];
      unnamed_idx_0 = (unsigned int)a->size[0];
      unnamed_idx_1 = (unsigned int)b_y->size[1];
      i45 = c_y->size[0] * c_y->size[1];
      c_y->size[0] = (int)unnamed_idx_0;
      c_y->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)c_y, i45, (int)sizeof(double));
      m = a->size[0];
      i45 = c_y->size[0] * c_y->size[1];
      emxEnsureCapacity((emxArray__common *)c_y, i45, (int)sizeof(double));
      br = c_y->size[1];
      for (i45 = 0; i45 < br; i45++) {
        ar = c_y->size[0];
        for (i46 = 0; i46 < ar; i46++) {
          c_y->data[i46 + c_y->size[0] * i45] = 0.0;
        }
      }

      if ((a->size[0] == 0) || (b_y->size[1] == 0)) {
      } else {
        nx = a->size[0] * (b_y->size[1] - 1);
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          i45 = cr + m;
          for (ic = cr; ic + 1 <= i45; ic++) {
            c_y->data[ic] = 0.0;
          }

          cr += m;
        }

        br = 0;
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          ar = -1;
          i45 = br + k;
          for (ib = br; ib + 1 <= i45; ib++) {
            if (b_y->data[ib] != 0.0) {
              ia = ar;
              i46 = cr + m;
              for (ic = cr; ic + 1 <= i46; ic++) {
                ia++;
                c_y->data[ic] += b_y->data[ib] * a->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          cr += m;
        }
      }
    }

    i45 = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)b_A, i45, (int)sizeof(double));
    b_t = t->data[i];
    br = A->size[0] * A->size[1];
    for (i45 = 0; i45 < br; i45++) {
      b_A->data[i45] = A->data[i45] * b_t;
    }

    expm(b_A, b);
    if ((c_y->size[1] == 1) || (b->size[0] == 1)) {
      i45 = b_C->size[0] * b_C->size[1];
      b_C->size[0] = c_y->size[0];
      b_C->size[1] = b->size[1];
      emxEnsureCapacity((emxArray__common *)b_C, i45, (int)sizeof(double));
      br = c_y->size[0];
      for (i45 = 0; i45 < br; i45++) {
        ar = b->size[1];
        for (i46 = 0; i46 < ar; i46++) {
          b_C->data[i45 + b_C->size[0] * i46] = 0.0;
          nx = c_y->size[1];
          for (cr = 0; cr < nx; cr++) {
            b_C->data[i45 + b_C->size[0] * i46] += c_y->data[i45 + c_y->size[0] *
              cr] * b->data[cr + b->size[0] * i46];
          }
        }
      }
    } else {
      k = c_y->size[1];
      unnamed_idx_0 = (unsigned int)c_y->size[0];
      unnamed_idx_1 = (unsigned int)b->size[1];
      i45 = b_C->size[0] * b_C->size[1];
      b_C->size[0] = (int)unnamed_idx_0;
      b_C->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)b_C, i45, (int)sizeof(double));
      m = c_y->size[0];
      i45 = b_C->size[0] * b_C->size[1];
      emxEnsureCapacity((emxArray__common *)b_C, i45, (int)sizeof(double));
      br = b_C->size[1];
      for (i45 = 0; i45 < br; i45++) {
        ar = b_C->size[0];
        for (i46 = 0; i46 < ar; i46++) {
          b_C->data[i46 + b_C->size[0] * i45] = 0.0;
        }
      }

      if ((c_y->size[0] == 0) || (b->size[1] == 0)) {
      } else {
        nx = c_y->size[0] * (b->size[1] - 1);
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          i45 = cr + m;
          for (ic = cr; ic + 1 <= i45; ic++) {
            b_C->data[ic] = 0.0;
          }

          cr += m;
        }

        br = 0;
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          ar = -1;
          i45 = br + k;
          for (ib = br; ib + 1 <= i45; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              i46 = cr + m;
              for (ic = cr; ic + 1 <= i46; ic++) {
                ia++;
                b_C->data[ic] += b->data[ib] * c_y->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          cr += m;
        }
      }
    }

    nx = r24->size[0];
    cr = r23->size[0];
    for (i45 = 0; i45 < cr; i45++) {
      for (i46 = 0; i46 < nx; i46++) {
        M0->data[(i + M0->size[0] * r24->data[i46]) + M0->size[0] * M0->size[1] *
          r23->data[i45]] = b_C->data[i46 + nx * i45];
      }
    }

    i++;
  }

  emxFree_real_T(&c_A);
  emxFree_real_T(&b_A);
  emxFree_real_T(&b_C);
  emxFree_int32_T(&r23);
  emxInit_real_T2(&M0_, 3);
  trapz(t, M0, M0_);
  i = 1;
  emxInit_real_T1(&c_C, 1);
  emxInit_real_T(&d_y, 2);
  emxInit_real_T1(&e_y, 1);
  emxInit_real_T1(&b_b, 1);
  emxInit_real_T2(&x, 3);
  emxInit_real_T(&f_y, 2);
  emxInit_real_T(&g_y, 2);
  emxInit_real_T(&h_y, 2);
  emxInit_real_T(&d_A, 2);
  emxInit_real_T(&e_A, 2);
  emxInit_real_T(&c_t, 2);
  emxInit_real_T2(&b_M0, 3);
  emxInit_real_T(&f_A, 2);
  emxInit_real_T(&g_A, 2);
  emxInit_real_T1(&i_y, 1);
  while (i - 1 <= t->size[1] - 2) {
    br = G1_y->size[1];
    i45 = r24->size[0];
    r24->size[0] = br;
    emxEnsureCapacity((emxArray__common *)r24, i45, (int)sizeof(int));
    for (i45 = 0; i45 < br; i45++) {
      r24->data[i45] = i45;
    }

    nx = M0_->size[1] * M0_->size[2];
    i45 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = n;
    b_y->size[1] = n;
    emxEnsureCapacity((emxArray__common *)b_y, i45, (int)sizeof(double));
    for (k = 0; k + 1 <= nx; k++) {
      b_y->data[k] = M0_->data[k];
    }

    i45 = g_A->size[0] * g_A->size[1];
    g_A->size[0] = A->size[0];
    g_A->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)g_A, i45, (int)sizeof(double));
    b_t = t->data[t->size[1] - 1];
    br = A->size[0] * A->size[1];
    for (i45 = 0; i45 < br; i45++) {
      g_A->data[i45] = A->data[i45] * b_t;
    }

    expm(g_A, b);
    mrdivide(b, b_y, a);
    b_t = t->data[i];
    i45 = f_A->size[0] * f_A->size[1];
    f_A->size[0] = A->size[1];
    f_A->size[1] = A->size[0];
    emxEnsureCapacity((emxArray__common *)f_A, i45, (int)sizeof(double));
    br = A->size[0];
    for (i45 = 0; i45 < br; i45++) {
      ar = A->size[1];
      for (i46 = 0; i46 < ar; i46++) {
        f_A->data[i46 + f_A->size[0] * i45] = A->data[i45 + A->size[0] * i46] *
          b_t;
      }
    }

    expm(f_A, b);
    if ((a->size[1] == 1) || (b->size[0] == 1)) {
      i45 = d_y->size[0] * d_y->size[1];
      d_y->size[0] = a->size[0];
      d_y->size[1] = b->size[1];
      emxEnsureCapacity((emxArray__common *)d_y, i45, (int)sizeof(double));
      br = a->size[0];
      for (i45 = 0; i45 < br; i45++) {
        ar = b->size[1];
        for (i46 = 0; i46 < ar; i46++) {
          d_y->data[i45 + d_y->size[0] * i46] = 0.0;
          nx = a->size[1];
          for (cr = 0; cr < nx; cr++) {
            d_y->data[i45 + d_y->size[0] * i46] += a->data[i45 + a->size[0] * cr]
              * b->data[cr + b->size[0] * i46];
          }
        }
      }
    } else {
      k = a->size[1];
      unnamed_idx_0 = (unsigned int)a->size[0];
      unnamed_idx_1 = (unsigned int)b->size[1];
      i45 = d_y->size[0] * d_y->size[1];
      d_y->size[0] = (int)unnamed_idx_0;
      d_y->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)d_y, i45, (int)sizeof(double));
      m = a->size[0];
      i45 = d_y->size[0] * d_y->size[1];
      emxEnsureCapacity((emxArray__common *)d_y, i45, (int)sizeof(double));
      br = d_y->size[1];
      for (i45 = 0; i45 < br; i45++) {
        ar = d_y->size[0];
        for (i46 = 0; i46 < ar; i46++) {
          d_y->data[i46 + d_y->size[0] * i45] = 0.0;
        }
      }

      if ((a->size[0] == 0) || (b->size[1] == 0)) {
      } else {
        nx = a->size[0] * (b->size[1] - 1);
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          i45 = cr + m;
          for (ic = cr; ic + 1 <= i45; ic++) {
            d_y->data[ic] = 0.0;
          }

          cr += m;
        }

        br = 0;
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          ar = -1;
          i45 = br + k;
          for (ib = br; ib + 1 <= i45; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              i46 = cr + m;
              for (ic = cr; ic + 1 <= i46; ic++) {
                ia++;
                d_y->data[ic] += b->data[ib] * a->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          cr += m;
        }
      }
    }

    i45 = b_b->size[0];
    b_b->size[0] = C->size[1];
    emxEnsureCapacity((emxArray__common *)b_b, i45, (int)sizeof(double));
    br = C->size[1];
    for (i45 = 0; i45 < br; i45++) {
      b_b->data[i45] = C->data[C->size[0] * i45];
    }

    if ((d_y->size[1] == 1) || (b_b->size[0] == 1)) {
      i45 = e_y->size[0];
      e_y->size[0] = d_y->size[0];
      emxEnsureCapacity((emxArray__common *)e_y, i45, (int)sizeof(double));
      br = d_y->size[0];
      for (i45 = 0; i45 < br; i45++) {
        e_y->data[i45] = 0.0;
        ar = d_y->size[1];
        for (i46 = 0; i46 < ar; i46++) {
          e_y->data[i45] += d_y->data[i45 + d_y->size[0] * i46] * b_b->data[i46];
        }
      }
    } else {
      k = d_y->size[1];
      unnamed_idx_0 = (unsigned int)d_y->size[0];
      i45 = e_y->size[0];
      e_y->size[0] = (int)unnamed_idx_0;
      emxEnsureCapacity((emxArray__common *)e_y, i45, (int)sizeof(double));
      m = d_y->size[0];
      nx = e_y->size[0];
      i45 = e_y->size[0];
      e_y->size[0] = nx;
      emxEnsureCapacity((emxArray__common *)e_y, i45, (int)sizeof(double));
      for (i45 = 0; i45 < nx; i45++) {
        e_y->data[i45] = 0.0;
      }

      if (d_y->size[0] == 0) {
      } else {
        cr = 0;
        while ((m > 0) && (cr <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            e_y->data[ic - 1] = 0.0;
          }

          cr = m;
        }

        br = 0;
        cr = 0;
        while ((m > 0) && (cr <= 0)) {
          ar = -1;
          i45 = br + k;
          for (ib = br; ib + 1 <= i45; ib++) {
            if (b_b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                e_y->data[ic] += b_b->data[ib] * d_y->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          cr = m;
        }
      }
    }

    b_t = y->data[i];
    i45 = i_y->size[0];
    i_y->size[0] = e_y->size[0];
    emxEnsureCapacity((emxArray__common *)i_y, i45, (int)sizeof(double));
    br = e_y->size[0];
    for (i45 = 0; i45 < br; i45++) {
      i_y->data[i45] = e_y->data[i45] * b_t;
    }

    nx = r24->size[0];
    for (i45 = 0; i45 < nx; i45++) {
      G1_y->data[i + G1_y->size[0] * r24->data[i45]] = i_y->data[i45];
    }

    br = G2_u->size[1];
    i45 = r24->size[0];
    r24->size[0] = br;
    emxEnsureCapacity((emxArray__common *)r24, i45, (int)sizeof(int));
    for (i45 = 0; i45 < br; i45++) {
      r24->data[i45] = i45;
    }

    nx = M0_->size[1] * M0_->size[2];
    i45 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = n;
    b_y->size[1] = n;
    emxEnsureCapacity((emxArray__common *)b_y, i45, (int)sizeof(double));
    for (k = 0; k + 1 <= nx; k++) {
      b_y->data[k] = M0_->data[k];
    }

    i45 = c_t->size[0] * c_t->size[1];
    c_t->size[0] = 1;
    c_t->size[1] = i + 1;
    emxEnsureCapacity((emxArray__common *)c_t, i45, (int)sizeof(double));
    for (i45 = 0; i45 <= i; i45++) {
      c_t->data[c_t->size[0] * i45] = t->data[i45];
    }

    br = M0->size[1];
    ar = M0->size[2];
    i45 = b_M0->size[0] * b_M0->size[1] * b_M0->size[2];
    b_M0->size[0] = i + 1;
    b_M0->size[1] = br;
    b_M0->size[2] = ar;
    emxEnsureCapacity((emxArray__common *)b_M0, i45, (int)sizeof(double));
    for (i45 = 0; i45 < ar; i45++) {
      for (i46 = 0; i46 < br; i46++) {
        for (cr = 0; cr <= i; cr++) {
          b_M0->data[(cr + b_M0->size[0] * i46) + b_M0->size[0] * b_M0->size[1] *
            i45] = M0->data[(cr + M0->size[0] * i46) + M0->size[0] * M0->size[1]
            * i45];
        }
      }
    }

    trapz(c_t, b_M0, x);
    nx = x->size[1] * x->size[2];
    i45 = c_y->size[0] * c_y->size[1];
    c_y->size[0] = n;
    c_y->size[1] = n;
    emxEnsureCapacity((emxArray__common *)c_y, i45, (int)sizeof(double));
    for (k = 0; k + 1 <= nx; k++) {
      c_y->data[k] = x->data[k];
    }

    i45 = e_A->size[0] * e_A->size[1];
    e_A->size[0] = A->size[0];
    e_A->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)e_A, i45, (int)sizeof(double));
    b_t = t->data[t->size[1] - 1];
    br = A->size[0] * A->size[1];
    for (i45 = 0; i45 < br; i45++) {
      e_A->data[i45] = A->data[i45] * b_t;
    }

    expm(e_A, b);
    mrdivide(b, b_y, a);
    if ((a->size[1] == 1) || (c_y->size[0] == 1)) {
      i45 = f_y->size[0] * f_y->size[1];
      f_y->size[0] = a->size[0];
      f_y->size[1] = c_y->size[1];
      emxEnsureCapacity((emxArray__common *)f_y, i45, (int)sizeof(double));
      br = a->size[0];
      for (i45 = 0; i45 < br; i45++) {
        ar = c_y->size[1];
        for (i46 = 0; i46 < ar; i46++) {
          f_y->data[i45 + f_y->size[0] * i46] = 0.0;
          nx = a->size[1];
          for (cr = 0; cr < nx; cr++) {
            f_y->data[i45 + f_y->size[0] * i46] += a->data[i45 + a->size[0] * cr]
              * c_y->data[cr + c_y->size[0] * i46];
          }
        }
      }
    } else {
      k = a->size[1];
      unnamed_idx_0 = (unsigned int)a->size[0];
      unnamed_idx_1 = (unsigned int)c_y->size[1];
      i45 = f_y->size[0] * f_y->size[1];
      f_y->size[0] = (int)unnamed_idx_0;
      f_y->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)f_y, i45, (int)sizeof(double));
      m = a->size[0];
      i45 = f_y->size[0] * f_y->size[1];
      emxEnsureCapacity((emxArray__common *)f_y, i45, (int)sizeof(double));
      br = f_y->size[1];
      for (i45 = 0; i45 < br; i45++) {
        ar = f_y->size[0];
        for (i46 = 0; i46 < ar; i46++) {
          f_y->data[i46 + f_y->size[0] * i45] = 0.0;
        }
      }

      if ((a->size[0] == 0) || (c_y->size[1] == 0)) {
      } else {
        nx = a->size[0] * (c_y->size[1] - 1);
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          i45 = cr + m;
          for (ic = cr; ic + 1 <= i45; ic++) {
            f_y->data[ic] = 0.0;
          }

          cr += m;
        }

        br = 0;
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          ar = -1;
          i45 = br + k;
          for (ib = br; ib + 1 <= i45; ib++) {
            if (c_y->data[ib] != 0.0) {
              ia = ar;
              i46 = cr + m;
              for (ic = cr; ic + 1 <= i46; ic++) {
                ia++;
                f_y->data[ic] += c_y->data[ib] * a->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          cr += m;
        }
      }
    }

    i45 = d_A->size[0] * d_A->size[1];
    d_A->size[0] = A->size[0];
    d_A->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)d_A, i45, (int)sizeof(double));
    b_t = t->data[i];
    br = A->size[0] * A->size[1];
    for (i45 = 0; i45 < br; i45++) {
      d_A->data[i45] = -A->data[i45] * b_t;
    }

    expm(d_A, b);
    if ((f_y->size[1] == 1) || (b->size[0] == 1)) {
      i45 = g_y->size[0] * g_y->size[1];
      g_y->size[0] = f_y->size[0];
      g_y->size[1] = b->size[1];
      emxEnsureCapacity((emxArray__common *)g_y, i45, (int)sizeof(double));
      br = f_y->size[0];
      for (i45 = 0; i45 < br; i45++) {
        ar = b->size[1];
        for (i46 = 0; i46 < ar; i46++) {
          g_y->data[i45 + g_y->size[0] * i46] = 0.0;
          nx = f_y->size[1];
          for (cr = 0; cr < nx; cr++) {
            g_y->data[i45 + g_y->size[0] * i46] += f_y->data[i45 + f_y->size[0] *
              cr] * b->data[cr + b->size[0] * i46];
          }
        }
      }
    } else {
      k = f_y->size[1];
      unnamed_idx_0 = (unsigned int)f_y->size[0];
      unnamed_idx_1 = (unsigned int)b->size[1];
      i45 = g_y->size[0] * g_y->size[1];
      g_y->size[0] = (int)unnamed_idx_0;
      g_y->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)g_y, i45, (int)sizeof(double));
      m = f_y->size[0];
      i45 = g_y->size[0] * g_y->size[1];
      emxEnsureCapacity((emxArray__common *)g_y, i45, (int)sizeof(double));
      br = g_y->size[1];
      for (i45 = 0; i45 < br; i45++) {
        ar = g_y->size[0];
        for (i46 = 0; i46 < ar; i46++) {
          g_y->data[i46 + g_y->size[0] * i45] = 0.0;
        }
      }

      if ((f_y->size[0] == 0) || (b->size[1] == 0)) {
      } else {
        nx = f_y->size[0] * (b->size[1] - 1);
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          i45 = cr + m;
          for (ic = cr; ic + 1 <= i45; ic++) {
            g_y->data[ic] = 0.0;
          }

          cr += m;
        }

        br = 0;
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          ar = -1;
          i45 = br + k;
          for (ib = br; ib + 1 <= i45; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              i46 = cr + m;
              for (ic = cr; ic + 1 <= i46; ic++) {
                ia++;
                g_y->data[ic] += b->data[ib] * f_y->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          cr += m;
        }
      }
    }

    if ((g_y->size[1] == 1) || (B->size[0] == 1)) {
      i45 = h_y->size[0] * h_y->size[1];
      h_y->size[0] = g_y->size[0];
      h_y->size[1] = B->size[1];
      emxEnsureCapacity((emxArray__common *)h_y, i45, (int)sizeof(double));
      br = g_y->size[0];
      for (i45 = 0; i45 < br; i45++) {
        ar = B->size[1];
        for (i46 = 0; i46 < ar; i46++) {
          h_y->data[i45 + h_y->size[0] * i46] = 0.0;
          nx = g_y->size[1];
          for (cr = 0; cr < nx; cr++) {
            h_y->data[i45 + h_y->size[0] * i46] += g_y->data[i45 + g_y->size[0] *
              cr] * B->data[cr + B->size[0] * i46];
          }
        }
      }
    } else {
      k = g_y->size[1];
      unnamed_idx_0 = (unsigned int)g_y->size[0];
      unnamed_idx_1 = (unsigned int)B->size[1];
      i45 = h_y->size[0] * h_y->size[1];
      h_y->size[0] = (int)unnamed_idx_0;
      h_y->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)h_y, i45, (int)sizeof(double));
      m = g_y->size[0];
      i45 = h_y->size[0] * h_y->size[1];
      emxEnsureCapacity((emxArray__common *)h_y, i45, (int)sizeof(double));
      br = h_y->size[1];
      for (i45 = 0; i45 < br; i45++) {
        ar = h_y->size[0];
        for (i46 = 0; i46 < ar; i46++) {
          h_y->data[i46 + h_y->size[0] * i45] = 0.0;
        }
      }

      if ((g_y->size[0] == 0) || (B->size[1] == 0)) {
      } else {
        nx = g_y->size[0] * (B->size[1] - 1);
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          i45 = cr + m;
          for (ic = cr; ic + 1 <= i45; ic++) {
            h_y->data[ic] = 0.0;
          }

          cr += m;
        }

        br = 0;
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          ar = -1;
          i45 = br + k;
          for (ib = br; ib + 1 <= i45; ib++) {
            if (B->data[ib] != 0.0) {
              ia = ar;
              i46 = cr + m;
              for (ic = cr; ic + 1 <= i46; ic++) {
                ia++;
                h_y->data[ic] += B->data[ib] * g_y->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          cr += m;
        }
      }
    }

    br = u->size[1];
    i45 = b_b->size[0];
    b_b->size[0] = br;
    emxEnsureCapacity((emxArray__common *)b_b, i45, (int)sizeof(double));
    for (i45 = 0; i45 < br; i45++) {
      b_b->data[i45] = u->data[i + u->size[0] * i45];
    }

    if ((h_y->size[1] == 1) || (b_b->size[0] == 1)) {
      i45 = c_C->size[0];
      c_C->size[0] = h_y->size[0];
      emxEnsureCapacity((emxArray__common *)c_C, i45, (int)sizeof(double));
      br = h_y->size[0];
      for (i45 = 0; i45 < br; i45++) {
        c_C->data[i45] = 0.0;
        ar = h_y->size[1];
        for (i46 = 0; i46 < ar; i46++) {
          c_C->data[i45] += h_y->data[i45 + h_y->size[0] * i46] * b_b->data[i46];
        }
      }
    } else {
      k = h_y->size[1];
      unnamed_idx_0 = (unsigned int)h_y->size[0];
      i45 = c_C->size[0];
      c_C->size[0] = (int)unnamed_idx_0;
      emxEnsureCapacity((emxArray__common *)c_C, i45, (int)sizeof(double));
      m = h_y->size[0];
      nx = c_C->size[0];
      i45 = c_C->size[0];
      c_C->size[0] = nx;
      emxEnsureCapacity((emxArray__common *)c_C, i45, (int)sizeof(double));
      for (i45 = 0; i45 < nx; i45++) {
        c_C->data[i45] = 0.0;
      }

      if (h_y->size[0] == 0) {
      } else {
        cr = 0;
        while ((m > 0) && (cr <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            c_C->data[ic - 1] = 0.0;
          }

          cr = m;
        }

        br = 0;
        cr = 0;
        while ((m > 0) && (cr <= 0)) {
          ar = -1;
          i45 = br + k;
          for (ib = br; ib + 1 <= i45; ib++) {
            if (b_b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                c_C->data[ic] += b_b->data[ib] * h_y->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          cr = m;
        }
      }
    }

    nx = r24->size[0];
    for (i45 = 0; i45 < nx; i45++) {
      G2_u->data[i + G2_u->size[0] * r24->data[i45]] = c_C->data[i45];
    }

    i++;
  }

  emxFree_real_T(&i_y);
  emxFree_real_T(&g_A);
  emxFree_real_T(&f_A);
  emxFree_real_T(&b_M0);
  emxFree_real_T(&c_t);
  emxFree_real_T(&e_A);
  emxFree_real_T(&d_A);
  emxFree_real_T(&h_y);
  emxFree_real_T(&g_y);
  emxFree_real_T(&f_y);
  emxFree_real_T(&x);
  emxFree_real_T(&c_y);
  emxFree_real_T(&b_b);
  emxFree_real_T(&e_y);
  emxFree_real_T(&b);
  emxFree_real_T(&a);
  emxFree_real_T(&d_y);
  emxFree_real_T(&b_y);
  emxFree_real_T(&c_C);
  emxFree_int32_T(&r24);
  emxFree_real_T(&M0_);
  emxFree_real_T(&M0);
  emxInit_real_T(&r25, 2);
  emxInit_real_T(&r26, 2);

  /* disp('X end'); */
  b_trapz(t, G1_y, r25);
  b_trapz(t, G2_u, r26);
  i45 = X_T->size[0];
  X_T->size[0] = r25->size[1];
  emxEnsureCapacity((emxArray__common *)X_T, i45, (int)sizeof(double));
  br = r25->size[1];
  emxFree_real_T(&G2_u);
  emxFree_real_T(&G1_y);
  for (i45 = 0; i45 < br; i45++) {
    X_T->data[i45] = r25->data[r25->size[0] * i45] + r26->data[r26->size[0] *
      i45];
  }

  emxFree_real_T(&r26);
  emxFree_real_T(&r25);
}

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                const emxArray_real_T *C
 *                const emxArray_real_T *t
 *                const emxArray_real_T *u
 *                const emxArray_real_T *y
 *                emxArray_real_T *X_T
 * Return Type  : void
 */
void b_FHZN_exact_state_observer_fin(const emxArray_real_T *A, const
  emxArray_real_T *B, const emxArray_real_T *C, const emxArray_real_T *t, const
  emxArray_real_T *u, const emxArray_real_T *y, emxArray_real_T *X_T)
{
  emxArray_real_T *M0;
  int n;
  int i48;
  int br;
  emxArray_real_T *G1_y;
  emxArray_real_T *G2_u;
  int i;
  emxArray_int32_T *r29;
  emxArray_real_T *b_C;
  emxArray_int32_T *r30;
  emxArray_real_T *b_y;
  emxArray_real_T *a;
  emxArray_real_T *b;
  emxArray_real_T *c_y;
  emxArray_real_T *b_A;
  emxArray_real_T *c_A;
  int ar;
  int i49;
  double b_t;
  int cr;
  int nx;
  int k;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  int m;
  int ic;
  int ib;
  int ia;
  emxArray_real_T *M0_;
  emxArray_real_T *c_C;
  emxArray_real_T *d_y;
  emxArray_real_T *e_y;
  emxArray_real_T *b_b;
  emxArray_real_T *x;
  emxArray_real_T *f_y;
  emxArray_real_T *g_y;
  emxArray_real_T *h_y;
  emxArray_real_T *d_A;
  emxArray_real_T *e_A;
  emxArray_real_T *c_t;
  emxArray_real_T *b_M0;
  emxArray_real_T *f_A;
  emxArray_real_T *g_A;
  emxArray_real_T *i_y;
  emxArray_real_T *r31;
  emxArray_real_T *r32;
  emxInit_real_T2(&M0, 3);
  n = A->size[0];
  i48 = M0->size[0] * M0->size[1] * M0->size[2];
  M0->size[0] = t->size[1];
  M0->size[1] = A->size[0];
  M0->size[2] = A->size[0];
  emxEnsureCapacity((emxArray__common *)M0, i48, (int)sizeof(double));
  br = t->size[1] * A->size[0] * A->size[0];
  for (i48 = 0; i48 < br; i48++) {
    M0->data[i48] = 0.0;
  }

  emxInit_real_T(&G1_y, 2);
  i48 = G1_y->size[0] * G1_y->size[1];
  G1_y->size[0] = y->size[0];
  G1_y->size[1] = A->size[0];
  emxEnsureCapacity((emxArray__common *)G1_y, i48, (int)sizeof(double));
  br = y->size[0] * A->size[0];
  for (i48 = 0; i48 < br; i48++) {
    G1_y->data[i48] = 0.0;
  }

  emxInit_real_T(&G2_u, 2);
  i48 = G2_u->size[0] * G2_u->size[1];
  G2_u->size[0] = y->size[0];
  G2_u->size[1] = A->size[0];
  emxEnsureCapacity((emxArray__common *)G2_u, i48, (int)sizeof(double));
  br = y->size[0] * A->size[0];
  for (i48 = 0; i48 < br; i48++) {
    G2_u->data[i48] = 0.0;
  }

  i = 0;
  emxInit_int32_T1(&r29, 1);
  emxInit_real_T(&b_C, 2);
  emxInit_int32_T1(&r30, 1);
  emxInit_real_T(&b_y, 2);
  emxInit_real_T(&a, 2);
  emxInit_real_T(&b, 2);
  emxInit_real_T(&c_y, 2);
  emxInit_real_T(&b_A, 2);
  emxInit_real_T(&c_A, 2);
  while (i <= t->size[1] - 1) {
    br = M0->size[1];
    i48 = r30->size[0];
    r30->size[0] = br;
    emxEnsureCapacity((emxArray__common *)r30, i48, (int)sizeof(int));
    for (i48 = 0; i48 < br; i48++) {
      r30->data[i48] = i48;
    }

    br = M0->size[2];
    i48 = r29->size[0];
    r29->size[0] = br;
    emxEnsureCapacity((emxArray__common *)r29, i48, (int)sizeof(int));
    for (i48 = 0; i48 < br; i48++) {
      r29->data[i48] = i48;
    }

    i48 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = C->size[1];
    b_y->size[1] = C->size[1];
    emxEnsureCapacity((emxArray__common *)b_y, i48, (int)sizeof(double));
    br = C->size[1];
    for (i48 = 0; i48 < br; i48++) {
      ar = C->size[1];
      for (i49 = 0; i49 < ar; i49++) {
        b_y->data[i48 + b_y->size[0] * i49] = C->data[C->size[0] * i48] *
          C->data[C->size[0] * i49];
      }
    }

    b_t = t->data[i];
    i48 = c_A->size[0] * c_A->size[1];
    c_A->size[0] = A->size[1];
    c_A->size[1] = A->size[0];
    emxEnsureCapacity((emxArray__common *)c_A, i48, (int)sizeof(double));
    br = A->size[0];
    for (i48 = 0; i48 < br; i48++) {
      ar = A->size[1];
      for (i49 = 0; i49 < ar; i49++) {
        c_A->data[i49 + c_A->size[0] * i48] = A->data[i48 + A->size[0] * i49] *
          b_t;
      }
    }

    expm(c_A, a);
    if ((a->size[1] == 1) || (b_y->size[0] == 1)) {
      i48 = c_y->size[0] * c_y->size[1];
      c_y->size[0] = a->size[0];
      c_y->size[1] = b_y->size[1];
      emxEnsureCapacity((emxArray__common *)c_y, i48, (int)sizeof(double));
      br = a->size[0];
      for (i48 = 0; i48 < br; i48++) {
        ar = b_y->size[1];
        for (i49 = 0; i49 < ar; i49++) {
          c_y->data[i48 + c_y->size[0] * i49] = 0.0;
          cr = a->size[1];
          for (nx = 0; nx < cr; nx++) {
            c_y->data[i48 + c_y->size[0] * i49] += a->data[i48 + a->size[0] * nx]
              * b_y->data[nx + b_y->size[0] * i49];
          }
        }
      }
    } else {
      k = a->size[1];
      unnamed_idx_0 = (unsigned int)a->size[0];
      unnamed_idx_1 = (unsigned int)b_y->size[1];
      i48 = c_y->size[0] * c_y->size[1];
      c_y->size[0] = (int)unnamed_idx_0;
      c_y->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)c_y, i48, (int)sizeof(double));
      m = a->size[0];
      i48 = c_y->size[0] * c_y->size[1];
      emxEnsureCapacity((emxArray__common *)c_y, i48, (int)sizeof(double));
      br = c_y->size[1];
      for (i48 = 0; i48 < br; i48++) {
        ar = c_y->size[0];
        for (i49 = 0; i49 < ar; i49++) {
          c_y->data[i49 + c_y->size[0] * i48] = 0.0;
        }
      }

      if ((a->size[0] == 0) || (b_y->size[1] == 0)) {
      } else {
        nx = a->size[0] * (b_y->size[1] - 1);
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          i48 = cr + m;
          for (ic = cr; ic + 1 <= i48; ic++) {
            c_y->data[ic] = 0.0;
          }

          cr += m;
        }

        br = 0;
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          ar = -1;
          i48 = br + k;
          for (ib = br; ib + 1 <= i48; ib++) {
            if (b_y->data[ib] != 0.0) {
              ia = ar;
              i49 = cr + m;
              for (ic = cr; ic + 1 <= i49; ic++) {
                ia++;
                c_y->data[ic] += b_y->data[ib] * a->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          cr += m;
        }
      }
    }

    i48 = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)b_A, i48, (int)sizeof(double));
    b_t = t->data[i];
    br = A->size[0] * A->size[1];
    for (i48 = 0; i48 < br; i48++) {
      b_A->data[i48] = A->data[i48] * b_t;
    }

    expm(b_A, b);
    if ((c_y->size[1] == 1) || (b->size[0] == 1)) {
      i48 = b_C->size[0] * b_C->size[1];
      b_C->size[0] = c_y->size[0];
      b_C->size[1] = b->size[1];
      emxEnsureCapacity((emxArray__common *)b_C, i48, (int)sizeof(double));
      br = c_y->size[0];
      for (i48 = 0; i48 < br; i48++) {
        ar = b->size[1];
        for (i49 = 0; i49 < ar; i49++) {
          b_C->data[i48 + b_C->size[0] * i49] = 0.0;
          cr = c_y->size[1];
          for (nx = 0; nx < cr; nx++) {
            b_C->data[i48 + b_C->size[0] * i49] += c_y->data[i48 + c_y->size[0] *
              nx] * b->data[nx + b->size[0] * i49];
          }
        }
      }
    } else {
      k = c_y->size[1];
      unnamed_idx_0 = (unsigned int)c_y->size[0];
      unnamed_idx_1 = (unsigned int)b->size[1];
      i48 = b_C->size[0] * b_C->size[1];
      b_C->size[0] = (int)unnamed_idx_0;
      b_C->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)b_C, i48, (int)sizeof(double));
      m = c_y->size[0];
      i48 = b_C->size[0] * b_C->size[1];
      emxEnsureCapacity((emxArray__common *)b_C, i48, (int)sizeof(double));
      br = b_C->size[1];
      for (i48 = 0; i48 < br; i48++) {
        ar = b_C->size[0];
        for (i49 = 0; i49 < ar; i49++) {
          b_C->data[i49 + b_C->size[0] * i48] = 0.0;
        }
      }

      if ((c_y->size[0] == 0) || (b->size[1] == 0)) {
      } else {
        nx = c_y->size[0] * (b->size[1] - 1);
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          i48 = cr + m;
          for (ic = cr; ic + 1 <= i48; ic++) {
            b_C->data[ic] = 0.0;
          }

          cr += m;
        }

        br = 0;
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          ar = -1;
          i48 = br + k;
          for (ib = br; ib + 1 <= i48; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              i49 = cr + m;
              for (ic = cr; ic + 1 <= i49; ic++) {
                ia++;
                b_C->data[ic] += b->data[ib] * c_y->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          cr += m;
        }
      }
    }

    nx = r30->size[0];
    cr = r29->size[0];
    for (i48 = 0; i48 < cr; i48++) {
      for (i49 = 0; i49 < nx; i49++) {
        M0->data[(i + M0->size[0] * r30->data[i49]) + M0->size[0] * M0->size[1] *
          r29->data[i48]] = b_C->data[i49 + nx * i48];
      }
    }

    i++;
  }

  emxFree_real_T(&c_A);
  emxFree_real_T(&b_A);
  emxFree_real_T(&b_C);
  emxFree_int32_T(&r29);
  emxInit_real_T2(&M0_, 3);
  trapz(t, M0, M0_);
  i = 1;
  emxInit_real_T1(&c_C, 1);
  emxInit_real_T(&d_y, 2);
  emxInit_real_T1(&e_y, 1);
  emxInit_real_T1(&b_b, 1);
  emxInit_real_T2(&x, 3);
  emxInit_real_T(&f_y, 2);
  emxInit_real_T(&g_y, 2);
  emxInit_real_T(&h_y, 2);
  emxInit_real_T(&d_A, 2);
  emxInit_real_T(&e_A, 2);
  emxInit_real_T(&c_t, 2);
  emxInit_real_T2(&b_M0, 3);
  emxInit_real_T(&f_A, 2);
  emxInit_real_T(&g_A, 2);
  emxInit_real_T1(&i_y, 1);
  while (i - 1 <= t->size[1] - 2) {
    br = G1_y->size[1];
    i48 = r30->size[0];
    r30->size[0] = br;
    emxEnsureCapacity((emxArray__common *)r30, i48, (int)sizeof(int));
    for (i48 = 0; i48 < br; i48++) {
      r30->data[i48] = i48;
    }

    nx = M0_->size[1] * M0_->size[2];
    i48 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = n;
    b_y->size[1] = n;
    emxEnsureCapacity((emxArray__common *)b_y, i48, (int)sizeof(double));
    for (k = 0; k + 1 <= nx; k++) {
      b_y->data[k] = M0_->data[k];
    }

    i48 = g_A->size[0] * g_A->size[1];
    g_A->size[0] = A->size[0];
    g_A->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)g_A, i48, (int)sizeof(double));
    b_t = t->data[t->size[1] - 1];
    br = A->size[0] * A->size[1];
    for (i48 = 0; i48 < br; i48++) {
      g_A->data[i48] = A->data[i48] * b_t;
    }

    expm(g_A, b);
    mrdivide(b, b_y, a);
    b_t = t->data[i];
    i48 = f_A->size[0] * f_A->size[1];
    f_A->size[0] = A->size[1];
    f_A->size[1] = A->size[0];
    emxEnsureCapacity((emxArray__common *)f_A, i48, (int)sizeof(double));
    br = A->size[0];
    for (i48 = 0; i48 < br; i48++) {
      ar = A->size[1];
      for (i49 = 0; i49 < ar; i49++) {
        f_A->data[i49 + f_A->size[0] * i48] = A->data[i48 + A->size[0] * i49] *
          b_t;
      }
    }

    expm(f_A, b);
    if ((a->size[1] == 1) || (b->size[0] == 1)) {
      i48 = d_y->size[0] * d_y->size[1];
      d_y->size[0] = a->size[0];
      d_y->size[1] = b->size[1];
      emxEnsureCapacity((emxArray__common *)d_y, i48, (int)sizeof(double));
      br = a->size[0];
      for (i48 = 0; i48 < br; i48++) {
        ar = b->size[1];
        for (i49 = 0; i49 < ar; i49++) {
          d_y->data[i48 + d_y->size[0] * i49] = 0.0;
          cr = a->size[1];
          for (nx = 0; nx < cr; nx++) {
            d_y->data[i48 + d_y->size[0] * i49] += a->data[i48 + a->size[0] * nx]
              * b->data[nx + b->size[0] * i49];
          }
        }
      }
    } else {
      k = a->size[1];
      unnamed_idx_0 = (unsigned int)a->size[0];
      unnamed_idx_1 = (unsigned int)b->size[1];
      i48 = d_y->size[0] * d_y->size[1];
      d_y->size[0] = (int)unnamed_idx_0;
      d_y->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)d_y, i48, (int)sizeof(double));
      m = a->size[0];
      i48 = d_y->size[0] * d_y->size[1];
      emxEnsureCapacity((emxArray__common *)d_y, i48, (int)sizeof(double));
      br = d_y->size[1];
      for (i48 = 0; i48 < br; i48++) {
        ar = d_y->size[0];
        for (i49 = 0; i49 < ar; i49++) {
          d_y->data[i49 + d_y->size[0] * i48] = 0.0;
        }
      }

      if ((a->size[0] == 0) || (b->size[1] == 0)) {
      } else {
        nx = a->size[0] * (b->size[1] - 1);
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          i48 = cr + m;
          for (ic = cr; ic + 1 <= i48; ic++) {
            d_y->data[ic] = 0.0;
          }

          cr += m;
        }

        br = 0;
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          ar = -1;
          i48 = br + k;
          for (ib = br; ib + 1 <= i48; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              i49 = cr + m;
              for (ic = cr; ic + 1 <= i49; ic++) {
                ia++;
                d_y->data[ic] += b->data[ib] * a->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          cr += m;
        }
      }
    }

    i48 = b_b->size[0];
    b_b->size[0] = C->size[1];
    emxEnsureCapacity((emxArray__common *)b_b, i48, (int)sizeof(double));
    br = C->size[1];
    for (i48 = 0; i48 < br; i48++) {
      b_b->data[i48] = C->data[C->size[0] * i48];
    }

    if ((d_y->size[1] == 1) || (b_b->size[0] == 1)) {
      i48 = e_y->size[0];
      e_y->size[0] = d_y->size[0];
      emxEnsureCapacity((emxArray__common *)e_y, i48, (int)sizeof(double));
      br = d_y->size[0];
      for (i48 = 0; i48 < br; i48++) {
        e_y->data[i48] = 0.0;
        ar = d_y->size[1];
        for (i49 = 0; i49 < ar; i49++) {
          e_y->data[i48] += d_y->data[i48 + d_y->size[0] * i49] * b_b->data[i49];
        }
      }
    } else {
      k = d_y->size[1];
      unnamed_idx_0 = (unsigned int)d_y->size[0];
      i48 = e_y->size[0];
      e_y->size[0] = (int)unnamed_idx_0;
      emxEnsureCapacity((emxArray__common *)e_y, i48, (int)sizeof(double));
      m = d_y->size[0];
      nx = e_y->size[0];
      i48 = e_y->size[0];
      e_y->size[0] = nx;
      emxEnsureCapacity((emxArray__common *)e_y, i48, (int)sizeof(double));
      for (i48 = 0; i48 < nx; i48++) {
        e_y->data[i48] = 0.0;
      }

      if (d_y->size[0] == 0) {
      } else {
        cr = 0;
        while ((m > 0) && (cr <= 0)) {
          for (ic = 1; ic <= m; ic++) {
            e_y->data[ic - 1] = 0.0;
          }

          cr = m;
        }

        br = 0;
        cr = 0;
        while ((m > 0) && (cr <= 0)) {
          ar = -1;
          i48 = br + k;
          for (ib = br; ib + 1 <= i48; ib++) {
            if (b_b->data[ib] != 0.0) {
              ia = ar;
              for (ic = 0; ic + 1 <= m; ic++) {
                ia++;
                e_y->data[ic] += b_b->data[ib] * d_y->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          cr = m;
        }
      }
    }

    b_t = y->data[i];
    i48 = i_y->size[0];
    i_y->size[0] = e_y->size[0];
    emxEnsureCapacity((emxArray__common *)i_y, i48, (int)sizeof(double));
    br = e_y->size[0];
    for (i48 = 0; i48 < br; i48++) {
      i_y->data[i48] = e_y->data[i48] * b_t;
    }

    nx = r30->size[0];
    for (i48 = 0; i48 < nx; i48++) {
      G1_y->data[i + G1_y->size[0] * r30->data[i48]] = i_y->data[i48];
    }

    br = G2_u->size[1];
    i48 = r30->size[0];
    r30->size[0] = br;
    emxEnsureCapacity((emxArray__common *)r30, i48, (int)sizeof(int));
    for (i48 = 0; i48 < br; i48++) {
      r30->data[i48] = i48;
    }

    nx = M0_->size[1] * M0_->size[2];
    i48 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = n;
    b_y->size[1] = n;
    emxEnsureCapacity((emxArray__common *)b_y, i48, (int)sizeof(double));
    for (k = 0; k + 1 <= nx; k++) {
      b_y->data[k] = M0_->data[k];
    }

    i48 = c_t->size[0] * c_t->size[1];
    c_t->size[0] = 1;
    c_t->size[1] = i + 1;
    emxEnsureCapacity((emxArray__common *)c_t, i48, (int)sizeof(double));
    for (i48 = 0; i48 <= i; i48++) {
      c_t->data[c_t->size[0] * i48] = t->data[i48];
    }

    br = M0->size[1];
    ar = M0->size[2];
    i48 = b_M0->size[0] * b_M0->size[1] * b_M0->size[2];
    b_M0->size[0] = i + 1;
    b_M0->size[1] = br;
    b_M0->size[2] = ar;
    emxEnsureCapacity((emxArray__common *)b_M0, i48, (int)sizeof(double));
    for (i48 = 0; i48 < ar; i48++) {
      for (i49 = 0; i49 < br; i49++) {
        for (nx = 0; nx <= i; nx++) {
          b_M0->data[(nx + b_M0->size[0] * i49) + b_M0->size[0] * b_M0->size[1] *
            i48] = M0->data[(nx + M0->size[0] * i49) + M0->size[0] * M0->size[1]
            * i48];
        }
      }
    }

    trapz(c_t, b_M0, x);
    nx = x->size[1] * x->size[2];
    i48 = c_y->size[0] * c_y->size[1];
    c_y->size[0] = n;
    c_y->size[1] = n;
    emxEnsureCapacity((emxArray__common *)c_y, i48, (int)sizeof(double));
    for (k = 0; k + 1 <= nx; k++) {
      c_y->data[k] = x->data[k];
    }

    i48 = e_A->size[0] * e_A->size[1];
    e_A->size[0] = A->size[0];
    e_A->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)e_A, i48, (int)sizeof(double));
    b_t = t->data[t->size[1] - 1];
    br = A->size[0] * A->size[1];
    for (i48 = 0; i48 < br; i48++) {
      e_A->data[i48] = A->data[i48] * b_t;
    }

    expm(e_A, b);
    mrdivide(b, b_y, a);
    if ((a->size[1] == 1) || (c_y->size[0] == 1)) {
      i48 = f_y->size[0] * f_y->size[1];
      f_y->size[0] = a->size[0];
      f_y->size[1] = c_y->size[1];
      emxEnsureCapacity((emxArray__common *)f_y, i48, (int)sizeof(double));
      br = a->size[0];
      for (i48 = 0; i48 < br; i48++) {
        ar = c_y->size[1];
        for (i49 = 0; i49 < ar; i49++) {
          f_y->data[i48 + f_y->size[0] * i49] = 0.0;
          cr = a->size[1];
          for (nx = 0; nx < cr; nx++) {
            f_y->data[i48 + f_y->size[0] * i49] += a->data[i48 + a->size[0] * nx]
              * c_y->data[nx + c_y->size[0] * i49];
          }
        }
      }
    } else {
      k = a->size[1];
      unnamed_idx_0 = (unsigned int)a->size[0];
      unnamed_idx_1 = (unsigned int)c_y->size[1];
      i48 = f_y->size[0] * f_y->size[1];
      f_y->size[0] = (int)unnamed_idx_0;
      f_y->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)f_y, i48, (int)sizeof(double));
      m = a->size[0];
      i48 = f_y->size[0] * f_y->size[1];
      emxEnsureCapacity((emxArray__common *)f_y, i48, (int)sizeof(double));
      br = f_y->size[1];
      for (i48 = 0; i48 < br; i48++) {
        ar = f_y->size[0];
        for (i49 = 0; i49 < ar; i49++) {
          f_y->data[i49 + f_y->size[0] * i48] = 0.0;
        }
      }

      if ((a->size[0] == 0) || (c_y->size[1] == 0)) {
      } else {
        nx = a->size[0] * (c_y->size[1] - 1);
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          i48 = cr + m;
          for (ic = cr; ic + 1 <= i48; ic++) {
            f_y->data[ic] = 0.0;
          }

          cr += m;
        }

        br = 0;
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          ar = -1;
          i48 = br + k;
          for (ib = br; ib + 1 <= i48; ib++) {
            if (c_y->data[ib] != 0.0) {
              ia = ar;
              i49 = cr + m;
              for (ic = cr; ic + 1 <= i49; ic++) {
                ia++;
                f_y->data[ic] += c_y->data[ib] * a->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          cr += m;
        }
      }
    }

    i48 = d_A->size[0] * d_A->size[1];
    d_A->size[0] = A->size[0];
    d_A->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)d_A, i48, (int)sizeof(double));
    b_t = t->data[i];
    br = A->size[0] * A->size[1];
    for (i48 = 0; i48 < br; i48++) {
      d_A->data[i48] = -A->data[i48] * b_t;
    }

    expm(d_A, b);
    if ((f_y->size[1] == 1) || (b->size[0] == 1)) {
      i48 = g_y->size[0] * g_y->size[1];
      g_y->size[0] = f_y->size[0];
      g_y->size[1] = b->size[1];
      emxEnsureCapacity((emxArray__common *)g_y, i48, (int)sizeof(double));
      br = f_y->size[0];
      for (i48 = 0; i48 < br; i48++) {
        ar = b->size[1];
        for (i49 = 0; i49 < ar; i49++) {
          g_y->data[i48 + g_y->size[0] * i49] = 0.0;
          cr = f_y->size[1];
          for (nx = 0; nx < cr; nx++) {
            g_y->data[i48 + g_y->size[0] * i49] += f_y->data[i48 + f_y->size[0] *
              nx] * b->data[nx + b->size[0] * i49];
          }
        }
      }
    } else {
      k = f_y->size[1];
      unnamed_idx_0 = (unsigned int)f_y->size[0];
      unnamed_idx_1 = (unsigned int)b->size[1];
      i48 = g_y->size[0] * g_y->size[1];
      g_y->size[0] = (int)unnamed_idx_0;
      g_y->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)g_y, i48, (int)sizeof(double));
      m = f_y->size[0];
      i48 = g_y->size[0] * g_y->size[1];
      emxEnsureCapacity((emxArray__common *)g_y, i48, (int)sizeof(double));
      br = g_y->size[1];
      for (i48 = 0; i48 < br; i48++) {
        ar = g_y->size[0];
        for (i49 = 0; i49 < ar; i49++) {
          g_y->data[i49 + g_y->size[0] * i48] = 0.0;
        }
      }

      if ((f_y->size[0] == 0) || (b->size[1] == 0)) {
      } else {
        nx = f_y->size[0] * (b->size[1] - 1);
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          i48 = cr + m;
          for (ic = cr; ic + 1 <= i48; ic++) {
            g_y->data[ic] = 0.0;
          }

          cr += m;
        }

        br = 0;
        cr = 0;
        while ((m > 0) && (cr <= nx)) {
          ar = -1;
          i48 = br + k;
          for (ib = br; ib + 1 <= i48; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              i49 = cr + m;
              for (ic = cr; ic + 1 <= i49; ic++) {
                ia++;
                g_y->data[ic] += b->data[ib] * f_y->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          cr += m;
        }
      }
    }

    if ((g_y->size[1] == 1) || (B->size[0] == 1)) {
      i48 = h_y->size[0] * h_y->size[1];
      h_y->size[0] = g_y->size[0];
      h_y->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)h_y, i48, (int)sizeof(double));
      br = g_y->size[0];
      for (i48 = 0; i48 < br; i48++) {
        for (i49 = 0; i49 < 2; i49++) {
          h_y->data[i48 + h_y->size[0] * i49] = 0.0;
          ar = g_y->size[1];
          for (nx = 0; nx < ar; nx++) {
            h_y->data[i48 + h_y->size[0] * i49] += g_y->data[i48 + g_y->size[0] *
              nx] * B->data[nx + B->size[0] * i49];
          }
        }
      }
    } else {
      k = g_y->size[1];
      unnamed_idx_0 = (unsigned int)g_y->size[0];
      i48 = h_y->size[0] * h_y->size[1];
      h_y->size[0] = (int)unnamed_idx_0;
      h_y->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)h_y, i48, (int)sizeof(double));
      m = g_y->size[0];
      i48 = h_y->size[0] * h_y->size[1];
      h_y->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)h_y, i48, (int)sizeof(double));
      for (i48 = 0; i48 < 2; i48++) {
        br = h_y->size[0];
        for (i49 = 0; i49 < br; i49++) {
          h_y->data[i49 + h_y->size[0] * i48] = 0.0;
        }
      }

      if (g_y->size[0] == 0) {
      } else {
        cr = 0;
        while ((m > 0) && (cr <= m)) {
          i48 = cr + m;
          for (ic = cr; ic + 1 <= i48; ic++) {
            h_y->data[ic] = 0.0;
          }

          cr += m;
        }

        br = 0;
        cr = 0;
        while ((m > 0) && (cr <= m)) {
          ar = -1;
          i48 = br + k;
          for (ib = br; ib + 1 <= i48; ib++) {
            if (B->data[ib] != 0.0) {
              ia = ar;
              i49 = cr + m;
              for (ic = cr; ic + 1 <= i49; ic++) {
                ia++;
                h_y->data[ic] += B->data[ib] * g_y->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          cr += m;
        }
      }
    }

    unnamed_idx_0 = (unsigned int)h_y->size[0];
    i48 = c_C->size[0];
    c_C->size[0] = (int)unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *)c_C, i48, (int)sizeof(double));
    m = h_y->size[0];
    nx = c_C->size[0];
    i48 = c_C->size[0];
    c_C->size[0] = nx;
    emxEnsureCapacity((emxArray__common *)c_C, i48, (int)sizeof(double));
    for (i48 = 0; i48 < nx; i48++) {
      c_C->data[i48] = 0.0;
    }

    if (h_y->size[0] == 0) {
    } else {
      cr = 0;
      while ((m > 0) && (cr <= 0)) {
        for (ic = 1; ic <= m; ic++) {
          c_C->data[ic - 1] = 0.0;
        }

        cr = m;
      }

      br = 0;
      cr = 0;
      while ((m > 0) && (cr <= 0)) {
        ar = -1;
        for (ib = br; ib + 1 <= br + 2; ib++) {
          if (u->data[i + u->size[0] * ib] != 0.0) {
            ia = ar;
            for (ic = 0; ic + 1 <= m; ic++) {
              ia++;
              c_C->data[ic] += u->data[i + u->size[0] * ib] * h_y->data[ia];
            }
          }

          ar += m;
        }

        br += 2;
        cr = m;
      }
    }

    nx = r30->size[0];
    for (i48 = 0; i48 < nx; i48++) {
      G2_u->data[i + G2_u->size[0] * r30->data[i48]] = c_C->data[i48];
    }

    i++;
  }

  emxFree_real_T(&i_y);
  emxFree_real_T(&g_A);
  emxFree_real_T(&f_A);
  emxFree_real_T(&b_M0);
  emxFree_real_T(&c_t);
  emxFree_real_T(&e_A);
  emxFree_real_T(&d_A);
  emxFree_real_T(&h_y);
  emxFree_real_T(&g_y);
  emxFree_real_T(&f_y);
  emxFree_real_T(&x);
  emxFree_real_T(&c_y);
  emxFree_real_T(&b_b);
  emxFree_real_T(&e_y);
  emxFree_real_T(&b);
  emxFree_real_T(&a);
  emxFree_real_T(&d_y);
  emxFree_real_T(&b_y);
  emxFree_real_T(&c_C);
  emxFree_int32_T(&r30);
  emxFree_real_T(&M0_);
  emxFree_real_T(&M0);
  emxInit_real_T(&r31, 2);
  emxInit_real_T(&r32, 2);

  /* disp('X end'); */
  b_trapz(t, G1_y, r31);
  b_trapz(t, G2_u, r32);
  i48 = X_T->size[0];
  X_T->size[0] = r31->size[1];
  emxEnsureCapacity((emxArray__common *)X_T, i48, (int)sizeof(double));
  br = r31->size[1];
  emxFree_real_T(&G2_u);
  emxFree_real_T(&G1_y);
  for (i48 = 0; i48 < br; i48++) {
    X_T->data[i48] = r31->data[r31->size[0] * i48] + r32->data[r32->size[0] *
      i48];
  }

  emxFree_real_T(&r32);
  emxFree_real_T(&r31);
}

/*
 * File trailer for FHZN_exact_state_observer_final.c
 *
 * [EOF]
 */
