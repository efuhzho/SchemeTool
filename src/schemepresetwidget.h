#ifndef SCHEMEPRESETWIDGET_H
#define SCHEMEPRESETWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QLabel>

#include "src/schemeDefine.h"


class SchemePresetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SchemePresetWidget(Preset* presetValue,QWidget *parent = nullptr);
    void initData();
    QString name();
signals:

private://elements
    QLabel* lableName{new QLabel};
    QDoubleSpinBox* spinboxVolt{new QDoubleSpinBox};
    QDoubleSpinBox* spinboxCurr{new QDoubleSpinBox};

private://members
    Preset* m_presetValue{nullptr};

private://inits
    void initUi();
};

#endif // SCHEMEPRESETWIDGET_H
