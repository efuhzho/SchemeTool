#pragma once

#include <QJsonDocument>
#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLineEdit>
#include <QTimer>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>

#include "schemetreewidget.h"

SchemeTreeWidget::SchemeTreeWidget( QWidget* parent )
    : QWidget( parent )
{
    initWidget( );
    initConnection( );
}

SchemeTreeWidget::~SchemeTreeWidget( )
{}

void SchemeTreeWidget::initWidget( )
{
    vLayout = new QVBoxLayout( this );
    vLayout->setMargin(0);
    lineEdit = new QLineEdit( );
    lineEdit->setPlaceholderText( tr( "Search here..." ) );
    treeWidget = new QTreeWidget( );
    treeWidget->setHeaderHidden( true );

    vLayout->addWidget( lineEdit );
    vLayout->addWidget( treeWidget );
}

void SchemeTreeWidget::initConnection( )
{
    connect( lineEdit, &QLineEdit::textChanged, this, &SchemeTreeWidget::findItem );
    connect(treeWidget,&QTreeWidget::itemChanged,this,&SchemeTreeWidget::treeItemChanged);
}

void SchemeTreeWidget::parseJsonRoot(QByteArray jsonArray )
{
    treeWidget->clear( );
    QJsonParseError jsonError;
    QJsonObject jsonObject;
    QJsonDocument document = QJsonDocument::fromJson( jsonArray, &jsonError );
    if ( document.isNull( ) || jsonError.error != QJsonParseError::NoError )
    {
        return;
    }    
    jsonObject = document.object( );

    if ( !jsonObject.contains( "scheme" ) )
    {
        return;
    }
    QJsonValue schemeValue = jsonObject.value( "scheme" );

    if ( !schemeValue.toObject( ).contains( "test_type" ) )
    {
        return;
    }
    QJsonValue testTypeValue = schemeValue.toObject( ).value( "test_type" );

    if ( !testTypeValue.toObject( ).contains( "subtype" ) )
    {
        return;
    }
    QJsonValue subTypeValue = testTypeValue.toObject( ).value( "subtype" );

    if ( !subTypeValue.isArray( ) )
    {
        return;
    }

    QJsonArray array = subTypeValue.toArray( );
    int nSize = array.size( );

    for ( int i = 0; i < nSize; i++ )
    {
        QJsonObject object = array.at( i ).toObject( );
        if ( !( object.contains( "name" ) ) )
        {
            return;
        }

        QString itemText = object.value( "name" ).toString( );
        QJsonArray itemChild = object.value( "item" ).toArray( );

        QTreeWidgetItem* itemRoot = new QTreeWidgetItem( treeWidget, QStringList( itemText ) );
        treeWidget->addTopLevelItem( itemRoot );

        if ( itemChild.size( ) != 0 )
        {
            parseArray( itemChild, itemRoot );
        }
    }
}

void SchemeTreeWidget::parseObject( const QJsonObject& obj, QTreeWidgetItem* itemNode )
{
    if ( obj.contains( "name" ) )
    {
        QString itemText = obj.value( "name" ).toString( );
        QJsonArray itemChild = obj.value( "item" ).toArray( );

        QTreeWidgetItem* item = new QTreeWidgetItem( itemNode, QStringList( itemText ) );
        itemNode->addChild( item );
        item->setCheckState(0,Qt::Checked);

        if ( itemChild.size( ) != 0 )
        {
            parseArray( itemChild, item );
        }
    }
}

void SchemeTreeWidget::parseArray( const QJsonArray& arr, QTreeWidgetItem* itemNode )
{
    int size = arr.size( );
    for ( int i = 0; i < size; i++ )
    {
        QJsonObject obj = arr.at( i ).toObject( );
        parseObject( obj, itemNode );
    }
}

void SchemeTreeWidget::findItem( const QString& text )
{
    treeWidget->collapseAll( );
    if ( text.isEmpty( ) )
    {
        QTreeWidgetItemIterator it(treeWidget);
        while ( *it )
        {
            ( *it )->setForeground( 0, Qt::black );
            it++;
        }
        return;
    }
    if ( !treeWidget->topLevelItemCount( ) )
    {
        return;
    }

    QTreeWidgetItemIterator it( treeWidget );
    while ( *it )
    {
        this->setCursor( Qt::WaitCursor );
        QString str = ( *it )->text( 0 );
        if ( -1 != str.indexOf( text ) )
        {
            QTreeWidgetItem* pItem = ( *it )->parent( );
            if ( pItem != nullptr )
            {
                bool isExpanded = pItem->isExpanded( );
                if ( !isExpanded )
                {
                    treeWidget->expandItem( pItem );
                }
            }
            ( *it )->setForeground( 0, Qt::red );
            parentExpand( *it );
        }
        else
        {
            ( *it )->setForeground( 0, Qt::black );
        }
        it++;
    }
    this->setCursor( Qt::ArrowCursor );
}

void SchemeTreeWidget::parentExpand( QTreeWidgetItem* item )
{
    if ( item->parent( ) != nullptr )
    {
        QTreeWidgetItem* pItem = item->parent( );
        if ( !pItem->isExpanded( ) )
        {
            pItem->setExpanded( true );
        }
        parentExpand( pItem );
    }
}

void SchemeTreeWidget::treeItemChanged(QTreeWidgetItem *item, int column)
{
    if (item->checkState(column) == Qt::Checked)
    {
        int cnt = item->childCount();
        if (cnt >0)
        {
            for (int i = 0;i < cnt;i++)
            {
                item->child(i)->setCheckState(0,Qt::Checked);
            }
        }
        else
        {
            updateParentItem(item);
        }
    }
    else if (item->checkState(column) == Qt::Unchecked)
    {
        int cnt = item->childCount();
        if (cnt > 0)
        {
            for (int i = 0;i < cnt;i++)
            {
                item->child(i)->setCheckState(0,Qt::Unchecked);
            }
        }
        else
        {
            updateParentItem(item);
        }
    }
}
void SchemeTreeWidget::updateParentItem(QTreeWidgetItem *item)
{
    QTreeWidgetItem *parent = item->parent();
    if (parent == NULL)
    {
        return;
    }
    //选中的子节点个数
    int selectedCount = 0;
    int childCount = parent->childCount();
    for (int i = 0; i < childCount; i++)
    {
        QTreeWidgetItem *childItem = parent->child(i);
        if (childItem->checkState(0) == Qt::Checked)
        {
            selectedCount++;
        }
    }
    if (selectedCount <= 0)
    {
        //未选中状态
        parent->setCheckState(0, Qt::Unchecked);
    }
    else if (selectedCount > 0 && selectedCount < childCount)
    {
        //部分选中状态
        parent->setCheckState(0, Qt::PartiallyChecked);
    }
    else if (selectedCount == childCount)
    {
        //选中状态
        parent->setCheckState(0, Qt::Checked);
    }
}


