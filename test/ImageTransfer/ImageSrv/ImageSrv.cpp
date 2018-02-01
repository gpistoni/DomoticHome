//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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
#pragma comment(lib, "opencv_videoio"CV_VER".lib")

class session
{
public:
	session(boost::asio::io_service& io_service)
		: socket_(io_service)
	{
		std::cout << "Nuova Sessione creata " << std::endl;
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		m_img = cv::imread( "\\img.bmp", 1);

		cv::resize( m_img, m_img, cv::Size( 4000, 4000 ) );

		std::cout << "Immagine x:" << m_img.cols << " y:" << m_img.rows << std::endl;
		
		std::cout << "Nuova Sessione avviata " << std::endl;
		socket_.async_read_some(boost::asio::buffer( m_data_r, max_length ),
			boost::bind(&session::handle_read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));


		m_stream1.open(0);		//0 is the id of video device.0 if you have only one camera.
			
		if (!m_stream1.isOpened())
		{ //check if video device has been initialised
			std::cout << "cannot open camera";
		}
	}

private:
	void handle_read(const boost::system::error_code& error,
		size_t bytes_transferred)
	{

		if (m_stream1.isOpened())
		{
			cv::Mat cameraFrame;
			m_stream1.read(cameraFrame);
			cv::imshow("cam", cameraFrame);
			cv::waitKey(30);

			cv::resize( cameraFrame, m_img, cv::Size( 400, 400 ) );
		}

		if (!error)
		{
			std::string cmd;
			m_data_r[ bytes_transferred ] = 0;		//termino stringa
			cmd = m_data_r;
						
			if ( cmd == "1" )
			{
				char sbuffer[255];
				sprintf( sbuffer, "<%i,%i,%i>", m_img.cols,  m_img.rows, (size_t) m_img.step );
		
				std::string pbuffer = sbuffer;
				boost::asio::async_write( socket_,
					boost::asio::buffer( pbuffer.c_str(), pbuffer.size()  ),
				boost::bind(&session::handle_write,  this, boost::asio::placeholders::error));
			}
			else if ( cmd == "2" && m_img.cols > 0  && m_img.rows )
			{
				uchar *pbuffeer = m_img.ptr(0);
				long long size = m_img.step * m_img.rows;

				boost::asio::async_write( socket_,
					boost::asio::buffer( (void*) pbuffeer, size ),
				boost::bind(&session::handle_write,  this, boost::asio::placeholders::error));
			}
			else
			{
				std::string pbuffer = "?";
				boost::asio::async_write( socket_,
					boost::asio::buffer( pbuffer.c_str(), pbuffer.size()  ),
				boost::bind(&session::handle_write,  this, boost::asio::placeholders::error));
			}
		}
		else
		{
			delete this;
		}
	}

	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			std::cout << "Write data " << m_data_r << std::endl;
			socket_.async_read_some( boost::asio::buffer( m_data_r, max_length ),
				boost::bind(&session::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			delete this;
		}
	}

	tcp::socket socket_;
	enum { max_length = 1024 };
	char m_data_r[max_length];
	cv::Mat m_img;
	cv::VideoCapture m_stream1;
};

class server
{
public:
	server(boost::asio::io_service& io_service, short port)
		: io_service_(io_service),
		acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
	{
		start_accept();
	}

private:
	void start_accept()
	{
		std::cout << "In attesa di una nuova Sessione " << std::endl;
		session* new_session = new session(io_service_);
		acceptor_.async_accept(new_session->socket(),
			boost::bind(&server::handle_accept, this, new_session,
			boost::asio::placeholders::error));
	}

	void handle_accept(session* new_session,
		const boost::system::error_code& error)
	{
		if (!error)
		{
			new_session->start();
		}
		else
		{
			delete new_session;
		}

		start_accept();
	}

	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;
};

int main(int argc, char* argv[])
{
	try
	{
		boost::asio::io_service io_service;

		using namespace std; // For atoi.

		std::cout << "Server Start port 8080" << std::endl;
		server s( io_service, 8080 );

		io_service.run();

	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}

