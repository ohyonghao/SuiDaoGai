#include "MainWindow.h"

/*************************************************************************************
 * The purpose for this program is to create a Qt frontend to the speedify-cli client
 * so that we can more easily use this for connecting to the VPN.
 *
 * To do this we will need the following portions:
 *
 * 1. json to model
 * 2. Command to json
 *
 * **** Views ****
 * 1. Main Window
 * 2. Settings
 *  i. Login
 *  ii. Preferred server list
 * 3. Analysis
 * 4. Transfer
 * 5. Debugging
 *
 * **** Models ****
 * 1. Tracking statistics
 *  i. Up/Down transfered amount
 *  ii. Up/Down Speed
 *  iii. latency
 * 2. Server selection
 * 3. State of speedify, connected/disconnected, login/out
 *
 * Other things to work on and solve
 * - Make the program go to an icon in the task bar
 * - Allow for fixing the nameserver
 */

/*************************************************************************************
 * **** Milestones ****
 * 3. Disconnect/Connect
 * 1. Reading json information and printing into a textarea
 * 2. Tracking state
 * 4. Server Selection
 * 5. Settings
 *  i. Include location of speedify_cli
 * 6. Login/Logout
 * 7. Telemetrics
 */

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
