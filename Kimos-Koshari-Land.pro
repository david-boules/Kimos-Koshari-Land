QT       += core gui widgets multimedia multimediawidgets

CONFIG   += c++17
TEMPLATE = app
TARGET   = KimosKoshariLand

INCLUDEPATH += src \
               src/kimo \
               src/enemies \
               src/projectiles \
               src/environment \
               src/misc \

DEPENDPATH  += src

SOURCES += \
    src/enemies/cat.cpp \
    src/levels/baselevel.cpp \
    src/levels/level1.cpp \
    src/levels/level2.cpp \
    src/levels/level3.cpp \
    src/levels/level4.cpp \
    src/levels/level5.cpp \
    src/levels/levelcompletedialog.cpp \
    src/levels/levelorchestrator.cpp \
    src/levels/levelselect.cpp \
    src/main.cpp \
    src/kimo/kimo.cpp \
    src/enemies/enemy.cpp \
    src/enemies/chili.cpp \
    src/enemies/macaroni.cpp \
    src/enemies/onion.cpp \
    src/misc/coin.cpp \
    src/misc/fallinglaundry.cpp \
    src/misc/kosharitrophy.cpp \
    src/misc/store.cpp \
    src/projectiles/fireball.cpp \
    src/projectiles/macaronimissile.cpp \
    src/environment/platform.cpp \
    src/projectiles/poison.cpp \
    src/projectiles/projectile.cpp

HEADERS += \
    src/enemies/cat.h \
    src/levels/baselevel.h \
    src/kimo/kimo.h \
    src/enemies/enemy.h \
    src/enemies/chili.h \
    src/enemies/macaroni.h \
    src/enemies/onion.h \
    src/levels/level1.h \
    src/levels/level2.h \
    src/levels/level3.h \
    src/levels/level4.h \
    src/levels/level5.h \
    src/levels/levelcompletedialog.h \
    src/levels/levelorchestrator.h \
    src/levels/levelselect.h \
    src/misc/coin.h \
    src/misc/fallinglaundry.h \
    src/misc/kosharitrophy.h \
    src/misc/store.h \
    src/projectiles/fireball.h \
    src/projectiles/macaronimissile.h \
    src/environment/platform.h \
    src/projectiles/poison.h \
    src/projectiles/projectile.h

RESOURCES += src/resources.qrc

FORMS +=
