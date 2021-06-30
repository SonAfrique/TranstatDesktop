#ifndef ADDCOUNTER_H
#define ADDCOUNTER_H

#include <QDialog>
#include "debugger.h"
namespace Ui {
class AddCounter;
}

class AddCounter : public QDialog
{
    Q_OBJECT

public:
    explicit AddCounter(QWidget *parent, std::map<int, dataPoint>&, std::map<int, std::map<QString, int>>&);
    ~AddCounter();


private:
    int counter_line_id;
    int new_counter_line_id;
public:
    std::map<int, dataPoint> counter_lines;
    std::map<int, std::map<QString, int>> counter_lines_data;
private:
    void add_counter_line();
    void add_counter_line_initial_data();
    dataPoint _new_data_point;

signals:
    void send_counter_addition_successful(int &);
    void send_counter_addition_cancelled();
    //
private slots:
    void on_btn_save_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::AddCounter *ui;
};

#endif // ADDCOUNTER_H
