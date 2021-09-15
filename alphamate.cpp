#include "alphamate.h"
#include "ui_alphamate.h"

alphamate::alphamate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alphamate)
{
    ui->setupUi(this);
}

alphamate::~alphamate()
{
    delete ui;
}
