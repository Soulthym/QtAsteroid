#ifndef ASTEROIDGAME_H
#define ASTEROIDGAME_H

#include <QtWidgets>
#include <QtMultimedia/QSound>
#include <QtMultimedia/QSoundEffect>

#include "playership.h"
#include "score.h"
#include "asteroid.h"
#include "projectile.h"
#include "scoreboardmenu.h"

class AsteroidGame : public QWidget
{
    Q_OBJECT

public:
    explicit AsteroidGame(QWidget* parent = nullptr);

signals:
    void scoreSaved(unsigned int score, QString text);

public slots:
    void refresh();
    void newProjectile(Projectile*);
    void projectileDestroyed();
    void accessScore(ScoreBoardMenu *scoreBoardMenu);

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
    ScoreBoardMenu *_scoreBoardMenu;
    QSoundEffect pew;
    QSoundEffect boum;
};

#endif // ASTEROIDGAME_H
