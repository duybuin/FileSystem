
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include "fsLow.h"
#include "mfs.h"



typedef struct{
	char title[20];
    char header[20];
    uint64_t magicNumber;
    uint64_t VolSize;//Volume Size in bytes
    uint64_t NumBlocks;// Number of blocks in volume
    uint64_t BlockSize;
	uint64_t numberOfBlocks;
	uint64_t RootBlock;
	uint64_t FSBlock;//Free Space Block
}VCB;

void initVCB(char * filename,uint64_t volumeSize,uint64_t blockSize);
int numblocks(int VCBSize,int BlockSize);