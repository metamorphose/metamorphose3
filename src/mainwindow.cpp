#include <QtCore/QtDebug>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusBar()->showMessage(tr("Ready"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setRenamerModel(RenamerModel *model)
{
    m_renamerModel = model;
    connect(m_renamerModel, SIGNAL(operationCompleted(QString)),
            this, SLOT(dirModel_operationCompleted(QString)));

    ui->tableView->setModel(m_renamerModel);
    ui->tableView->resizeColumnsToContents();

    SelectionParams *selectionParams = new SelectionParams();
    selectionParams->setRenamerModel(m_renamerModel);
    ui->mainTabWidget->insertTab(0, selectionParams, tr("Selection"));
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
    m_renamerModel->applyRenamingRules();
}

void MainWindow::on_renameButton_clicked()
{
    m_renamerModel->renameItems();
}

void MainWindow::on_clearAllButton_clicked()
{
    m_renamerModel->clear();
    ui->tableView->resizeColumnsToContents();
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::dirModel_operationCompleted(QString message)
{
    if (!message.isEmpty()) {
        statusBar()->showMessage(message);
    }
    ui->tableView->resizeColumnsToContents();
}

