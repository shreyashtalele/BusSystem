#ifndef UNICODE
#define UNICODE
#endif 

#include <tchar.h>
#include <windows.h>
#include "include/BusMenu.h"

#define BUSMENU 301
#define PASSENGERMENU 302
#define TICKETMENU 303
#define HELPMENU 304
#define ABOUTMENU 308
#define MAXWIDTH 900
#define MAXHEIGHT 700


void AddMenu(HWND);
void addBusMenu(HWND,int,wchar_t[]);
void addTicketMenu(HWND,int);

//HWND bus_window,ticket_window;

HMENU hmenu;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
wchar_t szClassName[] = L"Bus Reservation System";

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           L"Bus Reservation System",       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           MAXWIDTH,                 /* The programs width */
           MAXHEIGHT,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    COLORREF color = RGB(135,205,235);
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            AddMenu(hwnd);
            break;

        case WM_DESTROY:{
            ShowWindow(hwnd,SW_SHOW); /* send a WM_QUIT to the message queue */
            BusMenu bm;
        }
        /*case WM_QUIT:
            ShowWindow(hwnd,SW_MAXIMIZE); */
            break;

        case WM_COMMAND:{
            switch(wParam){
                case HELPMENU:
                    MessageBoxEx(hwnd,L"Help for application",L"Help",(UINT)MB_OK,(WORD)0);
                    break;

                case BUSMENU:
                    {
                        addBusMenu(hwnd,SW_SHOW,L"Bus menu is clicked");
                        addTicketMenu(hwnd,SW_HIDE);
                    }
                    break;
                
                case TICKETMENU:
                    {
                        addBusMenu(hwnd,SW_HIDE,L"Ticket menu is clicked");
                        addTicketMenu(hwnd,SW_SHOW);
                        color = RGB(0,255,0);
                        //MessageBoxEx(hwnd,L"Help for application",L"Ticket Menu",(UINT)MB_OK,(WORD)0);
                    }
                    break;
            }
        }
            break;

        case WM_CTLCOLORSTATIC:
        {
            HDC hdcStatic = (HDC) wParam;
            SetTextColor(hdcStatic, RGB(0,0,0));
            SetBkColor(hdcStatic, color);
            return (INT_PTR)CreateSolidBrush(color);
                // color_changer(hMainWindow,0,0,0);
        }

        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

void AddMenu(HWND hwnd){
    hmenu = CreateMenu();

    AppendMenu(hmenu,MF_STRING,BUSMENU,L"Bus");
    AppendMenu(hmenu,MF_STRING,PASSENGERMENU,L"Passenger");
    AppendMenu(hmenu,MF_STRING,TICKETMENU,L"Ticket");
    AppendMenu(hmenu,MF_STRING,HELPMENU,L"Help");
    AppendMenu(hmenu,MF_STRING,ABOUTMENU,L"About Us");

    SetMenu(hwnd,hmenu);
}

void addBusMenu(HWND hwnd,int status,wchar_t msg []){
    HWND bus_window = CreateWindowEx(0,L"Static",L"",WS_VISIBLE | WS_CHILD,0,0,MAXWIDTH,MAXHEIGHT,hwnd,NULL,NULL,NULL);

    CreateWindowEx(0,L"Static",msg,WS_VISIBLE | WS_CHILD,200,75,150,15,bus_window,NULL,NULL,NULL);        
    ShowWindow(bus_window,status);
    ShowWindow(bus_window,status);
}

void addTicketMenu(HWND hwnd,int status){
    HWND ticket_window = CreateWindowEx(0,L"Static",L"",WS_VISIBLE | WS_CHILD,0,0,MAXWIDTH,MAXHEIGHT,hwnd,NULL,NULL,NULL);

    CreateWindowEx(0,L"Static",L"Ticket menu",WS_VISIBLE | WS_CHILD,200,175,150,15,ticket_window,NULL,NULL,NULL);        
    ShowWindow(ticket_window,status);
    ShowWindow(ticket_window,status);
}




