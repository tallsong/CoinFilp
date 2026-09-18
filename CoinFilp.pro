QT       += core gui widgets multimedia

CONFIG += c++17

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

# Qt releases before 6.5.3 link every GUI app against Apple's AGL framework,
# which no longer exists in the macOS 14+ SDK shipped with Xcode 15 and later
# ("framework 'AGL' not found"). Keep only the OpenGL framework.
macx {
    QMAKE_LIBS_OPENGL = -framework OpenGL
    QMAKE_INCDIR_OPENGL = /System/Library/Frameworks/OpenGL.framework/Headers
}
