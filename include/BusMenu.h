#include <iostream>
#include <windows.h>

using namespace std;

class BusMenu{
    public:
        BusMenu();
        void createWindow(HWND);
};

BusMenu::BusMenu(){
    cout<<"linking success full";
}

void BusMenu::createWindow(HWND hwnd){
    HWND bus = CreateWindowEx(0,L"Bus",L"",WS_CHILD | WS_VISIBLE,0,0,950,900,hwnd,NULL,NULL,NULL);
    CreateWindowEx(0,L"Static",L"Element Symbol:-",WS_VISIBLE | WS_CHILD,200,75,150,15,bus,NULL,NULL,NULL);
    ShowWindow(bus,SW_SHOW);
}