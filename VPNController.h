#ifndef VPNCONTROLLER_H
#define VPNCONTROLLER_H

#include <QObject>
#include <functional>
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
public slots:
    void ConnectToVPN(){processor.QueueProcess(std::mem_fn(&VPNProcessor::ConnectToVPN));}
    void DisconnectFromVPN(){processor.QueueProcess(std::mem_fn(&VPNProcessor::DisconnectFromVPN));}

};

#endif // VPNCONTROLLER_H
