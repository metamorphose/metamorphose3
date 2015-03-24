#include <QtCore/QtDebug>
#include <QtWidgets/QFileDialog>

#include "selectionform.h"
#include "ui_selectionform.h"

SelectionForm::SelectionForm(RenamerModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectionForm)
{
    renamerModel = model;
    ui->setupUi(this);
}

SelectionForm::~SelectionForm()
{
    delete ui;
}

void SelectionForm::on_addDirButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOptions(QFileDialog::ReadOnly
                      | QFileDialog::ShowDirsOnly
                      | QFileDialog::DontResolveSymlinks);
    if (dialog.exec()) {
        renamerModel->addDirectories(dialog.selectedFiles(),
                                 ui->addRecursive->isChecked(),
                                 ui->filterNames->text().split(" "),
                                 ui->filterIncludeFiles->isChecked(),
                                 ui->filterIncludeDirs->isChecked(),
                                 ui->filterIncludeHidden->isChecked()
                                 );
    }
}

void SelectionForm::on_addFilesButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setOptions(QFileDialog::ReadOnly
                      | QFileDialog::DontResolveSymlinks);
    dialog.setNameFilter(ui->filterNames->text());
    if (dialog.exec()) {
        renamerModel->addFiles(dialog.selectedFiles());
    }
}

void SelectionForm::on_sortButton_clicked()
{
    Qt::SortOrder order;
    if (ui->sortAscending->isChecked()) {
        order = Qt::AscendingOrder;
    }
    else {
        order = Qt::DescendingOrder;
    }
    renamerModel->sort(0, order);
}
