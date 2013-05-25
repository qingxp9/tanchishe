#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "gamecontroller.h"
#include "food.h"
#include "snake.h"
#include "wall.h"


GameController::GameController(QGraphicsScene &scene, QObject *parent) :
    QObject(parent),
    scene(scene),
    snake(new Snake(*this)),
    wall(new Wall(30,40))
{
    timer.start( 1000/33 );

    Food *a1 = new Food(0,-50);
    scene.addItem(a1);
    scene.addItem(wall);

    scene.addItem(snake);
    scene.installEventFilter(this);

    resume();
}

GameController::~GameController()
{
}

void GameController::snakeAteFood(Snake *snake, Food *food)
{
    scene.removeItem(food);
    delete food;
    addNewFood();
}

void GameController::snakeHitWall(Snake *snake, Wall *wall)
{
    QTimer::singleShot(0, this, SLOT(gameOver()));
}

void GameController::snakeAteItself(Snake *snake)
{
    QTimer::singleShot(0, this, SLOT(gameOver()));
}

void GameController::handleKeyPressed(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Left:
            snake->setMoveDirection(Snake::MoveLeft);
            break;
        case Qt::Key_Right:
            snake->setMoveDirection(Snake::MoveRight);
            break;
        case Qt::Key_Up:
            snake->setMoveDirection(Snake::MoveUp);
            break;
        case Qt::Key_Down:
            snake->setMoveDirection(Snake::MoveDown);
            break;
    }
}

void GameController::addNewFood()
{
    //生成新食物
    int x, y;
    do {
        x = (int) (qrand() % 100) / 10;
        y = (int) (qrand() % 100) / 10;

        x *= 10;
        y *= 10;
    } while (snake->shape().contains(snake->mapFromScene(QPointF(x + 5, y + 5))));

    Food *food = new Food(x , y);
    scene.addItem(food);

    //生成wall  a,b
    int a,b;
    do {
        a = (int) (qrand() % 50) / 10;
        b = (int) (qrand() % 60) / 10;

        a *= 20;
        b *= 10;
    } while (snake->shape().contains(snake->mapFromScene(QPointF(a + 5, b + 5))) || QPointF(x,y) == QPoint(a,b));

    if(ok)
   { scene.removeItem(wall);}
    wall =new Wall(a , b);
    scene.addItem(wall);
}



void GameController::gameOver()
{
    scene.clear();
    ok=0;
    snake = new Snake(*this);
    scene.addItem(snake);
    addNewFood();
    ok=1;
}

void GameController::pause()
{
    disconnect(&timer, SIGNAL(timeout()),
               &scene, SLOT(advance()));
}

void GameController::resume()
{
    connect(&timer, SIGNAL(timeout()),
            &scene, SLOT(advance()));
}

bool GameController::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    } else {
        return QObject::eventFilter(object, event);
    }
}
