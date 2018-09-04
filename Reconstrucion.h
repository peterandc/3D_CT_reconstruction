#ifndef RECONSTRUCION_H
#define RECONSTRUCION_H

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkCleanPolyData.h>
#include <vtkSurfaceReconstructionFilter.h>
#include <vtkMarchingContourFilter.h>
#include <vtkPolyDataReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkReverseSense.h>


namespace Ui {
class Reconstrucion;
}

class Reconstruciton
{
public:
    Reconstruciton() {}
    virtual ~Reconstruciton() {}

    void start_reconstru();
    void show_reconstru();
    vtkRenderer * getvtkrenderer();

private:
    vtkPolyDataReader * vpd_reader;
    vtkCleanPolyData * Cleanpolydata;
    vtkSurfaceReconstructionFilter * surf;
    vtkMarchingContourFilter * contour;
    vtkReverseSense * reverse;
    vtkActor * reconstru_actor;
    vtkPolyDataMapper * reconstru_mapper;
    vtkRenderer * reconstru_renderer;

};
#endif // RECONSTRUCION_H
