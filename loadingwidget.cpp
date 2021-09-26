#include "loadingwidget.h"

QLoadingWidget::QLoadingWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QLoadingWidget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    int frmX = width();
    int frmY = height();

    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();

    QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
    move(movePoint);


    QMovie *movie = new QMovie(":/new/prefix1/res/loading");
    ui->lbl_gif->setMovie(movie);
    movie->start();
}

QLoadingWidget::~QLoadingWidget()
{
    delete ui;

}
