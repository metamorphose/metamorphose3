#ifndef OPERATIONSFORM_H
#define OPERATIONSFORM_H

#include <QWidget>
#include "operationmodel.h"

namespace Ui {
class OperationsForm;
}

class OperationsForm : public QWidget
{
    Q_OBJECT

public:
    explicit OperationsForm(OperationModel *operationModel, QWidget *parent = 0);
    ~OperationsForm();

private slots:
    void on_addOperation_activated(int index);

private:
    Ui::OperationsForm *ui;
    OperationModel *m_operationModel;
};

#endif // OPERATIONSFORM_H
