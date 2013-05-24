#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

typedef enum{
    MODE_NORMAL,
    MODE_CMD
}MODE;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    MODE mode;
    QString command;

private:
    void initVariables();
    void initEventListeners();
    void runCommand();
    bool isSearch(QChar cmdFlag);
    bool isCmd(QChar cmdFlag);
    void handleCmd();
    void handleSearch();

protected:
    bool eventFilter(QObject *, QEvent *);
private slots:
    void on_actionShow_Panel_triggered();
    void on_actionShow_Toolbar_triggered();
};

#endif // MAINWINDOW_H
