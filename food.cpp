#include <QPainter>

#include "constants.h"
#include "food.h"

static const  qreal FOOD_RADIUS = 3;

Food::Food(qreal x, qreal y )
{
    setPos (x, y);
    setData(GD_Type, GO_Food );
}

QRectF Food ::boundingRect() const
{
    return QRectF(-TILE_SIZE,    -TILE_SIZE,
                   TILE_SIZE * 2, TILE_SIZE * 2 );
}

void Food ::paint (QPainter  *painter, const  QStyleOptionGraphicsItem *, QWidget
*)
{
    painter->save();

    painter->setRenderHint (QPainter ::Antialiasing); //反走样
    painter->fillPath (shape (),  QPixmap(":/images/food") );

    painter->restore();
}

QPainterPath Food ::shape () const
{
    QPainterPath p;
    p.addRect (1, 1, TILE_SIZE-2 , TILE_SIZE-2 );
    return p;
}
