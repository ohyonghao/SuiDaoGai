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

}

void JsonVPNState::readJSON( const QJsonDocument &djson ){
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


}
