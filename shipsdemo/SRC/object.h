#ifndef OBJECT_H
#define OBJECT_H

#include "sys/types.h"
#include "globals.h"
#include "utils.h"
#include "camera.h"
typedef struct F3 {
    short             type;          /* Type of primitive */
    short             flag;
    short             coords[3];     /* Indices of the coords */
    short             pad1;
    CVECTOR           color;
 } F3;
 
 typedef struct FT3 {
    short             type;          /* Type of primitive */
    short             flag;
    short             coords[3];     /* Indices of the coords */
    short             texture;
    short             clut;
    short             tpage;
    char              u0;
    char              v0;
    char              u1;
    char              v1;
    char              u2;
    char              v2;
    short             pad1;
    CVECTOR           color;
 } FT3;
 
 typedef struct F4 {
    short             type;          /* Type of primitive */
    short             flag;
    short             coords[4];     /* Indices of the coords */
    CVECTOR           color;
 } F4;
 
 typedef struct FT4 {
    short             type;          /* Type of primitive */
    short             flag;
    short             coords[4];     /* Indices of the coords */
    short             texture;
    short             clut;
    short             tpage;
    char              u0;
    char              v0;
    char              u1;
    char              v1;
    char              u2;
    char              v2;
    char              u3;
    char              v3;
    short             pad1;
    CVECTOR           color;
 } FT4;
 
 typedef struct G3 {
    short             type;          /* Type of primitive */
    short             flag;
    short             coords[3];     /* Indices of the coords */
    short             pad1;
    CVECTOR           color[3];
 } G3;
 
 typedef struct GT3 {
    short             type;          /* Type of primitive */
    short             flag;
    short             coords[3];     /* Indices of the coords */
    short             texture;
    short             clut;
    short             tpage;
    char              u0;
    char              v0;
    char              u1;
    char              v1;
    char              u2;
    char              v2;
    short             pad1;
    CVECTOR           color[3];
 } GT3;
 
 typedef struct G4 {
    short             type;          /* Type of primitive */
    short             flag;
    short             coords[4];     /* Indices of the coords */
    CVECTOR           color[4];
 } G4;
 
 typedef struct GT4 {
    short             type;          /* Type of primitive */
    short             flag;
    short             coords[4];     /* Indices of the coords */
    short             texture;
    short             clut;
    short             tpage;
    char              u0;
    char              v0;
    char              u1;
    char              v1;
    char              u2;
    char              v2;
    char              u3;
    char              v3;
    short             pad1;
    CVECTOR           color[4];
 } GT4;
 
 typedef struct LSF3 {
    short             type;          /* Type of primitive */
    short             flag;
    short             coords[3];     /* Indices of the coords */
    short             normal;        /* Indices of the normals */
    CVECTOR           color;
 } LSF3;
 
 typedef struct LSFT3 {
    short             type;          /* Type of primitive */
    short             flag;
    short             coords[3];     /* Indices of the coords */
    short             normal;        /* Indices of the normals */
    short             texture;
    short             clut;
    short             tpage;
    char              u0;
    char              v0;
    char              u1;
    char              v1;
    char              u2;
    char              v2;
    CVECTOR           color;
 } LSFT3;
 
 typedef struct LSF4 {
    short             type;          /* Type of primitive */
    short             flag;
    short             coords[4];     /* Indices of the coords */
    short             normal;        /* Indices of the normals */
    short             pad1;
    CVECTOR           color;
 } LSF4;
 
 typedef struct LSFT4 {
    short             type;          /* Type of primitive */
    short             flag;
    short             coords[4];     /* Indices of the coords */
    short             normal;        /* Indices of the normals */
    short             texture;
    short             clut;
    short             tpage;
    char              u0;
    char              v0;
    char              u1;
    char              v1;
    char              u2;
    char              v2;
    char              u3;
    char              v3;
    CVECTOR           color;
 } LSFT4;
 
 typedef struct LSG3 {
    short             type;          /* Type of primitive */
    short             flag;
    short             coords[3];     /* Indices of the coords */
    short             normals[3];    /* Indices of the normals */
    CVECTOR           color[3];
 } LSG3;
 
 typedef struct LSGT3 {
    short             type;          /* Type of primitive */
    short             flag;
    short             coords[3];     /* Indices of the coords */
    short             normals[3];    /* Indices of the normals */
    short             texture;
    short             clut;
    short             tpage;
    char              u0;
    char              v0;
    char              u1;
    char              v1;
    char              u2;
    char              v2;
    CVECTOR           color[3];
 } LSGT3;
 
 typedef struct LSG4 {
    short             type;          /* Type of primitive */
    short             flag;
    short             coords[4];     /* Indices of the coords */
    short             normals[4];    /* Indices of the normals */
    CVECTOR           color[4];
 } LSG4;
 
 typedef struct LSGT4 {
    short             type;          /* Type of primitive */
    short             flag;
    short             coords[4];     /* Indices of the coords */
    short             normals[4];    /* Indices of the normals */
    short             texture;
    short             clut;
    short             tpage;
    char              u0;
    char              v0;
    char              u1;
    char              v1;
    char              u2;
    char              v2;
    char              u3;
    char              v3;
    short             pad1;
    CVECTOR           color[4];
 } LSGT4;
 
 typedef struct {
    u_long*   tag;
    CVECTOR  color0;
    DVECTOR  xy0;
    DVECTOR  xy1;
 } LineF2;
 
 typedef struct LF2 {
    short             type;          /* Type of primitive */
    short             flag;
    short             lines;         /* Number of lines */
    LineF2*           line[2];       /* 2 GPU Primitive arrays for double buffer */
 } LF2;
 
 typedef struct SPR {
    short             type;
    short             flag;
    short             coord;
    short             width;
    short             height;
    short             texture;
    CVECTOR           color;
 } SPR;
 
 typedef struct Spline {
    short             type;          /* Type of primitive */
    short             flag;
    SVECTOR           control1;
    SVECTOR           position;
    SVECTOR           control2;
    CVECTOR           color;
 } Spline;
 
 typedef struct PointLight {
    short             type;
    short             flag;
    VECTOR            position;
    CVECTOR           color;
    short             startFalloff;
    short             endFalloff;
 } PointLight;
 
 typedef struct SpotLight {
    short             type;
    short             flag;
    VECTOR            position;
    SVECTOR           direction;
    CVECTOR           color;
    short             startFalloff;
    short             endFalloff;
    short             coneAngle;
    short             spreadAngle;
 } SpotLight;
 
 typedef struct InfiniteLight {
    short             type;
    short             flag;
    SVECTOR           direction;
    CVECTOR           color;
 } InfiniteLight;
 
 
 /* Primitive Flags */
 #define  SingleSided    0x0001
 #define  ShipEngine     0x0002
 #define  Translucent    0x0004
 
 /* Primitive Types */
 #define     TYPE_F3               1
 #define     TYPE_FT3              2
 #define     TYPE_F4               3
 #define     TYPE_FT4              4
 #define     TYPE_G3               5
 #define     TYPE_GT3              6
 #define     TYPE_G4               7
 #define     TYPE_GT4              8
 
 #define     TYPE_LF2              9
 #define     TYPE_TSPR             10
 #define     TYPE_BSPR             11
 
 #define     TYPE_LSF3             12
 #define     TYPE_LSFT3            13
 #define     TYPE_LSF4             14
 #define     TYPE_LSFT4            15
 #define     TYPE_LSG3             16
 #define     TYPE_LSGT3            17
 #define     TYPE_LSG4             18
 #define     TYPE_LSGT4            19
 
 #define     TYPE_SPLINE          20
 
 #define     TYPE_INFINITELIGHT    21
 #define     TYPE_POINTLIGHT      22
 #define     TYPE_SPOTLIGHT       23

 #define FLAG_SINGLE_SIDED 0x0001
 #define FLAG_SHIP_ENGINE 0x0002
 #define FLAG_TRANSLUCENT 0x0004
 
 /* Primitive Union (since we want to only hold one of it per list node) */
 typedef union Prm {
   F3             *f3;
   FT3            *ft3;
   F4             *f4;
   FT4            *ft4;
   G3             *g3;
   GT3            *gt3;
   G4             *g4;
   GT4            *gt4;
   SPR            *spr;
   Spline         *spline;
   PointLight     *pointLight;
   SpotLight      *spotLight;
   InfiniteLight  *infiniteLight;
   LSF3           *lsf3;
   LSFT3          *lsft3;
   LSF4           *lsf4;
   LSFT4          *lsft4;
   LSG3           *lsg3;
   LSGT3          *lsgt3;
   LSG4           *lsg4;
   LSGT4          *lsgt4;
 } Prm;
 
 typedef struct PrimitiveNode {
   short type;
   short flag;
   Prm *primitive;
 } PrimitiveNode;

typedef struct Object{  // THIS IS FOR THE WIPEOUT PROJECT
    char    name[16];      /* MODEL NAME (16 characters / bytes)*/
    short   flags;        /*flags dictating how the object should be displayed*/

    VECTOR  origin;      /*Origin position (x,y,z)*/

    short   numvertices;  /*Number of vertices*/
    SVECTOR *vertices;  /*Pointer to 3D VERTICES (buffer)*/

    short   numnormals;   /* Number of normals*/
    SVECTOR* normals;   /* Pointer to 3D Normals*/

    short   numprimitives; /* Number of primitives*/
    PrimitiveNode *primitives;  /* Pointer to Z sort primitves*/

    SVECTOR rotation;   /*Model Rotation*/
    VECTOR  position; /*Model translation*/
    VECTOR  scale;       /*Model scale*/

    struct Object *next;
    
} Object;


Object *LoadObjectPRM(char *filename,u_short texturestart);   
Object *GetObjectByIndex(Object *list ,u_short index);
void RenderSceneObjects(Object *list,Camera *camera);
void RenderObject(Object *object,Camera *camera);


#endif