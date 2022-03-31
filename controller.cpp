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

    connect(&workerThread, &QThread::finished,
            &workerThread, &QThread::quit);

    connect(&workerThread, &QThread::finished,
            this, &QObject::deleteLater);

    connect(this, &Controller::operate,
            worker, &Worker::doWork);

    connect(worker, &Worker::resultReady,
            this, &Controller::handleResults);

    connect(worker, &Worker::progress,
            this, &Controller::print_progress);

    connect(this, &Controller::stop_thread,
            &workerThread, [=](i){
                workerThread.deleteLater();
            });

//    connect(worker, &Worker::progress,
//            this, &Controller::SignalForwardResult);


    workerThread.start();

}

Controller::~Controller()
{
    std::cout << "Controller DTOR" << std::endl;
    workerThread.quit();
    workerThread.wait();

}

void Controller::print_progress(const QPointF &point)
{
    emit recv_a_point(point);
}

void Controller::handleResults(const QString &n)
{
    std::cout << "The results are handled" << std::endl;
}
