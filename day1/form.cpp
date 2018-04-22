#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    m_webView = new QWebEngineView(this);
    m_webView1 = new QWebEngineView(this);
    m_webView2 = new QWebEngineView(this);
    m_webView3 = new QWebEngineView(this);
    l_tab = new QHBoxLayout(this);
    l_tab1 = new QHBoxLayout(this);
    l_tab2 = new QHBoxLayout(this);
    l_tab3 = new QHBoxLayout(this);

    l_tab -> addWidget(m_webView);
    l_tab -> setSpacing(1);
    ui->tab->setLayout(l_tab);

    l_tab1 -> addWidget(m_webView1);
    l_tab1 -> setSpacing(1);
    ui->tab_2->setLayout(l_tab1);

    l_tab2 -> addWidget(m_webView2);
    l_tab2 -> setSpacing(1);
    ui->tab_3->setLayout(l_tab2);

    l_tab3 -> addWidget(m_webView3);
    l_tab3 -> setSpacing(1);
    ui->tab_4->setLayout(l_tab3);

    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();
    QPoint movePoint(deskWidth / 2 - 600, deskHeight / 2 - 300);
    this->move(movePoint);
}

Form::~Form()
{
    delete ui;
}

void Form::Start_Init(QString data){
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1800);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    menu_bar = new QMenuBar(this);
    menu1 = new QMenu(data,this);
    menu_bar->addMenu(menu1);
    act1 = new QAction("切换账号",this);
    act2 = new QAction("退出程序",this);
    menu1->addAction(act1);
    menu1->addSeparator();
    menu1->addAction(act2);
    act1->setDisabled(true);
    act1->setToolTip("本功能暂不可用");
    ui->verticalLayout->setMenuBar(menu_bar);
    connect(act2,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(act1,SIGNAL(triggered(bool)),this,SLOT(Change_user()));
    this->setWindowTitle("教务系统 - " + data);
    this->show();
    return;
}
void Form::Form_XJKP_init(QString data){
    m_webView->setHtml(data);
    return;
}
void Form::Form_XSKB_init(QString data){
    m_webView2->setHtml(data);
    return;
}
void Form::Form_CJCX_init(QString data){
    m_webView1->setHtml(data);
    return;
}void Form::Form_HKSQ_init(QString data){
    m_webView3->setHtml(data);
    return;
}

void Form::Change_user(){
    emit toggle_to_login();
    this->close();
}
