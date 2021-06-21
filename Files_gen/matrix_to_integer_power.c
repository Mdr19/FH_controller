/*
 * File: matrix_to_integer_power.c
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
#include "matrix_to_integer_power.h"
#include "FHZN_define_model_del_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *a
 *                double b
 *                emxArray_real_T *c
 * Return Type  : void
 */
void matrix_to_large_integer_power(emxArray_real_T *a, double b, emxArray_real_T
  *c)
{
  unsigned int uv5[2];
  int i41;
  double e;
  boolean_T firstmult;
  emxArray_real_T *b_a;
  emxArray_real_T *b_c;
  emxArray_real_T *c_a;
  int exitg1;
  double ed2;
  int c_c[2];
  int br;
  int ar;
  int i42;
  int d_c;
  int cr;
  int k;
  int m;
  int ic;
  int ib;
  int ia;
  for (i41 = 0; i41 < 2; i41++) {
    uv5[i41] = (unsigned int)a->size[i41];
  }

  i41 = c->size[0] * c->size[1];
  c->size[0] = (int)uv5[0];
  c->size[1] = (int)uv5[1];
  emxEnsureCapacity((emxArray__common *)c, i41, (int)sizeof(double));
  if ((!rtIsInf(b)) && (!rtIsNaN(b))) {
    e = fabs(b);
    firstmult = true;
    emxInit_real_T(&b_a, 2);
    emxInit_real_T(&b_c, 2);
    emxInit_real_T(&c_a, 2);
    do {
      exitg1 = 0;
      ed2 = floor(e / 2.0);
      if (2.0 * ed2 != e) {
        if (firstmult) {
          for (i41 = 0; i41 < 2; i41++) {
            c_c[i41] = c->size[i41];
          }

          i41 = c->size[0] * c->size[1];
          c->size[0] = c_c[0];
          c->size[1] = c_c[1];
          emxEnsureCapacity((emxArray__common *)c, i41, (int)sizeof(double));
          br = c_c[1];
          for (i41 = 0; i41 < br; i41++) {
            ar = c_c[0];
            for (i42 = 0; i42 < ar; i42++) {
              c->data[i42 + c->size[0] * i41] = a->data[i42 + c_c[0] * i41];
            }
          }

          firstmult = false;
        } else {
          i41 = b_a->size[0] * b_a->size[1];
          b_a->size[0] = c->size[0];
          b_a->size[1] = c->size[1];
          emxEnsureCapacity((emxArray__common *)b_a, i41, (int)sizeof(double));
          br = c->size[0] * c->size[1];
          for (i41 = 0; i41 < br; i41++) {
            b_a->data[i41] = c->data[i41];
          }

          if ((c->size[1] == 1) || (a->size[0] == 1)) {
            i41 = b_c->size[0] * b_c->size[1];
            b_c->size[0] = c->size[0];
            b_c->size[1] = a->size[1];
            emxEnsureCapacity((emxArray__common *)b_c, i41, (int)sizeof(double));
            br = c->size[0];
            for (i41 = 0; i41 < br; i41++) {
              ar = a->size[1];
              for (i42 = 0; i42 < ar; i42++) {
                b_c->data[i41 + b_c->size[0] * i42] = 0.0;
                d_c = c->size[1];
                for (cr = 0; cr < d_c; cr++) {
                  b_c->data[i41 + b_c->size[0] * i42] += c->data[i41 + c->size[0]
                    * cr] * a->data[cr + a->size[0] * i42];
                }
              }
            }

            i41 = c->size[0] * c->size[1];
            c->size[0] = b_c->size[0];
            c->size[1] = b_c->size[1];
            emxEnsureCapacity((emxArray__common *)c, i41, (int)sizeof(double));
            br = b_c->size[1];
            for (i41 = 0; i41 < br; i41++) {
              ar = b_c->size[0];
              for (i42 = 0; i42 < ar; i42++) {
                c->data[i42 + c->size[0] * i41] = b_c->data[i42 + b_c->size[0] *
                  i41];
              }
            }
          } else {
            k = c->size[1];
            uv5[0] = (unsigned int)c->size[0];
            uv5[1] = (unsigned int)a->size[1];
            i41 = c->size[0] * c->size[1];
            c->size[0] = (int)uv5[0];
            c->size[1] = (int)uv5[1];
            emxEnsureCapacity((emxArray__common *)c, i41, (int)sizeof(double));
            m = b_a->size[0];
            i41 = c->size[0] * c->size[1];
            emxEnsureCapacity((emxArray__common *)c, i41, (int)sizeof(double));
            br = c->size[1];
            for (i41 = 0; i41 < br; i41++) {
              ar = c->size[0];
              for (i42 = 0; i42 < ar; i42++) {
                c->data[i42 + c->size[0] * i41] = 0.0;
              }
            }

            if ((b_a->size[0] == 0) || (a->size[1] == 0)) {
            } else {
              d_c = b_a->size[0] * (a->size[1] - 1);
              cr = 0;
              while ((m > 0) && (cr <= d_c)) {
                i41 = cr + m;
                for (ic = cr; ic + 1 <= i41; ic++) {
                  c->data[ic] = 0.0;
                }

                cr += m;
              }

              br = 0;
              cr = 0;
              while ((m > 0) && (cr <= d_c)) {
                ar = -1;
                i41 = br + k;
                for (ib = br; ib + 1 <= i41; ib++) {
                  if (a->data[ib] != 0.0) {
                    ia = ar;
                    i42 = cr + m;
                    for (ic = cr; ic + 1 <= i42; ic++) {
                      ia++;
                      c->data[ic] += a->data[ib] * b_a->data[ia];
                    }
                  }

                  ar += m;
                }

                br += k;
                cr += m;
              }
            }
          }
        }
      }

      if (ed2 == 0.0) {
        exitg1 = 1;
      } else {
        e = ed2;
        i41 = b_a->size[0] * b_a->size[1];
        b_a->size[0] = a->size[0];
        b_a->size[1] = a->size[1];
        emxEnsureCapacity((emxArray__common *)b_a, i41, (int)sizeof(double));
        br = a->size[0] * a->size[1];
        for (i41 = 0; i41 < br; i41++) {
          b_a->data[i41] = a->data[i41];
        }

        if ((a->size[1] == 1) || (a->size[0] == 1)) {
          i41 = c_a->size[0] * c_a->size[1];
          c_a->size[0] = a->size[0];
          c_a->size[1] = a->size[1];
          emxEnsureCapacity((emxArray__common *)c_a, i41, (int)sizeof(double));
          br = a->size[0];
          for (i41 = 0; i41 < br; i41++) {
            ar = a->size[1];
            for (i42 = 0; i42 < ar; i42++) {
              c_a->data[i41 + c_a->size[0] * i42] = 0.0;
              d_c = a->size[1];
              for (cr = 0; cr < d_c; cr++) {
                c_a->data[i41 + c_a->size[0] * i42] += a->data[i41 + a->size[0] *
                  cr] * a->data[cr + a->size[0] * i42];
              }
            }
          }

          i41 = a->size[0] * a->size[1];
          a->size[0] = c_a->size[0];
          a->size[1] = c_a->size[1];
          emxEnsureCapacity((emxArray__common *)a, i41, (int)sizeof(double));
          br = c_a->size[1];
          for (i41 = 0; i41 < br; i41++) {
            ar = c_a->size[0];
            for (i42 = 0; i42 < ar; i42++) {
              a->data[i42 + a->size[0] * i41] = c_a->data[i42 + c_a->size[0] *
                i41];
            }
          }
        } else {
          k = a->size[1];
          uv5[0] = (unsigned int)a->size[0];
          uv5[1] = (unsigned int)a->size[1];
          i41 = a->size[0] * a->size[1];
          a->size[0] = (int)uv5[0];
          a->size[1] = (int)uv5[1];
          emxEnsureCapacity((emxArray__common *)a, i41, (int)sizeof(double));
          m = b_a->size[0];
          i41 = a->size[0] * a->size[1];
          emxEnsureCapacity((emxArray__common *)a, i41, (int)sizeof(double));
          br = a->size[1];
          for (i41 = 0; i41 < br; i41++) {
            ar = a->size[0];
            for (i42 = 0; i42 < ar; i42++) {
              a->data[i42 + a->size[0] * i41] = 0.0;
            }
          }

          if ((b_a->size[0] == 0) || (b_a->size[1] == 0)) {
          } else {
            d_c = b_a->size[0] * (b_a->size[1] - 1);
            cr = 0;
            while ((m > 0) && (cr <= d_c)) {
              i41 = cr + m;
              for (ic = cr; ic + 1 <= i41; ic++) {
                a->data[ic] = 0.0;
              }

              cr += m;
            }

            br = 0;
            cr = 0;
            while ((m > 0) && (cr <= d_c)) {
              ar = -1;
              i41 = br + k;
              for (ib = br; ib + 1 <= i41; ib++) {
                if (b_a->data[ib] != 0.0) {
                  ia = ar;
                  i42 = cr + m;
                  for (ic = cr; ic + 1 <= i42; ic++) {
                    ia++;
                    a->data[ic] += b_a->data[ib] * b_a->data[ia];
                  }
                }

                ar += m;
              }

              br += k;
              cr += m;
            }
          }
        }
      }
    } while (exitg1 == 0);

    emxFree_real_T(&c_a);
    emxFree_real_T(&b_c);
    emxFree_real_T(&b_a);
  } else {
    i41 = c->size[0] * c->size[1];
    emxEnsureCapacity((emxArray__common *)c, i41, (int)sizeof(double));
    br = c->size[1];
    for (i41 = 0; i41 < br; i41++) {
      ar = c->size[0];
      for (i42 = 0; i42 < ar; i42++) {
        c->data[i42 + c->size[0] * i41] = rtNaN;
      }
    }
  }
}

/*
 * Arguments    : emxArray_real_T *a
 *                double b
 *                emxArray_real_T *c
 * Return Type  : void
 */
void matrix_to_small_integer_power(emxArray_real_T *a, double b, emxArray_real_T
  *c)
{
  double y;
  int n;
  int j;
  int nbitson;
  int nb;
  unsigned int uv4[2];
  int i39;
  int br;
  int ar;
  int i40;
  int k;
  int m;
  int ic;
  int ib;
  int ia;
  emxArray_real_T *cBuffer;
  emxArray_real_T *aBuffer;
  boolean_T first;
  boolean_T aBufferInUse;
  boolean_T cBufferInUse;
  int b_c[2];
  int b_k;
  y = fabs(b);
  n = (int)fabs(b);
  j = (int)y;
  nbitson = 0;
  nb = -1;
  while (j > 0) {
    nb++;
    if ((j & 1) != 0) {
      nbitson++;
    }

    j >>= 1;
  }

  for (i39 = 0; i39 < 2; i39++) {
    uv4[i39] = (unsigned int)a->size[i39];
  }

  i39 = c->size[0] * c->size[1];
  c->size[0] = (int)uv4[0];
  c->size[1] = (int)uv4[1];
  emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
  if ((int)y <= 2) {
    if (b == 2.0) {
      if ((a->size[1] == 1) || (a->size[0] == 1)) {
        i39 = c->size[0] * c->size[1];
        c->size[0] = a->size[0];
        c->size[1] = a->size[1];
        emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
        br = a->size[0];
        for (i39 = 0; i39 < br; i39++) {
          ar = a->size[1];
          for (i40 = 0; i40 < ar; i40++) {
            c->data[i39 + c->size[0] * i40] = 0.0;
            j = a->size[1];
            for (nbitson = 0; nbitson < j; nbitson++) {
              c->data[i39 + c->size[0] * i40] += a->data[i39 + a->size[0] *
                nbitson] * a->data[nbitson + a->size[0] * i40];
            }
          }
        }
      } else {
        k = a->size[1];
        uv4[0] = (unsigned int)a->size[0];
        uv4[1] = (unsigned int)a->size[1];
        i39 = c->size[0] * c->size[1];
        c->size[0] = (int)uv4[0];
        c->size[1] = (int)uv4[1];
        emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
        m = a->size[0];
        i39 = c->size[0] * c->size[1];
        emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
        br = c->size[1];
        for (i39 = 0; i39 < br; i39++) {
          ar = c->size[0];
          for (i40 = 0; i40 < ar; i40++) {
            c->data[i40 + c->size[0] * i39] = 0.0;
          }
        }

        if ((a->size[0] == 0) || (a->size[1] == 0)) {
        } else {
          j = a->size[0] * (a->size[1] - 1);
          nbitson = 0;
          while ((m > 0) && (nbitson <= j)) {
            i39 = nbitson + m;
            for (ic = nbitson; ic + 1 <= i39; ic++) {
              c->data[ic] = 0.0;
            }

            nbitson += m;
          }

          br = 0;
          nbitson = 0;
          while ((m > 0) && (nbitson <= j)) {
            ar = -1;
            i39 = br + k;
            for (ib = br; ib + 1 <= i39; ib++) {
              if (a->data[ib] != 0.0) {
                ia = ar;
                i40 = nbitson + m;
                for (ic = nbitson; ic + 1 <= i40; ic++) {
                  ia++;
                  c->data[ic] += a->data[ib] * a->data[ia];
                }
              }

              ar += m;
            }

            br += k;
            nbitson += m;
          }
        }
      }
    } else if (b == 1.0) {
      i39 = c->size[0] * c->size[1];
      c->size[0] = a->size[0];
      c->size[1] = a->size[1];
      emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
      br = a->size[0] * a->size[1];
      for (i39 = 0; i39 < br; i39++) {
        c->data[i39] = a->data[i39];
      }
    } else {
      i39 = c->size[0] * c->size[1];
      emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
      br = c->size[1];
      for (i39 = 0; i39 < br; i39++) {
        ar = c->size[0];
        for (i40 = 0; i40 < ar; i40++) {
          c->data[i40 + c->size[0] * i39] = 0.0;
        }
      }

      for (j = 0; j + 1 <= a->size[0]; j++) {
        c->data[j + c->size[0] * j] = 1.0;
      }
    }
  } else {
    emxInit_real_T(&cBuffer, 2);
    for (i39 = 0; i39 < 2; i39++) {
      i40 = cBuffer->size[0] * cBuffer->size[1];
      cBuffer->size[i39] = c->size[i39];
      emxEnsureCapacity((emxArray__common *)cBuffer, i40, (int)sizeof(double));
    }

    emxInit_real_T(&aBuffer, 2);
    for (i39 = 0; i39 < 2; i39++) {
      i40 = aBuffer->size[0] * aBuffer->size[1];
      aBuffer->size[i39] = a->size[i39];
      emxEnsureCapacity((emxArray__common *)aBuffer, i40, (int)sizeof(double));
    }

    first = true;
    aBufferInUse = false;
    cBufferInUse = !((nbitson & 1) != 0);
    for (k = 1; k <= nb; k++) {
      if ((n & 1) != 0) {
        if (first) {
          first = false;
          if (cBufferInUse) {
            if (aBufferInUse) {
              for (i39 = 0; i39 < 2; i39++) {
                b_c[i39] = cBuffer->size[i39];
              }

              i39 = cBuffer->size[0] * cBuffer->size[1];
              cBuffer->size[0] = b_c[0];
              cBuffer->size[1] = b_c[1];
              emxEnsureCapacity((emxArray__common *)cBuffer, i39, (int)sizeof
                                (double));
              br = b_c[1];
              for (i39 = 0; i39 < br; i39++) {
                ar = b_c[0];
                for (i40 = 0; i40 < ar; i40++) {
                  cBuffer->data[i40 + cBuffer->size[0] * i39] = aBuffer->
                    data[i40 + b_c[0] * i39];
                }
              }
            } else {
              for (i39 = 0; i39 < 2; i39++) {
                b_c[i39] = cBuffer->size[i39];
              }

              i39 = cBuffer->size[0] * cBuffer->size[1];
              cBuffer->size[0] = b_c[0];
              cBuffer->size[1] = b_c[1];
              emxEnsureCapacity((emxArray__common *)cBuffer, i39, (int)sizeof
                                (double));
              br = b_c[1];
              for (i39 = 0; i39 < br; i39++) {
                ar = b_c[0];
                for (i40 = 0; i40 < ar; i40++) {
                  cBuffer->data[i40 + cBuffer->size[0] * i39] = a->data[i40 +
                    b_c[0] * i39];
                }
              }
            }
          } else if (aBufferInUse) {
            for (i39 = 0; i39 < 2; i39++) {
              b_c[i39] = c->size[i39];
            }

            i39 = c->size[0] * c->size[1];
            c->size[0] = b_c[0];
            c->size[1] = b_c[1];
            emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
            br = b_c[1];
            for (i39 = 0; i39 < br; i39++) {
              ar = b_c[0];
              for (i40 = 0; i40 < ar; i40++) {
                c->data[i40 + c->size[0] * i39] = aBuffer->data[i40 + b_c[0] *
                  i39];
              }
            }
          } else {
            for (i39 = 0; i39 < 2; i39++) {
              b_c[i39] = c->size[i39];
            }

            i39 = c->size[0] * c->size[1];
            c->size[0] = b_c[0];
            c->size[1] = b_c[1];
            emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
            br = b_c[1];
            for (i39 = 0; i39 < br; i39++) {
              ar = b_c[0];
              for (i40 = 0; i40 < ar; i40++) {
                c->data[i40 + c->size[0] * i39] = a->data[i40 + b_c[0] * i39];
              }
            }
          }
        } else {
          if (aBufferInUse) {
            if (cBufferInUse) {
              if ((cBuffer->size[1] == 1) || (aBuffer->size[0] == 1)) {
                i39 = c->size[0] * c->size[1];
                c->size[0] = cBuffer->size[0];
                c->size[1] = aBuffer->size[1];
                emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
                br = cBuffer->size[0];
                for (i39 = 0; i39 < br; i39++) {
                  ar = aBuffer->size[1];
                  for (i40 = 0; i40 < ar; i40++) {
                    c->data[i39 + c->size[0] * i40] = 0.0;
                    j = cBuffer->size[1];
                    for (nbitson = 0; nbitson < j; nbitson++) {
                      c->data[i39 + c->size[0] * i40] += cBuffer->data[i39 +
                        cBuffer->size[0] * nbitson] * aBuffer->data[nbitson +
                        aBuffer->size[0] * i40];
                    }
                  }
                }
              } else {
                b_k = cBuffer->size[1];
                uv4[0] = (unsigned int)cBuffer->size[0];
                uv4[1] = (unsigned int)aBuffer->size[1];
                i39 = c->size[0] * c->size[1];
                c->size[0] = (int)uv4[0];
                c->size[1] = (int)uv4[1];
                emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
                m = cBuffer->size[0];
                i39 = c->size[0] * c->size[1];
                emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
                br = c->size[1];
                for (i39 = 0; i39 < br; i39++) {
                  ar = c->size[0];
                  for (i40 = 0; i40 < ar; i40++) {
                    c->data[i40 + c->size[0] * i39] = 0.0;
                  }
                }

                if ((cBuffer->size[0] == 0) || (aBuffer->size[1] == 0)) {
                } else {
                  j = cBuffer->size[0] * (aBuffer->size[1] - 1);
                  nbitson = 0;
                  while ((m > 0) && (nbitson <= j)) {
                    i39 = nbitson + m;
                    for (ic = nbitson; ic + 1 <= i39; ic++) {
                      c->data[ic] = 0.0;
                    }

                    nbitson += m;
                  }

                  br = 0;
                  nbitson = 0;
                  while ((m > 0) && (nbitson <= j)) {
                    ar = -1;
                    i39 = br + b_k;
                    for (ib = br; ib + 1 <= i39; ib++) {
                      if (aBuffer->data[ib] != 0.0) {
                        ia = ar;
                        i40 = nbitson + m;
                        for (ic = nbitson; ic + 1 <= i40; ic++) {
                          ia++;
                          c->data[ic] += aBuffer->data[ib] * cBuffer->data[ia];
                        }
                      }

                      ar += m;
                    }

                    br += b_k;
                    nbitson += m;
                  }
                }
              }
            } else if ((c->size[1] == 1) || (aBuffer->size[0] == 1)) {
              i39 = cBuffer->size[0] * cBuffer->size[1];
              cBuffer->size[0] = c->size[0];
              cBuffer->size[1] = aBuffer->size[1];
              emxEnsureCapacity((emxArray__common *)cBuffer, i39, (int)sizeof
                                (double));
              br = c->size[0];
              for (i39 = 0; i39 < br; i39++) {
                ar = aBuffer->size[1];
                for (i40 = 0; i40 < ar; i40++) {
                  cBuffer->data[i39 + cBuffer->size[0] * i40] = 0.0;
                  j = c->size[1];
                  for (nbitson = 0; nbitson < j; nbitson++) {
                    cBuffer->data[i39 + cBuffer->size[0] * i40] += c->data[i39 +
                      c->size[0] * nbitson] * aBuffer->data[nbitson +
                      aBuffer->size[0] * i40];
                  }
                }
              }
            } else {
              b_k = c->size[1];
              uv4[0] = (unsigned int)c->size[0];
              uv4[1] = (unsigned int)aBuffer->size[1];
              i39 = cBuffer->size[0] * cBuffer->size[1];
              cBuffer->size[0] = (int)uv4[0];
              cBuffer->size[1] = (int)uv4[1];
              emxEnsureCapacity((emxArray__common *)cBuffer, i39, (int)sizeof
                                (double));
              m = c->size[0];
              i39 = cBuffer->size[0] * cBuffer->size[1];
              emxEnsureCapacity((emxArray__common *)cBuffer, i39, (int)sizeof
                                (double));
              br = cBuffer->size[1];
              for (i39 = 0; i39 < br; i39++) {
                ar = cBuffer->size[0];
                for (i40 = 0; i40 < ar; i40++) {
                  cBuffer->data[i40 + cBuffer->size[0] * i39] = 0.0;
                }
              }

              if ((c->size[0] == 0) || (aBuffer->size[1] == 0)) {
              } else {
                j = c->size[0] * (aBuffer->size[1] - 1);
                nbitson = 0;
                while ((m > 0) && (nbitson <= j)) {
                  i39 = nbitson + m;
                  for (ic = nbitson; ic + 1 <= i39; ic++) {
                    cBuffer->data[ic] = 0.0;
                  }

                  nbitson += m;
                }

                br = 0;
                nbitson = 0;
                while ((m > 0) && (nbitson <= j)) {
                  ar = -1;
                  i39 = br + b_k;
                  for (ib = br; ib + 1 <= i39; ib++) {
                    if (aBuffer->data[ib] != 0.0) {
                      ia = ar;
                      i40 = nbitson + m;
                      for (ic = nbitson; ic + 1 <= i40; ic++) {
                        ia++;
                        cBuffer->data[ic] += aBuffer->data[ib] * c->data[ia];
                      }
                    }

                    ar += m;
                  }

                  br += b_k;
                  nbitson += m;
                }
              }
            }
          } else if (cBufferInUse) {
            if ((cBuffer->size[1] == 1) || (a->size[0] == 1)) {
              i39 = c->size[0] * c->size[1];
              c->size[0] = cBuffer->size[0];
              c->size[1] = a->size[1];
              emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
              br = cBuffer->size[0];
              for (i39 = 0; i39 < br; i39++) {
                ar = a->size[1];
                for (i40 = 0; i40 < ar; i40++) {
                  c->data[i39 + c->size[0] * i40] = 0.0;
                  j = cBuffer->size[1];
                  for (nbitson = 0; nbitson < j; nbitson++) {
                    c->data[i39 + c->size[0] * i40] += cBuffer->data[i39 +
                      cBuffer->size[0] * nbitson] * a->data[nbitson + a->size[0]
                      * i40];
                  }
                }
              }
            } else {
              b_k = cBuffer->size[1];
              uv4[0] = (unsigned int)cBuffer->size[0];
              uv4[1] = (unsigned int)a->size[1];
              i39 = c->size[0] * c->size[1];
              c->size[0] = (int)uv4[0];
              c->size[1] = (int)uv4[1];
              emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
              m = cBuffer->size[0];
              i39 = c->size[0] * c->size[1];
              emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
              br = c->size[1];
              for (i39 = 0; i39 < br; i39++) {
                ar = c->size[0];
                for (i40 = 0; i40 < ar; i40++) {
                  c->data[i40 + c->size[0] * i39] = 0.0;
                }
              }

              if ((cBuffer->size[0] == 0) || (a->size[1] == 0)) {
              } else {
                j = cBuffer->size[0] * (a->size[1] - 1);
                nbitson = 0;
                while ((m > 0) && (nbitson <= j)) {
                  i39 = nbitson + m;
                  for (ic = nbitson; ic + 1 <= i39; ic++) {
                    c->data[ic] = 0.0;
                  }

                  nbitson += m;
                }

                br = 0;
                nbitson = 0;
                while ((m > 0) && (nbitson <= j)) {
                  ar = -1;
                  i39 = br + b_k;
                  for (ib = br; ib + 1 <= i39; ib++) {
                    if (a->data[ib] != 0.0) {
                      ia = ar;
                      i40 = nbitson + m;
                      for (ic = nbitson; ic + 1 <= i40; ic++) {
                        ia++;
                        c->data[ic] += a->data[ib] * cBuffer->data[ia];
                      }
                    }

                    ar += m;
                  }

                  br += b_k;
                  nbitson += m;
                }
              }
            }
          } else if ((c->size[1] == 1) || (a->size[0] == 1)) {
            i39 = cBuffer->size[0] * cBuffer->size[1];
            cBuffer->size[0] = c->size[0];
            cBuffer->size[1] = a->size[1];
            emxEnsureCapacity((emxArray__common *)cBuffer, i39, (int)sizeof
                              (double));
            br = c->size[0];
            for (i39 = 0; i39 < br; i39++) {
              ar = a->size[1];
              for (i40 = 0; i40 < ar; i40++) {
                cBuffer->data[i39 + cBuffer->size[0] * i40] = 0.0;
                j = c->size[1];
                for (nbitson = 0; nbitson < j; nbitson++) {
                  cBuffer->data[i39 + cBuffer->size[0] * i40] += c->data[i39 +
                    c->size[0] * nbitson] * a->data[nbitson + a->size[0] * i40];
                }
              }
            }
          } else {
            b_k = c->size[1];
            uv4[0] = (unsigned int)c->size[0];
            uv4[1] = (unsigned int)a->size[1];
            i39 = cBuffer->size[0] * cBuffer->size[1];
            cBuffer->size[0] = (int)uv4[0];
            cBuffer->size[1] = (int)uv4[1];
            emxEnsureCapacity((emxArray__common *)cBuffer, i39, (int)sizeof
                              (double));
            m = c->size[0];
            i39 = cBuffer->size[0] * cBuffer->size[1];
            emxEnsureCapacity((emxArray__common *)cBuffer, i39, (int)sizeof
                              (double));
            br = cBuffer->size[1];
            for (i39 = 0; i39 < br; i39++) {
              ar = cBuffer->size[0];
              for (i40 = 0; i40 < ar; i40++) {
                cBuffer->data[i40 + cBuffer->size[0] * i39] = 0.0;
              }
            }

            if ((c->size[0] == 0) || (a->size[1] == 0)) {
            } else {
              j = c->size[0] * (a->size[1] - 1);
              nbitson = 0;
              while ((m > 0) && (nbitson <= j)) {
                i39 = nbitson + m;
                for (ic = nbitson; ic + 1 <= i39; ic++) {
                  cBuffer->data[ic] = 0.0;
                }

                nbitson += m;
              }

              br = 0;
              nbitson = 0;
              while ((m > 0) && (nbitson <= j)) {
                ar = -1;
                i39 = br + b_k;
                for (ib = br; ib + 1 <= i39; ib++) {
                  if (a->data[ib] != 0.0) {
                    ia = ar;
                    i40 = nbitson + m;
                    for (ic = nbitson; ic + 1 <= i40; ic++) {
                      ia++;
                      cBuffer->data[ic] += a->data[ib] * c->data[ia];
                    }
                  }

                  ar += m;
                }

                br += b_k;
                nbitson += m;
              }
            }
          }

          cBufferInUse = !cBufferInUse;
        }
      }

      n >>= 1;
      if (aBufferInUse) {
        if ((aBuffer->size[1] == 1) || (aBuffer->size[0] == 1)) {
          i39 = a->size[0] * a->size[1];
          a->size[0] = aBuffer->size[0];
          a->size[1] = aBuffer->size[1];
          emxEnsureCapacity((emxArray__common *)a, i39, (int)sizeof(double));
          br = aBuffer->size[0];
          for (i39 = 0; i39 < br; i39++) {
            ar = aBuffer->size[1];
            for (i40 = 0; i40 < ar; i40++) {
              a->data[i39 + a->size[0] * i40] = 0.0;
              j = aBuffer->size[1];
              for (nbitson = 0; nbitson < j; nbitson++) {
                a->data[i39 + a->size[0] * i40] += aBuffer->data[i39 +
                  aBuffer->size[0] * nbitson] * aBuffer->data[nbitson +
                  aBuffer->size[0] * i40];
              }
            }
          }
        } else {
          b_k = aBuffer->size[1];
          uv4[0] = (unsigned int)aBuffer->size[0];
          uv4[1] = (unsigned int)aBuffer->size[1];
          i39 = a->size[0] * a->size[1];
          a->size[0] = (int)uv4[0];
          a->size[1] = (int)uv4[1];
          emxEnsureCapacity((emxArray__common *)a, i39, (int)sizeof(double));
          m = aBuffer->size[0];
          i39 = a->size[0] * a->size[1];
          emxEnsureCapacity((emxArray__common *)a, i39, (int)sizeof(double));
          br = a->size[1];
          for (i39 = 0; i39 < br; i39++) {
            ar = a->size[0];
            for (i40 = 0; i40 < ar; i40++) {
              a->data[i40 + a->size[0] * i39] = 0.0;
            }
          }

          if ((aBuffer->size[0] == 0) || (aBuffer->size[1] == 0)) {
          } else {
            j = aBuffer->size[0] * (aBuffer->size[1] - 1);
            nbitson = 0;
            while ((m > 0) && (nbitson <= j)) {
              i39 = nbitson + m;
              for (ic = nbitson; ic + 1 <= i39; ic++) {
                a->data[ic] = 0.0;
              }

              nbitson += m;
            }

            br = 0;
            nbitson = 0;
            while ((m > 0) && (nbitson <= j)) {
              ar = -1;
              i39 = br + b_k;
              for (ib = br; ib + 1 <= i39; ib++) {
                if (aBuffer->data[ib] != 0.0) {
                  ia = ar;
                  i40 = nbitson + m;
                  for (ic = nbitson; ic + 1 <= i40; ic++) {
                    ia++;
                    a->data[ic] += aBuffer->data[ib] * aBuffer->data[ia];
                  }
                }

                ar += m;
              }

              br += b_k;
              nbitson += m;
            }
          }
        }
      } else if ((a->size[1] == 1) || (a->size[0] == 1)) {
        i39 = aBuffer->size[0] * aBuffer->size[1];
        aBuffer->size[0] = a->size[0];
        aBuffer->size[1] = a->size[1];
        emxEnsureCapacity((emxArray__common *)aBuffer, i39, (int)sizeof(double));
        br = a->size[0];
        for (i39 = 0; i39 < br; i39++) {
          ar = a->size[1];
          for (i40 = 0; i40 < ar; i40++) {
            aBuffer->data[i39 + aBuffer->size[0] * i40] = 0.0;
            j = a->size[1];
            for (nbitson = 0; nbitson < j; nbitson++) {
              aBuffer->data[i39 + aBuffer->size[0] * i40] += a->data[i39 +
                a->size[0] * nbitson] * a->data[nbitson + a->size[0] * i40];
            }
          }
        }
      } else {
        b_k = a->size[1];
        uv4[0] = (unsigned int)a->size[0];
        uv4[1] = (unsigned int)a->size[1];
        i39 = aBuffer->size[0] * aBuffer->size[1];
        aBuffer->size[0] = (int)uv4[0];
        aBuffer->size[1] = (int)uv4[1];
        emxEnsureCapacity((emxArray__common *)aBuffer, i39, (int)sizeof(double));
        m = a->size[0];
        i39 = aBuffer->size[0] * aBuffer->size[1];
        emxEnsureCapacity((emxArray__common *)aBuffer, i39, (int)sizeof(double));
        br = aBuffer->size[1];
        for (i39 = 0; i39 < br; i39++) {
          ar = aBuffer->size[0];
          for (i40 = 0; i40 < ar; i40++) {
            aBuffer->data[i40 + aBuffer->size[0] * i39] = 0.0;
          }
        }

        if ((a->size[0] == 0) || (a->size[1] == 0)) {
        } else {
          j = a->size[0] * (a->size[1] - 1);
          nbitson = 0;
          while ((m > 0) && (nbitson <= j)) {
            i39 = nbitson + m;
            for (ic = nbitson; ic + 1 <= i39; ic++) {
              aBuffer->data[ic] = 0.0;
            }

            nbitson += m;
          }

          br = 0;
          nbitson = 0;
          while ((m > 0) && (nbitson <= j)) {
            ar = -1;
            i39 = br + b_k;
            for (ib = br; ib + 1 <= i39; ib++) {
              if (a->data[ib] != 0.0) {
                ia = ar;
                i40 = nbitson + m;
                for (ic = nbitson; ic + 1 <= i40; ic++) {
                  ia++;
                  aBuffer->data[ic] += a->data[ib] * a->data[ia];
                }
              }

              ar += m;
            }

            br += b_k;
            nbitson += m;
          }
        }
      }

      aBufferInUse = !aBufferInUse;
    }

    if (first) {
      if (aBufferInUse) {
        for (i39 = 0; i39 < 2; i39++) {
          b_c[i39] = c->size[i39];
        }

        i39 = c->size[0] * c->size[1];
        c->size[0] = b_c[0];
        c->size[1] = b_c[1];
        emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
        br = b_c[1];
        for (i39 = 0; i39 < br; i39++) {
          ar = b_c[0];
          for (i40 = 0; i40 < ar; i40++) {
            c->data[i40 + c->size[0] * i39] = aBuffer->data[i40 + b_c[0] * i39];
          }
        }
      } else {
        for (i39 = 0; i39 < 2; i39++) {
          b_c[i39] = c->size[i39];
        }

        i39 = c->size[0] * c->size[1];
        c->size[0] = b_c[0];
        c->size[1] = b_c[1];
        emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
        br = b_c[1];
        for (i39 = 0; i39 < br; i39++) {
          ar = b_c[0];
          for (i40 = 0; i40 < ar; i40++) {
            c->data[i40 + c->size[0] * i39] = a->data[i40 + b_c[0] * i39];
          }
        }
      }
    } else if (aBufferInUse) {
      if ((cBuffer->size[1] == 1) || (aBuffer->size[0] == 1)) {
        i39 = c->size[0] * c->size[1];
        c->size[0] = cBuffer->size[0];
        c->size[1] = aBuffer->size[1];
        emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
        br = cBuffer->size[0];
        for (i39 = 0; i39 < br; i39++) {
          ar = aBuffer->size[1];
          for (i40 = 0; i40 < ar; i40++) {
            c->data[i39 + c->size[0] * i40] = 0.0;
            j = cBuffer->size[1];
            for (nbitson = 0; nbitson < j; nbitson++) {
              c->data[i39 + c->size[0] * i40] += cBuffer->data[i39 +
                cBuffer->size[0] * nbitson] * aBuffer->data[nbitson +
                aBuffer->size[0] * i40];
            }
          }
        }
      } else {
        k = cBuffer->size[1];
        uv4[0] = (unsigned int)cBuffer->size[0];
        uv4[1] = (unsigned int)aBuffer->size[1];
        i39 = c->size[0] * c->size[1];
        c->size[0] = (int)uv4[0];
        c->size[1] = (int)uv4[1];
        emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
        m = cBuffer->size[0];
        i39 = c->size[0] * c->size[1];
        emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
        br = c->size[1];
        for (i39 = 0; i39 < br; i39++) {
          ar = c->size[0];
          for (i40 = 0; i40 < ar; i40++) {
            c->data[i40 + c->size[0] * i39] = 0.0;
          }
        }

        if ((cBuffer->size[0] == 0) || (aBuffer->size[1] == 0)) {
        } else {
          j = cBuffer->size[0] * (aBuffer->size[1] - 1);
          nbitson = 0;
          while ((m > 0) && (nbitson <= j)) {
            i39 = nbitson + m;
            for (ic = nbitson; ic + 1 <= i39; ic++) {
              c->data[ic] = 0.0;
            }

            nbitson += m;
          }

          br = 0;
          nbitson = 0;
          while ((m > 0) && (nbitson <= j)) {
            ar = -1;
            i39 = br + k;
            for (ib = br; ib + 1 <= i39; ib++) {
              if (aBuffer->data[ib] != 0.0) {
                ia = ar;
                i40 = nbitson + m;
                for (ic = nbitson; ic + 1 <= i40; ic++) {
                  ia++;
                  c->data[ic] += aBuffer->data[ib] * cBuffer->data[ia];
                }
              }

              ar += m;
            }

            br += k;
            nbitson += m;
          }
        }
      }
    } else if ((cBuffer->size[1] == 1) || (a->size[0] == 1)) {
      i39 = c->size[0] * c->size[1];
      c->size[0] = cBuffer->size[0];
      c->size[1] = a->size[1];
      emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
      br = cBuffer->size[0];
      for (i39 = 0; i39 < br; i39++) {
        ar = a->size[1];
        for (i40 = 0; i40 < ar; i40++) {
          c->data[i39 + c->size[0] * i40] = 0.0;
          j = cBuffer->size[1];
          for (nbitson = 0; nbitson < j; nbitson++) {
            c->data[i39 + c->size[0] * i40] += cBuffer->data[i39 + cBuffer->
              size[0] * nbitson] * a->data[nbitson + a->size[0] * i40];
          }
        }
      }
    } else {
      k = cBuffer->size[1];
      uv4[0] = (unsigned int)cBuffer->size[0];
      uv4[1] = (unsigned int)a->size[1];
      i39 = c->size[0] * c->size[1];
      c->size[0] = (int)uv4[0];
      c->size[1] = (int)uv4[1];
      emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
      m = cBuffer->size[0];
      i39 = c->size[0] * c->size[1];
      emxEnsureCapacity((emxArray__common *)c, i39, (int)sizeof(double));
      br = c->size[1];
      for (i39 = 0; i39 < br; i39++) {
        ar = c->size[0];
        for (i40 = 0; i40 < ar; i40++) {
          c->data[i40 + c->size[0] * i39] = 0.0;
        }
      }

      if ((cBuffer->size[0] == 0) || (a->size[1] == 0)) {
      } else {
        j = cBuffer->size[0] * (a->size[1] - 1);
        nbitson = 0;
        while ((m > 0) && (nbitson <= j)) {
          i39 = nbitson + m;
          for (ic = nbitson; ic + 1 <= i39; ic++) {
            c->data[ic] = 0.0;
          }

          nbitson += m;
        }

        br = 0;
        nbitson = 0;
        while ((m > 0) && (nbitson <= j)) {
          ar = -1;
          i39 = br + k;
          for (ib = br; ib + 1 <= i39; ib++) {
            if (a->data[ib] != 0.0) {
              ia = ar;
              i40 = nbitson + m;
              for (ic = nbitson; ic + 1 <= i40; ic++) {
                ia++;
                c->data[ic] += a->data[ib] * cBuffer->data[ia];
              }
            }

            ar += m;
          }

          br += k;
          nbitson += m;
        }
      }
    }

    emxFree_real_T(&aBuffer);
    emxFree_real_T(&cBuffer);
  }
}

/*
 * File trailer for matrix_to_integer_power.c
 *
 * [EOF]
 */
