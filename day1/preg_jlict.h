#ifndef PREG_JLICT_H
#define PREG_JLICT_H
#include <chinese.h>
#include <QList>
#include <QDebug>
#include <QtXml>
#include <QRegExp>

class Preg_Jlict
{
public:
    Preg_Jlict();
    ~Preg_Jlict();
    QList<QString> Cjcx_preg(QString);
    QList<QString> Xskb_preg(QString);

};

#endif // PREG_JLICT_H
