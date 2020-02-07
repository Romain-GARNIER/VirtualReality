#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::changeAmbientLight()
{
    RVLight* lumiere = ui->widgetRV->light();
    QColor col = QColorDialog::getColor(lumiere->ambient(),this);
    if(col.isValid()){
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->ambientButton->setStyleSheet(qss);
        lumiere->setAmbient(col);
    }
}

void MainWindow::changeSpecularLight()
{
    RVLight* lumiere = ui->widgetRV->light();
    QColor col = QColorDialog::getColor(lumiere->specular(),this);
    if(col.isValid()){
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->specularButton->setStyleSheet(qss);
        lumiere->setSpecular(col);
    }
}

void MainWindow::changeDiffuseLight()
{
    RVLight* lumiere = ui->widgetRV->light();
    QColor col = QColorDialog::getColor(lumiere->diffuse(),this);
    if(col.isValid()){
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->diffuseButton->setStyleSheet(qss);
        lumiere->setDiffuse(col);
    }
}

void MainWindow::changeXLight()
{
    RVLight* lumiere = ui->widgetRV->light();
    QVector3D oldPos = lumiere->position();
    lumiere->setPosition(QVector3D(ui->xLight->value(),oldPos.y(),oldPos.z()));
}

void MainWindow::changeYLight()
{
    RVLight* lumiere = ui->widgetRV->light();
    QVector3D oldPos = lumiere->position();
    lumiere->setPosition(QVector3D(oldPos.x(),ui->yLight->value(),oldPos.z()));
}

void MainWindow::changeZLight()
{
    RVLight* lumiere = ui->widgetRV->light();
    QVector3D oldPos = lumiere->position();
    lumiere->setPosition(QVector3D(oldPos.x(),oldPos.y(),ui->zLight->value()));
}

void MainWindow::changeSpecCoeff(int newCoeff)
{
    ui->widgetRV->setSpecCoeff(newCoeff * 1.0f);
}
