#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QProcess>
#include <QStringList>
#include <QJsonDocument>

#include <memory>

#include "JsonVPNState.h"
class Command: public QObject
{
    Q_OBJECT

public:
    Command(QObject *parent=nullptr);

public slots:
    void connectVPN();
    void disconnectVPN();
    void checkState();
    void setServerNumber(int servernumber){_servernumber = servernumber;}
    void setServerName(QString servername){_servername = servername;}

private slots:
    void _changeState( JsonVPNState::ConnectionState _newstate );

signals:
    void connectedToVPN();
    void disconnectedFromVPN();
    void commandOutput(const QJsonDocument);
    void stateChanged(JsonVPNState::ConnectionState);
private:
    void changeState( QJsonValue state );

    const QString cName= "/usr/share/speedify/speedify_cli";

    std::shared_ptr<QProcess> runCommand( QStringList& parameters );

    QString _servername;
    int _servernumber;

    JsonVPNState::ConnectionState _currentState;
};

#endif // COMMAND_H
