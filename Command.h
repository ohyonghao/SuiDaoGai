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

signals:
    void connectedToVPN();
    void disconnectedFromVPN();
    void commandOutput(const QJsonDocument);
    void connectCommandOutput(const QJsonDocument);
    void disconnectCommandOutput(const QJsonDocument);
    void stateCommandOutput(const QJsonDocument);
private:

    const QString cName= "/usr/share/speedify/speedify_cli";

    QJsonDocument runCommand( QStringList& parameters );

    QString _servername;
    int _servernumber;
};

#endif // COMMAND_H
