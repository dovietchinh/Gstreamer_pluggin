#include "main.hpp"
#include <gst/gst.h>
#include <gflags/gflags.h>

DEFINE_int32(flip_mode,0,"This is flip mode");

static bool handle_gflags1(const char *flagname,  int value){
    switch (value)
    {
    case 0:
        return true;
        break;
    case 1:
        return true;
        break;
    default:
        return false;
        break;
    };
    return false;
};
DEFINE_validator(flip_mode,&handle_gflags1);

int main(int argc,char** argv){
    gst_init(&argc,&argv);
    gflags::ParseCommandLineFlags(&argc,&argv,true);
    gflags::ShutDownCommandLineFlags();
    cout << "flip_mode: " << FLAGS_flip_mode << endl;
    cout << ".......   " << endl;
    GstElement *src{NULL},*sink{NULL},*filter{NULL},*filter2,*pipeline{NULL};
    GstBus *bus;
    GstMessage *message;
    
    src = gst_element_factory_make("filesrc","src");
    g_object_set(src,"location","~/test.mp4",NULL);
    GstElementFactory *factory = gst_element_factory_find("chinhdv");
    if(!factory){
        cout << "can not import plugin" << endl;
        return EXIT_FAILURE;
    }
    filter = gst_element_factory_create(factory,"filter");
    filter2 = gst_element_factory_make("decodebin","filter2");
    // g_object_set(filter,"silent",'fal',NULL);
    // sink = gst_element_factory_make("fpsdisplaysink","sink");
    // g_object_set(sink,"video-sink","autovideosink",NULL);
    sink = gst_element_factory_make("autovideosink","sink");
    pipeline = gst_pipeline_new("test_pipeline");
    gst_bin_add_many(GST_BIN(pipeline),src,filter2,filter,sink,NULL);
    gboolean result = gst_element_link_many(src,filter2,filter2,sink,NULL);
    if(!result){
        cout << "can not link element " << endl;
        return EXIT_FAILURE;
    }


    GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    // if(!ret){
    //     cout << "can not change state of pipeline " << endl;
    //     return EXIT_FAILURE;
    // }

    bus = gst_element_get_bus(pipeline);
    message = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
    if (message != NULL) {
    GError *err;
    gchar *debug_info;

    switch (GST_MESSAGE_TYPE (message)) {
      case GST_MESSAGE_ERROR:
        gst_message_parse_error (message, &err, &debug_info);
        g_printerr ("Error received from element %s: %s\n",
            GST_OBJECT_NAME (message->src), err->message);
        g_printerr ("Debugging information: %s\n",
            debug_info ? debug_info : "none");
        g_clear_error (&err);
        g_free (debug_info);
        break;
      case GST_MESSAGE_EOS:
        g_print ("End-Of-Stream reached.\n");
        break;
      default:
        /* We should not reach here because we only asked for ERRORs and EOS */
        g_printerr ("Unexpected message received.\n");
        break;
    }
    gst_message_unref (message);
    }
    gst_object_unref(bus);
    gst_element_set_state(pipeline,GST_STATE_NULL);
    gst_object_unref(pipeline);
    return EXIT_SUCCESS;
}