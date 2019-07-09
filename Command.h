#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QProcess>

class Command
{
public:
    Command();

public slots:
    void connectVPN();
    void disconnectVPN();

private:
    const QString cName= "speedify_cli";
};

#endif // COMMAND_H
