#include "JsonVPNState.h"

#include <QJsonDocument>
#include <QJsonArray>

#include <vector>
#include <utility>
#include <iostream>
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
    cout << "readConnectionJSON" << endl;
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
    state = CONNECTED;
    emit ConnectedToVPN();
    emit VPNStateChanged();

}

void JsonVPNState::readDisconnectJSON(const QJsonDocument &djson ){

    readStateJSON(djson);
}

void JsonVPNState::readStatJSON(const QJsonDocument &/*djson*/ ){
    // Not implemented
}

void JsonVPNState::readStateJSON(const QJsonDocument &djson){
    cout << "readStateJSON" << endl;
    if( !djson["state"].isUndefined() ){
        cout << "reading state: " << djson["state"].toString().toStdString() << endl;
        bool stateChanged = false;
        if( djson["state"] == "LOGGED_IN" && state != LOGGED_IN ){
            auto prevstate = state;
            state = LOGGED_IN;
            stateChanged = true;
            if(prevstate == CONNECTED ){
                emit DisconnectedFromVPN();
            }
        }else if( djson["state"] == "CONNECTED" && state != CONNECTED ){
            state = CONNECTED;
            emit ConnectedToVPN();
            stateChanged = true;
        }else if( djson["state"] != "CONNECTED" && djson["state"] != "LOGGED_IN" && state != UNKNOWN ){
            state = UNKNOWN;
            stateChanged = true;
        }
        if(stateChanged) emit VPNStateChanged( );
    }
}
