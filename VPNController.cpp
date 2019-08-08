#include "VPNController.h"

#include <QJsonDocument>

#include <iostream>
using namespace std;

VPNController::VPNController(QObject *parent) : QObject(parent)
{
    _connectVPNProcessorSignals();
    processor.start();
}

void VPNController::_connectVPNProcessorSignals(){
    connect(&processor, &VPNProcessor::stateChanged, this, &VPNController::stateChanged );
    connect(&processor, &VPNProcessor::commandOutput, this, &VPNController::processOutput);
}

void VPNController::processOutput(const QJsonDocument djson){
    cout << "processOutput" << endl;
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
    }
    emit CommandOutput(QString::fromStdString(djson.toJson().toStdString()));
}
