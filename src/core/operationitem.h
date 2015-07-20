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
    void setApplyToName(const bool apply);
    void setApplyToExtension(const bool apply);
    QString parseSubOps();
    void preprocess();
    QString numbering();
    QString datetime(const QString format);

protected:
    virtual void operation(QString &name) = 0;
    int itemPosition;
    QString textToInsert;
    QStringList parsedTextSegments;

private:
    bool applyToName = true;
    bool applyToExtension = false;
};

#endif // OPERATIONITEM_H
