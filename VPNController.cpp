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
    cout << "processOutput" << endl;
    emit CommandOutput(QString::fromStdString(djson.toJson().toStdString()));
}
