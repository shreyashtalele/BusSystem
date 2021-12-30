#ifndef BUSMENU_H
#define BUSMENU_H
#include <tchar.h>
#include <windows.h>

class BusMenu
{
    public:
        BusMenu();
        int CreateTestWindow(HINSTANCE hInst);
        virtual ~BusMenu();

    protected:

    private:
        //TCHAR szClassName[] = _T("Bus Reservation System");
        HWND hWindow;
        LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

};

#endif // BUSMENU_H
