#ifndef GFX_H
#define GFX_H

#include <windows.h>
#include <ddraw.h>
#include "tga.h"
#define IMAGEFILE "images.tga"
class gfx{
public:
	bool InitDDraw(HWND hwnd);
	bool KillDDraw();
	void DrawImage(int x, int y,int index);
	void Present();
	void Clear(DWORD color);
private:
	LPDIRECTDRAW7 ddraw;
	LPDIRECTDRAWSURFACE7 primary;
	LPDIRECTDRAWSURFACE7 back;
	LPDIRECTDRAWSURFACE7 bmps;
};

#endif 