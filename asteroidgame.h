#ifndef ASTEROIDGAME_H
#define ASTEROIDGAME_H

#include <QtWidgets>
#include <QtMultimedia/QSoundEffect>
#include <QVBoxLayout>

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
    bool isPaused;
    unsigned int getScore();

signals:
    void backToMenu(bool playerDead);

public slots:
    void refresh();
    void newProjectile(Projectile*);
    void projectileDestroyed();
    void sound_changed (qreal volume);
    void change_difficulty (int index);
    void set_unpaused ();
    void return_to_mainmenu ();

protected:
    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;
    void resizeEvent(QResizeEvent*) override;
    void spawn_asteroids (AsteroidSizes size, int number, qreal asteroidSpeed);

    void collisions ();
    void gameOver(bool playerDead);

private:
    QBoxLayout *mainLayout;
    QWidget *pauseMenuWidget;
    QVBoxLayout *pauseMenu;
    QPushButton *returnToGameButton;
    QPushButton *mainMenuButton;
    QSlider *soundSlider;

    int numberSet[2] = {-1, 1};
    qreal asteroidSpeeds [3] = {0.03, 0.07, 0.12};
    qreal asteroidBaseSpeed;
    qreal asteroidSpeed;
    int difficulty;

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
    unsigned int lastscore;
};

#endif // ASTEROIDGAME_H
