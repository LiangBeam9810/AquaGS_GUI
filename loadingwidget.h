#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H



#include <QDialog>
#include <QDesktopWidget>
#include <QMovie>

namespace Ui {
class QLoadingWidget;
}

class QLoadingWidget : public QDialog
{
    Q_OBJECT

public:
    explicit QLoadingWidget(QWidget *parent = 0);
    ~QLoadingWidget();

private:
    Ui::QLoadingWidget *ui;
};

#endif // LOADINGWIDGET_H
