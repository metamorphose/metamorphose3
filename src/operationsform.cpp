#include <QtCore/QtDebug>
#include "operationsform.h"
#include "ui_operationsform.h"
#include "operation/insertform.h"

OperationsForm::OperationsForm(OperationFormModel *operationFormModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OperationsForm)
{
    m_operationFormModel = operationFormModel;

    ui->setupUi(this);

    ui->operationsTable->setModel(m_operationFormModel);
    ui->operationsTable->resizeColumnsToContents();
}

OperationsForm::~OperationsForm()
{
    delete ui;
}

void OperationsForm::on_addOperation_activated(int index)
{
    switch (index) {
    case 1: {
        qDebug() << "add new InsertForm";
        InsertForm *insertForm = new InsertForm(this);
        m_operationFormModel->addOperation(insertForm);

        ui->operationsView->addWidget(insertForm);
        int count = ui->operationsView->count() - 1;
        ui->operationsView->setCurrentIndex(count);

        ui->operationsTable->resizeColumnsToContents();
        break;
    }
    case 2: {
        break;
    }
    case 3: {
        break;
    }
    default:
        break;
    }
    // reset the combo box
    ui->addOperation->setCurrentIndex(0);
}

void OperationsForm::on_operationsTable_activated(const QModelIndex &index)
{
    int row = index.row();
    qDebug() << "activated operation at row" << row;
    ui->operationsView->setCurrentIndex(row);
}
