QT       += core gui widgets multimedia

CONFIG += c++20

# Xcode 26+/27 clang on Apple Silicon: Qt's qyieldcpu.h calls __yield(), which
# needs <arm_acle.h> to be declared first, otherwise the build fails with
# "implicitly declaring library function '__yield'". See qt_yield_fix.h.
macx: QMAKE_CXXFLAGS += -include $$PWD/qt_yield_fix.h

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chooselevelscene.cpp \
    main.cpp \
    mainscene.cpp \
    mypushbutton.cpp \
    playscene.cpp \
    mycoin.cpp \
    dataconfig.cpp

HEADERS += \
    constants.h \
    qt_yield_fix.h \
    chooselevelscene.h \
    mainscene.h \
    mypushbutton.h \
    playscene.h \
    mycoin.h \
    dataconfig.h

FORMS += \
    mainscene.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
