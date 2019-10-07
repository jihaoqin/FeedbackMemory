#-------------------------------------------------
#
# Project created by QtCreator 2019-09-17T16:58:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FeedbackMeomory
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Data.cpp \
    Notebook.cpp \
    Note.cpp \
    NoteListWidget.cpp \
    MetaWidget.cpp \
    ListModel.cpp \
    NoteModel.cpp \
    NoteWidget.cpp \
    AddDialog.cpp \
    ListDialog.cpp \
    TestIniDialog.cpp \
    TestDialog.cpp \
    TestWidget.cpp \
    TestData.cpp \
    TestResultWidget.cpp \
    SelfknownButton.cpp

HEADERS += \
        mainwindow.h \
    Data.h \
    UsingName.h \
    Notebook.h \
    Note.h \
    NoteListWidget.h \
    MetaWidget.h \
    ListModel.h \
    NoteModel.h \
    NoteWidget.h \
    AddDialog.h \
    ListDialog.h \
    TestIniDialog.h \
    TestDialog.h \
    TestWidget.h \
    TestData.h \
    TestResultWidget.h \
    SelfknownButton.h

FORMS +=
INCLUDEPATH += $$PWD/3rdparty/includes

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
