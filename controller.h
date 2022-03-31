#ifndef CONTROLLER_H
#define CONTROLLER_H

#pragma once
#include <QThread>
#include <QObject>
#include <QPointF>

class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;

public:
    Controller();
    ~Controller();

public slots:
    void handleResults(const QString &);
    void print_progress(const QPointF &);


signals:
    void operate(const QString &);
    void recv_a_point(const QPointF &);


};

#endif // CONTROLLER_H
