/*   CS580 HW1 display functions to be completed   */

#include   "stdafx.h"  
#include	"Gz.h"
#include	"disp.h"

int GzNewFrameBuffer(char** framebuffer, int width, int height)
{
	// HW1.1 create a framebuffer for MS Windows display:

	// -- check for boundary values
	if (width <= 0 || width > MAXXRES || height <= 0 || height > MAXYRES)
		return GZ_FAILURE;
	// -- allocate memory for framebuffer : 3 bytes(b, g, r) x width x height
	char* newFrameBuffer = new char[3 * width * height];
	// check if buffer is NULL
	if (newFrameBuffer == NULL)
		return GZ_FAILURE;
	// -- pass back pointer 
	*framebuffer = newFrameBuffer;

	return GZ_SUCCESS;
}

int GzNewDisplay(GzDisplay	**display, int xRes, int yRes)
{
	// HW1.2 create a display:

	// -- check for boundary values
	if (xRes <= 0 || xRes > MAXXRES || yRes <= 0 || yRes > MAXYRES)
		return GZ_FAILURE;
	// -- allocate memory for indicated resolution
	GzDisplay* newDisplay = new GzDisplay;
	newDisplay->xres = xRes;
	newDisplay->yres = yRes;
	newDisplay->fbuf = new GzPixel[xRes*yRes];
	// -- pass back pointer to GzDisplay object in display
	*display = newDisplay;

	return GZ_SUCCESS;
}

int GzFreeDisplay(GzDisplay	*display)
{
	// HW1.3 clean up, free memory

	if (display != NULL)
		delete display;

	return GZ_SUCCESS;
}

int GzGetDisplayParams(GzDisplay* display, int* xRes, int* yRes)
{
	// HW1.4 pass back values for a display
	// --check for boundary values
	if (display->xres <= 0 || display->xres > MAXXRES || display->yres <= 0 || display->yres > MAXYRES)
		return GZ_FAILURE;
	// --pass the values back 
	*xRes = display->xres;
	*yRes = display->yres;

	return GZ_SUCCESS;
}

int GzInitDisplay(GzDisplay	*display)
{
	// HW1.5 set everything to some default values - start a new frame

	// --check for boundary values 
	if (display == NULL)
		return GZ_FAILURE;
	// --Use the xres and yres from display to fill up fbuf
	int bufferSize = display->xres * display->yres;
	for (int i = 0; i < bufferSize; i++){
		display->fbuf[i].red = 2048;
		display->fbuf[i].green = 2048;
		display->fbuf[i].blue = 2048;
		display->fbuf[i].alpha = 1;
		display->fbuf[i].z = INT_MAX;
	}

	return GZ_SUCCESS;
}

int GzPutDisplay(GzDisplay *display, int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
	// HW1.6 write pixel values into the display

	// check the boundary values
	if (display == NULL)
		return GZ_FAILURE;
	if (i < 0 || i >= display->xres || j < 0 || j >= display->yres)
		return GZ_FAILURE;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	if (r > 4095)
		r = 4095;
	if (g > 4095)
		g = 4095;
	if (b > 4095)
		b = 4095;
	// these 2 were already intialized
	//display->xres =  ;
	//display->yres =  ;
	// initialize fbuf 
	// NOTE: fbuf is a 1D array => index = i + j*display->xres
	display->fbuf[ARRAY(i, j)].red = r;
	printf(" i = %d , j = %d , display = %d ", i, j, display->fbuf[ARRAY(i, j)].red);
	display->fbuf[ARRAY(i, j)].green = g;
	display->fbuf[ARRAY(i, j)].blue = b;
	display->fbuf[ARRAY(i, j)].alpha = a;
	display->fbuf[ARRAY(i, j)].z = z;

	return GZ_SUCCESS;
}

int GzGetDisplay(GzDisplay *display, int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
	// HW1.7 pass back a pixel value to the display

	// --check boundary values 
	if (display == NULL)
		return GZ_FAILURE;
	int bufferSize = display->xres * display->yres;
	if (ARRAY(i, j) < 0 || ARRAY(i, j) > bufferSize)
		return GZ_FAILURE;
	// pass back values to the display
	*r = display->fbuf[ARRAY(i, j)].red;
	*g = display->fbuf[ARRAY(i, j)].green;
	*b = display->fbuf[ARRAY(i, j)].blue;
	*a = display->fbuf[ARRAY(i, j)].alpha;
	*z = display->fbuf[ARRAY(i, j)].z;

	return GZ_SUCCESS;
}

int GzFlushDisplay2File(FILE* outfile, GzDisplay *display)
{
	// HW1.8 write pixels to ppm file -- "P6 %d %d 255\r" 

	// --check boundary values 
	if (display == NULL)
		return GZ_FAILURE;
	if (outfile == NULL)
		return GZ_FAILURE;

	int bufferSize = display->xres* display->yres;
	// write the first line
	fprintf(outfile, "P6 %d %d 255\r", display->xres, display->yres);
	// write the r,g,b values for each pixel
	for (int i = 0; i < bufferSize; i++){
		fwrite(&display->fbuf[i].red, 1, 1, outfile);
		fwrite(&display->fbuf[i].green, 1, 1, outfile);
		fwrite(&display->fbuf[i].blue, 1, 1, outfile);
	}

	return GZ_SUCCESS;
}

int GzFlushDisplay2FrameBuffer(char* framebuffer, GzDisplay *display)
{
	// HW1.9 write pixels to framebuffer: 
	//	- put the pixels into the frame buffer
	//	- CAUTION: when storing the pixels into the frame buffer, the order is blue, green, and red 
	//	- NOT red, green, and blue !!!

	if (framebuffer == NULL || display == NULL)
		return GZ_FAILURE;
	int bufferSize = display->xres* display->yres;
	int fb_index = 0;
	for (int i = 0; i < bufferSize - 1; i++){
		sprintf(framebuffer + fb_index, "%c", display->fbuf[i].blue >> 4);
		sprintf(framebuffer + fb_index + 1, "%c", display->fbuf[i].green >> 4);
		sprintf(framebuffer + fb_index + 2, "%c", display->fbuf[i].red >> 4);
		fb_index += 3;
	}

	return GZ_SUCCESS;
}