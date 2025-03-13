#include "object.h"
#include <stdio.h>


// LOAD MODEL.BIN FROM CD : VERTICES, FACES  & COLORS
void LoadModel(char *filename,Object *object){
    u_char *bytes;
    u_long length;
    u_long i;
    u_long b; // counter of bytes
    // Start Reading bytes from CD ROM
    bytes = FileRead(filename, &length);
    printf("We Read this %d number of bytes \n", length);
    
    b = 0;
  
    //Read the vertices from the file
    object->numverts = GetShortBE(bytes,&b);
    object->vertices = (SVECTOR *) malloc(object->numverts * sizeof(SVECTOR));
    printf("NUM VERTS = %d \n",object->numverts);
  
    for(i = 0;i < object->numverts;i++){
      object->vertices[i].vx = GetShortBE(bytes,&b); 
      object->vertices[i].vy = GetShortBE(bytes,&b); 
      object->vertices[i].vz = GetShortBE(bytes,&b); 
      printf("VERTEX %d : X = %d  Y = %d  Z = %d \n",i,object->vertices[i].vx,object->vertices[i].vy,object->vertices[i].vz);
    }
  
    //Read the faces indices from the file
    object->numfaces = GetShortBE(bytes,&b);
    object->faces = (short*) malloc(object->numfaces * 4 * sizeof(short));
    printf("NUM FACES = %d \n",object->numfaces);
  
    for(i=0;i< object->numfaces * 4;i++){
      object->faces[i]= GetShortBE(bytes,&b);
      printf("FACES %d : %d \n",i,object->faces[i]);
    }
  
    //Read the colors per face
    object->numcolors = GetByte(bytes,&b);
    printf("NUM COLORS = %d \n",object->numcolors);
    object->colors = (CVECTOR*) malloc(object->numcolors * sizeof(CVECTOR));
    for(i=0;i<object->numcolors;i++){
      object->colors[i].r = GetByte(bytes,&b);
      object->colors[i].g = GetByte(bytes,&b);
      object->colors[i].b = GetByte(bytes,&b);
      object->colors[i].cd = GetByte(bytes,&b);
      printf("COLORS %d : R : %d  G : %d B : %d cd : %d \n",i,object->colors[i].r,object->colors[i].g,object->colors[i].b,object->colors[i].cd);  
    }
  
  
  free(bytes);  
  } 