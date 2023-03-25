--[[
1 current key press

2 previous character
3 previous character length
4 Is consonant needed for this?

5 Current character Capital needed
6 how many back spaces needed
7 currnet character length
8 current character is it consonant

9 current character of max length allocated max_char_length

10+ max_char_length-1
--]]


debug_flag = true
dofile('other.lua')
dofile('keymap.lua')
dofile ('char2vkKey.lua')

max_length = #keymap_table

next_bksp_count = 0
next_char_length = 0
next_isit_consonant = false
next_char_table = {}


prev_char_unicode = 0
prev_char_length = 0
prev_was_consonant = false



function find_LUT_index (
						key_pressed,
						is_capital
						) 

	if debug_flag == true then 
		print ('entry-->', key_pressed, is_capital)
	end
	

	local was_consonant = _G.prev_was_consonant
	local last_unicode_length = _G.prev_char_length
	local prev_unicode
	if _G.prev_char_length > 0 then
		prev_unicode = _G.prev_char_unicode
	else
		prev_unicode = 0
	end 

	local next_char_table_local = {}
	-- ===================local variables =================
	local i = 0
	local cap_match , prev_key_match, consonant_match
	local final_match_index = 0 
	
	
	
	for i =1,max_length do
		if keymap_table[i][1] == key_pressed then  --  keypressed match! 
		
		
			if keymap_table[i][5] == true then
				if is_capital == true then
					cap_match = true
				else
					cap_match = false
				end
			else
				cap_match = true
			end
			
			
			
			if keymap_table[i][3] > 0 then -- if it has a requirement
				if last_unicode_length == keymap_table[i][3] then
					if prev_unicode == keymap_table[i][2] then
						prev_key_match = true
					else
						prev_key_match = false
					end
				else
					prev_key_match = false
				end
			else
				prev_key_match = true  -- prev keymatch not a requirement
			end
			
			consonant_match = ternary (keymap_table[i][4],was_consonant, false  )
			if debug_flag == true then
				print (i, cap_match,prev_key_match, consonant_match )
			end
			if (cap_match and  ( consonant_match or (  not consonant_match and prev_key_match) )) then
				final_match_index = i
				break;
			end
		end
	end
	
	if final_match_index == 0 then
		return 0
	else
		_G.next_bksp_count 		=  keymap_table[final_match_index][6] ;
		_G.next_char_length 	=  keymap_table[final_match_index][7] ;
		_G.next_isit_consonant 	=  keymap_table[final_match_index][8] ;
		for i = 1, max_char_length do
			table.insert ( next_char_table_local, keymap_table[final_match_index][8 + i] )
		end
		_G.next_char_table = next_char_table_local
		if debug_flag == true then
			print (key_pressed, final_match_index,  _G.next_char_length )
		end
		return 1 
	end
end

function reset_lua_var ()
	_G.next_bksp_count 		= 0 
	_G.next_char_length 	= 0 
	_G.next_isit_consonant  = false
	_G.next_char_table      = {0}  
	_G.prev_char_unicode    = 0
	_G.prev_char_length     = 0
	_G.prev_was_consonant   = false
	return 1
end


function shift_char ()
	if _G.next_char_length > 0 then
		_G.prev_char_unicode     = _G.next_char_table[_G.next_char_length]
	else
		_G.prev_char_unicode = 0
	end
	
	_G.prev_char_length      = _G.next_char_length 
	_G.prev_was_consonant    = _G.next_isit_consonant
	return 1
end

function set_prev (a,b,c)
	-- pre set the previous variables , for debugging
	_G.prev_char_unicode  = a
	_G.prev_char_length   = b
	_G.prev_was_consonant = c
	return 1
end

function search (a) -- character in string, if it's capital
	-- for readable inputs , only for debugging
	local a2 = string.upper(a)
	local nowkey = str2vk[a2]
	local capital_flag 
	if (a2 == a) then
		if a2:find ('%a') == nil then
			capital_flag = false
		else
			capital_flag = true
		end
	else
		capital_flag = false
	end 		
	
	print (nowkey, capital_flag )
	
	return 1
end

function do_algo ()
	print (" Nope ")
	
end