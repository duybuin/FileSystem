#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include "fsLow.h"
#include "mfs.h"
#include "bitmap.h"

void initBitMap(int numBlocks,int pos){
    block_t *bit_map = (block_t *)calloc(1,512);
    for(int i = 0; i < 512; i++){
        if(i <1){
            //bit_map->bytes[i]=0;//first 8 blocks are taken by vcb,fsm, and dir so first 8 bits are 0
            //due to intel architecture int bytes are stored backwards so to account maybe use the line below?
            bit_map->bytes[i]=12;
        }
        else{
        bit_map->bytes[i]=255;
        }
    }
    LBAwrite(bit_map,1,pos);//first block write
    pos++;
    bit_map->bytes[0]=255;
   //For bitmap 1 = free block,0 = taken
    for(int i = 2; i < 6;i++){//next four
        LBAwrite(bit_map,1,pos);
        pos++;
    }
    free(bit_map);

    //test code
    int test[2];
    test[0]=0;
    test[1]=7;
    allocate(2) ;
    //deallocate(test);
}
//allocate returns a pointer to an array that contains the LBA's of the blocks needed
int * allocate(int BlocksNeeded){
    int FreeBlocks[BlocksNeeded];
    unsigned char byte,Temp;
     int pos=0;
    block_t *bit= (block_t *)calloc(1,512);

    printf("allocation startingd\n");//change this later

   
    for(int x=1;x<=5;x++){//this outer loop runs through LBA of 1-5 for the bit map, change hardcoding later?
        LBAread(bit,1,x);
        for(int y = 0; y < 512; y++){//runs through the 512 byte block
            byte=127 ;//in binary this is 1000 0000
            for (int z = 0; z < 8; z++){//runs through the bits of each byte
                Temp = bit->bytes[z] & byte;
                if (Temp == byte){//double check logic
                    //record lba
                    FreeBlocks[pos];
                    byte=~byte;// flips all bit
                    bit->bytes[z]=bit->bytes[z] & byte;//changes bit to zero
                    //if that bit is unavailable
                    byte=byte>>1;//need to shift the 1 bit over 1
                }
                pos++;//updates pos everytime
                //else do nothing
            }
        }
        LBAwrite(bit,1,x);//RECENTLY ADDED
    }
    printf("allocation finished\n");//change this later
    return FreeBlocks;

}

void deallocate(int BlocksNeeded[]){//parameters is am array of SORTED ints of the LBA needed to open up 
    int offset,CurrBlock,size;
    unsigned char byte;
    block_t *bit= (block_t *)calloc(1,512);
    CurrBlock=0;
    size = sizeof BlocksNeeded / sizeof *BlocksNeeded;//calc size of array
    LBAread(bit,1,CurrBlock);//loads first block
    for(int i = 0; i <size;i++){
        if(BlocksNeeded[i]<512){
            byte =1;//in binary this is 0000 0001
            if(BlocksNeeded[i]==0){//0%8=0
                offset=1;
            }
            else{
                offset= BlocksNeeded[i]%8;
            }
            byte=byte<<(8-offset);
            BlocksNeeded[i]=BlocksNeeded[i]|byte;
            LBAwrite(bit,1,1);//HARD CODED CHANGE
        }
        else{

        }
    }
  
        



    
 
   
            
    
}