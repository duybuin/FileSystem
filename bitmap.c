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
            bit_map->bytes[i]=255;
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
//NOTE currently allocate and dellocate either recieve or return arrays with the LBA's but should change to single int's
//Also a lot of values are hard coded and need to be changed
//allocate returns a pointer to an array that contains the LBA's of the blocks needed
int * allocate(int BlocksNeeded){
    int FreeBlocks[BlocksNeeded];
    unsigned char byte,Temp,CurrentByte;
    int FBpos=0;
    int LBA=0;
    int NumBitChanges=0;
    block_t *bit= (block_t *)calloc(1,512);

    printf("allocation startingd\n");//change this later

for(int x = 1; x <=5; x++){
    LBAread(bit,1,x);//read through each block of the bit map
     for(int i = 0; i<512;i++){
        printf("byte %d:%hhx\n",i,bit->bytes[i]);
    }
    for(int y = 0; y < 512; y++){
        byte = 128;//byte holds the bit we are currently looking at so starting off in first position in binary this is 1000 0000
        CurrentByte = bit->bytes[y];// holds the current byte we are looking through
        for(int z = 0; z < 8; z++){// going through each bit
            Temp = CurrentByte & byte;// temp holds the result if the byte is free
            // COMMENTED PRINTF'S ARE FOR DEBUGGING
            //printf("\n");
            // printf("byte#:%d bit#:%d \n",y,z);
            // printf("byte:%hhx temp:%hhx\n",byte,Temp);
            // printf("bit changes:%d \n",NumBitChanges);
            if (byte == Temp){//this if statement checks if temp is holding a freebyte
                FreeBlocks[FBpos]=LBA;//if so record the LBA
                FBpos++;//update array pos
                //printf("byte:%hhx ",byte);
                byte = ~byte;//flip bits in order to make change to currentByte, check if this how it works
                CurrentByte = CurrentByte & byte;
                byte = ~byte;//flip bytes back in order to continue checking
                //printf("byte:%hhx temp:%hhx\n",byte,Temp);
                NumBitChanges++;//updates the number of open blocks we've found and bits we've changed
               // printf("bit changes:%d \n",NumBitChanges);
                if(NumBitChanges >= BlocksNeeded){// this if statement checks if we've found enough open blocks and if so will set for loop values so that we exit in this iteration
                    z = 8;//these are hardcoded change later
                }
            }
            byte=byte>>1;// shift the 1 in bytes right 1 unit
            LBA++;//update logical block address
        }
        
        //printf("%d written to bit %hhx\n",y,bit->bytes[y]);
        bit->bytes[y] = CurrentByte;//sets the current byte at position Y to the result of currentByte
        //printf("%d written to bit %hhx\n",y,bit->bytes[y]);
        if(NumBitChanges >= BlocksNeeded){// this if statement checks if we've found enough open blocks and if so will set for loop values so that we exit in this iteration
            y = 512;
        }
        
    }
    //printf("Current byte:%hhx\n",CurrentByte);
    LBAwrite(bit,1,x);// writes the new reulting block of the bitmap
    //printf("written to disk\n");
    for(int i = 0; i<512;i++){
        //printf("byte %d:%hhx\n",i,bit->bytes[i]);
    }
    if(NumBitChanges >= BlocksNeeded){// this if statement checks if we've found enough open blocks and if so will set for loop values so that we exit in this iteration
        x = 6;
    }
}
    for(int i = 0; i<BlocksNeeded;i++){
        //printf("fb:%d\n",FreeBlocks[i]);
    }
    printf("allocation finished\n");//change this later
    return FreeBlocks;

}
/* this was the first attempt, had some logical errors
    for(int x=1;x<=5;x++){//this outer loop runs through LBA of 1-5 for the bit map, change hardcoding later?
        LBAread(bit,1,x);
        for(int y = 0; y < 512; y++){//runs through the 512 byte block
            byte=127 ;//in binary this is 1000 0000
            for (int z = 0; z < 8; z++){//runs through the bits of each byte
                byte=127 ;//in binary this is 1000 0000
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
*/
void deallocate(int BlocksNeeded[]){//parameters is am array of SORTED ints of the LBA needed to open up 
    int offset,CurrBlock,CurrByte;
    unsigned char byte;
    block_t *bit= (block_t *)calloc(1,512);
    CurrBlock=0;     
    CurrByte=0;
    unsigned char ByteVal,offset;
    offset = 128;                                                                                                                                                                   
    int currentBlock=0;//hardcoded change later
    for( int i =0; i < (sizeof BlocksNeeded / sizeof *BlocksNeeded); i++){
        if((BlocksNeeded[i]/4096)>CurrBlock){
            LBAread(bit,1,CurrBlock + 1);//increment by 1 since bitmap starts at LBA 1
        }
        CurrByte = (BlocksNeeded[i] % 4096) / 8;//finds the needed byte
        offset = offset >> ( ( BlocksNeeded[i] % 4096  ) % 8);
        ByteVal = bit->bytes[CurrByte];
        bit->bytes[CurrByte]= ByteVal | offset;
         
    }
                                   
}