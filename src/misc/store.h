#ifndef STORE_H
#define STORE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QKeyEvent>
#include "kimo.h"

class Store : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit Store(QGraphicsView *view, Kimo *kimo, QObject *parent = nullptr);
    void show();
    void hide();
    bool purchaseItem(int index);

signals:
    void storeClosed();

public slots:
    void updateStoreButtons(const QString &abilityName, int remainingTime);

private slots:
    void purchaseFireball();
    void purchaseDoubleJump();
    void purchaseShield();
    void closeStore();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QGraphicsView *view;
    Kimo *kimo;
    QGraphicsRectItem *background;
    QGraphicsTextItem *title;
    QGraphicsTextItem *coinDisplay;
    QPushButton *closeButton;

    // Store items
    struct StoreItem
    {
        QString name;
        int cost;
        QString description;
        QGraphicsTextItem *nameText;
        QGraphicsTextItem *costText;
        QGraphicsTextItem *descText;
        QPushButton *buyButton;
    };

    QList<StoreItem> items;

    void setupItems();
    void updateCoinDisplay();
    bool canAfford(int cost) const;
    void updateButtonStates();
    bool hasActiveAbility;
};

#endif // STORE_H
