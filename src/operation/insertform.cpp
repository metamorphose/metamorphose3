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
    initSubOperations(ui->toInsert);

    ui->positionSelection->setId(ui->asPrefix, 0);
    ui->positionSelection->setId(ui->asSuffix, 1);
    ui->positionSelection->setId(ui->atPosition, 2);
    ui->positionSelection->setId(ui->beforeText, 3);
    ui->positionSelection->setId(ui->afterText, 4);

    connect(ui->positionSelection, SIGNAL(buttonClicked(int)),
            this, SLOT(positionSelection_buttonClicked(int)));
}

InsertForm::~InsertForm()
{
    delete ui;
}

/**
 * Handle enabling the postion spinner.
 */
void InsertForm::positionSelection_buttonClicked(int id)
{
    qCDebug(M3GUI) << "positionSelection" << id;
    if (id == 2) {
        ui->position->setEnabled(true);
    }
    else {
        ui->position->setEnabled(false);
    }
    if (id == 3 || id == 4) {
        ui->toSearch->setEnabled(true);
        ui->caseSensitive->setEnabled(true);
    }
    else {
        ui->toSearch->setEnabled(false);
        ui->caseSensitive->setEnabled(false);
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
    else if (ui->afterText->isChecked()) {
        insertOperation->setPositionType(InsertOperation::AfterText);
        insertOperation->setTextToSearch(ui->toSearch->text());
        insertOperation->setCaseSensitive(ui->caseSensitive->isChecked());
    }
    else if (ui->beforeText->isChecked()) {
        insertOperation->setPositionType(InsertOperation::BeforeText);
        insertOperation->setTextToSearch(ui->toSearch->text());
        insertOperation->setCaseSensitive(ui->caseSensitive->isChecked());
    }
    insertOperation->setApplyToExtension(applyToExtension);
    insertOperation->setApplyToName(applyToName);
}

QString InsertForm::name()
{
    return tr("Insert Operation");
}
