#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "xfreerdp.h"
#include <QDebug>
#include <QThread>
#include <QMessageBox>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditServer->setText("192.168.192.28");
    ui->lineEditUsername->setText("Administrator");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::errorString(QString err){

}

void MainWindow::stdoutevent(){
  qDebug("stdout signal recived");
}

void MainWindow::on_connectBtn_clicked()
{/*
  freerdpgui::XFreeRDP rdp_connection  freerdpgui::XFreeRDP::XFreeRDP(ui->lineEditServer->text(),
                                                                       ui->lineEditUsername->text());*/
  QThread * thread = new QThread;
  freerdpgui::XFreeRDP * rdp_connection = new freerdpgui::XFreeRDP(ui->lineEditServer->text(), ui->lineEditUsername->text(), this);
  rdp_connection->set_password(ui->lineEditPassword->text());

  rdp_connection->moveToThread(thread);
  connect(rdp_connection, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
  connect(thread, SIGNAL(started()), rdp_connection, SLOT(Connect()));
  connect(rdp_connection, SIGNAL(finished()), thread, SLOT(quit()));
  connect(rdp_connection, SIGNAL(finished()), thread, SLOT(deleteLater()));
  connect(rdp_connection, SIGNAL(stdoutevent()), this, SLOT(stdoutevent()));
  thread->start();

//  try{
//    rdp_connection.Connect();
//  }
//  catch(std::runtime_error e){
//    std::cerr << e.what() << "\n";
//  }

}
