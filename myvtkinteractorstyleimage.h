#ifndef MYVTKINTERACTORSTYLEIMAGE_H
#define MYVTKINTERACTORSTYLEIMAGE_H
#include <vtkInteractorStyleImage.h>
#include <vtkImageViewer2.h>
#include <vtkTextMapper.h>
#include <vtkRenderWindowInteractor.h>

class myVtkInteractorStyleImage : public vtkInteractorStyleImage
{
public:
    static myVtkInteractorStyleImage * New();
    vtkTypeMacro(myVtkInteractorStyleImage,vtkInteractorStyleImage)
    void SetImageViewer(vtkImageViewer2* imageViewer);
    void SetStatusMapper(vtkTextMapper* statusMapper);

protected:
   vtkImageViewer2* _ImageViewer;
   vtkTextMapper* _StatusMapper;
   int _Slice;
   int _MinSlice;
   int _MaxSlice;

public:
    void MoveSliceForward();
    void MoveSliceBackward();
    virtual void OnKeyDown();
    virtual void OnMouseWheelForward();
    virtual void OnMouseWheelBackward();
};

#endif // MYVTKINTERACTORSTYLEIMAGE_H
