#ifndef TCP_MODEL_H
#define TCP_MODEL_H
#include "Define.h"
#include "Model0_tcp_input_defconfig.h"
#include "Model1_tcp_input_defconfig.h"
#include "Model0_extern.h"
#include "Model1_extern.h"
#include "Model0_tcp_ipv4.h"
#include "Model1_tcp_ipv4.h"

//extern State now;

extern int packet_dep;
/*** Extern Definition ***/

extern struct Model0_sk_buff Model0_Skb_In[PACKET_NUM], Model0_Skb_Out;
extern struct Model1_sk_buff Model1_Skb_In[PACKET_NUM], Model1_Skb_Out;
extern char Model0_Buff_In[PACKET_NUM][SKB_DATA_MAX_SIZE], Model0_Buff_Out[SKB_DATA_MAX_SIZE];
extern char Model1_Buff_In[PACKET_NUM][SKB_DATA_MAX_SIZE], Model1_Buff_Out[SKB_DATA_MAX_SIZE];
extern struct Model0_tcp_sock Model0_Server_L, Model0_Server_A, Model0_Server, Model0_Client;
extern struct Model1_tcp_sock Model1_Server_L, Model1_Server_A, Model1_Server, Model1_Client;

extern struct Model0_sock *Model0_Dst_sk; // Dst_IP
extern struct Model1_sock *Model1_Dst_sk; // Dst_IP
extern bool Model0_Src_sk, Model1_Src_sk; //true: from Attack; false: from Client
extern bool Model0_Port_guessed, Model1_Port_guessed; // If port is guessed correctly
//////////////////////////////////////////////////////////////
//For tracking purpose
#define MAX_OFFSET 15000*200 // maximum basic block * basic offset
extern short Packet_Tracking[MAX_OFFSET][PATH_LIMIT][PACKET_NUM];
extern short Iteration_Tracking[PACKET_NUM];
extern short Packet_Tracking_Hash[MAX_OFFSET];
extern int Packet_Tracking_Index[15000];
extern int Packet_Tracking_Count;

/***  temporary variables ***/
extern int seq_val; //seq for server
extern int ack_val; //seq for client
extern int Model0_ack_val; //seq for client
extern int Model1_ack_val; //seq for client
extern int seq_val_a; //seq for server_a
extern int ack_val_a; //seq for attacker

/***  Global Variables  ***/
extern int Model0_SKB_DATA_SIZE;
extern int Model0_SKB_DATA_MAX_SIZE;
extern Model0___be32 Model0_TCP_HP_BITS;
extern int Model0_packet_dep;
extern struct Model0_smp_ops Model0_smp_ops;
extern bool Model0_flag_visited1, Model0_flag_visited2;
#if CY_ABSTRACT3
extern unsigned int Model0_challenge_count;
extern Model0_u32 Model0_challenge_timestamp;
#endif
extern bool Model0_Connection_reset;
extern bool Model0_delayed_ack;
extern int Model0_iteration_time;
extern int Model0_end_iteration_time;
extern int Model0_packet_len;
extern int Model0_verify_time;
extern struct Model0_tcp_skb_cb *Model0_tcb, *Model0_tcb0, *Model0_tcb1; 
extern struct Model0_tcphdr *Model0_th, *Model0_th0, *Model0_th1;
extern bool Model0_Out_pkt;
extern unsigned long Model0_phys_base;
extern __typeof__(struct Model0_task_struct *) Model0_current_task;
extern unsigned long volatile Model0_jiffies;
extern Model0_u32 Model0_K_now; 
extern int Model0_sysctl_tcp_recovery;
extern int Model0_sysctl_tcp_wmem[3];
extern int Model0_sysctl_tcp_rmem[3];
extern int Model0_cpu_number;
extern int Model0_tcp_memory_pressure;
extern Model0_atomic_long_t Model0_tcp_memory_allocated;
extern struct Model0_percpu_counter  Model0_tcp_sockets_allocated;
extern struct Model0_percpu_counter  Model0_tcp_orphan_count;
extern long Model0_sysctl_tcp_mem[3];
extern int Model0_sysctl_tcp_slow_start_after_idle;
extern int Model0_sysctl_tcp_min_tso_segs;
extern int Model0_sysctl_tcp_limit_output_bytes;
extern int Model0_sysctl_tcp_workaround_signed_windows;
extern int Model0_sysctl_tcp_timestamps;
extern int Model0_sysctl_tcp_window_scaling;
extern int Model0_sysctl_tcp_sack;
extern int Model0_sysctl_tcp_fack;
extern int Model0_sysctl_tcp_max_reordering;
extern int Model0_sysctl_tcp_dsack;
extern int Model0_sysctl_tcp_app_win;
extern int Model0_sysctl_tcp_adv_win_scale;
extern int Model0_sysctl_tcp_challenge_ack_limit; 
extern int Model0_sysctl_tcp_stdurg;
extern int Model0_sysctl_tcp_rfc1337;
extern int Model0_sysctl_tcp_max_orphans;
extern int Model0_sysctl_tcp_frto;
extern int Model0_sysctl_tcp_min_rtt_wlen;
extern int Model0_sysctl_tcp_thin_dupack;
extern int Model0_sysctl_tcp_moderate_rcvbuf;
extern int Model0_sysctl_tcp_early_retrans;
extern int Model0_sysctl_tcp_invalid_ratelimit;

extern struct Model0_net Model0_NET;
extern struct Model0_dst_entry Model0_DST_ENTRY;


extern int Model1_SKB_DATA_SIZE;
extern int Model1_SKB_DATA_MAX_SIZE;
extern Model1___be32 Model1_TCP_HP_BITS;
extern int Model1_packet_dep;
extern struct Model1_smp_ops Model1_smp_ops;
extern bool Model1_flag_visited1, Model1_flag_visited2;
#if CY_ABSTRACT3
extern unsigned int Model1_challenge_count;
extern Model1_u32 Model1_challenge_timestamp;
#endif
extern bool Model1_Connection_reset;
extern bool Model1_delayed_ack;
extern int Model1_iteration_time;
extern int Model1_end_iteration_time;
extern int Model1_packet_len;
extern int Model1_verify_time;
extern struct Model1_tcp_skb_cb *Model1_tcb, *Model1_tcb0, *Model1_tcb1;
extern struct Model1_tcphdr *Model1_th, *Model1_th0, *Model1_th1;
extern bool Model1_Out_pkt;
extern unsigned long Model1_phys_base;
extern __typeof__(struct Model1_task_struct *) Model1_current_task;
extern unsigned long volatile Model1_jiffies;
extern Model1_u32 Model1_K_now;
extern int Model1_sysctl_tcp_recovery;
extern int Model1_sysctl_tcp_wmem[3];
extern int Model1_sysctl_tcp_rmem[3];
extern int Model1_cpu_number;
extern int Model1_tcp_memory_pressure;
extern Model1_atomic_long_t Model1_tcp_memory_allocated;
extern struct Model1_percpu_counter  Model1_tcp_sockets_allocated;
extern struct Model1_percpu_counter  Model1_tcp_orphan_count;
extern long Model1_sysctl_tcp_mem[3];
extern int Model1_sysctl_tcp_slow_start_after_idle;
extern int Model1_sysctl_tcp_min_tso_segs;
extern int Model1_sysctl_tcp_limit_output_bytes;
extern int Model1_sysctl_tcp_workaround_signed_windows;
extern int Model1_sysctl_tcp_timestamps;
extern int Model1_sysctl_tcp_window_scaling;
extern int Model1_sysctl_tcp_sack;
extern int Model1_sysctl_tcp_fack;
extern int Model1_sysctl_tcp_max_reordering;
extern int Model1_sysctl_tcp_dsack;
extern int Model1_sysctl_tcp_app_win;
extern int Model1_sysctl_tcp_adv_win_scale;
extern int Model1_sysctl_tcp_challenge_ack_limit;
extern int Model1_sysctl_tcp_stdurg;
extern int Model1_sysctl_tcp_rfc1337;
extern int Model1_sysctl_tcp_max_orphans;
extern int Model1_sysctl_tcp_frto;
extern int Model1_sysctl_tcp_min_rtt_wlen;
extern int Model1_sysctl_tcp_thin_dupack;
extern int Model1_sysctl_tcp_moderate_rcvbuf;
extern int Model1_sysctl_tcp_early_retrans;
extern int Model1_sysctl_tcp_invalid_ratelimit;

extern struct Model1_net Model1_NET;
extern struct Model1_dst_entry Model1_DST_ENTRY;

#endif
