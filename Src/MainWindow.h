/**
 * @file    MainWindow.h
 * @author  Amit Tomar
 * @version 1.0
 *
 * Class decleration for class MainWindow
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "OpenGlSurface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_Bernstein_clicked();
    void on_Casteljau_clicked();

    void on_ScaleBar_sliderMoved(int position);
    void on_RotateBarX_sliderMoved(int position);

    void on_RorateBarY_sliderMoved(int position);

    void on_RotateBarZ_sliderMoved(int position);

    void on_TranslateBarX_sliderMoved(int position);

    void on_TranslateBarY_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    OpenGlSurface *drawingSurface;
};

#endif // MAINWINDOW_H
