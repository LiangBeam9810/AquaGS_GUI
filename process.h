#ifndef PROCESS_H
#define PROCESS_H

#include <QDebug>
#include <QProcess>
#include <QMessageBox>
#include <QTimer>
#include <QtGui/qguiapplication.h>



class Process : public QProcess
{
 Q_OBJECT
public:
    explicit Process(QObject *parent = nullptr);
    QString getMessage();
public slots:
    void on_readProcessOutput();
    void on_readProcessError();
    void on_outMessageReady(QString text);
    void on_errMessageReady(QString text);
    bool runRscript(QString param,QString title);
    bool runExTool(QString tool, QStringList param);
signals:
    void outMessageReady(const QString);
    void errMessageReady(const QString);
};
void Process_runing_gif(QProcess* Process,QString title);
#endif // PROCESS_H
