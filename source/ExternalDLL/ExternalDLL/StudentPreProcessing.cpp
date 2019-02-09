#include "StudentPreProcessing.h"
#include "ImageFactory.h"

#include <iostream>
#include <cmath>

float PI = 3.14159265359;

Intensity sinc(Intensity x) {
	if (x == 0) return 1;
	return (std::sin(PI*x)) / (PI*x);
}

Intensity lanczos2(Intensity x) {
	if (x < 2) {
		return ((std::sin(PI*x)) / (PI*x)) * ((std::sin((PI*x) / 2)) / ((PI*x) / 2));
	}
	return 0;
}

Intensity StudentPreProcessing::lanczosKernel(Intensity x) const {
	return sinc(x) * lanczos2(x);
}

 
Intensity StudentPreProcessing::lanczosInterpolate(Intensity a, Intensity b, Intensity c, Intensity d, float x) const {
	if (x <= 0) { return b; }
	if (x >= 1) { return c; }

	Intensity result = 0;
	result += lanczosKernel((x + 1) - 0) * a;
	result += lanczosKernel((x + 1) - 1) * b;
	result += lanczosKernel((x + 1) - 2) * c;
	result += lanczosKernel((x + 1) - 3) * d;

	return result;
}

Intensity StudentPreProcessing::lanczosInterpolate(const Intensity* source, float x) const {
	if (x <= 0) { return source[1]; }
	if (x >= 1) { return source[2]; }

	Intensity result = 0;
	for (int i = 0; i < 4;i++) {
		result += lanczosKernel((x + 1) - i) * source[i];
	}
	return result;
}

Intensity StudentPreProcessing::biLanczosInterpolate(const IntensityImage& source, float x, float y) const {
	int XValues[4] = { int(x) - 1, int(x), int(x) + 1, int(x) + 2 };
	int YValues[4] = { int(y) - 1, int(y), int(y) + 1, int(y) + 2 };
	for (int i = 0; i < 4;i++) {
		if (XValues[i] < 0) { XValues[i] = 0; }
		if (XValues[i] >= source.getWidth()) { XValues[i] = source.getWidth() - 1; }
		if (YValues[i] < 0) { YValues[i] = 0; }
		if (YValues[i] >= source.getHeight()) { YValues[i] = source.getHeight() - 1; }
	}

	Intensity intermediateValues[4] = { 0,0,0,0 };

	for (int i = 0; i < 4; i++) {
		Intensity neighbours[4] = {
			source.getPixel(XValues[0], YValues[i]),
			source.getPixel(XValues[1], YValues[i]),
			source.getPixel(XValues[2], YValues[i]),
			source.getPixel(XValues[3], YValues[i])
		};

		intermediateValues[i] = lanczosInterpolate(neighbours, x);
	}

	Intensity result = lanczosInterpolate(intermediateValues, y);
	return result;
}

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	if (image.getHeight() * image.getWidth() < 40000) { return ImageFactory::newIntensityImage(image); }

	float divider = std::sqrt((image.getWidth() * image.getHeight()) / 40000.0f); // TODO: improve
	int newWidth = int(image.getWidth() / divider);
	int newHeight = int(image.getHeight() / divider);
	IntensityImage* result = ImageFactory::newIntensityImage(newWidth, newHeight);

	for (int x = 0; x < newWidth; x++) {
		for (int y = 0;y < newHeight;y++) {
			Intensity pixel = biLanczosInterpolate(
				image,
				(x / float(newWidth)) * image.getWidth(),
				(y / float(newHeight)) * image.getHeight()
			);
			result->setPixel(x, y, pixel);
		}
	}
	return result;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}