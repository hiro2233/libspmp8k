// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
// $Log:$
//
// DESCRIPTION:
//	DOOM graphics stuff for SDL library
//
//-----------------------------------------------------------------------------

static const char
rcsid[] = "$Id: i_x.c,v 1.6 1997/02/03 22:45:10 b1 Exp $";

#include <stdlib.h>

//#include "SDL.h"

#include "libgame.h"

#include "m_swap.h"
#include "doomstat.h"
#include "i_system.h"
#include "v_video.h"
#include "m_argv.h"
#include "d_main.h"

#include "doomdef.h"

// the framebuffer
gfx_loadimg_t doom_video_img;
unsigned short doom_video_pal[256];
unsigned char doom_video_handle;

key_data_t prev_keys;

//
//  Translates the key 
//
/*
int xlatekey(SDL_keysym *key)
{
    int rc;

    switch(key->sym)
    {
      case SDLK_LEFT:	rc = KEY_LEFTARROW;	break;
      case SDLK_RIGHT:	rc = KEY_RIGHTARROW;	break;
      case SDLK_DOWN:	rc = KEY_DOWNARROW;	break;
      case SDLK_UP:	rc = KEY_UPARROW;	break;
      case SDLK_ESCAPE:	rc = KEY_ESCAPE;	break;
      case SDLK_RETURN:	rc = KEY_ENTER;		break;
      case SDLK_TAB:	rc = KEY_TAB;		break;
      case SDLK_F1:	rc = KEY_F1;		break;
      case SDLK_F2:	rc = KEY_F2;		break;
      case SDLK_F3:	rc = KEY_F3;		break;
      case SDLK_F4:	rc = KEY_F4;		break;
      case SDLK_F5:	rc = KEY_F5;		break;
      case SDLK_F6:	rc = KEY_F6;		break;
      case SDLK_F7:	rc = KEY_F7;		break;
      case SDLK_F8:	rc = KEY_F8;		break;
      case SDLK_F9:	rc = KEY_F9;		break;
      case SDLK_F10:	rc = KEY_F10;		break;
      case SDLK_F11:	rc = KEY_F11;		break;
      case SDLK_F12:	rc = KEY_F12;		break;
	
      case SDLK_BACKSPACE:
      case SDLK_DELETE:	rc = KEY_BACKSPACE;	break;

      case SDLK_PAUSE:	rc = KEY_PAUSE;		break;

      case SDLK_EQUALS:	rc = KEY_EQUALS;	break;

      case SDLK_KP_MINUS:
      case SDLK_MINUS:	rc = KEY_MINUS;		break;

      case SDLK_LSHIFT:
      case SDLK_RSHIFT:
	rc = KEY_RSHIFT;
	break;
	
      case SDLK_LCTRL:
      case SDLK_RCTRL:
	rc = KEY_RCTRL;
	break;
	
      case SDLK_LALT:
      case SDLK_LMETA:
      case SDLK_RALT:
      case SDLK_RMETA:
	rc = KEY_RALT;
	break;
	
      default:
        rc = key->sym;
	break;
    }

    return rc;

}
*/
void I_ShutdownGraphics(void)
{
	gfx_free_image(doom_video_handle);
	free(screens[0]);
}

//
// I_StartFrame
//
void I_StartFrame (void)
{
    // er?
}

/* This processes SDL events */
/*
void I_GetEvent(SDL_Event *Event)
{
    Uint8 buttonstate;
    event_t event;

    switch (Event->type)
    {
      case SDL_KEYDOWN:
	event.type = ev_keydown;
	event.data1 = xlatekey(&Event->key.keysym);
	D_PostEvent(&event);
        break;

      case SDL_KEYUP:
	event.type = ev_keyup;
	event.data1 = xlatekey(&Event->key.keysym);
	D_PostEvent(&event);
	break;

      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
	buttonstate = SDL_GetMouseState(NULL, NULL);
	event.type = ev_mouse;
	event.data1 = 0
	    | (buttonstate & SDL_BUTTON(1) ? 1 : 0)
	    | (buttonstate & SDL_BUTTON(2) ? 2 : 0)
	    | (buttonstate & SDL_BUTTON(3) ? 4 : 0);
	event.data2 = event.data3 = 0;
	D_PostEvent(&event);
	break;

#if (SDL_MAJOR_VERSION >= 0) && (SDL_MINOR_VERSION >= 9)
      case SDL_MOUSEMOTION:
	// Ignore mouse warp events
	if ((Event->motion.x != screen->w/2)||(Event->motion.y != screen->h/2))
	{
	    // Warp the mouse back to the center
	    if (grabMouse) {
		SDL_WarpMouse(screen->w/2, screen->h/2);
	    }
	    event.type = ev_mouse;
	    event.data1 = 0
	        | (Event->motion.state & SDL_BUTTON(1) ? 1 : 0)
	        | (Event->motion.state & SDL_BUTTON(2) ? 2 : 0)
	        | (Event->motion.state & SDL_BUTTON(3) ? 4 : 0);
	    event.data2 = Event->motion.xrel << 2;
	    event.data3 = -Event->motion.yrel << 2;
	    D_PostEvent(&event);
	}
	break;
#endif

      case SDL_QUIT:
	I_Quit();
    }

}
*/

//
// I_StartTic
//
void I_StartTic (void)
{
/*    SDL_Event Event;

    while ( SDL_PollEvent(&Event) )
	I_GetEvent(&Event);
*/
	key_data_t keys;
	event_t event;
	uint32_t key, prev_key;
	
	get_keys(&keys);
	
	// UP
	key = keys.key2 & KEY_UP;
	prev_key = prev_keys.key2 & KEY_UP;
	event.data1 = KEY_UPARROW;
	if ((key == KEY_UP) && (prev_key == 0)) {
		event.type = ev_keydown;
		D_PostEvent(&event);
	}
	else if ((key == 0) && (prev_key == KEY_UP)) {
		event.type = ev_keyup;
		D_PostEvent(&event);
	}
	
	// DOWN
	key = keys.key2 & KEY_DOWN;
	prev_key = prev_keys.key2 & KEY_DOWN;
	event.data1 = KEY_DOWNARROW;
	if ((key == KEY_DOWN) && (prev_key == 0)) {
		event.type = ev_keydown;
		D_PostEvent(&event);
	}
	else if ((key == 0) && (prev_key == KEY_DOWN)) {
		event.type = ev_keyup;
		D_PostEvent(&event);
	}
	
	// LEFT
	key = keys.key2 & KEY_LEFT;
	prev_key = prev_keys.key2 & KEY_LEFT;
	event.data1 = KEY_LEFTARROW;
	if ((key == KEY_LEFT) && (prev_key == 0)) {
		event.type = ev_keydown;
		D_PostEvent(&event);
	}
	else if ((key == 0) && (prev_key == KEY_LEFT)) {
		event.type = ev_keyup;
		D_PostEvent(&event);
	}
	
	// RIGHT
	key = keys.key2 & KEY_RIGHT;
	prev_key = prev_keys.key2 & KEY_RIGHT;
	event.data1 = KEY_RIGHTARROW;
	if ((key == KEY_RIGHT) && (prev_key == 0)) {
		event.type = ev_keydown;
		D_PostEvent(&event);
	}
	else if ((key == 0) && (prev_key == KEY_RIGHT)) {
		event.type = ev_keyup;
		D_PostEvent(&event);
	}
	
	// X (ENTER)
	key = keys.key2 & KEY_X;
	prev_key = prev_keys.key2 & KEY_X;
	event.data1 = KEY_ENTER;
	if ((key == KEY_X) && (prev_key == 0)) {
		event.type = ev_keydown;
		D_PostEvent(&event);
	}
	else if ((key == 0) && (prev_key == KEY_X)) {
		event.type = ev_keyup;
		D_PostEvent(&event);
	}
	
	// O (ESCAPE)
	key = keys.key2 & KEY_O;
	prev_key = prev_keys.key2 & KEY_O;
	event.data1 = KEY_ESCAPE;
	if ((key == KEY_O) && (prev_key == 0)) {
		event.type = ev_keydown;
		D_PostEvent(&event);
	}
	else if ((key == 0) && (prev_key == KEY_O)) {
		event.type = ev_keyup;
		D_PostEvent(&event);
	}
	
	prev_keys.key2 = keys.key2;
}
/*
KEY_UP		1
#define	KEY_DOWN	2
#define	KEY_LEFT	4
#define	KEY_RIGHT	8
#define	KEY_O		1 << 16
#define	KEY_X		2 << 16
*/
//
// I_UpdateNoBlit
//
void I_UpdateNoBlit (void)
{
    // what is this?
}

//
// I_FinishUpdate
//
void I_FinishUpdate (void)
{
	gfx_point2d_t pos;
	gfx_rect_t    rect;
	
	pos.x = 0;
	pos.y = 0;
	rect.x = 0;
	rect.y = 0;
	rect.width = SCREENWIDTH;
	rect.height = SCREENHEIGHT;
	gfx_bitblt(doom_video_handle, &rect, &pos);
	
	gfx_flush();
	gfx_paint();
	
/*
    static int	lasttic;
    int		tics;
    int		i;

    // scales the screen size before blitting it
    if ( SDL_MUSTLOCK(screen) ) {
	if ( SDL_LockSurface(screen) < 0 ) {
	    return;
	}
    }
    if ((multiply == 1) && SDL_MUSTLOCK(screen))
    {
	unsigned char *olineptr;
	unsigned char *ilineptr;
	int y;

	ilineptr = (unsigned char *) screens[0];
	olineptr = (unsigned char *) screen->pixels;

	y = SCREENHEIGHT;
	while (y--)
	{
	    memcpy(olineptr, ilineptr, screen->w);
	    ilineptr += SCREENWIDTH;
	    olineptr += screen->pitch;
	}
    }
    else if (multiply == 2)
    {
	unsigned int *olineptrs[2];
	unsigned int *ilineptr;
	int x, y, i;
	unsigned int twoopixels;
	unsigned int twomoreopixels;
	unsigned int fouripixels;

	ilineptr = (unsigned int *) (screens[0]);
	for (i=0 ; i<2 ; i++) {
	    olineptrs[i] =
		(unsigned int *)&((Uint8 *)screen->pixels)[i*screen->pitch];
        }

	y = SCREENHEIGHT;
	while (y--)
	{
	    x = SCREENWIDTH;
	    do
	    {
		fouripixels = *ilineptr++;
		twoopixels =	(fouripixels & 0xff000000)
		    |	((fouripixels>>8) & 0xffff00)
		    |	((fouripixels>>16) & 0xff);
		twomoreopixels =	((fouripixels<<16) & 0xff000000)
		    |	((fouripixels<<8) & 0xffff00)
		    |	(fouripixels & 0xff);
#ifdef __BIG_ENDIAN__
		*olineptrs[0]++ = twoopixels;
		*olineptrs[1]++ = twoopixels;
		*olineptrs[0]++ = twomoreopixels;
		*olineptrs[1]++ = twomoreopixels;
#else
		*olineptrs[0]++ = twomoreopixels;
		*olineptrs[1]++ = twomoreopixels;
		*olineptrs[0]++ = twoopixels;
		*olineptrs[1]++ = twoopixels;
#endif
	    } while (x-=4);
	    olineptrs[0] += screen->pitch/4;
	    olineptrs[1] += screen->pitch/4;
	}

    }
    else if (multiply == 3)
    {
	unsigned int *olineptrs[3];
	unsigned int *ilineptr;
	int x, y, i;
	unsigned int fouropixels[3];
	unsigned int fouripixels;

	ilineptr = (unsigned int *) (screens[0]);
	for (i=0 ; i<3 ; i++) {
	    olineptrs[i] = 
		(unsigned int *)&((Uint8 *)screen->pixels)[i*screen->pitch];
        }

	y = SCREENHEIGHT;
	while (y--)
	{
	    x = SCREENWIDTH;
	    do
	    {
		fouripixels = *ilineptr++;
		fouropixels[0] = (fouripixels & 0xff000000)
		    |	((fouripixels>>8) & 0xff0000)
		    |	((fouripixels>>16) & 0xffff);
		fouropixels[1] = ((fouripixels<<8) & 0xff000000)
		    |	(fouripixels & 0xffff00)
		    |	((fouripixels>>8) & 0xff);
		fouropixels[2] = ((fouripixels<<16) & 0xffff0000)
		    |	((fouripixels<<8) & 0xff00)
		    |	(fouripixels & 0xff);
#ifdef __BIG_ENDIAN__
		*olineptrs[0]++ = fouropixels[0];
		*olineptrs[1]++ = fouropixels[0];
		*olineptrs[2]++ = fouropixels[0];
		*olineptrs[0]++ = fouropixels[1];
		*olineptrs[1]++ = fouropixels[1];
		*olineptrs[2]++ = fouropixels[1];
		*olineptrs[0]++ = fouropixels[2];
		*olineptrs[1]++ = fouropixels[2];
		*olineptrs[2]++ = fouropixels[2];
#else
		*olineptrs[0]++ = fouropixels[2];
		*olineptrs[1]++ = fouropixels[2];
		*olineptrs[2]++ = fouropixels[2];
		*olineptrs[0]++ = fouropixels[1];
		*olineptrs[1]++ = fouropixels[1];
		*olineptrs[2]++ = fouropixels[1];
		*olineptrs[0]++ = fouropixels[0];
		*olineptrs[1]++ = fouropixels[0];
		*olineptrs[2]++ = fouropixels[0];
#endif
	    } while (x-=4);
	    olineptrs[0] += 2*screen->pitch/4;
	    olineptrs[1] += 2*screen->pitch/4;
	    olineptrs[2] += 2*screen->pitch/4;
	}

    }
    if ( SDL_MUSTLOCK(screen) ) {
	SDL_UnlockSurface(screen);
    }
    SDL_UpdateRect(screen, 0, 0, 0, 0);
*/
}


//
// I_ReadScreen
//
void I_ReadScreen (byte* scr)
{
    memcpy (scr, screens[0], SCREENWIDTH*SCREENHEIGHT);
}


//
// I_SetPalette
//
void I_SetPalette (byte* palette)
{
    int i;
    byte *ppal;
	int r, g, b;

	ppal = palette;
	for ( i=0; i<256; ++i ) {
		r = ppal[0];
		g = ppal[1];
		b = ppal[2];
		doom_video_pal[i] = ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | ((b & 0xf8) >> 3);	// 565 - r:g:b
		ppal+=3;
	}
}


void I_InitGraphics(void)
{
    static int	firsttime=1;
    gfx_rect_t rect;

    if (!firsttime) return;
    firsttime = 0;

	dmsg_puts("begin...");
	// initialize graphics
/*	gfx_init(NULL, 0);
	gfx_set_framebuffer(SCREENWIDTH, SCREENHEIGHT);

	rect.x = 0;
	rect.y = 0;
	rect.width = SCREENWIDTH;
	rect.height = SCREENHEIGHT;
	gfx_set_display_screen(&rect);
*/
	screens[0] = (unsigned char *)malloc(SCREENWIDTH * SCREENHEIGHT);
	screens[1] = screens[0];
    if (screens[0] == NULL) I_Error("Couldn't allocate screen memory");
	
	memset(screens[0], 0, SCREENWIDTH * SCREENHEIGHT);
	doom_video_img.data     = screens[0];
	doom_video_img.width    = SCREENWIDTH;
	doom_video_img.height   = SCREENHEIGHT;
	doom_video_img.img_type = IMG_TYPE_8BPP;
	doom_video_img.unk2     = 0;
	doom_video_img.pal_data = doom_video_pal;
	doom_video_img.pal_size = 256;
	doom_video_img.unk3     = 0xffffff80;
	
	gfx_load_image(&doom_video_img, &doom_video_handle);
	gfx_set_colorrop(0xcc);
	
	// initialize input
	prev_keys.key1 = 0;
	prev_keys.key2 = 0;
	
	dmsg_puts("end");
}
