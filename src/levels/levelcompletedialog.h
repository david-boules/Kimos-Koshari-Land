#ifndef LEVELCOMPLETEDIALOG_H
#define LEVELCOMPLETEDIALOG_H

#include <QDialog>
#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class LevelCompleteDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LevelCompleteDialog(const QString& levelName, QWidget* parent = nullptr);

protected:
    void closeEvent(QCloseEvent* event) override;

signals:
    void replayPushed();
    void nextLevelPushed();
    void levelSelectPushed();

};

#endif // LEVELCOMPLETEDIALOG_H
