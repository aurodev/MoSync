/* Copyright 2013 David Axmark

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/** \file drawable.cpp
*
* This file contains the class Drawable, representing a vertex model of any drawable 3-dimensional object.
*
* \author Patrick Broman and Niklas Nummelin
*
*/

#include "drawable.h"
#include <conprint.h>

/**
 * Create a drawable object, with numVertices number of vertices.
 */
Drawable::Drawable(int aNumVertices) :
	mCurVertex(0),
	mNumVertices(aNumVertices),
	mOriginal(new Vector[aNumVertices]),
	mTransformed(new Vector[aNumVertices])
{
}

/**
 * Destroy Drawable object.
 */
Drawable::~Drawable() {
	delete []mOriginal;
	delete []mTransformed;
}

/**
 * Add vertex with coordinates 'x', 'y', 'z'.
 */
void Drawable::addVertex(int x, int y, int z) {
	if(mCurVertex<mNumVertices)
		mOriginal[mCurVertex++] = Vector(x, y, z);
}

/**
 * Get number of vertices.
 */
int Drawable::getNumVertices() {
	return mNumVertices;
}

/**
 * Set position with coordinates 'x', 'y', 'z'.
 */
void Drawable::setPosition(int x, int y, int z) {
	mPosition = Vector(x, y, z);
}

/**
 * Set rotation with rotation angles 'x', 'y', 'z' around each respective axis.
 */
void Drawable::setRotation(int x, int y, int z) {
	mRotation = Vector(x, y, z);
}

/**
 * Set scale with scale factors 'x', 'y', 'z'.
 */
void Drawable::setScale(int x, int y, int z) {
	mScale = Vector(x, y, z);
}

/**
 * Transform object, and store it for rendering.
 */
void Drawable::transform() {
	int i;

	/// Do some precalculations for the rotations using fixed point math, and the macros for retrieving lookup table sinus values.
	int c1=COS(mRotation.mX), s1=SIN(mRotation.mX),
		c2=COS(mRotation.mY), s2=SIN(mRotation.mY),
		c3=COS(mRotation.mZ), s3=SIN(mRotation.mZ);
	int xx, xy, xz, yx, yy, yz, zx, zy, zz;
	xx=(c2*c1)>>TRIG_LOOKUP_BITS;
	xy=(c2*s1)>>TRIG_LOOKUP_BITS;
	xz=s2;
	yx=((c3*s1)>>TRIG_LOOKUP_BITS)+((s3*((s2*c1)>>TRIG_LOOKUP_BITS))>>TRIG_LOOKUP_BITS);
	yy=((-c3*c1)>>TRIG_LOOKUP_BITS)+((s3*((s2*s1)>>TRIG_LOOKUP_BITS))>>TRIG_LOOKUP_BITS);
	yz=(-s3*c2)>>TRIG_LOOKUP_BITS;
	zx=((s3*s1)>>TRIG_LOOKUP_BITS)-((((c3*s2)>>TRIG_LOOKUP_BITS)*c1)>>TRIG_LOOKUP_BITS);
	zy=((-s3*c1)>>TRIG_LOOKUP_BITS)-((((c3*s2)>>TRIG_LOOKUP_BITS)*s1)>>TRIG_LOOKUP_BITS);
	zz=(c3*c2)>>TRIG_LOOKUP_BITS;


	for(i=0; i < mNumVertices; i++) {
		/// Rotate object.
		mTransformed[i].mX=(xx * mOriginal[i].mX + xy * mOriginal[i].mY + xz * mOriginal[i].mZ)>>TRIG_LOOKUP_BITS;
		mTransformed[i].mY=(yx * mOriginal[i].mX + yy * mOriginal[i].mY + yz * mOriginal[i].mZ)>>TRIG_LOOKUP_BITS;
		mTransformed[i].mZ=(zx * mOriginal[i].mX + zy * mOriginal[i].mY + zz * mOriginal[i].mZ)>>TRIG_LOOKUP_BITS;

		/// Translate object.
		mTransformed[i].mX+=mPosition.mX;
		mTransformed[i].mY+=mPosition.mY;
		mTransformed[i].mZ+=mPosition.mZ;
	}
}
