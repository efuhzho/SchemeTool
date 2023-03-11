#include "schemepresetwidget.h"

#include <QLayout>
#include <QFormLayout>
//#include <>

SchemePresetWidget::SchemePresetWidget(Preset& presetValue,QWidget *parent)
    : QWidget{parent}
{
    m_presetValue = &presetValue;
    initUi();
    initSpinBox();
    initConnections();
}

void SchemePresetWidget::initData()
{
    dataWidget=new ModelDataWidget(m_presetValue->modelData);
    lableName->setText(m_presetValue->name);

    spinboxVolt->setValue(m_presetValue->ratedVoltage);
    spinboxCurr->setValue(m_presetValue->ratedCurrent);
    qDebug()<<m_presetValue->modelData.loops.size()<<" ---"<<&(m_presetValue->modelData);

    dataWidget->initData();
}

QString SchemePresetWidget::name()
{
    return m_presetValue->name;
}

void SchemePresetWidget::initUi()
{
    QFormLayout* voltLayout = new QFormLayout;
    voltLayout->addRow(tr("Rated Voltage"),spinboxVolt);

    QFormLayout* currLayout = new QFormLayout;
    currLayout->addRow(tr("Rated Current"),spinboxCurr);

    QHBoxLayout* ratedValueLayout {new QHBoxLayout};
    ratedValueLayout->addLayout(voltLayout);
    ratedValueLayout->addSpacing(20);
    ratedValueLayout->addLayout(currLayout);
    ratedValueLayout->addStretch();

    QVBoxLayout* vLayout = new QVBoxLayout(this);
    vLayout->addWidget(lableName);
    vLayout->addLayout(ratedValueLayout);
    vLayout->addWidget(dataWidget);
    vLayout->addStretch();
}

void SchemePresetWidget::initSpinBox()
{
    spinboxVolt->setSuffix("V");
    spinboxVolt->setRange(0,380);
    spinboxVolt->setSingleStep(10);
    //spinboxVolt->setKeyboardTracking(false);

    spinboxCurr->setSuffix("A");
    spinboxCurr->setRange(0,20);
    spinboxCurr->setSingleStep(1);
    //spinboxCurr->setKeyboardTracking(false);
}

void SchemePresetWidget::initConnections()
{
    connect(spinboxVolt,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
    {
        m_presetValue->ratedVoltage = value;
    });
    connect(spinboxCurr,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
    {
        m_presetValue->ratedCurrent = value;
    });
}
