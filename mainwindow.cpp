#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( st, &SchemeTranslator::sigReturnScheme, this, &MainWindow::receiveScheme );

    QString filePath = QFileDialog::getOpenFileName();
    qDebug()<<filePath;
    st->readFromJsonFile(filePath);

    QString savepath = QFileDialog::getSaveFileName( );
    st->writeToJsonFile( schemeObj, savepath );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveScheme(Scheme scheme)
{
    schemeObj=scheme;
}

