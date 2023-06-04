
#ifndef PIPE_H
#define PIPE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>

#define PIPE_WIDTH 68
#define PIPE_MIN_HEIGHT 40
#define PIPE_MAX_HEIGHT 165

class Pipe : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Pipe(bool is_top, QGraphicsItem *parent=0);
    ~Pipe();
public slots:
    void move();
    void deletePipe();
private:
    QTimer timer;
    bool is_top;
};

#endif // PIPE_H
