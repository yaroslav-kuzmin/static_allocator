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
#include <stdio.h>

#include <allocator.h>
/*****************************************************************************/

#define NUMBER_BIT    (sizeof(uint32_t) * 8)
#define SIZE_BITMAP   ((SIZE_BLOCK / NUMBER_BIT) + 1) 
void occuped_bitmap(t_counter_block number);
t_counter_block first_free_bitmap(t_counter_block number);
void free_bitmap(t_counter_block  number);
#if NUMBER_BLOCK != 100 
#error  "Для теста установите NUMBER_BLOCK равное 100"
#endif
int main(int argc, char * argv[])
{
	printf("Test bitmap : %ld\n", SIZE_BITMAP);
	if (NUMBER_BLOCK != 100) {
		printf("Для теста установите количество блоков равное 100!!\n");
		return 1;
	}
/*****************************************************************************/
	t_counter_block number = 0;
	occuped_bitmap(number);
	number = first_free_bitmap(number);
	if (number != 1) {
		printf("Erorr : Check number 1 : %d\n", number);
		return 1;
	}
/*****************************************************************************/
	number = 1;
	occuped_bitmap(number);
	number = first_free_bitmap(number);
	if (number != 2) {
		printf("Erorr : Check number 2 : %d\n", number);
		return 1;
	}
/*****************************************************************************/
	number = 2;
	occuped_bitmap(number);
	number = 3;
	occuped_bitmap(number);
	number = 4;
	occuped_bitmap(number);
	number = 5;
	occuped_bitmap(number);
	number = 6;
	occuped_bitmap(number);
	number = 7;
	occuped_bitmap(number);
	number = 8;
	occuped_bitmap(number);
	number = 9;
	occuped_bitmap(number);

	number = 7;
	free_bitmap(number);

	number = first_free_bitmap(number);
	if (number != 7) {
		printf("Error : Check number 7 : %d\n", number);
		return 1;
	}
/*****************************************************************************/
	for(number=0; number < 100;++number) {
		occuped_bitmap(number);
	}
	number = 77;
	free_bitmap(number);
	number = 48;
	free_bitmap(number);
	number = 35;
	free_bitmap(number);
	number = 90;
	free_bitmap(number);
	number = 20;
	number = first_free_bitmap(number);
	if (number != 35) {
		printf("Error : Check number 35 : %d\n", number);
		return 1;
	}
/*****************************************************************************/
	printf("Done\n");
	return 0;
}
/*****************************************************************************/
