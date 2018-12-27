#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile about("/etc/about.txt");
    if ( about.exists() ) {
        if ( about.open(QIODevice::ReadOnly | QIODevice::Text) ) {
            QTextStream aboutStream(&about);
            QString aboutString;
            aboutString.append(aboutStream.readAll());
            ui->about->setText(aboutString);
        } else {
            this->ui->about->setText("");
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moveEvent(QMoveEvent *)
{
    this->move( QPoint( 0, 0 ) );
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    exit(0);
}
