/*   CS580 HW1 display functions to be completed   */

#include   "stdafx.h"  
#include	"Gz.h"
#include	"disp.h"


int GzNewFrameBuffer(char** framebuffer, int width, int height)
{
/* HW1.1 create a framebuffer for MS Windows display:
 -- allocate memory for framebuffer : 3 bytes(b, g, r) x width x height
 -- pass back pointer 
 */
	return GZ_SUCCESS;
}

int GzNewDisplay(GzDisplay	**display, int xRes, int yRes)
{
/* HW1.2 create a display:
  -- allocate memory for indicated resolution
  -- pass back pointer to GzDisplay object in display
*/
	return GZ_SUCCESS;
}


int GzFreeDisplay(GzDisplay	*display)
{
/* HW1.3 clean up, free memory */
	return GZ_SUCCESS;
}


int GzGetDisplayParams(GzDisplay *display, int *xRes, int *yRes)
{
/* HW1.4 pass back values for a display */
	return GZ_SUCCESS;
}


int GzInitDisplay(GzDisplay	*display)
{
/* HW1.5 set everything to some default values - start a new frame */
	return GZ_SUCCESS;
}


int GzPutDisplay(GzDisplay *display, int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
/* HW1.6 write pixel values into the display */
	return GZ_SUCCESS;
}


int GzGetDisplay(GzDisplay *display, int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
/* HW1.7 pass back a pixel value to the display */
	return GZ_SUCCESS;
}


int GzFlushDisplay2File(FILE* outfile, GzDisplay *display)
{

/* HW1.8 write pixels to ppm file -- "P6 %d %d 255\r" */
	return GZ_SUCCESS;
}

int GzFlushDisplay2FrameBuffer(char* framebuffer, GzDisplay *display)
{

/* HW1.9 write pixels to framebuffer: 
	- put the pixels into the frame buffer
	- CAUTION: when storing the pixels into the frame buffer, the order is blue, green, and red 
	- NOT red, green, and blue !!!
*/
	return GZ_SUCCESS;
}