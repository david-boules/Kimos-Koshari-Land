#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <kimo.h>
#include <QTimer>

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
    kimo->setPos(0,100);
    scene.addItem(kimo);

    view.setScene(&scene);
    view.show();

    return a.exec();
}
