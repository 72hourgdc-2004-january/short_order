#include "gfx.h"

bool gfx::InitDDraw(HWND hwnd)
{
	DirectDrawCreateEx(NULL,(LPVOID *)&ddraw,IID_IDirectDraw7,NULL);
	
	ddraw->SetCooperativeLevel(hwnd,DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN );
	ddraw->SetDisplayMode(320,240,32,0,0);
	
	//Create primary surface
	DDSURFACEDESC2 dds2;
	ZeroMemory(&dds2,sizeof(dds2));

	dds2.dwBackBufferCount = 1;
	dds2.dwSize = sizeof(dds2); 
	dds2.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT; 
	dds2.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | 
    DDSCAPS_FLIP | DDSCAPS_COMPLEX; 
	ddraw->CreateSurface(&dds2,&primary,NULL);

	//Create backbuffer
	DDSCAPS2 ddc2; 
	ZeroMemory(&ddc2,sizeof(ddc2));
	ddc2.dwCaps = DDSCAPS_BACKBUFFER; 
	primary->GetAttachedSurface(&ddc2,&back);

	//Load the images
	targa data(IMAGEFILE);

	if(data.buffer==NULL)
		return false;
	
	ZeroMemory(&dds2,sizeof(dds2));

	dds2.dwSize = sizeof(dds2); 
	dds2.dwFlags =  DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	dds2.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY | DDSCAPS_LOCALVIDMEM;
	dds2.dwHeight = data.height;
	dds2.dwWidth = data.width;

	if(ddraw->CreateSurface(&dds2,&bmps,NULL)!=DD_OK)
		return false;

	unsigned char* surfacedat = NULL;

	if(bmps->Lock(NULL,&dds2,DDLOCK_WAIT,NULL)!=DD_OK)
		return false;
	
	surfacedat = (unsigned char*)dds2.lpSurface;

	int offset = 0;
	int offset2 = 0;

	for(int i=0;i<dds2.dwHeight;i++)
	{
		memcpy(&surfacedat[offset],&data.buffer[offset2],dds2.dwWidth*4);
		offset+=dds2.lPitch;
		offset2+=data.width*4;
	}

	bmps->Unlock(NULL);

	DDCOLORKEY ddck;

	ddck.dwColorSpaceHighValue = 0x00FFFFFF;
	ddck.dwColorSpaceLowValue = 0x00FFFFFF;

	bmps->SetColorKey(DDCKEY_SRCBLT ,&ddck);

	return true;
}

void gfx::Clear(DWORD color)
{
	DDBLTFX bltfx;
	ZeroMemory(&bltfx,sizeof(bltfx));

	bltfx.dwSize = sizeof(bltfx);
	bltfx.dwFillColor = color;
	back->Blt(NULL, NULL, NULL,DDBLT_COLORFILL , &bltfx);

}

bool gfx::KillDDraw()
{
	bmps->Release();
	back->Release();
	primary->Release();
	ddraw->Release();

	return true;
}

void gfx::Present()
{
	primary->Flip(NULL,0 );
}

void gfx::DrawImage(int x, int y,int index)
{
	
	RECT rc;

	rc.right = 32*(index%10) + 32;
	rc.left = 32*(index%10);

	rc.bottom = 32*(index/10) + 32;
	rc.top = 32*(index/10);

	back->BltFast(x,y,bmps,&rc, DDBLTFAST_SRCCOLORKEY);
}
