#include "mainwindow.h"

#include <QApplication>
#include"downloaderworker.h"
#include"RapidFileManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    auto files = std::make_shared<std::vector<std::shared_ptr<QFile>>>();



    w.show();
    return a.exec();
}
