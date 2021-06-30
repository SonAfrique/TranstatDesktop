#include "analysisid.h"
#include "ui_analysisid.h"

AnalysisId::AnalysisId(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalysisId)
{
    ui->setupUi(this);
    this->setFixedSize(420, 260);

    dbConnection = new DbConnection;
}

AnalysisId::~AnalysisId()
{
    delete ui;
}

void AnalysisId::on_btn_save_clicked()
{
    analysis_id = ui->le_analysis_id->text();
    check_for_data_integrity();
    if(_data_ready_for_storage){
        check_for_duplicate_analysis_id();
            if(!_analysis_id_exists){
                add_new_analysis_id_to_db();
                if(_id_added_successfully){
                    emit send_analysis_id_added_successfully(analysis_id);
                }
            }
    }
}


void AnalysisId::on_btn_cancel_clicked()
{
    emit send_analysis_id_addition_cancelled();
}

void AnalysisId::add_new_analysis_id_to_db()
{
    dbConnection->conn_open();
    QDateTime currentTime = QDateTime::currentDateTime();
    QString dateString = currentTime.toString("yyyy-MM-dd T hh:mm:ss");
    if(dbConnection->conn_open()){
         QSqlQuery query(QSqlDatabase::database("MyConnect"));
         query.prepare(QString("INSERT INTO analysis (analysis_id) "
                               "VALUES (:analysis_id)"));
         query.bindValue(":analysis_id", analysis_id);

        if(!query.exec()){
            Debug(query.lastError());
            QMessageBox::critical(this, "Analyst Id Insertion Database Error", query.lastError().text());
            return;
        }else{
            _id_added_successfully = true;
                }
        }
}

void AnalysisId::check_for_data_integrity()
{
    if(ui->le_analysis_id->text().isEmpty()){
        QMessageBox::critical(this, "Incomplete Data", "Please provide a valid analysis Id.");
        return;
    }else{
        _data_ready_for_storage = true;
    }

}

void AnalysisId::check_for_duplicate_analysis_id()
{
    if(dbConnection->conn_open()){
         QSqlQuery query(QSqlDatabase::database("MyConnect"));
         query.prepare(QString("SELECT COUNT(analysis_id) from analysis WHERE analysis_id = :analysis_id"));
         query.bindValue(":analysis_id", analysis_id);

        if(!query.exec()){
            Debug(query.lastError());
            QMessageBox::critical(this, "Analyst Duplicate Inquiry Database Error", query.lastError().text());
            return;
        }else{
            while(query.next()){
                int number_of_ids = query.value(0).toInt();
                if(number_of_ids>0){
                    _analysis_id_exists=true;
                    QMessageBox::critical(this, "Duplicate Analysis Id", "Analysis Id already exists.");
                           return;
                }else{
                    _analysis_id_exists = false;
                }
              }
        }
    }
}

