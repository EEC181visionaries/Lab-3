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
		++text_ptr;
		++offset;
	} // while
} // VGA_text

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
	/* create a message to be displayed on the VGA and LCD displays */
	char text_top_row[50] = "Hello World/0";
	char text_bottom_row[50] = "My Name is Foo! My Favorite Class is ECE181./0";

	/* output text message in the middle of the VGA monitor */
	VGA_text (35, 29, text_top_row);
	VGA_text (35, 30, text_bottom_row);

//	Pixel color is in Red_Green_Blue format - 0x0001.1_000.011_1.1111 = 0x1878
	VGA_box (1*4-2, 28*4, 79*4+1, 32*4, 0xF800); // Display Pixel X:0 to 319, 16-Bit RGB

	while(1);
	return 0;
} // main
