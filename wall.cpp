#include <QPainter>

#include "constants.h"
#include "wall.h"

static const  qreal WALL_RADIUS = 4;

Wall::Wall(qreal x, qreal y )
{
    setPos (x, y);
    setData(GD_Type, GO_Wall );
}

QRectF Wall ::boundingRect() const
{
    return QRectF(-TILE_SIZE,    -TILE_SIZE,
                   TILE_SIZE * 2, TILE_SIZE * 2 );
}

void Wall ::paint (QPainter  *painter, const  QStyleOptionGraphicsItem *, QWidget*)
{
    painter->save();

    painter->setRenderHint (QPainter ::Antialiasing); //反走样
    painter->fillPath (shape (),  Qt::black );

    painter->restore();
}

QPainterPath Wall ::shape () const
{
    QPainterPath p;
    p.addEllipse (QPointF(TILE_SIZE  / 2, TILE_SIZE / 2), WALL_RADIUS,
    WALL_RADIUS);
    return p;
}

