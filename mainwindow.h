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
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <sstream>
#include <QFile>
#include <QtConcurrent>
#include <QFuture>
#include <QMovie>
#include <QDialog>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QtConcurrent>
#include <QFuture>

#include "start.h"
#include "effect.h"
#include "phenotype.h"
#include "blup.h"
#include "ui_mainwindow.h"
#include "alphamate.h"
#include "plink.h"
#include "process.h"
#include "tool.h"
#include "loadingwight.h"
#include "h_matrix.h"
#include "terminal_dialog.h"
#include "data_view_dialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Terminal_Dialog* Terminal_log = nullptr;
    data_view_Dialog* data_view_page = nullptr;
    phenotype_select phenotype_select_line ;
    phenotype_display original_display;
    phenotype_display converted_display;

    prepare_effect_input fixed_effect_input_Discrete; //离散部分使用
    prepare_effect_input fixed_effect_input_Continuous;//连续部分使用
    prepare_effect_input random_effect_input;

    blup blup_mode ;
    fold_validate blup_fold_validate ;
    alphamate_edge alphamate_all;

    QLineEdit* out_line;
    QLineEdit* csv_line;
    QLineEdit* vcf_line;

    QStringList Rpackage ;


    QString csv_path = "";
    QString vcf_path = "";
    QString vcf_QCed_path = "";
    QString raw_path = "";
    QString A_matrix_path = "";
    QString G_matrix_path = "";
    QString H_matrix_path = "";
    QString output_path = "";
    QString Rdata_path = "";
    QString blup_varcomp_path = "";
    QString blup_formula_ans_path = "";
    QString plink_log_path = "";

    QString classical_GEBV_path = "";
    QString bayes_GEBV_path = "";
    QString Gender_path = "";
    QString Alphamate_running_path= "";

    QStringList phenotype_list ;
    QStringList factor_phenotype_list;
    QStringList numeric_phenotype_list;
    unsigned int target_phenotype_index= 0 ;
    unsigned int AnimalID_phenotype_index= 0 ;
    unsigned int Dam_phenotype_index= 0 ;
    unsigned int Sire_phenotype_index= 0 ;
    int Gender_phenotype_index = -1;

    unsigned int fist_convert_flag = 1;
    QStringList fixed_effect_list ;
    QStringList Discrete_fixed_effect_list ;
    QStringList Continuous_fixed_effect_list ;
    QStringList random_effect_list ;

    bool phenotype_converted_flag = false;

    bool Discrete_selected_fixed_flag = false;
    bool Continuous_selected_fixed_flag = false;
    bool selected_random_flag = false;
    bool gender_flag = false;
    bool blup_Hblup_flag = false;

    bool start_complete_flag = false;
    bool phenotype_complete_flag = false;
    bool effect_complete_flag = false;

    void init();
    void Phenotype_Init();
    void Effect_Init();
    void classical_method_Init();
    bool A_G_matirx_build();
    void Alphamate_Init();


    //for QC
    bool callPlinkGwas(QString* genotype, QString out);
    bool plink_convert_format(QString* genotype, QString out);
public slots:
    void sent_massage_to_terminal(QString message);
signals:
    void resetWindowSig();
    void setMsgBoxSig(const QString &title, const QString &text);


private slots:
    void receive_numeric_factor(QStringList Numeric_list,QStringList factor_list);

    void on_csv_pushButton_clicked();

    void on_output_pushButton_clicked();

    void on_vcf_pushButton_clicked();

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

    void on_effect_next_pushButton_clicked();

    void on_BLUP_accept_pushButtom_clicked();

    void on_AnimalID_ComboBox_currentIndexChanged(int index);

    void on_cross_validation_checkBox_stateChanged(int arg1);

    void on_classical_validate_pushButtom_clicked();

    void on_alphmate_checkBox_stateChanged(int arg1);

    void on_BLUP_mode_ComboBox_currentIndexChanged(int index);

    void on_GenderFile_checkBox_3_stateChanged(int arg1);

    void on_classical_mate_Button_3_clicked();

    void on_bayesrunpushButton_clicked();

    void on_fixed_phenotype_pr_TableView_2_clicked(const QModelIndex &index);

    void on_fixed_select_Button_2_clicked();

    void on_fixed_selected_TableView_2_clicked(const QModelIndex &index);

    void on_fixed_exclude_Button_2_clicked();

    void on_fixed_accept_pushButton_2_clicked();

    void on_random_effec_testing_ComboBox_currentIndexChanged(int index);

    void on_trans_formula_1_lineEdit_returnPressed();

    void on_Gender_CheckBox_stateChanged(int arg1);

    void on_Blup_CheckBox_stateChanged(int arg1);


    void on_toolButton_clicked();

    void on_qc_running_pushButton_clicked();

    void on_qc_vie_wlog_pushButton_clicked();

    void on_BLUP_next_pushButton_clicked();

    void on_Bayes_next_pushButton_clicked();

    void on_classical_more_Button_triggered(QAction *arg1);

    void on_bayes_GEBVform_comboBox_currentIndexChanged(int index);

    void on_NrmMatrixFileform_comboBox_currentIndexChanged(int index);

    void on_GEBVform_comboBox_currentIndexChanged(int index);

    void on_OutputFolder_commandLinkButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_phenotype_ComboBox_currentIndexChanged(int index);

    void on_genofillcheckBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    volatile bool runningFlag = false;
};
#endif // MAINWINDOW_H

