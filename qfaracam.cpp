#include "qfaracam.h"
#include "ui_qfaracam.h"
#include <QMessageBox>
#include <QPalette>

#include <QtWidgets>
#include <QFileDialog>


QFaraCam::QFaraCam(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QFaraCam)
{
    ui->setupUi(this);
    //exitButton=new QPushButton("Exit",this);
   // startCapture=new QPushButton("Start Capture",this);
   // stopCapture=new QPushButton("Stop Capture",this);

    gview = new MyQGraphicsView(this);
    scene = new QGraphicsScene();
    gview->setNewScene(scene);
    ui->draw_container->addWidget(gview);
     //connect(ui->action_calibr, SIGNAL(triggered(bool)), this, SLOT(calibrateLength()));
     connect(ui->action_calibr,SIGNAL(triggered()), this, SLOT(calibrateLength()));

     connect(gview, SIGNAL(rValueChanged(float)), this, SLOT(updateRField(float)));
     connect(gview, SIGNAL(realRValueChanged(float)), this, SLOT(updateRealRField(float)));


     connect(ui->spin_r, SIGNAL(valueChanged(double)), this, SLOT(updateCoefField(double)));
     connect(ui->calibr_length, SIGNAL(valueChanged(double)), this, SLOT(updateCoefField(double)));
     connect(ui->action_live,SIGNAL(triggered()), this, SLOT(displayViewfinder()));
     connect(ui->action_measure,SIGNAL(triggered()), this, SLOT(measureLength()));
     connect(ui->actionSave,SIGNAL(triggered()), this, SLOT(saveImage()));
     connect(ui->actionOpen,SIGNAL(triggered()), this, SLOT(openImage()));

    video=new videowidget();
    video->show();

   // vbox=new QVBoxLayout(this);
   // vbox->addWidget(video);
    ui->videoBox->addWidget(video);
    //vbox->addWidget(startCapture);
   // vbox->addWidget(stopCapture);
  //  vbox->addWidget(exitButton);

    //setLayout(vbox);

    //resize(1024,768);

    t=new CaptureThread(video);
    //video->setGeometry(ui->viewfinderPage->geometry());
    onStartCapture();
    displayViewfinder();
   // gview->setScene(scene);

    //gview->setScene(scene);
    //ui->graphicsView->setScene(scene);
    setMode(3);


}


void QFaraCam::on_exit_clicked()
{
    qDebug("bye bye");
    exit(0);
}

void QFaraCam::onStartCapture()
{
    if(t->devam==false){
        t->devam=true;
        t->start();
    }
}
void QFaraCam::onStopCapture()
{
   t->devam=false;

}

QFaraCam::~QFaraCam()
{

    delete ui;
}

void QFaraCam::closeEvent(QCloseEvent *event)
{
    exit(0);
}


void QFaraCam::processCapturedImage(int requestId, const QImage& img)
{
    Q_UNUSED(requestId);


           // QImage scaledImage = ui->viewfinderPage->grab().toImage();// ->prevImg;//img.scaled(ui->videoBox->size(),
                                 //  Qt::KeepAspectRatio,
                                 //  Qt::SmoothTransformation);
   // scene->addPixmap(QPixmap::fromImage(scaledImage));
    //setSceneRect(0,0,scaledImage.width(),scaledImage.height());
    //gview->fitInView(gview->sceneRect(), Qt::KeepAspectRatioByExpanding);
    //ui->lastImagePreviewLabel->setPixmap(QPixmap::fromImage(scaledImage));
    //gview->setNewPixmap(QPixmap::fromImage(scaledImage));
    // Display captured image for 4 seconds.
    displayCapturedImage();
    //QTimer::singleShot(4000, this, SLOT(displayViewfinder()));
}

void QFaraCam::saveImage()
{
    QString fname = QFileDialog::getSaveFileName(this, tr("Save as..."),
                                                 QString(), tr("*.png"));

    QImageWriter writer(fname, "png");
    writer.setText("Calibr.", QString::number(ui->calibr_coef->value()));
    QImage image;
    QGraphicsTextItem * io = new QGraphicsTextItem();
    io->setPos(0,0);
    QString text;
    text.sprintf("L=%.3f mm", ui->real_len->value());
    io->setPlainText(text);
    io->setHtml("<div style='background-color:#ffffff;'>" + text + "</div>");
    scene->addItem(io);
    gview->toImage(image);
    //QPixmap pixMap = gview->grab();
    //        pixMap.save("a.png");

    writer.write(image);
}


void QFaraCam::openImage()
{
    QString fname = QFileDialog::getOpenFileName(this, tr("Save as..."),
                                                 QString(), tr("*.png"));

    QImageReader reader(fname);
    //writer.setText("Calibr.", QString::number(ui->calibr_coef->value()));
    QImage image;
    //QImage icon(64, 64, QImage::Format_RGB32);
    //QPixmap pixMap = gview->grab();
    //        pixMap.save("a.png");

    reader.read(&image);
    scene->addPixmap(QPixmap::fromImage(image));
    calibr_coef = (image.text().split(":")[1]).toDouble();
    ui->calibr_coef->setValue( calibr_coef);

    displayCapturedImage();
    gview->drawState(0);
    setMode(2);

}


void QFaraCam::displayViewfinder()
{    video->show();
    ui->stackedWidget->setCurrentIndex(0);
    setMode(3);
     onStartCapture();
}

void QFaraCam::displayCapturedImage()
{
    ui->stackedWidget->setCurrentIndex(1);

}


void QFaraCam::setMode(int mode)
{
    this->mod = mode;
    gview->setCameraMod(mode);
}

/////////////////////////////// calibr
void QFaraCam::calibrateLength()
{
gview->clv();
onStartCapture();
video->show();
onStopCapture();
//video->hide();
    this->takeImage();
 gview->drawState(0);
 setMode(0);

}


void QFaraCam::updateRField(float r)
{

ui->spin_r->setValue(gview->value());
}

void QFaraCam::updateRealRField(float r)
{
ui->real_len->setValue(1/ui->calibr_coef->value()*r);
}

void QFaraCam::updateCoefField(double val)
{
    double r = ui->spin_r->value();
    double l = ui->calibr_length->value();

    try{

        double res = r/l;
        if (res){
            calibr_coef = res;
            ui->calibr_coef->setValue(calibr_coef);
        }
    }
    catch(char *e)
       {
           printf("Exception Caught: %s\n",e);
       }


}


void QFaraCam::measureLength()
{
    setMode(1);
    gview->clv();
    //onStartCapture();

    displayViewfinder();
    onStopCapture();
    displayCapturedImage();
    //video->hide();
        this->takeImage();
     gview->drawState(0);

}


void QFaraCam::takeImage()
{
//gview->clv();
    QImage scaledImage = ui->viewfinderPage->grab().toImage();// ->prevImg;//img.scaled(ui->videoBox->size(),
                         //  Qt::KeepAspectRatio,
                         //  Qt::SmoothTransformation);
    scene->addPixmap(QPixmap::fromImage(scaledImage));
    gview->setScene(scene);
    ui->stackedWidget->setCurrentIndex(1);
    video->hide();
    //onStopCapture();
//setMode(1);
   // this->takeImage();
 //gview->drawState(0);
 //setMode(0);

}

void QFaraCam::imageSaved(int id, const QString &fileName)
{
    Q_UNUSED(id);
    Q_UNUSED(fileName);

    isCapturingImage = false;
    if (applicationExiting)
        close();
}
