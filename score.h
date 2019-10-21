#ifndef SCORE_H
#define SCORE_H

#include <QtWidgets>

class Score : public QObject
{
    Q_OBJECT
public:
    explicit Score();
    void draw(QPainter* painter, const QRect& frame);
    unsigned int getScore();

signals:

public slots:
    void add(unsigned int value);

protected:

private:
    unsigned int _score;
};

#endif // SCORE_H
