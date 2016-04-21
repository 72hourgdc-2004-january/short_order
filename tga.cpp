// A slightly rewritten version of the TGA function used in 
// applications such as Dojo, Guardian and Campus Rumble
//It now uses standard ANSI C
// Loading functions to maintain some portablility
// This version also flips the image instead of just changing
// color positions

#include "tga.h"

targa::targa()
{
	width = 0;
	height = 0;
	buffer = NULL;
}

targa::targa(char* filename)
{
	tga_header tgahead;
	int size;

	BYTE* temp;
	FILE* fp;

	fp = fopen(filename, "rb");

	if(!fp)
	{
		//should be replaced with logging functions
		//MessageBox(NULL,"Could not find TGA file","TGA load error",NULL);
		buffer = NULL;
		return;
	}

	fread(&tgahead,1,sizeof(tga_header),fp);

	colordepth = tgahead.bits_per_pixel;

	//For 24 bit color textures
	if(tgahead.bits_per_pixel==24)
	{
		width=tgahead.image_width;
		height=tgahead.image_height;
		size=width*height*3;
		buffer=new BYTE[size];

		fread(buffer,size,sizeof(unsigned char),fp);
	
		temp= new BYTE[size];
		
		memcpy(temp,buffer,size);

		//flips the colors
		for(int index=0;index<height;index++)
			memcpy(&buffer[index*width*3],&temp[(height-index-1)*width*3],width*3);

		delete temp;
	}
	//For 8 bit alpha textures
	else if(tgahead.bits_per_pixel==8)
	{
		width=tgahead.image_width;
		height=tgahead.image_height;
		size=width*height;
		
		buffer=new BYTE[size];

		fread(buffer,size,sizeof(unsigned char),fp);
	}
	//Finally 32 bit RGBA textures
	else if(tgahead.bits_per_pixel==32)
	{
		width=tgahead.image_width;
		height=tgahead.image_height;
		size=width*height*4;
		
		buffer=new BYTE[size];

		fread(buffer,size,sizeof(unsigned char),fp);
	
		temp= new BYTE[size];
		
		memcpy(temp,buffer,size);

		//Flips the image
		for(int index=0;index<height;index++)
			memcpy(&buffer[index*width*4],&temp[(height-index-1)*width*4],width*4);
		
		
		delete temp;
	}

	if(buffer==NULL)
	{
		//should be replaced with logging functions

		//MessageBox(NULL,"TGA file empty?","TGA Load error",NULL);
	}

	fclose(fp);	
}	

targa::~targa()
{
	if(buffer!=NULL)
	{
		delete [] buffer;
		buffer = NULL;
	}
}		
