#include "FHZN_model.h"

FHZN_model* FH_ZONE_MODEL_create(void)
{
	FHZN_model* z_model = malloc(sizeof(FHZN_model));

	z_model->model_inputs[0] = 1;
	z_model->model_inputs[1] = 1;
	z_model->model_inputs[2] = 0;

	z_model->intervals_nr = 0;
	//z_model->current_interval_nr = 0;
	z_model->head = 0;
	z_model->tail = 0;
	z_model->current_interval_nr = 0;
	z_model->op_time = 0.0;
	z_model->op_interval_nr = 0;

	z_model->model_identified = false;
	z_model->current_model_size = 0;
	z_model->current_model_nr = 0;
	z_model->model_params = NULL;
	z_model->X0 = NULL;

	z_model->Omega = NULL;
	z_model->Psi = NULL;
	z_model->Gamma = NULL;
	z_model->A = NULL;
	z_model->B = NULL;
	z_model->Bd = NULL;
	z_model->C = NULL;
	z_model->Ap = NULL;
	z_model->Lzerot = NULL;
	z_model->M = NULL;

	
	for (int i = 0; i < FHZN_max_inputs + 2; i++)
	{
		z_model->op_offset[i] = 0;
	}

	for (int i = 0; i < max_buffer_size; i++)
	{
		for (int j = 0; j < max_model_inputs; j++)
		{
			z_model->signals_intervals[i].model_inputs[j] = false;
		}

		z_model->signals_intervals[i].op_interval_possible = false;
		z_model->signals_intervals[i].model_diff = 0.0;
		z_model->signals_intervals[i].sp_diff = 0.0;
	}

	return z_model;
}

int FH_ZONE_MODEL_add_interval(FHZN_model* z_model, cyclic_buffer* buff)
{
	if (z_model == NULL || buff == NULL)
	{
		return -1;
	}
	else
	{
		z_model->head = buff->head;
		z_model->tail = buff->tail;
		z_model->intervals_nr = buff->size;

		if (z_model->tail>0)
		{
			z_model->current_interval_nr = buff->tail - 1;
		}
		else 
		{
			z_model->current_interval_nr = max_buffer_size - 1;
		}

		return 0;
	}
}

void FH_ZONE_MODEL_print_current_model(FHZN_model* z_model)
{
	unsigned int inputs_nr = 0;

	for (int i = 0; i < FHZN_max_inputs; i++)
	{
		if (z_model->model_inputs[i]) {
			inputs_nr += 1;
		}
	}

	printf("+++++++++++++++++++++++++++++++++++++\n");
	if (z_model->model_identified) {
		printf("Current model nr: %d \n", z_model->current_model_nr);
		printf("------------------------------------\n");
		printf("Current op time: %fl \n", z_model->op_time);
		printf("------------------------------------\n");
		printf("Current model params: \n");
		for (unsigned int i = 0; i < z_model->current_model_size + inputs_nr; i++)
		{
			printf("%fl \n", z_model->model_params[i]);
		}
		printf("------------------------------------\n");
		printf("Current X0: \n");
		for (unsigned int i = 0; i < z_model->current_model_size - 1; i++)
		{
			printf("%fl \n", z_model->X0[i]);
		}
		printf("------------------------------------\n");
		printf("Current offset: \n");
		for (unsigned int i = 0; i < FHZN_max_inputs+2; i++)
		{
			printf("%fl \n", z_model->op_offset[i]);
		}
	}
	else {
		printf("Model empty \n");
	}
	printf("+++++++++++++++++++++++++++++++++++++\n");

}

void FH_ZONE_MODEL_print_intervals(FHZN_model* z_model) 
{
	for (unsigned int i = 0; i < z_model->intervals_nr; i++)
	{
		printf("Interval nr %d \n", i);
		display_signal_interval(z_model->signals_intervals[(z_model->head + i) % z_model->intervals_nr]);
	}
}

double FH_ZONE_get_last_model_diff(FHZN_model* z_model, int intervals_nr)
{
	int i;
	double model_diff = 0;

	if (z_model->intervals_nr < intervals_nr) {
		for (i = 0; i < z_model->intervals_nr; i++)
		{
			model_diff += z_model->signals_intervals[(z_model->head + i) % z_model->intervals_nr].model_diff;
		}
	}
	else {
		for (i = z_model->intervals_nr- intervals_nr; i < z_model->intervals_nr; i++)
		{
			model_diff += z_model->signals_intervals[(z_model->head + i) % z_model->intervals_nr].model_diff;
		}
	}

	//printf("Model diff: %fl \n", model_diff);

	return model_diff;
}

double FH_ZONE_get_last_SP_diff(FHZN_model* z_model, int intervals_nr)
{
	int i;
	double sp_diff = 0;

	if (z_model->intervals_nr < intervals_nr) {
		for (i = 0; i < z_model->intervals_nr; i++)
		{
			sp_diff += z_model->signals_intervals[(z_model->head + i) % z_model->intervals_nr].sp_diff;
		}
	}
	else {
		for (i = z_model->intervals_nr - intervals_nr; i < z_model->intervals_nr; i++)
		{
			sp_diff += z_model->signals_intervals[(z_model->head + i) % z_model->intervals_nr].sp_diff;
		}
	}

	//printf("SP diff: %fl \n", sp_diff);

	return sp_diff;
}

void FH_ZONE_prepare_data_to_send(FHZN_model* z_model, double* data_to_send)
{
	int i;
	int start_cnt;
	//double data_to_send[send_buffer_size / sizeof(double)];
	unsigned int inputs_nr = 0;

	for (int i = 1; i < FHZN_max_inputs; i++)
	{
		if (z_model->model_inputs[i]) {
			inputs_nr += 1;
		}
	}

	if (z_model->current_model_nr == 0) {
		for (i = 0; i < send_buffer_size / sizeof(double); i++)
		{
			data_to_send[i] = 0.0;
		}
	}
	else {
		//model nr
		data_to_send[0] = z_model->current_model_nr;

		//operating point
		data_to_send[1] = z_model->op_time;
		
		//model delay
		data_to_send[2] = z_model->signals_intervals[z_model->current_interval_nr].model_del;

		//system inputs
		data_to_send[3] = (double)z_model->model_inputs[0];
		data_to_send[4] = (double)z_model->model_inputs[1];
		data_to_send[5] = (double)z_model->model_inputs[2];

		//system params
		data_to_send[6] = 1.0;
		data_to_send[7] = z_model->current_model_size;
		data_to_send[8] = Laguerre_functions_nr;

		start_cnt = 9;

		//offset value
		for (i = 0; i < FHZN_max_inputs + 2; i++){
			data_to_send[i+start_cnt] = z_model->op_offset[i];
		}

		//data_to_send[13] = 0.0;

		start_cnt = 14;

		// Omega
		for (i = 0; i < Laguerre_functions_nr* inputs_nr * Laguerre_functions_nr* inputs_nr; i++) {
			data_to_send[i + start_cnt] = z_model->Omega[i];
			//printf("Omega %d val: %fl \n", i, z_model->Omega[i]);
		}
		start_cnt += Laguerre_functions_nr* inputs_nr * Laguerre_functions_nr* inputs_nr;

		//Psi
		for (i = 0; i < Laguerre_functions_nr* inputs_nr * z_model->current_model_size; i++) {
			data_to_send[i + start_cnt] = z_model->Psi[i];
			//printf("Psi %d val: %fl \n", i, z_model->Psi[i]);
		}
		start_cnt += Laguerre_functions_nr* inputs_nr * z_model->current_model_size;

		//Gamma
		for (i = 0; i < Laguerre_functions_nr* inputs_nr * Laguerre_functions_nr; i++) {
			data_to_send[i + start_cnt] = z_model->Gamma[i];
			//printf("Gamma %d val: %fl \n", i, z_model->Gamma[i]);
		}
		start_cnt += Laguerre_functions_nr* inputs_nr * Laguerre_functions_nr;

		//A
		for (i = 0; i < z_model->current_model_size * z_model->current_model_size; i++) {
			data_to_send[i + start_cnt] = z_model->A[i];
		}
		start_cnt += z_model->current_model_size * z_model->current_model_size;

		//B
		for (i = 0; i < z_model->current_model_size* inputs_nr; i++) {
			data_to_send[i + start_cnt] = z_model->B[i];
		}
		start_cnt += z_model->current_model_size* inputs_nr;

		//Bd
		for (i = 0; i < z_model->current_model_size; i++) {
			data_to_send[i + start_cnt] = z_model->Bd[i];
		}
		start_cnt += z_model->current_model_size;

		//C
		for (i = 0; i < z_model->current_model_size; i++) {
			data_to_send[i + start_cnt] = z_model->C[i];
		}
		start_cnt += z_model->current_model_size;

		//Ap
		for (i = 0; i < Laguerre_functions_nr * Laguerre_functions_nr; i++) {
			data_to_send[i + start_cnt] = z_model->Ap[i];
		}
		start_cnt += Laguerre_functions_nr * Laguerre_functions_nr;

		//Lzerot
		for (i = 0; i < inputs_nr*Laguerre_functions_nr* inputs_nr; i++) {
			data_to_send[i + start_cnt] = z_model->Lzerot[i];
		}
		start_cnt += inputs_nr*Laguerre_functions_nr* inputs_nr;

		//M
		for (i = 0; i < 4* inputs_nr * Laguerre_functions_nr* inputs_nr; i++) {
			data_to_send[i + start_cnt] = z_model->M[i];
		}
		start_cnt += 4 * inputs_nr* Laguerre_functions_nr* inputs_nr;

		//zeros
		for (i = start_cnt; i < (send_buffer_size / sizeof(double)); i++) {
			data_to_send[i] = 0.0;
		}

	}

	//return &data_to_send;
}


void FH_ZONE_MODEL_find_operating_point(FHZN_model* z_model, cyclic_buffer* buff)
{
	FHZN_define_model_del_initialize();

	emxArray_real_T* current_out;
	double op_time;
	//boolean_T op_interval_possible;
	int idx0;
	//int current_interval;


	static int iv0[1] = { struct_capacity };

    //current_out = argInit_Unboundedx1_real_T();
	current_out= emxCreateND_real_T(1, iv0);
		
	//printf("Tail pos %d current pos %d \n", buff->tail, z_model->current_interval_nr);

	/* Loop over the array to initialize each element. */
	for (idx0 = 0; idx0 < current_out->size[0U]; idx0++) {
		current_out->data[idx0] = buff->data[z_model->current_interval_nr].output_signal[idx0];  //->data[current_interval]->output_signal[idx0];
	}

    FHZN_find_operating_point(0.06, 100, 50, 4, 4, 5,current_out, buff->data[z_model->current_interval_nr].time[0],
		&z_model->signals_intervals[z_model->current_interval_nr].op_interval_possible, &op_time);

    emxDestroyArray_real_T(current_out);

	z_model->signals_intervals[z_model->current_interval_nr].op_pos_time = (int)op_time;

    //printf("Wyniki %d wynik time %d \n", z_model->signals_intervals[z_model->current_interval_nr].op_interval_possible, (int)op_time);

	FHZN_define_model_del_terminate();
}

void FH_ZONE_MODEL_define_model_delay(FHZN_model* z_model, cyclic_buffer* buff, double section_len)
{
	/* Initialize the application.
	 You do not need to do this more than one time. */
	FHZN_define_model_del_initialize();


	emxArray_real_T* pull_signal;
	double del_coef[2] = { 0.0344, 1.236 };
	//double section_len=1055.0;
	double signal_del;
	int idx0;
	int idx1;

	static int iv0[1] = { struct_capacity };

	/* Set the size of the array.
	   Change this size to the value that the application requires. */
	pull_signal = emxCreateND_real_T(1, iv0);

	for (idx0 = 0; idx0 < pull_signal->size[0U]; idx0++) {
		pull_signal->data[idx0] = buff->data[z_model->current_interval_nr].pull_signal[idx0];
	}

	signal_del = FHZN_define_model_del(pull_signal, section_len, del_coef);

	emxDestroyArray_real_T(pull_signal);

	z_model->signals_intervals[z_model->current_interval_nr].model_del = (int)signal_del;

	FHZN_define_model_del_terminate();
}


void FH_ZONE_MODEL_define_model_inputs_Z3(FHZN_model* z_model, cyclic_buffer* buff)
{
	FHZN_define_model_del_initialize();

	emxArray_real_T* model_inputs;
	//double inputs_nr;
	//double corr_tr;
	//double var_tr;
	emxArray_real_T* input_signals;
	emxArray_real_T* output_signal;

	double corr;
	double variance;


	int idx0;
	int idx1;
	int i;

	static int iv0[2] = { struct_capacity, 3 };
	static int iv1[1] = { struct_capacity };

	input_signals = emxCreateND_real_T(2, iv0);
	output_signal = emxCreateND_real_T(1, iv1);

	emxInitArray_real_T(&model_inputs, 2);


	for (idx0 = 0; idx0 < input_signals->size[0U]; idx0++) {
		for (idx1 = 0; idx1 < FHZ3_model_inputs_nr; idx1++) {
			if (idx1 == 0) {
				input_signals->data[idx0 + input_signals->size[0] * idx1] = buff->data[z_model->current_interval_nr].input_signal_1[idx0];
			}
			else if(idx1==1) {
				input_signals->data[idx0 + input_signals->size[0] * idx1] = buff->data[z_model->current_interval_nr].input_signal_2[idx0];
			}
			else if (idx1 == 2) {
				input_signals->data[idx0 + input_signals->size[0] * idx1] = buff->data[z_model->current_interval_nr].input_signal_3[idx0];
			}
		}
	}



	for (idx0 = 0; idx0 < output_signal->size[0U]; idx0++) {
		output_signal->data[idx0] = buff->data[z_model->current_interval_nr].output_signal[idx0];  //->data[current_interval]->output_signal[idx0];
	}

	/* Call the entry-point 'FHZN_define_model_inputs'. */

	FHZN_define_model_inputs(3.0, 0.5, 0.01, input_signals, output_signal, model_inputs, &variance, &corr);

	//printf("Variance %fl corr %fl \n", variance, corr);

	for (i = 0; i < FHZ3_model_inputs_nr; i++)
	{
		//printf("WART %d \n", (int)model_inputs->data[i]);
		z_model->signals_intervals[z_model->current_interval_nr].model_inputs[i] = model_inputs->data[i];
	}

	emxDestroyArray_real_T(model_inputs);
	emxDestroyArray_real_T(output_signal);
	emxDestroyArray_real_T(input_signals);

	FHZN_define_model_del_terminate();
}

void FH_ZONE_MODEL_ident_Z3(FHZN_model* z_model, cyclic_buffer* buff)
{
	FHZN_define_model_del_initialize();

	emxArray_real_T* ni_min_opt;
	//emxArray_real_T* op_offset;
	emxArray_real_T* model_X0;
	emxArray_FHZ3_DataBuff* DataBuff;
	emxArray_FHZ3_Int* FHZ_intervals;
	emxArray_MFM_Struct* MFM_ident_models;
	double h;
	double M;
	double N;
	double m;
	double n;
	double sp_diff_avg;
	double model_diff_avg;
	double op_offset[FHZ3_model_inputs_nr + 2];
	double op_time;
	double model_identified_op_int;
	double model_identified;
	double model_inputs[3];
	emxInitArray_real_T(&ni_min_opt, 1);
	emxInitArray_real_T(&model_X0, 1);
	MFM_model* MFM_Z3_models;

	static int iv0[1] = { struct_capacity };
	static int iv2[1] = { max_buffer_size };
	static int iv3[1] = { 2 };
	static int iv4[1] = { 5 };

	FHZ3_DataBuff temp_DataBuff;
	emxArray_real_T* temp_input_1;
	emxArray_real_T* temp_input_2;
	emxArray_real_T* temp_input_3;

	emxArray_real_T* temp_output;
	emxArray_real_T* temp_sp;
	emxArray_real_T* time;

	int idx0;
	int idx1;

	DataBuff = emxCreateND_FHZ3_DataBuff(1, iv2);
	FHZ_intervals = emxCreateND_FHZ3_Int(1, iv2);
	MFM_ident_models = emxCreateND_MFM_Struct(1, iv4);

	for (idx1 = 0; idx1 < z_model->intervals_nr; idx1++)
	{

		temp_input_1 = emxCreateND_real_T(1, iv0);
		temp_input_2 = emxCreateND_real_T(1, iv0);
		temp_input_3 = emxCreateND_real_T(1, iv0);
		temp_output = emxCreateND_real_T(1, iv0);
		temp_sp = emxCreateND_real_T(1, iv0);
		time = emxCreateND_real_T(1, iv0);

		for (idx0 = 0; idx0 < struct_capacity; idx0++) {

			temp_input_1->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].input_signal_1[idx0];
			temp_input_2->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].input_signal_2[idx0];
			temp_input_3->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].input_signal_3[idx0];
			temp_output->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].output_signal[idx0];
			temp_sp->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].sp_signal[idx0];
			time->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].time[idx0];
		}

		temp_DataBuff.input_1 = temp_input_1;
		temp_DataBuff.input_2 = temp_input_2;
		temp_DataBuff.input_3 = temp_input_3;

		temp_DataBuff.output = temp_output;
		temp_DataBuff.sp_value = temp_sp;
		temp_DataBuff.time = time;

		DataBuff->data[idx1] = temp_DataBuff;

		FHZ_intervals->data[idx1].op_interval_time = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].op_pos_time;
		FHZ_intervals->data[idx1].op_interval_possible = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].op_interval_possible;
		FHZ_intervals->data[idx1].op_interval = false;

		for (idx0 = 0; idx0 < FHZ3_model_inputs_nr; idx0++) {
			FHZ_intervals->data[idx1].model_inputs[idx0] = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].model_inputs[idx0];
		}

		//FHZ_intervals->data[idx1].model_inputs[0] = 1;
		//FHZ_intervals->data[idx1].model_inputs[1] = 1;
		//FHZ_intervals->data[idx1].model_inputs[2] = 0;

		FHZ_intervals->data[idx1].model_del = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].model_del;
		FHZ_intervals->data[idx1].model_diff = 0.0;
		FHZ_intervals->data[idx1].sp_diff = 0.0;
		FHZ_intervals->data[idx1].model_nr = 0.0;
		FHZ_intervals->data[idx1].X0 = emxCreateND_real_T(1, iv3);
	}

	MFM_Z3_models = init_MFM_models_Z3();

	for (unsigned int i = 0; i < MFM_models_nr; i++)
	{
		MFM_ident_models->data[i].N = MFM_Z3_models[i].N;
		MFM_ident_models->data[i].M = MFM_Z3_models[i].M;
		MFM_ident_models->data[i].n = MFM_Z3_models[i].n;
		MFM_ident_models->data[i].m = MFM_Z3_models[i].m;
		MFM_ident_models->data[i].h = MFM_Z3_models[i].h;
	}

	FHZN_obtain_FHZ3_model(DataBuff, FHZ_intervals, MFM_ident_models,
		z_model->intervals_nr, 8, 250, &model_identified,
		&model_identified_op_int, &op_time, ni_min_opt, op_offset, &model_diff_avg,
		&sp_diff_avg, model_inputs, model_X0, &n, &m, &N, &M, &h);

	//printf("MODEL PARAMS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	//printf("Model properties N: %fl M: %fl n: %fl m: %fl h: %fl \n", N, M, n, m, h);
	//printf("Quality %fl \n", model_diff_avg);

	if (model_identified >= 1)
	{
		z_model->current_model_nr = 1;
		z_model->model_identified = true;
		z_model->op_time = op_time;
		z_model->current_model_size = (int)m;

		z_model->model_params = malloc(ni_min_opt->size[0] * sizeof(double));
		z_model->X0 = malloc(model_X0->size[0] * sizeof(double));


		for (int i = 0; i < ni_min_opt->size[0]; i++)
		{
			z_model->model_params[i] = ni_min_opt->data[i];
		}

		for (int i = 0; i < model_X0->size[0]; i++)
		{
			z_model->X0[i] = model_X0->data[i];
		}

		for (int i = 0; i < FHZ3_model_inputs_nr;i++) 
		{
			z_model->model_inputs[i] = (unsigned int)model_inputs[i];
		}

		for (int i = 0; i < FHZ3_model_inputs_nr + 2; i++)
		{
			z_model->op_offset[i] = op_offset[i];
		}

		z_model->signals_intervals[z_model->intervals_nr - 1].model_diff = model_diff_avg;
		z_model->signals_intervals[z_model->intervals_nr - 1].sp_diff = sp_diff_avg;

		printf("Params vector: \n");
		for (int i = 0; i < ni_min_opt->size[0]; i++)
		{
			printf("%fl \n", ni_min_opt->data[i]);
		}
		printf("\n");

	}

	emxDestroyArray_real_T(model_X0);
	emxDestroyArray_real_T(ni_min_opt);
	emxDestroyArray_MFM_Struct(MFM_ident_models);
	emxDestroyArray_FHZ3_Int(FHZ_intervals);
	emxDestroyArray_FHZ3_DataBuff(DataBuff);

	FHZN_define_model_del_terminate();
}

void FH_ZONE_MODEL_simulate_output_Z3(FHZN_model* z_model, cyclic_buffer* buff)
{
	FHZN_define_model_del_initialize();

	emxArray_real_T* X0;
	emxArray_FHZ3_DataBuff* DataBuff;
	emxArray_real_T* params_vector;
	emxArray_real_T* op_offset;
	emxArray_real_T* X0_prev;
	double sp_diff=0;
	double model_diff=0;
	double model_inputs[FHZ3_model_inputs_nr];

	FHZ3_DataBuff temp_DataBuff;
	emxArray_real_T* temp_input_1;
	emxArray_real_T* temp_input_2;
	emxArray_real_T* temp_input_3;

	emxArray_real_T* temp_output;
	emxArray_real_T* temp_sp;
	emxArray_real_T* time;

	int idx0;
	//int idx1;

	static int iv0[1] = { struct_capacity };
	static int iv2[1] = { max_buffer_size };
	static int iv3[1] = { 6 };
	static int iv4[1] = { 5 };
	static int iv5[5] = { 3 };


	/* Initialize function 'FHZN_simulate_FHZ4_system' input arguments. */
	/* Initialize function input argument 'dataBuff'. */

	DataBuff = emxCreateND_FHZ3_DataBuff(1, iv2);

	for (unsigned int i = 0; i < z_model->intervals_nr; i++)
	{

		temp_input_1 = emxCreateND_real_T(1, iv0);
		temp_input_2 = emxCreateND_real_T(1, iv0);
		temp_input_3 = emxCreateND_real_T(1, iv0);
		temp_output = emxCreateND_real_T(1, iv0);
		temp_sp = emxCreateND_real_T(1, iv0);
		time = emxCreateND_real_T(1, iv0);

		for (idx0 = 0; idx0 < struct_capacity; idx0++) {

			temp_input_1->data[idx0] = buff->data[(z_model->head + i) % z_model->intervals_nr].input_signal_1[idx0];
			temp_input_2->data[idx0] = buff->data[(z_model->head + i) % z_model->intervals_nr].input_signal_2[idx0];
			temp_input_3->data[idx0] = buff->data[(z_model->head + i) % z_model->intervals_nr].input_signal_3[idx0];
			temp_output->data[idx0] = buff->data[(z_model->head + i) % z_model->intervals_nr].output_signal[idx0];
			temp_sp->data[idx0] = buff->data[(z_model->head + i) % z_model->intervals_nr].sp_signal[idx0];
			time->data[idx0] = buff->data[(z_model->head + i) % z_model->intervals_nr].time[idx0];
		}

		temp_DataBuff.input_1 = temp_input_1;
		temp_DataBuff.input_2 = temp_input_2;
		temp_DataBuff.input_3 = temp_input_3;

		temp_DataBuff.output = temp_output;
		temp_DataBuff.sp_value = temp_sp;
		temp_DataBuff.time = time;

		DataBuff->data[i] = temp_DataBuff;

	}

	/* Initialize function input argument 'params_vector'. */
	params_vector = emxCreateND_real_T(1, iv3);

	for (idx0 = 0; idx0 < params_vector->size[0U]; idx0++) {
		if (idx0 <= z_model->current_model_size + 2) {
			params_vector->data[idx0] = z_model->model_params[idx0];
		}
		else {
			params_vector->data[idx0] = 0.0;
		}
	}

	/* Initialize function input argument 'op_offset'. */
	op_offset = emxCreateND_real_T(1, iv4);

	for (idx0 = 0; idx0 < op_offset->size[0U]; idx0++) {
		op_offset->data[idx0] = z_model->op_offset[idx0];
	}



	/* Initialize function input argument 'X0_prev'. */
	X0_prev = emxCreateND_real_T(1, iv5);

	for (idx0 = 0; idx0 < X0_prev->size[0U]; idx0++) {
		if (idx0 < z_model->current_model_size - 1) {
			X0_prev->data[idx0] = z_model->X0[idx0];
		}
		else {
			X0_prev->data[idx0] = 0.0;
		}
	}

	/* Initialize model inputs */
	for (idx0 = 0; idx0 < FHZ3_model_inputs_nr; idx0++) {
		if (z_model->model_inputs[idx0]) {
			model_inputs[idx0] = 1.0;
		}
		else {
			model_inputs[idx0] = 0.0;
		}
	}

	/* Initialize X0 */
	emxInitArray_real_T(&X0, 1);

	/* Call the entry-point 'FHZN_simulate_FHZ4_system'. */
	FHZN_simulate_FHZ3_system(DataBuff, params_vector, &model_inputs, op_offset, X0_prev,
		z_model->signals_intervals[z_model->current_interval_nr].model_del,
		250, z_model->intervals_nr, 2, 1, z_model->current_model_size, &model_diff, &sp_diff, X0);

	printf("......................................\n");
	printf("X0: \n");
	for (unsigned int i = 0; i < X0->size[0]; i++)
	{
		printf("%fl \n", X0->data[i]);
	}

	if (model_diff > FHZN_tr_diff) {
		model_diff = FHZN_max_diff;
	}

	if (sp_diff > FHZN_tr_diff) {
		sp_diff = FHZN_max_diff;
	}

	printf("Difference model: %fl \n", model_diff);
	printf("Difference SP: %fl \n", sp_diff);

	z_model->signals_intervals[z_model->current_interval_nr].model_diff = model_diff;
	z_model->signals_intervals[z_model->current_interval_nr].sp_diff = sp_diff;

	//z_model->X0 = malloc(X0->size[0] * sizeof(double));

	for (unsigned int i = 0; i < z_model->current_model_size - 1; i++)
	{
		z_model->X0[i] = X0->data[i];
	}

	emxDestroyArray_real_T(X0);
	emxDestroyArray_real_T(X0_prev);
	emxDestroyArray_real_T(op_offset);
	emxDestroyArray_real_T(params_vector);
	emxDestroyArray_FHZ3_DataBuff(DataBuff);

	FHZN_define_model_del_terminate();
}

void FH_ZONE_MODEL_reident_Z3(FHZN_model* z_model, cyclic_buffer* buff)
{
	FHZN_define_model_del_initialize();

	emxArray_real_T* ni_min_opt;
	//emxArray_real_T* op_offset;
	emxArray_real_T* model_X0;
	emxArray_FHZ3_DataBuff* DataBuff;
	emxArray_FHZ3_Int* FHZ_intervals;
	emxArray_MFM_Struct* MFM_ident_models;
	double h;
	double M;
	double N;
	double m;
	double n;
	double sp_diff_avg;
	double model_diff_avg;
	double op_offset[FHZ3_model_inputs_nr + 2];
	double op_time;
	double model_identified_op_int;
	double model_identified;
	double model_inputs[3];
	emxInitArray_real_T(&ni_min_opt, 1);
	emxInitArray_real_T(&model_X0, 1);
	MFM_model* MFM_Z3_models;

	static int iv0[1] = { struct_capacity };
	static int iv2[1] = { max_buffer_size };
	static int iv3[1] = { 2 };
	static int iv4[1] = { 5 };

	FHZ3_DataBuff temp_DataBuff;
	emxArray_real_T* temp_input_1;
	emxArray_real_T* temp_input_2;
	emxArray_real_T* temp_input_3;

	emxArray_real_T* temp_output;
	emxArray_real_T* temp_sp;
	emxArray_real_T* time;

	int idx0;
	int idx1;

	DataBuff = emxCreateND_FHZ3_DataBuff(1, iv2);
	FHZ_intervals = emxCreateND_FHZ3_Int(1, iv2);
	MFM_ident_models = emxCreateND_MFM_Struct(1, iv4);

	for (idx1 = 0; idx1 < z_model->intervals_nr; idx1++)
	{

		temp_input_1 = emxCreateND_real_T(1, iv0);
		temp_input_2 = emxCreateND_real_T(1, iv0);
		temp_input_3 = emxCreateND_real_T(1, iv0);
		temp_output = emxCreateND_real_T(1, iv0);
		temp_sp = emxCreateND_real_T(1, iv0);
		time = emxCreateND_real_T(1, iv0);

		for (idx0 = 0; idx0 < struct_capacity; idx0++) {

			temp_input_1->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].input_signal_1[idx0];
			temp_input_2->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].input_signal_2[idx0];
			temp_input_3->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].input_signal_3[idx0];
			temp_output->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].output_signal[idx0];
			temp_sp->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].sp_signal[idx0];
			time->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].time[idx0];
		}

		temp_DataBuff.input_1 = temp_input_1;
		temp_DataBuff.input_2 = temp_input_2;
		temp_DataBuff.input_3 = temp_input_3;

		temp_DataBuff.output = temp_output;
		temp_DataBuff.sp_value = temp_sp;
		temp_DataBuff.time = time;

		DataBuff->data[idx1] = temp_DataBuff;

		FHZ_intervals->data[idx1].op_interval_time = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].op_pos_time;
		FHZ_intervals->data[idx1].op_interval_possible = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].op_interval_possible;
		FHZ_intervals->data[idx1].op_interval = false;

		for (idx0 = 0; idx0 < FHZ3_model_inputs_nr; idx0++) {
			FHZ_intervals->data[idx1].model_inputs[idx0] = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].model_inputs[idx0];
		}

		//FHZ_intervals->data[idx1].model_inputs[0] = 1;
		//FHZ_intervals->data[idx1].model_inputs[1] = 1;
		//FHZ_intervals->data[idx1].model_inputs[2] = 0;

		FHZ_intervals->data[idx1].model_del = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].model_del;
		FHZ_intervals->data[idx1].model_diff = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].model_diff;
		FHZ_intervals->data[idx1].sp_diff = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].sp_diff;
		FHZ_intervals->data[idx1].model_nr = 0.0;
		FHZ_intervals->data[idx1].X0 = emxCreateND_real_T(1, iv3);
	}

	MFM_Z3_models = init_MFM_models_Z3();

	for (unsigned int i = 0; i < MFM_models_nr; i++)
	{
		MFM_ident_models->data[i].N = MFM_Z3_models[i].N;
		MFM_ident_models->data[i].M = MFM_Z3_models[i].M;
		MFM_ident_models->data[i].n = MFM_Z3_models[i].n;
		MFM_ident_models->data[i].m = MFM_Z3_models[i].m;
		MFM_ident_models->data[i].h = MFM_Z3_models[i].h;
	}

	FHZN_obtain_FHZ3_model_nonzero(DataBuff, FHZ_intervals, MFM_ident_models,
		z_model->intervals_nr, 4, 250, &model_identified,
		&model_identified_op_int, &op_time, ni_min_opt, op_offset, &model_diff_avg,
		&sp_diff_avg, model_inputs, model_X0, &n, &m, &N, &M, &h);

	//printf("MODEL PARAMS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	//printf("Model properties N: %fl M: %fl n: %fl m: %fl h: %fl \n", N, M, n, m, h);
	//printf("Quality %fl \n", model_diff_avg);

	if (model_identified >= 1)
	{
		z_model->current_model_nr = z_model->current_model_nr + 1;
		z_model->model_identified = true;
		z_model->op_time = op_time;
		z_model->current_model_size = (int)m;

		z_model->model_params = malloc(ni_min_opt->size[0] * sizeof(double));
		z_model->X0 = malloc(model_X0->size[0] * sizeof(double));


		for (int i = 0; i < ni_min_opt->size[0]; i++)
		{
			z_model->model_params[i] = ni_min_opt->data[i];
		}

		for (int i = 0; i < model_X0->size[0]; i++)
		{
			z_model->X0[i] = model_X0->data[i];
		}

		for (int i = 0; i < FHZ3_model_inputs_nr; i++)
		{
			z_model->model_inputs[i] = (unsigned int)model_inputs[i];
		}

		for (int i = 0; i < FHZ3_model_inputs_nr + 2; i++)
		{
			z_model->op_offset[i] = op_offset[i];
		}

		z_model->signals_intervals[z_model->intervals_nr - 1].model_diff = model_diff_avg;
		z_model->signals_intervals[z_model->intervals_nr - 1].sp_diff = sp_diff_avg;

		printf("Params vector: \n");
		for (int i = 0; i < ni_min_opt->size[0]; i++)
		{
			printf("%fl \n", ni_min_opt->data[i]);
		}
		printf("\n");

	}

	emxDestroyArray_real_T(model_X0);
	emxDestroyArray_real_T(ni_min_opt);
	emxDestroyArray_MFM_Struct(MFM_ident_models);
	emxDestroyArray_FHZ3_Int(FHZ_intervals);
	emxDestroyArray_FHZ3_DataBuff(DataBuff);

	FHZN_define_model_del_terminate();
}





void FH_ZONE_MODEL_define_model_inputs_Z4(FHZN_model* z_model, cyclic_buffer* buff)
{
	FHZN_define_model_del_initialize();

	emxArray_real_T* model_inputs;
	//double inputs_nr;
	//double corr_tr;
	//double var_tr;
	emxArray_real_T* input_signals;
	emxArray_real_T* output_signal;

	double corr;
	double variance;


	int idx0;
	int idx1;
	int i;

	static int iv0[2] = { struct_capacity, 2 };
	static int iv1[1] = { struct_capacity };

	input_signals = emxCreateND_real_T(2, iv0);
	output_signal = emxCreateND_real_T(1, iv1);

	emxInitArray_real_T(&model_inputs, 2);


	for (idx0 = 0; idx0 < input_signals->size[0U]; idx0++) {
		for (idx1 = 0; idx1 < 2; idx1++) {
			if (idx1 == 0) {
				input_signals->data[idx0 + input_signals->size[0] * idx1] = buff->data[z_model->current_interval_nr].input_signal_1[idx0];
			}
			else {
				input_signals->data[idx0 + input_signals->size[0] * idx1] = buff->data[z_model->current_interval_nr].input_signal_2[idx0];
			}
		}
	}



	for (idx0 = 0; idx0 < output_signal->size[0U]; idx0++) {
		output_signal->data[idx0] = buff->data[z_model->current_interval_nr].output_signal[idx0];  //->data[current_interval]->output_signal[idx0];
	}

	/* Call the entry-point 'FHZN_define_model_inputs'. */

	FHZN_define_model_inputs(2.0, 0.5, 0.01, input_signals, output_signal, model_inputs, &variance, &corr);

	//printf("Variance %fl corr %fl \n", variance, corr);

	for (i = 0; i < FHZ4_model_inputs_nr; i++)
	{
		//printf("WART %d \n", (int)model_inputs->data[i]);
		z_model->signals_intervals[z_model->current_interval_nr].model_inputs[i] = model_inputs->data[i];
	}

	emxDestroyArray_real_T(model_inputs);
	emxDestroyArray_real_T(output_signal);
	emxDestroyArray_real_T(input_signals);

	FHZN_define_model_del_terminate();
}

void FH_ZONE_MODEL_ident_Z4(FHZN_model* z_model, cyclic_buffer* buff)
{
	FHZN_define_model_del_initialize();

	emxArray_real_T* ni_min_opt;
	//emxArray_real_T* op_offset;
	emxArray_real_T* model_X0;
	emxArray_FHZ4_DataBuff* DataBuff;
	emxArray_FHZ4_Int* FHZ_intervals;
	emxArray_MFM_Struct* MFM_ident_models;
	double h;
	double M;
	double N;
	double m;
	double n;
	double sp_diff_avg;
	double model_diff_avg;
	double op_offset[FHZ4_model_inputs_nr+2];
	double op_time;
	double model_identified_op_int;
	double model_identified;
	emxInitArray_real_T(&ni_min_opt, 1);
	emxInitArray_real_T(&model_X0, 1);
	MFM_model* MFM_Z4_models;

	static int iv0[1] = { struct_capacity };
	static int iv2[1] = { max_buffer_size };
	static int iv3[1] = { 2 };
	static int iv4[1] = { 5 };

	FHZ4_DataBuff temp_DataBuff;
	emxArray_real_T* temp_input_1;
	emxArray_real_T* temp_input_2;

	emxArray_real_T* temp_output;
	emxArray_real_T* temp_sp;
	emxArray_real_T* time;

	int idx0;
	int idx1;

	DataBuff = emxCreateND_FHZ4_DataBuff(1, iv2);
	FHZ_intervals = emxCreateND_FHZ4_Int(1, iv2);
	MFM_ident_models = emxCreateND_MFM_Struct(1, iv4);

	for (idx1 = 0; idx1 < z_model->intervals_nr; idx1++)
	{
		
		temp_input_1 = emxCreateND_real_T(1, iv0);
		temp_input_2 = emxCreateND_real_T(1, iv0);
		temp_output = emxCreateND_real_T(1, iv0);
		temp_sp = emxCreateND_real_T(1, iv0);
		time = emxCreateND_real_T(1, iv0);

		for (idx0 = 0; idx0 < struct_capacity; idx0++) {

			temp_input_1->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].input_signal_1[idx0];
			temp_input_2->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].input_signal_2[idx0];
			temp_output->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].output_signal[idx0];
			temp_sp->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].sp_signal[idx0];
			time->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].time[idx0];
		}

		temp_DataBuff.input_1 = temp_input_1;
		temp_DataBuff.input_2 = temp_input_2;

		temp_DataBuff.output = temp_output;
		temp_DataBuff.sp_value = temp_sp;
		temp_DataBuff.time = time;

		DataBuff->data[idx1] = temp_DataBuff;

		FHZ_intervals->data[idx1].op_interval_time = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].op_pos_time;
		FHZ_intervals->data[idx1].op_interval_possible = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].op_interval_possible;
		FHZ_intervals->data[idx1].op_interval = false;

		for (idx0 = 0; idx0 < 2; idx0++) {
			FHZ_intervals->data[idx1].model_inputs[idx0] = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].model_inputs[idx0];
		}

		FHZ_intervals->data[idx1].model_del = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].model_del;
		FHZ_intervals->data[idx1].model_diff = 0.0;
		FHZ_intervals->data[idx1].sp_diff = 0.0;
		FHZ_intervals->data[idx1].model_nr = 0.0;
		FHZ_intervals->data[idx1].X0 = emxCreateND_real_T(1, iv3);
	}

	MFM_Z4_models = init_MFM_models_Z4();

	for (unsigned int i = 0; i < MFM_models_nr; i++)
	{
		MFM_ident_models->data[i].N = MFM_Z4_models[i].N;
		MFM_ident_models->data[i].M = MFM_Z4_models[i].M;
		MFM_ident_models->data[i].n = MFM_Z4_models[i].n;
		MFM_ident_models->data[i].m = MFM_Z4_models[i].m;
		MFM_ident_models->data[i].h = MFM_Z4_models[i].h;
	}

	FHZN_obtain_FHZ4_model(DataBuff, FHZ_intervals, MFM_ident_models,
		z_model->intervals_nr, 8, 250, &model_identified,
		&model_identified_op_int, &op_time, ni_min_opt, op_offset, &model_diff_avg,
		&sp_diff_avg, model_X0, &n, &m, &N, &M, &h);

	//printf("MODEL PARAMS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	//printf("Model properties N: %fl M: %fl n: %fl m: %fl h: %fl \n", N, M, n, m, h);
	//printf("Quality %fl \n", model_diff_avg);

	if (model_identified >= 1)
	{
		z_model->current_model_nr = 1;
		z_model->model_identified = true;
		z_model->op_time = op_time;
		z_model->current_model_size = (int)m;

		z_model->model_params = malloc(ni_min_opt->size[0] * sizeof(double));
		z_model->X0 = malloc(model_X0->size[0] * sizeof(double));


		for (int i = 0; i < ni_min_opt->size[0]; i++)
		{
			z_model->model_params[i] = ni_min_opt->data[i];
		}

		for (int i = 0; i < model_X0->size[0]; i++)
		{
			z_model->X0[i] = model_X0->data[i];
		}

		for (int i = 0; i < FHZ4_model_inputs_nr+2; i++)
		{
			z_model->op_offset[i] = op_offset[i];
		}

		z_model->signals_intervals[z_model->intervals_nr - 1].model_diff = model_diff_avg;
		z_model->signals_intervals[z_model->intervals_nr - 1].sp_diff = sp_diff_avg;

		printf("Params vector: \n");
		for (int i = 0; i < ni_min_opt->size[0]; i++)
		{
			printf("%fl \n", ni_min_opt->data[i]);
		}
		printf("\n");

	}

	emxDestroyArray_real_T(model_X0);
	emxDestroyArray_real_T(ni_min_opt);
	emxDestroyArray_MFM_Struct(MFM_ident_models);
	emxDestroyArray_FHZ4_Int(FHZ_intervals);
	emxDestroyArray_FHZ4_DataBuff(DataBuff);

	FHZN_define_model_del_terminate();
}

void FH_ZONE_MODEL_reident_Z4(FHZN_model* z_model, cyclic_buffer* buff)
{
	FHZN_define_model_del_initialize();

	emxArray_real_T* ni_min_opt;
	emxArray_real_T* model_X0;
	emxArray_FHZ4_DataBuff* DataBuff;
	emxArray_FHZ4_Int* FHZ_intervals;
	emxArray_MFM_Struct* MFM_ident_models;
	double h;
	double M;
	double N;
	double m;
	double n;
	double sp_diff_avg;
	double model_diff_avg;
	double op_offset[FHZ4_model_inputs_nr+2];
	double op_time;
	double model_reidentified_op_int;
	double model_reidentified;
	emxInitArray_real_T(&ni_min_opt, 1);
	emxInitArray_real_T(&model_X0, 1);

	static int iv0[1] = { struct_capacity };
	static int iv2[1] = { max_buffer_size };
	static int iv3[1] = { 2 };
	static int iv4[1] = { 5 };

	MFM_model* MFM_Z4_models;
	FHZ4_DataBuff temp_DataBuff;
	emxArray_real_T* temp_input_1;
	emxArray_real_T* temp_input_2;

	emxArray_real_T* temp_output;
	emxArray_real_T* temp_sp;
	emxArray_real_T* time;

	int idx0;
	int idx1;

	DataBuff = emxCreateND_FHZ4_DataBuff(1, iv2);
	FHZ_intervals = emxCreateND_FHZ4_Int(1, iv2);
	MFM_ident_models = emxCreateND_MFM_Struct(1, iv4);



	for (idx1 = 0; idx1 < z_model->intervals_nr; idx1++)
	{

		temp_input_1 = emxCreateND_real_T(1, iv0);
		temp_input_2 = emxCreateND_real_T(1, iv0);
		temp_output = emxCreateND_real_T(1, iv0);
		temp_sp = emxCreateND_real_T(1, iv0);
		time = emxCreateND_real_T(1, iv0);

		for (idx0 = 0; idx0 < struct_capacity; idx0++) {

			temp_input_1->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].input_signal_1[idx0];
			temp_input_2->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].input_signal_2[idx0];
			temp_output->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].output_signal[idx0];
			temp_sp->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].sp_signal[idx0];
			time->data[idx0] = buff->data[(z_model->head + idx1) % z_model->intervals_nr].time[idx0];
		}

		temp_DataBuff.input_1 = temp_input_1;
		temp_DataBuff.input_2 = temp_input_2;

		temp_DataBuff.output = temp_output;
		temp_DataBuff.sp_value = temp_sp;
		temp_DataBuff.time = time;

		DataBuff->data[idx1] = temp_DataBuff;

		FHZ_intervals->data[idx1].op_interval_time = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].op_pos_time;
		FHZ_intervals->data[idx1].op_interval_possible = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].op_interval_possible;
		FHZ_intervals->data[idx1].op_interval = false;

		for (idx0 = 0; idx0 < 2; idx0++) {
			FHZ_intervals->data[idx1].model_inputs[idx0] = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].model_inputs[idx0];
		}

		FHZ_intervals->data[idx1].model_del = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].model_del;
		FHZ_intervals->data[idx1].model_diff = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].model_diff;
		FHZ_intervals->data[idx1].sp_diff = z_model->signals_intervals[(z_model->head + idx1) % z_model->intervals_nr].sp_diff;
		FHZ_intervals->data[idx1].model_nr = 0.0;
		FHZ_intervals->data[idx1].X0 = emxCreateND_real_T(1, iv3);
	}

	MFM_Z4_models = init_MFM_models_Z4();

	for (unsigned int i = 0; i < MFM_models_nr; i++)
	{
		MFM_ident_models->data[i].N = MFM_Z4_models[i].N;
		MFM_ident_models->data[i].M = MFM_Z4_models[i].M;
		MFM_ident_models->data[i].n = MFM_Z4_models[i].n;
		MFM_ident_models->data[i].m = MFM_Z4_models[i].m;
		MFM_ident_models->data[i].h = MFM_Z4_models[i].h;
	}

	/* Call the entry-point 'FHZN_obtain_FHZ4_model_nonzero'. */
	FHZN_obtain_FHZ4_model_nonzero(DataBuff, FHZ_intervals, MFM_ident_models,
		z_model->intervals_nr, 4, 250, &model_reidentified,
		&model_reidentified_op_int, &op_time, ni_min_opt, op_offset, &model_diff_avg,
		&sp_diff_avg, model_X0, &n, &m, &N, &M, &h);

	if (model_reidentified >= 1)
	{
		z_model->current_model_nr = z_model->current_model_nr + 1;
		z_model->model_identified = true;
		z_model->op_time = op_time;
		z_model->current_model_size = (int)m;

		z_model->model_params = malloc(ni_min_opt->size[0] * sizeof(double));
		z_model->X0 = malloc(model_X0->size[0] * sizeof(double));


		for (int i = 0; i < ni_min_opt->size[0]; i++)
		{
			z_model->model_params[i] = ni_min_opt->data[i];
		}

		for (int i = 0; i < model_X0->size[0]; i++)
		{
			z_model->X0[i] = model_X0->data[i];
		}

		for (int i = 0; i < FHZ4_model_inputs_nr + 2; i++)
		{
			z_model->op_offset[i] = op_offset[i];
		}

		z_model->signals_intervals[z_model->intervals_nr - 1].model_diff = model_diff_avg;
		z_model->signals_intervals[z_model->intervals_nr - 1].sp_diff = sp_diff_avg;

		printf("New offset: \n");
		for (unsigned int i = 0; i < 4; i++)
		{
			printf("%fl \n", op_offset[i]);
		}
		printf("\n");


		printf("Params vector: \n");
		for (unsigned int i = 0; i < ni_min_opt->size[0]; i++)
		{
			printf("%fl \n", ni_min_opt->data[i]);
		}
		printf("\n");

	}

	emxDestroyArray_real_T(model_X0);
	emxDestroyArray_real_T(ni_min_opt);
	emxDestroyArray_MFM_Struct(MFM_ident_models);
	emxDestroyArray_FHZ4_Int(FHZ_intervals);
	emxDestroyArray_FHZ4_DataBuff(DataBuff);

	FHZN_define_model_del_terminate();
}

void FH_ZONE_MODEL_simulate_output_Z4(FHZN_model* z_model, cyclic_buffer* buff)
{
	FHZN_define_model_del_initialize();

	emxArray_real_T* X0;
	emxArray_FHZ4_DataBuff* DataBuff;
	emxArray_real_T* params_vector;
	emxArray_real_T* op_offset;
	emxArray_real_T* X0_prev;
	double sp_diff;
	double model_diff;

	FHZ4_DataBuff temp_DataBuff;
	emxArray_real_T* temp_input_1;
	emxArray_real_T* temp_input_2;

	emxArray_real_T* temp_output;
	emxArray_real_T* temp_sp;
	emxArray_real_T* time;

	int idx0;
	//int idx1;

	static int iv0[1] = { struct_capacity };
	static int iv2[1] = { max_buffer_size };
	static int iv3[1] = { 6 };
	static int iv4[1] = { 4 };
	static int iv5[5] = { 3 };


	/* Initialize function 'FHZN_simulate_FHZ4_system' input arguments. */
	/* Initialize function input argument 'dataBuff'. */

	DataBuff = emxCreateND_FHZ4_DataBuff(1, iv2);

	for (unsigned int i = 0; i < z_model->intervals_nr; i++)
	{

		temp_input_1 = emxCreateND_real_T(1, iv0);
		temp_input_2 = emxCreateND_real_T(1, iv0);
		temp_output = emxCreateND_real_T(1, iv0);
		temp_sp = emxCreateND_real_T(1, iv0);
		time = emxCreateND_real_T(1, iv0);

		for (idx0 = 0; idx0 < struct_capacity; idx0++) {

			temp_input_1->data[idx0] = buff->data[(z_model->head + i) % z_model->intervals_nr].input_signal_1[idx0];
			temp_input_2->data[idx0] = buff->data[(z_model->head + i) % z_model->intervals_nr].input_signal_2[idx0];
			temp_output->data[idx0] = buff->data[(z_model->head + i) % z_model->intervals_nr].output_signal[idx0];
			temp_sp->data[idx0] = buff->data[(z_model->head + i) % z_model->intervals_nr].sp_signal[idx0];
			time->data[idx0] = buff->data[(z_model->head + i) % z_model->intervals_nr].time[idx0];
		}

		temp_DataBuff.input_1 = temp_input_1;
		temp_DataBuff.input_2 = temp_input_2;

		temp_DataBuff.output = temp_output;
		temp_DataBuff.sp_value = temp_sp;
		temp_DataBuff.time = time;

		DataBuff->data[i] = temp_DataBuff;

	}

	/* Initialize function input argument 'params_vector'. */
	params_vector = emxCreateND_real_T(1, iv3);

	for (idx0 = 0; idx0 < params_vector->size[0U]; idx0++) {
		if (idx0 <= z_model->current_model_size + 2){
			params_vector->data[idx0] = z_model->model_params[idx0];
		}
		else {
			params_vector->data[idx0] = 0.0;
		}
	}

	/* Initialize function input argument 'op_offset'. */
	op_offset = emxCreateND_real_T(1, iv4);

	for (idx0 = 0; idx0 < op_offset->size[0U]; idx0++) {
		op_offset->data[idx0] = z_model->op_offset[idx0];
	}



	/* Initialize function input argument 'X0_prev'. */
	X0_prev = emxCreateND_real_T(1, iv5);

	for (idx0 = 0; idx0 < X0_prev->size[0U]; idx0++) {
		if (idx0 < z_model->current_model_size -1) {
			X0_prev->data[idx0] = z_model->X0[idx0];
		}
		else {
			X0_prev->data[idx0] = 0.0;
		}
	}

	emxInitArray_real_T(&X0, 1);

	/* Call the entry-point 'FHZN_simulate_FHZ4_system'. */
	FHZN_simulate_FHZ4_system(DataBuff, params_vector, op_offset, X0_prev,
		z_model->signals_intervals[z_model->current_interval_nr].model_del,
		250, z_model->intervals_nr, 2, 1, z_model->current_model_size, &model_diff, &sp_diff, X0);

	printf("......................................\n");
	printf("X0: \n");
	for (unsigned int i = 0; i < X0->size[0]; i++)
	{
		printf("%fl \n", X0->data[i]);
	}

	if (model_diff > FHZN_tr_diff) {
		model_diff = FHZN_max_diff;
	}

	if (sp_diff > FHZN_tr_diff) {
		sp_diff = FHZN_max_diff;
	}

	printf("Difference model: %fl \n", model_diff);
	printf("Difference SP: %fl \n", sp_diff);

	z_model->signals_intervals[z_model->current_interval_nr].model_diff = model_diff;
	z_model->signals_intervals[z_model->current_interval_nr].sp_diff = sp_diff;

	//z_model->X0 = malloc(X0->size[0] * sizeof(double));

	for (unsigned int i = 0; i < z_model->current_model_size-1; i++)
	{
		z_model->X0[i] = X0->data[i];
	}

	emxDestroyArray_real_T(X0);
	emxDestroyArray_real_T(X0_prev);
	emxDestroyArray_real_T(op_offset);
	emxDestroyArray_real_T(params_vector);
	emxDestroyArray_FHZ4_DataBuff(DataBuff);

	FHZN_define_model_del_terminate();
}

void FH_ZONE_MODEL_obtain_MPC_model(FHZN_model* z_model, cyclic_buffer* buff)
{
	FHZN_define_model_del_initialize();

	emxArray_real_T* Omega;
	emxArray_real_T* Psi;
	emxArray_real_T* Gamma;
	emxArray_real_T* A;
	emxArray_real_T* B;
	emxArray_real_T* Bd;
	emxArray_real_T* C;
	emxArray_real_T* Q;
	emxArray_real_T* R;
	emxArray_real_T* Ap;
	emxArray_real_T* Lzerot;
	emxArray_real_T* M;

	int i;
	int j;
	unsigned int inputs_nr = 0;

	double inputs[3];

	for (i = 0; i < max_model_inputs; i++) {
		inputs[i] = (double)z_model->model_inputs[i];
	}

	static int iv3[1] = { 6 };
	emxArray_real_T* params_vector;
	int idx0;

	emxInitArray_real_T(&Omega, 2);
	emxInitArray_real_T(&Psi, 2);
	emxInitArray_real_T(&Gamma, 2);
	emxInitArray_real_T(&A, 2);
	emxInitArray_real_T(&B, 2);
	emxInitArray_real_T(&Bd, 2);
	emxInitArray_real_T(&C, 2);
	emxInitArray_real_T(&Q, 2);
	emxInitArray_real_T(&R, 2);
	emxInitArray_real_T(&Ap, 2);
	emxInitArray_real_T(&Lzerot, 2);
	emxInitArray_real_T(&M, 2);

	for (int i = 1; i < FHZN_max_inputs; i++) 
	{
		if (z_model->model_inputs[i]) {
			inputs_nr += 1;
		}
	}

	/* Initialize function 'FHZN_obtain_MPC_model_FF' input arguments. */
	/* Initialize function input argument 'inputs'. */
	//argInit_1x3_uint8_T(inputs);

	/* Initialize function input argument 'params_vector'. */
	//params_vector = argInit_Unboundedx1_real_T();

	params_vector = emxCreateND_real_T(1, iv3);

	for (idx0 = 0; idx0 < params_vector->size[0U]; idx0++) {
		if (idx0 <= z_model->current_model_size + 2) {
			params_vector->data[idx0] = z_model->model_params[idx0];
		}
		else {
			params_vector->data[idx0] = 0.0;
		}
	}

	/* Call the entry-point 'FHZN_obtain_MPC_model_FF'. */
	FHZN_obtain_MPC_model_FF(inputs, params_vector, 1, z_model->current_model_size,
		Laguerre_functions_nr, Laguerre_function_coef, MPC_Tp, MPC_h, 
		Omega, Psi, Gamma, A, B, Bd, C, Q, R, Ap, Lzerot, M);

	printf("Omega: \n");
	z_model->Omega = malloc(Laguerre_functions_nr * inputs_nr * Laguerre_functions_nr * inputs_nr * sizeof(double));
	for (i = 0; i < Omega->size[0]; i++){
		for (j = 0; j < Omega->size[1]; j++){
			printf("%fl ", Omega->data[i + j * Omega->size[0]]);
			z_model->Omega[i + j * Omega->size[0]] = Omega->data[i + j * Omega->size[0]];
		}
		printf("\n");
	}

	printf("Psi: \n");
	z_model->Psi = malloc(Laguerre_functions_nr* inputs_nr * z_model->current_model_size * sizeof(double));
	for (i = 0; i < Psi->size[0]; i++){
		for (j = 0; j < Psi->size[1]; j++){
			printf("%fl ", Psi->data[i + j * Psi->size[0]]);
			z_model->Psi[i + j * Psi->size[0]] = Psi->data[i + j * Psi->size[0]];
		}
		printf("\n");
	}

	printf("Gamma: \n");
	z_model->Gamma = malloc(Laguerre_functions_nr * inputs_nr * Laguerre_functions_nr * sizeof(double));
	for (i = 0; i < Gamma->size[0]; i++){
		for (j = 0; j < Gamma->size[1]; j++){
			printf("%fl ", Gamma->data[i + j * Gamma->size[0]]);
			z_model->Gamma[i + j * Gamma->size[0]] = Gamma->data[i + j * Gamma->size[0]];
		}
		printf("\n");
	}

	printf("A: \n");
	z_model->A = malloc(z_model->current_model_size * z_model->current_model_size * sizeof(double));
	for (i = 0; i < A->size[0]; i++){
		for (j = 0; j < A->size[1]; j++){
			printf("%fl ", A->data[i + j * A->size[0]]);
			z_model->A[i + j * A->size[0]] = A->data[i + j * A->size[0]];
		}
		printf("\n");
	}

	printf("B: \n");
	z_model->B = malloc(z_model->current_model_size * inputs_nr * sizeof(double));
	for (i = 0; i < B->size[0]; i++){
		for (j = 0; j < B->size[1]; j++){
			printf("%fl ", B->data[i + j * B->size[0]]);
			z_model->B[i + j * B->size[0]] = B->data[i + j * B->size[0]];
		}
		printf("\n");
	}

	printf("Bd: \n");
	z_model->Bd = malloc(z_model->current_model_size * sizeof(double));
	for (i = 0; i < Bd->size[0]; i++){
		for (j = 0; j < Bd->size[1]; j++) {
			printf("%fl ", Bd->data[i+j * Bd->size[0]]);
			z_model->Bd[i + j * B->size[0]] = Bd->data[i + j * Bd->size[0]];
			printf("\n");
		}		
	}

	printf("C: \n");
	z_model->C = malloc(z_model->current_model_size * sizeof(double));
	for (i = 0; i < C->size[0]; i++) {
		for (j = 0; j < C->size[1]; j++) {
			printf("%fl ", C->data[i+j*C->size[0]]);
			z_model->C[i+j*C->size[0]] = C->data[i + j * C->size[0]];
		}
	}
	printf("\n");

	printf("Ap: \n");
	z_model->Ap = malloc(Laguerre_functions_nr * Laguerre_functions_nr * sizeof(double));
	for (i = 0; i < Ap->size[0]; i++){
		for (j = 0; j < Ap->size[1]; j++){
			printf("%fl ", Ap->data[i + j * Ap->size[0]]);
			z_model->Ap[i + j * Ap->size[0]] = Ap->data[i + j * Ap->size[0]];
		}
		printf("\n");
	}

	printf("Lzerot: \n");
	z_model->Lzerot = malloc(inputs_nr*Laguerre_functions_nr* inputs_nr * sizeof(double));
	for (i = 0; i < Lzerot->size[0]; i++){
		for (j = 0; j < Lzerot->size[1]; j++) {
			printf("%fl ", Lzerot->data[i+j*Lzerot->size[0]]);
			z_model->Lzerot[i + j * Lzerot->size[0]] = Lzerot->data[i + j * Lzerot->size[0]];
		}
		printf("\n");
	}

	printf("M: \n");
	z_model->M = malloc(4 * inputs_nr * Laguerre_functions_nr * inputs_nr * sizeof(double));
	for (i = 0; i < M->size[0]; i++) {
		for (j = 0; j < M->size[1]; j++) {
			printf("%fl ", M->data[i + j * M->size[0]]);
			z_model->M[i + j * M->size[0]] = M->data[i + j * M->size[0]];
		}
		printf("\n");
	}


	emxDestroyArray_real_T(M);
	emxDestroyArray_real_T(Lzerot);
	emxDestroyArray_real_T(Ap);
	emxDestroyArray_real_T(R);
	emxDestroyArray_real_T(Q);
	emxDestroyArray_real_T(C);
	emxDestroyArray_real_T(Bd);
	emxDestroyArray_real_T(B);
	emxDestroyArray_real_T(A);
	emxDestroyArray_real_T(Gamma);
	emxDestroyArray_real_T(Psi);
	emxDestroyArray_real_T(Omega);
	emxDestroyArray_real_T(params_vector);

	FHZN_define_model_del_terminate();
}
