#ifndef MQTT_PARSER_H
#define MQTT_PARSER_H

#include <stdint.h>
#include <stddef.h>

#include "errors.h"
#include "message.h"

typedef enum mqtt_parser_rc_e {
  MQTT_PARSER_RC_ERROR       = -1,
  MQTT_PARSER_RC_CONTINUE    = 0,
  MQTT_PARSER_RC_INCOMPLETE  = 1,
  MQTT_PARSER_RC_DONE        = 2,
  MQTT_PARSER_RC_WANT_MEMORY = 3,
} mqtt_parser_rc_t;

typedef enum mqtt_parser_state_e {
  MQTT_PARSER_STATE_INITIAL = 0,
  MQTT_PARSER_STATE_REMAINING_LENGTH = 1,
  MQTT_PARSER_STATE_CONNECT_PROTOCOL_NAME = 3,
  MQTT_PARSER_STATE_CONNECT_PROTOCOL_VERSION = 4,
  MQTT_PARSER_STATE_CONNECT_FLAGS = 5,
  MQTT_PARSER_STATE_CONNECT_KEEP_ALIVE = 6,
  MQTT_PARSER_STATE_CONNECT_CLIENT_IDENTIFIER = 7,
  MQTT_PARSER_STATE_CONNECT_WILL_TOPIC = 8,
  MQTT_PARSER_STATE_CONNECT_WILL_MESSAGE = 9,
  MQTT_PARSER_STATE_CONNECT_USERNAME = 10,
  MQTT_PARSER_STATE_CONNECT_PASSWORD = 11,
} mqtt_parser_state_t;

typedef struct mqtt_parser_s {
  mqtt_parser_state_t state;
  mqtt_error_t error;
  char buffer_pending;
  uint8_t* buffer;
  size_t buffer_length;
} mqtt_parser_t;

void mqtt_parser_init(mqtt_parser_t* parser);
void mqtt_parser_buffer(mqtt_parser_t* parser, uint8_t* buffer, size_t buffer_length);
mqtt_parser_rc_t mqtt_parser_execute(mqtt_parser_t* parser, mqtt_message_t* message, uint8_t* data, size_t len, size_t* nread);

#endif
