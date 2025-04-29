#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <kimo.h>
#include <enemy.h>
#include <platform.h>

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
    scene.addItem(kimo);

    //create enemy
    Enemy* enemy = new Enemy();
    scene.addItem(enemy);
    enemy->setPos(500, 336);
    enemy->setTargetKimo(kimo);

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
