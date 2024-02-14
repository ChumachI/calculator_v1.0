QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp\
    ../backend/calculate/calculate.c\
    ../backend/translate_to_rpn/_translate_to_rpn.c\
    ../backend/stack/_stack.c\
    ../backend/calculate_rpn/_calculate_rpn.c\
    ../backend/PL_stack/_PL_stack.c\
    qcustomplot.cpp

HEADERS += \
    mainwindow.h\
    qcustomplot.h\
    ../backend/backend.h

FORMS += \
    mainwindow.ui

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
