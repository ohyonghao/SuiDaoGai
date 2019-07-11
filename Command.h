#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QProcess>

class Command: public QObject
{
    Q_OBJECT

public:
    Command();

public slots:
    void connectVPN();
    void disconnectVPN();
signals:
    void connectedToVPN();
    void disconnectedFromVPN();
    void commandOutput(const QString&);
private:
    const QString cName= "/usr/share/speedify/speedify_cli";
};

#endif // COMMAND_H
