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
    QPushButton* exitGameButton = new QPushButton("Exit Game", this);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(congratsLabel);
    layout->addWidget(replayButton);
    layout->addWidget(nextLevelButton);
    layout->addWidget(levelSelectButton);
    layout->addWidget(exitGameButton);
    setLayout(layout);

    // General Qt Syntax for 'connect:' connect(sender, signal, receiver, slot/signal);
    connect(replayButton, &QPushButton::clicked, this, [this]() {
        emit replayPushed();
        accept();
    });

    connect(nextLevelButton, &QPushButton::clicked, this, [this]() {
        emit nextLevelPushed();
        this->accept();
    });

    connect(levelSelectButton, &QPushButton::clicked, this, [this]() {
        emit levelSelectPushed();
        this->accept();
    });

    connect(exitGameButton, &QPushButton::clicked, this, [this]() {
        emit exitGamePushed();
        this->accept();
    });

}

void LevelCompleteDialog::closeEvent(QCloseEvent* event) {
    // Simply closing the dialog wihtout the app crashing or quitting
    accept();
    QDialog::closeEvent(event);  // This passes control to a default handler
}
