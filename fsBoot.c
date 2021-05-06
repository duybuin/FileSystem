#include "fsBoot.h"
int fsBoot(int argc, char *argv[]){
    char * filename;
	uint64_t volumeSize;
	uint64_t blockSize;
    int retVal;
    
	if (argc > 3)
		{
		filename = argv[1];
		volumeSize = atoll (argv[2]);
		blockSize = atoll (argv[3]);
		}
	else
		{
		printf ("Usage: fsLowDriver volumeFileName volumeSize blockSize\n");
		return -1;
		}
    //Might need to use magic number around here 
	retVal = startPartitionSystem (filename, &volumeSize, &blockSize);	
	printf("Opened %s, Volume Size: %llu;  BlockSize: %llu; Return %d\n", filename, (ull_t)volumeSize, (ull_t)blockSize, retVal);
	VCB* vcb;
    vcb = calloc( (numblocks(sizeof(VCB),blockSize)) , ((numblocks(sizeof(VCB),blockSize))*blockSize) );
    initVCB(filename,volumeSize,blockSize);

	initBitMap(5,1);
	printf("init Bit Map successfully!\n");
	
	  
// printf(buf);
// if(buf!=NULL){
//     return -1;
// }


	initRoot();
	
	//currentPath ="/root";
	return 0;
	//helloworld
	
}