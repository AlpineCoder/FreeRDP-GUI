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

void freerdpgui::XFreeRDP::Connect(void)
{
  QString u,p,v;

  u = "/u:" + username_;
  p = "/p:" + password_;
  v = "/v:" + hostname_;

  arguments_ << u;
  arguments_ << p;
  arguments_ << v;

  arguments_ << "/dynamic-resolution";

  process = new QProcess(parent_);

  connect( process, SIGNAL(readyReadStandardOutput()), this, SLOT(readFromStdout()));
  connect( process, SIGNAL(readyReadStandardError()), this, SLOT(readFromStdout()));
  process->startDetached("xfreerdp", arguments_);
  process->waitForFinished(10000);
  delete process;
}

void freerdpgui::XFreeRDP::readFromStdout()
{
  QByteArray * tmp = new QByteArray;
  tmp->append(process->readAllStandardOutput());

  std::cout << tmp->toStdString() << "\n";
}
