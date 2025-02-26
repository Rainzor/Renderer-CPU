#ifndef COLOR_H
#define COLOR_H

#include "common.h"
#include "rtw_stb_image.h"
#include <iostream>
#include <vector>
#include <filesystem>
#include <string>

namespace fs = std::filesystem; // 使用命名空间简化代码


inline void write_color(std::ostream &out, color pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

inline void write_color(std::ostream& out, color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    if (r != r) r = 0.0;
    if (g != g) g = 0.0;
    if (b != b) b = 0.0;

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

inline int write_img(const char* path, int width ,int height,const std::vector<color>& img, int samples_per_pixel=1) {
    int num_channels = 3;
    char *data = new char[width * height * num_channels];
    int index = 0;
    for (int j = height - 1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            color pixel_color = img[j * width + i];
            auto r = pixel_color.x();
            auto g = pixel_color.y();
            auto b = pixel_color.z();

            if (r != r) r = 0.0;
            if (g != g) g = 0.0;
            if (b != b) b = 0.0;

            // Divide the color by the number of samples and gamma-correct for gamma=2.0.
            float scale = 1.0 / samples_per_pixel;
            r = sqrt(scale * r);
            g = sqrt(scale * g);
            b = sqrt(scale * b);

            // Write the translated [0,255] value of each color component.
            data[index++] = static_cast<int>(256 * clamp(r, 0.0, 0.999));
            data[index++] = static_cast<int>(256 * clamp(g, 0.0, 0.999));
            data[index++] = static_cast<int>(256 * clamp(b, 0.0, 0.999));
        }
    }

	std::string folder_path, file_name;
    folder_path = fs::path(path).parent_path().string();
    if (!fs::exists(folder_path)) {
        return fs::create_directories(folder_path);
    }

    if (stbi_write_png(path, width, height, num_channels, data, width * num_channels)) {
        std::cout << "Write to " << path << " successfully." << std::endl;
		return 0;
    }
    else {
        std::cerr << "Write to " << path << " failed." << std::endl;
		return -1;
    }

    delete [] data;
}

#endif