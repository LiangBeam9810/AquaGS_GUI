#include "alphamate.h"

void alphamate_page_Init(alphamate_edge blup_alphamate_all)
{
    blup_alphamate_all.classical_more_Button->setEnabled(true);
    blup_alphamate_all.classical_mate_Button->setEnabled(true);
    blup_alphamate_all.TargetDegree_spinBox->setValue(45);
    blup_alphamate_all.TargetDegree_spinBox->setEnabled(true);
    blup_alphamate_all.TargetCoancestryRate_doubleSpinBox->setValue(0.01);
    blup_alphamate_all.TargetCoancestryRate_doubleSpinBox->setEnabled(true);
    blup_alphamate_all.NumberOfMatingCandidate_spinBox->setValue(100);
    blup_alphamate_all.SelCriterionFile_lineEdit->setEnabled(true);
    blup_alphamate_all.NumberOfMatings_spinBox->setValue(30);
    blup_alphamate_all.NumberOfMatings_spinBox->setEnabled(true);
    blup_alphamate_all.NumberOfMaleParents_spinBox->setValue(10);
    blup_alphamate_all.NumberOfMaleParents_spinBox->setEnabled(false);
    blup_alphamate_all.NumberOfFemaleParents_spinBox->setValue(10);
    blup_alphamate_all.NumberOfFemaleParents_spinBox->setEnabled(false);
    blup_alphamate_all.NrmMatrix_lineEdit->setEnabled(true);
    blup_alphamate_all.ModeOpt_checkBox->setCheckState(Qt::Checked);
    blup_alphamate_all.ModeOpt_checkBox->setEnabled(true);
    blup_alphamate_all.ModeMinInbreeding_checkBox->setCheckState(Qt::Checked);
    blup_alphamate_all.ModeMinInbreeding_checkBox->setEnabled(true);
    blup_alphamate_all.ModeMinCoancestry_checkBox->setCheckState(Qt::Checked);
    blup_alphamate_all.ModeMinCoancestry_checkBox->setEnabled(true);
    blup_alphamate_all.ModeMaxCriterion_checkBox->setCheckState(Qt::Checked);
    blup_alphamate_all.ModeMaxCriterion_checkBox->setEnabled(true);

    blup_alphamate_all.GenderFile_lineEdit->setEnabled(false);
    blup_alphamate_all.GenderFile_CheckBox->setCheckState(Qt::Unchecked);
    blup_alphamate_all.EvaluateFrontier_checkBox->setCheckState(Qt::Checked);
    blup_alphamate_all.EvaluateFrontier_checkBox->setEnabled(true);
    blup_alphamate_all.EvaluateFrontier_checkBox->setCheckState(Qt::Checked);
    blup_alphamate_all.EqualizeMaleContributions_checkBox->setCheckState(Qt::Checked);
    blup_alphamate_all.EqualizeMaleContributions_checkBox->setEnabled(false);
    blup_alphamate_all.EqualizeFemaleContributions_checkBox->setCheckState(Qt::Checked);
    blup_alphamate_all.EqualizeFemaleContributions_checkBox->setEnabled(false);
    blup_alphamate_all.GenderFile_CheckBox->setCheckState(Qt::Unchecked);
    blup_alphamate_all.GEBVform_comboBox->setEnabled(true);
    blup_alphamate_all.NrmMatrixFileform_comboBox->setEnabled(true);

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
    blup_alphamate_all.GEBVform_comboBox->setEnabled(true);
    blup_alphamate_all.NrmMatrixFileform_comboBox->setEnabled(true);

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
    blup_alphamate_all.GEBVform_comboBox->setEnabled(false);
    blup_alphamate_all.NrmMatrixFileform_comboBox->setEnabled(false);


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

void copyPath(QString src, QString dst)
{
    QDir dir(src);
    if (! dir.exists())
        return;

    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString dst_path = dst + QDir::separator() + d;
        dir.mkpath(dst_path);
        copyPath(src+ QDir::separator() + d, dst_path);//use recursion
    }

    foreach (QString f, dir.entryList(QDir::Files)) {
        QFile::copy(src + QDir::separator() + f, dst + QDir::separator() + f);
    }
}


void produce_AlphaMateSpec(alphamate_edge blup_alphamate_all,QString Alphamate_running_path )
{
    QString filepath = Alphamate_running_path+"/AlphaMateSpec.txt";
    QFile file(filepath);
    qDebug()<<"producing AlphaMateSpec.txt"+filepath;
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::warning(nullptr, "File error:", "Can't open "+filepath+" !");
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
            QMessageBox::warning(nullptr, "File error:", "Can't find the  "+GenderFile+"!");
            return false;
        }

    }
    QString NrmMatrixFile = blup_alphamate_all.NrmMatrix_lineEdit->text();
    if(!(copy_file(NrmMatrixFile,Alphamate_running_path+"/Nrm.txt")))
    {
        QMessageBox::warning(nullptr, "File error:", "Can't find the "+NrmMatrixFile+"!");
        return false;
    }

    QString SelCriterionFile = blup_alphamate_all.SelCriterionFile_lineEdit->text();
    if(!(copy_file(SelCriterionFile,Alphamate_running_path+"/Criterion.txt")))
    {
        QMessageBox::warning(nullptr, "File error:", "Can't find the "+SelCriterionFile+"!");
        return false;
    }

    Process *alphamate_clipping_process;
    alphamate_clipping_process = new Process;

    QString runPath = QDir::currentPath();
    runPath.append("/rscript/clipping_Alphamate.R");
    qDebug() << endl <<"runPath:" << runPath << endl;
    QString param;
    // The sequence of param is not changeable
    param.clear();
    param.append("Rscript");
    param.append(" ");
    param.append(runPath);
    param.append(" ");
    int NumberOfMatingCandidate = (blup_alphamate_all.NumberOfMatingCandidate_spinBox->value());
    QString NumberOfMatingCandidate_string;
    NumberOfMatingCandidate_string = QString::number(NumberOfMatingCandidate,10,5);
    param.append(NumberOfMatingCandidate_string);
    param.append(" ");
    if(blup_alphamate_all.GenderFile_CheckBox->isChecked())
    {
        param.append("1");
    }
    else {
        param.append("0");
    }
    param.append(" ");
    param.append(Alphamate_running_path+"/Criterion.txt");
    param.append(" ");
    param.append(Alphamate_running_path+"/Nrm.txt");
    param.append(" ");
    if(blup_alphamate_all.GenderFile_CheckBox->isChecked())
    {
        param.append(Alphamate_running_path+"/Gender.txt");
    }
    param.append(" ");
    qDebug() << endl <<(blup_alphamate_all.NumberOfMatingCandidate_spinBox->value())<<"param:" << param << endl;
    if(!(alphamate_clipping_process->runRscript(param,"Clipping for Alpahmate")))
    {
        QMessageBox::warning(nullptr, "Process error:", "Can't open the Allphamate Clipping process!");
        return false;
    }

    produce_AlphaMateSpec(blup_alphamate_all,Alphamate_running_path);

    return true;
}

bool running_alphamate(alphamate_edge blup_alphamate_all,QString Alphamate_running_path,QString output_path){
    QString Alphamate_new_running_path = output_path+"/AlphaMateLinux";//在输出文件夹创建Alphamate的文件夹

 /*------------------判断该文件夹是否存在 如果不存在就创建---------------------*/
    QDir dir(Alphamate_new_running_path);
    if(!dir.exists()){
        bool ismkdir = dir.mkdir(Alphamate_new_running_path);
        if(!ismkdir)
            qDebug() << "Create path fail" << endl;
        else
            qDebug() << "Create fullpath success" << endl;
    }
    else{
        qDebug() << "fullpath exist" << endl;
    }
/*-------------------------------------------------------------------------*/

    copyPath(Alphamate_running_path,Alphamate_new_running_path);
    Alphamate_running_path = Alphamate_new_running_path;
    qDebug()<<"Alphamate_running_path:"<<Alphamate_running_path<<endl;
    if(!(prepare_alphamate_file(blup_alphamate_all,Alphamate_running_path)))
    {
        return false;
    }
    Process *alphamate_process;
    alphamate_process = new Process;
    //alphamate_process->setWorkingDirectory(Alphamate_running_path);
    if(!(alphamate_process->runAlphamate(Alphamate_running_path,"./AlphaMate AlphaMateSpec.txt","Alpahmate")))
    {
        QMessageBox::warning(nullptr, "Process error:", "Can't open the Allphamate process!");
        return false;
    }
    //alphamate_process->start("./AlphaMate AlphaMateSpec.txt");
    //Process_runing_gif(alphamate_process,"Alpahmate");
    //qDebug() << endl <<"alphamate_process_state :" <<alphamate_process->state() << endl;
    //qDebug() << endl <<"Alphamated...."  << endl;
    return true;
}
