QT       += core gui network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    fileinfo.cpp \
    main.cpp \
    mainwindow.cpp \
    settings.cpp \
    threshold.cpp

HEADERS += \
    about.h \
    fileinfo.h \
    label.h \
    mainwindow.h \
    settings.h \
    threshold.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

TRANSLATIONS += \
    i18n/daruma_en.ts \
    i18n/daruma_ja.ts \
    i18n/daruma_ru.ts \
    i18n/daruma_fr.ts \
    i18n/daruma_ko.ts \
    i18n/daruma_de.ts \
    i18n/daruma_es.ts \
    i18n/daruma_zh_TW.ts \
    i18n/daruma_zh_CN.ts \

RC_ICONS = favicon.ico
