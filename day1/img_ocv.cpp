#include "img_ocv.h"
#include "ui_img_ocv.h"

Img_OCV::Img_OCV(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Img_OCV)
{
    ui->setupUi(this);
}

Img_OCV::~Img_OCV()
{
    delete ui;
}
