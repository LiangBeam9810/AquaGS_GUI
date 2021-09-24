#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("AquaGS");
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    out_line = ui->output_lineEdit;
    csv_line = ui->csv_lineEdit;
    vcf_line = ui->vcf_lineEdit;
    /*----------StratTAB init---------------------------------------*/
    //ui->csv_input_lineEdit->setText("Enter/Select the csv file.");
    //ui->vcf_input_lineEdit->setText("Enter/Select the vcf file.");
    //ui->out_lineEdit->setText("Enter/Select the output folder.");
    csv_line->setText("/home/zhi/Desktop/AquaGS_GUI/Input/ABT20210617.csv");
    vcf_line->setText("/home/zhi/Desktop/AquaGS_GUI/snp_abt_630_imput_out_select48K.vcf");
    out_line->setText("/home/zhi/Desktop/AquaGS_GUI/Output");
    ui->tabWidget->setCurrentIndex(0);//Start index
    /*--------------------------------------------------------------*/

    /*----------phnotpye init---------------------------------------*/
    phenotype_converted_flag =false;
    ui->phenotype_convert_Button->setEnabled(false);
    ui->phenotype_reset_Button->setEnabled(false);
    ui->phenotype_accept_Button->setEnabled(false);
    ui->phenotype_detial_Button->setEnabled(false);
    ui->convert_swith->setCheckState(Qt::Unchecked);
    ui->outlier_swith->setCheckState(Qt::Unchecked);
    ui->convert_swith->setEnabled(false);
    /*--------------------------------------------------------------*/

    /*----------Effect init-----------------------------------------*/
    //Effect_Init();

    return;
}

/*-------------------------------------- start -----------------------------------------*/
void MainWindow::on_csv_pushButton_clicked()
{
    get_select_path("csv(*csv);;all(*)",this,csv_line,1);
    return;
}

void MainWindow::on_vcf_pushButton_clicked()
{
    get_select_path("vcf(*vcf);;all(*)",this,vcf_line,2);
    return;
}

void MainWindow::on_output_pushButton_clicked()
{
    get_select_path(" ",this,out_line,0);
    return;
}


void MainWindow::on_csv_lineEdit_editingFinished()
{
    get_enter_path( csv_line,1);
    return;
}

void MainWindow::on_vcf_lineEdit_editingFinished()
{
    get_enter_path( vcf_line,2);
    return;
}


void MainWindow::on_output_lineEdit_editingFinished()
{
    get_enter_path( out_line,0);
    return;
}

void MainWindow::on_start_next_pushButton_clicked()
{
    if(check_all_path(ui->output_lineEdit,ui->csv_lineEdit,ui->vcf_lineEdit,&output_path,&csv_path,&vcf_path))
    {
        start_complete_flag = true;
        Phenotype_Init();
        ui->tabWidget->setCurrentIndex(1);//To the next index.
    }
    return ;
}

/*---------------------------------phenotype--------------------------------------*/
void MainWindow::Phenotype_Init()
{
    if(!start_complete_flag)
    {

    }
    else
    {
        phenotype_select_line.AnimalID_ComboBox = ui->AnimalID_ComboBox;
        phenotype_select_line.Dam_ComboBox = ui->Dam_ComboBox;
        phenotype_select_line.Sire_ComboBox = ui->Sire_ComboBox;
        phenotype_select_line.target_phenotype_ComboBox = ui->phenotype_ComboBox;
        phenotype_select_line.outlier_CheckBox = ui->outlier_swith;
        phenotype_select_line_init(phenotype_select_line,csv_path,&phenotype_list);
    }
}

void MainWindow::on_outlier_swith_stateChanged(int arg1)
{
    qDebug()<< endl << "outlier swith state :"<< arg1 << endl;
}

void MainWindow::on_convert_swith_stateChanged(int arg1)
{
    qDebug()<< endl << "convertswith state :"<< arg1 << endl;
    change_convert_wight_state(arg1, ui->phenotype_convert_Button,ui->phenotype_reset_Button,ui->phenotype_accept_Button,ui->phenotype_detial_Button);
    return;
}

void MainWindow::on_phenotype_run_Button_clicked()
{
    unsigned int outlier_state = 0;
    check_all_path(ui->output_lineEdit,ui->csv_lineEdit,ui->vcf_lineEdit,&output_path,&csv_path,&vcf_path);//ever time click run,the path need to be reload.
    init_ready_for_run(ui->skewnessdisplay_1,ui->kurtosisdisplay_1,ui->horizontallabel_1,
                       ui->skewnessdisplay_2,ui->kurtosisdisplay_2,ui->horizontallabel_2,
                       ui->outlier_swith,
                       ui->phenotype_ComboBox,
                       ui->phenotype_accept_Button,
                       ui->convert_swith,
                       &outlier_state,&fist_convert_flag,&target_phenotype_index);
    phenotype_select_line_get_index(phenotype_select_line,&target_phenotype_index,&AnimalID_phenotype_index,&Dam_phenotype_index,&Sire_phenotype_index);
    if(outlier_elimination(&csv_path,outlier_state,target_phenotype_index))
    {
        qDebug()<<endl<<"outlier completed!"<<endl;
        qDebug()<<endl<<"csv path:"<<csv_path<<endl;
        qDebug()<<"target_index:"<<target_phenotype_index;
        qDebug()<<"ID_index:"<<AnimalID_phenotype_index;
        qDebug()<<"Dam_index:"<<Dam_phenotype_index;
        qDebug()<<"Sire_index:"<<Sire_phenotype_index;
    }
    else {
        qDebug()<<endl<<"outlier error!"<<endl;
        return;
    }

    if( display_normality(csv_path,output_path,target_phenotype_index,"original",
                          ui->skewnessdisplay_1,ui->kurtosisdisplay_1,ui->horizontallabel_1))
    {
        qDebug()<<endl<<"display completed!"<<endl;
    }
    else {
        qDebug()<<endl<<"display error!"<<endl;
        return;
    }
}



void MainWindow::on_phenotype_convert_Button_clicked()
{
    QString csv_path_new = csv_path;
       //can't using "csv_path.replace(".csv", "_new.csv")" directly.
       csv_path_new.replace(".csv","_converted.csv");
       //becuase of the end of phenotype_list is '',so phenotype_list.count() = the number of not empty strings + 1
       unsigned int target_phenotype_index_new = phenotype_list.count();

       qDebug()<<endl<<"csv_path:" <<csv_path<<endl;
       qDebug()<<endl<<"csv_path_new:" <<csv_path_new<<endl;
       qDebug()<<endl<<"phenotype_list:"<<phenotype_list<<endl;
       qDebug()<<endl<<"lenth of phenotype_list: "<<phenotype_list.count()<<endl;
       qDebug()<<endl<<"index of new: "<<target_phenotype_index_new<<endl;
       if(fist_convert_flag)
       {
           qDebug()<<endl<<"fist convert!"<<endl;
           convert_phenotype(csv_path,target_phenotype_index,fist_convert_flag);
           display_normality(csv_path_new,output_path,target_phenotype_index_new,"converted",
                             ui->skewnessdisplay_2,ui->kurtosisdisplay_2,ui->horizontallabel_2);
           fist_convert_flag = 0;
           ui->phenotype_accept_Button->setEnabled(true);
           ui->phenotype_detial_Button->setEnabled(true);
       }
       else{

           convert_phenotype(csv_path_new,target_phenotype_index_new,fist_convert_flag);
           display_normality(csv_path_new,output_path,target_phenotype_index_new,"converted",
                             ui->skewnessdisplay_2,ui->kurtosisdisplay_2, ui->horizontallabel_2);

       }
       return;
}


void MainWindow::on_phenotype_reset_Button_clicked()
{
    clean_normality_index(ui->skewnessdisplay_2,ui->kurtosisdisplay_2,ui->horizontallabel_2);
    fist_convert_flag = 1 ;//The new start from now on,need to init flag&path
    return;
}


void MainWindow::on_phenotype_accept_Button_clicked()
{
    csv_path.replace(".csv","_converted.csv");
    target_phenotype_index = phenotype_list.count();
    qDebug() << endl << "the final csv_path: "<<csv_path << endl <<"the final index: "<<target_phenotype_index<<endl;
    QMessageBox::information(NULL, "OK", "Phnotype ready");
    change_convert_wight_state(0, ui->phenotype_convert_Button,ui->phenotype_reset_Button,ui->phenotype_accept_Button,ui->phenotype_detial_Button);
    ui->convert_swith->setEnabled(false);
    phenotype_converted_flag =true;
    return;
}

void MainWindow::on_phenotype_next_pushButton_clicked()
{

     if(check_convert_path_of_phenotype(phenotype_converted_flag,ui->convert_swith))
     {
         ui->tabWidget->setCurrentIndex(2);
     }
     else
     {
          QMessageBox::warning(NULL, "OK", "The converted switch was checked, but no converted phenotype was accepted!");
     }
     return;
}



/*-------------------------------------- QC -----------------------------------------*/


void MainWindow::on_qc_next_pushButton_clicked()
{

    QString phenotype = csv_path;
    QString genotype = vcf_path;
    QString out = output_path;

    this->runningFlag = true;
    ui->qc_next_pushButton->setDisabled(true);
    qApp->processEvents();

    QFuture<void> fu = QtConcurrent::run(QThreadPool::globalInstance(), [&]()
    {
        if (!this->callPlinkGwas(phenotype, genotype, out))
        {
            emit resetWindowSig();
            QThread::msleep(10);
            return;
        }
        qDebug()  << "After callPlinkGs" << endl;

   });
    while (!fu.isFinished())
    {
        qApp->processEvents(QEventLoop::AllEvents, 50);
        QThread::msleep(10);
    }

    this->runningFlag = false;
    ui->qc_next_pushButton->setEnabled(true);

    /*-----------------*/
    A_G_matirx_build();
    Effect_Init();
    if(prepare_effect(fixed_effect_input))
    {
        qDebug()<<endl<<"prepare fixed effect complete"<<endl;
        QStringList NULL_List;
        prepare_phenotype(csv_path,&NULL_List,ui->AnimalID_ComboBox);
        ui->tabWidget->setCurrentIndex(3);
    }
    else {
        qDebug()<<endl<<"error in preparing fixed effect "<<endl;
    }
    /*--------------------------------------------------------------------*/

}

bool MainWindow::callPlinkGwas(QString phenotype, QString genotype, QString out)
{

    QString runPath1 = QDir::currentPath();
//    runPath.append("/rscript/fixed_effect_testing.R");
    qDebug() << endl <<"runPath1:" << runPath1 << endl;

    QString maf = ui->mafcheckBox->isChecked()? ui->mafdoubleSpinBox->text():nullptr;
    QString mind = ui->mindcheckBox->isChecked()? ui->minddoubleSpinBox->text():nullptr;
    QString geno = ui->genocheckBox->isChecked()? ui->genodoubleSpinBox->text():nullptr;
    QString hwe = ui->hwcheckBox->isChecked()? ui->hwdoubleSpinBox->text():nullptr;

    QString plinkpath = runPath1.append("/plink/");
//    QString plinkpath = "/home/zhi/Desktop/AquaGS_GUI-main/plink/";
    //这里修改生成的中间文件和输出raw的路径
    QString file2=plinkpath+"files/"+"file2";
    QString file3=plinkpath+"files/"+"file3";
    QString file4=plinkpath+"files/"+"file4";
    QString file5=plinkpath+"files/"+"file5";
    QString outfile=out+"/raw_output";
    raw_path = outfile+".raw";
    Plink plink;

    plink.part1(genotype, file2);
    if (!runExTool(plinkpath+"plink", plink.getParamList()))
    {
        return false;
    }

    plink.part2(file2, geno, maf, mind, file3);
    if (!runExTool(plinkpath+"plink", plink.getParamList()))
    {
        return false;
    }

    plink.part3(file3, hwe, file4);
    if (!runExTool(plinkpath+"plink", plink.getParamList()))
    {
        return false;
    }

    if (ui->swcheckBox->isChecked())
    {
        QString winSize, stepLen, r2Threshold;

        winSize = ui->winsizedoubleSpinBox->text();
        stepLen = ui->steplengthdoubleSpinBox->text();
        r2Threshold = ui->r2doubleSpinBox->text();
        plink.part4(file4, winSize, stepLen, r2Threshold, file5);
        if (!runExTool(plinkpath+"plink", plink.getParamList()))
        {
            return false;
        }
        plink.part5(file5, outfile);
        if (!runExTool(plinkpath+"plink", plink.getParamList()))
        {
            return false;
        }

    }
    else
    {
        plink.part6(file4, outfile);
        if (!runExTool(plinkpath+"plink", plink.getParamList()))
        {
            return false;
        }

    }

    return true;

}
bool MainWindow::runExTool(QString tool, QStringList param)
{
    Process *proc = new Process;

    // Read message form Process and display in RunningMsgWidget
    connect(proc, SIGNAL(outMessageReady(QString)), this, SLOT(on_outMessageReady(QString)));
    connect(proc, SIGNAL(errMessageReady(QString)), this, SLOT(on_errMessageReady(QString)));
   // connect(this, SIGNAL(terminateProcess()), proc, SLOT(on_terminateProcess()), Qt::DirectConnection);

    // proc->execute(tool, param);
    static int i = 0;
    proc->start(tool, param);
    if (!proc->waitForStarted())
    {
        emit setMsgBoxSig("Error", "Can't open " + tool);
        delete proc;
        proc = nullptr;
        return false;
    }
    proc->waitForFinished(-1);

    ++i;
    qDebug() << "i: " << i << endl
             << tool << endl << param << endl;

    bool ret = true;
    proc->close();
    delete proc;
    proc = nullptr;

    return ret;
}
void MainWindow::on_outMessageReady(const QString text)
{
    if (this->runningFlag)
    {
        qDebug() << "Out: " << text << endl;
        qApp->processEvents();
    }
}

void MainWindow::on_errMessageReady(const QString text)
{
    if (this->runningFlag)
    {
        qDebug() << "Error: " << text << endl;
    }
}
/*---------------------------------------------------------------------------------------*/
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




/*-------------------------------------- Effect -----------------------------------------*/
//Fixed effect part
void MainWindow::Effect_Init()
{


    fixed_effect_input.input_path = Rdata_path;
    fixed_effect_input.output_path = output_path;
    fixed_effect_input.A_matrix_path = A_matrix_path;
    fixed_effect_input.G_matrix_path = G_matrix_path;
    fixed_effect_input.original_tableview = ui->fixed_phenotype_pr_TableView;
    fixed_effect_input.selected_tableview = ui->fixed_selected_TableView;
    fixed_effect_input.animal_combobox = ui->AnimalID_ComboBox;
    fixed_effect_input.randeff_testing_combobox = ui->random_effec_testing_ComboBox;
    fixed_effect_input.target_index = target_phenotype_index;
    fixed_effect_input.process_random_flag = 0;
    fixed_effect_input.fixed_effect_list = &fixed_effect_list;
    fixed_effect_input.random_effect_list = &random_effect_list;

    random_effect_input.input_path = Rdata_path;
    random_effect_input.output_path = output_path;
    random_effect_input.A_matrix_path = A_matrix_path;
    random_effect_input.G_matrix_path = G_matrix_path;
    random_effect_input.original_tableview = ui->random_phenotype_pr_TableView;
    random_effect_input.selected_tableview = ui->random_selected_TableView;
    random_effect_input.animal_combobox = ui->AnimalID_ComboBox;
    random_effect_input.randeff_testing_combobox = ui->random_effec_testing_ComboBox;
    random_effect_input.AnimalID_index = &AnimalID_phenotype_index;
    random_effect_input.target_index = target_phenotype_index;
    random_effect_input.process_random_flag = 1;
    random_effect_input.fixed_effect_list = &fixed_effect_list;
    random_effect_input.random_effect_list = &random_effect_list;

    fixed_effect_list.clear();
    random_effect_list.clear();
    selected_fixed_flag = false;
    selected_random_flag = false;
    ui->random_accept_pushButton->setEnabled(false);
    ui->random_exclude_Button->setEnabled(false);
    ui->random_select_Button->setEnabled(false);
    ui->fixed_accept_pushButton->setEnabled(false);
    ui->fixed_exclude_Button->setEnabled(false);
    ui->fixed_select_Button->setEnabled(false);
}

void MainWindow::on_fixed_phenotype_pr_TableView_clicked(const QModelIndex &index)
{
    //qDebug()<<endl<<"fixed_tableview_clicked:" <<index<<endl;
    change_select_exclude_Button(1,selected_fixed_flag,ui->fixed_select_Button,ui->fixed_exclude_Button);
    return;
}
void MainWindow::on_fixed_selected_TableView_clicked(const QModelIndex &index)
{
    //qDebug()<<endl<<"fixed_tableview_clicked:" <<index<<endl;
    change_select_exclude_Button(0,selected_fixed_flag,ui->fixed_select_Button,ui->fixed_exclude_Button);
    return;
}
void MainWindow::on_fixed_select_Button_clicked()
{
    add_item2effect_list(ui->fixed_phenotype_pr_TableView,phenotype_list,&fixed_effect_list);
    qDebug()<<endl<<"fixed_effect_list  is "<<fixed_effect_list<<endl;
    prepare_effect(fixed_effect_input);
    ui->fixed_accept_pushButton->setEnabled(true);
}
void MainWindow::on_fixed_exclude_Button_clicked()
{
    remove_item_from_effect_list(ui->fixed_selected_TableView, &fixed_effect_list);
    prepare_effect(fixed_effect_input);
    if(isTableView_empty(ui->fixed_selected_TableView))
    {
        ui->fixed_accept_pushButton->setEnabled(false);
        qDebug()<<endl<<"selected tableview is empty"<<endl;
    }
    else
    {
        ui->fixed_accept_pushButton->setEnabled(true);
        qDebug()<<endl<<"selected tableview is  no empty"<<endl;
    }
}
void MainWindow::on_fixed_accept_pushButton_clicked()
{
    selected_fixed_flag = true;
    prepare_effect(random_effect_input);
    change_select_exclude_Button(0,selected_fixed_flag,ui->fixed_select_Button,ui->fixed_exclude_Button);
    ui->fixed_accept_pushButton->setEnabled(false);
}
//random effect part
void MainWindow::on_random_phenotype_pr_TableView_clicked(const QModelIndex &index)
{
    change_select_exclude_Button(1,selected_random_flag,ui->random_select_Button,ui->random_exclude_Button);
    return;
}
void MainWindow::on_random_selected_TableView_clicked(const QModelIndex &index)
{
    change_select_exclude_Button(0,selected_random_flag,ui->random_select_Button,ui->random_exclude_Button);
    return;
}
void MainWindow::on_random_select_Button_clicked()
{
    if(random_effect_list.count()&&(!ui->random_effec_testing_ComboBox->currentIndex()))//ui->random_effec_testing_ComboBox->currentIndex()=0 is use
                                                                                        //lemer to test random effect
    {
        QMessageBox::warning(NULL, "Error ","The maxium  of random effect testing \n named  \"lmer\" is 1." );
    }
    else
    {
        add_item2effect_list(ui->random_phenotype_pr_TableView,phenotype_list,&random_effect_list);
        prepare_effect(random_effect_input);
    }
    ui->random_accept_pushButton->setEnabled(true);
}
void MainWindow::on_random_exclude_Button_clicked()
{
    remove_item_from_effect_list(ui->random_selected_TableView, &random_effect_list);
    prepare_effect(random_effect_input);
    if(isTableView_empty(ui->random_selected_TableView))
    {
        ui->random_accept_pushButton->setEnabled(false);
        qDebug()<<endl<<"selected tableview is empty"<<endl;
    }
    else
    {
        ui->random_accept_pushButton->setEnabled(true);
        qDebug()<<endl<<"selected tableview is  no empty"<<endl;
    }
}
void MainWindow::on_random_accept_pushButton_clicked()
{
    selected_random_flag = true;
    change_select_exclude_Button(0,selected_random_flag,ui->random_select_Button,ui->random_exclude_Button);
    ui->random_accept_pushButton->setEnabled(false);
}
void MainWindow::on_effect_reset_pushButton_clicked()
{
    Effect_Init();
    prepare_effect(fixed_effect_input);
}
void MainWindow::on_AnimalID_ComboBox_currentIndexChanged(int index)
{
    AnimalID_phenotype_index = index;
}


void MainWindow::on_effect_next_pushButton_clicked()
{
    AnimalID_phenotype_index = ui->AnimalID_ComboBox->currentIndex();
    if(ui->fixed_accept_pushButton->isEnabled()||ui->fixed_accept_pushButton->isEnabled())
    {
       QMessageBox::warning(NULL, "Error ","pleas accept this effect." );
    }
    else
    {
        classical_method_Init();
        ui->tabWidget->setCurrentIndex(4);
    }
}

/*----------------------------------------------------------------------------------------*/
/*---------------------------------class_method-------------------------------------------*/
void MainWindow::classical_method_Init()
{
    blup_mode.fiexd_effect_lineedit = ui->blup_fixed_lineEdit;
    blup_mode.random_effect_lineedit = ui->blup_random_lineEdit;

    blup_mode.BLUP_accept_pushButtom = ui->BLUP_accept_pushButtom;
    blup_mode.BLUP_mode_ComboBox = ui->BLUP_mode_ComboBox;
    blup_mode.trans_formula_1_ComboBox = ui->trans_formula_1_ComboBox;
    blup_mode.trans_formula_2_ComboBox = ui->trans_formula_2_ComboBox;
    blup_mode.A_matrix_path = A_matrix_path;
    blup_mode.G_matrix_path = G_matrix_path;
    blup_mode.Rdata_path = Rdata_path;
    blup_mode.output_path = output_path;
    blup_mode.output_path.append("/GEBV.txt");
    classical_GEBV_path = blup_mode.output_path;
    bayes_GEBV_path = output_path+"/bayes_GEBV.txt";
    blup_mode.AnimalID_index = AnimalID_phenotype_index;
    blup_mode.target_index = target_phenotype_index;

    blup_mode.fixed_effect_list = fixed_effect_list;
    blup_mode.random_effect_list = random_effect_list;
    blup_mode.fixed_effect_list2R = fixed_effect_list;
    blup_mode.random_effect_list2R= random_effect_list;
    for(int i = 0;i < (fixed_effect_list.count());i++){
         blup_mode.fixed_effect_list[i] = phenotype_list[(fixed_effect_list[i].toInt())];
         qDebug()<<phenotype_list[(fixed_effect_list[i].toInt())];
    }

    for(int i = 0;i < random_effect_list.length();i++){
         blup_mode.random_effect_list[i] = phenotype_list[(random_effect_list[i].toInt())];
         qDebug()<<blup_mode.random_effect_list[i];
    }
    blup_fold_validate.Rdata_path = Rdata_path;
    blup_fold_validate.output_path = output_path;
    blup_fold_validate.output_path.append("/classical_accuracy.csv");
    blup_fold_validate.ACC_lineEdit = ui->class_val_accuracy_lineEdit;
    blup_fold_validate.STD_lineEdit = ui->class_val_std_lineEdit;
    blup_fold_validate.cross_validation_checkBox = ui->cross_validation_checkBox;
    blup_fold_validate.k_flod_times_ComboBox = ui->k_flod_times_ComboBox;
    blup_fold_validate.fixed_effect_list = fixed_effect_list;
    blup_fold_validate.random_effect_list = random_effect_list;
    blup_fold_validate.cross_validation_pushbutton = ui->classical_validate_pushButtom;

    blup_alphamate_all.alphmate_checkBox = ui->alphmate_checkBox;
    blup_alphamate_all.classical_more_Button = ui->classical_more_Button_3;
    blup_alphamate_all.classical_mate_Button = ui->classical_mate_Button_3;
    blup_alphamate_all.TargetDegree_spinBox = ui-> TargetDegree_spinBox_3;
    blup_alphamate_all.TargetCoancestryRate_doubleSpinBox = ui->TargetCoancestryRate_doubleSpinBox_3;
    blup_alphamate_all.SelCriterionFile_lineEdit = ui->SelCriterionFile_lineEdit_3 ;
    blup_alphamate_all.NumberOfMatings_spinBox = ui->NumberOfMatings_spinBox_3;
    blup_alphamate_all.NumberOfMaleParents_spinBox = ui->NumberOfMaleParents_spinBox_3;
    blup_alphamate_all.NumberOfFemaleParents_spinBox = ui -> NumberOfFemaleParents_spinBox_3;
    blup_alphamate_all.NrmMatrix_lineEdit = ui->NrmMatrix_lineEdit_3;
    blup_alphamate_all.ModeOpt_checkBox = ui->ModeOpt_checkBox_3;
    blup_alphamate_all.ModeMinInbreeding_checkBox= ui->ModeMinInbreeding_checkBox_3;
    blup_alphamate_all.ModeMinCoancestry_checkBox= ui->ModeMinCoancestry_checkBox_3;
    blup_alphamate_all.ModeMaxCriterion_checkBox = ui->ModeMaxCriterion_checkBox_3;
    blup_alphamate_all.GenderFile_lineEdit = ui->GenderFile_lineEdit_3;
    blup_alphamate_all.EvaluateFrontier_checkBox = ui->EvaluateFrontier_checkBox_3;
    blup_alphamate_all.EqualizeMaleContributions_checkBox = ui->EqualizeMaleContributions_checkBox_3;
    blup_alphamate_all.EqualizeFemaleContributions_checkBox = ui->EqualizeFemaleContributions_checkBox_3;
    blup_alphamate_all.GenderFile_CheckBox = ui->GenderFile_checkBox_3;

    bayes_alphamate_all.alphmate_checkBox = ui->alphmate_checkBox_2;
    bayes_alphamate_all.classical_more_Button = ui->classical_more_Button_4;
    bayes_alphamate_all.classical_mate_Button = ui->classical_mate_Button_4;
    bayes_alphamate_all.TargetDegree_spinBox = ui-> TargetDegree_spinBox_4;
    bayes_alphamate_all.TargetCoancestryRate_doubleSpinBox = ui->TargetCoancestryRate_doubleSpinBox_4;
    bayes_alphamate_all.SelCriterionFile_lineEdit = ui->SelCriterionFile_lineEdit_4 ;
    bayes_alphamate_all.NumberOfMatings_spinBox = ui->NumberOfMatings_spinBox_4;
    bayes_alphamate_all.NumberOfMaleParents_spinBox = ui->NumberOfMaleParents_spinBox_4;
    bayes_alphamate_all.NumberOfFemaleParents_spinBox = ui -> NumberOfFemaleParents_spinBox_4;
    bayes_alphamate_all.NrmMatrix_lineEdit = ui->NrmMatrix_lineEdit_4;
    bayes_alphamate_all.ModeOpt_checkBox = ui->ModeOpt_checkBox_4;
    bayes_alphamate_all.ModeMinInbreeding_checkBox= ui->ModeMinInbreeding_checkBox_4;
    bayes_alphamate_all.ModeMinCoancestry_checkBox= ui->ModeMinCoancestry_checkBox_4;
    bayes_alphamate_all.ModeMaxCriterion_checkBox = ui->ModeMaxCriterion_checkBox_4;
    bayes_alphamate_all.GenderFile_lineEdit = ui->GenderFile_lineEdit_4;
    bayes_alphamate_all.EvaluateFrontier_checkBox = ui->EvaluateFrontier_checkBox_4;
    bayes_alphamate_all.EqualizeMaleContributions_checkBox = ui->EqualizeMaleContributions_checkBox_4;
    bayes_alphamate_all.EqualizeFemaleContributions_checkBox = ui->EqualizeFemaleContributions_checkBox_4;
    bayes_alphamate_all.GenderFile_CheckBox = ui->GenderFile_checkBox_4;

    QString runPath = QDir::currentPath();
    Alphamate_running_path =  runPath;
    Alphamate_running_path.append("/AlphaMateLinux");

    if(blup_mode.BLUP_mode_ComboBox->currentIndex())
    {
        blup_alphamate_all.NrmMatrix_lineEdit->setText(G_matrix_path);
        bayes_alphamate_all.NrmMatrix_lineEdit->setText(G_matrix_path);
        qDebug()<<"GBLUP  NrmMatrix PATH : "<<G_matrix_path;
    }else{
        blup_alphamate_all.NrmMatrix_lineEdit->setText(A_matrix_path);
        bayes_alphamate_all.NrmMatrix_lineEdit->setText(A_matrix_path);
        qDebug()<<"BLUP  NrmMatrix PATH : "<<A_matrix_path;
    }
    blup_alphamate_all.SelCriterionFile_lineEdit->setText(classical_GEBV_path);
    bayes_alphamate_all.SelCriterionFile_lineEdit->setText(classical_GEBV_path);
    qDebug()<<"SelCriterionFile PATH : "<<classical_GEBV_path;
    Gender_path =  "/home/liang/Documents/AquaGS_GUI/Output/gender.txt";//
    blup_alphamate_all.GenderFile_lineEdit->setText(Gender_path);
    bayes_alphamate_all.GenderFile_lineEdit->setText(Gender_path);

    blup_Init(blup_mode);
    blup_fold_validate_Init(blup_fold_validate);
    blup_alphamate_Init(blup_alphamate_all);
    blup_alphamate_Init(bayes_alphamate_all);
}

void MainWindow::on_BLUP_mode_ComboBox_currentIndexChanged(int index)
{
    classical_method_Init();
}


void MainWindow::on_BLUP_accept_pushButtom_clicked()
{
    blup_build(blup_mode);
}

void MainWindow::on_cross_validation_checkBox_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        blup_fold_validate.k_flod_times_ComboBox->setEnabled(true);
        blup_fold_validate.cross_validation_pushbutton->setEnabled(true);
    }
}

void MainWindow::on_classical_validate_pushButtom_clicked()
{
    if(classical_method_cross_validation_and_display(blup_mode,blup_fold_validate))
    {
        qDebug()<<"cross validation complete!";
    }
}
void MainWindow::on_alphmate_checkBox_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        alphmate_enable_all(blup_alphamate_all);
    }else{
        alphmate_disable_all(blup_alphamate_all);
    }
}
void MainWindow::on_classical_more_Button_3_clicked()
{
    alphamate *alphamate_window = new alphamate(this);
    alphamate_window->show();
}

void MainWindow::on_GenderFile_checkBox_3_stateChanged(int arg1)
{
    if((ui->alphmate_checkBox->checkState() == Qt::Checked)&& arg1 == 2)
    {
        alphmate_able_gender(blup_alphamate_all,true);
    }else
    {
        alphmate_able_gender(blup_alphamate_all,false);
    }
}

void MainWindow::on_classical_mate_Button_3_clicked()
{
     running_alphamate(blup_alphamate_all,Alphamate_running_path,output_path);
}



/*----------------------------------------------------------------------------------------*/
/*---------------------------------bayes_method-------------------------------------------*/



void MainWindow::on_bayesrunpushButton_clicked()
{

    QString runPath = QDir::currentPath();
    runPath.append("/rscript/bayes1.R");
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
    param.append(output_path);
    param.append(" ");
    param.append(output_path+"/raw_output.raw");
    param.append(" ");
    param.append(ui->modelcomboBox->currentText());
    param.append(" ");
    param.append(ui->k_flod_ComboBox->currentText());
    param.append(" ");
    param.append(ui->iterationspinBox->text());
    param.append(" ");
    param.append(ui->dropoutspinBox->text());
    param.append(" ");

    qDebug()<< endl<<"display param :"<<param<< endl;

    //QMessageBox::information(NULL, "Massage", "This will take a few minutes");

    QProcess display_process;

    display_process.execute(param);
    if(display_process.waitForStarted())
    {
        qDebug()<<"OUTLIER PROCESS STRATED";
        display_process.close();

    }
    if(display_process.waitForFinished())
    {
        qDebug()<<"OUTLIER PROCESS FINISHED";
        display_process.close();

    }
    display_process.close();

    QFile f(output_path+"/bayes_output.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }

    QTextStream txtInput(&f);
    QStringList bayesoutput;
    QString lineStr;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
          bayesoutput.append(lineStr);
        qDebug() << lineStr << endl;
    }

    f.close();

    ui->accuracytextBrowser->insertPlainText(bayesoutput[0]);
    ui->herittextBrowser->insertPlainText(bayesoutput[1]);
    ui->varcomp1textBrowser->insertPlainText(bayesoutput[2]);
    ui->varcomp2textBrowser->insertPlainText(bayesoutput[3]);

}


void MainWindow::on_alphmate_checkBox_2_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        alphmate_enable_all(bayes_alphamate_all);
    }else{
        alphmate_disable_all(bayes_alphamate_all);
    }
}
void MainWindow::on_classical_more_Button_4_clicked()
{
    alphamate *alphamate_window = new alphamate(this);
    alphamate_window->show();
}

void MainWindow::on_GenderFile_checkBox_4_stateChanged(int arg1)
{
    if((ui->alphmate_checkBox->checkState() == Qt::Checked)&& arg1 == 2)
    {
        alphmate_able_gender(bayes_alphamate_all,true);
    }else
    {
        alphmate_able_gender(bayes_alphamate_all,false);
    }
}

void MainWindow::on_classical_mate_Button_4_clicked()
{

    running_alphamate(bayes_alphamate_all,Alphamate_running_path,output_path);

}
