#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "core/renamermodel.h"
#include "operationformmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(RenamerModel *renamerModel,
                        OperationFormModel *operationFormModel,
                        QWidget *parent = 0);
    ~MainWindow();
    void allowPreview(bool allow) const;

private slots:
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();
    void on_renameButton_clicked();
    void on_previewButton_clicked();
    void on_clearAllButton_clicked();
    void dirModel_operationCompleted(QString message);

private:
    Ui::MainWindow *ui;
    RenamerModel *renamerModel;
    OperationFormModel *operationFormModel;
};

#endif // MAINWINDOW_H
