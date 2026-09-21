/*****************************************************************
 * This file is the first source code file for sys programming . *
 *              Author : Miss yangyaoqin                         *
 *               Date  : September 19 , 2026                     *
 *****************************************************************/ 

#include <unistd.h>
#include <string.h>

int main(void) {
	char *hello = "Hello , system programming .\n\n";
	
       /*
	do {
		write(1, hello, sizeof(*hello));
		hello = hello + 1 ;
	} while(*hello != '\n');

        * 这段代码本来是第一版的系统编程的"Hello World"的主干，但是这里面有些细节值得认真考虑：
	* 
	* 对于sizeof()，这个是C语言的运算符（operator），其本质是：让编译器计算某个类型或表达式在存储空间中所占的大小。
	* 同时，经过运算符计算的内容将在编译期得到确定。
	* 
	* 对与上面的代码，应当注意sizeof(hello)和sizeof(*hello)的区别：
	* sizeof(hello)是计算指针char *hello的大小，在x86_64架构的Fedora GNU/Linux下得到字符串指针的大小是8个字节。
	* 而对于sizeof(*hello)，计算的是对指针解引用后的结果，这里面指针指向字符串的第一个字符，并通过第一个字符的寻址从而找到整个字符串；
	* 但是指针指向的是第一个字符，因此sizeof(*hello)的结果是1个字节。也就是：
	* `sizeof(hello)   == 8 ; sizeof(*hello)  == 1`
	*
	* 另外，关于字节：
	* 在C语言中，一个 char 对象就是一个 byte。
	* 也就是，C 规定一个 char 是一个 byte；但一个人类意义上的字符，可以由一个或多个 byte 表示。
	*
	* 回到代码整体：
	*
	* `do {} while();`的逻辑是：先无条件执行一次循环体，再判断条件，如果条件是真，那么就继续执行；条件的是假，就终止。
	* 
	* 这里代码先向终端标准输出一个字符后，指针偏移寻址下一个字符，然后判断条件*hello != '\n'是否为真，然后选择终止或继续。
	*
	* 很明显这里，是指针一直寻址，直到取到字符'\n'，也就是刚拿到'\n'，马上做了判断*hello != '\n'为假，终止循环。
	* 也就是输出是这样的：
	* yangyaoqin@fedora:~/sys_programming$ gcc hello.c -o hello
	* yangyaoqin@fedora:~/sys_programming$ ./hello
	* Hello , system programming .yangyaoqin@fedora:~/sys_programming$
	*
	*/

	write(2, hello, strlen(hello));
	/*
	 * 关于系统调用函数write()的定义和头文件可以在终端输入
	 * `man 2 write`
	 * 以查阅系统调用关于write()的定义和用法，但是系统调用的技术文档只是说明了基础的定义和用法，但是值得强调的是：
	 * 
	 * 文件描述符(fd)
	 * 文件描述符（File Descriptor，简称 fd）是计算机 UNIX 和类 UNIX 系统中，内核为了高效管理已被打开的文件或其他输入输出资源而创建的非负整数索引。
	 * 
	 * 核心概念
	 * 1）核心概念本质是索引：它对应着内核中每个进程维护的文件描述符表的下标。
	 * 2）一切皆文件：在 Linux 系统中，无论是普通文件、目录、设备、管道还是网络套接字（Socket），进程进行读写等 I/O 操作时，都通过文件描述符来进行。
	 * 3）生命周期：当进程打开现有文件或创建新文件时，内核向进程返回一个文件描述符；当关闭文件时，该描述符被释放。
	 * 
	 * 默认的标准文件描述符
	 * 系统启动或进程运行时，默认会打开三个特殊的文件描述符：
	 * 1）0（标准输入，STDIN_FILENO）：通常对应键盘输入。
	 * 2）1（标准输出，STDOUT_FILENO）：通常对应屏幕输出。
	 * 3）2（标准错误，STDERR_FILENO）：通常对应错误信息输出到屏幕。
	 *
	 * 但是，在这里，一个具体的shell环境下，0、1、2作为fd去进行系统调用都是可以的，也就是说，
	 * write(fd, hello, strlen(hello));
	 * 这个语句里，无论是fd = 0、1、2，都有可能有输出打印到终端屏幕，这个行为取决于具体的shell环境。
	 *
	 * 但是按照约定，0、1、2分别负担这不同的意义，也就是以后使用到shell命令的重定向功能，
	 * 比如`./hello > hello.txt`或者`./hello 2> hello.txt`时，fd约定的意义会重新显影。
	 * 如果fd = 1，那么`./hello > hello.txt`和`./hello 2> hello.txt`的结果会完全不同，这里面`./hello > hello.txt`的输出会被选择重定向写入hello.txt；
	 * 但是`./hello 2> hello.txt`中的`2>`将完全过滤掉fd = 1的输出，也就是说，在`./hello 2> hello.txt`时，hello.txt不会有任何的写入。
	 */

	return 0;
}
