#include <worker.h>
#include <iostream>
#include <QThread>

using namespace std;

void Worker::doWork(const QString &parametrs)
{

    cout << "Function doWork: " << QThread::currentThreadId() << endl;
    for(int i=0; i<100; i++){
        cout << i << endl;
        emit progress(QString::number(i));
    }
    QString result = "finished";
    emit resultReady(result);
}
