#ifndef ASTEROIDGAME_H
#define ASTEROIDGAME_H

#include <QtWidgets>
#include <QtMultimedia/QSoundEffect>

#include "playership.h"
#include "score.h"
#include "asteroid.h"
#include "projectile.h"

class AsteroidGame : public QWidget
{
    Q_OBJECT

public:
    explicit AsteroidGame(QWidget* parent = nullptr);
    void connectGameOver (const QObject *receiver, const char * slotMemberFunction );

signals:
    void backToMenu();

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
    void gameOver();

private:
    QSet <Projectile*> projectiles;
    QSet <Asteroid*> asteroidSet;
    PlayerShip *playerShip;
    QTimer* refreshTimer;
    QElapsedTimer absoluteTime;
    QElapsedTimer interframeTime;
    Score score;
    QSet <int> pressedKeys;
    QSoundEffect pew;
    QSoundEffect boum;
    QString scoreFilename;
};

#endif // ASTEROIDGAME_H
