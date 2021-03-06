#include <stdio.h>

#define BACKGROUND_COLOR 0xF800

// Function to send a string of text to the VGA monitor
void VGA_text(int x, int y, char * text_ptr)
{
	int offset;
	
	// VGA char_buffer_slave location address - Base address is 0x04004000 in Qsys
	volatile char * character_buffer = (char *) 0xC4004000;

	// Note: Assume all characters will fit on a single line
	offset = (y << 7) + x;
	while ( *(text_ptr) )
	{
		*(character_buffer + offset) = *(text_ptr);
		text_ptr++;
		offset++;
	} // while
} // VGA_text

void VGA_bounce(int x_start, int x_end, int y_start, int y_end, char * text_ptr)
{
	char *ptr_start;
	int offset;
	int y = (y_start + y_end)/2;
	int x = (x_start + x_end)/2;
	int x_move = 1;
	int y_move = 1;
	int i=0;
	int j = 0;
	char orig_char[50];
	

	// VGA char_buffer_slave location address - Base address is 0x04004000 in Qsys
	volatile char * character_buffer = (char *) 0xC4004000;
	ptr_start = text_ptr;
	while(1)
	{
		j = 0;
		text_ptr = ptr_start;
		if (x == x_start || x == x_end)
			x_move = -x_move;
		if (y == y_start || y == y_end)
			y_move = -y_move;
		x = x + x_move;
		y = y + y_move;
		offset = (y << 7) + x;
		while ( *(text_ptr) )
		{
			orig_char[j] = *(character_buffer + offset);
			*(character_buffer + offset) = *(text_ptr);
			text_ptr++;
			offset++;
			j++;
		} // while
		for (i = 0; i< 500000; i++)
		{
		}
		text_ptr = ptr_start;
		offset = (y << 7) + x;
		j = 0;
		while ( *(text_ptr) )
		{
			*(character_buffer + offset) = orig_char[j];
			text_ptr++;
			offset++;
			j++;
		} // while
	}	// while(1)
}	// VGA_bounce

// Function to Draw a filled rectangle o nthe VGA monitor
void VGA_box(int x1, int y1, int x2, int y2, short pixel_color)
{
	int offset, row, col;

	// VGA pixel buffer location address in On-Chip Memory Address in Qsys
	// Remember Pixel DMA does not have embedded memory
	// VGA SDRAM location address - Base address is 0x0000_0000 in Qsys
	volatile short * pixel_buffer = (short *) 0xC0000000;

	// Note: Assume that the box coordinates are valid on the screen
	// If coordinates are off the screen it is helpful to set coordinates so that the
	// box swhows on the screen again. You may need to choose coordinates within the screen
	// resolution
	// Each pixel value is represented as 16-bit halfword, with five bits for the blue, 
	// five bits for the red, and six bits for green
	for (row = y1; row <= y2; row++)
		for (col = x1; col <= x2; ++col)
		{
			offset = (row << 9) + col;
			*(pixel_buffer + offset) = pixel_color; // compute halfword address, set pixel color
		} // for col
} // VGA_box

int main(void)
{
	int x = 31;	// 120/4
	int y = 26;	// 100/4
	int x_move = 1;
	int y_move = 1;
	int i = 0;
	/* create a message to be displayed on the VGA and LCD displays */
	char text_stationary[50] = "Visionaries\0";
	char text_bouncing[50] = "Bounce\0";
	/* output text message in the middle of the VGA monitor */
	VGA_text (140/4, 120/4, text_stationary);

//	Pixel color is in Red_Green_Blue format - 0x0001.1_000.011_1.1111 = 0x1878

	// background
	VGA_box (0*4, 0*4, 80*4, 120*4, BACKGROUND_COLOR); // Display Pixel X:0 to 319, 16-Bit RGB
	// green box
	VGA_box(120,100,200,140,0x07E0);

	VGA_bounce(30,44,25,34,text_bouncing);
	
	while(1)
	{

	}
	
	return 0;
} // main
