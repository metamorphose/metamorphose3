#include "operation/insertform.h"
#include "ui_insertform.h"

InsertForm::InsertForm(QWidget *parent) :
    OperationFormItem(parent),
    ui(new Ui::InsertForm)
{
    ui->setupUi(this);
    insertOperation = new InsertOperation();

    ui->positionSelection->setId(ui->asPrefix, 0);
    ui->positionSelection->setId(ui->asSuffix, 1);
    ui->positionSelection->setId(ui->atPosition, 2);
}

InsertForm::~InsertForm()
{
    delete ui;
}

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

}
