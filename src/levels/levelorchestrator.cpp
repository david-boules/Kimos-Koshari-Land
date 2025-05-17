#include "levelorchestrator.h"
#include "levelcompletedialog.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "level5.h"

LevelOrchestrator::LevelOrchestrator(QGraphicsView* view, QWidget* parent)
    : QObject(parent), view(view)
{
    kimo = new Kimo();
    healthText = new QGraphicsTextItem();
    levelText = new QGraphicsTextItem();
}

void LevelOrchestrator::loadLevel(Level level) {
    qDebug() << "[loadLevel] Entered with level:" << level;
    if (!kimo || !view || !healthText || !levelText) {
        qDebug() << "[ERROR] Null pointers found during loadLevel!";
    }
    switch (level) {
    case L1:
        currentLevel = new Level1(view, kimo, healthText, levelText);
        currentLevel->setupScene("Koshari Kitchen");
        connect(kimo, &Kimo::levelComplete, this, &LevelOrchestrator::onLevelComplete);
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
}

void LevelOrchestrator::onLevelComplete() {
    LevelCompleteDialog* LevelComplete = new LevelCompleteDialog(currentLevel->getLevelName());
    connect(LevelComplete, &LevelCompleteDialog::replayPushed, this, &LevelOrchestrator::reloadCurrenentLevel);
}

void LevelOrchestrator::switchLevel() {

}
