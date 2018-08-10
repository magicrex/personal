#include <glog/logging.h>

 

int main(int argc,char* argv[])
{
    google::InitGoogleLogging((const char *)argv[0]);
    fLS::FLAGS_log_dir="./log/";
    LOG(WARNING) << "thisis the 1st warning!";
    return 0;
}
