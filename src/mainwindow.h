#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "renamermodel.h"
#include "operationmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(RenamerModel *renamerModel,
                        OperationModel *operationModel,
                        QWidget *parent = 0);
    ~MainWindow();
    void setRenamerModel(RenamerModel *model);

private slots:
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();
    void on_renameButton_clicked();
    void on_previewButton_clicked();
    void on_clearAllButton_clicked();
    void dirModel_operationCompleted(QString message);

private:
    Ui::MainWindow *ui;
    RenamerModel *m_renamerModel;
    OperationModel *m_operationModel;
};

#endif // MAINWINDOW_H
