# SuiDaoGai

This project is a wrapper for a VPN service called Speedify. They provide a Linux CLI upon request which is still in Beta.
This takes the CLI and creates a Qt GUI wrapper around it. Running the wrapper it assumes that `speedify_cli` is in the
path. It makes use of creating multiple processes of `speedify_cli` and monitors the JSON output.

# Contributers

David Post

# Build Instructions 
## Getting the source

You can grab the source from the GitHub repository:

```
git clone https://github.com/ohyonghao/SuiDaoGai.git
```

## Prerequisites

This program is built with Qt 5.13 using Qt Creator IDE 4.9.2.

This also relies on features of C++ available in GCC 4.8.1 version of the C++ compiler.

## Building

Build requires a C++ compiler and a Qt 5 environment. A Qt pro file is included in the repository.

Usually this is built is the Qt Creator IDE.

From the command line you can use `qmake` to create a Makefile, then run `make`:

```
qmake
make
./SuiDaoGai-qt
```

# License
This project is relased under the "GPL-3.0 License" found in the `LICENSE` file.

# Road Map

The purpose for this program is to create a Qt frontend to the speedify-cli client
so that we can more easily use this for connecting to the VPN.

To do this we will need the following portions:
 1. json to model
 2. Command to json

## Views
1. Main Window
2. Settings
i. Login
ii. Preferred server list
3. Analysis
4. Transfer
5. Debugging

## Models
1. Tracking statistics
 i. Up/Down transfered amount
 ii. Up/Down Speed
 iii. latency
2. Server selection
3. State of speedify, connected/disconnected, login/out

## Other things to work on and solve
- Make the program go to an icon in the task bar
- Allow for fixing the nameserver

## Milestones
1. Disconnect/Connect
2. Tracking state
3. Server Selection
5. Settings
i. Include location of speedify_cli
6. Login/Logout
7. Telemetrics
