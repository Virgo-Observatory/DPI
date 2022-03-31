// Custom interfaces
#include <mainwindow.h>
#include <ui_mainwindow.h>
//#include <workerthread.h>
#include <worker.h>
#include <controller.h>

// Qt includes
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QValueAxis>
#include <QPointF>
#include <QRandomGenerator>
#include <iostream>
#include <QThreadPool>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>

MainWindow::MainWindow(QWidget *parent) :
            QMainWindow(parent),
            ui(new Ui::MainWindow)
{

    mpController = new Controller();

    // Initialize the main windows interface
    ui->setupUi(this);

    connect(mpController, &Controller::recv_a_point,
            this, &MainWindow::UpdateText);

    connect(ui->actionExit, SIGNAL(triggered(bool)),
            this, SLOT(exitMenu()));

    connect(ui->pushButton, SIGNAL(clicked(bool)),
            this, SLOT(start_measure()));

    // Initialize chart and put it in the gridLayout

    view = new QChartView();
    char1 = new QChart();
    char1->setAnimationOptions(QChart::SeriesAnimations);

    view->setChart(char1);

    ui->gridLayout->addWidget(view, 1, 1);

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::exitMenu()
{
    this->close();
}

void MainWindow::start_measure(){

    measure = new QScatterSeries();
    spline_m = new QSplineSeries();

    measure->setName("Points");
    spline_m->setName("Spline");

    char1->addSeries(measure);
    char1->addSeries(spline_m);
    char1->createDefaultAxes();

    char1->axisY()->setRange(0, 2.5);

    std::cout << "Satrt the measure thread " << std::endl;
    QString *s = new QString("New Thread");
    emit mpController->operate(*s);

    static double xMin = 0;
    static double xMax = 0;
    static double yMin = 0;
    static double yMax = 0;

    connect(measure, &QScatterSeries::pointAdded,
            this, [=](int index){
        double x = measure->at(index).x();
        if(x < xMin || x > xMax){
            if(x < xMin) xMin = x;
            if(x > xMax) xMax = x;
            char1->axisX()->setRange(xMin-5, xMax+5);
        }
    });
}

void MainWindow::UpdateText(const QPointF &p){

    ui->label_2->setText(QString::number(p.y()));
    measure->append(p);
    spline_m->append(p);
    view->update();

}


