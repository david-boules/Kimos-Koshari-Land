#ifndef KOSHARITROPHY_H
#define KOSHARITROPHY_H

#include <QGraphicsPixmapItem>
#include <QObject>

class KoshariTrophy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit KoshariTrophy(QGraphicsItem *parent = nullptr);
};

#endif // KOSHARITROPHY_H
