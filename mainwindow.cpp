// Custom interfaces
#include <mainwindow.h>
#include <ui_mainwindow.h>
//#include <workerthread.h>
#include <worker.h>
#include <controller.h>

// Qt includes
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QRandomGenerator>
#include <iostream>
#include <QThreadPool>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>

MainWindow::MainWindow(QWidget *parent) :
            QMainWindow(parent),
            ui(new Ui::MainWindow),
            mpController(std::make_unique<Controller>())
{
    static double xMin = 0;
    static double xMax = 10;

    // Initialize the main windows interface
    ui->setupUi(this);

    connect(mpController, &Controller::SignalForwardResult,
            this, &MainWindow::UpdateText);

    connect(ui->actionExit, SIGNAL(triggered(bool)),
            this, SLOT(exitMenu()));

    connect(ui->pushButton, SIGNAL(clicked(bool)),
            this, SLOT(start_measure()));



    // Initialize chart and put it in the gridLayout
    measure = new QScatterSeries();
    spline_m = new QSplineSeries();
    view = new QChartView();
    char1 = new QChart();

    measure->setName("Points");
    spline_m->setName("Spline");
    char1->addSeries(measure);
    char1->addSeries(spline_m);
    char1->createDefaultAxes();
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

    std::cout << "Satrt the measure thread " << std::endl;
    QString *s = new QString("New Thread");
    emit mpController->operate(*s);

}

void MainWindow::UpdateText(int i){
    ui->textEdit->setText(QString::number(i));
}






//mainwindow.cpp:34:5: error: no matching member function for call to 'connect'
//qobject.h:217:43: note: candidate function [with Func1 = void (Controller::*)(const QString &), Func2 = void (MainWindow::*)()] not viable: no known conversion from 'std::unique_ptr<Controller>' to 'const typename QtPrivate::FunctionPointer<void (Controller::*)(const QString &)>::Object *' (aka 'const Controller *') for 1st argument
//qobject.h:197:36: note: candidate function not viable: no known conversion from 'std::unique_ptr<Controller>' to 'const QObject *' for 1st argument
//qobject.h:200:36: note: candidate function not viable: no known conversion from 'std::unique_ptr<Controller>' to 'const QObject *' for 1st argument
//qobject.h:443:41: note: candidate function not viable: no known conversion from 'std::unique_ptr<Controller>' to 'const QObject *' for 1st argument
//qobject.h:258:13: note: candidate template ignored: requirement '!QtPrivate::FunctionPointer<void (MainWindow::*)()>::IsPointerToMemberFunction' was not satisfied [with Func1 = void (Controller::*)(const QString &), Func2 = void (MainWindow::*)()]
//qobject.h:297:13: note: candidate template ignored: requirement 'QtPrivate::FunctionPointer<void (MainWindow::*)()>::ArgumentCount == -1' was not satisfied [with Func1 = void (Controller::*)(const QString &), Func2 = void (MainWindow::*)()]
//qobject.h:249:13: note: candidate function template not viable: requires 3 arguments, but 4 were provided
//qobject.h:289:13: note: candidate function template not viable: requires 3 arguments, but 4 were provided








