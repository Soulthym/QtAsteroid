#include "playership.h"

PlayerShip::PlayerShip() {
    _angle = 0.0;
    _pos = QPointF(0.0, 0.0);
    _velocity = QPointF(0.0, 0.0);
}

qreal PlayerShip::angle() {
    return _angle;
}

void PlayerShip::setAngle(const qreal& angle) {
    _angle = angle;
}

qreal PlayerShip::rotate(const qreal& angle) {
    _angle += angle;
    return _angle;
}

void PlayerShip::draw(QPainter* painter, const QRect& frame) {
    painter->save();

    painter->translate(_pos);
    painter->rotate(_angle);
    painter->scale(0.02, 0.02);

    // draw shape
    static const QPolygonF shape = QPolygonF()
        << QPoint( 0.0, -2.0)
        << QPoint( 1.0,  1.0)
        << QPoint( 0.0,  0.0)
        << QPoint(-1.0,  1.0)
        << QPoint( 0.0, -2.0);
    painter->drawPolyline(shape);

    painter->restore();
}

void PlayerShip::animate(const qreal& t, const qreal& dt, const QSet<int>& pressedKeys) {
    QTransform rotation;

    if (pressedKeys.contains(Qt::Key_Left)) {
        _angle -= 80.0 * dt;
    }

    if (pressedKeys.contains(Qt::Key_Right)) {
        _angle += 80.0 * dt;
    }

    rotation.rotate(_angle);

    if (pressedKeys.contains(Qt::Key_Up)) {
        _velocity += rotation.map(QPointF(0.0, -1.0)) * dt;
    }

    // move forward
    _pos += _velocity * dt;

    // fade speed
    _velocity = _velocity * std::min(dt * 100, 0.99);

    // handle warps
    if (_pos.rx() < -1.0)
        _pos.rx() += 2.0;

    if (_pos.rx() > 1.0)
        _pos.rx() -= 2.0;

    if (_pos.ry() < -1.0)
        _pos.ry() += 2.0;

    if (_pos.ry() > 1.0)
        _pos.ry() -= 2.0;
}

void PlayerShip::shoot() {
    Projectile* projectile = new Projectile(_pos, _angle);
    emit newProjectile(projectile);
}
