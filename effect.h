#ifndef EFFECT_H
#define EFFECT_H
#include "qstring.h"
#include "qtableview.h"
#include "qcombobox.h"
#include "qdebug.h"
#include "qprocess.h"
#include "qstandarditemmodel.h"
#include "qdir.h"
#include "qmessagebox.h"
#include "process.h"
#include "qpushbutton.h"
#include "qheaderview.h"



struct prepare_effect_input
{
    QString input_path;
    QString output_path;
    QString A_matrix_path;
    QString G_matrix_path;
    QTableView* original_tableview= nullptr;
    QTableView* selected_tableview= nullptr;
    QLabel* original_label = nullptr;
    QLabel* selected_label = nullptr;
    QComboBox* animal_combobox= nullptr;
    QComboBox* randeff_testing_combobox= nullptr;
    unsigned int* AnimalID_index= nullptr;
    unsigned int target_index;
    unsigned  int process_flag;//0:随机 1：离散固定效应 2：连续固定效应
    QStringList* fixed_effect_list = nullptr;
    QStringList* random_effect_list= nullptr;
    QStringList* Discrete_fixed_effect_list = nullptr;
    QStringList* Continuous_fixed_effect_list  = nullptr;
    QStringList factor_list;
    QStringList numeric_list;
    QString target_effect_name ;
    QString AnimalID_name ;
};
void clean_tablevie(QTableView* tableview);
bool prepare_effect(prepare_effect_input effect_input);
void clean_effect_table(QTableView* tableview);
void add_item2effect_list(QTableView* original_tableview,QStringList phenotypelist,QStringList* fixed_effect_list);
void remove_item_from_effect_list(QTableView* selected_tableview,QStringList* fixed_effect_list);
bool isTableView_empty(QTableView* tableview);
int get_phenotype_index(QTableView*tableview,QStringList phenotype_list);
void change_select_exclude_Button(unsigned int flag,bool elected_flag,QPushButton* select_Button,QPushButton* exclude_Button);
#endif // EFFECT_H
