#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QLayout>
#include <QLabel>
#include <QJsonObject>
#include <QByteArray>

#include "schememodeldefine.h"

class StateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StateWidget(QWidget *parent = nullptr);
    void  setModel(State &state);
    void setUnit(const QString unit);
    void clear();
    QString unit();
    State* Model();

signals:
    void sigModelUpdated();

private slots:
    void onModelUpdated();

private ://inits
    void initUI();
    QGridLayout* createDataGrid();
    void initSpinBox();
    void clearSpinBox();
    void initConnects();    

private://members
    State* m_stateModel;
    QString m_unit {" %"} ;

private://elements

    //电压
    QDoubleSpinBox* boxUa = new QDoubleSpinBox;
    QDoubleSpinBox* boxUb = new QDoubleSpinBox;
    QDoubleSpinBox* boxUc = new QDoubleSpinBox;
    QDoubleSpinBox* boxUx = new QDoubleSpinBox;
    //电流
    QDoubleSpinBox* boxIa = new QDoubleSpinBox;
    QDoubleSpinBox* boxIb = new QDoubleSpinBox;
    QDoubleSpinBox* boxIc = new QDoubleSpinBox;
    QDoubleSpinBox* boxIx = new QDoubleSpinBox;
    //电压相位
    QDoubleSpinBox* boxPhUa = new QDoubleSpinBox;
    QDoubleSpinBox* boxPhUb = new QDoubleSpinBox;
    QDoubleSpinBox* boxPhUc = new QDoubleSpinBox;
    QDoubleSpinBox* boxPhUx = new QDoubleSpinBox;
    //电流相位
    QDoubleSpinBox* boxPhIa = new QDoubleSpinBox;
    QDoubleSpinBox* boxPhIb = new QDoubleSpinBox;
    QDoubleSpinBox* boxPhIc = new QDoubleSpinBox;
    QDoubleSpinBox* boxPhIx = new QDoubleSpinBox;
    //有功功率
    QDoubleSpinBox* boxPa = new QDoubleSpinBox;
    QDoubleSpinBox* boxPb = new QDoubleSpinBox;
    QDoubleSpinBox* boxPc = new QDoubleSpinBox;
    QDoubleSpinBox* boxPx = new QDoubleSpinBox;
    QDoubleSpinBox* boxPsum = new QDoubleSpinBox;
    //无功功率
    QDoubleSpinBox* boxQa = new QDoubleSpinBox;
    QDoubleSpinBox* boxQb = new QDoubleSpinBox;
    QDoubleSpinBox* boxQc = new QDoubleSpinBox;
    QDoubleSpinBox* boxQx = new QDoubleSpinBox;
    QDoubleSpinBox* boxQsum = new QDoubleSpinBox;
    //功率因数
    QDoubleSpinBox* boxPFa = new QDoubleSpinBox;
    QDoubleSpinBox* boxPFb = new QDoubleSpinBox;
    QDoubleSpinBox* boxPFc = new QDoubleSpinBox;
    QDoubleSpinBox* boxPFx = new QDoubleSpinBox;
    QDoubleSpinBox* boxPFsum = new QDoubleSpinBox;
    //频率
    QDoubleSpinBox* boxFa = new QDoubleSpinBox;
    QDoubleSpinBox* boxFb = new QDoubleSpinBox;
    QDoubleSpinBox* boxFc = new QDoubleSpinBox;
    QDoubleSpinBox* boxFx = new QDoubleSpinBox;

};

#endif // STATEWIDGET_H
