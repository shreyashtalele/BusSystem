#ifndef BUSMENU_H
#define BUSMENU_H
#include <tchar.h>
#include <windows.h>

class BusMenu
{
    public:
        BusMenu();
        virtual ~BusMenu();

    protected:

    private:
        //TCHAR szClassName[] = _T("Bus Reservation System");
        LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

};

#endif // BUSMENU_H
