#include <workerthread.h>
#include <iostream>
#include <QRandomGenerator>

#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QRandomGenerator>
#include <iostream>


WorkerThread::WorkerThread(){
    std::cout << "WorkThread CTOR" << std::endl;
}

WorkerThread::~WorkerThread(){
    std::cout << "WorkThread DTOR" << std::endl;
}


void WorkerThread::run(){

    QString result;

    std::cout << "Start Working Thread" << std::endl;
    std::cout << "Thread ID MainWindows: " << QThread::currentThreadId() << std::endl;

    QRandomGenerator *rng = new QRandomGenerator();
    rng->seed(123);

    QScatterSeries *measure = new QScatterSeries();
    QSplineSeries *spline_m = new QSplineSeries();
    QChart *chart1 = new QChart();
    QChartView *chart1_view = new QChartView();

    measure->setName("Points");
    spline_m->setName("Spline");
    for(int i = 0; i < 5000; i++){

        double r = rng->generateDouble();

        measure->append(double(i), r);
        spline_m->append(double(i), r);

    }
    chart1->addSeries(measure);
    chart1->addSeries(spline_m);
    chart1_view->show();


    emit resultReady(result);
}
