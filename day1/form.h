#ifndef FORM_H
#define FORM_H

#include <chinese.h>
#include <QDebug>
#include <QWidget>
#include <QPropertyAnimation>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QPoint>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolTip>
#include <QFile>
#include <QList>
#include <QStandardPaths>
#include <preg_jlict.h>
#include <QStandardItem>
#include <QMessageBox>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
signals:
    void init_so();
    void toggle_to_login();
public slots:
    void Start_Init(QString);
    void Form_CJCX_init(QString);
    void Form_XSKB_init(QString);
    void Change_user();
    void Show_Score();
private:
    Ui::Form *ui;
    QString Score = "";
    QHBoxLayout *l_tab1;
    QHBoxLayout *l_tab2;
    QMenuBar *menu_bar;
    QMenu *menu1;
    QMenu *menu2;
    QAction *act1;
    QAction *act2;
    QAction *act3;
    Preg_Jlict *j;
};

#endif // FORM_H
