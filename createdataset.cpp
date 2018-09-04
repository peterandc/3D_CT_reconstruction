#include "createdataset.h"
#include "stdio.h"
#include "iostream"
#include "stdlib.h"
#include "string"
#include "sstream"

createdataset::createdataset()
{
    char p[100] = "/home/peter/qt_vtk_pro/qt_pro/midfile/result.txt";
    this->orignal_data = p;
}

createdataset::~createdataset()
{

}

int createdataset::Numberofpoints(char* orignal_data)
{
    int numerofpoints = 0;
    int c = 0;
    FILE * fp = NULL;
    fp =fopen(orignal_data,"r");
    if(!fp)
    {
        std::cout<<"falue to read the file! ! !";
        exit(0);
    }
    while(!feof(fp))
    {
        c = fgetc(fp);
        if(c == '\n')
        {
            ++numerofpoints;
        }
    }
    return numerofpoints;
}

void createdataset::Get_pcdfile()
{
    int n = 0; //n用来计文件中点个数
    FILE *fp;
    fp = fopen(orignal_data,"r");
    n = Numberofpoints(orignal_data);      //使用numofPoints函数计算文件中点个数

    std::cout << "there are "<<n<<" points in the file..." <<std::endl;
        //新建一个点云文件，然后将结构中获取的xyz值传递到点云指针cloud中。
    pcl::PointCloud<pcl::PointXYZ> cloud;
    cloud.width    = n;
    cloud.height   = 1;
    cloud.is_dense = false;
    cloud.points.resize (cloud.width * cloud.height);

    double x=0,y=0,z=0;
    int i = 0;
    while(!feof(fp))
    {
        fscanf(fp,"%lf %lf %lf\n",&x,&y,&z);
        cloud.points[i].x = x;
        cloud.points[i].y = y;
        cloud.points[i].z = z;
        // std::cout<<" "<<x<<" "<<y<<" "<<z<<" "<<std::endl;
        i++;
    }
    fclose(fp);

  pcl::io::savePCDFileASCII ("/home/peter/qt_vtk_pro/qt_pro/midfile/dataset_pcd.pcd", cloud);
  std::cerr << "Saved " << cloud.points.size () << " data points to test_pcd.pcd." << std::endl;
}

void createdataset::Greedy_pro()
{
    // Load input file into a PointCloud<T> with an appropriate type
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PCLPointCloud2 cloud_blob;
    pcl::io::loadPCDFile ("/home/peter/qt_vtk_pro/qt_pro/midfile/dataset_pcd.pcd", cloud_blob);
    pcl::fromPCLPointCloud2 (cloud_blob, *cloud);
    //* the data should be available in cloud

    // Normal estimation*
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
    pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud (cloud);
    n.setInputCloud (cloud);
    n.setSearchMethod (tree);
    n.setKSearch (20);
    n.compute (*normals);
    //* normals should not contain the point normals + surface curvatures

    // Concatenate the XYZ and normal fields*
    pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals (new pcl::PointCloud<pcl::PointNormal>);
    pcl::concatenateFields (*cloud, *normals, *cloud_with_normals);
    //* cloud_with_normals = cloud + normals

    // Create search tree*
    pcl::search::KdTree<pcl::PointNormal>::Ptr tree2 (new pcl::search::KdTree<pcl::PointNormal>);
    tree2->setInputCloud (cloud_with_normals);

    // Initialize objects
    pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
    pcl::PolygonMesh triangles;

    // Set the maximum distance between connected points (maximum edge length)
    gp3.setSearchRadius (0.025);

    // Set typical values for the parameters
    gp3.setMu (2.5);
    gp3.setMaximumNearestNeighbors (100);
    gp3.setMaximumSurfaceAngle(M_PI/4); // 45 degrees
    gp3.setMinimumAngle(M_PI/18); // 10 degrees
    gp3.setMaximumAngle(2*M_PI/3); // 120 degrees
    gp3.setNormalConsistency(false);

    // Get result
    gp3.setInputCloud (cloud_with_normals);
    gp3.setSearchMethod (tree2);
    gp3.reconstruct (triangles);

    // Additional vertex information
    //std::vector<int> parts = gp3.getPartIDs();
    //std::vector<int> states = gp3.getPointStates();

    //save vtk file
    pcl::io::saveVTKFile("mymesh.vtk", triangles);
    QMessageBox::information(NULL, "information", "file is make up", QMessageBox::Yes, QMessageBox::Yes);


}

void createdataset::read_segdata()
{
    //write the points to the result.txt
    FILE*fp2 = NULL;
    fp2 = fopen("/home/peter/qt_vtk_pro/qt_pro/midfile/result.txt","w+");
    if(!fp2)
    {
        printf("falue to open file!!!\n");
        exit(0);
    }

    std::string slices= "/home/peter/Desktop/CloudPoints/T1Gd1txt/P_";
    std::string s;
    //get the first point of first segmentation txt file
    FILE * firstpoint = NULL;
    firstpoint = fopen("/home/peter/Desktop/CloudPoints/T1Gd1txt/P_1.txt","r");
    double fx,fy;//,fz;
    fscanf(firstpoint,"%lf %lf",&fx,&fy);
    //fz = 0.0018;
    fclose(firstpoint);
    int i=1;
    //get the x , y point of each of txt file and put them together to get the 3D point txt file
    for(int t_size=1;t_size<500;t_size++)
    {
    //get the file name
        std::stringstream ss;
        ss<<t_size;
        s = slices + ss.str() + ".txt";

    //open txt file
        FILE*fp = NULL;
        fp = fopen(s.c_str(),"r");
        if(!fp)
        {
            printf("falue to open file!!\n");
            break;
        }
    std::cout<<s<<std::endl;
    //we use those to read the each point of txt file.
        double x=0,y=0,z=0,useless1,useless2;
    //we use those to save the point we need.
        double firstx[100000],firsty[100000],firstz[100000];

        while(!feof(fp))
        {
            fscanf(fp," %lf %lf %lf %lf %lf",&x,&y,&z,&useless1,&useless2);
            firstx[i] = (x-fx)/1000.0;
            firsty[i] = (y-fy)/1000.0;
            firstz[i] = 0.0018*t_size;
            //printf("%lf %lf %lf %d\n",firstx[i],firsty[i],firstz[i],i);
            fprintf(fp2,"%lf %lf %lf\n",firstx[i],firsty[i],firstz[i]);
            i++;
            printf("%d\n",t_size);
        }
        fclose(fp);
    }
    fclose(fp2);
    //printf("%d\n",i);
}

void createdataset::open_dataset()
{

}
