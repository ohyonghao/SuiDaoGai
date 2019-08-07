#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QTextEdit>

#include "VPNController.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();

    // Layout
    QVBoxLayout *mainLayout;
    QPushButton *pbConnect;
    QPushButton *pbDisconnect;

    QStackedWidget *swConnection;

    QTextEdit *teDebugArea;

    QLabel *status;

    VPNController controller;
public slots:
    void connected(){ swConnection->setCurrentWidget(pbDisconnect); swConnection->setEnabled(true);}
    void disconnected(){ swConnection->setCurrentWidget(pbConnect); swConnection->setEnabled(true);}
    void updateStatus(QString message);

private slots:

};

#endif // MAINWINDOW_H
