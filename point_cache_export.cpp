#include "asset/parsers/point_cache_export.hpp"

// CUI: #include <iostream>
#include <fstream>
#include <toolbox_config/tbx_assert.hpp>

#include "asset/parsers/endianess.hpp"

// =============================================================================
namespace asset {
// =============================================================================

// =============================================================================
namespace loader {
// =============================================================================

Point_cache_file::Point_cache_file(int nb_points, int nb_frame_hint)
{
    tbx_assert(nb_points > 0);
    if(nb_frame_hint > 0)
    {
        _nb_points = nb_points;
        _frames.reserve(nb_frame_hint);
//        for(int i = 0; i < nb_frame_hint; i++)
//            _frames[i].resize(nb_points);
    }
}

// -----------------------------------------------------------------------------

void Point_cache_file::add_frame(float* points, int offset, int stride)
{
    _frames.push_back(std::vector<float>());
    const int frame_idx = (int)_frames.size() - 1;
    _frames[frame_idx].resize(_nb_points*3);
    for(int i = offset, j = 0; i < (_nb_points + offset); i++, j++)
    {
        _frames[frame_idx][j*3  ] = points[i*(3+stride)  ];
        _frames[frame_idx][j*3+1] = points[i*(3+stride)+1];
        _frames[frame_idx][j*3+2] = points[i*(3+stride)+2];
    }
}

// -----------------------------------------------------------------------------

/*
MDD file format

The first thing to note is that the MDD file format is Motorola Big Endian byte
order as opposed to the Intel Little Endian standard.
So however you implement the structure below, you must come up with an algorithm
to flip the bytes during file IO.

The data structure is like so:
typedef Struct{
    int totalframes;
    int totalPoints;
    float *Times; //time for each frame
    float **points[3];
}mddstruct;


and the data is written like so:


totalframes
totalPoints
Times
while(!totalframes)
{
    while(!totalPoints)
    {
        write point[frame][point][axis];
        point++;
    }
    frame++;
}
*/
void Point_cache_file::export_mdd(const std::string& path_name)
{
    std::ofstream file(path_name.c_str(), std::ios::binary|std::ios::trunc);

    if(!file.is_open())
    {
        tbx_warning("ERROR: can't create/open %s", path_name.c_str());
        return;
    }

    int ibuff = endianess::big_long( (int)_frames.size() );
    file.write((char*)&ibuff, 4);
    ibuff = endianess::big_long( (int)(_nb_points)  );
    file.write((char*)&ibuff, 4);

    float fbuff[3] = {endianess::big_float(0.1f), 0.f, 0.f};
    for(unsigned f = 0; f < _frames.size(); f++)
        file.write((char*)fbuff, 4);

    for(unsigned f = 0; f < _frames.size(); f++)
    {
        for(int p = 0; p < _nb_points; p++)
        {
            fbuff[0] = endianess::big_float( _frames[f][p*3    ] );
            fbuff[1] = endianess::big_float( _frames[f][p*3 + 1] );
            fbuff[2] = endianess::big_float( _frames[f][p*3 + 2] );
            file.write((char*)fbuff, 4*3);
        }
    }
    file.close();
}

}// END loader =================================================================

} // END asset Namespace =======================================================
