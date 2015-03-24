#ifndef SELECTIONFORM_H
#define SELECTIONFORM_H

#include <QtWidgets/QWidget>
#include "core/renamermodel.h"

namespace Ui {
class SelectionForm;
}

class SelectionForm : public QWidget
{
    Q_OBJECT

public:
    explicit SelectionForm(RenamerModel *model, QWidget *parent = 0);
    ~SelectionForm();

private:
    Ui::SelectionForm *ui;
    RenamerModel* renamerModel;

private slots:
    void on_addDirButton_clicked();
    void on_addFilesButton_clicked();
    void on_sortButton_clicked();
};

#endif // SELECTIONFORM_H
