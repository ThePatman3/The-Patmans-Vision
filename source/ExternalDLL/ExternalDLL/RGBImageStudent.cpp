#include "RGBImageStudent.h"

void RGBImageStudent::cleanMemory() {
	if (!memoryAllocated) { return; }
	delete[] pixelArray;
	memoryAllocated = false;
}

RGBImageStudent::RGBImageStudent() : RGBImage(), memoryAllocated(false) {}

RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) : RGBImage(other.getWidth(), other.getHeight()), memoryAllocated(true) {
	pixelArray = new RGB[other.getWidth()*other.getHeight()];
	for (int i = 0; i < (getWidth()*getHeight()); i++) {
		pixelArray[i] = other.getPixel(i);
	}
}


RGBImageStudent::RGBImageStudent(const int width, const int height) : RGBImage(width, height), memoryAllocated(true) {
	pixelArray = new RGB[width*height];
	for (int i = 0; i < (width*height); i++) {
		pixelArray[i] = 0;
	}
}

RGBImageStudent::~RGBImageStudent() {
	cleanMemory();
}

void RGBImageStudent::set(const int width, const int height) {
	RGBImage::set(width, height);
	cleanMemory();
	pixelArray = new RGB[width*height];
	memoryAllocated = true;
	for (int i = 0; i < (width*height); i++) {
		pixelArray[i] = 0;
	}
}

void RGBImageStudent::set(const RGBImageStudent &other) {
	RGBImage::set(other.getWidth(), other.getHeight());
	cleanMemory();
	pixelArray = new RGB[getWidth()*getHeight()];
	memoryAllocated = true;
	for (int i = 0; i < (getWidth()*getHeight()); i++) {
		pixelArray[i] = other.getPixel(i);
	}
}

void RGBImageStudent::setPixel(int x, int y, RGB pixel) {
	pixelArray[x + (y*getWidth())] = pixel;
}

void RGBImageStudent::setPixel(int i, RGB pixel) {
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

RGB RGBImageStudent::getPixel(int x, int y) const {
	return pixelArray[x + (y*getWidth())];
}

RGB RGBImageStudent::getPixel(int i) const {
	return pixelArray[i];
}