#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commands.h"
#include <QKeyEvent>
#include <QtWidgets>

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
    isContentLoaded = false;
}

void MainWindow::initEventListeners(){
    ui->centralWidget->installEventFilter(this);
    ui->treeWidget->installEventFilter(this);
//    ui->textBrowser->installEventFilter(this)
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
        else if (cmd == CMD_OPEN_FILE) {
            on_actionOpen_triggered();
        }
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    if (event->type() == QEvent::KeyPress){
        QKeyEvent *keyevent = static_cast<QKeyEvent *>(event);
        int key = keyevent->key();
        QChar ckey = QChar(key);
        bool needUpdateStatus = false;
        if (key == Qt::Key_Return){
            runCommand();
            command = "";
            needUpdateStatus = true;
            isWaitingMoreInput = false;
        }
        else {
            if (key == Qt::Key_Backspace){
                command.chop(1);
                needUpdateStatus = true;
            }
            else if (isWaitingMoreInput){
                command += ckey;
                needUpdateStatus = true;
            }
            else {
                if (isCmd(ckey) || isSearch(ckey)){
                    command += ckey;
                    needUpdateStatus = true;
                }
                else{
                    handleSingleKeyCmd(ckey);
                    statusBar()->showMessage(ckey.toLower(), 2000);
                }
            }

        }
        if (!command.isEmpty()){
            isWaitingMoreInput = true;
        }
        if (needUpdateStatus) {
            statusBar()->showMessage(command.toLower(), 2000);
        }
    }
    return true;
}

void MainWindow::handleSingleKeyCmd(QChar cmd){
    cmd = cmd.toLower();
    if (cmd == CMD_DOWN_A_LINE){
        QTextCursor cursor = ui->textBrowser->textCursor();
        cursor.movePosition(QTextCursor::Down);
        ui->textBrowser->setTextCursor(cursor);
    }
    else if (cmd == CMD_UP_A_LINE){
        QTextCursor cursor = ui->textBrowser->textCursor();
        cursor.movePosition(QTextCursor::Up);
        ui->textBrowser->setTextCursor(cursor);
    }
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

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this);
    if (filename.isEmpty()){

    }
    else{
        // read the content of the file
        setWindowFilePath(filename);
        QString ftitle = filename.split('/').last();
        setWindowTitle(ftitle + "-" + "vChm");
        loadContentAndShow(filename);
    }
}

void MainWindow::loadContentAndShow(const QString fileName){
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this, "can't read the file", file.errorString());
    }
    QTextStream in(&file);
    QString cont = in.readAll();
    ui->textBrowser->document()->setHtml(cont);
    isContentLoaded = true;
}
