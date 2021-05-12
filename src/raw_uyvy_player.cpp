#include <stdio.h>
#include <iostream>
#include <signal.h>
#include "gstcontrol.h"

static volatile int keepRunning = 1;

void intHandler(int dummy) 
{
    printf ("\nFinishing...\n");
    keepRunning = 0;
}

using namespace std;

GSTVideoControl *gst_control = new GSTVideoControl;

int main (int argc, char **argv)
{

    int width;
    int height;
    int framerate;
    
    signal(SIGINT, intHandler);
    
    if (argc < 5)
    {
        printf ("\nUsage: gstplayer <videofile> <width> <height> <framerate> \n");
        exit (0);
    }
    
    width = atoi (argv[2]);
    height = atoi (argv[3]);
    framerate = atoi (argv[4]);
    
    // init GStreamer 
    gst_init (&argc, &argv);
    
    if ( ! gst_control->GSTBuildPipeline (argv[1], width, height, framerate, GST_VIDEO_FORMAT_UYVY, (char *) "autovideosink"))
    {
        printf ("\nError creating gst pipeline, aborting...");
        exit (0);
    }
    
    gst_control->GSTPlay();
  
    do
    {
      
    } while (keepRunning);
      
    gst_control->GSTDeInit ();
    
    return 0;
}
