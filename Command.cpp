#include "Command.h"
#include <QProcess>

using namespace std;

Command::Command()
{

}
shared_ptr<QProcess> Command::runCommand( QStringList& parameters ){
    shared_ptr<QProcess> process = make_shared<QProcess>();
    process->setProgram(cName);
    process->setArguments(parameters);
    process->start();
    process->waitForFinished();
    emit commandOutput(process->readAllStandardOutput());
    return process;
}
void Command::connectVPN(){
    runCommand(QStringList() << "connect" << "gb");
    emit connectedToVPN();
}

void Command::disconnectVPN(){
    runCommand(QStringList() << "disconnect");
    emit disconnectedFromVPN();
}

void Command::checkState(){
    runCommand(QStringList() << "state");
}
