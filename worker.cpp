#include <worker.h>
#include <iostream>
#include <QThread>
#include <QRandomGenerator>
#include <QPointF>

#include <unistd.h>
#include <time.h>

using namespace std;

void Worker::doWork(const QString &parametrs)
{
    QRandomGenerator *rng = new QRandomGenerator();
    rng->seed();
    QPointF *p = new QPointF();

    cout << "Function doWork: " << QThread::currentThreadId() << endl;
    for(int i=0; i<10000; i++){
        usleep(1000000);
        double x = rng->generateDouble();
        double y = rng->generateDouble();
        p->setX(i);
        p->setY(y+x);
        emit progress(*p);
    }
    QString result = "finished";
    emit resultReady(result);
}
