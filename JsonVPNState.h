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

    JsonVPNState::ConnectionState currentState() const{return state;}
    const QString& getFriendlyName() const{return friendlyName;}
    const QString& getTag() const{return tag;}

signals:
    void VPNStateChanged();
    void ConnectedToVPN();
    void DisconnectedFromVPN();
public slots:
    void readConnectionJSON( const QJsonDocument& djson );
    void readStateJSON( const QJsonDocument& djson );
    void readStatJSON( const QJsonDocument& djson );
    void readDisconnectJSON( const QJsonDocument& djson);

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
