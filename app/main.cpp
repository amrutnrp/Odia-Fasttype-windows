#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <iostream>
#include <unistd.h>

using namespace std;
extern "C" {
    #include "include/lua.h"
    #include "include/lua.hpp"
    #include "include/lualib.h"
    #include "include/lauxlib.h"
}

#ifdef _WIN32
#pragma comment  (lib,"lua needed")
#endif


/*
Find all the improvement points by searching ##

*/
bool debug_flag = false;
bool Check_lua_var(lua_State *L, int type){
    if (type ==1){ // function
        if (lua_isfunction(L,-1) == false){
			cout<<"bad lua function"<<endl;
			return true;
			}
        else return false;
    }
    if (type ==2){ // float or int
        if (lua_isnumber(L,-1) == false){
			cout<<"bad lua number"<<endl;
			return true;
			}
        else return false;
    }
    if (type ==3){ // table
        if (lua_istable(L,-1) == false){
			cout<<"bad lua table"<<endl;
			return true;
			}
        else return false;
    }
    if (type ==4){ // float or int
        if (lua_isstring(L,-1) == false){
			cout<<"bad lua number"<<endl;
			return true;
			}
        else return false;
    }


}
bool CheckLua (lua_State *L, int r) {
    if (r!=LUA_OK){
        string errormsg = lua_tostring (L, -1);
        cout << errormsg << endl;
        return false;
    }
    return true;
}


void reset_values (lua_State *L) {
	lua_getglobal (L, "reset_lua_var");
	if (CheckLua( L, lua_pcall ( L, 0, 1, 0)) )
		{
			if (debug_flag) cout<<"reset done nicely"<<endl;
			int temp_val = (int)lua_tonumber(L, -1);
			if (temp_val != 1){
				cout<<"Something went wrong in reset var function"<<endl;
			}
		}

}
// used inside main & keyboard_hook
HHOOK hHook{ NULL };
// used inside keyboard_hook only
bool switch_to_eng = false;
bool is_shift_pressed, is_cap_pressed, is_upper;
bool is_ctrl_pressed, is_alt_pressed, ctrl_n_alt;
bool position_keys_pressed = false, undo_pressed = false, redo_pressed = false;
bool cursor_changed, prorgess_flag = false;
char result;
int LUTindex;

lua_State* L;

int last_Unicode = 0, Unicode_length = 0;
int temp_val;

int max_char_length = 0;
int do_i_need_bksp = 0;

//=======================================================================
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
		is_ctrl_pressed =   ctrl_active();
		is_alt_pressed	=	alt_active();
		ctrl_n_alt = is_ctrl_pressed || is_alt_pressed;
        if (ctrl_n_alt == false && switch_to_eng == false){  // ctrl + key  or alt+key isn't considered

			//======================================================================= LUA block start

            if (wVirtKey == VK_PACKET || wVirtKey == VK_BACK)
                LUTindex = 0;
            else {
                lua_getglobal (L, "find_LUT_index");
                lua_pushnumber (L, (int)wVirtKey);
                lua_pushboolean (L, is_upper);
                if (CheckLua( L, lua_pcall ( L, 2, 1, 0)) )
                {
                    if (debug_flag) cout<<"function executed nicely"<<endl;
                    LUTindex = (int)lua_tonumber(L, -1);
                    if (debug_flag)  cout<<LUTindex<<endl;
                }
                else{
                    cout<<"find_LUT_index couldn't run"<<endl;
                    LUTindex = 0;
                    return 0;
                }
            }
			//======================================================================= LUA block end
        }
        else if ( is_ctrl_pressed == 1 && is_alt_pressed == 1 )
        {
             if(wVirtKey == 0x4D ) {
                switch_to_eng = !switch_to_eng;   // ctrl + alt + m to change language
                std::cout<< "Odia <-> english mode changed, value =  ";
                if (switch_to_eng)  std::cout <<"OFF"<<std::endl; else  std::cout<<"ON "<<std::endl;

                return 1;
			}
			else if (wVirtKey == 0x51 ) {  // ctrl+alt+q to quit transliteration program
				std::cout<< "Transliteration program stopped  "<<std::endl; //## this is not stopping the code
				return NULL;
			}
        }



		if ( LUTindex == 1){
			//==================================================== LUA block start
			if (debug_flag)  std::cout << "valid Key pressed" << std::endl;

			lua_getglobal (L, "next_bksp_count");
			//if ( Check_lua_var(L,2)){ cout<<"FATAL1 "<<endl; return 0; }
			do_i_need_bksp = (int)lua_tonumber(L, -1);

			lua_getglobal (L, "next_char_length");
			//if ( Check_lua_var(L,2)){ cout<<"FATAL2 "<<endl; return 0; }
			Unicode_length = (int)lua_tonumber(L, -1);

			lua_getglobal (L, "next_char_table");
			//if ( Check_lua_var(L,3)){ cout<<"FATAL2 "<<endl; return 0; }


			int next_char_array[ Unicode_length ] = {};
			ZeroMemory(next_char_array, sizeof(next_char_array));

			if (debug_flag) cout<<endl;
			for (int s =0; s< Unicode_length  ; s++){
				lua_pushnumber (L, s+1 );
				lua_gettable(L,-2);
				next_char_array [s]  = 	lua_tonumber (L,-1);
				lua_pop(L,1);
				if (debug_flag) cout<<next_char_array [s] <<"{}";
			 }
			 if (debug_flag) cout<<endl;
			 //===================================== LUA block end
            prorgess_flag = true;

            INPUT inputs[ Unicode_length  ] = {};
            ZeroMemory(inputs, sizeof(inputs));
			if (debug_flag){
				cout<<"BKSP: " <<do_i_need_bksp <<" " << Unicode_length <<endl;
			}
			// press backspace
             if ( do_i_need_bksp >0 ){
                for ( int s = 0; s < do_i_need_bksp ; s ++){
                keybd_event( VK_BACK, 14, 0 , 0);
                usleep(100);
                keybd_event( VK_BACK, 14, KEYEVENTF_KEYUP, 0);
                usleep(100);
                }
             }
			// Send odia character
            for (int s =0; s< Unicode_length  ; s++)
                {
                    inputs[s].type = INPUT_KEYBOARD;
                    inputs[s].ki.wVk = 0;
					// get each character one by one
                    inputs[s].ki.wScan = next_char_array [s] ;
                    inputs[s].ki.dwFlags = KEYEVENTF_UNICODE;
                }

			//==================================================== LUA block start
            lua_getglobal (L, "shift_char");
            if (CheckLua( L, lua_pcall ( L, 0, 1, 0)) )
                {
                    if (debug_flag) cout<<"shift done nicely"<<endl;
                    temp_val = (int)lua_tonumber(L, -1);
                    if (temp_val != 1){
                        cout<<"Something went wrong in shift char function"<<endl;
                    }
                }
			//===================================== LUA block end

            UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
            if (uSent != ARRAYSIZE(inputs))
            {
                std::cout<<"SendInput failed: "<<std::endl;
            }
            prorgess_flag = false;
			//  proessing done
			return 1;
		}
		else if (wVirtKey == VK_PACKET || wVirtKey == VK_BACK)
		     {;
		     if (prorgess_flag == false) {
                reset_values(L);
		     }
			}
		else {
			/*  some other key pressed !
				May be enter, numpad , anythinn else: but shouldn't reset the LUT values
				maybe even the sendKeys itself!!
			*/
			position_keys_pressed = (wVirtKey == VK_LEFT
								||	wVirtKey == VK_RIGHT
								||	wVirtKey == VK_UP
								||	wVirtKey == VK_DOWN
								||	wVirtKey == VK_HOME
								||	wVirtKey == VK_END
								||	wVirtKey == VK_PRIOR
								||	wVirtKey == VK_DOWN
								||	wVirtKey == VK_NEXT
								||  wVirtKey == VK_TAB
								||  wVirtKey == VK_RETURN
								||  wVirtKey == VK_SPACE
									);
			undo_pressed  = (is_ctrl_pressed && wVirtKey == 0x5A ); //CTRL+Z
			redo_pressed  = (is_ctrl_pressed && wVirtKey == 0x52 ); //CTRL+R


			if ( position_keys_pressed || undo_pressed || redo_pressed)
			// ## need mouse info to see if window changed or cursor changed
			// ## cursor_changed hasn't beed used , can be removed later
			{
				cursor_changed = true;
				//======================================================================= LUA block start
				reset_values(L);
				//======================================================================= LUA block end
			}
			else {
				cursor_changed = false;
			}


		//======================================================================= ## why print the below items here?
		// ToAscii(wVirtKey, wScanCode, lpKeyState, (LPWORD)&result, 0);
		// std::cout << result << wVirtKey << " =?= "<< shift_active() << std::endl;
		}
		ToAscii(wVirtKey, wScanCode, lpKeyState, (LPWORD)&result, 0);
		if (debug_flag) std::cout << result << wVirtKey << "  "<< shift_active() << std::endl;
	}
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int main(int argc, char* argv[])
{
    L = luaL_newstate();

	luaL_openlibs(L);

    if (CheckLua ( L, luaL_dofile(L,"decipher_script.lua")  ) == false)
	{ 	cout<<"bad lua env"<<endl;
		return 0; }
	else
	{
		lua_getglobal (L, "find_LUT_index");
		if ( Check_lua_var(L,1)){ return 0; }
		lua_getglobal (L, "do_algo");
		if ( Check_lua_var(L,1)){ return 0; }

		lua_getglobal (L, "next_bksp_count");
        if ( Check_lua_var(L,2)){ cout<<"FATAL1 "<<endl; return 0;}

		lua_getglobal (L, "next_char_table");
        if ( Check_lua_var(L,3)){ cout<<"FATAL2 "<<endl; return 0; }

        lua_getglobal (L, "shift_char");
        if ( Check_lua_var(L,1)){ cout<<"FATAL3 "<<endl; return 0; }

        lua_getglobal (L, "reset_lua_var");
        if ( Check_lua_var(L,1)){ cout<<"FATAL4 "<<endl; return 0; }

        lua_getglobal (L, "max_char_length");
        if ( Check_lua_var(L,2)){ return 0; }

        max_char_length = (int)lua_tonumber(L, -1);

	}
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_hook, NULL, 0);
	if (hHook == NULL) {
		std::cout << "Keyboard hook failed!" << std::endl;
		return 1;
	}

	while (GetMessage(NULL, NULL, 0, 0));

    return 0;
}
