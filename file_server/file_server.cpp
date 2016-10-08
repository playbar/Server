#include <stdio.h>
#include "base/netlib.h"
#include "base/ConfigFileReader.h"
#include "base/version.h"
#include "base/pb/protocol/IM.BaseDefine.pb.h"

#include "config_util.h"
#include "file_client_conn.h"
#include "file_msg_server_conn.h"

int main(int argc, char *argv[])
{
    if( (argc == 2) && (strcmp(argv[1], "-v") == 0))
    {
        printf("Server Version: FileServer/%s\n", VERSION);
        printf("Server Build: %s %s\n", __DATE__, __TIME__);
        return 0;
    }
    
    signal(SIGPIPE, SIG_IGN);
    CConfigFileReader config_file("fileserver.conf");
    
    char *str_client_listen_ip = config_file.GetConfigName("ClientListenIP");
    char *str_client_listen_port = config_file.GetConfigName("ClientListenPort");
    char *str_msg_server_listen_ip = config_file.GetConfigName("MsgServerListenIP");
    char *str_msg_server_listen_port = config_file.GetConfigName("MsgServerListenPort");
    
    char *str_task_timeout = config_file.GetConfigName("TaskTimeout");
    
    if( str_client_listen_ip == NULL || str_client_listen_port == NULL ||
       str_msg_server_listen_ip == NULL || str_msg_server_listen_port == NULL )
    {
        log("config item missing, exit... ");
        return 0;
    }
    
    uint16_t client_listen_port = atoi(str_client_listen_port);
    CStrExplode client_listen_ip_list( str_client_listen_ip, ';');
    std::list<IM::BaseDefine::IpAddr> q;
    for( uint32_t i = 0; i < client_listen_ip_list.GetItemCnt(); ++i)
    {
        ConfigUtil::GetInstance()->AddAddress(client_listen_ip_list.GetItem(i), client_listen_port);
    }
    
    uint16_t msg_server_listen_port = atoi(str_msg_server_listen_port);
    uint32_t task_timeout = atoi(str_task_timeout);
    
    ConfigUtil::GetInstance()->SetTaskTimeout(task_timeout);
    
    InitializeFileMsgServerConn();
    InitializeFileClientConn();
    
    int ret = netlib_init();
    if( NETLIB_ERROR == ret )
    {
        return ret;
    }
    
    for( uint32_t i = 0; i < client_listen_ip_list.GetItemCnt(); ++i)
    {
        ret = netlib_listen(client_listen_ip_list.GetItem(i), client_listen_port,
                            FileClientConnCallback, NULL);
        if (ret == NETLIB_ERROR)
        {
            printf("listen %s:%d error!!\n", client_listen_ip_list.GetItem(i), client_listen_port);
            return ret;
        }
        else
        {
            printf("server start listen on %s:%d\n", client_listen_ip_list.GetItem(i),
                   client_listen_port);
        }
    }
    
    ret = netlib_listen(str_msg_server_listen_ip, msg_server_listen_port,
                        FileMsgServerConnCallback, NULL);
    if (ret == NETLIB_ERROR)
    {
        printf("listen %s:%d error!!\n", str_msg_server_listen_ip, msg_server_listen_port);
        return ret;
    }
    else
    {
        printf("server start listen on %s:%d\n", str_msg_server_listen_ip, msg_server_listen_port);
    }
    
    printf("now enter the event loop...\n");
    
    writePid();
    
    netlib_eventloop();
    
    printf("exiting.......\n");
    log("exit");

    
    return 0;
}
