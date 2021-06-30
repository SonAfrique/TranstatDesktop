#ifndef ANALYSISID_H
#define ANALYSISID_H

#include <QDialog>
#include "dbconnection.h"

namespace Ui {
class AnalysisId;
}

class AnalysisId : public QDialog
{
    Q_OBJECT

public:
    explicit AnalysisId(QWidget *parent = nullptr);
    ~AnalysisId();

private slots:
    void on_btn_save_clicked();
    void on_btn_cancel_clicked();

private:
    QString analysis_id;
    DbConnection* dbConnection;
    void add_new_analysis_id_to_db();
    void check_for_data_integrity();
    void check_for_duplicate_analysis_id();
    bool _data_ready_for_storage = false;
    bool _analysis_id_exists = true;
    bool _id_added_successfully = false;

signals:
    void send_analysis_id_added_successfully(QString&);
    void send_analysis_id_addition_cancelled();


private:
    Ui::AnalysisId *ui;
};

#endif // ANALYSISID_H
