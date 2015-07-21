#include "operationformitem.h"
#include "ui_operationformitem.h"

OperationFormItem::OperationFormItem(QWidget *parent) :
    QWidget(parent),
    formItemUi(new Ui::OperationFormItem)
{
    qCDebug(M3GUI) << "init OperationFormItem";
    formItemUi->setupUi(this);

    defaultSubOpFormat.setFontWeight(QFont::Bold);
    defaultSubOpFormat.setBackground(QColor("#F2F5A9"));
    defaultSubOpFormat.setForeground(QColor("#000000"));
}

void OperationFormItem::initSubOperations(QLineEdit *mainInput)
{
    subOperationsForm = new SubOperationsForm(formItemUi->subOperation);
    connect(subOperationsForm, SIGNAL(subOperationAdded(QString)),
            this, SLOT(insertSubOpText(QString)));
    this->mainInput = mainInput;
}

OperationFormItem::~OperationFormItem()
{
    delete formItemUi;
}

void OperationFormItem::insertSubOpText(QString text)
{
    if (mainInput && mainInput->isEnabled()) {
        mainInput->insert(text);
        mainInput->setFocus();
        return;
    }
    qCWarning(M3GUI, "Can't insert sub-operation text");
}

void OperationFormItem::setLineEditTextFormat(QLineEdit* lineEdit)
{
    if(!lineEdit) {
        return;
    }

    QList<QInputMethodEvent::Attribute> attributes;
    foreach(const QTextLayout::FormatRange& fr, textFormats) {
        QInputMethodEvent::AttributeType type = QInputMethodEvent::TextFormat;
        int start = fr.start - lineEdit->cursorPosition();
        int length = fr.length;
        QVariant value = fr.format;
        attributes.append(QInputMethodEvent::Attribute(type, start, length, value));
    }
    QInputMethodEvent event(QString(), attributes);
    QCoreApplication::sendEvent(lineEdit, &event);
}

