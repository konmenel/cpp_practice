#include <iostream>
#include <fstream>
#include <vector>

void write_file_header(std::ofstream &out_file)
{
    out_file << "# vtk DataFile Version 2.0\n";
    out_file << "Test data\n";
    out_file << "BINARY\n";
    out_file << "DATASET POLYDATA\n";
    out_file << "POINTS 2 float\n";
}

template <typename T>
void SwapEnd(T& var)
{
  char* varArray = reinterpret_cast<char*>(&var);
  for(long i = 0; i < static_cast<long>(sizeof(var)/2); i++)
    std::swap(varArray[sizeof(var) - 1 - i],varArray[i]);
}


int main() 
{
    float data[6] = {1.0f, 2.0f, 0.0f,
                    2.0f, 2.0f, 0.0f};
    std::ofstream out_file("test.vtk", std::ios::out);
    
    write_file_header(out_file);
    for (int i=0; i<6; i++) {
        float r = data[i];
        SwapEnd(r);
        out_file.write(reinterpret_cast<char*>(&r), sizeof(float));
    }
    out_file << "\n";
    out_file.close();

    return 0;
}
