#include "effect.h"

void display_fixed_effect(QString pr_csv_path,QTableView* tableview,QStringList fixed_effect_list)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({"phenotype", "p value"});
    tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QFile csv_file(pr_csv_path);
    QStringList csv_list;
    csv_list.clear();
    if (!csv_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<endl << pr_csv_path << "is broken!"<< endl;
        return;
    }
    QTextStream stream(&csv_file);
    while (!stream.atEnd())
    {
        csv_list.push_back(stream.readLine());
    }
    csv_file.close();
    qDebug()<<endl<<"csv_list:"<<csv_list<<endl;
    unsigned int i =0;
    Q_FOREACH(QString str, csv_list)
    {
       QStringList valsplit = str.split(",");
       model->setItem(i, 0, new QStandardItem(valsplit[0].mid(1,valsplit[0].length()-2)));
       model->setItem(i, 1, new QStandardItem(valsplit[1].mid(0,5)));
       if(!(-1 == fixed_effect_list.indexOf(QString::number(i))))
       {
           qDebug()<<endl<<"find the effect in the fixed_effect_list already,index is "<<fixed_effect_list.indexOf(QString::number(i))<<endl;
           model->item(i,0)->setFont(QFont( "Abyssinica SIL", 13, QFont::Light));
           model->item(i,1)->setFont(QFont( "Abyssinica SIL", 13, QFont::ExtraLight));
           model->item(i, 0)->setForeground(QBrush(QColor(128, 0, 0)));
           model->item(i, 1)->setForeground(QBrush(QColor(128, 0, 0)));
       }
       i++;
    }
    tableview->setModel(model);
    tableview->show();
}

bool fixed_effect_testing(QString input_path,QString output_path,unsigned int target_phenotype_index,QStringList fixed_effect_list)
{
    QString runPath = QDir::currentPath();
    runPath.append("/rscript/fixed_effect_testing.R");
    qDebug() << endl <<"runPath;" << runPath << endl;
    QString param;
    // The sequence of param is not changeable
    param.clear();
    param.append("Rscript");
    param.append(" ");
    param.append("/home/liang/Documents/AquaGS_GUI/rscript/fixed_effect_testing.R");
    param.append(" ");
    param.append(input_path);
    param.append(" ");
    param.append(output_path);
    param.append(" ");
    param.append(QString::number(target_phenotype_index));
    param.append(" ");
    param.append(QString::number(fixed_effect_list.length()));
    param.append(" ");
    for(int i = 0;i < fixed_effect_list.length();i++){
        param.append(fixed_effect_list[i]);
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

bool random_effect_testing(QString input_path,QString output_path,unsigned int target_phenotype_index,QStringList fixed_effect_list)
{
    QString runPath = QDir::currentPath();
    runPath.append("/rscript/rondom_effect_testing.R");
    qDebug() << endl <<"runPath;" << runPath << endl;
    QString param;
    // The sequence of param is not changeable
    param.clear();
    param.append("Rscript");
    param.append(" ");
    param.append("/home/liang/Documents/AquaGS_GUI/rscript/random_effect_testing.R");
    param.append(" ");
    param.append(input_path);
    param.append(" ");
    param.append(output_path);
    param.append(" ");
    param.append(QString::number(target_phenotype_index));
    param.append(" ");
    param.append(QString::number(fixed_effect_list.length()));
    param.append(" ");
    for(int i = 0;i < fixed_effect_list.length();i++){
        param.append(fixed_effect_list[i]);
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

bool prepare_effect(QString input_path,QString output_path,QTableView* tableview,
                    unsigned int index,unsigned  int flag,
                    QStringList fixed_effect_list)
{
    QString effect_path = output_path;
    bool callbake = false;
    if(flag){
        effect_path.append("/rondom_effect.csv");
        qDebug() << endl << "fixed_effect_path:" << effect_path <<endl;
        callbake =  random_effect_testing(input_path,effect_path,index,fixed_effect_list);

    }
    else{
        effect_path.append("/fixed_effect.csv");
        qDebug() << endl << "fixed_effect_path:" << effect_path <<endl;
        callbake =  fixed_effect_testing(input_path,effect_path,index,fixed_effect_list);
    }
    if(callbake)
    {
        display_fixed_effect(effect_path,tableview,fixed_effect_list);
    }
    return callbake;

}

void add_item2table_listwidget(QTableView* phenotype_pr_TableView,QListWidget* selected_PhenoListWidget,QStringList phenotypelist,QStringList* fixed_effect_list)
{
    unsigned int selected_index = phenotype_pr_TableView->currentIndex().row();
    qDebug()<<endl<<"selected row of  fixed is"<<selected_index;

    bool Norepetition_flag = true;  //check the item is selected already or not
    unsigned int count_fixed_effect_list = (*fixed_effect_list).length();
    qDebug()<<endl<<"the num of fixed_effect_list:"<<count_fixed_effect_list;
    if(count_fixed_effect_list) //check the new effect is selected already?
    {
        for(int i = 0;i < ((*fixed_effect_list).length());i++){
            if(QString::number(selected_index) == (*fixed_effect_list)[i]){
                Norepetition_flag = false;
            }
        }
    }
    if(Norepetition_flag){
        selected_PhenoListWidget->addItem(phenotypelist[selected_index]);
        *fixed_effect_list << QString::number(selected_index);
        qDebug()<<endl<<"fixed_effect_list:"<<*fixed_effect_list;
    }

}

void remove_item2table_listwidget(QListWidget* selected_PhenoListWidget,QStringList* fixed_effect_list)
{
    unsigned int fixed_remove_index = selected_PhenoListWidget->currentRow();
    qDebug()<<endl<<"remove row of fixed is"<<fixed_remove_index;
    (*fixed_effect_list).removeAt(fixed_remove_index);
    qDebug()<<endl<<"fixed_effect_list:"<<*fixed_effect_list;
    selected_PhenoListWidget->takeItem(fixed_remove_index);
}
