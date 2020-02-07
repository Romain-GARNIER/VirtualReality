#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();    

private slots:
    void changeAmbientLight();
    void changeSpecularLight();
    void changeDiffuseLight();

    void changeXLight();
    void changeYLight();
    void changeZLight();

    void changeSpecCoeff(int);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
