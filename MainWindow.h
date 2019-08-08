#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QTextEdit>
#include <QSystemTrayIcon>

#include "VPNController.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    void createTrayIcon();
    void setIcon( QString icon );

    // Layout
    QVBoxLayout *mainLayout;
    QPushButton *pbConnect;
    QPushButton *pbDisconnect;

    QStackedWidget *swConnection;

    QTextEdit *teDebugArea;

    QLabel *status;

    QSystemTrayIcon *sysTrayIcon;

    VPNController controller;
public slots:
    void connected(){ swConnection->setCurrentWidget(pbDisconnect); swConnection->setEnabled(true);}
    void disconnected(){ swConnection->setCurrentWidget(pbConnect); swConnection->setEnabled(true);}
    void updateStatus(QString message);
    void VPNStateChanged();

private slots:
    void onShowHide(QSystemTrayIcon::ActivationReason);
    void onShowHide( bool /*triggered*/);
    void onExit( bool /*triggered*/ );
};

#endif // MAINWINDOW_H
