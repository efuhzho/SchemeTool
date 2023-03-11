#ifndef SCHEMEINFOWIDGET_H
#define SCHEMEINFOWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QString>

#include "src/schemeDefine.h"

class SchemeInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SchemeInfoWidget(SchemeValue& schemeValue, QWidget *parent = nullptr);
    void initData();
    QString name();

private://inits
    void initUi();
    void initConnections();

private://elements
    QLineEdit* lineEditSchemeName {new QLineEdit};
    QLineEdit* lineEditVersion {new QLineEdit};
    QLineEdit* lineEditCreateDate {new QLineEdit};
    QLineEdit* lineEditUpdateDate {new QLineEdit};
    QLineEdit* lineEditUser {new QLineEdit};
    QTextEdit* textEditDescription {new QTextEdit};

private://members
    SchemeValue* m_schemeValue{nullptr};
};

#endif // SCHEMEINFOWIDGET_H
