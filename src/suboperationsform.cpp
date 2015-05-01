#include "suboperationsform.h"
#include "ui_suboperationsform.h"

Q_LOGGING_CATEGORY(M3GUI, "gui")

SubOperationsForm::SubOperationsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubOperationsForm)
{
    ui->setupUi(this);
}

SubOperationsForm::~SubOperationsForm()
{
    delete ui;
}

void SubOperationsForm::on_numberingButton_clicked()
{
    emit subOperationAdded("::numb::");
}

void SubOperationsForm::on_dateButton_clicked()
{
    emit subOperationAdded("::date::");
}

void SubOperationsForm::on_timeButton_clicked()
{
    emit subOperationAdded("::time::");
}
