#include "VPNProcessor.h"
#include <iostream>
using namespace std;
VPNProcessor::VPNProcessor(QObject *parent) :
    QThread{parent},
    restart{false},
    abort{false}
{
    _queueProcess(std::mem_fn(&VPNProcessor::GetCurrentState) );
    _command.setServerName("gb");
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
            {
                cout << "Running Function" << endl;
                mutex.lock();
                mutex.unlock();
            }
            mutex.lock();
            if(queued.isEmpty()){
                condition.wait(&mutex);
            }
            mutex.unlock();
        }
    }
}

void VPNProcessor::_queueProcess(pmf process){
    cout << "Queued Process" << endl;
    QMutexLocker locker(&qmutex);
    queued.push_back(process);
    restartThread();
}
