#ifndef PROCESS_H
#define PROCESS_H

#include <QDebug>
#include <QProcess>
#include <QMessageBox>
#include <QTimer>
#include <QtGui/qguiapplication.h>
#include "loadingwight.h"



class Process : public QProcess
{
 Q_OBJECT
public:
    explicit Process(QObject *parent = nullptr);
    QString getMessage();
    void Process_runing_gif(QString title);
public slots:
    void on_readProcessOutput();
    void on_readProcessError();
    //void on_outMessageReady(QString text);
    //void on_errMessageReady(QString text);
    bool runRscript(QString param,QString title);
    bool runExTool(QString tool, QStringList param);
    bool runAlphamate(QString dir,QString param,QString title);
    void process_notrunning();
signals:
    void process_end_to_close_gif(const QString);
};
void Process_runing_gif(QProcess* Process,QString title);
#endif // PROCESS_H
