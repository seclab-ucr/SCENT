/*
 * Have attacker and victim client's 2 connections. No Model1.
 * Used for build the model (phase 2)
 */
//#include <stdio.h>
#include "TCP_Model.h"
#define TEST_PORT 1 //The only difference is Port
#define TEST_SEQ 0 //The only difference is Sequence
#define TEST_ACK 0 //The only difference is ACK


int seq_val = 2; //= 1; //seq for server, its value will update by SYN skb's seq value (TODO: is it good? rcv_nxt is not fixed)
int Model0_ack_val = 2; //seq for client
int Model1_ack_val = 2; //seq for client
int ack_val = 2; //Model0_ack_val;

int seq_val_a = 2; // = 1; //seq for server_a
int ack_val_a = 2; //seq for attacker

void Packet_Track_Init(){
    /*  Don't have to initialize to -1. */ 
    for (int i = 0; i < PACKET_NUM; i++)
        Iteration_Tracking[i] = -1;
}
int Packet_Track_Insert(int bb_offset){
    if (Packet_Tracking_Hash[bb_offset] < PATH_LIMIT){
        int path_index = Packet_Tracking_Hash[bb_offset];
        
        // check if this packet trace is covered before
        if (path_index > 0){
            int pkt_itr = 0;
            for (pkt_itr = 0; pkt_itr < PACKET_NUM; pkt_itr++){
                if (Iteration_Tracking[pkt_itr] == -1 || Packet_Tracking[bb_offset][path_index-1][pkt_itr] != Iteration_Tracking[pkt_itr])
                    break;
            }
            if (pkt_itr == PACKET_NUM || Iteration_Tracking[pkt_itr] == -1)
                return 0; //means current packet trace is covered
        }
        
        Packet_Tracking_Hash[bb_offset]++;
        //printf("%d#", bb_offset);
        for (int i = 0; i < PACKET_NUM; i++){
            Packet_Tracking[bb_offset][path_index][i] = Iteration_Tracking[i];
            //printf("%d,", Packet_Tracking[bb_offset][i]);
        }
        //printf("\n");
        if (path_index == 0)
            Packet_Tracking_Index[Packet_Tracking_Count++] = bb_offset;
    }
    return 0;
}
void Packet_Output(){
    FILE *packet_track = fopen("PACKET_TRACK.txt", "w");
    int target_index;
    DEBUG_PRINT("PACKET_TRACK\n");
    for (int i = 0; i < Packet_Tracking_Count; i++){
        target_index = Packet_Tracking_Index[i]; //bb_offset
        fprintf(packet_track, "%d#", target_index);
        for (int k = 0; k < Packet_Tracking_Hash[target_index]; k++){
            for (int j = 0; j < PACKET_NUM; j++){
                fprintf(packet_track, "%d", Packet_Tracking[target_index][k][j]);
                if (j != PACKET_NUM-1)
                    fprintf(packet_track, ",");
                else
                    fprintf(packet_track, "|");

            }
        }
        fprintf(packet_track, "\n");
    }
    fclose(packet_track);
}

void Execution(int pkt_depth, int pkt_index);
void  Packet_generate(int pkt_depth);

void Pair_Difference(){
    Packet_Track_Init();
    //DEBUG_PRINT("Replace_DEBUG_Start\n");
    //Model0_Replace_DEBUG();
    //printf("Model1\n");
    //Model1_Replace_DEBUG();
    //DEBUG_PRINT("Replace_DEBUG_End\n");
    //Assume fast_path on for Server's sockets
    Model0_tcp_fast_path_on(&Model0_Server);
    Model0_tcp_fast_path_on(&Model0_Server_A);
    Model1_tcp_fast_path_on(&Model1_Server);
    Model1_tcp_fast_path_on(&Model1_Server_A);

    //Send first SYN in attacker's own connection
    Model0_tcp_hdr(&Model0_Skb_In[0])->Model0_ack = 0; Model1_tcp_hdr(&Model1_Skb_In[0])->Model1_ack = 0; Model0_Src_sk = true;       Model1_Src_sk = true; Execution(packet_dep, 0);
    Packet_generate(0);

#if TEST_PORT
    //If port is different
    Model0_Port_guessed = true;
    Model1_Port_guessed = false;

#elif TEST_SEQ
    //If seq is different
    Model0_Port_guessed = true;
    Model1_Port_guessed = true;
    Model1_tcp_hdr(&Model1_Skb_In[0])->Model1_seq++; //Victim Connection, Model1

#elif TEST_ACK
     //If ack is different
     Model0_Port_guessed = true;
     Model1_Port_guessed = true;
     Model1_ack_val = Model0_ack_val+1;
         
#endif

    //Send first SYN in victim connection
    Model0_tcp_hdr(&Model0_Skb_In[0])->Model0_ack = 0; Model1_tcp_hdr(&Model1_Skb_In[0])->Model1_ack = 0; Model0_Src_sk = false;      Model1_Src_sk = false; Execution(packet_dep, 0);
    Packet_generate(0);
}

void  Packet_generate(int pkt_depth){ 
#if CY_ABSTRACT3
    //use snapshot to initialize packets
    Model0_SKB_Initialize(pkt_depth);
    Model1_SKB_Initialize(pkt_depth);
#else
    struct Model0_sock *sk0 = (struct Model0_sock *) &Model0_Client;
    //struct Model1_sock *sk1 = (struct Model1_sock *) &Model1_Client;

    struct Model0_sk_buff *buff0;
    //struct Model1_sk_buff *buff1;
    buff0 = &Model0_Skb_In[pkt_depth];
    //buff1 = &Model1_Skb_In[pkt_depth];
    Model0_cy_alloc_skb(buff0, Model0_Buff_In[pkt_depth], Model0_SKB_DATA_SIZE);
    //Model1_cy_alloc_skb(buff1, Model1_Buff_In[pkt_depth], Model1_SKB_DATA_SIZE);
        
    Model0_skb_reserve(buff0, (128+(96 + 48))); // data+= len; tail += len;
    //Model1_skb_reserve(buff1, (128+(96 + 48))); // data+= len; tail += len;

    DEBUG_PRINT("Model0_skb_tailroom in Initialization 0: %d\n", Model0_skb_tailroom(buff0));

    Model0_tcp_init_nondata_skb(buff0, Model0_tcp_acceptable_seq(sk0), 0x10); //set the seq and flag of tcb. But how about ack_seq? 
    //Model1_tcp_init_nondata_skb(buff1, Model1_tcp_acceptable_seq(sk1), 0x10); //set the seq and flag of tcb. But how about ack_seq? 

    Model0_skb_reserve(buff0, 1); // data+= len; tail += len;
    //Model1_skb_reserve(buff1, 1); // data+= len; tail += len;
    DEBUG_PRINT("Model0_skb_tailroom in Initialization 1: %d\n", Model0_skb_tailroom(buff0));
   
    //[CY] in cy_tcp_transmit_skb, sk's value will be changed, which is not what we expected.
    Model0_cy_tcp_transmit_skb(sk0, buff0, 0, 0);
    //Model1_cy_tcp_transmit_skb(sk1, buff1, 0, 0);
    //DEBUG_PRINT("Model0_skb_tailroom in Initialization: %d\n", Model0_skb_tailroom(buff0));
    //DEBUG_PRINT("Client.snd_nxt: %u\n", Client[0].snd_nxt);
#endif
}

void Packet_Initialization(){
    for (int i = 0; i < PACKET_NUM; i++){
        Packet_generate(i);
    }
    /********** Initialize seq_val, ack_val for packet enumeration *********/
    /*
     *  we calculate seq_val and ack_val for packet enumeration purpose:
     *  seq: [seq_val-2, seq_val+2]
     *  ack: [ack_val-2, ack_val+2]
     *  NO NEED TO UPDATE TCB if we call it from tcp_v4_rcv
     */
     
    //In 3-way handshake, server itself doesn't have rcv_nxt and snd_nxt;
    //  seq_val: future rcv_nxt, gets from pkt
    //  ack_val: snd_nxt is decided by server
    seq_val = Model0_htonl(Model0_tcp_hdr(&Model0_Skb_In[0])->Model0_seq)+1;
    seq_val_a = seq_val;
    //don't change ack_val's value

  
#if CY_ESTABLISHED
    //In established state, SKB_INIT and SK_INIT should be paired
    seq_val = Model0_htonl(Model0_tcp_hdr(&Model0_Skb_In[0])->Model0_seq);
    seq_val_a = seq_val;
    ack_val = Model0_htonl(Model0_tcp_hdr(&Model0_Skb_In[0])->Model0_ack_seq);
    ack_val_a = ack_val;
#endif
}

void PreProcess(){
    //For convenience, replace predefix into global
    Model0_SKB_DATA_SIZE = 304;  //MAX_TCP_HEADER+sizeof(struct skb_shared_info)
    Model0_SKB_DATA_MAX_SIZE = 1000; //800
    Model0_Connection_reset = false;
    Model0_delayed_ack = false;


    Model0_Global_Initialize();
    Model0_Listen_Server_Initialize();
    
    Model1_SKB_DATA_SIZE = 304;  //MAX_TCP_HEADER+sizeof(struct skb_shared_info)
    Model1_SKB_DATA_MAX_SIZE = 1000; //800
    Model1_Connection_reset = false;
    Model1_delayed_ack = false;


    Model1_Global_Initialize();
    Model1_Listen_Server_Initialize();
  
#if CY_ESTABLISHED
    //When We test it in established state
    Model0_Server_Initialize();
    Model1_Server_Initialize();
    Model0_Server_A_Initialize();
    Model1_Server_A_Initialize();
#endif 

    //Currently we dont keep Client's state, assumming Client won't respond packets
    /*
    Model0_Client_Initialize();
    Model1_Client_Initialize();
    */
}

void PKT_Prepare(){
    Packet_Initialization();
    Pair_Difference();
}

// with datapayload
void Spoofed(bool spoofed, int has_payload, int pkt_depth){ //Packet initialization
    
    Model0_th = (struct Model0_tcphdr *)(&Model0_Skb_In[pkt_depth])->Model0_data;
    Model0_tcb = ((struct Model0_tcp_skb_cb *)&((&Model0_Skb_In[pkt_depth])->Model0_cb[0]));
    Model1_th = (struct Model1_tcphdr *)(&Model1_Skb_In[pkt_depth])->Model1_data;
    Model1_tcb = ((struct Model1_tcp_skb_cb *)&((&Model1_Skb_In[pkt_depth])->Model1_cb[0]));
    
    
    //update Model1 hdr based on Model0 hdr
    Model1_th->Model1_seq = Model0_th->Model0_seq;
    Model1_th->Model1_ack_seq = Model0_th->Model0_ack_seq;
    (((Model1_u_int8_t *)Model1_th)[13]) = (((Model0_u_int8_t *)Model0_th)[13]);
    
    //last parameter   
    Model0_packet_len = 20;
    Model1_packet_len = 20;

#if CY_DEBUG3
    printf("Before packet_len: %d\n", Model0_Skb_In[pkt_depth].Model0_len);
#endif
    if (has_payload) {
        //Model0_Skb_In[pkt_depth].Model0_len += has_payload;
        //Model1_Skb_In[pkt_depth].Model1_len += has_payload;
        Model0_packet_len = 20+has_payload;
        Model1_packet_len = 20+has_payload;
#if CY_DEBUG3
        printf("0 packet_len: %d\n", Model0_Skb_In[pkt_depth].Model0_len);
#endif

        Model0_Skb_In[pkt_depth].Model0_truesize = Model0_SKB_DATA_SIZE+sizeof(struct Model0_sk_buff)+((int)(has_payload)); //sizeof(struct Model0_ //MAX_TCP_HEADER+data payload+sk_buff structure size
        Model1_Skb_In[pkt_depth].Model1_truesize = Model1_SKB_DATA_SIZE+sizeof(struct Model1_sk_buff)+((int)(has_payload)); //sizeof(struct Model0_ //MAX_TCP_HEADER+data payload+sk_buff structure size

        Model0_skb_put(&Model0_Skb_In[pkt_depth], has_payload); //put is used to add data. This function is allocate space for data payload
        Model1_skb_put(&Model1_Skb_In[pkt_depth], has_payload); //put is used to add data. This function is allocate space for data payload
#if CY_DEBUG3
        printf("1 packet_len: %d\n", Model0_Skb_In[pkt_depth].Model0_len);
#endif
    }
    else{
        Model0_tcb->Model0_end_seq = (Model0_tcb->Model0_seq + has_payload); // % Model0_SEQ_RANGE;
        Model1_tcb->Model1_end_seq = (Model1_tcb->Model1_seq + has_payload); // % Model1_SEQ_RANGE;
        //Model0_skb_set_tcp_pure_ack(&Model0_Skb_In[pkt_depth]);
        //Model1_skb_set_tcp_pure_ack(&Model1_Skb_In[pkt_depth]);
    }
    //both Model0 and Model1's TCP_SKB_CB will be updated inside Inside tcp_v4_rcv
    /*
    Model0_tcb->Model0_seq = Model0_htonl(Model0_th->Model0_seq);
    Model0_tcb->Model0_ack_seq = Model0_htonl(Model0_th->Model0_ack_seq);
    Model0_tcb->Model0_tcp_flags = (((Model0_u_int8_t *)Model0_th)[13]);
    Model0_tcb->Model0_end_seq...
    */

    if (!spoofed) {
        Model0_Dst_sk = (struct Model0_sock *) &Model0_Server_A; //with 3-way handshake, Dst_sk seems not used
        Model1_Dst_sk = (struct Model1_sock *) &Model1_Server_A; //with 3-way handshake, Dst_sk seems not used

        Model0_Src_sk = true; //From Attacker
        Model1_Src_sk = true; //From Attacker
    }
    else{
        Model0_Dst_sk = (struct Model0_sock *) &Model0_Server; 
        Model1_Dst_sk = (struct Model1_sock *) &Model1_Server; 
        
        Model0_Src_sk = false; //From Client
        Model1_Src_sk = false; //From Client 
    }
    
#if CY_DEBUG3
        printf("seq: %u\n", Model0_tcb->Model0_seq);
        printf("end_seq: %u\n", Model0_tcb->Model0_end_seq);
        printf("hdr->seq: %u\n", ntohl(Model0_tcp_hdr(&Model0_Skb_In[pkt_depth])->Model0_seq));
        printf("packet_len: %d\n", Model0_Skb_In[pkt_depth].Model0_len);
        printf("packet_doff: %d\n", Model0_th->Model0_doff*4);
#endif
}

/*
void Spoofed_with_no_payload(bool spoofed){
    tcb = ((struct tcp_skb_cb *)&((&Skb[0])->cb[0]));
    packet_len = 20;
    //printf("th->doff: %d\n", th->doff);

    if (!spoofed) {
        Src_sk[0] = (struct sock *) &Current_Attacker[0]; 
        Dst_sk[0] = (struct sock *) &Current_Server_A[0]; 
        Src_sk[1] = (struct sock *) &Current_Attacker[1]; 
        Dst_sk[1] = (struct sock *) &Current_Server_A[1];

        //printf("unspoofed\n");
    }
    else{
        Src_sk[0] = (struct sock *) &Client[0];
        Dst_sk[0] = (struct sock *) &Server[0]; 
        Src_sk[1] = (struct sock *) &Client[1]; 
        Dst_sk[1] = (struct sock *) &Server[1]; 
        //printf("spoofed\n");
    }
    //printf("th->doff: %d\n", th->doff);
}
*/

void Execution(int pkt_depth, int pkt_index){
    //DEBUG_PRINT("===================Iteration: %d =====================\n", Model0_iteration_time);
    //DEBUG_PRINT("pkt_depth: %d, pkt_index: %d\n", pkt_depth, pkt_index);
    if (Model0_iteration_time == 1315985){
        printf("pkt_index: %d\n", pkt_index);
    }
#if CY_DEBUG
    printf("Model0 tcp_rmem[2]: %d\n", Model0_sysctl_tcp_rmem[2]);
    printf("Model0 tcp_prot.sysctl_rmem[2]: %d\n", Model0_tcp_prot.Model0_sysctl_rmem[2]);
    //printf("Model hard limit: %d\n", Model0_sk_prot_rmem_limits(Model0_Dst_sk, 2));
    //DEBUG_PRINT("Model hard limit: %d\n", Model0_Dst_sk->Model0___sk_common.Model0_skc_prot->Model0_sysctl_rmem[2]);
    if (Model0_Src_sk)
        DEBUG_PRINT("Not Spoofed\n");
    else
        DEBUG_PRINT("Spoofed\n");
    DEBUG_PRINT("Server Addr: %p\n", Model0_Server.Model0_inet_conn.Model0_icsk_inet.Model0_sk.Model0___sk_common.Model0_skc_prot);
    DEBUG_PRINT("Server A Addr: %p\n", Model0_Server_A.Model0_inet_conn.Model0_icsk_inet.Model0_sk.Model0___sk_common.Model0_skc_prot);
    DEBUG_PRINT("test0\n");
    
    Model0_tcb = ((struct Model0_tcp_skb_cb *)&((&Model0_Skb_In[pkt_depth])->Model0_cb[0]));
    Model1_tcb = ((struct Model1_tcp_skb_cb *)&((&Model1_Skb_In[pkt_depth])->Model1_cb[0]));
    printf("Model0 packet_doff: %d\n", Model0_tcp_hdr(&Model0_Skb_In[pkt_depth])->Model0_doff*4);
    printf("Model1 packet_doff: %d\n", Model1_tcp_hdr(&Model1_Skb_In[pkt_depth])->Model1_doff*4);
    printf("Model0_tcb->Model0_end_seq: %d\n", Model0_tcb->Model0_end_seq);
    printf("Model1_tcb->Model1_end_seq: %d\n", Model1_tcb->Model1_end_seq);
    DEBUG_PRINT("packet depth: %d, Model0_Server, mem allocated: %d\n", pkt_depth, Model0_atomic_long_read(((struct Model0_sock *) &Model0_Server)->Model0___sk_common.Model0_skc_prot->Model0_memory_allocated));
    //DEBUG_PRINT("packet depth: %d, Model1_Server, mem allocated: %d\n", now.packet_dep, Model1_atomic_long_read(((struct Model1_sock *) &Model1_Server)->Model1___sk_common.Model1_skc_prot->Model1_memory_allocated));
#endif

    Iteration_Tracking[pkt_depth] = pkt_index;
    Model0_Out_pkt = false;
    Model1_Out_pkt = false;

    struct Model0_tcp_sock *tp0 = Model0_tcp_sk(Model0_Dst_sk);
    struct Model1_tcp_sock *tp1 = Model1_tcp_sk(Model1_Dst_sk);
    Model0_iteration_time++;
    Model0_packet_dep = pkt_depth;
    Model1_packet_dep = pkt_depth;
    
    Model0_tcp_v4_rcv(&Model0_Skb_In[pkt_depth]);
    //Model0_cy_tcp_v4_rcv(&Model0_Skb_In[pkt_depth]); //copied from tcp_v4_rcv
 	//Model0_tcp_rcv_established(Model0_Dst_sk, &Model0_Skb_In[pkt_depth], (struct Model0_tcphdr *)(&Model0_Skb_In[pkt_depth])->Model0_data, Model0_packet_len);
    //Model1_TCP_SKB_CB_Initialization(buff1); //copied from tcp_v4_rcv
   
#if CY_DEBUG3
    DEBUG_PRINT("=====================================\n");
#endif
    Model1_tcp_v4_rcv(&Model1_Skb_In[pkt_depth]);
    //Model1_cy_tcp_v4_rcv(&Model1_Skb_In[pkt_depth]); //copied from tcp_v4_rcv
 	//Model1_tcp_rcv_established(Model1_Dst_sk, &Model1_Skb_In[pkt_depth], (struct Model1_tcphdr *)(&Model1_Skb_In[pkt_depth])->Model1_data, Model1_packet_len);
    //DEBUG_PRINT("packet_dep: %d\n", now.packet_dep);

#if CY_DEBUG
    DEBUG_PRINT("================END=================\n");
    //DEBUG_PRINT("packet depth: %d, Model0_Server, mem allocated: %d\n", pkt_depth, Model0_atomic_long_read(((struct Model0_sock *) &Model0_Server)->Model0___sk_common.Model0_skc_prot->Model0_memory_allocated));
    //DEBUG_PRINT("packet depth: %d, Model1_Server, mem allocated: %d\n", now.packet_dep, Model1_atomic_long_read(((struct Model1_sock *) &Model1_Server)->Model1___sk_common.Model1_skc_prot->Model1_memory_allocated));
 //DEBUG_PRINT("Model0 tcp_in_quickack_mode- quickack: %d\n", Model0_inet_csk(Model0_Dst_sk)->Model0_icsk_ack.Model0_quick); 
 //DEBUG_PRINT("Model0 tcp_in_quickack_mode- pingpong: %d\n", Model0_inet_csk(Model0_Dst_sk)->Model0_icsk_ack.Model0_pingpong); 
 //DEBUG_PRINT("Model1 tcp_in_quickack_mode- quickack: %d\n", Model1_inet_csk(Model1_Dst_sk)->Model1_icsk_ack.Model1_quick); 
 //DEBUG_PRINT("Model1 tcp_in_quickack_mode- pingpong: %d\n", Model1_inet_csk(Model1_Dst_sk)->Model1_icsk_ack.Model1_pingpong); 
#endif
}

//return false: violation; true: correct
bool Verify(){
    /*
    if (Model0_Out_pkt){
        if (((struct Model0_tcp_skb_cb *)&(Model0_Skb_Out.Model0_cb[0]))->Model0_sacked)
            DEBUG_PRINT("Send out sack is true\n");
        else
            DEBUG_PRINT("Send out sack is false\n");
    }
    */
    struct Model0_tcp_skb_cb *tcb0;
    struct Model1_tcp_skb_cb *tcb1;
    struct Model0_tcphdr *th0;
    struct Model1_tcphdr *th1;

    if (Model0_delayed_ack ^ Model1_delayed_ack){
        printf("One connection send delayed ACK: ");
        if (Model0_delayed_ack)
            printf("Model0\n");
        else
            printf("Model1\n");
        return false;
    }
    Model0_delayed_ack = false;
    Model1_delayed_ack = false;

    if (Model0_Out_pkt ^ Model1_Out_pkt){
        //DEBUG_PRINT("Only one connection receives one packet\n");
        printf("Only one connection receives one packet\n");
        if (Model0_Out_pkt) printf("Model0_Out\n");
        if (Model1_Out_pkt) printf("Model1_Out\n");
        return false;
    }
    else if ((Model0_Out_pkt == true && Model1_Out_pkt == true)){ //When it's send from Attacker to Server
#if CY_DEBUG
        DEBUG_PRINT("Both have packets\n");
#endif
		tcb0 = ((struct Model0_tcp_skb_cb *)&((&Model0_Skb_Out)->Model0_cb[0])); 
		tcb1 = ((struct Model1_tcp_skb_cb *)&((&Model1_Skb_Out)->Model1_cb[0]));
		th0 = (struct Model0_tcphdr *)(&Model0_Skb_Out)->Model0_data; 
		th1 = (struct Model1_tcphdr *)(&Model1_Skb_Out)->Model1_data;

        //Use hdr instead of tcb
		if (!(th0->Model0_seq == th1->Model1_seq && th0->Model0_ack_seq == th1->Model1_ack_seq && th0->Model0_window == th1->Model1_window && ((Model0_u_int8_t *)th0)[13] == ((Model1_u_int8_t *)th1)[13] && th0->Model0_doff == th1->Model1_doff)){//(Model0___u16)th0->Model0_res1 == (Model1___u16)th1->Model1_res1
            printf("Some fields are different\n");
            printf("tcb0->Model0_seq: %u\n", tcb0->Model0_seq);
            printf("tcb0->Model0_ack_seq: %d\n", tcb0->Model0_ack_seq);
            printf("th0->Model0_ack_seq: %d\n", th0->Model0_ack_seq);
            printf("th0->Model0_window: %d\n", th0->Model0_window);
            printf("th0->Model0_rst: %d\n", th0->Model0_rst);
            printf("th0->Model0_syn: %d\n", th0->Model0_syn);
            printf("th0->Model0_doff: %d\n", th0->Model0_doff);
            printf("-----------\n");
            printf("tcb1->Model1_seq: %u\n", tcb1->Model1_seq);
            printf("tcb1->Model1_ack_seq: %d\n", tcb1->Model1_ack_seq);
            printf("th1->Model1_ack_seq: %d\n", th1->Model1_ack_seq);
            printf("th1->Model1_window: %d\n", th1->Model1_window);
            printf("th1->Model1_rst: %d\n", th1->Model1_rst);
            printf("th1->Model1_syn: %d\n", th1->Model1_syn);
            printf("th1->Model1_doff: %d\n", th1->Model1_doff);
            return false;
        }
	}
    return true;
}

void Instrument_Summary() __attribute__((optnone)) {
}
