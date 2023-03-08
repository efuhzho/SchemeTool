#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QDebug>
#include <QFileDialog>
#include <QToolBar>
#include <QLayout>
#include <QDockWidget>

MainWindow::MainWindow( QWidget* parent )
	: QMainWindow( parent )
	, ui( new Ui::MainWindow )
{
	ui->setupUi( this );

#if 0
	{
		connect( m_schemeConvertor, &SchemeConvertor::sigReturnScheme, this, &MainWindow::onReturnScheme );
		QString filePath = QFileDialog::getOpenFileName( );
		qDebug( ) << filePath;
		m_schemeConvertor->readFromJsonFile( filePath );
		QString savepath = QFileDialog::getSaveFileName( );
		m_schemeConvertor->writeToJsonFile( m_scheme, savepath );
	}
#endif

	initWindow( );
	initConnections( );
	createToolbars( );
	createStatusBar( );

}

MainWindow::~MainWindow( )
{
	delete ui;
}

void MainWindow::onFileUpdated( QString filePath )
{
	m_lableFilePath->setText( filePath );
}

void MainWindow::onReturnScheme( Scheme scheme )
{
	m_scheme = scheme;
}

void MainWindow::onReturnJsonData( QByteArray jsonData )
{
	m_schemeTree->parseJsonRoot( jsonData );
}

void MainWindow::onActionLoad( )
{
	QString filePath { QCoreApplication::applicationDirPath( ) };
	filePath = QFileDialog::getOpenFileName( this, tr( "Load" ), filePath, "scheme(*.json)" );
	if ( filePath.isEmpty( ) )
	{
		return;
	}
	m_schemeConvertor->readFromJsonFile( filePath );
	emit sigFileUpdated( filePath );
}

void MainWindow::onActionDump( )
{
	QString filePath { QCoreApplication::applicationDirPath( ) };
	filePath = QFileDialog::getSaveFileName( this, tr( "Dump" ), filePath, "scheme(*.json)" );
	if ( filePath.isEmpty( ) )
	{
		return;
	}
	m_schemeConvertor->writeToJsonFile( m_scheme, filePath );
	emit sigFileUpdated( filePath );
}

void MainWindow::onActionNew( )
{

}

void MainWindow::initWindow( )
{
	//global settings
	this->setFont( QFont( "Microsoft Yahei" ) );
	this->setWindowTitle( tr( "Scheme Editor" ) );
	this->setContentsMargins( 4, 0, 4, 0 );

	//set window background color
	QPalette p;
	p.setColor( QPalette::Background, QColor( 240, 248, 255 ) );
	this->setPalette( p );

	//main window layout
	QHBoxLayout* mainLayout = new QHBoxLayout( ui->centralwidget );
	mainLayout->addWidget( new QPushButton );
	mainLayout->setMargin( 0 );

	//treewidget dock
	QDockWidget* treeDock = new QDockWidget( tr( "Scheme" ) );
	treeDock->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
	treeDock->setFeatures( QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable );
	treeDock->setWidget( m_schemeTree );
	this->addDockWidget( Qt::LeftDockWidgetArea, treeDock );
}

void MainWindow::createToolbars( )
{
	QToolBar* toolbar = new QToolBar;
	toolbar->layout( )->setSpacing( 4 );
	toolbar->layout( )->setMargin( 4 );

	toolbar->addAction( m_actionNew );
	toolbar->addSeparator( );
	toolbar->addAction( m_actionLoad );
	toolbar->addAction( m_actionDump );
	this->addToolBar( toolbar );
}

void MainWindow::createStatusBar( )
{
	this->statusBar( )->addWidget( m_lableFilePath );
}

void MainWindow::initConnections( )
{
	//when file changed
	connect( this, &MainWindow::sigFileUpdated, this, &MainWindow::onFileUpdated );

	//connect to Actions
	connect( m_actionLoad, &QAction::triggered, this, &MainWindow::onActionLoad );
	connect( m_actionDump, &QAction::triggered, this, &MainWindow::onActionDump );
	connect( m_actionNew, &QAction::triggered, this, &MainWindow::onActionNew );

	//connect to SchemeConvertor signals
	connect( m_schemeConvertor, &SchemeConvertor::sigReturnJsonData, this, &MainWindow::onReturnJsonData );
	connect( m_schemeConvertor, &SchemeConvertor::sigReturnScheme, this, &MainWindow::onReturnScheme );
}

