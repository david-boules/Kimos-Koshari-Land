#include "levelcompletedialog.h"

LevelCompleteDialog::LevelCompleteDialog(const QString& levelName, QWidget *parent) :QDialog(parent) {
    setWindowTitle("Level Complete!");
    setModal(true);                     // Blocks all input to other windows until it is closed
    setMinimumSize(350, 200);

    QLabel* congratsLabel = new QLabel("Congratulations! </h2><p>You completed the level: <b>" + levelName + "</b>!</p>");
    congratsLabel->setTextFormat(Qt::RichText); // So HTML tags are rendered properly
    congratsLabel->setAlignment(Qt::AlignCenter);

    QPushButton* replayButton = new QPushButton("Replay Level", this);
    QPushButton* nextLevelButton = new QPushButton("Next Level", this);
    QPushButton* levelSelectButton = new QPushButton("Level Select", this);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(congratsLabel);
    layout->addWidget(replayButton);
    layout->addWidget(nextLevelButton);
    layout->addWidget(levelSelectButton);
    setLayout(layout);

    // General Qt Syntax for 'connect:' connect(sender, signal, receiver, slot/signal);
    connect(replayButton, &QPushButton::clicked, this, &LevelCompleteDialog::replayPushed);
    connect(nextLevelButton, &QPushButton::clicked, this, &LevelCompleteDialog::nextLevelPushed);
    connect(levelSelectButton, &QPushButton::clicked, this, &LevelCompleteDialog::levelSelectPushed);
}
