#include "phenotype.h"


/*--------------------------phenotype index------------------------------------*/
void phenotype_select_line_init(phenotype_select phenotype_select_line,QString csv_path,QStringList* phenotype_list)
{
    prepare_phenotype(csv_path, phenotype_list , phenotype_select_line.AnimalID_ComboBox);
    prepare_phenotype(csv_path, phenotype_list , phenotype_select_line.Dam_ComboBox);
    prepare_phenotype(csv_path, phenotype_list , phenotype_select_line.Sire_ComboBox);
    prepare_phenotype(csv_path, phenotype_list , phenotype_select_line.target_phenotype_ComboBox);
    phenotype_select_line.outlier_CheckBox->setCheckState(Qt::Unchecked);
}

void phenotype_select_line_get_index(phenotype_select phenotype_select_line,unsigned int * target_index,
                                     unsigned int * ID_index,
                                     unsigned int * Dam_index,
                                     unsigned int * Sire_index)
{
    *target_index = phenotype_select_line.target_phenotype_ComboBox->currentIndex();
    *ID_index = phenotype_select_line.AnimalID_ComboBox->currentIndex();
    *Dam_index = phenotype_select_line.Dam_ComboBox->currentIndex();
    *Sire_index = phenotype_select_line.Sire_ComboBox->currentIndex();
}

void prepare_phenotype(QString csv_path,
                       QStringList* phenotype_list ,
                       QComboBox*  ComboBox)
{
    qDebug()<<endl<< "All path are correct." << endl;
    *phenotype_list =(get_csv_title(csv_path)); //Reading  phenotypes.
    ComboBox->clear();
    for(int i =0 ;i< (*phenotype_list).length();i++){
        ComboBox->addItem((*phenotype_list)[i]);
    }
}

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
                         unsigned int* target_phenotype_index)
{
    //clear plot
    clean_normality_index( skewnessddisplay_1,kurtosisdisplay_2,horizontallabel_2);
    clean_normality_index( skewnessddisplay_2,kurtosisdisplay_1,horizontallabel_1);

    //disable accept_button and enable convert_swith
    accept_Button->setEnabled(false);
    convert_swith->setEnabled(true);
    convert_swith->setCheckState(Qt::Unchecked);
    //read user's selection
    *outlier_state = (outlierswith->isChecked())? 1:0;
    *fist_convert_flag = 1;
    *target_phenotype_index = phenotypeComboBox->currentIndex();
}
void change_convert_wight_state(int state, QPushButton* convert_Button,QPushButton* reset_Button,QPushButton* accept_Button,QToolButton* detial_Button)
{
    if(state){
            convert_Button->setEnabled(true);
            reset_Button->setEnabled(true);
            accept_Button->setEnabled(false);
            detial_Button->setEnabled(false);
        }
        else{
            convert_Button->setEnabled(false);
            reset_Button->setEnabled(false);
            accept_Button->setEnabled(false);
            detial_Button->setEnabled(false);
        }
}


bool outlier_elimination(QString* csv_path,
                    unsigned int outlier_state,
                    unsigned inttarget_phenotype_index)
{
    QString runPath = QDir::currentPath();
    runPath.append("/rscript/outlier_elimination.R");
    qDebug() << endl <<"runPath:" << runPath << endl;
    QString param;
        // The sequence of param is not changeable
        param.clear();
        param.append("Rscript");
        param.append(" ");
        param.append(runPath);
        param.append(" ");
        param.append(*csv_path);
        param.append(" ");
        param.append(QString::number(outlier_state));
        param.append(" ");
        param.append(QString::number(inttarget_phenotype_index));
        param.append(" ");
    qDebug()<<endl<<"outlier param :"<<param<<endl;

    QProcess* outlier_process;
    outlier_process = new QProcess;
    outlier_process->start(param);
    Process_runing_gif(outlier_process,"Reading phenotype");
    outlier_process->close();

    //Check the existion of the file after outlier
    QString path = *csv_path;
    path.replace(".csv", "_outlier.csv");
    if(isFileExist(path))
    {
        (*csv_path).replace(".csv", "_outlier.csv");
        qDebug()<<endl<<"outliered csv path :"<<(*csv_path)<<endl;
        return true;
    }
    else
    {
        return false;
    }

}

void clean_normality_index( QTextBrowser* skewnessddisplay,
                            QTextBrowser* kurtosisdisplay,
                            QLabel* horizontallabel)
{
    skewnessddisplay->clear();
    kurtosisdisplay->clear();
    horizontallabel->clear();
}


bool display_normality(QString input_path,
                       QString output_path,
                       unsigned int target_phenotype_index,
                       QString type,
                       QTextBrowser* skewnessdisplay,
                       QTextBrowser* kurtosisdisplay,
                       QLabel* graphicedisplay)
{
    QString runPath = QDir::currentPath();
    runPath.append("/rscript/check_normality.R");
    qDebug() << endl <<"runPath:" << runPath << endl;
    QString param;
    // The sequence of param is not changeable
    param.clear();
    param.append("Rscript");
    param.append(" ");
    param.append(runPath);
    param.append(" ");
    param.append(input_path);
    param.append(" ");
    param.append(output_path);
    param.append(" ");
    param.append(QString::number(target_phenotype_index));
    param.append(" ");
    param.append(type);
    param.append(" ");
    qDebug()<< endl<<"display param :"<<param<< endl;

    QProcess* display_process;
    display_process = new QProcess;
    display_process->start(param);
    Process_runing_gif(display_process,"Ploting phenotype");
    display_process->close();

    QString ske_kur_ans_path = output_path;
    QString histogram_ans_path = output_path;
    ske_kur_ans_path.append("/ske_kur_of_");
    ske_kur_ans_path.append(type);
    ske_kur_ans_path.append(".csv");
    histogram_ans_path.append("/histogram_of_");
    histogram_ans_path.append(type);
    histogram_ans_path.append(".png");

    if((isFileExist(ske_kur_ans_path))&&(isFileExist(ske_kur_ans_path)))
    {
        QFile csv_file(ske_kur_ans_path);
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
            qDebug()<<endl<< "ske&kur: " << csv_list << endl;
            skewnessdisplay->setText((csv_list[0].mid(0,5)));
            kurtosisdisplay->setText(csv_list[1].mid(0,5));
        }
        else
        {
             QMessageBox::about(NULL, "csv file", "Can't open csv file!");
             return false;
        }

         qDebug()<< "showing img..." ;
        QImage *img =new QImage;;
        img->load(histogram_ans_path);
        graphicedisplay->setScaledContents(true);
        graphicedisplay->setPixmap(QPixmap::fromImage(*img));
    }
    else
    {
         QMessageBox::about(NULL, "csv file", "NO EXIST csv file!");
         return false;
    }
    return true;
}

bool convert_phenotype(QString input_path,unsigned int target_phenotype_index,unsigned int fist_convert_flag)
{
    QString runPath = QDir::currentPath();
    runPath.append("/rscript/convert_normality.R");
    qDebug() << endl <<"runPath:" << runPath << endl;
    QString param;
    // The sequence of param is not changeable
    param.clear();
    param.append("Rscript");
    param.append(" ");
    param.append(runPath);
    param.append(" ");
    param.append(input_path);
    param.append(" ");
    param.append(QString::number(target_phenotype_index));
    param.append(" ");
    param.append(QString::number(fist_convert_flag));
    param.append(" ");
    qDebug()<< endl<<"display param :"<<param<< endl;

    QProcess* display_process;
    display_process = new QProcess;
    display_process->start(param);
    Process_runing_gif(display_process,"Converting");
    display_process->close();
    QString path = input_path;
    path.replace(".csv","_converted.csv");
    if(isFileExist(path)){
        qDebug()<<endl<<"converted csv path :"<<path<<endl;
        return true;
    }
    else
    {
        qDebug()<<endl<<"convert error :"<<endl;
        return false;
    }
    return true;
}

bool check_convert_path_of_phenotype(bool converted_flag ,QCheckBox* convert_swith)
{
    if((convert_swith->checkState() == Qt::Checked)&&(converted_flag))
    {
        return true;
    }
    else if((convert_swith->checkState() == Qt::Unchecked))
    {
        return true;
    }
    else
    {
        return false;
    }
}
