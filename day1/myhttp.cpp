#include <myhttp.h>

MyHttp::MyHttp(QString url = "") : QObject()
{
    Url = url;
    manager = new QNetworkAccessManager(this);
}
MyHttp::MyHttp() : QObject()
{
    manager = new QNetworkAccessManager(this);
}

MyHttp::~MyHttp()
{
    delete manager;

}


void MyHttp::init(void){
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyHome(QNetworkReply*)));
    QNetworkRequest* Request1 = new QNetworkRequest(QUrl("http://api.keep-it.cn/jlict/index.php/"));
    manager->get(*Request1);
    return;
}

void MyHttp::replyHome(QNetworkReply *reply)
{
    QObject::disconnect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyHome(QNetworkReply*)));
    if(reply->error() == QNetworkReply::NoError)
    {
        Secure_str = reply->readAll();
        QRegExp rx("cookie=ASP.NET_SessionId=([\\s\\S]*)");
        if(rx.indexIn(Secure_str)){
            Cookie = rx.cap(1);
            Secure_str.replace("cookie=ASP.NET_SessionId="+Cookie,"");
            QNetworkCookie new_cookie("ASP.NET_SessionId=",Cookie.toUtf8());
            Cookies.append(new_cookie);
            Unlogin = new QNetworkCookieJar(manager);
            //QString target = "HTTP://210.47.10.163";
            Unlogin->setCookiesFromUrl(Cookies,QUrl("http://210.47.10.163/"));
            manager->setCookieJar(Unlogin);
        }
        QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyCert(QNetworkReply*)));
        QNetworkRequest* Request1 = new QNetworkRequest(QUrl("http://210.47.10.163/other/CheckCode.aspx?datetime=az"));
        manager->get(*Request1);
    }else{
        emit login_timeout();
    }
    return;
}

void MyHttp::replyCert(QNetworkReply *reply){
    QObject::disconnect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyCert(QNetworkReply*)));
    if(reply->error() == QNetworkReply::NoError)
    {
    //获取字节流构造 QPixmap 对象
    Current_pix = new QPixmap();
    Current_pix->loadFromData(reply->readAll());
    //QString filename = QDir::tempPath()+"/Xcode.jpg";
    //currentPicture->save(filename);//保存图片
    emit cert_got(Current_pix);
    }
    return;
}

void MyHttp::loginStart(QString * data){
    Login_str = Secure_str + *data;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(loginEnd(QNetworkReply*)));
    QNetworkRequest* Request1 = new QNetworkRequest(QUrl("http://210.47.10.163/login.aspx"));
    Request1->setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QByteArray postData;
    postData.clear();
    postData.append(Login_str);
    //Request1->setHeader(QNetworkRequest::ContentLengthHeader,postData.size ());
    manager->post(*Request1,postData);
    return;
}


void MyHttp::loginEnd(QNetworkReply *data){
    QObject::disconnect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(loginEnd(QNetworkReply*)));
    if(data->error() == QNetworkReply::NoError)
    {
        if(data->hasRawHeader("Set-Cookie")){
            QString tmp_str =  data->rawHeader("Set-Cookie");
            QRegExp rx(".ASPXAUTH=([a-zA-Z0-9]*);([\\s\\S]*)");
            if(rx.indexIn(tmp_str) != -1){
                tmp_str = rx.cap(1);
                QNetworkCookie new_cookie(".ASPXAUTH=",tmp_str.toUtf8());
                Cookies.append(new_cookie);
                Unlogin->setCookiesFromUrl(Cookies,QUrl("http://210.47.10.163/"));
                manager->setCookieJar(Unlogin);
            }
            Form_init();
            emit login_suc(false);
        }else{
            emit login_error();
        }
    }else{
        emit login_timeout();
    }
    return;

}

void MyHttp::Form_init(){
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(Form_init_end(QNetworkReply*)));
    QNetworkRequest* Request1 = new QNetworkRequest(QUrl("http://210.47.10.163/JWXS/Default2.aspx"));
    manager->get(*Request1);
    return;
}


void MyHttp::Form_init_end(QNetworkReply* data){
    QObject::disconnect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(Form_init_end(QNetworkReply*)));
    if(data->error() == QNetworkReply::NoError)
    {
         QString instr =QString::fromLocal8Bit(data->readAll());
         //qDebug() <<instr;
         QRegExp rx("<spanid=\"users\">([\\s\\S]*)<span>");
         rx.setMinimal(true);
         instr = preg_Html(instr);
         if(rx.indexIn(instr) != -1){
             if(!Check_caches(rx.cap(1))){
                 QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(Form_CJCX_init(QNetworkReply*)));
                 QString str = "http://210.47.10.163/JWXS/cjcx/jwxs_cjcx_like.aspx?usermain="+Name;
                 QNetworkRequest* Request1 = new QNetworkRequest(QUrl(str));
                 manager->get(*Request1);
             }
         }else{
            emit form_init_error();
         }

    }else{
        emit form_init_error();
    }
    return;
}


MyHttp * MyHttp::SetUrl(QString url = ""){
    Url = url ;
    return this;
    //http://210.47.10.163/JWXS/cjcx/jwxs_cjcx_like.aspx?usermain=1410665119
    //http://210.47.10.163/JWXS/Default2.aspx
    //http://210.47.10.163/JWXS/pkgl/XsKB_List.aspx?usermain=1410665119
    //HKSQ/JWXS_HKSQ_LIST.aspx?usermain=1410665119
    //http://210.47.10.163/JWXS/xskp/jwxs_xskp_like.aspx?usermain=1410665119
    //http://jlhg.tiandihengye.com:90/m/html/login.html
}

void MyHttp::init_name(QString name){
    Name = name;
    return;
}

QString MyHttp::preg_Html(QString html = ""){
    html.replace("\r","");
    html.replace("\n","");
    html.replace("\t","");
    html.replace("/","");
    //data.replace("\"","");
    html.replace("&nbsp;","");
    html.replace(" ","");
    return html;
}




void MyHttp::Form_CJCX_init(QNetworkReply * reply){
    disconnect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(Form_CJCX_init(QNetworkReply*)));
    if(reply->error() == QNetworkReply::NoError){
        QString tmp = preg_Html(QString::fromLocal8Bit(reply->readAll()));
        emit Form_CJCX_end(tmp);
        QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(Form_XSKB_init(QNetworkReply*)));
        QString str = "http://210.47.10.163/JWXS/pkgl/XsKB_List.aspx?usermain="+Name;
        QNetworkRequest* Request1 = new QNetworkRequest(QUrl(str));
        manager->get(*Request1);
    }
    return;
}

void MyHttp::Form_XSKB_init(QNetworkReply * reply){
    disconnect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(Form_XSKB_init(QNetworkReply*)));
    if(reply->error() == QNetworkReply::NoError){
        QString tmp = preg_Html(QString::fromLocal8Bit(reply->readAll()));
        emit Form_XSKB_end(tmp);

    }
    return;
}


bool MyHttp::Check_caches(QString name){
    realname = name;
    bool ret = false;
    QCryptographicHash hash(QCryptographicHash::RealSha3_512);
    hash.addData(name.toLocal8Bit());
    QByteArray result_byte_array = hash.result();
    QString Filename = result_byte_array.toHex();
    QString user_dir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QDir dir(user_dir+"/JLICT/Caches");
    if(!dir.exists()){
        dir.mkdir(user_dir+"/JLICT/Caches");
    }
    QString fileFullName = user_dir+"/JLICT/Caches/"+Filename+".dat";
    QFileInfo fileInfo(fileFullName);
        if(fileInfo.isFile())
        {
            if(QDateTime::currentDateTime().daysTo(fileInfo.created()) <= -7){
                QFile file(fileFullName);
                if(file.open(QFile::WriteOnly)){
                    QDataStream out(&file);
                    qint32 flag = 0xC0C0C0C8;
                    out.setVersion(QDataStream::Qt_5_10);
                    out << flag;
                    out << name;
                    out << flag;
                    file.close();
                }
                ret = false;
                emit form_init_end(name);
            }else{
                emit form_init_end("");
                emit Form_Cache_Right(fileFullName);
                ret = true;
            }
        }else{
            QFile file(fileFullName);
            if(file.open(QFile::WriteOnly)){
                QDataStream out(&file);
                qint32 flag = 0xC0C0C0C8;
                out.setVersion(QDataStream::Qt_5_10);
                out << flag;
                out << name;
                out << flag;
                file.close();
            }
            ret = false;
            emit form_init_end(name);
        }
    return ret;
}
