#ifndef SCHEMECONVERTOR_H
#define SCHEMECONVERTOR_H

#include <QObject>
#include "schemeModelDefine.h"

class SchemeConvertor : public QObject
{
    Q_OBJECT
public:
    explicit SchemeConvertor(QObject *parent = nullptr);

signals:
    void sigReturnScheme(SchemeModel schememodel);
    void sigReturnJsonData(QJsonObject jsonObject);

public slots:
    void writeToJsonFile(SchemeModel schememodel,QString filePath);
    void readFromJsonFile(QString filePath);
};

#endif // SCHEMECONVERTOR_H
