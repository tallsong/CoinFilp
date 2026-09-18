QT       += core gui widgets multimedia

CONFIG += c++20

TARGET = CoinFilp
VERSION = 1.1.0

# Release builds: full optimisation plus link-time optimisation.
CONFIG(release, debug|release): CONFIG += optimize_full ltcg

macx {
    # Build a native Apple Silicon binary. For a universal binary that also
    # runs on Intel Macs use: QMAKE_APPLE_DEVICE_ARCHS = arm64 x86_64
    QMAKE_APPLE_DEVICE_ARCHS = arm64

    # App bundle metadata (Info.plist placeholders are filled in by qmake).
    QMAKE_TARGET_BUNDLE_PREFIX = com.tallsong
    QMAKE_INFO_PLIST = $$PWD/Info.plist
    ICON = $$PWD/img/CoinFilp.icns

    # Qt 6.10 only claims support up to the macOS 26 SDK; building with the
    # Xcode 27 SDK works, so silence the version-check warning.
    CONFIG += sdk_no_version_check

    # Xcode 26+/27 clang on Apple Silicon: Qt's qyieldcpu.h calls __yield(),
    # which needs <arm_acle.h> to be declared first, otherwise the build fails
    # with "implicitly declaring library function '__yield'". See
    # qt_yield_fix.h.
    QMAKE_CXXFLAGS += -include $$PWD/qt_yield_fix.h
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chooselevelscene.cpp \
    menus.cpp \
    main.cpp \
    mainscene.cpp \
    mypushbutton.cpp \
    playscene.cpp \
    mycoin.cpp \
    dataconfig.cpp

HEADERS += \
    constants.h \
    menus.h \
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

DISTFILES += \
    Info.plist \
    img/CoinFilp.icns
