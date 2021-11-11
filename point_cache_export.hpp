#ifndef ASSET_POINT_CACHE_EXPORT_HPP
#define ASSET_POINT_CACHE_EXPORT_HPP

#include <vector>
#include <string>

// =============================================================================
namespace asset {
// =============================================================================

// =============================================================================
namespace loader {
// =============================================================================

/**
 * @brief (.mdd loader) Handling export of mesh point frame by frame
 * Point cache frame files enables to save at each frame the position of every
 * vertices of a mesh. It's an easy way to export a whole animation as the
 * format is largely supported by other animation software. The file is
 * rapidely too large to fit in memory though...
 * Don't record hours of sequences!
*/
class Point_cache_file{
public:


    Point_cache_file(int nb_points, int nb_frame_hint = 0);

    /// Add a new frame given the list of points coordinates points.
    /// @param points array of points with x y z coordinates contigus
    /// @param offset The number of elements to ignore and begin to read the
    /// array 'points'
    /// @param stride number of elements to ignore between each points
    void add_frame(float* points, int offset=0, int stride=0);

    /// Write out a mdd file
    void export_mdd(const std::string& path_name);


    // TODO:
    //void export_pc2(const std::string& path_name);
    //void import_pc2(const std::string& path_name,
    //                const std::vector< std::vector<float> >& frames);


private:
    /// list of frame. Each frame stores the object vertex coordinates.
    /// X Y Z coordinates are contigus.
    /// _frames[num_frame][list_points]
    std::vector< std::vector<float> > _frames;

    /// Number of points the cached object is.
    int _nb_points;

};

}// END loader =================================================================

}// END asset NAMESPACE ========================================================

#endif // ASSET_POINT_CACHE_EXPORT_HPP
