#ifndef __GSTCONTROL_H__
#define __GSTCONTROL_H__

#include <gst/gst.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>

#define GST_VIDE_FORMAT_I420    2
#define GST_VIDE_FORMAT_YV12    3
#define GST_VIDE_FORMAT_YUY2    4
#define GST_VIDEO_FORMAT_UYVY   5
#define GST_VIDE_FORMAT_AYUV    6
#define GST_VIDE_FORMAT_YVYU    19
#define GST_VIDE_FORMAT_Y444    20


class GSTVideoControl
{
	
	public:
		
		bool  GSTInit 		      (void);
		bool  GSTBuildPipeline    (char *location, int width, int height, int framerate, int format, char *videosink);
		void  GSTPlay             (void);
		void  GSTStop 	          (void);
		void  GSTPause 	  	      (void);
		void  GSTDeInit           (void);		

	private:
		
        char        *__location;
		GstElement 	*__pipeline;
        GstElement *__filesrc;
        GstElement *__videoparse; 
        GstElement *__videoconvert;
        GstElement 	*__videosink;

};

#endif
