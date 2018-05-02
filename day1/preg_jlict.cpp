#include "preg_jlict.h"


Preg_Jlict::Preg_Jlict()
{
return;
}

Preg_Jlict::~Preg_Jlict(){
}


QList<QString> Preg_Jlict::Cjcx_preg(QString data){
    QList<QString> rs;
    QRegExp rx("<tr><td>([\\S\\s]+)<tr>");
    if(rx.indexIn(data) != -1){
        data = rx.cap(0)  ;
    }
    rs = data.split("<td>");
    return rs;
}




QList<QString> Preg_Jlict::Xskb_preg(QString data){
    QList<QString> rs;
    QRegExp rx("<tr><td>([\\S\\s]+)<tr>");
    if(rx.indexIn(data) != -1){
        data = rx.cap(0)  ;
    }
    rs = data.split("<td>",QString::SkipEmptyParts);
    return rs;
}
