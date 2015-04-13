#include "myqgraphicsview.h"
#include <QPointF>
#include <QtMath>



MyQGraphicsView::MyQGraphicsView(QWidget *parent) :
        QGraphicsView(parent)
{
    //scene = new QGraphicsScene();
    //this->setSceneRect(0, 0, this->size().width(),this->size().height());
    //this->setScene(scene);
    inDrawing = -1;
    lineDraw = 0;
    camMod = 0;
}

void MyQGraphicsView::setNewPixmap(QPixmap p)
{
    QBrush brush = QBrush(Qt::red, p);
    scene->setBackgroundBrush(brush);
}

void MyQGraphicsView::setNewScene(QGraphicsScene *s)
{
    scene = s;
    this->setScene(scene);
}

void MyQGraphicsView::mousePressEvent(QMouseEvent * e)
{


    if (inDrawing >=0){
        QPen *pen1, *pen2;
        if (camMod == 0){
            pen1 = new QPen(Qt::red);
            pen2 = new QPen(Qt::blue);

        }

        else if (camMod >= 1){
            pen1 = new QPen(Qt::green);
            pen2 = new QPen(Qt::yellow);
        }
    double rad = 2;
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
            inDrawing = -1;
            //QGraphicsTextItem * io = new QGraphicsTextItem();
            //io->setPos(0,0);
            //QString text;
            //text.sprintf("L=%.3f mm", real_r_value/calibr_coef);
            //io->setPlainText(text);
            //io->setHtml("<div style='background-color:#ffffff;'>" + text + "</div>");
            //scene->addItem(io);
            //scene->addItem(text);

        }
        else if (camMod == 2){
            setRealRValue(val);
            inDrawing = 0;
            //QGraphicsTextItem * io = new QGraphicsTextItem();
            //io->setPos(0,0);
            //QString text;
            //text.sprintf("L=%.3f mm", real_r_value/calibr_coef);
            //io->setPlainText(text);
            //io->setHtml("<div style='background-color:#ffffff;'>" + text + "</div>");
            //scene->addItem(io);
            //scene->addItem(text);

        }
    }
    }


}



void MyQGraphicsView::mouseMoveEvent(QMouseEvent * e)
{
    //double rad = 5;
    //QPointF pt = mapToScene(e->pos());
   /* if (inDrawing == 0)
    {
        endPos = pt;

        float val = qSqrt(qPow(startPos.x()-endPos.x(), 2) + qPow(startPos.y()-endPos.y(), 2 ));
        setRValue(val);

        //scene->update(startPos.x(), startPos.y(),abs(pt.x()-startPos.x()),abs(pt.y()-startPos.y()));
        //lineDraw->setLine(line);
    }
    //line.setLine(startPos.x(), startPos.y(),pt.x(),pt.y());*/
    update();

    QToolTip::showText(e->globalPos(),
                           //  In most scenarios you will have to change these for
                           //  the coordinate system you are working in.
                           QString::number( e->pos().x() ) + ", " +
                           QString::number( e->pos().y() ) + " : ",
                           this, rect() );
  //QWidget::mouseMoveEvent(e);

}

void MyQGraphicsView::mouseReleaseEvent(QMouseEvent *e)
{/*
    if (inDrawing >=0){
        QPen *pen1, *pen2;

            pen1 = new QPen(Qt::green);
            pen2 = new QPen(Qt::yellow);

    double rad = 2;
    QPointF pt = mapToScene(e->pos());
    scene->addEllipse(pt.x()-rad, pt.y()-rad, rad*2.0, rad*2.0,
        *pen1, QBrush(Qt::transparent));


        endPos = pt;
        inDrawing = -1;

        scene->addLine(startPos.x(),startPos.y(),endPos.x(),endPos.y(),*pen2);
        update();

        float val = qSqrt(qPow(startPos.x()-endPos.x(), 2) + qPow(startPos.y()-endPos.y(), 2 ));


            setRealRValue(val);
            inDrawing = 0;
            QGraphicsTextItem text(QString("L=%.3f mm").arg(val));
            text.transform().rotate(45);
            scene->addItem(&text);



    }*/
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

void MyQGraphicsView::toImage(QImage &image)
{



    scene->clearSelection();                                                  // Selections would also render to the file
    scene->setSceneRect(scene->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
    QImage *im = new QImage(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
    im->fill(Qt::transparent);                                              // Start all pixels transparent

    QPainter painter(im);
    scene->render(&painter);
    image = *im;
    //image.save("file_name.png");
}
