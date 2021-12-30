#include "BusMenu.h"
#include <windows.h>
#include <iostream>

using namespace std;

/*  Make the class name into a global variable  */

BusMenu::BusMenu()
{
    //ctor

    cout<<"Linking succesfull";
}

BusMenu::~BusMenu()
{
    //dtor
}

int BusMenu::CreateTestWindow(HWND mainWindow)
{
    WNDCLASS wincl;

    if (!GetClassInfo(hInst, thisClassName, &wincl))
    {
        ...
        wincl.hInstance = hInst;
        wincl.lpszClassName = thisClassName;
        wincl.lpfnWndProc = &ThisWindowProc;

        if (RegisterClass(&wincl) == 0)
            return -1;
    }

    hWindow = CreateWindow(..., hInst, this);
    if (hWindow == NULL)
        return -1;

    ...

    MSG msg;
    while (GetMessage(&msg, hWindow, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyWindow(hWindow);
    hWindow = NULL;

    return msg.wParam;
}

LRESULT CALLBACK BusMenu::ThisWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    viewvars *view;

    if (message == WM_NCCREATE)
    {
        CREATESTRUCT *cs = (CREATESTRUCT*) lParam;
        view = (viewvars*) cs->lpCreateParams;

        SetLastError(0);
        if (SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG_PTR) view) == 0)
        {
            if (GetLastError() != 0)
                return FALSE;
        }
    }
    else
    {
        view = (viewvars*) GetWindowLongPtr(hwnd, GWL_USERDATA);
    }

    if (view)
        return view->WindowProc(message, wParam, lParam);

    return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT BusMenu::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // you can access non-static members in here...

    switch (message)
    {
        case WM_PAINT:
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hWindow, message, wParam, lParam);
    }
}
