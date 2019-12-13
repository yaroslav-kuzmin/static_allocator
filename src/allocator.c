/*****************************************************************************/
/*                                                                           */
/* allocator : Модуль блочного выделения памяти                              */
/*                                                                           */
/*  Copyright (C) 2019 Kuzmin Yaroslav <kuzmin.yaroslav@gmail.com>           */
/*                                                                           */
/* allocator is free software: you can redistribute it and/or modify it      */
/* under the terms of the GNU General Public License as published by the     */
/* Free Software Foundation, either version 3 of the License, or             */
/* (at your option) any later version.                                       */
/*                                                                           */
/* allocator is distributed in the hope that it will be useful, but          */
/* WITHOUT ANY WARRANTY; without even the implied warranty of                */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                      */
/* See the GNU General Public License for more details.                      */
/*                                                                           */
/* You should have received a copy of the GNU General Public License along   */
/* with this program.  If not, see <http://www.gnu.org/licenses/>.           */
/*                                                                           */
/*****************************************************************************/

#include <stdlib.h>

#include <allocator.h>

/*****************************************************************************/
#define SIZE_BLOCK_BYTE   (UINT32_C(0x00000001) << SIZE_BLOCK_POWER2)
#if (ADDRESS_BLOCK == 0)
static uint8_t shadow_array[SIZE_BLOCK_BYTE * NUMBER_BLOCK] = {0};
static uint8_t * array = shadow_array;
static uint8_t * free_block = shadow_array;
#else
static uint8_t * array = ADDRESS_BLOCK;
static uint8_t * free_block = ADDRESS_BLOCK;
#endif

static t_counter_block counter_occuped_block = 0;
static t_counter_block number_occuped_block = 0;
static t_counter_block number_free_block = NUMBER_BLOCK;

/*колличество бит в 4 байтах*/
#define NUMBER_BIT_POWER2  5
#define NUMBER_BIT         (UINT32_C(0x00000001)<< NUMBER_BIT_POWER2)

static uint32_t bitmap_occuped_block[NUMBER_BITMAP] = {0};
/*Установка бит в массиве битов указывает что блок занят*/
void occuped_bitmap(t_counter_block number)
{
	t_counter_block position = number >> NUMBER_BIT_POWER2;
	uint32_t mask = number - (position << NUMBER_BIT_POWER2);
	mask = UINT32_C(0x00000001) << mask;
	uint32_t *bitmap = bitmap_occuped_block + position;
	*bitmap |= mask;
}
/*Возврашает номер первого свободного блока  , если номер равен колличеству блоков то все блоки заняты*/
t_counter_block first_free_bitmap(t_counter_block number)
{
	t_counter_block free_number = number;
	t_counter_block position = number >> NUMBER_BIT_POWER2;
	t_counter_block bit_number = number - (position << NUMBER_BIT_POWER2);
	uint32_t * bitmap = bitmap_occuped_block + position;
	uint32_t bit = *bitmap;
	bit >>= bit_number;
	for(;position < NUMBER_BITMAP;) {
		for(;bit_number < NUMBER_BIT;++bit_number){
			if ((bit & 0x00000001) == 0) {
				return free_number;
			}
			++free_number;
			bit >>=1;
		}
		bit_number= 0;
		++position;
		++bitmap;
		bit = *(bitmap);
	}
	return free_number;
}
/*Снимает бит в массиве битов указывая что блок свободен*/
void free_bitmap(t_counter_block number)
{
	t_counter_block position = number >> NUMBER_BIT_POWER2;
	uint32_t mask = number - (position << NUMBER_BIT_POWER2);
	mask = UINT32_C(0x00000001) << mask;
	mask = ~mask;
	uint32_t * bitmap = bitmap_occuped_block + position;
	*bitmap &= mask;
}

/*возврашает указатель на свободный блок , если NULL все блоки заняты*/
void * static_malloc(void)
{
	void * block = NULL;
	OPEN_ATOMIC_BLOCK;
	if (counter_occuped_block != NUMBER_BLOCK) {
		block = free_block;
		free_block += SIZE_BLOCK_BYTE;
		occuped_bitmap(counter_occuped_block);
		++counter_occuped_block;
		++number_occuped_block;
	}
	else {
		if (number_occuped_block != NUMBER_BLOCK) {
			block = free_block;
			occuped_bitmap(number_free_block);
			++number_occuped_block;
			if (number_occuped_block != NUMBER_BLOCK) {
				number_free_block = first_free_bitmap(number_free_block);
				free_block = array + (SIZE_BLOCK_BYTE * number_free_block);
			}
			else {
				number_free_block = NUMBER_BLOCK;
				free_block = NULL;
			}
		}
	}

	CLOSE_ATOMIC_BLOCK;
	return block;
}
/*высвобождает блок*/
void static_free(void * block)
{
	OPEN_ATOMIC_BLOCK;
	void * begin_block = (void*)array;
	/*TODO проверка на некоррекный адрес*/
	t_counter_block number = block - begin_block;
	number = number >> SIZE_BLOCK_POWER2;
	free_bitmap(number);
	--number_occuped_block;
	if (number_occuped_block == 0) {
		counter_occuped_block = 0;
		number_free_block = NUMBER_BLOCK;
		free_block = array;
	}
	else {
		if (number_free_block > number) {
			number_free_block = number;
			if (counter_occuped_block == NUMBER_BLOCK) {
				free_block = array + (SIZE_BLOCK_BYTE * number);
			}
		}
	}
	CLOSE_ATOMIC_BLOCK;
}
/*****************************************************************************/
