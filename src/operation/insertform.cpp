#include "operation/insertform.h"
#include "ui_insertform.h"
#include "ui_operationformitem.h"

InsertForm::InsertForm(QWidget *parent) :
    OperationFormItem(parent),
    ui(new Ui::InsertForm)
{
    qCDebug(M3GUI) << "init InsertForm";

    insertOperation = new InsertOperation();

    ui->setupUi(formItemUi->operation);
    initSubOperations(ui->toInsert);

    ui->positionSelection->setId(ui->asPrefix, 0);
    ui->positionSelection->setId(ui->asSuffix, 1);
    ui->positionSelection->setId(ui->atPosition, 2);
    ui->positionSelection->setId(ui->beforeText, 3);
    ui->positionSelection->setId(ui->afterText, 4);

    connect(ui->positionSelection, SIGNAL(buttonClicked(int)),
            this, SLOT(positionSelection_buttonClicked(int)));
    connect(ui->toInsert, SIGNAL(selectionChanged()),
            this, SLOT(toInsert_selectionChanged()));
    connect(ui->toInsert, SIGNAL(textChanged(const QString)),
            this, SLOT(toInsert_textChanged(const QString)));
}

InsertForm::~InsertForm()
{
    delete ui;
}

/**
 * Handle enabling the postion spinner.
 */
void InsertForm::positionSelection_buttonClicked(int id)
{
    qCDebug(M3GUI) << "positionSelection" << id;
    if (id == 2) {
        ui->position->setEnabled(true);
    }
    else {
        ui->position->setEnabled(false);
    }
    if (id == 3 || id == 4) {
        ui->toSearch->setEnabled(true);
        ui->caseSensitive->setEnabled(true);
    }
    else {
        ui->toSearch->setEnabled(false);
        ui->caseSensitive->setEnabled(false);
    }
}

OperationItem* InsertForm::getOperation()
{
    return insertOperation;
}

void InsertForm::configureOperation()
{
    insertOperation->setTextToInsert(ui->toInsert->text());
    if (ui->asPrefix->isChecked()) {
        insertOperation->setPositionType(InsertOperation::Prefix);
    }
    else if (ui->asSuffix->isChecked()) {
        insertOperation->setPositionType(InsertOperation::Suffix);
    }
    else if (ui->atPosition->isChecked()) {
        insertOperation->setPositionType(InsertOperation::Fixed);
        insertOperation->setPosition(ui->position->value());
    }
    else if (ui->afterText->isChecked()) {
        insertOperation->setPositionType(InsertOperation::AfterText);
        insertOperation->setTextToSearch(ui->toSearch->text());
        insertOperation->setCaseSensitive(ui->caseSensitive->isChecked());
    }
    else if (ui->beforeText->isChecked()) {
        insertOperation->setPositionType(InsertOperation::BeforeText);
        insertOperation->setTextToSearch(ui->toSearch->text());
        insertOperation->setCaseSensitive(ui->caseSensitive->isChecked());
    }
    insertOperation->setApplyToExtension(applyToExtension);
    insertOperation->setApplyToName(applyToName);
}

QString InsertForm::name()
{
    return tr("Insert Operation");
}

void InsertForm::toInsert_selectionChanged()
{
    qCDebug(M3GUI) << "selection" << ui->toInsert->selectedText();
}

void InsertForm::toInsert_textChanged(const QString &arg1)
{
    textFormats.clear();

    // first index all subops start & end positions
    QList<int> indexList;
    int next = 0;
    bool first = true;
    while (next > -1) {
        // prevents endless loop on finding ":" at first position
        if (first) {
            next = arg1.indexOf(":", 0);
            first = false;
        }
        else {
            next = arg1.indexOf(":", next + 1);
        }
        if (next > -1) {
            indexList << next;
        }
    }

    // now create format ranges for each subop
    for (int i = 0; i < indexList.size(); ++i) {
        if (i % 2 == 1) {
            QTextLayout::FormatRange subop;
            subop.format = defaultSubOpFormat;
            subop.start = indexList.at(i - 1);
            subop.length = indexList.at(i) - subop.start + 1;
            textFormats.append(subop);
        }
    }

    setLineEditTextFormat(ui->toInsert);
}
