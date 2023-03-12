#ifndef MODELDATAWIDGET_H
#define MODELDATAWIDGET_H

#define DEBUG

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <QSplitter>
#include <QToolBar>
#include <QPushButton>
#include <QListWidget>
#include <QButtonGroup>

#include "schemeDefine.h"

class ModelDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModelDataWidget(QWidget *parent = nullptr);
    void setModel(ModelData& modeldata);

signals:
    void sigModelUpdated();
    void sigLoopChecked(int index);
    void sigStateChecked(int loopIndex,int stateIndex);

private slots:
    void slotUpdateLoopsList();
    void slotUpdateStatesList(int loopIndex);
    void slotUpdateDataGrid(int loopIndex,int stateIndex);
    void slotAddLoop();
    void slotDeleteLoop();
    void slotAddState();
    void slotDeleteState();

private://inits
    void initUi();
    void initSpinBox();
    QGridLayout* createDataGrid();
    QSplitter* createOptionsWidget();
    void initConnections();

private://members
    ModelData* m_modelData {nullptr};
   // QVector<ModelDataValue>* m_loops {&m_modelData->loops};


    QString unitU = "%";
    QString unitI = "%";
    QString unitP = "%";
    QString unitQ = "%";


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

    QPushButton* btnAddLoop {new QPushButton(tr("Add loop"))};
    QPushButton* btnDeleteLoop {new QPushButton(tr("Delete loop"))};
    QPushButton* btnAddState {new QPushButton(tr("Add state"))};
    QPushButton* btnDeleteState {new QPushButton(tr("Delete state"))};

    QVBoxLayout* loopsLayout {new QVBoxLayout};
    QVBoxLayout* statesLayout{new QVBoxLayout};
    QButtonGroup* groupLoops {new QButtonGroup(this)};
    QButtonGroup* groupStates {new QButtonGroup(this)};
};

#endif // MODELDATAWIDGET_H
