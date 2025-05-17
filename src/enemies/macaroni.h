#ifndef MACARONI_H
#define MACARONI_H

#include "enemy.h"

enum class macaroni_move { level1, level2,level2_1, level3, level4 };


class macaroni : public Enemy {
    Q_OBJECT

public:
    macaroni(QPixmap path, QPointF startingPos, QGraphicsItem* parent = nullptr);
    void setMoveStyle(macaroni_move style);
    macaroni_move getMoveStyle() const;

private slots:
    void move() override; // Implement the pure virtual function
    //level2


private:

 macaroni_move moveStyle= macaroni_move::level1;
};



#endif // MACARONI_H
