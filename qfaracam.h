#ifndef QFARACAM_H
#define QFARACAM_H

#include "videowidget.h"
#include "capturethread.h"

#include <QMainWindow>
#include <QImageWriter>
#include <QImageReader>
#include <QGraphicsScene>
#include "myqgraphicsview.h"
namespace Ui {
class QFaraCam;
}

class QFaraCam : public QMainWindow
{
    Q_OBJECT

public:
    explicit QFaraCam(QWidget *parent = 0);
    ~QFaraCam();
    CaptureThread *t;
    videowidget *video;
private slots:
    /*void on_videoWidget_destroyed();*/
    void saveImage();
    void openImage();
   // void on_exit_clicked();
    void onStartCapture();
    void onStopCapture();
    void updateDevList();
    void updateCameraDevice(QAction *a);

    void imageSaved(int id, const QString &fileName);
    void calibrateLength();
    void measureLength();
    void updateRField(float);
    void updateRealRField(float);
    void updateCoefField(double);
    void displayViewfinder();
    void displayCapturedImage();
    void setMode(int mode);
    void takeImage();
    void processCapturedImage(int requestId, const QImage& img);
protected:
    void closeEvent(QCloseEvent *event);
private:
    int mod;
    Ui::QFaraCam *ui;
    bool isCapturingImage;
    bool applicationExiting;
    MyQGraphicsView *gview;
    QGraphicsScene *scene;
    double calibr_coef;
};

#endif // QFARACAM_H
