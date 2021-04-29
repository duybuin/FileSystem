#include "VCB.h"

void initVCB(char * filename,uint64_t volumeSize,uint64_t blockSize){
    VCB* vcb;
    int MAGICNUMBER = 314156;
    int NumBlocksVCB= numblocks(sizeof(VCB),blockSize);
    vcb = calloc(NumBlocksVCB,NumBlocksVCB*blockSize);//is this the right system call? first arguemnet is how many instances were creating
    strcpy(vcb->header,"Volume Control Block");
    strcpy(vcb->title,filename);
    vcb->magicNumber=MAGICNUMBER;
    vcb->VolSize = volumeSize;
    vcb->BlockSize = blockSize;
    vcb->FSBlock=1;
    vcb->RootBlock=6;//change these so they are not hard coded
    LBAwrite(vcb,NumBlocksVCB,0);

//test code
char* buf2 = malloc(blockSize);
memset(buf2, 0, blockSize);
VCB* vcb2;
vcb = calloc(NumBlocksVCB,NumBlocksVCB*blockSize);

LBAread(buf2,1,0);
vcb2=(struct VCB*)buf2;
printf("magic number %ld\n",vcb2->magicNumber);

}
int numblocks(int VCBSize,int BlockSize){
    uint64_t NumBlks= VCBSize/BlockSize;
    if(VCBSize%BlockSize!=0){
        NumBlks+=1;
    }
    return NumBlks;

}

