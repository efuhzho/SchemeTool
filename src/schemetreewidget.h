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

    void parseJsonRoot( QByteArray jsonArray );
    void parseObject( const QJsonObject& obj, QTreeWidgetItem* parentNode );
    void parseArray( const QJsonArray& arr, QTreeWidgetItem* parentNode );

    void findItem( const QString& text );
    void parentExpand( QTreeWidgetItem* item );
signals:
    void sigItemClicked(QTreeWidgetItem *item, int column);

private:
    void treeItemChanged(QTreeWidgetItem *item, int column);
    void updateParentItem(QTreeWidgetItem *item);
    void onItemClicked(QTreeWidgetItem *item, int column);

private:
    QLineEdit* lineEdit;
    QTreeWidget* treeWidget;
    QVBoxLayout* vLayout;
    QString m_schemeKey{"scheme"};
    QString m_keyword{"name"};
};
