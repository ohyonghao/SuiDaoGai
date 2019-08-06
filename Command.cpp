#include "Command.h"

#include <QProcess>
#include <QJsonDocument>

#include <iostream>
using namespace std;

Command::Command(QObject *parent):
    QObject{parent},
    _currentState{JsonVPNState::UNKNOWN}

{
    connect(this, &Command::stateChanged, this, &Command::_changeState);
    qRegisterMetaType<JsonVPNState::ConnectionState>();
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
    emit stateChanged(JsonVPNState::CONNECTED);
}

void Command::disconnectVPN(){
    auto process = runCommand(QStringList() << "disconnect");
    emit disconnectedFromVPN();
    emit stateChanged(JsonVPNState::LOGGED_IN);
}

void Command::checkState(){
    auto process = runCommand(QStringList() << "state");

    QJsonDocument djson = QJsonDocument::fromJson(process->readAllStandardOutput());

    if(djson["state"] != QJsonValue::Undefined ){
        changeState( djson["state"] );
    }
}

void Command::changeState(QJsonValue _state){
    QString state = _state.toString();
    if( state == "LOGGED_IN" ){
        emit stateChanged(JsonVPNState::LOGGED_IN);
    }else if( state == "CONNECTED" ){
        emit stateChanged(JsonVPNState::CONNECTED);
    }else {
        emit stateChanged(JsonVPNState::UNKNOWN);
    }
}

void Command::_changeState( JsonVPNState::ConnectionState _newstate ){
    _currentState = _newstate;
}
