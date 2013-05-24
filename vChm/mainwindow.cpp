#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commands.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initVariables();
    initEventListeners();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initVariables(){
    mode = MODE_NORMAL;
    command = "";
}

void MainWindow::initEventListeners(){
    ui->treeWidget->installEventFilter(this);
    ui->textBrowser->installEventFilter(this);
}

bool MainWindow::isSearch(QChar cmdFlag){
    QString searchflags = CMD_FLAG_SEARCH;
    return searchflags.contains(cmdFlag);
}

bool MainWindow::isCmd(QChar cmdFlag){
    QString searchflags = CMD_FLAG_CMD;
    return searchflags.contains(cmdFlag);
}

void MainWindow::runCommand(){
    if (command.isEmpty()) return;
    QString cmd = command.toLower();    // make it to lowercase
    QChar cmdFlag = command.at(0);
    if (isSearch(cmdFlag)){

    }
    else if (isCmd(cmdFlag)){
        if (cmd == CMD_QUIT){
            close();
        }
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    if (event->type() == QEvent::KeyPress){
        QKeyEvent *keyevent = static_cast<QKeyEvent *>(event);
        int key = keyevent->key();
        if (mode == MODE_CMD){
            if (key == Qt::Key_Return){
                runCommand();
                mode = MODE_NORMAL;
                command = "";
            }
            else {
                command += QChar(key);
                statusBar()->showMessage(command.toLower(), 2000);
            }
        }
        else if (isCmd(QChar(key)) || isSearch(QChar(key))){
            mode = MODE_CMD;
            command += QChar(key);
            statusBar()->showMessage(command.toLower(), 2000);
        }
    }
    return true;
}
