#include "DatabaseConnection.h"
#include <iostream>

using namespace std;

DatabaseConnection::DatabaseConnection()
{
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"127.0.0.1","rushi","Rushi_1192#","ttms",3306,NULL,0);
    if(conn)
        cout<<"Connected";
    else
        cout << "Not connected" << endl;
    //ctor
}

DatabaseConnection::~DatabaseConnection()
{
    //dtor
}
