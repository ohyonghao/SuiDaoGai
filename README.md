# SuiDaoGai

This project is a wrapper for a VPN service called Speedify. They provide a Linux CLI upon request which is still in Beta.
This takes the CLI and creates a Qt GUI wrapper around it.

# Contributers
David Post

# Getting the source

You can grab the source from the GitHub repository:

```
git clone https://github.com/ohyonghao/SuiDaoGai.git
```

# Prerequisites

This program is built with Qt 5.13 using Qt Creator IDE 4.9.2.

This also relies on features of C++ available in GCC 4.8.1 version of the C++ compiler.

# Building

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
