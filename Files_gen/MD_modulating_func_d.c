/*
 * File: MD_modulating_func_d.c
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
#include "power.h"
#include "factorial.h"
#include "FHZN_define_model_del_rtwutil.h"

/* Function Definitions */

/*
 * UNTITLED3 Summary of this function goes here
 *    Detailed explanation goes here
 * Arguments    : double k
 *                const emxArray_real_T *t
 *                double h
 *                double N
 *                double M
 *                emxArray_real_T *y
 * Return Type  : void
 */
void MD_modulating_func_d(double k, const emxArray_real_T *t, double h, double N,
  double M, emxArray_real_T *y)
{
  unsigned int uv0[2];
  int b_y;
  int loop_ub;
  int i;
  emxArray_real_T *r1;
  emxArray_real_T *r2;
  emxArray_real_T *b_h;
  double d0;
  double d1;
  double d2;
  double d3;
  double d4;
  double d5;
  double d6;
  double aux;

  /* N=4; */
  /* M=5; */
  /*  bylo N=6, M=7 */
  /* N=MD_constant_values.N; */
  /* M=MD_constant_values.M; */
  for (b_y = 0; b_y < 2; b_y++) {
    uv0[b_y] = (unsigned int)t->size[b_y];
  }

  b_y = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = (int)uv0[1];
  emxEnsureCapacity((emxArray__common *)y, b_y, (int)sizeof(double));
  loop_ub = (int)uv0[1];
  for (b_y = 0; b_y < loop_ub; b_y++) {
    y->data[b_y] = 0.0;
  }

  i = 0;
  emxInit_real_T(&r1, 2);
  emxInit_real_T(&r2, 2);
  emxInit_real_T(&b_h, 2);
  while (i <= (int)(k + 1.0) - 1) {
    d0 = k;
    factorial(&d0);
    d1 = i;
    factorial(&d1);
    d2 = k - (double)i;
    factorial(&d2);
    d3 = N;
    factorial(&d3);
    d4 = (N - k) + (double)i;
    factorial(&d4);
    d5 = M;
    factorial(&d5);
    d6 = M - (double)i;
    factorial(&d6);
    aux = rt_powd_snf(-1.0, i) * d0 / (d1 * d2) * (d3 / d4) * (d5 / d6);
    power(t, (N - k) + (double)i, r2);
    b_y = r2->size[0] * r2->size[1];
    r2->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)r2, b_y, (int)sizeof(double));
    b_y = r2->size[0];
    loop_ub = r2->size[1];
    loop_ub *= b_y;
    for (b_y = 0; b_y < loop_ub; b_y++) {
      r2->data[b_y] *= aux;
    }

    b_y = b_h->size[0] * b_h->size[1];
    b_h->size[0] = 1;
    b_h->size[1] = t->size[1];
    emxEnsureCapacity((emxArray__common *)b_h, b_y, (int)sizeof(double));
    loop_ub = t->size[0] * t->size[1];
    for (b_y = 0; b_y < loop_ub; b_y++) {
      b_h->data[b_y] = h - t->data[b_y];
    }

    power(b_h, M - (double)i, r1);
    b_y = y->size[0] * y->size[1];
    y->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)y, b_y, (int)sizeof(double));
    loop_ub = y->size[0];
    b_y = y->size[1];
    loop_ub *= b_y;
    for (b_y = 0; b_y < loop_ub; b_y++) {
      y->data[b_y] += r2->data[b_y] * r1->data[b_y];
    }

    i++;
  }

  emxFree_real_T(&b_h);
  emxFree_real_T(&r2);
  emxFree_real_T(&r1);

  /* y=sum(g(1:rank-1)); */
  /* y=1; */
  /* y=t.^N.*(h-t).^M; */
  /* y=ones(h, 1); */
  /* y1=zeros(10, 1); */
  /* y=[y1; y(10:h)]; */
  /* y=zeros(h,1); */
  /* y(1)=100000; */
}

/*
 * File trailer for MD_modulating_func_d.c
 *
 * [EOF]
 */
