#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <kimo.h>
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

    // Create Kimo Instance
    Kimo *kimo = new Kimo();
    kimo->setFlag(QGraphicsItem::ItemIsFocusable);
    kimo->setFocus();
    kimo->setPos(0,500-60);
    scene.addItem(kimo);

    // Create Platform
    Platform *platform = new Platform();
    platform->setPos(0,500);
    scene.addItem(platform);

    view.setScene(&scene);
    view.setBackgroundBrush(Qt::blue);
    view.show();

    return a.exec();
}
