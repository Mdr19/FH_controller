# include <stdlib.h>
# include <stdio.h>
# include "data_struct.h"

data_struct* DATA_STR_create(unsigned int capacity)
{
	data_struct* str = (data_struct*)malloc(sizeof(data_struct));

	if (str == NULL) {
		printf("Cannot allocate\n");
		return NULL;
	}
	else
	{
		str->signals_len = capacity;
		str->input_signal_1 = (double*)malloc(capacity * sizeof(double));
		str->input_signal_2 = (double*)malloc(capacity * sizeof(double));
		str->input_signal_3 = (double*)malloc(capacity * sizeof(double));
		str->output_signal = (double*)malloc(capacity * sizeof(double));
		str->sp_signal = (double*)malloc(capacity * sizeof(double));
		str->pull_signal = (double*)malloc(capacity * sizeof(double));
		str->time = (double*)malloc(capacity * sizeof(double));

		if ((str->input_signal_1 == NULL) || (str->input_signal_2 == NULL) || (str->input_signal_3 == NULL) ||
			(str->output_signal == NULL) || (str->sp_signal == NULL) || (str->pull_signal == NULL) || (str->time == NULL))
		{
			printf("Cannot allocate signals\n");
			return NULL;
		}
	}

	DATA_STR_init_selected_number(str, 0.0);

	return str;
}

int DATA_STR_init_random(data_struct* str)
{
	if (str==NULL)
	{
		return -1;
	}
	else {
		int i;
		for (i = 0; i < str->signals_len; i++)
		{
			str->input_signal_1[i] = rand();
			str->input_signal_2[i] = rand();
			str->input_signal_3[i] = rand();
			str->output_signal[i] = rand();
			str->sp_signal[i] = rand();
			str->pull_signal[i] = rand();
			str->time[i] = rand();
		}

		return 0;
	}
}

int DATA_STR_init_selected_number(data_struct* str, double number)
{
	if (str == NULL)
	{
		return -1;
	}
	else {

		//str->test = number;
		//str->test_2 = number_2;

		int i;
		for (i = 0; i < str->signals_len; i++)
		{
			str->input_signal_1[i] = number;
			str->input_signal_2[i] = number;
			str->input_signal_3[i] = number;
			str->output_signal[i] = number;
			str->sp_signal[i] = number;
			str->pull_signal[i] = number;
			str->time[i] = number;
		}

		//printf("Przypisalem %lf a chcialem %lf drugie przypisanie %lf a chcialem %lf\n", 
		//	str->test, number, str->test_2,number_2);

		return 0;
	}
}


data_struct DATA_STR_copy(const data_struct* original_str)
{

		int i;
		data_struct* new_str; //= (data_struct*)malloc(sizeof(data_struct));

		if (original_str == NULL) {
			new_str = DATA_STR_create(0);
		}
		else {
			new_str = DATA_STR_create(original_str->signals_len);

			for (i = 0; i < new_str->signals_len; i++)
			{
				new_str->input_signal_1[i] = original_str->input_signal_1[i];
				new_str->input_signal_2[i] = original_str->input_signal_2[i];
				new_str->input_signal_3[i] = original_str->input_signal_3[i];
				new_str->output_signal[i] = original_str->output_signal[i];
				new_str->sp_signal[i] = original_str->sp_signal[i];
				new_str->pull_signal[i] = original_str->pull_signal[i];
				new_str->time[i] = original_str->time[i];
			}
		}

		return *new_str;

}


void DATA_STR_print(const data_struct* str)
{
	if (str!= NULL)
	{
		printf("Time:   Input 1:   Input 2:   Input 3:   Output:   SP:   Pull:   \n");

		for (int i = 0; i < str->signals_len; i++)
		{
			//printf("%d \n", str->signals_len);
			printf("%lf, %lf, %lf, %lf, %lf, %lf, %lf \n", str->time[i], str->input_signal_1[i],
				str->input_signal_2[i], str->input_signal_3[i], str->output_signal[i], str->sp_signal[i], str->pull_signal[i]);
		}
	}
}

void DATA_STR_print_short(const data_struct* str)
{
	if (str != NULL)
	{
		printf("Time:   Input 1:   Input 2:   Input 3:   Output:   SP:   Pull:   \n");

		printf("%lf, %lf, %lf, %lf, %lf, %lf, %lf  \n", str->time[0], str->input_signal_1[0],
			str->input_signal_2[0], str->input_signal_3[0], str->output_signal[0], str->sp_signal[0], str->pull_signal[0]);
		printf("..........................\n");
		printf("%lf, %lf, %lf, %lf, %lf, %lf, %lf  \n", str->time[str->signals_len - 1], str->input_signal_1[str->signals_len - 1],
			str->input_signal_2[str->signals_len - 1], str->input_signal_3[str->signals_len - 1], str->output_signal[str->signals_len - 1],
			str->sp_signal[str->signals_len - 1], str->pull_signal[str->signals_len - 1]);
	}
}


int DATA_STR_add_s1(data_struct* str, char* buff)
{
	if (buff == NULL) 
	{
		return -1;
	}
	else 
	{
		for (int i = 0; i < str->signals_len; i++) 
		{
			str->input_signal_1[i] = *((double*)buff+i);
		}

		return 0;
	}
}

int DATA_STR_add_s2(data_struct* str, char* buff)
{
	if (buff == NULL)
	{
		return -1;
	}
	else
	{
		for (int i = 0; i < str->signals_len; i++)
		{
			str->input_signal_2[i] = *((double*)buff + i);
		}

		return 0;
	}
}

int DATA_STR_add_s3(data_struct* str, char* buff)
{
	if (buff == NULL)
	{
		return -1;
	}
	else
	{
		for (int i = 0; i < str->signals_len; i++)
		{
			str->input_signal_3[i] = *((double*)buff + i);
		}

		return 0;
	}
}

int DATA_STR_add_output(data_struct* str, char* buff)
{
	if (buff == NULL)
	{
		return -1;
	}
	else
	{
		for (int i = 0; i < str->signals_len; i++)
		{
			str->output_signal[i] = *((double*)buff + i);
		}

		return 0;
	}
}

int DATA_STR_add_sp(data_struct* str, char* buff)
{
	if (buff == NULL)
	{
		return -1;
	}
	else
	{
		for (int i = 0; i < str->signals_len; i++)
		{
			str->sp_signal[i] = *((double*)buff + i);
		}

		return 0;
	}
}

int DATA_STR_add_pull(data_struct* str, char* buff)
{
	if (buff == NULL)
	{
		return -1;
	}
	else
	{
		for (int i = 0; i < str->signals_len; i++)
		{
			str->pull_signal[i] = *((double*)buff + i);
		}

		return 0;
	}
}

int DATA_STR_add_time(data_struct* str, char* buff)
{
	if (buff == NULL)
	{
		return -1;
	}
	else
	{
		for (int i = 0; i < str->signals_len; i++)
		{
			str->time[i] = *((double*)buff + i);
		}

		return 0;
	}
}


void DATA_STR_free(data_struct* str)
{
	free(str->input_signal_1);
	free(str->input_signal_2);
	free(str->input_signal_3);
	free(str->output_signal);
	free(str->sp_signal);
	free(str->pull_signal);
	free(str->time);

	free(str);
}
