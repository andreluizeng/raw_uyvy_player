#include "gstcontrol.h"

//-------------------------------------------------------------------------------
// Name: GSTInit
// Arguments: argc, argv (command line arguments)
// Description: gstreamer initialization
// usage: object->GSTInit (&argc, &argv);
//-------------------------------------------------------------------------------
bool GSTVideoControl::GSTInit (void)
{
	
    __location = (char *) malloc (sizeof (char) * 500);

    if (! __location)
	{
		printf ("\nError allocating memory for the Location string");
		printf ("\nAborting...");
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------
// Name: GSTBuildPipeline
// Arguments: video_sink 		("fakesink", "mfw_v4lsink", "vro4l2sink", etc..)
// Arguments: location          (path to the video file)
// Description: pipeline creation
// usage: object->GSTBuildPipeline ("data/video.uyvy", "autovideosink");
//-------------------------------------------------------------------------------
bool GSTVideoControl::GSTBuildPipeline (char *location, int width, int height, int framerate, int format, char *videosink)
{
    __pipeline = gst_pipeline_new ("pipeline");
  
    __filesrc = gst_element_factory_make ("filesrc", "src");
    if(! __filesrc) 
    {
        GST_WARNING("Error in: src");
    }
    g_object_set (G_OBJECT (__filesrc), "location", location, NULL);
    
    
    __videoparse = gst_element_factory_make("videoparse", NULL);
    if(! __videoparse) 
    {
        GST_WARNING("Error in: videoparse");
    }
    
    g_object_set(G_OBJECT(__videoparse),"width", width, NULL);
    g_object_set(G_OBJECT(__videoparse),"height", height, NULL);
    g_object_set(G_OBJECT(__videoparse),"framerate", framerate, 1, NULL);
    g_object_set(G_OBJECT(__videoparse),"format", format , NULL);
    
    
    __videoconvert = gst_element_factory_make("videoconvert", NULL);
    if(! __videoconvert) 
    {
        GST_WARNING("Error in: videoconvert");
    }   
    
    __videosink = gst_element_factory_make(videosink, NULL);
    if(! __videosink) 
    {
        GST_WARNING("Error in: videosink");
    }     

    gst_bin_add_many(GST_BIN(__pipeline), __filesrc, __videoparse, __videoconvert, __videosink, NULL);

    gst_element_link_many(__filesrc, __videoparse, __videoconvert, __videosink, NULL);
    
    // gst_element_link(filesrc, videoparse);
    // gst_element_link(videoparse, videoconvert);
    // gst_element_link(videoconvert, videosink);

   	gst_element_set_state (__pipeline, GST_STATE_PAUSED);

	return TRUE;
}

//-------------------------------------------------------------------------------
// Name: GSTPlay
// Arguments: none
// Description: start playing
// usage: object->GSTPlay ();
//-------------------------------------------------------------------------------
void GSTVideoControl::GSTPlay(void)
{
	if (__pipeline)
	{
        gst_element_set_state (__pipeline, GST_STATE_PLAYING);
        if (gst_element_get_state (__pipeline, NULL, NULL, -1) == GST_STATE_CHANGE_FAILURE) 
        {    
            g_error ("Failed to go into PLAYING state");
        }

	}
	
    	else
	{
		printf ("\nError: no pipeline created\n");
	}
	
	
	return;
}

//-------------------------------------------------------------------------------
// Name: GSTStop
// Arguments: none
// Description: stop playing (needs to create another pipeline to play again)
// usage: object->GSTStop ();
//-------------------------------------------------------------------------------
void GSTVideoControl::GSTStop(void)
{
    	if (__pipeline)
    	{
        	gst_element_set_state (__pipeline, GST_STATE_NULL);
        	gst_object_unref (GST_OBJECT (__pipeline));
        	__pipeline = NULL;
    	}
    	else
	{
		printf ("\nError: no pipeline created\n");
	}
	
	return;
}

//-------------------------------------------------------------------------------
// Name: GSTPause
// Arguments: none
// Description: pause playing
// usage: object->GSTPause ();
//-------------------------------------------------------------------------------
void GSTVideoControl::GSTPause(void)
{
	if (__pipeline)
	{
		gst_element_set_state (__pipeline, GST_STATE_PAUSED);
	}
	
    	else
	{
		printf ("\nError: no pipeline created\n");
	}
	
	
	return;
}

//-------------------------------------------------------------------------------
// Name: GstDeInit
// Arguments: none
// Description: destroy the object
// usage: object->GSTFastRewind(2);
//-------------------------------------------------------------------------------
void GSTVideoControl::GSTDeInit(void)
{
	if (__pipeline)
	{
		gst_object_unref (GST_OBJECT (__pipeline));
	  	gst_element_set_state (__pipeline, GST_STATE_NULL);
	}

	
	if (__location) free (__location);
	
	gst_deinit();

	return;
}
