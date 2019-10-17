#ifndef ASTEROIDGAME_H
#define ASTEROIDGAME_H

#include <QtWidgets>

#include "playership.h"

#include "projectile.h"

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

    private:
        QTimer* refreshTimer;
        QElapsedTimer absoluteTime;
        QElapsedTimer interframeTime;

        QSet<int> pressedKeys;

        PlayerShip* playerShip;
        QSet<Projectile*> projectiles;
};

#endif // ASTEROIDGAME_H
