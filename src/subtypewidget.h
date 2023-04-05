#ifndef SUBTYPEWIDGET_H
#define SUBTYPEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QDoubleSpinBox>

#include "schememodeldefine.h"
#include "testpointwidget.h"

class SubtypeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubtypeWidget(QWidget *parent = nullptr);
    void setModel(SubType& model);
    QString name();

signals:
    void sigModelUpdated();

private:
    SubType* m_model;
    QString currentPointName {QString()};

    QLabel* nameLable {new QLabel};
    QLabel* typeLable {new QLabel};
    QLabel* idLable {new QLabel};
    QGroupBox* testpointsGroup {new QGroupBox};

    QPushButton* addTestpointButton {new QPushButton};
    QPushButton* deleteTestpointButton {new QPushButton};
    QDoubleSpinBox* addPointSpinbox {new QDoubleSpinBox};

    TestPointWidget* testpointWidget {new TestPointWidget};

private:
    void initUi();
    void initConnections();
    void initTestpointsGroup();
};

#endif // SUBTYPEWIDGET_H
