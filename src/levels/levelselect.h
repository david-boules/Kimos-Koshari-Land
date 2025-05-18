#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <QDialog>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "levelorchestrator.h"

class LevelSelect : public QDialog
{
    Q_OBJECT
public:
    explicit LevelSelect(LevelOrchestrator* orchestrator, QWidget *parent = nullptr);

private slots:
    void loadLevel(LevelOrchestrator::Level level);

private:
    LevelOrchestrator* orchestrator;
};

#endif // LEVELSELECT_H
