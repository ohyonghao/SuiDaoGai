#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonDocument>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>

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

    QJsonDocument *json;
    QLabel *ljson;

};

#endif // MAINWINDOW_H
