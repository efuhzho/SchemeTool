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
    explicit SchemeInfoWidget(QWidget *parent = nullptr);
    void setModel(Scheme& schemeValue);
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
    Scheme* m_schemeValue{nullptr};
};

#endif // SCHEMEINFOWIDGET_H
