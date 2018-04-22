#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <chinese.h>
#include <mainwindow.h>
#include <myhttp.h>
#include <QDebug>
#include <QFile>
#include <QFontDatabase>
#include <form.h>
#include <loadingdialog.h>



int main(int argc,char **argv){
    QApplication a(argc,argv);

    /**
     * @brief file
     * 读取QSS样式文件
     *
     */
    QFile file(":/Style");
    if(file.open(QFile::ReadOnly)){
        a.setStyleSheet(file.readAll());
        file.close();
    }



    /**
     * @brief index
     * 读取TTF字体文件
     *
     */
    int index = QFontDatabase::addApplicationFont(":/MyFont");
        if(index != -1) {
            QStringList fontList(QFontDatabase::applicationFontFamilies(index));

            /* font -- LiHei Pro */
            if(fontList.count() > 0) {
                QFont font_zh(fontList.at(0));
                font_zh.setBold(false);
                font_zh.setLetterSpacing(QFont::AbsoluteSpacing,1);
                a.setFont(font_zh);
            }
        }


    /**
     * @brief mainW
     * 实例化并显示登录窗口
     * 开始应用程序
     *
     */
    mainWindow mainW;
    Form *form1 = new Form();

    mainW.show();
    MyHttp *http1 = new MyHttp();

    LoadingDialog *load = new LoadingDialog(Q_NULLPTR);
    /**
     * @brief img_url
     * 登录窗口的初始化验证码等操作
     *
     */
    QString img_url("http://210.47.10.163/other/CheckCode.aspx?datetime=az");
    http1->SetUrl(img_url)->init();

    /**
     * @brief QObject::connect
     * 事件绑定
     */
    QObject::connect(http1,SIGNAL(cert_got(QPixmap *)),&mainW,SLOT(flash_img(QPixmap *)));
    QObject::connect(&mainW,SIGNAL(StartLogin(QString*)),http1,SLOT(loginStart(QString*)));
    QObject::connect(http1,SIGNAL(login_suc(bool)),&mainW,SLOT(Cls(bool)));
    QObject::connect(&mainW,SIGNAL(Refresh()),http1,SLOT(init()));
    QObject::connect(http1,SIGNAL(login_error()),&mainW,SLOT(Login_Error()));
    QObject::connect(http1,SIGNAL(login_timeout()),&mainW,SLOT(Login_Timeout()));
    QObject::connect(&mainW,SIGNAL(SetName(QString)),http1,SLOT(init_name(QString)));
    QObject::connect(&mainW,SIGNAL(Toggle()),load,SLOT(loading()));
    QObject::connect(http1,SIGNAL(form_init_end(QString)),load,SLOT(toggeleToForm(QString)));
    QObject::connect(load,SIGNAL(toForm(QString)),form1,SLOT(Start_Init(QString)));
    QObject::connect(http1,SIGNAL(Form_XJKP_end(QString)),form1,SLOT(Form_XJKP_init(QString)));
    QObject::connect(http1,SIGNAL(Form_HKSQ_end(QString)),form1,SLOT(Form_HKSQ_init(QString)));
    QObject::connect(http1,SIGNAL(Form_CJCX_end(QString)),form1,SLOT(Form_CJCX_init(QString)));
    QObject::connect(http1,SIGNAL(Form_XSKB_end(QString)),form1,SLOT(Form_XSKB_init(QString)));
    QObject::connect(form1,SIGNAL(toggle_to_login()),&mainW,SLOT(show()));
    //QObject::connect(&form1,SIGNAL(destroyed(QObject*)),&mainW,SLOT(close()));


    return a.exec();
}

