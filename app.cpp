#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <iostream>
#include <unistd.h>
#include "keymap.cpp"

int find_LUT_index( int    key_ch,
                    int     prev_unicode,
                    int     last_unicode_length,
                    bool    is_Capital,
                    bool    Condition_Key_Multiple

                      )
{
//std::cout<< "CAPITAL: :   "<<is_Capital <<std::endl;
 int i=0;
 int found0 =0;
 int found1 = 0;
 int found2 = 0;
 bool cap_match ;
 bool is_key_reqd = true ;
 for (;i<max_length; i++)
 {
    if (LUT[i][0] == key_ch)
    {
        cap_match = (   (( LUT[i][3] == 1 ) ^ (is_Capital == true) ) == false );
        is_key_reqd =  ( LUT[i][5] == 1 ) ? (Condition_Key_Multiple == 1) : true;
        if (found0 == 0 && cap_match  && is_key_reqd) {
            found0 = i;
        }
        else if (( LUT[i][1] == prev_unicode) && cap_match && is_key_reqd  ){ // adding else doesn't make any difference
            if (found1 == 0){
                found1 = i;
            }
            else if (LUT[i][2]==last_unicode_length)  {
                found2 = i;
                break;
            }
        }
    }
 }
//std::cout  <<"\n<<" << key_ch << " " << found0 <<" \n" ;
//std::cout  <<"  " << found2 << " " << found1 <<" "<<  found0 << ">>" ;
 if (found2 != 0){
    return found2;  // incase of not found, it'll just return 00, which is used for not-found data
 }
 else if(found1 != 0){
    return found1;
 }
 else {
    return found0;
 }
}



HHOOK hHook{ NULL };
int LUTindex;
long int bkp_idx;
int last_Unicode = 0, last_Unicode_length = 0, many_condition_key= 0, len_backup1;
bool a,b,c,d,e , cursor_changed , switch_to_eng = false, is_shift_pressed, is_cap_pressed, is_upper;
int do_i_need_bksp = 0 ;
int lut_offset = len_pos  +1;
enum Keys
{
	ShiftKey = 16,
	Capital = 20,
};

int shift_active() {
	return GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0;
}

int capital_active() {
	return (GetKeyState(VK_CAPITAL) & 1) == 1;
}

int ctrl_active() {
    return  GetKeyState(VK_LCONTROL) < 0 || GetKeyState(VK_RCONTROL) < 0;
}

int alt_active (){
    return  GetKeyState(VK_LMENU) < 0 || GetKeyState(VK_RMENU) < 0;
}

LRESULT CALLBACK keyboard_hook(const int nCode, const WPARAM wParam, const LPARAM lParam) {

	if (wParam == WM_KEYDOWN ) {
		KBDLLHOOKSTRUCT *kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
		DWORD wVirtKey = kbdStruct->vkCode;
		DWORD wScanCode = kbdStruct->scanCode;

		BYTE lpKeyState[256];
		GetKeyboardState(lpKeyState);
		lpKeyState[Keys::ShiftKey] = 0;
		lpKeyState[Keys::Capital] = 0;
		if (shift_active()) {
			lpKeyState[Keys::ShiftKey] = 0x80;
			is_shift_pressed = true;
		}
		else{
            is_shift_pressed = false;
		}
		if (capital_active()) {
			lpKeyState[Keys::Capital] = 0x01;
			is_cap_pressed = true;
		}
		else{
            is_cap_pressed = false;
		}
		is_upper = is_shift_pressed ^ is_cap_pressed ;

		LUTindex =0;
		e= (ctrl_active() || alt_active());
        if (!e && switch_to_eng == false){

//            LUTindex =find_LUT_index (wVirtKey, 0 );
            LUTindex =find_LUT_index (  wVirtKey,
                                        last_Unicode,
                                        last_Unicode_length,
                                        is_upper,
                                        many_condition_key
                                          );
//            if (wVirtKey == 0x41)
//                LUTindex = 1;
//            else if (wVirtKey == 0x42)
//                LUTindex = 2;
        }
        else if ( ctrl_active() == 1 && alt_active() == 1 )
        {
             if((wVirtKey == 0x4D ) == 1) {
                switch_to_eng = !switch_to_eng;   // ctrl + alt + m to change language
                //std::cout<< "Odia <-> english mode changed  "<<switch_to_eng <<std::endl;
                return 1;
             }
//             else if ((wVirtKey == 0x51 ) == 1) {  // ctrl+alt+q to quit
//                return NULL;
//             }


        }


        a = (wVirtKey == VK_LEFT ||wVirtKey == VK_UP);
        b = ( wVirtKey == VK_DOWN ||wVirtKey == VK_RIGHT);
        c =( wVirtKey == VK_HOME || wVirtKey == VK_END );
        d= (wVirtKey == VK_NEXT || wVirtKey == VK_PRIOR );

        if (a && b && c && d && e)
        {
            cursor_changed = true;
            last_Unicode = 0;
            last_Unicode_length = 0;
            many_condition_key = 0;
        }
        else {
            cursor_changed = false;
            //last_Unicode =0;
        }

		//index = 0;
		//find the index of customised keys, if index =0, then don't process it
		// if index is non-zero use it later to find addiitional information

		if (LUTindex > 0){
			std::cout << "LUT Key pressed" << std::endl;
//            std::cout << "\n->  " ;
//            std::cout << LUTindex << "?" ;

			do_i_need_bksp = ( LUT[LUTindex][4] ==0) ? 0 : 2 ;
            bkp_idx = LUTindex;


            len_backup1 = last_Unicode_length;
			last_Unicode_length = LUT[LUTindex][len_pos];
			many_condition_key = LUT[LUTindex][6];

            INPUT inputs[ last_Unicode_length  ] = {};
            ZeroMemory(inputs, sizeof(inputs));


//             std::cout << "\["<< LUTindex << bkp_idx << "?" ;
//                         std::cout  <<"=" << LUTindex << " < " ;
//            for (int s2=0; s2<max_width; s2++){
//                std::cout << LUT[LUTindex][s2] <<" "  ;
//            }
//            std::cout  <<"="  ;
             if ( do_i_need_bksp == 2 ){

                for ( int bksp_num = 0; bksp_num < len_backup1 ; bksp_num ++){
                keybd_event( VK_BACK, 14, 0 , 0);
                usleep(100);
                keybd_event( VK_BACK, 14, KEYEVENTF_KEYUP, 0);
                usleep(100);
                }
             }


//             std::cout << do_i_need_bksp ;
//             std::cout << "\["<< LUTindex << bkp_idx<< "?" ;
            LUTindex = bkp_idx;
//            std::cout  <<"=" << LUTindex << " < " ;
//            for (int s2=0; s2<max_width; s2++){
//                std::cout << LUT[LUTindex][s2] <<" "  ;
//            }
//            std::cout  <<"="  ;
//            std::cout <<"\["<<  LUTindex << "?" ;


            for (int s =0; s< last_Unicode_length  ; s++)
                {
                    inputs[s].type = INPUT_KEYBOARD;
                    inputs[s].ki.wVk = 0;
                    inputs[s].ki.wScan = LUT[LUTindex][s+lut_offset] ;
                    inputs[s].ki.dwFlags = KEYEVENTF_UNICODE;
                    //std::cout<< s<< " "<< LUT[LUTindex][s+lut_offset]<<std::endl;

                    last_Unicode =  LUT[LUTindex][s+lut_offset] ;

//                    std::cout << last_Unicode <<" "  ;


//                    LPGUITHREADINFO lpgui = NULL;
//                    HWND target_window = NULL;
//
//                     if( GetGUIThreadInfo( NULL, lpgui ) )
//                        target_window = lpgui->hwndFocus;
//                    else
//                    {
//                        // You can get more information on why the function failed by calling
//                        // the win32 function, GetLastError().
//                        std::cout<<"Capture GUI threadinfo failed: "<<std::endl;
//                    }
                }

            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs))
            {
                std::cout<<"SendInput failed: "<<std::endl;
            }
			//  proessing done
			return 1;
		}
		else {
                if (wVirtKey != 0xE7) {
            ; // when LUT isn't invoked or alt/control isn't pressed.
//             last_Unicode_length = 0;
             last_Unicode =  0;
             many_condition_key = 0;
		char result;
		ToAscii(wVirtKey, wScanCode, lpKeyState, (LPWORD)&result, 0);
		std::cout << result << wVirtKey << " =?= "<< shift_active() << std::endl;

                }
		}


//		char result;
//		ToAscii(wVirtKey, wScanCode, lpKeyState, (LPWORD)&result, 0);
//		std::cout << result << wVirtKey << "  "<< shift_active() << std::endl;
	}

	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int main(int argc, char* argv[])
{
    std::cout << "LUT is  " << LUT[1][1] << std::endl;
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_hook, NULL, 0);
	if (hHook == NULL) {
		std::cout << "Keyboard hook failed!" << std::endl;
		return 1;
	}

	while (GetMessage(NULL, NULL, 0, 0));
    return 0;
}
