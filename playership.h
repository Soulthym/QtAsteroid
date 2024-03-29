#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <QtWidgets>
#include "projectile.h"

class PlayerShip : public QObject
{
    Q_OBJECT

public:
    explicit PlayerShip();

    void setAngle(const qreal& angle);
    qreal rotate(const qreal& angle);

    void draw(QPainter* painter, const QRect& frame);
    void animate(const qreal& t, const qreal& dt, const QSet<int>& pressedKeys);
    const QPolygonF get_player_polygon ();
    void shoot();
    void reset();

signals:
    void newProjectile(Projectile*);

public slots:

protected:

private:
    qreal angle;
    QPointF pos;
    QPointF velocity;
    QPolygonF shape;
};

#endif // PLAYERSHIP_H
