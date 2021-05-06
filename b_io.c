#include "b_io.h"
#include "mfs.h"
int b_open (char * filename, int flags){// we open and establish a DE and file on our end

}
int b_read (int fd, char * buffer, int count){//read from an LBA into buffer, fd is a file on our end we get from b_open

}
int b_write (int fd, char * buffer, int count){// we read from the char buffer count bytes into our own fd

}
int b_seek (int fd, off_t offset, int whence){//I don't under wtf this is even for

}
void b_close (int fd){//close the file on our end

}



//NOTE cp or copy file command in fsshell makes a duplicate file in our fs