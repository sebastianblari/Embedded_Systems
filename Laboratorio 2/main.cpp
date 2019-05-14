#include "main.hpp"

//----------------------------------------------------------------
/* Clear display and redraw Status */
void LCD_DrawStatus()
{
    Graphics_clearDisplay(&g_sContext);
    LCD_DrawRectangle(64);

    Graphics_drawStringCentered(&g_sContext, (int8_t *)"NIVELADO:",
                                AUTO_STRING_LENGTH, 64, 30, OPAQUE_TEXT);
}

//----------------------------------------------------------------
/* Clear display and redraw title + accelerometer data */
void LCD_DrawTitle()
{
    //Graphics_clearDisplay(&g_sContext);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)"Accelerometer:",
                                    AUTO_STRING_LENGTH,
                                    64,
                                    30,
                                    OPAQUE_TEXT);
    LCD_DrawAccelData();
}

//----------------------------------------------------------------
/* Redraw accelerometer data */
void LCD_DrawAccelData()
{
    char string[10];
    sprintf(string, "X: %5d", resultsBuffer[0]);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)string,
                                    8,
                                    64,
                                    50,
                                    OPAQUE_TEXT);

    sprintf(string, "Y: %5d", resultsBuffer[1]);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)string,
                                    8,
                                    64,
                                    70,
                                    OPAQUE_TEXT);

    sprintf(string, "Z: %5d", resultsBuffer[2]);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)string,
                                    8,
                                    64,
                                    90,
                                    OPAQUE_TEXT);

}

//----------------------------------------------------------------
//Cambiar yInitPosition segun lectura acelerometro
void LCD_DrawRectangle(const int yInitPosition)
{
    //draws blue part
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
    Graphics_Rectangle t_Rectangle2 = {0,yInitPosition,128,128};
    Graphics_fillRectangle(&g_sContext, &t_Rectangle2);

    //draws brown part
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    Graphics_Rectangle t_Rectangle1 = {0,0,128,yInitPosition};
    Graphics_fillRectangle(&g_sContext, &t_Rectangle1);

    //draws white line
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_drawLine(&g_sContext, 0, 128, 128, 0);

    //displays info (para debugging)

    //Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    //Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
    //LCD_DrawAccelData();
    //LCD_DrawTitle();
    return;
}

//----------------------------------------------------------------
int main(void)
{
    /* Halting WDT and disabling master interrupts */
    MAP_WDT_A_holdTimer();
    MAP_Interrupt_disableMaster();

    Power_up();

    /* Triggering the start of the sample */
    MAP_ADC14_enableConversion();
    MAP_ADC14_toggleConversionTrigger();

    //LCD_DrawRectangle(64);

    while(1)
    {
        MAP_PCM_gotoLPM0();
    }
}
