#include "levelselect.h"
#include <QObject>

LevelSelect::LevelSelect(LevelOrchestrator* orch, QWidget *parent)
    : QDialog(parent), orchestrator(orch)
{
    setWindowTitle("Select Level");
    setFixedSize(300, 300);

    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* title = new QLabel("Choose a Level", this);
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    // Push Buttons for each level
    QPushButton* level1Btn = new QPushButton("Level 1", this);
    QPushButton* level2Btn = new QPushButton("Level 2", this);
    QPushButton* level3Btn = new QPushButton("Level 3", this);
    QPushButton* level4Btn = new QPushButton("Level 4", this);
    QPushButton* level5Btn = new QPushButton("Level 5", this);

    layout->addWidget(level1Btn);
    layout->addWidget(level2Btn);
    layout->addWidget(level3Btn);
    layout->addWidget(level4Btn);
    layout->addWidget(level5Btn);

    connect(level1Btn, &QPushButton::clicked, this, [=]() {
        orchestrator->loadLevel(LevelOrchestrator::L1);
        accept();
    });
    connect(level2Btn, &QPushButton::clicked, this, [=]() {
        orchestrator->loadLevel(LevelOrchestrator::L2);
        accept();
    });
    connect(level3Btn, &QPushButton::clicked, this, [=]() {
        orchestrator->loadLevel(LevelOrchestrator::L3);
        accept();
    });
    connect(level4Btn, &QPushButton::clicked, this, [=]() {
        orchestrator->loadLevel(LevelOrchestrator::L4);
        accept();
    });
    connect(level5Btn, &QPushButton::clicked, this, [=]() {
        orchestrator->loadLevel(LevelOrchestrator::L5);
        accept();
    });
}

void LevelSelect::loadLevel(LevelOrchestrator::Level level) {
    this->close();
    orchestrator->loadLevel(level);
}
