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

    JsonVPNState(QObject *parent=nullptr);

public slots:
    void readJSON(const QJsonDocument &djson);

private:
    QString servername;
    int servernumber;

    QString friendlyName;
    QString tag;
    QString country;
    QString city;

    bool isPrivate;
    bool torrentAllowed;

    ConnectionState state{UNKNOWN};

};

#endif // JSONVPNSTATE_H
