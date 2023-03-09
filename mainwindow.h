#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QAction>
#include <QCoreApplication>
#include <QLabel>

#include "src/schemeDefine.h"
#include "src/schemeConvertor.h"
#include "src/schemetreewidget.h"

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
    SchemeValue* m_schemeValue{&m_scheme.value};
    SchemeConvertor* m_schemeConvertor{new SchemeConvertor(this)} ;
    SchemeTreeWidget* m_schemeTree{new SchemeTreeWidget};


private://ui elements
    QAction* m_actionNew {new QAction(tr("New Scheme"))};
    QAction* m_actionLoad{new QAction(tr("Load"))};
    QAction* m_actionDump {new QAction(tr("Dump"))};
    QLabel* m_lableFilePath{new QLabel(tr("Haven't load any scheme file."))};
    QLineEdit* test{new QLineEdit};

private://inits
    void initWindow();
    void createToolbars();
    void createStatusBar();
    void initConnections();

};
#endif // MAINWINDOW_H
