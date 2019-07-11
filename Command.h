#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QProcess>
#include <QStringList>

#include <memory>

class Command: public QObject
{
    Q_OBJECT

public:
    Command();

public slots:
    void connectVPN();
    void disconnectVPN();
    void checkState();
signals:
    void connectedToVPN();
    void disconnectedFromVPN();
    void commandOutput(const QString&);
private:
    const QString cName= "/usr/share/speedify/speedify_cli";

    std::shared_ptr<QProcess> runCommand( QStringList& parameters );
};

#endif // COMMAND_H
