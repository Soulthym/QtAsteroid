#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <QtWidgets>

class PlayerShip : public QObject
{
  Q_OBJECT

public:
  explicit PlayerShip();

  qreal angle();
  void setAngle(const qreal& angle);
  qreal rotate(const qreal& angle);

  void draw(QPainter* painter, const QRect& frame);
  void animate(const qreal& t, const qreal& dt, const QSet<int>& pressedKeys);

signals:

public slots:

protected:

private:
  qreal _angle;
  QPointF _pos;
  QPointF _velocity;
};

#endif // PLAYERSHIP_H