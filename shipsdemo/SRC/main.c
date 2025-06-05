#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libetc.h>
#include <libgpu.h>
#include <libcd.h>
#include <stdio.h>
#include "inline_n.h"
#include "globals.h"
#include "display.h"
#include "joypad.h"
#include "camera.h"
#include "object.h"
#include "utils.h"
#include "texture.h"

Camera camera;
Object *ships;
Object *ship;

u_short angle = 0;

u_long ship_index = 0;

int holdingright = 0;
int holdingleft = 0;

void Setup(void) {
  u_short shipstarttexture;

  ScreenInit();
  CdInit();
  JoyPadInit();

  ResetNextPrim(GetCurrBuff());

  shipstarttexture = GetTextureCount();
  printf("SHIP START TEXTURE is %X \n", shipstarttexture);

  LoadTextureCMP("\\ALLSH.CMP;1");

  ships = LoadObjectPRM( "\\ALLSH.PRM;1",shipstarttexture); // curr is the head now of the linked list

  
  setVector(&camera.position, 0, -300, -900);
  camera.lookat = (MATRIX){0};

}

void Update(void) {
  u_short i;

  EmptyOT(GetCurrBuff());

  JoyPadUpdate();

  if (JoyPadCheck(PAD1_LEFT)) {
    if (ship_index > 0 && !holdingleft) {
      ship_index--;
    }
    if (!holdingleft) {
      holdingleft = 1;
    }
  } else {
    holdingleft = 0;
  }

  if (JoyPadCheck(PAD1_RIGHT)) {
    if (ship_index < 7 && !holdingright) {
      ship_index++;
    }
    if (!holdingright) {
      holdingright = 1;
    }
  } else {
    holdingright = 0;
  }

  // Loop all nodes of the list until we reach the current object index we want
  ship = ships;
  for (i = 0; i < ship_index; i++) {
    ship = ship->next;
  }

  angle += 20;
  ship->rotation.vy = angle;

  LookAt(&camera, &camera.position, &ship->position, &(VECTOR){0, -ONE, 0});

  RenderObject(ship, &camera);
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
