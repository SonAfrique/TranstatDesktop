#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QDialog>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QtSql>
#include "debugger.h"

class DbConnection
{
public:
    DbConnection();
public:
    void conn_close();
    bool conn_open();
    QSqlDatabase db;
};

#endif // DBCONNECTION_H
