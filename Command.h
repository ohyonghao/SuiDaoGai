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
private:
    const QString cName= "speedify_cli";
};

#endif // COMMAND_H
