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

void SchemeConvertor::writeToJsonFile(SchemeModel schememodel, QString filePath )
{
	if ( filePath.isEmpty( ) )
	{
		return;
	}
    QJsonObject schememodelObject = schememodel.toJson( );
    QJsonDocument schemeDoc( schememodelObject );
	QByteArray jsonData = schemeDoc.toJson( );

	QFile file( filePath );
	if ( !file.open( QIODevice::WriteOnly ) )
	{
		qDebug( ) << tr( "Open json file failed!Message from:SchemeTranslator::writeToJsonFile(Scheme scheme)" );
		return;
	}
	file.write( jsonData );
	file.close( );
    emit sigReturnJsonData( schememodelObject );
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

    SchemeModel schememodel;
	if ( jsonDoc.isObject( ) )
	{
        schememodel.fromJson( jsonDoc.object( ) );
	}
    emit sigReturnScheme( schememodel );
    emit sigReturnJsonData( jsonDoc.object() );
}


