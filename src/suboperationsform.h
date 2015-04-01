#ifndef SUBOPERATIONSFORM_H
#define SUBOPERATIONSFORM_H

#include <QWidget>

namespace Ui {
class SubOperationsForm;
}

class SubOperationsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SubOperationsForm(QWidget *parent = 0);
    ~SubOperationsForm();

private:
    Ui::SubOperationsForm *ui;
};

#endif // SUBOPERATIONSFORM_H
