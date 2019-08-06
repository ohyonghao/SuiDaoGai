#ifndef JSONVPNSTATE_H
#define JSONVPNSTATE_H

#include <QObject>

enum ConnectionState {
    DISCONNECTED,
    CONNECTED
};

class JsonVPNState: public QObject
{
    Q_OBJECT
public:
    JsonVPNState(QObject *parent);

public slots:
    void readJSON(const QString&);

signals:
    void invalidJSON();
    void stateChanged(ConnectionState state);
};

#endif // JSONVPNSTATE_H
