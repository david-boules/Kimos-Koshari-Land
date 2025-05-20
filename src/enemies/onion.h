#ifndef ONION_H
#define ONION_H
#include "enemy.h"
#include "poison.h"
#include <QtMath>
#include <QElapsedTimer>

enum class onion_move { level1, level2,level2_1,level3, level3_1, level3_2, level4 };

class onion : public Enemy {
    Q_OBJECT
public:
    onion(QString path, QPointF startingPos, QGraphicsItem* parent = nullptr); //for one image

    onion(QString right_image, QString left_image, QPointF startingPos, QGraphicsItem* parent = nullptr);//for two images
    void move() override;

    void setBounds(qreal min, qreal max){
        minX=min;
        maxX=max;



    }






public:
    void setMoveStyle(onion_move style);
    onion_move getMoveStyle() const;
    void shoot_poison();
    QTimer* shootTimer;
    qreal jump = 0.0;
    qreal original_y = 0.0;
    bool is_jumping = false;




private:
    qreal angle = 0.0;
    qreal speed;
    qreal damage;
    int enemy_health=1;
    qreal minX = 0;
    qreal maxX = 800;
    onion_move moveStyle = onion_move::level1;
 QElapsedTimer poisonCooldown;


    QPixmap leftPixmap;
   QPixmap rightPixmap;
    bool has_left_and_right = false;


};
#endif // ONION_H
