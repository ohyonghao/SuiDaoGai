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
QJsonDocument Command::runCommand( QStringList& parameters ){
    cout << "RunCommand" << endl;
    shared_ptr<QProcess> process = make_shared<QProcess>();
    process->setProgram(cName);
    process->setArguments(parameters);
    process->start();
    process->waitForFinished();
    auto djson = QJsonDocument::fromJson(process->readAllStandardOutput());

    cout << djson.toJson().toStdString();
    emit commandOutput(djson);
    return djson;
}
void Command::connectVPN(){
    if(_servername.isEmpty()) return;

    QStringList params;
    params << "connect" << _servername;

    // If we specified a number, append it
    if( _servernumber > -1 )
        params << QString::number(_servernumber);
    auto djson = runCommand( params );

    // parse results

    if( !djson["country"].isUndefined() ){
        emit commandOutput(djson);
        emit connectedToVPN();
        emit stateChanged(JsonVPNState::CONNECTED);
    }
}

void Command::disconnectVPN(){
    auto process = runCommand(QStringList() << "disconnect");
    emit disconnectedFromVPN();
    emit stateChanged(JsonVPNState::LOGGED_IN);
}

void Command::checkState(){
    cout << "CheckState" << endl;
    auto djson = runCommand(QStringList() << "state");

    if( !djson["state"].isUndefined() ){
        cout << "State Changed to " << djson["state"].toString().toStdString() << endl;
        changeState( djson["state"] );
    }else{
        cout << "Undefined" << endl;
    }
}

void Command::changeState(QJsonValue _state){
    QString state = _state.toString();
    cout << "Change State to " << state.toStdString() << endl;
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
