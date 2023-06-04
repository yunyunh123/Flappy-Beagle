
#ifndef GAME_H
#define GAME_H

#include <QDebug>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QBrush>
#include <QImage>
#include <QObject>
#include <QTimer>
#include <QString>
#include <stdlib.h>
#include <QGraphicsTextItem>
#include "beagle.h"
#include "pipe.h"
#include "touchscreen.h"

#define WIDTH 500
#define HEIGHT 300
#define PIPES_INTERVAL 2000
#define SCORE_INTERVAL 2000
#define BUTTON_W 200
#define BUTTON_H 30
#define FLAPPY 1
#define SNAKE 2

class Game : public QWidget
{
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);
    ~Game();
public slots:
    void createPipes();
    void startMenu();
    void gameOver();
    void startFlappy();
    void incrementScore();
signals:
    void removePipes();
private:
    // Private helper functions
    void createBeginScene();
    void createEndScene();
    void createFlappyScene();
    void styleButton(QPushButton *btn, QString text, int x, int y);

    // Private variables
    QGraphicsView view;
    QString font = "Helvetica";
    int txt_size = 15;
    int current_game = -1;

    // Menu:
    QGraphicsScene begin_scene;
    QPushButton st_flappy;
    QPushButton st_snake;
    QGraphicsTextItem begin_msg;

    // FlappyBeagle:
    QGraphicsScene flappy_scene;
    Beagle player;
    QTimer timer;
    QTimer timer_score;
    QGraphicsTextItem score_text;
    int score;
    QGraphicsTextItem *score_final;
    touchscreen touch;

    // Game Over scene:
    QGraphicsScene end_scene;
    //QPushButton restart;
    QPushButton menu;
    QGraphicsTextItem end_msg;
};

#endif // GAME_H
