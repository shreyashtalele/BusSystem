#include "DatabaseConnection.h"
#include <iostream>

using namespace std;

DatabaseConnection::DatabaseConnection(char* query)
{
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"127.0.0.1","rushi","Rushi_1192#","ttms",3306,NULL,0);
    if(conn){
        cout<<"Connected";

		qstate = mysql_query(conn, query);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				cout<<"\n"<<row[0]<<row[1]<<row[2];
			}
		}
		else
		{
			cout << "\nQuery failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		cout<<"Connection to database has failed!";
	}

    //ctor
}

DatabaseConnection::~DatabaseConnection()
{
    //dtor
}

DatabaseConnection::DatabaseConnection(){
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"127.0.0.1","rushi","Rushi_1192#","ttms",3306,NULL,0);
}
