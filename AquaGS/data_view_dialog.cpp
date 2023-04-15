#include "data_view_dialog.h"
#include "ui_data_view_dialog.h"
#include "start.h"
data_view_Dialog::data_view_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::data_view_Dialog)
{
    ui->setupUi(this);
}

data_view_Dialog::~data_view_Dialog()
{
    delete ui;
}

void data_view_Dialog::data_view_clear()
{
    QStandardItemModel* model = new QStandardItemModel();
    model->clear();
    data_view_Dialog::factor_tableview->setModel(model);
    data_view_Dialog::Numeric_tableview->setModel(model);
    data_view_Dialog::original_tableview->setModel(model);
}

void data_view_Dialog::data_view_refresh(QStringList Phenotype_list )
{
    QStandardItemModel* original_model = new QStandardItemModel();
    QStandardItemModel* factor_selected_model = new QStandardItemModel();
    QStandardItemModel* Numeric_selected_model = new QStandardItemModel();

    original_model->setHorizontalHeaderLabels({"Constraint Phenotype"});
    factor_selected_model->setHorizontalHeaderLabels({"Factor"});
    Numeric_selected_model->setHorizontalHeaderLabels({"Numeric"});

    data_view_Dialog::original_tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    data_view_Dialog::factor_tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    data_view_Dialog::Numeric_tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    unsigned count = 0;
    int i =0;//original 左侧为选择的计数
    int j =0;//factor 右侧已经选择的计数
    int k =0;//numeric 右侧已经选择的计数
    Q_FOREACH(QString str, Phenotype_list)
    {
        if((!(-1 ==  data_view_Dialog::factor_list.indexOf(QString::number(count))))){//if str in factor_list
            qDebug()<<endl<<"find the "<< str <<" in the factor_list already,index is "<<Phenotype_list.indexOf(str)<<endl;
            factor_selected_model->setItem(j, 0, new QStandardItem(str));
            j++;
        }
        else if ((!(-1 ==  data_view_Dialog::Numeric_list.indexOf(QString::number(count))))) {//if str in Numeric_list
            qDebug()<<endl<<"find the "<< str <<"in the Numeric_list already,index is "<<Phenotype_list.indexOf(str)<<endl;
            Numeric_selected_model->setItem(k, 0, new QStandardItem(str));
            k++;
        }
        else {//str still in original_tableview
            original_model->setItem(i, 0, new QStandardItem(str));
            i++;
        }
        count++;
    }

    data_view_Dialog::original_tableview->setModel(original_model);
    data_view_Dialog::factor_tableview->setModel(factor_selected_model);
    data_view_Dialog::Numeric_tableview->setModel(Numeric_selected_model);

    data_view_Dialog::original_tableview->show();
    data_view_Dialog::factor_tableview->show();
    data_view_Dialog::Numeric_tableview->show();
    data_view_Dialog::original_tableview->setCurrentIndex(original_model->index(0,0));//select the first row in original tableview
}


void data_view_Dialog::data_view_init(QStringList Phenotype_list)
{
    original_tableview = data_view_Dialog::ui->data_view_original_TableView;
    factor_tableview = data_view_Dialog::ui->data_view_factor_TableView;
    Numeric_tableview = data_view_Dialog::ui->data_view_numeric_TableView;
    view_data_button = data_view_Dialog::ui->view_data_pushButton;
    factor_select_button = data_view_Dialog::ui->select_to_factor_pushButton;
    factor_disselect_button = data_view_Dialog::ui->disselect_to_factor_pushButton;
    Numeric_select_button = data_view_Dialog::ui->select_to_num_pushButton;
    Numeric_disselect_button = data_view_Dialog::ui->disselect_to_num_pushButton;
    finish_button = data_view_Dialog::ui->data_view_done_pushButton;

    //factor_select_button->setDisabled(true);
    factor_disselect_button->setDisabled(true);
    //Numeric_select_button->setDisabled(true);
    Numeric_disselect_button->setDisabled(true);
    data_view_Dialog::Phenotype_list = Phenotype_list;
    data_view_refresh(data_view_Dialog::Phenotype_list);
}

void data_view_Dialog::on_data_view_original_TableView_clicked(const QModelIndex &index)
{
    factor_select_button->setEnabled(true);
    Numeric_select_button->setEnabled(true);
    factor_disselect_button->setDisabled(true);
    Numeric_disselect_button->setDisabled(true);
}

void data_view_Dialog::on_data_view_numeric_TableView_clicked(const QModelIndex &index)
{
    factor_select_button->setDisabled(true);
    Numeric_select_button->setDisabled(true);
    factor_disselect_button->setDisabled(true);
    Numeric_disselect_button->setEnabled(true);
}

void data_view_Dialog::on_data_view_factor_TableView_clicked(const QModelIndex &index)
{
    factor_select_button->setDisabled(true);
    Numeric_select_button->setDisabled(true);
    factor_disselect_button->setEnabled(true);
    Numeric_disselect_button->setDisabled(true);
}

void data_view_Dialog::data_view_add2list(bool factor_or_not,QStringList Phenotype_list)
{
    int selected_row = data_view_Dialog::original_tableview->currentIndex().row();
    int select_phenotype_index =  get_phenotype_index( data_view_Dialog::original_tableview,Phenotype_list);
    qDebug()<<endl<<"selected row of  effect in original_tableview is"<<selected_row;
    if((selected_row==-1))
    {

        return ;
    }
    bool Norepetition_flag = true;  //check the item is selected already or not
    QStringList* list_bf;
    if(factor_or_not){
        list_bf = &factor_list;
    }else {
        list_bf = &Numeric_list;
    }
    int count_effect_list = (*list_bf).length();




    if(count_effect_list) //check the new effect is selected already?
    {
        for(int i = 0;i < ((*list_bf).length());i++)
        {
            if(QString::number(select_phenotype_index) == (*list_bf)[i])//如果新添加效应已存在
            {
                Norepetition_flag = false;
                qDebug()<<endl<<"selected index of phenotypelist is "<<select_phenotype_index;
                break;
            }
        }
    }
    if(Norepetition_flag)
    {
        (*list_bf) << QString::number(select_phenotype_index);
        qDebug()<<endl<<"effect_list:"<<(*list_bf);
        qDebug()<<endl<<"the num of effect_list:"<<count_effect_list;
    }

}

void remove_item_from_list(QTableView* select_tableview,QStringList* list_bf)
{
    int fixed_remove_index = select_tableview->currentIndex().row();
    qDebug()<<endl<<"remove row of effect is"<<fixed_remove_index;
    if(!(fixed_remove_index==-1))
    {
        (*list_bf).removeAt(fixed_remove_index);
    }

    qDebug()<<endl<<"effect_list:"<<*list_bf;
}

void data_view_Dialog::on_select_to_num_pushButton_clicked()
{
    data_view_add2list(false,data_view_Dialog::Phenotype_list);
    data_view_refresh(data_view_Dialog::Phenotype_list);
}

void data_view_Dialog::on_disselect_to_num_pushButton_clicked()
{
    remove_item_from_list(data_view_Dialog::Numeric_tableview,&Numeric_list);
    data_view_refresh(data_view_Dialog::Phenotype_list);
}

void data_view_Dialog::on_select_to_factor_pushButton_clicked()
{
    data_view_add2list(true,data_view_Dialog::Phenotype_list);
    data_view_refresh(data_view_Dialog::Phenotype_list);
}

void data_view_Dialog::on_disselect_to_factor_pushButton_clicked()
{
    remove_item_from_list(data_view_Dialog::factor_tableview,&factor_list);
    data_view_refresh(data_view_Dialog::Phenotype_list);
}

void data_view_Dialog::on_data_view_done_pushButton_clicked()
{
    if((data_view_Dialog::Numeric_list.length()+data_view_Dialog::factor_list.length())==data_view_Dialog::Phenotype_list.length())
    {
        qDebug()<<endl<<"emit factor and numeric..";
        emit sendData(data_view_Dialog::Numeric_list,data_view_Dialog::factor_list);
    }
    else {
        QMessageBox::information(nullptr, "Error", "There are still some phenotypes that have not been selected!");
    }

}

void data_view_Dialog::on_view_data_pushButton_clicked()
{
    QString runPath = QDir::currentPath();
    runPath.append("/rscript/review_data.R");
    qDebug() << endl <<"runPath:" << runPath << endl;
    QString param;
        // The sequence of param is not changeable
        param.clear();
        param.append("Rscript");
        param.append(" ");
        param.append(runPath);
        param.append(" ");
        param.append(data_view_Dialog::csv_path);
        param.append(" ");
        param.append(data_view_Dialog::output_path);
    qDebug()<<endl<<"review data param :"<<param<<endl;
    Process* outlier_process;
    outlier_process = new Process();
    if(!(outlier_process->runRscript(param,"Review data")))
    {
        QMessageBox::warning(nullptr, "Process error:", "Can't review data!");
    }
    QString plot_histogrom_image_path = data_view_Dialog::output_path + "/plot_histogram.png";
    QString plot_bar_image_path = data_view_Dialog::output_path + "/plot_bar.png";

    QPixmap plot_histogrom_image;
    QPixmap plot_bar_image;

    if (plot_histogrom_image.load(plot_histogrom_image_path))
    {
        QLabel *review_data_label=new QLabel();
        plot_histogrom_image.scaled(review_data_label->size(),Qt::KeepAspectRatio);
        review_data_label->setScaledContents(true);
        review_data_label->setPixmap(plot_histogrom_image);
        review_data_label->show();
        review_data_label->setToolTip("Histogrom");
    }
    else {
        QMessageBox::warning(nullptr, "file error:", "Can't find "+plot_histogrom_image_path);
    }
    if (plot_bar_image.load(plot_bar_image_path))
    {
        QLabel *review_data_label=new QLabel();
        plot_bar_image.scaled(review_data_label->size(),Qt::KeepAspectRatio);
        review_data_label->setScaledContents(true);
        review_data_label->setPixmap(plot_bar_image_path);
        review_data_label->show();
        review_data_label->setToolTip("Bar");
    }
    else {
        QMessageBox::warning(nullptr, "file error:", "Can't find "+plot_bar_image_path);
    }




}
