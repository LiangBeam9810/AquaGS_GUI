#include "mainwindow.h"

#ifndef BLUP_H
#define BLUP_H

struct blup
{
    QComboBox* BLUP_mode_ComboBox = NULL;
    QLineEdit* fiexd_effect_lineedit = NULL;
    QLineEdit* random_effect_lineedit = NULL;
    QLineEdit* trans_formula_1_lineEdit = NULL;
    QLineEdit* trans_formula_2_lineEdit = NULL;
    QPushButton* BLUP_accept_pushButtom = NULL;
    QTextBrowser* classical_Estimate_textBrowser = NULL;
    QTextBrowser* classical_SE_textBrowser = NULL;
    QTableView* classical_varComp_tableView = NULL;


    QString Rdata_path = "";
    QString A_matrix_path = "";
    QString G_matrix_path = "";
    QString blup_varcomp_path = "";
    QString blup_formula_ans_path = "";
    QString trans_formula_1 = "";
    QString trans_formula_2 = "";
    unsigned int AnimalID_index;
    unsigned int target_index;
    QString output_path = "";
    QStringList fixed_effect_list ;
    QStringList random_effect_list ;
    QStringList fixed_effect_list2R ;
    QStringList random_effect_list2R ;
    bool blup_hblup_flag = false;
};

struct fold_validate{
   QCheckBox* cross_validation_checkBox = NULL;
   QComboBox* k_flod_times_ComboBox = NULL;
   QLineEdit* ACC_lineEdit = NULL;
   QLineEdit* STD_lineEdit = NULL;
   QPushButton* cross_validation_pushbutton = NULL;
   QSpinBox*  k_flod_rep_SpinBox = NULL;

   QString Rdata_path = "";
   QString output_path = "";
   QStringList fixed_effect_list ;
   QStringList fixed_effect_input_Discrete ;
   QStringList random_effect_list;
};


void blup_Init(blup blup_input);
void blup_fold_validate_Init(fold_validate fold_validate_input);


bool blup_build(blup blup_input);

bool classical_method_cross_validation_and_display(blup blup_mode,fold_validate blup_fold_validate);


#endif // BLUP_H
