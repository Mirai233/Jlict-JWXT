#include "loadingdialog.h"
LoadingDialog::LoadingDialog(QWidget* parent = Q_NULLPTR)
    :QDialog(parent)
{
    gif = new QLabel(this);
    tips = new QLabel(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint |Qt::WindowStaysOnTopHint);
    this->setFixedSize(120,140);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();
    QPoint movePoint(deskWidth / 2 - 60, deskHeight / 2 - 60);
    this->move(movePoint);
    loader = new QMovie(":/loading");
    gif->setFixedSize(120,120);
    loader->setScaledSize(QSize(120,120));
    gif->setMovie(loader);
    tips->setText("载入中..");
    tips->move(0,120);
    tips->setFixedSize(120,20);
    tips->setAlignment(Qt::AlignCenter);
    tips->setStyleSheet("background-color:#252525;font-size:12px");
}
LoadingDialog::LoadingDialog()
    :QDialog()
{
    gif = new QLabel(this);
    tips = new QLabel(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint |Qt::WindowStaysOnTopHint);
    this->setFixedSize(120,140);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();
    QPoint movePoint(deskWidth / 2 - 60, deskHeight / 2 - 60);
    this->move(movePoint);
    loader = new QMovie(":/loading");
    gif->setFixedSize(120,120);
    loader->setScaledSize(QSize(120,120));
    gif->setMovie(loader);
    tips->setText("载入中...");
    tips->move(0,120);
    tips->setFixedSize(120,20);
    tips->setAlignment(Qt::AlignCenter);
    tips->setStyleSheet("background-color:#252525;font-size:12px");
}

LoadingDialog::~LoadingDialog(){

}
void LoadingDialog::loading()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    loader->start();
    this->show();
    return;
}
void LoadingDialog::toggeleToForm(QString str){
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    this->sleep(5000);
    animation->setDuration(1000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    this->sleep(1000);
    loader->stop();
    this->hide();
    emit toForm(str);
}

void LoadingDialog::sleep(int msec)
{
QTime dieTime = QTime::currentTime().addMSecs(msec);
while( QTime::currentTime() < dieTime )
QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
