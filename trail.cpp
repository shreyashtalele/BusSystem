#ifndef UNICODE
#define UNICODE
#endif 

#define BUSMENU 301
#define PASSENGERMENU 302
#define TICKETMENU 303
#define HELPMENU 304
#define ABOUTMENU 308

#include <windows.h>

void addMenu(HWND);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_CREATE:
        addMenu(hwnd);
        break;

    case WM_CTLCOLORSTATIC:
        {
            HDC hdcStatic = (HDC) wParam;
            SetTextColor(hdcStatic, RGB(0,0,0));
            SetBkColor(hdcStatic, RGB(135,205,235));
            return (INT_PTR)CreateSolidBrush(RGB(135,205,235));
                // color_changer(hMainWindow,0,0,0);
        }

    /*case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);



            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

            EndPaint(hwnd, &ps);
        }
        return 0;*/

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void addMenu(HWND hwnd){
    HMENU hmenu = CreateMenu();

    AppendMenu(hmenu,MF_STRING,BUSMENU,L"Bus");
    AppendMenu(hmenu,MF_STRING,PASSENGERMENU,L"Passenger");
    AppendMenu(hmenu,MF_STRING,TICKETMENU,L"Ticket");
    AppendMenu(hmenu,MF_STRING,HELPMENU,L"Help");
    AppendMenu(hmenu,MF_STRING,ABOUTMENU,L"About Us");

    SetMenu(hwnd,hmenu);
}
