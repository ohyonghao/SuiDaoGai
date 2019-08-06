#include "VPNController.h"

VPNController::VPNController(QObject *parent) : QObject(parent)
{
    processor.start();
}
