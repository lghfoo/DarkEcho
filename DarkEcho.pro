QT += gui widgets

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canvas.cpp \
    footprint.cpp \
    game.cpp \
    main.cpp \
    monster.cpp \
    world.cpp \
    buttons/basebutton.cpp \
    buttons/buttonline.cpp \
    buttons/levelbutton.cpp \
    buttons/pixmapbutton.cpp \
    buttons/textbutton.cpp \
    scenes/basescene.cpp \
    scenes/choicescene.cpp \
    scenes/gamescene.cpp \
    scenes/levelscene.cpp \
    scenes/showscene.cpp \
    walls/bezierwall.cpp \
    walls/linewall.cpp \
    walls/wall.cpp \
    waves/basewave.cpp \
    waves/castwave.cpp \
    waves/customwave.cpp \
    waves/normalwave.cpp \
    waves/reflectwave.cpp \
    waves/soundwave.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

HEADERS += \
    allheader.h \
    canvas.h \
    footprint.h \
    game.h \
    monster.h \
    world.h \
    buttons/basebutton.h \
    buttons/buttonline.h \
    buttons/levelbutton.h \
    buttons/pixmapbutton.h \
    buttons/textbutton.h \
    scenes/basescene.h \
    scenes/choicescene.h \
    scenes/gamescene.h \
    scenes/levelscene.h \
    scenes/showscene.h \
    walls/bezierwall.h \
    walls/linewall.h \
    walls/wall.h \
    waves/basewave.h \
    waves/castwave.h \
    waves/customwave.h \
    waves/normalwave.h \
    waves/reflectwave.h \
    waves/soundwave.h
