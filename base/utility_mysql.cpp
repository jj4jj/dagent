#include "logger.h"
#include "utility_mysql.h"
extern "C" {
	#include "mysql/mysql.h"
}
	
NS_BEGIN(dcsutil)

///////////////////////////////////////////////////////////////
static const int MAX_MYSQL_ERR_MSG_SZ = 1024;
struct mysqlclient_impl_t {
	MYSQL *			mysql_conn;
	mysqlclient_t::cnnx_conf_t		conf;
	std::string		error_msg;
	mysqlclient_impl_t() {
		mysql_conn = NULL;
		error_msg.reserve(MAX_MYSQL_ERR_MSG_SZ);
	}
};

#define _THIS_HANDLE	((mysqlclient_impl_t*)(handle))
#define LOG_S(format, ...)	//LOGSTR(_THIS_HANDLE->error_msg,format, ##__VA_ARGS__)

mysqlclient_t::mysqlclient_t(){
	handle = new mysqlclient_impl_t();
}
mysqlclient_t::~mysqlclient_t(){
	if (_THIS_HANDLE){
		if (_THIS_HANDLE->mysql_conn){
			mysql_close(_THIS_HANDLE->mysql_conn);
			_THIS_HANDLE->mysql_conn = NULL;
		}
		delete _THIS_HANDLE;
	}
}
//
int		mysqlclient_t::init(const mysqlclient_t::cnnx_conf_t & conf){
	//_THIS_HANDLE->conf = conf;
	//_THIS_HANDLE->mysql_conn 
	auto conn = mysql_init(NULL);
	if (!conn){
		LOG_S("mysql client init error = %d (%s)",mysql_errno(NULL), mysql_error(NULL));
		return -1;
	}
	char tmpset[255] = "";
	if (conf.wait_timeout > 0){
		sprintf(tmpset, "set wait_timeout=%d", conf.wait_timeout);
		mysql_options(conn, MYSQL_INIT_COMMAND, tmpset);
		mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &conf.wait_timeout);
		mysql_options(conn, MYSQL_OPT_READ_TIMEOUT, &conf.wait_timeout);
		mysql_options(conn, MYSQL_OPT_WRITE_TIMEOUT, &conf.wait_timeout);
	}
	if (conf.intr_timeout > 0)
	{
		sprintf(tmpset, "set interactive_timeout=%d", conf.intr_timeout);
		mysql_options(conn, MYSQL_INIT_COMMAND, tmpset);
	}
	//auto reconnect
	bool auto_reconnect = conf.auto_reconnect ? 1 : 0;
	mysql_options(conn, MYSQL_OPT_RECONNECT, &auto_reconnect);

	//connect to server
	if (!mysql_real_connect(conn, conf.ip.c_str(), conf.uname.c_str(),
		conf.passwd.c_str(), NULL, conf.port,
		conf.unisock.c_str(), conf.cliflag)){
		LOG_S("mysql_real_connectn Error %u (%s)\n",
			mysql_errno(conn), mysql_error(conn));
		goto FAIL_CONN;
	}

	if (mysql_set_character_set(conn, conf.char_set.c_str())){
		LOG_S("set charset Error %u (%s)\n",
			mysql_errno(conn), mysql_error(conn));
		goto FAIL_CONN;
	}
	if (mysql_autocommit(conn, conf.auto_commit ? 1 : 0)){
		LOG_S("auto commit set  Error %u (%s)\n",
			mysql_errno(conn), mysql_error(conn));
		goto FAIL_CONN;
	}
	////////////////////////////////////////////////
	_THIS_HANDLE->conf = conf;
	_THIS_HANDLE->mysql_conn = conn;
	return 0;
FAIL_CONN:
	conn = NULL;
	mysql_close(conn);
	return -2;
}
//return affects num
int		mysqlclient_t::execute(const std::string & sql){
	LOGP("exec sql = \n[%s]\n", sql.c_str());
	if (mysql_query(_THIS_HANDLE->mysql_conn, sql.c_str())){
		LOG_S("sql:%s excute error = %d (%s)", sql.c_str(),
			mysql_errno(_THIS_HANDLE->mysql_conn),
			mysql_error(_THIS_HANDLE->mysql_conn));
		return -1;
	}
	return mysql_affected_rows(_THIS_HANDLE->mysql_conn);
}
int		mysqlclient_t::commit(){//if not auto commit
	if (mysql_commit(_THIS_HANDLE->mysql_conn)){
		LOG_S("commit error = %d(%s)",
			mysql_errno(_THIS_HANDLE->mysql_conn),
			mysql_error(_THIS_HANDLE->mysql_conn));
	}
	return 0;
}

int		mysqlclient_t::result(void * ud, result_cb_func_t cb){//get result for select
	MYSQL_RES *res_set = mysql_store_result(_THIS_HANDLE->mysql_conn);
	if (res_set == NULL){
		LOG_S("mysql_store_result failed %d (%s)",
			mysql_errno(_THIS_HANDLE->mysql_conn),
			mysql_error(_THIS_HANDLE->mysql_conn));
		return -1;
	}
	struct mysqlclient_row_t row_store;
	row_store.row_offset = 0;
	row_store.row_total = mysql_num_rows(res_set);
	row_store.fields_count = mysql_field_count(_THIS_HANDLE->mysql_conn);
	bool	need_more = true;
	MYSQL_FIELD * fields_all = mysql_fetch_fields(res_set);
	if (row_store.row_total == 0){
		goto FREE_RESULT;
	}
	for (size_t i = 0; i < row_store.fields_count; ++i){
		row_store.fields_name[i] = fields_all[i].name;
	}
	for (; row_store.row_offset < row_store.row_total && need_more; ++row_store.row_offset){
		row_store.row_data = (const char **)mysql_fetch_row(res_set);
		row_store.row_length = mysql_fetch_lengths(res_set);
		cb(ud, need_more, row_store);
	}
FREE_RESULT:
	mysql_free_result(res_set);
	return row_store.row_offset;
}

int				mysqlclient_t::err_no(){
	return mysql_errno(_THIS_HANDLE->mysql_conn);
}
const char *	mysqlclient_t::err_msg(){
	return _THIS_HANDLE->error_msg.c_str();
}




NS_END()