#include <QtCore/QtDebug>

#include "operation/insert.h"
#include "ui_insertoperation.h"

InsertOperation::InsertOperation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InsertOperation)
{
    ui->setupUi(this);
}

InsertOperation::~InsertOperation()
{
    delete ui;
}
