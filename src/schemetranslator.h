#ifndef SCHEMETRANSLATOR_H
#define SCHEMETRANSLATOR_H

#include <QObject>
#include "schemeDefine.h"

class SchemeTranslator : public QObject
{
    Q_OBJECT
public:
    explicit SchemeTranslator(QObject *parent = nullptr);

signals:
    void sigReturnScheme(Scheme scheme);
    void sigReturnJsonData(QByteArray jsonData);

public slots:
    void writeToJsonFile(Scheme scheme);
    void readFromJsonFile(QString& filePath);
};

#endif // SCHEMETRANSLATOR_H
