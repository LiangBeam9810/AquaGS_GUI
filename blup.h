#include "mainwindow.h"

#ifndef BLUP_H
#define BLUP_H

struct blup
{
    QComboBox* BLUP_mode_ComboBox = NULL;
    QListWidget* fiexd_effect_listwidget = NULL;
    QListWidget* random_effect_listwidget = NULL;
    QComboBox* trans_formula_1_ComboBox = NULL;
    QComboBox* trans_formula_2_ComboBox = NULL;
    QPushButton* BLUP_accept_pushButtom = NULL;

    QString Rdata_path = "";
    QString A_matrix_path = "";
    QString G_matrix_path = "";
    unsigned int AnimalID_index;
    unsigned int target_index;
    QString output_path = "";
    QStringList fixed_effect_list ;
    QStringList random_effect_list ;
    QStringList fixed_effect_list2R ;
    QStringList random_effect_list2R ;
};

struct fold_validate{
   QCheckBox* cross_validation_checkBox = NULL;
   QComboBox* k_flod_times_ComboBox = NULL;
   QLineEdit* ACC_lineEdit = NULL;
   QLineEdit* STD_lineEdit = NULL;
   QPushButton* cross_validation_pushbutton = NULL;

   QString csv_path = "";
   QString Matrix_path = "";
   QString output_path = "";
   QStringList fixed_effect_list ;
   QStringList random_effect_list;
};
void blup_Init(blup blup_input);
void blup_fold_validate_Init(fold_validate fold_validate_input);

bool blup_build(blup blup_input);

void classical_method_cross_validation_and_display(blup blup_mode,fold_validate blup_fold_validate);
#endif // BLUP_H
