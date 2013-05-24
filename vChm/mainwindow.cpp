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
    //ui->textBrowser->installEventFilter(this);
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
        else if (cmd == CMD_TOGGLE_PANEL){
           on_actionShow_Panel_triggered();
        }
        else if (cmd == CMD_TOGGLE_TOOLPANEL){
            on_actionShow_Toolbar_triggered();
        }
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    if (event->type() == QEvent::KeyPress){
        QKeyEvent *keyevent = static_cast<QKeyEvent *>(event);
        int key = keyevent->key();
        bool needUpdateStatus = false;
        if (mode == MODE_CMD){
            if (key == Qt::Key_Return){
                runCommand();
                mode = MODE_NORMAL;
                command = "";
                needUpdateStatus = true;
            }
            else if (key == Qt::Key_Backspace){
                command.chop(1);
                needUpdateStatus = true;
            }
            else {
                command += QChar(key);
                needUpdateStatus = true;
            }
        }
        else if (isCmd(QChar(key)) || isSearch(QChar(key))){
            mode = MODE_CMD;
            command += QChar(key);
            needUpdateStatus = true;
        }
        if (needUpdateStatus) {
            statusBar()->showMessage(command.toLower(), 2000);
        }
    }
    return true;
}

void MainWindow::on_actionShow_Panel_triggered()
{
    ui->treeWidget->setVisible(!ui->treeWidget->isVisible());
    ui->actionShow_Panel->setChecked(ui->treeWidget->isVisible());
}

void MainWindow::on_actionShow_Toolbar_triggered()
{
   ui->mainToolBar->setVisible(!ui->mainToolBar->isVisible());
   ui->actionShow_Toolbar->setChecked(ui->mainToolBar->isVisible());
}
