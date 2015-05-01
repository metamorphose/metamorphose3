#ifndef OPERATIONITEM_H
#define OPERATIONITEM_H

#include <QtCore/QObject>
#include <QtCore/QLoggingCategory>
#include <QtCore/QDateTime>

Q_DECLARE_LOGGING_CATEGORY(M3CORE)

class OperationItem : public QObject
{
    Q_OBJECT

public:
    void applyOperation(int itemPosition, std::pair<QString, QString> &name);
    void setApplyToName(bool apply);
    void setApplyToExtension(bool apply);
    void parseSubOps(int itemPosition, QString &text);

protected:
    virtual void operation(int itemPosition, QString &name) = 0;

private:
    bool applyToName = true;
    bool applyToExtension = false;
};

#endif // OPERATIONITEM_H
