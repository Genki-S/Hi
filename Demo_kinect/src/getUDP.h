//
//  getUDP.h
//  recv_fext
//
//  Created by ryokenmiyazaki on 2014/07/31.
//  Copyright (c) 2014年 ryoken miyazaki. All rights reserved.
//

#ifndef recv_fext_getUDP_h
#define recv_fext_getUDP_h
#include "textFileforSendHSV.h"
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>

#include <pthread.h>



pthread_t leapMotionThread;
bool thread_flag;
void leap_receive(int testdata);
double leap_velocity;

struct
{
    int color;//オーラの色
    std::string message;//受信メッセージ
    int pushlike;//mark
    int pushjoin;//mark
    
} typedef KinectData;

KinectData kinect_data;

void LeapThreadInit()
{
    kinect_data.color=0;
    kinect_data.message="";
    kinect_data.pushlike=0;
    kinect_data.pushjoin=0;
	std::cout << "Starting External Froce thread...." << std::endl;
	thread_flag = true;
	pthread_create(&leapMotionThread, NULL, (void *(*)(void *))&leap_receive, (void *)NULL);
}

void leap_receive(int testdata)
{
	//std::cout << "External Froce thread started" << std::endl;
	while(thread_flag) {
		double vel;
		int sd;
		struct sockaddr_in addr;
		char tmp[128];
        
		socklen_t sin_size;
		struct sockaddr_in from_addr;
        
		char buf[128]; // 受信バッファ
        
		// IPv4 UDP のソケットを作成
		if((sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
			perror("socket");
			break;
		}
        
		// 待ち受けるIPとポート番号を設定
		addr.sin_family = AF_INET;
		addr.sin_port = htons(55555);//任意の値
		addr.sin_addr.s_addr = INADDR_ANY;//inet_addr("127.0.0.1");//INADDR_ANY; すべてのアドレス宛のパケットを受信する
        
		// バインドする
		if(bind(sd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
			perror("bind");
			break;
		}
		//ノンブロッキング設定
		//int val = 1; // ノンブロッキング
		int val = 0; // ブロッキング
		ioctl(sd, FIONBIO, &val);
        
		// 受信バッファの初期化
		memset(buf, 0, sizeof(buf));
        
		int len = recv(sd, buf, sizeof(buf), 0);
        std::cout << "recv:"<<len <<std::endl;
		if(len>0) {
			int tmpcolor=0;
            int tmppushlike=0;
            int tmppushjoin=0;
            char tmpmessage[128];
            memset(tmpmessage, 0, sizeof(tmpmessage));
            printf("%s\n", buf);
            //like,hi,hsv,message
			sscanf(buf, "%d,%d,%d,%[^¥n]", &tmppushlike, &tmppushjoin, &tmpcolor, tmpmessage);
            kinect_data.color=tmpcolor;
            kinect_data.message=tmpmessage;
            kinect_data.pushlike=tmppushlike;
            kinect_data.pushjoin=tmppushjoin;
            
            creat_textfile(kinect_data.color);
            //HSV = kinect_data.color;
		}
		else {
		}
        
		// ソケットのクローズ
		close(sd);
        
		// 受信データの出力
		//printf("%s\n", buf);
        
		//数値に戻す。
		//scanfにする
		//vel = atoi(buf);
		//sscanf(buf.c_str(), "%lf", &vel);
	}
}



int LeapMotionInit()
{/*
  // IPv4 UDP のソケットを作成
  if((sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
  perror("socket");
  return -1;
  }
  
  // 待ち受けるIPとポート番号を設定
  addr.sin_family = AF_INET;
  addr.sin_port = htons(12345);//任意の値
  addr.sin_addr.s_addr = INADDR_ANY;//inet_addr("127.0.0.1");//INADDR_ANY; すべてのアドレス宛のパケットを受信する
  
  // バインドする
  if(bind(sd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
  perror("bind");
  return -1;
  }
  //ノンブロッキング設定
  int val = 1;
  ioctl(sd, FIONBIO, &val);
  
  return 0;*/
}

double FromLeapMotion()
{
    double vel;
    int sd;
    struct sockaddr_in addr;
    char tmp[32];
    
    socklen_t sin_size;
    struct sockaddr_in from_addr;
    
    char buf[32]; // 受信バッファ
    
    // IPv4 UDP のソケットを作成
    if((sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		return -1;
    }
    
    // 待ち受けるIPとポート番号を設定
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);//任意の値
    addr.sin_addr.s_addr = INADDR_ANY;//inet_addr("127.0.0.1");//INADDR_ANY; すべてのアドレス宛のパケットを受信する
    
    // バインドする
    if(bind(sd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		return -1;
    }
    //ノンブロッキング設定
    //int val = 1; // ノンブロッキング
    int val = 0; // ブロッキング
    ioctl(sd, FIONBIO, &val);
    
    // 受信バッファの初期化
    memset(buf, 0, sizeof(buf));
    
    //select文の追加
    fd_set fds;
    std::cout << "1" << std::endl;
    select(sd,&fds,NULL,NULL,NULL);
    std::cout << "2" << std::endl;
    
	if(FD_ISSET(sd,&fds)){
        
		// 受信 パケットが到着するまでブロック
		// ブロックしない
		// from_addr には、送信元アドレスが格納される
        
		if(recvfrom(sd, buf, sizeof(buf), 0,
                    (struct sockaddr *)&from_addr, &sin_size) < 0) {
			//perror("recvfrom");
			//return -1;
		}
		std::cout << buf << std::endl;
	}
	else{
        
		//strcpy(buf, tmp);
		std::cout << "No data" << std::endl;
	}
    
    
    // ソケットのクローズ
    close(sd);
    
    // 受信データの出力
    //printf("%s\n", buf);
    
    //数値に戻す。
    //scanfにする
    //vel = atoi(buf);
    //sscanf(buf.c_str(), "%lf", &vel);
    sscanf(buf, "%lf", &vel);
    //strcpy(tmp, buf);
    return vel;
}

void LeapMotionEnd()
{
    thread_flag = false;
    //close(sd);
}



#endif
