#ifndef SCHEMEPRESETWIDGET_H
#define SCHEMEPRESETWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QDebug>

#include "schemeModelDefine.h"
#include "src/modeldatawidget.h"


class SchemePresetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SchemePresetWidget(QWidget *parent = nullptr);
    void setModel(Preset& preset);
    QString name();
signals:

private://elements
    QLabel* lableName{new QLabel};
    QDoubleSpinBox* spinboxVolt{new QDoubleSpinBox};
    QDoubleSpinBox* spinboxCurr{new QDoubleSpinBox};
    ModelDataWidget* modelDataWidget{new ModelDataWidget};

private://members
    Preset m_preset{nullptr};

private://inits
    void initUi();
    void initSpinBox();
    void initConnections();
};

#endif // SCHEMEPRESETWIDGET_H
