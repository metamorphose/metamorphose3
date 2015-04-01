#include "operationsform.h"
#include "ui_operationsform.h"
#include "operation/insertform.h"

OperationsForm::OperationsForm(OperationFormModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OperationsForm)
{
    operationFormModel = model;
    connect(operationFormModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
            this, SLOT(operationFormModel_rowsInserted()));

    ui->setupUi(this);

    ui->operationsTable->setModel(operationFormModel);
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
        InsertForm *insertForm = new InsertForm(this);
        operationFormModel->addOperationForm(insertForm);

        ui->operationsView->addWidget(insertForm);
        int selectedOp = ui->operationsView->count() - 1;

        ui->operationsView->setCurrentIndex(selectedOp);
        ui->operationsTable->selectRow(selectedOp);
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
    qCDebug(M3GUI) << "activated operation at row" << row;
    ui->operationsView->setCurrentIndex(row);
}

void OperationsForm::operationFormModel_rowsInserted()
{
    setActionsEnabled(true);
}

void OperationsForm::setActionsEnabled(bool enable)
{
    if (enable && operationFormModel->rowCount() > 1) {
        //ui->moveOpDown->setEnabled(true);
        //ui->moveOpUp->setEnabled(true);
    }
    else {
        ui->moveOpUp->setEnabled(false);
        ui->moveOpUp->setEnabled(false);
    }
    ui->deleteOperation->setEnabled(enable);
    ui->applyLabel->setEnabled(enable);
    ui->applyToName->setEnabled(enable);
    ui->applyToExtension->setEnabled(enable);
}

void OperationsForm::on_deleteOperation_activated(int index)
{
    switch (index) {
    // delete a single operation
    case 0: {
        int currentOpIndex = ui->operationsView->currentIndex();
        operationFormModel->removeRows(currentOpIndex, 1);

        int opCount = operationFormModel->rowCount();
        if (opCount > 0) {
            ui->operationsView->setCurrentIndex(opCount - 1);
        }
        else {
            setActionsEnabled(false);
        }
        break;
    }
    // delete all operations
    case 1: {
        operationFormModel->removeRows(0, operationFormModel->rowCount());
        setActionsEnabled(false);
        break;
    }
    default:
        break;
    }
    // reset the combo box
    ui->deleteOperation->setCurrentIndex(0);
}

void OperationsForm::on_applyToName_clicked(bool checked)
{
    int row = ui->operationsView->currentIndex();
    OperationFormItem *opForm = operationFormModel->getOperationAt(row);
    opForm->applyToName = checked;
}

void OperationsForm::on_applyToExtension_clicked(bool checked)
{
    int row = ui->operationsView->currentIndex();
    OperationFormItem *opForm = operationFormModel->getOperationAt(row);
    opForm->applyToExtension = checked;
}
