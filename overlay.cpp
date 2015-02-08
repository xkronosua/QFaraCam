#include "overlay.h"
#include <QPainter>
#include <QPen>
#include <QToolTip>
#include <QtCore/qmath.h>

Overlay::Overlay(QWidget *parent) :QWidget(parent) {
    setPalette(Qt::transparent);
    setAutoFillBackground(false);
    setAttribute(Qt::WA_TransparentForMouseEvents);

    startPos = QPoint();
    endPos = QPoint();
    inDrawing = -1;
    calibr_coef = 0;
    r_value = 0;
    setMouseTracking(true);
}

void Overlay::setValue(float value)
{
    if (value != r_value) {
        r_value = value;
        emit this->valueChanged(value);
    }
}
/*
void Overlay::valueChanged(float){
    //return r_value;
}*/


void Overlay::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(4);

    p.setPen(pen);

    drawLines(&p);
   // painter.setPen(QPen(Qt::red));
   // painter.drawLine(width()/8, height()/8, 7*width()/8, 7*height()/8);
    //painter.drawLine(width()/8, 7*height()/8, 7*width()/8, height()/8);
}

void Overlay::drawState(int state)
{
    inDrawing = state;
}

void Overlay::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (inDrawing >= 0)
        {
            startPos = event->pos();
            inDrawing = 1;
        }
        else if(inDrawing == 1)
        {
            endPos = event->pos();

            //QLine line = QLine(startPos, event->pos());
            //lines.append(line);
            inDrawing = -1;
        }

        //inDrawing = !inDrawing;
    }
}

void Overlay::mouseReleaseEvent(QMouseEvent *event)
{

    endPos = event->pos();
        update();
        inDrawing = -1;
}

void Overlay::mouseMoveEvent(QMouseEvent *event)
{
    if (inDrawing == 1)
    {
        endPos = event->pos();
        update();
        r_value = qSqrt(qPow(startPos.x()-endPos.x(), 2) + qPow(startPos.y()-endPos.y(), 2 ));
        this->setValue(r_value);

    }
    QToolTip::showText(event->globalPos(),
                           //  In most scenarios you will have to change these for
                           //  the coordinate system you are working in.
                           QString::number( event->pos().x() ) + ", " +
                           QString::number( event->pos().y() ) + " : " +
                           QString::number( r_value ),
                           this, rect() );
        QWidget::mouseMoveEvent(event);

}

void Overlay::drawLines(QPainter *p)
{
    if (!startPos.isNull() && startPos.x() && startPos.y() && !endPos.isNull())
    {
        p->drawLine(startPos, endPos);
    }

    //p->drawLines(lines);
}
/*
void Overlay::paintEvent(QPaintEvent *event)
{
    QPainter p(overlay);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(4);

    p.setPen(pen);

    drawLines(&p);
}
*/
