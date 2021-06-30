#include "dbconnection.h"

DbConnection::DbConnection()
{

}

void DbConnection::conn_close()
{
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
}

bool DbConnection::conn_open()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("/home/vt/projects/transtatDesktop/database/transtat.db");
        if(!db.open()){
            Debug(db.lastError().text());
            LOGx("[Error]: Database did NOT Open...");
            return false;
        }else{
            LOGx("[Success]: Database Successfully Opened...");
        return true;
   }
}
