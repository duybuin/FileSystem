#include "rootdirectory.h"
#define blockSize 512

void initRoot(){
dir* dr;
dr = malloc(40);
strcpy(dr->filename,"dir_name");
int numberOfEntries=0;
if((void*)dr<=0){
    printf("failed to allocate memory");
    return -1;
}
printf("rootdirectory initialized\n");

int size;
size= sizeof(*dr);
 printf("size of struct: %d\n",size);



char *buf = malloc(blockSize);
memset(buf,0,blockSize);
for(int i=0;i<12;i++){
    memmove(buf+(i*40),dr,40);
}
LBAwrite(buf,1,6);
LBAwrite(buf,1,7);
}

//(numberOfEntries*sizeof(dir)/blockSize)