#include "JsonVPNState.h"

#include <QJsonDocument>
#include <QJsonArray>

#include <vector>
#include <utility>
using namespace std;

JsonVPNState::JsonVPNState(QObject *parent):QObject(parent),
    servername{},
    servernumber{-1},
    friendlyName{},
    tag{},
    country{},
    city{},
    isPrivate{false},
    torrentAllowed{false}
{
    qRegisterMetaType<JsonVPNState::ConnectionState>();
}

void JsonVPNState::readConnectionJSON(const QJsonDocument &djson){
    // Create a json document
    vector<pair<QString*,QString>> strings;
    strings.push_back( make_pair(&friendlyName, "friendlyName") );
    strings.push_back( make_pair(&tag,"tag"));
    strings.push_back( make_pair(&country,"country"));
    strings.push_back( make_pair(&city,"city"));
    strings.push_back( make_pair(&servername,"servername"));
    for(auto item: strings ){
        if( !djson[item.second].isUndefined() ){
            *(item.first) = djson[item.second].toString();
        }
    }
    emit VPNStateChanged();

}

void JsonVPNState::readDisconnectJSON(const QJsonDocument &djson ){

    readStatJSON(djson);
}

void JsonVPNState::readStatJSON(const QJsonDocument &/*djson*/ ){
    // Not implemented
}

void JsonVPNState::readStateJSON(const QJsonDocument &djson){
    if( !djson["state"].isUndefined() ){
        QString state = djson["state"].toString();
        bool stateChanged = false;
        if( djson["state"] == "LOGGED_IN" && state != JsonVPNState::LOGGED_IN ){
            auto prevstate = state;
            state = JsonVPNState::LOGGED_IN;
            stateChanged = true;
            if(prevstate == CONNECTED ){
                emit DisconnectedFromVPN();
            }
        }else if( djson["state"] == "CONNECTED" && state != JsonVPNState::CONNECTED ){
            state = JsonVPNState::CONNECTED;
            emit ConnectedToVPN();
            stateChanged = true;
        }else if( state != JsonVPNState::UNKNOWN ){
            state = JsonVPNState::UNKNOWN;
            stateChanged = true;
        }
        if(stateChanged) emit VPNStateChanged( );
    }
}
