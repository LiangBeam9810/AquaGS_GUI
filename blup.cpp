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
    param.append(" ");  param.append(runPath);
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
    Process *A_G_matirx_build_process;
    A_G_matirx_build_process = new Process;
    if(!A_G_matirx_build_process->runRscript(param," Building A and G matirx "))
    {
        QMessageBox::warning(NULL, "Process error:", "Can't open the A&G matirx build process!");
        return false;
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
        blup_input.classical_Estimate_textBrowser->setText((csv_list[0].mid(0,5)));
        blup_input.classical_SE_textBrowser->setText(csv_list[1].mid(0,5));
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
}

bool blup_build(blup blup_input)
{
    unsigned int mode_flag = blup_input.BLUP_mode_ComboBox->currentIndex();
    QString runPath = QDir::currentPath();
    if(blup_input.trans_formula_1_lineEdit->text().isEmpty() || blup_input.trans_formula_2_lineEdit->text().isEmpty())
    {
        QMessageBox::warning(NULL, "Formula error:", "Please enter the formula !");
        return false;
    }
    QString formula = "";
    formula = blup_input.trans_formula_1_lineEdit->text()+"~("+blup_input.trans_formula_2_lineEdit->text()+")";
    qDebug()<<"formula : "<<formula;
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
        if(csv_list.isEmpty())
        {
            return false;
        }
        blup_fold_validate.ACC_lineEdit->setText((csv_list[0].mid(0,5)));
        blup_fold_validate.STD_lineEdit->setText(csv_list[1].mid(0,5));
    }
    return true;
}







