/*
 * File: expm.c
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
#include "expm.h"
#include "FHZN_define_model_del_emxutil.h"
#include "mldivide.h"
#include "power.h"
#include "norm.h"
#include "FHZN_define_model_del_rtwutil.h"

/* Function Declarations */
static void PadeApproximantOfDegree(const emxArray_real_T *A, unsigned char m,
  emxArray_real_T *F);
static void b_PadeApproximantOfDegree(const emxArray_real_T *A, emxArray_real_T *
  F);

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                unsigned char m
 *                emxArray_real_T *F
 * Return Type  : void
 */
static void PadeApproximantOfDegree(const emxArray_real_T *A, unsigned char m,
  emxArray_real_T *F)
{
  int n;
  emxArray_real_T *A2;
  int i13;
  int br;
  int ar;
  int i14;
  int c;
  int cr;
  int k;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  int b_m;
  int ic;
  int ib;
  int ia;
  emxArray_real_T *U;
  emxArray_real_T *V;
  emxArray_real_T *b;
  emxArray_real_T *C;
  double d;
  emxArray_real_T *A3;
  emxArray_real_T *A4;
  n = A->size[0] - 1;
  emxInit_real_T(&A2, 2);
  if ((A->size[1] == 1) || (A->size[0] == 1)) {
    i13 = A2->size[0] * A2->size[1];
    A2->size[0] = A->size[0];
    A2->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)A2, i13, (int)sizeof(double));
    br = A->size[0];
    for (i13 = 0; i13 < br; i13++) {
      ar = A->size[1];
      for (i14 = 0; i14 < ar; i14++) {
        A2->data[i13 + A2->size[0] * i14] = 0.0;
        c = A->size[1];
        for (cr = 0; cr < c; cr++) {
          A2->data[i13 + A2->size[0] * i14] += A->data[i13 + A->size[0] * cr] *
            A->data[cr + A->size[0] * i14];
        }
      }
    }
  } else {
    k = A->size[1];
    unnamed_idx_0 = (unsigned int)A->size[0];
    unnamed_idx_1 = (unsigned int)A->size[1];
    i13 = A2->size[0] * A2->size[1];
    A2->size[0] = (int)unnamed_idx_0;
    A2->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)A2, i13, (int)sizeof(double));
    b_m = A->size[0];
    i13 = A2->size[0] * A2->size[1];
    emxEnsureCapacity((emxArray__common *)A2, i13, (int)sizeof(double));
    br = A2->size[1];
    for (i13 = 0; i13 < br; i13++) {
      ar = A2->size[0];
      for (i14 = 0; i14 < ar; i14++) {
        A2->data[i14 + A2->size[0] * i13] = 0.0;
      }
    }

    if ((A->size[0] == 0) || (A->size[1] == 0)) {
    } else {
      c = A->size[0] * (A->size[1] - 1);
      cr = 0;
      while ((b_m > 0) && (cr <= c)) {
        i13 = cr + b_m;
        for (ic = cr; ic + 1 <= i13; ic++) {
          A2->data[ic] = 0.0;
        }

        cr += b_m;
      }

      br = 0;
      cr = 0;
      while ((b_m > 0) && (cr <= c)) {
        ar = -1;
        i13 = br + k;
        for (ib = br; ib + 1 <= i13; ib++) {
          if (A->data[ib] != 0.0) {
            ia = ar;
            i14 = cr + b_m;
            for (ic = cr; ic + 1 <= i14; ic++) {
              ia++;
              A2->data[ic] += A->data[ib] * A->data[ia];
            }
          }

          ar += b_m;
        }

        br += k;
        cr += b_m;
      }
    }
  }

  emxInit_real_T(&U, 2);
  emxInit_real_T(&V, 2);
  emxInit_real_T(&b, 2);
  if (m == 3) {
    i13 = U->size[0] * U->size[1];
    U->size[0] = A2->size[0];
    U->size[1] = A2->size[1];
    emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
    br = A2->size[0] * A2->size[1];
    for (i13 = 0; i13 < br; i13++) {
      U->data[i13] = A2->data[i13];
    }

    for (k = 0; k <= n; k++) {
      U->data[k + U->size[0] * k] += 60.0;
    }

    i13 = b->size[0] * b->size[1];
    b->size[0] = U->size[0];
    b->size[1] = U->size[1];
    emxEnsureCapacity((emxArray__common *)b, i13, (int)sizeof(double));
    br = U->size[0] * U->size[1];
    for (i13 = 0; i13 < br; i13++) {
      b->data[i13] = U->data[i13];
    }

    emxInit_real_T(&C, 2);
    if ((A->size[1] == 1) || (U->size[0] == 1)) {
      i13 = C->size[0] * C->size[1];
      C->size[0] = A->size[0];
      C->size[1] = U->size[1];
      emxEnsureCapacity((emxArray__common *)C, i13, (int)sizeof(double));
      br = A->size[0];
      for (i13 = 0; i13 < br; i13++) {
        ar = U->size[1];
        for (i14 = 0; i14 < ar; i14++) {
          C->data[i13 + C->size[0] * i14] = 0.0;
          c = A->size[1];
          for (cr = 0; cr < c; cr++) {
            C->data[i13 + C->size[0] * i14] += A->data[i13 + A->size[0] * cr] *
              U->data[cr + U->size[0] * i14];
          }
        }
      }

      i13 = U->size[0] * U->size[1];
      U->size[0] = C->size[0];
      U->size[1] = C->size[1];
      emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
      br = C->size[1];
      for (i13 = 0; i13 < br; i13++) {
        ar = C->size[0];
        for (i14 = 0; i14 < ar; i14++) {
          U->data[i14 + U->size[0] * i13] = C->data[i14 + C->size[0] * i13];
        }
      }
    } else {
      k = A->size[1];
      unnamed_idx_0 = (unsigned int)A->size[0];
      unnamed_idx_1 = (unsigned int)U->size[1];
      i13 = U->size[0] * U->size[1];
      U->size[0] = (int)unnamed_idx_0;
      U->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
      b_m = A->size[0];
      i13 = U->size[0] * U->size[1];
      emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
      br = U->size[1];
      for (i13 = 0; i13 < br; i13++) {
        ar = U->size[0];
        for (i14 = 0; i14 < ar; i14++) {
          U->data[i14 + U->size[0] * i13] = 0.0;
        }
      }

      if ((A->size[0] == 0) || (b->size[1] == 0)) {
      } else {
        c = A->size[0] * (b->size[1] - 1);
        cr = 0;
        while ((b_m > 0) && (cr <= c)) {
          i13 = cr + b_m;
          for (ic = cr; ic + 1 <= i13; ic++) {
            U->data[ic] = 0.0;
          }

          cr += b_m;
        }

        br = 0;
        cr = 0;
        while ((b_m > 0) && (cr <= c)) {
          ar = -1;
          i13 = br + k;
          for (ib = br; ib + 1 <= i13; ib++) {
            if (b->data[ib] != 0.0) {
              ia = ar;
              i14 = cr + b_m;
              for (ic = cr; ic + 1 <= i14; ic++) {
                ia++;
                U->data[ic] += b->data[ib] * A->data[ia];
              }
            }

            ar += b_m;
          }

          br += k;
          cr += b_m;
        }
      }
    }

    emxFree_real_T(&C);
    i13 = V->size[0] * V->size[1];
    V->size[0] = A2->size[0];
    V->size[1] = A2->size[1];
    emxEnsureCapacity((emxArray__common *)V, i13, (int)sizeof(double));
    br = A2->size[0] * A2->size[1];
    for (i13 = 0; i13 < br; i13++) {
      V->data[i13] = 12.0 * A2->data[i13];
    }

    d = 120.0;
  } else {
    emxInit_real_T(&A3, 2);
    if ((A2->size[1] == 1) || (A2->size[0] == 1)) {
      i13 = A3->size[0] * A3->size[1];
      A3->size[0] = A2->size[0];
      A3->size[1] = A2->size[1];
      emxEnsureCapacity((emxArray__common *)A3, i13, (int)sizeof(double));
      br = A2->size[0];
      for (i13 = 0; i13 < br; i13++) {
        ar = A2->size[1];
        for (i14 = 0; i14 < ar; i14++) {
          A3->data[i13 + A3->size[0] * i14] = 0.0;
          c = A2->size[1];
          for (cr = 0; cr < c; cr++) {
            A3->data[i13 + A3->size[0] * i14] += A2->data[i13 + A2->size[0] * cr]
              * A2->data[cr + A2->size[0] * i14];
          }
        }
      }
    } else {
      k = A2->size[1];
      unnamed_idx_0 = (unsigned int)A2->size[0];
      unnamed_idx_1 = (unsigned int)A2->size[1];
      i13 = A3->size[0] * A3->size[1];
      A3->size[0] = (int)unnamed_idx_0;
      A3->size[1] = (int)unnamed_idx_1;
      emxEnsureCapacity((emxArray__common *)A3, i13, (int)sizeof(double));
      b_m = A2->size[0];
      i13 = A3->size[0] * A3->size[1];
      emxEnsureCapacity((emxArray__common *)A3, i13, (int)sizeof(double));
      br = A3->size[1];
      for (i13 = 0; i13 < br; i13++) {
        ar = A3->size[0];
        for (i14 = 0; i14 < ar; i14++) {
          A3->data[i14 + A3->size[0] * i13] = 0.0;
        }
      }

      if ((A2->size[0] == 0) || (A2->size[1] == 0)) {
      } else {
        c = A2->size[0] * (A2->size[1] - 1);
        cr = 0;
        while ((b_m > 0) && (cr <= c)) {
          i13 = cr + b_m;
          for (ic = cr; ic + 1 <= i13; ic++) {
            A3->data[ic] = 0.0;
          }

          cr += b_m;
        }

        br = 0;
        cr = 0;
        while ((b_m > 0) && (cr <= c)) {
          ar = -1;
          i13 = br + k;
          for (ib = br; ib + 1 <= i13; ib++) {
            if (A2->data[ib] != 0.0) {
              ia = ar;
              i14 = cr + b_m;
              for (ic = cr; ic + 1 <= i14; ic++) {
                ia++;
                A3->data[ic] += A2->data[ib] * A2->data[ia];
              }
            }

            ar += b_m;
          }

          br += k;
          cr += b_m;
        }
      }
    }

    if (m == 5) {
      i13 = U->size[0] * U->size[1];
      U->size[0] = A3->size[0];
      U->size[1] = A3->size[1];
      emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
      br = A3->size[0] * A3->size[1];
      for (i13 = 0; i13 < br; i13++) {
        U->data[i13] = A3->data[i13] + 420.0 * A2->data[i13];
      }

      for (k = 0; k <= n; k++) {
        U->data[k + U->size[0] * k] += 15120.0;
      }

      i13 = b->size[0] * b->size[1];
      b->size[0] = U->size[0];
      b->size[1] = U->size[1];
      emxEnsureCapacity((emxArray__common *)b, i13, (int)sizeof(double));
      br = U->size[0] * U->size[1];
      for (i13 = 0; i13 < br; i13++) {
        b->data[i13] = U->data[i13];
      }

      emxInit_real_T(&C, 2);
      if ((A->size[1] == 1) || (U->size[0] == 1)) {
        i13 = C->size[0] * C->size[1];
        C->size[0] = A->size[0];
        C->size[1] = U->size[1];
        emxEnsureCapacity((emxArray__common *)C, i13, (int)sizeof(double));
        br = A->size[0];
        for (i13 = 0; i13 < br; i13++) {
          ar = U->size[1];
          for (i14 = 0; i14 < ar; i14++) {
            C->data[i13 + C->size[0] * i14] = 0.0;
            c = A->size[1];
            for (cr = 0; cr < c; cr++) {
              C->data[i13 + C->size[0] * i14] += A->data[i13 + A->size[0] * cr] *
                U->data[cr + U->size[0] * i14];
            }
          }
        }

        i13 = U->size[0] * U->size[1];
        U->size[0] = C->size[0];
        U->size[1] = C->size[1];
        emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
        br = C->size[1];
        for (i13 = 0; i13 < br; i13++) {
          ar = C->size[0];
          for (i14 = 0; i14 < ar; i14++) {
            U->data[i14 + U->size[0] * i13] = C->data[i14 + C->size[0] * i13];
          }
        }
      } else {
        k = A->size[1];
        unnamed_idx_0 = (unsigned int)A->size[0];
        unnamed_idx_1 = (unsigned int)U->size[1];
        i13 = U->size[0] * U->size[1];
        U->size[0] = (int)unnamed_idx_0;
        U->size[1] = (int)unnamed_idx_1;
        emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
        b_m = A->size[0];
        i13 = U->size[0] * U->size[1];
        emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
        br = U->size[1];
        for (i13 = 0; i13 < br; i13++) {
          ar = U->size[0];
          for (i14 = 0; i14 < ar; i14++) {
            U->data[i14 + U->size[0] * i13] = 0.0;
          }
        }

        if ((A->size[0] == 0) || (b->size[1] == 0)) {
        } else {
          c = A->size[0] * (b->size[1] - 1);
          cr = 0;
          while ((b_m > 0) && (cr <= c)) {
            i13 = cr + b_m;
            for (ic = cr; ic + 1 <= i13; ic++) {
              U->data[ic] = 0.0;
            }

            cr += b_m;
          }

          br = 0;
          cr = 0;
          while ((b_m > 0) && (cr <= c)) {
            ar = -1;
            i13 = br + k;
            for (ib = br; ib + 1 <= i13; ib++) {
              if (b->data[ib] != 0.0) {
                ia = ar;
                i14 = cr + b_m;
                for (ic = cr; ic + 1 <= i14; ic++) {
                  ia++;
                  U->data[ic] += b->data[ib] * A->data[ia];
                }
              }

              ar += b_m;
            }

            br += k;
            cr += b_m;
          }
        }
      }

      emxFree_real_T(&C);
      i13 = V->size[0] * V->size[1];
      V->size[0] = A3->size[0];
      V->size[1] = A3->size[1];
      emxEnsureCapacity((emxArray__common *)V, i13, (int)sizeof(double));
      br = A3->size[0] * A3->size[1];
      for (i13 = 0; i13 < br; i13++) {
        V->data[i13] = 30.0 * A3->data[i13] + 3360.0 * A2->data[i13];
      }

      d = 30240.0;
    } else {
      emxInit_real_T(&A4, 2);
      if ((A3->size[1] == 1) || (A2->size[0] == 1)) {
        i13 = A4->size[0] * A4->size[1];
        A4->size[0] = A3->size[0];
        A4->size[1] = A2->size[1];
        emxEnsureCapacity((emxArray__common *)A4, i13, (int)sizeof(double));
        br = A3->size[0];
        for (i13 = 0; i13 < br; i13++) {
          ar = A2->size[1];
          for (i14 = 0; i14 < ar; i14++) {
            A4->data[i13 + A4->size[0] * i14] = 0.0;
            c = A3->size[1];
            for (cr = 0; cr < c; cr++) {
              A4->data[i13 + A4->size[0] * i14] += A3->data[i13 + A3->size[0] *
                cr] * A2->data[cr + A2->size[0] * i14];
            }
          }
        }
      } else {
        k = A3->size[1];
        unnamed_idx_0 = (unsigned int)A3->size[0];
        unnamed_idx_1 = (unsigned int)A2->size[1];
        i13 = A4->size[0] * A4->size[1];
        A4->size[0] = (int)unnamed_idx_0;
        A4->size[1] = (int)unnamed_idx_1;
        emxEnsureCapacity((emxArray__common *)A4, i13, (int)sizeof(double));
        b_m = A3->size[0];
        i13 = A4->size[0] * A4->size[1];
        emxEnsureCapacity((emxArray__common *)A4, i13, (int)sizeof(double));
        br = A4->size[1];
        for (i13 = 0; i13 < br; i13++) {
          ar = A4->size[0];
          for (i14 = 0; i14 < ar; i14++) {
            A4->data[i14 + A4->size[0] * i13] = 0.0;
          }
        }

        if ((A3->size[0] == 0) || (A2->size[1] == 0)) {
        } else {
          c = A3->size[0] * (A2->size[1] - 1);
          cr = 0;
          while ((b_m > 0) && (cr <= c)) {
            i13 = cr + b_m;
            for (ic = cr; ic + 1 <= i13; ic++) {
              A4->data[ic] = 0.0;
            }

            cr += b_m;
          }

          br = 0;
          cr = 0;
          while ((b_m > 0) && (cr <= c)) {
            ar = -1;
            i13 = br + k;
            for (ib = br; ib + 1 <= i13; ib++) {
              if (A2->data[ib] != 0.0) {
                ia = ar;
                i14 = cr + b_m;
                for (ic = cr; ic + 1 <= i14; ic++) {
                  ia++;
                  A4->data[ic] += A2->data[ib] * A3->data[ia];
                }
              }

              ar += b_m;
            }

            br += k;
            cr += b_m;
          }
        }
      }

      if (m == 7) {
        i13 = U->size[0] * U->size[1];
        U->size[0] = A4->size[0];
        U->size[1] = A4->size[1];
        emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
        br = A4->size[0] * A4->size[1];
        for (i13 = 0; i13 < br; i13++) {
          U->data[i13] = (A4->data[i13] + 1512.0 * A3->data[i13]) + 277200.0 *
            A2->data[i13];
        }

        for (k = 0; k <= n; k++) {
          U->data[k + U->size[0] * k] += 8.64864E+6;
        }

        i13 = b->size[0] * b->size[1];
        b->size[0] = U->size[0];
        b->size[1] = U->size[1];
        emxEnsureCapacity((emxArray__common *)b, i13, (int)sizeof(double));
        br = U->size[0] * U->size[1];
        for (i13 = 0; i13 < br; i13++) {
          b->data[i13] = U->data[i13];
        }

        emxInit_real_T(&C, 2);
        if ((A->size[1] == 1) || (U->size[0] == 1)) {
          i13 = C->size[0] * C->size[1];
          C->size[0] = A->size[0];
          C->size[1] = U->size[1];
          emxEnsureCapacity((emxArray__common *)C, i13, (int)sizeof(double));
          br = A->size[0];
          for (i13 = 0; i13 < br; i13++) {
            ar = U->size[1];
            for (i14 = 0; i14 < ar; i14++) {
              C->data[i13 + C->size[0] * i14] = 0.0;
              c = A->size[1];
              for (cr = 0; cr < c; cr++) {
                C->data[i13 + C->size[0] * i14] += A->data[i13 + A->size[0] * cr]
                  * U->data[cr + U->size[0] * i14];
              }
            }
          }

          i13 = U->size[0] * U->size[1];
          U->size[0] = C->size[0];
          U->size[1] = C->size[1];
          emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
          br = C->size[1];
          for (i13 = 0; i13 < br; i13++) {
            ar = C->size[0];
            for (i14 = 0; i14 < ar; i14++) {
              U->data[i14 + U->size[0] * i13] = C->data[i14 + C->size[0] * i13];
            }
          }
        } else {
          k = A->size[1];
          unnamed_idx_0 = (unsigned int)A->size[0];
          unnamed_idx_1 = (unsigned int)U->size[1];
          i13 = U->size[0] * U->size[1];
          U->size[0] = (int)unnamed_idx_0;
          U->size[1] = (int)unnamed_idx_1;
          emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
          b_m = A->size[0];
          i13 = U->size[0] * U->size[1];
          emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
          br = U->size[1];
          for (i13 = 0; i13 < br; i13++) {
            ar = U->size[0];
            for (i14 = 0; i14 < ar; i14++) {
              U->data[i14 + U->size[0] * i13] = 0.0;
            }
          }

          if ((A->size[0] == 0) || (b->size[1] == 0)) {
          } else {
            c = A->size[0] * (b->size[1] - 1);
            cr = 0;
            while ((b_m > 0) && (cr <= c)) {
              i13 = cr + b_m;
              for (ic = cr; ic + 1 <= i13; ic++) {
                U->data[ic] = 0.0;
              }

              cr += b_m;
            }

            br = 0;
            cr = 0;
            while ((b_m > 0) && (cr <= c)) {
              ar = -1;
              i13 = br + k;
              for (ib = br; ib + 1 <= i13; ib++) {
                if (b->data[ib] != 0.0) {
                  ia = ar;
                  i14 = cr + b_m;
                  for (ic = cr; ic + 1 <= i14; ic++) {
                    ia++;
                    U->data[ic] += b->data[ib] * A->data[ia];
                  }
                }

                ar += b_m;
              }

              br += k;
              cr += b_m;
            }
          }
        }

        emxFree_real_T(&C);
        i13 = V->size[0] * V->size[1];
        V->size[0] = A4->size[0];
        V->size[1] = A4->size[1];
        emxEnsureCapacity((emxArray__common *)V, i13, (int)sizeof(double));
        br = A4->size[0] * A4->size[1];
        for (i13 = 0; i13 < br; i13++) {
          V->data[i13] = (56.0 * A4->data[i13] + 25200.0 * A3->data[i13]) +
            1.99584E+6 * A2->data[i13];
        }

        d = 1.729728E+7;
      } else if (m == 9) {
        if ((A4->size[1] == 1) || (A2->size[0] == 1)) {
          i13 = V->size[0] * V->size[1];
          V->size[0] = A4->size[0];
          V->size[1] = A2->size[1];
          emxEnsureCapacity((emxArray__common *)V, i13, (int)sizeof(double));
          br = A4->size[0];
          for (i13 = 0; i13 < br; i13++) {
            ar = A2->size[1];
            for (i14 = 0; i14 < ar; i14++) {
              V->data[i13 + V->size[0] * i14] = 0.0;
              c = A4->size[1];
              for (cr = 0; cr < c; cr++) {
                V->data[i13 + V->size[0] * i14] += A4->data[i13 + A4->size[0] *
                  cr] * A2->data[cr + A2->size[0] * i14];
              }
            }
          }
        } else {
          k = A4->size[1];
          unnamed_idx_0 = (unsigned int)A4->size[0];
          unnamed_idx_1 = (unsigned int)A2->size[1];
          i13 = V->size[0] * V->size[1];
          V->size[0] = (int)unnamed_idx_0;
          V->size[1] = (int)unnamed_idx_1;
          emxEnsureCapacity((emxArray__common *)V, i13, (int)sizeof(double));
          b_m = A4->size[0];
          i13 = V->size[0] * V->size[1];
          emxEnsureCapacity((emxArray__common *)V, i13, (int)sizeof(double));
          br = V->size[1];
          for (i13 = 0; i13 < br; i13++) {
            ar = V->size[0];
            for (i14 = 0; i14 < ar; i14++) {
              V->data[i14 + V->size[0] * i13] = 0.0;
            }
          }

          if ((A4->size[0] == 0) || (A2->size[1] == 0)) {
          } else {
            c = A4->size[0] * (A2->size[1] - 1);
            cr = 0;
            while ((b_m > 0) && (cr <= c)) {
              i13 = cr + b_m;
              for (ic = cr; ic + 1 <= i13; ic++) {
                V->data[ic] = 0.0;
              }

              cr += b_m;
            }

            br = 0;
            cr = 0;
            while ((b_m > 0) && (cr <= c)) {
              ar = -1;
              i13 = br + k;
              for (ib = br; ib + 1 <= i13; ib++) {
                if (A2->data[ib] != 0.0) {
                  ia = ar;
                  i14 = cr + b_m;
                  for (ic = cr; ic + 1 <= i14; ic++) {
                    ia++;
                    V->data[ic] += A2->data[ib] * A4->data[ia];
                  }
                }

                ar += b_m;
              }

              br += k;
              cr += b_m;
            }
          }
        }

        i13 = U->size[0] * U->size[1];
        U->size[0] = V->size[0];
        U->size[1] = V->size[1];
        emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
        br = V->size[0] * V->size[1];
        for (i13 = 0; i13 < br; i13++) {
          U->data[i13] = ((V->data[i13] + 3960.0 * A4->data[i13]) + 2.16216E+6 *
                          A3->data[i13]) + 3.027024E+8 * A2->data[i13];
        }

        for (k = 0; k <= n; k++) {
          U->data[k + U->size[0] * k] += 8.8216128E+9;
        }

        i13 = b->size[0] * b->size[1];
        b->size[0] = U->size[0];
        b->size[1] = U->size[1];
        emxEnsureCapacity((emxArray__common *)b, i13, (int)sizeof(double));
        br = U->size[0] * U->size[1];
        for (i13 = 0; i13 < br; i13++) {
          b->data[i13] = U->data[i13];
        }

        emxInit_real_T(&C, 2);
        if ((A->size[1] == 1) || (U->size[0] == 1)) {
          i13 = C->size[0] * C->size[1];
          C->size[0] = A->size[0];
          C->size[1] = U->size[1];
          emxEnsureCapacity((emxArray__common *)C, i13, (int)sizeof(double));
          br = A->size[0];
          for (i13 = 0; i13 < br; i13++) {
            ar = U->size[1];
            for (i14 = 0; i14 < ar; i14++) {
              C->data[i13 + C->size[0] * i14] = 0.0;
              c = A->size[1];
              for (cr = 0; cr < c; cr++) {
                C->data[i13 + C->size[0] * i14] += A->data[i13 + A->size[0] * cr]
                  * U->data[cr + U->size[0] * i14];
              }
            }
          }

          i13 = U->size[0] * U->size[1];
          U->size[0] = C->size[0];
          U->size[1] = C->size[1];
          emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
          br = C->size[1];
          for (i13 = 0; i13 < br; i13++) {
            ar = C->size[0];
            for (i14 = 0; i14 < ar; i14++) {
              U->data[i14 + U->size[0] * i13] = C->data[i14 + C->size[0] * i13];
            }
          }
        } else {
          k = A->size[1];
          unnamed_idx_0 = (unsigned int)A->size[0];
          unnamed_idx_1 = (unsigned int)U->size[1];
          i13 = U->size[0] * U->size[1];
          U->size[0] = (int)unnamed_idx_0;
          U->size[1] = (int)unnamed_idx_1;
          emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
          b_m = A->size[0];
          i13 = U->size[0] * U->size[1];
          emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
          br = U->size[1];
          for (i13 = 0; i13 < br; i13++) {
            ar = U->size[0];
            for (i14 = 0; i14 < ar; i14++) {
              U->data[i14 + U->size[0] * i13] = 0.0;
            }
          }

          if ((A->size[0] == 0) || (b->size[1] == 0)) {
          } else {
            c = A->size[0] * (b->size[1] - 1);
            cr = 0;
            while ((b_m > 0) && (cr <= c)) {
              i13 = cr + b_m;
              for (ic = cr; ic + 1 <= i13; ic++) {
                U->data[ic] = 0.0;
              }

              cr += b_m;
            }

            br = 0;
            cr = 0;
            while ((b_m > 0) && (cr <= c)) {
              ar = -1;
              i13 = br + k;
              for (ib = br; ib + 1 <= i13; ib++) {
                if (b->data[ib] != 0.0) {
                  ia = ar;
                  i14 = cr + b_m;
                  for (ic = cr; ic + 1 <= i14; ic++) {
                    ia++;
                    U->data[ic] += b->data[ib] * A->data[ia];
                  }
                }

                ar += b_m;
              }

              br += k;
              cr += b_m;
            }
          }
        }

        emxFree_real_T(&C);
        i13 = V->size[0] * V->size[1];
        emxEnsureCapacity((emxArray__common *)V, i13, (int)sizeof(double));
        c = V->size[0];
        cr = V->size[1];
        br = c * cr;
        for (i13 = 0; i13 < br; i13++) {
          V->data[i13] = ((90.0 * V->data[i13] + 110880.0 * A4->data[i13]) +
                          3.027024E+7 * A3->data[i13]) + 2.0756736E+9 * A2->
            data[i13];
        }

        d = 1.76432256E+10;
      } else {
        i13 = U->size[0] * U->size[1];
        U->size[0] = A4->size[0];
        U->size[1] = A4->size[1];
        emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
        br = A4->size[0] * A4->size[1];
        for (i13 = 0; i13 < br; i13++) {
          U->data[i13] = (3.352212864E+10 * A4->data[i13] + 1.05594705216E+13 *
                          A3->data[i13]) + 1.1873537964288E+15 * A2->data[i13];
        }

        for (k = 0; k <= n; k++) {
          U->data[k + U->size[0] * k] += 3.238237626624E+16;
        }

        i13 = b->size[0] * b->size[1];
        b->size[0] = A4->size[0];
        b->size[1] = A4->size[1];
        emxEnsureCapacity((emxArray__common *)b, i13, (int)sizeof(double));
        br = A4->size[0] * A4->size[1];
        for (i13 = 0; i13 < br; i13++) {
          b->data[i13] = (A4->data[i13] + 16380.0 * A3->data[i13]) + 4.08408E+7 *
            A2->data[i13];
        }

        emxInit_real_T(&C, 2);
        if ((A4->size[1] == 1) || (b->size[0] == 1)) {
          i13 = C->size[0] * C->size[1];
          C->size[0] = A4->size[0];
          C->size[1] = b->size[1];
          emxEnsureCapacity((emxArray__common *)C, i13, (int)sizeof(double));
          br = A4->size[0];
          for (i13 = 0; i13 < br; i13++) {
            ar = b->size[1];
            for (i14 = 0; i14 < ar; i14++) {
              C->data[i13 + C->size[0] * i14] = 0.0;
              c = A4->size[1];
              for (cr = 0; cr < c; cr++) {
                C->data[i13 + C->size[0] * i14] += A4->data[i13 + A4->size[0] *
                  cr] * b->data[cr + b->size[0] * i14];
              }
            }
          }
        } else {
          k = A4->size[1];
          unnamed_idx_0 = (unsigned int)A4->size[0];
          unnamed_idx_1 = (unsigned int)b->size[1];
          i13 = C->size[0] * C->size[1];
          C->size[0] = (int)unnamed_idx_0;
          C->size[1] = (int)unnamed_idx_1;
          emxEnsureCapacity((emxArray__common *)C, i13, (int)sizeof(double));
          b_m = A4->size[0];
          i13 = C->size[0] * C->size[1];
          emxEnsureCapacity((emxArray__common *)C, i13, (int)sizeof(double));
          br = C->size[1];
          for (i13 = 0; i13 < br; i13++) {
            ar = C->size[0];
            for (i14 = 0; i14 < ar; i14++) {
              C->data[i14 + C->size[0] * i13] = 0.0;
            }
          }

          if ((A4->size[0] == 0) || (b->size[1] == 0)) {
          } else {
            c = A4->size[0] * (b->size[1] - 1);
            cr = 0;
            while ((b_m > 0) && (cr <= c)) {
              i13 = cr + b_m;
              for (ic = cr; ic + 1 <= i13; ic++) {
                C->data[ic] = 0.0;
              }

              cr += b_m;
            }

            br = 0;
            cr = 0;
            while ((b_m > 0) && (cr <= c)) {
              ar = -1;
              i13 = br + k;
              for (ib = br; ib + 1 <= i13; ib++) {
                if (b->data[ib] != 0.0) {
                  ia = ar;
                  i14 = cr + b_m;
                  for (ic = cr; ic + 1 <= i14; ic++) {
                    ia++;
                    C->data[ic] += b->data[ib] * A4->data[ia];
                  }
                }

                ar += b_m;
              }

              br += k;
              cr += b_m;
            }
          }
        }

        i13 = C->size[0] * C->size[1];
        emxEnsureCapacity((emxArray__common *)C, i13, (int)sizeof(double));
        c = C->size[0];
        cr = C->size[1];
        br = c * cr;
        for (i13 = 0; i13 < br; i13++) {
          C->data[i13] += U->data[i13];
        }

        if ((A->size[1] == 1) || (C->size[0] == 1)) {
          i13 = U->size[0] * U->size[1];
          U->size[0] = A->size[0];
          U->size[1] = C->size[1];
          emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
          br = A->size[0];
          for (i13 = 0; i13 < br; i13++) {
            ar = C->size[1];
            for (i14 = 0; i14 < ar; i14++) {
              U->data[i13 + U->size[0] * i14] = 0.0;
              c = A->size[1];
              for (cr = 0; cr < c; cr++) {
                U->data[i13 + U->size[0] * i14] += A->data[i13 + A->size[0] * cr]
                  * C->data[cr + C->size[0] * i14];
              }
            }
          }
        } else {
          k = A->size[1];
          unnamed_idx_0 = (unsigned int)A->size[0];
          unnamed_idx_1 = (unsigned int)C->size[1];
          i13 = U->size[0] * U->size[1];
          U->size[0] = (int)unnamed_idx_0;
          U->size[1] = (int)unnamed_idx_1;
          emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
          b_m = A->size[0];
          i13 = U->size[0] * U->size[1];
          emxEnsureCapacity((emxArray__common *)U, i13, (int)sizeof(double));
          br = U->size[1];
          for (i13 = 0; i13 < br; i13++) {
            ar = U->size[0];
            for (i14 = 0; i14 < ar; i14++) {
              U->data[i14 + U->size[0] * i13] = 0.0;
            }
          }

          if ((A->size[0] == 0) || (C->size[1] == 0)) {
          } else {
            c = A->size[0] * (C->size[1] - 1);
            cr = 0;
            while ((b_m > 0) && (cr <= c)) {
              i13 = cr + b_m;
              for (ic = cr; ic + 1 <= i13; ic++) {
                U->data[ic] = 0.0;
              }

              cr += b_m;
            }

            br = 0;
            cr = 0;
            while ((b_m > 0) && (cr <= c)) {
              ar = -1;
              i13 = br + k;
              for (ib = br; ib + 1 <= i13; ib++) {
                if (C->data[ib] != 0.0) {
                  ia = ar;
                  i14 = cr + b_m;
                  for (ic = cr; ic + 1 <= i14; ic++) {
                    ia++;
                    U->data[ic] += C->data[ib] * A->data[ia];
                  }
                }

                ar += b_m;
              }

              br += k;
              cr += b_m;
            }
          }
        }

        emxFree_real_T(&C);
        i13 = b->size[0] * b->size[1];
        b->size[0] = A4->size[0];
        b->size[1] = A4->size[1];
        emxEnsureCapacity((emxArray__common *)b, i13, (int)sizeof(double));
        br = A4->size[0] * A4->size[1];
        for (i13 = 0; i13 < br; i13++) {
          b->data[i13] = (182.0 * A4->data[i13] + 960960.0 * A3->data[i13]) +
            1.32324192E+9 * A2->data[i13];
        }

        if ((A4->size[1] == 1) || (b->size[0] == 1)) {
          i13 = V->size[0] * V->size[1];
          V->size[0] = A4->size[0];
          V->size[1] = b->size[1];
          emxEnsureCapacity((emxArray__common *)V, i13, (int)sizeof(double));
          br = A4->size[0];
          for (i13 = 0; i13 < br; i13++) {
            ar = b->size[1];
            for (i14 = 0; i14 < ar; i14++) {
              V->data[i13 + V->size[0] * i14] = 0.0;
              c = A4->size[1];
              for (cr = 0; cr < c; cr++) {
                V->data[i13 + V->size[0] * i14] += A4->data[i13 + A4->size[0] *
                  cr] * b->data[cr + b->size[0] * i14];
              }
            }
          }
        } else {
          k = A4->size[1];
          unnamed_idx_0 = (unsigned int)A4->size[0];
          unnamed_idx_1 = (unsigned int)b->size[1];
          i13 = V->size[0] * V->size[1];
          V->size[0] = (int)unnamed_idx_0;
          V->size[1] = (int)unnamed_idx_1;
          emxEnsureCapacity((emxArray__common *)V, i13, (int)sizeof(double));
          b_m = A4->size[0];
          i13 = V->size[0] * V->size[1];
          emxEnsureCapacity((emxArray__common *)V, i13, (int)sizeof(double));
          br = V->size[1];
          for (i13 = 0; i13 < br; i13++) {
            ar = V->size[0];
            for (i14 = 0; i14 < ar; i14++) {
              V->data[i14 + V->size[0] * i13] = 0.0;
            }
          }

          if ((A4->size[0] == 0) || (b->size[1] == 0)) {
          } else {
            c = A4->size[0] * (b->size[1] - 1);
            cr = 0;
            while ((b_m > 0) && (cr <= c)) {
              i13 = cr + b_m;
              for (ic = cr; ic + 1 <= i13; ic++) {
                V->data[ic] = 0.0;
              }

              cr += b_m;
            }

            br = 0;
            cr = 0;
            while ((b_m > 0) && (cr <= c)) {
              ar = -1;
              i13 = br + k;
              for (ib = br; ib + 1 <= i13; ib++) {
                if (b->data[ib] != 0.0) {
                  ia = ar;
                  i14 = cr + b_m;
                  for (ic = cr; ic + 1 <= i14; ic++) {
                    ia++;
                    V->data[ic] += b->data[ib] * A4->data[ia];
                  }
                }

                ar += b_m;
              }

              br += k;
              cr += b_m;
            }
          }
        }

        i13 = V->size[0] * V->size[1];
        emxEnsureCapacity((emxArray__common *)V, i13, (int)sizeof(double));
        c = V->size[0];
        cr = V->size[1];
        br = c * cr;
        for (i13 = 0; i13 < br; i13++) {
          V->data[i13] = ((V->data[i13] + 6.704425728E+11 * A4->data[i13]) +
                          1.29060195264E+14 * A3->data[i13]) +
            7.7717703038976E+15 * A2->data[i13];
        }

        d = 6.476475253248E+16;
      }

      emxFree_real_T(&A4);
    }

    emxFree_real_T(&A3);
  }

  emxFree_real_T(&b);
  emxFree_real_T(&A2);
  for (k = 0; k <= n; k++) {
    V->data[k + V->size[0] * k] += d;
  }

  i13 = U->size[0] * U->size[1];
  for (k = 0; k < i13; k++) {
    V->data[k] -= U->data[k];
    U->data[k] *= 2.0;
  }

  mldivide(V, U, F);
  k = 0;
  emxFree_real_T(&V);
  emxFree_real_T(&U);
  while (k <= n) {
    F->data[k + F->size[0] * k]++;
    k++;
  }
}

/*
 * Arguments    : const emxArray_real_T *A
 *                emxArray_real_T *F
 * Return Type  : void
 */
static void b_PadeApproximantOfDegree(const emxArray_real_T *A, emxArray_real_T *
  F)
{
  int n;
  emxArray_real_T *A2;
  int i15;
  int br;
  int ar;
  int i16;
  int c;
  int cr;
  int k;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  int m;
  int ic;
  int ib;
  int ia;
  emxArray_real_T *A3;
  emxArray_real_T *A4;
  emxArray_real_T *U;
  emxArray_real_T *b;
  emxArray_real_T *C;
  emxArray_real_T *V;
  n = A->size[0] - 1;
  emxInit_real_T(&A2, 2);
  if ((A->size[1] == 1) || (A->size[0] == 1)) {
    i15 = A2->size[0] * A2->size[1];
    A2->size[0] = A->size[0];
    A2->size[1] = A->size[1];
    emxEnsureCapacity((emxArray__common *)A2, i15, (int)sizeof(double));
    br = A->size[0];
    for (i15 = 0; i15 < br; i15++) {
      ar = A->size[1];
      for (i16 = 0; i16 < ar; i16++) {
        A2->data[i15 + A2->size[0] * i16] = 0.0;
        c = A->size[1];
        for (cr = 0; cr < c; cr++) {
          A2->data[i15 + A2->size[0] * i16] += A->data[i15 + A->size[0] * cr] *
            A->data[cr + A->size[0] * i16];
        }
      }
    }
  } else {
    k = A->size[1];
    unnamed_idx_0 = (unsigned int)A->size[0];
    unnamed_idx_1 = (unsigned int)A->size[1];
    i15 = A2->size[0] * A2->size[1];
    A2->size[0] = (int)unnamed_idx_0;
    A2->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)A2, i15, (int)sizeof(double));
    m = A->size[0];
    i15 = A2->size[0] * A2->size[1];
    emxEnsureCapacity((emxArray__common *)A2, i15, (int)sizeof(double));
    br = A2->size[1];
    for (i15 = 0; i15 < br; i15++) {
      ar = A2->size[0];
      for (i16 = 0; i16 < ar; i16++) {
        A2->data[i16 + A2->size[0] * i15] = 0.0;
      }
    }

    if ((A->size[0] == 0) || (A->size[1] == 0)) {
    } else {
      c = A->size[0] * (A->size[1] - 1);
      cr = 0;
      while ((m > 0) && (cr <= c)) {
        i15 = cr + m;
        for (ic = cr; ic + 1 <= i15; ic++) {
          A2->data[ic] = 0.0;
        }

        cr += m;
      }

      br = 0;
      cr = 0;
      while ((m > 0) && (cr <= c)) {
        ar = -1;
        i15 = br + k;
        for (ib = br; ib + 1 <= i15; ib++) {
          if (A->data[ib] != 0.0) {
            ia = ar;
            i16 = cr + m;
            for (ic = cr; ic + 1 <= i16; ic++) {
              ia++;
              A2->data[ic] += A->data[ib] * A->data[ia];
            }
          }

          ar += m;
        }

        br += k;
        cr += m;
      }
    }
  }

  emxInit_real_T(&A3, 2);
  if ((A2->size[1] == 1) || (A2->size[0] == 1)) {
    i15 = A3->size[0] * A3->size[1];
    A3->size[0] = A2->size[0];
    A3->size[1] = A2->size[1];
    emxEnsureCapacity((emxArray__common *)A3, i15, (int)sizeof(double));
    br = A2->size[0];
    for (i15 = 0; i15 < br; i15++) {
      ar = A2->size[1];
      for (i16 = 0; i16 < ar; i16++) {
        A3->data[i15 + A3->size[0] * i16] = 0.0;
        c = A2->size[1];
        for (cr = 0; cr < c; cr++) {
          A3->data[i15 + A3->size[0] * i16] += A2->data[i15 + A2->size[0] * cr] *
            A2->data[cr + A2->size[0] * i16];
        }
      }
    }
  } else {
    k = A2->size[1];
    unnamed_idx_0 = (unsigned int)A2->size[0];
    unnamed_idx_1 = (unsigned int)A2->size[1];
    i15 = A3->size[0] * A3->size[1];
    A3->size[0] = (int)unnamed_idx_0;
    A3->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)A3, i15, (int)sizeof(double));
    m = A2->size[0];
    i15 = A3->size[0] * A3->size[1];
    emxEnsureCapacity((emxArray__common *)A3, i15, (int)sizeof(double));
    br = A3->size[1];
    for (i15 = 0; i15 < br; i15++) {
      ar = A3->size[0];
      for (i16 = 0; i16 < ar; i16++) {
        A3->data[i16 + A3->size[0] * i15] = 0.0;
      }
    }

    if ((A2->size[0] == 0) || (A2->size[1] == 0)) {
    } else {
      c = A2->size[0] * (A2->size[1] - 1);
      cr = 0;
      while ((m > 0) && (cr <= c)) {
        i15 = cr + m;
        for (ic = cr; ic + 1 <= i15; ic++) {
          A3->data[ic] = 0.0;
        }

        cr += m;
      }

      br = 0;
      cr = 0;
      while ((m > 0) && (cr <= c)) {
        ar = -1;
        i15 = br + k;
        for (ib = br; ib + 1 <= i15; ib++) {
          if (A2->data[ib] != 0.0) {
            ia = ar;
            i16 = cr + m;
            for (ic = cr; ic + 1 <= i16; ic++) {
              ia++;
              A3->data[ic] += A2->data[ib] * A2->data[ia];
            }
          }

          ar += m;
        }

        br += k;
        cr += m;
      }
    }
  }

  emxInit_real_T(&A4, 2);
  if ((A3->size[1] == 1) || (A2->size[0] == 1)) {
    i15 = A4->size[0] * A4->size[1];
    A4->size[0] = A3->size[0];
    A4->size[1] = A2->size[1];
    emxEnsureCapacity((emxArray__common *)A4, i15, (int)sizeof(double));
    br = A3->size[0];
    for (i15 = 0; i15 < br; i15++) {
      ar = A2->size[1];
      for (i16 = 0; i16 < ar; i16++) {
        A4->data[i15 + A4->size[0] * i16] = 0.0;
        c = A3->size[1];
        for (cr = 0; cr < c; cr++) {
          A4->data[i15 + A4->size[0] * i16] += A3->data[i15 + A3->size[0] * cr] *
            A2->data[cr + A2->size[0] * i16];
        }
      }
    }
  } else {
    k = A3->size[1];
    unnamed_idx_0 = (unsigned int)A3->size[0];
    unnamed_idx_1 = (unsigned int)A2->size[1];
    i15 = A4->size[0] * A4->size[1];
    A4->size[0] = (int)unnamed_idx_0;
    A4->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)A4, i15, (int)sizeof(double));
    m = A3->size[0];
    i15 = A4->size[0] * A4->size[1];
    emxEnsureCapacity((emxArray__common *)A4, i15, (int)sizeof(double));
    br = A4->size[1];
    for (i15 = 0; i15 < br; i15++) {
      ar = A4->size[0];
      for (i16 = 0; i16 < ar; i16++) {
        A4->data[i16 + A4->size[0] * i15] = 0.0;
      }
    }

    if ((A3->size[0] == 0) || (A2->size[1] == 0)) {
    } else {
      c = A3->size[0] * (A2->size[1] - 1);
      cr = 0;
      while ((m > 0) && (cr <= c)) {
        i15 = cr + m;
        for (ic = cr; ic + 1 <= i15; ic++) {
          A4->data[ic] = 0.0;
        }

        cr += m;
      }

      br = 0;
      cr = 0;
      while ((m > 0) && (cr <= c)) {
        ar = -1;
        i15 = br + k;
        for (ib = br; ib + 1 <= i15; ib++) {
          if (A2->data[ib] != 0.0) {
            ia = ar;
            i16 = cr + m;
            for (ic = cr; ic + 1 <= i16; ic++) {
              ia++;
              A4->data[ic] += A2->data[ib] * A3->data[ia];
            }
          }

          ar += m;
        }

        br += k;
        cr += m;
      }
    }
  }

  emxInit_real_T(&U, 2);
  i15 = U->size[0] * U->size[1];
  U->size[0] = A4->size[0];
  U->size[1] = A4->size[1];
  emxEnsureCapacity((emxArray__common *)U, i15, (int)sizeof(double));
  br = A4->size[0] * A4->size[1];
  for (i15 = 0; i15 < br; i15++) {
    U->data[i15] = (3.352212864E+10 * A4->data[i15] + 1.05594705216E+13 *
                    A3->data[i15]) + 1.1873537964288E+15 * A2->data[i15];
  }

  for (k = 0; k <= n; k++) {
    U->data[k + U->size[0] * k] += 3.238237626624E+16;
  }

  emxInit_real_T(&b, 2);
  i15 = b->size[0] * b->size[1];
  b->size[0] = A4->size[0];
  b->size[1] = A4->size[1];
  emxEnsureCapacity((emxArray__common *)b, i15, (int)sizeof(double));
  br = A4->size[0] * A4->size[1];
  for (i15 = 0; i15 < br; i15++) {
    b->data[i15] = (A4->data[i15] + 16380.0 * A3->data[i15]) + 4.08408E+7 *
      A2->data[i15];
  }

  emxInit_real_T(&C, 2);
  if ((A4->size[1] == 1) || (b->size[0] == 1)) {
    i15 = C->size[0] * C->size[1];
    C->size[0] = A4->size[0];
    C->size[1] = b->size[1];
    emxEnsureCapacity((emxArray__common *)C, i15, (int)sizeof(double));
    br = A4->size[0];
    for (i15 = 0; i15 < br; i15++) {
      ar = b->size[1];
      for (i16 = 0; i16 < ar; i16++) {
        C->data[i15 + C->size[0] * i16] = 0.0;
        c = A4->size[1];
        for (cr = 0; cr < c; cr++) {
          C->data[i15 + C->size[0] * i16] += A4->data[i15 + A4->size[0] * cr] *
            b->data[cr + b->size[0] * i16];
        }
      }
    }
  } else {
    k = A4->size[1];
    unnamed_idx_0 = (unsigned int)A4->size[0];
    unnamed_idx_1 = (unsigned int)b->size[1];
    i15 = C->size[0] * C->size[1];
    C->size[0] = (int)unnamed_idx_0;
    C->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)C, i15, (int)sizeof(double));
    m = A4->size[0];
    i15 = C->size[0] * C->size[1];
    emxEnsureCapacity((emxArray__common *)C, i15, (int)sizeof(double));
    br = C->size[1];
    for (i15 = 0; i15 < br; i15++) {
      ar = C->size[0];
      for (i16 = 0; i16 < ar; i16++) {
        C->data[i16 + C->size[0] * i15] = 0.0;
      }
    }

    if ((A4->size[0] == 0) || (b->size[1] == 0)) {
    } else {
      c = A4->size[0] * (b->size[1] - 1);
      cr = 0;
      while ((m > 0) && (cr <= c)) {
        i15 = cr + m;
        for (ic = cr; ic + 1 <= i15; ic++) {
          C->data[ic] = 0.0;
        }

        cr += m;
      }

      br = 0;
      cr = 0;
      while ((m > 0) && (cr <= c)) {
        ar = -1;
        i15 = br + k;
        for (ib = br; ib + 1 <= i15; ib++) {
          if (b->data[ib] != 0.0) {
            ia = ar;
            i16 = cr + m;
            for (ic = cr; ic + 1 <= i16; ic++) {
              ia++;
              C->data[ic] += b->data[ib] * A4->data[ia];
            }
          }

          ar += m;
        }

        br += k;
        cr += m;
      }
    }
  }

  i15 = C->size[0] * C->size[1];
  emxEnsureCapacity((emxArray__common *)C, i15, (int)sizeof(double));
  c = C->size[0];
  cr = C->size[1];
  br = c * cr;
  for (i15 = 0; i15 < br; i15++) {
    C->data[i15] += U->data[i15];
  }

  if ((A->size[1] == 1) || (C->size[0] == 1)) {
    i15 = U->size[0] * U->size[1];
    U->size[0] = A->size[0];
    U->size[1] = C->size[1];
    emxEnsureCapacity((emxArray__common *)U, i15, (int)sizeof(double));
    br = A->size[0];
    for (i15 = 0; i15 < br; i15++) {
      ar = C->size[1];
      for (i16 = 0; i16 < ar; i16++) {
        U->data[i15 + U->size[0] * i16] = 0.0;
        c = A->size[1];
        for (cr = 0; cr < c; cr++) {
          U->data[i15 + U->size[0] * i16] += A->data[i15 + A->size[0] * cr] *
            C->data[cr + C->size[0] * i16];
        }
      }
    }
  } else {
    k = A->size[1];
    unnamed_idx_0 = (unsigned int)A->size[0];
    unnamed_idx_1 = (unsigned int)C->size[1];
    i15 = U->size[0] * U->size[1];
    U->size[0] = (int)unnamed_idx_0;
    U->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)U, i15, (int)sizeof(double));
    m = A->size[0];
    i15 = U->size[0] * U->size[1];
    emxEnsureCapacity((emxArray__common *)U, i15, (int)sizeof(double));
    br = U->size[1];
    for (i15 = 0; i15 < br; i15++) {
      ar = U->size[0];
      for (i16 = 0; i16 < ar; i16++) {
        U->data[i16 + U->size[0] * i15] = 0.0;
      }
    }

    if ((A->size[0] == 0) || (C->size[1] == 0)) {
    } else {
      c = A->size[0] * (C->size[1] - 1);
      cr = 0;
      while ((m > 0) && (cr <= c)) {
        i15 = cr + m;
        for (ic = cr; ic + 1 <= i15; ic++) {
          U->data[ic] = 0.0;
        }

        cr += m;
      }

      br = 0;
      cr = 0;
      while ((m > 0) && (cr <= c)) {
        ar = -1;
        i15 = br + k;
        for (ib = br; ib + 1 <= i15; ib++) {
          if (C->data[ib] != 0.0) {
            ia = ar;
            i16 = cr + m;
            for (ic = cr; ic + 1 <= i16; ic++) {
              ia++;
              U->data[ic] += C->data[ib] * A->data[ia];
            }
          }

          ar += m;
        }

        br += k;
        cr += m;
      }
    }
  }

  emxFree_real_T(&C);
  i15 = b->size[0] * b->size[1];
  b->size[0] = A4->size[0];
  b->size[1] = A4->size[1];
  emxEnsureCapacity((emxArray__common *)b, i15, (int)sizeof(double));
  br = A4->size[0] * A4->size[1];
  for (i15 = 0; i15 < br; i15++) {
    b->data[i15] = (182.0 * A4->data[i15] + 960960.0 * A3->data[i15]) +
      1.32324192E+9 * A2->data[i15];
  }

  emxInit_real_T(&V, 2);
  if ((A4->size[1] == 1) || (b->size[0] == 1)) {
    i15 = V->size[0] * V->size[1];
    V->size[0] = A4->size[0];
    V->size[1] = b->size[1];
    emxEnsureCapacity((emxArray__common *)V, i15, (int)sizeof(double));
    br = A4->size[0];
    for (i15 = 0; i15 < br; i15++) {
      ar = b->size[1];
      for (i16 = 0; i16 < ar; i16++) {
        V->data[i15 + V->size[0] * i16] = 0.0;
        c = A4->size[1];
        for (cr = 0; cr < c; cr++) {
          V->data[i15 + V->size[0] * i16] += A4->data[i15 + A4->size[0] * cr] *
            b->data[cr + b->size[0] * i16];
        }
      }
    }
  } else {
    k = A4->size[1];
    unnamed_idx_0 = (unsigned int)A4->size[0];
    unnamed_idx_1 = (unsigned int)b->size[1];
    i15 = V->size[0] * V->size[1];
    V->size[0] = (int)unnamed_idx_0;
    V->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)V, i15, (int)sizeof(double));
    m = A4->size[0];
    i15 = V->size[0] * V->size[1];
    emxEnsureCapacity((emxArray__common *)V, i15, (int)sizeof(double));
    br = V->size[1];
    for (i15 = 0; i15 < br; i15++) {
      ar = V->size[0];
      for (i16 = 0; i16 < ar; i16++) {
        V->data[i16 + V->size[0] * i15] = 0.0;
      }
    }

    if ((A4->size[0] == 0) || (b->size[1] == 0)) {
    } else {
      c = A4->size[0] * (b->size[1] - 1);
      cr = 0;
      while ((m > 0) && (cr <= c)) {
        i15 = cr + m;
        for (ic = cr; ic + 1 <= i15; ic++) {
          V->data[ic] = 0.0;
        }

        cr += m;
      }

      br = 0;
      cr = 0;
      while ((m > 0) && (cr <= c)) {
        ar = -1;
        i15 = br + k;
        for (ib = br; ib + 1 <= i15; ib++) {
          if (b->data[ib] != 0.0) {
            ia = ar;
            i16 = cr + m;
            for (ic = cr; ic + 1 <= i16; ic++) {
              ia++;
              V->data[ic] += b->data[ib] * A4->data[ia];
            }
          }

          ar += m;
        }

        br += k;
        cr += m;
      }
    }
  }

  emxFree_real_T(&b);
  i15 = V->size[0] * V->size[1];
  emxEnsureCapacity((emxArray__common *)V, i15, (int)sizeof(double));
  c = V->size[0];
  cr = V->size[1];
  br = c * cr;
  for (i15 = 0; i15 < br; i15++) {
    V->data[i15] = ((V->data[i15] + 6.704425728E+11 * A4->data[i15]) +
                    1.29060195264E+14 * A3->data[i15]) + 7.7717703038976E+15 *
      A2->data[i15];
  }

  emxFree_real_T(&A4);
  emxFree_real_T(&A3);
  emxFree_real_T(&A2);
  for (k = 0; k <= n; k++) {
    V->data[k + V->size[0] * k] += 6.476475253248E+16;
  }

  i15 = U->size[0] * U->size[1];
  for (k = 0; k < i15; k++) {
    V->data[k] -= U->data[k];
    U->data[k] *= 2.0;
  }

  mldivide(V, U, F);
  k = 0;
  emxFree_real_T(&V);
  emxFree_real_T(&U);
  while (k <= n) {
    F->data[k + F->size[0] * k]++;
    k++;
  }
}

/*
 * Arguments    : emxArray_real_T *A
 *                emxArray_real_T *F
 * Return Type  : void
 */
void expm(emxArray_real_T *A, emxArray_real_T *F)
{
  int i11;
  int i12;
  double normA;
  int eint;
  boolean_T exitg1;
  static const double theta[5] = { 0.01495585217958292, 0.253939833006323,
    0.95041789961629319, 2.097847961257068, 5.3719203511481517 };

  static const unsigned char uv1[5] = { 3U, 5U, 7U, 9U, 13U };

  double s;
  int b_A;
  int br;
  int j;
  emxArray_real_T *a;
  emxArray_real_T *b_F;
  int ar;
  int k;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  int m;
  int ic;
  int ib;
  int ia;
  for (i11 = 0; i11 < 2; i11++) {
    i12 = F->size[0] * F->size[1];
    F->size[i11] = A->size[i11];
    emxEnsureCapacity((emxArray__common *)F, i12, (int)sizeof(double));
  }

  if ((A->size[0] == 0) || (A->size[1] == 0)) {
  } else {
    normA = norm(A);
    if (normA <= 5.3719203511481517) {
      eint = 0;
      exitg1 = false;
      while ((!exitg1) && (eint < 5)) {
        if (normA <= theta[eint]) {
          PadeApproximantOfDegree(A, uv1[eint], F);
          exitg1 = true;
        } else {
          eint++;
        }
      }
    } else {
      normA /= 5.3719203511481517;
      if ((!rtIsInf(normA)) && (!rtIsNaN(normA))) {
        normA = frexp(normA, &eint);
      } else {
        eint = 0;
      }

      s = eint;
      if (normA == 0.5) {
        s = (double)eint - 1.0;
      }

      normA = rt_powd_snf(2.0, s);
      i11 = A->size[0] * A->size[1];
      emxEnsureCapacity((emxArray__common *)A, i11, (int)sizeof(double));
      eint = A->size[0];
      b_A = A->size[1];
      br = eint * b_A;
      for (i11 = 0; i11 < br; i11++) {
        A->data[i11] /= normA;
      }

      b_PadeApproximantOfDegree(A, F);
      j = 0;
      emxInit_real_T(&a, 2);
      emxInit_real_T(&b_F, 2);
      while (j <= (int)s - 1) {
        i11 = a->size[0] * a->size[1];
        a->size[0] = F->size[0];
        a->size[1] = F->size[1];
        emxEnsureCapacity((emxArray__common *)a, i11, (int)sizeof(double));
        br = F->size[0] * F->size[1];
        for (i11 = 0; i11 < br; i11++) {
          a->data[i11] = F->data[i11];
        }

        if ((F->size[1] == 1) || (F->size[0] == 1)) {
          i11 = b_F->size[0] * b_F->size[1];
          b_F->size[0] = F->size[0];
          b_F->size[1] = F->size[1];
          emxEnsureCapacity((emxArray__common *)b_F, i11, (int)sizeof(double));
          br = F->size[0];
          for (i11 = 0; i11 < br; i11++) {
            ar = F->size[1];
            for (i12 = 0; i12 < ar; i12++) {
              b_F->data[i11 + b_F->size[0] * i12] = 0.0;
              b_A = F->size[1];
              for (eint = 0; eint < b_A; eint++) {
                b_F->data[i11 + b_F->size[0] * i12] += F->data[i11 + F->size[0] *
                  eint] * F->data[eint + F->size[0] * i12];
              }
            }
          }

          i11 = F->size[0] * F->size[1];
          F->size[0] = b_F->size[0];
          F->size[1] = b_F->size[1];
          emxEnsureCapacity((emxArray__common *)F, i11, (int)sizeof(double));
          br = b_F->size[1];
          for (i11 = 0; i11 < br; i11++) {
            ar = b_F->size[0];
            for (i12 = 0; i12 < ar; i12++) {
              F->data[i12 + F->size[0] * i11] = b_F->data[i12 + b_F->size[0] *
                i11];
            }
          }
        } else {
          k = F->size[1];
          unnamed_idx_0 = (unsigned int)F->size[0];
          unnamed_idx_1 = (unsigned int)F->size[1];
          i11 = F->size[0] * F->size[1];
          F->size[0] = (int)unnamed_idx_0;
          F->size[1] = (int)unnamed_idx_1;
          emxEnsureCapacity((emxArray__common *)F, i11, (int)sizeof(double));
          m = a->size[0];
          i11 = F->size[0] * F->size[1];
          emxEnsureCapacity((emxArray__common *)F, i11, (int)sizeof(double));
          br = F->size[1];
          for (i11 = 0; i11 < br; i11++) {
            ar = F->size[0];
            for (i12 = 0; i12 < ar; i12++) {
              F->data[i12 + F->size[0] * i11] = 0.0;
            }
          }

          if ((a->size[0] == 0) || (a->size[1] == 0)) {
          } else {
            b_A = a->size[0] * (a->size[1] - 1);
            eint = 0;
            while ((m > 0) && (eint <= b_A)) {
              i11 = eint + m;
              for (ic = eint; ic + 1 <= i11; ic++) {
                F->data[ic] = 0.0;
              }

              eint += m;
            }

            br = 0;
            eint = 0;
            while ((m > 0) && (eint <= b_A)) {
              ar = 0;
              i11 = br + k;
              for (ib = br; ib + 1 <= i11; ib++) {
                if (a->data[ib] != 0.0) {
                  ia = ar;
                  i12 = eint + m;
                  for (ic = eint; ic + 1 <= i12; ic++) {
                    ia++;
                    F->data[ic] += a->data[ib] * a->data[ia - 1];
                  }
                }

                ar += m;
              }

              br += k;
              eint += m;
            }
          }
        }

        j++;
      }

      emxFree_real_T(&b_F);
      emxFree_real_T(&a);
    }
  }
}

/*
 * File trailer for expm.c
 *
 * [EOF]
 */
