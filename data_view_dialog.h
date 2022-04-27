#ifndef DATA_VIEW_DIALOG_H
#define DATA_VIEW_DIALOG_H

#include <QDialog>
#include <QWidget>
#include "qtableview.h"
#include "qpushbutton.h"
#include "qstandarditemmodel.h"
#include "qdebug.h"
#include "effect.h"
#include "qmessagebox.h"

namespace Ui {
class data_view_Dialog;
}

class data_view_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit data_view_Dialog(QWidget *parent = nullptr);
    ~data_view_Dialog();
    QTableView* original_tableview = nullptr;
    QTableView* factor_tableview = nullptr;
    QTableView* Numeric_tableview = nullptr;
    QPushButton* view_data_button = nullptr;
    QPushButton* factor_select_button = nullptr;
    QPushButton* factor_disselect_button = nullptr;
    QPushButton* Numeric_select_button = nullptr;
    QPushButton* Numeric_disselect_button = nullptr;
    QPushButton* finish_button = nullptr;

    QStringList factor_list ;
    QStringList Numeric_list;
    QStringList Phenotype_list;

    QString csv_path = "";
    QString output_path = "";

    void data_view_clear();
    void data_view_refresh(QStringList Phenotype_list);
    void data_view_init(QStringList Phenotype_list);

    void data_view_add2list(bool factor_or_not,QStringList Phenotype_list);

    QStringList feedback();

    signals:
        void sendData(QStringList,QStringList);   //用来传递数据的信号

private slots:
    void on_data_view_original_TableView_clicked(const QModelIndex &index);

    void on_data_view_numeric_TableView_clicked(const QModelIndex &index);

    void on_data_view_factor_TableView_clicked(const QModelIndex &index);

    void on_select_to_num_pushButton_clicked();

    void on_disselect_to_num_pushButton_clicked();

    void on_select_to_factor_pushButton_clicked();

    void on_disselect_to_factor_pushButton_clicked();

    void on_data_view_done_pushButton_clicked();

    void on_view_data_pushButton_clicked();

private:
    Ui::data_view_Dialog *ui;
};

#endif // DATA_VIEW_DIALOG_H
