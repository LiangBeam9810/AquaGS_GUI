#ifndef TERMINAL_DIALOG_H
#define TERMINAL_DIALOG_H

#include <QDialog>

namespace Ui {
class Terminal_Dialog;
}

class Terminal_Dialog : public QDialog
{
    Q_OBJECT

    void init();
public:
    void append_Terminal_textBrowser(QString message);
    explicit Terminal_Dialog(QWidget *parent = nullptr);
    ~Terminal_Dialog();
public slots:
    void  open_terminal();

private:
    Ui::Terminal_Dialog *ui;
};

#endif // TERMINAL_DIALOG_H
