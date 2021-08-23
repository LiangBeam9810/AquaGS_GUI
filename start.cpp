#include "start.h"

/*--------------------------strat index------------------------------------*/
bool isDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if(dir.exists())
    {
      return true;
    }
    return false;
}

bool isFileExist(QString fullFileName)
{
    QFileInfo fileInfo(fullFileName);
    if(fileInfo.isFile())
    {
        return true;
    }
    return false;
}

void lineEdit2green(QLineEdit* lineedit)
{
   lineedit->setStyleSheet("color:green");
   lineedit->setFont(QFont( "Abyssinica SIL" , 12 ,  QFont::Bold) );
   return;
}

void lineEdit2red(QLineEdit* lineedit)
{
   lineedit->setStyleSheet("color:red");
   lineedit->setFont(QFont( "Abyssinica SIL" , 12 ,  QFont::Bold) );
   return;
}

QString get_select_path(QString file_type,QMainWindow* mainwindow,QLineEdit* lineedit,int type)
{
    if(!type)
    {
        QString flodpath = QFileDialog::getExistingDirectory(mainwindow, "choose output folder","/");
        if(flodpath.isEmpty()) return "";
        lineedit->setText(flodpath);
        lineEdit2green(lineedit);
        qDebug()<<endl << "user select :"<<flodpath <<endl;
        return flodpath;
    }
    else
    {
        QFileDialog *fileDialog = new QFileDialog(mainwindow, "Open file", "", file_type);
        fileDialog->setViewMode(QFileDialog::Detail);
        QString filepath;
        if (fileDialog->exec())
        {
            filepath = (fileDialog->selectedFiles())[0];
            lineedit->setText(filepath);
            lineEdit2green(lineedit);
        }
        qDebug() <<endl << "user select :"<<filepath <<endl;
        delete fileDialog;
        return filepath;
    }

}

void get_enter_path(QLineEdit* lineedit,int type)
{
    QString enter_path = lineedit->text();
    qDebug() <<endl << "user enter: " << enter_path<<endl;
    lineedit->setText(enter_path);
    if((type&&(isFileExist(enter_path)))||((!type)&&(isDirExist(enter_path)))){ //0:flod 1:csv 2:vcf
        lineEdit2green(lineedit);
    }
    else
    {
        QString out_info;
        switch (type)
        {
            case 0:
                out_info = "The fold path error!";
                break;
            case 1:
                out_info = "The csv path error!";
                break;
            case 2:
                out_info = "The vcf path error!";
                break;
            default: break;
        }
       qDebug()  <<endl<<"Error of path:"<< out_info<<endl;
       QMessageBox::information(NULL, "Error ", out_info);
       lineEdit2red(lineedit);
    }
}

QStringList get_csv_title(QString path)
{
    QFile csv_file(path);
    QStringList csv_list;
    csv_list.clear();
    if (csv_file.open(QIODevice::ReadWrite)) //
    {
        qDebug()<< "reading csv..." ;
        QTextStream stream(&csv_file);
        csv_list.push_back(stream.readLine());//
        Q_FOREACH(QString str, csv_list) //½«QStringlist£¨csv_list£©×ª³É QString£¨str£©
        csv_list = str.split(",");//·Ö¸ô×Ö·û´®
        csv_file.close();
        qDebug()<< "csv title: " ;
        qDebug()<< csv_list << endl;
    }
    else
    {
         QMessageBox::about(NULL, "csv file", "Can't open csv file!");
    }
    return csv_list;
}

bool check_all_path(QLineEdit* out_line,QLineEdit* csv_line,QLineEdit* vcf_line,
                    QString* output_path,QString* csv_path,QString* vcf_path)
{
    *output_path = out_line->text();
    *csv_path = csv_line->text();
    *vcf_path = vcf_line->text();
    if(!(isFileExist(*csv_path)) || (*csv_path).isEmpty()||!(isFileExist(*vcf_path)) || (*vcf_path).isEmpty() ||!(isDirExist(*output_path))|| (*output_path).isEmpty())
    {
        if(!(isFileExist(*csv_path)) || (*csv_path).isEmpty())
        {
            qDebug() <<endl << "csv path no exist!"<<endl;
            QMessageBox::information(NULL, "Error ", "The csv path error!");
            lineEdit2red(csv_line);
        }
        if(!(isFileExist(*vcf_path)) || (*vcf_path).isEmpty() )
        {
            qDebug() <<endl << "vcf path no exist!"<<endl;
            QMessageBox::information(NULL, "Error ", "The vcf path error!");
            lineEdit2red(vcf_line);
        }
        if(!(isDirExist(*output_path))|| (*output_path).isEmpty())
        {
            qDebug() <<endl << "output path no exist!"<<endl;
            QMessageBox::information(NULL, "Error ", "The output path error!");
            lineEdit2red(out_line);
        }
        return false;
    }
    else //Let's go to the next page(or called 'index').
    {
        return true;
    }
}
