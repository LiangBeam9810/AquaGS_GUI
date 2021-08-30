#include "mainwindow.h"

#ifndef EFFECT_H
#define EFFECT_H

struct prepare_effect_input
{
    QString input_path;
    QString output_path;
    QString A_matrix_path;
    QString G_matrix_path;
    QTableView* original_tableview;
    QTableView* selected_tableview;
    QComboBox* animal_combobox;
    QComboBox* randeff_testing_combobox;
    unsigned int target_index;
    unsigned  int process_random_flag;
    QStringList* fixed_effect_list ;
    QStringList* random_effect_list;
};

bool prepare_effect(prepare_effect_input effect_input);
void clean_effect_table(QTableView* tableview);
void add_item2effect_list(QTableView* original_tableview,QStringList phenotypelist,QStringList* fixed_effect_list);
void remove_item_from_effect_list(QTableView* selected_tableview,QStringList* fixed_effect_list);
bool isTableView_empty(QTableView* tableview);
int get_phenotype_index(QTableView*tableview,QStringList phenotype_list);
void change_select_exclude_Button(unsigned int flag,bool elected_flag,QPushButton* select_Button,QPushButton* exclude_Button);
#endif // EFFECT_H
