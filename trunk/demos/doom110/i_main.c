// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// $Log:$
//
// DESCRIPTION:
//	Main program, simply calls D_DoomMain high level loop.
//
//-----------------------------------------------------------------------------

static const char
rcsid[] = "$Id: i_main.c,v 1.4 1997/02/03 22:45:10 b1 Exp $";

#ifdef SPMP8
#include "libgame.h"
#endif

#include "doomdef.h"

#include "m_argv.h"
#include "d_main.h"

int
main
( int		argc,
  char**	argv ) 
{ 
#ifndef SPMP8
    myargc = argc; 
    myargv = argv; 
 
    D_DoomMain (); 
#else
	uint32_t color;
	gfx_rect_t rect;
	key_data_t keys;
	
	myargc = 0;
    myargv = NULL;
	
	// initialize the game api
	libgame_init();
	gfx_init(NULL, 0);

	rect.x = 0;
	rect.y = 0;
	rect.width = 320;
	rect.height = 240;

	gfx_set_framebuffer(320, 240);
	gfx_set_display_screen(&rect);
	
	// clear the background
	color = MAKE_RGB(255,255,255);
	gfx_enable_feature(3);
	gfx_set_fgcolor(&color);
	gfx_set_colorrop(COLOR_ROP_NOP);
	gfx_fillrect(&rect);
	
	// initialize the dmsg
	dmsg_init(0, 0, 320, 240);
	dmsg_puts("Debug Console\n");
/*
	// okay, I_GetTime() works
	int ti, t;
	ti = I_GetTime();
	while (1) {
		get_keys(&keys);
		if (keys.key2 & KEY_O) break;
		
		t = I_GetTime();
		if ((t - ti) > 10) {
			dmsg_puts(".");
			ti = t;
		}
	}
*/
//	dmsg_wait(1);
	D_DoomMain();

	dmsg_shutdown();
#endif
    return 0;
} 
