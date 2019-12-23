//
// Created by Evan George on 12/17/19.
//

#include <fstream>
#include <iostream>
#include "PixelData.h"

namespace raytracer {

	//constructor
	PixelData::PixelData(int width, int height) : width(width), height(height) {
		//initialize 2D array
		pixels = new Pixel*[width];

		for(int x = 0; x < width; ++x)
			pixels[x] = new Pixel[height];
	}

	//destructor
	PixelData::~PixelData() {
		//memory cleanup
		for(int x = 0; x < width; ++x)
			delete[] pixels[x];

		delete[] pixels;
		pixels = nullptr;
	}

	//takes a CameraCapture and exposure factor and converts each rays luminance  RGB pixels
	PixelData getPixelData(CameraCapture &capture, double exposure) {
		//create the PixelData object with the same dimensions of the camera capture
		PixelData data(capture.getWidth(), capture.getHeight());

		for(int x = 0; x < capture.getWidth(); ++x) {
			for(int y = 0; y < capture.getHeight(); ++y) {
				//expose and clamp each channel of the luminance and create the corresponding RGB pixel

				double r = 255 * clamp(exposure * capture.luminanceAt(x, y).getR(), 0, 1);
				double g = 255 * clamp(exposure * capture.luminanceAt(x, y).getG(), 0, 1);
				double b = 255 * clamp(exposure * capture.luminanceAt(x, y).getB(), 0, 1);

				data.pixels[x][y] = Pixel(r, g, b);
			}
		}

		return data;
	}

	//creates a PixelData from a CameraCapture and automatically determines the exposure to use
	PixelData getAutoExposedPixelData(CameraCapture &capture) {

		double max_color_channel = 0;

		//iterate over every pixel and find the maximum value for red, green, or blue in any of the pixels
		for(int x = 0; x < capture.getWidth(); ++x) {
			for(int y = 0; y < capture.getHeight(); ++y) {
				max_color_channel = std::max(max_color_channel, capture.luminanceAt(x, y).getR());
				max_color_channel = std::max(max_color_channel, capture.luminanceAt(x, y).getG());
				max_color_channel = std::max(max_color_channel, capture.luminanceAt(x, y).getB());
			}
		}

		double auto_exposure = 0;

		//make the exposure such that the highest color channel found becomes 255 in it's pixel representation
		if(max_color_channel != 0)
			auto_exposure = 1 / max_color_channel;

		return getPixelData(capture, auto_exposure);
	}

	//clamp the value between the min and max
	double clamp(double value, double min, double max) {
		if(value < min) return min;
		if(value > max) return max;

		return value;
	}

	//writes the pixel data to a file in Portable Pixel Map (PPM) format
	bool writeToFile(const PixelData &pixelData, const std::string &path) {
		std::ofstream ofs;

		try {
			//attempt to open file
			ofs.open(path, std::ios::binary);
			if (ofs.fail()) throw("Can't open output file \"" + path + "\"");

			//print PPM header and width and height to the file
			ofs << "P6\n" << pixelData.getWidth() << " " << pixelData.getHeight() << "\n255\n";

			//print each pixel to the file
			for(int y = 0; y < pixelData.getHeight(); ++y) {
				for(int x = 0; x < pixelData.getWidth(); ++x) {
					const Pixel& pixel = pixelData.getPixel(x, y);
					ofs << pixel.getR() << pixel.getG() << pixel.getB();
				}
			}

			//close the stream
			ofs.close();
		}
		catch (const std::string &err) {
			std::cerr << err;
			ofs.close();
		}
	}
}