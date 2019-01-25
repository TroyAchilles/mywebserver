#pragma once
/********************************BMP define*************************************/
#define BI_BITFIELDS 0x3
#define BI_RGB 0x00000000

typedef struct tagBITMAPFILEHEADER{ 	// BMP file header
        int16_t bfType;					// ‘BM’(1-2BYTE）
        int32_t bfSize;					// size of file，unit bytes（3-6 bytes，low byte first）
        int16_t bfReserved1;			// must be 0(7-8 bytes）
        int16_t bfReserved2;			// must be 0(9-10 bytes）
        int32_t bfOffBits;				// pointer to the pixmap bits（11-14 byte，low bytes first）
}__attribute__((packed)) BitMapFileHeader;

typedef struct tagBITMAPINFOHEADER{ 	// BMP information header
        int32_t biSize;					// size of this struct（15-18 bytes）
        int32_t biWidth;				// pixmap width, unit pixel（19-22 bytes）
        int32_t biHeight; 				// pimap height, unit pixel（23-26 bytes）
        int16_t biPlanes; 				// device levev，should be 1 (27-28 bytes）
        int16_t biBitCount; 			// number of bits per pixel，1（2），4(16），8(256）16(高彩色)或24（真彩色）(29-30 bytes)
        int32_t biCompression; 			// compression method，0（no compression），（31-34 bytes）
        int32_t biSizeImage; 			// size of image(include aligned bytes)（35-38 bytes）
        int32_t biXPelsPerMeter; 		// horizontal resolution（39-42 bytes）
        int32_t biYPelsPerMeter; 		// vertical resolution（43-46 bytes)
        int32_t biClrUsed; 				// number of colors used（47-50 bytes）
        int32_t biClrImportant; 		// number of important colors（51-54 bytes）

        uint32_t biRedMask;
        uint32_t biGreenMask;
        uint32_t biBlueMask;
        uint32_t biAlphaMask;
}__attribute__((packed)) BitMapInfoHeader;
// end BMP define
