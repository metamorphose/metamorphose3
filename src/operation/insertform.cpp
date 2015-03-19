#include <QtCore/QtDebug>

#include "operation/insertform.h"
#include "ui_insertform.h"

InsertForm::InsertForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InsertForm)
{
    ui->setupUi(this);
}

InsertForm::~InsertForm()
{
    delete ui;
}
