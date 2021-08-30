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

    QString csv_path = "";
    QString Matrix_path = "";
    QString output_path = "";
    QStringList fixed_effect_list ;
    QStringList random_effect_list ;
};

struct fold_validate{
   QCheckBox* cross_validation_checkBox = NULL;
   QComboBox* k_flod_times_ComboBox = NULL;
   QTextBrowser* accuracyA_textBrowser = NULL;
   QTextBrowser* accuracyG_textBrowser = NULL;

   QString csv_path = "";
   QString Matrix_path = "";
   QString output_path = "";
   QStringList fixed_effect_list ;
   QStringList random_effect_list;
};
void blup_Init(blup blup_input);
void blup_fold_validate_Init(fold_validate fold_validate_input);
#endif // BLUP_H
