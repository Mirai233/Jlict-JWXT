#ifndef MYLABEL_H
#define MYLABEL_H
#include <QLabel>
#include <QMouseEvent>

class Mylabel : public QLabel
{
    Q_OBJECT
public:
    Mylabel(QWidget *);
    ~Mylabel();
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // MYLABEL_H
