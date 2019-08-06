#include "Command.h"
#include <QProcess>
#include <iostream>
using namespace std;

Command::Command()
{

}
shared_ptr<QProcess> Command::runCommand( QStringList& parameters ){
    cout << "RunCommand" << endl;
    shared_ptr<QProcess> process = make_shared<QProcess>();
    process->setProgram(cName);
    process->setArguments(parameters);
    process->start();
    process->waitForFinished();
    cout << process->readAllStandardOutput().toStdString();
    emit commandOutput(process->readAllStandardOutput());
    return process;
}
void Command::connectVPN(){
    QStringList params;
    params << "connect" << _servername;
    if( _servernumber > -1 )
        params << QString::number(_servernumber);
    auto process = runCommand( params );
    // parse results
    emit connectedToVPN();
}

void Command::disconnectVPN(){
    auto process = runCommand(QStringList() << "disconnect");
    emit disconnectedFromVPN();
}

void Command::checkState(){
    auto process = runCommand(QStringList() << "state");
}
