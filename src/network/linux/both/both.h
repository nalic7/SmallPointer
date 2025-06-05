#ifndef NALI_NETWORK_LINUX_BOTH_H
#define NALI_NETWORK_LINUX_BOTH_H

//s0-net
//s1-client
#define NALI_NLB_C_SYNC_PLAYER 0
#define NALI_NLB_C_ADD_MODEL 1
//e1-client

//s1-server
#define NALI_NLB_S_KEY_PLAYER 0

//s2-key
#define NALI_NLB_S_KEY_W 1
#define NALI_NLB_S_KEY_A 1 << 1
#define NALI_NLB_S_KEY_S 1 << 2
#define NALI_NLB_S_KEY_D 1 << 3
#define NALI_NLB_S_KEY_SPACE 1 << 4
#define NALI_NLB_S_KEY_CTRL 1 << 5
#define NALI_NLB_S_KEY_LEFT_CLICK 1 << 6
#define NALI_NLB_S_KEY_LEFT 1 << 7
#define NALI_NLB_S_KEY_RIGHT 1 << 8
#define NALI_NLB_S_KEY_UP 1 << 9
#define NALI_NLB_S_KEY_DOWN 1 << 10
#define NALI_NLB_S_KEY_RIGHT_CLICK 1 << 11
//e2-key
//e1-server
//e0-net

// #define NALI_NLB_PASSWORD
void nlb_loop();

#endif