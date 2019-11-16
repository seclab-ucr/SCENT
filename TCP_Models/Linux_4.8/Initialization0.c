#include <stdio.h>
#include "TCP_Model.h"
#include <assert.h>

//Variable Definition

int packet_dep = 0;
/*** Variables for each entity ***/
struct Model0_sk_buff Model0_Skb_In[PACKET_NUM], Model0_Skb_Out;
struct Model1_sk_buff Model1_Skb_In[PACKET_NUM], Model1_Skb_Out;
char Model0_Buff_In[PACKET_NUM][SKB_DATA_MAX_SIZE], Model0_Buff_Out[SKB_DATA_MAX_SIZE];
char Model1_Buff_In[PACKET_NUM][SKB_DATA_MAX_SIZE], Model1_Buff_Out[SKB_DATA_MAX_SIZE];
struct Model0_tcp_sock Model0_Server_L, Model0_Server_A, Model0_Server, Model0_Client;
struct Model1_tcp_sock Model1_Server_L, Model1_Server_A, Model1_Server, Model1_Client;

struct Model0_tcp_request_sock Model0_Req, Model0_Req_A;
struct Model1_tcp_request_sock Model1_Req, Model1_Req_A;

struct Model0_sock *Model0_Dst_sk; // Dst_IP
struct Model1_sock *Model1_Dst_sk; // Dst_IP
bool Model0_Src_sk, Model0_Port_guessed; //Src_sk; //true: from Attack; false: from Client //If port is guessed correctly
bool Model1_Src_sk, Model1_Port_guessed; //Src_sk; //true: from Attack; false: from Client //If port is guessed correctly

/*** Extra variables for tracking purpose ***/
short Packet_Tracking[MAX_OFFSET][PATH_LIMIT][PACKET_NUM];
short Packet_Tracking_Hash[MAX_OFFSET];
int Packet_Tracking_Index[15000];
int Packet_Tracking_Count;
short Iteration_Tracking[PACKET_NUM];

/***  Global Variables  ***/
int Model0_SKB_DATA_SIZE;
int Model0_SKB_DATA_MAX_SIZE;
Model0___be32 Model0_TCP_HP_BITS;
int Model0_packet_dep;
struct Model0_smp_ops Model0_smp_ops;
bool Model0_flag_visited1, Model0_flag_visited2;
#if CY_ABSTRACT3
unsigned int Model0_challenge_count;
Model0_u32 Model0_challenge_timestamp;
#endif
bool Model0_Connection_reset;
bool Model0_delayed_ack;
int Model0_iteration_time;
int Model0_end_iteration_time;
int Model0_packet_len;
int Model0_verify_time;
struct Model0_tcp_skb_cb *Model0_tcb, *Model0_tcb0, *Model0_tcb1; 
struct Model0_tcphdr *Model0_th, *Model0_th0, *Model0_th1;
bool Model0_Out_pkt;
unsigned long Model0_phys_base;
__typeof__(struct Model0_task_struct *) Model0_current_task;
unsigned long volatile Model0_jiffies;
Model0_u32 Model0_K_now; 
int Model0_sysctl_tcp_recovery;
int Model0_sysctl_tcp_wmem[3];
int Model0_sysctl_tcp_rmem[3];
int Model0_cpu_number;
int Model0_tcp_memory_pressure;
Model0_atomic_long_t Model0_tcp_memory_allocated;
struct Model0_percpu_counter  Model0_tcp_sockets_allocated;
struct Model0_percpu_counter  Model0_tcp_orphan_count;
long Model0_sysctl_tcp_mem[3];
int Model0_sysctl_tcp_slow_start_after_idle;
int Model0_sysctl_tcp_min_tso_segs;
int Model0_sysctl_tcp_limit_output_bytes;
int Model0_sysctl_tcp_workaround_signed_windows;
int Model0_sysctl_tcp_timestamps;
int Model0_sysctl_tcp_window_scaling;
int Model0_sysctl_tcp_sack;
int Model0_sysctl_tcp_fack;
int Model0_sysctl_tcp_max_reordering;
int Model0_sysctl_tcp_dsack;
int Model0_sysctl_tcp_app_win;
int Model0_sysctl_tcp_adv_win_scale;
int Model0_sysctl_tcp_challenge_ack_limit; 
int Model0_sysctl_tcp_stdurg;
int Model0_sysctl_tcp_rfc1337;
int Model0_sysctl_tcp_max_orphans;
int Model0_sysctl_tcp_frto;
int Model0_sysctl_tcp_min_rtt_wlen;
int Model0_sysctl_tcp_thin_dupack;
int Model0_sysctl_tcp_moderate_rcvbuf;
int Model0_sysctl_tcp_early_retrans;
int Model0_sysctl_tcp_invalid_ratelimit;

struct Model0_net Model0_init_net;
struct Model0_tcp_mib Model0_cy_tcp_mib;
struct Model0_linux_mib Model0_cy_linux_mib;
struct Model0_net Model0_NET;
struct Model0_dst_entry Model0_DST_ENTRY;

int Model0_sysctl_tcp_fastopen;
int Model0_sysctl_tcp_abort_on_overflow;
struct Model0_kmem_cache *Model0_skbuff_head_cache;

/* Model1 */

int Model1_SKB_DATA_SIZE;
int Model1_SKB_DATA_MAX_SIZE;
Model1___be32 Model1_TCP_HP_BITS;
int Model1_packet_dep;
struct Model1_smp_ops Model1_smp_ops;
bool Model1_flag_visited1, Model1_flag_visited2;
#if CY_ABSTRACT3
unsigned int Model1_challenge_count;
Model1_u32 Model1_challenge_timestamp;
#endif
bool Model1_Connection_reset;
bool Model1_delayed_ack;
int Model1_iteration_time;
int Model1_end_iteration_time;
int Model1_packet_len;
int Model1_verify_time;
struct Model1_tcp_skb_cb *Model1_tcb, *Model1_tcb0, *Model1_tcb1;
struct Model1_tcphdr *Model1_th, *Model1_th0, *Model1_th1;
bool Model1_Out_pkt;
unsigned long Model1_phys_base;
__typeof__(struct Model1_task_struct *) Model1_current_task;
unsigned long volatile Model1_jiffies;
Model1_u32 Model1_K_now;
int Model1_sysctl_tcp_recovery;
int Model1_sysctl_tcp_wmem[3];
int Model1_sysctl_tcp_rmem[3];
int Model1_cpu_number;
int Model1_tcp_memory_pressure;
Model1_atomic_long_t Model1_tcp_memory_allocated;
struct Model1_percpu_counter  Model1_tcp_sockets_allocated;
struct Model1_percpu_counter  Model1_tcp_orphan_count;
long Model1_sysctl_tcp_mem[3];
int Model1_sysctl_tcp_slow_start_after_idle;
int Model1_sysctl_tcp_min_tso_segs;
int Model1_sysctl_tcp_limit_output_bytes;
int Model1_sysctl_tcp_workaround_signed_windows;
int Model1_sysctl_tcp_timestamps;
int Model1_sysctl_tcp_window_scaling;
int Model1_sysctl_tcp_sack;
int Model1_sysctl_tcp_fack;
int Model1_sysctl_tcp_max_reordering;
int Model1_sysctl_tcp_dsack;
int Model1_sysctl_tcp_app_win;
int Model1_sysctl_tcp_adv_win_scale;
int Model1_sysctl_tcp_challenge_ack_limit;
int Model1_sysctl_tcp_stdurg;
int Model1_sysctl_tcp_rfc1337;
int Model1_sysctl_tcp_max_orphans;
int Model1_sysctl_tcp_frto;
int Model1_sysctl_tcp_min_rtt_wlen;
int Model1_sysctl_tcp_thin_dupack;
int Model1_sysctl_tcp_moderate_rcvbuf;
int Model1_sysctl_tcp_early_retrans;
int Model1_sysctl_tcp_invalid_ratelimit;

struct Model1_net Model1_init_net;
struct Model1_tcp_mib Model1_cy_tcp_mib;
struct Model1_linux_mib Model1_cy_linux_mib;
struct Model1_net Model1_NET;
struct Model1_dst_entry Model1_DST_ENTRY;

int Model1_sysctl_tcp_fastopen;
int Model1_sysctl_tcp_abort_on_overflow;
struct Model1_kmem_cache *Model1_skbuff_head_cache;
