#ifndef BUSMENU_H
#define BUSMENU_H
#include <windows.h>

class BusMenu
{
    public:
        BusMenu();
        virtual ~BusMenu();
        void createBusWindow(HWND hwnd,int status);

    protected:

    private:
};


#endif // BUSMENU_H
