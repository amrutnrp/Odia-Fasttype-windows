

//key_press prev_char prev_length
//--shift?_input bksp?_output
//--new_length result
const int max_width = 14;
const int len_pos = max_width - 6 -1;


const int LUT[][14]= {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0x46,0,0,0,0,0,0,1,0xb4d,0,0,0,0,0},
{0x48,0,0,0,0,0,0,1,0xb39,0,0,0,0,0},
{0x48,0x200d,1,0,1,0,0,1,0xb39,0,0,0,0,0},
{0x41,0,0,0,0,1,0,1,0xb3e,0,0,0,0,0},
{0x41,0,0,0,0,0,0,1,0xb05,0,0,0,0,0},
{0x41,0xb05,1,0,1,0,0,1,0xb06,0,0,0,0,0},
{0x41,0,0,1,0,0,0,1,0xb06,0,0,0,0,0},
{0xbf,0xb05,1,0,1,0,0,1,0xb06,0,0,0,0,0},
{0x41,0xb3e,1,0,1,0,0,1,0xb3e,0,0,0,0,0},
{0x41,0x200d,1,0,1,0,0,1,0xb06,0,0,0,0,0},
{0x45,0,0,0,0,1,0,1,0xb47,0,0,0,0,0},
{0x45,0,0,0,0,0,0,1,0xb0f,0,0,0,0,0},
{0x45,0,0,1,0,0,0,1,0xb10,0,0,0,0,0},
{0xbf,0xb0f,1,0,1,0,0,1,0xb10,0,0,0,0,0},
{0xbf,0xb47,1,0,1,0,0,1,0xb48,0,0,0,0,0},
{0x45,0x200d,1,0,1,0,0,1,0xb0f,0,0,0,0,0},
{0x49,0,0,0,0,1,0,1,0xb3f,0,0,0,0,0},
{0x49,0,0,0,0,0,0,1,0xb07,0,0,0,0,0},
{0x49,0,0,1,0,0,0,1,0xb08,0,0,0,0,0},
{0xbf,0xb07,1,0,1,0,0,1,0xb08,0,0,0,0,0},
{0xbf,0xb3f,1,0,1,0,0,1,0xb40,0,0,0,0,0},
{0x49,0x200d,1,0,1,0,0,1,0xb07,0,0,0,0,0},
{0x4f,0,0,0,0,1,0,1,0xb4b,0,0,0,0,0},
{0x4f,0,0,0,0,0,0,1,0xb13,0,0,0,0,0},
{0x4f,0,0,1,0,0,0,1,0xb14,0,0,0,0,0},
{0xbf,0xb13,1,0,1,0,0,1,0xb14,0,0,0,0,0},
{0xbf,0xb4b,1,0,1,0,0,1,0xb4c,0,0,0,0,0},
{0x4f,0x200d,1,0,1,0,0,1,0xb13,0,0,0,0,0},
{0x55,0,0,0,0,1,0,1,0xb41,0,0,0,0,0},
{0x55,0,0,0,0,0,0,1,0xb09,0,0,0,0,0},
{0x55,0,0,1,0,0,0,1,0xb0a,0,0,0,0,0},
{0xbf,0xb09,1,0,1,0,0,1,0xb0a,0,0,0,0,0},
{0xbf,0xb41,1,0,1,0,0,1,0xb42,0,0,0,0,0},
{0x55,0x200d,1,0,1,0,0,1,0xb09,0,0,0,0,0},
{0x41,0xb3e,1,0,1,0,0,1,0xb06,0,0,0,0,0},
{0x4f,0xb3e,1,0,1,0,0,1,0xb05,0,0,0,0,0},
{0x49,0xb3e,1,0,1,0,0,1,0xb48,0,0,0,0,0},
{0x55,0xb3e,1,0,1,0,0,1,0xb4c,0,0,0,0,0},
{0x49,0xb47,1,0,1,0,0,1,0xb48,0,0,0,0,0},
{0x55,0xb4b,1,0,1,0,0,1,0xb4c,0,0,0,0,0},
{0x45,0xb47,1,0,1,0,0,1,0xb40,0,0,0,0,0},
{0x4f,0xb4b,1,0,1,0,0,1,0xb42,0,0,0,0,0},
{0x49,0xb3f,1,0,1,0,0,1,0xb40,0,0,0,0,0},
{0x55,0xb41,1,0,1,0,0,1,0xb42,0,0,0,0,0},
{0x46,0xb05,1,0,1,0,0,1,0xb3e,0,0,0,0,0},
{0x46,0xb0f,1,0,1,0,0,1,0xb47,0,0,0,0,0},
{0x46,0xb07,1,0,1,0,0,1,0xb3f,0,0,0,0,0},
{0x46,0xb13,1,0,1,0,0,1,0xb4b,0,0,0,0,0},
{0x46,0xb09,1,0,1,0,0,1,0xb41,0,0,0,0,0},
{0x30,0,0,0,0,0,0,1,0xb66,0,0,0,0,0},
{0x31,0,0,0,0,0,0,1,0xb67,0,0,0,0,0},
{0x32,0,0,0,0,0,0,1,0xb68,0,0,0,0,0},
{0x33,0,0,0,0,0,0,1,0xb69,0,0,0,0,0},
{0x34,0,0,0,0,0,0,1,0xb6a,0,0,0,0,0},
{0x35,0,0,0,0,0,0,1,0xb6b,0,0,0,0,0},
{0x36,0,0,0,0,0,0,1,0xb6c,0,0,0,0,0},
{0x37,0,0,0,0,0,0,1,0xb6d,0,0,0,0,0},
{0x38,0,0,0,0,0,0,1,0xb6e,0,0,0,0,0},
{0x39,0,0,0,0,0,0,1,0xb6f,0,0,0,0,0},
{0xbe,0,0,0,0,0,0,2,0x20,0x964,0,0,0,0},
{0xc0,0,0,1,0,0,0,1,0xb70,0,0,0,0,0},
{0xdb,0,0,0,0,0,0,1,0x200d,0,0,0,0,0},
{0xc0,0,0,0,0,0,0,1,0xb4d,0,0,0,0,0},
{0xbe,0x964,1,0,1,0,0,1,0x965,0,0,0,0,0},
{0x42,0,0,0,0,0,1,1,0xb2c,0,0,0,0,0},
{0x43,0,0,0,0,0,1,1,0xb1a,0,0,0,0,0},
{0x44,0,0,0,0,0,1,1,0xb26,0,0,0,0,0},
{0x47,0,0,0,0,0,1,1,0xb17,0,0,0,0,0},
{0x4a,0,0,0,0,0,1,1,0xb1c,0,0,0,0,0},
{0x4b,0,0,0,0,0,1,1,0xb15,0,0,0,0,0},
{0x4c,0,0,0,0,0,1,1,0xb32,0,0,0,0,0},
{0x4d,0,0,0,0,0,1,1,0xb2e,0,0,0,0,0},
{0x4e,0,0,0,0,0,1,1,0xb28,0,0,0,0,0},
{0x50,0,0,0,0,0,1,1,0xb2a,0,0,0,0,0},
{0x51,0,0,0,0,0,1,1,0xb24,0,0,0,0,0},
{0x52,0,0,0,0,0,1,1,0xb30,0,0,0,0,0},
{0x53,0,0,0,0,0,1,1,0xb38,0,0,0,0,0},
{0x54,0,0,0,0,0,1,1,0xb1f,0,0,0,0,0},
{0x56,0,0,0,0,0,1,1,0xb21,0,0,0,0,0},
{0x57,0,0,0,0,0,1,1,0xb71,0,0,0,0,0},
{0x58,0,0,0,0,0,1,3,0xb15,0xb4d,0xb37,0,0,0},
{0x59,0,0,0,0,0,1,1,0xb5f,0,0,0,0,0},
{0x5a,0,0,0,0,0,1,1,0xb2f,0,0,0,0,0},
{0x42,0,0,1,0,0,1,3,0xb2e,0xb4d,0xb2c,0,0,0},
{0x43,0,0,1,0,0,1,3,0xb1e,0xb4d,0xb1a,0,0,0},
{0x44,0,0,1,0,0,1,3,0xb28,0xb4d,0xb26,0,0,0},
{0x46,0,0,1,0,0,1,1,0xb3c,0,0,0,0,0},
{0x47,0,0,1,0,0,1,3,0xb19,0xb4d,0xb17,0,0,0},
{0x48,0,0,1,0,0,1,1,0xb39,0,0,0,0,0},
{0x4a,0,0,1,0,0,1,3,0xb1e,0xb4d,0xb1c,0,0,0},
{0x4b,0,0,1,0,0,1,3,0xb19,0xb4d,0xb15,0,0,0},
{0x4c,0,0,1,0,0,1,1,0xb33,0,0,0,0,0},
{0x4d,0,0,1,0,0,0,1,0xb02,0,0,0,0,0},
{0x4e,0,0,1,0,0,1,1,0xb23,0,0,0,0,0},
{0x50,0,0,1,0,0,1,3,0xb2e,0xb4d,0xb2a,0,0,0},
{0x51,0,0,1,0,0,1,3,0xb28,0xb4d,0xb24,0,0,0},
{0x52,0,0,1,0,0,0,1,0xb43,0,0,0,0,0},
{0x53,0,0,1,0,0,1,1,0xb37,0,0,0,0,0},
{0x54,0,0,1,0,0,1,3,0xb23,0xb4d,0xb1f,0,0,0},
{0x56,0,0,1,0,0,1,3,0xb23,0xb4d,0xb21,0,0,0},
{0x57,0,0,1,0,0,0,1,0xb01,0,0,0,0,0},
{0x58,0,0,1,0,0,1,1,0xb5d,0,0,0,0,0},
{0x59,0,0,1,0,0,0,1,0xb73,0,0,0,0,0},
{0x5a,0,0,1,0,0,1,1,0xb5c,0,0,0,0,0},
{0x48,0xb2c,1,0,1,0,1,1,0xb2d,0,0,0,0,0},
{0x48,0xb1a,1,0,1,0,1,1,0xb1b,0,0,0,0,0},
{0x48,0xb26,1,0,1,0,1,1,0xb27,0,0,0,0,0},
{0x48,0xb17,1,0,1,0,1,1,0xb18,0,0,0,0,0},
{0x48,0xb1c,1,0,1,0,1,1,0xb1d,0,0,0,0,0},
{0x48,0xb15,1,0,1,0,1,1,0xb16,0,0,0,0,0},
{0x48,0xb32,1,0,1,0,1,3,0xb32,0xb4d,0xb32,0,0,0},
{0x48,0xb2a,1,0,1,0,1,1,0xb2b,0,0,0,0,0},
{0x48,0xb24,1,0,1,0,1,1,0xb25,0,0,0,0,0},
{0x48,0xb30,1,0,1,0,1,1,0xb60,0,0,0,0,0},
{0x48,0xb38,1,0,1,0,1,1,0xb36,0,0,0,0,0},
{0x48,0xb1f,1,0,1,0,1,1,0xb20,0,0,0,0,0},
{0x48,0xb21,1,0,1,0,1,1,0xb22,0,0,0,0,0},
{0x48,0xb71,1,0,1,0,1,1,0xb35,0,0,0,0,0},
{0xbf,0xb1a,1,0,1,0,1,1,0xb1e,0,0,0,0,0},
{0xbf,0xb17,1,0,1,0,1,1,0xb19,0,0,0,0,0},
{0xbf,0xb1c,1,0,1,0,1,1,0xb1e,0,0,0,0,0},
{0xbf,0xb15,1,0,1,0,1,1,0xb19,0,0,0,0,0},
{0xbf,0xb32,1,0,1,0,1,1,0xb0c,0,0,0,0,0},
{0xbf,0xb28,1,0,1,0,1,3,0xb23,0xb4d,0xb23,0,0,0},
{0xbf,0xb30,1,0,1,0,1,1,0xb43,0,0,0,0,0},
{0xbf,0xb38,1,0,1,0,1,3,0xb37,0xb4d,0xb23,0,0,0},
{0xbf,0xb39,1,0,1,0,1,1,0xb03,0,0,0,0,0},
{0xbf,0xb37,3,0,1,0,1,3,0xb1c,0xb4d,0xb1e,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

const int max_length = 130;