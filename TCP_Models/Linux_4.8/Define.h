#ifndef DEFINE_H
#define DEFINE_H

#include <stdio.h>

#define SKB_DATA_MAX_SIZE 1000
#define PACKET_NUM 4
#define PATH_LIMIT 3
#define CY_ABSTRACT0 1 //remove static temporary so we can reuse function for packet initialization
#define CY_ABSTRACT1 1 //Interface outside current file
#define CY_ABSTRACT2 1 //Time related abstraction. To avoid state explosion, we fix time
#define CY_ABSTRACT3 1 //stub function
#define CY_ABSTRACT4 1 //Own abstraction, such as reset flag, similar to type3
#define CY_ABSTRACT6 1 //abstract assembly language (ASM), which would cause errors in KLEE
#define CY_ABSTRACT7 1 //replace function pointer with actual function
#define CY_ABSTRACT10 1 //abstraction that I'm not sure
//#define CY_NEWDEBUG 1 //related to taint. Have to set it true

#if CY_DEBUG0
//#define DEBUG_PRINT(...) fprintf(stderr, __VA_ARGS__)
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

//#define META_PRINT(...) fprintf(stderr, __VA_ARGS__)
#define META_PRINT(...) printf(__VA_ARGS__)

/* TCP Logic related */
#define Model0_MAX_TCP_WINDOW 32767U 
#define Model1_MAX_TCP_WINDOW 32767U 

/* map array size to trace a packet sequence to reach specific branch condition */
#define MAX_OFFSET 15000*200 // maximum basic block * basic offset

//skb_try_coalesce
void Taint_Source();
void Test_Value();
void Model0_Listen_Server_Initialize();
void Model1_Listen_Server_Initialize();
void Model0_SKB_Initialize(int pkt_depth);
void Model1_SKB_Initialize(int pkt_depth);
void Model0_Client_Initialize();
void Model1_Client_Initialize();
void Model0_Server_Initialize();
void Model1_Server_Initialize();
void Model0_Server_A_Initialize();
void Model1_Server_A_Initialize();
void Model0_Taint_Globals();
void Model1_Taint_Globals();
void Pair_Difference();
void Packet_Initialization();
void Model0_Global_Initialize();
void Model1_Global_Initialize();

#define Model0_TCP_ADD_STATS(x, val) x=x+val
#define Model0_NET_INC_STATS(x) x=x+1
#define Model0_TCP_INC_STATS(x) x=x+1
#define Model0_NET_ADD_STATS(x, val) x=x+val
#define Model0_NET_INC_STATS_BH(x) x=x+1
 
#define Model1_TCP_ADD_STATS(x, val) x=x+val
#define Model1_NET_INC_STATS(x) x=x+1
#define Model1_TCP_INC_STATS(x) x=x+1
#define Model1_NET_ADD_STATS(x, val) x=x+val
#define Model1_NET_INC_STATS_BH(x) x=x+1

#endif
