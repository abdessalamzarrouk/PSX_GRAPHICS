/*** PSX_GRAPHICS:
 *      DRAWING A PYRAMID with multiple Gouraud - shaded Triangles
 *  ***/


#include <sys/types.h>
#include <stdio.h>
#include <libgte.h>
#include <libetc.h>
#include <libgpu.h>
#include <libapi.h>

#define VMODE 0
#define SCREENX 320
#define SCREENY 240
#define OTlen 9
int db;
DRAWENV drawenv[2];
DISPENV dispenv[2];
long printid1;
long printid2;
u_long OT[2][1024];
char primbuff[2][32768]; // Primitive buffer
char *nextpri = primbuff[0];          // Next primitive pointer
SVECTOR RotVector = {0,0,0}; // you can play around with this to rotate the pyramid
VECTOR ScaleVector = {ONE,ONE,ONE}; 
VECTOR TransVector = {0,0,0,0};
MATRIX TrMatrix = {0};
long OTZ;
long OTZ1;
long p;
long flag;
SVECTOR VertPos[18];
POLY_G3 *g3 = {0}; // first triangle
POLY_G3 *g31= {0}; // second triangle
POLY_G3 *g312= {0}; //.......
POLY_G3 *g313= {0};
POLY_G3 *g41= {0};
POLY_G3 *g42= {0};
int PadStatus;
void init(){
    InitGeom();
    SetGeomOffset(SCREENX/2,SCREENY/2+50);
    SetGeomScreen(SCREENX/2);
    //RESET GPU AND ENABLE INTERRUPTS
    ResetGraph(VMODE);
    PadInit(0);

    //SET DISP AND DRAW ENV

    SetDefDispEnv(&dispenv[0],0,0,SCREENX,SCREENY); //upper frame buffer
    SetDefDrawEnv(&drawenv[1],0,240,SCREENX,SCREENY); //lower frame buffer

    SetDefDrawEnv(&drawenv[0],0,0,SCREENX,SCREENY);// upper frame buffer
    SetDefDispEnv(&dispenv[1],0,240,SCREENX,SCREENY); //lower frame buffer
    
    setRGB0(&drawenv[0], 0, 25, 25); // Set the first DRAWENV primitive's color
	setRGB0(&drawenv[1], 0, 25, 25); // Set the second "			
    drawenv[0].isbg = 1; 
	drawenv[1].isbg = 1;

    PutDispEnv(&dispenv[0]); // Set disp env for first time
    PutDrawEnv(&drawenv[0]); // Set draw env for first time

    db = 0;
    // initialize font and font cords in display 
    FntLoad(960,0);
    printid2 = FntOpen(10,190,300,100,0,100);
}

void display(){
    DrawSync(0);
    VSync(0);
    PutDispEnv(&dispenv[db]);
    PutDrawEnv(&drawenv[db]);
    DrawOTag(&OT[db][0]);
    db = !db;
    nextpri = primbuff[db];
    SetDispMask(1);
}

int main(){    
    SVECTOR VertPos[18] = {                    
            {-25, 0, 1 },                          
            {25,  0, 1 },                         
            {0, -50, 20 },                   
            {25,  0, 1 },
            {25,  0, 40 },
            {0, -50, 20 },
            {25,  0, 40 },
            {-25, 0, 40 },
            {0, -50, 20},
            {-25, 0, 1 }, 
            {-25, 0, 40},
            {0, -50, 20},
            {-25, 1, 1},  // base vetices {  
            {-25,1, 40},                         
            {25, 1, 40},                       
            {-25,1,1},                             
            {25,1,1},
            {25,1,40}    // }
        };    
    init();
    while(1){
        ClearOTag(OT[db],1024);
        g3 = (POLY_G3*)nextpri;
        // defining the rotation and scale matrices to use
        RotMatrix(&RotVector,&TrMatrix);
        ScaleMatrix(&TrMatrix,&ScaleVector);
        SetRotMatrix(&TrMatrix);
        
        // Triangle face number 1
        SetPolyG3(g3);
        setRGB0(g3, 0, 0, 255);
        setRGB1(g3, 0, 255, 0); 
        setRGB2(g3, 255, 0, 0);
        OTZ = RotTransPers3(&VertPos[0],&VertPos[1],&VertPos[2],(long*)&g3->x0,(long*)&g3->x1,(long*)&g3->x2,(long*)p,(long*)flag);
        RotVector.vy+=5;
        addPrim(OT[db],g3);
        nextpri += sizeof(POLY_G3);

        // Triangle face number 2
        g31 = (POLY_G3*)nextpri;
        SetPolyG3(g31);
        setRGB0(g31, 0, 0, 255);
        setRGB1(g31, 0, 255, 255); 
        setRGB2(g31, 255, 0, 255);
        OTZ = RotTransPers3(&VertPos[3],&VertPos[4],&VertPos[5],(long*)&g31->x0,(long*)&g31->x1,(long*)&g31->x2,(long*)p,(long*)flag);
        addPrim(OT[db],g31);
        nextpri += sizeof(POLY_G3);

        // Triangle face number 3
        g312 = (POLY_G3*)nextpri;
        SetPolyG3(g312);
        setRGB0(g312, 0, 255, 255);
        setRGB1(g312, 0, 255, 0); 
        setRGB2(g312, 255, 255, 0);
        OTZ = RotTransPers3(&VertPos[6],&VertPos[7],&VertPos[8],(long*)&g312->x0,(long*)&g312->x1,(long*)&g312->x2,(long*)p,(long*)flag);
        addPrim(OT[db],g312);
        nextpri += sizeof(POLY_G3);

        // Triangle face number 4
        g313 = (POLY_G3*)nextpri;
        SetPolyG3(g313);
        setRGB0(g313, 255, 0, 255);
        setRGB1(g313, 0, 255, 0); 
        setRGB2(g313, 255, 0, 255);
        OTZ = RotTransPers3(&VertPos[9],&VertPos[10],&VertPos[11],(long*)&g313->x0,(long*)&g313->x1,(long*)&g313->x2,(long*)p,(long*)flag);
        addPrim(OT[db],g313);
        nextpri += sizeof(POLY_G3);

        // Triangle face number 5
        g41 = (POLY_G3*)nextpri;
        SetPolyG3(g41);
        setRGB0(g41, 255, 0, 255);
        setRGB1(g41, 0, 255, 255); 
        setRGB2(g41, 255, 0, 255);
        OTZ = RotTransPers3(&VertPos[12],&VertPos[13],&VertPos[14],(long*)&g41->x0,(long*)&g41->x1,(long*)&g41->x2,(long*)p,(long*)flag);
        addPrim(OT[db],g41);
        nextpri += sizeof(POLY_G3);

        // Triangle face number 6
        g42 = (POLY_G3*)nextpri;
        SetPolyG3(g42);
        setRGB0(g42, 255, 0, 255);
        setRGB1(g42, 0, 255, 255); 
        setRGB2(g42, 255, 0, 255);
        OTZ = RotTransPers3(&VertPos[15],&VertPos[16],&VertPos[17],(long*)&g42->x0,(long*)&g42->x1,(long*)&g42->x2,(long*)p,(long*)flag);
        addPrim(OT[db][0],g42);
        nextpri += sizeof(POLY_G3); 

        display();
    }

}