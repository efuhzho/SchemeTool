#include <QJsonDocument>
#

#include "statewidget.h"

StateWidget::StateWidget(QWidget *parent)
    : QWidget{parent}
{
    initUI();
    initConnects();
}

void StateWidget::setModel(State &state)
{
    m_stateModel = &state;
    emit sigModelUpdated();
}

void StateWidget::onModelUpdated()
{
    if(m_stateModel->parameters.isEmpty())
    {
        initSpinboxData(-1);
    }
    if(m_stateModel->parameters.contains("Ua"))
    {
        Parameter para = m_stateModel->parameters["Ua"];
        boxUa->setValue(para.mag);
        boxUa->setEnabled(true);

        boxPhUa->setValue(para.ang);
        boxPhUa->setEnabled(true);

        boxFa->setValue(para.freq);
        boxFa->setEnabled(true);
    }

    if(m_stateModel->parameters.contains("Ub"))
    {
        auto para = m_stateModel->parameters["Ub"];
        boxUb->setValue(para.mag);
        boxUb->setEnabled(true);

        boxPhUb->setValue(para.ang);
        boxPhUb->setEnabled(true);

        boxFb->setValue(para.freq);
        boxFb->setEnabled(true);
    }

    if(m_stateModel->parameters.contains("Uc"))
    {
        auto para = m_stateModel->parameters["Uc"];
        boxUc->setValue(para.mag);
        boxUc->setEnabled(true);

        boxPhUc->setValue(para.ang);
        boxPhUc->setEnabled(true);

        boxFc->setValue(para.freq);
        boxFc->setEnabled(true);
    }

    if(m_stateModel->parameters.contains("Ux"))
    {
        auto para = m_stateModel->parameters["Ux"];
        boxUx->setValue(para.mag);
        boxUx->setEnabled(true);

        boxPhUx->setValue(para.ang);
        boxPhUx->setEnabled(true);

        boxFx->setValue(para.freq);
        boxFx->setEnabled(true);
    }

    if(m_stateModel->parameters.contains("Ia"))
    {
        auto para = m_stateModel->parameters["Ia"];
        boxIa->setValue(para.mag);
        boxIa->setEnabled(true);

        boxPhIa->setValue(para.ang);
        boxPhIa->setEnabled(true);

        boxFa->setValue(para.freq);
        boxFa->setEnabled(true);
    }

    if(m_stateModel->parameters.contains("Ib"))
    {
        auto para = m_stateModel->parameters["Ib"];
        boxIb->setValue(para.mag);
        boxIb->setEnabled(true);

        boxPhIb->setValue(para.ang);
        boxPhIb->setEnabled(true);

        boxFb->setValue(para.freq);
        boxFb->setEnabled(true);
    }

    if(m_stateModel->parameters.contains("Ic"))
    {
        auto para = m_stateModel->parameters["Ic"];
        boxIc->setValue(para.mag);
        boxIc->setEnabled(true);

        boxPhIc->setValue(para.ang);
        boxPhIc->setEnabled(true);

        boxFc->setValue(para.freq);
        boxFc->setEnabled(true);
    }

    if(m_stateModel->parameters.contains("Ix"))
    {
        auto para = m_stateModel->parameters["Ix"];
        boxIx->setValue(para.mag);
        boxIx->setEnabled(true);

        boxPhIx->setValue(para.ang);
        boxPhIx->setEnabled(true);

        boxFx->setValue(para.freq);
        boxFx->setEnabled(true);
    }
}

void StateWidget::initUI()
{
    QVBoxLayout* mainlayout {new QVBoxLayout(this)};
    mainlayout->addLayout(createDataGrid());
    initSpinBox();
}

QGridLayout *StateWidget::createDataGrid()
{
    QGridLayout* dataGrid = new QGridLayout;
    //row 0 header
    dataGrid->addWidget(new QLabel("A"),0,2,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel("B"),0,3,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel("C"),0,4,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel("X"),0,5,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel(QString::fromLocal8Bit("Σ")),0,6,Qt::AlignCenter);

    //colum 0 header
    dataGrid->addWidget(new QLabel("U"),1,0,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel("I"),2,0,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel(QString::fromLocal8Bit("ΦU")),3,0,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel(QString::fromLocal8Bit("ΦI")),4,0,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel("P"),5,0,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel("Q"),6,0,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel("PF"),7,0,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel("Freq"),8,0,Qt::AlignCenter);

    //colum 1 header
    {
        //        QLabel* unitU = new QLabel("%");
        //        QLabel* unitI = new QLabel("%");
        //        QLabel* unitFaiU = new QLabel("°");
        //        QLabel* unitFaiI = new QLabel("°");
        //        QLabel* unitP = new QLabel("W");
        //        QLabel* unitQ = new QLabel("Var");
        //        QLabel* unitFreq = new QLabel("Hz");

        //        dataGrid->addWidget(unitU,1,1,Qt::AlignCenter);
        //        dataGrid->addWidget(unitI,2,1,Qt::AlignCenter);
        //        dataGrid->addWidget(unitFaiU,3,1,Qt::AlignCenter);
        //        dataGrid->addWidget(unitFaiI,4,1,Qt::AlignCenter);
        //        dataGrid->addWidget(unitP,5,1,Qt::AlignCenter);
        //        dataGrid->addWidget(unitQ,6,1,Qt::AlignCenter);
        //        dataGrid->addWidget(unitFreq,8,1,Qt::AlignCenter);

        //        QPalette unitColor;
        //        unitColor.setColor(QPalette::WindowText, Qt::darkGray);
        //        unitU->setPalette(unitColor);
        //        unitI->setPalette(unitColor);
        //        unitFaiU->setPalette(unitColor);
        //        unitFaiI->setPalette(unitColor);
        //        unitP->setPalette(unitColor);
        //        unitQ->setPalette(unitColor);
        //        unitFreq->setPalette(unitColor);
    }

    //添加数值控件
    {
        //电压值
        dataGrid->addWidget( boxUa, 1, 2 );
        dataGrid->addWidget( boxUb, 1, 3 );
        dataGrid->addWidget( boxUc, 1, 4 );
        dataGrid->addWidget( boxUx, 1, 5 );

        //电流值
        dataGrid->addWidget( boxIa, 2, 2 );
        dataGrid->addWidget( boxIb, 2, 3 );
        dataGrid->addWidget( boxIc, 2, 4 );
        dataGrid->addWidget( boxIx, 2, 5 );

        //电压相位值
        dataGrid->addWidget( boxPhUa, 3, 2 );
        dataGrid->addWidget( boxPhUb, 3, 3 );
        dataGrid->addWidget( boxPhUc, 3, 4 );
        dataGrid->addWidget( boxPhUx, 3, 5 );

        //电流相位值
        dataGrid->addWidget( boxPhIa, 4, 2 );
        dataGrid->addWidget( boxPhIb, 4, 3 );
        dataGrid->addWidget( boxPhIc, 4, 4 );
        dataGrid->addWidget( boxPhIx, 4, 5 );

        //有功功率值
        dataGrid->addWidget( boxPa, 5, 2 );
        dataGrid->addWidget( boxPb, 5, 3 );
        dataGrid->addWidget( boxPc, 5, 4 );
        dataGrid->addWidget( boxPx, 5, 5 );
        dataGrid->addWidget( boxPsum, 5, 6 );

        //无功功率值
        dataGrid->addWidget( boxQa, 6, 2 );
        dataGrid->addWidget( boxQb, 6, 3 );
        dataGrid->addWidget( boxQc, 6, 4 );
        dataGrid->addWidget( boxQx, 6, 5 );
        dataGrid->addWidget( boxQsum, 6, 6 );

        //功率因数
        dataGrid->addWidget( boxPFa, 7, 2 );
        dataGrid->addWidget( boxPFb, 7, 3 );
        dataGrid->addWidget( boxPFc, 7, 4 );
        dataGrid->addWidget( boxPFx, 7, 5 );
        dataGrid->addWidget( boxPFsum, 7, 6 );

        //频率
        dataGrid->addWidget( boxFa, 8, 2 );
        dataGrid->addWidget( boxFb, 8, 3 );
        dataGrid->addWidget( boxFc, 8, 4 );
        dataGrid->addWidget( boxFx, 8, 5 );
    }

    //set grid stretch rule
    dataGrid->setColumnStretch( 2, 1 );
    dataGrid->setColumnStretch( 3, 1 );
    dataGrid->setColumnStretch( 4, 1 );
    dataGrid->setColumnStretch( 5, 1 );
    dataGrid->setColumnStretch( 6, 1 );

    //Colum width
    dataGrid->setColumnMinimumWidth( 2, 80 );
    dataGrid->setColumnMinimumWidth( 3, 80 );
    dataGrid->setColumnMinimumWidth( 4, 80 );
    dataGrid->setColumnMinimumWidth( 5, 80 );
    dataGrid->setColumnMinimumWidth( 6, 80 );

    //row height
    dataGrid->setRowMinimumHeight( 0, 25);
    dataGrid->setRowMinimumHeight( 1, 25);
    dataGrid->setRowMinimumHeight( 2, 25);
    dataGrid->setRowMinimumHeight( 3, 25);
    dataGrid->setRowMinimumHeight( 4, 25);
    dataGrid->setRowMinimumHeight( 5, 25);
    dataGrid->setRowMinimumHeight( 6, 25);
    dataGrid->setRowMinimumHeight( 7, 25);
    dataGrid->setRowMinimumHeight( 8, 25);

    return dataGrid;
}

void StateWidget::initSpinBox()
{
    //SetSuffix
    {
        boxUa->setSuffix(unitU);
        boxUa->setKeyboardTracking(false);
        boxUb->setSuffix(unitU);
        boxUc->setSuffix(unitU);
        boxUx->setSuffix(unitU);

        boxIa->setSuffix(unitI);
        boxIb->setSuffix(unitI);
        boxIc->setSuffix(unitI);
        boxIx->setSuffix(unitI);

        boxPhUa->setSuffix(QString::fromLocal8Bit("°"));
        boxPhUb->setSuffix(QString::fromLocal8Bit("°"));
        boxPhUc->setSuffix(QString::fromLocal8Bit("°"));
        boxPhUx->setSuffix(QString::fromLocal8Bit("°"));

        boxPhIa->setSuffix(QString::fromLocal8Bit("°"));
        boxPhIb->setSuffix(QString::fromLocal8Bit("°"));
        boxPhIc->setSuffix(QString::fromLocal8Bit("°"));
        boxPhIx->setSuffix(QString::fromLocal8Bit("°"));

        boxPa->setSuffix(unitP);
        boxPb->setSuffix(unitP);
        boxPc->setSuffix(unitP);
        boxPx->setSuffix(unitP);
        boxPsum->setSuffix(unitP);

        boxQa->setSuffix(unitQ);
        boxQb->setSuffix(unitQ);
        boxQc->setSuffix(unitQ);
        boxQx->setSuffix(unitQ);
        boxQsum->setSuffix(unitQ);

        boxFa->setSuffix("Hz");
        boxFb->setSuffix("Hz");
        boxFc->setSuffix("Hz");
        boxFx->setSuffix("Hz");
    }

    //SetRange
    {
        boxUa->setRange(-1,100);
        boxUb->setRange(-1,100);
        boxUc->setRange(-1,100);
        boxUx->setRange(-1,100);

        boxIa->setRange(-1,100);
        boxIb->setRange(-1,100);
        boxIc->setRange(-1,100);
        boxIx->setRange(-1,100);

        boxPhUa->setRange(-1,359.99);
        boxPhUb->setRange(-1,359.99);
        boxPhUc->setRange(-1,359.99);
        boxPhUx->setRange(-1,359.99);

        boxPhIa->setRange(-1,359.99);
        boxPhIb->setRange(-1,359.99);
        boxPhIc->setRange(-1,359.99);
        boxPhIx->setRange(-1,359.99);

        boxPa->setRange(-1,100);
        boxPb->setRange(-1,100);
        boxPc->setRange(-1,100);
        boxPx->setRange(-1,100);
        boxPsum->setRange(-1,100);

        boxQa->setRange(-1,100);
        boxQb->setRange(-1,100);
        boxQc->setRange(-1,100);
        boxQx->setRange(-1,100);
        boxQsum->setRange(-1,100);

        boxFa->setRange(-1,125);
        boxFb->setRange(-1,125);
        boxFc->setRange(-1,125);
        boxFx->setRange(-1,125);
    }

    //setSpecialValueText
    {
        boxUa->setSpecialValueText("NULL");
        boxUb->setSpecialValueText("NULL");
        boxUc->setSpecialValueText("NULL");
        boxUx->setSpecialValueText("NULL");
    }

    //setSingleStep
    {
//        boxUa->setSingleStep(10);
//        boxUb->setSingleStep(10);
//        boxUc->setSingleStep(10);
//        boxUx->setSingleStep(10);

//        boxIa->setSingleStep(10);
//        boxIb->setSingleStep(10);
//        boxIc->setSingleStep(10);
//        boxIx->setSingleStep(10);

//        boxPhUa->setSingleStep(30);
//        boxPhUb->setSingleStep(30);
//        boxPhUc->setSingleStep(30);
//        boxPhUx->setSingleStep(30);

//        boxPhIa->setSingleStep(30);
//        boxPhIb->setSingleStep(30);
//        boxPhIc->setSingleStep(30);
//        boxPhIx->setSingleStep(30);

//        boxPa->setSingleStep(10);
//        boxPb->setSingleStep(10);
//        boxPc->setSingleStep(10);
//        boxPx->setSingleStep(10);
//        boxPsum->setSingleStep(10);

//        boxQa->setSingleStep(10);
//        boxQb->setSingleStep(10);
//        boxQc->setSingleStep(10);
//        boxQx->setSingleStep(10);
//        boxQsum->setSingleStep(10);

//        boxFa->setSingleStep(1);
//        boxFb->setSingleStep(1);
//        boxFc->setSingleStep(1);
//        boxFx->setSingleStep(1);
    }

    //setEnable
    {
//        boxUa->setEnabled(false);
//        boxUb->setEnabled(false);
//        boxUc->setEnabled(false);
//        boxUx->setEnabled(false);

//        boxIa->setEnabled(false);
//        boxIb->setEnabled(false);
//        boxIc->setEnabled(false);
//        boxIx->setEnabled(false);

//        boxPhUa->setEnabled(false);
//        boxPhUb->setEnabled(false);
//        boxPhUc->setEnabled(false);
//        boxPhUx->setEnabled(false);

//        boxPhIa->setEnabled(false);
//        boxPhIb->setEnabled(false);
//        boxPhIc->setEnabled(false);
//        boxPhIx->setEnabled(false);

//        boxPa->setEnabled(false);
//        boxPb->setEnabled(false);
//        boxPc->setEnabled(false);
//        boxPx->setEnabled(false);
//        boxPsum->setEnabled(false);

//        boxQa->setEnabled(false);
//        boxQb->setEnabled(false);
//        boxQc->setEnabled(false);
//        boxQx->setEnabled(false);
//        boxQsum->setEnabled(false);

//        boxFa->setEnabled(false);
//        boxFb->setEnabled(false);
//        boxFc->setEnabled(false);
//        boxFx->setEnabled(false);

//        boxPFa->setEnabled(false);
//        boxPFb->setEnabled(false);
//        boxPFc->setEnabled(false);
//        boxPFx->setEnabled(false);
//        boxPFsum->setEnabled(false);
    }
}

void StateWidget::initSpinboxData(double value)
{
    boxUa->setValue(value);
    boxUb->setValue(value);
    boxUc->setValue(value);
    boxUx->setValue(value);

    boxIa->setValue(value);
    boxIb->setValue(value);
    boxIc->setValue(value);
    boxIx->setValue(value);

    boxPhUa->setValue(value);
    boxPhUb->setValue(value);
    boxPhUc->setValue(value);
    boxPhUx->setValue(value);

    boxPhIa->setValue(value);
    boxPhIb->setValue(value);
    boxPhIc->setValue(value);
    boxPhIx->setValue(value);

    boxPa->setValue(value);
    boxPb->setValue(value);
    boxPc->setValue(value);
    boxPx->setValue(value);
    boxPsum->setValue(value);

    boxQa ->setValue(value);
    boxQb ->setValue(value);
    boxQc ->setValue(value);
    boxQx->setValue(value);
    boxQsum->setValue(value);

    boxPFa ->setValue(value);
    boxPFb ->setValue(value);
    boxPFc ->setValue(value);
    boxPFx->setValue(value);
    boxPFsum->setValue(value);

    boxFa->setValue(value);
    boxFb->setValue(value);
    boxFc->setValue(value);
    boxFx->setValue(value);
}

void StateWidget::initConnects()
{
    connect(this,&StateWidget::sigModelUpdated,this,&StateWidget::onModelUpdated);

    //幅度设置
    {
        connect(boxUa,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ua"].mag = value;
        });
        connect(boxUb,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ub"].mag = value;
        });
        connect(boxUc,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Uc"].mag = value;
        });
        connect(boxUx,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ux"].mag = value;
        });
        connect(boxIa,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ia"].mag = value;
        });
        connect(boxIb,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ib"].mag = value;
        });
        connect(boxIc,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ic"].mag = value;
        });
        connect(boxIx,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ix"].mag = value;
        });
    }

    //相位设置
    {
        connect(boxPhUa,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ua"].ang = value;
        });
        connect(boxPhUb,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ub"].ang = value;
        });
        connect(boxPhUc,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Uc"].ang = value;
        });
        connect(boxPhUx,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ux"].ang = value;
        });
        connect(boxPhIa,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ia"].ang = value;
        });
        connect(boxPhIb,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ib"].ang = value;
        });
        connect(boxPhIc,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ic"].ang = value;
        });
        connect(boxPhIx,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ix"].ang = value;
        });
    }

    //相位设置
    {
        connect(boxFa,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ua"].freq = value;
        });
        connect(boxFb,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ub"].freq = value;
        });
        connect(boxFc,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Uc"].freq = value;
        });
        connect(boxFx,qOverload<double>(&QDoubleSpinBox::valueChanged),this,[=](double value)
        {
            if(value<0)
            {
                return;
            }
            m_stateModel->parameters["Ux"].freq = value;
        });
    }
}
