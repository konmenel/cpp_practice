#include "vtk.h"


int main() 
{
    float data[9] = {
        1.0f, 2.0f, 3.0f,
        10.0f, 2.0f, 3.0f,
        20.0f, 2.0f, 3.0f
    };

    // Legacy_VTK_IO vtk_io("test.vtk");
    // vtk_io.write_header();
    // vtk_io.write_data(reinterpret_cast<char*>(data), sizeof(data));
    // vtk_io.write_tail();

    Xml_VTK_OI vtk_io2("test.vtp");
    vtk_io2.write_header();
    vtk_io2.write_data(reinterpret_cast<char*>(data), sizeof(data));
    vtk_io2.write_tail();

    // std::string encoded_data = Xml_VTK_OI::base64_encoder(std::string(reinterpret_cast<char*>(data), sizeof(data)));
    std::string encoded_data = macaron::Base64::Encode(std::string(reinterpret_cast<char*>(data), sizeof(data)));
    std::string decoded_data;
    macaron::Base64::Decode(encoded_data, decoded_data);

    float *data_ = reinterpret_cast<float *>((char *)decoded_data.c_str());

    for (int i = 0; i < 9; ++i)
    {
        std::cout << data_[i] << std::endl;
    }

    return 0;
}
