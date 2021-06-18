QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

ENGINE_PATH = $$PWD/extern/PixelEngine
include($$ENGINE_PATH/PixelEngine.pri)

incPath = inc
srcPath = src

blocksInc = $$incPath/GameObject/Blocks
blocksSrc = $$srcPath/GameObject/Blocks

INCLUDEPATH += $$incPath \
               $$incPath/GameObject \
               $$blocksInc

SOURCES += \
        $$srcPath/main.cpp  \
        $$srcPath/GameObject/grass.cpp \
        $$srcPath/GameObject/player.cpp \
        $$blocksSrc/block.cpp \
        $$srcPath/level.cpp

HEADERS += \
        $$incPath/GameObject/grass.h \
        $$incPath/GameObject/player.h \
        $$blocksInc/block.h \
        $$incPath/level.h \
        $$incPath/GameObject/texturePaths.h \
        $$blocksInc/grassblock.h \
        $$blocksInc/dirtblock.h \
        $$blocksInc/sandblock.h \
        $$blocksInc/stoneblock.h \
        $$blocksInc/waterblock.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

