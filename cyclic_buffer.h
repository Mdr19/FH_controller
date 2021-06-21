#pragma once

# include "data_struct.h"
//const int intervals_number = 10;
#define max_buffer_size 10

typedef struct cyclic_buffer cyclic_buffer;

struct cyclic_buffer {
	unsigned int tail;
	unsigned int head;
	unsigned int size;
	unsigned int capacity;
	data_struct *data;
};

cyclic_buffer* BUFF_create(int max_buff_size);
void BUFF_free(cyclic_buffer* buff);
int BUFF_empty(cyclic_buffer* buff);
int BUFF_full(cyclic_buffer* buff);
int BUFF_add(cyclic_buffer* buff, const data_struct* str);
void BUFF_display(const cyclic_buffer* buff);
void BUFF_display_short(const cyclic_buffer* buff);
void BUFF_display_vshort(const cyclic_buffer* buff);

