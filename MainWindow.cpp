#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();

    this->setCentralWidget(new QWidget);
    centralWidget()->setLayout( mainLayout );
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupUI(){
    mainLayout = new QVBoxLayout;
    pbConnect = new QPushButton(tr("Connect"));
    pbDisconnect = new QPushButton(tr("Disconnect"));
    swConnection = new QStackedWidget;

    swConnection->addWidget(pbConnect);
    swConnection->addWidget(pbDisconnect);

    connect(pbConnect, &QPushButton::clicked, &controller, &VPNController::ConnectToVPN);
    connect(pbDisconnect, &QPushButton::clicked, &controller, &VPNController::DisconnectFromVPN);
    connect(&controller, &VPNController::ConnectedToVPN, this, &MainWindow::connected);
    connect(&controller, &VPNController::DisconnectedFromVPN, this, &MainWindow::disconnected);

    teDebugArea = new QTextEdit;
    teDebugArea->setReadOnly(true);

    connect(&controller, &VPNController::CommandOutput, teDebugArea, &QTextEdit::append);

    mainLayout->addWidget(teDebugArea);
    mainLayout->addWidget(swConnection);
}
