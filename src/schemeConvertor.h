#ifndef SCHEMECONVERTOR_H
#define SCHEMECONVERTOR_H

#include <QObject>
#include "schemeDefine.h"

class SchemeConvertor : public QObject
{
    Q_OBJECT
public:
    explicit SchemeConvertor(QObject *parent = nullptr);

signals:
    void sigReturnScheme(Scheme scheme);
    void sigReturnJsonData(QByteArray jsonData);

public slots:
    void writeToJsonFile(Scheme scheme,QString filePath);
    void readFromJsonFile(QString filePath);
};

#endif // SCHEMECONVERTOR_H
