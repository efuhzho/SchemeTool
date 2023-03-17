#include "modeldatawidget.h"
#include <QPushButton>
#include <QDebug>

ModelDataWidget::ModelDataWidget(QWidget *parent)
    : QWidget{parent}
{
    initUi();
    initConnections();
}

void ModelDataWidget::setModel(ModelData& modeldata)
{
    m_modelData = modeldata;
    emit sigModelUpdated();
}

void ModelDataWidget::onModelUpdated()
{
    QList<QAbstractButton*> btnsInGroup = groupLoops->buttons();
    foreach (QAbstractButton *btn, btnsInGroup)
    {
        if(btn)
        {
            delete btn;
        }
    }

    QStringList loopnames = m_modelData.loops.keys();
    for (int i = 0; i < loopnames.size(); ++i)
    {
        QRadioButton* radbtn = new QRadioButton(loopnames[i]);
        groupLoops->addButton(radbtn,i);
        loopsLayout->addWidget(radbtn);
    }

    QString btnText;
    Loop loop;
    if(groupLoops->buttons().count()>0)
    {
        groupLoops->buttons().at(0)->setChecked(true);
        btnText = groupLoops->checkedButton()->text();
        loop = m_modelData.loops[btnText];
    }

    emit sigLoopChecked(loop);
}

void ModelDataWidget::onLoopChecked(Loop &loop)
{
    QList<QAbstractButton*> btnsInGroup = groupStates->buttons();
    foreach (QAbstractButton *btn, btnsInGroup)
    {
        if(btn)
        {
            delete btn;
        }
    }

    QStringList statenames = loop.states.keys();
    if(statenames.isEmpty())
    {
        return;
    }

    for (int i = 0; i < statenames.size(); ++i)
    {
        QRadioButton* radioState = new QRadioButton(statenames[i]);

        groupStates->addButton(radioState,i);
        statesLayout->addWidget(radioState);
    }

    QString btnText;
    State state;
    if(groupStates->buttons().count()>0)
    {
        groupStates->buttons().at(0)->setChecked(true);
        btnText = groupStates->checkedButton()->text();
        state = loop.states[btnText];
    }
    emit sigStateChecked(state);
}

void ModelDataWidget::onStateChecked(State& state)
{        
    m_stateWidget->setModel(state);
}

void ModelDataWidget::slotAddLoop()
{
    m_modelData.addLoop();
    emit sigModelUpdated();

    groupLoops->buttons().at(0)->setChecked(true);
    QString btnText = groupLoops->checkedButton()->text();

    Loop loop = m_modelData.loops[btnText];
    emit sigLoopChecked(loop);
}

void ModelDataWidget::slotDeleteLoop()
{
    bool result = m_modelData.deleteLoop();
    if(!result)
    {
        return;
    }
    emit sigModelUpdated();
    int count = groupLoops->buttons().count();
    if(count==0)
    {
        return;
    }
    groupLoops->buttons().at(count-1)->setChecked(true);
    QString btnText = groupLoops->checkedButton()->text();

    Loop loop = m_modelData.loops[btnText];
    emit sigLoopChecked(loop);
}

void ModelDataWidget::slotAddState()
{
    QString loopname= groupLoops->checkedButton()->text();

    m_modelData.loops[loopname].addState();

    //update state list
    emit sigLoopChecked(m_modelData.loops[loopname]);

    int count = groupStates->buttons().count();
    if(count>0)
    {
        groupStates->buttons().at(count-1)->setChecked(true);
        QString statename = groupStates->checkedButton()->text();
        State state = m_modelData.loops[loopname].states[statename];
        emit sigStateChecked(state);
    }
}

void ModelDataWidget::slotDeleteState()
{
    QString loopname = groupLoops->checkedButton()->text();

    bool result =m_modelData.loops[loopname].deleteState();

    if(!result)
    {
        return;
    }

    //update state list
    emit sigLoopChecked(m_modelData.loops[loopname]);

    int count = groupStates->buttons().count();
    groupStates->buttons().at(count)->setChecked(true);
    QString statename = groupStates->checkedButton()->text();
    emit sigStateChecked(m_modelData.loops[loopname].states[statename]);

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

    QVBoxLayout* optionsLayout {new QVBoxLayout};
    optionsLayout->addWidget(createOptionsWidget());

    QHBoxLayout* mainLayout { new QHBoxLayout(this)};
    mainLayout->addWidget(m_stateWidget);
    mainLayout->addLayout(optionsLayout);
    mainLayout->addStretch();
    //mainLayout->setSizeConstraint(QLayout::SetFixedSize);
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
    connect(this,&ModelDataWidget::sigModelUpdated,this,&ModelDataWidget::onModelUpdated);

    //when a loop button checked,update state list
    connect(this,&ModelDataWidget::sigLoopChecked,this,&ModelDataWidget::onLoopChecked);

    //when a state button checked,update grid data
    connect(this,&ModelDataWidget::sigStateChecked,this,&ModelDataWidget::onStateChecked);

    //a loop checked by user
    connect(groupLoops,qOverload<QAbstractButton *>(&QButtonGroup::buttonClicked),this,[=](QAbstractButton *button)
    {
        emit sigLoopChecked(m_modelData.loops[button->text()]);
    });

    //a state checked by user
    connect(groupStates,QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),this,[=](QAbstractButton *button)
    {
        QString loopname = groupLoops->checkedButton()->text();
        emit sigStateChecked(m_modelData.loops[loopname].states[button->text()]);
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








