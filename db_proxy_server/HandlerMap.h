#ifndef __HANDLERMAP_H__
#define __HANDLERMAP_H__


#include "../base/util.h"
#include "ProxyTask.h"

typedef map<uint32_t, pdu_handler_t> HandlerMap_t;

class CHandlerMap
{
public:
	virtual ~CHandlerMap();

	static CHandlerMap* getInstance();

	void Init();
	pdu_handler_t GetHandler(uint32_t pdu_type);
private:
	CHandlerMap();

private:
	static  CHandlerMap* s_handler_instance;

	HandlerMap_t 	m_handler_map;
};

#endif /* __HANDLERMAP_H__ */
