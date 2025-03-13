#ifndef OBJECT_H
#define OBJECT_H

#include "sys/types.h"
#include "globals.h"
#include "utils.h"

typedef struct Object{  
    char    name[16];      /* MODEL NAME (16 characters / bytes)*/
    short   flags;        /*flags dictating how the object should be displayed*/

    VECTOR  position;      /*Origin position (x,y,z)*/

    short   numverts;  /*Number of vertices*/
    SVECTOR *vertices;  /*Pointer to 3D VERTICES (buffer)*/

    short   numnormals;   /* Number of normals*/
    SVECTOR* normals;   /* Pointer to 3D Normals*/

    short   numfaces;   /* Number of normals*/
    short *faces;   /* Pointer to faces indices*/

    short   numcolors;   /* Number of colors*/
    CVECTOR *colors;   /* Pointer to CVECTOR colors*/


    SVECTOR rotation;   /*Model Rotation*/
    VECTOR  translation; /*Model translation*/
    VECTOR  scale;       /*Model scale*/
} Object;


void LoadModel(char *filename,Object *object);

#endif 