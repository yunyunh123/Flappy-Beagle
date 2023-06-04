
#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include <QGraphicsRectItem>
#include <QObject>

class touchscreen : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    touchscreen();
    bool sceneEvent(QEvent* event) override;
signals:
    void touchEvent();
};

#endif // TOUCHSCREEN_H
