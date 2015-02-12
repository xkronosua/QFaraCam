TEMPLATE = app
TARGET = camera

QT += multimedia multimediawidgets

HEADERS = \
    camera.h \
    imagesettings.h \
    myqgraphicsview.h \
    #scene.h

SOURCES = \
    main.cpp \
    camera.cpp \
    imagesettings.cpp \
    myqgraphicsview.cpp \
   # scene.cpp

FORMS += \
    camera.ui \
    videosettings.ui \
    imagesettings.ui

target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/camera
INSTALLS += target

QT+=widgets
