#include "schemeinfowidget.h"

#include <QFormLayout>

SchemeInfoWidget::SchemeInfoWidget( QWidget* parent )
    : QWidget { parent }
{
    initUi( );
    initConnections( );
}

void SchemeInfoWidget::initUi( )
{
    QFormLayout* formLayout = new QFormLayout( this );
    formLayout->setRowWrapPolicy( QFormLayout::WrapAllRows );

    //add elements
    formLayout->addRow( tr( "Scheme Name:" ), lineEditSchemeName );
    formLayout->addRow( tr( "Version:" ), lineEditVersion );
    formLayout->addRow( tr( "Create Date:" ), lineEditCreateDate );
    formLayout->addRow( tr( "Update Date:" ), lineEditUpdateDate );
    formLayout->addRow( tr( "User:" ), lineEditUser );
    formLayout->addRow( tr( "Description:" ), textEditDescription );
}

void SchemeInfoWidget::initConnections( )
{
    //when scheme naem was edited
    connect( lineEditSchemeName, &QLineEdit::textEdited, this, [=]( QString text )
    {
        m_scheme->name = text;
    } );

    //when scheme version was edited
    connect( lineEditVersion, &QLineEdit::textEdited, this, [=]( QString text )
    {
        m_scheme->version = text;
    } );

    //when scheme create date was edited
    connect( lineEditCreateDate, &QLineEdit::textEdited, this, [=]( QString text )
    {
        m_scheme->createDate = text;
    } );

    //when scheme update date was edited
    connect( lineEditUpdateDate, &QLineEdit::textEdited, this, [=]( QString text )
    {
        m_scheme->updateDate = text;
    } );

    //when scheme user was edited
    connect( lineEditUser, &QLineEdit::textEdited, this, [=]( QString text )
    {
        m_scheme->user = text;
    } );

    //when scheme description was edited
    connect( textEditDescription, &QTextEdit::textChanged, this, [=]
    {
        m_scheme->description = textEditDescription->toPlainText( );
    } );
}

void SchemeInfoWidget::setModel( Scheme& scheme )
{
    m_scheme = &scheme;
    lineEditSchemeName->setText( m_scheme->name );
    lineEditVersion->setText( m_scheme->version );
    lineEditCreateDate->setText( m_scheme->createDate );
    lineEditUpdateDate->setText( m_scheme->updateDate );
    lineEditUser->setText( m_scheme->user );
    textEditDescription->setText( m_scheme->description );
}

QString SchemeInfoWidget::name( )
{
    return m_scheme->name;
}
