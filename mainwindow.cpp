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
/*-------------------------------------- Global auxiliary function -----------------------------------------*/




/*------------------------------------------------------------------------ */
void MainWindow::init()
{
    out_line = ui->output_lineEdit;
    csv_line = ui->csv_lineEdit;
    vcf_line = ui->vcf_lineEdit;
    /*----------StratTAB init---------------------------------------*/
    //ui->csv_input_lineEdit->setText("Enter/Select the csv file.");
    //ui->vcf_input_lineEdit->setText("Enter/Select the vcf file.");
    //ui->out_lineEdit->setText("Enter/Select the output folder.");
    csv_line->setText("/home/liang/Documents/AquaGS_GUI/Input/ABT20210617.csv");
    vcf_line->setText("/home/liang/Documents/AquaGS_GUI/snp_abt_630_imput_out_select48K.vcf");
    out_line->setText("/home/liang/Desktop");
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
        phenotype_select_line.Gender_CheckBox = ui->Gender_CheckBox;
        phenotype_select_line.Gender_ComboBox = ui->Gender_ComboBox;
        phenotype_select_line_init(phenotype_select_line,csv_path,&phenotype_list);
        ui->Gender_ComboBox->setEnabled(false);
        ui->Dam_ComboBox->setEnabled(false);
        ui->Sire_ComboBox->setEnabled(false);
    }
    return;
}

void MainWindow::on_outlier_swith_stateChanged(int arg1)
{
    qDebug()<< endl << "outlier swith state :"<< arg1 << endl;
    return;
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
    check_all_path(ui->output_lineEdit,
                   ui->csv_lineEdit,
                   ui->vcf_lineEdit,
                   &output_path,
                   &csv_path,
                   &vcf_path);//if clicked run buttun,the path need to be reload.
    init_ready_for_run(ui->skewnessdisplay_1,ui->kurtosisdisplay_1,ui->horizontallabel_1,
                       ui->skewnessdisplay_2,ui->kurtosisdisplay_2,ui->horizontallabel_2,
                       ui->outlier_swith,
                       ui->phenotype_ComboBox,
                       ui->phenotype_accept_Button,
                       ui->convert_swith,
                       &outlier_state,
                       &fist_convert_flag,
                       &target_phenotype_index);
    phenotype_select_line_get_index(phenotype_select_line,
                                    &target_phenotype_index,
                                    &AnimalID_phenotype_index,
                                    &Dam_phenotype_index,
                                    &Sire_phenotype_index,
                                    &Gender_phenotype_index);
    if(outlier_elimination(&csv_path,outlier_state,target_phenotype_index))
    {
        qDebug()<<endl<<"outlier completed!"<<endl;
        qDebug()<<endl<<"csv path:"<<csv_path<<endl;
        qDebug()<<"target_index:"<<target_phenotype_index;
        qDebug()<<"ID_index:"<<AnimalID_phenotype_index;
        qDebug()<<"Dam_index:"<<Dam_phenotype_index;
        qDebug()<<"Sire_index:"<<Sire_phenotype_index;
        qDebug()<<"Gender_index:"<<Gender_phenotype_index;
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

         if(blup_Hblup_flag == false)
         {
             QMessageBox::warning(NULL, "OK", "\"Dam\" and \"Sire\" is missing.\n Please select \"GBlup\" in the \"Classical method \"");
         }
         ui->tabWidget->setCurrentIndex(2);//显示下一页
    }
     else //没有点击accept按钮 确认正态转换后的数据
     {
          QMessageBox::warning(NULL, "OK", "The converted switch was checked, but no converted phenotype was accepted!");
     }
     return;
}

void MainWindow::on_AnimalID_ComboBox_currentIndexChanged(int index)
{
    AnimalID_phenotype_index = index;
}

void MainWindow::on_Gender_CheckBox_stateChanged(int arg1)
{
    qDebug()<<arg1;
    if(arg1 == 2)
    {
        ui->Gender_ComboBox->setEnabled(true);
        gender_flag = true;
    }
    else {
        ui->Gender_ComboBox->setEnabled(false);
        gender_flag = false;
    }
}


void MainWindow::on_Blup_CheckBox_stateChanged(int arg1)
{
    qDebug()<<arg1;
    if(arg1 == 2)
    {
        ui->Dam_ComboBox->setEnabled(true);
        ui->Sire_ComboBox->setEnabled(true);
        blup_Hblup_flag = true;
    }
    else {
        ui->Dam_ComboBox->setEnabled(false);
        ui->Sire_ComboBox->setEnabled(false);
        blup_Hblup_flag = false;
    }
}


/*-------------------------------------- QC -----------------------------------------*/


void MainWindow::on_qc_next_pushButton_clicked()
{

    if(ui->genofillcheckBox->isChecked())
    {

        QString newvcf = ui->genofill_output_lineEdit->text();

        QString param0 = "source /etc/profile";
        QProcess display_process0;
        display_process0.execute(param0);

        QString runPath = QDir::currentPath();
        runPath.append("/beagle.28Jun21.220.jar");
        qDebug() << endl <<"runPath:" << runPath << endl;
        QString param;
        // The sequence of param is not changeable
        param.clear();
        param.append("java");
        param.append(" ");
        param.append("-jar");
        param.append(" ");
        param.append(runPath);
        param.append(" ");
        param.append("gt="+vcf_path);
        param.append(" ");
        param.append("out="+output_path+"/"+newvcf);
        param.append(" ");
        qDebug()<< endl<<"display param :"<<param<< endl;
        Process* validate_process;
        validate_process = new Process;
        if(!(validate_process->runRscript(param,"Genotype Filling")))
        {
            QMessageBox::warning(NULL, "Process error:", "Can't open the Genotype Filling process!");
            return;
        }

        QString param1 = "gunzip "+output_path+"/"+newvcf+".vcf.gz";
        QProcess display_process1;
        display_process1.execute(param1);
    }

    QString phenotype = csv_path;
    QString genotype;
    if(ui->genofillcheckBox->isChecked())
    {
        genotype = output_path+ui->genofill_output_lineEdit->text()+".vcf";
    }
    else
    {
        genotype = vcf_path;
    }
    QString out = output_path;

    this->runningFlag = true;
    ui->qc_next_pushButton->setDisabled(true);
    qApp->processEvents();

    QFuture<void> fu = QtConcurrent::run(QThreadPool::globalInstance(), [&]()
    {
        if (!this->callPlinkGwas(genotype, out))
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

    A_G_matirx_build();
    if(blup_Hblup_flag) bilud_H_matrix(Rdata_path,output_path, &H_matrix_path);
    Effect_Init();
    if(prepare_effect(fixed_effect_input_Discrete))
    {
        qDebug()<<endl<<"prepare fixed effect complete"<<endl;
        ui->tabWidget->setCurrentIndex(3);
    }
    else {
        qDebug()<<endl<<"error in preparing fixed effect "<<endl;
    }
    /*--------------------------------------------------------------------*/

}



/*---------------------------------------------------------------------------------------*/

/*-------------------------------------- Effect -----------------------------------------*/
//Fixed effect part
void MainWindow::Effect_Init()
{
    fixed_effect_input_Discrete.input_path = Rdata_path;
    fixed_effect_input_Discrete.output_path = output_path;
    fixed_effect_input_Discrete.A_matrix_path = A_matrix_path;
    fixed_effect_input_Discrete.G_matrix_path = G_matrix_path;
    fixed_effect_input_Discrete.original_tableview = ui->fixed_phenotype_pr_TableView;
    fixed_effect_input_Discrete.selected_tableview = ui->fixed_selected_TableView;
    fixed_effect_input_Discrete.animal_combobox = ui->AnimalID_ComboBox;
    fixed_effect_input_Discrete.randeff_testing_combobox = ui->random_effec_testing_ComboBox;
    fixed_effect_input_Discrete.target_index = target_phenotype_index;
    fixed_effect_input_Discrete.process_flag = 1;
    fixed_effect_input_Discrete.fixed_effect_list = &fixed_effect_list;
    fixed_effect_input_Discrete.Discrete_fixed_effect_list = &Discrete_fixed_effect_list;
    //fixed_effect_input_Discrete.Continuous_fixed_effect_list = &Continuous_fixed_effect_list;
    fixed_effect_input_Discrete.random_effect_list = &random_effect_list;

    fixed_effect_input_Continuous.input_path = Rdata_path;
    fixed_effect_input_Continuous.output_path = output_path;
    fixed_effect_input_Continuous.A_matrix_path = A_matrix_path;
    fixed_effect_input_Continuous.G_matrix_path = G_matrix_path;
    fixed_effect_input_Continuous.original_tableview = ui->fixed_phenotype_pr_TableView_2;
    fixed_effect_input_Continuous.selected_tableview = ui->fixed_selected_TableView_2;
    fixed_effect_input_Continuous.animal_combobox = ui->AnimalID_ComboBox;
    fixed_effect_input_Continuous.randeff_testing_combobox = ui->random_effec_testing_ComboBox;
    fixed_effect_input_Continuous.target_index = target_phenotype_index;
    fixed_effect_input_Continuous.process_flag = 2;
    fixed_effect_input_Continuous.fixed_effect_list = &fixed_effect_list;
    fixed_effect_input_Continuous.Discrete_fixed_effect_list = &Discrete_fixed_effect_list;
    //fixed_effect_input_Continuous.Continuous_fixed_effect_list = &Continuous_fixed_effect_list;
    fixed_effect_input_Continuous.random_effect_list = &random_effect_list;

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
    random_effect_input.process_flag = 0;
    random_effect_input.fixed_effect_list = &fixed_effect_list;
    random_effect_input.random_effect_list = &random_effect_list;

    fixed_effect_list.clear();
    Discrete_fixed_effect_list.clear();
    random_effect_list.clear();

    Discrete_selected_fixed_flag = false;
    Continuous_selected_fixed_flag = false;
    selected_random_flag = false;
    clean_tablevie(ui->fixed_phenotype_pr_TableView);
    clean_tablevie(ui->fixed_phenotype_pr_TableView_2);
    clean_tablevie(ui->fixed_selected_TableView);
    clean_tablevie(ui->fixed_selected_TableView_2);
    clean_tablevie(ui->random_selected_TableView);
    clean_tablevie(ui->random_phenotype_pr_TableView);
    ui->random_accept_pushButton->setEnabled(false);
    ui->random_exclude_Button->setEnabled(false);
    ui->random_select_Button->setEnabled(false);
    ui->fixed_accept_pushButton->setEnabled(true);
    ui->fixed_exclude_Button->setEnabled(false);
    ui->fixed_select_Button->setEnabled(false);
    ui->fixed_accept_pushButton_2->setEnabled(true);
    ui->fixed_exclude_Button_2->setEnabled(false);
    ui->fixed_select_Button_2->setEnabled(false);
}
/**********************
* 点击了离散型待选框（左侧）
**********************/
void MainWindow::on_fixed_phenotype_pr_TableView_clicked(const QModelIndex &index)
{
    qDebug()<<endl<<"Discrete_fixed_tableview_clicked:" <<index<<endl;
    change_select_exclude_Button(1,Discrete_selected_fixed_flag,ui->fixed_select_Button,ui->fixed_exclude_Button);
    return;
}
/**********************
* 点击了离散型已选框（右侧）
**********************/
void MainWindow::on_fixed_selected_TableView_clicked(const QModelIndex &index)
{
    qDebug()<<endl<<"Discrete_fixed_tableview_clicked:" <<index<<endl;
    change_select_exclude_Button(0,Discrete_selected_fixed_flag,ui->fixed_select_Button,ui->fixed_exclude_Button);
    return;
}

void MainWindow::on_fixed_select_Button_clicked()
{
    add_item2effect_list(ui->fixed_phenotype_pr_TableView,
                         phenotype_list,&fixed_effect_list);
    prepare_effect(fixed_effect_input_Discrete);
    //ui->fixed_accept_pushButton->setEnabled(true);qDebug()<<endl<<"Discrete_fixed_effect_list  is "<<fixed_effect_list<<endl;
}
void MainWindow::on_fixed_exclude_Button_clicked()
{
    remove_item_from_effect_list(ui->fixed_selected_TableView, &fixed_effect_list);
    prepare_effect(fixed_effect_input_Discrete);
    if(isTableView_empty(ui->fixed_selected_TableView))
    {
        //ui->fixed_accept_pushButton->setEnabled(false);
        qDebug()<<endl<<"selected tableview is empty"<<endl;
    }
    else
    {
        //ui->fixed_accept_pushButton->setEnabled(true);
        qDebug()<<endl<<"selected tableview is  no empty"<<endl;
    }
}
void MainWindow::on_fixed_accept_pushButton_clicked()
{
    Discrete_selected_fixed_flag = true;
    change_select_exclude_Button(0,Discrete_selected_fixed_flag,ui->fixed_select_Button,ui->fixed_exclude_Button);
    ui->fixed_accept_pushButton->setEnabled(false);
    Discrete_fixed_effect_list = fixed_effect_list;//将离散型效应列表记录下来
    qDebug()<<"Discrete fixed effect was accepted ,fixed_effect_list: "<<fixed_effect_list;
    prepare_effect(fixed_effect_input_Continuous);//准备刷新连续型固定效应
}

void MainWindow::on_fixed_phenotype_pr_TableView_2_clicked(const QModelIndex &index)
{
    qDebug()<<endl<<"Continuous_fixed_tableview_clicked:" <<index<<endl;
    change_select_exclude_Button(1,Continuous_selected_fixed_flag,ui->fixed_select_Button_2,ui->fixed_exclude_Button_2);
    return;
}

void MainWindow::on_fixed_selected_TableView_2_clicked(const QModelIndex &index)
{
    qDebug()<<endl<<"Continuous_fixed_tableview_clicked:" <<index<<endl;
    change_select_exclude_Button(0,Continuous_selected_fixed_flag,ui->fixed_select_Button_2,ui->fixed_exclude_Button_2);
    return;
}

void MainWindow::on_fixed_select_Button_2_clicked()
{
    add_item2effect_list(ui->fixed_phenotype_pr_TableView_2,phenotype_list,&fixed_effect_list);
    qDebug()<<endl<<"Continuous_fixed_effect_list  is "<<fixed_effect_list<<endl;
    prepare_effect(fixed_effect_input_Continuous);
    //ui->fixed_accept_pushButton_2->setEnabled(true);
}

void MainWindow::on_fixed_exclude_Button_2_clicked()
{
    remove_item_from_effect_list(ui->fixed_selected_TableView_2, &fixed_effect_list);
    prepare_effect(fixed_effect_input_Continuous);
    if(isTableView_empty(ui->fixed_selected_TableView_2))
    {
        //ui->fixed_accept_pushButton_2->setEnabled(false);
        qDebug()<<endl<<"selected tableview is empty"<<endl;
    }
    else
    {
        //ui->fixed_accept_pushButton_2->setEnabled(true);
        qDebug()<<endl<<"selected tableview is  no empty"<<endl;
    }
}

void MainWindow::on_fixed_accept_pushButton_2_clicked()
{
    Continuous_selected_fixed_flag = true;
    change_select_exclude_Button(0,Continuous_selected_fixed_flag,ui->fixed_select_Button_2,ui->fixed_exclude_Button_2);
    ui->fixed_accept_pushButton_2->setEnabled(false);
    prepare_effect(random_effect_input);//准备刷新随机效应

}

//----------------------------random effect part-------------------------------------------------------------------
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
        //ui->random_accept_pushButton->setEnabled(false);
        qDebug()<<endl<<"selected tableview is empty"<<endl;
    }
    else
    {
        //ui->random_accept_pushButton->setEnabled(true);
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
    prepare_effect(fixed_effect_input_Discrete);
}

void MainWindow::on_random_effec_testing_ComboBox_currentIndexChanged(int index)
{
    prepare_effect(random_effect_input);
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

    //bilud_H_matrix(Rdata_path,output_path, &H_matrix_path);
    blup_mode.blup_hblup_flag = blup_Hblup_flag;
    blup_mode.fiexd_effect_lineedit = ui->blup_fixed_lineEdit;
    blup_mode.random_effect_lineedit = ui->blup_random_lineEdit;

    blup_mode.BLUP_accept_pushButtom = ui->BLUP_accept_pushButtom;
    blup_mode.BLUP_mode_ComboBox = ui->BLUP_mode_ComboBox;
    blup_mode.trans_formula_1_lineEdit = ui->trans_formula_1_lineEdit;
    blup_mode.trans_formula_2_lineEdit = ui->trans_formula_2_lineEdit;
    blup_mode.classical_SE_textBrowser = ui->classical_SE_textBrowser;
    blup_mode.classical_varComp_tableView = ui->classical_varComp_tableView;
    blup_mode.classical_Estimate_textBrowser = ui->classical_Estimate_textBrowser;
    blup_mode.A_matrix_path = A_matrix_path;
    blup_mode.G_matrix_path = G_matrix_path;
    blup_mode.Rdata_path = Rdata_path;
    blup_mode.output_path = output_path;
    blup_mode.output_path.append("/GEBV.txt");
    classical_GEBV_path = blup_mode.output_path;

    blup_mode.blup_varcomp_path = output_path;
    blup_mode.blup_varcomp_path.append("/blup_varcomp.csv");
    blup_varcomp_path = blup_mode.blup_varcomp_path;

    blup_mode.blup_formula_ans_path = output_path;
    blup_mode.blup_formula_ans_path.append("/blup_formula_ans.csv");
    blup_formula_ans_path = blup_mode.blup_formula_ans_path;

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
    //Gender_path =  "/home/liang/Documents/AquaGS_GUI/Output/gender.txt";//
    blup_alphamate_all.GenderFile_lineEdit->setText(Gender_path);
    bayes_alphamate_all.GenderFile_lineEdit->setText(Gender_path);

    blup_Init(blup_mode);
    blup_fold_validate_Init(blup_fold_validate);
    blup_alphamate_Init(bayes_alphamate_all);
}

void MainWindow::on_trans_formula_1_lineEdit_returnPressed()
{
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

}

void MainWindow::on_GenderFile_checkBox_3_stateChanged(int arg1)
{
    if(arg1 == 2)
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
    param.append(csv_path);//1
    param.append(" ");
    param.append(output_path);//2
    param.append(" ");
    param.append(output_path+"/raw_output.raw");//3
    param.append(" ");
    param.append(ui->modelcomboBox->currentText());//4
    param.append(" ");
    param.append(ui->k_flod_ComboBox->currentText());//5
    param.append(" ");
    param.append(ui->iterationspinBox->text());//6
    param.append(" ");
    param.append(ui->dropoutspinBox->text());//7
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










