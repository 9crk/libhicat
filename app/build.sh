CV_LIBPATH=../opt/opencvlib
arm-hisiv100nptl-linux-g++ lineTrack.cpp ../lib/libhisiv.a -I../include -lpthread -lm -o lineTrack

arm-hisiv100nptl-linux-g++ capture.cpp ../lib/libhisiv.a -I../include -lpthread -lm -o capture -I$CV_LIBPATH/include/opencv -I$CV_LIBPATH/include -L$CV_LIBPATH/lib/ -lopencv_highgui -lopencv_imgproc -lopencv_core -Wno-psabi

arm-hisiv100nptl-linux-g++ match.cpp ../lib/libhisiv.a -I../include -o match -I$CV_LIBPATH/include -I$CV_LIBPATH/include/opencv -L$CV_LIBPATH/lib -lopencv_highgui -lopencv_imgproc -lopencv_core -lpthread
