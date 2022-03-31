#include <controller.h>
#include <worker.h>
#include <QThread>
#include <iostream>
#include <QSlider>

Controller::Controller()
{

    std::cout << "Thread ID: " << &QThread::currentThreadId << std::endl;
    std::cout << "Controller CTOR" << std::endl;
    Worker *worker = new Worker;

    worker->moveToThread(&workerThread);

    connect(worker, &Worker::progress,
            this, &Controller::SignalForwardResult);

    connect(&workerThread, &QThread::finished,
            worker, &QObject::deleteLater );

    connect(this, &Controller::operate,
            worker, &Worker::doWork);

    workerThread.start();

}

Controller::~Controller()
{
    std::cout << "Controller DTOR" << std::endl;
    workerThread.quit();
    workerThread.wait();

}

//void Controller::handleResults(const QString &n)
//{
//    // how do I update the mainWindow from here
//}
