#ifndef LEVELORCHESTRATOR_H
#define LEVELORCHESTRATOR_H

#include <QObject>
#include <QGraphicsView>
#include "baselevel.h"
#include "levelcompletedialog.h"

class LevelOrchestrator : public QObject
{
    Q_OBJECT

public:
    LevelOrchestrator(QGraphicsView* view, QWidget* parent = nullptr);
    enum Level {L1, L2, L3, L4, L5}; // Public so that the enum values can be accessed outside the class
    void loadLevel(Level level); // Sets up the level environment, objects, etc.

    // Functions that emit 'pauseGame()' and 'resumeGame()' signals
    void pause();
    void resume();

public slots:
    void onLevelComplete();
    void reloadCurrentLevel();
    void switchLevel();
    void showLevelSelect();
    void exitGame();

signals:
    void pauseGame();
    void resumeGame();

private:
    QGraphicsView* view;
    LevelCompleteDialog* dialog = nullptr;
    BaseLevel* currentLevel = nullptr;
    Level currentLevelEnum;
};

#endif // LEVELORCHESTRATOR_H
