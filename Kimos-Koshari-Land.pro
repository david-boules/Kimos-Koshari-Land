QT       += core gui widgets

CONFIG   += c++17
TEMPLATE = app
TARGET   = KimosKoshariLand

INCLUDEPATH += src \
               src/kimo \
               src/enemies \
               src/projectiles \
               src/movement \
               src/environment \

DEPENDPATH  += src

SOURCES += \
    src/main.cpp \
    src/kimo/kimo.cpp \
    src/enemies/enemy.cpp \
    src/movement/chili.cpp \
    src/movement/macaroni.cpp \
    src/movement/onion.cpp \
    src/projectiles/fireball.cpp \
    src/projectiles/macaronimissile.cpp \
    src/environment/platform.cpp \
    src/projectiles/projectile.cpp

HEADERS += \
    src/kimo/kimo.h \
    src/enemies/enemy.h \
    src/movement/chili.h \
    src/movement/macaroni.h \
    src/movement/onion.h \
    src/projectiles/fireball.h \
    src/projectiles/macaronimissile.h \
    src/environment/platform.h \
    src/projectiles/projectile.h

RESOURCES += src/resources.qrc

FORMS +=
