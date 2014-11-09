#include <iostream>
#include <fstream>
#include <string>

void creat_textfile(int HSVfromKinect) {
    
    std::ofstream ofs( "/Users/user/Downloads/of_v0.8.4_osx_release/apps/myApps/Demo_kinect/HSV.txt", std::ios::trunc );
    
    ofs << HSVfromKinect << std::endl;
    
    return 0;
}

