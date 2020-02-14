#-------------------------------------------------
# Cours de Réalité Virtuelle
# leo.donati@univ-cotedazur.fr
#
# EPU 2019-20
#
# TP n°3
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    rvairplane.cpp \
    rvbody.cpp \
    rvcamera.cpp \
    rvcurve.cpp \
    rvdice.cpp \
    rvhelix.cpp \
    rvlight.cpp \
    rvmesh.cpp \
    rvmodel.cpp \
    rvplane.cpp \
    rvscene.cpp \
    rvskybox.cpp \
    rvsphere.cpp \
    rvsphericalcamera.cpp \
    rvstereocamera.cpp \
    rvsurface.cpp \
    rvtexcube.cpp \
    rvtorus.cpp \
    rvwidget.cpp

HEADERS += \
    mainwindow.h \
    rvairplane.h \
    rvbody.h \
    rvcamera.h \
    rvcurve.h \
    rvdice.h \
    rvhelix.h \
    rvlight.h \
    rvmesh.h \
    rvmodel.h \
    rvplane.h \
    rvscene.h \
    rvskybox.h \
    rvsphere.h \
    rvsphericalcamera.h \
    rvstereocamera.h \
    rvsurface.h \
    rvtexcube.h \
    rvtorus.h \
    rvwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    FS_plan.fsh \
    FS_simple.fsh \
    VS_simple.vsh \
    VS_simple_texture.vsh \
    VS_simpler.vsh

RESOURCES += \
    RVResources.qrc

FORMS += \
    mainwindow.ui

windows:LIBS += -lopengl32

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../assimp-5.0.0/lib/release/ -lassimp-vc141-mtd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../assimp-5.0.0/lib/debug/ -lassimp-vc141-mtd

INCLUDEPATH += $$PWD/../assimp-5.0.0/include
DEPENDPATH += $$PWD/../assimp-5.0.0/include
