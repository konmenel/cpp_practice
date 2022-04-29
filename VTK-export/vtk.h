#include <iostream>
#include <fstream>
#include <vector>

#include "Base64.h"


enum class endianness
{
    little = 0,
    big = 1,
};

inline endianness get_system_endianness()
{
    const int value { 0x01 };
    const void *address = static_cast<const void *>(&value);
    const unsigned char *least_significant_address = static_cast<const unsigned char *>(address);
    return (*least_significant_address == 0x01) ? endianness::little : endianness::big;
}

class VTKOI 
{
public:
    VTKOI(const std::string filename) : _out_file(std::ofstream(filename, std::ios::binary | std::ios::out)) {};

    virtual ~VTKOI() 
    {
        _out_file.close();
    };

    virtual void write_header() = 0;
    virtual void write_tail() = 0;
    virtual void write_data(const char *data, const size_t total_num_bytes, const size_t data_type_size) = 0;

protected:
    std::ofstream _out_file;
};


class LegacyVTKIO : public VTKOI
{
public:
    LegacyVTKIO(const std::string filename) : VTKOI(filename)
    {
        _system_endianness = get_system_endianness();
    }

    virtual ~LegacyVTKIO() {}

    void write_header() override
    {
        _out_file << "# vtk DataFile Version 2.0\n";
        _out_file << "Test data\n";
        _out_file << "BINARY\n";
        _out_file << "DATASET POLYDATA\n";
        _out_file << "POINTS 3 float\n";
    }

    void write_tail() override {}

    void write_data(const char *data, const size_t total_num_bytes, const size_t data_type_size) override {
        if (_system_endianness == endianness::little) {
            for (int i = 0; i < total_num_bytes; i += data_type_size) {
                for (int j = data_type_size-1; j >=0; j--) {
                    _out_file.write((data+i+j), 1);
                }
            }
        } else {
            _out_file.write(data, total_num_bytes);
        }
        _out_file << "\n";
    }

protected:
    endianness _system_endianness;
    friend LegacyVTKIO& operator<<(LegacyVTKIO& vtk_io, std::string str);
};


LegacyVTKIO& operator<<(LegacyVTKIO& vtk_io, std::string str)
{
    vtk_io._out_file << str;
    return vtk_io;
}


class XmlVTKOI : public VTKOI
{
public:
    XmlVTKOI(const std::string filename) : VTKOI(filename) {}

    virtual ~XmlVTKOI() {}

    static std::string base64_encoder(const unsigned char bytes[], const size_t bytes_len) 
    {
        static constexpr char ENCODING_TABLE[] = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
            'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
            'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
            'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
            'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
            'w', 'x', 'y', 'z', '0', '1', '2', '3',
            '4', '5', '6', '7', '8', '9', '+', '/'
        };

        const size_t encoded_len = (bytes_len + 2) / 3 * 4;
        std::string encoded_string(encoded_len, '\0');

        for (size_t i = 0, j = 0; i < (bytes_len - 2); i += 3, j += 4) {
            // Concate the three bytes into a single 24-bit integer
            const uint32_t triplet = (bytes[i] << 16) |
                                     (bytes[i+1] << 8) |
                                     bytes[i+2]; 

            encoded_string[j] = ENCODING_TABLE[(triplet >> 18) & 0b11'1111];
            encoded_string[j+1] = ENCODING_TABLE[(triplet >> 12) & 0b11'1111];
            encoded_string[j+2] = ENCODING_TABLE[(triplet >> 6) & 0b11'1111];
            encoded_string[j+3] = ENCODING_TABLE[triplet & 0b11'1111];
        }

        // Handle the last two bytes
        
        if (bytes_len % 3 == 1) {
            const uint32_t triplet = bytes[bytes_len] << 16;
            encoded_string[encoded_len - 4] = ENCODING_TABLE[(triplet >> 18) & 0b11'1111];
            encoded_string[encoded_len - 3] = ENCODING_TABLE[(triplet >> 12) & 0b11'1111];
            encoded_string[encoded_len - 2] = '=';
            encoded_string[encoded_len - 1] = '=';
        } else if (bytes_len % 3 == 2) {
            const uint32_t triplet = (bytes[bytes_len] << 16) |
                                     (bytes[bytes_len + 1] << 8);
            encoded_string[encoded_len - 4] = ENCODING_TABLE[(triplet >> 18) & 0b11'1111];
            encoded_string[encoded_len - 3] = ENCODING_TABLE[(triplet >> 12) & 0b11'1111];
            encoded_string[encoded_len - 2] = ENCODING_TABLE[(triplet >> 6) & 0b11'1111];
            encoded_string[encoded_len - 1] = '=';
        }

        return encoded_string;
    }

    void write_header() override
    {
        _out_file << "<?xml version=\"1.0\"?>\n";
        _out_file << "<VTKFile type=\"PolyData\" version=\"0.1\" byte_order=\"LittleEndian\">\n";
        _out_file << " <PolyData>\n";
        _out_file << "  <Piece NumberOfPoints=\"3\">\n";
    }

    void write_tail() override
    {
        _out_file << "  </Piece>\n";
        _out_file << " </PolyData>\n";
        _out_file << "</VTKFile>\n";
    }

    void write_data(const char *data, const size_t total_num_bytes, const size_t data_type_size = 0) override {
        // std::string encoded_bytes = macaron::Base64::Encode(bytes);
        std::string encoded_bytes = base64_encoder(reinterpret_cast<const unsigned char *>(data), total_num_bytes);
        _out_file << "   <Points>\n";
        _out_file << "    <DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"binary\">\n";
        _out_file << "    " << encoded_bytes << "\n";
        _out_file << "    </DataArray>\n";
        _out_file << "   </Points>\n";
    }
};
