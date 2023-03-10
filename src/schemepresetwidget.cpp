#include "schemepresetwidget.h"

#include <QLayout>
#include <QFormLayout>
//#include <>

SchemePresetWidget::SchemePresetWidget(Preset* presetValue,QWidget *parent)
    : QWidget{parent}
{
    m_presetValue = presetValue;
    initUi();
}

void SchemePresetWidget::initData()
{
    lableName->setText(m_presetValue->name);
}

QString SchemePresetWidget::name()
{
    return m_presetValue->name;
}

void SchemePresetWidget::initUi()
{
    QVBoxLayout* vLayout = new QVBoxLayout(this);
    vLayout->addWidget(lableName);

    //add rated voltage and current value
    {
        QHBoxLayout* ratedValueLayout {new QHBoxLayout};

        QFormLayout* voltLayout = new QFormLayout;
        voltLayout->addRow(tr("Rated Voltage"),spinboxVolt);

        QFormLayout* currLayout = new QFormLayout;
        currLayout->addRow(tr("Rated Current"),spinboxCurr);

        spinboxVolt->setSuffix("V");
        spinboxCurr->setRange(1000,0);
        spinboxCurr->setSuffix("A");

        ratedValueLayout->addLayout(voltLayout);
        ratedValueLayout->addSpacing(20);
        ratedValueLayout->addLayout(currLayout);
        ratedValueLayout->addStretch();
        vLayout->addLayout(ratedValueLayout);
    }


    vLayout->addStretch();
}
