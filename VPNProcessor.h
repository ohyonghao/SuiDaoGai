#ifndef VPNPROCESSOR_H
#define VPNPROCESSOR_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
#include <QFunctionPointer>
#include <QMutexLocker>
#include <QJsonDocument>

#include "Command.h"

class VPNProcessor : public QThread
{
    Q_OBJECT
public:
    explicit VPNProcessor(QObject *parent = nullptr);
    ~VPNProcessor() override;
signals:
    void commandProcessed();
    void commandOutput(const QJsonDocument);
    void connectCommandOutput(const QJsonDocument);
    void disconnectCommandOutput(const QJsonDocument);
    void stateCommandOutput(const QJsonDocument);
public slots:
    void setServerName(QString servername);
    void setServerNumber(int servernumber);

protected:
    void run() override;

private:
    QMutex mutex;
    QMutex qmutex;

    QWaitCondition condition;

    Command _command;

    bool restart;
    bool abort;

    QString _servername;
    int _servernumber;

public:
    void restartThread();
    // Processing functions
    void ConnectToVPN();
    void DisconnectFromVPN();
    void GetCurrentState();

    typedef decltype(std::mem_fn<void(), VPNProcessor>(&VPNProcessor::ConnectToVPN)) pmf;
    void QueueProcess(pmf process){ _queueProcess(process);}
private:

    QQueue<pmf> queued;
    void _queueProcess(pmf process);
    void _connectCommandSignals();
};

#endif // VPNPROCESSOR_H
