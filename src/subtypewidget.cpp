#include "subtypewidget.h"
#include <QLayout>
#include <QFormLayout>
#include <QRadioButton>


SubtypeWidget::SubtypeWidget(QWidget *parent)
    : QWidget{parent}
{
    initUi();
    initConnections();
}

void SubtypeWidget::setModel(SubType &model)
{
    m_model = &model;
    if(m_model)
    {
        emit sigModelUpdated();
    }
}

QString SubtypeWidget::name()
{
    if(m_model)
    {
        return m_model->name;
    }
    return QString();
}

void SubtypeWidget::initUi()
{
    QWidget* infoWidget {new QWidget};
    {
        //设置窗口背景色
        QPalette background;
        background.setColor( QPalette::Background, QColor(240,240,240) );
        infoWidget->setPalette( background );
        infoWidget->setAutoFillBackground( true );

        //测试项类型
        QFormLayout* typeForm {new QFormLayout};
        typeForm->addRow(tr("Type:"),typeLable);

        //测试项ID
        QFormLayout* idForm {new QFormLayout};
        idForm->addRow(tr("ID:"),idLable);

        QHBoxLayout* infoLayout {new QHBoxLayout};
        infoLayout->addWidget(nameLable);

        infoLayout->addStretch();
        infoLayout->addLayout(typeForm);
        infoLayout->addSpacing(20);
        infoLayout->addLayout(idForm);

        infoWidget->setLayout(infoLayout);
    }

    QHBoxLayout* pointsGroupLayout {new QHBoxLayout};
    testpointsGroup->setLayout(pointsGroupLayout);
    testpointsGroup->setTitle(tr("Test Points"));

    QVBoxLayout* mainLayout {new QVBoxLayout(this)};
    mainLayout->addWidget(infoWidget);
    mainLayout->addWidget(testpointsGroup);
    mainLayout->addWidget(testpointWidget);

    //设置测试项名称字体
    {
        QFont nameFont;
        nameFont.setPointSize(18);
        nameLable->setFont(nameFont);
    }

    //设置按钮、增加测试点输入框尺寸策略
    {
        addTestpointButton->setIcon(QIcon("://icons/icons8-plus-48.png"));
        deleteTestpointButton->setIcon(QIcon("://icons/icons8-minus-48.png"));
        QSizePolicy sizePolicy ;
        sizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
        addTestpointButton->setSizePolicy(sizePolicy);
        deleteTestpointButton->setSizePolicy(sizePolicy);

        addPointSpinbox->setSizePolicy(sizePolicy);
        addPointSpinbox->setRange(0,120);
        addPointSpinbox->setSuffix(" %");
        addPointSpinbox->setSingleStep(5);
    }
}

void SubtypeWidget::initConnections()
{
    connect(this,&SubtypeWidget::sigModelUpdated,this,[=]
    {
        nameLable->setText(m_model->name);
        typeLable->setText(m_model->type);
        idLable->setText(m_model->id);
        initTestpointsGroup();
    });

    connect(addTestpointButton,&QPushButton::clicked,this,[=]
    {
//        if(!addPointSpinbox->value())
//        {
//            return;
//        }
        m_model->addTestPoint(addPointSpinbox->value());
        emit sigModelUpdated();
    });

    connect(deleteTestpointButton,&QPushButton::clicked,this,[=]
    {

    });
}

void SubtypeWidget::initTestpointsGroup()
{
    QList<QRadioButton*> btns = testpointsGroup->findChildren<QRadioButton*>();//获取所有按钮
    foreach (QRadioButton* btn, btns)
    {
        delete btn;    //析构所有按钮
    }

    for (int i = 0; i < m_model->testPoints.size(); ++i)
    {
        QString testPointName = m_model->testPoints.at(i).name;
        QRadioButton* pointButton {new QRadioButton(testPointName)};
        connect(pointButton,&QRadioButton::clicked,this,[=]
        {
            testpointWidget->setModel(m_model->testPoints[i]);
        });
        testpointsGroup->layout()->addWidget(pointButton);
    }

    testpointsGroup->layout()->addWidget(addPointSpinbox);
    testpointsGroup->layout()->addWidget(addTestpointButton);
    testpointsGroup->layout()->addWidget(deleteTestpointButton);
}
