#include "mf_devicemgr.h"
#include "mf_switch.h"

struct mf_switch * mf_switch_map[MAX_MF_SWITCH_NUM];

struct mf_switch * get_switch(uint32_t sock)
{
	return mf_switch_map[sock % MAX_MF_SWITCH_NUM];
}

void add_switch(struct mf_switch* sw)
{
	mf_switch_map[sw->sockfd % MAX_MF_SWITCH_NUM] = sw;
}