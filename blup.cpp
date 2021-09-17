#include "blup.h"

void blup_Init(blup blup_input)
{
    blup_input.fiexd_effect_lineedit->setText(blup_input.fixed_effect_list.join(","));
    blup_input.random_effect_lineedit->setText(blup_input.random_effect_list.join(","));
}

void blup_fold_validate_Init(fold_validate fold_validate_input)
{
    fold_validate_input.k_flod_times_ComboBox->setEnabled(false);
    fold_validate_input.cross_validation_pushbutton->setEnabled(false);
}

bool blup_build(blup blup_input)
{
    unsigned int mode_flag = blup_input.BLUP_mode_ComboBox->currentIndex();
    QString runPath = QDir::currentPath();
    runPath.append("/rscript/blup_gblup_build(Rdata).R");
    qDebug() << endl <<"runPath:" << runPath << endl;
    QString param;
    // The sequence of param is not changeable
    param.clear();
    param.append("Rscript");
    param.append(" ");
    param.append(runPath);
    param.append(" ");
    param.append(blup_input.Rdata_path);//1
    param.append(" ");
    param.append(blup_input.output_path);//2
    param.append(" ");
    param.append(QString::number(blup_input.AnimalID_index));
    param.append(" ");
    param.append(QString::number(blup_input.target_index));
    param.append(" ");
    param.append(QString::number(mode_flag));
    param.append(" ");

    param.append(QString::number(blup_input.fixed_effect_list2R.length()));
    qDebug()<< endl<<"display fixed_effect_list :"<<blup_input.fixed_effect_list2R<< endl;
    param.append(" ");
    for(int i = 0;i < blup_input.fixed_effect_list2R.length();i++){
        param.append(blup_input.fixed_effect_list2R[i]);
        param.append(" ");
    }

    param.append(QString::number(blup_input.random_effect_list2R.length()));
    qDebug()<< endl<<"display random_effect_list :"<<blup_input.random_effect_list2R<< endl;
    param.append(" ");
    for(int i = 0;i < blup_input.random_effect_list2R.length();i++){
        param.append(blup_input.random_effect_list2R[i]);
        param.append(" ");
    }

    qDebug()<< endl<<"display param :"<<param<< endl;
    QProcess* build_process;
    build_process = new QProcess;
    build_process->start(param);
    Process_runing_gif(build_process,"BULP/GULP building");
    build_process->close();
    return true;

}


bool classical_method_cross_validation_and_display(blup blup_mode,fold_validate blup_fold_validate)
{
    unsigned int method_flag = blup_mode.BLUP_mode_ComboBox->currentIndex();
    QString runPath = QDir::currentPath();
    runPath.append("/rscript/classical_cross_validation(Rdata).R");
    qDebug() << endl <<"runPath:" << runPath << endl;
    QString param;
    // The sequence of param is not changeable
    param.clear();
    param.append("Rscript");
    param.append(" ");
    param.append(runPath);
    param.append(" ");
    param.append(blup_fold_validate.Rdata_path);//1
    param.append(" ");
    param.append(blup_fold_validate.output_path);//2
    param.append(" ");
    param.append(QString::number(blup_mode.AnimalID_index));
    param.append(" ");
    param.append(QString::number(blup_mode.target_index));
    param.append(" ");
    param.append(QString::number(method_flag));
    param.append(" ");
    param.append(QString::number(blup_fold_validate.fixed_effect_list.length()));
    qDebug()<< endl<<"display fixed_effect_list :"<<blup_fold_validate.fixed_effect_list<< endl;
    param.append(" ");
    for(int i = 0;i < blup_fold_validate.fixed_effect_list.length();i++){
        param.append(blup_fold_validate.fixed_effect_list[i]);
        param.append(" ");
    }
    param.append(QString::number(blup_fold_validate.random_effect_list.length()));
    qDebug()<< endl<<"display random_effect_list :"<<blup_fold_validate.random_effect_list<< endl;
    param.append(" ");
    for(int i = 0;i < blup_fold_validate.random_effect_list.length();i++){
        param.append(blup_fold_validate.random_effect_list[i]);
        param.append(" ");
    }
    param.append(QString::number(1));//rep
    param.append(" ");
    param.append(QString::number(blup_fold_validate.k_flod_times_ComboBox->currentIndex()));//k_num
    param.append(" ");
    qDebug()<< endl<<"display param :"<<param<< endl;
    QProcess* validate_process;
    validate_process = new Process;
    validate_process->start(param);
    Process_runing_gif(validate_process,"Validating");
    validate_process->close();

    QFile csv_file(blup_fold_validate.output_path);
    QStringList csv_list;
    csv_list.clear();
    if (csv_file.open(QIODevice::ReadWrite))
    {
        qDebug()<< "reading csv..." ;
        QTextStream stream(&csv_file);
        csv_list.push_back(stream.readAll());//
        Q_FOREACH(QString str, csv_list) //
        csv_list = str.split("\n");//
        csv_file.close();
        qDebug()<<endl<< "ACC&STD: " << csv_list << endl;
        blup_fold_validate.ACC_lineEdit->setText((csv_list[0].mid(0,5)));
        blup_fold_validate.STD_lineEdit->setText(csv_list[1].mid(0,5));
    }
    return true;
}

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

void Process_runing_gif(QProcess* Process,QString title)
{
    unsigned int i = 0;
    while ((Process->state() == QProcess::Starting)||(Process->state() == QProcess::Running)) {
        QString title_string = title;
        for(unsigned int j = 0;j < i;j++)
        {
             title_string = title_string + +". ";
        }
        i++;
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,"Running",title_string);
        QTimer::singleShot(1000,m_box,SLOT(close()));
        m_box->exec();
        if(i > 3)
        {
            i = 0;
        }

    }
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


