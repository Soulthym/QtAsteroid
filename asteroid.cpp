#include "asteroid.h"

Asteroid::Asteroid (AsteroidSizes _size, QPointF initialPos, qreal _maxSpeed, QObject *parent) : QObject(parent)  {
    size = _size;
    pos = initialPos;
    maxSpeed = _maxSpeed;
    velocity = QPointF (
                (QRandomGenerator::global()->bounded(maxSpeed*2.0) - maxSpeed),
                (QRandomGenerator::global()->bounded(maxSpeed*2.0) - maxSpeed)
                );

    switch (_size) {
    case SMALL :
        radius = 0.03;
        break;
    case MEDIUM :
        radius = 0.05;
        break;
    case BIG:
        radius = 0.12;
        break;
    }

    qreal angle = QRandomGenerator::global()->bounded(360.0);

    shape << QPointF (radius * qCos (angle), radius * qSin (angle));
    for (int n = 1; n < sideNumber; n++)   //draws a N sided polygon in a circle of radius radius
        shape << QPointF (
                     radius * (QRandomGenerator::global()->bounded(0.4) + 0.6) * qCos (angle + n * 360.0/sideNumber * M_PI / 180.0),
                     radius * (QRandomGenerator::global()->bounded(0.4) + 0.6) * qSin (angle + n * 360.0/sideNumber * M_PI / 180.0)
                     );
    shape << QPointF (radius * qCos (angle), radius * qSin (angle));    //close the shape
}

int Asteroid::get_score () {
    int score = int ((velocity.rx()+velocity.ry()+1)/2.0 * 10.0);
    switch (size) {
        case BIG :
            return 50 * score;
        case MEDIUM:
            return 150 * score;
        case SMALL:
            return 300 * score;
    }
    return 0;
}

void Asteroid::draw (QPainter* painter) {
    painter->save ();

    painter->translate (pos);
    painter->drawPolyline (shape);

    painter->restore ();
}

void Asteroid::animate (const qreal& dt) {

    pos += velocity * dt;

    //check collision


    // handle warps
    if (pos.rx () < -1.0)
        pos.rx () += 2.0;
    if (pos.rx () > 1.0)
        pos.rx () -= 2.0;
    if (pos.ry () < -1.0)
        pos.ry () += 2.0;
    if (pos.ry () > 1.0)
        pos.ry () -= 2.0;
}

AsteroidSizes get_next_size (AsteroidSizes size) {
    switch (size) {
    case BIG:
        return MEDIUM;
    case MEDIUM:
        return SMALL;
    case SMALL:
        return SMALL;
    }
    return SMALL;
}

bool Asteroid::is_intersecting (const QPolygonF toTest) {
    QTransform trans;
    trans.translate(pos.rx(), pos.ry());
    return toTest.intersects(trans.map(shape));
}

bool Asteroid::is_intersecting (const QPointF toTest) {
    QTransform trans;
    trans.translate(pos.rx(), pos.ry());
    return trans.map(shape).containsPoint(toTest, Qt::FillRule::OddEvenFill);
}

QPair<Asteroid*, Asteroid*> * Asteroid::destroy () {
    //animation destruction
    deleteLater();

    if (size == SMALL)
        return nullptr;

    AsteroidSizes newSize = get_next_size (size);
    return new QPair <Asteroid*, Asteroid*> (
                new Asteroid (newSize, pos, maxSpeed * 2.0),
                new Asteroid (newSize, pos, maxSpeed * 2.0)
                );
};


