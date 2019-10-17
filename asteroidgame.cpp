#include "asteroidgame.h"

AsteroidGame::AsteroidGame(QWidget* parent) : QWidget(parent) {
    // set FPS timer
    refreshTimer = new QTimer();
    QObject::connect(refreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));
    refreshTimer->setSingleShot(false);
    refreshTimer->start(1000 / 60); // 1/60s

    // start chronometers
    absoluteTime.start();
    interframeTime.start();

    playerShip = new PlayerShip();
    connect(playerShip, SIGNAL(newProjectile(Projectile*)), this, SLOT(newProjectile(Projectile*)));
}

void AsteroidGame::refresh() {
    const qreal t = absoluteTime.nsecsElapsed() * 1e-9;
    const qreal dt = interframeTime.nsecsElapsed() * 1e-9; interframeTime.restart();

    playerShip->animate(t, dt, pressedKeys);

    foreach (Projectile* p, projectiles) {
        p->animate(t, dt, pressedKeys);
    }

    // trigger redraw
    update();
}

void AsteroidGame::newProjectile(Projectile* projectile) {
    projectiles.insert(projectile);
    connect(projectile, SIGNAL(destroyed()), this, SLOT(projectileDestroyed()));
}

void AsteroidGame::projectileDestroyed() {
    Projectile* caller = (Projectile*) QObject::sender();
    projectiles.remove(caller);
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

    painter.scale((qreal)frame.width() / 2.0, (qreal)frame.height() / 2.0);
    painter.translate(QPointF(1.0, 1.0));

    playerShip->draw(&painter, frame);

    foreach (Projectile* p, projectiles) {
        p->draw(&painter, frame);
    }
}

void AsteroidGame::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space) {
        playerShip->shoot();
        return;
    }

    pressedKeys.insert(event->key());
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
