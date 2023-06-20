#ifndef PACKETSEND_HOOKS
#define PACKETSEND_HOOKD

#if(ENABLE_INDEV_NETWORK)

void HookPacketSend();
extern CRITICAL_SECTION nSend_criti;

#endif

#endif