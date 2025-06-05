#ifndef UTILS_H
#define UTILS_H

#include <sys/types.h>

char *FileRead(char* filename,u_long* length);

short GetShortBE(u_char *bytes, u_long *b);
short GetShortLE(u_char *bytes, u_long *b);
long GetLongBE(u_char *bytes, u_long *b);
long GetLongLE(u_char *bytes, u_long *b);
char GetByte(u_char *bytes,u_long *b);



#endif