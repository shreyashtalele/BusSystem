#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H
#include <mysql.h>

class DatabaseConnection
{
    public:
        DatabaseConnection(char *);
        virtual ~DatabaseConnection();

    protected:

    private:
        MYSQL* conn;
        MYSQL_ROW row;
        MYSQL_RES *res;
        int qstate;
};

#endif // DATABASECONNECTION_H
