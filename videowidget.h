#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QPainter>

class videowidget : public QWidget
{
Q_OBJECT
public:
    explicit videowidget(QWidget *parent = 0);
    QImage img;
    QImage prevImg;

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

};

#endif // VIDEOWIDGET_H
