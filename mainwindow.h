#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Custom Interfaces
#include <worker.h>
#include <controller.h>

// Standard Templates Library
#include <memory>

// Main window interface
#include <QMainWindow>

// Create scatter charts and fit them with splines
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>

// Threads and Mutex variable
#include <QThreadPool>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QPointF>

class Controller;

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Chart
    QChart *char1;
    QChartView *view;
    QScatterSeries *measure;
    QSplineSeries *spline_m;

    // Threads splitting to avoid
    // not-responding status of the
    // main interface
    //std::unique_ptr<Controller> mpController;
    Controller *mpController;


private slots:
    void UpdateText(const QPointF &);
    void exitMenu();
    void start_measure();

};
#endif // MAINWINDOW_H
