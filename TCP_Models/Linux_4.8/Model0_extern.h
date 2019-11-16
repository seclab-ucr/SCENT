#ifndef Model0_EXTERN_H
#define Model0_EXTERN_H
/****** declaration *****/
void Model0_cy_alloc_skb(struct Model0_sk_buff *Model0_skb, char *Model0_data, int Model0_size);
void Model0_cy_tcp_v4_rcv(struct Model0_sk_buff *Model0_skb);
 void Model0_tcp_init_nondata_skb(struct Model0_sk_buff *Model0_skb, Model0_u32 Model0_seq, Model0_u8  Model0_flags);

__u32 Model0_tcp_acceptable_seq(const struct Model0_sock *Model0_sk);

void Model0_tcp_event_data_sent(struct Model0_tcp_sock *Model0_tp, struct Model0_sock *Model0_sk);

void Model0_tcp_event_ack_sent(struct Model0_sock *Model0_sk, unsigned int Model0_pkts);

Model0_u32 Model0___tcp_select_window(struct Model0_sock *Model0_sk);
Model0_u16 Model0_tcp_select_window(struct Model0_sock *Model0_sk);

unsigned char *Model0_skb_push(struct Model0_sk_buff *Model0_skb, unsigned int Model0_len);

static void Model0_sock_def_wakeup(struct Model0_sock *Model0_sk);
#endif
