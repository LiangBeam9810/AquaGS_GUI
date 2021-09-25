#include "alphamate.h"

void blup_alphamate_Init(alphamate_edge blup_alphamate_all)
{
    blup_alphamate_all.alphmate_checkBox->setCheckState(Qt::Unchecked);
    blup_alphamate_all.classical_more_Button->setEnabled(false);
    blup_alphamate_all.classical_mate_Button->setEnabled(false);
    blup_alphamate_all.TargetDegree_spinBox->setValue(45);
    blup_alphamate_all.TargetDegree_spinBox->setEnabled(false);
    blup_alphamate_all.TargetCoancestryRate_doubleSpinBox->setValue(0.01);
    blup_alphamate_all.TargetCoancestryRate_doubleSpinBox->setEnabled(false);

    blup_alphamate_all.SelCriterionFile_lineEdit->setEnabled(false);
    blup_alphamate_all.NumberOfMatings_spinBox->setValue(30);
    blup_alphamate_all.NumberOfMatings_spinBox->setEnabled(false);
    blup_alphamate_all.NumberOfMaleParents_spinBox->setValue(10);
    blup_alphamate_all.NumberOfMaleParents_spinBox->setEnabled(false);
    blup_alphamate_all.NumberOfFemaleParents_spinBox->setValue(10);
    blup_alphamate_all.NumberOfFemaleParents_spinBox->setEnabled(false);
    blup_alphamate_all.NrmMatrix_lineEdit->setEnabled(false);
    blup_alphamate_all.ModeOpt_checkBox->setCheckState(Qt::Checked);
    blup_alphamate_all.ModeOpt_checkBox->setEnabled(false);
    blup_alphamate_all.ModeMinInbreeding_checkBox->setCheckState(Qt::Checked);
    blup_alphamate_all.ModeMinInbreeding_checkBox->setEnabled(false);
    blup_alphamate_all.ModeMinCoancestry_checkBox->setCheckState(Qt::Checked);
    blup_alphamate_all.ModeMinCoancestry_checkBox->setEnabled(false);
    blup_alphamate_all.ModeMaxCriterion_checkBox->setCheckState(Qt::Checked);
    blup_alphamate_all.ModeMaxCriterion_checkBox->setEnabled(false);

    blup_alphamate_all.GenderFile_lineEdit->setEnabled(false);
    blup_alphamate_all.GenderFile_CheckBox->setCheckState(Qt::Unchecked);
    blup_alphamate_all.EvaluateFrontier_checkBox->setCheckState(Qt::Checked);
    blup_alphamate_all.EvaluateFrontier_checkBox->setEnabled(false);
    blup_alphamate_all.EvaluateFrontier_checkBox->setCheckState(Qt::Checked);
    blup_alphamate_all.EqualizeMaleContributions_checkBox->setCheckState(Qt::Checked);
    blup_alphamate_all.EqualizeMaleContributions_checkBox->setEnabled(false);
    blup_alphamate_all.EqualizeFemaleContributions_checkBox->setCheckState(Qt::Checked);
    blup_alphamate_all.EqualizeFemaleContributions_checkBox->setEnabled(false);
}

void alphmate_enable_all(alphamate_edge blup_alphamate_all)
{

    blup_alphamate_all.classical_more_Button->setEnabled(true);
    blup_alphamate_all.classical_mate_Button->setEnabled(true);
    blup_alphamate_all.TargetDegree_spinBox->setEnabled(true);
    blup_alphamate_all.TargetCoancestryRate_doubleSpinBox->setEnabled(true);
    blup_alphamate_all.SelCriterionFile_lineEdit->setEnabled(true);
    blup_alphamate_all.NrmMatrix_lineEdit->setEnabled(true);
    blup_alphamate_all.ModeOpt_checkBox->setEnabled(true);
    blup_alphamate_all.ModeMinInbreeding_checkBox->setEnabled(true);
    blup_alphamate_all.ModeMinCoancestry_checkBox->setEnabled(true);
    blup_alphamate_all.ModeMaxCriterion_checkBox->setEnabled(true);
    blup_alphamate_all.EvaluateFrontier_checkBox->setEnabled(true);


    if(blup_alphamate_all.GenderFile_CheckBox->checkState() == Qt::Checked)
    {
        blup_alphamate_all.NumberOfMatings_spinBox->setEnabled(true);
        blup_alphamate_all.NumberOfMaleParents_spinBox->setEnabled(true);
        blup_alphamate_all.NumberOfFemaleParents_spinBox->setEnabled(true);
        blup_alphamate_all.GenderFile_lineEdit->setEnabled(true);
        blup_alphamate_all.EqualizeMaleContributions_checkBox->setEnabled(true);
        blup_alphamate_all.EqualizeFemaleContributions_checkBox->setEnabled(true);
    }else{
        blup_alphamate_all.NumberOfMatings_spinBox->setEnabled(false);
        blup_alphamate_all.NumberOfMaleParents_spinBox->setEnabled(false);
        blup_alphamate_all.NumberOfFemaleParents_spinBox->setEnabled(false);
        blup_alphamate_all.GenderFile_lineEdit->setEnabled(false);
        blup_alphamate_all.EqualizeMaleContributions_checkBox->setEnabled(false);
        blup_alphamate_all.EqualizeFemaleContributions_checkBox->setEnabled(false);
    }

}

void alphmate_disable_all(alphamate_edge blup_alphamate_all)
{

    blup_alphamate_all.classical_more_Button->setEnabled(false);
    blup_alphamate_all.classical_mate_Button->setEnabled(false);
    blup_alphamate_all.TargetDegree_spinBox->setEnabled(false);
    blup_alphamate_all.TargetCoancestryRate_doubleSpinBox->setEnabled(false);
    blup_alphamate_all.SelCriterionFile_lineEdit->setEnabled(false);
    blup_alphamate_all.NrmMatrix_lineEdit->setEnabled(false);
    blup_alphamate_all.ModeOpt_checkBox->setEnabled(false);
    blup_alphamate_all.ModeMinInbreeding_checkBox->setEnabled(false);
    blup_alphamate_all.ModeMinCoancestry_checkBox->setEnabled(false);
    blup_alphamate_all.ModeMaxCriterion_checkBox->setEnabled(false);
    blup_alphamate_all.EvaluateFrontier_checkBox->setEnabled(false);

    blup_alphamate_all.NumberOfMatings_spinBox->setEnabled(false);
    blup_alphamate_all.NumberOfMaleParents_spinBox->setEnabled(false);
    blup_alphamate_all.NumberOfFemaleParents_spinBox->setEnabled(false);
    blup_alphamate_all.GenderFile_lineEdit->setEnabled(false);
    blup_alphamate_all.GenderFile_CheckBox->setEnabled(false);
    blup_alphamate_all.EqualizeMaleContributions_checkBox->setEnabled(false);
    blup_alphamate_all.EqualizeFemaleContributions_checkBox->setEnabled(false);
}



void alphmate_able_gender(alphamate_edge blup_alphamate_all,bool state)
{
    blup_alphamate_all.NumberOfMatings_spinBox->setEnabled(state);
    blup_alphamate_all.NumberOfMaleParents_spinBox->setEnabled(state);
    blup_alphamate_all.NumberOfFemaleParents_spinBox->setEnabled(state);
    blup_alphamate_all.GenderFile_lineEdit->setEnabled(state);
    blup_alphamate_all.EqualizeMaleContributions_checkBox->setEnabled(state);
    blup_alphamate_all.EqualizeFemaleContributions_checkBox->setEnabled(state);
}

bool copy_file(QString sourceDir ,QString toDir)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile     = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
            createfile->remove(toDir);
    }

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}


void produce_AlphaMateSpec()
{

}

bool running_alphamate(alphamate_edge blup_alphamate_all,QString Alphamate_running_path,QString output_path){
    qDebug() << endl <<"Alphamate_running_path:" << Alphamate_running_path << endl;
    if(blup_alphamate_all.GenderFile_CheckBox->checkState() == Qt::Checked)
    {
        QString GenderFile = blup_alphamate_all.GenderFile_lineEdit->text();
        copy_file(GenderFile,Alphamate_running_path+"/Gender.txt");
    }
    QString NrmMatrixFile = blup_alphamate_all.NrmMatrix_lineEdit->text();
    copy_file(NrmMatrixFile,Alphamate_running_path+"/Nrm.txt");
    QString SelCriterionFile = blup_alphamate_all.SelCriterionFile_lineEdit->text();
    copy_file(SelCriterionFile,Alphamate_running_path+"/Criterion.txt");
    QProcess *alphamate_process;
    alphamate_process = new QProcess;
    alphamate_process->setWorkingDirectory(Alphamate_running_path);
    alphamate_process->start("./AlphaMate AlphaMateSpec.txt");
    Process_runing_gif(alphamate_process,"Alpahmate");
    qDebug() << endl <<"alphamate_process_state :" <<alphamate_process->state() << endl;
    qDebug() << endl <<"Alphamated...."  << endl;
}
