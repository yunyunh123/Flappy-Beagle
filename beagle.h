
#ifndef BEAGLE_H
#define BEAGLE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <QDebug>
#include "pipe.h"

#define VIEW_HEIGHT 300

class Beagle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Beagle(QGraphicsItem *parent=0);

private:
    QTimer * timer;
    void checkCollision();
    void keyPressEvent(QKeyEvent * event);
public slots:
    void fall();
    void jump();
signals:
    void isCollision();
};

#endif // BEAGLE_H
