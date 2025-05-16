#ifndef LEVELORCHESTRATOR_H
#define LEVELORCHESTRATOR_H

#include <QObject>
#include <QGraphicsView>
#include "baselevel.h"
#include "kimo.h"

class LevelOrchestrator : public QObject
{
    Q_OBJECT

public:
    LevelOrchestrator(QGraphicsView* view, QWidget* parent = nullptr);
    enum Level {L1, L2, L3, L4, L5}; // Public so that the enum values can be accessed outside the class
    void loadLevel(Level level); // Sets up the level environment, objects, etc.
    void switchLevel();

private:
    QGraphicsView* view;
    QVector<QString> levelNames = {"Koshari Kitchen", "Streets of Cairo", "Pyramids Dash", "Abou Tarek's Castle", "Rooftop Showdown"};
    Kimo* kimo;
    QGraphicsTextItem* healthText; // To be carried over to next levels
    QGraphicsTextItem* levelText;
    BaseLevel* currentLevel;
};

#endif // LEVELORCHESTRATOR_H
