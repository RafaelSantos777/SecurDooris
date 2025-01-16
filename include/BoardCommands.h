/**
 * @file BoardCommands.h
 * @brief Defines the commands used for communication between the boards and Node-Red in the SecurDooris system.
 *
 * This file contains the enumeration of commands that can be sent to control various components
 * of the SecurDooris system, such as turning on/off lights, uploading photos, opening doors,
 * sounding alarms, and handling NFC tags.
 */

 /**
  * @enum BoardCommand
  * @brief Enumeration of commands for board communication.
  */
enum BoardCommand {
    PING = 0, // only for nano
    TURN_ON_LIGHT = 1,
    TURN_OFF_LIGHT,
    UPLOAD_HAND_PHOTO,
    UPLOAD_INTRUDER_PHOTO,
    OPEN_DOOR,
    SOUND_ALARM,
    WARN_INVALID_NFC_TAG,
    WARN_INVALID_HAND_CODE,
    REQUEST_HAND_PHOTO_UPLOAD,
    UPDATE_SESSION, //only for nano
    NFC //only for nano
};

const bool IN_DEBUG_MODE = true;//TODO apagar dps de tudo a funcionar

