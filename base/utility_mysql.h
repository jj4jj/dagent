#pragma  once
#include "stdinc.h"

NS_BEGIN(dcsutil)

struct mysqlclient_t {
	struct mysqlclient_row_t {
		size_t			fields_count;
		const char * *	fields_name;
		const char * *  row_data;
		size_t	*		row_length;
		//--------------------------
		size_t			row_total;
		size_t			row_offset;
	};
	struct cnnx_conf_t {
		std::string  ip;
		std::string  uname;
		std::string  passwd;
		std::string  dbname;
		std::string  unisock;
		std::string	 char_set;
		bool	auto_commit;
		bool	auto_reconnect;
		int     port;
		int     wait_timeout;
		int     intr_timeout;
		long    cliflag;
		cnnx_conf_t()
		{
			port = cliflag = wait_timeout = intr_timeout = 0;
			ip = uname = passwd = dbname = unisock = "";
			auto_commit = auto_reconnect = true;
			char_set = "utf8";
		}
	};
	void	*	handle;
	//////////////////////////////////
	mysqlclient_t();
	~mysqlclient_t();
	int			init(const cnnx_conf_t & conf);
	int			execute(const std::string & sql);
	int			commit();//if not auto commit

	//return 1:fetch next, return 0:
	typedef void	result_cb_func_t(void* ud, OUT bool & need_more, const mysqlclient_row_t & row);
	int				result(void * ud, result_cb_func_t cb);//get result for select
	//error sth 
	int				err_no();
	const char *	err_msg();
};

NS_END()
