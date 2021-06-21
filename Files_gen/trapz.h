/*
 * File: trapz.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 18-May-2021 18:57:58
 */

#ifndef __TRAPZ_H__
#define __TRAPZ_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FHZN_define_model_del_types.h"

/* Function Declarations */
extern void b_trapz(const emxArray_real_T *x, const emxArray_real_T *y,
                    emxArray_real_T *z);
extern void trapz(const emxArray_real_T *x, const emxArray_real_T *y,
                  emxArray_real_T *z);

#endif

/*
 * File trailer for trapz.h
 *
 * [EOF]
 */
