#include "mainwindow.h"
#include "Reconstrucion.h"
#include "createdataset.h"
#include "ui_mainwindow.h"
#include "statusmessage.h"
#include "myvtkinteractorstyleimage.h"
#include "vtkEventQtSlotConnect.h"
#include "QVTKInteractor.h"
vtkStandardNewMacro(myVtkInteractorStyleImage)


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

void MainWindow::LoadDirs(QString path, QTreeWidget *treewidget, QTreeWidgetItem *item)
{
    QDir dir(path);
    if (!dir.exists()) return;

    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();
    int size = list.size();

    for (int i = 0; i < size; i++) {
        QFileInfo info = list.at(i);
        if (info.fileName() == "." || info.fileName() == "..") continue;

        if (info.isDir()) {
            QTreeWidgetItem *fileItem = new QTreeWidgetItem(QStringList() << info.fileName(), 0);  //0表示目录
            if (treewidget == NULL) item->addChild(fileItem);
            else treewidget->addTopLevelItem(fileItem);
            LoadDirs(info.filePath(), NULL, fileItem);
        } else {
            QTreeWidgetItem *fileItem = new QTreeWidgetItem(QStringList() << info.fileName(), 1);   //1表示是文件
            if (treewidget == NULL) item->addChild(fileItem);
            else treewidget->addTopLevelItem(fileItem);
        }
    }
}

void MainWindow::on_Reconstruction_clicked()
{
    /*
    vtkSmartPointer<vtkDICOMImageReader> reader =
              vtkSmartPointer<vtkDICOMImageReader>::New();
    reader->SetFileName("/home/peter/CT-MONO2-16-brain");
    reader->Update();

    vtkSmartPointer<vtkImageViewer2> viewer=
            vtkSmartPointer<vtkImageViewer2>::New();
    viewer->SetInputConnection(reader->GetOutputPort());

    viewer->SetRenderWindow(ui->qvtkWidget->GetRenderWindow());
    viewer->Render();
    */

    /*
    vtkSmartPointer<vtkPolyDataReader> vpd_reader =
            vtkSmartPointer<vtkPolyDataReader>::New();
    vpd_reader->SetFileName("/home/peter/test111/build/result.vtk");
    vpd_reader->Update();

    vtkSmartPointer<vtkCleanPolyData> Cleanpolydata =
            vtkSmartPointer<vtkCleanPolyData>::New();
    Cleanpolydata->SetInputConnection(vpd_reader->GetOutputPort());
    Cleanpolydata->SetTolerance(0.0001);
    Cleanpolydata->Update();

    vtkSmartPointer<vtkSurfaceReconstructionFilter> surf =
            vtkSmartPointer<vtkSurfaceReconstructionFilter>::New();
    surf->SetInputData(Cleanpolydata->GetOutput());
    surf->SetNeighborhoodSize(40);
    surf->SetSampleSpacing(0.005);
    surf->Update();

    vtkSmartPointer<vtkMarchingContourFilter> contour =
            vtkSmartPointer<vtkMarchingContourFilter>::New();
    contour->SetInputConnection(surf->GetOutputPort());
    contour->SetValue(0,0.001);
    contour->Update();

    vtkSmartPointer<vtkReverseSense> reverse =
    vtkSmartPointer<vtkReverseSense>::New();
    reverse->SetInputConnection(contour->GetOutputPort());
    reverse->ReverseCellsOn();
    reverse->ReverseNormalsOn();

    vtkSmartPointer<vtkPolyDataMapper> reconstru_mapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    reconstru_mapper->SetInputConnection(reverse->GetOutputPort());

    vtkSmartPointer<vtkActor> reconstru_actor =
            vtkSmartPointer<vtkActor>::New();
    reconstru_actor->SetMapper(reconstru_mapper);

    vtkSmartPointer<vtkRenderer> reconstru_renderer =
            vtkSmartPointer<vtkRenderer>::New();
    reconstru_renderer->AddActor(reconstru_actor);
    reconstru_renderer->SetBackground(0,0,0);

    reconstru_renderer->GetActiveCamera()->SetPosition(0, -1, 0);
    reconstru_renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
    reconstru_renderer->GetActiveCamera()->SetViewUp(0,0,1);
    reconstru_renderer->GetActiveCamera()->Azimuth(30);
    reconstru_renderer->GetActiveCamera()->Elevation(30);
    reconstru_renderer->ResetCamera();


*/
    Reconstruciton * recong = new Reconstruciton();
    recong->start_reconstru();
    //ui->recons_show->hide();
    ui->recons_show->GetRenderWindow()->AddRenderer(recong->getvtkrenderer());
    ui->recons_show->GetRenderWindow()->Render();
    connect(ui->recons_show,SIGNAL(clicked()),this,SLOT(mousePressEventSlot()));

    //ui->qvtkWidget->SetRenderWindow(rw);
}

void MainWindow::on_create_data_set_clicked()
{
    createdataset * dataset = new createdataset();
    dataset->read_segdata();
    dataset->Get_pcdfile();
    dataset->Greedy_pro();
}

void MainWindow::on_pushButton_clicked()
{
    //QMessageBox::information(NULL, "information", "file is make up", QMessageBox::Yes, QMessageBox::Yes);
    //QDirModel *model = new QDirModel();
    //ui->treeWidget->setModel(model);
    //ui->treeWidget->setRootIndex(model->index("/home/peter/Desktop/CloudPoints"));
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();
    if(x>120 && x<(120+512) && y>60 && y<(60+512))
        emit clicked();
}
/*
void MainWindow::wheelEvent(QWheelEvent *e)
{
    if(e->delta() > 0){
        std::cout << "wheel up" << std::endl;
    }else{
        std::cout << "wheel down" << std::endl;
        //myVtkinterstyimage-> OnMouseWheelBackward();
    }
}
*/
void MainWindow::mousePressEventSlot()
{
    QMessageBox::about(this,"qq","qqq");
}

void MainWindow::mouseWheelEventSlot()
{

}

void MainWindow::Open_File()
{
    QString path;
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("Open Directory"));
    fileDialog->setDirectory(".");
    //fileDialog->setFilter(tr("Directory Files(*.)"));
    fileDialog->setFileMode(QFileDialog::Directory);
    fileDialog->setOptions(QFileDialog::ShowDirsOnly);
    if(fileDialog->exec() == QDialog::Accepted) {
            path = fileDialog->selectedFiles()[0];
            QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
    } else {
            QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }

    LoadDirs(path,ui->treeWidget,NULL);


    //read the dicom files
    vtkDICOMImageReader * reader = vtkDICOMImageReader::New();
    QByteArray ba = path.toLatin1();
    char *mm = ba.data();
    qDebug()<<mm<<endl;
    reader->SetDirectoryName(mm);
    reader->Update();

    //visualize
    vtkImageViewer2 * imageViewer = vtkImageViewer2::New();
    imageViewer->SetInputConnection(reader->GetOutputPort());

    //slices status message
    vtkTextProperty * sliceTextProp = vtkTextProperty::New();
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(20);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkTextMapper * sliceTextMapper = vtkTextMapper::New();


    QString msg = StatusMessage::Format(imageViewer->GetSliceMin(),imageViewer->GetSliceMax());
    QByteArray ba1 = msg.toLatin1();
    char * textinput = ba1.data();
    sliceTextMapper->SetInput(textinput);
    sliceTextMapper->SetTextProperty(sliceTextProp);

    vtkSmartPointer<vtkActor2D> sliceTextActor = vtkSmartPointer<vtkActor2D>::New();
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    // usage hint message
    vtkSmartPointer<vtkTextProperty> usageTextProp = vtkSmartPointer<vtkTextProperty>::New();
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(14);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkSmartPointer<vtkTextMapper> usageTextMapper = vtkSmartPointer<vtkTextMapper>::New();
    usageTextMapper->SetInput("- Slice with mouse wheel\n  or Up/Down-Key\n- Zoom with pressed right\n  mouse button while dragging");
    usageTextMapper->SetTextProperty(usageTextProp);

    vtkSmartPointer<vtkActor2D> usageTextActor = vtkSmartPointer<vtkActor2D>::New();
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue( 0.05, 0.95);

    vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle =
       vtkSmartPointer<myVtkInteractorStyleImage>::New();

    // make imageviewer2 and sliceTextMapper visible to our interactorstyle
    // to enable slice status message updates when scrolling through the slices
    myInteractorStyle->SetImageViewer(imageViewer);
    myInteractorStyle->SetStatusMapper(sliceTextMapper);

    imageViewer->SetupInteractor(ui->show_dicom->GetRenderWindow()->GetInteractor());

    ui->show_dicom->SetRenderWindow(imageViewer->GetRenderWindow());
    // make the interactor use our own interactorstyle
    // cause SetupInteractor() is defining it's own default interatorstyle
    // this must be called after SetupInteractor()
    //renderWindowInteractor->SetInteractorStyle(myInteractorStyle);
    ui->show_dicom->GetInteractor()->SetInteractorStyle(myInteractorStyle);
    ui->show_dicom->GetInteractor()->Initialize();
    // add slice status message and usage hint message to the renderer
    imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
    imageViewer->GetRenderer()->AddActor2D(usageTextActor);

    // initialize rendering and interaction
    //imageViewer->GetRenderWindow()->SetSize(400, 300);
    //imageViewer->GetRenderer()->SetBackground(0.2, 0.3, 0.4);
    ui->show_dicom->GetRenderWindow()->GetInteractor()->Start();
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->SetRenderWindow(ui->show_dicom->GetRenderWindow());
    //ui->recons_show->GetRenderWindow()->AddRenderer(imageViewer->GetRenderer());
    //ui->recons_show->GetRenderWindow()->Render();
    imageViewer->Render();

 //   imageViewer->Render();


}
