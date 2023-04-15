#include <QMainWindow>
#include <iostream>
#include <QMainWindow>
#include <QApplication>
#include <QMainWindow>
#include <QFileDialog>
#include <QAbstractItemView>
#include <QProcess>
#include <QDebug>
#include <QList>
#include <QThread>
#include <QMap>
#include <QButtonGroup>
#include <QDateTime>
#include <QThread>
#include <QMessageBox>
#include <QComboBox>
#include <QTextBrowser>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTableView>
#include <QStandardItemModel>
#include <QListWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <sstream>
#include <QFile>
#include <QtConcurrent>
#include <QFuture>
#include <QMovie>
#include <QDialog>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QtConcurrent>
#include <QFuture>


#ifndef START_H
#define START_H
/*--------------------------------------*/
void init_flode(QString flode_path);
void init_file(QString output_path,QStringList filelist);
bool isDirExist(QString fullPath);
bool isFileExist(QString fullFileName);

void lineEdit2green(QLineEdit* lineedit);
void lineEdit2red(QLineEdit* lineedit);

QString get_select_path(QString file_type,QMainWindow* mainwindow,QLineEdit* lineedit,int type);
void get_enter_path(QLineEdit* lineedit,int type);
bool check_all_path(QLineEdit* out_line,QLineEdit* csv_line,QLineEdit* vcf_line,
                    QString* output_path,QString* csv_path,QString* vcf_path,QString* plink_log_path);

QStringList get_csv_title(QString path);
/*--------------------------------------*/
#endif // START_H
