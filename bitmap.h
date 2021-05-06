#include "mfs.h"

typedef struct block
{
	unsigned char bytes[512];//128 int = 512 bytes
} block_t;
void initBitMap(int numBlocks,int pos);
int  allocate();
void deallocate(int BlockNeeded);