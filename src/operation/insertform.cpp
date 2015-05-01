#include "operation/insertform.h"
#include "ui_insertform.h"
#include "ui_operationformitem.h"

InsertForm::InsertForm(QWidget *parent) :
    OperationFormItem(parent),
    ui(new Ui::InsertForm)
{
    qCDebug(M3GUI) << "init InsertForm";

    insertOperation = new InsertOperation();

    ui->setupUi(formItemUi->operation);
    init(ui->toInsert);

    ui->positionSelection->setId(ui->asPrefix, 0);
    ui->positionSelection->setId(ui->asSuffix, 1);
    ui->positionSelection->setId(ui->atPosition, 2);
}

InsertForm::~InsertForm()
{
    delete ui;
}

/**
 * Handle enabling the postion spinner.
 */
void InsertForm::on_positionSelection_buttonClicked(int id)
{
    if (id == 2) {
        ui->position->setEnabled(true);
    }
    else {
        ui->position->setEnabled(false);
    }
}

OperationItem* InsertForm::getOperation()
{
    return insertOperation;
}

void InsertForm::configureOperation()
{
    insertOperation->setTextToInsert(ui->toInsert->text());
    if (ui->asPrefix->isChecked()) {
        insertOperation->setPositionType(InsertOperation::Prefix);
    }
    else if (ui->asSuffix->isChecked()) {
        insertOperation->setPositionType(InsertOperation::Suffix);
    }
    else if (ui->atPosition->isChecked()) {
        insertOperation->setPositionType(InsertOperation::Fixed);
        insertOperation->setPosition(ui->position->value());
    }
    insertOperation->setApplyToExtension(applyToExtension);
    insertOperation->setApplyToName(applyToName);
}

QString InsertForm::name()
{
    return tr("Insert Operation");
}
