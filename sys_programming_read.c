/********************************************************************************
 * This file is the second source code file for learning the `read` system call.*
 *                       Author :  Miss yangyaoqin                              *
 *                        Date  : September 21, 2026                            *
 ********************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
	char hello[100];
	ssize_t num = read(2, hello, 100);
	// write(1, hello, num);
	printf("num = %zd\n", num);
	printf("errno = %d\n", errno);
	return 0;
}

