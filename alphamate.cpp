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
    blup_alphamate_all.NumberOfMatings_spinBox->setEnabled(true);

    if(blup_alphamate_all.GenderFile_CheckBox->checkState() == Qt::Checked)
    {

        //blup_alphamate_all.NumberOfMaleParents_spinBox->setEnabled(true);
        blup_alphamate_all.NumberOfFemaleParents_spinBox->setEnabled(true);
        blup_alphamate_all.GenderFile_lineEdit->setEnabled(true);
        blup_alphamate_all.EqualizeMaleContributions_checkBox->setEnabled(true);
        blup_alphamate_all.EqualizeFemaleContributions_checkBox->setEnabled(true);
    }else{
        //blup_alphamate_all.NumberOfMatings_spinBox->setEnabled(false);
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
    //blup_alphamate_all.GenderFile_CheckBox->setEnabled(false);
    blup_alphamate_all.EqualizeMaleContributions_checkBox->setEnabled(false);
    blup_alphamate_all.EqualizeFemaleContributions_checkBox->setEnabled(false);
}



void alphmate_able_gender(alphamate_edge blup_alphamate_all,bool state)
{
    //blup_alphamate_all.NumberOfMatings_spinBox->setEnabled(state);
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


void produce_AlphaMateSpec(alphamate_edge blup_alphamate_all,QString Alphamate_running_path )
{
    QString filepath = Alphamate_running_path+"/AlphaMateSpec.txt";
    QFile file(filepath);
    qDebug()<<"producing AlphaMateSpec.txt"+filepath;
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::warning(NULL, "File error:", "Can't open "+filepath+" !");
        return;
    }
    QTextStream txtOutput(&file);
    if(blup_alphamate_all.GenderFile_CheckBox->isChecked())
    {
        txtOutput << "GenderFile, Gender.txt"<<"\n";
    }
    txtOutput << "NrmMatrixFile, Nrm.txt"<<"\n";
    txtOutput << "SelCriterionFile, Criterion.txt"<<"\n";
    txtOutput << "NumberOfMatings"<<"  ,  "<<blup_alphamate_all.NumberOfMatings_spinBox->value()<<"\n";
    if(blup_alphamate_all.GenderFile_CheckBox->isChecked())
    {

        txtOutput << "NumberOfMaleParents"<<"  ,  "<<blup_alphamate_all.NumberOfMaleParents_spinBox->value()<<"\n";
        if(blup_alphamate_all.EqualizeMaleContributions_checkBox->isChecked())
        {
            txtOutput << "EqualizeMaleContributions"<<"  ,  "<<"Yes"<<"\n";
        }else {
            txtOutput << "EqualizeMaleContributions"<<"  ,  "<<"No"<<"\n";
        }
        txtOutput << "NumberOfFemaleParents  "<<"  ,  "<<blup_alphamate_all.NumberOfFemaleParents_spinBox->value()<<"\n";
        if(blup_alphamate_all.EqualizeFemaleContributions_checkBox->isChecked())
        {
            txtOutput << "EqualizeFemaleContributions"<<"  ,  "<<"Yes"<<"\n";
        }else {
            txtOutput << "EqualizeFemaleContributions"<<"  ,  "<<"No"<<"\n";
        }

    }
    txtOutput << "TargetDegree"<<"  ,  "<<blup_alphamate_all.TargetDegree_spinBox->value()<<"\n";
    txtOutput << "TargetCoancestryRate"<<"  ,  "<<blup_alphamate_all.TargetCoancestryRate_doubleSpinBox->value()<<"\n";

    if(blup_alphamate_all.EvaluateFrontier_checkBox->isChecked())
    {
        txtOutput << "EvaluateFrontier"<<"  ,  "<<"Yes"<<"\n";
    }else {
        txtOutput << "EvaluateFrontier"<<"  ,  "<<"No"<<"\n";
    }
    //ModeMinCoancestry           , Yes;
    if(blup_alphamate_all.ModeMinCoancestry_checkBox->isChecked())
    {
        txtOutput << "ModeMinCoancestry"<<"  ,  "<<"Yes"<<"\n";
    }else {
        txtOutput << "ModeMinCoancestry"<<"  ,  "<<"No"<<"\n";
    }
    //ModeMinInbreeding           , Yes;
    if(blup_alphamate_all.ModeMinInbreeding_checkBox->isChecked())
    {
        txtOutput << "ModeMinInbreeding"<<"  ,  "<<"Yes"<<"\n";
    }else {
        txtOutput << "ModeMinInbreeding"<<"  ,  "<<"No"<<"\n";
    }
    //ModeMaxCriterion            , Yes;
    if(blup_alphamate_all.ModeMaxCriterion_checkBox->isChecked())
    {
        txtOutput << "ModeMaxCriterion"<<"  ,  "<<"Yes"<<"\n";
    }else {
        txtOutput << "ModeMaxCriterion"<<"  ,  "<<"No"<<"\n";
    }
    //ModeOpt                     , Yes;
    if(blup_alphamate_all.ModeOpt_checkBox->isChecked())
    {
        txtOutput << "ModeOpt"<<"  ,  "<<"Yes"<<"\n";
    }else {
        txtOutput << "ModeOpt"<<"  ,  "<<"No"<<"\n";
    }
    txtOutput << "Stop"<<"\n";
    file.close();



}
bool prepare_alphamate_file(alphamate_edge blup_alphamate_all,QString Alphamate_running_path )
{
    qDebug() << endl <<"Alphamate_running_path:" << Alphamate_running_path << endl;
    if(blup_alphamate_all.GenderFile_CheckBox->checkState() == Qt::Checked)//如果勾选性别选项 则复制性别文件
    {
        QString GenderFile = blup_alphamate_all.GenderFile_lineEdit->text();
        if(!(copy_file(GenderFile,Alphamate_running_path+"/Gender.txt")))
        {
            QMessageBox::warning(NULL, "File error:", "Can't find the  "+GenderFile+"!");
            return false;
        }

    }
    QString NrmMatrixFile = blup_alphamate_all.NrmMatrix_lineEdit->text();
    if(!(copy_file(NrmMatrixFile,Alphamate_running_path+"/Nrm.txt")))
    {
        QMessageBox::warning(NULL, "File error:", "Can't find the "+NrmMatrixFile+"!");
        return false;
    }

    QString SelCriterionFile = blup_alphamate_all.SelCriterionFile_lineEdit->text();
    if(!(copy_file(SelCriterionFile,Alphamate_running_path+"/Criterion.txt")))
    {
        QMessageBox::warning(NULL, "File error:", "Can't find the "+SelCriterionFile+"!");
        return false;
    }
    produce_AlphaMateSpec(blup_alphamate_all,Alphamate_running_path);
    return true;
}

bool running_alphamate(alphamate_edge blup_alphamate_all,QString Alphamate_running_path,QString output_path){
    if(!(prepare_alphamate_file(blup_alphamate_all,Alphamate_running_path)))
    {
        return false;
    }
    Process *alphamate_process;
    alphamate_process = new Process;
    //alphamate_process->setWorkingDirectory(Alphamate_running_path);
    if(!(alphamate_process->runAlphamate(Alphamate_running_path,"./AlphaMate AlphaMateSpec.txt","Alpahmate")))
    {
        QMessageBox::warning(NULL, "Process error:", "Can't open the Allphamate process!");
        return false;
    }
    //alphamate_process->start("./AlphaMate AlphaMateSpec.txt");
    //Process_runing_gif(alphamate_process,"Alpahmate");
    //qDebug() << endl <<"alphamate_process_state :" <<alphamate_process->state() << endl;
    //qDebug() << endl <<"Alphamated...."  << endl;
    return true;
}
