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
    vLayout->setSpacing(2);
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
   // connect(treeWidget,&QTreeWidget::itemChanged,this,&SchemeTreeWidget::treeItemChanged);
    connect(treeWidget,&QTreeWidget::itemClicked,this,&SchemeTreeWidget::onItemClicked);
}

void SchemeTreeWidget::setJsonData(QString jsonFilePath)
{   
    QFile jsonfile(jsonFilePath);
    if(! jsonfile.open(QIODevice::ReadOnly))
    {
        return;
    }
    QByteArray jsonBytes = jsonfile.readAll();
    jsonfile.close();
    setJsonData(jsonBytes);
}

void SchemeTreeWidget::setJsonData(QByteArray jsonBytes )
{
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson( jsonBytes, &jsonError );
    if ( document.isNull( ) || jsonError.error != QJsonParseError::NoError )
    {
        return;
    }
    setJsonData(document);
}

void SchemeTreeWidget::setJsonData(QJsonDocument jsonDoc)
{
    QJsonObject scheme = jsonDoc.object();
    setJsonData(scheme);
}

void SchemeTreeWidget::setJsonData(QJsonObject jsonObject)
{
    treeWidget->clear( );
    QJsonObject schemeValue = jsonObject[m_schemeKey].toObject();
    QString objectName = schemeValue[m_keyword].toString();

    QTreeWidgetItem* itemRoot = new QTreeWidgetItem( treeWidget,QStringList(objectName));
    itemRoot->setData(0,Qt::UserRole,schemeValue);
    treeWidget->addTopLevelItem( itemRoot );
    parseObject(schemeValue,itemRoot);
}

void SchemeTreeWidget::parseObject(const QJsonObject& obj, QTreeWidgetItem* parentNode )
{
    QTreeWidgetItem* child;
    if (obj.contains(m_keyword)&&obj[m_keyword].toString()!=parentNode->text(0))
    {
        QString value = obj[m_keyword].toString();
        child = new QTreeWidgetItem( parentNode,QStringList(value));
        //child->setCheckState(0,Qt::Checked);
        child->setData(0,Qt::UserRole,obj);
    }
    else
    {
        child = parentNode;
    }

    QStringList keys = obj.keys();
    for (int i = 0; i < keys.size(); ++i)
    {
        QJsonValue value = obj[keys[i]];
        if (value.isObject())
        {
            parseObject(value.toObject(),child);
        }
        else if (value.isArray())
        {
            parseArray(value.toArray(),child);
        }
    }
}

void SchemeTreeWidget::parseArray(const QJsonArray& arr, QTreeWidgetItem* parentNode )
{
    int size = arr.size( );
    for ( int i = 0; i < size; i++ )
    {
        QJsonObject obj = arr.at( i ).toObject( );
        parseObject( obj, parentNode );
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
        updateParentItem(item);
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
        updateParentItem(item);
    }
    else
    {
        updateParentItem(item);
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
    int unSelectedCount = 0;
    int childCount = parent->childCount();
    for (int i = 0; i < childCount; i++)
    {
        QTreeWidgetItem *childItem = parent->child(i);
        if (childItem->checkState(0) == Qt::Checked)
        {
            selectedCount++;
        }
        else if (childItem->checkState(0) == Qt::Unchecked)
        {
            unSelectedCount ++;
        }
    }
    if (unSelectedCount == childCount)
    {
        //子项全未选
        parent->setCheckState(0, Qt::Unchecked);
    }
    else if (selectedCount == childCount)
    {
        //子项全选中
        parent->setCheckState(0, Qt::Checked);
    }
    else
    {
        //部分选中状态
        parent->setCheckState(0, Qt::PartiallyChecked);
    }
}

void SchemeTreeWidget::onItemClicked(QTreeWidgetItem *item, int column)
{
    emit sigItemClicked(item,column);
}


