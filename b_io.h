/**************************************************************
* Class:  CSC-415-0# 
* Name:
* Student ID:
* Project: File System Project
*
* File: b_io.h
*
* Description: Interface of basic I/O functions
*
**************************************************************/

#ifndef _B_IO_H
#define _B_IO_H
#include <fcntl.h>

int b_open (char * filename, int flags);// we open and establish a DE and file on our end
int b_read (int fd, char * buffer, int count);//read from an LBA into buffer, fd is a file on our end we get from b_open
int b_write (int fd, char * buffer, int count);// we read from the char buffer count bytes into our own fd
int b_seek (int fd, off_t offset, int whence);//
void b_close (int fd);//close the file on our end

#endif

/*
INFO on off_t data type in seek
https://www.gnu.org/software/libc/manual/html_node/File-Position-Primitive.html


source for what lseek() does and what seek should try and replicate(?)
https://users.pja.edu.pl/~jms/qnx/help/watcom/clibref/src/lseek.html
*/