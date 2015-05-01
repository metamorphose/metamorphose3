#ifndef SUBOPERATIONSFORM_H
#define SUBOPERATIONSFORM_H

#include <QtWidgets/QWidget>
#include <QtCore/QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(M3GUI)

namespace Ui {
class SubOperationsForm;
}

class SubOperationsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SubOperationsForm(QWidget *parent = 0);
    ~SubOperationsForm();

signals:
    void subOperationAdded(QString operation);

private slots:
    void on_numberingButton_clicked();
    void on_dateButton_clicked();
    void on_timeButton_clicked();

private:
    Ui::SubOperationsForm *ui;
};

#endif // SUBOPERATIONSFORM_H
