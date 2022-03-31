#include <mainwindow.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QSize *sw = new QSize(720, 512);
    w.setFixedSize(*sw);
    w.show();

    return a.exec();
}
