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
    csv_line->setText("/home/liang/Documents/AquaGS_GUI/Input/ABT20210617.csv");
    vcf_line->setText("/home/liang/Documents/AquaGS_GUI (copy)/Input/snp_abt_630_imput_out_select48K.vcf");
    out_line->setText("/home/liang/Documents/AquaGS_GUI/Output");
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
    Effect_Init();

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
    if(check_all_path(ui->output_lineEdit,ui->csv_lineEdit,ui->vcf_lineEdit,&output_path,&csv_path,&vcf_path)){
            prepare_phenotype(csv_path,&phenotype_list,ui->phenotype_ComboBox);
            ui->tabWidget->setCurrentIndex(1);//To the next index.
        }
    return ;
}

/*---------------------------------phenotype--------------------------------------*/
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
    if(outlier_elimination(&csv_path,outlier_state,target_phenotype_index))
    {
        qDebug()<<endl<<"outlier completed!"<<endl;
        qDebug()<<endl<<"csv path:"<<csv_path<<endl;
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

}
/*---------------------------------------------------------------------------------------*/

/*-------------------------------------- Effect -----------------------------------------*/
//Fixed effect part
void MainWindow::Effect_Init()
{

    /*-------------------------------------------*/
    A_matrix_path = output_path+"/A_matrix.txt";
    G_matrix_path = output_path+"/G_matrix.txt";
    qDebug()<<endl<<"A_matrix_path"<<A_matrix_path;
    qDebug()<<"G_matrix_path"<<G_matrix_path<<endl;
    /*-------------------------------------------*/
    fixed_effect_input.input_path = csv_path;
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

    random_effect_input.input_path = csv_path;
    random_effect_input.output_path = output_path;
    random_effect_input.A_matrix_path = A_matrix_path;
    random_effect_input.G_matrix_path = G_matrix_path;
    random_effect_input.original_tableview = ui->random_phenotype_pr_TableView;
    random_effect_input.selected_tableview = ui->random_selected_TableView;
    random_effect_input.animal_combobox = ui->AnimalID_ComboBox;
    random_effect_input.randeff_testing_combobox = ui->random_effec_testing_ComboBox;
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

void MainWindow::on_effect_next_pushButton_clicked()
{
    AnimalID_phenotype_index = ui->AnimalID_ComboBox->currentIndex();

}

/*----------------------------------------------------------------------------------------*/
/*---------------------------------class_method-------------------------------------------*/
void MainWindow::classical_method_Init()
{
    blup_mode.fiexd_effect_listView = ui ->fiexd_effect_listView;
    blup_mode.random_effect_listView = ui->random_effect_listView;
    blup_mode.BLUP_accept_pushButtom = ui->BLUP_accept_pushButtom;
    blup_mode.BLUP_mode_ComboBox = ui->BLUP_mode_ComboBox;
    blup_mode.trans_formula_1_ComboBox = ui->trans_formula_1_ComboBox;
    blup_mode.trans_formula_2_ComboBox = ui->trans_formula_2_ComboBox;
    blup_mode.Matrix_path = "";
    blup_mode.csv_path = csv_path;
    blup_mode.output_path = output_path;
    blup_mode.fixed_effect_list = fixed_effect_list;
    blup_mode.random_effect_list = random_effect_list;

    blup_fold_validate.accuracyA_textBrowser = ui->accuracyA_textBrowser;
    blup_fold_validate.accuracyG_textBrowser = ui->accuracyG_textBrowser;
    blup_fold_validate.cross_validation_checkBox = ui->cross_validation_checkBox;
    blup_fold_validate.k_flod_times_ComboBox = ui->k_flod_times_ComboBox;
    blup_fold_validate.Matrix_path = "";
    blup_fold_validate.csv_path = csv_path;
    blup_fold_validate.fixed_effect_list = fixed_effect_list;
    blup_fold_validate.random_effect_list = random_effect_list;
}









/*----------------------------------------------------------------------------------------*/


