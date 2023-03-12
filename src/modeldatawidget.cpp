#include "modeldatawidget.h"
#include <QPushButton>
#include <QDebug>

ModelDataWidget::ModelDataWidget(QWidget *parent)
    : QWidget{parent}
{
    initUi();
    initSpinBox();
    initConnections();
}

void ModelDataWidget::setModel(ModelData& modeldata)
{
    m_modelData = &modeldata;
    emit sigModelUpdated();
}

void ModelDataWidget::slotUpdateLoopsList()
{
    QList<QAbstractButton*> btnsInGroup = groupLoops->buttons();
    foreach (QAbstractButton *btn, btnsInGroup)
    {
        delete btn;
    }

    int size = m_modelData->loops.size();
    for (int i = 0; i < size; ++i)
    {
        QString key = m_modelData->loops[i].key;
        QRadioButton* radbtn = new QRadioButton(key);

        groupLoops->addButton(radbtn,i);
        loopsLayout->addWidget(radbtn);
    }

    if(groupLoops->buttons().count()>0)
    {
        groupLoops->buttons().at(0)->setChecked(true);
        emit sigLoopChecked(0);
    }
}

void ModelDataWidget::slotUpdateStatesList(int loopIndex)
{
    QList<QAbstractButton*> btnsInGroup = groupStates->buttons();
    foreach (QAbstractButton *btn, btnsInGroup)
    {
        delete btn;
    }

    int count = m_modelData->loops[loopIndex].loopValue.states.size();
    for (int i = 0; i < count; ++i)
    {
        QString key = m_modelData->loops[loopIndex].loopValue.states.at(i).key;
        QRadioButton* radioState = new QRadioButton(key);

        groupStates->addButton(radioState,i);
        statesLayout->addWidget(radioState);
    }
    if(groupStates->buttons().count()>0)
    {
        groupStates->buttons().at(0)->setChecked(true);
        emit sigStateChecked(loopIndex,0);
    }
}

void ModelDataWidget::slotUpdateDataGrid(int loopIndex,int stateIndex)
{
    State state =m_modelData->loops[loopIndex].loopValue.states[stateIndex].stateValue;
    int cout = state.parameters.size();
    for (int i = 0; i < cout; ++i)
    {
        Parameter para = state.parameters.at(i);
        if(para.phaseName.toLower()=="ua")
        {
            boxUa->setValue(para.phaseData.mag);
            boxPhUa->setValue(para.phaseData.ang);
            boxFa->setValue(para.phaseData.freq);
        }
        else if (para.phaseName.toLower()=="ub")
        {
            boxUb->setValue(para.phaseData.mag);
            boxPhUb->setValue(para.phaseData.ang);
            boxFb->setValue(para.phaseData.freq);
        }
        else if (para.phaseName.toLower()=="uc")
        {
            boxUc->setValue(para.phaseData.mag);
            boxPhUc->setValue(para.phaseData.ang);
            boxFc->setValue(para.phaseData.freq);
        }
        else if (para.phaseName.toLower()=="ux")
        {
            boxUx->setValue(para.phaseData.mag);
            boxPhUx->setValue(para.phaseData.ang);
            boxFx->setValue(para.phaseData.freq);
        }
        else if (para.phaseName.toLower()=="ia")
        {
            boxIa->setValue(para.phaseData.mag);
            boxPhIa->setValue(para.phaseData.ang);
        }
        else if (para.phaseName.toLower()=="ib")
        {
            boxIb->setValue(para.phaseData.mag);
            boxPhIb->setValue(para.phaseData.ang);
        }
        else if (para.phaseName.toLower()=="ic")
        {
            boxIc->setValue(para.phaseData.mag);
            boxPhIc->setValue(para.phaseData.ang);
        }
        else if (para.phaseName.toLower()=="ix")
        {
            boxIx->setValue(para.phaseData.mag);
            boxPhIx->setValue(para.phaseData.ang);
        }
    }
}

void ModelDataWidget::slotAddLoop()
{
    if(m_modelData->loops.size()<0)
    {
        qDebug()<<"No loop template.From:ModelDataWidget::slotAddLoop()";
        return;
    }
    m_modelData->addLoop(m_modelData->loops.last());
    emit sigModelUpdated();

    //select the last loop button
    int count = groupLoops->buttons().count();
    if (count>0)
    {
        groupLoops->buttons().at(count-1)->setChecked(true);
        emit sigLoopChecked(count-1);
    }
#ifdef DEBUG
    qDebug()<<"m_modelData"<<m_modelData->loops.size();
    qDebug()<<"groupLoops"<<groupLoops->buttons().count();
#endif
}

void ModelDataWidget::slotDeleteLoop()
{
    bool result = m_modelData->deleteLoop();
    if(!result)
    {
        return;
    }
    emit sigModelUpdated();

    int count = groupLoops->buttons().count();
    groupLoops->buttons().at(count-1)->setChecked(true);
    emit sigLoopChecked(count-1);

#ifdef DEBUG
    qDebug()<<"m_modelData"<<m_modelData->loops.size();
    qDebug()<<"groupLoops"<<groupLoops->buttons().count();
#endif
}

void ModelDataWidget::slotAddState()
{
    int loopIndex = groupLoops->checkedId();
    int statesCount = m_modelData->loops.at(loopIndex).loopValue.states.size();
    if(statesCount<0)
    {
        qDebug()<<"No state template.From:ModelDataWidget::slotAddState()";
        return;
    }
    LoopValue item = m_modelData->loops[loopIndex].loopValue.states.last();
    m_modelData->loops[loopIndex].loopValue.addState(item);

    //update state list
    emit sigLoopChecked(loopIndex);

    int count = groupStates->buttons().count();
    if(count>0)
    {
        groupStates->buttons().at(count-1)->setChecked(true);
        emit sigStateChecked(loopIndex,count-1);
    }
}

void ModelDataWidget::slotDeleteState()
{
    int loopIndex = groupLoops->checkedId();
    if(loopIndex<0)
    {
        qDebug()<<"no loop button is checked!From:ModelDataWidget::slotDeleteState()";
        return;
    }
    bool result = m_modelData->loops[loopIndex].loopValue.deleteState();
    if(!result)
    {
        return;
    }

    //update state list
    emit sigLoopChecked(loopIndex);

    int count = groupStates->buttons().count();
    if(count>0)
    {
        groupStates->buttons().at(count-1)->setChecked(true);
        emit sigStateChecked(loopIndex,count-1);
    }
}

void ModelDataWidget::initUi()
{
    //set widget background color
    QPalette background ;
    background.setColor( QPalette::Background, QColor( 255, 255, 255) );
    this->setPalette( background );
    this->setAutoFillBackground(true);

    //设置禁止垂直缩放
    QSizePolicy sizepolicy = this->sizePolicy();
    sizepolicy.setHorizontalPolicy(QSizePolicy::Fixed);
    sizepolicy.setVerticalPolicy(QSizePolicy::Fixed);
    this->setSizePolicy(sizepolicy);

    QVBoxLayout* gridLayout {new QVBoxLayout};
    gridLayout->addLayout(createDataGrid());
    gridLayout->addStretch();

    QVBoxLayout* optionsLayout {new QVBoxLayout};
    optionsLayout->addWidget(createOptionsWidget());

    QHBoxLayout* mainLayout { new QHBoxLayout(this)};
    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(optionsLayout);
    mainLayout->addStretch();
    //mainLayout->setSizeConstraint(QLayout::SetFixedSize);
}

void ModelDataWidget::initSpinBox()
{
    //SetSuffix
    {
        boxUa->setSuffix(unitU);
        boxUb->setSuffix(unitU);
        boxUc->setSuffix(unitU);
        boxUx->setSuffix(unitU);

        boxIa->setSuffix(unitI);
        boxIb->setSuffix(unitI);
        boxIc->setSuffix(unitI);
        boxIx->setSuffix(unitI);

        boxPhUa->setSuffix("°");
        boxPhUb->setSuffix("°");
        boxPhUc->setSuffix("°");
        boxPhUx->setSuffix("°");

        boxPhIa->setSuffix("°");
        boxPhIb->setSuffix("°");
        boxPhIc->setSuffix("°");
        boxPhIx->setSuffix("°");

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
        boxUa->setRange(0,100);
        boxUb->setRange(0,100);
        boxUc->setRange(0,100);
        boxUx->setRange(0,100);

        boxIa->setRange(0,100);
        boxIb->setRange(0,100);
        boxIc->setRange(0,100);
        boxIx->setRange(0,100);

        boxPhUa->setRange(0,359.99);
        boxPhUb->setRange(0,359.99);
        boxPhUc->setRange(0,359.99);
        boxPhUx->setRange(0,359.99);

        boxPhIa->setRange(0,359.99);
        boxPhIb->setRange(0,359.99);
        boxPhIc->setRange(0,359.99);
        boxPhIx->setRange(0,359.99);

        boxPa->setRange(0,100);
        boxPb->setRange(0,100);
        boxPc->setRange(0,100);
        boxPx->setRange(0,100);
        boxPsum->setRange(0,100);

        boxQa->setRange(0,100);
        boxQb->setRange(0,100);
        boxQc->setRange(0,100);
        boxQx->setRange(0,100);
        boxQsum->setRange(0,100);

        boxFa->setRange(0,125);
        boxFb->setRange(0,125);
        boxFc->setRange(0,125);
        boxFx->setRange(0,125);
    }

    //setSingleStep
    {
        boxUa->setSingleStep(10);
        boxUb->setSingleStep(10);
        boxUc->setSingleStep(10);
        boxUx->setSingleStep(10);

        boxIa->setSingleStep(10);
        boxIb->setSingleStep(10);
        boxIc->setSingleStep(10);
        boxIx->setSingleStep(10);

        boxPhUa->setSingleStep(30);
        boxPhUb->setSingleStep(30);
        boxPhUc->setSingleStep(30);
        boxPhUx->setSingleStep(30);

        boxPhIa->setSingleStep(30);
        boxPhIb->setSingleStep(30);
        boxPhIc->setSingleStep(30);
        boxPhIx->setSingleStep(30);

        boxPa->setSingleStep(10);
        boxPb->setSingleStep(10);
        boxPc->setSingleStep(10);
        boxPx->setSingleStep(10);
        boxPsum->setSingleStep(10);

        boxQa->setSingleStep(10);
        boxQb->setSingleStep(10);
        boxQc->setSingleStep(10);
        boxQx->setSingleStep(10);
        boxQsum->setSingleStep(10);

        boxFa->setSingleStep(1);
        boxFb->setSingleStep(1);
        boxFc->setSingleStep(1);
        boxFx->setSingleStep(1);
    }
}

QGridLayout* ModelDataWidget::createDataGrid()
{
    QGridLayout* dataGrid = new QGridLayout;
    //row 0 header
    dataGrid->addWidget(new QLabel("A"),0,2,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel("B"),0,3,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel("C"),0,4,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel("X"),0,5,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel("Σ"),0,6,Qt::AlignCenter);

    //colum 0 header
    dataGrid->addWidget(new QLabel("U"),1,0,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel("I"),2,0,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel("ΦU"),3,0,Qt::AlignCenter);
    dataGrid->addWidget(new QLabel("ΦI"),4,0,Qt::AlignCenter);
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

QSplitter *ModelDataWidget::createOptionsWidget()
{
    QSplitter* splitterMain = new QSplitter(Qt::Horizontal);
    QPalette background ;
    background.setColor( QPalette::Background, QColor( 240, 248, 255) );

    //loops widget
    {
        QWidget* loopOptionsWidget = new QWidget(splitterMain);
        QVBoxLayout* mainLayout {new QVBoxLayout(loopOptionsWidget)};
        loopOptionsWidget->setPalette(background);
        loopOptionsWidget->setAutoFillBackground(true);

        QHBoxLayout* loopscommandLayout {new QHBoxLayout};
        loopscommandLayout->addWidget(btnAddLoop);
        loopscommandLayout->addWidget(btnDeleteLoop);

        mainLayout->addLayout(loopscommandLayout);
        mainLayout->addLayout(loopsLayout);
        mainLayout->addStretch();
    }

    //states widget
    {
        QWidget* stateOptionsWidget = new QWidget(splitterMain);
        QVBoxLayout* stateMainLayout {new QVBoxLayout(stateOptionsWidget)};
        stateOptionsWidget->setPalette(background);
        stateOptionsWidget->setAutoFillBackground(true);

        QHBoxLayout* statesscommandLayout {new QHBoxLayout};
        statesscommandLayout->addWidget(btnAddState);
        statesscommandLayout->addWidget(btnDeleteState);

        stateMainLayout->addLayout(statesscommandLayout);
        stateMainLayout->addLayout(statesLayout);
        stateMainLayout->addStretch();
    }

    return splitterMain;
}

void ModelDataWidget::initConnections()
{
    //when model data updated,update loop list
    connect(this,&ModelDataWidget::sigModelUpdated,this,&ModelDataWidget::slotUpdateLoopsList);

    //when a loop button checked,update state list
    connect(this,&ModelDataWidget::sigLoopChecked,this,&ModelDataWidget::slotUpdateStatesList);

    //when a state button checked,update grid data
    connect(this,&ModelDataWidget::sigStateChecked,this,&ModelDataWidget::slotUpdateDataGrid);

    //a loop checked by user
    connect(groupLoops,&QButtonGroup::idClicked,this,&ModelDataWidget::slotUpdateStatesList);

    //a state checked by user
    connect(groupStates,&QButtonGroup::idClicked,this,[=](int stateIndex)
    {
        int loopIndex = groupLoops->checkedId();
        emit sigStateChecked(loopIndex,stateIndex);
    });

    //add a loop
    connect(btnAddLoop,&QPushButton::clicked,this,&ModelDataWidget::slotAddLoop);

    //add a state
    connect(btnAddState,&QPushButton::clicked,this,&ModelDataWidget::slotAddState);

    //delete a loop
    connect(btnDeleteLoop,&QPushButton::clicked,this,&ModelDataWidget::slotDeleteLoop);

    //delete a state
    connect(btnDeleteState,&QPushButton::clicked,this,&ModelDataWidget::slotDeleteState);
}






