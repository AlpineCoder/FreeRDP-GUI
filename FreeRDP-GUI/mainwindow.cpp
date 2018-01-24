#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "xfreerdp.h"
#include <QDebug>

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



void MainWindow::on_connectBtn_clicked()
{/*
  freerdpgui::XFreeRDP rdp_connection  freerdpgui::XFreeRDP::XFreeRDP(ui->lineEditServer->text(),
                                                                       ui->lineEditUsername->text());*/

  freerdpgui::XFreeRDP rdp_connection(ui->lineEditServer->text(), ui->lineEditUsername->text(), this);
  rdp_connection.set_password(ui->lineEditPassword->text());
  try{
    rdp_connection.Connect();
  }
  catch(std::runtime_error e){
    std::cerr << e.what() << "\n";
  }

}
