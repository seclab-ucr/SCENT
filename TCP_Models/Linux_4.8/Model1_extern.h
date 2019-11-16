#ifndef Model1_EXTERN_H
#define Model1_EXTERN_H
/****** declaration *****/
void Model1_cy_alloc_skb(struct Model1_sk_buff *Model1_skb, char *Model1_data, int Model1_size);
void Model1_cy_tcp_v4_rcv(struct Model1_sk_buff *Model1_skb);
 void Model1_tcp_init_nondata_skb(struct Model1_sk_buff *Model1_skb, Model1_u32 Model1_seq, Model1_u8  Model1_flags);

__u32 Model1_tcp_acceptable_seq(const struct Model1_sock *Model1_sk);

void Model1_tcp_event_data_sent(struct Model1_tcp_sock *Model1_tp, struct Model1_sock *Model1_sk);

void Model1_tcp_event_ack_sent(struct Model1_sock *Model1_sk, unsigned int Model1_pkts);

Model1_u32 Model1___tcp_select_window(struct Model1_sock *Model1_sk);
Model1_u16 Model1_tcp_select_window(struct Model1_sock *Model1_sk);

unsigned char *Model1_skb_push(struct Model1_sk_buff *Model1_skb, unsigned int Model1_len);
#endif
