#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit->append("<b>Информация о системе:</b>");
    ui->textEdit->append("Количество потоков: <font color='blue'>" + QString::number(QThread::idealThreadCount()) + "</font>");

    for(int i = 1; i< QThread::idealThreadCount()+1; i++)
    {
        ui->comboBox->addItem(QString::number(i));
    }

    w = new DownLoaderWorker();
    th = new QThread;


    connect(ui->lineEdit,&QLineEdit::editingFinished,this,[this](){
        if(ui->lineEdit->text().isEmpty() || !QUrl(ui->lineEdit->text()).isValid()) return;

        emit GetCorrectURL(QUrl(ui->lineEdit->text()));

    });

    connect(this,&MainWindow::GetCorrectURL,w,&DownLoaderWorker::setUrl,Qt::QueuedConnection);

    connect(ui->comboBox,&QComboBox::activated,w,&DownLoaderWorker::setThread,Qt::QueuedConnection);

    connect(ui->pushButton,&QPushButton::clicked,w,&DownLoaderWorker::SuccefulSaveData);

    connect(w,&DownLoaderWorker::GetInfo,[this](const auto& info){
        ui->textEditLog->append(info);
    });
    connect(w,&DownLoaderWorker::getSize,this,[this](quint64 c){
        ui->progressBar->setValue(c);
    });



    connect(ui->btnLetsGoy,&QPushButton::clicked,this,[this](){

        w->downloadFile();

    });

    w->moveToThread(th);

    th->start();
}

MainWindow::~MainWindow()
{
    th->quit();
    th->wait();
    delete w;
    delete th;
    delete ui;
}
