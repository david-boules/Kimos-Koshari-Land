#include "levelorchestrator.h"
#include "levelcompletedialog.h"
#include "levelselect.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "level5.h"
#include "kimo.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QApplication>

LevelOrchestrator::LevelOrchestrator(QGraphicsView* view, QWidget* parent)
    : QObject(parent), view(view)
{
    loadLevel(L4);
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
        currentLevel = new Level1(view, kimo, healthText, levelText, this);
        currentLevel->setupScene("Koshari Kitchen");
        break;

    case L2:
        currentLevel = new Level2(view, kimo, healthText, levelText, this);
        currentLevel->setupScene("Pyramids Dash");
        break;

    case L3:
        currentLevel = new Level3(view, kimo, healthText, levelText, this);
        currentLevel->setupScene("Streets of Cairo");
        break;

    case L4:
        currentLevel = new Level4(view, kimo, healthText, levelText, this);
        currentLevel->setupScene("Abou Tarek's Castle");
        break;

    case L5:
        currentLevel = new Level5(view, kimo, healthText, levelText, this);
        currentLevel->setupScene("Rooftop Showdown");
        break;
    }

    view->setScene(currentLevel);
    // Connect pause/resume signals to all scene items
    for (QGraphicsItem* item : currentLevel->items()) {
        QObject* obj = dynamic_cast<QObject*>(item); // cast to QObject to check for active objects
        if (!obj) continue;

        const QMetaObject* meta = obj->metaObject(); // 'meta object' contains metadata about each class, checking if an object has a 'pause' function to connect these at runtime
        if (meta->indexOfSlot("pause()") != -1)
            connect(this, SIGNAL(pauseGame()), obj, SLOT(pause()));
        if (meta->indexOfSlot("resume()") != -1)
            connect(this, SIGNAL(resumeGame()), obj, SLOT(resume()));
    }
    connect(this, &LevelOrchestrator::pauseGame, kimo, &Kimo::pause);
    connect(this, &LevelOrchestrator::resumeGame, kimo, &Kimo::resume);
    connect(kimo, &Kimo::levelComplete, this, &LevelOrchestrator::onLevelComplete);
    // Connect store open/close to global pause/resume
    connect(currentLevel, &BaseLevel::storeOpened, this, &LevelOrchestrator::pause);
    connect(currentLevel, &BaseLevel::storeClosed, this, &LevelOrchestrator::resume);
}

void LevelOrchestrator::onLevelComplete() {

    // Victory Jingle:
    currentLevel->stopMusic();
    QMediaPlayer* lvlCompletePlayer = new QMediaPlayer(this);
    QAudioOutput* lvlCompleteOutput = new QAudioOutput(this);
    lvlCompletePlayer->setAudioOutput(lvlCompleteOutput);
    lvlCompletePlayer->setSource(QUrl("qrc:/audio/lvlcomplete.mp3"));
    lvlCompletePlayer->play();

    // Display a 'Level Complete' dialog
    QString levelName = currentLevel->getLevelName()->toPlainText().remove("Level: ");
    LevelCompleteDialog LevelComplete(levelName);

    // Singals / Slots for all options on the level complete dialog
    connect(&LevelComplete, &LevelCompleteDialog::replayPushed, this, &LevelOrchestrator::reloadCurrentLevel);
    connect(&LevelComplete, &LevelCompleteDialog::nextLevelPushed, this, [=]() {
        QTimer::singleShot(0, this, &LevelOrchestrator::switchLevel);   // Ensures 'switchLevel' which triggers 'loadLevel' runs after the current dialog fully closes, preventing 'delete currentLevel' from accessing invalid memory
    });
    connect(&LevelComplete, &LevelCompleteDialog::levelSelectPushed, this, &LevelOrchestrator::showLevelSelect);
    connect(&LevelComplete, &LevelCompleteDialog::exitGamePushed, this, &LevelOrchestrator::exitGame);

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
    LevelSelect ls(this);
    ls.exec();
}

void LevelOrchestrator::pause() {
    emit pauseGame();
}

void LevelOrchestrator::resume() {
    emit resumeGame();
}

void LevelOrchestrator::exitGame() {
    QApplication::quit();
}
