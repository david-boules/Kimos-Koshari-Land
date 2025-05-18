#include "levelorchestrator.h"
#include "levelcompletedialog.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "level5.h"
#include "kimo.h"

LevelOrchestrator::LevelOrchestrator(QGraphicsView* view, QWidget* parent)
    : QObject(parent), view(view)
{
    loadLevel(L1);
}

void LevelOrchestrator::loadLevel(Level level) {
    currentLevelEnum = level;
    view->setScene(nullptr);
    // Check for an existing 'currentLevel' pointer when loading a level and delete this object
    if (currentLevel) {
        if (auto kimo = currentLevel->BaseLevel::getKimo())
            disconnect(kimo, nullptr, this, nullptr);
        delete currentLevel;
        currentLevel = nullptr;
    }

    QGraphicsTextItem* healthText = new QGraphicsTextItem();
    QGraphicsTextItem* levelText = new QGraphicsTextItem();
    Kimo* kimo = new Kimo(); // Creating the new Kimo to be used in the new level

    switch (level) {
    case L1:
        currentLevel = new Level1(view, kimo, healthText, levelText);
        currentLevel->setupScene("Koshari Kitchen");
        break;

    case L2:
        currentLevel = new Level2(view, kimo, healthText, levelText);
        currentLevel->setupScene("Streets of Cairo");
        break;

    case L3:
        currentLevel = new Level3(view, kimo, healthText, levelText);
        currentLevel->setupScene("Pyramids Dash");
        break;

    case L4:
        currentLevel = new Level4(view, kimo, healthText, levelText);
        currentLevel->setupScene("Abou Tarek's Castle");
        break;

    case L5:
        currentLevel = new Level5(view, kimo, healthText, levelText);
        currentLevel->setupScene("Rooftop Showdown");
        break;
    }

    view->setScene(currentLevel);
    connect(kimo, &Kimo::levelComplete, this, &LevelOrchestrator::onLevelComplete);
}

void LevelOrchestrator::onLevelComplete() {

    QString levelName = currentLevel->getLevelName()->toPlainText().remove("Level: ");
    LevelCompleteDialog LevelComplete(levelName);

    connect(&LevelComplete, &LevelCompleteDialog::replayPushed, this, &LevelOrchestrator::reloadCurrentLevel);
    connect(&LevelComplete, &LevelCompleteDialog::nextLevelPushed, this, &LevelOrchestrator::switchLevel);
    connect(&LevelComplete, &LevelCompleteDialog::levelSelectPushed, this, &LevelOrchestrator::showLevelSelect);

    LevelComplete.exec();
}


void LevelOrchestrator::switchLevel() {
    int next = static_cast<int>(currentLevelEnum) + 1;
    if (next < 5) loadLevel(static_cast<Level>(next));
    else {
        QGraphicsTextItem* winText = new QGraphicsTextItem("You have defeated Abou Tarek and completed the game!");
        winText->setDefaultTextColor(Qt::yellow);
        winText->setFont(QFont("Arial", 32));
        winText->setPos(600, 300);
        currentLevel->addItem(winText);
    }
}

void LevelOrchestrator::reloadCurrentLevel() {
    loadLevel(currentLevelEnum);
}

void LevelOrchestrator::showLevelSelect() {
    // To-Do: Level Select screen is not yet defined
}
