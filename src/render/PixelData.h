//
// Created by Evan George on 12/17/19.
//

#ifndef RAYTRACERCPP_PIXELDATA_H
#define RAYTRACERCPP_PIXELDATA_H

#include <scene/CameraCapture.h>
#include "Pixel.h"

namespace raytracer {

	class PixelData {

	public:
		//constructor
		PixelData(int width, int height);

		//destructor
		~PixelData();

		//accessors
		int getWidth() const { return width; }
		int getHeight() const { return height; }
		const Pixel &getPixel(int x, int y) const { return pixels[x][y]; }

		//takes a CameraCapture and exposure factor and converts each rays luminance  RGB pixels
		friend PixelData getPixelData(CameraCapture &capture, double exposure);
	private:
		//2D array of pixels
		Pixel** pixels = nullptr;

		//width and height of the pixel array
		int width, height;
	};

	//creates a PixelData from a CameraCapture and automatically determines the exposure to use
	PixelData getAutoExposedPixelData(CameraCapture &capture);

	//writes the pixel data to a file in Portable Pixel Map (PPM) format
	bool writeToFile(const PixelData &pixelData, const std::string &path);

	//clamp the value between the min and max
	double clamp(double value, double min, double max);
}

#endif //RAYTRACERCPP_PIXELDATA_H