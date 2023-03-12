#include "schemeinfowidget.h"

#include <QFormLayout>

SchemeInfoWidget::SchemeInfoWidget(QWidget *parent)
    : QWidget{parent}
{   
    initUi();
    initConnections();
}

void SchemeInfoWidget::initUi()
{
    QFormLayout* formLayout =new QFormLayout(this);
    formLayout->setRowWrapPolicy(QFormLayout::WrapAllRows);

    //add elements
    formLayout->addRow(tr("Scheme Name:"),lineEditSchemeName);
    formLayout->addRow(tr("Version:"),lineEditVersion);
    formLayout->addRow(tr("Create Date:"),lineEditCreateDate);
    formLayout->addRow(tr("Update Date:"),lineEditUpdateDate);
    formLayout->addRow(tr("User:"),lineEditUser);
    formLayout->addRow(tr("Description:"),textEditDescription);
}

void SchemeInfoWidget::initConnections()
{
    //when scheme naem was edited
    connect(lineEditSchemeName,&QLineEdit::textEdited,this,[=](QString text)
    {
        m_schemeValue->name = text;
    });

    //when scheme version was edited
    connect(lineEditVersion,&QLineEdit::textEdited,this,[=](QString text)
    {
        m_schemeValue->version = text;
    });

    //when scheme create date was edited
    connect(lineEditCreateDate,&QLineEdit::textEdited,this,[=](QString text)
    {
        m_schemeValue->createDate = text;
    });

    //when scheme update date was edited
    connect(lineEditUpdateDate,&QLineEdit::textEdited,this,[=](QString text)
    {
        m_schemeValue->updateDate = text;
    });

    //when scheme user was edited
    connect(lineEditUser,&QLineEdit::textEdited,this,[=](QString text)
    {
        m_schemeValue->user = text;
    });

    //when scheme description was edited
    connect(textEditDescription,&QTextEdit::textChanged,this,[=]
    {
        m_schemeValue->description = textEditDescription->toPlainText();
    });
}

void SchemeInfoWidget::setModel(SchemeValue& schemeValue)
{
    m_schemeValue = &schemeValue;
    lineEditSchemeName->setText(m_schemeValue->name);
    lineEditVersion->setText(m_schemeValue->version);
    lineEditCreateDate->setText(m_schemeValue->createDate);
    lineEditUpdateDate->setText(m_schemeValue->updateDate);
    lineEditUser->setText(m_schemeValue->user);
    textEditDescription->setText(m_schemeValue->description);
}

QString SchemeInfoWidget::name()
{
    return m_schemeValue->name;
}
