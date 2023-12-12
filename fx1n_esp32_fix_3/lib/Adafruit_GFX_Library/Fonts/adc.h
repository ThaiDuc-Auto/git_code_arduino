const uint8_t adcBitmaps[] PROGMEM =
{
  
};

const GFXglyph adcGlyphs[] PROGMEM =
{
    { 0,  11,  16,  14,    2,  -15 } 
};

const GFXfont adc PROGMEM =
{
  (uint8_t*)adcBitmaps,
  (GFXglyph*)adcGlyphs,
  0x20, 0xFF, 20
};

// Approx. 21 bytes
