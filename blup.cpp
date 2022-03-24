#include "blup.h"

#define BLUP 0
#define GBLUP 1
#define HBLUP 2

bool rdata_init(QString Rdata_path,QString csv_path,QString raw_path,unsigned int  target_index,unsigned int AnimalID_index)
{
    QString runPath = QDir::currentPath();
    runPath.append("/rscript/data_init.R");
    qDebug() << endl <<"runPath:" << runPath ;

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
    param.append(QString::number(target_index));
    param.append(" ");
    param.append(QString::number(AnimalID_index));
    qDebug() <<"param:" << param << endl;
    Process* rdata_init_process;
    rdata_init_process = new Process;
    if(!(rdata_init_process->runRscript(param,"Building rdata")))
    {
        QMessageBox::warning(NULL, "Process error:", "Can't open the rdata init process!");
        return false;
    }
    return true;
}

bool G_matirx_build(QString Rdata_path,QString G_matrix_path)
{
    QString runPath = QDir::currentPath();
    runPath.append("/rscript/G_matirx_build.R");
    qDebug() << endl <<"runPath:" << runPath ;

    QString param;
    // The sequence of param is not changeable
    param.clear();
    param.append("Rscript");
    param.append(" ");
    param.append(runPath);
    param.append(" ");
    param.append(Rdata_path);
    param.append(" ");
    param.append(G_matrix_path);
    qDebug() <<"param:" << param << endl;
    Process* G_matirx_build_process;
    G_matirx_build_process = new Process;
    if(!(G_matirx_build_process->runRscript(param,"Building G matirx")))
    {
        QMessageBox::warning(NULL, "Process error:", "Can't open the G matirx build process!");
        return false;
    }
    return true;
}

bool A_matirx_build(QString Rdata_path,QString A_matrix_path,int Dam_index,int Sire_index)
{
    QString runPath = QDir::currentPath();
    runPath.append("/rscript/A_matirx_build.R");
    qDebug() << endl <<"runPath:" << runPath ;
    QString param;
    // The sequence of param is not changeable
    param.clear();
    param.append("Rscript");
    param.append(" ");
    param.append(runPath);
    param.append(" ");
    param.append(Rdata_path);
    param.append(" ");
    param.append(A_matrix_path);
    param.append(" ");
    param.append(QString::number(Dam_index));
    param.append(" ");
    param.append(QString::number(Sire_index));
    qDebug() <<"param:" << param << endl;
    Process* A_matirx_build_process;
    A_matirx_build_process = new Process;
    if(!(A_matirx_build_process->runRscript(param,"Building A matirx")))
    {
        QMessageBox::warning(NULL, "Process error:", "Can't open the A matirx build process!");
        return false;
    }
    return true;
}

bool Gender_build(QString Rdata_path,QString Gender_path,unsigned Gender_index)
{
    QString runPath = QDir::currentPath();
    runPath.append("/rscript/Gender_build.R");
    qDebug() << endl <<"runPath:" << runPath ;

    QString param;
    // The sequence of param is not changeable
    param.clear();
    param.append("Rscript");
    param.append(" ");
    param.append(runPath);
    param.append(" ");
    param.append(Rdata_path);
    param.append(" ");
    param.append(Gender_path);
    param.append(" ");
    param.append(QString::number(Gender_index));
    qDebug() <<"param:" << param << endl;
    Process* Gender_build_process;
    Gender_build_process = new Process;
    if(!(Gender_build_process->runRscript(param,"Building gender.txt")))
    {
        QMessageBox::warning(NULL, "Process error:", "Can't open the gender build process!");
        return false;
    }
    return true;
}

bool MainWindow::A_G_matirx_build()
{

    /*-------------------------------------------*/
    Rdata_path = output_path;
    Rdata_path.append("/Rbuffer.Rdata");
    A_matrix_path = output_path+"/A_matrix.txt";
    G_matrix_path = output_path+"/G_matrix.txt";
    Gender_path =  output_path+"/gender.txt";
    qDebug()<<endl<<"Rdata_path"<<Rdata_path;
    qDebug()<<endl<<"A_matrix_path"<<A_matrix_path;
    qDebug()<<"G_matrix_path"<<G_matrix_path<<endl;
    /*-------------------------------------------*/
    rdata_init(Rdata_path,csv_path,raw_path,target_phenotype_index,AnimalID_phenotype_index);
    G_matirx_build(Rdata_path,G_matrix_path);
    if(blup_Hblup_flag)
    {
        A_matirx_build(Rdata_path,A_matrix_path,Dam_phenotype_index,Sire_phenotype_index);
    }
    if(gender_flag)
    {
        Gender_build(Rdata_path,Gender_path,Gender_phenotype_index);
    }

    return true;
}

void display_vpredict(blup blup_input)
{
    QFile csv_file(blup_input.blup_formula_ans_path);
    QStringList csv_list;
    csv_list.clear();
    if (csv_file.open(QIODevice::ReadWrite))
    {
        qDebug()<< "reading vpredict csv..." ;
        QTextStream stream(&csv_file);
        csv_list.push_back(stream.readAll());//
        Q_FOREACH(QString str, csv_list) //
        csv_list = str.split("\n");//
        csv_file.close();
        qDebug()<<endl<< "Estimate&SE: " << csv_list << endl;
        if(csv_list.length()>1)
        {
            blup_input.classical_Estimate_textBrowser->setText((csv_list[0].mid(0,5)));
            blup_input.classical_SE_textBrowser->setText(csv_list[1].mid(0,5));
        }
        else
        {
            blup_input.classical_Estimate_textBrowser->setText("NA");
            blup_input.classical_SE_textBrowser->setText("NA");
            QMessageBox::warning(NULL, "File error:", "Can't open the validate file!");
            return ;
        }
    }
}

void display_varComp(blup blup_input)
{
    QStandardItemModel* model = new QStandardItemModel();
    /* 设置表格标题行(输入数据为QStringList类型) */
    model->setHorizontalHeaderLabels({"VarComp", "VarCompSE", "Zratio", "Constraint"});
    blup_input.classical_varComp_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QFile csv_file(blup_input.blup_varcomp_path);
    QStringList csv_list;
    csv_list.clear();
    if (!csv_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<endl << blup_input.blup_varcomp_path << "is broken!"<< endl;
        return;
    }
    QTextStream stream(&csv_file);
    while (!stream.atEnd())
    {
        csv_list.push_back(stream.readLine());
    }
    csv_file.close();
    qDebug()<<endl<<"csv_list of varComp:"<<csv_list<<endl;

    unsigned count = 0;
    Q_FOREACH(QString str, csv_list)
    {
        QStringList valsplit = str.split(",");
        model->setItem(count, 0, new QStandardItem(valsplit[0]));
        model->setItem(count, 1, new QStandardItem(valsplit[1]));
        model->setItem(count, 2, new QStandardItem(valsplit[2]));
        model->setItem(count, 3, new QStandardItem(valsplit[3]));
        count++;
    }
    blup_input.classical_varComp_tableView->setModel(model);
    blup_input.classical_varComp_tableView->show();

}

void blup_Init(blup blup_input)
{
    blup_input.fiexd_effect_lineedit->setText(blup_input.fixed_effect_list.join(","));
    blup_input.random_effect_lineedit->setText(blup_input.random_effect_list.join(","));
    blup_input.classical_SE_textBrowser->clear();
    blup_input.classical_Estimate_textBrowser->clear();
    clean_tablevie(blup_input.classical_varComp_tableView);
}

void blup_fold_validate_Init(fold_validate fold_validate_input)
{
    fold_validate_input.k_flod_times_ComboBox->setEnabled(false);
    fold_validate_input.cross_validation_pushbutton->setEnabled(false);
    fold_validate_input.cross_validation_checkBox->setCheckState(Qt::Unchecked);
    fold_validate_input.k_flod_rep_SpinBox->setEnabled(false);
}

bool blup_build(blup blup_input)
{
    unsigned int mode_flag = blup_input.BLUP_mode_ComboBox->currentIndex();
    if((!(mode_flag == GBLUP))&&(!(blup_input.blup_hblup_flag)))//
    {
        QMessageBox::information(NULL, "Notice ", "\"Dam\" and \"Sire\" is missing.\n Please select \"GBlup\" in the \"Classical method \"");
        return false;
    }
    QString runPath = QDir::currentPath();
    if(blup_input.trans_formula_1_lineEdit->text().isEmpty() || blup_input.trans_formula_2_lineEdit->text().isEmpty())
    {
        QMessageBox::warning(NULL, "Formula error:", "Please enter the formula !");
        return false;
    }
    QString formula = "";
    formula = blup_input.trans_formula_1_lineEdit->text()+"~("+blup_input.trans_formula_2_lineEdit->text()+")";
    qDebug()<<"formula : "<<formula;
    if(mode_flag == GBLUP||mode_flag == BLUP)
    {
        runPath.append("/rscript/blup_gblup_build(Rdata).R");
    }
    else {
        runPath.append("/rscript/hblup_build(Rdata).R");
    }

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
    param.append(" ");
    param.append(formula);
    param.append(" ");
    param.append(blup_input.blup_varcomp_path);
    param.append(" ");
    param.append(blup_input.blup_formula_ans_path);
    qDebug()<< endl<<"display blup build param :"<<param<< endl;
    Process* blup_build_process;
    blup_build_process = new Process;
    if(!(blup_build_process->runRscript(param,"Building")))
    {
        QMessageBox::warning(NULL, "Process error:", "Can't open the blup build process!");
        return false;
    }
    display_vpredict(blup_input);
    display_varComp(blup_input);
    return true;
}


bool classical_method_cross_validation_and_display(blup blup_mode,fold_validate blup_fold_validate)
{
    unsigned int method_flag = blup_mode.BLUP_mode_ComboBox->currentIndex();
    QString runPath = QDir::currentPath();

    if(blup_mode.trans_formula_1_lineEdit->text().isEmpty() || blup_mode.trans_formula_2_lineEdit->text().isEmpty())
    {
        QMessageBox::warning(NULL, "Formula error:", "Please enter the formula !");
        return false;
    }
    QString formula = "";
    formula = blup_mode.trans_formula_1_lineEdit->text()+"~("+blup_mode.trans_formula_2_lineEdit->text()+")";

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
    param.append(QString::number(blup_fold_validate.fixed_effect_input_Discrete.length()));
    qDebug()<< endl<<"display fixed_effect_input_Discrete :"<<blup_fold_validate.fixed_effect_input_Discrete<< endl;
    param.append(" ");
    for(int i = 0;i < blup_fold_validate.fixed_effect_input_Discrete.length();i++){
        param.append(blup_fold_validate.fixed_effect_input_Discrete[i]);
        param.append(" ");
    }
    param.append(QString::number(blup_fold_validate.random_effect_list.length()));
    qDebug()<< endl<<"display random_effect_list :"<<blup_fold_validate.random_effect_list<< endl;
    param.append(" ");
    for(int i = 0;i < blup_fold_validate.random_effect_list.length();i++){
        param.append(blup_fold_validate.random_effect_list[i]);
        param.append(" ");
    }
    param.append(QString::number(blup_fold_validate.k_flod_rep_SpinBox->value()));//rep
    param.append(" ");
    param.append(blup_fold_validate.k_flod_times_ComboBox->currentText());//k_num
    param.append(" ");
    param.append(formula);
    qDebug()<< endl<<"display param :"<<param<< endl;
    Process* validate_process;
    validate_process = new Process;
    if(!(validate_process->runRscript(param,"Validating")))
    {
        QMessageBox::warning(NULL, "Process error:", "Can't open the validate process!");
        return false;
    }

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
        if(csv_list.length()>1)
        {
            blup_fold_validate.ACC_lineEdit->setText((csv_list[0].mid(0,5)));
            blup_fold_validate.STD_lineEdit->setText(csv_list[1].mid(0,5));
        }
        else
        {
            blup_fold_validate.ACC_lineEdit->setText("NA");
            blup_fold_validate.STD_lineEdit->setText("NA");
            QMessageBox::warning(NULL, "File error:", "Can't open the validate file!");
            return false;
        }
    }
    return true;
}







