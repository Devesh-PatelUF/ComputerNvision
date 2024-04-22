#ifndef TIMER_H
#define TIMER_H

#include <QTimer>
#include <QObject>

class Timer : public QObject
{
    Q_OBJECT
public:
    explicit Timer(uint64_t ms, QObject *parent = nullptr);
signals:
private:
    QTimer* time;
};

#endif // TIMER_H
