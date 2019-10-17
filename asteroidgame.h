#ifndef ASTEROIDGAME_H
#define ASTEROIDGAME_H

#include <QtWidgets>

#include "playership.h"
#include "score.h"
#include "asteroid.h"
#include "projectiles.h"

class AsteroidGame : public QWidget
{
    Q_OBJECT

public:
    explicit AsteroidGame(QWidget* parent = nullptr);

signals:

public slots:
    void refresh();
    void newProjectile(Projectile*);
    void projectileDestroyed();

protected:
    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;
    void resizeEvent(QResizeEvent*) override;

    void collisions ();

private:
    QSet<Projectile*> projectiles;
    QSet <Asteroid*> asteroidSet;
    PlayerShip *playerShip;
    QTimer* refreshTimer;
    QElapsedTimer absoluteTime;
    QElapsedTimer interframeTime;
    Score score;
    QSet<int> pressedKeys;
};

#endif // ASTEROIDGAME_H
