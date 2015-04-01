#include "suboperationsform.h"
#include "ui_suboperationsform.h"

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
