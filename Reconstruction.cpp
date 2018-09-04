#include "Reconstrucion.h"
//#include "ui_mainwindow.h"

void Reconstruciton::start_reconstru()
{
    vpd_reader = vtkPolyDataReader::New();
    vpd_reader->SetFileName("mymesh.vtk");
    vpd_reader->Update();

    Cleanpolydata = vtkCleanPolyData::New();
    Cleanpolydata->SetInputConnection(vpd_reader->GetOutputPort());
    Cleanpolydata->SetTolerance(0.0001);
    Cleanpolydata->Update();

    surf = vtkSurfaceReconstructionFilter::New();
    surf->SetInputData(Cleanpolydata->GetOutput());
    surf->SetNeighborhoodSize(40);
    surf->SetSampleSpacing(0.005);
    surf->Update();

    contour = vtkMarchingContourFilter::New();
    contour->SetInputConnection(surf->GetOutputPort());
    contour->SetValue(0,0.001);
    contour->Update();

    reverse = vtkReverseSense::New();
    reverse->SetInputConnection(contour->GetOutputPort());
    reverse->ReverseCellsOn();
    reverse->ReverseNormalsOn();

    reconstru_mapper = vtkPolyDataMapper::New();
    reconstru_mapper->SetInputConnection(reverse->GetOutputPort());

    reconstru_actor = vtkActor::New();
    reconstru_actor->SetMapper(reconstru_mapper);

    reconstru_renderer = vtkRenderer::New();
    reconstru_renderer->AddActor(reconstru_actor);
    reconstru_renderer->SetBackground(0,0,0);

    reconstru_renderer->GetActiveCamera()->SetPosition(0, -1, 0);
    reconstru_renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
    reconstru_renderer->GetActiveCamera()->SetViewUp(0,0,1);
    reconstru_renderer->GetActiveCamera()->Azimuth(30);
    reconstru_renderer->GetActiveCamera()->Elevation(30);
    reconstru_renderer->ResetCamera();
}

void Reconstruciton::show_reconstru()
{
}

vtkRenderer * Reconstruciton::getvtkrenderer()
{
    return this->reconstru_renderer;
}

