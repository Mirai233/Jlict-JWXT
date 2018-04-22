#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <chinese.h>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QImage>
#include <QMessageBox>
#include <QIcon>
#include <QImage>
#include <QDebug>
#include <myhttp.h>
#include <mylabel.h>
#include <QPropertyAnimation>
#include <QRegExpValidator>
#include <QDialog>
#include <QCheckBox>
#include <form.h>
#include <QStandardPaths>
#include <QList>
#include <QDataStream>
#include <QMessageBox>

class mainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

signals:
    void Signed(void);
    void StartLogin(QString *);
    void SetName(QString);
    void Refresh();
    void Toggle();
public slots:
    void flash_img(QPixmap *);
    void Sign(void);
    void Cls(bool);
    void Login_Error();
    void Login_Timeout();
    void refresh();
private:
    QWidget *win;

    QLabel *title1;
    QLabel *leb_name;
    QLabel *leb_psw;
    QLabel *leb_cert;
    Mylabel *replace_cert;
    QLineEdit *edit_name;
    QLineEdit *edit_psw;
    QLineEdit *edit_cert;
    QImage *image_cert;

    QHBoxLayout *h_name;
    QHBoxLayout *h_psw;
    QHBoxLayout *h_cert;
    QHBoxLayout *h_btn;
    QVBoxLayout *v1;

    QPushButton *btn_login;
    QPushButton *btn_close;

    Form *form1;

};

#endif // MAINWINDOW_H
