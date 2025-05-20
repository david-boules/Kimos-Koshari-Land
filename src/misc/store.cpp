#include "store.h"
#include <QFont>
#include <QGraphicsProxyWidget>

Store::Store(QGraphicsView *view, Kimo *kimo, QObject *parent)
    : view(view), kimo(kimo), hasActiveAbility(false)
{
    connect(kimo, &Kimo::coinsChanged, this, &Store::updateCoinDisplay);

    // Create background
    background = new QGraphicsRectItem(0, 0, 800, 600);
    background->setBrush(QColor(0, 0, 0, 200));
    background->setParentItem(this);

    // Create title
    title = new QGraphicsTextItem("Store");
    title->setFont(QFont("Arial", 24, QFont::Bold));
    title->setDefaultTextColor(Qt::white);
    title->setPos(350, 50);
    title->setParentItem(this);

    // Create coin display
    coinDisplay = new QGraphicsTextItem();
    coinDisplay->setFont(QFont("Arial", 16));
    coinDisplay->setDefaultTextColor(Qt::yellow);
    coinDisplay->setPos(20, 20);
    coinDisplay->setParentItem(this);

    // Create close button
    closeButton = new QPushButton("Close");
    closeButton->setFixedSize(80, 30);
    if (view && view->scene()) {
        QGraphicsProxyWidget *closeProxy = view->scene()->addWidget(closeButton);
        closeProxy->setPos(700, 20);
    } else {
        qWarning() << "ERROR: view or scene not initialized yet!";
    }
    connect(closeButton, &QPushButton::clicked, this, &Store::closeStore);

    // Connect ability countdown signal
    connect(kimo, &Kimo::abilityCountdownChanged, this, &Store::updateStoreButtons, Qt::QueuedConnection);

    setupItems();
}

void Store::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_S)
    {
        closeStore();
    }
}

void Store::setupItems()
{
    // Define store items
    items = {
        {"Fireball", 3, "Shoot fireballs at enemies", nullptr, nullptr, nullptr, nullptr},
        {"Double Jump", 2, "Jump twice in mid-air", nullptr, nullptr, nullptr, nullptr},
        {"Shield", 3, "Temporary invincibility", nullptr, nullptr, nullptr, nullptr}};

    // Create UI elements for each item
    int yPos = 150;
    for (int i = 0; i < items.size(); ++i)
    {
        StoreItem &item = items[i];

        // Item name
        item.nameText = new QGraphicsTextItem(item.name);
        item.nameText->setFont(QFont("Arial", 18, QFont::Bold));
        item.nameText->setDefaultTextColor(Qt::white);
        item.nameText->setPos(100, yPos);
        item.nameText->setParentItem(this);

        // Item cost
        item.costText = new QGraphicsTextItem(QString::number(item.cost) + " coins");
        item.costText->setFont(QFont("Arial", 14));
        item.costText->setDefaultTextColor(Qt::yellow);
        item.costText->setPos(100, yPos + 30);
        item.costText->setParentItem(this);

        // Item description
        item.descText = new QGraphicsTextItem(item.description);
        item.descText->setFont(QFont("Arial", 12));
        item.descText->setDefaultTextColor(Qt::lightGray);
        item.descText->setPos(100, yPos + 60);
        item.descText->setParentItem(this);

        // Buy button
        QPushButton *buyButton = new QPushButton("Buy");
        buyButton->setFixedSize(80, 30);
        QGraphicsProxyWidget *proxy = view->scene()->addWidget(buyButton);
        proxy->setParentItem(this);
        proxy->setPos(600, yPos + 20);
        item.buyButton = buyButton;

        // Connect button to purchase function
        switch (i)
        {
        case 0:
            connect(buyButton, &QPushButton::clicked, this, &Store::purchaseFireball);
            break;
        case 1:
            connect(buyButton, &QPushButton::clicked, this, &Store::purchaseDoubleJump);
            break;
        case 2:
            connect(buyButton, &QPushButton::clicked, this, &Store::purchaseShield);
            break;
        }

        yPos += 150;
    }
}

void Store::show()
{
    this->setVisible(true);
    updateCoinDisplay();
}

void Store::hide()
{
    this->setVisible(false);
}

void Store::updateCoinDisplay()
{
    coinDisplay->setPlainText(QString("Coins: %1").arg(kimo->getCoins()));
}

bool Store::canAfford(int cost) const
{
    return kimo->getCoins() >= cost;
}

bool Store::purchaseItem(int index)
{
    if (hasActiveAbility)
    {
        return false;
    }

    if (index >= 0 && index < items.size() && canAfford(items[index].cost))
    {
        kimo->addCoins(-items[index].cost);
        updateCoinDisplay();
        return true;
    }
    return false;
}

void Store::purchaseFireball()
{
    if (purchaseItem(0))
    {
        // Grant fireball ability
        kimo->grantFireball();
    }
}

void Store::purchaseDoubleJump()
{
    if (purchaseItem(1))
    {
        // Grant double jump ability
        kimo->grantDoubleJump();
    }
}

void Store::purchaseShield()
{
    if (purchaseItem(2))
    {
        // Grant shield ability
        kimo->grantShield();
    }
}

void Store::closeStore()
{
    hide();
    emit storeClosed();
}

void Store::updateStoreButtons(const QString &abilityName, int remainingTime)
{
    hasActiveAbility = remainingTime > 0;
    updateButtonStates();
}

void Store::updateButtonStates()
{
    if (hasActiveAbility)
    {
        // Disable all buttons and update their text
        for (StoreItem &item : items)
        {
            item.buyButton->setEnabled(false);
            item.buyButton->setText("Ability in use");
        }
    }
    else
    {
        // Re-enable buttons and restore their original text
        for (StoreItem &item : items)
        {
            item.buyButton->setEnabled(true);
            item.buyButton->setText("Buy");
        }
    }
}
