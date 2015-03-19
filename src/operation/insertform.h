#ifndef INSERTFORM_H
#define INSERTFORM_H

#include <QWidget>

namespace Ui {
class InsertForm;
}

class InsertForm : public QWidget
{
    Q_OBJECT

public:
    explicit InsertForm(QWidget *parent = 0);
    ~InsertForm();

private:
    Ui::InsertForm *ui;
};

#endif // INSERTFORM_H
