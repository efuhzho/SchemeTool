﻿#ifndef MODELDATAWIDGET_H
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
#include <QTabWidget>

#include "schemeModelDefine.h"
#include "statewidget.h"

class ModelDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModelDataWidget(QWidget *parent = nullptr);
    void setModel(ModelData& model);
    ModelData* Model();

    void setUnit(const QString unit);
    QString unit();

signals:
    void sigModelUpdated();

private slots:
    void updateLoopsListWidget();
    void updateStatesListWidget(QListWidgetItem *item);
    void updateStateWidget(QListWidgetItem *item);

private://inits
    void initUi();
    void initConnections();

private://members
    ModelData* m_model ;
    QString m_unit;
    StateWidget* m_stateWidget {new StateWidget};

private://elements

    QListWidget* loopsListWidget{new QListWidget};
    QListWidget* statesListWidget{new QListWidget};

    QPushButton* btnAddLoop {new QPushButton};
    QPushButton* btnDeleteLoop {new QPushButton};
    QPushButton* btnAddState {new QPushButton};
    QPushButton* btnDeleteState {new QPushButton};
};

#endif // MODELDATAWIDGET_H
