#pragma once

class cKException { // Wyj�tek
public:
	const char * info;
	cKException(const char * info):info(info) {}
};

class cKException_Msg:public cKException { // Wyj�tek
public:
	const struct sIMessage_base * msg;
	cKException_Msg(const char * info , const sIMessage_base * msg):cKException(info), msg(msg) {}
};
