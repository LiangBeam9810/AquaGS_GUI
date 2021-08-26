#include "mainwindow.h"

#ifndef PHENOTYPE_H
#define PHENOTYPE_H

/*--------------------------------------*/
void prepare_phenotype(QString csv_path,
                       QStringList* phenotype_list ,
                       QComboBox*  ComboBox);

void init_ready_for_run(QTextBrowser* skewnessddisplay_1,
                        QTextBrowser* kurtosisdisplay_1,
                        QLabel* horizontallabel_1,
                        QTextBrowser* skewnessddisplay_2,
                        QTextBrowser* kurtosisdisplay_2,
                        QLabel* horizontallabel_2,
                        QCheckBox* outlierswith,
                        QComboBox* phenotypeComboBox,
                        QPushButton* accept_Button,
                        QCheckBox* convert_swith,
                        unsigned int* outlier_state,
                        unsigned int* fist_convert_flag,
                        unsigned int* target_phenotype_index);

void change_convert_wight_state(int state, QPushButton* convert_Button,QPushButton* reset_Button,QPushButton* accept_Button,QToolButton* detial_Button);

void clean_normality_index( QTextBrowser* skewnessddisplay,
                            QTextBrowser* kurtosisdisplay,
                            QLabel* horizontallabel);

bool outlier_elimination(QString* csv_path,
                    unsigned int outlier_state,
                    unsigned inttarget_phenotype_index);

bool display_normality(QString input_path,
                       QString output_path,
                       unsigned int target_phenotype_index,
                       QString type,
                       QTextBrowser* skewnessdisplay,
                       QTextBrowser* kurtosisdisplay,
                       QLabel* graphicedisplay);

bool convert_phenotype(QString csv_path_new,unsigned int target_phenotype_index_new,unsigned intfist_convert_flag);
bool check_convert_path_of_phenotype(bool converted_flag ,QCheckBox* convert_swith);
#endif // PHENOTYPE_H
