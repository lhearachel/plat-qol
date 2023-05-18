#ifndef __FIELD_H
#define __FIELD_H

struct FieldState {
    void *processControl;
    void *mapData;
    void *graphicsSystem;
    void *saveData;
    void *eventController;
    void *eventData;
    int  subscreenType;         // 1 = poketch, 2 = underground, 3 = union room, 4 = no poketch
    void *location;
    int  fieldCameraType;       // 0 = normal,  1 = angled
    void *camera;
    void *mapStitchingData;     // this is used for figuring out what maps to load/unload based on player pos
    void *worldMap;
    void *mapResource;
    void *mmdl;
    void *fieldObjects;
    void *playerState;
    // rest from here is undocumented, glhf
};

#endif // __FIELD_H