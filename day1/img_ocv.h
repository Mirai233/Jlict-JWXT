#ifndef IMG_OCV_H
#define IMG_OCV_H

#include <QWidget>

namespace Ui {
class Img_OCV;
}

class Img_OCV : public QWidget
{
    Q_OBJECT

public:
    explicit Img_OCV(QWidget *parent = 0);
    ~Img_OCV();

private:
    Ui::Img_OCV *ui;
};

#endif // IMG_OCV_H
