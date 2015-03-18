#ifndef INSERTOPERATION_H
#define INSERTOPERATION_H

#include <QWidget>

namespace Ui {
class InsertOperation;
}

class InsertOperation : public QWidget
{
    Q_OBJECT

public:
    explicit InsertOperation(QWidget *parent = 0);
    ~InsertOperation();

private:
    Ui::InsertOperation *ui;
};

#endif // INSERTOPERATION_H
