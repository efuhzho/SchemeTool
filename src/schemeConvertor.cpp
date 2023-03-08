#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QFileDialog>
#include <QDebug>

#include "schemeConvertor.h"

SchemeConvertor::SchemeConvertor( QObject* parent )
	: QObject { parent }
{

}

void SchemeConvertor::writeToJsonFile( Scheme scheme, QString filePath )
{
	if ( filePath.isEmpty( ) )
	{
		return;
	}
	QJsonObject schemeObject = scheme.toJson( );
	QJsonDocument schemeDoc( schemeObject );
	QByteArray jsonData = schemeDoc.toJson( );

	QFile file( filePath );
	if ( !file.open( QIODevice::WriteOnly ) )
	{
		qDebug( ) << tr( "Open json file failed!Message from:SchemeTranslator::writeToJsonFile(Scheme scheme)" );
		return;
	}
	file.write( jsonData );
	file.close( );
	emit sigReturnJsonData( jsonData );
}

void SchemeConvertor::readFromJsonFile( QString filePath )
{
	QFile file( filePath );
	if ( !file.open( QIODevice::ReadOnly ) )
	{
		qDebug( ) << tr( "Open json file failed!Message from:SchemeTranslator::readFromJsonFile(QString& filePath)" );
		return;
	}

	QByteArray fileData = file.readAll( );
	file.close( );
	QJsonParseError jsonError;
	QJsonDocument jsonDoc = QJsonDocument::fromJson( fileData, &jsonError );
	if ( jsonError.error != QJsonParseError::NoError )
	{
		qDebug( ) << tr( "Json file error.Message from:SchemeTranslator::readFromJsonFile(QString& filePath)" );
		return;
	}

	Scheme scheme;
	if ( jsonDoc.isObject( ) )
	{
		scheme.fromJson( jsonDoc.object( ) );
	}
	emit sigReturnScheme( scheme );
	emit sigReturnJsonData( fileData );
}

#if 0

#endif // 0

