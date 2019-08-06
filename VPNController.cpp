#include "VPNController.h"

VPNController::VPNController(QObject *parent) : QObject(parent)
{
    _connectVPNProcessorSignals();
    processor.start();
}

void VPNController::_connectVPNProcessorSignals(){
    connect(&processor, &VPNProcessor::stateChanged, this, &VPNController::stateChanged );
}
