#include "Command.h"
#include <QProcess>

Command::Command()
{

}

void Command::connectVPN(){
    QProcess process;
    process.setProgram(cName);
    process.setArguments(QStringList() << "connect" << "gb");
    process.start();
}

void Command::disconnectVPN(){

}
