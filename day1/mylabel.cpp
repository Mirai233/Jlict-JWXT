#include "mylabel.h"
Mylabel::Mylabel(QWidget* parent = Q_NULLPTR)
    :QLabel(parent)
{

}
Mylabel::~Mylabel(){

}
void Mylabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}
