#ifndef CONTROLLER_H
#define CONTROLLER_H

#pragma once
#include <QThread>
#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;

public:
    Controller();
    ~Controller();


signals:
    void operate(const QString &);
    void SignalForwardResult(const QString &);


};

#endif // CONTROLLER_H
