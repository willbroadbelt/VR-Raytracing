
/* 
 * File:   vrsystem.cpp
 * Author: willbroadbelt
 * 
 * Created on 30 November 2017, 12:17
 */
/*
#include "vrsystem.h"

#include <stdio.h>

VRsystem::VRsystem() {
    
    vr::EVRInitError eError = vr::VRInitError_None;
    m_pHMD = vr::VR_Init(&eError, vr::VRApplication_Scene);

    if (eError != vr::VRInitError_None) {
        m_pHMD = NULL;
        char buf[1024];
        snprintf(buf, sizeof ( buf), "Unable to init VR runtime: %s", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "VR_Init Failed", buf, NULL);
        exit(EXIT_FAILURE);
    }


    m_pRenderModels = (vr::IVRRenderModels *)vr::VR_GetGenericInterface(vr::IVRRenderModels_Version, &eError);
    if (!m_pRenderModels) {
        m_pHMD = NULL;
        vr::VR_Shutdown();

        char buf[1024];
        snprintf(buf, sizeof ( buf), "Unable to get render model interface: %s", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "VR_Init Failed", buf, NULL);
        exit(EXIT_FAILURE);
    }
    

}
 * */