#pragma once

//
// This file contains all IDs of game assets 
//

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define FILEPATH_FONT L"font\\SuperMarioBros.ttf"

#define DEFAULT_TIME_PLAY 300

#define ID_TEX_SWITCH_SCENE_EFFECT -200
#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TILE 30
#define ID_TEX_MAP 40
#define ID_TEX_HUD 50

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5
#define OBJECT_TYPE_LUCKYBOX 6
#define OBJECT_TYPE_PARAGOOMBA 7
#define OBJECT_TYPE_MUSHROOM 8
#define OBJECT_TYPE_PARAKOOPAS 9
#define OBJECT_TYPE_GROUND 10
#define OBJECT_TYPE_PIRANHAPLANT 11
#define OBJECT_TYPE_FIREBALL 12
#define OBJECT_TYPE_SUPERLEAF 13
#define OBJECT_TYPE_LUCKYBOX_MUSHROOM 14
#define OBJECT_TYPE_PIRANHAPLANT_NOT_SHOOT 15
#define OBJECT_TYPE_TELEPORT 16
#define OBJECT_TYPE_HIDDENBUTTON 17
#define OBJECT_TYPE_GOLDBRICK 18
#define OBJECT_TYPE_EFFECTS 19
#define OBJECT_TYPE_MUSHROOM_GREEN 20
#define OBJECT_TYPE_PIPE 21
#define OBJECT_TYPE_RANDOMGADGET 22
#define OBJECT_TYPE_EFFECT_SWITCH_SCENE 23


#define OBJECT_TYPE_PORTAL	50

#define OBJECT_TYPE_MAP 100
#define OBJECT_TYPE_MAP_ENTITY 101
#define OBJECT_TYPE_HELP_MESSAGE 102//in overworld(introscene)
#define OBJECT_TYPE_NUM_VERSION 103
#define OBJECT_TYPE_SELECT_OPTION 104
#define OBJECT_TYPE_GAMEOVER_MENU 105

#define OBJECT_TYPE_PLAYER_INFORMATION 200

enum SCENE
{
	SCENE_MENU = 0,
	SCENE_1 = 1,
	SCENE_2 = 2
};

#define ID_SPRITE_TILE 0

//10000
#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)
#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)
#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)
#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)
#define ID_SPRITE_MARIO_BIG_KICK (ID_SPRITE_MARIO_BIG + 700)
#define ID_SPRITE_MARIO_BIG_KICK_LEFT (ID_SPRITE_MARIO_BIG_KICK + 10)
#define ID_SPRITE_MARIO_BIG_KICK_RIGHT (ID_SPRITE_MARIO_BIG_KICK + 20)

#define ID_SPRITE_MARIO_TRANSFORM_SMALL_TO_BIG (ID_SPRITE_MARIO_BIG + 800)
#define ID_SPRITE_MARIO_TRANSFORM_SMALL_TO_BIG_LEFT (ID_SPRITE_MARIO_TRANSFORM_SMALL_TO_BIG + 10)
#define ID_SPRITE_MARIO_TRANSFORM_SMALL_TO_BIG_RIGHT (ID_SPRITE_MARIO_TRANSFORM_SMALL_TO_BIG + 20)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

#define ID_SPRITE_MARIO_SMALL_KICK (ID_SPRITE_MARIO_SMALL + 600)
#define ID_SPRITE_MARIO_SMALL_KICK_LEFT (ID_SPRITE_MARIO_SMALL_KICK + 10)
#define ID_SPRITE_MARIO_SMALL_KICK_RIGHT (ID_SPRITE_MARIO_SMALL_KICK + 20)

#define ID_SPRITE_MARIO_SMALL_INTRO_SCENE (ID_SPRITE_MARIO_SMALL + 700)


#define ID_SPRITE_MARIO_RACCOON (ID_SPRITE_MARIO + 4000)
#define ID_SPRITE_MARIO_RACCOON_IDLE (ID_SPRITE_MARIO_RACCOON + 100)
#define ID_SPRITE_MARIO_RACCOON_IDLE_LEFT (ID_SPRITE_MARIO_RACCOON_IDLE + 10)
#define ID_SPRITE_MARIO_RACCOON_IDLE_RIGHT (ID_SPRITE_MARIO_RACCOON_IDLE + 20)

#define ID_SPRITE_MARIO_RACCOON_WALKING (ID_SPRITE_MARIO_RACCOON + 200)
#define ID_SPRITE_MARIO_RACCOON_WALKING_LEFT (ID_SPRITE_MARIO_RACCOON_WALKING + 10)
#define ID_SPRITE_MARIO_RACCOON_WALKING_RIGHT (ID_SPRITE_MARIO_RACCOON_WALKING + 20)
#define ID_SPRITE_MARIO_RACCOON_RUNNING (ID_SPRITE_MARIO_RACCOON + 300)
#define ID_SPRITE_MARIO_RACCOON_RUNNING_LEFT (ID_SPRITE_MARIO_RACCOON_RUNNING + 10)
#define ID_SPRITE_MARIO_RACCOON_RUNNING_RIGHT (ID_SPRITE_MARIO_RACCOON_RUNNING + 20)
#define ID_SPRITE_MARIO_RACCOON_JUMP (ID_SPRITE_MARIO_RACCOON + 400)
#define ID_SPRITE_MARIO_RACCOON_JUMP_WALK (ID_SPRITE_MARIO_RACCOON_JUMP + 10)
#define ID_SPRITE_MARIO_RACCOON_JUMP_WALK_LEFT (ID_SPRITE_MARIO_RACCOON_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_RACCOON_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_RACCOON_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_RACCOON_JUMP_RUN (ID_SPRITE_MARIO_RACCOON_JUMP + 20)
#define ID_SPRITE_MARIO_RACCOON_JUMP_RUN_LEFT (ID_SPRITE_MARIO_RACCOON_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_RACCOON_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_RACCOON_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_RACCOON_SIT (ID_SPRITE_MARIO_RACCOON + 500)
#define ID_SPRITE_MARIO_RACCOON_SIT_LEFT (ID_SPRITE_MARIO_RACCOON_SIT + 10)
#define ID_SPRITE_MARIO_RACCOON_SIT_RIGHT (ID_SPRITE_MARIO_RACCOON_SIT + 20)
#define ID_SPRITE_MARIO_RACCOON_BRACE (ID_SPRITE_MARIO_RACCOON + 600)
#define ID_SPRITE_MARIO_RACCOON_BRACE_LEFT (ID_SPRITE_MARIO_RACCOON_BRACE + 10)
#define ID_SPRITE_MARIO_RACCOON_BRACE_RIGHT (ID_SPRITE_MARIO_RACCOON_BRACE + 20)

#define ID_SPRITE_MARIO_RACCOON_TURN_AROUND (ID_SPRITE_MARIO_RACCOON + 700)
#define ID_SPRITE_MARIO_RACCOON_TURN_AROUND_LEFT (ID_SPRITE_MARIO_RACCOON_TURN_AROUND + 10)
#define ID_SPRITE_MARIO_RACCOON_TURN_AROUND_RIGHT (ID_SPRITE_MARIO_RACCOON_TURN_AROUND + 20)
#define ID_SPRITE_MARIO_RACCOON_TURN_AROUND_FORWARD (ID_SPRITE_MARIO_RACCOON_TURN_AROUND + 30)
#define ID_SPRITE_MARIO_RACCOON_TURN_AROUND_BACKWARD (ID_SPRITE_MARIO_RACCOON_TURN_AROUND + 40)

#define ID_SPRITE_MARIO_RACCOON_KICK (ID_SPRITE_MARIO_RACCOON + 800)
#define ID_SPRITE_MARIO_RACCOON_KICK_LEFT (ID_SPRITE_MARIO_RACCOON_KICK + 10)
#define ID_SPRITE_MARIO_RACCOON_KICK_RIGHT (ID_SPRITE_MARIO_RACCOON_KICK + 20)

#define ID_SPRITE_MARIO_RACCOON_FLY (ID_SPRITE_MARIO_RACCOON + 900)
#define ID_SPRITE_MARIO_RACCOON_FLY_LEFT (ID_SPRITE_MARIO_RACCOON_FLY + 10)
#define ID_SPRITE_MARIO_RACCOON_FLY_RIGHT (ID_SPRITE_MARIO_RACCOON_FLY + 20)
#define ID_SPRITE_MARIO_RACCOON_FLY_FAST_LEFT (ID_SPRITE_MARIO_RACCOON_FLY + 30)
#define ID_SPRITE_MARIO_RACCOON_FLY_FAST_RIGHT (ID_SPRITE_MARIO_RACCOON_FLY + 40)

#define ID_SPRITE_MARIO_BIG_PICK_UP (ID_SPRITE_MARIO_BIG + 900)
#define ID_SPRITE_MARIO_BIG_PICK_UP_LEFT (ID_SPRITE_MARIO_BIG_PICK_UP + 10)
#define ID_SPRITE_MARIO_BIG_PICK_UP_RIGHT (ID_SPRITE_MARIO_BIG_PICK_UP + 20)
#define ID_SPRITE_MARIO_BIG_PICK_UP_LEFT_IDLE (ID_SPRITE_MARIO_BIG_PICK_UP_LEFT + 3)
#define ID_SPRITE_MARIO_BIG_PICK_UP_RIGHT_IDLE (ID_SPRITE_MARIO_BIG_PICK_UP_RIGHT + 3)

#define ID_SPRITE_MARIO_SMALL_PICK_UP (ID_SPRITE_MARIO_SMALL + 800)
#define ID_SPRITE_MAIRO_SMALL_PICK_UP_LEFT (ID_SPRITE_MARIO_SMALL_PICK_UP + 10)
#define ID_SPRITE_MAIRO_SMALL_PICK_UP_RIGHT (ID_SPRITE_MARIO_SMALL_PICK_UP + 20)
#define ID_SPRITE_MARIO_SMALL_PICK_UP_LEFT_IDLE (ID_SPRITE_MAIRO_SMALL_PICK_UP_LEFT + 1)
#define ID_SPRITE_MARIO_SMALL_PICK_UP_RIGHT_IDLE (ID_SPRITE_MAIRO_SMALL_PICK_UP_RIGHT + 1)

#define ID_SPRITE_MARIO_RACCOON_PICK_UP (ID_SPRITE_MARIO_RACCOON + 1000)
#define ID_SPRITE_MARIO_RACCOON_PICK_UP_LEFT (ID_SPRITE_MARIO_RACCOON_PICK_UP + 10)
#define ID_SPRITE_MARIO_RACCOON_PICK_UP_RIGHT (ID_SPRITE_MARIO_RACCOON_PICK_UP + 20)
#define ID_SPRITE_MARIO_RACCOON_PICK_UP_LEFT_IDLE (ID_SPRITE_MARIO_RACCOON_PICK_UP_LEFT + 3)
#define ID_SPRITE_MARIO_RACCOON_PICK_UP_RIGHT_IDLE (ID_SPRITE_MARIO_RACCOON_PICK_UP_RIGHT + 3)



#pragma endregion 

#define ID_SPRITE_BRICK 20000
#define ID_SPRITE_GOLD_BRICK (ID_SPRITE_BRICK + 1000)

#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)

#define ID_SPRITE_COIN 40000

#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)

#define ID_SPRITE_LUCKYBOX 60000
#define ID_SPRITE_LUCKYBOX_COLLECTED (ID_SPRITE_LUCKYBOX + 1000)

#define ID_SPRITE_KOOPAS 70000
#define ID_SPRITE_KOOPAS_WALK_LEFT (ID_SPRITE_KOOPAS + 1000)
#define ID_SPRITE_KOOPAS_WALK_RIGHT (ID_SPRITE_KOOPAS + 2000)
#define ID_SPRITE_KOOPAS_HIDE (ID_SPRITE_KOOPAS + 3000)
#define ID_SPRITE_KOOPAS_HIDE_FLIP (ID_SPRITE_KOOPAS + 4000)


#define ID_SPRITE_PARAGOOMBA 80000
#define ID_SPRITE_PARAGOOMBA_FLY (ID_SPRITE_PARAGOOMBA + 1000)
#define ID_SPRITE_PARAGOOMBA_WALK (ID_SPRITE_PARAGOOMBA + 2000)

#define ID_SPRITE_MUSHROOM 90000

#define ID_SPRITE_PARAKOOPAS 100000
#define ID_SPRITE_PARAKOOPAS_FLY (ID_SPRITE_PARAKOOPAS + 1000)
#define ID_SPRITE_PARAKOOPAS_WALK_LEFT (ID_SPRITE_PARAKOOPAS + 2000)
#define ID_SPRITE_PARAKOOPAS_WALK_RIGHT (ID_SPRITE_PARAKOOPAS + 3000)

#define ID_SPRITE_PIRANHAPLANT 110000
#define ID_SPRITE_PIRANHAPLANT_HEAD_UP (ID_SPRITE_PIRANHAPLANT + 1000)
#define ID_SPRITE_PIRANHAPLANT_HEAD_DOWN (ID_SPRITE_PIRANHAPLANT + 2000)
#define ID_SPRITE_PIRANHAPLANT_HEAD_UP_FLIP (ID_SPRITE_PIRANHAPLANT + 3000)
#define ID_SPRITE_PIRANHAPLANT_HEAD_DOWN_FLIP (ID_SPRITE_PIRANHAPLANT + 4000)
#define ID_SPRITE_PIRANHAPLANT_NOT_SHOOT (ID_SPRITE_PIRANHAPLANT + 5000)

#define ID_SPRITE_FIREBALL 120000

#define ID_SPRITE_HIDDENBUTTON 130000

#define ID_SPRITE_EFFECTS 140000
#define ID_SPRITE_POINT_100 (ID_SPRITE_EFFECTS + 10)
#define ID_SPRITE_POINT_200 (ID_SPRITE_EFFECTS + 20)
#define ID_SPRITE_POINT_400 (ID_SPRITE_EFFECTS + 30)
#define ID_SPRITE_POINT_800 (ID_SPRITE_EFFECTS + 40)
#define ID_SPRITE_POINT_1000 (ID_SPRITE_EFFECTS + 50)
#define ID_SPRITE_POINT_2000 (ID_SPRITE_EFFECTS + 60)
#define ID_SPRITE_POINT_4000 (ID_SPRITE_EFFECTS + 70)
#define ID_SPRITE_POINT_8000 (ID_SPRITE_EFFECTS + 80)
#define ID_SPRITE_KABOOM (ID_SPRITE_EFFECTS + 90)
#define ID_SPRITE_BRICK_CRUMB (ID_SPRITE_EFFECTS + 100)
#define ID_SPRITE_1UP (ID_SPRITE_EFFECTS + 110)
#define ID_SPRITE_TRANSFORM (ID_SPRITE_EFFECTS + 120)

#define ID_SPRITE_MAP_1 150000
#define ID_SPRITE_TREE_MAP_1 (ID_SPRITE_MAP_1 + 100)
#define ID_SPRITE_HELP_MESSAGE (ID_SPRITE_MAP_1 + 200)
#define ID_SPRITE_FINISH_SCENE (ID_SPRITE_MAP_1 + 300)
#define ID_SPRITE_MAP_TITLE 155000

#define ID_SPRITE_PLAYER_STATUS 160000
#define ID_SPRITE_MARIO_SPEED (ID_SPRITE_PLAYER_STATUS + 100)
#define ID_SPRITE_MARIO_SPEED_1 (ID_SPRITE_MARIO_SPEED + 10)
#define ID_SPRITE_MARIO_SPEED_2 (ID_SPRITE_MARIO_SPEED + 20)
#define ID_SPRITE_MARIO_SPEED_3 (ID_SPRITE_MARIO_SPEED + 30)
#define ID_SPRITE_MARIO_SPEED_4 (ID_SPRITE_MARIO_SPEED + 40)
#define ID_SPRITE_MARIO_SPEED_5 (ID_SPRITE_MARIO_SPEED + 50)
#define ID_SPRITE_MARIO_SPEED_6 (ID_SPRITE_MARIO_SPEED + 60)
#define ID_SPRITE_MARIO_SPEED_7 (ID_SPRITE_MARIO_SPEED + 70)
#define ID_SPRITE_MARIO_SPEED_8 (ID_SPRITE_MARIO_SPEED + 80)

#define ID_SPRITE_GADGET (ID_SPRITE_PLAYER_STATUS + 200)
#define ID_SPRITE_GADGET_MUSHROOM (ID_SPRITE_GADGET + 10)
#define ID_SPRITE_GADGET_FLOWER (ID_SPRITE_GADGET + 20)
#define ID_SPRITE_GADGET_STAR (ID_SPRITE_GADGET + 30)

#define ID_SPRITE_PAUSE_GAME (ID_SPRITE_PLAYER_STATUS + 300)

#define ID_SPRITE_RANDOMGADGET 170000

#define ID_SPRITE_SELECT_OPTION 180000

#define ID_SPRITE_GAMEOVER_MENU 181000