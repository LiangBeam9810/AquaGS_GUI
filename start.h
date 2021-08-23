#include "mainwindow.h"

#ifndef START_H
#define START_H
/*--------------------------------------*/
bool isDirExist(QString fullPath);
bool isFileExist(QString fullFileName);

void lineEdit2green(QLineEdit* lineedit);
void lineEdit2red(QLineEdit* lineedit);

QString get_select_path(QString file_type,QMainWindow* mainwindow,QLineEdit* lineedit,int type);
void get_enter_path(QLineEdit* lineedit,int type);
bool check_all_path(QLineEdit* out_line,QLineEdit* csv_line,QLineEdit* vcf_line,
                    QString* output_path,QString* csv_path,QString* vcf_path);

QStringList get_csv_title(QString path);
/*--------------------------------------*/
#endif // START_H
