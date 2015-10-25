#include "dcnode/dcnode.h"
#include "base/stdinc.h"
#include "base/utility.hpp"

static int total = 0;
static int ncur = 0;
uint64_t	start_time = 0;
static int pingpong(void * ud, const char* src, const msg_buffer_t & msg)
{
	dcnode_t * dc = (dcnode_t*)(ud);
	ncur++;
	if (ncur == 1){
		start_time = util::time_unixtime_us();
	}
	if (ncur < total){
		dcnode_send(dc, src, msg.buffer, msg.valid_size);
	}
	else {
		uint64_t current_time = util::time_unixtime_us();
		uint64_t cost_time = current_time - start_time;
		double speed = total / cost_time;
		printf("pingpong test result msg length:%d count:%d time:%luus speed qpus:%lf qps:%lf\n",
			msg.valid_size, total, cost_time, speed, speed*1000000);
	}
	return 0;
}

static dcnode_t* _create(bool ping, const char* name, const char * key,
	const char* listen_tcp , const char * conn_tcp ){
	dcnode_config_t dcf;
	dcf.addr.msgq_path = key;
	dcf.addr.msgq_push = ping;
	dcf.max_channel_buff_size = 1024 * 1024;
	dcf.name = name;
	dcf.heart_beat_gap = 10;
	dcf.max_live_heart_beat_gap = 20;
	dcf.addr.parent_addr = conn_tcp; ;
	dcf.addr.listen_addr = listen_tcp;
	auto dc = dcnode_create(dcf);
	if (!dc){
		LOGP("creat dcnode error !");
		return nullptr;
	}
	dcnode_set_dispatcher(dc, pingpong, dc);
	return dc;
}
void usage(){
	puts("./pingpong <mode:c|s> <mq|tcp|dcn> <tcpaddr|msgqpath> <max>");
	puts("eg:");
	puts("./pingpong c mq ./pingpong 10000000");
	puts("./pingpong s mq ./pingpong 10000000");
	puts("./pingpong c tcp 127.0.0.1:8888 10000000");
	puts("./pingpong s tcp 127.0.0.1:8888 10000000");
	puts("./pingpong c dcn ./pingpong;127.0.0.1:8888	#agent connect to 8888;");
	puts("./pingpong s dcn ./pingpong;127.0.0.1:8888	#agent listen to 8888;");
}

int main(int argc , char * argv[]){
	logger_config_t loger_conf;
	global_logger_init(loger_conf);
	if (argc < 5){
		usage();
		return -1;
	}
	bool ping = argv[1][0] == 'c';
	const char * key = argv[3];
	char * tcpaddr = argv[3];
	const char * name = "mqc";
	const char * listen_tcpaddr = "";
	const char * conn_tcpaddr = "";

	if (strcmp(argv[2], "mq") == 0){
		tcpaddr = "";
		if (ping) name = "mqc";
		else name = "mqs";
	}
	else if(strcmp(argv[2],"tcp") == 0){
		key = "";
		if (ping) {
			name = "tcpc";
			conn_tcpaddr = tcpaddr;
		}
		else{
			name = "tcps";
			listen_tcpaddr = tcpaddr;
		}
	}
	else {//dcn
		tcpaddr = strchr(tcpaddr, ';');
		*tcpaddr = 0;
		tcpaddr += 1;
		if (ping){
			name = "agent:c";
			conn_tcpaddr = tcpaddr;
		}
		else{
			name = "agent:s";
			listen_tcpaddr = tcpaddr;
		}
		ping = false;
	}
	string sname = name;
	sname[sname.length() - 1] = 's';
	int maxn = atoi(argv[4]);
	total = maxn;
	bool start = false;
	const char * s_sendbuff = "PingPong: Hello?";
	string s_send_msg = s_sendbuff;
	//for (auto i = 0; i < 20; i++) s_send_msg += s_send_msg;
	LOGP("pingpong msg :%s length:%zu", s_send_msg.c_str(), s_send_msg.length());
	dcnode_t* dc = _create(ping, name, key, listen_tcpaddr, conn_tcpaddr);
	if (!dc){
		LOGP("create dncode error !");
		return -2;
	}
	logger_set_level(nullptr, LOG_LVL_INFO);
	while (true)
	{
		dcnode_update(dc, 1000);
		if (dcnode_ready(dc) && ping && !start){
			dcnode_send(dc, sname.c_str(), s_send_msg.c_str(), s_send_msg.length());
			start = true;
		}
		if (dcnode_stoped(dc)){
			LOGP("dcnode stoped ....");
			return -1;
		}
		usleep(1000);
	}
	return 0;
}

