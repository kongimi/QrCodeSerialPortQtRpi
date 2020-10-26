#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QDebug>

QSerialPort serial;
QString bb;
int fin=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial.setPortName("/dev/ttyUSB0");
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.open(QIODevice::ReadWrite);

    connect(&serial,SIGNAL(readyRead()), this,SLOT(serialReceive()));
}

MainWindow::~MainWindow()
{
    delete ui;
    serial.close();
}

void MainWindow::serialReceive()
{
    QByteArray aa;

    aa = serial.readAll();
    for(int i=0;i<aa.length();i++){
        if( (aa[i]!='\r') && (aa[i]!='\n') ){
            bb += aa[i];
        }else{
            fin = 1;
        }
    }

    if(fin==1){
        qDebug() << bb;
        ui->label->setText(bb);
        bb = "";
    }
}
