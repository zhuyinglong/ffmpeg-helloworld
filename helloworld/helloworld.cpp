#include <iostream>
#include "configs.h"

using namespace std;

int protocolinfo();
int avformatinfo();
int avcodecinfo();
int avfilterinfo();
int configurationinfo();

int main()
{
	av_register_all();
    avfilter_register_all();
	cout << "==============configurationinfo=============="<< endl;
    configurationinfo();
	cout << "==============protocolinfo==============" << endl;
	protocolinfo();
	cout << "==============avformatinfo==============" << endl;
	avformatinfo();
	cout << "==============avcodecinfo==============" << endl;
    avcodecinfo();
	cout << "==============avfilterinfo==============" << endl;
    avfilterinfo();   
	return 0;
}

int protocolinfo()
{
	void *opaque = NULL;
	const char *name;

	while ((name = avio_enum_protocols(&opaque, 0)))
	{ 
		cout << "[In]"<< name << endl;
	}
	cout << "====>Supported Output file protocols:" << endl;
	while ((name = avio_enum_protocols(&opaque, 1)))
	{
		cout <<"[Out]"<< name << endl;
	}
	return 0;
}

int avformatinfo()
{
	AVInputFormat *if_temp = av_iformat_next(NULL);
	AVOutputFormat *of_temp = av_oformat_next(NULL);

	while (if_temp != NULL) 
	{
		cout << "[In]" << if_temp->name << endl;
		if_temp = if_temp->next;
	}
	while (of_temp != NULL) 
	{
		cout << "[Out]" << of_temp->name << endl;
		of_temp = of_temp->next;
	}
	return 0;
}

int avcodecinfo()
{
	AVCodec *c_temp = av_codec_next(NULL);
	while (c_temp != NULL) 
	{
		if (c_temp->decode != NULL) 
		{
			cout << "[Dec]";
		}
		else 
		{
			cout << "[Enc]";
		}
		switch (c_temp->type) 
		{
			case AVMEDIA_TYPE_VIDEO:
				cout<<"[Video]";
				break;
			case AVMEDIA_TYPE_AUDIO:
				cout<<"[Audio]";
				break;
			default:
				cout<<"[Other]";
				break;
		}

		cout << c_temp->name << endl;
		c_temp = c_temp->next;
	}
	return 0;
}

int avfilterinfo()
{
	AVFilter *f_temp = (AVFilter *)avfilter_next(NULL);

	while (f_temp != NULL) 
	{
		cout << f_temp->name << endl;
		f_temp = f_temp->next;
	}
	return 0;
}


int configurationinfo()
{
	cout << avcodec_configuration() << endl;
	return 0;
}