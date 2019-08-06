#include "JsonVPNState.h"

#include <QJsonDocument>
#include <QJsonArray>

JsonVPNState::JsonVPNState(QObject *parent):QObject(parent)
{

}

void JsonVPNState::readJSON( const QString &json ){
    // Create a json document
    QJsonDocument djson = QJsonDocument::fromJson(json.toUtf8());

    // Quick check for valid document
    if( djson.isEmpty() ) return;

    // Probably need to check what kind of json
    // we are reading

    if( djson["state"] == "CONNECTED" ){
        emit stateChanged(CONNECTED);
    }else if( djson["state"] == "DISCONNECTED"){
        emit stateChanged(DISCONNECTED);
    }
}
