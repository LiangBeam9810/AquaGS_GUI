#include "mainwindow.h"

#ifndef BLUP_H
#define BLUP_H

struct blup
{
    QComboBox* BLUP_mode_ComboBox = NULL;
    QListView* fiexd_effect_listView = NULL;
    QListView* random_effect_listView = NULL;
    QComboBox* trans_formula_1_ComboBox = NULL;
    QComboBox* trans_formula_2_ComboBox = NULL;
    QPushButton* BLUP_accept_pushButtom = NULL;

    QString csv_path = "";
    QString Matrix_path = "";
    QString output_path = "";
    QStringList fixed_effect_list ;
    QStringList random_effect_list;
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

#endif // BLUP_H
