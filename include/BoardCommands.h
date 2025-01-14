enum BoardCommand {
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

const bool IN_UNO_DEBUG_MODE = true;//TODO apagar dps de tudo a funcionar

