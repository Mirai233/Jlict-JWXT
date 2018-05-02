#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H
#include <chinese.h>
#include <QDialog>
#include <QMovie>
#include <QDesktopWidget>
#include <QPoint>
#include <QLabel>
#include <QTime>
#include <QIcon>
#include <QPropertyAnimation>


class LoadingDialog : public QDialog
{
    Q_OBJECT
public:
    LoadingDialog(QWidget *);
    LoadingDialog();
    ~LoadingDialog();
    void sleep(int);
public slots:
    void loading();
    void loading_error();
    void toggeleToForm(QString);
signals:
    void toForm(QString);
private:
    QLabel * gif;
    QLabel * tips;
    QMovie * loader;
};

#endif // LOADINGDIALOG_H
