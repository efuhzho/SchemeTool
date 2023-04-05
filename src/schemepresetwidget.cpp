#include "schemepresetwidget.h"

#include <QLayout>
#include <QFormLayout>

SchemePresetWidget::SchemePresetWidget( QWidget* parent )
	: QWidget { parent }
{

	initUi( );
	initSpinBox( );
	initConnections( );
}

void SchemePresetWidget::setModel( Preset& preset )
{
	m_preset = &preset;
	if ( !m_preset )
	{
		return;
	}
	modelDataWidget->setModel( m_preset->modelData );

	lableName->setText( m_preset->name );
	spinboxVolt->setValue( m_preset->edVolt );
	spinboxCurr->setValue( m_preset->edCurr );
}

QString SchemePresetWidget::name( )
{
	return m_preset->name;
}

void SchemePresetWidget::initUi( )
{
	QFormLayout* voltLayout = new QFormLayout;
	voltLayout->addRow( tr( "Rated Voltage" ), spinboxVolt );

	QFormLayout* currLayout = new QFormLayout;
	currLayout->addRow( tr( "Rated Current" ), spinboxCurr );

	QHBoxLayout* ratedValueLayout { new QHBoxLayout };
	ratedValueLayout->addLayout( voltLayout );
	ratedValueLayout->addSpacing( 20 );
	ratedValueLayout->addLayout( currLayout );
	ratedValueLayout->addStretch( );

	QVBoxLayout* vLayout = new QVBoxLayout( this );
	vLayout->addWidget( lableName );
	vLayout->addLayout( ratedValueLayout );
	vLayout->addWidget( modelDataWidget );
	vLayout->addStretch( );
}

void SchemePresetWidget::initSpinBox( )
{
	spinboxVolt->setSuffix( "V" );
	spinboxVolt->setRange( 0, 380 );
	spinboxVolt->setSingleStep( 10 );
	//spinboxVolt->setKeyboardTracking(false);

	spinboxCurr->setSuffix( "A" );
	spinboxCurr->setRange( 0, 20 );
	spinboxCurr->setSingleStep( 1 );
	//spinboxCurr->setKeyboardTracking(false);
}

void SchemePresetWidget::initConnections( )
{
	connect( spinboxVolt, qOverload<double>( &QDoubleSpinBox::valueChanged ), this, [=]( double value )
		{
			m_preset->edVolt = value;
		} );
	connect( spinboxCurr, qOverload<double>( &QDoubleSpinBox::valueChanged ), this, [=]( double value )
		{
			m_preset->edCurr = value;
		} );
}
