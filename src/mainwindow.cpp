#include <QtWidgets/QMessageBox>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dirModel = new DirModel(this);

    ui->tableView->setModel(dirModel);

    statusBar()->showMessage("Ready");
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
    aboutBox.setWindowTitle("About Métamorphose");
    aboutBox.exec();
}

void MainWindow::on_previewButton_clicked()
{
    dirModel->applyRenamingRules();
}

void MainWindow::on_addDirButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOptions(QFileDialog::ReadOnly
                      | QFileDialog::ShowDirsOnly
                      | QFileDialog::DontResolveSymlinks);
    if (dialog.exec()) {
        dirModel->addDirectories(dialog.selectedFiles(), ui->recursiveCheckBox->isChecked());
    }
}

void MainWindow::on_addFilesButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setOptions(QFileDialog::ReadOnly
                      | QFileDialog::DontResolveSymlinks);
    if (dialog.exec()) {
        dirModel->addFiles(dialog.selectedFiles());
    }
}

void MainWindow::on_resetButton_clicked()
{
    dirModel->clear();
}

void MainWindow::on_renameButton_clicked()
{
    dirModel->renameItems();
}
