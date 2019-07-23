#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();

    this->setCentralWidget(new QWidget);
    centralWidget()->setLayout( mainLayout );

    command.checkState();

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

    connect(pbConnect, &QPushButton::clicked, &command, &Command::connectVPN);
    connect(pbDisconnect, &QPushButton::clicked, &command, &Command::disconnectVPN);
    connect(&command, &Command::connectedToVPN, this, &MainWindow::connected);
    connect(&command, &Command::disconnectedFromVPN, this, &MainWindow::disconnected);

    teDebugArea = new QTextEdit;
    teDebugArea->setReadOnly(true);

    connect(&command, &Command::commandOutput, teDebugArea, &QTextEdit::append);

    mainLayout->addWidget(teDebugArea);
    mainLayout->addWidget(swConnection);
}
