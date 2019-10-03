#ifndef ASTEROIDGAME_H
#define ASTEROIDGAME_H

#include <QtWidgets>

#include "playership.h"

class AsteroidGame : public QWidget
{
  Q_OBJECT

public:
  explicit AsteroidGame(QWidget* parent = nullptr);

signals:

public slots:
  void refresh();

protected:
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void resizeEvent(QResizeEvent*) override;

private:
  PlayerShip playerShip;
  QTimer* refreshTimer;
  QElapsedTimer absoluteTime;
  QElapsedTimer interframeTime;

  QSet<int> pressedKeys;
};

#endif // ASTEROIDGAME_H
