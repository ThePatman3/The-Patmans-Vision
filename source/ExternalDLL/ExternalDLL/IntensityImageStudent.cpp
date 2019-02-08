#include "IntensityImageStudent.h"

void IntensityImageStudent::cleanMemory() {
	if (!memoryAllocated) { return; }
	delete[] pixelArray;
	memoryAllocated = false;
}

IntensityImageStudent::IntensityImageStudent() : IntensityImage(), memoryAllocated(false){}

IntensityImageStudent::IntensityImageStudent(const IntensityImageStudent &other) : IntensityImage(other.getWidth(), other.getHeight()), memoryAllocated(true){
	pixelArray = new Intensity[getWidth()*getHeight()];
	for (int i = 0; i < (getWidth()*getHeight()); i++) {
		pixelArray[i] = other.getPixel(i);
	}
}

IntensityImageStudent::IntensityImageStudent(const int width, const int height) : IntensityImage(width, height), memoryAllocated(true){
	pixelArray = new Intensity[width*height];
	for (int i = 0; i < (width*height); i++) {
		pixelArray[i] = 0;
	}
}

IntensityImageStudent::~IntensityImageStudent() {
	cleanMemory();
}

void IntensityImageStudent::set(const int width, const int height) {
	IntensityImage::set(width, height);
	cleanMemory();
	pixelArray = new Intensity[width*height];
	memoryAllocated = true;
	for (int i = 0; i < (width*height); i++) {
		pixelArray[i] = 0;
	}
}

void IntensityImageStudent::set(const IntensityImageStudent &other) {
	IntensityImage::set(other.getWidth(), other.getHeight());
	cleanMemory();
	pixelArray = new Intensity[getWidth()*getHeight()];
	memoryAllocated = true;
	for (int i = 0; i < (getWidth()*getHeight()); i++) {
		pixelArray[i] = other.getPixel(i);
	}
}

void IntensityImageStudent::setPixel(int x, int y, Intensity pixel) {
	pixelArray[x + (y*getWidth())] = pixel;
}

void IntensityImageStudent::setPixel(int i, Intensity pixel) {
	pixelArray[i] = pixel;
	/*
	* set pixel i in "Row-Major Order"
	*
	*
	* Original 2d image (values):
	* 9 1 2
	* 4 3 5
	* 8 7 8
	*
	* 1d representation (i, value):
	* i		value
	* 0		9
	* 1		1
	* 2		2
	* 3		4
	* 4		3
	* 5		5
	* 6		8
	* 7		7
	* 8		8
	*/
}

Intensity IntensityImageStudent::getPixel(int x, int y) const {
	return pixelArray[x + (y*getWidth())];
}

Intensity IntensityImageStudent::getPixel(int i) const {
	return pixelArray[i];
}