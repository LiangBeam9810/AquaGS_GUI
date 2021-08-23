#include "mainwindow.h"

#ifndef EFFECT_H
#define EFFECT_H
bool prepare_effect(QString input_path,QString output_path,
                    QTableView* original_tableview,QTableView* selected_tableview,
                    unsigned int target_index,
                    unsigned  int flag,
                    QStringList fixed_effect_list);
void add_item2fixed_effect_list(QTableView* original_tableview,QStringList phenotypelist,QStringList* fixed_effect_list);
void remove_item2table_listwidget(QListWidget* selected_PhenoListWidget,QStringList* fixed_effect_list);
#endif // EFFECT_H
