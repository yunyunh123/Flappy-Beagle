
#include "pipe.h"

Pipe::Pipe(bool is_top, QGraphicsItem *parent)
{
    this->is_top = is_top;
    setPixmap(QPixmap(":/Images/pipe.png"));

    // Continuously move left
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(move()));
    timer.start(100);
}

Pipe::~Pipe() {
    timer.stop();
    scene()->removeItem(this);
}

void Pipe::move() {
    setPos(x()-10, y());

    // Once pipe moves off screen, delete pipe
    if (x() < -50) {
        delete this;
    }
}

void Pipe::deletePipe() {
    delete this;
}
