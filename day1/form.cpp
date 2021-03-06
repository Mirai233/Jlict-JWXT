#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    pTitleBar = new TitleBar(this);
    pTitleBar->setObjectName("TitleBar");
    installEventFilter(pTitleBar);

    l_tab1 = new QHBoxLayout(this);
    l_tab2 = new QHBoxLayout(this);
    l_index = new QHBoxLayout(this);



    j = new Preg_Jlict();

    l_tab1->addWidget(ui->tableWidget);
    l_tab1 -> setSpacing(1);
    ui->tab_2->setLayout(l_tab1);

    l_tab2->addWidget(ui->tableWidget_2);
    l_tab2 -> setSpacing(1);
    ui->tab_3->setLayout(l_tab2);



    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();
    QPoint movePoint(deskWidth / 2 - 650, deskHeight / 2 - 310);
    this->move(movePoint);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->resizeColumnsToContents();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->verticalHeader()->setHidden(true);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(12, QHeaderView::ResizeToContents);
}

Form::~Form()
{
}

void Form::Start_Init(QString data){
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1800);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    menu_bar = new QMenuBar(this);
    menu1 = new QMenu(data,this);
    menu2 = new QMenu("数据",this);
    menu3 = new QMenu("更多功能",this);
    menu_bar->addMenu(menu1);
    menu_bar->addMenu(menu2);
    menu_bar->addMenu(menu3);
    act1 = new QAction("切换账号",this);
    act2 = new QAction("退出程序",this);
    act3 = new QAction("学分统计",this);
    act4 = new QAction("图片处理",this);
    act5 = new QAction("清除数据缓存",this);
    menu1->addAction(act1);
    menu1->addSeparator();
    menu1->addAction(act2);
    menu2->addAction(act3);
    menu3->addAction(act4);
    menu3->addAction(act5);
    act1->setDisabled(true);
    act1->setToolTip("本功能暂不可用");
    ui->verticalLayout->insertWidget(0,pTitleBar);
    QWidget * Qm = new QWidget(this);
    ui->verticalLayout->insertWidget(1,Qm);
    QVBoxLayout *Lm = new QVBoxLayout(this);
    Lm->setMenuBar(menu_bar);
    Qm->setLayout(Lm);


    connect(act2,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(act1,SIGNAL(triggered(bool)),this,SLOT(Change_user()));
    connect(act3,SIGNAL(triggered(bool)),this,SLOT(Show_Score()));
    connect(act4,SIGNAL(triggered(bool)),this,SLOT(more()));
    connect(act5,SIGNAL(triggered(bool)),this,SLOT(ClearCache()));
    this->setWindowTitle("教务系统 - " + data);
    if(File.compare("") == 0){
        QCryptographicHash hash(QCryptographicHash::RealSha3_512);
        hash.addData(data.toLocal8Bit());
        QByteArray result_byte_array = hash.result();
        QString Filename = result_byte_array.toHex();
        File = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JLICT/Caches/"+Filename+".dat";
    }
    return;
}
void Form::Form_XSKB_init(QString data){
    QList<QString> s = j->Xskb_preg(data);
    WriteCache(s);
    QList<QString>::iterator i;
    int col = 7,row = -1;
    for(i = s.begin()+15;i <= s.end()-9;i++){
        if(col < 7){
            QString cls =  i->section("<nobr>",1,1);
            QTableWidgetItem *item;
            QString str = "";
            if(cls.size()){
                QRegExp rx(">([\\S\\s]*)<br>([\\S\\s]*)<br>([\\S\\s]*)<br>([\\S\\s]*)<br>([\\S\\s]*)<a>");
                rx.setMinimal(true);
                if(int a = rx.indexIn(cls)){
                    for(int index = 1;index < a;index++){
                        if(rx.cap(index).size()){
                            str += rx.cap(index);
                            str += "\n";
                        }

                    }
                }
                item = new QTableWidgetItem(str);
            }else{
                item = new QTableWidgetItem("");
            }
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->tableWidget_2->setItem(row, col, item);
            col ++;
        }else{
            col = 0;
            row++;
        }

    }
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(2200);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    this->show();
    return;
}
void Form::Form_CJCX_init(QString data){
    QList<QString> s = j->Cjcx_preg(data);
    WriteCache(s);
    QList<QString>::iterator i;
    int col = 13,row = 0;

    for(i = s.begin()+27;i <= s.end()-3;i+=2){
        if(col < 13){
            QTableWidgetItem *item;
            if(QString::compare(*i,"<tr><tr>") == 0){
                item = new QTableWidgetItem ("");
            }else{
                item = new QTableWidgetItem (*i);
            }
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->tableWidget->setItem(row, col, item);
            col ++;
        }else{
            col = 0;
            row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            QTableWidgetItem *item;
            if(QString::compare(*i,"<tr><tr>") == 0){
                item = new QTableWidgetItem ("");
            }else{
                item = new QTableWidgetItem (*i);
            }
            item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->tableWidget->setItem(row, col, item);
            col ++;
        }
    }

    i = s.end()-2;
    QString str = *i;
    Score = "";
    str.replace("<span>"," ");
    str.replace("\"","");
    QRegExp rx("([\\S\\s]*)<spanid=lbzxf>([\\S\\s]*)<spanid=lbbxxf>([\\S\\s]*)<spanid=lblzyxxxf>([\\S\\s]*)<spanid=lblggxxxf>([\\S\\s]*)<spanid=lblpgxfjd>([\\S\\s]*)<br>([\\S\\s]*)<spanid=lbzxs>([\\S\\s]*)<spanid=lbkcms>([\\S\\s]*)<spanid=lbbjgms>([\\S\\s]*)$");
    rx.setMinimal(true);
    int r = rx.indexIn(str);
    if(r != -1){
        for(int index = 1;index <= 10;index++){
            Score += rx.cap(index);
        }
        WriteCache(Score);
    }
    return;
}


void Form::Change_user(){
    emit toggle_to_login();
    this->close();
}

void Form::Show_Score(void){
    QMessageBox::information(this, "成绩统计",Score);
    return;
}

void Form::more(){
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1800);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    this->sleep(1800);
    emit togglt_to_more();
    this->close();
    return;
}


void Form::sleep(qint32 msec)
{
QTime dieTime = QTime::currentTime().addMSecs(msec);
while( QTime::currentTime() < dieTime )
QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
return;
}


void Form::ReadCache(QString filename){
    QFile file(filename);
    if(file.open(QFile::ReadOnly)){
        QDataStream out(&file);
        qint32 flag;
        out.setVersion(QDataStream::Qt_5_10);
        QString data = "";
        out >> flag;
        out >> data;
        out >> flag;
        QList<QString> s;
        out >> s;
        out >> flag;
        QList<QString>::iterator i;
        int col = 13,row = 0;
        for(i = s.begin()+27;i <= s.end()-3;i+=2){
            if(col < 13){
                QTableWidgetItem *item;
                if(QString::compare(*i,"<tr><tr>") == 0){
                    item = new QTableWidgetItem ("");
                }else{
                    item = new QTableWidgetItem (*i);
                }
                item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                ui->tableWidget->setItem(row, col, item);
                col ++;
            }else{
                col = 0;
                row = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(row);
                QTableWidgetItem *item;
                if(QString::compare(*i,"<tr><tr>") == 0){
                    item = new QTableWidgetItem ("");
                }else{
                    item = new QTableWidgetItem (*i);
                }
                item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                ui->tableWidget->setItem(row, col, item);
                col ++;
            }
        }
        Score = "";
        out >> Score;
        out >> flag;
        out >> s;
        col = 7,row = -1;
        for(i = s.begin()+15;i <= s.end()-9;i++){
            if(col < 7){
                QString cls =  i->section("<nobr>",1,1);
                QTableWidgetItem *item;
                QString str = "";
                if(cls.size()){
                    QRegExp rx(">([\\S\\s]*)<br>([\\S\\s]*)<br>([\\S\\s]*)<br>([\\S\\s]*)<br>([\\S\\s]*)<a>");
                    rx.setMinimal(true);
                    if(int a = rx.indexIn(cls)){
                        for(int index = 1;index < a;index++){
                            if(rx.cap(index).size()){
                                str += rx.cap(index);
                                str += "\n";
                            }

                        }
                    }
                    item = new QTableWidgetItem(str);
                }else{
                    item = new QTableWidgetItem("");
                }
                item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                ui->tableWidget_2->setItem(row, col, item);
                col ++;
            }else{
                col = 0;
                row++;
            }

        }
        this->Start_Init(data);
        file.close();
    }
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(2200);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    this->show();
    return;
}

void Form::WriteCache(QList<QString> data){
    QFile file(File);
    if(file.open(QFile::Append)){
        QDataStream out(&file);
        qint32 flag = 0xC0C0C0C8;
        out.setVersion(QDataStream::Qt_5_10);
        out << data;
        out << flag;
        file.close();
    }
    return;
}

void Form::WriteCache(QString data){
    QFile file(File);
    if(file.open(QFile::Append)){
        QDataStream out(&file);
        qint32 flag = 0xC0C0C0C8;
        out.setVersion(QDataStream::Qt_5_10);
        out << data;
        out << flag;
        file.close();
    }
    return;
}


void Form::ClearCache(){
    QString folderFullPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JLICT/";
    QDir dir(folderFullPath);
    dir.setFilter(QDir::Files);
    int fileCount = dir.count();
    for (int i = 0; i < fileCount; i++)
    dir.remove(dir[i]);
    folderFullPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/JLICT/Caches/";
    QDir dir1(folderFullPath);
    dir1.setFilter(QDir::Files);
    fileCount = dir1.count();
    for (int i = 0; i < fileCount; i++)
    dir1.remove(dir1[i]);
    QMessageBox::information(this, "清除缓存","缓存已经完全删除，请重新启动程序后生效");
    return;
}
