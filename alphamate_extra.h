#include "mainwindow.h"

#ifndef ALPHAMATE_EXTRA_H
#define ALPHAMATE_EXTRA_H

#include <QDialog>

namespace Ui {
class alphamate;
}

class alphamate : public QDialog
{
    Q_OBJECT

public:
    explicit alphamate(QWidget *parent = nullptr);
    ~alphamate();

private:
    Ui::alphamate *ui;
};

#endif // ALPHAMATE_H
