/*****************************************************************************
 *   Copyright(C)2009-2019 by VSF Team                                       *
 *                                                                           *
 *  Licensed under the Apache License, Version 2.0 (the "License");          *
 *  you may not use this file except in compliance with the License.         *
 *  You may obtain a copy of the License at                                  *
 *                                                                           *
 *     http://www.apache.org/licenses/LICENSE-2.0                            *
 *                                                                           *
 *  Unless required by applicable law or agreed to in writing, software      *
 *  distributed under the License is distributed on an "AS IS" BASIS,        *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 *  See the License for the specific language governing permissions and      *
 *  limitations under the License.                                           *
 *                                                                           *
 ****************************************************************************/

#ifndef __USRAPP_UI_COMMON_H__
#define __USRAPP_UI_COMMON_H__

/*============================ INCLUDES ======================================*/

#include "vsf.h"

#if     VSF_USE_UI == ENABLED                                                   \
    &&  (VSF_DISP_USE_SDL2 == ENABLED || VSF_DISP_USE_FB == ENABLED || VSF_DISP_USE_DL1X5 == ENABLED)\
    &&  (VSF_USE_SDL2 == ENABLED || VSF_USE_TINY_GUI == ENABLED || VSF_USE_AWTK == ENABLED || VSF_USE_LVGL == ENABLED)

#if VSF_USE_LVGL == ENABLED
#   include "lvgl/lvgl.h"
#   include "lv_conf.h"
#   include "component/3rd-party/lvgl/port/vsf_lvgl_port.h"
#endif

/*============================ MACROS ========================================*/

#ifndef VSF_TGUI_CFG_SV_PORT_COLOR_BUFFER_SIZE
#   define VSF_TGUI_CFG_SV_PORT_COLOR_BUFFER_SIZE                               \
                (VSF_TGUI_HOR_MAX * VSF_TGUI_VER_MAX / 10)
#endif

#if VSF_USE_LVGL == ENABLED
#   ifndef APP_LVGL_DEMO_CFG_PIXEL_BUFFER_SIZE
#       define APP_LVGL_DEMO_CFG_PIXEL_BUFFER_SIZE                              \
                (LV_VER_RES_MAX * LV_HOR_RES_MAX / 10)
#   endif
#endif

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

typedef struct usrapp_ui_common_t {
    vk_disp_t *disp;

#if VSF_DISP_USE_SDL2 == ENABLED
    vk_disp_sdl2_t disp_sdl2;
#elif VSF_DISP_USE_FB == ENABLED
    vk_disp_fb_t disp_fb;
#endif

#if VSF_USE_TINY_GUI == ENABLED
    struct {
        vk_input_notifier_t notifier;
#if APP_DISP_SDL2_COLOR == VSF_DISP_COLOR_RGB565
        uint16_t color[VSF_TGUI_CFG_SV_PORT_COLOR_BUFFER_SIZE];
#elif (APP_DISP_SDL2_COLOR == VSF_DISP_COLOR_ARGB8888) || (APP_DISP_SDL2_COLOR == VSF_DISP_COLOR_RGB666_32)
        uint32_t color[VSF_TGUI_CFG_SV_PORT_COLOR_BUFFER_SIZE];
#endif
    } tgui;
#endif

#if VSF_USE_AWTK == ENABLED
    struct {
        vk_input_notifier_t notifier;
    } awtk;
#endif

#if VSF_USE_LVGL == ENABLED
    struct {
        vk_input_notifier_t notifier;
#if APP_LVGL_DEMO_USE_TOUCHSCREEN == ENABLED
        vk_touchscreen_evt_t ts_evt;
#else
        vk_mouse_evt_t mouse_evt;
#endif
#if LV_USE_GROUP == ENABLED
        vk_keyboard_evt_t kb_evt;
        lv_group_t* group;
#endif
        lv_disp_buf_t disp_buf;
// if APP_LVGL_DEMO_CFG_PIXEL_BUFFER_PTR is defined, use defined buffer
#ifdef APP_LVGL_DEMO_CFG_PIXEL_BUFFER_PTR
        lv_color_t *color;
#else
        lv_color_t color[APP_LVGL_DEMO_CFG_PIXEL_BUFFER_SIZE];
#endif
        vsf_eda_t *eda_poll;
    } lvgl;
#endif
} usrapp_ui_common_t;

/*============================ GLOBAL VARIABLES ==============================*/

extern usrapp_ui_common_t usrapp_ui_common;

/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

#endif      // VSF_USE_UI
#endif      // __USRAPP_UI_COMMON_H__
/* EOF */