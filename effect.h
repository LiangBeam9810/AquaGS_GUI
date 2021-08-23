#include "mainwindow.h"

#ifndef EFFECT_H
#define EFFECT_H
bool prepare_effect(QString input_path,QString output_path,QTableView* tableview,
                    unsigned int index,unsigned  int flag,
                    QStringList fixed_effect_list);
void add_item2table_listwidget(QTableView* phenotype_pr_TableView,QListWidget* excludedPhenoListWidget,QStringList phenotypelist,QStringList* fixed_effect_list);
void remove_item2table_listwidget(QListWidget* selected_PhenoListWidget,QStringList* fixed_effect_list);
#endif // EFFECT_H
