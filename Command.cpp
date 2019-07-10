#include "Command.h"
#include <QProcess>

Command::Command()
{

}

void Command::connectVPN(){
    QProcess process;
    process.setProgram(cName);
    process.setArguments(QStringList() << "connect" << "gb");
    process.start();
    process.waitForFinished();
    emit connectedToVPN();
}

void Command::disconnectVPN(){
    QProcess process;
    process.setProgram(cName);
    process.setArguments(QStringList() << "disconnect");
    process.start();
    process.waitForFinished();
    emit disconnectedFromVPN();
}
