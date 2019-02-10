/*
* Copyright (c) 2015 DottedEye Designs, Alexander Hustinx, NeoTech Software, Rolf Smit - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*/

#pragma once
#include "PreProcessing.h"
class StudentPreProcessing : public PreProcessing {
private:
	Intensity lanczosKernel(float x) const;

	// Takes four intensity pixels and a float x which tells where between the second and third pixels the interpolation should take place
	// if x <= 0 then the interpolation will take place precisely at the second pixel, if x >= 1 then the interpolation will take place precisely at the third pixel
	Intensity lanczosInterpolate(const Intensity* source, float x) const;
	// here, the first pixel is a, the second is b, etc.
	Intensity lanczosInterpolate(Intensity a, Intensity b, Intensity c, Intensity d, float x) const;

	// Extrapolates the intensity of a pixel at coordinate (x;y) using the source image as reference.
	Intensity biLanczosInterpolate(const IntensityImage& source, float x, float y) const;

	Intensity cubicInterpolate(const Intensity* source, float x) const;
	Intensity biCubicInterpolate(const IntensityImage& source, float x, float y) const;
public:
	static enum ScalingType
	{
		Lanczos, BiCubic
	};
	static ScalingType scalingType;

	IntensityImage * stepToIntensityImage(const RGBImage &image) const;
	IntensityImage * stepScaleImage(const IntensityImage &image) const;
	IntensityImage * stepEdgeDetection(const IntensityImage &image) const;
	IntensityImage * stepThresholding(const IntensityImage &image) const;
};