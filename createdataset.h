#ifndef CREATEDATASET_H
#define CREATEDATASET_H
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/io/vtk_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <QMessageBox>

class createdataset
{
public:
    createdataset();
    virtual ~createdataset();
    void read_segdata();
    int Numberofpoints(char *orignal_data);
    void Get_pcdfile();
    void Greedy_pro();
    void open_dataset();

private:
    char* orignal_data;
};

#endif // CREATEDATASET_H
