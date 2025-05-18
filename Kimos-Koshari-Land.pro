QT       += core gui widgets

CONFIG   += c++17
TEMPLATE = app
TARGET   = KimosKoshariLand

INCLUDEPATH += src \
               src/kimo \
               src/enemies \
               src/projectiles \
               src/environment \

DEPENDPATH  += src

SOURCES += \
    src/levels/baselevel.cpp \
    src/levels/level1.cpp \
    src/levels/level2.cpp \
    src/levels/level3.cpp \
    src/levels/level4.cpp \
    src/levels/level5.cpp \
    src/levels/levelcompletedialog.cpp \
    src/levels/levelorchestrator.cpp \
    src/main.cpp \
    src/kimo/kimo.cpp \
    src/enemies/enemy.cpp \
    src/enemies/chili.cpp \
    src/enemies/macaroni.cpp \
    src/enemies/onion.cpp \
    src/projectiles/fireball.cpp \
    src/projectiles/macaronimissile.cpp \
    src/environment/platform.cpp \
    src/projectiles/projectile.cpp

HEADERS += \
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
    src/projectiles/fireball.h \
    src/projectiles/macaronimissile.h \
    src/environment/platform.h \
    src/projectiles/projectile.h

RESOURCES += src/resources.qrc

FORMS +=
