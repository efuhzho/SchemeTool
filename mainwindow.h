#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/schemeDefine.h"
#include "src/schemetranslator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void receiveScheme(Scheme scheme);

private:
    Ui::MainWindow *ui;
    Scheme schemeObj;
    SchemeTranslator* st{new SchemeTranslator(this)} ;
};
#endif // MAINWINDOW_H
