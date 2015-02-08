TEMPLATE = app
TARGET = camera
QT += core gui
QT += multimedia
QT += multimedia multimediawidgets

HEADERS = \
    camera.h \
    imagesettings.h \
    overlay.h

SOURCES = \
    main.cpp \
    camera.cpp \
    imagesettings.cpp \
    overlay.cpp

FORMS += \
    camera.ui \
    imagesettings.ui

#target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/camera
INSTALLS += target

QT+=widgets
