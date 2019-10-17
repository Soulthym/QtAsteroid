#include "playership.h"

PlayerShip::PlayerShip() {
    angle = 0.0;
    pos = QPointF(0.0, 0.0);
    velocity = QPointF(0.0, 0.0);

    // draw shape
    shape = QPolygonF()
            << QPointF( 0.0, -0.04)
            << QPointF( 0.02,  0.02)
            << QPointF( 0.0,  0.0)
            << QPointF( -0.02,  0.02)
            << QPointF( 0.0, -0.04);
}

void PlayerShip::setAngle(const qreal& _angle) {
    angle = _angle;
}

qreal PlayerShip::rotate(const qreal& _angle) {
    angle += _angle;
    return angle;
}

void PlayerShip::draw(QPainter* painter, const QRect& frame) {
    painter->save();

    painter->translate(pos);
    painter->rotate(angle);

    painter->drawPolyline(shape);

    painter->restore();
}

void PlayerShip::animate(const qreal& t, const qreal& dt, const QSet<int>& pressedKeys) {
    QTransform rotation;

    if (pressedKeys.contains(Qt::Key_Left)) {
        angle -= 80.0 * dt;
    }

    if (pressedKeys.contains(Qt::Key_Right)) {
        angle += 80.0 * dt;
    }

    rotation.rotate(angle);

    if (pressedKeys.contains(Qt::Key_Up)) {
        velocity += rotation.map(QPointF(0.0, -1.0)) * dt;
    }

    // move forward
    pos += velocity * dt;

    // fade speed
    velocity *= std::min(dt * 100, 0.99);

    // handle warps
    if (pos.rx() < -1.0)
        pos.rx() += 2.0;

    if (pos.rx() > 1.0)
        pos.rx() -= 2.0;

    if (pos.ry() < -1.0)
        pos.ry() += 2.0;

    if (pos.ry() > 1.0)
        pos.ry() -= 2.0;
}


const QPolygonF PlayerShip::get_player_polygon () {
    QTransform trans;
    trans.translate(pos.rx(), pos.ry());
    return trans.map(shape);
}
