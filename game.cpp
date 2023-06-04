
#include "game.h"

Game::Game(QWidget *parent)
{
    // Enable touchscreen
    setAttribute(Qt::WA_AcceptTouchEvents, true);
    QObject::connect(&touch, SIGNAL(touchEvent()), &player, SLOT(jump()));

    // Create Scenes
    createBeginScene();
    createEndScene();
    createFlappyScene();

    // Show view
    view.setScene(&begin_scene);
    view.setFixedSize(WIDTH, HEIGHT);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.show();
}

Game::~Game()
{
}


/* --------------------- Menu --------------------- */
void Game::startMenu() {
    view.setScene(&begin_scene);
}

void Game::createBeginScene() {
    begin_scene.setSceneRect(0,0,WIDTH,HEIGHT);
    begin_scene.setBackgroundBrush(QBrush(QColor::fromRgb(229,255,204)));

    // Display scene's title
    begin_msg.setPlainText("Arcade Cabinet");
    begin_msg.setDefaultTextColor(QColor::fromRgb(0,51,25));
    begin_msg.setFont(QFont(font, 30, QFont::Bold));
    begin_msg.setPos(WIDTH/2-begin_msg.boundingRect().width()/2, HEIGHT/2-100);
    begin_scene.addItem(&begin_msg);

    // Display game options
    styleButton(&st_flappy, "Flappy Beagle", WIDTH/2 - BUTTON_W/2, HEIGHT/2-20);
    begin_scene.addWidget(&st_flappy);
    styleButton(&st_snake, "Snake", WIDTH/2 - BUTTON_W/2, HEIGHT/2+40);
    begin_scene.addWidget(&st_snake);

    QObject::connect(&st_flappy, SIGNAL(released()), this, SLOT(startFlappy()));
    //QObject::connect(&st_snake, SIGNAL(released()), this, SLOT(startSnake()));
}

/* --------------------- Game Over --------------------- */

void Game::gameOver() {
    if (current_game == FLAPPY) {
        score_final->setPlainText(QString("Score: ") + QString::number(score));
        emit removePipes();
        timer.stop();
        timer_score.stop();
    }
    view.setScene(&end_scene);
}

void Game::createEndScene() {
    end_scene.setSceneRect(0,0,WIDTH,HEIGHT);
    end_scene.setBackgroundBrush(QBrush("black"));

    // Display scene's title
    end_msg.setPlainText("Game Over");
    end_msg.setDefaultTextColor("red");
    end_msg.setFont(QFont(font, 30, QFont::Bold));
    end_msg.setPos(WIDTH/2-end_msg.boundingRect().width()/2, HEIGHT/2-100);
    end_scene.addItem(&end_msg);

    // Final Score:
    score_final = new QGraphicsTextItem();
    score_final->setPlainText(QString("Score: ") + QString::number(score));
    score_final->setDefaultTextColor("white");
    score_final->setFont(QFont(font, 20, QFont::Bold));
    score_final->setPos(WIDTH/2 - 50, HEIGHT/2-30);
    end_scene.addItem(score_final);

    // Button:
    styleButton(&menu, "Go back to Menu", WIDTH/2 - 90, HEIGHT/2-BUTTON_H/2+50);
    QObject::connect(&menu, SIGNAL(released()), this, SLOT(startMenu()));
    end_scene.addWidget(&menu);

    /* Restart button removed
    styleButton(&restart, "Restart Game", WIDTH/2 - restart.rect().width()/2, HEIGHT/2-BUTTON_H/2 + 20);
    QObject::connect(&restart, SIGNAL(released()), this, SLOT(startFlappy()));
    end_scene.addWidget(&restart);
    */
}

/* -------------------- Helper Functions -------------------- */

void Game::styleButton(QPushButton *btn, QString text, int x, int y) {
    btn->setText(text);
    btn->setFont(QFont(font, txt_size, QFont::Bold));
    btn->setFixedSize(BUTTON_W, BUTTON_H);
    btn->move(x, y);
}

/* -------------------- Flappy Beagle --------------------- */
void Game::startFlappy() {
    current_game = FLAPPY;

    // Scoring
    score = 0;
    score_text.setPlainText(QString("Score: ") + QString::number(score));
    timer_score.start(SCORE_INTERVAL+PIPES_INTERVAL);

    // Reset player
    player.setPos(WIDTH/2,HEIGHT/2-40);
    player.setFlag(QGraphicsItem::ItemIsFocusable);
    player.setFocus();

    // Start creating pipes
    timer.start(PIPES_INTERVAL);

    view.setScene(&flappy_scene);
}

void Game::createPipes() {
    // Top pipe
    Pipe * top = new Pipe(true);
    int height_top = - rand() % (PIPE_MAX_HEIGHT - PIPE_MIN_HEIGHT);
    top->setPos(WIDTH, height_top);
    flappy_scene.addItem(top);
    QObject::connect(this, SIGNAL(removePipes()), top, SLOT(deletePipe()));

    // Bottom pipe
    Pipe * bottom = new Pipe(false);
    bottom->setTransformOriginPoint(0,0);
    bottom->setRotation(180);
    bottom->setPos(WIDTH+PIPE_WIDTH, HEIGHT + PIPE_MAX_HEIGHT - PIPE_MIN_HEIGHT +  height_top + 15);
    flappy_scene.addItem(bottom);
    QObject::connect(this, SIGNAL(removePipes()), bottom, SLOT(deletePipe()));
}


void Game::incrementScore() {
    if (score == 0) {
        timer_score.start(SCORE_INTERVAL);
    }
    score += 1;
    score_text.setPlainText(QString("Score: ") + QString::number(score));
}

void Game::createFlappyScene() {
    flappy_scene.setSceneRect(0,0,WIDTH,HEIGHT);
    flappy_scene.setBackgroundBrush(QBrush(QImage(":/Images/background.jpg")));

    // Score
    score = 0;
    score_text.setPlainText(QString("Score: ") + QString::number(score));
    score_text.setFont(QFont(font, 20));
    score_text.setPos(0,0);
    score_text.setZValue(5);
    flappy_scene.addItem(&score_text);

    // Player
    player.setPos(WIDTH/2,HEIGHT/2-40);
    player.setFlag(QGraphicsItem::ItemIsFocusable);
    player.setFocus();
    flappy_scene.addItem(&player);

    QObject::connect(&player, SIGNAL(isCollision()), this, SLOT(gameOver()));
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(createPipes()));
    QObject::connect(&timer_score, SIGNAL(timeout()), this, SLOT(incrementScore()));
}

/* -------------------- Snake Game -------------------- */
