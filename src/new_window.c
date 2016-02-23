#include <pebble.h>
#include "new_window.h"

static Window *s_main_window;
static TextLayer *s_text_layer;

static void window_load(Window *window) {
  s_text_layer = text_layer_create(GRect(0, 40, 144, 154));
  // Set the text, font, and text alignment
  text_layer_set_text(s_text_layer, "Another Window");
  text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);

  // Add the text layer to the window
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(s_text_layer);

  window_destroy(window);
  s_main_window = NULL;
}

void new_window_push() {
  if(!s_main_window) {
    s_main_window = window_create();
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
  }
  window_stack_push(s_main_window, true);
}

