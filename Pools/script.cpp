#include "script.h"
#include "keyboard.h"
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <vector>


void drawstring(std::string string, float X, float Y)
{
	std::string Template = "<FONT FACE='$title' COLOR='#%04X'>" + string + "</FONT>";
	const char* InsertTemplate = MISC::VAR_STRING(10, "LITERAL_STRING", _strdup(Template.c_str()));
	UIDEBUG::_BG_SET_TEXT_SCALE(0.3f, 0.3f);
	UIDEBUG::_BG_DISPLAY_TEXT(MISC::VAR_STRING(42, "COLOR_STRING", 0, InsertTemplate), X, Y);
}

void ScriptMain()
{
	int con = GetPrivateProfileInt("CONFIG", "Condition", 25, ".\\WJam.ini");
	double co = ((double)(con) / 100);
	bool kdown = GetPrivateProfileInt("CONFIG", "Knockdown", 1, ".\\WJam.ini");
	srand(time(0));
	int x;
	std::vector<int> y;
	Vector3 pos;
	unsigned int weaponhash;
	bool broken = false;
	bool check1 = false;
	bool broke1;
	bool broke2;
	Object weaponobject;
	Object tempobject;
	std::vector<Object> ojects;
	while (true)
	{
		/*std::stringstream temp_str;
		temp_str << (co) << " " << (kdown);
		std::string str = temp_str.str();
		UIDEBUG::_BG_DISPLAY_TEXT(MISC::VAR_STRING(10, "LITERAL_STRING", _strdup(str.c_str())), 0.5f, 0.5f);*/
		//pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true, false);


		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), &weaponhash, 0, 0, 0);

		weaponobject = ENTITY::GET_OBJECT_INDEX_FROM_ENTITY_INDEX(WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID(), 0));
		for (int i = 0; i < ojects.size(); i++) {
			if (ojects[i] == ENTITY::GET_OBJECT_INDEX_FROM_ENTITY_INDEX(WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID(), 0))) {
				broke2 = true;
				break;
			}
			else {
				broke2 = false;
			}
		}
		if (broke2) {
			PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), true);
			if (GRAPHICS::ANIMPOSTFX_IS_RUNNING("WheelHUDIn")) {
				std::string warning = "Your currently equipped weapon is broken. \nClean it to repair it.";
				drawstring(warning, 0.01f, 0.1f);
			}
		}
		if (GetKeyState(VK_LBUTTON) < 0) {
			weaponobject = ENTITY::GET_OBJECT_INDEX_FROM_ENTITY_INDEX(WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID(), 0));
			pos = ENTITY::GET_ENTITY_COORDS(WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID(), 0), true, true);
			for (int i = 0; i < ojects.size(); i++) {
				if (ojects[i] == weaponobject) {
					check1 = true;
					y.push_back(i);
					break;
				}
				else {
					check1 = false;
				}
			}
			if (WEAPON::GET_WEAPON_DEGRADATION(weaponobject) > ((float)(co)) && !check1) {
				x = (rand() % 100);
				if (x < 20) {
					PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), true);
					//if ((PED::GET_PED_CROUCH_MOVEMENT(PLAYER::PLAYER_PED_ID()))) {
					if (!kdown) {
						PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), false);
					}
					FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 15, 0.5f, true, false, 0.5f);
					//}
					//else {
						//FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z + 0.5f, 15, 0.5f, true, false, 0.5f);
					//}
					FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 13, 0.0f, true, false, 0.5f);
					/*comment this line back in when finished*/PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), false);
					//WEAPON::_DROP_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), false, true, false, true);
					PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), true);
					broken = true;
					tempobject = ENTITY::GET_OBJECT_INDEX_FROM_ENTITY_INDEX(WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID(), 0));
					ojects.push_back(tempobject);
				}
			}
			else if (WEAPON::GET_WEAPON_DEGRADATION(weaponobject) < ((float)(co)) && check1) {
				broken = false;
				for (int i = 0; i < ojects.size(); i++) {
					if (ojects[i] == weaponobject) {
						ojects.erase(ojects.begin() + i);
						check1 = false;
					}
				}
			}
			else {
				while (true) {
					for (int i = 0; i < ojects.size(); i++) {
						if (ojects[i] == ENTITY::GET_OBJECT_INDEX_FROM_ENTITY_INDEX(WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID(), 0))) {
							broke1 = true;
							break;
						}
						else {
							broke1 = false;
						}
					}
					if (broke1/* && ENTITY::GET_OBJECT_INDEX_FROM_ENTITY_INDEX(WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID(), 0)) == tempobject && WEAPON::GET_WEAPON_DEGRADATION(weaponobject) > 0.05*/) {
						PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), true);
						if (GRAPHICS::ANIMPOSTFX_IS_RUNNING("WheelHUDIn")) {
							std::string warning = "Your currently equipped weapon is broken. \nClean it to repair it.";
							drawstring(warning, 0.01f, 0.1f);
						}
					}
					else {
						break;
					}
					WAIT(0);
				}
			}
		}
		
		if (broken) {
			//PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), true);
			//if (WEAPON::GET_WEAPON_DEGRADATION(weaponobject) < 0.25) {
			//	broken = false;
			//}
		}
		WAIT(0);
	}
}
