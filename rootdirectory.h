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
#define MAXFILESALLOWEDINDIR 20

typedef struct directory {
    char filename[20];
    uint32_t file_size;
    u_int16_t start_data_block;
    u_int8_t unused[8];
}dir;

//struct rootdirectoryEntry_t *rootDirectoryBlock;

void initRoot();