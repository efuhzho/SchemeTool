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

    QHBoxLayout* secondRow {new QHBoxLayout};
    {
        QHBoxLayout* pointsGroupLayout {new QHBoxLayout};
        testpointsGroup->setLayout(pointsGroupLayout);
        testpointsGroup->setTitle(tr("Test Points"));
        secondRow->addWidget(testpointsGroup);

        QHBoxLayout* btnLayout {new QHBoxLayout};
        btnLayout->addWidget(addPointSpinbox);
        btnLayout->addWidget(addTestpointButton);
        btnLayout->addWidget(deleteTestpointButton);
        secondRow->addLayout(btnLayout);
    }

    QVBoxLayout* mainLayout {new QVBoxLayout(this)};
    mainLayout->addWidget(infoWidget);
    mainLayout->addLayout(secondRow);
    mainLayout->addWidget(testpointWidget);

    //设置测试项名称字体
    {
        QFont nameFont;
        nameFont.setPointSize(18);
        nameLable->setFont(nameFont);
    }

    //设置:按钮、测试点输入框尺寸策略
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
        currentPointName = QString();
        initTestpointsGroup();
    });

    connect(addTestpointButton,&QPushButton::clicked,this,[=]
    {
        QString testPointName = m_model->addTestPoint(addPointSpinbox->value());

        if(testPointName.isEmpty())
        {
            return;
        }

        currentPointName = testPointName;
        emit sigModelUpdated();
    });

    connect(deleteTestpointButton,&QPushButton::clicked,this,[=]
    {
        bool result =  m_model->deleteTestPoint(currentPointName);
        if(result)
        {
            currentPointName = QString();
            emit sigModelUpdated();
        }
    });
}

void SubtypeWidget::initTestpointsGroup()
{
    //释放原有按钮资源
    QList<QRadioButton*> btns = testpointsGroup->findChildren<QRadioButton*>();//获取所有按钮
    foreach (QRadioButton* btn, btns)
    {
        delete btn;    //析构所有按钮
    }

    QList<TestPointName> pointNames = m_model->testPoints.keys();
    for (int i = 0; i < pointNames.size(); ++i)
    {
        //逐个添加按钮
        QString testPointName =pointNames[i].toString() ;

        QRadioButton* pointButton {new QRadioButton(testPointName)};
        connect(pointButton,&QRadioButton::clicked,this,[=]
        {
            currentPointName = pointButton->text();
            testpointWidget->setModel(m_model->testPoints[testPointName]);
        });
        testpointsGroup->layout()->addWidget(pointButton);

        //设置默认选中的按钮
        if(i==0 && currentPointName.isEmpty())
        {
           currentPointName = pointButton->text();
           pointButton->setChecked(true);
           emit pointButton->clicked(true);
        }
    }

    //重新选中测试点按钮
    QList<QRadioButton*> afterBtns = testpointsGroup->findChildren<QRadioButton*>();//获取所有按钮
    foreach (QRadioButton* btn, afterBtns)
    {
        if(btn->text() == currentPointName)
        {
            btn->setChecked(true);
            emit btn->clicked(true);
        }
    }
}
