#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QTextEdit>

#include "Command.h"

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

    Command command;
public slots:
    void connected(){ swConnection->setCurrentWidget(pbDisconnect);}
    void disconnected(){ swConnection->setCurrentWidget(pbConnect);}
};

#endif // MAINWINDOW_H
