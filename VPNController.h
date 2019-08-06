#ifndef VPNCONTROLLER_H
#define VPNCONTROLLER_H

#include <QObject>
#include <QDebug>

#include <functional>
#include <iostream>
using namespace std;

#include "VPNProcessor.h"
#include "JsonVPNState.h"

class VPNController : public QObject
{
    Q_OBJECT
public:
    explicit VPNController(QObject *parent = nullptr);

private:
    VPNProcessor processor;

signals:
    void stateChanged(ConnectionState);
    void ConnectedToVPN();
    void DisconnectedFromVPN();
    void CommandOutput(QString);
public slots:
    void ConnectToVPN(){ processor.QueueProcess(std::mem_fn(&VPNProcessor::ConnectToVPN)); }
    void DisconnectFromVPN(){ processor.QueueProcess(std::mem_fn(&VPNProcessor::DisconnectFromVPN)); }

};

#endif // VPNCONTROLLER_H
