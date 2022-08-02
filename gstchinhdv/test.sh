gst-launch-1.0 \
    filesrc location=~/test.mp4 ! \
    decodebin ! videoconvert ! capsfilter caps="video/x-raw,format=BGRx" !\
    fpsdisplaysink video-sink=autovideosink sync=true

