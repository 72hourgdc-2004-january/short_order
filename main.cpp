#include <windows.h>
#include "game.h"

HWND hwnd;
gfx* GFX;
int x, y, mstate;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
		case WM_CLOSE:
			
			DestroyWindow(hWnd);
		break;

		case WM_DESTROY:
			GFX->KillDDraw();
			delete GFX;
			ShowCursor(TRUE);
			PostQuitMessage(0);
		break;

		case WM_LBUTTONDOWN:
			mstate = DOWN;
			y = HIWORD(lparam);
			x = LOWORD(lparam);
			MouseBurgers(x,y,mstate);
			break;
		case WM_LBUTTONUP:
			mstate = UP;
			y = HIWORD(lparam);
			x = LOWORD(lparam);

			MouseBurgers(x,y,mstate);
			break;

		case WM_KEYDOWN:
			switch(wparam)
			{
			case VK_ESCAPE:
				DestroyWindow(hWnd);
				break;
			
			}
			break;

		case WM_RBUTTONUP:
			mstate = RIGHT;
			MouseBurgers(0,0,mstate);
			break;
		case WM_MOUSEMOVE:
			y = HIWORD(lparam);
			x = LOWORD(lparam);
			break;

	}
	return DefWindowProc(hWnd,msg,wparam,lparam);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinst, LPSTR CmdLine, int nShowCmd)
{
	WNDCLASS wndclass;
	MSG msg;

	wndclass.cbClsExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hInstance = hinstance;
	wndclass.lpszClassName = "shortclass";
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = (WNDPROC)WndProc;
	wndclass.cbWndExtra = 0;

	RegisterClass(&wndclass);

	hwnd = CreateWindow("shortclass","short order",WS_POPUP,0,0,320,240,NULL,NULL,hinstance,NULL);

	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);

	GFX = new gfx;

	GFX->InitDDraw(hwnd);
	ShowCursor(FALSE);
	g_timer.Init();
	init();
	while(1)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
		{
			if(!GetMessage(&msg,NULL,0,0))
				return msg.wParam;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else{ 
			GFX->Clear(0xFFFFFFFF);
			UpdateOrders();
			UpdateBurgers();
			DrawBackground(GFX);
			DrawOrders(GFX);
			DrawScore(GFX);
			
			DrawBurgers(GFX);
			GFX->DrawImage(x-16,y-16,CURSOR);
			
			GFX->Present();
		}
	}
	return msg.wParam;
}
