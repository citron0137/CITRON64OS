// ������ 256�� ��Ʈ ������, 8x16 pixel 
unsigned char g_vucEnglishFont[] = { 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x18,0x3C,0x7E,0x7E,0x7E,0x3C,0x18,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0xFF,0xE7,0xC3,0x81,0x81,0x81,0xC3,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,
0x00,0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x24,0x18,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0xFF,0xE7,0xDB,0xBD,0xBD,0xBD,0xDB,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,
0x00,0x00,0x1F,0x05,0x05,0x09,0x09,0x10,0x10,0x38,0x44,0x44,0x44,0x38,0x00,0x00,
0x00,0x00,0x1C,0x22,0x22,0x22,0x1C,0x08,0x08,0x7F,0x08,0x08,0x08,0x08,0x00,0x00,
0x00,0x10,0x18,0x14,0x12,0x11,0x11,0x11,0x11,0x12,0x30,0x70,0x70,0x60,0x00,0x00,
0x00,0x03,0x1D,0x11,0x13,0x1D,0x11,0x11,0x11,0x13,0x17,0x36,0x70,0x60,0x00,0x00,
0x00,0x08,0x08,0x5D,0x22,0x22,0x22,0x63,0x22,0x22,0x22,0x5D,0x08,0x08,0x00,0x00,
0x00,0x10,0x10,0x10,0x10,0x10,0x10,0xFE,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,
0x00,0x00,0x02,0x06,0x0E,0x1E,0x3E,0x7E,0x3E,0x1E,0x0E,0x06,0x02,0x00,0x00,0x00,
0x00,0x10,0x38,0x54,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x54,0x38,0x10,0x00,0x00,
0x00,0x00,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x00,0x00,0x24,0x24,0x00,0x00,
0x00,0x00,0x34,0x54,0x54,0x54,0x54,0x54,0x34,0x14,0x14,0x14,0x14,0x14,0x00,0x00,
0x00,0x10,0x10,0x10,0x10,0x10,0x10,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,
0x00,0x10,0x10,0x10,0x10,0x10,0x10,0xF0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,
0x00,0x00,0x10,0x38,0x54,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x1E,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x04,0x7E,0x04,0x08,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x20,0x7E,0x20,0x10,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x50,0x50,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x04,0x04,0x04,0x08,0x3F,0x08,0x11,0x11,0x7F,0x22,0x22,0x22,0x00,0x00,
0x08,0x08,0x3E,0x49,0x49,0x48,0x38,0x0E,0x09,0x09,0x49,0x49,0x3E,0x08,0x08,0x00,
0x00,0x00,0x38,0x44,0x44,0x44,0x39,0x01,0x02,0x04,0x04,0x08,0x10,0x10,0x00,0x00,
0x00,0x1C,0x22,0x22,0x22,0x14,0x18,0x24,0x42,0x41,0x41,0x22,0x1C,0x00,0x00,0x00,
0x00,0x00,0x20,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x08,0x10,0x20,0x20,0x40,0x40,0x40,0x40,0x40,0x40,0x20,0x20,0x10,0x08,0x00,
0x00,0x40,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x20,0x40,0x00,
0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x7C,0x10,0x28,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x7F,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x40,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x00,0x00,
0x00,0x00,0x04,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x40,0x40,0x80,0x80,0x00,0x00,
0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x22,0x1C,0x00,0x00,
0x00,0x00,0x08,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
0x00,0x00,0x1C,0x22,0x41,0x41,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x7F,0x00,0x00,
0x00,0x00,0x1C,0x22,0x41,0x01,0x02,0x1C,0x02,0x01,0x01,0x41,0x22,0x1C,0x00,0x00,
0x00,0x00,0x06,0x0A,0x0A,0x12,0x12,0x22,0x22,0x42,0x7F,0x02,0x02,0x02,0x00,0x00,
0x00,0x00,0x7F,0x40,0x40,0x40,0x5C,0x62,0x41,0x01,0x01,0x41,0x22,0x1C,0x00,0x00,
0x00,0x00,0x1C,0x22,0x41,0x40,0x5C,0x62,0x41,0x41,0x41,0x41,0x22,0x1C,0x00,0x00,
0x00,0x00,0x7F,0x01,0x02,0x04,0x04,0x08,0x08,0x08,0x10,0x10,0x10,0x10,0x00,0x00,
0x00,0x00,0x1C,0x22,0x41,0x41,0x22,0x1C,0x22,0x41,0x41,0x41,0x22,0x1C,0x00,0x00,
0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x23,0x1D,0x01,0x41,0x22,0x1C,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x20,0x00,0x00,0x00,0x20,0x20,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x20,0x00,0x00,0x00,0x20,0x20,0x40,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x10,0x08,0x04,0x02,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,0x00,
0x00,0x00,0x3C,0x42,0x42,0x02,0x04,0x08,0x10,0x10,0x00,0x00,0x10,0x10,0x00,0x00,
0x00,0x00,0x07,0x08,0x10,0x26,0x29,0x51,0x51,0x52,0x4D,0x40,0x20,0x1F,0x00,0x00,
0x00,0x00,0x04,0x04,0x0A,0x0A,0x11,0x11,0x11,0x20,0x3F,0x20,0x40,0x40,0x00,0x00,
0x00,0x00,0x7E,0x41,0x41,0x41,0x42,0x7E,0x41,0x40,0x40,0x40,0x41,0x7E,0x00,0x00,
0x00,0x00,0x0F,0x10,0x20,0x40,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x0F,0x00,0x00,
0x00,0x00,0x7C,0x42,0x41,0x40,0x40,0x40,0x40,0x40,0x40,0x41,0x42,0x7C,0x00,0x00,
0x00,0x00,0x7F,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x7F,0x00,0x00,
0x00,0x00,0x7F,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,
0x00,0x00,0x0F,0x10,0x20,0x40,0x40,0x40,0x43,0x40,0x40,0x20,0x11,0x0E,0x00,0x00,
0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,
0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,
0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x88,0x88,0x70,0x00,0x00,
0x00,0x00,0x40,0x41,0x42,0x44,0x48,0x50,0x68,0x44,0x42,0x41,0x40,0x40,0x00,0x00,
0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x00,0x00,
0x00,0x00,0x40,0x40,0x60,0x60,0x50,0x50,0x48,0x48,0x45,0x45,0x42,0x42,0x00,0x00,
0x00,0x00,0x40,0x60,0x50,0x50,0x48,0x44,0x44,0x42,0x41,0x41,0x40,0x40,0x00,0x00,
0x00,0x00,0x0F,0x10,0x20,0x40,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x0F,0x00,0x00,
0x00,0x00,0x7E,0x41,0x40,0x40,0x40,0x41,0x7E,0x40,0x40,0x40,0x40,0x40,0x00,0x00,
0x00,0x00,0x0F,0x10,0x20,0x40,0x40,0x40,0x40,0x40,0x40,0x21,0x10,0x0F,0x00,0x00,
0x00,0x00,0x7E,0x41,0x40,0x40,0x40,0x41,0x7E,0x41,0x40,0x40,0x40,0x40,0x00,0x00,
0x00,0x00,0x1E,0x21,0x40,0x40,0x20,0x1C,0x03,0x00,0x00,0x40,0x21,0x1E,0x00,0x00,
0x00,0x00,0xFF,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,
0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x20,0x1F,0x00,0x00,
0x00,0x00,0x40,0x40,0x20,0x20,0x20,0x11,0x11,0x11,0x0A,0x0A,0x04,0x04,0x00,0x00,
0x00,0x00,0x41,0x41,0x41,0x22,0x22,0x22,0x14,0x14,0x14,0x08,0x08,0x08,0x00,0x00,
0x00,0x00,0x40,0x40,0x20,0x11,0x0A,0x04,0x04,0x0A,0x11,0x20,0x40,0x40,0x00,0x00,
0x00,0x00,0x40,0x40,0x20,0x11,0x11,0x0A,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,
0x00,0x00,0x7F,0x00,0x01,0x02,0x02,0x04,0x08,0x10,0x10,0x20,0x40,0x7F,0x00,0x00,
0x00,0x1C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1C,0x00,
0x00,0x00,0x21,0x21,0x21,0x22,0x7F,0x22,0x14,0x14,0x14,0x08,0x08,0x08,0x00,0x00,
0x00,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x38,0x00,
0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,
0x00,0x40,0x20,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3E,0x41,0x01,0x1F,0x21,0x41,0x41,0x41,0x3E,0x00,0x00,
0x00,0x00,0x40,0x40,0x40,0x5C,0x62,0x41,0x41,0x41,0x41,0x41,0x62,0x5C,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x1E,0x21,0x40,0x40,0x40,0x40,0x40,0x21,0x1E,0x00,0x00,
0x00,0x00,0x01,0x01,0x01,0x1D,0x23,0x41,0x41,0x41,0x41,0x41,0x23,0x1D,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x7F,0x40,0x40,0x21,0x1E,0x00,0x00,
0x00,0x00,0x18,0x20,0x20,0xF8,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x1D,0x23,0x41,0x41,0x41,0x41,0x23,0x1D,0x01,0x42,0x3C,
0x00,0x00,0x40,0x40,0x40,0x5E,0x61,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x00,0x00,
0x00,0x00,0x40,0x40,0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,
0x00,0x00,0x20,0x20,0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xC0,
0x00,0x00,0x40,0x40,0x40,0x42,0x44,0x48,0x50,0x70,0x48,0x44,0x42,0x41,0x00,0x00,
0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x5C,0x63,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x5E,0x61,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x1E,0x21,0x40,0x40,0x40,0x40,0x40,0x21,0x1E,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x5C,0x62,0x41,0x41,0x41,0x41,0x41,0x62,0x5C,0x40,0x40,
0x00,0x00,0x00,0x00,0x00,0x1D,0x23,0x41,0x41,0x41,0x41,0x41,0x23,0x1D,0x01,0x01,
0x00,0x00,0x00,0x00,0x00,0x58,0x60,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3E,0x41,0x41,0x30,0x0C,0x02,0x41,0x41,0x3E,0x00,0x00,
0x00,0x00,0x20,0x20,0x20,0xF8,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x18,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x43,0x3D,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x41,0x41,0x41,0x22,0x22,0x14,0x14,0x08,0x08,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x44,0x44,0x44,0x2A,0x2A,0x2A,0x11,0x11,0x11,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x41,0x41,0x22,0x14,0x08,0x14,0x22,0x41,0x41,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x41,0x41,0x41,0x22,0x22,0x14,0x14,0x08,0x08,0x10,0x60,
0x00,0x00,0x00,0x00,0x00,0x7F,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x7F,0x00,0x00,
0x00,0x06,0x08,0x08,0x08,0x08,0x08,0x30,0x08,0x08,0x08,0x08,0x08,0x08,0x06,0x00,
0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x00,0x30,0x08,0x08,0x08,0x08,0x08,0x06,0x08,0x08,0x08,0x08,0x08,0x08,0x30,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x43,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x7E,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x7E,0x00,0x00,
0x00,0x00,0x00,0x0F,0x10,0x20,0x20,0x7F,0x20,0x7F,0x20,0x20,0x10,0x0F,0x00,0x00,
0x00,0x00,0x00,0xE0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xE0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x40,0x00,
0x00,0x00,0x00,0x06,0x08,0x08,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x48,0x30,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x24,0x24,0x48,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x08,0x08,0x08,0x08,0x7F,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
0x00,0x08,0x08,0x08,0x7F,0x08,0x08,0x08,0x08,0x08,0x08,0x7F,0x08,0x08,0x08,0x00,
0x00,0x10,0x28,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x30,0x48,0x48,0x49,0x4A,0x35,0x0A,0x12,0x22,0x42,0x01,0x00,0x00,
0x11,0x0A,0x04,0x1F,0x20,0x40,0x40,0x30,0x0E,0x01,0x00,0x40,0x20,0x1F,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x08,0x10,0x20,0x10,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x0F,0x11,0x21,0x41,0x41,0x41,0x41,0x41,0x21,0x11,0x0F,0x00,0x00,
0x00,0x00,0x00,0xE0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xE0,0x00,0x00,0x00,
0x11,0x0A,0x04,0x7F,0x00,0x01,0x02,0x04,0x04,0x08,0x10,0x20,0x40,0x7F,0x00,0x00,
0x00,0x00,0x00,0xE0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xE0,0x00,0x00,0x00,
0x00,0x00,0x00,0xE0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xE0,0x00,0x00,0x00,
0x00,0x20,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x20,0x20,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x24,0x48,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x24,0x24,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x1C,0x3E,0x3E,0x3E,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x32,0x4C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x22,0x14,0x08,0x00,0x3E,0x41,0x40,0x30,0x0C,0x02,0x01,0x41,0x3E,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x20,0x10,0x08,0x10,0x20,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x22,0x1C,0x00,0x00,
0x00,0x00,0x00,0xE0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xE0,0x00,0x00,0x00,
0x00,0x22,0x14,0x08,0x00,0x7E,0x02,0x04,0x08,0x08,0x10,0x20,0x40,0x7E,0x00,0x00,
0x00,0x0A,0x00,0x40,0x40,0x20,0x11,0x11,0x0A,0x04,0x04,0x04,0x04,0x04,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x10,0x10,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x00,0x00,0x00,0x01,0x01,0x1E,0x23,0x44,0x44,0x48,0x48,0x50,0x31,0x3E,0x20,0x00,
0x00,0x00,0x00,0x0E,0x11,0x21,0x20,0x20,0x7F,0x10,0x10,0x71,0x99,0x66,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x5D,0x22,0x41,0x41,0x41,0x22,0x5D,0x00,0x00,0x00,
0x00,0x00,0x00,0x40,0x40,0x20,0x11,0x7F,0x0A,0x7F,0x04,0x04,0x04,0x04,0x00,0x00,
0x00,0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x20,
0x00,0x1C,0x22,0x22,0x10,0x08,0x14,0x22,0x22,0x22,0x14,0x08,0x04,0x22,0x22,0x1C,
0x00,0x00,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x07,0x18,0x23,0x24,0x48,0x48,0x48,0x48,0x24,0x23,0x18,0x07,0x00,0x00,
0x00,0x00,0x30,0x48,0x38,0x48,0x34,0x00,0x7C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x12,0x24,0x48,0x24,0x12,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x07,0x18,0x27,0x28,0x48,0x48,0x4F,0x48,0x28,0x28,0x18,0x07,0x00,0x00,
0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x30,0x48,0x48,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x02,0x02,0x02,0x02,0x7F,0x02,0x02,0x02,0x02,0x00,0x7F,0x00,0x00,0x00,
0x00,0x00,0x00,0x30,0x48,0x08,0x10,0x20,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x30,0x48,0x10,0x08,0x48,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x18,0x10,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x63,0x5D,0x40,0x40,
0x00,0x00,0x00,0x1F,0x3D,0x7D,0x7D,0x3D,0x1D,0x05,0x05,0x05,0x05,0x05,0x05,0x05,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x60,0x10,0x60,
0x00,0x00,0x00,0x00,0x10,0x30,0x10,0x10,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x38,0x44,0x44,0x44,0x38,0x00,0x7C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x48,0x24,0x12,0x24,0x48,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x08,0x18,0x08,0x08,0x08,0x08,0x7E,0x08,0x18,0x28,0x28,0x7C,0x08,
0x00,0x00,0x00,0x08,0x18,0x08,0x08,0x08,0x08,0x7E,0x18,0x24,0x24,0x08,0x10,0x3C,
0x00,0x00,0x00,0x18,0x24,0x08,0x04,0x24,0x18,0x7E,0x08,0x18,0x28,0x28,0x7C,0x08,
0x00,0x00,0x00,0x08,0x08,0x00,0x08,0x08,0x08,0x10,0x20,0x40,0x41,0x41,0x22,0x1C,
0x0C,0x04,0x02,0x04,0x04,0x0A,0x0A,0x11,0x11,0x20,0x3F,0x40,0x40,0x40,0x00,0x00,
0x0C,0x08,0x10,0x04,0x04,0x0A,0x0A,0x11,0x11,0x20,0x3F,0x40,0x40,0x40,0x00,0x00,
0x04,0x0A,0x11,0x04,0x04,0x0A,0x0A,0x11,0x11,0x20,0x3F,0x40,0x40,0x40,0x00,0x00,
0x19,0x26,0x00,0x04,0x04,0x0A,0x0A,0x11,0x11,0x20,0x3F,0x40,0x40,0x40,0x00,0x00,
0x00,0x11,0x00,0x04,0x04,0x0A,0x0A,0x11,0x11,0x20,0x3F,0x40,0x40,0x40,0x00,0x00,
0x0C,0x12,0x0C,0x04,0x04,0x0A,0x0A,0x11,0x11,0x20,0x3F,0x40,0x40,0x40,0x00,0x00,
0x00,0x00,0x00,0x03,0x05,0x05,0x09,0x09,0x11,0x1F,0x21,0x21,0x41,0x40,0x00,0x00,
0x00,0x00,0x00,0x0F,0x10,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x0F,0x01,0x06,
0x0C,0x04,0x02,0x3F,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x3F,0x00,0x00,
0x06,0x04,0x08,0x3F,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x3F,0x00,0x00,
0x04,0x0A,0x11,0x3F,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x3F,0x00,0x00,
0x00,0x11,0x00,0x3F,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x3F,0x00,0x00,
0x60,0x20,0x10,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,
0x30,0x20,0x40,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,
0x20,0x50,0x88,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,
0x00,0x50,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,
0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0xFC,0x20,0x20,0x20,0x20,0x1F,0x00,0x00,
0x0C,0x13,0x00,0x40,0x60,0x50,0x48,0x44,0x42,0x42,0x41,0x40,0x40,0x40,0x00,0x00,
0x0C,0x04,0x02,0x0F,0x10,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x0F,0x00,0x00,
0x03,0x02,0x04,0x0F,0x10,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x0F,0x00,0x00,
0x02,0x05,0x08,0x0F,0x10,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x0F,0x00,0x00,
0x0C,0x13,0x00,0x0F,0x10,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x0F,0x00,0x00,
0x00,0x08,0x00,0x0F,0x10,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x0F,0x00,0x00,
0x00,0x00,0x00,0x20,0x10,0x08,0x05,0x02,0x05,0x08,0x10,0x20,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x0F,0x10,0x20,0x41,0x41,0x42,0x44,0x44,0x28,0x10,0x2F,0x20,0x00,
0x0C,0x04,0x02,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x20,0x1F,0x00,0x00,
0x06,0x04,0x08,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x20,0x1F,0x00,0x00,
0x06,0x09,0x10,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x20,0x1F,0x00,0x00,
0x00,0x09,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x20,0x1F,0x00,0x00,
0x06,0x04,0x08,0x40,0x20,0x11,0x11,0x0A,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,
0x00,0x00,0x40,0x40,0x7E,0x41,0x40,0x40,0x40,0x40,0x41,0x7E,0x40,0x40,0x00,0x00,
0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x46,0x41,0x40,0x40,0x40,0x51,0x4E,0x00,0x00,
0x00,0x18,0x08,0x04,0x00,0x3E,0x41,0x01,0x0F,0x31,0x41,0x41,0x41,0x3E,0x00,0x00,
0x00,0x0C,0x08,0x10,0x00,0x3E,0x41,0x01,0x0F,0x31,0x41,0x41,0x41,0x3E,0x00,0x00,
0x00,0x08,0x14,0x22,0x00,0x3E,0x41,0x01,0x0F,0x31,0x41,0x41,0x41,0x3E,0x00,0x00,
0x00,0x00,0x19,0x26,0x00,0x3E,0x41,0x01,0x0F,0x31,0x41,0x41,0x41,0x3E,0x00,0x00,
0x00,0x00,0x00,0x12,0x00,0x3E,0x41,0x01,0x0F,0x31,0x41,0x41,0x41,0x3E,0x00,0x00,
0x00,0x0C,0x12,0x0C,0x00,0x3E,0x41,0x01,0x0F,0x31,0x41,0x41,0x41,0x3E,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3D,0x42,0x02,0x1F,0x22,0x42,0x42,0x42,0x3D,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x1E,0x21,0x40,0x40,0x40,0x40,0x40,0x21,0x1E,0x04,0x18,
0x00,0x18,0x08,0x04,0x00,0x1C,0x22,0x41,0x41,0x7F,0x40,0x40,0x21,0x1E,0x00,0x00,
0x00,0x0C,0x08,0x10,0x00,0x1C,0x22,0x41,0x41,0x7F,0x40,0x40,0x21,0x1E,0x00,0x00,
0x00,0x08,0x14,0x22,0x00,0x1C,0x22,0x41,0x41,0x7F,0x40,0x40,0x21,0x1E,0x00,0x00,
0x00,0x00,0x00,0x12,0x00,0x1C,0x22,0x41,0x41,0x7F,0x40,0x40,0x21,0x1E,0x00,0x00,
0x00,0x00,0x60,0x20,0x10,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,
0x00,0x00,0x30,0x20,0x40,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,
0x00,0x00,0x00,0x20,0x50,0x88,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,
0x00,0x00,0x00,0x50,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,
0x00,0x00,0x00,0x0B,0x04,0x1A,0x01,0x1F,0x21,0x40,0x40,0x40,0x21,0x1E,0x00,0x00,
0x00,0x00,0x32,0x4C,0x00,0x5C,0x62,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x00,0x00,
0x00,0x0C,0x04,0x02,0x00,0x1E,0x21,0x40,0x40,0x40,0x40,0x40,0x21,0x1E,0x00,0x00,
0x00,0x06,0x04,0x08,0x00,0x1E,0x21,0x40,0x40,0x40,0x40,0x40,0x21,0x1E,0x00,0x00,
0x00,0x04,0x0A,0x11,0x00,0x1E,0x21,0x40,0x40,0x40,0x40,0x40,0x21,0x1E,0x00,0x00,
0x00,0x00,0x19,0x26,0x00,0x1E,0x21,0x40,0x40,0x40,0x40,0x40,0x21,0x1E,0x00,0x00,
0x00,0x00,0x00,0x12,0x00,0x1E,0x21,0x40,0x40,0x40,0x40,0x40,0x21,0x1E,0x00,0x00,
0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x1E,0x21,0x42,0x44,0x44,0x48,0x50,0x21,0x5E,0x00,0x00,
0x00,0x18,0x08,0x04,0x00,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x23,0x1D,0x00,0x00,
0x00,0x0C,0x08,0x10,0x00,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x23,0x1D,0x00,0x00,
0x00,0x08,0x14,0x22,0x00,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x23,0x1D,0x00,0x00,
0x00,0x00,0x00,0x12,0x00,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x23,0x1D,0x00,0x00,
0x00,0x0C,0x08,0x10,0x00,0x42,0x42,0x42,0x24,0x24,0x18,0x18,0x10,0x10,0x20,0x40,
0x00,0x00,0x00,0x40,0x40,0x5E,0x61,0x40,0x40,0x40,0x40,0x40,0x61,0x5E,0x40,0x40,
0x00,0x00,0x00,0x24,0x00,0x42,0x42,0x42,0x24,0x24,0x18,0x18,0x10,0x10,0x20,0x40};