#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "dirmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();
    void on_previewButton_clicked();
    void on_addDirButton_clicked();
    void on_addFilesButton_clicked();
    void on_renameButton_clicked();
    void on_clearAllButton_clicked();

    void dirModel_operationCompleted(QString message);

    void on_sortButton_clicked();

private:
    Ui::MainWindow *ui;
    DirModel* dirModel;
};

#endif // MAINWINDOW_H
