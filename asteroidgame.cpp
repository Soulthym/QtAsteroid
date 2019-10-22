#include "asteroidgame.h"

AsteroidGame::AsteroidGame(QWidget* parent) : QWidget(parent) {
    //init pause menu
    mainLayout = new QBoxLayout (QBoxLayout::LeftToRight, this);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    pauseMenuWidget = new QWidget (this);
    pauseMenu = new QVBoxLayout (pauseMenuWidget);
    returnToGameButton = new QPushButton ("Return to Game");
    mainMenuButton = new QPushButton ("Main Menu");
    soundSlider = new QSlider;
    soundSlider->setOrientation(Qt::Orientation::Horizontal);
    soundSlider->setRange(0, 100);
    soundSlider->setValue(50);

    connect (returnToGameButton, &QPushButton::pressed, this, &AsteroidGame::set_unpaused);
    connect (mainMenuButton, &QPushButton::pressed, this, &AsteroidGame::return_to_mainmenu);
    connect (soundSlider, &QSlider::valueChanged, this, &AsteroidGame::sound_changed);

    pauseMenu->addWidget(returnToGameButton);
    pauseMenu->addWidget(mainMenuButton);
    pauseMenu->addWidget(soundSlider);
    pauseMenuWidget->setVisible(false);
    pauseMenuWidget->setAttribute(Qt::WA_TranslucentBackground, true);
    pauseMenuWidget->setHidden(true);
    mainLayout->addWidget (pauseMenuWidget, Qt::AlignCenter);

    // set FPS timer
    refreshTimer = new QTimer();
    QObject::connect(refreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));
    refreshTimer->setSingleShot(false);
    refreshTimer->start(1000 / 60); // 1/60s

    //instantiate asteroids
    change_difficulty(1);
    spawn_asteroids (BIG, 5, asteroidBaseSpeed);
    isPaused = true;

    // start chronometers
    absoluteTime.start();
    interframeTime.start();

    //instantiate player
    playerShip = new PlayerShip();
    connect(playerShip, SIGNAL(newProjectile(Projectile*)), this, SLOT(newProjectile(Projectile*)));

    //sound system
    pew.setSource(QUrl::fromLocalFile("./16bit-pew.wav"));
    boum.setSource(QUrl::fromLocalFile("./8bit-explosion-SFX.wav"));
    scoreFilename="./scores.csv";
    lastscore = 0;
}

void AsteroidGame::spawn_asteroids (AsteroidSizes size, int numberToSpawn, qreal asteroidSpeed) {
    for (int i=0; i<numberToSpawn; i++) {
        qreal placement = QRandomGenerator::global()->bounded(0.95);
        asteroidSet << new Asteroid (size,
                                     QPointF(
                                        placement * numberSet[QRandomGenerator::global()->bounded(2)],
                                        (1.0-placement) * numberSet[QRandomGenerator::global()->bounded(2)]
                                     ),
                                     asteroidSpeed);
    }
}

void AsteroidGame::refresh() {
    const qreal t = absoluteTime.nsecsElapsed() * 1e-9;
    const qreal dt = interframeTime.nsecsElapsed() * 1e-9; interframeTime.restart();

    if (isPaused)
        return; //game paused : no events treated

    playerShip->animate(t, dt, pressedKeys);

    foreach (Asteroid* ast, asteroidSet)
        ast->animate(dt);

    foreach (Projectile* p, projectiles)
        p->animate(t, dt, pressedKeys);

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

    foreach (Projectile* p, projectiles)
          p->draw(&painter, frame);

    foreach (Asteroid* ast, asteroidSet)
        ast->draw(&painter);

    collisions ();  //handle collisions

    //new asteroid wave
    if (asteroidSet.empty()) {
        asteroidSpeed *= 1.1;
        spawn_asteroids (BIG, 5, asteroidSpeed);
    }
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
    //Is player dead ?
    foreach (Asteroid* ast, asteroidSet) {
        if (ast->is_intersecting(playerShip->get_player_polygon())) {
            gameOver(true);
            return;
        }
    }

    //calculate destroyed asteroids
    foreach (Projectile* p, projectiles) {
        foreach (Asteroid* ast, asteroidSet) {
            //if (delAsteroids.contains(ast)) //asteroid does not exist anymore
            //    continue;
            if (ast->is_intersecting (p->get_shape  ())) {  //projectile intersects asteroid
                boum.play();
                score.add( ast->get_score () * (1 + difficulty * 10));

                //divide asteroid ?
                QPair<Asteroid*, Asteroid*> *res = ast->destroy();
                if (res != nullptr and res->first != nullptr and res->second != nullptr) {
                    //divide asteroid
                    asteroidSet << res->first << res->second;
                }

                asteroidSet.remove(ast);
                ast->deleteLater();
                p->deleteLater();
            }
        }
    }
}

void AsteroidGame::keyPressEvent(QKeyEvent* event) {
    pressedKeys.insert(event->key());
    if (event->key() == Qt::Key_Space and !event->isAutoRepeat()) {
        if (!isPaused)
            playerShip->shoot();
        return;
    }
    if (event->key() == Qt::Key_Escape) {
        isPaused = !isPaused;
        if (isPaused) {
            //print menu
            pauseMenuWidget->setVisible(true);
            pauseMenuWidget->setHidden(false);
            pauseMenuWidget->setFocus();
        }
        else {
            //remove pause menu
            pauseMenuWidget->setVisible(false);
            pauseMenuWidget->setHidden(true);
            this->setFocus();
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

void AsteroidGame::gameOver(bool playerDead) {
    if (playerDead) {
        QFile csvFile(scoreFilename);
        if (csvFile.open(QIODevice::Append)) {
            QTextStream stream(&csvFile);
            stream << QDir::home().dirName() << ',' << score.getScore() << endl;
        }
        lastscore = score.getScore();
    }
    score.reset();
    projectiles.clear();
    asteroidSet.clear();
    pressedKeys.clear();
    playerShip->reset();

    isPaused = true;

    spawn_asteroids (BIG, 5, asteroidBaseSpeed);
    pauseMenuWidget->setVisible(false);
    pauseMenuWidget->setHidden(true);
    this->setFocus();
    emit backToMenu(playerDead);
}

void AsteroidGame::connectGameOver (const QObject *receiver, const char * slotMemberFunction ) {
    //called by MainWindow to return when Game is Over
    connect (this, SIGNAL(backToMenu(bool)), receiver, slotMemberFunction);
}

void AsteroidGame::change_difficulty(int index) {
    difficulty = index;
    asteroidSpeed = asteroidBaseSpeed = asteroidSpeeds [index];
}
unsigned int AsteroidGame::getScore() {
    return lastscore;
}

void AsteroidGame::set_unpaused () {
    //stop pause display
    isPaused = false;
    pauseMenuWidget->setVisible(false);
    pauseMenuWidget->setHidden(true);
    this->setFocus();
}
void AsteroidGame::return_to_mainmenu () {
    //stop pause display
    gameOver(false);
}
