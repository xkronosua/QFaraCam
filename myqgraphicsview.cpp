#include "myqgraphicsview.h"
#include <QPointF>
#include <QtMath>



MyQGraphicsView::MyQGraphicsView(QWidget *parent) :
        QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    this->setSceneRect(0, 0, this->size().width(),this->size().height());
    this->setScene(scene);
    inDrawing = -1;
    lineDraw = 0;
    camMod = 0;

}

void MyQGraphicsView::setNewPixmap(QPixmap p)
{
    QBrush brush = QBrush(Qt::red, p);
scene->setBackgroundBrush(brush);
}



void MyQGraphicsView::mousePressEvent(QMouseEvent * e)
{



    if (inDrawing >=0){
        QPen *pen1, *pen2;
        if (camMod == 0){
            pen1 = new QPen(Qt::red);
            pen2 = new QPen(Qt::blue);
        }

        else if (camMod == 1){
            pen1 = new QPen(Qt::green);
            pen2 = new QPen(Qt::yellow);
        }
    double rad = 5;
    QPointF pt = mapToScene(e->pos());
    scene->addEllipse(pt.x()-rad, pt.y()-rad, rad*2.0, rad*2.0,
        *pen1, QBrush(Qt::transparent));

    if (inDrawing == 0) {
        startPos = pt;
        inDrawing = 1;
    }
    else {
        endPos = pt;
        inDrawing = -1;

        scene->addLine(startPos.x(),startPos.y(),endPos.x(),endPos.y(),*pen2);
        update();

        float val = qSqrt(qPow(startPos.x()-endPos.x(), 2) + qPow(startPos.y()-endPos.y(), 2 ));
        if (camMod == 0)
        {
        setRValue(val);

        }
        else if (camMod == 1){
            setRealRValue(val);
            inDrawing = 0;
        }
    }
    }


}



void MyQGraphicsView::mouseMoveEvent(QMouseEvent * e)
{
    double rad = 5;
    QPointF pt = mapToScene(e->pos());
    if (inDrawing == 0)
    {
        endPos = pt;

        float val = qSqrt(qPow(startPos.x()-endPos.x(), 2) + qPow(startPos.y()-endPos.y(), 2 ));
        setRValue(val);
       // QLine line(startPos.x(), startPos.y(),pt.x(),pt.y());
        //lineDraw->setLine(line);
    }
    update();
    QToolTip::showText(e->globalPos(),
                           //  In most scenarios you will have to change these for
                           //  the coordinate system you are working in.
                           QString::number( e->pos().x() ) + ", " +
                           QString::number( e->pos().y() ) + " : " +
                           QString::number( r_value ) +"|" + QString::number( inDrawing ),
                           this, rect() );
  //QWidget::mouseMoveEvent(e);


}



void MyQGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{

}



void MyQGraphicsView::setRValue(float value)
{

    if (value != r_value) {
        r_value = value;
        emit this->rValueChanged(r_value);
    }

}

void MyQGraphicsView::setRealRValue(float value)
{

    if (value != real_r_value) {
        real_r_value = value;
        emit this->realRValueChanged(real_r_value);
    }

}



void MyQGraphicsView::clv()
{
    scene->clear();
}


