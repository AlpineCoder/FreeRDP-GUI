#include "xfreerdp.h"

#include <memory>
#include <iostream>
#include <QProcess>


freerdpgui::XFreeRDP::XFreeRDP(QString hostname, QString username, QObject *parent):QObject()
{
  hostname_ = hostname;
  username_ = username;
  parent_ = parent;

}

freerdpgui::XFreeRDP::~XFreeRDP(){}

void freerdpgui::XFreeRDP::Connect(void)
{
  QString u,p,v,d;

  p = "/p:" + password_;
  v = "/v:" + hostname_;

  arguments_ << p;
  arguments_ << v;
  arguments_ << "/dynamic-resolution";
  // Accept certificates for now until I found a way to let
  // the user decide.
  arguments_ << "/cert-tofu";

  //check if the username contains a backslash
  //if does we have also a domain paramter to hand
  //over to the process
  if(username_.contains("\\")){
      QStringList tmp = username_.split("\\");
      d = "/d:" + tmp[0];
      u = "/u:" + tmp[1];

      arguments_ << u;
      arguments_ << d;
    }
  else{
      u = "/u:" + username_;
      arguments_ << u;
    }

  process = new QProcess(parent_);

  connect( process, SIGNAL(readyReadStandardOutput()), this, SLOT(readFromStdout()));
  connect( process, SIGNAL(readyReadStandardError()), this, SLOT(readFromStdout()));
  process->start("xfreerdp", arguments_);

  process->waitForStarted(-1);

  process->waitForFinished(-1);
  emit finished();
  delete process;
}

void freerdpgui::XFreeRDP::readFromStdout()
{
  QByteArray * tmp = new QByteArray;
  tmp->append(process->readAllStandardOutput());
  QString qstr(*tmp);
  std::cout << qstr.toStdString() << "\n";
  emit stdoutevent();

  //std::cout << tmp->toStdString() << "\n";
}
