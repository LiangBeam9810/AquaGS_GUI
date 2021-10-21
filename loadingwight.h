#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H
#include <QMovie>
#include <QLabel>
#include <QDialog>
#include <QPainter>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QDir>
#include <QDebug>
#include <terminal_dialog.h>
#define USER_CANCEL -1
class LoadingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoadingDialog(QWidget *parent = nullptr);
    ~LoadingDialog();
    //设置提示文本
    void setTipsText(QString strTipsText);
    //设置是否显示取消等待按钮
    void setCanCancel(bool bCanCancel);
    //移动到指定窗口中间显示
    void moveToCenter(QWidget* pParent);
    //
    void opend_terminal_page(Terminal_Dialog* Terminal_log);
     QPushButton *m_pCancelBtn;
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    void initUi();
Q_SIGNALS:
    void cancelWaiting();
public slots:
    void cancelBtnClicked();
private:
    QFrame *m_pCenterFrame;
    QLabel *m_pMovieLabel;
    QMovie *m_pLoadingMovie;
    QLabel *m_pTipsLabel;

};
#endif // LOADINGDIALOG_H
