#include "modeldatawidget.h"
#include <QPushButton>
#include <QDebug>

ModelDataWidget::ModelDataWidget( QWidget* parent )
	: QWidget { parent }
{
	initUi( );
	initConnections( );
}

void ModelDataWidget::setModel( ModelData& model )
{
	m_model = &model;
	emit sigModelUpdated( );
}

ModelData* ModelDataWidget::Model( )
{
	return m_model;
}

void ModelDataWidget::setUnit( const QString unit )
{
	m_unit = unit;
}

QString ModelDataWidget::unit( )
{
	return m_unit;
}

void ModelDataWidget::updateLoopsListWidget( )
{
	loopsListWidget->clear( );
	statesListWidget->clear( );
	m_stateWidget->clear( );
	btnAddState->setEnabled( false );
	btnDeleteState->setEnabled( false );

	QStringList loopNames = m_model->loops.keys( );
	if ( loopNames.isEmpty( ) )
	{
		qDebug( ) << "loopNames is empty." << "from :ModelDataWidget::updateLoopsListWidget( )";
		return;
	}
	loopsListWidget->addItems( loopNames );
	int count = loopNames.count( );

	loopsListWidget->setCurrentItem( loopsListWidget->item( count - 1 ) );
}

void ModelDataWidget::updateStatesListWidget( QListWidgetItem* item )
{
	if ( !item )
	{
		return;
	}
	statesListWidget->clear( );
	btnAddState->setEnabled( true );
	btnDeleteState->setEnabled( true );

	QStringList stateNames = m_model->loops[item->text( )].states.keys( );
	if ( stateNames.isEmpty( ) )
	{
		qDebug( ) << "stateNames or QListWidgetItem* is empty." << "from :ModelDataWidget::updateStatesListWidget(QListWidgetItem *item)";
		return;
	}

	statesListWidget->addItems( stateNames );
	int count = stateNames.count( );
	statesListWidget->setCurrentItem( statesListWidget->item( count - 1 ) );
}

void ModelDataWidget::updateStateWidget( QListWidgetItem* item )
{
	if ( !item || !loopsListWidget->currentItem( ) )
	{
		qDebug( ) << "QListWidgetItem *item is empty." << "from :updateStateWidget(QListWidgetItem *item)";
		return;
	}
	QString loopName = loopsListWidget->currentItem( )->text( );
	QString stateName = item->text( );
	m_stateWidget->setModel( m_model->loops[loopName].states[stateName] );
}

void ModelDataWidget::initUi( )
{
	//设置窗口背景色
	QPalette background;
	background.setColor( QPalette::Background, QColor( 255, 255, 255 ) );
	this->setPalette( background );
	this->setAutoFillBackground( true );

	//设置禁止垂直缩放
	QSizePolicy sizepolicy = this->sizePolicy( );
	sizepolicy.setHorizontalPolicy( QSizePolicy::Fixed );
	sizepolicy.setVerticalPolicy( QSizePolicy::Fixed );
	this->setSizePolicy( sizepolicy );

	//创建主窗口布局控件
	QHBoxLayout* mainLayout { new QHBoxLayout( this ) };

	//创建回路布局
	{
		QVBoxLayout* loopsLayout { new QVBoxLayout };

		QHBoxLayout* loopButtons { new QHBoxLayout };
		loopButtons->addWidget( btnAddLoop );
		loopButtons->addWidget( btnDeleteLoop );

		loopsLayout->addWidget( loopsListWidget );
		loopsLayout->addLayout( loopButtons );

		mainLayout->addLayout( loopsLayout );
	}

	//创建状态步布局
	{
		QVBoxLayout* statesLayout { new QVBoxLayout };

		QHBoxLayout* statesButtons { new QHBoxLayout };
		statesButtons->addWidget( btnAddState );
		statesButtons->addWidget( btnDeleteState );

		statesLayout->addWidget( statesListWidget );
		statesLayout->addLayout( statesButtons );

		mainLayout->addLayout( statesLayout );
	}

	//设置按钮图标
	{
		btnAddLoop->setIcon( QIcon( "://icons/icons8-plus-48.png" ) );
		btnDeleteLoop->setIcon( QIcon( "://icons/icons8-minus-48.png" ) );
		btnAddState->setIcon( QIcon( "://icons/icons8-plus-48.png" ) );
		btnDeleteState->setIcon( QIcon( "://icons/icons8-minus-48.png" ) );
	}

	mainLayout->addWidget( m_stateWidget );
	mainLayout->addStretch( );
}

void ModelDataWidget::initConnections( )
{
	//更新loops列表
	connect( this, &ModelDataWidget::sigModelUpdated, this, &ModelDataWidget::updateLoopsListWidget );

	//更新states列表
	connect( loopsListWidget, &QListWidget::itemClicked, this, &ModelDataWidget::updateStatesListWidget );

	//更新stateWidget数据
	connect( statesListWidget, &QListWidget::itemClicked, this, &ModelDataWidget::updateStateWidget );

	//追加一个回路
	connect( btnAddLoop, &QPushButton::clicked, this, [=]
		{
			m_model->addLoop( );
			updateLoopsListWidget( );
		} );

	//删除一个回路
	connect( btnDeleteLoop, &QPushButton::clicked, this, [=]
		{
			bool result = m_model->deleteLoop( );
			if ( result )
			{
				updateLoopsListWidget( );
			}
		} );

	//追加一个状态步
	connect( btnAddState, &QPushButton::clicked, this, [=]
		{
			if ( !loopsListWidget->currentItem( ) )
			{
				qDebug( ) << "no current loop item." << "from :ModelDataWidget::initConnections( ).";
				return;
			}
			QString loopName = loopsListWidget->currentItem( )->text( );
			m_model->loops[loopName].addState( );
			updateStatesListWidget( loopsListWidget->currentItem( ) );
		} );

	//删除一个状态步
	connect( btnDeleteState, &QPushButton::clicked, this, [=]
		{
			if ( !loopsListWidget->currentItem( ) )
			{
				qDebug( ) << "no current loop item." << "from :ModelDataWidget::initConnections( ).";
				return;
			}
			QString loopName = loopsListWidget->currentItem( )->text( );
			m_model->loops[loopName].deleteState( );
			updateStatesListWidget( loopsListWidget->currentItem( ) );
		} );

	connect( loopsListWidget, &QListWidget::currentItemChanged, this, &ModelDataWidget::updateStatesListWidget );
	connect( statesListWidget, &QListWidget::currentItemChanged, this, &ModelDataWidget::updateStateWidget );
}
