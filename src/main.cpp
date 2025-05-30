#include <QApplication>
#include <QGraphicsView>
#include "levels/levelorchestrator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create View
    QGraphicsView view;
    view.setFixedSize(800, 600);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Instantiating the Level Orchestrator
    LevelOrchestrator orchestrator(&view);

    view.show();

    return a.exec();
}
