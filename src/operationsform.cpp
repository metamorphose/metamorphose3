#include "operationsform.h"
#include "ui_operationsform.h"
#include "operation/insertform.h"

OperationsForm::OperationsForm(OperationFormModel *model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OperationsForm)
{
    operationFormModel = model;

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
        ui->gridLayout->addWidget(insertForm, 1, 1, 2, ui->gridLayout->columnCount() - 1);
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

    ui->operationsTable->resizeColumnsToContents();
    int selectedOp = operationFormModel->rowCount() - 1;
    showOperation(selectedOp);
    setActionsEnabled(true);
}

void OperationsForm::showOperation(const int row)
{
    for (int i = 0; i < operationFormModel->rowCount(); ++i) {
        OperationFormItem *opForm = operationFormModel->getOperationAt(i);
        opForm->setVisible(false);
    }
    OperationFormItem *opForm = operationFormModel->getOperationAt(row);
    ui->applyToName->setChecked(opForm->applyToName);
    ui->applyToExtension->setChecked(opForm->applyToExtension);
    opForm->setVisible(true);

    ui->operationsTable->selectRow(row);
}

void OperationsForm::on_operationsTable_clicked(const QModelIndex &index)
{
    int row = index.row();
    showOperation(row);
    qCDebug(M3GUI) << "activated operation at row" << row;
}

void OperationsForm::setActionsEnabled(const bool enable)
{
    if (enable && operationFormModel->rowCount() > 1) {
        ui->moveOpDown->setEnabled(true);
        ui->moveOpUp->setEnabled(true);
    }
    else {
        ui->moveOpDown->setEnabled(false);
        ui->moveOpUp->setEnabled(false);
    }
    ui->deleteOperation->setEnabled(enable);
    ui->applyLabel->setEnabled(enable);
    ui->applyToName->setEnabled(enable);
    ui->applyToExtension->setEnabled(enable);
    ui->helpText->setVisible(!enable);
}

void OperationsForm::on_deleteOperation_activated(const int index)
{
    switch (index) {
    // delete a single operation
    case 0: {
        int currentRow = ui->operationsTable->currentIndex().row();
        operationFormModel->removeRows(currentRow, 1);

        int opCount = operationFormModel->rowCount();
        if (opCount < 1) {
            setActionsEnabled(false);
        }
        else {
            showOperation(0);
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
    int row = ui->operationsTable->currentIndex().row();
    OperationFormItem *opForm = operationFormModel->getOperationAt(row);
    opForm->applyToName = checked;
}

void OperationsForm::on_applyToExtension_clicked(bool checked)
{
    int row = ui->operationsTable->currentIndex().row();
    OperationFormItem *opForm = operationFormModel->getOperationAt(row);
    opForm->applyToExtension = checked;
}

void OperationsForm::on_moveOpUp_clicked()
{
    int row = ui->operationsTable->currentIndex().row();
    operationFormModel->moveRow(operationFormModel->parentItem, row,
                                operationFormModel->parentItem, row - 1);
}

void OperationsForm::on_moveOpDown_clicked()
{
    int row = ui->operationsTable->currentIndex().row();
    operationFormModel->moveRow(operationFormModel->parentItem, row,
                                operationFormModel->parentItem, row + 1);
}

