#ifndef TGA_H
#define TGA_H

// By the way, disable the STL warnings
#pragma warning (disable:4786)

#include <windows.h>
#include <stdio.h>

struct tga_header {
	BYTE ID_length;
	BYTE image_type;
	WORD first_color_map_entry;
	WORD color_map_length;
	BYTE color_map_entry_size;
	WORD image_x_origin;
	WORD image_y_origin;
	WORD image_width;
	WORD image_height;
	BYTE bits_per_pixel;
	BYTE image_descriptor_bits;
};

class targa{
	
	public:

	targa();
	targa::targa(char* filename);
	targa::~targa();

	unsigned char* buffer;

	int colordepth,width,height; //color, height, width
};

#endif