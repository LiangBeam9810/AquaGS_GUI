#include "blup.h"

bool MainWindow::A_G_matirx_build()
{

    /*-------------------------------------------*/
    Rdata_path = output_path;
    Rdata_path.append("/Rbuffer.Rdata");
    A_matrix_path = output_path+"/A_matrix.txt";
    G_matrix_path = output_path+"/G_matrix.txt";
    qDebug()<<endl<<"Rdata_path"<<Rdata_path;
    qDebug()<<endl<<"A_matrix_path"<<A_matrix_path;
    qDebug()<<"G_matrix_path"<<G_matrix_path<<endl;
    /*-------------------------------------------*/

    QString runPath = QDir::currentPath();
    runPath.append("/rscript/A_G_matirx_build.R");
    qDebug() << endl <<"runPath:" << runPath << endl;
    QString param;
    // The sequence of param is not changeable
    param.clear();
    param.append("Rscript");
    param.append(" ");
    param.append(runPath);
    param.append(" ");
    param.append(csv_path);
    param.append(" ");
    param.append(raw_path);
    param.append(" ");
    param.append(Rdata_path);
    param.append(" ");
    param.append(A_matrix_path);
    param.append(" ");
    param.append(G_matrix_path);
    param.append(" ");
    param.append(QString::number(target_phenotype_index));
    param.append(" ");
    param.append(QString::number(AnimalID_phenotype_index));
    param.append(" ");
    param.append(QString::number(Dam_phenotype_index));
    param.append(" ");
    param.append(QString::number(Sire_phenotype_index));
    param.append(" ");
    qDebug()<< endl<<"display param :"<<param<< endl;
    QProcess *A_G_matirx_build_process;
    A_G_matirx_build_process = new QProcess;
    A_G_matirx_build_process->setWorkingDirectory(Alphamate_running_path);
    A_G_matirx_build_process->start(param);
    Process_runing_gif(A_G_matirx_build_process," Building A and G matirx ");
    A_G_matirx_build_process->close();
    return true;
}


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







