//
// Created by Steven Roddan on 12/21/2025.
//

#ifndef WARPLIB_DEVICE_API_HPP
#define WARPLIB_DEVICE_API_HPP

#ifdef _WIN32
#ifdef WARP_DEVICE_EXPORTS
    #define WARP_DEVICE_API __declspec(dllexport)
  #else
    #define WARP_DEVICE_API __declspec(dllimport)
  #endif
#else
#define WARP_DEVICE_API
#endif

#endif //WARPLIB_DEVICE_API_HPP
