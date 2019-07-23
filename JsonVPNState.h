#ifndef JSONVPNSTATE_H
#define JSONVPNSTATE_H

#include <QObject>

class JsonVPNState
{
public:
    JsonVPNState();

public slots:
    void readJSON(const QString&);
};

#endif // JSONVPNSTATE_H
