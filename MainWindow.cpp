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
 * 1. Reading json information and printing into a textarea
 * 2. Tracking state
 * 3. Disconnect/Connect
 * 4. Server Selection
 * 5. Settings
 *  i. Include location of speedify_cli
 * 6. Login/Logout
 * 7. Telemetrics
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      json{new QJsonDocument},
      ljson{new QLabel()}
{
    // For now we're setting the central widget to the label
    this->setCentralWidget(ljson);

    // Hardcode the json first, then work on reading in from speedify
    QByteArray fjson("{\n"
                     "\"tag\":  \"gb-london-18\",\n"
                     "\"friendlyName\": \"Great Britain - London #18\",\n"
                     "\"country\":      \"gb\",\n"
                     "\"city\": \"london\",\n"
                     "\"num\":  18,\n"
                     "\"isPrivate\":    false,\n"
                     "\"torrentAllowed\":       false,\n"
                     "\"publicIP\":     [\"206.189.23.67\"]\n"
                    "}");
    *json = json->fromJson(fjson);
    ljson->setText(json->toJson());
}

MainWindow::~MainWindow()
{

}
