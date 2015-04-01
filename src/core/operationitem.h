#ifndef OPERATIONITEM_H
#define OPERATIONITEM_H

#include <QtCore/QObject>
#include <QtCore/QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(M3CORE)

class OperationItem : public QObject
{
    Q_OBJECT

public:
    void applyOperation(int itemPosition, std::pair<QString, QString> &name);
    void setEnabled(bool enabled);
    bool isEnabled();
    void setApplyToName(bool apply);
    void setApplyToExtension(bool apply);

protected:
    virtual void operation(QString &name) = 0;

private:
    bool enabled = true;
    bool applyToName = true;
    bool applyToExtension = false;
};

#endif // OPERATIONITEM_H
