
#include "beagle.h"

Beagle::Beagle(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/Images/player.png"));

    // Falling beagle
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(fall()));
    timer->start(100);
}

void Beagle::jump() {
    if ((y() - 20) < 0) { // Out of bounds
        setPos(x(), 0);
    } else { // Fly up
        setPos(x(), y()-20);
    }
    checkCollision();
}

void Beagle::keyPressEvent(QKeyEvent * event) {
    if(event->key() == Qt::Key_Up) {
        jump();
    }
}

void Beagle::fall() {
    setPos(x(), y()+6); // Fall down
    if (y() > VIEW_HEIGHT) { // Out of bounds
        setPos(x(), VIEW_HEIGHT);
    }
    checkCollision();
}

void Beagle::checkCollision() {
    QList<QGraphicsItem *> items = collidingItems();
    int i = 0;
    for (i = 0; i < items.size(); i++) {
        if (typeid(*(items[i])) == typeid(Pipe)) {
            emit isCollision();
            break;
        }
    }
}
