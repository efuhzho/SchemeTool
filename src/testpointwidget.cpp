#include <QFormLayout>
#include <QLayout>

#include "testpointwidget.h"

TestPointWidget::TestPointWidget(QWidget *parent)
    : QWidget{parent}
{
    initUi();
    initConnections();
}

void TestPointWidget::setModel(TestPoint &model)
{
    m_testPoint = &model;
    emit sigModelUpdated();
}

void TestPointWidget::initUi()
{
    QVBoxLayout* mainLayout {new QVBoxLayout(this)};

    {
        QHBoxLayout* lineEditsLay {new QHBoxLayout};
        mainLayout->addLayout(lineEditsLay);

        //测试点名称
        {
            QFormLayout* nameForm {new QFormLayout};
            nameForm->addRow(tr("Name"),nameLineEdit);
            lineEditsLay->addLayout(nameForm);
            lineEditsLay->addSpacing(20);
        }

        //测试点值
        {
            QFormLayout* varForm {new QFormLayout};
            varForm->addRow(tr("Var"),varLineEdit);
            lineEditsLay->addLayout(varForm);
            lineEditsLay->addSpacing(20);
        }

        //单位
        {
            QFormLayout* unitForm {new QFormLayout};
            unitForm->addRow(tr("Unit"),unitLineEdit);
            lineEditsLay->addLayout(unitForm);
            lineEditsLay->addSpacing(20);
        }

        //ID
        {
            QFormLayout* idForm {new QFormLayout};
            idForm->addRow(tr("ID"),idLineEdit);
            lineEditsLay->addLayout(idForm);
            lineEditsLay->addSpacing(20);
        }
    }

    mainLayout->addWidget(widgetModelData);
    mainLayout->addStretch();
}

void TestPointWidget::initConnections()
{
    connect(this,&TestPointWidget::sigModelUpdated,this,[=]
    {
        nameLineEdit->setText(m_testPoint->name);
        unitLineEdit->setText(m_testPoint->unit);
        varLineEdit->setText(m_testPoint->var);
        idLineEdit->setText(m_testPoint->id);

        widgetModelData->setModel(m_testPoint->modelData);
    });

    connect(nameLineEdit,&QLineEdit::textChanged,this,[=](QString name)
    {
       m_testPoint->name = name;
    });

    connect(unitLineEdit,&QLineEdit::textChanged,this,[=](QString unit)
    {
        m_testPoint->unit = unit;
    });

    connect(varLineEdit,&QLineEdit::textChanged,this,[=](QString var)
    {
        m_testPoint->var = var;
    });
}
