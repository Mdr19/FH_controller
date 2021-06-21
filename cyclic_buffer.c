# include <stdlib.h>
# include <stdio.h>

#include "cyclic_buffer.h"
#include "data_struct.h"

//extern void free_data_struct(data_struct*);


cyclic_buffer* BUFF_create(int max_buff_size)
{
	cyclic_buffer* buff = malloc(sizeof(cyclic_buffer));

	if (buff == NULL)
	{
		printf("Cyclic buffer cannot be created\n");
		return NULL;
	}
	else
	{
		printf("Cyclic buffer created\n");
		buff->tail = 0;
		buff->head = 0;
		buff->size = 0;
		buff->capacity = max_buffer_size;
		//buff->signals_len = signals_len;
		buff->data = (data_struct*)malloc(buff->capacity * sizeof(data_struct));

		/*
		for (int i = 0; i < buff->capacity; i++)
		{
			buff->data[i]= create_data_struct(buff->signals_len);
			//create_data_struct(buff->data);
		}
		*/
	

		return buff;
	}
}

int BUFF_empty(cyclic_buffer* buff)
{
	if (buff == NULL) {
		return -1;
	}
	else if(buff->size==0){
		return 1;
	}else{
		return 0;
	}
}

int BUFF_full(cyclic_buffer* buff)
{
	if (buff == NULL) {
		return -1;
	}
	else if (buff->size == buff->capacity) {
		return 1;
	}
	else {
		return 0;
	}
}


int BUFF_add(cyclic_buffer* buff, const data_struct* str)
{

	if (buff == NULL) {
		return -1;
	}
	else {

		if (buff->size >= buff->capacity)
		{
			buff->head = (buff->head + 1) % buff->capacity;
		}

		buff->data[buff->tail]= DATA_STR_copy(str);
		buff->tail = (buff->tail + 1) % buff->capacity;

		if (buff->size < buff->capacity)
		{
			buff->size = buff->size + 1;
		}

		return 0;
	}
}

void BUFF_display(const cyclic_buffer* buff)
{
	if (buff == NULL) 
	{
		printf("Buffer empty \n");
	}
	else 
	{
		printf("Buffer elements: %d \n", buff->size);
		printf("Buffer HEAD: %d \n", buff->head);
		printf("Buffer TAIL: %d \n", buff->tail);

		for (int i = 0; i < buff->size; i++)
		{
			DATA_STR_print(buff->data + (buff->head + i) % buff->capacity);
			//DATA_STR_print(&buff->data[buff->head]);
		}
	}
}

void BUFF_display_short(const cyclic_buffer* buff)
{
	if (buff == NULL)
	{
		printf("Buffer empty \n");
	}
	else
	{
		printf("\n");
		printf("************************************************\n");
		printf("************************************************\n");
		printf("Buffer elements: %d \n", buff->size);
		printf("Buffer HEAD: %d \n", buff->head);
		printf("Buffer TAIL: %d \n", buff->tail);
		printf("Buffer capacity: %d \n", buff->capacity);


		for (int i = 0; i < buff->size; i++)
		{
			printf("************************************************\n");
			printf("ELEMENT %d POS %d \n", i+1, (buff->head + i) % buff->capacity);
			DATA_STR_print_short(buff->data + (buff->head + i) % buff->capacity);
		}
	}
}

void BUFF_display_vshort(const cyclic_buffer* buff)
{
	if (buff == NULL)
	{
		printf("Buffer empty \n");
	}
	else
	{
		printf("\n");
		printf("************************************************\n");
		printf("************************************************\n");
		printf("Buffer elements: %d \n", buff->size);
		printf("Buffer HEAD: %d \n", buff->head);
		printf("Buffer TAIL: %d \n", buff->tail);
	}
}



void BUFF_free(cyclic_buffer* buff) 
{
	unsigned int i = buff->size;

	while (buff->size - i !=NULL) {
		DATA_STR_free(buff->data + i);
		i--;
	}
}


