#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QProcess>
#include <QStringList>

#include <memory>

#include "JsonVPNState.h"
class Command: public QObject
{
    Q_OBJECT

public:
    Command();

public slots:
    void connectVPN();
    void disconnectVPN();
    void checkState();
    void setServerNumber(int servernumber){_servernumber = servernumber;}
    void setServerName(QString servername){_servername = servername;}
signals:
    void connectedToVPN();
    void disconnectedFromVPN();
    void commandOutput(const QString&);
    void stateChanged(ConnectionState);
private:
    const QString cName= "/usr/share/speedify/speedify_cli";

    std::shared_ptr<QProcess> runCommand( QStringList& parameters );

    QString _servername;
    int _servernumber;
};

#endif // COMMAND_H
