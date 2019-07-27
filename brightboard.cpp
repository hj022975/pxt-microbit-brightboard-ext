/**
* Test brightboard code
*/


#include "pxt.h"
#include "pxtbase.h"
#include "brightboard.h"
#include <cstdint>
#include <math.h>

using namespace pxt;

namespace brightboard {

	//%
	void dotStarSPIMode(int bits, int mode) {
		//pins::spiFormat(8,3);
		pins::spiFormat(bits,mode);
	}
	

	SPI* getSPI() {
		SPI* spi = pins::allocSPI();
		return spi;
	}	
	
	
	//%
	void spiDotStarSendBuffer(Buffer buf, int len) {
		SPI* spi = getSPI();
		// Send zero frame initially
		for (int8_t i = 0; i < 4; i++) {
			spi->write(0x00);
		}
		int offset;
		uint8_t* bufPtr = buf->data;
		// Send values from buffer
		for(int8_t i = 0; i < len; i++) {
			offset = i*3;
			spi->write(0xff); //Brightness on full - colors already scaled in buffer
			// For some reason colors go out in reverse order
			spi->write(bufPtr[offset+2]);
			spi->write(bufPtr[offset+1]);
			spi->write(bufPtr[offset]);
			spi->write(0x00);
		}
		// Send end frame
		for (int8_t i = 0; i < 4; i++) {
			spi->write(0xff);
		}		
	}
	
	
	
	//%
	void clear() {
		SPI* spi = getSPI();
		// Send zero frame intitially
		for (int8_t i = 0; i < 4; i++) {
			spi->write(0x00);
		}
		// Send data for each pixel (red on, green, blue off)
		for (int8_t i = 0; i < 12; i++) {
			spi->write(0xff); //Brightness on full
			spi->write(0x00); //Red fully off
			spi->write(0x00); //Blue/green fully off
			spi->write(0x00);
		}
		// Send end frame
		for (int8_t i = 0; i < 4; i++) {
			spi->write(0xff);
		}	
	}
	
}
