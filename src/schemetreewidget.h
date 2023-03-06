#pragma once

#include <QWidget>
#include <QTreeWidget>
#include <QLineEdit>
#include <QLayout>
#include <QTreeWidgetItemIterator>
#include <QFile>

class SchemeTreeWidget  : public QWidget
{
	Q_OBJECT

public:
    SchemeTreeWidget(QWidget *parent = nullptr );
    ~SchemeTreeWidget();

    void initWidget( );
    void initConnection( );

    // 解析json并将指定字段添加到树节点
    void parseJsonRoot( QByteArray jsonArray );
    void parseObject( const QJsonObject& obj, QTreeWidgetItem* itemNode );
    void parseArray( const QJsonArray& arr, QTreeWidgetItem* itemNode );

    // 树节点查找功能
    void findItem( const QString& text );
    void parentExpand( QTreeWidgetItem* item );

private:
    void treeItemChanged(QTreeWidgetItem *item, int column);
    void updateParentItem(QTreeWidgetItem *item);

private:
    QLineEdit* lineEdit;
    QTreeWidget* treeWidget;
    QVBoxLayout* vLayout;  
};
