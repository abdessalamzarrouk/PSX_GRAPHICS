#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libetc.h>
#include <libgpu.h>
#include <libcd.h>


#include "inline_n.h"
#include "globals.h"
#include "display.h"
#include "joypad.h"
#include "camera.h"
#include "utils.h"
#include "object.h"
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Declarations and global variables
///////////////////////////////////////////////////////////////////////////////
POLY_FT4 *polyft4;

Camera camera;
Object object;

MATRIX worldmat = {0};
MATRIX viewmat = {0};


u_long timmode; /* pixel mode of the tim*/
RECT timprect; /* Store X and Y location of the texture */
RECT timcrect; /* Store X and Y location of the clut*/

// LOAD TEXTURE DATE FROM CD : tim file
void LoadTexture(char *filename){
  u_long *bytes;
  u_long i,b,length;
  TIM_IMAGE tim;

  // Start reading bytes from CD
  bytes = (u_long *) FileRead(filename,&length);

  OpenTIM(bytes);
  ReadTIM(&tim);

  // Load texture into VRAM and wait for copy to complete
  LoadImage(tim.prect,tim.paddr);
  DrawSync(0);

  //Load CLUT into VRAM (if present) and wait for copy to complete
  if(tim.mode & 0x8){
    LoadImage(tim.crect,tim.caddr);
    DrawSync(0);
  }

  timmode = tim.mode;
  timprect = *tim.prect;
  timcrect = *tim.crect;

  // Deallocate file buffer
  free(bytes);

}


///////////////////////////////////////////////////////////////////////////////
// Setup function that is called once at the beginning of the execution
///////////////////////////////////////////////////////////////////////////////
void Setup(void) {

  // Setup the display environment
  ScreenInit();

  //Initialize CD Subsystem
  CdInit();

  // Initializes the joypad
  JoyPadInit();

  // Reset next primitive pointer to the start of the primitive buffer
  ResetNextPrim(GetCurrBuff());

  // Initializes camera object
  setVector(&camera.position,500,-800,-900);
  camera.lookat = (MATRIX) {0};
   
  setVector(&object.position,0,0,0);
  setVector(&object.rotation,0,0,0);
  setVector(&object.scale,ONE,ONE,ONE);


  //LOAD OBJECT DATA FROM CD (VERTICES FACES AND COLORS)
  LoadModel("\\MODEL.BIN;1",&object);

  //Load Texture from BRICKS.TIM
  LoadTexture("\\BRICKS.TIM;1");
  printf("VERTEX TEST 0 : X = %d  Y = %d  Z = %d \n",object.vertices[0].vx,object.vertices[0].vy,object.vertices[0].vz);

}

///////////////////////////////////////////////////////////////////////////////
// Setup function that is called once at the beginning of the execution
///////////////////////////////////////////////////////////////////////////////
void Update(void) {
  int i, j, nclip;
  long otz, p, flg;
  u_long pad;

  // Empty the Ordering Table
  EmptyOT(GetCurrBuff());

  // Update the state of the controller
  JoyPadUpdate();

  if (JoyPadCheck(PAD1_LEFT)) {
    camera.position.vx -= 50;
  }
  if (JoyPadCheck(PAD1_RIGHT)) {
    camera.position.vx += 50;
  }
  if (JoyPadCheck(PAD1_UP)) {
    camera.position.vy -= 50;
  }
  if (JoyPadCheck(PAD1_DOWN)) {
    camera.position.vy += 50;
  }
  if (JoyPadCheck(PAD1_CROSS)) {
    camera.position.vz += 50;
  }
  if (JoyPadCheck(PAD1_CIRCLE)) {
    camera.position.vz -= 50;
  } 

  
  
  // COMPUTE LOOKAT MATRIX  
  LookAt(&camera,&camera.position,&object.position,&(VECTOR){0,-ONE,0});

  /////////////////////
  // Draw the Cube
  /////////////////////
  RotMatrix(&object.rotation, &worldmat);
  TransMatrix(&worldmat, &object.position);
  ScaleMatrix(&worldmat, &object.scale);

  // COMBINE WORLD MATRIX AND LOOKAT MATRIX TO MAKE VIEW MATRIX
  CompMatrixLV(&camera.lookat,&worldmat,&viewmat);  


  SetRotMatrix(&viewmat);
  SetTransMatrix(&viewmat);

   for (i = 0, j = 0; j < object.numfaces; i += 4, j++) {
    polyft4 = (POLY_FT4*) GetNextPrim();
    setPolyFT4(polyft4);
    setRGB0(polyft4,128,128,128);

    polyft4->u0 = 0; polyft4->v0 = 0; 
    polyft4->u1 = 63; polyft4->v1 = 0;
    polyft4->u2 = 0; polyft4->v2 = 63;
    polyft4->u3 = 63; polyft4->v3 = 63;

    polyft4->tpage = getTPage(timmode & 0x3, 0, timprect.x, timprect.y); // & 0x3 : to test if there is 16 bit mode
    polyft4->clut = getClut(timcrect.x,timcrect.y);

    printf("LOOP i : %d , j : %d  object.colors[j].r %d object.colors[j].g %d object.colors[j].b %d \n",i,j,object.colors[j].r,object.colors[j].g,object.colors[j].b);

    // Loading the first 3 vertices (the GTE can only perform a max. of 3 vectors at a time)
    gte_ldv0(&object.vertices[object.faces[i + 0]]);
    gte_ldv1(&object.vertices[object.faces[i + 1]]);
    gte_ldv2(&object.vertices[object.faces[i + 2]]);

    gte_rtpt();

    gte_nclip();
    gte_stopz(&nclip);

    if (nclip >= 0) {
      // Store/save the transformed projected coord of the first vertex
      gte_stsxy0(&polyft4->x0);

      // Load the last 4th vertex
      gte_ldv0(&object.vertices[object.faces[i + 3]]);

      // Project & transform the remaining 4th vertex
      gte_rtps();

      // Store the transformed last vertices
      gte_stsxy3(&polyft4->x1, &polyft4->x2, &polyft4->x3);

      gte_avsz4();
      gte_stotz(&otz);

      if ((otz > 0) && (otz < OT_LEN)) {
        addPrim(GetOTAt(GetCurrBuff(), otz), polyft4);
        IncrementNextPrim(sizeof(POLY_FT4));
      }
    }  
    object.rotation.vy += 5;
  }

  
}

///////////////////////////////////////////////////////////////////////////////
// Render function that invokes the draw of the current frame
///////////////////////////////////////////////////////////////////////////////
void Render(void) {
  DisplayFrame();
}



///////////////////////////////////////////////////////////////////////////////
// Main function
///////////////////////////////////////////////////////////////////////////////
int main(void) {
  Setup();
  while (1) {
    Update();
    Render();
  }
  return 0;
}
