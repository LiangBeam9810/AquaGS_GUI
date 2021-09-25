#include "process.h"

Process::Process(QObject *parent) : QProcess(parent)
{
    connect(this, SIGNAL(readyReadStandardOutput()), this, SLOT(on_readProcessOutput()));
    connect(this, SIGNAL(readyReadStandardError()), this, SLOT(on_readProcessError()));
    // Read message form Process and display in RunningMsgWidget
}

void Process::on_readProcessOutput()
{
    QString message = QString::fromLocal8Bit(this->readAllStandardOutput().data());
    emit on_outMessageReady(message);
}

void Process::on_readProcessError()
{
    QString message = QString::fromLocal8Bit(this->readAllStandardError().data());
    emit on_errMessageReady(message);
}

void Process_runing_gif(QProcess* Process,QString title)
{
    unsigned int i = 0;
    while ((Process->state() == QProcess::Starting)||(Process->state() == QProcess::Running)) {
        QString title_string = title;
        for(unsigned int j = 0;j < i;j++)
        {
             title_string = title_string + +". ";
        }
        i++;
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,"Running",title_string);
        QTimer::singleShot(1000,m_box,SLOT(close()));
        m_box->exec();
        if(i > 3)
        {
            i = 0;
        }
    }
}
void Process::on_outMessageReady(const QString text)
{
    //if (this->running_flag)
    //{
        qDebug() << "Out: " << text << endl;
        qApp->processEvents();
    //}
}

void Process::on_errMessageReady(const QString text)
{
    //if (this->running_flag)
    //{
        qDebug() << "Error: " << text << endl;
    //}
}
bool  Process::runRscript(QString param,QString title)
{
    connect(this, SIGNAL(outMessageReady(QString)), this, SLOT(on_outMessageReady(QString)));
    connect(this, SIGNAL(errMessageReady(QString)), this, SLOT(on_errMessageReady(QString)));
    this->start(param);
    if (!this->waitForStarted())
    {
        this->close();
        return false;
    }
    Process_runing_gif(this,title);
    this->close();
    return true;
}

bool Process::runExTool(QString tool, QStringList param)
{
    connect(this, SIGNAL(outMessageReady(QString)), this, SLOT(on_outMessageReady(QString)));
    connect(this, SIGNAL(errMessageReady(QString)), this, SLOT(on_errMessageReady(QString)));
    static int runExTool_count = 0;
    this->start(tool, param);
    if (!this->waitForStarted())
    {
        //emit setMsgBoxSig("Error", "Can't open " + tool);
        this->close();
        return false;
    }
    //proc->waitForFinished(-1);
    Process_runing_gif(this,"plinking ");
    ++runExTool_count;
    qDebug() << "i: " << runExTool_count << endl
             << tool << endl << param << endl;

    bool ret = true;
    this->close();
    return ret;
}


