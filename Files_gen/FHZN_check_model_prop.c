/*
 * File: FHZN_check_model_prop.c
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
#include "FHZN_check_model_prop.h"

/* Function Definitions */

/*
 * UNTITLED Summary of this function goes here
 *    Detailed explanation goes here
 * Arguments    : const emxArray_real_T *params_vector
 *                double model_inputs_nr
 *                const double model_inputs[3]
 *                double n
 *                const double input_signs[3]
 * Return Type  : boolean_T
 */
boolean_T FHZN_check_model_prop(const emxArray_real_T *params_vector, double
  model_inputs_nr, const double model_inputs[3], double n, const double
  input_signs[3])
{
  boolean_T model_prop;
  double current_input;
  int i;
  boolean_T exitg1;
  int j;
  boolean_T exitg2;
  model_prop = true;

  /* inputs_nr=sum(model_inputs); */
  current_input = 1.0;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i <= (int)model_inputs_nr - 1)) {
    j = 0;
    exitg2 = false;
    while ((!exitg2) && (j <= (int)n - 1)) {
      /* model_nr */
      /* i */
      /* current_input */
      /* params_vector(end-(model_inputs_nr-current_input+1)*n+j) */
      if ((model_inputs[i] == 0.0) || (input_signs[i] == 0.0) ||
          ((params_vector->data[(int)(((double)params_vector->size[0] -
              ((model_inputs_nr - current_input) + 1.0) * n) + (1.0 + (double)j))
            - 1] > 0.0) && (input_signs[i] == 1.0)) || ((params_vector->data
            [(int)(((double)params_vector->size[0] - ((model_inputs_nr -
                current_input) + 1.0) * n) + (1.0 + (double)j)) - 1] < 0.0) &&
           (input_signs[i] == -1.0))) {
        j++;
      } else {
        model_prop = false;
        exitg2 = true;
      }
    }

    if (!model_prop) {
      exitg1 = true;
    } else {
      current_input++;
      i++;
    }
  }

  return model_prop;
}

/*
 * UNTITLED Summary of this function goes here
 *    Detailed explanation goes here
 * Arguments    : const emxArray_real_T *params_vector
 *                double n
 * Return Type  : boolean_T
 */
boolean_T b_FHZN_check_model_prop(const emxArray_real_T *params_vector, double n)
{
  boolean_T model_prop;
  double current_input;
  int i;
  boolean_T exitg1;
  int j;
  boolean_T exitg2;
  model_prop = true;

  /* inputs_nr=sum(model_inputs); */
  current_input = 1.0;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i <= 1)) {
    j = 0;
    exitg2 = false;
    while ((!exitg2) && (j <= (int)n - 1)) {
      /* model_nr */
      /* i */
      /* current_input */
      /* params_vector(end-(model_inputs_nr-current_input+1)*n+j) */
      if (params_vector->data[(int)(((double)params_vector->size[0] - ((2.0 -
              current_input) + 1.0) * n) + (1.0 + (double)j)) - 1] > 0.0) {
        j++;
      } else {
        model_prop = false;
        exitg2 = true;
      }
    }

    if (!model_prop) {
      exitg1 = true;
    } else {
      current_input++;
      i++;
    }
  }

  return model_prop;
}

/*
 * File trailer for FHZN_check_model_prop.c
 *
 * [EOF]
 */
