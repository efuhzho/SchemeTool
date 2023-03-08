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
    void sigFileUpdated(QString filePath);

private slots:
    void onFileUpdated(QString filePath);

    void onReturnScheme(Scheme scheme);
    void onReturnJsonData(QByteArray jsonData);
    void onActionLoad();
    void onActionDump();
    void onActionNew();

    //members
private:
    Ui::MainWindow *ui;

    Scheme m_scheme;
    SchemeConvertor* m_schemeConvertor{new SchemeConvertor(this)} ;
    SchemeTreeWidget* m_schemeTree{new SchemeTreeWidget};

    //ui elements
private:
    QAction* m_actionNew {new QAction(tr("New Scheme"))};
    QAction* m_actionLoad{new QAction(tr("Load"))};
    QAction* m_actionDump {new QAction(tr("Dump"))};
    QLabel* m_lableFilePath{new QLabel(tr("Haven't load any scheme file."))};

    //inits
private:
    void initWindow();
    void createToolbars();
    void createStatusBar();
    void initConnections();

};
#endif // MAINWINDOW_H
