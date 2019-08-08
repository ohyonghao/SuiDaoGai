#include "VPNController.h"

#include <QJsonDocument>

#include <iostream>
using namespace std;

VPNController::VPNController(QObject *parent) : QObject(parent)
{
    _connectVPNProcessorSignals();
    _connectJsonVPNStateSignals();
    processor.start();
}

void VPNController::_connectVPNProcessorSignals(){
    connect(&processor, &VPNProcessor::commandOutput, this, &VPNController::processOutput);
    connect(&processor, &VPNProcessor::connectCommandOutput, &model, &JsonVPNState::readConnectionJSON);
    connect(&processor, &VPNProcessor::disconnectCommandOutput, &model, &JsonVPNState::readDisconnectJSON);
    connect(&processor, &VPNProcessor::stateCommandOutput, &model, &JsonVPNState::readStateJSON);
}
void VPNController::_connectJsonVPNStateSignals(){
    connect(&model, &JsonVPNState::VPNStateChanged, this, &VPNController::VPNStateChanged );
    connect(&model, &JsonVPNState::ConnectedToVPN, this, &VPNController::ConnectedToVPN );
    connect(&model, &JsonVPNState::DisconnectedFromVPN, this, &VPNController::DisconnectedFromVPN );
}

void VPNController::processOutput(const QJsonDocument djson){
    cout << "processOutput" << endl;/*
    if( djson["friendlyName"] != QJsonValue::Undefined ){
        cout << "friendlyName";
        emit UpdateStatus(tr("Connected - %1").arg(djson["friendlyName"].toString()) );
        emit ConnectedToVPN();
    }

    if( djson["state"] != QJsonValue::Undefined ){
        cout << "state" << endl;
        // State message
        if( djson["state"].toString() == "CONNECTED"){
            emit UpdateStatus(tr("Connected"));
            emit ConnectedToVPN();
        }else if( djson["state"].toString( ) == "LOGGED_IN"){
            emit UpdateStatus(tr("Logged In - Disconnected"));
            emit DisconnectedFromVPN();
        }else{
            emit UpdateStatus(tr("Unknown"));
        }
    }*/
    emit CommandOutput(QString::fromStdString(djson.toJson().toStdString()));
}
