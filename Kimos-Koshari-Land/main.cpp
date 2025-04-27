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
    Platform *ground = new Platform(800, 50, 0, 550);
    scene.addItem(ground);

    // Floating platforms
    Platform *platform1 = new Platform(150, 20, 100, 400);
    scene.addItem(platform1);

    Platform *platform2 = new Platform(150, 20, 300, 300);
    scene.addItem(platform2);

    Platform *platform3 = new Platform(150, 20, 500, 200);
    scene.addItem(platform3);

    Platform *platform4 = new Platform(150, 20, 200, 100);
    scene.addItem(platform4);

    view.setScene(&scene);
    view.setBackgroundBrush(Qt::blue);
    view.show();

    return a.exec();
}
