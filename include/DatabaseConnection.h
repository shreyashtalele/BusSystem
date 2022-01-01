#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H
#include <mysql.h>

class DatabaseConnection
{
    public:
        DatabaseConnection();
        virtual ~DatabaseConnection();

    protected:

    private:
        MYSQL* conn;
};

#endif // DATABASECONNECTION_H
