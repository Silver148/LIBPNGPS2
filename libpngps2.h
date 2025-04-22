#ifndef PNG_PS2_H
#define PNG_PS2_H

#include <malloc.h>
#include <string.h>
#include <gsKit.h>
#include <dmaKit.h>
#include <gsToolkit.h>
#include <stdio.h>
#include "upng/upng.h"

void init_graphics(GSGLOBAL **gsGlobal, int width, int height);
void load_texture(GSGLOBAL **gsGlobal, GSTEXTURE *texture, const unsigned char *data, unsigned int size, char PSM);
void create_texture(GSGLOBAL *gsGlobal, GSTEXTURE *texture, int x, int y);
void FreeMemory(GSGLOBAL *gsGlobal, GSTEXTURE *texture);
void print_vram_usage(GSGLOBAL *gsGlobal);

#endif // PNG_PS2_H
