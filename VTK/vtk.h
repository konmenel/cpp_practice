#include <iostream>
#include <fstream>
#include <vector>

#include "Base64.h"


class VTK_OI 
{
public:
    VTK_OI(const std::string filename) : _out_file(std::ofstream(filename)) {};

    virtual ~VTK_OI() 
    {
        _out_file.close();
    };

    virtual void write_header() = 0;
    virtual void write_tail() = 0;
    virtual void write_data(char *data, size_t len) = 0;

protected:
    std::ofstream _out_file;
};


class Legacy_VTK_IO : public VTK_OI
{
public:
    Legacy_VTK_IO(const std::string filename) : VTK_OI(filename) {};

    virtual ~Legacy_VTK_IO() {}


    // VERY UNSAFE - DO NOT USE
    // TODO: RETURN COPY DO NOT SWAP INPLACE
    static void swap_endian(char *bytes, size_t bytes_len, size_t type_len)
    {
        for (size_t i = 0; i < bytes_len; i += type_len)
        {
            for (size_t j = 0; j < type_len / 2; ++j)
            {
                char tmp = bytes[i + j];
                bytes[i + j] = bytes[i + type_len - j - 1];
                bytes[i + type_len - j - 1] = tmp;
            }
        }
    }

    void write_header() override
    {
        _out_file << "# vtk DataFile Version 2.0\n";
        _out_file << "Test data\n";
        _out_file << "BINARY\n";
        _out_file << "DATASET POLYDATA\n";
        _out_file << "POINTS 2 float\n";
    }

    void write_tail() override {}

    void write_data(char *data, size_t len) override {
        swap_endian(data, len, sizeof(float));
        _out_file.write(data, len);
    }

};


class Xml_VTK_OI : public VTK_OI
{
public:
    Xml_VTK_OI(const std::string filename) : VTK_OI(filename) {}

    virtual ~Xml_VTK_OI() {}

    static std::string base64_encoder(const std::string &bytes) 
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

        std::string encoded_string(4 * ((bytes.size() + 2) / 3), '=');
        const size_t bytes_len = bytes.size();
        const size_t encoded_len = encoded_string.size();

        for (size_t i = 0, j = 0; i < (bytes_len - 2); i += 3, j += 4) {
            // Concate the three bytes into a single 24-bit integer
            uint32_t triplet = (bytes[i] << 16) | (bytes[i + 1] << 8) | bytes[i + 2]; 

            encoded_string[j] = ENCODING_TABLE[(triplet >> 18) & 0x3F];
            encoded_string[j + 1] = ENCODING_TABLE[(triplet >> 12) & 0x3F];
            encoded_string[j + 2] = ENCODING_TABLE[(triplet >> 6) & 0x3F];
            encoded_string[j + 3] = ENCODING_TABLE[triplet & 0x3F];
        }

        // Handle the last two bytes
        
        if (bytes_len % 3 == 1) {
            uint32_t triplet = bytes[bytes_len] << 16;
            encoded_string[encoded_len - 4] = ENCODING_TABLE[(triplet >> 18) & 0x3F];
            encoded_string[encoded_len - 3] = ENCODING_TABLE[(triplet >> 12) & 0x3F];
        } else if (bytes_len % 3 == 2) {
            uint32_t triplet = (bytes[bytes_len] << 16 | bytes[bytes_len + 1] << 8);
            encoded_string[encoded_len - 4] = ENCODING_TABLE[(triplet >> 18) & 0x3F];
            encoded_string[encoded_len - 3] = ENCODING_TABLE[(triplet >> 12) & 0x3F];
            encoded_string[encoded_len - 2] = ENCODING_TABLE[(triplet >> 6) & 0x3F];
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

    void write_data(char *data, size_t len) override {
        std::string bytes(data, len);
        std::string encoded_bytes = macaron::Base64::Encode(bytes);
        // std::string encoded_bytes = base64_encoder(bytes);
        _out_file << "   <Points>\n";
        _out_file << "    <DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"binary\">\n";
        _out_file << "    " << encoded_bytes << "\n";
        _out_file << "    </DataArray>\n";
        _out_file << "   </Points>\n";
    }
};
