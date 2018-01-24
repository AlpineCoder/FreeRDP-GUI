#ifndef XFREERDP_H
#define XFREERDP_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QProcess>

namespace freerdpgui {
  class XFreeRDP : public QObject
  {
    Q_OBJECT
  public:
    XFreeRDP(QString hostname, QString username, QObject * parent);

    void Connect(void);
    QObject * parent_;
    QProcess * process;
    QString hostname(void){ return hostname_;}
    QString username(void){ return username_;}
    void set_password(const QString & password){password_ = password;}

  public slots:
    void readFromStdout();

  private:
    QString hostname_, username_, password_;
    QStringList arguments_;
  };
} // end of namespace freerdpgui


#endif // XFREERDP_H
