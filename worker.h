#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QPointF>

class Worker : public QObject
{
    Q_OBJECT

public slots:
    void doWork(const QString &parameter);

signals:
    void progress(const QPointF &r);
    void resultReady(const QString &result);

};

#endif // WORKER_H
