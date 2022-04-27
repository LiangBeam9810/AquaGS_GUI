#include "mainwindow.h"
#ifndef ALPHAMATE_H
#define ALPHAMATE_H



struct alphamate_edge{
    QComboBox* GEBVform_comboBox = NULL;
    QComboBox* NrmMatrixFileform_comboBox = NULL;

    QLineEdit* NrmMatrix_lineEdit = NULL;
    QLineEdit*  SelCriterionFile_lineEdit = NULL;
    QCheckBox* GenderFile_CheckBox = NULL;
    QLineEdit*    GenderFile_lineEdit= NULL;

    QSpinBox*  NumberOfMatings_spinBox = NULL;
    QSpinBox*   NumberOfMaleParents_spinBox = NULL;
    QSpinBox*   NumberOfFemaleParents_spinBox = NULL;
    QSpinBox*   TargetDegree_spinBox = NULL;

    QCheckBox*  EqualizeMaleContributions_checkBox = NULL;
    QCheckBox*  EqualizeFemaleContributions_checkBox = NULL;
    QDoubleSpinBox*  TargetCoancestryRate_doubleSpinBox = NULL;
    QCheckBox*  EvaluateFrontier_checkBox = NULL;
    QCheckBox*  ModeMinCoancestry_checkBox = NULL;
    QCheckBox*  ModeMinInbreeding_checkBox = NULL;
    QCheckBox*  ModeMaxCriterion_checkBox = NULL;
    QCheckBox*  ModeOpt_checkBox = NULL;

    QToolButton*  classical_more_Button = NULL;
    QPushButton*  classical_mate_Button = NULL;
};


void alphamate_page_Init(alphamate_edge blup_alphamate_all);
void alphmate_enable_all(alphamate_edge blup_alphamate_all);
void alphmate_disable_all(alphamate_edge blup_alphamate_all);
void alphmate_able_gender(alphamate_edge blup_alphamate_all,bool state);
bool running_alphamate(alphamate_edge blup_alphamate_all,QString Alphamate_running_path,QString output_path);

#endif // ALPHAMATE_H
