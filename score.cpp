#include "score.h"

Score::Score() {
    _score = 0;
}

void Score::draw(QPainter* painter, const QRect& frame) {
    painter->save();
    painter->translate(-1,-0.945);
    painter->scale(0.005, 0.005);
    //void QPainter::fillRect(const QRectF & rectangle, const QBrush & brush)

    //int x, int y, int width, int height, int flags, const QString & text, QRect * boundingRect = 0)
    painter->drawText(0, 0, QString::number(_score));
    painter->restore();
}

void Score::add(unsigned int value) {
    _score += value;
}

unsigned int Score::getScore() {
    return _score;
}
