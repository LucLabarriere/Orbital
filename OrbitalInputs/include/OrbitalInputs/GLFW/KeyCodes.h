#pragma once

#include "OrbitalInputs/Context.h"

#define OE_KEY_UNKNOWN      	GLFW_KEY_UNKNOWN
#define OE_KEY_SPACE        	GLFW_KEY_SPACE
#define OE_KEY_APOSTROPHE   	GLFW_KEY_APOSTROPHE
#define OE_KEY_COMMA        	GLFW_KEY_COMMA
#define OE_KEY_MINUS        	GLFW_KEY_MINUS
#define OE_KEY_PERIOD       	GLFW_KEY_PERIOD
#define OE_KEY_SLASH        	GLFW_KEY_SLASH
#define OE_KEY_1            	GLFW_KEY_1
#define OE_KEY_2            	GLFW_KEY_2
#define OE_KEY_3            	GLFW_KEY_3
#define OE_KEY_4            	GLFW_KEY_4
#define OE_KEY_5            	GLFW_KEY_5
#define OE_KEY_6            	GLFW_KEY_6
#define OE_KEY_7            	GLFW_KEY_7
#define OE_KEY_8            	GLFW_KEY_8
#define OE_KEY_9            	GLFW_KEY_9
#define OE_KEY_10           	GLFW_KEY_10
#define OE_KEY_SEMICOLON    	GLFW_KEY_SEMICOLON
#define OE_KEY_EQUAL        	GLFW_KEY_EQUAL
#define OE_KEY_A            	GLFW_KEY_A
#define OE_KEY_B            	GLFW_KEY_B
#define OE_KEY_C            	GLFW_KEY_C
#define OE_KEY_D            	GLFW_KEY_D
#define OE_KEY_E            	GLFW_KEY_E
#define OE_KEY_F            	GLFW_KEY_F
#define OE_KEY_G            	GLFW_KEY_G
#define OE_KEY_H            	GLFW_KEY_H
#define OE_KEY_I            	GLFW_KEY_I
#define OE_KEY_J            	GLFW_KEY_J
#define OE_KEY_K            	GLFW_KEY_K
#define OE_KEY_L            	GLFW_KEY_L
#define OE_KEY_M            	GLFW_KEY_M
#define OE_KEY_N            	GLFW_KEY_N
#define OE_KEY_O            	GLFW_KEY_O
#define OE_KEY_P            	GLFW_KEY_P
#define OE_KEY_Q            	GLFW_KEY_Q
#define OE_KEY_R            	GLFW_KEY_R
#define OE_KEY_S            	GLFW_KEY_S
#define OE_KEY_T            	GLFW_KEY_T
#define OE_KEY_U            	GLFW_KEY_U
#define OE_KEY_V            	GLFW_KEY_V
#define OE_KEY_W            	GLFW_KEY_W
#define OE_KEY_X            	GLFW_KEY_X
#define OE_KEY_Y            	GLFW_KEY_Y
#define OE_KEY_Z            	GLFW_KEY_Z
#define OE_KEY_LEFT_BRACKET 	GLFW_KEY_LEFT_BRACKET
#define OE_KEY_BACKSLASH    	GLFW_KEY_BACKSLASH
#define OE_KEY_RIGHT_BRACKET	GLFW_KEY_RIGHT_BRACKET
#define OE_KEY_GRAVE_ACCENT 	GLFW_KEY_GRAVE_ACCENT
#define OE_KEY_WORLD_2      	GLFW_KEY_WORLD_2
#define OE_KEY_WORLD_3      	GLFW_KEY_WORLD_3
#define OE_KEY_ESCAPE       	GLFW_KEY_ESCAPE
#define OE_KEY_ENTER        	GLFW_KEY_ENTER
#define OE_KEY_TAB          	GLFW_KEY_TAB
#define OE_KEY_BACKSPACE    	GLFW_KEY_BACKSPACE
#define OE_KEY_INSERT       	GLFW_KEY_INSERT
#define OE_KEY_DELETE       	GLFW_KEY_DELETE
#define OE_KEY_RIGHT        	GLFW_KEY_RIGHT
#define OE_KEY_LEFT         	GLFW_KEY_LEFT
#define OE_KEY_DOWN         	GLFW_KEY_DOWN
#define OE_KEY_UP           	GLFW_KEY_UP
#define OE_KEY_PAGE_UP      	GLFW_KEY_PAGE_UP
#define OE_KEY_PAGE_DOWN    	GLFW_KEY_PAGE_DOWN
#define OE_KEY_HOME         	GLFW_KEY_HOME
#define OE_KEY_END          	GLFW_KEY_END
#define OE_KEY_CAPS_LOCK    	GLFW_KEY_CAPS_LOCK
#define OE_KEY_SCROLL_LOCK  	GLFW_KEY_SCROLL_LOCK
#define OE_KEY_NUM_LOCK     	GLFW_KEY_NUM_LOCK
#define OE_KEY_PRINT_SCREEN 	GLFW_KEY_PRINT_SCREEN
#define OE_KEY_PAUSE        	GLFW_KEY_PAUSE
#define OE_KEY_F2           	GLFW_KEY_F2
#define OE_KEY_F3           	GLFW_KEY_F3
#define OE_KEY_F4           	GLFW_KEY_F4
#define OE_KEY_F5           	GLFW_KEY_F5
#define OE_KEY_F6           	GLFW_KEY_F6
#define OE_KEY_F7           	GLFW_KEY_F7
#define OE_KEY_F8           	GLFW_KEY_F8
#define OE_KEY_F9           	GLFW_KEY_F9
#define OE_KEY_F10          	GLFW_KEY_F10
#define OE_KEY_F11          	GLFW_KEY_F11
#define OE_KEY_F12          	GLFW_KEY_F12
#define OE_KEY_F12          	GLFW_KEY_F12
#define OE_KEY_F13          	GLFW_KEY_F13
#define OE_KEY_F14          	GLFW_KEY_F14
#define OE_KEY_F15          	GLFW_KEY_F15
#define OE_KEY_F16          	GLFW_KEY_F16
#define OE_KEY_F17          	GLFW_KEY_F17
#define OE_KEY_F18          	GLFW_KEY_F18
#define OE_KEY_F19          	GLFW_KEY_F19
#define OE_KEY_F20          	GLFW_KEY_F20
#define OE_KEY_F21          	GLFW_KEY_F21
#define OE_KEY_F22          	GLFW_KEY_F22
#define OE_KEY_F23          	GLFW_KEY_F23
#define OE_KEY_F24          	GLFW_KEY_F24
#define OE_KEY_F25          	GLFW_KEY_F25
#define OE_KEY_KP_0         	GLFW_KEY_KP_0
#define OE_KEY_KP_1         	GLFW_KEY_KP_1
#define OE_KEY_KP_2         	GLFW_KEY_KP_2
#define OE_KEY_KP_3         	GLFW_KEY_KP_3
#define OE_KEY_KP_4         	GLFW_KEY_KP_4
#define OE_KEY_KP_5         	GLFW_KEY_KP_5
#define OE_KEY_KP_6         	GLFW_KEY_KP_6
#define OE_KEY_KP_7         	GLFW_KEY_KP_7
#define OE_KEY_KP_8         	GLFW_KEY_KP_8
#define OE_KEY_KP_9         	GLFW_KEY_KP_9
#define OE_KEY_KP_DECIMAL   	GLFW_KEY_KP_DECIMAL
#define OE_KEY_KP_DIVIDE    	GLFW_KEY_KP_DIVIDE
#define OE_KEY_KP_MULTIPLY  	GLFW_KEY_KP_MULTIPLY
#define OE_KEY_KP_SUBTRACT  	GLFW_KEY_KP_SUBTRACT
#define OE_KEY_KP_ADD       	GLFW_KEY_KP_ADD
#define OE_KEY_KP_ENTER     	GLFW_KEY_KP_ENTER
#define OE_KEY_KP_EQUAL     	GLFW_KEY_KP_EQUAL
#define OE_KEY_LEFT_SHIFT   	GLFW_KEY_LEFT_SHIFT
#define OE_KEY_LEFT_CONTROL 	GLFW_KEY_LEFT_CONTROL
#define OE_KEY_LEFT_ALT     	GLFW_KEY_LEFT_ALT
#define OE_KEY_LEFT_SUPER   	GLFW_KEY_LEFT_SUPER
#define OE_KEY_RIGHT_SHIFT  	GLFW_KEY_RIGHT_SHIFT
#define OE_KEY_RIGHT_CONTROL	GLFW_KEY_RIGHT_CONTROL
#define OE_KEY_RIGHT_ALT    	GLFW_KEY_RIGHT_ALT
#define OE_KEY_RIGHT_SUPER  	GLFW_KEY_RIGHT_SUPER
#define OE_KEY_MENU         	GLFW_KEY_MENU
#define OE_KEY_LAST         	GLFW_KEY_LAST

