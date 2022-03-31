#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread();
    ~WorkerThread();
private:
    void run() override;
signals:
    void resultReady(const QString &s);
};

#endif // WORKERTHREAD_H

//void MyObject::startWorkInAThread()
//{
//    WorkerThread *workerThread = new WorkerThread(this);
//    connect(workerThread, &WorkerThread::resultReady, this, &MyObject::handleResults);
//    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
//    workerThread->start();
//}
