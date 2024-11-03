/*** PSX_GRAPHICS:
 *      DRAWING A GOURAUD-SHADED TRIANGLE
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
u_long OT[2][9];
char primbuff[2][32768]; // Primitive buffer
char *nextpri = primbuff[0];          // Next primitive pointer
SVECTOR RotVector = {0,0,0};
VECTOR ScaleVector = {ONE,ONE,ONE};
VECTOR TransVector = {0,0,0,0};
MATRIX TrMatrix = {0};
long OTZ;
long p;
long flag;
SVECTOR VertPos[3];
POLY_G3 *g3 = {0};

void init(){
    InitGeom();
    SetGeomOffset(SCREENX/2,SCREENY/2+50);
    SetGeomScreen(SCREENX/2);
    //RESET GPU AND ENABLE INTERRUPTS
    ResetGraph(VMODE);

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
    SVECTOR VertPos[3] = {                    
            {-25, 0, 1 },                         // Vert 1 
            {25,  0, 1 },                         // Vert 2
            {0, -50, 1 },                         // Vert 3
        };    
    init();
    while(1){
        ClearOTag(OT[db],9);
        g3 = (POLY_G3*)nextpri;
        RotMatrix(&RotVector,&TrMatrix);
        TransMatrix(&TrMatrix,&TransVector);
        ScaleMatrix(&TrMatrix,&ScaleVector);
        SetRotMatrix(&TrMatrix);
        SetTransMatrix(&TrMatrix);
        SetPolyG3(g3);
        setRGB0(g3, 0, 0, 255);
        setRGB1(g3, 0, 255, 0); 
        setRGB2(g3, 255, 0, 0);  
        OTZ = RotTransPers3(&VertPos[0],&VertPos[1],&VertPos[2],(long*)&g3->x0,(long*)&g3->x1,(long*)&g3->x2,(long*)p,(long*)flag);
        RotVector.vy +=25;
        addPrim(OT[db],g3);
        nextpri += sizeof(POLY_G3); 
        FntPrint(printid2,"MADE BY ABDESSALAM \n\n x0 : %d y0 : %d x1 : %d y1 : %d \n x2 : %d y2 : %d",g3->x0,g3->y0,g3->x1,g3->y1,g3->x2,g3->y2); // just to see if cords change and everything works
        FntFlush(-1);
        display();
    }

}