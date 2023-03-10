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
    initWindow( );
    initConnections( );
    initToolbars( );
    initStatusBar( );
}

MainWindow::~MainWindow( )
{
    delete ui;
}

void MainWindow::onFileChanged( QString filePath )
{
    m_lableFilePath->setText( filePath );

    //init widgets data
    m_schemeInfoWidget->initData();
    m_presetWidget->initData();
    initStackWidget();
}

void MainWindow::onReturnScheme( Scheme scheme )
{
    m_scheme = scheme;    
}

void MainWindow::onReturnJsonData(QJsonObject jsonObject )
{
    m_schemeTree->setJsonData( jsonObject );
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
    emit sigFileChanged( filePath );
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
    emit sigFileChanged( filePath );
}

void MainWindow::onActionNew( )
{

}

void MainWindow::onTreeItemClicked(QTreeWidgetItem *item, int column)
{
    if(item->text(column)==m_schemeInfoWidget->name())
    {
        m_stackWidget->setCurrentWidget(m_schemeInfoWidget);
    }
    else if (item->text(column)==m_presetWidget->name())
    {
        m_stackWidget->setCurrentWidget(m_presetWidget);
    }
}

void MainWindow::initWindow( )
{
    //global mainwindow settings
    this->setFont( QFont( "Microsoft Yahei" ) );
    this->setWindowTitle( tr( "Scheme Editor" ) );
    this->setContentsMargins( 4, 0, 4, 0 );

    //set window background color
    QPalette background;
    background.setColor( QPalette::Background, QColor( 240, 248, 255) );
    this->setPalette( background );

    //main window layout
    QVBoxLayout* mainLayout = new QVBoxLayout( ui->centralwidget );
    mainLayout->addWidget( m_stackWidget );
    mainLayout->setMargin( 0 );

    //treewidget dock
    QDockWidget* treeDock = new QDockWidget( tr( "Scheme" ) );
    treeDock->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
    treeDock->setFeatures( QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable );
    treeDock->setWidget( m_schemeTree );
    this->addDockWidget( Qt::LeftDockWidgetArea, treeDock );
}

void MainWindow::initToolbars( )
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

void MainWindow::initStatusBar( )
{
    this->statusBar( )->addWidget( m_lableFilePath );
}

void MainWindow::initConnections( )
{
    //when file changed
    connect( this, &MainWindow::sigFileChanged, this, &MainWindow::onFileChanged );

    //connect to Actions
    connect( m_actionLoad, &QAction::triggered, this, &MainWindow::onActionLoad );
    connect( m_actionDump, &QAction::triggered, this, &MainWindow::onActionDump );
    connect( m_actionNew, &QAction::triggered, this, &MainWindow::onActionNew );

    //connect to SchemeConvertor signals
    connect( m_schemeConvertor, &SchemeConvertor::sigReturnJsonData, this, &MainWindow::onReturnJsonData );
    connect( m_schemeConvertor, &SchemeConvertor::sigReturnScheme, this, &MainWindow::onReturnScheme );

    //connect to treeWidget signals
    connect(m_schemeTree,&SchemeTreeWidget::sigItemClicked,this,&MainWindow::onTreeItemClicked);

}

void MainWindow::initStackWidget()
{
    m_stackWidget->addWidget(m_schemeInfoWidget);
    m_stackWidget->addWidget(m_presetWidget);
}

