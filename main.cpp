#ifndef UNICODE
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include "include\DatabaseConnection.h"

#define MAXWIDTH 900
#define MAXHEIGHT 700

#define BUSMENU 301
#define PASSENGERMENU 302
#define TICKETMENU 303
#define HELPMENU 304
#define ABOUTMENU 305
#define BUS_BUTTON_SEARCH 306

using namespace std;

void AddMenu(HWND);
void addBusMenu(HWND,int);
void addTicketMenu(HWND,int);
void addPassengerMenu(HWND,int);
void addAboutMenu(HWND,int);

//HWND bus_window,ticket_window;

HMENU hmenu;
HWND hedit;
const wchar_t *GetWC(const char *c)
{
    const size_t cSize = strlen(c)+1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs (wc, c, cSize);

    return wc;
}
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
           300,       /* Windows decides the position */
           100,       /* where the window ends up on the screen */
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
    SCROLLINFO si;

    // These variables are required to display text.
    static int xClient;     // width of client area
    static int yClient;     // height of client area
    static int yChar; // vertical scrolling unit
    static int yPos;  // current vertical scrolling position

    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            AddMenu(hwnd);
            break;

        case WM_DESTROY:{
            PostQuitMessage(0); /* send a WM_QUIT to the message queue */
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
                        addBusMenu(hwnd,SW_SHOW);
                        addTicketMenu(hwnd,SW_HIDE);
                        addPassengerMenu(hwnd,SW_HIDE);
                        addAboutMenu(hwnd,SW_HIDE);
                        DatabaseConnection dc = DatabaseConnection("SELECT * FROM traindata;");
                        //dc.setEditText(hedit);
                    }
                    break;

                case TICKETMENU:
                    {
                        addBusMenu(hwnd,SW_HIDE);
                        addTicketMenu(hwnd,SW_SHOW);
                        addPassengerMenu(hwnd,SW_HIDE);
                        addAboutMenu(hwnd,SW_HIDE);
                        //MessageBoxEx(hwnd,L"Help for application",L"Ticket Menu",(UINT)MB_OK,(WORD)0);
                    }
                    break;

                case PASSENGERMENU:
                    {
                        addBusMenu(hwnd,SW_HIDE);
                        addTicketMenu(hwnd,SW_HIDE);
                        addPassengerMenu(hwnd,SW_SHOW);
                        addAboutMenu(hwnd,SW_HIDE);
                    }
                    break;

                case ABOUTMENU:
                    {
                        addBusMenu(hwnd,SW_HIDE);
                        addTicketMenu(hwnd,SW_HIDE);
                        addPassengerMenu(hwnd,SW_HIDE);
                        addAboutMenu(hwnd,SW_SHOW);
                    }
                    break;

                case BUS_BUTTON_SEARCH:
                    {
                        //MessageBoxEx(hwnd,L"Button is clicked",L"Trail",(UINT)MB_OK,(WORD)0);
                        DatabaseConnection dc;
                        MYSQL_ROW row;
                        MYSQL_RES *res;
                        wchar_t data;
                        char* query = "SELECT * FROM traindata;";
                        if(dc.conn){
                            cout<<"Connected";

                            int qstate = mysql_query(dc.conn, query);
                            if (!qstate)
                            {
                                res = mysql_store_result(dc.conn);
                                while (row = mysql_fetch_row(res))
                                {
                                    SetWindowText(hedit,GetWC(row[0]));
                                }

                            }
                            else
                            {
                                cout << "\nQuery failed: " << mysql_error(dc.conn) << endl;
                            }
                        }
                        else {
                            cout<<"Connection to database has failed!";
                        }
                    }
                    break;
            }
        }
            break;

        case WM_CTLCOLORSTATIC:
        {
            HDC hdcStatic = (HDC) wParam;
            SetTextColor(hdcStatic, RGB(0,0,0));
            SetBkColor(hdcStatic, RGB(252,191,73));
            return (INT_PTR)CreateSolidBrush(RGB(252,191,73));
                // color_changer(hMainWindow,0,0,0);
        }
        break;

        case WM_CTLCOLORBTN:
        {
            HDC hdcStatic = (HDC) wParam;
            SetTextColor(hdcStatic, RGB(0,0,0));
            SetBkColor(hdcStatic, RGB(247,127,0));
            return (INT_PTR)CreateSolidBrush(RGB(247,127,0));
        }
        break;

        case WM_CTLCOLOREDIT:
        {
            HDC hdcStatic = (HDC) wParam;
            SetTextColor(hdcStatic, RGB(255,255,255));
            SetBkColor(hdcStatic, RGB(247,127,0));
            return (INT_PTR)CreateSolidBrush(RGB(247,127,0));
        }
        break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);



            FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(252,191,73)));

            EndPaint(hwnd, &ps);
        }
        break;

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

//function for creating bus window
void addBusMenu(HWND hwnd,int status){
    HWND bus_window = CreateWindowEx(0,szClassName,L"",WS_VISIBLE | WS_CHILD,0,0,MAXWIDTH,MAXHEIGHT,hwnd,NULL,NULL,NULL);

    CreateWindowEx(0,L"Static",L"Bus menu",WS_VISIBLE | WS_CHILD ,200,75,150,15,bus_window,NULL,NULL,NULL);
    hedit = CreateWindowEx(0,L"Edit",L"Edit",WS_VISIBLE | WS_CHILD,450,10,100,25,bus_window,(HMENU)BUS_BUTTON_SEARCH,NULL,NULL);
    CreateWindowEx(0,L"Button",L"Search",WS_VISIBLE | WS_CHILD,450,50,100,25,bus_window,(HMENU)BUS_BUTTON_SEARCH,NULL,NULL);
    ShowWindow(bus_window,status);
    ShowWindow(bus_window,status);
}

//function for creating ticket window
void addTicketMenu(HWND hwnd,int status){
    HWND ticket_window = CreateWindowEx(0,szClassName,L"",WS_VISIBLE | WS_CHILD,0,0,MAXWIDTH,MAXHEIGHT,hwnd,NULL,NULL,NULL);

    CreateWindowEx(0,L"Static",L"Ticket menu",WS_VISIBLE | WS_CHILD,200,175,150,15,ticket_window,NULL,NULL,NULL);
    ShowWindow(ticket_window,status);
    ShowWindow(ticket_window,status);
}

//function for creating passenger window
void addPassengerMenu(HWND hwnd,int status){
    HWND passenger_window = CreateWindowEx(0,szClassName,L"",WS_VISIBLE | WS_CHILD,0,0,MAXWIDTH,MAXHEIGHT,hwnd,NULL,NULL,NULL);

    CreateWindowEx(0,L"Static",L"Passenger menu",WS_VISIBLE | WS_CHILD,200,275,150,15,passenger_window,NULL,NULL,NULL);
    //CreateWindowEx(0,L"Edit",L"Passenger menu",WS_VISIBLE | WS_CHILD,200,275,150,15,passenger_window,NULL,NULL,NULL);
    ShowWindow(passenger_window,status);
    ShowWindow(passenger_window,status);
}

//function for creating passenger window
void addAboutMenu(HWND hwnd,int status){
    HWND about_window = CreateWindowEx(0,szClassName,L"",WS_VISIBLE | WS_CHILD | WS_VSCROLL,0,0,MAXWIDTH,MAXHEIGHT,hwnd,NULL,NULL,NULL);

    wchar_t about[] = L"This is bus reservation system\n"
                      L"This is developed by rushi";

    CreateWindowEx(0,L"Static",about,WS_VISIBLE | WS_CHILD,100,80,700,500,about_window,NULL,NULL,NULL);

    ShowScrollBar(about_window,SB_VERT,TRUE);

    ShowWindow(about_window,status);
    ShowWindow(about_window,status);
}





