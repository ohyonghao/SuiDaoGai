#ifndef JSONVPNSTATE_H
#define JSONVPNSTATE_H

#include <QObject>
class JsonVPNState: public QObject
{
    Q_OBJECT

public:
    enum ConnectionState {
        UNKNOWN,
        LOGGED_IN,
        CONNECTED
    };

    Q_ENUM(ConnectionState)

    JsonVPNState(QObject *parent);

public slots:
    void readJSON(const QString&);

signals:
    void invalidJSON();
    void stateChanged(ConnectionState state);
};

#endif // JSONVPNSTATE_H
