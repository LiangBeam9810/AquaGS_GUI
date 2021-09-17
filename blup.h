#include "mainwindow.h"

#ifndef BLUP_H
#define BLUP_H

struct blup
{
    QComboBox* BLUP_mode_ComboBox = NULL;
    QLineEdit* fiexd_effect_lineedit = NULL;
    QLineEdit* random_effect_lineedit = NULL;
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

   QString Rdata_path = "";
   QString output_path = "";
   QStringList fixed_effect_list ;
   QStringList random_effect_list;
};
struct alphamate_edge{
    QCheckBox* alphmate_checkBox = NULL;

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

void blup_Init(blup blup_input);
void blup_fold_validate_Init(fold_validate fold_validate_input);
void blup_alphamate_Init(alphamate_edge blup_alphamate_all);

bool blup_build(blup blup_input);

bool classical_method_cross_validation_and_display(blup blup_mode,fold_validate blup_fold_validate);
void Process_runing_gif(QProcess* Process,QString title);

void alphmate_enable_all(alphamate_edge blup_alphamate_all);
void alphmate_disable_all(alphamate_edge blup_alphamate_all);
void alphmate_able_gender(alphamate_edge blup_alphamate_all,bool state);
bool running_alphamate(alphamate_edge blup_alphamate_all,QString Alphamate_running_path,QString output_path);
#endif // BLUP_H
