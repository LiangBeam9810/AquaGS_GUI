#include "process.h"
#include "mainwindow.h"
extern MainWindow* m;


Process::Process(QObject *parent) : QProcess(parent)
{
    connect(this, SIGNAL(readyReadStandardOutput()), this, SLOT(on_readProcessOutput()));
    connect(this, SIGNAL(readyReadStandardError()), this, SLOT(on_readProcessError()));
    connect(this, SIGNAL(stateChanged(QProcess::ProcessState)), this,SLOT(process_notrunning()));
    connect(this, SIGNAL(messageStandardOutput(QString)), m,SLOT(sent_massage_to_terminal(QString)));//将发送输出信号与写入终端界面函数绑定
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
    if((message[0] == '\x8')||(message[0] == '\xd')){// ignore  such as "36%" , "--vcf: 34k variants complete." and "27%"
        return;
    }
    emit messageStandardOutput(message);//发送输出信号
    //qApp->processEvents();
    //emit on_outMessageReady(message);
}

void Process::on_readProcessError()
{
    QString message = QString::fromLocal8Bit(this->readAllStandardError().data());
    qDebug()  <<  message.toStdString().data() ;
    emit messageStandardOutput(message);//发送输出信号
    //emit on_errMessageReady(message);
}

void Process::Process_runing_gif(QString title)
{
    //unsigned int i = 0;
    LoadingDialog* loading_page;
    loading_page = new  LoadingDialog;
    QString title_string = title;
    loading_page->setTipsText(title_string);
    connect(loading_page->m_pCancelBtn, &QPushButton::clicked, m->Terminal_log, &Terminal_Dialog::open_terminal);
    connect(this, SIGNAL(process_end_to_close_gif(QString)), loading_page, SLOT(cancelBtnClicked()));//运行完成信号 绑定关闭loading界面的取消函数
    while ((this->state() == QProcess::Starting)||(this->state() == QProcess::Running))
    {
       loading_page->exec();
    }
    loading_page->cancelWaiting();
    loading_page->close();
}

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
    static int runExTool_count = 0;
    this->start(tool, param);
    if (!this->waitForStarted())
    {
        this->close();
        return false;
    }
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
