#include "process.h"

Process::Process(QObject *parent) : QProcess(parent)
{
    connect(this, SIGNAL(readyReadStandardOutput()), this, SLOT(on_readProcessOutput()));
    connect(this, SIGNAL(readyReadStandardError()), this, SLOT(on_readProcessError()));
    connect(this, SIGNAL(stateChanged(QProcess::ProcessState)), this,SLOT(process_notrunning()));
    // Read message form Process and display in RunningMsgWidget
}
void Process:: process_notrunning()
{
    if(this->state() == QProcess::NotRunning)
    {
        emit process_end_to_close_gif("1");//运行完成发送信号
    }
}
void Process::on_readProcessOutput()
{
    QString message = QString::fromLocal8Bit(this->readAllStandardOutput().data());
    qDebug()  <<  message.toStdString().data() ;
    //qApp->processEvents();
    //emit on_outMessageReady(message);
}

void Process::on_readProcessError()
{
    QString message = QString::fromLocal8Bit(this->readAllStandardError().data());
    qDebug()  <<  message.toStdString().data() ;
    //emit on_errMessageReady(message);
}

void Process::Process_runing_gif(QString title)
{
    //unsigned int i = 0;
    LoadingDialog* loading_page;
    loading_page = new  LoadingDialog;
    QString title_string = title;
    loading_page->setTipsText(title_string);
    connect(this, SIGNAL(process_end_to_close_gif(QString)), loading_page, SLOT(cancelBtnClicked()));//运行完成信号 绑定关闭loading界面的取消函数

    while ((this->state() == QProcess::Starting)||(this->state() == QProcess::Running))
    {
       loading_page->exec();
    }
    loading_page->cancelWaiting();
}
/*
void Process::on_outMessageReady(const QString text)
{
    //if (this->running_flag)
    //{
        qDebug()  << "Exoutput:" << text.toStdString().data() ;
        qApp->processEvents();
    //}
}

void Process::on_errMessageReady(const QString text)
{
    //if (this->running_flag)
    //{
        qDebug() << "Exoutput:" <<text.toStdString().data() ;
    //}
}
*/
bool  Process::runRscript(QString param,QString title)
{
    //connect(this, SIGNAL(outMessageReady(QString)), this, SLOT(on_outMessageReady(QString)));
    //connect(this, SIGNAL(errMessageReady(QString)), this, SLOT(on_errMessageReady(QString)));
    this->start(param);
    if (!this->waitForStarted())
    {
        this->close();
        return false;
    }
    this->Process_runing_gif(title);
    this->close();
    return true;
}

bool Process::runExTool(QString tool, QStringList param)
{
    //connect(this, SIGNAL(outMessageReady(QString)), this, SLOT(on_outMessageReady(QString)));
    //connect(this, SIGNAL(errMessageReady(QString)), this, SLOT(on_errMessageReady(QString)));
    static int runExTool_count = 0;
    this->start(tool, param);
    if (!this->waitForStarted())
    {
        //emit setMsgBoxSig("Error", "Can't open " + tool);
        this->close();
        return false;
    }
    //proc->waitForFinished(-1);
    this->Process_runing_gif("plinking ");
    ++runExTool_count;
    qDebug() << "i: " << runExTool_count << endl
             << tool << endl << param << endl;

    bool ret = true;
    this->close();
    return ret;
}

bool Process::runAlphamate(QString dir,QString param,QString title)
{
    this->setWorkingDirectory(dir);
    this->start(param);
    if (!this->waitForStarted())
    {
        this->close();
        return false;
    }
    this->Process_runing_gif(title);
    this->close();
    return true;
}
