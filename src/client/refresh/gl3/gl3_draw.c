/*
 * Copyright (C) 1997-2001 Id Software, Inc.
 * Copyright (C) 2016 Daniel Gibson
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * =======================================================================
 *
 * Drawing of all images that are not textures
 *
 * =======================================================================
 */

#include "header/local.h"

unsigned d_8to24table[256];

static cvar_t *gl_nolerp_list;

gl3image_t *draw_chars;

void
GL3_Draw_InitLocal(void)
{
	/* don't bilerp characters and crosshairs */
	gl_nolerp_list = ri.Cvar_Get("gl_nolerp_list", "pics/conchars.pcx pics/ch1.pcx pics/ch2.pcx pics/ch3.pcx", 0);

	/* load console characters */
	draw_chars = GL3_FindImage("pics/conchars.pcx", it_pic);
}

int
GL3_Draw_GetPalette(void)
{
	int i;
	int r, g, b;
	unsigned v;
	byte *pic, *pal;
	int width, height;

	/* get the palette */
	LoadPCX("pics/colormap.pcx", &pic, &pal, &width, &height);

	if (!pal)
	{
		ri.Sys_Error(ERR_FATAL, "Couldn't load pics/colormap.pcx");
	}

	for (i = 0; i < 256; i++)
	{
		r = pal[i * 3 + 0];
		g = pal[i * 3 + 1];
		b = pal[i * 3 + 2];

		v = (255 << 24) + (r << 0) + (g << 8) + (b << 16);
		d_8to24table[i] = LittleLong(v);
	}

	d_8to24table[255] &= LittleLong(0xffffff); /* 255 is transparent */

	free(pic);
	free(pal);

	return 0;
}


