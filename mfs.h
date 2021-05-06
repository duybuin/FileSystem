/**************************************************************
* Class:  CSC-415
* Name: Professor Bierman
* Student ID: N/A
* Project: Basic File System
*
* File: fsLow.h
*
* Description: 
*	This is the file system interface.
*	This is the interface needed by the driver to interact with
*	your filesystem.
*
**************************************************************/
#ifndef _MFS_H
#define _MFS_H
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#include "b_io.h"

#include <dirent.h>
#define FT_REGFILE	DT_REG
#define FT_DIRECTORY DT_DIR
#define FT_LINK	DT_LNK

#ifndef uint64_t
typedef u_int64_t uint64_t;
#endif
#ifndef uint32_t
typedef u_int32_t uint32_t;
#endif



#define FILENAME_SIZE 20

/*				TO DO: 
1)IMPLEMENT MOVE FILE COMMAND IN FSSHELL
2)ADD ADDITIONAL LOGIC TO NAVIGATE DIRECTORIES OUTSIDE OF ROOT
3)IMPLEMENT THE STREAM FUNCTIONS LIKE READDIR
4)IMPLEMENT FCB'S(?),MENTIONED IN LECTURE, possibly the first LBA of a file is the fcb
5)IMPLEMENT GET CWD AND SET CWD
6)BUG TESTING
7)ANYTHING ELSE WE CAN THINK OF
*/

struct fs_diriteminfo
	{
    unsigned short d_reclen;    /* length of this record */
    unsigned char fileType;    
    char d_name[256]; 			/* filename max filename is 255 characters */
	

	};//I think this is only in memory to iterate through the directories and maybe files

typedef struct//48 bytes bytes 
	{
	/*****TO DO:  Fill in this structure with what your open/read directory needs  *****/
	unsigned short  d_reclen;		/*length of this record */
	unsigned short	dirEntryPosition;	/*which directory entry position, like file pos */
	uint64_t	directoryStartLocation;		/*Starting LBA of directory */

	//both
	char name[FILENAME_SIZE];
	int type;//0-free 1-file 2-dir 
	
	//file
	int numBytes;//size of the file, though may use this for dir also need to think about it

	//dir
	
	
	} fdDir;//im thinking this is the info for each directory entry (which may be a file or directory) and this struct is what 
	// we LBA WRITE either in B_io/write ( for file creation) or in mkDir(for directory creation)
	//need one for every dirEntry
	//will need one for DE 0 AND 1 where names are . and ..

	//NOTE
	// probably need a few custom functions for logic used in multiple functions 

char* CurrentDir[1024];//Do i need to specify size?

int fs_mkdir(const char *pathname, mode_t mode);
int fs_rmdir(const char *pathname);
fdDir * fs_opendir(const char *name);
struct fs_diriteminfo *fs_readdir(fdDir *dirp);
int fs_closedir(fdDir *dirp);

char * fs_getcwd(char *buf, size_t size);
int fs_setcwd(char *buf);   //linux chdir
int fs_isFile(char * path);	//return 1 if file, 0 otherwise
int fs_isDir(char * path);		//return 1 if directory, 0 otherwise
int fs_delete(char* filename);	//removes a file

int initRoot();
void initBlk(int x);
int dirLBA();//returns the LBA of the current Dir

struct fs_stat
	{
	off_t     st_size;    		/* total size, in bytes */
	blksize_t st_blksize; 		/* blocksize for file system I/O */
	blkcnt_t  st_blocks;  		/* number of 512B blocks allocated */
	time_t    st_accesstime;   	/* time of last access */
	time_t    st_modtime;   	/* time of last modification */
	time_t    st_createtime;   	/* time of last status change */
	
	/* add additional attributes here for your file system */
	};

int fs_stat(const char *path, struct fs_stat *buf);

#endif

