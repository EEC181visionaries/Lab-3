#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* For Reference
===========================
	int btn_value;
	int wait = 99999;
	int h = 0b1110110;
	int e = 0b1111001;
	int l = 0b0111000;
	int o = 0b0111111;
	int u = 0b0111110;
	int r = 0b1010000;
	int d = 0b1011110;
	===============
	*/

// Locations
#define HEX2_0_ADDRESS 0xFF200000	// 0x00000000
#define HEX5_3_ADDRESS 0xFF200010	// 0x00000010
#define LEDS_ADDRESS   0xFF200020	// 0x00000020
#define SW_ADDRESS     0xFF200030	// 0x00000030
#define PUSHBUTTON_ADDRESS 0xFF200040	// 0x00000040
#define CHAR_BUFFER_SLAVE_ADDRESS 0xC4004000	// 0x04004000

#define BOX_SIZE 30

//	Pixel color is in Red_Green_Blue format - 0x0001.1_000.011_1.1111 = 0x1878
#define BACKGROUND_COLOR 0xF800
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F


// Function to send a string of text to the VGA monitor
void VGA_text(int x, int y, char * text_ptr);

void VGA_bounce(int x_start, int x_end, int y_start, int y_end, char * text_ptr);

// Function to Draw a filled rectangle on the VGA monitor
void VGA_box(int x1, int y1, int x2, int y2, short pixel_color);

void VGA_temp_box(int x1, int x2, int y1, int y2, short pixel_color);

// ==============================================================================
// Main
// ==============================================================================

int main(void)
{
	srand(time(NULL));
	
	volatile int * led = (int *) LEDS_ADDRESS;
	volatile int * sw = (int *) SW_ADDRESS;
	volatile int * hex2_0 = (int *) HEX2_0_ADDRESS;
	volatile int * hex5_3 = (int *) HEX5_3_ADDRESS;
	volatile int * pushbuttons = (int *) PUSHBUTTON_ADDRESS;
	int switches;
	int buttons;
	int x[3];	// 120/4
	int y[3];	// 100/4
	int x_move = 1;
	int y_move = 1;
	int i = 0;
	int player = 0;
	int score1 = 0;	// change to array
	int score2 = 0;
	int color[3] = {BACKGROUND_COLOR,BLUE, GREEN};
	char text_stationary[50] = "Visionaries\0";
	VGA_text (140/4, 120/4, text_stationary);
	int times[3];



	// background
	VGA_box (0*4, 0*4, 80*4, 120*4, BACKGROUND_COLOR); // Display Pixel X:0 to 319, 16-Bit RGB

// Game initialization
	int x_start[3] = {0,rand()%(320-BOX_SIZE),rand()%(320-BOX_SIZE)};
	int y_start[3] = {0,rand()%(240-BOX_SIZE),rand()%(240-BOX_SIZE)};
	// generate new numbers until non-overlap
		while((x_start[3] > x_start[2] && x_start[3] < (x_start[2]+BOX_SIZE)) && (x_start[3]+BOX_SIZE > x_start[2] && x_start[3]+BOX_SIZE < (x_start[2]+BOX_SIZE)))
		{
			x_start[3] = rand()%(320-BOX_SIZE);
		}
		while((y_start[3] > y_start[2] && y_start[3] < (y_start[2]+BOX_SIZE)) && (y_start[3]+BOX_SIZE > y_start[2] && y_start[3]+BOX_SIZE < (y_start[2]+BOX_SIZE)))
		{
			y_start[3] = rand()%(320-BOX_SIZE);
		}
	for (i = 0; i <3; i++)
	{
		x[i] = x_start[i];
		y[i] = y_start[i];
	}
	
	VGA_temp_box(x[1],x[1]+BOX_SIZE,y[1],y[1]+BOX_SIZE,color[1]);
	VGA_temp_box(x[2],x[2]+BOX_SIZE,y[2],y[2]+BOX_SIZE,color[2]);

	while(1)
	{
		switches = *sw;
		switch(switches)
		{
		case 1:// 00000_00001
			player = 2;
			break;
		case 2://00000_00010
			player = 1;
			break;
		case 4://00000_00100
			score1 = 0;
			score2 = 0;
			player = 0;
			break;
		default:
			player = 0;
		}
		if (player)
		{
			buttons = *pushbuttons;
			if(buttons)
				VGA_temp_box(x[player],x[player]+BOX_SIZE,y[player],y[player]+BOX_SIZE,BACKGROUND_COLOR);
			
			if(buttons == 1)
				x[player]++;
			if(buttons == 2)
				x[player]--;
			if (buttons == 4)
				y[player]--;
			if (buttons == 8)
				y[player]++;

			VGA_temp_box(x[player],x[player]+BOX_SIZE,y[player],y[player]+BOX_SIZE,color[player]);
			
			
			while(buttons)
				buttons = *pushbuttons;	// wait until user releases buttons

			if((x[3] > x[2] && x[3] < (x[2]+BOX_SIZE)) && (x[3]+BOX_SIZE > x[2] && x[3]+BOX_SIZE < (x[2]+BOX_SIZE)))
			{
				*led = player;
			}
		}
	}
	
	return 0;
} // main


// ==============================================================================
// Function Definitions
// ==============================================================================

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

void VGA_temp_box(int x1, int x2, int y1, int y2, short pixel_color)
{
	int offset, row, col;

	// VGA pixel buffer location address in On-Chip Memory Address in Qsys
	// Remember Pixel DMA does not have embedded memory
	// VGA SDRAM location address - Base address is 0x0000_0000 in Qsys
	volatile short * pixel_buffer = (short *) 0xC4000000;

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
}
