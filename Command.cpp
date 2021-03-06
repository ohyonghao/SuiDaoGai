#include "Command.h"

#include <QProcess>
#include <QJsonDocument>

#include <iostream>
using namespace std;

Command::Command(QObject *parent):
    QObject{parent}

{
}
QJsonDocument Command::runCommand( QStringList& parameters ){
    shared_ptr<QProcess> process = make_shared<QProcess>();
    process->setProgram(cName);
    process->setArguments(parameters);
    process->start();
    process->waitForFinished();
    auto djson = QJsonDocument::fromJson(process->readAllStandardOutput());

    QString json(djson.toJson().toStdString().data());
    cout << json.toStdString() << endl;
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
        emit connectCommandOutput(djson);
    }else{
        checkState();
    }
    QString json(djson.toJson().toStdString().data());
    cout << json.toStdString() << endl;
}

void Command::disconnectVPN(){
    auto djson = runCommand(QStringList() << "disconnect");
    emit disconnectCommandOutput(djson);
}

void Command::checkState(){
    auto djson = runCommand(QStringList() << "state");
    emit stateCommandOutput(djson);
    if( !djson["country"].isUndefined() ){
        emit connectCommandOutput(djson);
    }
    if( !djson["errorMessage"].isUndefined() ){
        checkState();
    }
    if( !djson["state"].isUndefined() && djson["state"] == "CONNECTING" ){
        checkState();
    }
}
