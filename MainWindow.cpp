#include "MainWindow.h"

#include <QAction>
#include <QMenu>
#include <QApplication>

#include "JsonVPNState.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createMenu();
    setupUI();
    createTrayIcon();

    this->setCentralWidget(new QWidget);
    centralWidget()->setLayout( mainLayout );
    controller.CheckState();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupUI(){
    mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    pbConnect = new QPushButton(tr("Connect"));
    pbDisconnect = new QPushButton(tr("Disconnect"));
    swConnection = new QStackedWidget;
    status = new QLabel(tr("Unknown"));

    swConnection->addWidget(pbConnect);
    swConnection->addWidget(pbDisconnect);

    connect(pbConnect, &QPushButton::clicked, &controller, &VPNController::ConnectToVPN);
    connect(pbConnect, &QPushButton::clicked, this, &MainWindow::disableConnectionButtons);
    connect(pbDisconnect, &QPushButton::clicked, &controller, &VPNController::DisconnectFromVPN);
    connect(pbDisconnect, &QPushButton::clicked, this, &MainWindow::disableConnectionButtons);

    connect(&controller, &VPNController::VPNStateChanged, this, &MainWindow::VPNStateChanged);
    connect(&controller, &VPNController::ConnectedToVPN, this, &MainWindow::connected);
    connect(&controller, &VPNController::DisconnectedFromVPN, this, &MainWindow::disconnected);
    connect(&controller, &VPNController::ConnectedToVPN, this, &MainWindow::enableConnectionButtons);
    connect(&controller, &VPNController::DisconnectedFromVPN, this, &MainWindow::enableConnectionButtons);

    teDebugArea = new QTextEdit;
    teDebugArea->setReadOnly(true);

    connect(&controller, &VPNController::CommandOutput, teDebugArea, &QTextEdit::append);
    mainLayout->addWidget(teDebugArea);
    mainLayout->addWidget(swConnection);
    mainLayout->addWidget(status);
}
void MainWindow::createMenu(){
    menuBar = new QMenuBar;
    fileMenu = new QMenu(tr("&File"), this);

    QAction *action;
    action = fileMenu->addAction(tr("S&ettings"));
    action->setDisabled(true);
    action = fileMenu->addAction(tr("C&lose Window"));
    connect(action, &QAction::triggered, this, &QMainWindow::close);
    action = fileMenu->addAction(tr("E&xit"));
    connect(action, &QAction::triggered, this, &QApplication::quit);

    menuBar->addMenu(fileMenu);

}
void MainWindow::createTrayIcon(){
    sysTrayIcon = new QSystemTrayIcon(QIcon("./unknown.png"));
    connect( sysTrayIcon, &QSystemTrayIcon::activated, this, QOverload<QSystemTrayIcon::ActivationReason>::of(&MainWindow::onShowHide));

    QAction *aQuit = new QAction( tr("Exit"), sysTrayIcon );
    connect( aQuit, &QAction::triggered, this, &MainWindow::onExit );

    QAction *aHide = new QAction( tr("Show/Hide") , sysTrayIcon );
    connect( aHide, &QAction::triggered, this, QOverload<bool>::of(&MainWindow::onShowHide ) );

    QMenu *mTrayMenu = new QMenu;
    mTrayMenu->addAction( aHide );
    mTrayMenu->addAction( aQuit );

    sysTrayIcon->setContextMenu( mTrayMenu );

    sysTrayIcon->show();
}

void MainWindow::onShowHide(QSystemTrayIcon::ActivationReason reason){
    if( reason != QSystemTrayIcon::DoubleClick){
        return;
    }

    if( isVisible() ){
        hide();
    }else{
        show();
        raise();
        setFocus();
    }
}

void MainWindow::onShowHide(bool /*triggered*/ ){
    onShowHide(QSystemTrayIcon::DoubleClick);
}

void MainWindow::onExit(bool /*triggered*/){
    QApplication::quit();
}

void MainWindow::updateStatus( QString message ){
    status->setText(message);
}

void MainWindow::setIcon(QString icon){
    cout << "Set Icon to " << icon.toStdString() << endl;
    sysTrayIcon->setIcon(QIcon(icon));
    setWindowIcon(QIcon(icon));
}

void MainWindow::VPNStateChanged(){
    // Get the new information and update the UI
    auto& model = controller.getModel();
    switch(model.currentState() ){
    case JsonVPNState::CONNECTED:
        setIcon("./connected.png");
        updateStatus( tr("Connected - %1" ).arg(model.getFriendlyName()) );
        break;
    case JsonVPNState::LOGGED_IN:
        setIcon("./unknown.png");
        updateStatus( tr( "Logged In - Disconnected" ) );
        break;
    case JsonVPNState::UNKNOWN:
        setIcon("./unknown.png");
        updateStatus( tr( "Unknown") );
    }
}

void MainWindow::disableConnectionButtons(){
    swConnection->setDisabled(true);
}

void MainWindow::enableConnectionButtons(){
    swConnection->setDisabled(false);
}
