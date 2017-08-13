#pragma once

#include "imaging/bitmap.h"
#include <string>
#include <ostream>
#include <fstream>
#include <vector>

namespace imaging
{
    /// <summary>
    /// Class used to write WIF files.
    /// </summary>
    class WIF
    {
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="path">Path of WIF file</param>
        WIF(const std::string& path);

        /// <summary>
        /// Destructor.
        /// </summary>
        ~WIF();

        /// <summary>
        /// Writes a new frame to file.
        /// </summary>
        void write_frame(const Bitmap& bitmap);

    private:
        std::ofstream out;
        unsigned m_frame_index;
    };

    namespace wif
    {
        void convert_frame(std::vector<uint8_t>& buffer, const Bitmap& bitmap);
        void mark_eof(std::vector<uint8_t>& buffer);
    }
}