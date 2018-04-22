﻿#ifndef MYHTTP_H
#define MYHTTP_H

#include <QObject>
#include <chinese.h>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QDebug>
#include <QNetworkRequest>
#include <QUrl>
#include <Qdir>
#include <QRegExp>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QList>
#include <QTextCodec>


class MyHttp : public QObject
{
    Q_OBJECT
public:
    explicit MyHttp(QString);
    explicit MyHttp();
    ~MyHttp();
    MyHttp * SetUrl(QString);
    QString preg_Html(QString);
signals:
    void cert_got(QPixmap *);
    void login_suc(bool);
    void login_timeout();
    void login_error();
    void form_init_end(QString);
    void Form_XJKP_end(QString);
    void Form_CJCX_end(QString);
    void Form_XSKB_end(QString);
    void Form_HKSQ_end(QString);
public slots:
    void init();
    void replyHome(QNetworkReply *);
    void loginStart(QString *);
    void loginEnd(QNetworkReply *);
    void replyCert(QNetworkReply *);


    void init_name(QString);
    void Form_init();
    void Form_init_end(QNetworkReply*);
    void Form_XJKP_init(QNetworkReply*);
    void Form_HKSQ_init(QNetworkReply*);
    void Form_CJCX_init(QNetworkReply*);
    void Form_XSKB_init(QNetworkReply*);


private:
    QString Url;
    QString Name;
    QString Cookie;
    QString Login_str;
    QString Secure_str;
    QPixmap *Current_pix;
    QList<QNetworkCookie> Cookies;
    QNetworkAccessManager *manager;
    QNetworkCookieJar *Unlogin;
};

#endif // MYHTTP_H
