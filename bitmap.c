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
            bit_map->bytes[i]=1;
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
    
}
//NOTE currently allocate and dellocate either recieve or return arrays with the LBA's but should change to single int's
//Also a lot of values are hard coded and need to be changed
//allocate returns a pointer to an array that contains the LBA's of the blocks needed
int allocate(){
    unsigned char byte,Temp,CurrentByte;
    int LBA=0;
    block_t *bit= (block_t *)calloc(1,512);
    int STATE=0;
    printf("allocation startingd\n");//change this later

for(int x = 1; x <=5; x++){//NOTE MAYBE FOR FIRST ARRAY ENTRY MAKE THAT THE SIZE
    LBAread(bit,1,x);//read through each block of the bit map
     for(int i = 0; i<512;i++){
        //printf("byte %d:%hhx\n",i,bit->bytes[i]);
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
                //printf("byte:%hhx ",byte);
                byte = ~byte;//flip bits in order to make change to currentByte, check if this how it works
                CurrentByte = CurrentByte & byte;
                //printf("byte:%hhx temp:%hhx\n",byte,Temp);
               // printf("bit changes:%d \n",NumBitChanges);
                z = 8;//these are hardcoded change later
                STATE=1;//WE CHANGED THE BYTE TIME TO EXIT OIT OF LOOP
            }
            byte=byte>>1;// shift the 1 in bytes right 1 unit
            LBA++;//update logical block address
        }
        
        //printf("%d written to bit %hhx\n",y,bit->bytes[y]);
        bit->bytes[y] = CurrentByte;//sets the current byte at position Y to the result of currentByte
        //printf("%d written to bit %hhx\n",y,bit->bytes[y]);
        if(STATE==1){// this if statement checks if we've found enough open blocks and if so will set for loop values so that we exit in this iteration
            y = 512;
        }
        
    }
    //printf("Current byte:%hhx\n",CurrentByte);
    LBAwrite(bit,1,x);// writes the new reulting block of the bitmap
    //printf("written to disk\n");
    for(int i = 0; i<512;i++){
        //printf("byte %d:%hhx\n",i,bit->bytes[i]);
    }
    if(STATE==1){// this if statement checks if we've found enough open blocks and if so will set for loop values so that we exit in this iteration
        x = 6;
    }
}

    printf("allocation finished\n");//change this later
    printf("Avail Block:%d\n",LBA);
    return LBA-1;//is the -1 correct?

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
void deallocate(int BlockNeeded){//parameters is am array of SORTED ints of the LBA needed to open up 
    int offset,CurrByte;
    unsigned char byte;
    block_t *bit= (block_t *)calloc(1,512);     
    CurrByte=0;
    unsigned char ByteVal;//,offset;
    offset = 128;                                                                                                                                                                   
    int currentBlock=1+(BlockNeeded/4096);//hardcoded change later
    printf("block loaded:%d\n",currentBlock);
    LBAread(bit,1,currentBlock);//increment by 1 since bitmap starts at LBA 1
 

    CurrByte = (BlockNeeded % 4096) / 8;//finds the needed byte
    offset = offset >> ( ( BlockNeeded % 4096  ) % 8);
    printf("byte :%d    offset:%d\n",CurrByte,offset);
    ByteVal = bit->bytes[CurrByte];
    printf("updated byte :%d\n",bit->bytes[CurrByte]);
    bit->bytes[CurrByte]= ByteVal | offset;
    printf("updated byte :%d\n",bit->bytes[CurrByte]);
    LBAwrite(bit,1,currentBlock);
    //USED TO TAKE ARRAY AND DELOCATE ALL BLOCKS BASED ON lba but now we just revieve a single lba so logic needs to change                             
}