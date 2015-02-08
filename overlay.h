#ifndef OVERLAY_H
#define OVERLAY_H

#include <QWidget>
//#include <QObject>
#include <QPaintEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class Overlay; }
QT_END_NAMESPACE

class Overlay : public QWidget
{
     Q_OBJECT
public:
    explicit Overlay(QWidget *parent = 0);
    void drawState(int);
    float value() const {return r_value;}
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


public slots:
    void setValue(float value);

signals:
    void valueChanged(float);
private:

    void drawLines(QPainter *p);

    QPoint startPos;
    QPoint endPos;
    int inDrawing;

    QVector<QLine> lines;
    float r_value;
    double calibr_coef;

};

#endif // OVERLAY_H
