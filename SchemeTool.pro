QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/modeldatawidget.cpp \
    src/schemeinfowidget.cpp \
    src/schemeConvertor.cpp \
    src/schemepresetwidget.cpp \
    src/schemetreewidget.cpp \
    src/statewidget.cpp

HEADERS += \
    mainwindow.h \
    src/modeldatawidget.h \
    src/schemeinfowidget.h \
    src/schemeConvertor.h \
    src/schememodeldefine.h \
    src/schemepresetwidget.h \
    src/schemetreewidget.h \
    src/statewidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

DISTFILES += \
    icons/icons8-minus-48.png \
    icons/icons8-plus-48.png \
    icons/icons8_Json4_Download.ico \
    icons/icons8_Json4_Download_16.png \
    icons/icons8_Json4_Download_32.png \
    icons/icons8_Json4_Download_48.png \
    icons/icons8_Json4_Download_64.png \
    icons/icons8_add_file.ico \
    icons/icons8_add_file_16.png \
    icons/icons8_add_file_32.png \
    icons/icons8_download.ico \
    icons/icons8_download_16.png \
    icons/icons8_download_32.png \
    icons/icons8_json2_download.ico \
    icons/icons8_json2_download_16.png \
    icons/icons8_json2_download_32.png \
    icons/icons8_json2_download_48.png \
    icons/icons8_json2_download_64.png \
    icons/icons8_json3_download_16.png \
    icons/icons8_json3_download_32.png \
    icons/icons8_json3_download_48.png \
    icons/icons8_json3_download_64.png \
    icons/icons8_json_download.ico \
    icons/icons8_json_download_16.png \
    icons/icons8_json_download_32.png \
    schemes/schemeModel.json
