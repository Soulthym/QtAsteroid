#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QtWidgets>

class Projectile : public QObject
{
    Q_OBJECT

    public:
        explicit Projectile(QPointF initPos, qreal angle);
        const QPointF get_shape ();
        void draw(QPainter* painter, const QRect& frame);
        void animate(const qreal& t, const qreal& dt, const QSet<int>& pressedKeys);
        void destroy ();

    private:
        QPointF pos;
        QPointF velocity;
};

#endif // PROJECTILE_H
