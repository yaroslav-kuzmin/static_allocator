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
#include <stdarg.h>

#include <allocator.h>

#define SUCCES     0
#define FAILURE   -1

#if NUMBER_BLOCK != 10 
#error  "Для теста установите NUMBER_BLOCK равное 10"
#endif
/*****************************************************************************/
void printf_erorr(char * str, ...)
{
	va_list arg;
	va_start(arg,str);
	printf("Error : ");
	vprintf(str, arg);
	printf("\n");
	va_end(arg);
}

int main(int argc, char * argv[])
{
	printf("Test test_main %d\n", NUMBER_BLOCK);

/*****************************************************************************/
	void * block[11] = {NULL};

	for (int i = 0; i < 11;++i) {
		block[i] = static_malloc();
	}
	if (block[10] != NULL) {
		printf_erorr("check fill pool");
		return FAILURE;
	}

/*****************************************************************************/
	void * block_7 = block[7];
	void * block_1 = block[1];
	static_free(block[7]);
	static_free(block[1]);
	block[7] = NULL;
	block[1] = NULL;
	
	block[7] = static_malloc();
	if (block_1 != block[7]) {
		printf_erorr("Check realloc 7");
		return FAILURE;
	}

	block[1] = static_malloc();
	if (block_7 != block[1]) {
		printf_erorr("Check realloc 1");
		return FAILURE;
	}

/*****************************************************************************/
	void * block_0 = block[0];

	for (int i=0; i< 10; ++i) {
		static_free(block[i]);
	}
	block[10] = static_malloc();  
	if (block_0 != block[10]) {
		printf_erorr("Check free");
		return FAILURE;
	}
/*****************************************************************************/
	printf("Done\n");
	return SUCCES;
}
/*****************************************************************************/
