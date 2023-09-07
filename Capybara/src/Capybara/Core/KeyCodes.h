#pragma once

// TODO: 完成跨平台的工作, 可以通过条件编译, 也可以通过绑定函数, 本质上都是定义了一个lookuptable
// From glfw3.h
#define CPBR_KEY_SPACE              32
#define CPBR_KEY_APOSTROPHE         39  /* ' */
#define CPBR_KEY_COMMA              44  /* , */
#define CPBR_KEY_MINUS              45  /* - */
#define CPBR_KEY_PERIOD             46  /* . */
#define CPBR_KEY_SLASH              47  /* / */
#define CPBR_KEY_0                  48
#define CPBR_KEY_1                  49
#define CPBR_KEY_2                  50
#define CPBR_KEY_3                  51
#define CPBR_KEY_4                  52
#define CPBR_KEY_5                  53
#define CPBR_KEY_6                  54
#define CPBR_KEY_7                  55
#define CPBR_KEY_8                  56
#define CPBR_KEY_9                  57
#define CPBR_KEY_SEMICOLON          59  /* ; */
#define CPBR_KEY_EQUAL              61  /* = */
#define CPBR_KEY_A                  65
#define CPBR_KEY_B                  66
#define CPBR_KEY_C                  67
#define CPBR_KEY_D                  68
#define CPBR_KEY_E                  69
#define CPBR_KEY_F                  70
#define CPBR_KEY_G                  71
#define CPBR_KEY_H                  72
#define CPBR_KEY_I                  73
#define CPBR_KEY_J                  74
#define CPBR_KEY_K                  75
#define CPBR_KEY_L                  76
#define CPBR_KEY_M                  77
#define CPBR_KEY_N                  78
#define CPBR_KEY_O                  79
#define CPBR_KEY_P                  80
#define CPBR_KEY_Q                  81
#define CPBR_KEY_R                  82
#define CPBR_KEY_S                  83
#define CPBR_KEY_T                  84
#define CPBR_KEY_U                  85
#define CPBR_KEY_V                  86
#define CPBR_KEY_W                  87
#define CPBR_KEY_X                  88
#define CPBR_KEY_Y                  89
#define CPBR_KEY_Z                  90
#define CPBR_KEY_LEFT_BRACKET       91  /* [ */
#define CPBR_KEY_BACKSLASH          92  /* \ */
#define CPBR_KEY_RIGHT_BRACKET      93  /* ] */
#define CPBR_KEY_GRAVE_ACCENT       96  /* ` */
#define CPBR_KEY_WORLD_1            161 /* non-US #1 */
#define CPBR_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define CPBR_KEY_ESCAPE             256
#define CPBR_KEY_ENTER              257
#define CPBR_KEY_TAB                258
#define CPBR_KEY_BACKSPACE          259
#define CPBR_KEY_INSERT             260
#define CPBR_KEY_DELETE             261
#define CPBR_KEY_RIGHT              262
#define CPBR_KEY_LEFT               263
#define CPBR_KEY_DOWN               264
#define CPBR_KEY_UP                 265
#define CPBR_KEY_PAGE_UP            266
#define CPBR_KEY_PAGE_DOWN          267
#define CPBR_KEY_HOME               268
#define CPBR_KEY_END                269
#define CPBR_KEY_CAPS_LOCK          280
#define CPBR_KEY_SCROLL_LOCK        281
#define CPBR_KEY_NUM_LOCK           282
#define CPBR_KEY_PRINT_SCREEN       283
#define CPBR_KEY_PAUSE              284
#define CPBR_KEY_F1                 290
#define CPBR_KEY_F2                 291
#define CPBR_KEY_F3                 292
#define CPBR_KEY_F4                 293
#define CPBR_KEY_F5                 294
#define CPBR_KEY_F6                 295
#define CPBR_KEY_F7                 296
#define CPBR_KEY_F8                 297
#define CPBR_KEY_F9                 298
#define CPBR_KEY_F10                299
#define CPBR_KEY_F11                300
#define CPBR_KEY_F12                301
#define CPBR_KEY_F13                302
#define CPBR_KEY_F14                303
#define CPBR_KEY_F15                304
#define CPBR_KEY_F16                305
#define CPBR_KEY_F17                306
#define CPBR_KEY_F18                307
#define CPBR_KEY_F19                308
#define CPBR_KEY_F20                309
#define CPBR_KEY_F21                310
#define CPBR_KEY_F22                311
#define CPBR_KEY_F23                312
#define CPBR_KEY_F24                313
#define CPBR_KEY_F25                314
#define CPBR_KEY_KP_0               320
#define CPBR_KEY_KP_1               321
#define CPBR_KEY_KP_2               322
#define CPBR_KEY_KP_3               323
#define CPBR_KEY_KP_4               324
#define CPBR_KEY_KP_5               325
#define CPBR_KEY_KP_6               326
#define CPBR_KEY_KP_7               327
#define CPBR_KEY_KP_8               328
#define CPBR_KEY_KP_9               329
#define CPBR_KEY_KP_DECIMAL         330
#define CPBR_KEY_KP_DIVIDE          331
#define CPBR_KEY_KP_MULTIPLY        332
#define CPBR_KEY_KP_SUBTRACT        333
#define CPBR_KEY_KP_ADD             334
#define CPBR_KEY_KP_ENTER           335
#define CPBR_KEY_KP_EQUAL           336
#define CPBR_KEY_LEFT_SHIFT         340
#define CPBR_KEY_LEFT_CONTROL       341
#define CPBR_KEY_LEFT_ALT           342
#define CPBR_KEY_LEFT_SUPER         343
#define CPBR_KEY_RIGHT_SHIFT        344
#define CPBR_KEY_RIGHT_CONTROL      345
#define CPBR_KEY_RIGHT_ALT          346
#define CPBR_KEY_RIGHT_SUPER        347
#define CPBR_KEY_MENU               348