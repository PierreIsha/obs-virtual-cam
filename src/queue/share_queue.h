#pragma once

#include <Windows.h>
#include "libavutil/pixfmt.h"
#include "libavutil/samplefmt.h"

#define AUDIO_SIZE 4096
#define MAPPING_NAMEV  "OBSVirtualVideo"
#define MAPPING_NAMEV2 "OBSVirtualVideo2"
#define MAPPING_NAMEV3 "OBSVirtualVideo3"
#define MAPPING_NAMEV4 "OBSVirtualVideo4"
// TODO16
#define MAPPING_NAMEV5 "OBSVirtualVideo5"
#define MAPPING_NAMEV6 "OBSVirtualVideo6"
#define MAPPING_NAMEV7 "OBSVirtualVideo7"
#define MAPPING_NAMEV8 "OBSVirtualVideo8"
#define MAPPING_NAMEV9 "OBSVirtualVideo9"
#define MAPPING_NAMEV10 "OBSVirtualVideo10"
#define MAPPING_NAMEV11 "OBSVirtualVideo11"
#define MAPPING_NAMEV12 "OBSVirtualVideo12"
#define MAPPING_NAMEV13 "OBSVirtualVideo13"
#define MAPPING_NAMEV14 "OBSVirtualVideo14"
#define MAPPING_NAMEV15 "OBSVirtualVideo15"
#define MAPPING_NAMEV16 "OBSVirtualVideo16"
#define MAPPING_NAMEA  "OBSVirtualAudio"

typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

enum {
	ModeVideo = 0,
	ModeVideo2 = 1,
	ModeVideo3 = 2,
	ModeVideo4 = 3,
	// TODO16
	ModeVideo5 = 4,
	ModeVideo6 = 5,
	ModeVideo7 = 6,
	ModeVideo8 = 7,
	ModeVideo9 = 8,
	ModeVideo10 = 9,
	ModeVideo11 = 10,
	ModeVideo12 = 11,
	ModeVideo13 = 12,
	ModeVideo14 = 13,
	ModeVideo15 = 14,
	ModeVideo16 = 15,
	ModeAudio = 17,
};

enum {
	OutputStop = 0,
	OutputStart = 1,
	OutputReady = 2,
};

struct frame_header {
	uint64_t timestamp;
	uint32_t linesize[4];
	int frame_width;
	int frame_height;
};

struct queue_header {
	int state;
	int format;
	int queue_length;
	int write_index;
	int header_size;
	int element_size;
	int element_header_size;
	int delay_frame;
	int recommended_width;
	int recommended_height;
	int aspect_ratio_type;
	uint64_t last_ts;
	uint64_t frame_time;
};

struct share_queue {
	int mode =0 ;
	int index = -1;
	int operating_width;
	int operating_height;
	HANDLE hwnd =NULL;
	queue_header* header = nullptr;
};

inline char* get_mapping_name(int mode)
{
	switch (mode){
		case ModeVideo:    return MAPPING_NAMEV;
		case ModeVideo2:   return MAPPING_NAMEV2;
		case ModeVideo3:   return MAPPING_NAMEV3;
		case ModeVideo4:   return MAPPING_NAMEV4;
		// TODO16
		case ModeVideo5:   return MAPPING_NAMEV5;
		case ModeVideo6:   return MAPPING_NAMEV6;
		case ModeVideo7:   return MAPPING_NAMEV7;
		case ModeVideo8:   return MAPPING_NAMEV8;
		case ModeVideo9:   return MAPPING_NAMEV8;
		case ModeVideo10:   return MAPPING_NAMEV10;
		case ModeVideo11:   return MAPPING_NAMEV11;
		case ModeVideo12:   return MAPPING_NAMEV12;
		case ModeVideo13:   return MAPPING_NAMEV13;
		case ModeVideo14:   return MAPPING_NAMEV14;
		case ModeVideo15:   return MAPPING_NAMEV15;
		case ModeVideo16:   return MAPPING_NAMEV16;
		case ModeAudio:    return MAPPING_NAMEA;
		default:           return NULL;
	}
}

inline frame_header* get_frame_header(queue_header* qhead, int index)
{
	int offset = qhead->header_size + (qhead->element_size) * index;
	uint8_t* buff = (uint8_t*)qhead + offset;
	return (frame_header*)buff;
}

inline int cal_video_buffer_size(int format, int width, int height)
{
	int frame_size = 0;
	switch (format) { 
		case AV_PIX_FMT_YUV420P:
		case AV_PIX_FMT_NV12:
			frame_size = width * height * 3 / 2;
			break;

		case AV_PIX_FMT_GRAY8:
			frame_size = width * height;
			break;

		case AV_PIX_FMT_YUYV422:
		case AV_PIX_FMT_UYVY422:
			frame_size = width * height *2;
			break;

		case AV_PIX_FMT_RGBA:
		case AV_PIX_FMT_BGRA:
			frame_size = width * height * 4;
			break;

		case AV_PIX_FMT_YUV444P:
			frame_size = width * height * 3;
			break;	
	}

	return frame_size;
}