#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QUrl>
#include"downloaderworker.h"



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
    DownLoaderWorker* w;
    QThread* th;
    QList<QFile*> files;

signals:
    void GetCorrectURL(const QUrl& urlDownload);

};
#endif // MAINWINDOW_H
