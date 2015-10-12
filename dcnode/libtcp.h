#pragma once



struct stcp_msg_t
{
    const char * buff;
    int   buff_sz;
};

struct stcp_addr_t
{
    char ip[32];
    int  port;
};
struct stcp_config_t
{
    int is_server; //0:client, 1:server
    int max_recv_buff;
    int max_send_buff;
    stcp_addr_t listen_addr;
};

struct stcp_t;

enum stcp_event_type
{
    STCP_CONNECTED = 0, //client :connected, server:new connection
    STCP_CLOSED ,
    STCP_READ ,
    STCP_WRITE ,
    STCP_EVENT_MAX
};

struct stcp_event_t
{
    stcp_event_type type;
    stcp_t  *       stcp;
    const stcp_msg_t *  msg;
};

typedef void (*stcp_event_cb_t)(stcp_t*, const stcp_event_t & ev);

struct stcp_t * stcp_create(const stcp_config_t & conf);
void            stcp_destroy(stcp_t * );
void            stcp_event_cb(stcp_t*, stcp_event_cb_t cb);
void            stcp_poll(stcp_t *,int timeout_ms);
void            stcp_listen(stcp_t *);
int             stcp_connect(stcp_t *, const stcp_addr_t & addr,int timeout_ms);//ms
bool            stcp_is_server(stcp_t *);

