#include "utils.h"
#include "globals.h"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <libcd.h>

u_char* FileRead(char* filename,u_long* length){
    CdlFILE filepos;
    int numsectors;
    char* buffer;

    if(CdSearchFile(&filepos,filename)==NULL){
        printf("%s FILE NOT FOUND IN THE CD \n", filename);
    }
    else{
        printf("FILENAME %s IS IN THE CD \n", filename);
        numsectors = (filepos.size + 2047) / 2048;   // compute the number of sectors from this file
        buffer = (char *) malloc(2048 * numsectors);     // allocate buffer for the file
        if(!buffer){
            printf("ERROR ALLOCATING SECTORS %d \n", numsectors);
        }
        CdControl(CdlSetloc,(u_char*) &filepos.pos,0);
        CdRead(numsectors,(u_long*) buffer,CdlModeSpeed);
        CdReadSync(0,0);

        *length = filepos.size;
    }
    return buffer;
}

char GetByte(u_char *bytes,u_long *b){
    return bytes[(*b)++];
}

short GetShortBE(u_char *bytes, u_long *b){   // Big endian definition
    unsigned short value = 0;  
    value |= bytes[(*b)++] << 8;
    value |= bytes[(*b)++];
    return (short) value;
}

short GetShortLE(u_char *bytes, u_long *b){   // Little endian definition
    unsigned short value = 0;  
    value |= bytes[(*b)++];
    value |= bytes[(*b)++] << 8;
    return (short) value;
}

long GetLongLE(u_char *bytes, u_long *b){   // Little endian definition
    unsigned long value = 0;  
    value |= bytes[(*b)++] << 0;
    value |= bytes[(*b)++] << 8;
    value |= bytes[(*b)++] << 16;
    value |= bytes[(*b)++] << 24;
    return (long) value;
}

long GetLongBE(u_char *bytes, u_long *b){   // Big endian definition
    unsigned long value = 0;  
    value |= bytes[(*b)++] << 24;
    value |= bytes[(*b)++] << 16;
    value |= bytes[(*b)++] << 8;
    value |= bytes[(*b)++] << 0;
    return (long) value;
}




