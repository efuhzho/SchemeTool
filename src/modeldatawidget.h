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

#include "schemeModelDefine.h"
#include "statewidget.h"

class ModelDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModelDataWidget(QWidget *parent = nullptr);
    void setModel(ModelData& modeldata);

signals:
    void sigModelUpdated();
    void sigLoopChecked(Loop& loop);
    void sigStateChecked(State& state);

private slots:
    void onModelUpdated();
    void onLoopChecked(Loop& loop);
    void onStateChecked(State& state);
    void slotAddLoop();
    void slotDeleteLoop();
    void slotAddState();
    void slotDeleteState();

private://inits
    void initUi();
    QSplitter* createOptionsWidget();
    void initConnections();
    //void selectLastChild(QButtonGroup& group);



private://members
    ModelData m_modelData ;    

private://elements   

    QPushButton* btnAddLoop {new QPushButton(tr("Add loop"))};
    QPushButton* btnDeleteLoop {new QPushButton(tr("Delete loop"))};
    QPushButton* btnAddState {new QPushButton(tr("Add state"))};
    QPushButton* btnDeleteState {new QPushButton(tr("Delete state"))};

    QVBoxLayout* loopsLayout {new QVBoxLayout};
    QVBoxLayout* statesLayout{new QVBoxLayout};
    QButtonGroup* groupLoops {new QButtonGroup(this)};
    QButtonGroup* groupStates {new QButtonGroup(this)};

    StateWidget* m_stateWidget {new StateWidget};
};

#endif // MODELDATAWIDGET_H
