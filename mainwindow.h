#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType)
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkReverseSense.h>
#include <vtkDICOMImageReader.h>
#include <QMainWindow>
#include <QMessageBox>
#include <qdirmodel.h>
#include <QMouseEvent>
#include <QFileDialog>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkActor2D.h>
#include <QDebug>
#include <myvtkinteractorstyleimage.h>
#include <vtkTextRenderer.h>
#include <QTreeWidget>
#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void LoadDirs(QString path, QTreeWidget *treewidget, QTreeWidgetItem *item);
signals:
    void clicked();

private slots:
    void on_Reconstruction_clicked();

    void on_create_data_set_clicked();

    void on_pushButton_clicked();

    void mousePressEventSlot();

    void mouseWheelEventSlot();

    void Open_File();

protected:
    void mousePressEvent(QMouseEvent *e);
//    void wheelEvent(QWheelEvent *e);

private:
    Ui::MainWindow *ui;
    myVtkInteractorStyleImage * myVtkinterstyimage;
};

#endif // MAINWINDOW_H
