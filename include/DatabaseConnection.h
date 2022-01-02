#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H
#include <mysql.h>
#include <windows.h>

class DatabaseConnection
{
    public:
        MYSQL* conn;
        DatabaseConnection(char *);
        DatabaseConnection();
        virtual ~DatabaseConnection();
        //void setEditText(HWND);

    protected:

    private:
        MYSQL_ROW row;
        MYSQL_RES *res;
        int qstate;
};

#endif // DATABASECONNECTION_H
