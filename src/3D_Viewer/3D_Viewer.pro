QT       += core gui openglwidgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../affine.c \
    ../parser.c \
    gif/giflib/dgif_lib.c \
    gif/giflib/egif_lib.c \
    gif/giflib/gif_err.c \
    gif/giflib/gif_font.c \
    gif/giflib/gif_hash.c \
    gif/giflib/gifalloc.c \
    gif/giflib/quantize.c \
    gif/qgifimage.cpp \
    glview.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../affine.h \
    ../parser.h \
    ../struct.h \
    gif/giflib/gif_hash.h \
    gif/giflib/gif_lib.h \
    gif/giflib/gif_lib_private.h \
    gif/qgifglobal.h \
    gif/qgifimage.h \
    gif/qgifimage_p.h \
    glview.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    gif/gifimage.pro

DISTFILES += \
    gif/giflib/AUTHORS \
    gif/giflib/COPYING \
    gif/giflib/README
