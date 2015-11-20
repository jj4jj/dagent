#pragma  once
#include "stdinc.h"

NS_BEGIN(dcsutil)

	class noncopyable
	{
	protected:
		noncopyable() {}
		~noncopyable() {}
	private: // emphasize the following members are private  
		noncopyable(const noncopyable&);
		const noncopyable& operator=(const noncopyable&);
	};

	//time 
	uint64_t		time_unixtime_ms();
	uint64_t		time_unixtime_us();
	int				daemonlize(int closestd = 1, int chrootdir = 0);
	int				readfile(const char * file, char * buffer, size_t sz);
	int				writefile(const char * file, const char * buffer, size_t sz = 0);
	//-1:open file error , getpid():lock ok , 0:lock error but not known peer, >0: the locker pid.
	int				lockpidfile(const char * pidfile, int kill_other_sig = 0, bool nb = true);
	int				split(const std::string & str, const string & sep, std::vector<std::string> & vs);
	const char*		strftime(std::string & str, time_t unixtime = 0, const char * format = "%Y-%m-%d %H:%M:%S");
	time_t			from_strtime(const char * strtime = "1970-1-1 08:00:00");


NS_END()