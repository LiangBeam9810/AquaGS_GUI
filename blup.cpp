#include "blup.h"

void blup_Init(blup blup_input)
{
    blup_input.fiexd_effect_listwidget->addItems(blup_input.fixed_effect_list);
    blup_input.random_effect_listwidget->addItems(blup_input.random_effect_list);

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
    QProcess display_process;
    display_process.execute(param);
    if(display_process.waitForStarted())
    {
        qDebug()<<"OUTLIER PROCESS STRATED";
        display_process.close();
        return false;
    }
    if(display_process.waitForFinished())
    {
        qDebug()<<"OUTLIER PROCESS FINISHED";
        display_process.close();
        return false;
    }
    display_process.close();
    return true;

}


void classical_method_cross_validation_and_display(blup blup_mode,fold_validate blup_fold_validate)
{

}
