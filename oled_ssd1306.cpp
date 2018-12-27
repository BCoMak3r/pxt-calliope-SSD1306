
#include "pxt.h"
#include "Adafruit_SSD1306.h"
#include <cmath>


using namespace pxt;

namespace oled_ssd1306 {
	#define SSD1306_ADDRESS 0x78
	#define FONT_WIDTH 6
	#define FONT_HEIGHT 8
	// #define PI 3,1415926535897932384626433832795
	
	#undef printf

	// ################################## (Namespace) global variables  ##################################
	//
	MicroBitI2C i2c(I2C_SDA0, I2C_SCL0);
	Adafruit_SSD1306_I2C *oled;

	
	// Winkel
	const double pi = std::acos(-1);
	
	// Drawing specific name space global variables.
	// Will partly be set/reset with init functions
	
	// Colors
	int drawColor = 1;
	int txtFgColor = 1;
	int txtBgColor = 1;
	
	
	// Variables for progress bar
	int progressBarX = 0;
	int progressBarY = 0;
	int progressBarWidth = 0;
	int progressBarHeight = 0;
	bool progressBarBoxDrawn = false;


	// Variables for circle
	bool circleFilled = false;
	int circleRadius = 0;

	
	// Variables for rectangle
	bool rectangleFilled = false;
	int rectangleEdgeRadius = 0;

	
	
	// ################################## Functions ########################################################################
	//
	
	// ### Initialisation ##################################################################################################
	
	
	//%
	void initDisplay(int height = 64, int width = 128, int i2c_address = 0x78){
		// SSD1306_ADDRESS was changed to be setable!
		if (oled != NULL) delete oled;
		oled = new Adafruit_SSD1306_I2C(i2c, i2c_address, height, width);
		oled->clearDisplay();
		oled->display();
		oled->setTextCursor(0, 0);
	}


	//%
	void switchDisplayToOn(bool on = true) {
		oled->isDisplay = on;
		if(on) {
		    oled->display();
		}
	}

	
	//%
	void clearDisplay(){
		oled->clearDisplay();
		oled->display();
	}


	// ### Printing of text / numbers ######################################################################################

	
	//%
	void setTextColor(int fgColor, int bgColor){
		txtFgColor = fgColor;
		txtBgColor = bgColor;
		oled->setTextColor(fgColor, bgColor);
	}

	
	//%
	void setTextSize(int size) {
		oled->setTextSize(size);
	}
	
	
	//%
	void setTextCursorXY(int x, int y) {
		oled->setTextCursor(x, y);
	}
	
	
	//%
	void setTextCursorRowColumn(int row, int column) {
		row = row * FONT_HEIGHT;
		column = column * FONT_WIDTH;
		oled->setTextCursor(column, row);
	}
	
	
	//%
	void printString(StringData *text) {
		oled->printf("%s\n", text->data);
		oled->display();
	}
    
	
	//%
	void printNumber(int number) {
		oled->printf("%d\n", number);
		oled->display();
	}
    

	// ### Drawing of lines, circles, rectangles etc. ######################################################################


	//%
	void setdrawColor(int color){
		drawColor = color;
	}

	
	//%
	void drawLine(int x0, int y0, int x1, int y1) {
		oled->drawLine(x0, y0, x1, y1, drawColor);
		if(oled->isDisplay) {
			oled->display();
		}
	}

		
	//%
	void drawLine2(int x0, int y0, int width, int alpha) {		
		
		int alphaRad = alpha * pi / 180;
		
		int gamma = 90 - alpha;
		int gammaRad = gamma * pi / 180;
		
		int x1 = x0 + ( width * std::sin(gammaRad) );
		int y1 = y0 + ( width * std::sin(alphaRad) );
		//int x1 = x0 + 20;
		//int y1 = y0 + 0;
		oled->drawLine(x0, y0, x1, y1, drawColor);
		if(oled->isDisplay) {
			oled->display();
		}
	}
	

	//%
    void initCircle(bool filled, int radius) {
		circleFilled = filled;
		circleRadius = radius;
        return;
    }
	
	
	//%
	void drawCircle(int x0, int y0){
		if (!circleFilled) {
				oled->drawCircle(x0, y0, circleRadius, drawColor);
		} else {
				oled->fillCircle(x0, y0, circleRadius, drawColor);
		}

		if(oled->isDisplay) {
			oled->display();
		}
	}

	
	//%
	void initRectangle(bool filled, int edgeRadius) {
		rectangleFilled = filled;
		rectangleEdgeRadius = edgeRadius;
	}	

	
	//%
	void drawRectangle(int x0, int y0, int width, int height) {
		if (rectangleEdgeRadius == 0) {
			if (!rectangleFilled) {
					oled->drawRect(x0, y0, width, height, drawColor);
			} else {
					oled->fillRect(x0, y0, width, height, drawColor);
			}
		} else {
			if (!rectangleFilled) {
					oled->fillRoundRect(x0, y0, width, height, rectangleEdgeRadius, drawColor);
			} else {
					oled->fillRoundRect(x0, y0, width, height, rectangleEdgeRadius, drawColor);
			}
		}
		
		if(oled->isDisplay) {
			oled->display();
		}				
	}
	
	
	//%
	void initProgressBar(int x0, int y0, int width, int height) {
		progressBarX = x0;
		progressBarY = y0;
		progressBarWidth = width;
		progressBarHeight = height;
	}

	
	//%
	void drawProgressBar(int progress) {
		int progressBarActWidth = progress * (progressBarWidth-4)/100;		
		int progressBarFillX = progressBarX + 2;
		int progressBarFillY = progressBarY + 2;
		int progressBarFillHeight = progressBarHeight - 4;
		
		if (!progressBarBoxDrawn) { 
			oled->drawRect(progressBarX, progressBarY, progressBarWidth, progressBarHeight, drawColor);
			progressBarBoxDrawn = true;
		}
		
		oled->fillRect(progressBarFillX, progressBarFillY, progressBarActWidth, progressBarFillHeight, drawColor);

		if(oled->isDisplay) {
			oled->display();
		}						

	}

	
    #define printf(...) uBit.serial.printf(__VA_ARGS__)

}









