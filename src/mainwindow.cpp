#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "selectionform.h"
#include "ui_selectionform.h"
#include "operationsform.h"

MainWindow::MainWindow(RenamerModel *renamerModel,
                       OperationFormModel *operationFormModel,
                       QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->renamerModel = renamerModel;
    connect(renamerModel, SIGNAL(operationCompleted(QString)),
            this, SLOT(dirModel_operationCompleted(QString)));

    ui->setupUi(this);

    ui->tableView->setModel(renamerModel);
    ui->tableView->resizeColumnsToContents();

    SelectionForm *selectionForm = new SelectionForm(renamerModel);
    connect(selectionForm, SIGNAL(itemsLoaded(int)),
            this, SLOT(itemsLoaded(int)));

    ui->mainTabWidget->addTab(selectionForm, tr("Selection"));


    this->operationFormModel = operationFormModel;
    OperationsForm *operationsForm = new OperationsForm(this->operationFormModel);
    ui->mainTabWidget->addTab(operationsForm, tr("Renaming"));

    statusBar()->showMessage(tr("Ready"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    exit(0);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox aboutBox (this);
    aboutBox.setIcon(QMessageBox::Information);
    aboutBox.setText("Métamorphose Renamer v3"
                     "\n\nCopyright © 2015 Ianaré Sévi"
                     "\n\nMétamorphose is free software: you can redistribute it and/or modify "
                     "it under the terms of the GNU General Public License as published by "
                     "the Free Software Foundation, either version 3 of the License, or "
                     "(at your option) any later version."
                     "\n\nMétamorphose is distributed in the hope that it will be useful, "
                     "but WITHOUT ANY WARRANTY; without even the implied warranty of "
                     "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."
                     "\nSee the GNU General Public License for more details."
                     );
    aboutBox.setWindowTitle(tr("About Métamorphose"));
    aboutBox.exec();
}

void MainWindow::on_previewButton_clicked()
{
    renamerModel->setOperations(operationFormModel->getConfiguredOps());
    int changedCount = renamerModel->applyRenamingOps();
    if (changedCount > 0) {
        ui->renameButton->setEnabled(true);
    }
}

void MainWindow::on_renameButton_clicked()
{
    renamerModel->renameItems();
}

void MainWindow::on_clearAllButton_clicked()
{
    renamerModel->clearAndDelete();
    ui->tableView->resizeColumnsToContents();
    allowPreview(false);
    ui->renameButton->setEnabled(false);
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::allowPreview(bool allow) const
{
    ui->clearAllButton->setEnabled(allow);
    ui->previewButton->setEnabled(allow);
}

void MainWindow::dirModel_operationCompleted(QString message)
{
    if (!message.isEmpty()) {
        statusBar()->showMessage(message);
    }
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::itemsLoaded(int itemCount)
{
    allowPreview((itemCount != 0));
}

