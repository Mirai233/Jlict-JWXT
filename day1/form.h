#ifndef FORM_H
#define FORM_H

#include <chinese.h>
#include <QDebug>
#include <QWidget>
#include <QPropertyAnimation>
#include <QWebEngineView>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QPoint>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolTip>

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
    void Form_XJKP_init(QString);
    void Form_CJCX_init(QString);
    void Form_XSKB_init(QString);
    void Form_HKSQ_init(QString);
    void Change_user();
private:
    Ui::Form *ui;
    QWebEngineView *m_webView;
    QWebEngineView *m_webView1;
    QWebEngineView *m_webView2;
    QWebEngineView *m_webView3;
    QHBoxLayout *l_tab;
    QHBoxLayout *l_tab1;
    QHBoxLayout *l_tab2;
    QHBoxLayout *l_tab3;
    QMenuBar *menu_bar;
    QMenu *menu1;
    QAction *act1;
    QAction *act2;
};

#endif // FORM_H
