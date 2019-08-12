#include "VPNProcessor.h"

#include <iostream>
using namespace std;

VPNProcessor::VPNProcessor(QObject *parent) :
    QThread{parent},
    restart{false},
    abort{false}
{
    _command.setServerName("gb");
    _connectCommandSignals();
}

VPNProcessor::~VPNProcessor(){
    mutex.lock();
    abort = true;
    condition.wakeOne();
    mutex.unlock();

    wait();
}

void VPNProcessor::setServerName(QString servername){ QMutexLocker locker(&mutex); _command.setServerName(servername);}
void VPNProcessor::setServerNumber(int servernumber){ QMutexLocker locker(&mutex); _command.setServerNumber(servernumber);}

void VPNProcessor::restartThread(){
    if (!isRunning()) {
            start(LowPriority);
    } else {
        condition.wakeOne();
    }
}

void VPNProcessor::ConnectToVPN(){
    QMutexLocker locker(&mutex);
    _command.connectVPN();
}

void VPNProcessor::DisconnectFromVPN(){
    QMutexLocker locker(&mutex);
    _command.disconnectVPN();
}

void VPNProcessor::GetCurrentState(){
    QMutexLocker locker(&mutex);
    _command.checkState();
}
void VPNProcessor::run(){
    forever{
        if( abort )
            return;
        while(!queued.isEmpty()){
            qmutex.lock();
            auto func = queued.takeFirst();
            qmutex.unlock();
            func(this);
            mutex.lock();
            if(queued.isEmpty()){
                condition.wait(&mutex);
            }
            mutex.unlock();
        }
    }
}

void VPNProcessor::_queueProcess(pmf process){
    QMutexLocker locker(&qmutex);
    queued.push_back(process);
    restartThread();
}

void VPNProcessor::_connectCommandSignals(){
    connect( &_command, &Command::commandOutput, this, &VPNProcessor::commandOutput);
    connect( &_command, &Command::connectCommandOutput, this, &VPNProcessor::connectCommandOutput);
    connect( &_command, &Command::disconnectCommandOutput, this, &VPNProcessor::disconnectCommandOutput);
    connect( &_command, &Command::stateCommandOutput, this, &VPNProcessor::stateCommandOutput);
}
