#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QMainWindow>
#include <QApplication>
#include <QMainWindow>
#include <QFileDialog>
#include <QAbstractItemView>
#include <QProcess>
#include <QDebug>
#include <QList>
#include <QThread>
#include <QMap>
#include <QButtonGroup>
#include <QDateTime>
#include <QThread>
#include <QMessageBox>
#include <QComboBox>
#include <QProcess>
#include <QTextBrowser>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTableView>
#include <QStandardItemModel>
#include <QListWidget>
#include <sstream>

#include "start.h"
#include "effect.h"
#include "phenotype.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QLineEdit* out_line;
    QLineEdit* csv_line;
    QLineEdit* vcf_line;

    QString csv_path = "";
    QString vcf_path = "";
    QString A_matrix_path = "";
    QString G_matrix_path = "";
    QString output_path = "";
    QStringList phenotype_list ;
    unsigned int target_phenotype_index= 0 ;
    unsigned int fist_convert_flag = 1;
    QStringList fixed_effect_list ;
    QStringList random_effect_list ;

    bool phenotype_converted_flag = false;

    bool selected_fixed_flag = false;
    bool selected_random_flag = false;

    void init();
    void Effect_Init();
private slots:
    void on_csv_pushButton_clicked();

    void on_output_pushButton_clicked();

    void on_vcf_pushButton_clicked();

    void on_csv_lineEdit_editingFinished();

    void on_vcf_lineEdit_editingFinished();

    void on_output_lineEdit_editingFinished();

    void on_start_next_pushButton_clicked();

    void on_outlier_swith_stateChanged(int arg1);

    void on_phenotype_run_Button_clicked();

    void on_convert_swith_stateChanged(int arg1);

    void on_phenotype_convert_Button_clicked();

    void on_phenotype_reset_Button_clicked();

    void on_phenotype_accept_Button_clicked();

    void on_phenotype_next_pushButton_clicked();

    void on_qc_next_pushButton_clicked();


    void on_fixed_phenotype_pr_TableView_clicked(const QModelIndex &index);

    void on_fixed_select_Button_clicked();

    void on_fixed_exclude_Button_clicked();

    void on_fixed_accept_pushButton_clicked();

    void on_fixed_selected_TableView_clicked(const QModelIndex &index);

    void on_random_select_Button_clicked();

    void on_random_exclude_Button_clicked();


    void on_random_phenotype_pr_TableView_clicked(const QModelIndex &index);

    void on_random_selected_TableView_clicked(const QModelIndex &index);

    void on_random_accept_pushButton_clicked();

    void on_effect_reset_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
