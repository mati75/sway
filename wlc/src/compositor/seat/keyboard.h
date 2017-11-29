#ifndef _WLC_KEYBOARD_H_
#define _WLC_KEYBOARD_H_

#include <stdint.h>
#include <stdbool.h>
#include <wlc/wlc.h>
#include <wayland-util.h>
#include "resources/resources.h"

enum wl_keyboard_key_state;

struct wl_list;
struct wl_resource;
struct xkb_state;
struct wlc_keymap;
struct wlc_view;
struct wlc_client;
struct wlc_modifiers;

struct wlc_keyboard {
   struct wlc_keymap *keymap;
   struct wlc_source resources;
   struct chck_iter_pool keys;

   struct {
      struct wl_event_source *repeat;
   } timer;

   struct {
      struct chck_iter_pool resources;
      wlc_handle view;
   } focused;

   struct {
      uint32_t depressed;
      uint32_t latched;
      uint32_t locked;
      uint32_t group;
   } mods;

   // for interface calls (public)
   struct wlc_modifiers modifiers;

   struct {
      uint32_t delay, rate;
   } repeat;

   struct {
      struct xkb_state *xkb, *sym;
      bool repeat, repeating, focused;
   } state;
};

WLC_NONULLV(1) uint32_t wlc_keyboard_get_keysym_for_key_ptr(struct wlc_keyboard *keyboard, uint32_t key, const struct wlc_modifiers *modifiers);
WLC_NONULLV(1) uint32_t wlc_keyboard_get_utf32_for_key_ptr(struct wlc_keyboard *keyboard, uint32_t key, const struct wlc_modifiers *modifiers);

WLC_NONULLV(1) void wlc_keyboard_update_modifiers(struct wlc_keyboard *keyboard, struct libinput_device *device);
WLC_NONULL bool wlc_keyboard_request_key(struct wlc_keyboard *keyboard, uint32_t time, const struct wlc_modifiers *mods, uint32_t key, enum wl_keyboard_key_state state);
WLC_NONULL bool wlc_keyboard_update(struct wlc_keyboard *keyboard, uint32_t key, enum wl_keyboard_key_state state);
WLC_NONULL void wlc_keyboard_key(struct wlc_keyboard *keyboard, uint32_t time, uint32_t key, enum wl_keyboard_key_state state);
WLC_NONULLV(1) void wlc_keyboard_focus(struct wlc_keyboard *keyboard, struct wlc_view *view);
WLC_NONULLV(1) bool wlc_keyboard_set_keymap(struct wlc_keyboard *keyboard, struct wlc_keymap *keymap);
void wlc_keyboard_release(struct wlc_keyboard *keyboard);
WLC_NONULL bool wlc_keyboard(struct wlc_keyboard *keyboard, struct wlc_keymap *keymap);

#endif /* _WLC_KEYBOARD_H_ */
