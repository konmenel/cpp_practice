#include "vtk.h"
#include "mytimer.h"


int main() 
{
    float points[9] = {
        1.0f, 2.0f, 3.0f,
        10.0f, 2.0f, 3.0f,
        20.0f, 2.0f, 3.0f
    };

    float vel[9] = {
        1.0f, 2.0f, 3.0f,
        10.0f, 2.0f, 3.0f,
        20.0f, 2.0f, 3.0f
    };

    {
        Timer timer("vtk write");
        LegacyVTKIO vtk_io("test.vtk");
        vtk_io.write_header();
        vtk_io.write_data(reinterpret_cast<const char*>(points), sizeof(points), sizeof(float));
    
        vtk_io.write_tail();
    }

    // XmlVTKOI vtk_io2("test.vtp");
    // vtk_io2.write_header();
    // const char *bytes_data = reinterpret_cast<const char*>(data);
    // vtk_io2.write_data(bytes_data, sizeof(data));
    // vtk_io2.write_tail();

    double x = 123.456789;
    float y = static_cast<float>(x);

    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "sizeof(y): " << sizeof(y) << std::endl;

    return 0;
}
