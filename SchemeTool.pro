QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/schemeinfowidget.cpp \
    src/schemeConvertor.cpp \
    src/schemepresetwidget.cpp \
    src/schemetreewidget.cpp

HEADERS += \
    mainwindow.h \
    src/schemeinfowidget.h \
    src/schemeConvertor.h \
    src/schemeDefine.h \
    src/schemepresetwidget.h \
    src/schemetreewidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
