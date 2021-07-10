QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


#CONFIG+=BUILD_WITH_EASY_PROFILER

include(../PixelEngine/PixelEngine.pri)
#include($$PWD/extern/PixelEngine.pri)

incPath = inc
srcPath = src

blocksInc = $$incPath/GameObject/Blocks
blocksSrc = $$srcPath/GameObject/Blocks

animalsInc = $$incPath/GameObject/Animals
animalsSrc = $$srcPath/GameObject/Animals

plantsInc  = $$incPath/GameObject/Plants
plantsSrc  = $$srcPath/GameObject/Plants

INCLUDEPATH += $$incPath \
               $$incPath/GameObject \
               $$blocksInc \
               $$animalsInc \
               $$plantsInc

SOURCES += \
        $$srcPath/main.cpp  \
        $$plantsSrc/grass.cpp \
        $$srcPath/GameObject/player.cpp \
        $$blocksSrc/block.cpp \
        $$srcPath/level.cpp \
        $$animalsSrc/sheep.cpp

HEADERS += \
        $$plantsInc/grass.h \
        $$incPath/GameObject/player.h \
        $$blocksInc/block.h \
        $$incPath/level.h \
        $$incPath/GameObject/texturePaths.h \
        $$blocksInc/grassblock.h \
        $$blocksInc/dirtblock.h \
        $$blocksInc/sandblock.h \
        $$blocksInc/stoneblock.h \
        $$blocksInc/waterblock.h \
        $$animalsInc/sheep.h \
        inc/GameObject/Plants/flower.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

