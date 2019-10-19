#include "projectiles.h"

const QPointF Projectile::get_shape () {
    return pos;
}

void Projectile::destroy () {
    deleteLater();
}

Projectile::Projectile(QPointF initPos, qreal angle) {
    pos = initPos;

    QTransform transform;
    transform.rotate(angle);
    transform.scale(0.02, 0.02);

    velocity = transform.map(QPointF(0.0, -1.0)) * 20;

    pos += velocity / 10.0;
}

void Projectile::draw(QPainter* painter, const QRect& frame) {
    painter->save();

    painter->translate(pos);
    painter->scale(0.01, 0.01);

    painter->drawEllipse(QPointF(0.0, 0.0), 0.5, 0.5);

    painter->restore();
}

void Projectile::animate(const qreal& t, const qreal& dt, const QSet<int>& pressedKeys) {
    pos += velocity * dt;

    // handle warps
    if (pos.rx() < -1.0)
        deleteLater();

    if (pos.rx() > 1.0)
        deleteLater();

    if (pos.ry() < -1.0)
        deleteLater();

    if (pos.ry() > 1.0)
        deleteLater();
}
