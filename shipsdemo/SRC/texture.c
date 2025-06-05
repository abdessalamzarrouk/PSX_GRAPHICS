#include "texture.h"
#include "globals.h"
#include "lzss.h"
#include <stdlib.h>

static Texture *texturestore[MAX_TEXTURES];
static u_short texturecount = 0;

Texture *GetFromTextureStore(u_int i) {
  return texturestore[i];
}

u_short GetTextureCount(void) {
  return texturecount;
}

void LoadTextureCMP(char *filename) {
  u_long b, i;
  u_long length;
  u_char *bytes;
  u_short numtextures;
  u_long totaltimsize;
  Texture *texture;

  static void *timsbaseaddr;
  static long timoffsets[400];

  bytes = (u_char*) FileRead(filename, &length);

  if (bytes == NULL) {
    printf("Error reading %s from the CD.\n", filename);
    return;
  }

  b = 0;

  numtextures = GetLongLE(bytes, &b);
  

  // The next values of the file are the size (in bytes) of each TIM texture (uncompressed)
  totaltimsize = 0;
  for (i = 0; i < numtextures; i++) {
    u_long timsize;
    timoffsets[i] = totaltimsize; // stores the offset (in bytes) to access each TIM texture
    timsize = GetLongLE(bytes, &b);
    totaltimsize += timsize;
  }
 

  // Allocate the total memory necessary for all uncompressed TIMs in this CMP file
  timsbaseaddr = (char*) malloc(totaltimsize);

  // Compute the correct offset by adding the base address plus each TIM offset
  for (i = 0; i < numtextures; i++) {
    timoffsets[i] += (long)timsbaseaddr;
  }

  // Expand/decompress the entire compressed data using LZSS
  ExpandLZSSData(&bytes[b], timsbaseaddr);

  // Deallocating the file buffer
  free(bytes);

  // Upload all textures to VRAM
  for (i = 0; i < numtextures; i++) {
    texture = UploadTextureToVRAM(timoffsets[i]);
    if (texture != NULL) {
      texturestore[texturecount++] = texture;
    }
    if (texturecount > MAX_TEXTURES) {
      printf("Texture global store is full!!!\n");
    }
  }

  // Since all textures were uploaded to VRAM, we can deallocate the buffer
  free(timsbaseaddr);
}

Texture *UploadTextureToVRAM(long timptr) {
  Tim *tim;
  Texture *texture;
  u_short x, y;
  RECT rect;
  tim = (Tim*) timptr;
  switch (ClutType(tim)) {
    case CLUT_4BIT: {
      TimClut4 *tc4;
      tc4 = (TimClut4*) tim;
      texture = (Texture*) malloc(sizeof(Texture));
      texture->type = CLUT4;
      texture->textureX = tc4->textureX;
      texture->textureY = tc4->textureY;
      texture->textureW = tc4->textureW;
      texture->textureH = tc4->textureH;
      texture->clutX    = tc4->clutX;
      texture->clutY    = tc4->clutY;
      texture->clutW    = tc4->clutW;
      texture->clutH    = tc4->clutH;

      x = tc4->textureX - TextureHOffset(tc4->textureX);
      y = tc4->textureY - TextureVOffset(tc4->textureY);

      texture->u0 = (x << 2);
      texture->v0 = (y);
      texture->u1 = ((x + tc4->textureW) << 2) - 1;
      texture->v1 = (y);
      texture->u2 = (x << 2);
      texture->v2 = (y + tc4->textureH) - 1;
      texture->u3 = ((x + tc4->textureW) << 2) - 1;
      texture->v3 = (y + tc4->textureH) - 1;

      texture->tpage = TPAGE(CLUT_4BIT, TRANSLUCENT, texture->textureX, texture->textureY);
      texture->clut  = CLUT(texture->clutX >> 4, texture->clutY);

      // Load the CLUT rectangle to VRAM
      rect.x = tc4->clutX;
      rect.y = tc4->clutY;
      rect.w = tc4->clutW;
      rect.h = tc4->clutH;
      LoadImage(&rect, (u_long*)(&tc4->clut));
      DrawSync(0);

      // Load the Texture rectangle to VRAM
      rect.x = tc4->textureX;
      rect.y = tc4->textureY;
      rect.w = tc4->textureW;
      rect.h = tc4->textureH;
      LoadImage(&rect, (u_long*)(tc4 + 1));
      DrawSync(0);

      break;
    }
    case CLUT_8BIT: {
      TimClut8 *tc8;
      tc8 = (TimClut8*) tim;
      texture = (Texture*) malloc(sizeof(Texture));
      texture->type = CLUT8;
      texture->textureX = tc8->textureX;
      texture->textureY = tc8->textureY;
      texture->textureW = tc8->textureW;
      texture->textureH = tc8->textureH;
      texture->clutX    = tc8->clutX;
      texture->clutY    = tc8->clutY;
      texture->clutW    = tc8->clutW;
      texture->clutH    = tc8->clutH;

      x = tc8->textureX - TextureHOffset(tc8->textureX);
      y = tc8->textureY - TextureVOffset(tc8->textureY);

      texture->u0 = (x << 1);
      texture->v0 = (y);
      texture->u1 = ((x + tc8->textureW) << 1) - 1;
      texture->v1 = (y);
      texture->u2 = (x << 1);
      texture->v2 = (y + tc8->textureH) - 1;
      texture->u3 = ((x + tc8->textureW) << 1) - 1;
      texture->v3 = (y + tc8->textureH) - 1;

      texture->tpage = TPAGE(CLUT_8BIT, TRANSLUCENT, texture->textureX, texture->textureY);
      texture->clut  = CLUT(texture->clutX >> 4, texture->clutY);

      // Load the CLUT rectangle to VRAM
      rect.x = tc8->clutX;
      rect.y = tc8->clutY;
      rect.w = tc8->clutW;
      rect.h = tc8->clutH;
      LoadImage(&rect, (u_long*)(&tc8->clut));
      DrawSync(0);

      // Load the Texture rectangle to VRAM
      rect.x = tc8->textureX;
      rect.y = tc8->textureY;
      rect.w = tc8->textureW;
      rect.h = tc8->textureH;
      LoadImage(&rect, (u_long*)(tc8 + 1));
      DrawSync(0);

      break;
    }
  }
  return texture;
}
