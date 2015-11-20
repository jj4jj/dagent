#include "utility.hpp"
#include "logger.h"

namespace dcsutil {
	uint64_t	time_unixtime_ms(){
		return time_unixtime_us() / 1000;
	}
	uint64_t	time_unixtime_us(){
		timeval tv;
		gettimeofday(&tv, NULL);
		return tv.tv_sec * 1000000 + tv.tv_usec;
	}

	int			daemonlize(int closestd, int chrootdir){
#if _BSD_SOURCE || (_XOPEN_SOURCE && _XOPEN_SOURCE < 500)
		return daemon(!chrootdir, !closestd);
#else
		assert("not implement in this platform , using nohup & launch it ?")
			return -404;//todo 
#endif
	}


	int			readfile(const char * file, char * buffer, size_t sz){
		FILE * fp = fopen(file, "r");
		if (!fp){
			LOGP("open file��%s error:%d", file, errno);
			return -1;
		}
		int n;
		size_t tsz = 0;
		while ((n = fread(buffer + tsz, 1, sz - tsz, fp))){
			if (n > 0){
				tsz += n;
			}
			else if (errno != EINTR &&
				errno != EAGAIN) {
				LOGP("read file:%s ret:%d error :%d total sz:%zu", file, n, errno, tsz);
				break;
			}
		}
		fclose(fp);
		if (n >= 0){
			if (tsz < sz){
				buffer[tsz] = 0;
			}
			return tsz;
		}
		else {
			return -2;
		}
	}
	int			writefile(const char * file, const char * buffer, size_t sz){
		FILE * fp = fopen(file, "w");
		if (!fp){
			LOGP("open file��%s error:%d", file, errno);
			return -1;
		}
		if (sz == 0){
			sz = strlen(buffer);
		}
		size_t tsz = 0;
		int n = 0;
		while ((n = fwrite(buffer + tsz, 1, sz - tsz, fp))){
			if (n > 0){
				tsz += n;
			}
			else  if (errno != EINTR &&
				errno != EAGAIN) {
				LOGP("write file:%s ret:%d error :%d writed sz:%zu total:%zu", file, n, errno, tsz, sz);
				break;
			}
		}
		fclose(fp);
		if (tsz == sz){
			return tsz;
		}
		else {
			LOGP("write file:%s writed:%zu error :%d total sz:%zu", file, tsz, errno, sz);
			return -2;
		}
	}

	int			lockpidfile(const char * pidfile, int kill_other_sig, bool nb){
		int fd = open(pidfile, O_RDWR | O_CREAT, 0644);
		if (fd == -1) {
			LOGP("open file:%s error ", pidfile);
			return -1;
		}
		int flags = LOCK_EX;
		if (nb){
			flags |= LOCK_NB;
		}
		char szpid[16] = { 0 };
		int pid = 0;
		while (flock(fd, flags) == -1) {
			if (pid == 0){ //just read once
				int n = readfile(pidfile, szpid, sizeof(szpid));
				if (n > 0){
					pid = strtol(szpid, NULL, 10);
					LOGP("lock pidfile:%s fail , the file is held by pid %d", pidfile, pid);
				}
				else {
					LOGP("lock pidfile:%s fail but read pid from file error !", pidfile);
				}
			}
			if (pid > 0 && kill_other_sig > 0){
				if (kill(pid, kill_other_sig) && errno == ESRCH){
					LOGP("killed the pidfile locker:%d by signal:%d", pid, kill_other_sig);
					break;
				}
			}
			else {
				return pid;
			}
		}
		pid = getpid();
		snprintf(szpid, sizeof(szpid), "%d", pid);
		writefile(pidfile, szpid);

		return pid;
	}
	int			split(const std::string & str, const string & sep, std::vector<std::string> & vs){
		vs.clear();
		string::size_type beg = 0;
		string::size_type pos = 0;
		//if pos not found add the rest then return , else add substr . again
		do {
			pos = str.find(sep, beg);
			if (pos == string::npos){
				if (beg < str.length()){
					vs.push_back(str.substr(beg));
				}
				return vs.size();
			}
			else { //found sep
				if (pos > beg){
					vs.push_back(str.substr(beg, pos - beg));
				}
				beg = pos + sep.length();
			}
		} while (true);
		return vs.size();
	}
	const char*		strftime(std::string & str, time_t unixtime, const char * format){
		str.reserve(32);
		if (unixtime == 0){
			unixtime = time(NULL);
		}
		struct tm _sftm;
		localtime_r(&unixtime, &_sftm);
		strftime((char*)str.c_str(), str.capacity(), format, &_sftm);
		return str.c_str();
	}
	time_t			from_strtime(const char * strtime){
		int Y = 0, M = 0, D = 0, h = 0, m = 0, s = 0;
		sscanf(strtime, "%4d-%2d-%2d %02d:%02d:%02d", &Y, &M, &D, &h, &m, &s);
		struct tm stm;
		stm.tm_year = Y - 1900;
		stm.tm_mon = M - 1;
		stm.tm_mday = D;
		stm.tm_hour = h;
		stm.tm_min = m;
		stm.tm_sec = s;
		stm.tm_isdst = 0;
		return mktime(&stm);
	}

	

}



