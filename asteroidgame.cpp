#include "asteroidgame.h"

AsteroidGame::AsteroidGame(QWidget* parent) : QWidget(parent) {
    // set FPS timer
    refreshTimer = new QTimer();
    QObject::connect(refreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));
    refreshTimer->setSingleShot(false);
    refreshTimer->start(1000 / 60); // 1/60s
    isPaused = true;

    //instantiate asteroids
    spawn_asteroids (BIG, 5);

    // start chronometers
    absoluteTime.start();
    interframeTime.start();

    //
    playerShip = new PlayerShip();
    connect(playerShip, SIGNAL(newProjectile(Projectile*)), this, SLOT(newProjectile(Projectile*)));
    pew.setSource(QUrl::fromLocalFile("./16bit-pew.wav"));
    boum.setSource(QUrl::fromLocalFile("./8bit-explosion-SFX.wav"));
    scoreFilename="./scores.csv";
}

void AsteroidGame::spawn_asteroids (AsteroidSizes size, int number) {
    for (int i=0; i<number; i++) {
        qreal placement = QRandomGenerator::global()->bounded(0.95);
        asteroidSet << new Asteroid (size,
                                     QPointF(
                                        placement * numberSet[QRandomGenerator::global()->bounded(2)],
                                        (1.0-placement) * numberSet[QRandomGenerator::global()->bounded(2)]
                                     ),
                                     0.06);
    }
}

void AsteroidGame::refresh() {
    const qreal t = absoluteTime.nsecsElapsed() * 1e-9;
    const qreal dt = interframeTime.nsecsElapsed() * 1e-9; interframeTime.restart();

    if (isPaused)
        return;

    playerShip->animate(t, dt, pressedKeys);

    foreach (Asteroid* ast, asteroidSet) {
        ast->animate(dt);
    }

    foreach (Projectile* p, projectiles) {
        p->animate(t, dt, pressedKeys);
    }

    // trigger redraw
    update();
}

void AsteroidGame::sound_changed (qreal volume) {
    pew.setVolume(volume);
    boum.setVolume(volume);
}

void AsteroidGame::paintEvent(QPaintEvent* event) {
    const QColor bgColor(Qt::black);
    const QColor fgColor(Qt::white);


    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    painter.setBrush(fgColor);

    QPen pen(fgColor);
    pen.setCosmetic(true); // scale-independent thickness
    pen.setWidth(1);
    painter.setPen(pen);


    QRect frame = this->rect(); // widget's inner geometry
    painter.fillRect(frame, bgColor); // draw background

    painter.scale(qreal (frame.width()) / 2.0, qreal(frame.height()) / 2.0);
    painter.translate(QPointF(1.0, 1.0));

    playerShip->draw(&painter, frame);
    score.draw(&painter, frame);

    foreach (Projectile* p, projectiles) {
          p->draw(&painter, frame);
      }

    foreach (Asteroid* ast, asteroidSet) {
        ast->draw(&painter);
    }
    collisions ();
}

void AsteroidGame::newProjectile(Projectile* projectile) {
    projectiles.insert(projectile);
    connect(projectile, SIGNAL(destroyed()), this, SLOT(projectileDestroyed()));
    pew.play();
}

void AsteroidGame::projectileDestroyed() {
    Projectile* caller = (Projectile*) QObject::sender();
    projectiles.remove(caller);
}

void AsteroidGame::collisions () {
    QSet <Asteroid*> newAsteroids;
    QSet <Asteroid*> delAsteroids;
    QSet <Projectile*> toDestroy;

    foreach (Asteroid* ast, asteroidSet) {
        if (ast->is_intersecting(playerShip->get_player_polygon())) {
            gameOver();
            return;
        }
    }

    foreach (Projectile* p, projectiles) {
        foreach (Asteroid* ast, asteroidSet) {
            if (ast->is_intersecting (p->get_shape  ())) {
                p->destroy();
                boum.play();
                //QSound::play("8bit-explosion-SFX.wav");
                toDestroy << p;
                score.add(1);
                QPair<Asteroid*, Asteroid*> *res = ast->destroy();
                if (res != nullptr and res->first != nullptr and res->second != nullptr) {
                    newAsteroids << res->first << res->second;
                }
                delAsteroids << ast;
            }
        }
    }


    foreach (Asteroid *ast, newAsteroids)
        asteroidSet.insert (ast);
    foreach (Asteroid *ast, delAsteroids)
        asteroidSet.remove (ast);
    foreach (Projectile *p, toDestroy)
        toDestroy.remove (p);
}

void AsteroidGame::keyPressEvent(QKeyEvent* event) {
    pressedKeys.insert(event->key());
    if (event->key() == Qt::Key_Space) {
            playerShip->shoot();
            return;
    }
    if (event->key() == Qt::Key_Escape) {
        isPaused = !isPaused;
        if (isPaused) {
            //print menu

        }
    }
}

void AsteroidGame::keyReleaseEvent(QKeyEvent* event) {
    pressedKeys.remove(event->key());
}

// constrain square size
void AsteroidGame::resizeEvent(QResizeEvent* event) {
    event->accept();

    int sideSize = std::min(event->size().height(), event->size().width());
    QWidget::resize(sideSize, sideSize);
}

void AsteroidGame::gameOver() {
    QFile csvFile(scoreFilename);
    if (csvFile.open(QIODevice::Append)) {
        QTextStream stream(&csvFile);
        stream << QDir::home().dirName() << ',' << score.getScore() << endl;
    }
    score.reset();
    projectiles.clear();
    asteroidSet.clear();
    pressedKeys.clear();
    playerShip->reset();

    isPaused = true;
    spawn_asteroids (BIG, 5);
    emit backToMenu();
}

void AsteroidGame::connectGameOver (const QObject *receiver, const char * slotMemberFunction ) {
    //called by MainWindow to return when Game is Over
    connect (this, SIGNAL(backToMenu()), receiver, slotMemberFunction);
}
