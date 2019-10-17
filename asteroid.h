#ifndef ASTEROID_H
#define ASTEROID_H

#include <QObject>
#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>
#include <QPair>

static const uint8_t sideNumber = 12;    //Asteroid side number

enum AsteroidSizes {
    SMALL,
    MEDIUM,
    BIG
};

class Asteroid : public QObject
{
    Q_OBJECT
public:
    explicit Asteroid (AsteroidSizes size, qreal maxSpeed, QObject *parent = nullptr);
    void draw (QPainter* painter);
    void animate (const qreal& dt);
    bool is_intersecting (QPolygonF toTest);
    QPair<Asteroid*, Asteroid*> * destroy ();

signals:
    void touched_player ();

public slots:

private :
    AsteroidSizes size;
    QPointF pos;
    QPointF velocity;
    qreal radius;
    qreal maxSpeed;
    QPolygonF shape;

};

#endif // ASTEROID_H
