#include <QtCore/QtDebug>
#include <QtWidgets/QFileDialog>

#include "selectionparams.h"
#include "ui_selectionparams.h"

SelectionParams::SelectionParams(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectionParams)
{
    ui->setupUi(this);
}

SelectionParams::~SelectionParams()
{
    delete ui;
}

void SelectionParams::setRenamerModel(RenamerModel *model)
{
    m_renamerModel = model;
}

void SelectionParams::on_addDirButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOptions(QFileDialog::ReadOnly
                      | QFileDialog::ShowDirsOnly
                      | QFileDialog::DontResolveSymlinks);
    if (dialog.exec()) {
        m_renamerModel->addDirectories(dialog.selectedFiles(),
                                 ui->addRecursive->isChecked(),
                                 ui->filterNames->text().split(" "),
                                 ui->filterIncludeFiles->isChecked(),
                                 ui->filterIncludeDirs->isChecked(),
                                 ui->filterIncludeHidden->isChecked()
                                 );
    }
}

void SelectionParams::on_addFilesButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setOptions(QFileDialog::ReadOnly
                      | QFileDialog::DontResolveSymlinks);
    dialog.setNameFilter(ui->filterNames->text());
    if (dialog.exec()) {
        m_renamerModel->addFiles(dialog.selectedFiles());
    }
}

void SelectionParams::on_sortButton_clicked()
{
    Qt::SortOrder order;
    if (ui->sortAscending->isChecked()) {
        order = Qt::AscendingOrder;
    }
    else {
        order = Qt::DescendingOrder;
    }
    m_renamerModel->sort(0, order);
}
