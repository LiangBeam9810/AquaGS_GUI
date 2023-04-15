#include "mainwindow.h"
#include <QDesktopServices>
MainWindow* m;
extern MainWindow* m;
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
QString executeLinuxCmd(QString strCmd)
{
    QProcess p;
    p.start("bash", QStringList() <<"-c" << strCmd);
    p.waitForFinished();
    QString strResult = p.readAllStandardOutput();
    return strResult;
}

bool Init_tool()
{
    QString param;
    QString runPath = QDir::currentPath();
    QString plink_Path = runPath+"/plink/plink";
    // The sequence of param is not changeable
    param.clear();
    param.append("chmod a+x");
    param.append(" ");
    param.append(plink_Path);
    qDebug()<<"Init_tool_process param :"<<param;
    executeLinuxCmd(param);

    QString Alphamate_Path = runPath+"/AlphaMateLinux/AlphaMate";
    // The sequence of param is not changeable
    param.clear();
    param.append("chmod a+x");
    param.append(" ");
    param.append(Alphamate_Path);
    qDebug()<<"Init_tool_process param :"<<param;
    executeLinuxCmd(param);

    return true;

}

void MainWindow::init()
{
    out_line = ui->output_lineEdit;
    csv_line = ui->csv_lineEdit;
    vcf_line = ui->vcf_lineEdit;
    Rpackage.clear();
    Rpackage<<"data.table"<<"bestNormalize"<<"ggplot2"<<"sommer"<<"lme4"<<"lmerTest"<<"nadiv"<<"ASRgenomics";
    Terminal_log = new Terminal_Dialog(this);
    data_view_page = new data_view_Dialog(this);
    connect(data_view_page, SIGNAL(sendData(QStringList,QStringList)), this, SLOT(receive_numeric_factor(QStringList,QStringList)));
    /*----------StratTAB init---------------------------------------*/

    csv_line->setText("Enter/Select the csv file.");
    vcf_line->setText("Enter/Select the vcf file.");
    out_line->setText("Select the output folder.");

    //csv_line->setText("/mnt/hgfs/Input/ABT20210617.csv");
    //vcf_line->setText("/mnt/hgfs/Input/snp_abt_630_imput_out_select48K.vcf");
    //out_line->setText("/mnt/hgfs/Output");

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

    /*----------tool init-----------------------------------------*/
    if(Init_tool())
    {
        sent_massage_to_terminal("plink and AlphaMate initted!");
    }
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
    get_select_path("(*.vcf *.gz)",this,vcf_line,2);
    return;
}

void MainWindow::on_output_pushButton_clicked()
{
    get_select_path(" ",this,out_line,0);
    return;
}

void MainWindow::on_start_next_pushButton_clicked()
{
    if(check_all_path(ui->output_lineEdit,ui->csv_lineEdit,ui->vcf_lineEdit,&output_path,&csv_path,&vcf_path,&plink_log_path))
    {
        check_all_package();
        start_complete_flag = true;
        phenotype_list =(get_csv_title(csv_path));//Reading  phenotypes.
        factor_phenotype_list.clear();
        numeric_phenotype_list.clear();
        data_view_page->Numeric_list.clear();
        data_view_page->factor_list.clear();
        data_view_page->setModal(false);
        data_view_page->clearMask();
        data_view_page->show();
        data_view_page->output_path = output_path;
        data_view_page->csv_path = csv_path;
        data_view_page->data_view_init(phenotype_list);
        ui->OutputFolder_commandLinkButton->setEnabled(true);
    }
    return ;
}
/*---------------------------------data_view--------------------------------------*/
void MainWindow::receive_numeric_factor(QStringList Numeric_list,QStringList factor_list)
{
    factor_phenotype_list = factor_list;
    numeric_phenotype_list = Numeric_list;
    qDebug()<<"factor_phenotype_list is "<<factor_phenotype_list;
    qDebug()<<"numeric_phenotype_list is "<<numeric_phenotype_list;
    data_view_page->close();
    ui->tabWidget->setEnabled(true);
    if((ui->tabWidget->currentIndex()) == 0)//如果在Start界面 则开启初始化Phenotype界面
    {
        Phenotype_Init();
        ui->tabWidget->setCurrentIndex(1);//To the next index.
    }
    
}

/*---------------------------------phenotype--------------------------------------*/
void MainWindow::Phenotype_Init()
{
    phenotype_select_line.AnimalID_ComboBox = ui->AnimalID_ComboBox;
    phenotype_select_line.Dam_ComboBox = ui->Dam_ComboBox;
    phenotype_select_line.Sire_ComboBox = ui->Sire_ComboBox;
    phenotype_select_line.target_phenotype_ComboBox = ui->phenotype_ComboBox;
    phenotype_select_line.outlier_CheckBox = ui->outlier_swith;
    phenotype_select_line.Gender_CheckBox = ui->Gender_CheckBox;
    phenotype_select_line.Gender_ComboBox = ui->Gender_ComboBox;

    phenotype_select_line.Gender_CheckBox->setCheckState(Qt::Unchecked);
    phenotype_select_line.outlier_CheckBox->setCheckState(Qt::Unchecked);
    ui->Blup_CheckBox->setCheckState(Qt::Unchecked);
    ui->convert_swith->setCheckState(Qt::Unchecked);
    ui->convert_swith->setEnabled(false);
    ui->horizontallabel_1->clear();
    ui->skewnessdisplay_1->clear();
    ui->kurtosisdisplay_1->clear();

    ui->horizontallabel_2->clear();
    ui->skewnessdisplay_2->clear();
    ui->kurtosisdisplay_2->clear();
    phenotype_select_line_init(phenotype_select_line,csv_path,&phenotype_list);
    ui->Gender_ComboBox->setEnabled(false);
    ui->Dam_ComboBox->setEnabled(false);
    ui->Sire_ComboBox->setEnabled(false);
    return;
}
void MainWindow::on_phenotype_ComboBox_currentIndexChanged(int index)
{

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
    ui->skewnessdisplay_2->clear();
    ui->kurtosisdisplay_2->clear();
    ui->horizontallabel_2->clear();
    return;
}

void MainWindow::on_phenotype_run_Button_clicked()
{
    unsigned int outlier_state = 0;
    check_all_path(ui->output_lineEdit,ui->csv_lineEdit,ui->vcf_lineEdit,&output_path,&csv_path,&vcf_path,&plink_log_path);//if clicked run buttun,the path need to be reload.
    init_ready_for_run_(ui->skewnessdisplay_1,
                        ui->kurtosisdisplay_1,
                        ui->horizontallabel_1,
                        ui->skewnessdisplay_2,
                        ui->kurtosisdisplay_2,
                        ui->horizontallabel_2,
                       ui->outlier_swith,
                        ui->phenotype_ComboBox,
                        ui->phenotype_accept_Button,
                        ui->convert_swith,
                       &outlier_state,&fist_convert_flag,&target_phenotype_index);
    phenotype_select_line_get_index(phenotype_select_line,&target_phenotype_index,&AnimalID_phenotype_index,&Dam_phenotype_index,&Sire_phenotype_index,
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
       int target_phenotype_index_new = phenotype_list.count();

       qDebug()<<endl<<"csv_path:" <<csv_path<<endl;
       qDebug()<<endl<<"csv_path_new:" <<csv_path_new<<endl;
       qDebug()<<endl<<"phenotype_list:"<<phenotype_list<<endl;
       qDebug()<<endl<<"lenth of phenotype_list: "<<phenotype_list.count()<<endl;
       qDebug()<<endl<<"index of new: "<<target_phenotype_index_new<<endl;
       if(fist_convert_flag)
       {
           qDebug()<<endl<<"fist convert!"<<endl;
           convert_phenotype(csv_path,target_phenotype_index,fist_convert_flag);
           display_normality(csv_path_new,output_path,unsigned(target_phenotype_index_new),"converted",
                             ui->skewnessdisplay_2,ui->kurtosisdisplay_2,ui->horizontallabel_2);
           fist_convert_flag = 0;
           ui->phenotype_accept_Button->setEnabled(true);
           ui->phenotype_detial_Button->setEnabled(true);
       }
       else{

           convert_phenotype(csv_path_new,unsigned(target_phenotype_index_new),fist_convert_flag);
           display_normality(csv_path_new,output_path,unsigned(target_phenotype_index_new),"converted",
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
    if(!(ui->convert_swith->isChecked()))
    {
        QMessageBox::warning(nullptr, "Error", "convert swith is uncheck.");
        return ;
    }
    csv_path.replace(".csv","_converted.csv");
    target_phenotype_index = unsigned(phenotype_list.count());
    phenotype_list =(get_csv_title(csv_path));//Reading  phenotypes.
    qDebug() << endl << "the final csv_path: "<<csv_path << endl <<"the final index: "<<target_phenotype_index<<endl;
    QMessageBox::information(nullptr, "OK", "Phnotype ready");
    change_convert_wight_state(0, ui->phenotype_convert_Button,ui->phenotype_reset_Button,ui->phenotype_accept_Button,ui->phenotype_detial_Button);
    ui->convert_swith->setEnabled(false);
    phenotype_converted_flag =true;
    phenotype_list =(get_csv_title(csv_path));//Reading  phenotypes.
    data_view_page->setModal(false);
    data_view_page->clearMask();
    data_view_page->show();
    data_view_page->output_path = output_path;
    data_view_page->csv_path = csv_path;
    data_view_page->data_view_init(phenotype_list);
    return;
}

void MainWindow::on_phenotype_next_pushButton_clicked()
{

     if(check_convert_path_of_phenotype(phenotype_converted_flag,ui->convert_swith))
     {

         if(blup_Hblup_flag == false)
         {
             QMessageBox::information(nullptr, "Notice ", "\"Dam\" and \"Sire\" is missing.\n Please select \"GBlup\" in the \"Classical method \"");
         }
         ui->tabWidget->setCurrentIndex(2);//显示下一页
    }
     else //没有点击accept按钮 确认正态转换后的数据
     {
          QMessageBox::warning(nullptr, "OK", "The converted switch was checked, but no converted phenotype was accepted!");
     }
     return;
}

void MainWindow::on_AnimalID_ComboBox_currentIndexChanged(int index)
{
    AnimalID_phenotype_index = unsigned(index);
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
void MainWindow::on_qc_running_pushButton_clicked()
{
    init_flode(output_path +"/plink_log/");//plink_log_path = *output_path +"/plink_log/" init the plink log flode
    QStringList files_name_of_qc_produce = {"raw_data.log","raw_data.raw","raw_data.nosex","imputated.log","imputated.vcf","vcf_after_qc.log","vcf_after_qc.vcf","vcf_after_qc.nosex"};
    init_file(output_path,files_name_of_qc_produce);


    QString phenotype = csv_path;
    QString genotype = vcf_path; // the key of pipleline
    QString out = output_path;

    this->runningFlag = true;
    ui->qc_next_pushButton->setDisabled(true);
    qApp->processEvents();
    QFuture<void> fu = QtConcurrent::run(QThreadPool::globalInstance(), [&]()
    {
        qDebug()<<endl<<"QC ready, the frist genotype path :"<<genotype;
        if (!this->callPlinkGwas(&genotype, out)) //running after
        {
            emit resetWindowSig();
            QThread::msleep(10);
            return;
        }
        qDebug()<< "After callPlinkGs"<<"genotype path :"<<genotype;
        vcf_QCed_path = genotype;//updata vcf_QCed_path after qc
   });
    while (!fu.isFinished())
    {
        qApp->processEvents(QEventLoop::AllEvents, 50);
        QThread::msleep(10);
    }

    qDebug()<<"After qc , the new genotype path is "<<genotype;

    if(ui->genofillcheckBox->isChecked())   //if checked genotype imputarion?
    {

        QString newvcf_name = "imputated"; //the name of vcf file after imputation
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
        param.append("gt="+genotype);
        param.append(" ");
        param.append("out="+output_path+"/"+newvcf_name);
        //param.append(" ");
        //param.append("ne=1120");
        param.append(" ");
        qDebug()<< endl<<"display param :"<<param<< endl;
        Process* validate_process;
        validate_process = new Process;
        if(!(validate_process->runRscript(param,"Genotype Imputation Running")))
        {
            QMessageBox::warning(nullptr, "Process error:", "Can't open the Genotype Filling process!");
            return;
        }

        QString param1 = "gunzip "+output_path+"/"+newvcf_name+".vcf.gz";
        QProcess display_process1;
        display_process1.execute(param1);
        genotype = output_path + "/" +newvcf_name + ".vcf"; // update the genotype to the path of vcf file after imputation
        qDebug()<<"After imputation , the new genotype path is "<<genotype;
    }
    else
    {
        genotype = vcf_QCed_path;
        qDebug()<<"Without imputation , the new genotype path is "<<genotype;
    }

    QFuture<void> conver_format = QtConcurrent::run(QThreadPool::globalInstance(), [&]()
    {
        qDebug()<<endl<<"Conver format ready, the genotype path :"<<genotype;
        if (!this->plink_convert_format(&genotype, out)) //running after
        {
            emit resetWindowSig();
            QThread::msleep(10);
            return;
        }
        qDebug()<< "After conver format, the genotype path :"<<genotype;
        raw_path = genotype;//updata raw_path after conver format
   });
    while (!conver_format.isFinished())
    {
        qApp->processEvents(QEventLoop::AllEvents, 50);
        QThread::msleep(10);
    }

    this->runningFlag = false;
    ui->qc_next_pushButton->setEnabled(true);
    if((isDirExist(plink_log_path)))
    {
        ui->qc_vie_wlog_pushButton->setEnabled(true);
        ui->qc_next_pushButton->setEnabled(true);
    }
    if(ui->genofillcheckBox->isChecked())
    {
        QMessageBox::information(nullptr, "Done ", "Gennotype Imputation and QC are completed");
    }
    else {
        QMessageBox::information(nullptr, "Done ", " QC complete");
    }
}

void MainWindow::on_qc_next_pushButton_clicked()
{

    if(!(A_G_matirx_build())){
            return ;
    }
    if(blup_Hblup_flag) {
        if(!(bilud_H_matrix(Rdata_path,output_path, &H_matrix_path))){
            return ;
        }
    }
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

void MainWindow::on_qc_vie_wlog_pushButton_clicked()
{
    if(!(isDirExist(plink_log_path)))
    {
        return;
    }
    else {
        QDesktopServices::openUrl(QUrl(plink_log_path));
    }
}


/*---------------------------------------------------------------------------------------*/

/*-------------------------------------- Effect -----------------------------------------*/
//Fixed effect part
void MainWindow::Effect_Init()
{
    //empty all list of effect testing
    fixed_effect_list.clear();
    Discrete_fixed_effect_list.clear();
    Continuous_fixed_effect_list.clear();
    random_effect_list.clear();

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
    fixed_effect_input_Discrete.Continuous_fixed_effect_list = &Continuous_fixed_effect_list;
    fixed_effect_input_Discrete.random_effect_list = &random_effect_list;
    fixed_effect_input_Discrete.factor_list=factor_phenotype_list;
    fixed_effect_input_Discrete.numeric_list = numeric_phenotype_list;
    fixed_effect_input_Discrete.original_label = ui->fixed_phenotype_pr_label;
    fixed_effect_input_Discrete.selected_label = ui->fixed_selected_label;
    fixed_effect_input_Discrete.target_effect_name = phenotype_list[int(target_phenotype_index)];
    fixed_effect_input_Discrete.AnimalID_name = phenotype_list[int(AnimalID_phenotype_index)];
    qDebug()<<"fixed_effect_input_Discrete.target_effect_name"<<fixed_effect_input_Discrete.target_effect_name;

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
    fixed_effect_input_Continuous.Continuous_fixed_effect_list = &Continuous_fixed_effect_list;
    fixed_effect_input_Continuous.random_effect_list = &random_effect_list;
    fixed_effect_input_Continuous.factor_list=factor_phenotype_list;
    fixed_effect_input_Continuous.numeric_list = numeric_phenotype_list;
    fixed_effect_input_Continuous.original_label = ui->fixed_phenotype_pr_label_2;
    fixed_effect_input_Continuous.selected_label = ui->fixed_selected_label_2;
    fixed_effect_input_Continuous.target_effect_name = phenotype_list[target_phenotype_index];
    fixed_effect_input_Continuous.AnimalID_name = phenotype_list[AnimalID_phenotype_index];

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
    random_effect_input.factor_list=factor_phenotype_list;
    random_effect_input.numeric_list = numeric_phenotype_list;
    random_effect_input.original_label = ui->random_phenotype_pr_label;
    random_effect_input.selected_label = ui->random_selected_label;
    random_effect_input.target_effect_name = phenotype_list[target_phenotype_index];
    random_effect_input.AnimalID_name = phenotype_list[AnimalID_phenotype_index];

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
    ui->fixed_accept_pushButton_2->setEnabled(false);
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
    QStringList file_list = {"Discrete_fixed_effect_dis.csv"};
    init_file(output_path,file_list);
    add_item2effect_list(ui->fixed_phenotype_pr_TableView,
                         phenotype_list,&fixed_effect_list);
    prepare_effect(fixed_effect_input_Discrete);
    //ui->fixed_accept_pushButton->setEnabled(true);
    qDebug()<<endl<<"Discrete_fixed_effect_list  is "<<fixed_effect_list<<endl;
}

void MainWindow::on_fixed_exclude_Button_clicked()
{
    QStringList file_list = {"Discrete_fixed_effect_dis.csv"};
    init_file(output_path,file_list);
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
    qDebug()<<endl<<"Discrete fixed effect was accepted ,Discrete_fixed_effect_list: "<<Discrete_fixed_effect_list;
    prepare_effect(fixed_effect_input_Continuous);//准备刷新连续型固定效应
    ui->random_accept_pushButton->setEnabled(false);
    ui->random_exclude_Button->setEnabled(false);
    ui->random_select_Button->setEnabled(false);
    ui->fixed_accept_pushButton->setEnabled(false);
    ui->fixed_exclude_Button->setEnabled(false);
    ui->fixed_select_Button->setEnabled(false);
    ui->fixed_accept_pushButton_2->setEnabled(true);
    ui->fixed_exclude_Button_2->setEnabled(false);
    ui->fixed_select_Button_2->setEnabled(false);
}

void MainWindow::on_fixed_phenotype_pr_TableView_2_clicked(const QModelIndex &index)
{
    qDebug()<<endl<<"Continuous_fixed_tableview_clicked:" <<index<<endl;
    change_select_exclude_Button(1,Continuous_selected_fixed_flag,ui->fixed_select_Button_2,ui->fixed_exclude_Button_2);
    return;
}
/****************************
* 点击了continuce型已选框（右侧）
*****************************/
void MainWindow::on_fixed_selected_TableView_2_clicked(const QModelIndex &index)
{
    qDebug()<<endl<<"Continuous_fixed_tableview_clicked:" <<index<<endl;
    change_select_exclude_Button(0,Continuous_selected_fixed_flag,ui->fixed_select_Button_2,ui->fixed_exclude_Button_2);
    return;
}

void MainWindow::on_fixed_select_Button_2_clicked()
{
    QStringList file_list = {"Continuous_fixed_effect_dis.csv"};
    init_file(output_path,file_list);
    add_item2effect_list(ui->fixed_phenotype_pr_TableView_2,phenotype_list,&fixed_effect_list);
    qDebug()<<endl<<"Continuous_fixed_effect_list  is "<<fixed_effect_list<<endl;
    prepare_effect(fixed_effect_input_Continuous);
    //ui->fixed_accept_pushButton_2->setEnabled(true);
}

void MainWindow::on_fixed_exclude_Button_2_clicked()
{
    QStringList file_list = {"Continuous_fixed_effect_dis.csv"};
    init_file(output_path,file_list);
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
    ui->random_accept_pushButton->setEnabled(true);
    ui->random_exclude_Button->setEnabled(false);
    ui->random_select_Button->setEnabled(false);
    ui->fixed_accept_pushButton->setEnabled(false);
    ui->fixed_exclude_Button->setEnabled(false);
    ui->fixed_select_Button->setEnabled(false);
    ui->fixed_accept_pushButton_2->setEnabled(false);
    ui->fixed_exclude_Button_2->setEnabled(false);
    ui->fixed_select_Button_2->setEnabled(false);

}

//----------------------------random effect part-------------------------------------------------------------------
void MainWindow::on_random_phenotype_pr_TableView_clicked(const QModelIndex &index)
{
    change_select_exclude_Button(1,selected_random_flag,ui->random_select_Button,ui->random_exclude_Button);
    qDebug()<< "random_phenotype index:" << index ;
    return;
}
void MainWindow::on_random_selected_TableView_clicked(const QModelIndex &index)
{
    change_select_exclude_Button(0,selected_random_flag,ui->random_select_Button,ui->random_exclude_Button);
    return;
}
void MainWindow::on_random_select_Button_clicked()
{
    QStringList file_list = {"random_effect.csv"};
    init_file(output_path,file_list);
    if(random_effect_list.count()&&(!ui->random_effec_testing_ComboBox->currentIndex()))//ui->random_effec_testing_ComboBox->currentIndex()=0 is use
                                                                                        //lemer to test random effect
    {
        QMessageBox::warning(nullptr, "Error ","The maxium  of random effect testing \n named  \"lmer\" is 1." );
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
    QStringList file_list = {"random_effect.csv"};
    init_file(output_path,file_list);
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
    QStringList file_list = {"Discrete_fixed_effect_dis.csv","Continuous_fixed_effect_dis.csv","random_effect.csv"};
    init_file(output_path,file_list);
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

    if(ui->fixed_accept_pushButton->isEnabled()&&ui->fixed_accept_pushButton_2->isEnabled()&&ui->random_accept_pushButton->isEnabled())
    {
       QMessageBox::warning(nullptr, "Error ","pleas accept this effect." );
       return ;
    }
    else
    {
        classical_method_Init();
        ui->tabWidget->setCurrentIndex(4);
        return ;
    }
}

/*----------------------------------------------------------------------------------------*/
/*---------------------------------class_method-------------------------------------------*/
void MainWindow::classical_method_Init()
{

    //bilud_H_matrix(Rdata_path,output_path, &H_matrix_path);
    blup_mode.blup_hblup_flag = blup_Hblup_flag;
    blup_mode.model_display_label = ui->model_display_label;
    blup_mode.phenotype_list = phenotype_list;
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
    blup_mode.output_path.append("/blups_GEBV.txt");
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
    blup_fold_validate.ACC_STD_lineEdit = ui->class_val_std_lineEdit;
    blup_fold_validate.Bias_lineEdit = ui->class_val_bias_lineEdit;
    blup_fold_validate.Bias_STD_lineEdit = ui->class_val_std_lineEdit_2;
    blup_fold_validate.cross_validation_checkBox = ui->cross_validation_checkBox;
    blup_fold_validate.k_flod_times_ComboBox = ui->k_flod_times_ComboBox;
    blup_fold_validate.k_flod_rep_SpinBox = ui->k_flod_rep_spinBox;
    blup_fold_validate.fixed_effect_list = fixed_effect_list;
    blup_fold_validate.fixed_effect_input_Discrete = Discrete_fixed_effect_list;
    blup_fold_validate.random_effect_list = random_effect_list;
    blup_fold_validate.cross_validation_pushbutton = ui->classical_validate_pushButtom;



    blup_Init(blup_mode);
    blup_fold_validate_Init(blup_fold_validate);

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
    QStringList file_list = {"blup_formula_ans.csv","blup_varcomp.csv","blups_GEBV.txt"};
    init_file(output_path,file_list);
    blup_build(blup_mode);
}

void MainWindow::on_cross_validation_checkBox_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        blup_fold_validate.k_flod_times_ComboBox->setEnabled(true);
        blup_fold_validate.cross_validation_pushbutton->setEnabled(true);
        blup_fold_validate.k_flod_rep_SpinBox->setEnabled(true);
        blup_fold_validate.ACC_lineEdit->setEnabled(true);
        blup_fold_validate.ACC_STD_lineEdit->setEnabled(true);
        blup_fold_validate.Bias_lineEdit->setEnabled(true);
        blup_fold_validate.Bias_STD_lineEdit ->setEnabled(true);
    }
    else {
        blup_fold_validate.k_flod_times_ComboBox->setEnabled(false);
        blup_fold_validate.cross_validation_pushbutton->setEnabled(false);
        blup_fold_validate.k_flod_rep_SpinBox->setEnabled(false);
        blup_fold_validate.ACC_lineEdit->setEnabled(false);
        blup_fold_validate.ACC_STD_lineEdit->setEnabled(false);
        blup_fold_validate.Bias_lineEdit->setEnabled(false);
        blup_fold_validate.Bias_STD_lineEdit ->setEnabled(false);
    }
}
/*----------------------------------------------------------------------------------------*/
/*--------------------------------------AlphaMate-----------------------------------------*/
void MainWindow::Alphamate_Init()
{
    alphamate_all.classical_more_Button = ui->classical_more_Button;
    alphamate_all.classical_mate_Button = ui->classical_mate_Button_3;
    alphamate_all.TargetDegree_spinBox = ui-> TargetDegree_spinBox_3;
    alphamate_all.TargetCoancestryRate_doubleSpinBox = ui->TargetCoancestryRate_doubleSpinBox_3;
    alphamate_all.SelCriterionFile_lineEdit = ui->SelCriterionFile_lineEdit_3 ;
    alphamate_all.NumberOfMatings_spinBox = ui->NumberOfMatings_spinBox_3;
    alphamate_all.NumberOfMaleParents_spinBox = ui->NumberOfMaleParents_spinBox_3;
    alphamate_all.NumberOfFemaleParents_spinBox = ui -> NumberOfFemaleParents_spinBox_3;
    alphamate_all.NrmMatrix_lineEdit = ui->NrmMatrix_lineEdit_3;
    alphamate_all.ModeOpt_checkBox = ui->ModeOpt_checkBox_3;
    alphamate_all.ModeMinInbreeding_checkBox= ui->ModeMinInbreeding_checkBox_3;
    alphamate_all.ModeMinCoancestry_checkBox= ui->ModeMinCoancestry_checkBox_3;
    alphamate_all.ModeMaxCriterion_checkBox = ui->ModeMaxCriterion_checkBox_3;
    alphamate_all.GenderFile_lineEdit = ui->GenderFile_lineEdit_3;
    alphamate_all.EvaluateFrontier_checkBox = ui->EvaluateFrontier_checkBox_3;
    alphamate_all.EqualizeMaleContributions_checkBox = ui->EqualizeMaleContributions_checkBox_3;
    alphamate_all.EqualizeFemaleContributions_checkBox = ui->EqualizeFemaleContributions_checkBox_3;
    alphamate_all.GenderFile_CheckBox = ui->GenderFile_checkBox_3;
    alphamate_all.NrmMatrixFileform_comboBox = ui->NrmMatrixFileform_comboBox;
    alphamate_all.GEBVform_comboBox = ui->GEBVform_comboBox;
    alphamate_all.NumberOfMatingCandidate_spinBox = ui->NumberOfMatingCandidate_spinBox;


    QString runPath = QDir::currentPath();
    Alphamate_running_path =  runPath;
    Alphamate_running_path.append("/AlphaMateLinux");
    alphmate_enable_all(alphamate_all);//初始化

    if(blup_mode.BLUP_mode_ComboBox->currentIndex()==1)
    {
        alphamate_all.NrmMatrix_lineEdit->setText(G_matrix_path);
        ui->NrmMatrixFileform_comboBox->setCurrentIndex(1);
        qDebug()<<"GBLUP  NrmMatrix PATH : "<<G_matrix_path;
    }else if((blup_mode.BLUP_mode_ComboBox->currentIndex()==2))
    {
        alphamate_all.NrmMatrix_lineEdit->setText(H_matrix_path);
        ui->NrmMatrixFileform_comboBox->setCurrentIndex(2);
        qDebug()<<"HBLUP  NrmMatrix PATH : "<<H_matrix_path;
    }
    else{
        alphamate_all.NrmMatrix_lineEdit->setText(A_matrix_path);
        ui->NrmMatrixFileform_comboBox->setCurrentIndex(0);
        qDebug()<<"BLUP  NrmMatrix PATH : "<<A_matrix_path;
    }
    alphamate_all.SelCriterionFile_lineEdit->setText(classical_GEBV_path);
    qDebug()<<"SelCriterionFile PATH : "<<classical_GEBV_path;
    alphamate_all.GenderFile_lineEdit->setText(Gender_path);

    alphamate_page_Init(alphamate_all);
}
void MainWindow::on_classical_validate_pushButtom_clicked()
{
    QStringList file_list = {"blup_formula_ans.csv","blup_varcomp.csv"};
    init_file(output_path,file_list);

    if(classical_method_cross_validation_and_display(blup_mode,blup_fold_validate))
    {
        qDebug()<<"cross validation complete!";
    }
}
void MainWindow::on_alphmate_checkBox_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        alphmate_enable_all(alphamate_all);
    }else{
        alphmate_disable_all(alphamate_all);
    }
}

void MainWindow::on_classical_more_Button_triggered(QAction *arg1)
{

}

void MainWindow::on_GenderFile_checkBox_3_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        alphmate_able_gender(alphamate_all,true);
    }else
    {
        alphmate_able_gender(alphamate_all,false);
    }
}

void MainWindow::on_classical_mate_Button_3_clicked()
{
     running_alphamate(alphamate_all,Alphamate_running_path,output_path);
}



/*----------------------------------------------------------------------------------------*/
/*---------------------------------bayes_method-------------------------------------------*/



void MainWindow::on_bayesrunpushButton_clicked()
{

    QString runPath = QDir::currentPath();
    QString bayes_GEBV_path_bf = output_path+"/bayes_GEBV.txt";// the outfile of bayes
    QString bayes_output_path = output_path+"/bayes_output.txt";// the outfile of bayes
    QString bayes_output_path_running = output_path+"/R/";// the outfile of bayes
    QStringList bayes_file_list ={bayes_output_path,bayes_GEBV_path_bf};
    qDebug() <<"bayes_output_path_running:" << bayes_output_path_running << endl;
    init_flode(bayes_output_path_running);//bayes_output_path_running
    init_file(output_path,bayes_file_list);
    //QStringList files_name_of_qc_produce = {,};
    //init_file(output_path,files_name_of_qc_produce);

    runPath.append("/rscript/bayes1.R");
    qDebug() << endl <<"runPath:" << runPath << endl;
    QString param;
    // The sequence of param is not changeable
    param.clear();
    param.append("Rscript");
    param.append(" ");
    param.append(runPath);
    param.append(" ");
    param.append(Rdata_path);//1
    param.append(" ");
    param.append(bayes_GEBV_path_bf);//2
    param.append(" ");
    param.append(bayes_output_path);//3 set output to R running path
    param.append(" ");
    param.append(QString::number(AnimalID_phenotype_index));
    param.append(" ");
    param.append(QString::number(target_phenotype_index));
    param.append(" ");
    param.append(ui->bayes_model_comboBox->currentText());//bayes model
    param.append(" ");
    param.append(ui->bayes_k_flod_rep_spinBox->text());//
    param.append(" ");
    param.append(ui->bayes_k_flod_ComboBox->currentText());//flod times
    param.append(" ");
    param.append(ui->bayes_iteration_spinBox->text());//nIter
    param.append(" ");
    param.append(ui->bayes_butnIn_spinBox->text());//butnIn
    param.append(" ");
    param.append(QString::number(fixed_effect_list.length()));
    for(int i = 0;i < fixed_effect_list.length();i++){
        param.append(" ");
        param.append(fixed_effect_list[i]);
    }
    for(int i = 0;i < fixed_effect_list.length();i++){
        if((!(-1 == factor_phenotype_list.indexOf(fixed_effect_list[i]))))  // if the effect in the factor_phenotype_list already,
                                                                            //so fixed_effect_list[i] is a factor fixed phenotype
        {
            param.append(" ");
            param.append("1");
            qDebug()<<fixed_effect_list[i]<<"is the factor fixed effect";
        }
        else {
            param.append(" ");
            param.append("0");
            qDebug()<<fixed_effect_list[i]<<"is the number fixed effect";
        }

    }
    param.append(" ");
    param.append(bayes_output_path_running);
    qDebug()<< endl<<"display param :"<<param<< endl;

    Process* bayes_process;
    bayes_process = new Process;
    if(!(bayes_process->runRscript(param,"Running bayes")))
    {
        QMessageBox::warning(nullptr, "Process error:", "Can't open the rdata init process!");
        return;
    }

    QFile f(bayes_output_path);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the :"<<bayes_output_path<<" !"<<endl;
        QMessageBox::warning(nullptr, "Process error:", "Can't open the :"+bayes_output_path+" !");
        return;
    }
    else {
        QTextStream txtInput(&f);
        QStringList bayesoutput;
        QString lineStr;
        while(!txtInput.atEnd())
        {
            lineStr = txtInput.readLine();
            if(lineStr.length()>8){
                lineStr = lineStr.mid(0,7);
            }
              bayesoutput.append(lineStr);
            qDebug() << lineStr << endl;
        }
         ui->accuracytextBrowser->clear();
        ui->accuracytext_sd_Browser->clear();
        ui->herittextBrowser->clear();
        ui->herittext_sd_Browser->clear();
        ui->varcomp1textBrowser->clear();
        ui->varcomp1text_sd_Browser->clear();
        ui->varcomp2textBrowser->clear();
        ui->varcomp2text_sd_Browser->clear();
        f.close();
        if(bayesoutput.length()>7)
        {
            ui->accuracytextBrowser->insertPlainText(bayesoutput[0]);
            ui->accuracytext_sd_Browser->insertPlainText(bayesoutput[1]);
            ui->herittextBrowser->insertPlainText(bayesoutput[2]);
            ui->herittext_sd_Browser->insertPlainText(bayesoutput[3]);
            ui->varcomp1textBrowser->insertPlainText(bayesoutput[4]);
            ui->varcomp1text_sd_Browser->insertPlainText(bayesoutput[5]);
            ui->varcomp2textBrowser->insertPlainText(bayesoutput[6]);
            ui->varcomp2text_sd_Browser->insertPlainText(bayesoutput[6]);
        }
        else {

            ui->accuracytextBrowser->insertPlainText("NA");
            ui->accuracytext_sd_Browser->insertPlainText("NA");
            ui->herittextBrowser->insertPlainText("NA");
            ui->herittext_sd_Browser->insertPlainText("NA");
            ui->varcomp1textBrowser->insertPlainText("NA");
            ui->varcomp1text_sd_Browser->insertPlainText("NA");
            ui->varcomp2textBrowser->insertPlainText("NA");
            ui->varcomp2text_sd_Browser->insertPlainText("NA");
        }
        ui->accuracytextBrowser->setEnabled(true);
        ui->accuracytext_sd_Browser->setEnabled(true);
        ui->herittextBrowser->setEnabled(true);
        ui->herittext_sd_Browser->setEnabled(true);
        ui->varcomp1textBrowser->setEnabled(true);
        ui->varcomp1text_sd_Browser->setEnabled(true);
        ui->varcomp2textBrowser->setEnabled(true);
        ui->varcomp2text_sd_Browser->setEnabled(true);

    }
    if(isFileExist(bayes_GEBV_path_bf)) bayes_GEBV_path = bayes_GEBV_path_bf;
    else {
        qDebug()<<"Can't find the :"<<bayes_GEBV_path_bf<<" !"<<endl;
        QMessageBox::warning(nullptr, "Process error:", "Can't find the :"+bayes_GEBV_path_bf+" !");
        return;
    }
}



//点击底部终端输出按钮
void MainWindow::on_toolButton_clicked()
{
    Terminal_log->setModal(false);
    Terminal_log->clearMask();
    Terminal_log->show();
}
//槽函数 将文本打印到终端输出界面
void MainWindow::sent_massage_to_terminal(QString massage)
{
    Terminal_log->append_Terminal_textBrowser(massage);
}

void MainWindow::on_BLUP_next_pushButton_clicked()
{
    Alphamate_Init();
    alphamate_all.SelCriterionFile_lineEdit->setText(classical_GEBV_path);
    ui->GEBVform_comboBox->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(6);

}

void MainWindow::on_Bayes_next_pushButton_clicked()
{
    Alphamate_Init();
    alphamate_all.SelCriterionFile_lineEdit->setText(bayes_GEBV_path);
    ui->GEBVform_comboBox->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(6);
}


void MainWindow::on_bayes_GEBVform_comboBox_currentIndexChanged(int index)
{
    if(index == 1)//bayes
    {
        Alphamate_Init();
        alphamate_all.SelCriterionFile_lineEdit->setText(bayes_GEBV_path);
        ui->GEBVform_comboBox->setCurrentIndex(1); //select GEBVfile form bayes
        ui->tabWidget->setCurrentIndex(6);
    }
    else if (index == 0) {
        Alphamate_Init();
        alphamate_all.SelCriterionFile_lineEdit->setText(classical_GEBV_path);
        ui->GEBVform_comboBox->setCurrentIndex(0);//select GEBVfile form blup
        ui->tabWidget->setCurrentIndex(6);
    }
}

void MainWindow::on_NrmMatrixFileform_comboBox_currentIndexChanged(int index)
{
    qDebug()<<endl<<"NrmMatrix PATH changing! index =  "<<index;
    if(index==1)
    {
        alphamate_all.NrmMatrix_lineEdit->setText(G_matrix_path);
        qDebug()<<"GBLUP  NrmMatrix PATH : "<<G_matrix_path;
    }else if(index==2)
    {
        alphamate_all.NrmMatrix_lineEdit->setText(H_matrix_path);
        qDebug()<<"HBLUP  NrmMatrix PATH : "<<H_matrix_path;
    }
    else{//index==0
        alphamate_all.NrmMatrix_lineEdit->setText(A_matrix_path);
        qDebug()<<"BLUP  NrmMatrix PATH : "<<A_matrix_path;
    }
}

void MainWindow::on_GEBVform_comboBox_currentIndexChanged(int index)
{
    if(index == 1)//bayes
    {
        alphamate_all.SelCriterionFile_lineEdit->setText(bayes_GEBV_path);
        ui->GEBVform_comboBox->setCurrentIndex(1); //select GEBVfile form bayes
        ui->tabWidget->setCurrentIndex(6);
    }
    else if (index == 0) {
        alphamate_all.SelCriterionFile_lineEdit->setText(classical_GEBV_path);
        ui->GEBVform_comboBox->setCurrentIndex(0);//select GEBVfile form blup
        ui->tabWidget->setCurrentIndex(6);
    }
}

void MainWindow::on_OutputFolder_commandLinkButton_clicked()
{
    if(!(isDirExist(output_path)))
    {
        return;
    }
    else {
        QDesktopServices::openUrl(QUrl(output_path));
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch (index) {
    case 0:
        break;;
    case 1:
        break;;
    case 2:
        break;;
    case 3:
        break;;
    case 4:
        break;;
    case 5:
        break;;
    case 6:
        alphamate_all.classical_more_Button = ui->classical_more_Button;
        alphamate_all.classical_mate_Button = ui->classical_mate_Button_3;
        alphamate_all.TargetDegree_spinBox = ui-> TargetDegree_spinBox_3;
        alphamate_all.TargetCoancestryRate_doubleSpinBox = ui->TargetCoancestryRate_doubleSpinBox_3;
        alphamate_all.SelCriterionFile_lineEdit = ui->SelCriterionFile_lineEdit_3 ;
        alphamate_all.NumberOfMatings_spinBox = ui->NumberOfMatings_spinBox_3;
        alphamate_all.NumberOfMaleParents_spinBox = ui->NumberOfMaleParents_spinBox_3;
        alphamate_all.NumberOfFemaleParents_spinBox = ui -> NumberOfFemaleParents_spinBox_3;
        alphamate_all.NrmMatrix_lineEdit = ui->NrmMatrix_lineEdit_3;
        alphamate_all.ModeOpt_checkBox = ui->ModeOpt_checkBox_3;
        alphamate_all.ModeMinInbreeding_checkBox= ui->ModeMinInbreeding_checkBox_3;
        alphamate_all.ModeMinCoancestry_checkBox= ui->ModeMinCoancestry_checkBox_3;
        alphamate_all.ModeMaxCriterion_checkBox = ui->ModeMaxCriterion_checkBox_3;
        alphamate_all.GenderFile_lineEdit = ui->GenderFile_lineEdit_3;
        alphamate_all.EvaluateFrontier_checkBox = ui->EvaluateFrontier_checkBox_3;
        alphamate_all.EqualizeMaleContributions_checkBox = ui->EqualizeMaleContributions_checkBox_3;
        alphamate_all.EqualizeFemaleContributions_checkBox = ui->EqualizeFemaleContributions_checkBox_3;
        alphamate_all.GenderFile_CheckBox = ui->GenderFile_checkBox_3;
        alphamate_all.NrmMatrixFileform_comboBox = ui->NrmMatrixFileform_comboBox;
        alphamate_all.GEBVform_comboBox = ui->GEBVform_comboBox;
        break;
    default :break;
    }
}



void MainWindow::on_genofillcheckBox_stateChanged(int arg1)
{

}
