#include "mainwindow.h"

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    TitleBar *pTitleBar = new TitleBar(this);
    pTitleBar->setObjectName("TitleBar");
    pTitleBar->disableMax();
    installEventFilter(pTitleBar);
    win = new QWidget(this);
    /**QPalette pal(pTitleBar->palette());
    pal.setColor(QPalette::Base, QColor(0, 0, 0));
    setAutoFillBackground(true);
    setPalette(pal);**/

    title1 = new QLabel(this);
    leb_name = new QLabel(this);
    leb_psw = new QLabel(this);
    leb_cert = new QLabel(this);
    replace_cert = new Mylabel(this);
    image_cert = new QImage();
    edit_name = new QLineEdit(this);
    edit_psw = new QLineEdit(this);
    edit_cert = new QLineEdit(this);



    h_name = new QHBoxLayout(this);
    h_psw = new QHBoxLayout(this);
    h_cert = new QHBoxLayout(this);
    h_btn = new QHBoxLayout(this);
    v1 = new QVBoxLayout(this);

    btn_login = new QPushButton(this);
    btn_close = new QPushButton(this);


    //this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setWindowTitle("教务系统v0.01C");
    this->setWindowIcon(QIcon(":/J.ico"));
    this->setFixedSize(400,280);
    this->setCentralWidget(win);
    title1->setText("Beta 0.01C");
    title1->setAlignment(Qt::AlignCenter);


    QRegExp regExp("[0-9]\\d{10}");
    leb_name->setText("用户名：");
    leb_name->setBuddy(edit_name);
    edit_name->setFixedSize(160,24);
    edit_name->setValidator(new QRegExpValidator(regExp, this));
    h_name->addStretch();
    h_name->addWidget(leb_name);
    h_name->addWidget(edit_name);
    h_name->addStretch();
    h_name->setMargin(5);
    h_name->setSpacing(6);

    leb_psw->setText("  密码：");
    leb_psw->setBuddy(edit_psw);
    edit_psw->setFixedSize(160,24);
    edit_psw->setEchoMode(QLineEdit::Password);
    h_psw->addStretch();
    h_psw->addWidget(leb_psw);
    h_psw->addWidget(edit_psw);
    h_psw->addStretch();
    h_psw->setMargin(5);
    h_psw->setSpacing(6);

    leb_cert->setText("验证码：");
    replace_cert->setText("loading");
    replace_cert->setCursor(Qt::PointingHandCursor);
    replace_cert->setFixedSize(66,26);
    edit_cert->setFixedSize(92,24);
    QRegExp regEx("[0-9a-zA-Z]{4}");
    edit_cert->setValidator(new QRegExpValidator(regEx, this));
    leb_cert->setBuddy(edit_cert);
    h_cert->addStretch();
    h_cert->addWidget(leb_cert);
    h_cert->addWidget(replace_cert);
    h_cert->addWidget(edit_cert);
    h_cert->addStretch();
    h_cert->setMargin(5);
    h_cert->setSpacing(6);





    btn_login->setText("登录");
    btn_close->setText("退出");
    btn_login->setDefault(true);
    //btn_login->setShortcut(Qt::Key_Enter);
    btn_login->setFixedSize(80,38);
    btn_close->setFixedSize(80,38);
    h_btn->addStretch();
    h_btn->addWidget(btn_login);
    h_btn->addWidget(btn_close);
    h_btn->addStretch();
    h_btn->setSpacing(40);

    v1->addWidget(pTitleBar);
    v1->addStretch();
    v1->addWidget(title1);
    v1->addStretch();
    v1->addLayout(h_name);
    v1->addLayout(h_psw);
    v1->addLayout(h_cert);
    v1->addStretch();
    v1->addLayout(h_btn);
    v1->addStretch();
    v1->setMargin(10);
    v1->addSpacing(20);


    edit_cert->setStyleSheet("font-weight:blod");
    edit_name->setStyleSheet(" font-weight:blod");
    edit_psw->setStyleSheet(" font-weight:blod;");



    win->setLayout(v1);



    QString user_dir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QDir dir(user_dir+"/JLICT/");
    if(!dir.exists()){
        dir.mkdir(user_dir+"/JLICT/");
    }
    QFile file(user_dir+"/JLICT/data.dat");
    if(file.open(QFile::ReadOnly)){
        QDataStream in_stream(&file);
        qint32 flag;
        in_stream.setVersion(QDataStream::Qt_5_10);
        in_stream >> flag;
        if(flag != 0xA0B0C0D0){
            file.close();
        }else{
            QString tmp;
            in_stream >> tmp;
            edit_name->setText(tmp);
            tmp = "";
            in_stream >> flag;
            in_stream >> tmp;
            edit_psw->setText(tmp);
            edit_cert->setFocus();
            file.close();
        }

    }



    connect(btn_close,SIGNAL(clicked()),this,SLOT(close()));
    connect(btn_login,SIGNAL(clicked()),this,SLOT(Sign()));
    connect(replace_cert,SIGNAL(clicked()),this,SLOT(refresh()));
    connect(edit_cert,SIGNAL(returnPressed()),this,SLOT(Sign()));
    //connect(replace_cert,SIGNAL,,);



    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    return;
}
mainWindow::~mainWindow(){

}

void mainWindow::Sign(void){
    QString login_data = "Account=" + edit_name->text() + "&PWD=" + edit_psw->text() + "&CheckCode=" + edit_cert->text() + "&cmdok=";
    emit StartLogin(&login_data);

    return;
}

void mainWindow::flash_img(QPixmap * src){
    //qDebug() << src;
    //image_cert->load(src);
    replace_cert->setPixmap(*src);
    return;
}


void mainWindow::Login_Error(){
    QMessageBox::information(this, "登录失败","请确认用户名密码及验证码输入正确");
    edit_name->setText("");
    edit_psw->setText("");
    edit_cert->setText("");
    this->refresh();
    return;
}

void mainWindow::Login_Timeout(){
    QMessageBox::information(this, "网络异常","请确认网络连接正常");
    return;
}
void mainWindow::Cls(bool bl)
{
   //界面动画，改变透明度的方式消失1 - 0渐变
   QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
   animation->setDuration(1000);
   animation->setStartValue(1);
   animation->setEndValue(0);
   animation->start();
   if(!bl){
       QString user_dir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
       QFile file(user_dir+"/JLICT/data.dat");
       if(file.open(QFile::WriteOnly)){
           QDataStream out(&file);
           qint32 flag = 0xA0B0C0D0;
           out.setVersion(QDataStream::Qt_5_10);
           out << flag;
           out << edit_name->text();
           flag = 0xC0D0E0F0;
           out << flag;
           out << edit_psw->text();
           file.close();
       }
        emit SetName(edit_name->text());
        emit Toggle();
   }
  this->close();
  return;
}


void mainWindow::refresh(){
    emit Refresh();
    return;
}



