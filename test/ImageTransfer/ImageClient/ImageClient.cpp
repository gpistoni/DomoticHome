#include "stdafx.h"


//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2014 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>


#include <boost/asio.hpp>
#include <opencv2/opencv.hpp>
#include <Windows.h>

using boost::asio::ip::tcp;

#ifdef _DEBUG
#define CV_VER "300d"
#else
#define CV_VER "300"
#endif

#pragma comment(lib, "opencv_core"CV_VER".lib")
#pragma comment(lib, "opencv_imgproc"CV_VER".lib")
#pragma comment(lib, "opencv_highgui"CV_VER".lib")
#pragma comment(lib, "opencv_video"CV_VER".lib")
#pragma comment(lib, "opencv_objdetect"CV_VER".lib")
#pragma comment(lib, "opencv_imgcodecs"CV_VER".lib")
#pragma comment(lib, "opencv_features2d"CV_VER".lib")


using boost::asio::ip::tcp;
using namespace std; // For strlen.

enum { max_length = 255 };

int main(int argc, char* argv[])
{
	try
	{
		//std::string host = "172.31.11.24", port = "8080" ;
		std::string host = "localhost", port = "8080" ;

		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(tcp::v4(), host, port );
		tcp::resolver::iterator iterator = resolver.resolve(query);

		tcp::socket s(io_service);
		boost::asio::connect(s, iterator);

		while (1)
		{
			try
			{
				char request1[max_length] = "1";

				COORD CursorPosition;
				CursorPosition.X = 0; 
				CursorPosition.Y = 0; 
				SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition ); 

				double t0 = cv::getTickCount();
				boost::asio::write(s, boost::asio::buffer(request1, strlen(request1)));

				char reply[max_length];
				size_t reply_length = boost::asio::read(s, boost::asio::buffer(reply, max_length), boost::asio::transfer_at_least(1) );
				double t1 = cv::getTickCount();
				int dt1 = 1000 * (t1-t0) / cv::getTickFrequency();


				if ( reply[0] == '<' )
				{				
					std::cout <<  endl << endl  << "Create Image ";
					std::cout.write(reply, reply_length);

					std::string sreply = reply;
					int p1 = sreply.find_first_of(",",0);
					int p2 = sreply.find_first_of(",",p1+1);
					int p3 = sreply.find_first_of(">",0);

					std::string s1 = sreply.substr( 1, p1-1); 
					std::string s2 = sreply.substr( p1+1, p2-p1-1);
					std::string s3 = sreply.substr( p2+1, p3-p2-1);

					cv::Mat img( std::stoi(s1), std::stoi(s2), CV_8UC3 );

					if ( img.step != std::stoi(s3) )
					{
						assert(0);
					}

					size_t size = img.step * img.rows;
					uchar * pbuffeer = img.ptr(0);
					char request2[max_length] = "2";

					double t2 = cv::getTickCount();
					boost::asio::write(s, boost::asio::buffer(request2, strlen(request2)));

					reply_length = boost::asio::read(s, boost::asio::buffer( pbuffeer, size), boost::asio::transfer_at_least( size ) );	
					std::cout << endl << "KBytes" << reply_length / 1000;

					double t3 = cv::getTickCount();
					int dt3 = 1000 * (t3-t2) / cv::getTickFrequency();

					double t4 = cv::getTickCount();
					int dt4 = 1000 * (t4-t0) / cv::getTickFrequency();

					std::cout << endl << "Header: " << dt1;
					std::cout << "ms Image:" << dt3 << "ms Total:" << dt4 <<  "ms";
					std::cout << " -- Image: " << reply_length / 1024.0 / 1024.0 / dt3 * 1000 << " Mb/s" <<" OverAll: " << reply_length / 1024.0 / 1024.0 / dt4 * 1000 << " Mb/s";

					cv::imshow("out", img);
					cv::waitKey(50);
				}
			}
			catch (std::exception& e)
			{
				std::cerr << "Exception: " << e.what() << "\n";
			}

		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}