//
//  textFileforReadHSV.h
//  kinectExample
//
//  Created by ryoken on 2014/11/09.
//
//

#ifndef kinectExample_textFileforReadHSV_h
#define kinectExample_textFileforReadHSV_h

int read_textfile(){
    int HSV=0;
    std::ifstream ifs("/Users/user/Downloads/of_v0.8.4_osx_release/apps/myApps/Demo_kinect/HSV.txt");
    std::string str;
    
    if (ifs.fail())
    {
        std::cerr << "失敗" << std::endl;
        return EXIT_FAILURE;
    }
    
    getline(ifs, str);
    std::cout << "HELLO: [" << str << "]" << std::flush;
    //stringstream ss;
    //ss << str;
    int tmp = 0;
    for(int i = 0; i< str.length(); i++) {
        tmp *= 10;
        tmp += str[i] - '0';
    }
    //ss >> tmp;
    //sscanf(str.c_str(), "%d", &HSV);
    std::cout << "[[" << tmp << "]]" << std::flush;
    return tmp;
}

#endif
