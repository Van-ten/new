/**
  ******************************************************************************
  * @file           : st7735.c
  * @brief          : ST7735 driver
  * @author         : MicroTechnics (microtechnics.ru)
  ******************************************************************************
  */



/* Includes ------------------------------------------------------------------*/
//#include "fonts.h"

#include "st7735.h"





uint16_t width;
/* Declarations and definitions ----------------------------------------------*/

extern SPI_HandleTypeDef hspi1;

typedef struct
{
	uint16_t TextColor;
	uint16_t BackColor;
	sFONT *pFont;
}LCD_DrawPropTypeDef;
LCD_DrawPropTypeDef lcdprop;

/* Functions -----------------------------------------------------------------*/
void TFT9341_FontsIni(void)
{
  Font8.Height = 8;
  Font8.Width = 5;
  Font12.Height = 12;
  Font12.Width = 7;
  Font16.Height = 16;
  Font16.Width = 11;
  Font20.Height = 20;
  Font20.Width = 14;
  Font24.Height = 24;
  Font24.Width = 17;
  lcdprop.BackColor= ST7735_COLOR_BLACK;
  lcdprop.TextColor= ST7735_COLOR_GREEN;
  lcdprop.pFont=&Font16;
}
/*----------------------------------------------------------------------------*/
void ST7735_SendByte(uint8_t data)
{
  // HAL_SPI_Transmit(&hspi1, &data, 1, ST7735_SPI_TIMEOUT);
  while((SPI1->SR & SPI_SR_TXE) == RESET);  
  SPI1->DR = data;
}



/*----------------------------------------------------------------------------*/
void ST7735_WaitLastData()
{
  while((SPI1->SR & SPI_SR_TXE) == RESET);
  while((SPI1->SR & SPI_SR_BSY) != RESET);
}



/*----------------------------------------------------------------------------*/
void ST7735_SendCommand(uint8_t data)
{
  HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_RESET);
  ST7735_SendByte(data);
  ST7735_WaitLastData();
}



/*----------------------------------------------------------------------------*/
void ST7735_SendData(uint8_t data)
{
  HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_SET);  
  ST7735_SendByte(data);
  ST7735_WaitLastData();
}



/*----------------------------------------------------------------------------*/
void ST7735_SendDataMultiple(uint8_t *data, uint32_t num)
{
  HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_SET);
  
  for (uint32_t i = 0; i < num; i++)
  {
    ST7735_SendByte(*data);
    data++;
  }
  
  ST7735_WaitLastData();
}



/*----------------------------------------------------------------------------*/
void ST7735_Init()
{ 
  SPI1->CR1 |= SPI_CR1_SPE;
  HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_RESET);
  
  HAL_GPIO_WritePin(ST7735_RESET_PORT, ST7735_RESET_PIN, GPIO_PIN_SET);
  HAL_Delay(5);
	HAL_GPIO_WritePin(ST7735_RESET_PORT, ST7735_RESET_PIN, GPIO_PIN_RESET);
  HAL_Delay(5);
  HAL_GPIO_WritePin(ST7735_RESET_PORT, ST7735_RESET_PIN, GPIO_PIN_SET);
  HAL_Delay(5);
    
  ST7735_SendCommand(ST7735_SWRESET);  
  HAL_Delay(150);

  ST7735_SendCommand(ST7735_SLPOUT);  
  HAL_Delay(500);

  ST7735_SendCommand(ST7735_FRMCTR1);
  ST7735_SendData(0x01);
  ST7735_SendData(0x2C);
  ST7735_SendData(0x2D);

  ST7735_SendCommand(ST7735_FRMCTR2);
  ST7735_SendData(0x01);
  ST7735_SendData(0x2C);
  ST7735_SendData(0x2D);

  ST7735_SendCommand(ST7735_FRMCTR3);
  ST7735_SendData(0x01);
  ST7735_SendData(0x2C);
  ST7735_SendData(0x2D);
  ST7735_SendData(0x01);
  ST7735_SendData(0x2C);
  ST7735_SendData(0x2D);

  ST7735_SendCommand(ST7735_INVCTR);
  ST7735_SendData(0x07);

  ST7735_SendCommand(ST7735_PWCTR1);
  ST7735_SendData(0xA2);
  ST7735_SendData(0x02);
  ST7735_SendData(0x84);

  ST7735_SendCommand(ST7735_PWCTR2);
  ST7735_SendData(0xC5);

  ST7735_SendCommand(ST7735_PWCTR3);
  ST7735_SendData(0x0A);
  ST7735_SendData(0x00);

  ST7735_SendCommand(ST7735_PWCTR4);
  ST7735_SendData(0x8A);
  ST7735_SendData(0x2A);

  ST7735_SendCommand(ST7735_PWCTR5);
  ST7735_SendData(0x8A);
  ST7735_SendData(0xEE);

  ST7735_SendCommand(ST7735_VMCTR1);
  ST7735_SendData(0x0E);

  ST7735_SendCommand(ST7735_INVOFF);

  ST7735_SendCommand(ST7735_MADCTL);//ориентация экрана
  ST7735_SendData(0xC0);

  ST7735_SendCommand(ST7735_COLMOD);
  ST7735_SendData(0x05);

  ST7735_SendCommand(ST7735_GMCTRP1);
  ST7735_SendData(0x02);
  ST7735_SendData(0x1c);
  ST7735_SendData(0x07);
  ST7735_SendData(0x12);
  ST7735_SendData(0x37);
  ST7735_SendData(0x32);
  ST7735_SendData(0x29);
  ST7735_SendData(0x2d);
  ST7735_SendData(0x29);
  ST7735_SendData(0x25);
  ST7735_SendData(0x2B);
  ST7735_SendData(0x39);	
  ST7735_SendData(0x00);
  ST7735_SendData(0x01);
  ST7735_SendData(0x03);
  ST7735_SendData(0x10);

  ST7735_SendCommand(ST7735_GMCTRN1);
  ST7735_SendData(0x03);
  ST7735_SendData(0x1d);
  ST7735_SendData(0x07);
  ST7735_SendData(0x06);
  ST7735_SendData(0x2E);
  ST7735_SendData(0x2C);
  ST7735_SendData(0x29);
  ST7735_SendData(0x2D);
  ST7735_SendData(0x2E);
  ST7735_SendData(0x2E);
  ST7735_SendData(0x37);
  ST7735_SendData(0x3F);	
  ST7735_SendData(0x00);
  ST7735_SendData(0x00);
  ST7735_SendData(0x02);
  ST7735_SendData(0x10);

  ST7735_SendCommand(ST7735_NORON);
  HAL_Delay(10);

  ST7735_SendCommand(ST7735_DISPON);
  HAL_Delay(100);

  HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_SET);
	
	TFT9341_FontsIni();
}



/*----------------------------------------------------------------------------*/
void ST7735_SetColAddr(uint16_t cStart, uint16_t cStop)
{
  uint8_t data[4];
  
  data[0] = (cStart & 0xFF00) >> 8;
  data[1] = cStart & 0x00FF;
  data[2] = (cStop & 0xFF00) >> 8;
  data[3] = cStop & 0x00FF;
  
  ST7735_SendCommand(ST7735_CASET);
  ST7735_SendDataMultiple(data, 4);
}



/*----------------------------------------------------------------------------*/
void ST7735_SetRowAddr(uint16_t rStart, uint16_t rStop)
{
  uint8_t data[4];
  
  data[0] = (rStart & 0xFF00) >> 8;
  data[1] = rStart & 0x00FF;
  data[2] = (rStop & 0xFF00) >> 8;
  data[3] = rStop & 0x00FF;

  ST7735_SendCommand(ST7735_RASET);
  ST7735_SendDataMultiple(data, 4);
}



/*----------------------------------------------------------------------------*/
void ST7735_DrawRect(uint16_t cStart, uint16_t rStart, uint16_t cStop, uint16_t rStop, uint16_t color)
{
  HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_RESET);
  ST7735_SetColAddr(cStart, cStop - 1);
  ST7735_SetRowAddr(rStart, rStop - 1);
  
  ST7735_SendCommand(ST7735_RAMWR);
  
  uint32_t size = (cStop - cStart) * (rStop - rStart);
  uint8_t colorBytes[2];
  colorBytes[0] = (color & 0xFF00) >> 8;
  colorBytes[1] = color & 0x00FF;
  
  HAL_GPIO_WritePin(ST7735_DC_PORT, ST7735_DC_PIN, GPIO_PIN_SET);
  
  for (uint32_t i = 0; i < size; i++)
  {
    ST7735_SendByte(colorBytes[0]);
    ST7735_SendByte(colorBytes[1]);
  }
  
  ST7735_WaitLastData();
  HAL_GPIO_WritePin(ST7735_CS_PORT, ST7735_CS_PIN, GPIO_PIN_SET);
}
void ST7735_FillScreen(uint16_t color) {
    ST7735_DrawRect(0, 0, ST7735_X_SIZE, ST7735_Y_SIZE, color);
}

void ST7735_DrawPixel(int x, int y, uint16_t color)
{
	if((x<0)||(y<0)||(x>=ST7735_X_SIZE)||(y>=ST7735_Y_SIZE)) return;
    ST7735_DrawRect(x, y, x+1, y+1, color);
}

//-------------------------------------------------------------------
void ST7735_SetTextColor(uint16_t color)//Функция установки цвета текста
{
  lcdprop.TextColor=color;
}
//------------------------------------
void ST7735_SetBackColor(uint16_t color)//Функция установки цвета заливки
{
  lcdprop.BackColor=color;
}
//------------------------------------
void ST7735_SetFont(sFONT *pFonts)//Функция установки цвета шрифта
{
  lcdprop.pFont=pFonts;
}
//---------------------------------------------------------------
void ST7735_DrawChar(uint16_t x, uint16_t y, uint8_t c)//Функция вывода символа в определённую позицию экрана
{
  uint32_t i = 0, j = 0;
  uint16_t height, width;
  uint8_t offset;
  uint8_t *c_t;
  uint8_t *pchar;
  uint32_t line=0;
  height = lcdprop.pFont->Height;
  width  = lcdprop.pFont->Width;
  offset = 8 *((width + 7)/8) -  width ;
  c_t = (uint8_t*) &(lcdprop.pFont->table[(c-' ') * lcdprop.pFont->Height * ((lcdprop.pFont->Width + 7) / 8)]);
  for(i = 0; i < height; i++)
  {
    pchar = ((uint8_t *)c_t + (width + 7)/8 * i);
    switch(((width + 7)/8))
    {
      case 1:
          line =  pchar[0];      
          break;
      case 2:
          line =  (pchar[0]<< 8) | pchar[1];
          break;
      case 3:
      default:
        line =  (pchar[0]<< 16) | (pchar[1]<< 8) | pchar[2];      
        break;
    }
    for (j = 0; j < width; j++)
    {
      if(line & (1 << (width- j + offset- 1))) 
      {
        ST7735_DrawPixel((x + j), y, lcdprop.TextColor);
      }
      else
      {
        ST7735_DrawPixel((x + j), y, lcdprop.BackColor);
      } 
    }
    y++;      
  }
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
void ST7735_String(uint16_t x,uint16_t y, char *str)//Функция вввода строки в определённую позицию экрана
{
  while(*str)
  {
    ST7735_DrawChar(x,y,str[0]);
    x+=lcdprop.pFont->Width;
    (void)*str++;
  }
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
void ST7735_SetRotation(uint8_t r)//Функция изменения ориентации экрана
{
 ST7735_SendCommand(0x36);
  switch(r)
  {
    case 0:
      ST7735_SendData(0x48);
			ST7735_X_SIZE ;
      ST7735_Y_SIZE ;
      break;
    case 1:
      ST7735_SendData(0x28);
			ST7735_X_SIZE ;
      ST7735_Y_SIZE ;
      break;
    case 2:
      ST7735_SendData(0x88);
      ST7735_X_SIZE ;
      ST7735_Y_SIZE ;
      break;
    case 3:
       ST7735_SendData(0xE8);
      ST7735_X_SIZE ;
      ST7735_Y_SIZE ;
      break;
  }
}
//-------------------------------------------------------
// Вывод картинки из массива
void ST7735_img(uint8_t x, uint8_t y, uint16_t w, uint16_t h, const uint16_t *pix)
{
  
  while(x < h) // Крутимся пока не заполнятся все ряды
  {
    while(y < w)
    {
      ST7735_DrawPixel(x, y, *pix);
      pix++;
      y++;
    }
    y = 0;
    x++;
  } 
}

/*----------------------------------------------------------------------------*/
