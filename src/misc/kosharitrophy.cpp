#include "kosharitrophy.h"
#include <QPixmap>

KoshariTrophy::KoshariTrophy(QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent)
{
    QPixmap trophy(":/images/misc/koshari_trophy.png");
    setPixmap(trophy.scaled(64, 64));
}
