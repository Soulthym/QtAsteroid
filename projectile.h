#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QtWidgets>

class Projectile : public QObject
{
    Q_OBJECT

    public:
        explicit Projectile(QPointF initPos, qreal angle);

        void draw(QPainter* painter, const QRect& frame);
        void animate(const qreal& t, const qreal& dt, const QSet<int>& pressedKeys);

    private:
        QPointF pos;
        QPointF velocity;
};

#endif // PROJECTILE_H
