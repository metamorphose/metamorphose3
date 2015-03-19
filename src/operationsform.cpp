#include <QtCore/QtDebug>
#include "operationsform.h"
#include "ui_operationsform.h"
#include "operation/insertform.h"

OperationsForm::OperationsForm(OperationModel *operationModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OperationsForm)
{
    m_operationModel = operationModel;

    ui->setupUi(this);

    ui->operationsView->setModel(m_operationModel);
    ui->operationsView->resizeColumnsToContents();
}

OperationsForm::~OperationsForm()
{
    delete ui;
}

void OperationsForm::on_addOperation_activated(int index)
{
    qDebug() << index;
    m_operationModel->addOperation(new InsertForm());
    ui->addOperation->setCurrentIndex(0);
}
