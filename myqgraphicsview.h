#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H



#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QToolTip>
#include <QGraphicsEllipseItem>
#include <QMouseEvent>
#include <QPaintEvent>
//#include "scene.h"

class MyQGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyQGraphicsView(QWidget *parent = 0);
    void setNewPixmap(QPixmap);
    void drawState(int state) {inDrawing = state;};
    void setCameraMod(int mod){camMod = mod;};
    float value() const {return r_value;}
    void clv();




public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    //void keyPressEvent(QKeyEvent *event);
    //void paintEvent(QPaintEvent *event);
public slots:

    void setRValue(float value);
    void setRealRValue(float value);

signals:
    void rValueChanged(float);
    void realRValueChanged(float);
private:
    //void drawLines(QPainter *p);
    QGraphicsScene* scene;
    QPointF origPoint;
    QGraphicsLineItem* lineDraw;
    QLineF line;
    QPointF startPos;
    QPointF endPos;
    int inDrawing;
    int camMod;

    float r_value;
    float real_r_value;
    double calibr_coef;

    //QLineF ;//line(10, 20, 300,300);

protected:



};

#endif // MYQGRAPHICSVIEW_H
