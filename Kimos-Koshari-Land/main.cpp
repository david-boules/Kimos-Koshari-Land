#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <kimo.h>
#include <enemy.h>
#include <platform.h>
#include <move1.h>
#include <move2.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create Scene
    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 800, 600);

    // Create View
    QGraphicsView view;
    view.setFixedSize(800, 600);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Create Kimo Instance
    Kimo *kimo = new Kimo();
    kimo->setFlag(QGraphicsItem::ItemIsFocusable);
    kimo->setFocus();
    kimo->setPos(100, 400); // Starting position
    kimo->setPixmap(QPixmap (":/images/Kimo.png").scaled(64,64));
    scene.addItem(kimo);

    // Create Health Text
    QGraphicsTextItem* healthText = new QGraphicsTextItem("Health: 3");
    healthText->setDefaultTextColor(Qt::white);
    healthText->setFont(QFont("Arial", 16));
    healthText->setPos(700, 10);
    scene.addItem(healthText);
    kimo->setHealthText(healthText); // Links the Kimo instance with the health text so it can be updated

    //Create enemy
    move2* Chili = new move2(":/images/chili.png",QPointF(500,336));
    scene.addItem(Chili);
    Chili->setTargetKimo(kimo);

    Enemy* macaroni = new Enemy(":/images/macaroni.png",QPointF(364,236));
    scene.addItem(macaroni);
    macaroni->setTargetKimo(kimo);

    move1* onion = new move1(":/images/onion.png",QPointF(500,100));
    scene.addItem(onion);
    onion->setTargetKimo(kimo);

    // Create Platforms
    // Ground platform
    StaticPlatform *ground = new StaticPlatform(800, 50, 0, 550);
    scene.addItem(ground);

    // floating static plaforms
    StaticPlatform *platform1 = new StaticPlatform(160, 20, 100, 400);
    scene.addItem(platform1);

    StaticPlatform *platform2 = new StaticPlatform(160, 20, 300, 300);
    scene.addItem(platform2);

    // Moving platform (moves horizontally with range 200 and speed 2)
    MovingPlatform *platform3 = new MovingPlatform(160, 20, 400, 200, 200, 2);
    scene.addItem(platform3);

    // spikey platform
    SpikyPlatform *platform4 = new SpikyPlatform(160, 20, 200, 100);
    scene.addItem(platform4);

    view.setScene(&scene);
    view.setBackgroundBrush(Qt::blue);
    view.show();

    // Add a timer to update the moving platform so it moves
    QTimer *platformTimer = new QTimer();
    QObject::connect(platformTimer, &QTimer::timeout, [platform3]() {
        platform3->update();
    });
    platformTimer->start(16); // ~60 FPS

    return a.exec();
}
