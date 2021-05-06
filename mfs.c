#include "mfs.h"
#define blockSize 512
char* defaultDirName= "empty DE";

int initRoot(){
fdDir* dr;
int size;
size= sizeof(*dr);
dr = malloc(size);
strcpy(dr->name,"");
int numberOfEntries=0;
if((void*)dr<=0){
    printf("failed to allocate memory");
    return -1;
}
printf("rootdirectory initialized\n");


 printf("size of struct: %d\n",size);



 char *buf = malloc(blockSize);

printf("F....../n");
memset(buf,0,blockSize);
for(int i=0;i<(blockSize/size);i++){
    
 if(i==0){
        strcpy(dr->name,"A");
        memmove(buf+(i*size),dr,size);
    }else if(i==1){
        strcpy(dr->name,"BC");
        memmove(buf+(i*size),dr,size);
    }else if(i>1){
        strcpy(dr->name,defaultDirName);
    
    printf("%s\n",dr->name);
    dr->d_reclen=48;
    dr->dirEntryPosition=i;
    dr->directoryStartLocation=6;
    strcpy(dr->name,defaultDirName);
    dr->type=0;
    dr->numBytes=512;
  memmove(buf+(i*size),dr,size);
    strcpy(CurrentDir,"/root");//CHANGE LATER SO WE DONT INIT THIS EVERY TIME
}
}
LBAwrite(buf,1,6);

free(buf);
return 1;
}

int fs_mkdir(const char *pathname, mode_t mode){
    printf("Running mkdir\n");
    //dirLBA();//remove later, this for testing
    fdDir* DE;
    int size;
    size= sizeof(*DE);
    DE = malloc(size);
    char *buf = malloc(blockSize);

    memset(buf,0,blockSize);//sets every byte in buf to 0 makeing sure there is no garabage data
    int pos;
    LBAread(buf,1,6);//HARDCODED to only read root dir for testing, CHANGE LATER
    
    //checks to see if dir already exists
    //loop through entries before adding directory to make sure theres no dupliates
    for(int i=2;i<(blockSize/size);i++){
        memmove(DE,buf+(size*i),size);
    if(strcmp(DE->name,pathname)==0){
        printf("\ndirectory name in this parent directory already exists please choose another name!\n");
        return 1;
    }
    }
    for(int i=2;i<(blockSize/size);i++){
        memmove(DE,buf+(size*i),size);
        if(DE->type==0){
            DE->type=2;//PROBABLY NEED TO FILL IN  MORE FIELDS
            pos=i;
            i=10;
         memset(DE->name,0,20);//clears out garbage data IMPORTANT!
         strcpy(DE->name,pathname); 
   
    memcpy(buf+(size*pos),DE,size);
    LBAwrite(buf,1,6);
    printf("1 placeholder\n ");
    DE->directoryStartLocation=allocate();
    printf("2 placeholder\n");
    initBlk(DE->directoryStartLocation);
    printf("3 placeholder \n");
    
    free(buf);
    free(DE);
    }

    }
    /*
    LBAread(buf,1,6);
    for (int i =0;i<10;i++){
    memmove(DE,buf+(size*i),size);
    printf("Name:%s    ",DE->name);
    printf("Length:%d   ",DE->d_reclen);
    printf("Position:%d    ",DE->dirEntryPosition);
    printf("LBA:%d    ",DE->directoryStartLocation);
    printf("Type:%d    ",DE->type);
    printf("Number of Bytes:%d\n",DE->numBytes);
    }
    */
}

fdDir * fs_opendir(const char *name){//Used for command ls to open a stream to dir and return a dir ptr

}
struct fs_diriteminfo *fs_readdir(fdDir *dirp){//used in display file func in fsshell and that function is also call by ls. Similar to str_tokR

}
int fs_closedir(fdDir *dirp){//used in display files assuming to close the strea

}

char * fs_getcwd(char *buf, size_t size){//return current array

}
int fs_setcwd(char *buf){//linux chdir
    //the way our dir is setup the global array 
}
int fs_isFile(char * path){//return 1 if file, 0 otherwise
    //Probably needs to be changed but assuming path is the file name and were searching in the current level of the directory
    //also this is set up assuming a dir is one block long which wont be the case most of the time so need to set up logic for 
    //the end cap of the dir block that points to the next block
    //this state of incomplete logic is the case for both isdir and isfile
    fdDir* DE;
    int size;
    size= sizeof(*DE);
    char* buf = malloc(blockSize);
    DE = malloc(size);
    memset(buf,0,blockSize);//sets every byte in buf to 0 makeing sure there is no garabage data
    LBAread(buf,1,6);//hard coded change later
    for(int i=0; i < 10; i++){
        memmove(DE,buf+(size*i),size);
        if(strcmp(DE->name,path)==0){
            if(DE->type == 0){
                return 0;
            }
            else if(DE->type == 1){
                return 1;
            }
        }
    }
    
}
int fs_isDir(char * path){//return 1 if directory, 0 otherwise
    fdDir* DE;
    int size;
    size= sizeof(*DE);
    char* buf = malloc(blockSize);
    DE = malloc(size);
    memset(buf,0,blockSize);//sets every byte in buf to 0 makeing sure there is no garabage data
    LBAread(buf,1,6);//hard coded change later
    for(int i=0; i < 10; i++){//EQUALS IS ZERO
        memmove(DE,buf+(size*i),size);
        if(DE->name==path){
            if(strcmp(DE->name,path)==0){
                return 1;
            }
            else if(DE->type == 1){
                return 0;
            }
        }
    }
}



int fs_delete(char* filename){	//removes a file
}

void initBlk(int x){
fdDir* dr;
int size;
size= sizeof(*dr);
dr = malloc(size);
strcpy(dr->name,"");
int numberOfEntries=0;
if((void*)dr<=0){
  
    return -1;
}
char *buf = malloc(blockSize);
memset(buf,0,blockSize);
for(int i=0;i<(blockSize/size);i++){
    if(i==0){
        strcpy(dr->name,".");
    }else if(i==1){
        strcpy(dr->name,"..");
    }else{
        strcpy(dr->name,"A");
    }
    printf("%s",dr->name);
    dr->d_reclen=48;
    dr->dirEntryPosition=i;
    dr->directoryStartLocation=6;
    //strcpy(dr->name, pathname);
    dr->type=0;
    dr->numBytes=512;
    memmove(buf+(i*size),dr,size);
}
LBAwrite(buf,1,x);

free(buf);
}


int fs_rmdir(const char *pathname){
fdDir* dr;

int pos;
int size = sizeof(*dr);
dr=malloc(size);

char *buf = malloc(blockSize);
memset(buf,0,blockSize);

LBAread(buf,1,6);//hard coded change later,also add deallocate
    

//this part of code below throws core dump idk why?
//navigate to parent
     

//remove in parent

printf("F: %c - %d\n",buf,size);

for(int i=2;i<10;i++){
    printf("does this run? 7\n");
    memmove(dr,buf+(size*i),size);
    printf("does this run?%s 8\n",pathname);
    printf("does this run?%s 8\n",dr->name);

   if(strcmp(dr->name,pathname)==0 && dr->type == 2){
        pos=i;
        printf("strcmp: %d\n",strcmp(dr->name,pathname));
        printf("does this fucking run?\n");
        //strcpy(dr->name,defaultDirName);//sets fields to default
        dr->type=0;//sets default to default
        memset(dr->name,0,20);
        strcpy(dr->name,defaultDirName);
        printf("%s: = buffwerrr\n",buf);
        //printf("buf:%d  pos:%d  dr:%d   size:%d\n", sizeof(*buf),pos,sizeof(*dr),size);
        memcpy(buf+(sizeof(*dr)*pos),dr,sizeof(*dr));  
        printf("%s: = new buffer\n",buf);
        printf("does this run?%s 10\n",pathname);
        LBAwrite(buf,1,6);//writes to actual desired directory being deleted and sets all bytes to 0      dr->directoryStartLocation
        i=10;
        //other remove logic
        // deallocate(/*block assigned to directory(LBA address)*/);//dellocate doesnt work yet, needs some small tweaks
        //leaves garbage data in root directory needs fixing
        printf("\ndirectory successfully removed\n");
        return 1;
  } 
 }
free(buf);
printf("no directory named %d to delete!\n",pathname);
return 0;
}


int dirLBA(){
    /*
    Global array CurrentDir holds the absolute path of the currect directory you are currently in, ex /root/dirA/dirB
    This array cycles through the array using "\" as a delimeter until the very end and returns the LBA of the current directory, example LBA of dirB
    */
    int LBA;
    fdDir* DE;
    int size;
    size= sizeof(*DE);
    DE = malloc(size);
    char *buf = malloc(blockSize);
    memset(buf,0,blockSize);
    int pos;
    int CurrBlk=6;
    //THE CRUX AND POSSIBLE REASON WHY AN INODE MAP MIGHT BE NEEDED IS BECAUSE THIS SEARCHES EVERY DIRECTORY TO THE BOTTOM DEPTH TO FIND THE LBA OF THE NEEDED DIRECTORY SO IT HAS TO 
    //LBA READ MULTIPLE TIMES WHICH IS INNEFFICIENT
    //Note as of now this entire functions assumes each dir is only 1 block long will need to change logic to determine how many blocks in the current dir that is being searched
    // Extract the first token
    char * token = strtok(CurrentDir, "\\");//delimeter is "\""
    while( token != NULL ) {
    LBAread(buf,1,CurrBlk);//HARDCODED CHANGE LATER
      printf( "searching directory %s\n", token ); //printing each token
      for(int i=0;i<10;i++){
        memmove(DE,buf+(size*i),size);
        if(DE->name==token){
            CurrBlk=DE->directoryStartLocation;
            i=10;//exits from for loop
        }    
    }
      token = strtok(NULL, " ");

   }
   return LBA;
    //FINISH TOMORROW
}
