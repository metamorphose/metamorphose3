#ifndef SELECTIONPARAMS_H
#define SELECTIONPARAMS_H

#include <QWidget>
#include "renamermodel.h"

namespace Ui {
class SelectionParams;
}

class SelectionParams : public QWidget
{
    Q_OBJECT

public:
    explicit SelectionParams(QWidget *parent = 0);
    ~SelectionParams();
    void setRenamerModel(RenamerModel *model);

private:
    Ui::SelectionParams *ui;
    RenamerModel* m_renamerModel;

private slots:
    void on_addDirButton_clicked();
    void on_addFilesButton_clicked();
    void on_sortButton_clicked();
};

#endif // SELECTIONPARAMS_H
