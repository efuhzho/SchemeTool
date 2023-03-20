#ifndef TESTPOINTWIDGET_H
#define TESTPOINTWIDGET_H

#include <QWidget>
#include <QLineEdit>

#include "schememodeldefine.h"
#include "modeldatawidget.h"

class TestPointWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TestPointWidget(QWidget *parent = nullptr);
    void setModel(TestPoint& model);

signals:
    void sigModelUpdated();

private:
    TestPoint* m_testPoint;

    QLineEdit* nameLineEdit {new QLineEdit};
    QLineEdit* unitLineEdit {new QLineEdit};
    QLineEdit* varLineEdit {new QLineEdit};
    QLineEdit* idLineEdit {new QLineEdit};
    ModelDataWidget* widgetModelData {new ModelDataWidget};

private:
    void initUi();
    void initConnections();

};

#endif // TESTPOINTWIDGET_H
