QT       += core gui network printsupport multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    adjustment.cpp \
    brightness.cpp \
    camera.cpp \
    contrast.cpp \
    fileinfo.cpp \
    hue.cpp \
    label.cpp \
    main.cpp \
    mainwindow.cpp \
    saturation.cpp \
    settings.cpp \
    threshold.cpp \
    warmth.cpp

HEADERS += \
    about.h \
    adjustment.h \
    brightness.h \
    camera.h \
    contrast.h \
    fileinfo.h \
    hue.h \
    label.h \
    mainwindow.h \
    saturation.h \
    settings.h \
    threshold.h \
    warmth.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

TRANSLATIONS += $$files(i18n/daruma_*.ts)

RC_ICONS = favicon.ico
