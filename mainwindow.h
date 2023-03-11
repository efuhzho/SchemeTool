#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QAction>
#include <QCoreApplication>
#include <QLabel>
#include <QStackedWidget>

#include "src/schemeDefine.h"
#include "src/schemeConvertor.h"
#include "src/schemetreewidget.h"
#include "src/schemeinfowidget.h"
#include "src/schemepresetwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sigFileChanged(QString filePath);
    void sigSchemeDataChanged();

private slots:
    void onFileChanged(QString filePath);

    //when received SchemeConvertor's signals
    void onReturnScheme(Scheme scheme);
    void onReturnJsonData(QJsonObject jsonObject);

    //when customer clicked buttons
    void onActionLoad();
    void onActionDump();
    void onActionNew();

    //when treewidget item selected
    void onTreeItemClicked(QTreeWidgetItem *item, int column);


private://members
    Ui::MainWindow *ui;

    Scheme m_scheme;
    //SchemeValue* m_schemeValue{&m_scheme.value};
    //Preset m_presetValue{m_schemeValue->preset};
    SchemeConvertor* m_schemeConvertor{new SchemeConvertor(this)} ;
    //QMap stackWidgetMap;

private://ui elements
    //actions
    QAction* m_actionNew {new QAction(tr("New Scheme"))};
    QAction* m_actionLoad{new QAction(tr("Load"))};
    QAction* m_actionDump {new QAction(tr("Dump"))};

    //strings
    QLabel* m_lableFilePath{new QLabel(tr("Haven't load any scheme file."))};

    //stackwidget
    QStackedWidget* m_stackWidget{new QStackedWidget};

    //customer widgets
    SchemeTreeWidget* m_schemeTree{new SchemeTreeWidget};
    SchemeInfoWidget* m_schemeInfoWidget{new SchemeInfoWidget(m_scheme.value)};
    SchemePresetWidget* m_presetWidget{new SchemePresetWidget(m_scheme.value.preset)};


private://inits
    void initWindow();
    void initToolbars();
    void initStatusBar();
    void initConnections();
    void initStackWidget();

};
#endif // MAINWINDOW_H
