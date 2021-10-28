#include "terminal_dialog.h"
#include "ui_terminal_dialog.h"

Terminal_Dialog::Terminal_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Terminal_Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("OUTPUT MESSAGE LOG");
    init();
}

Terminal_Dialog::~Terminal_Dialog()
{
    delete ui;
}
void Terminal_Dialog:: open_terminal()
{
    this->show();
}
void Terminal_Dialog::init()
{
    ui->Terminal_textBrowser->clear();//清空终端界面
}
void Terminal_Dialog::append_Terminal_textBrowser(QString massage)
{
    ui->Terminal_textBrowser->append(massage)  ; //文本框逐条添加数据
    ui->Terminal_textBrowser->moveCursor(ui->Terminal_textBrowser->textCursor().End) ;//滑动到最后
}
