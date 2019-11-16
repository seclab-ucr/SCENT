#include "TCP_Model.h"
#include <assert.h>

/* START OF tcp_ipv4.c */

// globals
int Model0_sysctl_tcp_low_latency __attribute__((__section__(".data..read_mostly")));
__typeof__(int) Model0___preempt_count;
struct Model0_inet_hashinfo Model0_tcp_hashinfo;
                           ;
static const struct Model0_tcp_request_sock_ops Model0_tcp_request_sock_ipv4_ops = {
 .Model0_mss_clamp = 536U,




 .Model0_init_req = Model0_tcp_v4_init_req,



 .Model0_route_req = Model0_tcp_v4_route_req,
 .Model0_init_seq = Model0_tcp_v4_init_sequence,
 .Model0_send_synack = Model0_tcp_v4_send_synack,
};
struct Model0_request_sock_ops Model0_tcp_request_sock_ops __attribute__((__section__(".data..read_mostly"))) = {
 .Model0_family = 2,
 .Model0_obj_size = sizeof(struct Model0_tcp_request_sock),
 .Model0_rtx_syn_ack = Model0_tcp_rtx_synack,
 .Model0_send_ack = Model0_tcp_v4_reqsk_send_ack,
 .Model0_destructor = Model0_tcp_v4_reqsk_destructor,
 .Model0_send_reset = Model0_tcp_v4_send_reset,
 .Model0_syn_ack_timeout = Model0_tcp_syn_ack_timeout,
};

// functions

void Model0_tcp_syn_ack_timeout(const struct Model0_request_sock *Model0_req){
    assert(0);
}
void Model0_ip_send_unicast_reply(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb,
      const struct Model0_ip_options *Model0_sopt,
      Model0___be32 Model0_daddr, Model0___be32 Model0_saddr,
      const struct Model0_ip_reply_arg *Model0_arg,
      unsigned int Model0_len){
#if CY_ABSTRACT3
    //Used for verification of violation. Since we only compare headers, so here we only copy headers
    if (Model0_Src_sk == true){
        Model0_Out_pkt = true;
    }
    //Modify 06/11/2018 Right now we only have one direction from Client or Attacker to Server
    //We assume Client won't send packet to Server so we ignore packets sent to Client
    else{
        Model0_Out_pkt = false;
        return;
    }
#if CY_ABSTRACT3
    Model0_cy_alloc_skb(&Model0_Skb_Out, Model0_Buff_Out, Model0_SKB_DATA_SIZE);
#endif
    memcpy((struct Model0_tcphdr *)((&Model0_Skb_Out)->Model0_data), Model0_arg->Model0_iov[0].Model0_iov_base, Model0_arg->Model0_iov[0].Model0_iov_len);
#else
    assert(0);
#endif
}

Model0___wsum Model0_csum_partial(const void *Model0_buff, int Model0_len, Model0___wsum Model0_sum){
    assert(0);
    return 0;
}

int Model0___sk_backlog_rcv(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb){
    assert(0);
    return 0;
}
int Model0_tcp_rtx_synack(const struct Model0_sock *Model0_sk, struct Model0_request_sock *Model0_req)
{
 const struct Model0_tcp_request_sock_ops *Model0_af_ops = Model0_tcp_rsk(Model0_req)->Model0_af_specific;
 struct Model0_flowi Model0_fl;
 int Model0_res;

 Model0_tcp_rsk(Model0_req)->Model0_txhash = Model0_net_tx_rndhash();
#if CY_ABSTRACT7
  Model0_tcp_v4_send_synack(Model0_sk, ((void *)0), &Model0_fl, Model0_req, ((void *)0), Model0_TCP_SYNACK_NORMAL);
#else
 Model0_res = Model0_af_ops->Model0_send_synack(Model0_sk, ((void *)0), &Model0_fl, Model0_req, ((void *)0), Model0_TCP_SYNACK_NORMAL);
#endif
 if (!Model0_res) {
  (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_RETRANSSEGS] += 1);
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPSYNRETRANS] += 1);
  if (__builtin_expect(!!(Model0_tcp_passive_fastopen(Model0_sk)), 0))
   Model0_tcp_sk(Model0_sk)->Model0_total_retrans++;
 }
 return Model0_res;
}

void Model0___wake_up_sync_key(Model0_wait_queue_head_t *Model0_q, unsigned int Model0_mode, int Model0_nr, void *Model0_key){
    assert(0);
}

/* The code following below sending ACKs in SYN-RECV and TIME-WAIT states
   outside socket context is ugly, certainly. What can I do?
 */

static void Model0_tcp_v4_send_ack(struct Model0_net *Model0_net,
       struct Model0_sk_buff *Model0_skb, Model0_u32 Model0_seq, Model0_u32 Model0_ack,
       Model0_u32 Model0_win, Model0_u32 Model0_tsval, Model0_u32 Model0_tsecr, int Model0_oif,
       struct Model0_tcp_md5sig_key *Model0_key,
       int Model0_reply_flags, Model0_u8 Model0_tos)
{
 const struct Model0_tcphdr *Model0_th = Model0_tcp_hdr(Model0_skb);
 struct {
  struct Model0_tcphdr Model0_th;
  Model0___be32 Model0_opt[(12 >> 2)



   ];
 } Model0_rep;
 struct Model0_ip_reply_arg Model0_arg;

 memset(&Model0_rep.Model0_th, 0, sizeof(struct Model0_tcphdr));
 memset(&Model0_arg, 0, sizeof(Model0_arg));

 Model0_arg.Model0_iov[0].Model0_iov_base = (unsigned char *)&Model0_rep;
 Model0_arg.Model0_iov[0].Model0_iov_len = sizeof(Model0_rep.Model0_th);
 if (Model0_tsecr) {
  Model0_rep.Model0_opt[0] = (( Model0___be32)(__builtin_constant_p((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10))) ? ((__u32)( (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x000000ffUL) << 24) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32(((1 << 24) | (1 << 16) | (8 << 8) | 10))));


  Model0_rep.Model0_opt[1] = (( Model0___be32)(__builtin_constant_p((__u32)((Model0_tsval))) ? ((__u32)( (((__u32)((Model0_tsval)) & (__u32)0x000000ffUL) << 24) | (((__u32)((Model0_tsval)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((Model0_tsval)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((Model0_tsval)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32((Model0_tsval))));
  Model0_rep.Model0_opt[2] = (( Model0___be32)(__builtin_constant_p((__u32)((Model0_tsecr))) ? ((__u32)( (((__u32)((Model0_tsecr)) & (__u32)0x000000ffUL) << 24) | (((__u32)((Model0_tsecr)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((Model0_tsecr)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((Model0_tsecr)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32((Model0_tsecr))));
  Model0_arg.Model0_iov[0].Model0_iov_len += 12;
 }

 /* Swap the send and the receive. */
 Model0_rep.Model0_th.Model0_dest = Model0_th->Model0_source;
 Model0_rep.Model0_th.Model0_source = Model0_th->Model0_dest;
 Model0_rep.Model0_th.Model0_doff = Model0_arg.Model0_iov[0].Model0_iov_len / 4;
 Model0_rep.Model0_th.Model0_seq = (( Model0___be32)(__builtin_constant_p((__u32)((Model0_seq))) ? ((__u32)( (((__u32)((Model0_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)((Model0_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((Model0_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((Model0_seq)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32((Model0_seq))));
 Model0_rep.Model0_th.Model0_ack_seq = (( Model0___be32)(__builtin_constant_p((__u32)((Model0_ack))) ? ((__u32)( (((__u32)((Model0_ack)) & (__u32)0x000000ffUL) << 24) | (((__u32)((Model0_ack)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((Model0_ack)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((Model0_ack)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32((Model0_ack))));
 Model0_rep.Model0_th.Model0_ack = 1;
 Model0_rep.Model0_th.Model0_window = (( Model0___be16)(__builtin_constant_p((Model0___u16)((Model0_win))) ? ((Model0___u16)( (((Model0___u16)((Model0_win)) & (Model0___u16)0x00ffU) << 8) | (((Model0___u16)((Model0_win)) & (Model0___u16)0xff00U) >> 8))) : Model0___fswab16((Model0_win))));
 Model0_arg.Model0_flags = Model0_reply_flags;
 Model0_arg.Model0_csum = Model0_csum_tcpudp_nofold(Model0_ip_hdr(Model0_skb)->Model0_daddr,
          Model0_ip_hdr(Model0_skb)->Model0_saddr, /* XXX */
          Model0_arg.Model0_iov[0].Model0_iov_len, Model0_IPPROTO_TCP, 0);
 Model0_arg.Model0_csumoffset = __builtin_offsetof(struct Model0_tcphdr, Model0_check) / 2;
 if (Model0_oif)
  Model0_arg.Model0_bound_dev_if = Model0_oif;
 Model0_arg.Model0_tos = Model0_tos;
 Model0_local_bh_disable();
#if CY_ABSTRACT1
 //TODO: confirm its correctness
 //net0>ipv4.tcp_sk will be updated inside the function. But this sock seems to be a temporary value, so it won't affect existed socks.         Besides, in our abstraction, we only copy its value.
 Model0_ip_send_unicast_reply(&Model0_Server,
#else
 Model0_ip_send_unicast_reply(*({ (void)(0); ({ do { const void *Model0___vpp_verify = (typeof((Model0_net->Model0_ipv4.Model0_tcp_sk) + 0))((void *)0); (void)Model0___vpp_verify; } while (0); (typeof(*(Model0_net->Model0_ipv4.Model0_tcp_sk)) *)(Model0_net->Model0_ipv4.Model0_tcp_sk); }); }),
#endif
         Model0_skb, &((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_header.Model0_h4.Model0_opt,
         Model0_ip_hdr(Model0_skb)->Model0_saddr, Model0_ip_hdr(Model0_skb)->Model0_daddr,
         &Model0_arg, Model0_arg.Model0_iov[0].Model0_iov_len);

 (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_OUTSEGS] += 1);
 Model0_local_bh_enable();
}
void Model0___local_bh_enable_ip(unsigned long Model0_ip, unsigned int Model0_cnt){
#if CY_ABSTRACT1
    //TODO: disable it so far
#else
    assert(0);
#endif
}
/*
 *	IPv4 request_sock destructor.
 */
void Model0_tcp_v4_reqsk_destructor(struct Model0_request_sock *Model0_req)
{
 Model0_kfree(Model0_inet_rsk(Model0_req)->Model0_opt);
}

static inline __attribute__((no_instrument_function)) struct Model0_tcp_md5sig_key *Model0_tcp_md5_do_lookup(const struct Model0_sock *Model0_sk,
      const union Model0_tcp_md5_addr *Model0_addr,
      int Model0_family)
{
 return ((void *)0);
}

static void Model0_tcp_v4_reqsk_send_ack(const struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb,
      struct Model0_request_sock *Model0_req)
{
 /* sk->sk_state == TCP_LISTEN -> for regular TCP_SYN_RECV
	 * sk->sk_state == TCP_SYN_RECV -> for Fast Open.
	 */
 Model0_u32 Model0_seq = (Model0_sk->Model0___sk_common.Model0_skc_state == Model0_TCP_LISTEN) ? Model0_tcp_rsk(Model0_req)->Model0_snt_isn + 1 :
          Model0_tcp_sk(Model0_sk)->Model0_snd_nxt;

 /* RFC 7323 2.3
	 * The window field (SEG.WND) of every outgoing segment, with the
	 * exception of <SYN> segments, MUST be right-shifted by
	 * Rcv.Wind.Shift bits:
	 */
 Model0_tcp_v4_send_ack(Model0_sock_net(Model0_sk), Model0_skb, Model0_seq,
   Model0_tcp_rsk(Model0_req)->Model0_rcv_nxt,
   Model0_req->Model0___req_common.Model0_skc_rcv_wnd >> Model0_inet_rsk(Model0_req)->Model0_rcv_wscale,
   ((__u32)(Model0_jiffies)),
   Model0_req->Model0_ts_recent,
   0,
   Model0_tcp_md5_do_lookup(Model0_sk, (union Model0_tcp_md5_addr *)&Model0_ip_hdr(Model0_skb)->Model0_daddr,
       2),
   Model0_inet_rsk(Model0_req)->Model0_no_srccheck ? 1 : 0,
   Model0_ip_hdr(Model0_skb)->Model0_tos);
}

void Model0___tcp_v4_send_check(struct Model0_sk_buff *Model0_skb, Model0___be32 Model0_saddr, Model0___be32 Model0_daddr)
{
 struct Model0_tcphdr *Model0_th = Model0_tcp_hdr(Model0_skb);

 if (Model0_skb->Model0_ip_summed == 3) {
  Model0_th->Model0_check = ~Model0_tcp_v4_check(Model0_skb->Model0_len, Model0_saddr, Model0_daddr, 0);
  Model0_skb->Model0_csum_start = Model0_skb_transport_header(Model0_skb) - Model0_skb->Model0_head;
  Model0_skb->Model0_csum_offset = __builtin_offsetof(struct Model0_tcphdr, Model0_check);
 } else {
  Model0_th->Model0_check = Model0_tcp_v4_check(Model0_skb->Model0_len, Model0_saddr, Model0_daddr,
      Model0_csum_partial(Model0_th,
            Model0_th->Model0_doff << 2,
            Model0_skb->Model0_csum));
 }
}

static void Model0_tcp_v4_timewait_ack(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb)
{
 struct Model0_inet_timewait_sock *Model0_tw = Model0_inet_twsk(Model0_sk);
 struct Model0_tcp_timewait_sock *Model0_tcptw = Model0_tcp_twsk(Model0_sk);

 Model0_tcp_v4_send_ack(Model0_sock_net(Model0_sk), Model0_skb,
   Model0_tcptw->Model0_tw_sk.Model0___tw_common.Model0_skc_tw_snd_nxt, Model0_tcptw->Model0_tw_sk.Model0___tw_common.Model0_skc_tw_rcv_nxt,
   Model0_tcptw->Model0_tw_rcv_wnd >> Model0_tw->Model0_tw_rcv_wscale,
   ((__u32)(Model0_jiffies)) + Model0_tcptw->Model0_tw_ts_offset,
   Model0_tcptw->Model0_tw_ts_recent,
   Model0_tw->Model0___tw_common.Model0_skc_bound_dev_if,
   ((void *)0),
   Model0_tw->Model0_tw_transparent ? 1 : 0,
   Model0_tw->Model0_tw_tos
   );

 Model0_inet_twsk_put(Model0_tw);
}
void Model0_inet_csk_reqsk_queue_drop_and_put(struct Model0_sock *Model0_sk, struct Model0_request_sock *Model0_req){
    assert(0);
}
int Model0_sk_filter_trim_cap(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb, unsigned int Model0_cap){
    assert(0);
    return 0;
}

static struct Model0_sock *Model0_tcp_v4_cookie_check(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb)
{






 return Model0_sk;
}

/*
 *	This routine will send an RST to the other tcp.
 *
 *	Someone asks: why I NEVER use socket parameters (TOS, TTL etc.)
 *		      for reset.
 *	Answer: if a packet caused RST, it is not for a socket
 *		existing in our system, if it is matched to a socket,
 *		it is just duplicate segment or bug in other side's TCP.
 *		So that we build reply only basing on parameters
 *		arrived with segment.
 *	Exception: precedence violation. We do not implement it in any case.
 */

static void Model0_tcp_v4_send_reset(const struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb)
{
 const struct Model0_tcphdr *Model0_th = Model0_tcp_hdr(Model0_skb);
 struct {
  struct Model0_tcphdr Model0_th;



 } Model0_rep;
 struct Model0_ip_reply_arg Model0_arg;







 struct Model0_net *Model0_net;

 /* Never send a reset in response to a reset. */
 if (Model0_th->Model0_rst)
  return;

 /* If sk not NULL, it means we did a successful lookup and incoming
	 * route had to be correct. prequeue might have dropped our dst.
	 */
#if !CY_ABSTRACT1
 if (!Model0_sk && Model0_skb_rtable(Model0_skb)->Model0_rt_type != Model0_RTN_LOCAL)
  return;
#endif

 /* Swap the send and the receive. */
 memset(&Model0_rep, 0, sizeof(Model0_rep));
 Model0_rep.Model0_th.Model0_dest = Model0_th->Model0_source;
 Model0_rep.Model0_th.Model0_source = Model0_th->Model0_dest;
 Model0_rep.Model0_th.Model0_doff = sizeof(struct Model0_tcphdr) / 4;
 Model0_rep.Model0_th.Model0_rst = 1;

 if (Model0_th->Model0_ack) {
  Model0_rep.Model0_th.Model0_seq = Model0_th->Model0_ack_seq;
 } else {
  Model0_rep.Model0_th.Model0_ack = 1;
  Model0_rep.Model0_th.Model0_ack_seq = (( Model0___be32)(__builtin_constant_p((__u32)(((__builtin_constant_p((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq))) ? ((__u32)( (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32(( __u32)(Model0___be32)(Model0_th->Model0_seq))) + Model0_th->Model0_syn + Model0_th->Model0_fin + Model0_skb->Model0_len - (Model0_th->Model0_doff << 2)))) ? ((__u32)( (((__u32)(((__builtin_constant_p((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq))) ? ((__u32)( (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32(( __u32)(Model0___be32)(Model0_th->Model0_seq))) + Model0_th->Model0_syn + Model0_th->Model0_fin + Model0_skb->Model0_len - (Model0_th->Model0_doff << 2))) & (__u32)0x000000ffUL) << 24) | (((__u32)(((__builtin_constant_p((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq))) ? ((__u32)( (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32(( __u32)(Model0___be32)(Model0_th->Model0_seq))) + Model0_th->Model0_syn + Model0_th->Model0_fin + Model0_skb->Model0_len - (Model0_th->Model0_doff << 2))) & (__u32)0x0000ff00UL) << 8) | (((__u32)(((__builtin_constant_p((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq))) ? ((__u32)( (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32(( __u32)(Model0___be32)(Model0_th->Model0_seq))) + Model0_th->Model0_syn + Model0_th->Model0_fin + Model0_skb->Model0_len - (Model0_th->Model0_doff << 2))) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(((__builtin_constant_p((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq))) ? ((__u32)( (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32(( __u32)(Model0___be32)(Model0_th->Model0_seq))) + Model0_th->Model0_syn + Model0_th->Model0_fin + Model0_skb->Model0_len - (Model0_th->Model0_doff << 2))) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32(((__builtin_constant_p((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq))) ? ((__u32)( (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32(( __u32)(Model0___be32)(Model0_th->Model0_seq))) + Model0_th->Model0_syn + Model0_th->Model0_fin + Model0_skb->Model0_len - (Model0_th->Model0_doff << 2)))));

 }

 memset(&Model0_arg, 0, sizeof(Model0_arg));
 Model0_arg.Model0_iov[0].Model0_iov_base = (unsigned char *)&Model0_rep;
 Model0_arg.Model0_iov[0].Model0_iov_len = sizeof(Model0_rep.Model0_th);

 Model0_net = Model0_sk ? Model0_sock_net(Model0_sk) : Model0_dev_net(Model0_skb_dst(Model0_skb)->Model0_dev);
 Model0_arg.Model0_csum = Model0_csum_tcpudp_nofold(Model0_ip_hdr(Model0_skb)->Model0_daddr,
          Model0_ip_hdr(Model0_skb)->Model0_saddr, /* XXX */
          Model0_arg.Model0_iov[0].Model0_iov_len, Model0_IPPROTO_TCP, 0);
 Model0_arg.Model0_csumoffset = __builtin_offsetof(struct Model0_tcphdr, Model0_check) / 2;
 Model0_arg.Model0_flags = (Model0_sk && Model0_inet_sk_transparent(Model0_sk)) ? 1 : 0;

 /* When socket is gone, all binding information is lost.
	 * routing might fail in this case. No choice here, if we choose to force
	 * input interface, we will misroute in case of asymmetric route.
	 */
 if (Model0_sk)
  Model0_arg.Model0_bound_dev_if = Model0_sk->Model0___sk_common.Model0_skc_bound_dev_if;

 ((void)sizeof(char[1 - 2*!!(__builtin_offsetof(struct Model0_sock, Model0___sk_common.Model0_skc_bound_dev_if) != __builtin_offsetof(struct Model0_inet_timewait_sock, Model0___tw_common.Model0_skc_bound_dev_if))]));


 Model0_arg.Model0_tos = Model0_ip_hdr(Model0_skb)->Model0_tos;
 Model0_local_bh_disable();
#if CY_ABSTRACT1
    Model0_ip_send_unicast_reply(&Model0_Server,
#else
 Model0_ip_send_unicast_reply(*({ (void)(0); ({ do { const void *Model0___vpp_verify = (typeof((Model0_net->Model0_ipv4.Model0_tcp_sk) + 0))((void *)0); (void)Model0___vpp_verify; } while (0); (typeof(*(Model0_net->Model0_ipv4.Model0_tcp_sk)) *)(Model0_net->Model0_ipv4.Model0_tcp_sk); }); }),
#endif
         Model0_skb, &((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_header.Model0_h4.Model0_opt,
         Model0_ip_hdr(Model0_skb)->Model0_saddr, Model0_ip_hdr(Model0_skb)->Model0_daddr,
         &Model0_arg, Model0_arg.Model0_iov[0].Model0_iov_len);

 (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_OUTSEGS] += 1);
 (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_OUTRSTS] += 1);
 Model0_local_bh_enable();





}
int Model0___ip_options_echo(struct Model0_ip_options *Model0_dopt, struct Model0_sk_buff *Model0_skb,
        const struct Model0_ip_options *Model0_sopt){
    assert(0);
    return 0;
}
/* Packet is added to VJ-style prequeue for processing in process
 * context, if a reader task is waiting. Apparently, this exciting
 * idea (VJ's mail "Re: query about TCP header on tcp-ip" of 07 Sep 93)
 * failed somewhere. Latency? Burstiness? Well, at least now we will
 * see, why it failed. 8)8)				  --ANK
 *
 */
bool Model0_tcp_prequeue(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 if (Model0_sysctl_tcp_low_latency || !Model0_tp->Model0_ucopy.Model0_task)
  return false;

 if (Model0_skb->Model0_len <= Model0_tcp_hdrlen(Model0_skb) &&
     Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue) == 0)
  return false;

 /* Before escaping RCU protected region, we need to take care of skb
	 * dst. Prequeue is only enabled for established sockets.
	 * For such sockets, we might need the skb dst only to set sk->sk_rx_dst
	 * Instead of doing full sk_rx_dst validity here, let's perform
	 * an optimistic check.
	 */
 if (__builtin_expect(!!(Model0_sk->Model0_sk_rx_dst), 1))
  Model0_skb_dst_drop(Model0_skb);
 else
  Model0_skb_dst_force_safe(Model0_skb);

 Model0___skb_queue_tail(&Model0_tp->Model0_ucopy.Model0_prequeue, Model0_skb);
 Model0_tp->Model0_ucopy.Model0_memory += Model0_skb->Model0_truesize;
 if (Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue) >= 32 ||
     Model0_tp->Model0_ucopy.Model0_memory + Model0_atomic_read(&Model0_sk->Model0_sk_backlog.Model0_rmem_alloc) > Model0_sk->Model0_sk_rcvbuf) {
  struct Model0_sk_buff *Model0_skb1;

  do { if (Model0_sock_owned_by_user(Model0_sk)) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);
  ({ Model0___this_cpu_preempt_check("add"); do { do { const void *Model0___vpp_verify = (typeof((&((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) + 0))((void *)0); (void)Model0___vpp_verify; } while (0); switch(sizeof((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) { case 1: do { typedef typeof(((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) Model0_pao_T__; const int Model0_pao_ID__ = (__builtin_constant_p(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)) && ((Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)) == 1 || (Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)) == -1)) ? (int)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)) : 0; if (0) { Model0_pao_T__ Model0_pao_tmp__; Model0_pao_tmp__ = (Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)); (void)Model0_pao_tmp__; } switch (sizeof(((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))) { case 1: if (Model0_pao_ID__ == 1) asm("incb """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model0_pao_ID__ == -1) asm("decb """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addb %1, """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) : "qi" ((Model0_pao_T__)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)))); break; case 2: if (Model0_pao_ID__ == 1) asm("incw """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model0_pao_ID__ == -1) asm("decw """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addw %1, """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) : "ri" ((Model0_pao_T__)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)))); break; case 4: if (Model0_pao_ID__ == 1) asm("incl """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model0_pao_ID__ == -1) asm("decl """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addl %1, """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) : "ri" ((Model0_pao_T__)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)))); break; case 8: if (Model0_pao_ID__ == 1) asm("incq """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model0_pao_ID__ == -1) asm("decq """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addq %1, """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) : "re" ((Model0_pao_T__)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)))); break; default: Model0___bad_percpu_size(); } } while (0);break; case 2: do { typedef typeof(((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) Model0_pao_T__; const int Model0_pao_ID__ = (__builtin_constant_p(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)) && ((Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)) == 1 || (Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)) == -1)) ? (int)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)) : 0; if (0) { Model0_pao_T__ Model0_pao_tmp__; Model0_pao_tmp__ = (Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)); (void)Model0_pao_tmp__; } switch (sizeof(((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))) { case 1: if (Model0_pao_ID__ == 1) asm("incb """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model0_pao_ID__ == -1) asm("decb """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addb %1, """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) : "qi" ((Model0_pao_T__)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)))); break; case 2: if (Model0_pao_ID__ == 1) asm("incw """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model0_pao_ID__ == -1) asm("decw """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addw %1, """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) : "ri" ((Model0_pao_T__)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)))); break; case 4: if (Model0_pao_ID__ == 1) asm("incl """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model0_pao_ID__ == -1) asm("decl """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addl %1, """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) : "ri" ((Model0_pao_T__)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)))); break; case 8: if (Model0_pao_ID__ == 1) asm("incq """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model0_pao_ID__ == -1) asm("decq """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addq %1, """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) : "re" ((Model0_pao_T__)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)))); break; default: Model0___bad_percpu_size(); } } while (0);break; case 4: do { typedef typeof(((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) Model0_pao_T__; const int Model0_pao_ID__ = (__builtin_constant_p(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)) && ((Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)) == 1 || (Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)) == -1)) ? (int)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)) : 0; if (0) { Model0_pao_T__ Model0_pao_tmp__; Model0_pao_tmp__ = (Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)); (void)Model0_pao_tmp__; } switch (sizeof(((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))) { case 1: if (Model0_pao_ID__ == 1) asm("incb """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model0_pao_ID__ == -1) asm("decb """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addb %1, """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) : "qi" ((Model0_pao_T__)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)))); break; case 2: if (Model0_pao_ID__ == 1) asm("incw """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model0_pao_ID__ == -1) asm("decw """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addw %1, """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) : "ri" ((Model0_pao_T__)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)))); break; case 4: if (Model0_pao_ID__ == 1) asm("incl """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model0_pao_ID__ == -1) asm("decl """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addl %1, """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) : "ri" ((Model0_pao_T__)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)))); break; case 8: if (Model0_pao_ID__ == 1) asm("incq """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model0_pao_ID__ == -1) asm("decq """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addq %1, """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) : "re" ((Model0_pao_T__)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)))); break; default: Model0___bad_percpu_size(); } } while (0);break; case 8: do { typedef typeof(((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) Model0_pao_T__; const int Model0_pao_ID__ = (__builtin_constant_p(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)) && ((Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)) == 1 || (Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)) == -1)) ? (int)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)) : 0; if (0) { Model0_pao_T__ Model0_pao_tmp__; Model0_pao_tmp__ = (Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)); (void)Model0_pao_tmp__; } switch (sizeof(((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))) { case 1: if (Model0_pao_ID__ == 1) asm("incb """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model0_pao_ID__ == -1) asm("decb """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addb %1, """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) : "qi" ((Model0_pao_T__)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)))); break; case 2: if (Model0_pao_ID__ == 1) asm("incw """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model0_pao_ID__ == -1) asm("decw """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addw %1, """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) : "ri" ((Model0_pao_T__)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)))); break; case 4: if (Model0_pao_ID__ == 1) asm("incl """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model0_pao_ID__ == -1) asm("decl """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addl %1, """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) : "ri" ((Model0_pao_T__)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)))); break; case 8: if (Model0_pao_ID__ == 1) asm("incq """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model0_pao_ID__ == -1) asm("decq """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addq %1, """ "%" "0" : "+m" (((Model0_sock_net(Model0_sk))->Model0_mib.Model0_net_statistics->Model0_mibs[Model0_LINUX_MIB_TCPPREQUEUEDROPPED])) : "re" ((Model0_pao_T__)(Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue)))); break; default: Model0___bad_percpu_size(); } } while (0);break; default: Model0___bad_size_call_parameter();break; } } while (0); });


  while ((Model0_skb1 = Model0___skb_dequeue(&Model0_tp->Model0_ucopy.Model0_prequeue)) != ((void *)0))
   Model0_sk_backlog_rcv(Model0_sk, Model0_skb1);

  Model0_tp->Model0_ucopy.Model0_memory = 0;
 } else if (Model0_skb_queue_len(&Model0_tp->Model0_ucopy.Model0_prequeue) == 1) {
  Model0___wake_up_sync_key((Model0_sk_sleep(Model0_sk)), 1, 1, (void *) (0x0001 | 0x0040 | 0x0080));

  if (!Model0_inet_csk_ack_scheduled(Model0_sk))
   Model0_inet_csk_reset_xmit_timer(Model0_sk, 2,
        (3 * Model0_tcp_rto_min(Model0_sk)) / 4,
        ((unsigned)(120*1000)));
 }
 return true;
}

void Model0_inet_twsk_put(struct Model0_inet_timewait_sock *Model0_tw){
    assert(0);
}

struct Model0_sock *Model0___inet_lookup_listener(struct Model0_net *Model0_net,
        struct Model0_inet_hashinfo *Model0_hashinfo,
        struct Model0_sk_buff *Model0_skb, int Model0_doff,
        const Model0___be32 Model0_saddr, const Model0___be16 Model0_sport,
        const Model0___be32 Model0_daddr,
        const unsigned short Model0_hnum,
        const int Model0_dif){
#if CY_ABSTRACT1
    return &Model0_Server_L;
#else
    assert(0);
    return NULL;
#endif
}

/*
 * Queue segment on the new socket if the new socket is active,
 * otherwise we just shortcircuit this and continue with
 * the new socket.
 *
 * For the vast majority of cases child->sk_state will be TCP_SYN_RECV
 * when entering. But other states are possible due to a race condition
 * where after __inet_lookup_established() fails but before the listener
 * locked is obtained, other packets cause the same connection to
 * be created.
 */

int Model0_tcp_child_process(struct Model0_sock *Model0_parent, struct Model0_sock *Model0_child,
        struct Model0_sk_buff *Model0_skb)
{
 int Model0_ret = 0;
 int Model0_state = Model0_child->Model0___sk_common.Model0_skc_state;

 Model0_tcp_segs_in(Model0_tcp_sk(Model0_child), Model0_skb);
 if (!Model0_sock_owned_by_user(Model0_child)) {
  Model0_ret = Model0_tcp_rcv_state_process(Model0_child, Model0_skb);
  /* Wakeup parent, send SIGIO */
  if (Model0_state == Model0_TCP_SYN_RECV && Model0_child->Model0___sk_common.Model0_skc_state != Model0_state)
#if CY_ABSTRACT3
      //not sure which function it points to
      //1. net/core/sock.c: sock_def_readable  (we abstract it since we avoid concurrency)
      //2. net/netlink/af_netlink.c: netlink_data_ready (its empty)
      //Therefore, we just abstrct it
      ;
#else
   Model0_parent->Model0_sk_data_ready(Model0_parent);
#endif
 } else {
  /* Alas, it is possible again, because we do lookup
		 * in main socket hash table and lock on listening
		 * socket does not protect us more.
		 */
  Model0___sk_add_backlog(Model0_child, Model0_skb);
 }

 Model0_spin_unlock(&((Model0_child)->Model0_sk_lock.Model0_slock));
 Model0_sock_put(Model0_child);
 return Model0_ret;
}
unsigned char *Model0___pskb_pull_tail(struct Model0_sk_buff *Model0_skb, int Model0_delta){
#if CY_ABSTRACT1
    // Moves tail of skb head forward, copying data from fragmented part, when it is necessary.
    // Assume it always fail due to malloc failure
    return NULL;
#else
    assert(0);
    return NULL;
#endif
}

static inline __attribute__((no_instrument_function)) int Model0_xfrm4_policy_check(struct Model0_sock *Model0_sk, int Model0_dir, struct Model0_sk_buff *Model0_skb)
{
 return 1;
}
__u32 Model0_secure_tcp_sequence_number(Model0___be32 Model0_saddr, Model0___be32 Model0_daddr,
     Model0___be16 Model0_sport, Model0___be16 Model0_dport){
    return ack_val;
}
void *Model0_memmove(void *Model0_dest, const void *Model0_src, Model0_size_t Model0_count){
    assert(0);
    return NULL;
}
/* Socket demux engine toys. */
/* What happens here is ugly; there's a pair of adjacent fields in
   struct inet_sock; __be16 dport followed by __u16 num.  We want to
   search by pair, so we combine the keys into a single 32bit value
   and compare with 32bit value read from &...->dport.  Let's at least
   make sure that it's not mixed with anything else...
   On 64bit targets we combine comparisons with pair of adjacent __be32
   fields in the same way.
*/
/* Sockets in TCP_CLOSE state are _always_ taken out of the hash, so we need
 * not check it for lookups anymore, thanks Alexey. -DaveM
 */
struct Model0_sock *Model0___inet_lookup_established(struct Model0_net *Model0_net,
           struct Model0_inet_hashinfo *Model0_hashinfo,
           const Model0___be32 Model0_saddr, const Model0___be16 Model0_sport,
           const Model0___be32 Model0_daddr, const Model0_u16 Model0_hnum,
           const int Model0_dif){
#if CY_ABSTRACT1
    if (Model0_Src_sk){
        if (((struct Model0_sock *)&Model0_Server_A)->Model0___sk_common.Model0_skc_state != 0)
            return &Model0_Server_A;
        else if (((struct Model0_request_sock *)&Model0_Req_A)->Model0___req_common.Model0_skc_state != 0)
            return &Model0_Req_A;
    }
    else{
        if (((struct Model0_sock *)&Model0_Server)->Model0___sk_common.Model0_skc_state != 0)
            return &Model0_Server;
        else if (((struct Model0_request_sock *)&Model0_Req)->Model0___req_common.Model0_skc_state != 0)
            return &Model0_Req;
    }
    return NULL;
#else
    assert(0);
    return NULL;
#endif
}

void Model0_inet_twsk_deschedule_put(struct Model0_inet_timewait_sock *Model0_tw){
    assert(0);
}

static inline __attribute__((no_instrument_function)) void Model0_sk_mark_napi_id(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb)
{
}

struct Model0_dst_entry *Model0_inet_csk_route_req(const struct Model0_sock *Model0_sk, struct Model0_flowi4 *Model0_fl4,
         const struct Model0_request_sock *Model0_req){
    assert(0);
    return NULL;
}

/* Called with rcu_read_lock() */
enum Model0_tcp_tw_status Model0_tcp_timewait_state_process(struct Model0_inet_timewait_sock *Model0_tw,
           struct Model0_sk_buff *Model0_skb,
           const struct Model0_tcphdr *Model0_th){
    assert(0);
    return 0;
}
static bool Model0_tcp_v4_inbound_md5_hash(const struct Model0_sock *Model0_sk,
        const struct Model0_sk_buff *Model0_skb)
{
 return false;
}

static void Model0_tcp_v4_init_req(struct Model0_request_sock *Model0_req,
       const struct Model0_sock *Model0_sk_listener,
       struct Model0_sk_buff *Model0_skb)
{
 struct Model0_inet_request_sock *Model0_ireq = Model0_inet_rsk(Model0_req);

 Model0_sk_rcv_saddr_set(Model0_req_to_sk(Model0_req), Model0_ip_hdr(Model0_skb)->Model0_daddr);
 Model0_sk_daddr_set(Model0_req_to_sk(Model0_req), Model0_ip_hdr(Model0_skb)->Model0_saddr);
 Model0_ireq->Model0_no_srccheck = Model0_inet_sk(Model0_sk_listener)->Model0_transparent;
 Model0_ireq->Model0_opt = Model0_tcp_v4_save_options(Model0_skb);
}

static struct Model0_dst_entry *Model0_tcp_v4_route_req(const struct Model0_sock *Model0_sk,
       struct Model0_flowi *Model0_fl,
       const struct Model0_request_sock *Model0_req,
       bool *Model0_strict)
{
 struct Model0_dst_entry *Model0_dst = Model0_inet_csk_route_req(Model0_sk, &Model0_fl->Model0_u.Model0_ip4, Model0_req);

 if (Model0_strict) {
  if (Model0_fl->Model0_u.Model0_ip4.Model0_daddr == Model0_inet_rsk(Model0_req)->Model0_req.Model0___req_common.Model0_skc_daddr)
   *Model0_strict = true;
  else
   *Model0_strict = false;
 }

 return Model0_dst;
}

static __u32 Model0_tcp_v4_init_sequence(const struct Model0_sk_buff *Model0_skb)
{
#if CY_ABSTRACT3
 if (Model0_Src_sk) //not spoofed
     return ack_val_a;
 else
     return ack_val;
 //return ack_val; //ack_val and ack_val_a have same value
#else
 return Model0_secure_tcp_sequence_number(Model0_ip_hdr(Model0_skb)->Model0_daddr,
       Model0_ip_hdr(Model0_skb)->Model0_saddr,
       Model0_tcp_hdr(Model0_skb)->Model0_dest,
       Model0_tcp_hdr(Model0_skb)->Model0_source);
#endif
}

/*
 *	Send a SYN-ACK after having received a SYN.
 *	This still operates on a request_sock only, not on a big
 *	socket.
 */
static int Model0_tcp_v4_send_synack(const struct Model0_sock *Model0_sk, struct Model0_dst_entry *Model0_dst,
         struct Model0_flowi *Model0_fl,
         struct Model0_request_sock *Model0_req,
         struct Model0_tcp_fastopen_cookie *Model0_foc,
         enum Model0_tcp_synack_type Model0_synack_type)
{
 const struct Model0_inet_request_sock *Model0_ireq = Model0_inet_rsk(Model0_req);
 struct Model0_flowi4 Model0_fl4;
 int err = -1;
 struct Model0_sk_buff *Model0_skb;

 /* First, grab a route. */
#if CY_ABSTRACT3
 //TODO: confirm if we can ignore it. 
 //Assumption: we work on TCP layer only, so we don't care about route information
#else
 if (!Model0_dst && (Model0_dst = Model0_inet_csk_route_req(Model0_sk, &Model0_fl4, Model0_req)) == ((void *)0))
  return -1;
#endif

 Model0_skb = Model0_tcp_make_synack(Model0_sk, Model0_dst, Model0_req, Model0_foc, Model0_synack_type);

 if (Model0_skb) {
  Model0___tcp_v4_send_check(Model0_skb, Model0_ireq->Model0_req.Model0___req_common.Model0_skc_rcv_saddr, Model0_ireq->Model0_req.Model0___req_common.Model0_skc_daddr);

  err = Model0_ip_build_and_send_pkt(Model0_skb, Model0_sk, Model0_ireq->Model0_req.Model0___req_common.Model0_skc_rcv_saddr,
         Model0_ireq->Model0_req.Model0___req_common.Model0_skc_daddr,
         Model0_ireq->Model0_opt);
  err = ((err) == 0x02 ? 0 : (err));
 }

 return err;
}

int Model0_tcp_v4_conn_request(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb)
{
 /* Never answer to SYNs send to broadcast or multicast */
#if !CY_ABSTRACT1
 if (Model0_skb_rtable(Model0_skb)->Model0_rt_flags & (0x10000000 | 0x20000000))
  goto Model0_drop;
#endif

 return Model0_tcp_conn_request(&Model0_tcp_request_sock_ops,
    &Model0_tcp_request_sock_ipv4_ops, Model0_sk, Model0_skb);

Model0_drop:
 Model0_tcp_listendrop(Model0_sk);
 return 0;
}
/* The socket must have it's spinlock held when we get
 * here, unless it is a TCP_LISTEN socket.
 *
 * We have a potential double-lock case here, so even when
 * doing backlog processing we use the BH locking scheme.
 * This is because we cannot sleep with the original spinlock
 * held.
 */
int Model0_tcp_v4_do_rcv(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb)
{
 struct Model0_sock *Model0_rsk;
 if (Model0_sk->Model0___sk_common.Model0_skc_state == Model0_TCP_ESTABLISHED) { /* Fast path */
  struct Model0_dst_entry *Model0_dst = Model0_sk->Model0_sk_rx_dst;

  Model0_sock_rps_save_rxhash(Model0_sk, Model0_skb);
  Model0_sk_mark_napi_id(Model0_sk, Model0_skb);
  if (Model0_dst) {
   if (Model0_inet_sk(Model0_sk)->Model0_rx_dst_ifindex != Model0_skb->Model0_skb_iif ||
       !Model0_dst->Model0_ops->Model0_check(Model0_dst, 0)) { //based on our assumption (no dst process), we will ignore this function; But not sure how it will be processed
    Model0_dst_release(Model0_dst);
    Model0_sk->Model0_sk_rx_dst = ((void *)0);
   }
  }
  Model0_tcp_rcv_established(Model0_sk, Model0_skb, Model0_tcp_hdr(Model0_skb), Model0_skb->Model0_len);
  return 0;
 }

 if (Model0_tcp_checksum_complete(Model0_skb))
  goto Model0_csum_err;

 if (Model0_sk->Model0___sk_common.Model0_skc_state == Model0_TCP_LISTEN) {
  struct Model0_sock *Model0_nsk = Model0_tcp_v4_cookie_check(Model0_sk, Model0_skb);

  if (!Model0_nsk)
   goto Model0_discard;
  if (Model0_nsk != Model0_sk) {
   Model0_sock_rps_save_rxhash(Model0_nsk, Model0_skb);
   Model0_sk_mark_napi_id(Model0_nsk, Model0_skb);
   if (Model0_tcp_child_process(Model0_sk, Model0_nsk, Model0_skb)) {
    Model0_rsk = Model0_nsk;
    goto Model0_reset;
   }
   return 0;
  }
 } else
  Model0_sock_rps_save_rxhash(Model0_sk, Model0_skb);

 if (Model0_tcp_rcv_state_process(Model0_sk, Model0_skb)) {
  Model0_rsk = Model0_sk;
  goto Model0_reset;
 }
 return 0;

Model0_reset:
 Model0_tcp_v4_send_reset(Model0_rsk, Model0_skb);
Model0_discard:
 Model0_kfree_skb(Model0_skb);
 /* Be careful here. If this function gets more complicated and
	 * gcc suffers from register pressure on the x86, sk (in %ebx)
	 * might be destroyed here. This current version compiles correctly,
	 * but you have been warned.
	 */
 return 0;

Model0_csum_err:
 (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_CSUMERRORS] += 1);
 (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_INERRS] += 1);
 goto Model0_discard;
}

/*
 * The three way handshake has completed - we got a valid synack -
 * now create the new socket.
 */
struct Model0_sock *Model0_tcp_v4_syn_recv_sock(const struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb,
      struct Model0_request_sock *Model0_req,
      struct Model0_dst_entry *Model0_dst,
      struct Model0_request_sock *Model0_req_unhash,
      bool *Model0_own_req)
{
 struct Model0_inet_request_sock *Model0_ireq;
 struct Model0_inet_sock *Model0_newinet;
 struct Model0_tcp_sock *Model0_newtp;
 struct Model0_sock *Model0_newsk;



 struct Model0_ip_options_rcu *Model0_inet_opt;

 if (Model0_sk_acceptq_is_full(Model0_sk))
  goto Model0_exit_overflow;

 Model0_newsk = Model0_tcp_create_openreq_child(Model0_sk, Model0_req, Model0_skb);
 if (!Model0_newsk)
  goto Model0_exit_nonewsk;

 Model0_newsk->Model0_sk_gso_type = Model0_SKB_GSO_TCPV4;
 Model0_inet_sk_rx_dst_set(Model0_newsk, Model0_skb);

 Model0_newtp = Model0_tcp_sk(Model0_newsk);
 Model0_newinet = Model0_inet_sk(Model0_newsk);
 Model0_ireq = Model0_inet_rsk(Model0_req);
 Model0_sk_daddr_set(Model0_newsk, Model0_ireq->Model0_req.Model0___req_common.Model0_skc_daddr);
 Model0_sk_rcv_saddr_set(Model0_newsk, Model0_ireq->Model0_req.Model0___req_common.Model0_skc_rcv_saddr);
 Model0_newsk->Model0___sk_common.Model0_skc_bound_dev_if = Model0_ireq->Model0_req.Model0___req_common.Model0_skc_bound_dev_if;
 Model0_newinet->Model0_inet_saddr = Model0_ireq->Model0_req.Model0___req_common.Model0_skc_rcv_saddr;
 Model0_inet_opt = Model0_ireq->Model0_opt;
 ({ Model0_uintptr_t Model0__r_a_p__v = (Model0_uintptr_t)(Model0_inet_opt); if (__builtin_constant_p(Model0_inet_opt) && (Model0__r_a_p__v) == (Model0_uintptr_t)((void *)0)) ({ union { typeof((Model0_newinet->Model0_inet_opt)) Model0___val; char Model0___c[1]; } Model0___u = { .Model0___val = ( typeof((Model0_newinet->Model0_inet_opt))) ((typeof(Model0_newinet->Model0_inet_opt))(Model0__r_a_p__v)) }; Model0___write_once_size(&((Model0_newinet->Model0_inet_opt)), Model0___u.Model0___c, sizeof((Model0_newinet->Model0_inet_opt))); Model0___u.Model0___val; }); else do { do { bool Model0___cond = !((sizeof(*&Model0_newinet->Model0_inet_opt) == sizeof(char) || sizeof(*&Model0_newinet->Model0_inet_opt) == sizeof(short) || sizeof(*&Model0_newinet->Model0_inet_opt) == sizeof(int) || sizeof(*&Model0_newinet->Model0_inet_opt) == sizeof(long))); extern void Model0___compiletime_assert_1297(void) ; if (Model0___cond) Model0___compiletime_assert_1297(); do { ((void)sizeof(char[1 - 2 * Model0___cond])); } while (0); } while (0); __asm__ __volatile__("": : :"memory"); ({ union { typeof(*&Model0_newinet->Model0_inet_opt) Model0___val; char Model0___c[1]; } Model0___u = { .Model0___val = ( typeof(*&Model0_newinet->Model0_inet_opt)) ((typeof(*((typeof(Model0_newinet->Model0_inet_opt))Model0__r_a_p__v)) *)((typeof(Model0_newinet->Model0_inet_opt))Model0__r_a_p__v)) }; Model0___write_once_size(&(*&Model0_newinet->Model0_inet_opt), Model0___u.Model0___c, sizeof(*&Model0_newinet->Model0_inet_opt)); Model0___u.Model0___val; }); } while (0); Model0__r_a_p__v; });
 Model0_ireq->Model0_opt = ((void *)0);
 Model0_newinet->Model0_mc_index = Model0_inet_iif(Model0_skb);
 Model0_newinet->Model0_mc_ttl = Model0_ip_hdr(Model0_skb)->Model0_ttl;
 Model0_newinet->Model0_rcv_tos = Model0_ip_hdr(Model0_skb)->Model0_tos;
 Model0_inet_csk(Model0_newsk)->Model0_icsk_ext_hdr_len = 0;
 if (Model0_inet_opt)
  Model0_inet_csk(Model0_newsk)->Model0_icsk_ext_hdr_len = Model0_inet_opt->Model0_opt.Model0_optlen;
 Model0_newinet->Model0_inet_id = Model0_newtp->Model0_write_seq ^ Model0_jiffies;

#if !CY_ABSTRACT1
 //dst is IP layer. TODO: currently we ignroe it
 if (!Model0_dst) {
  Model0_dst = Model0_inet_csk_route_child_sock(Model0_sk, Model0_newsk, Model0_req);
  if (!Model0_dst)
   goto Model0_put_and_exit;
 } else {
  /* syncookie case : see end of cookie_v4_check() */
 }
 Model0_sk_setup_caps(Model0_newsk, Model0_dst);

 Model0_tcp_ca_openreq_child(Model0_newsk, Model0_dst);
 Model0_tcp_sync_mss(Model0_newsk, Model0_dst_mtu(Model0_dst));
 Model0_newtp->Model0_advmss = Model0_dst_metric_advmss(Model0_dst);
#endif
 if (Model0_tcp_sk(Model0_sk)->Model0_rx_opt.Model0_user_mss &&
     Model0_tcp_sk(Model0_sk)->Model0_rx_opt.Model0_user_mss < Model0_newtp->Model0_advmss)
  Model0_newtp->Model0_advmss = Model0_tcp_sk(Model0_sk)->Model0_rx_opt.Model0_user_mss;

 Model0_tcp_initialize_rcv_mss(Model0_newsk);
 if (Model0___inet_inherit_port(Model0_sk, Model0_newsk) < 0)
  goto Model0_put_and_exit;
 *Model0_own_req = Model0_inet_ehash_nolisten(Model0_newsk, Model0_req_to_sk(Model0_req_unhash));
 if (*Model0_own_req)
  Model0_tcp_move_syn(Model0_newtp, Model0_req);

 return Model0_newsk;

Model0_exit_overflow:
 (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_LISTENOVERFLOWS] += 1);
Model0_exit_nonewsk:
 Model0_dst_release(Model0_dst);
Model0_exit:
 Model0_tcp_listendrop(Model0_sk);
 return ((void *)0);
Model0_put_and_exit:
 Model0_inet_csk_prepare_forced_close(Model0_newsk);
 Model0_tcp_done(Model0_newsk);
 goto Model0_exit;
}
/*
 *	From tcp_input.c
 */

int Model0_tcp_v4_rcv(struct Model0_sk_buff *Model0_skb)
{
#if CY_ABSTRACT3
//    if (Model0_Src_sk == false && Model0_Port_guessed == false)
//        return 0;
#endif
 struct Model0_net *Model0_net = Model0_dev_net(Model0_skb->Model0_dev);
 const struct Model0_iphdr *Model0_iph;
 const struct Model0_tcphdr *Model0_th;
 bool Model0_refcounted;
 struct Model0_sock *Model0_sk;
 int Model0_ret;

 if (Model0_skb->Model0_pkt_type != 0)
  goto Model0_discard_it;

 /* Count it even if it's bad */
 (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_INSEGS] += 1);

 if (!Model0_pskb_may_pull(Model0_skb, sizeof(struct Model0_tcphdr)))
  goto Model0_discard_it;

 Model0_th = (const struct Model0_tcphdr *)Model0_skb->Model0_data;

 if (__builtin_expect(!!(Model0_th->Model0_doff < sizeof(struct Model0_tcphdr) / 4), 0))
  goto Model0_bad_packet;
 if (!Model0_pskb_may_pull(Model0_skb, Model0_th->Model0_doff * 4))
  goto Model0_discard_it;

 /* An explanation is required here, I think.
	 * Packet length and doff are validated by header prediction,
	 * provided case of th->doff==0 is eliminated.
	 * So, we defer the checks. */

#if !CY_ABSTRACT1
 if (({ Model0___sum16 Model0___ret = 0; Model0_skb->Model0_csum_valid = 0; if (Model0___skb_checksum_validate_needed(Model0_skb, false, 0)) Model0___ret = Model0___skb_checksum_validate_complete(Model0_skb, false, Model0_inet_compute_pseudo(Model0_skb, Model0_IPPROTO_TCP)); Model0___ret; }))
  goto Model0_csum_error;
#endif

 Model0_th = (const struct Model0_tcphdr *)Model0_skb->Model0_data;
 Model0_iph = Model0_ip_hdr(Model0_skb);
 /* This is tricky : We move IPCB at its correct location into TCP_SKB_CB()
	 * barrier() makes sure compiler wont play fool^Waliasing games.
	 */
#if !CY_ABSTRACT1
 Model0_memmove(&((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_header.Model0_h4, ((struct Model0_inet_skb_parm*)((Model0_skb)->Model0_cb)),
  sizeof(struct Model0_inet_skb_parm));
#endif
 __asm__ __volatile__("": : :"memory");

 ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq = (__builtin_constant_p((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq))) ? ((__u32)( (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32(( __u32)(Model0___be32)(Model0_th->Model0_seq)));
 ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq = (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq + Model0_th->Model0_syn + Model0_th->Model0_fin +
        Model0_skb->Model0_len - Model0_th->Model0_doff * 4);
 ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_ack_seq = (__builtin_constant_p((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_ack_seq))) ? ((__u32)( (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_ack_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_ack_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_ack_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_ack_seq)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32(( __u32)(Model0___be32)(Model0_th->Model0_ack_seq)));
 ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_tcp_flags = (((Model0_u_int8_t *)Model0_th)[13]);
 ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_tcp_tw_isn = 0;
 ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_ip_dsfield = Model0_ipv4_get_dsfield(Model0_iph);
 ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked = 0;

Model0_lookup:
 Model0_sk = Model0___inet_lookup_skb(&Model0_tcp_hashinfo, Model0_skb, Model0___tcp_hdrlen(Model0_th), Model0_th->Model0_source,
          Model0_th->Model0_dest, &Model0_refcounted);
 if (!Model0_sk)
  goto Model0_no_tcp_socket;

Model0_process:
 if (Model0_sk->Model0___sk_common.Model0_skc_state == Model0_TCP_TIME_WAIT)
  goto Model0_do_time_wait;

 if (Model0_sk->Model0___sk_common.Model0_skc_state == Model0_TCP_NEW_SYN_RECV) {
  struct Model0_request_sock *Model0_req = Model0_inet_reqsk(Model0_sk);
  struct Model0_sock *Model0_nsk;

  Model0_sk = Model0_req->Model0___req_common.Model0_skc_listener;
  if (__builtin_expect(!!(Model0_tcp_v4_inbound_md5_hash(Model0_sk, Model0_skb)), 0)) {
   Model0_reqsk_put(Model0_req);
   goto Model0_discard_it;
  }
  if (__builtin_expect(!!(Model0_sk->Model0___sk_common.Model0_skc_state != Model0_TCP_LISTEN), 0)) {
   Model0_inet_csk_reqsk_queue_drop_and_put(Model0_sk, Model0_req);
   goto Model0_lookup;
  }

  /* We own a reference on the listener, increase it again
		 * as we might lose it too soon.
		 */
  Model0_sock_hold(Model0_sk);
  Model0_refcounted = true;
  Model0_nsk = Model0_tcp_check_req(Model0_sk, Model0_skb, Model0_req, false);
  if (!Model0_nsk) {
   Model0_reqsk_put(Model0_req);
   goto Model0_discard_and_relse;
  }
  if (Model0_nsk == Model0_sk) {
   Model0_reqsk_put(Model0_req);
  } else if (Model0_tcp_child_process(Model0_sk, Model0_nsk, Model0_skb)) {
   Model0_tcp_v4_send_reset(Model0_nsk, Model0_skb);
   goto Model0_discard_and_relse;
  } else {
   Model0_sock_put(Model0_sk);
   return 0;
  }
 }
#if !CY_ABSTRACT1
 if (__builtin_expect(!!(Model0_iph->Model0_ttl < Model0_inet_sk(Model0_sk)->Model0_min_ttl), 0)) {
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPMINTTLDROP] += 1);
  goto Model0_discard_and_relse;
 }
#endif

 if (!Model0_xfrm4_policy_check(Model0_sk, Model0_XFRM_POLICY_IN, Model0_skb))
  goto Model0_discard_and_relse;

 if (Model0_tcp_v4_inbound_md5_hash(Model0_sk, Model0_skb))
  goto Model0_discard_and_relse;

 Model0_nf_reset(Model0_skb);

#if !CY_ABSTRACT1
 if (Model0_sk_filter(Model0_sk, Model0_skb))
  goto Model0_discard_and_relse;
#endif

 Model0_skb->Model0_dev = ((void *)0);

 if (Model0_sk->Model0___sk_common.Model0_skc_state == Model0_TCP_LISTEN) {
  Model0_ret = Model0_tcp_v4_do_rcv(Model0_sk, Model0_skb);
  goto Model0_put_and_return;
 }

 Model0_sk_incoming_cpu_update(Model0_sk);

 do { do { __asm__ __volatile__("": : :"memory"); do { (void)0; (void)(((void)(1), (Model0_spinlock_check(&((Model0_sk)->Model0_sk_lock.Model0_slock))))); } while (0); } while (0); } while (0);
 Model0_tcp_segs_in(Model0_tcp_sk(Model0_sk), Model0_skb);
 Model0_ret = 0;
 if (!Model0_sock_owned_by_user(Model0_sk)) {
  if (!Model0_tcp_prequeue(Model0_sk, Model0_skb))
   Model0_ret = Model0_tcp_v4_do_rcv(Model0_sk, Model0_skb);
 }
#if !CY_ABSTRACT1
 else if (__builtin_expect(!!(Model0_sk_add_backlog(Model0_sk, Model0_skb, Model0_sk->Model0_sk_rcvbuf + Model0_sk->Model0_sk_sndbuf)), 0)) {

  Model0_spin_unlock(&((Model0_sk)->Model0_sk_lock.Model0_slock));
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPBACKLOGDROP] += 1);
  goto Model0_discard_and_relse;
 }
#endif
 Model0_spin_unlock(&((Model0_sk)->Model0_sk_lock.Model0_slock));
Model0_put_and_return:
 if (Model0_refcounted)
  Model0_sock_put(Model0_sk);

 return Model0_ret;
Model0_no_tcp_socket:
 if (!Model0_xfrm4_policy_check(((void *)0), Model0_XFRM_POLICY_IN, Model0_skb))
  goto Model0_discard_it;

 if (Model0_tcp_checksum_complete(Model0_skb)) {
Model0_csum_error:
  (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_CSUMERRORS] += 1);
Model0_bad_packet:
  (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_INERRS] += 1);
 } else {
  Model0_tcp_v4_send_reset(((void *)0), Model0_skb);
 }

Model0_discard_it:
 /* Discard frame. */
 Model0_kfree_skb(Model0_skb);
 return 0;

Model0_discard_and_relse:
 Model0_sk_drops_add(Model0_sk, Model0_skb);
 if (Model0_refcounted)
  Model0_sock_put(Model0_sk);
 goto Model0_discard_it;

Model0_do_time_wait:
 if (!Model0_xfrm4_policy_check(((void *)0), Model0_XFRM_POLICY_IN, Model0_skb)) {
  Model0_inet_twsk_put(Model0_inet_twsk(Model0_sk));
  goto Model0_discard_it;
 }

 if (Model0_tcp_checksum_complete(Model0_skb)) {
  Model0_inet_twsk_put(Model0_inet_twsk(Model0_sk));
  goto Model0_csum_error;
 }
 switch (Model0_tcp_timewait_state_process(Model0_inet_twsk(Model0_sk), Model0_skb, Model0_th)) {
 case Model0_TCP_TW_SYN: {
  struct Model0_sock *Model0_sk2 = Model0_inet_lookup_listener(Model0_dev_net(Model0_skb->Model0_dev),
       &Model0_tcp_hashinfo, Model0_skb,
       Model0___tcp_hdrlen(Model0_th),
       Model0_iph->Model0_saddr, Model0_th->Model0_source,
       Model0_iph->Model0_daddr, Model0_th->Model0_dest,
       Model0_inet_iif(Model0_skb));
  if (Model0_sk2) {
   Model0_inet_twsk_deschedule_put(Model0_inet_twsk(Model0_sk));
   Model0_sk = Model0_sk2;
   Model0_refcounted = false;
   goto Model0_process;
  }
  /* Fall through to ACK */
 }
 case Model0_TCP_TW_ACK:
  Model0_tcp_v4_timewait_ack(Model0_sk, Model0_skb);
  break;
 case Model0_TCP_TW_RST:
  Model0_tcp_v4_send_reset(Model0_sk, Model0_skb);
  Model0_inet_twsk_deschedule_put(Model0_inet_twsk(Model0_sk));
  goto Model0_discard_it;
 case Model0_TCP_TW_SUCCESS:;
 }
 goto Model0_discard_it;
}

/* START OF extern.c */

struct Model0_net Model0_init_net;
int Model0_sysctl_max_syn_backlog;
struct Model0_inet_timewait_death_row Model0_tcp_death_row = {
 .Model0_sysctl_max_tw_buckets = 8192 * 2,
#if CY_ABSTRACT1
#else
 //.Model0_hashinfo = &Model0_tcp_hashinfo,
#endif
};

// copied from tcp_output.c
struct Model0_tcp_out_options {
 Model0_u16 Model0_options; /* bit field of OPTION_* */
 Model0_u16 Model0_mss; /* 0 to disable */
 Model0_u8 Model0_ws; /* window scale, 0 to disable */
 Model0_u8 Model0_num_sack_blocks; /* number of SACK blocks to include */
 Model0_u8 Model0_hash_size; /* bytes in hash_location */
 __u8 *Model0_hash_location; /* temporary pointer, overloaded */
 __u32 Model0_tsval, Model0_tsecr; /* need to include OPTION_TS */
 struct Model0_tcp_fastopen_cookie *Model0_fastopen_cookie; /* Fast open cookie */
};

/****** extra function ******/
static void Model0_inet_child_forget(struct Model0_sock *Model0_sk, struct Model0_request_sock *Model0_req,
         struct Model0_sock *Model0_child)
{
    assert(0);
}
void Model0_security_sk_free(struct Model0_sock *Model0_sk){
}
#if CY_ABSTRACT3 //!CONFIG_MODULES
bool Model0_try_module_get(struct Model0_module *Model0_module){
    //TODO: currently to make it simply, assume CONFIG_MODULES is false, but it's not true
    return 1;
}
#endif
int Model0_security_sk_alloc(struct Model0_sock *Model0_sk, int Model0_family, Model0_gfp_t Model0_priority){
    return 0;
}
void Model0_net_enable_timestamp(void){
    assert(0);
}
bool Model0_sock_needs_netstamp(const struct Model0_sock *Model0_sk)
{
 switch (Model0_sk->Model0___sk_common.Model0_skc_family) {
 case 0:
 case 1:
  return false;
 default:
  return true;
 }
}

static inline int Model0_xfrm_sk_clone_policy(struct Model0_sock *Model0_sk, const struct Model0_sock *Model0_osk) { return 0; }
/* try to charge the socket memory if there is space available
 * return true on success
 */
bool Model0_sk_filter_charge(struct Model0_sock *Model0_sk, struct Model0_sk_filter *Model0_fp){
#if CY_ABSTRACT3
    //TODO: currently ignore it
    return true;
#endif
}
/*
 * Initialize an sk_lock.
 *
 * (We also register the sk_lock with the lock validator.)
 */
static inline __attribute__((no_instrument_function)) void Model0_sock_lock_init(struct Model0_sock *Model0_sk)
{
#if CY_ABSTRACT3
    //TODO: currently ignore lock initialization
#else
#endif
}
/*
 * Copy all fields from osk to nsk but nsk->sk_refcnt must not change yet,
 * even temporarly, because of RCU lookups. sk_node should also be left as is.
 * We must not copy fields between sk_dontcopy_begin and sk_dontcopy_end
 */
static void Model0_sock_copy(struct Model0_sock *Model0_nsk, const struct Model0_sock *Model0_osk)
{

 ({ Model0_size_t Model0___len = (__builtin_offsetof(struct Model0_sock, Model0___sk_common.Model0_skc_dontcopy_begin)); void *Model0___ret; if (__builtin_constant_p(__builtin_offsetof(struct Model0_sock, Model0___sk_common.Model0_skc_dontcopy_begin)) && Model0___len >= 64) Model0___ret = Model0___memcpy((Model0_nsk), (Model0_osk), Model0___len); else Model0___ret = __builtin_memcpy((Model0_nsk), (Model0_osk), Model0___len); Model0___ret; });

 ({ Model0_size_t Model0___len = (Model0_osk->Model0___sk_common.Model0_skc_prot->Model0_obj_size - __builtin_offsetof(struct Model0_sock, Model0___sk_common.Model0_skc_dontcopy_end)); void *Model0___ret; if (__builtin_constant_p(Model0_osk->Model0___sk_common.Model0_skc_prot->Model0_obj_size - __builtin_offsetof(struct Model0_sock, Model0___sk_common.Model0_skc_dontcopy_end)) && Model0___len >= 64) Model0___ret = Model0___memcpy((&Model0_nsk->Model0___sk_common.Model0_skc_dontcopy_end), (&Model0_osk->Model0___sk_common.Model0_skc_dontcopy_end), Model0___len); else Model0___ret = __builtin_memcpy((&Model0_nsk->Model0___sk_common.Model0_skc_dontcopy_end), (&Model0_osk->Model0___sk_common.Model0_skc_dontcopy_end), Model0___len); Model0___ret; });






}
static struct Model0_sock *Model0_sk_prot_alloc(struct Model0_proto *Model0_prot, Model0_gfp_t Model0_priority,
  int Model0_family);
static inline void Model0_security_inet_csk_clone(struct Model0_sock *Model0_newsk,
    const struct Model0_request_sock *Model0_req)
{
}
/**
* sk_stream_write_space - stream socket write_space callback.
* @sk: socket
*
* FIXME: write proper description
*/
void Model0_sk_stream_write_space(struct Model0_sock *Model0_sk){
    //TODO: seems not needed
    assert(0);
}
/**
 *	sk_clone_lock - clone a socket, and lock its clone
 *	@sk: the socket to clone
 *	@priority: for allocation (%GFP_KERNEL, %GFP_ATOMIC, etc)
 *
 *	Caller must unlock socket even in error path (bh_unlock_sock(newsk))
 */
struct Model0_sock *Model0_sk_clone_lock(const struct Model0_sock *Model0_sk, const Model0_gfp_t Model0_priority)
{
 struct Model0_sock *Model0_newsk;
 bool Model0_is_charged = true;

 Model0_newsk = Model0_sk_prot_alloc(Model0_sk->Model0___sk_common.Model0_skc_prot, Model0_priority, Model0_sk->Model0___sk_common.Model0_skc_family);
 if (Model0_newsk != ((void *)0)) {
  struct Model0_sk_filter *Model0_filter;

  Model0_sock_copy(Model0_newsk, Model0_sk);

  /* SANITY */
  if (__builtin_expect(!!(Model0_newsk->Model0___sk_common.Model0_skc_net_refcnt), 1))
   Model0_get_net(Model0_sock_net(Model0_newsk));
  Model0_sk_node_init(&Model0_newsk->Model0___sk_common.Model0_skc_node);
  Model0_sock_lock_init(Model0_newsk);
  Model0_spin_lock(&((Model0_newsk)->Model0_sk_lock.Model0_slock));
  Model0_newsk->Model0_sk_backlog.Model0_head = Model0_newsk->Model0_sk_backlog.Model0_tail = ((void *)0);
  Model0_newsk->Model0_sk_backlog.Model0_len = 0;

  Model0_atomic_set(&Model0_newsk->Model0_sk_backlog.Model0_rmem_alloc, 0);
  /*
		 * sk_wmem_alloc set to one (see sk_free() and sock_wfree())
		 */
  Model0_atomic_set(&Model0_newsk->Model0_sk_wmem_alloc, 1);
  Model0_atomic_set(&Model0_newsk->Model0_sk_omem_alloc, 0);
  Model0_skb_queue_head_init(&Model0_newsk->Model0_sk_receive_queue);
  Model0_skb_queue_head_init(&Model0_newsk->Model0_sk_write_queue);

#if !CY_ABSTRACT1
    //TODO: temporarily removed
  do { *(&Model0_newsk->Model0_sk_callback_lock) = (Model0_rwlock_t) { .Model0_raw_lock = { }, }; } while (0);
  do { (void)(Model0_af_callback_keys + Model0_newsk->Model0___sk_common.Model0_skc_family); (void)(Model0_af_family_clock_key_strings[Model0_newsk->Model0___sk_common.Model0_skc_family]); } while (0);
#endif


  Model0_newsk->Model0_sk_dst_cache = ((void *)0);
  Model0_newsk->Model0_sk_wmem_queued = 0;
  Model0_newsk->Model0_sk_forward_alloc = 0;
  Model0_atomic_set(&Model0_newsk->Model0_sk_drops, 0);
  Model0_newsk->Model0_sk_send_head = ((void *)0);
  Model0_newsk->Model0_sk_userlocks = Model0_sk->Model0_sk_userlocks & ~8;

  Model0_sock_reset_flag(Model0_newsk, Model0_SOCK_DONE);
  Model0_skb_queue_head_init(&Model0_newsk->Model0_sk_error_queue);

  Model0_filter = ({ do { } while (0); ; ((typeof(*(Model0_newsk->Model0_sk_filter)) *)((Model0_newsk->Model0_sk_filter))); });
  if (Model0_filter != ((void *)0))
   /* though it's an empty new sock, the charging may fail
			 * if sysctl_optmem_max was changed between creation of
			 * original socket and cloning
			 */
   Model0_is_charged = Model0_sk_filter_charge(Model0_newsk, Model0_filter);

  if (__builtin_expect(!!(!Model0_is_charged || Model0_xfrm_sk_clone_policy(Model0_newsk, Model0_sk)), 0)) {
   /* It is still raw copy of parent, so invalidate
			 * destructor and make plain sk_free() */
   Model0_newsk->Model0_sk_destruct = ((void *)0);
   Model0_spin_unlock(&((Model0_newsk)->Model0_sk_lock.Model0_slock));
   Model0_sk_free(Model0_newsk);
   Model0_newsk = ((void *)0);
   goto Model0_out;
  }
  do { ; ({ union { typeof(Model0_newsk->Model0_sk_reuseport_cb) Model0___val; char Model0___c[1]; } Model0___u = { .Model0___val = ( typeof(Model0_newsk->Model0_sk_reuseport_cb)) ((typeof(*(((void *)0))) *)(((void *)0))) }; Model0___write_once_size(&(Model0_newsk->Model0_sk_reuseport_cb), Model0___u.Model0___c, sizeof(Model0_newsk->Model0_sk_reuseport_cb)); Model0___u.Model0___val; }); } while (0);

  Model0_newsk->Model0_sk_err = 0;
  Model0_newsk->Model0_sk_priority = 0;
  Model0_newsk->Model0___sk_common.Model0_skc_incoming_cpu = 0;
  Model0_atomic64_set(&Model0_newsk->Model0___sk_common.Model0_skc_cookie, 0);

  Model0_cgroup_sk_alloc(&Model0_newsk->Model0_sk_cgrp_data);

  /*
		 * Before updating sk_refcnt, we must commit prior changes to memory
		 * (Documentation/RCU/rculist_nulls.txt for details)
		 */
  __asm__ __volatile__("": : :"memory");
  Model0_atomic_set(&Model0_newsk->Model0___sk_common.Model0_skc_refcnt, 2);

  /*
		 * Increment the counter in the same struct proto as the master
		 * sock (sk_refcnt_debug_inc uses newsk->sk_prot->socks, that
		 * is the same as sk->sk_prot->socks, as this field was copied
		 * with memcpy).
		 *
		 * This _changes_ the previous behaviour, where
		 * tcp_create_openreq_child always was incrementing the
		 * equivalent to tcp_prot->socks (inet_sock_nr), so this have
		 * to be taken into account in all callers. -acme
		 */
  do { } while (0);
  Model0_sk_set_socket(Model0_newsk, ((void *)0));
  Model0_newsk->Model0_sk_wq = ((void *)0);

  if (0 && Model0_sk->Model0_sk_memcg)
   Model0_sock_update_memcg(Model0_newsk);

  if (Model0_newsk->Model0___sk_common.Model0_skc_prot->Model0_sockets_allocated)
   Model0_sk_sockets_allocated_inc(Model0_newsk);

  if (Model0_sock_needs_netstamp(Model0_sk) &&
      Model0_newsk->Model0___sk_common.Model0_skc_flags & ((1UL << Model0_SOCK_TIMESTAMP) | (1UL << Model0_SOCK_TIMESTAMPING_RX_SOFTWARE)))
   Model0_net_enable_timestamp();
 }
Model0_out:
 return Model0_newsk;
}
static void Model0_tcp_ecn_openreq_child(struct Model0_tcp_sock *Model0_tp,
      const struct Model0_request_sock *Model0_req)
{
 Model0_tp->Model0_ecn_flags = Model0_inet_rsk(Model0_req)->Model0_ecn_ok ? 1 : 0;
}
/**
 *	inet_csk_clone_lock - clone an inet socket, and lock its clone
 *	@sk: the socket to clone
 *	@req: request_sock
 *	@priority: for allocation (%GFP_KERNEL, %GFP_ATOMIC, etc)
 *
 *	Caller must unlock socket even in error path (bh_unlock_sock(newsk))
 */
struct Model0_sock *Model0_inet_csk_clone_lock(const struct Model0_sock *Model0_sk,
     const struct Model0_request_sock *Model0_req,
     const Model0_gfp_t Model0_priority)
{
 struct Model0_sock *Model0_newsk = Model0_sk_clone_lock(Model0_sk, Model0_priority);

 if (Model0_newsk) {
  struct Model0_inet_connection_sock *Model0_newicsk = Model0_inet_csk(Model0_newsk);

  Model0_newsk->Model0___sk_common.Model0_skc_state = Model0_TCP_SYN_RECV;
  Model0_newicsk->Model0_icsk_bind_hash = ((void *)0);

  Model0_inet_sk(Model0_newsk)->Model0_sk.Model0___sk_common.Model0_skc_dport = Model0_inet_rsk(Model0_req)->Model0_req.Model0___req_common.Model0_skc_dport;
  Model0_inet_sk(Model0_newsk)->Model0_sk.Model0___sk_common.Model0_skc_num = Model0_inet_rsk(Model0_req)->Model0_req.Model0___req_common.Model0_skc_num;
  Model0_inet_sk(Model0_newsk)->Model0_inet_sport = (( Model0___be16)(__builtin_constant_p((Model0___u16)((Model0_inet_rsk(Model0_req)->Model0_req.Model0___req_common.Model0_skc_num))) ? ((Model0___u16)( (((Model0___u16)((Model0_inet_rsk(Model0_req)->Model0_req.Model0___req_common.Model0_skc_num)) & (Model0___u16)0x00ffU) << 8) | (((Model0___u16)((Model0_inet_rsk(Model0_req)->Model0_req.Model0___req_common.Model0_skc_num)) & (Model0___u16)0xff00U) >> 8))) : Model0___fswab16((Model0_inet_rsk(Model0_req)->Model0_req.Model0___req_common.Model0_skc_num))));
  Model0_newsk->Model0_sk_write_space = Model0_sk_stream_write_space;

  /* listeners have SOCK_RCU_FREE, not the children */
  Model0_sock_reset_flag(Model0_newsk, Model0_SOCK_RCU_FREE);

  Model0_newsk->Model0_sk_mark = Model0_inet_rsk(Model0_req)->Model0_ir_mark;
  Model0_atomic64_set(&Model0_newsk->Model0___sk_common.Model0_skc_cookie,
        Model0_atomic64_read(&Model0_inet_rsk(Model0_req)->Model0_req.Model0___req_common.Model0_skc_cookie));

  Model0_newicsk->Model0_icsk_retransmits = 0;
  Model0_newicsk->Model0_icsk_backoff = 0;
  Model0_newicsk->Model0_icsk_probes_out = 0;

  /* Deinitialize accept_queue to trap illegal accesses. */
  memset(&Model0_newicsk->Model0_icsk_accept_queue, 0, sizeof(Model0_newicsk->Model0_icsk_accept_queue));

  Model0_security_inet_csk_clone(Model0_newsk, Model0_req);
 }
 return Model0_newsk;
}
void Model0_tcp_init_xmit_timers(struct Model0_sock *Model0_sk){
#if CY_ABSTRACT2
    //Since we fix the time in our model, timers won't be triggered
#else
    assert(0);
#endif
}
void Model0_inet_csk_prepare_forced_close(struct Model0_sock *Model0_sk){
    assert(0);
}
bool Model0_inet_ehash_nolisten(struct Model0_sock *Model0_sk, struct Model0_sock *Model0_osk){
#if CY_ABSTRACT3
    return true;
#else
    assert(0);
    return true;
#endif
}
int Model0___inet_inherit_port(const struct Model0_sock *Model0_sk, struct Model0_sock *Model0_child){
#if CY_ABSTRACT3
    //TODO: inherit port (hash value) from its father. But currently we abstracted hash system
    return 0;
#else
    assert(0);
    return 0;
#endif
}
void Model0_tcp_ca_openreq_child(struct Model0_sock *Model0_sk, const struct Model0_dst_entry *Model0_dst)
{
#if CY_ABSTRACT1
    assert(0);
#else
 struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
 Model0_u32 Model0_ca_key = Model0_dst_metric(Model0_dst, Model0_RTAX_CC_ALGO);
 bool Model0_ca_got_dst = false;

 if (Model0_ca_key != 0) {
  const struct Model0_tcp_congestion_ops *Model0_ca;

  Model0_rcu_read_lock();
  Model0_ca = Model0_tcp_ca_find_key(Model0_ca_key);
  if (__builtin_expect(!!(Model0_ca && Model0_try_module_get(Model0_ca->Model0_owner)), 1)) {
   Model0_icsk->Model0_icsk_ca_dst_locked = Model0_tcp_ca_dst_locked(Model0_dst);
   Model0_icsk->Model0_icsk_ca_ops = Model0_ca;
   Model0_ca_got_dst = true;
  }
  Model0_rcu_read_unlock();
 }

 /* If no valid choice made yet, assign current system default ca. */
 if (!Model0_ca_got_dst &&
     (!Model0_icsk->Model0_icsk_ca_setsockopt ||
      !Model0_try_module_get(Model0_icsk->Model0_icsk_ca_ops->Model0_owner)))
  Model0_tcp_assign_congestion_control(Model0_sk);

 Model0_tcp_set_ca_state(Model0_sk, Model0_TCP_CA_Open);
#endif
}

void Model0_sk_setup_caps(struct Model0_sock *Model0_sk, struct Model0_dst_entry *Model0_dst){
    assert(0);
}
/* This is not only more efficient than what we used to do, it eliminates
 * a lot of code duplication between IPv4/IPv6 SYN recv processing. -DaveM
 *
 * Actually, we could lots of memory writes here. tp of listening
 * socket contains all necessary default parameters.
 */
struct Model0_sock *Model0_tcp_create_openreq_child(const struct Model0_sock *Model0_sk,
          struct Model0_request_sock *Model0_req,
          struct Model0_sk_buff *Model0_skb)
{
 struct Model0_sock *Model0_newsk = Model0_inet_csk_clone_lock(Model0_sk, Model0_req, ((( Model0_gfp_t)0x20u)|(( Model0_gfp_t)0x80000u)|(( Model0_gfp_t)0x2000000u)));

 if (Model0_newsk) {
  const struct Model0_inet_request_sock *Model0_ireq = Model0_inet_rsk(Model0_req);
  struct Model0_tcp_request_sock *Model0_treq = Model0_tcp_rsk(Model0_req);
  struct Model0_inet_connection_sock *Model0_newicsk = Model0_inet_csk(Model0_newsk);
  struct Model0_tcp_sock *Model0_newtp = Model0_tcp_sk(Model0_newsk);

  /* Now setup tcp_sock */
  Model0_newtp->Model0_pred_flags = 0;

  Model0_newtp->Model0_rcv_wup = Model0_newtp->Model0_copied_seq =
  Model0_newtp->Model0_rcv_nxt = Model0_treq->Model0_rcv_isn + 1;
  Model0_newtp->Model0_segs_in = 1;

  Model0_newtp->Model0_snd_sml = Model0_newtp->Model0_snd_una =
  Model0_newtp->Model0_snd_nxt = Model0_newtp->Model0_snd_up = Model0_treq->Model0_snt_isn + 1;

  Model0_tcp_prequeue_init(Model0_newtp);
  Model0_INIT_LIST_HEAD(&Model0_newtp->Model0_tsq_node);

  Model0_tcp_init_wl(Model0_newtp, Model0_treq->Model0_rcv_isn);

  Model0_newtp->Model0_srtt_us = 0;
  Model0_newtp->Model0_mdev_us = Model0_jiffies_to_usecs(((unsigned)(1*1000)));
  Model0_newtp->Model0_rtt_min[0].Model0_rtt = ~0U;
  Model0_newicsk->Model0_icsk_rto = ((unsigned)(1*1000));

  Model0_newtp->Model0_packets_out = 0;
  Model0_newtp->Model0_retrans_out = 0;
  Model0_newtp->Model0_sacked_out = 0;
  Model0_newtp->Model0_fackets_out = 0;
  Model0_newtp->Model0_snd_ssthresh = 0x7fffffff;
  Model0_tcp_enable_early_retrans(Model0_newtp);
  Model0_newtp->Model0_tlp_high_seq = 0;
  Model0_newtp->Model0_lsndtime = Model0_treq->Model0_snt_synack.Model0_stamp_jiffies;
  Model0_newsk->Model0_sk_txhash = Model0_treq->Model0_txhash;
  Model0_newtp->Model0_last_oow_ack_time = 0;
  Model0_newtp->Model0_total_retrans = Model0_req->Model0_num_retrans;

  /* So many TCP implementations out there (incorrectly) count the
		 * initial SYN frame in their delayed-ACK and congestion control
		 * algorithms that we must have the following bandaid to talk
		 * efficiently to them.  -DaveM
		 */
  Model0_newtp->Model0_snd_cwnd = 10;
  Model0_newtp->Model0_snd_cwnd_cnt = 0;

  Model0_tcp_init_xmit_timers(Model0_newsk);
  Model0___skb_queue_head_init(&Model0_newtp->Model0_out_of_order_queue);
  Model0_newtp->Model0_write_seq = Model0_newtp->Model0_pushed_seq = Model0_treq->Model0_snt_isn + 1;

  Model0_newtp->Model0_rx_opt.Model0_saw_tstamp = 0;

  Model0_newtp->Model0_rx_opt.Model0_dsack = 0;
  Model0_newtp->Model0_rx_opt.Model0_num_sacks = 0;

  Model0_newtp->Model0_urg_data = 0;

  if (Model0_sock_flag(Model0_newsk, Model0_SOCK_KEEPOPEN))
   Model0_inet_csk_reset_keepalive_timer(Model0_newsk,
             Model0_keepalive_time_when(Model0_newtp));

  Model0_newtp->Model0_rx_opt.Model0_tstamp_ok = Model0_ireq->Model0_tstamp_ok;
  if ((Model0_newtp->Model0_rx_opt.Model0_sack_ok = Model0_ireq->Model0_sack_ok) != 0) {
   if (Model0_sysctl_tcp_fack)
    Model0_tcp_enable_fack(Model0_newtp);
  }
  Model0_newtp->Model0_window_clamp = Model0_req->Model0___req_common.Model0_skc_window_clamp;
  Model0_newtp->Model0_rcv_ssthresh = Model0_req->Model0___req_common.Model0_skc_rcv_wnd;
  Model0_newtp->Model0_rcv_wnd = Model0_req->Model0___req_common.Model0_skc_rcv_wnd;
  Model0_newtp->Model0_rx_opt.Model0_wscale_ok = Model0_ireq->Model0_wscale_ok;
  if (Model0_newtp->Model0_rx_opt.Model0_wscale_ok) {
   Model0_newtp->Model0_rx_opt.Model0_snd_wscale = Model0_ireq->Model0_snd_wscale;
   Model0_newtp->Model0_rx_opt.Model0_rcv_wscale = Model0_ireq->Model0_rcv_wscale;
  } else {
   Model0_newtp->Model0_rx_opt.Model0_snd_wscale = Model0_newtp->Model0_rx_opt.Model0_rcv_wscale = 0;
   Model0_newtp->Model0_window_clamp = ({ typeof(Model0_newtp->Model0_window_clamp) Model0__min1 = (Model0_newtp->Model0_window_clamp); typeof(65535U) Model0__min2 = (65535U); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
  }
  Model0_newtp->Model0_snd_wnd = ((__builtin_constant_p((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_window))) ? ((Model0___u16)( (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_window)) & (Model0___u16)0x00ffU) << 8) | (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_window)) & (Model0___u16)0xff00U) >> 8))) : Model0___fswab16(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_window))) <<
      Model0_newtp->Model0_rx_opt.Model0_snd_wscale);
  Model0_newtp->Model0_max_window = Model0_newtp->Model0_snd_wnd;

  if (Model0_newtp->Model0_rx_opt.Model0_tstamp_ok) {
   Model0_newtp->Model0_rx_opt.Model0_ts_recent = Model0_req->Model0_ts_recent;
   Model0_newtp->Model0_rx_opt.Model0_ts_recent_stamp = Model0_get_seconds();
   Model0_newtp->Model0_tcp_header_len = sizeof(struct Model0_tcphdr) + 12;
  } else {
   Model0_newtp->Model0_rx_opt.Model0_ts_recent_stamp = 0;
   Model0_newtp->Model0_tcp_header_len = sizeof(struct Model0_tcphdr);
  }
  Model0_newtp->Model0_tsoffset = 0;





  if (Model0_skb->Model0_len >= 536U + Model0_newtp->Model0_tcp_header_len)
   Model0_newicsk->Model0_icsk_ack.Model0_last_seg_size = Model0_skb->Model0_len - Model0_newtp->Model0_tcp_header_len;
  Model0_newtp->Model0_rx_opt.Model0_mss_clamp = Model0_req->Model0_mss;
  Model0_tcp_ecn_openreq_child(Model0_newtp, Model0_req);
  Model0_newtp->Model0_fastopen_rsk = ((void *)0);
  Model0_newtp->Model0_syn_data_acked = 0;
  Model0_newtp->Model0_rack.Model0_mstamp.Model0_v64 = 0;
  Model0_newtp->Model0_rack.Model0_advanced = 0;

  (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_PASSIVEOPENS] += 1);
 }
 return Model0_newsk;
}

struct Model0_dst_entry *Model0_inet_csk_route_child_sock(const struct Model0_sock *Model0_sk,
         struct Model0_sock *Model0_newsk,
         const struct Model0_request_sock *Model0_req)
{
#if CY_ABSTRACT1
    assert(0);
    return NULL;
#else
 const struct Model0_inet_request_sock *Model0_ireq = Model0_inet_rsk(Model0_req);
 struct Model0_net *Model0_net = Model0_read_pnet(&Model0_ireq->Model0_req.Model0___req_common.Model0_skc_net);
 struct Model0_inet_sock *Model0_newinet = Model0_inet_sk(Model0_newsk);
 struct Model0_ip_options_rcu *Model0_opt;
 struct Model0_flowi4 *Model0_fl4;
 struct Model0_rtable *Model0_rt;

 Model0_fl4 = &Model0_newinet->Model0_cork.Model0_fl.Model0_u.Model0_ip4;

 Model0_rcu_read_lock();
 Model0_opt = ({ typeof(*(Model0_newinet->Model0_inet_opt)) *Model0_________p1 = (typeof(*(Model0_newinet->Model0_inet_opt)) *)({ typeof((Model0_newinet->Model0_inet_opt)) Model0__________p1 = ({ union { typeof((Model0_newinet->Model0_inet_opt)) Model0___val; char Model0___c[1]; } Model0___u; if (1) Model0___read_once_size(&((Model0_newinet->Model0_inet_opt)), Model0___u.Model0___c, sizeof((Model0_newinet->Model0_inet_opt))); else Model0___read_once_size_nocheck(&((Model0_newinet->Model0_inet_opt)), Model0___u.Model0___c, sizeof((Model0_newinet->Model0_inet_opt))); Model0___u.Model0___val; }); typeof(*((Model0_newinet->Model0_inet_opt))) *Model0____typecheck_p __attribute__((unused)); do { } while (0); (Model0__________p1); }); do { } while (0); ; ((typeof(*(Model0_newinet->Model0_inet_opt)) *)(Model0_________p1)); });
 Model0_flowi4_init_output(Model0_fl4, Model0_ireq->Model0_req.Model0___req_common.Model0_skc_bound_dev_if, Model0_ireq->Model0_ir_mark,
      (((Model0_inet_sk(Model0_sk)->Model0_tos)&0x1E) | Model0_sock_flag(Model0_sk, Model0_SOCK_LOCALROUTE)), Model0_RT_SCOPE_UNIVERSE,
      Model0_sk->Model0_sk_protocol, Model0_inet_sk_flowi_flags(Model0_sk),
      (Model0_opt && Model0_opt->Model0_opt.Model0_srr) ? Model0_opt->Model0_opt.Model0_faddr : Model0_ireq->Model0_req.Model0___req_common.Model0_skc_daddr,
      Model0_ireq->Model0_req.Model0___req_common.Model0_skc_rcv_saddr, Model0_ireq->Model0_req.Model0___req_common.Model0_skc_dport,
      (( Model0___be16)(__builtin_constant_p((Model0___u16)((Model0_ireq->Model0_req.Model0___req_common.Model0_skc_num))) ? ((Model0___u16)( (((Model0___u16)((Model0_ireq->Model0_req.Model0___req_common.Model0_skc_num)) & (Model0___u16)0x00ffU) << 8) | (((Model0___u16)((Model0_ireq->Model0_req.Model0___req_common.Model0_skc_num)) & (Model0___u16)0xff00U) >> 8))) : Model0___fswab16((Model0_ireq->Model0_req.Model0___req_common.Model0_skc_num)))));
 Model0_security_req_classify_flow(Model0_req, Model0_flowi4_to_flowi(Model0_fl4));
 Model0_rt = Model0_ip_route_output_flow(Model0_net, Model0_fl4, Model0_sk);
 if (Model0_IS_ERR(Model0_rt))
  goto Model0_no_route;
 if (Model0_opt && Model0_opt->Model0_opt.Model0_is_strictroute && Model0_rt->Model0_rt_uses_gateway)
  goto Model0_route_err;
 Model0_rcu_read_unlock();
 return &Model0_rt->Model0_dst;

Model0_route_err:
 Model0_ip_rt_put(Model0_rt);
Model0_no_route:
 Model0_rcu_read_unlock();
 ({ Model0___this_cpu_preempt_check("add"); do { do { const void *Model0___vpp_verify = (typeof((&((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) + 0))((void *)0); (void)Model0___vpp_verify; } while (0); switch(sizeof((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) { case 1: do { typedef typeof(((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) Model0_pao_T__; const int Model0_pao_ID__ = (__builtin_constant_p(1) && ((1) == 1 || (1) == -1)) ? (int)(1) : 0; if (0) { Model0_pao_T__ Model0_pao_tmp__; Model0_pao_tmp__ = (1); (void)Model0_pao_tmp__; } switch (sizeof(((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))) { case 1: if (Model0_pao_ID__ == 1) asm("incb """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else if (Model0_pao_ID__ == -1) asm("decb """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else asm("addb %1, """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) : "qi" ((Model0_pao_T__)(1))); break; case 2: if (Model0_pao_ID__ == 1) asm("incw """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else if (Model0_pao_ID__ == -1) asm("decw """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else asm("addw %1, """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) : "ri" ((Model0_pao_T__)(1))); break; case 4: if (Model0_pao_ID__ == 1) asm("incl """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else if (Model0_pao_ID__ == -1) asm("decl """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else asm("addl %1, """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) : "ri" ((Model0_pao_T__)(1))); break; case 8: if (Model0_pao_ID__ == 1) asm("incq """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else if (Model0_pao_ID__ == -1) asm("decq """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else asm("addq %1, """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) : "re" ((Model0_pao_T__)(1))); break; default: Model0___bad_percpu_size(); } } while (0);break; case 2: do { typedef typeof(((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) Model0_pao_T__; const int Model0_pao_ID__ = (__builtin_constant_p(1) && ((1) == 1 || (1) == -1)) ? (int)(1) : 0; if (0) { Model0_pao_T__ Model0_pao_tmp__; Model0_pao_tmp__ = (1); (void)Model0_pao_tmp__; } switch (sizeof(((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))) { case 1: if (Model0_pao_ID__ == 1) asm("incb """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else if (Model0_pao_ID__ == -1) asm("decb """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else asm("addb %1, """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) : "qi" ((Model0_pao_T__)(1))); break; case 2: if (Model0_pao_ID__ == 1) asm("incw """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else if (Model0_pao_ID__ == -1) asm("decw """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else asm("addw %1, """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) : "ri" ((Model0_pao_T__)(1))); break; case 4: if (Model0_pao_ID__ == 1) asm("incl """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else if (Model0_pao_ID__ == -1) asm("decl """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else asm("addl %1, """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) : "ri" ((Model0_pao_T__)(1))); break; case 8: if (Model0_pao_ID__ == 1) asm("incq """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else if (Model0_pao_ID__ == -1) asm("decq """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else asm("addq %1, """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) : "re" ((Model0_pao_T__)(1))); break; default: Model0___bad_percpu_size(); } } while (0);break; case 4: do { typedef typeof(((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) Model0_pao_T__; const int Model0_pao_ID__ = (__builtin_constant_p(1) && ((1) == 1 || (1) == -1)) ? (int)(1) : 0; if (0) { Model0_pao_T__ Model0_pao_tmp__; Model0_pao_tmp__ = (1); (void)Model0_pao_tmp__; } switch (sizeof(((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))) { case 1: if (Model0_pao_ID__ == 1) asm("incb """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else if (Model0_pao_ID__ == -1) asm("decb """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else asm("addb %1, """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) : "qi" ((Model0_pao_T__)(1))); break; case 2: if (Model0_pao_ID__ == 1) asm("incw """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else if (Model0_pao_ID__ == -1) asm("decw """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else asm("addw %1, """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) : "ri" ((Model0_pao_T__)(1))); break; case 4: if (Model0_pao_ID__ == 1) asm("incl """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else if (Model0_pao_ID__ == -1) asm("decl """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else asm("addl %1, """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) : "ri" ((Model0_pao_T__)(1))); break; case 8: if (Model0_pao_ID__ == 1) asm("incq """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else if (Model0_pao_ID__ == -1) asm("decq """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else asm("addq %1, """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) : "re" ((Model0_pao_T__)(1))); break; default: Model0___bad_percpu_size(); } } while (0);break; case 8: do { typedef typeof(((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) Model0_pao_T__; const int Model0_pao_ID__ = (__builtin_constant_p(1) && ((1) == 1 || (1) == -1)) ? (int)(1) : 0; if (0) { Model0_pao_T__ Model0_pao_tmp__; Model0_pao_tmp__ = (1); (void)Model0_pao_tmp__; } switch (sizeof(((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))) { case 1: if (Model0_pao_ID__ == 1) asm("incb """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else if (Model0_pao_ID__ == -1) asm("decb """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else asm("addb %1, """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) : "qi" ((Model0_pao_T__)(1))); break; case 2: if (Model0_pao_ID__ == 1) asm("incw """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else if (Model0_pao_ID__ == -1) asm("decw """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else asm("addw %1, """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) : "ri" ((Model0_pao_T__)(1))); break; case 4: if (Model0_pao_ID__ == 1) asm("incl """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else if (Model0_pao_ID__ == -1) asm("decl """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else asm("addl %1, """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) : "ri" ((Model0_pao_T__)(1))); break; case 8: if (Model0_pao_ID__ == 1) asm("incq """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else if (Model0_pao_ID__ == -1) asm("decq """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES]))); else asm("addq %1, """ "%" "0" : "+m" (((Model0_net)->Model0_mib.Model0_ip_statistics->Model0_mibs[Model0_IPSTATS_MIB_OUTNOROUTES])) : "re" ((Model0_pao_T__)(1))); break; default: Model0___bad_percpu_size(); } } while (0);break; default: Model0___bad_size_call_parameter();break; } } while (0); });
 return ((void *)0);
#endif
}

void Model0_inet_csk_reqsk_queue_drop(struct Model0_sock *Model0_sk, struct Model0_request_sock *Model0_req)
{
#if CY_ABSTRACT1
    //TODO: currently we ignore process to deal with hashqueue, and remove value so far
#else
 if (Model0_reqsk_queue_unlink(&Model0_inet_csk(Model0_sk)->Model0_icsk_accept_queue, Model0_req)) {
  Model0_reqsk_queue_removed(&Model0_inet_csk(Model0_sk)->Model0_icsk_accept_queue, Model0_req);
  Model0_reqsk_put(Model0_req);
 }
#endif
}
/*
 * Write buffer destructor automatically called from kfree_skb.
 */
void Model0_sock_wfree(struct Model0_sk_buff *Model0_skb)
{
#if CY_ABSTRACT3
    assert(0); //this skb allocate and free too frequently. We may ignore this logic
#else
 struct Model0_sock *Model0_sk = Model0_skb->Model0_sk;
 unsigned int Model0_len = Model0_skb->Model0_truesize;

 if (!Model0_sock_flag(Model0_sk, Model0_SOCK_USE_WRITE_QUEUE)) {
  /*
		 * Keep a reference on sk_wmem_alloc, this will be released
		 * after sk_write_space() call
		 */
  Model0_atomic_sub(Model0_len - 1, &Model0_sk->Model0_sk_wmem_alloc);
  Model0_sk->Model0_sk_write_space(Model0_sk);
  Model0_len = 1;
 }
 /*
	 * if sk_wmem_alloc reaches 0, we must finish what sk_free()
	 * could not do because of in-flight packets
	 */
 if (Model0_atomic_sub_and_test(Model0_len, &Model0_sk->Model0_sk_wmem_alloc))
  Model0___sk_free(Model0_sk);
#endif
}
void Model0_skb_set_owner_w(struct Model0_sk_buff *Model0_skb, struct Model0_sock *Model0_sk)
{
 Model0_skb_orphan(Model0_skb);
 Model0_skb->Model0_sk = Model0_sk;







 Model0_skb->Model0_destructor = Model0_sock_wfree;
 Model0_skb_set_hash_from_sk(Model0_skb, Model0_sk);
 /*
	 * We used to take a refcount on sk, but following operation
	 * is enough to guarantee sk_free() wont free this sock until
	 * all in-flight packets are completed
	 */
#if !CY_ABSTRACT3
 Model0_atomic_add(Model0_skb->Model0_truesize, &Model0_sk->Model0_sk_wmem_alloc);
#endif
}

/* Determine a window scaling and initial window to offer.
 * Based on the assumption that the given amount of space
 * will be offered. Store the results in the tp structure.
 * NOTE: for smooth operation initial space offering should
 * be a multiple of mss if possible. We assume here that mss >= 1.
 * This MUST be enforced by all callers.
 */
void Model0_tcp_select_initial_window(int Model0___space, __u32 Model0_mss,
          __u32 *Model0_rcv_wnd, __u32 *Model0_window_clamp,
          int Model0_wscale_ok, __u8 *Model0_rcv_wscale,
          __u32 Model0_init_rcv_wnd)
{
#if CY_ABSTRACT3
    assert(0);
#else
 unsigned int Model0_space = (Model0___space < 0 ? 0 : Model0___space);

 /* If no clamp set the clamp to the max possible scaled window */
 if (*Model0_window_clamp == 0)
  (*Model0_window_clamp) = (65535 << 14);
 Model0_space = ({ typeof(*Model0_window_clamp) Model0__min1 = (*Model0_window_clamp); typeof(Model0_space) Model0__min2 = (Model0_space); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });

 /* Quantize space offering to a multiple of mss if possible. */
 if (Model0_space > Model0_mss)
  Model0_space = (Model0_space / Model0_mss) * Model0_mss;

 /* NOTE: offering an initial window larger than 32767
	 * will break some buggy TCP stacks. If the admin tells us
	 * it is likely we could be speaking with such a buggy stack
	 * we will truncate our initial window offering to 32K-1
	 * unless the remote has sent us a window scaling option,
	 * which we interpret as a sign the remote TCP is not
	 * misinterpreting the window field as a signed quantity.
	 */
 if (Model0_sysctl_tcp_workaround_signed_windows)
  (*Model0_rcv_wnd) = ({ typeof(Model0_space) Model0__min1 = (Model0_space); typeof(32767U) Model0__min2 = (32767U); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
 else
  (*Model0_rcv_wnd) = Model0_space;

 (*Model0_rcv_wscale) = 0;
 if (Model0_wscale_ok) {
  /* Set window scaling on max possible window
		 * See RFC1323 for an explanation of the limit to 14
		 */
  Model0_space = ({ Model0_u32 Model0___max1 = (Model0_space); Model0_u32 Model0___max2 = (Model0_sysctl_tcp_rmem[2]); Model0___max1 > Model0___max2 ? Model0___max1: Model0___max2; });
  Model0_space = ({ Model0_u32 Model0___max1 = (Model0_space); Model0_u32 Model0___max2 = (Model0_sysctl_rmem_max); Model0___max1 > Model0___max2 ? Model0___max1: Model0___max2; });
  Model0_space = ({ Model0_u32 Model0___min1 = (Model0_space); Model0_u32 Model0___min2 = (*Model0_window_clamp); Model0___min1 < Model0___min2 ? Model0___min1: Model0___min2; });
  while (Model0_space > 65535 && (*Model0_rcv_wscale) < 14) {
   Model0_space >>= 1;
   (*Model0_rcv_wscale)++;
  }
 }

 if (Model0_mss > (1 << *Model0_rcv_wscale)) {
  if (!Model0_init_rcv_wnd) /* Use default unless specified otherwise */
   Model0_init_rcv_wnd = Model0_tcp_default_init_rwnd(Model0_mss);
  *Model0_rcv_wnd = ({ typeof(*Model0_rcv_wnd) Model0__min1 = (*Model0_rcv_wnd); typeof(Model0_init_rcv_wnd * Model0_mss) Model0__min2 = (Model0_init_rcv_wnd * Model0_mss); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
 }

 /* Set the clamp no higher than max representable value */
 (*Model0_window_clamp) = ({ typeof(65535U << (*Model0_rcv_wscale)) Model0__min1 = (65535U << (*Model0_rcv_wscale)); typeof(*Model0_window_clamp) Model0__min2 = (*Model0_window_clamp); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
#endif
}
static bool Model0_tcp_fastopen_cookie_gen(struct Model0_request_sock *Model0_req,
        struct Model0_sk_buff *Model0_syn,
        struct Model0_tcp_fastopen_cookie *Model0_foc)
{
    assert(0);
    return true;
}

/* Set up TCP options for SYN-ACKs. */
//copied from tcp_output.c
static unsigned int Model0_tcp_synack_options(struct Model0_request_sock *Model0_req,
           unsigned int Model0_mss, struct Model0_sk_buff *Model0_skb,
           struct Model0_tcp_out_options *Model0_opts,
           const struct Model0_tcp_md5sig_key *Model0_md5,
           struct Model0_tcp_fastopen_cookie *Model0_foc)
{
 struct Model0_inet_request_sock *Model0_ireq = Model0_inet_rsk(Model0_req);
 unsigned int Model0_remaining = 40;
 /* We always send an MSS option. */
 Model0_opts->Model0_mss = Model0_mss;
 Model0_remaining -= 4;

 if (__builtin_expect(!!(Model0_ireq->Model0_wscale_ok), 1)) {
  Model0_opts->Model0_ws = Model0_ireq->Model0_rcv_wscale;
  Model0_opts->Model0_options |= (1 << 3);
  Model0_remaining -= 4;
 }
 if (__builtin_expect(!!(Model0_ireq->Model0_tstamp_ok), 1)) {
  Model0_opts->Model0_options |= (1 << 1);
  Model0_opts->Model0_tsval = Model0_tcp_skb_timestamp(Model0_skb);
  Model0_opts->Model0_tsecr = Model0_req->Model0_ts_recent;
  Model0_remaining -= 12;
 }
 if (__builtin_expect(!!(Model0_ireq->Model0_sack_ok), 1)) {
  Model0_opts->Model0_options |= (1 << 0);
  if (__builtin_expect(!!(!Model0_ireq->Model0_tstamp_ok), 0))
   Model0_remaining -= 4;
 }
 if (Model0_foc != ((void *)0) && Model0_foc->Model0_len >= 0) {
  Model0_u32 Model0_need = Model0_foc->Model0_len;

  Model0_need += Model0_foc->Model0_exp ? 4 :
       2;
  Model0_need = (Model0_need + 3) & ~3U; /* Align to 32 bits */
  if (Model0_remaining >= Model0_need) {
   Model0_opts->Model0_options |= (1 << 8);
   Model0_opts->Model0_fastopen_cookie = Model0_foc;
   Model0_remaining -= Model0_need;
  }
 }

 return 40 - Model0_remaining;
}

static void
Model0_tcp_ecn_make_synack(const struct Model0_request_sock *Model0_req, struct Model0_tcphdr *Model0_th)
{
 if (Model0_inet_rsk(Model0_req)->Model0_ecn_ok)
  Model0_th->Model0_ece = 1;
}

static void Model0_tcp_options_write(Model0___be32 *Model0_ptr, struct Model0_tcp_sock *Model0_tp,
         struct Model0_tcp_out_options *Model0_opts){
    // we don't have options for the header
#if CY_ABSTRACT1
    return;
#else
    assert(0);
#endif
}

static bool Model0_tcp_fastopen_queue_check(struct Model0_sock *Model0_sk)
{
 struct Model0_fastopen_queue *Model0_fastopenq;

 /* Make sure the listener has enabled fastopen, and we don't
	 * exceed the max # of pending TFO requests allowed before trying
	 * to validating the cookie in order to avoid burning CPU cycles
	 * unnecessarily.
	 *
	 * XXX (TFO) - The implication of checking the max_qlen before
	 * processing a cookie request is that clients can't differentiate
	 * between qlen overflow causing Fast Open to be disabled
	 * temporarily vs a server not supporting Fast Open at all.
	 */
 Model0_fastopenq = &Model0_inet_csk(Model0_sk)->Model0_icsk_accept_queue.Model0_fastopenq;
 if (Model0_fastopenq->Model0_max_qlen == 0)
  return false;

 if (Model0_fastopenq->Model0_qlen >= Model0_fastopenq->Model0_max_qlen) {
  struct Model0_request_sock *Model0_req1;
  Model0_spin_lock(&Model0_fastopenq->Model0_lock);
  Model0_req1 = Model0_fastopenq->Model0_rskq_rst_head;
  if (!Model0_req1 || (({ unsigned long Model0___dummy; typeof(Model0_req1->Model0_rsk_timer.Model0_expires) Model0___dummy2; (void)(&Model0___dummy == &Model0___dummy2); 1; }) && ({ unsigned long Model0___dummy; typeof(Model0_jiffies) Model0___dummy2; (void)(&Model0___dummy == &Model0___dummy2); 1; }) && ((long)((Model0_jiffies) - (Model0_req1->Model0_rsk_timer.Model0_expires)) < 0))) {
   (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPFASTOPENLISTENOVERFLOW] += 1);

   Model0_spin_unlock(&Model0_fastopenq->Model0_lock);
   return false;
  }
  Model0_fastopenq->Model0_rskq_rst_head = Model0_req1->Model0_dl_next;
  Model0_fastopenq->Model0_qlen--;
  Model0_spin_unlock(&Model0_fastopenq->Model0_lock);
  Model0_reqsk_put(Model0_req1);
 }
 return true;
}

static bool Model0___tcp_fastopen_cookie_gen(const void *Model0_path,
          struct Model0_tcp_fastopen_cookie *Model0_foc)
{
    assert(0);
    return true;
    /*
 struct Model0_tcp_fastopen_context *Model0_ctx;
 bool Model0_ok = false;

 Model0_rcu_read_lock();
 Model0_ctx = ({ typeof(*(Model0_tcp_fastopen_ctx)) *Model0_________p1 = (typeof(*(Model0_tcp_fastopen_ctx)) *)({ typeof((Model0_tcp_fastopen_ctx)) Model0__________p1 = ({ union { typeof((Model0_tcp_fastopen_ctx)) Model0___val; char Model0___c[1]; } Model0___u; if (1) Model0___read_once_size(&((Model0_tcp_fastopen_ctx)), Model0___u.Model0___c, sizeof((Model0_tcp_fastopen_ctx))); else Model0___read_once_size_nocheck(&((Model0_tcp_fastopen_ctx)), Model0___u.Model0___c, sizeof((Model0_tcp_fastopen_ctx))); Model0___u.Model0___val; }); typeof(*((Model0_tcp_fastopen_ctx))) *Model0____typecheck_p __attribute__((unused)); do { } while (0); (Model0__________p1); }); do { } while (0); ; ((typeof(*(Model0_tcp_fastopen_ctx)) *)(Model0_________p1)); });
 if (Model0_ctx) {
  Model0_crypto_cipher_encrypt_one(Model0_ctx->Model0_tfm, Model0_foc->Model0_val, Model0_path);
  Model0_foc->Model0_len = 8;
  Model0_ok = true;
 }
 Model0_rcu_read_unlock();
 return Model0_ok;
 */
}

int Model0_memcmp(const void *s1, const void *s2, size_t n){
    return memcmp(s1, s2, n);
}

static struct Model0_sock *Model0_tcp_fastopen_create_child(struct Model0_sock *Model0_sk,
           struct Model0_sk_buff *Model0_skb,
           struct Model0_dst_entry *Model0_dst,
           struct Model0_request_sock *Model0_req)
{
    assert(0);
    return NULL;
}

Model0_u32 Model0_tcp_reno_ssthresh(struct Model0_sock *Model0_sk){
    assert(0);
    return 0;
}

static void Model0_sock_def_wakeup(struct Model0_sock *Model0_sk){
#if CY_ABSTRACT3
    //Default Socket Callbacks
    //TODO: currently we assume no callback or no concurrency
#endif
}

static void Model0_sock_def_readable(struct Model0_sock *Model0_sk){
#if CY_ABSTRACT1
    //We assume one-way interleaving, so we ignore such concurrency
#else
    assert(0);
#endif
}
void Model0_inet_sk_rx_dst_set(struct Model0_sock *Model0_sk, const struct Model0_sk_buff *Model0_skb){
#if CY_ABSTRACT3
    //TODO: assume dst in IP layer
#else
    assert(0);
#endif
}

int Model0_inet_sk_rebuild_header(struct Model0_sock *Model0_sk){
#if CY_ABSTRACT3
    //we ignore route in IP layer
    return 0; //always correct
#endif
}
/****** functions ******/
Model0_u32 Model0_tcp_default_init_rwnd(Model0_u32 Model0_mss)
{
 /* Initial receive window should be twice of TCP_INIT_CWND to
	 * enable proper sending of new unsent data during fast recovery
	 * (RFC 3517, Section 4, NextSeg() rule (2)). Further place a
	 * limit when mss is larger than 1460.
	 */
 Model0_u32 Model0_init_rwnd = 10 * 2;

 if (Model0_mss > 1460)
  Model0_init_rwnd = ({ typeof((1460 * Model0_init_rwnd) / Model0_mss) Model0__max1 = ((1460 * Model0_init_rwnd) / Model0_mss); typeof(2U) Model0__max2 = (2U); (void) (&Model0__max1 == &Model0__max2); Model0__max1 > Model0__max2 ? Model0__max1 : Model0__max2; });
 return Model0_init_rwnd;
}

unsigned int Model0_tcp_current_mss(struct Model0_sock *Model0_sk){
#if CY_ABSTRACT3
    return 65535;
#endif
}

void Model0_tcp_xmit_retransmit_queue(struct Model0_sock *cy){
    assert(0);
}

unsigned int Model0_jiffies_to_usecs(const unsigned long Model0_j){
#if CY_ABSTRACT3
    return (1000000L / 1000) * Model0_j;
#endif
}

unsigned long Model0___usecs_to_jiffies(const unsigned int Model0_u){
#if CY_ABSTRACT2
    // always false
    /*
    if (u > jiffies_to_usecs(MAX_JIFFY_OFFSET))
        return MAX_JIFFY_OFFSET;
    */
    return Model0__usecs_to_jiffies(Model0_u);
#else
    assert(0);
    return 0;
#endif
}

unsigned long Model0___msecs_to_jiffies(const unsigned int Model0_m){
#if CY_ABSTRACT3
   if ((int)Model0_m < 0)
       return ((((long)(~0UL>>1)) >> 1)-1);
   return Model0__msecs_to_jiffies(Model0_m);
#endif
}

Model0_u64 Model0_sched_clock_cpu(int Model0_cpu){ 
#if CY_ABSTRACT2
    return 0;
#else
	if (unlikely(!sched_clock_running))
		return 0;

	return sched_clock();
#endif
}

void Model0_sk_reset_timer(struct Model0_sock *Model0_sk, struct Model0_timer_list *Model0_timer,
unsigned long Model0_expires){
    assert(0);
}

int Model0_tcp_fragment(struct Model0_sock *cy0, struct Model0_sk_buff *cy, Model0_u32 cy1, unsigned int cy2,   Model0_gfp_t cy3) {
    assert(0);
}

int Model0_net_ratelimit(void){
    assert(0);
}

void Model0_tcp_done(struct Model0_sock *Model0_sk){
    assert(0);
}

void Model0_inet_put_port(struct Model0_sock *Model0_sk){
    assert(0);
}
void Model0_tcp_set_state(struct Model0_sock *Model0_sk, int Model0_state)
{
 int Model0_oldstate = Model0_sk->Model0___sk_common.Model0_skc_state;

 switch (Model0_state) {
 case Model0_TCP_ESTABLISHED:
  if (Model0_oldstate != Model0_TCP_ESTABLISHED)
   (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_CURRESTAB] += 1);
  break;

 case Model0_TCP_CLOSE:
  if (Model0_oldstate == Model0_TCP_CLOSE_WAIT || Model0_oldstate == Model0_TCP_ESTABLISHED)
   (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_ESTABRESETS] += 1);

  Model0_sk->Model0___sk_common.Model0_skc_prot->Model0_unhash(Model0_sk);
  if (Model0_inet_csk(Model0_sk)->Model0_icsk_bind_hash &&
      !(Model0_sk->Model0_sk_userlocks & 8))
   Model0_inet_put_port(Model0_sk);
  /* fall through */
 default:
  if (Model0_oldstate == Model0_TCP_ESTABLISHED)
   (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_CURRESTAB] -= 1);
 }

 /* Change state AFTER socket is unhashed to avoid closed
	 * socket sitting in hash tables.
	 */
 Model0_sk_state_store(Model0_sk, Model0_state);




}

/**
 * tcp_make_synack - Prepare a SYN-ACK.
 * sk: listener socket
 * dst: dst entry attached to the SYNACK
 * req: request_sock pointer
 *
 * Allocate one skb and build a SYNACK packet.
 * @dst is consumed : Caller should not use it again.
 */
struct Model0_sk_buff *Model0_tcp_make_synack(const struct Model0_sock *Model0_sk, struct Model0_dst_entry *Model0_dst,
    struct Model0_request_sock *Model0_req,
    struct Model0_tcp_fastopen_cookie *Model0_foc,
    enum Model0_tcp_synack_type Model0_synack_type)
{
 struct Model0_inet_request_sock *Model0_ireq = Model0_inet_rsk(Model0_req);
 const struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_tcp_md5sig_key *Model0_md5 = ((void *)0);
 struct Model0_tcp_out_options Model0_opts;
 struct Model0_sk_buff *Model0_skb;
 int Model0_tcp_header_size;
 struct Model0_tcphdr *Model0_th;
 Model0_u16 Model0_user_mss;
 int Model0_mss;

#if CY_ABSTRACT4
 Model0_skb = &Model0_Skb_Out;
 Model0_cy_alloc_skb(Model0_skb, Model0_Buff_Out, Model0_SKB_DATA_SIZE);
#else
 Model0_skb = Model0_alloc_skb((128 + 32), ((( Model0_gfp_t)0x20u)|(( Model0_gfp_t)0x80000u)|(( Model0_gfp_t)0x2000000u)));
 if (__builtin_expect(!!(!Model0_skb), 0)) {
  Model0_dst_release(Model0_dst);
  return ((void *)0);
 }
#endif
 /* Reserve space for headers. */
 Model0_skb_reserve(Model0_skb, (128 + 32));

 switch (Model0_synack_type) {
 case Model0_TCP_SYNACK_NORMAL:
  Model0_skb_set_owner_w(Model0_skb, Model0_req_to_sk(Model0_req));
  break;
 case Model0_TCP_SYNACK_COOKIE:
  /* Under synflood, we do not attach skb to a socket,
		 * to avoid false sharing.
		 */
  break;
 case Model0_TCP_SYNACK_FASTOPEN:
  /* sk is a const pointer, because we want to express multiple
		 * cpu might call us concurrently.
		 * sk->sk_wmem_alloc in an atomic, we can promote to rw.
		 */
  Model0_skb_set_owner_w(Model0_skb, (struct Model0_sock *)Model0_sk);
  break;
 }
#if !CY_ABSTRACT3
 Model0_skb_dst_set(Model0_skb, Model0_dst);
#endif

 Model0_mss = Model0_dst_metric_advmss(Model0_dst);
 Model0_user_mss = ({ union { typeof(Model0_tp->Model0_rx_opt.Model0_user_mss) Model0___val; char Model0___c[1]; } Model0___u; if (1) Model0___read_once_size(&(Model0_tp->Model0_rx_opt.Model0_user_mss), Model0___u.Model0___c, sizeof(Model0_tp->Model0_rx_opt.Model0_user_mss)); else Model0___read_once_size_nocheck(&(Model0_tp->Model0_rx_opt.Model0_user_mss), Model0___u.Model0___c, sizeof(Model0_tp->Model0_rx_opt.Model0_user_mss)); Model0___u.Model0___val; });
 if (Model0_user_mss && Model0_user_mss < Model0_mss)
  Model0_mss = Model0_user_mss;

 memset(&Model0_opts, 0, sizeof(Model0_opts));





 Model0_skb_mstamp_get(&Model0_skb->Model0_skb_mstamp);





 Model0_skb_set_hash(Model0_skb, Model0_tcp_rsk(Model0_req)->Model0_txhash, Model0_PKT_HASH_TYPE_L4);
 Model0_tcp_header_size = Model0_tcp_synack_options(Model0_req, Model0_mss, Model0_skb, &Model0_opts, Model0_md5, Model0_foc) +
     sizeof(*Model0_th);

 Model0_skb_push(Model0_skb, Model0_tcp_header_size);
 Model0_skb_reset_transport_header(Model0_skb);

 Model0_th = (struct Model0_tcphdr *)Model0_skb->Model0_data;
 memset(Model0_th, 0, sizeof(struct Model0_tcphdr));
 Model0_th->Model0_syn = 1;
 Model0_th->Model0_ack = 1;
 Model0_tcp_ecn_make_synack(Model0_req, Model0_th);
 Model0_th->Model0_source = (( Model0___be16)(__builtin_constant_p((Model0___u16)((Model0_ireq->Model0_req.Model0___req_common.Model0_skc_num))) ? ((Model0___u16)( (((Model0___u16)((Model0_ireq->Model0_req.Model0___req_common.Model0_skc_num)) & (Model0___u16)0x00ffU) << 8) | (((Model0___u16)((Model0_ireq->Model0_req.Model0___req_common.Model0_skc_num)) & (Model0___u16)0xff00U) >> 8))) : Model0___fswab16((Model0_ireq->Model0_req.Model0___req_common.Model0_skc_num))));
 Model0_th->Model0_dest = Model0_ireq->Model0_req.Model0___req_common.Model0_skc_dport;
 /* Setting of flags are superfluous here for callers (and ECE is
	 * not even correctly set)
	 */
 Model0_tcp_init_nondata_skb(Model0_skb, Model0_tcp_rsk(Model0_req)->Model0_snt_isn,
        0x02 | 0x10);

 Model0_th->Model0_seq = (( Model0___be32)(__builtin_constant_p((__u32)((((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq))) ? ((__u32)( (((__u32)((((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)((((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32((((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq))));
 /* XXX data is queued and acked as is. No buffer/window check */
 Model0_th->Model0_ack_seq = (( Model0___be32)(__builtin_constant_p((__u32)((Model0_tcp_rsk(Model0_req)->Model0_rcv_nxt))) ? ((__u32)( (((__u32)((Model0_tcp_rsk(Model0_req)->Model0_rcv_nxt)) & (__u32)0x000000ffUL) << 24) | (((__u32)((Model0_tcp_rsk(Model0_req)->Model0_rcv_nxt)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((Model0_tcp_rsk(Model0_req)->Model0_rcv_nxt)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((Model0_tcp_rsk(Model0_req)->Model0_rcv_nxt)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32((Model0_tcp_rsk(Model0_req)->Model0_rcv_nxt))));

 /* RFC1323: The window in SYN & SYN/ACK segments is never scaled. */
 Model0_th->Model0_window = (( Model0___be16)(__builtin_constant_p((Model0___u16)((({ typeof(Model0_req->Model0___req_common.Model0_skc_rcv_wnd) Model0__min1 = (Model0_req->Model0___req_common.Model0_skc_rcv_wnd); typeof(65535U) Model0__min2 = (65535U); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; })))) ? ((Model0___u16)( (((Model0___u16)((({ typeof(Model0_req->Model0___req_common.Model0_skc_rcv_wnd) Model0__min1 = (Model0_req->Model0___req_common.Model0_skc_rcv_wnd); typeof(65535U) Model0__min2 = (65535U); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; }))) & (Model0___u16)0x00ffU) << 8) | (((Model0___u16)((({ typeof(Model0_req->Model0___req_common.Model0_skc_rcv_wnd) Model0__min1 = (Model0_req->Model0___req_common.Model0_skc_rcv_wnd); typeof(65535U) Model0__min2 = (65535U); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; }))) & (Model0___u16)0xff00U) >> 8))) : Model0___fswab16((({ typeof(Model0_req->Model0___req_common.Model0_skc_rcv_wnd) Model0__min1 = (Model0_req->Model0___req_common.Model0_skc_rcv_wnd); typeof(65535U) Model0__min2 = (65535U); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; })))));
 Model0_tcp_options_write((Model0___be32 *)(Model0_th + 1), ((void *)0), &Model0_opts);
 Model0_th->Model0_doff = (Model0_tcp_header_size >> 2);
 (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_OUTSEGS] += 1);
 /* Do not fool tcpdump (if any), clean our debris */
 Model0_skb->Model0_tstamp.Model0_tv64 = 0;
 return Model0_skb;
}

void Model0_tcp_send_ack(struct Model0_sock *Model0_sk){
	//cy consider to use one global variable, instead of using dynamic allocation.
    
    struct Model0_sk_buff *Model0_buff;
    struct Model0_sock * Model0_temp;
    //dst: Current from Attacker to Server/Server_A -> going to send a packet from Server/Server_A
    if (Model0_Src_sk == true){
        Model0_Out_pkt = true;
    }
    //Modify 06/11/2018 Right now we only have one direction from Client or Attacker to Server
    //We assume Client won't send packet to Server so we ignore packets sent to Client
    else{
        //return;
        Model0_Out_pkt = false;
    }

	/* If we have been reset, we may not send again. */
	if (Model0_sk->Model0___sk_common.Model0_skc_state == Model0_TCP_CLOSE)
		return;
    
    //cy: remove tcp_ca_event rihgt now. Othersie Segmentation fault
	Model0_tcp_ca_event(Model0_sk, 7); //CA_EVENT_NON_DELAYED_ACK

#if CY_ABSTRACT4
    Model0_buff = &Model0_Skb_Out;
    Model0_cy_alloc_skb(Model0_buff, Model0_Buff_Out, Model0_SKB_DATA_SIZE);
	/* We are not putting this on the write queue, so
	 * tcp_transmit_skb() will set the ownership to this
	 * sock.
	 */
#else
	buff = alloc_skb(MAX_TCP_HEADER,
			 sk_gfp_mask(sk, GFP_ATOMIC | __GFP_NOWARN));
	// Assume every time buff would be allocated successfully

  	if ((!buff)) {
	   inet_csk_schedule_ack(sk);
   		inet_csk(sk)->icsk_ack.ato = ((unsigned)(1000/25));
   		inet_csk_reset_xmit_timer(sk, 2,
        	((unsigned)(1000/5)), ((unsigned)(120*1000)));
   		return;
  	}
#endif
	/* Reserve space for headers and prepare control bits. */
	// cy: both data and tail pointer would be increased.
	Model0_skb_reserve(Model0_buff, (128 + (96 + 48)));
	// cy: add the ack number and seq number
	Model0_tcp_init_nondata_skb(Model0_buff, Model0_tcp_acceptable_seq(Model0_sk), 0x10); //0x10 -> ACK

	/* We do not want pure acks influencing TCP Small Queues or fq/pacing
	 * too much.
	 * SKB_TRUESIZE(max(1 .. 66, MAX_TCP_HEADER)) is unfortunately ~784
	 * We also avoid tcp_wfree() overhead (cache line miss accessing
	 * tp->tsq_flags) by using regular sock_wfree()
	 */
	Model0_skb_set_tcp_pure_ack(Model0_buff);

	/* Send it off, this clears delayed acks for us. */
    //cy: not sure about this part. UNCLEAR
	Model0_skb_mstamp_get(&Model0_buff->Model0_skb_mstamp);

    //cy_tcp_transmit_skb(sk, buff, flag_visited1);
	//tcp_transmit_skb(sk, buff, 0, (__force gfp_t)0); 
	Model0_cy_tcp_transmit_skb(Model0_sk, Model0_buff, 0, 0);
           
    //CY: Currently we ignore function:tcp_rcv_established
}

void Model0_tcp_time_wait(struct Model0_sock *Model0_sk, int Model0_state, int Model0_timeo){
    assert(0);
}

/**
 *	kfree_skb - free an sk_buff
 *	@skb: buffer to free
 *
 *	Drop a reference to the buffer and free it if the usage count has
 *	hit zero.
 */
void Model0_kfree_skb(struct Model0_sk_buff *Model0_skb)
{
//this function won't be visited
 if (__builtin_expect(!!(!Model0_skb), 0))
  return;
 if (__builtin_expect(!!(Model0_atomic_read(&Model0_skb->Model0_users) == 1), 1))
  __asm__ __volatile__("": : :"memory");
 else if (__builtin_expect(!!(!Model0_atomic_dec_and_test(&Model0_skb->Model0_users)), 1))
  return;
#if !CY_ABSTRACT3
 //somehow cannot find its declaration and defintition at all
 Model0_trace_kfree_skb(Model0_skb, __builtin_return_address(0));
#endif
 Model0___kfree_skb(Model0_skb);
}

/**
 *	__sk_mem_reclaim - reclaim memory_allocated
 *	@sk: socket
 *	@amount: number of bytes (rounded down to a SK_MEM_QUANTUM multiple)
 */
void Model0___sk_mem_reclaim(struct Model0_sock *Model0_sk, int Model0_amount)
{
 Model0_amount >>= ( __builtin_constant_p(((int)((1UL) << 12))) ? ( (((int)((1UL) << 12))) < 1 ? Model0_____ilog2_NaN() : (((int)((1UL) << 12))) & (1ULL << 63) ? 63 : (((int)((1UL) << 12))) & (1ULL << 62) ? 62 : (((int)((1UL) << 12))) & (1ULL << 61) ? 61 : (((int)((1UL) << 12))) & (1ULL << 60) ? 60 : (((int)((1UL) << 12))) & (1ULL << 59) ? 59 : (((int)((1UL) << 12))) & (1ULL << 58) ? 58 : (((int)((1UL) << 12))) & (1ULL << 57) ? 57 : (((int)((1UL) << 12))) & (1ULL << 56) ? 56 : (((int)((1UL) << 12))) & (1ULL << 55) ? 55 : (((int)((1UL) << 12))) & (1ULL << 54) ? 54 : (((int)((1UL) << 12))) & (1ULL << 53) ? 53 : (((int)((1UL) << 12))) & (1ULL << 52) ? 52 : (((int)((1UL) << 12))) & (1ULL << 51) ? 51 : (((int)((1UL) << 12))) & (1ULL << 50) ? 50 : (((int)((1UL) << 12))) & (1ULL << 49) ? 49 : (((int)((1UL) << 12))) & (1ULL << 48) ? 48 : (((int)((1UL) << 12))) & (1ULL << 47) ? 47 : (((int)((1UL) << 12))) & (1ULL << 46) ? 46 : (((int)((1UL) << 12))) & (1ULL << 45) ? 45 : (((int)((1UL) << 12))) & (1ULL << 44) ? 44 : (((int)((1UL) << 12))) & (1ULL << 43) ? 43 : (((int)((1UL) << 12))) & (1ULL << 42) ? 42 : (((int)((1UL) << 12))) & (1ULL << 41) ? 41 : (((int)((1UL) << 12))) & (1ULL << 40) ? 40 : (((int)((1UL) << 12))) & (1ULL << 39) ? 39 : (((int)((1UL) << 12))) & (1ULL << 38) ? 38 : (((int)((1UL) << 12))) & (1ULL << 37) ? 37 : (((int)((1UL) << 12))) & (1ULL << 36) ? 36 : (((int)((1UL) << 12))) & (1ULL << 35) ? 35 : (((int)((1UL) << 12))) & (1ULL << 34) ? 34 : (((int)((1UL) << 12))) & (1ULL << 33) ? 33 : (((int)((1UL) << 12))) & (1ULL << 32) ? 32 : (((int)((1UL) << 12))) & (1ULL << 31) ? 31 : (((int)((1UL) << 12))) & (1ULL << 30) ? 30 : (((int)((1UL) << 12))) & (1ULL << 29) ? 29 : (((int)((1UL) << 12))) & (1ULL << 28) ? 28 : (((int)((1UL) << 12))) & (1ULL << 27) ? 27 : (((int)((1UL) << 12))) & (1ULL << 26) ? 26 : (((int)((1UL) << 12))) & (1ULL << 25) ? 25 : (((int)((1UL) << 12))) & (1ULL << 24) ? 24 : (((int)((1UL) << 12))) & (1ULL << 23) ? 23 : (((int)((1UL) << 12))) & (1ULL << 22) ? 22 : (((int)((1UL) << 12))) & (1ULL << 21) ? 21 : (((int)((1UL) << 12))) & (1ULL << 20) ? 20 : (((int)((1UL) << 12))) & (1ULL << 19) ? 19 : (((int)((1UL) << 12))) & (1ULL << 18) ? 18 : (((int)((1UL) << 12))) & (1ULL << 17) ? 17 : (((int)((1UL) << 12))) & (1ULL << 16) ? 16 : (((int)((1UL) << 12))) & (1ULL << 15) ? 15 : (((int)((1UL) << 12))) & (1ULL << 14) ? 14 : (((int)((1UL) << 12))) & (1ULL << 13) ? 13 : (((int)((1UL) << 12))) & (1ULL << 12) ? 12 : (((int)((1UL) << 12))) & (1ULL << 11) ? 11 : (((int)((1UL) << 12))) & (1ULL << 10) ? 10 : (((int)((1UL) << 12))) & (1ULL << 9) ? 9 : (((int)((1UL) << 12))) & (1ULL << 8) ? 8 : (((int)((1UL) << 12))) & (1ULL << 7) ? 7 : (((int)((1UL) << 12))) & (1ULL << 6) ? 6 : (((int)((1UL) << 12))) & (1ULL << 5) ? 5 : (((int)((1UL) << 12))) & (1ULL << 4) ? 4 : (((int)((1UL) << 12))) & (1ULL << 3) ? 3 : (((int)((1UL) << 12))) & (1ULL << 2) ? 2 : (((int)((1UL) << 12))) & (1ULL << 1) ? 1 : (((int)((1UL) << 12))) & (1ULL << 0) ? 0 : Model0_____ilog2_NaN() ) : (sizeof(((int)((1UL) << 12))) <= 4) ? Model0___ilog2_u32(((int)((1UL) << 12))) : Model0___ilog2_u64(((int)((1UL) << 12))) );
 Model0_sk_memory_allocated_sub(Model0_sk, Model0_amount);
 Model0_sk->Model0_sk_forward_alloc -= Model0_amount << ( __builtin_constant_p(((int)((1UL) << 12))) ? ( (((int)((1UL) << 12))) < 1 ? Model0_____ilog2_NaN() : (((int)((1UL) << 12))) & (1ULL << 63) ? 63 : (((int)((1UL) << 12))) & (1ULL << 62) ? 62 : (((int)((1UL) << 12))) & (1ULL << 61) ? 61 : (((int)((1UL) << 12))) & (1ULL << 60) ? 60 : (((int)((1UL) << 12))) & (1ULL << 59) ? 59 : (((int)((1UL) << 12))) & (1ULL << 58) ? 58 : (((int)((1UL) << 12))) & (1ULL << 57) ? 57 : (((int)((1UL) << 12))) & (1ULL << 56) ? 56 : (((int)((1UL) << 12))) & (1ULL << 55) ? 55 : (((int)((1UL) << 12))) & (1ULL << 54) ? 54 : (((int)((1UL) << 12))) & (1ULL << 53) ? 53 : (((int)((1UL) << 12))) & (1ULL << 52) ? 52 : (((int)((1UL) << 12))) & (1ULL << 51) ? 51 : (((int)((1UL) << 12))) & (1ULL << 50) ? 50 : (((int)((1UL) << 12))) & (1ULL << 49) ? 49 : (((int)((1UL) << 12))) & (1ULL << 48) ? 48 : (((int)((1UL) << 12))) & (1ULL << 47) ? 47 : (((int)((1UL) << 12))) & (1ULL << 46) ? 46 : (((int)((1UL) << 12))) & (1ULL << 45) ? 45 : (((int)((1UL) << 12))) & (1ULL << 44) ? 44 : (((int)((1UL) << 12))) & (1ULL << 43) ? 43 : (((int)((1UL) << 12))) & (1ULL << 42) ? 42 : (((int)((1UL) << 12))) & (1ULL << 41) ? 41 : (((int)((1UL) << 12))) & (1ULL << 40) ? 40 : (((int)((1UL) << 12))) & (1ULL << 39) ? 39 : (((int)((1UL) << 12))) & (1ULL << 38) ? 38 : (((int)((1UL) << 12))) & (1ULL << 37) ? 37 : (((int)((1UL) << 12))) & (1ULL << 36) ? 36 : (((int)((1UL) << 12))) & (1ULL << 35) ? 35 : (((int)((1UL) << 12))) & (1ULL << 34) ? 34 : (((int)((1UL) << 12))) & (1ULL << 33) ? 33 : (((int)((1UL) << 12))) & (1ULL << 32) ? 32 : (((int)((1UL) << 12))) & (1ULL << 31) ? 31 : (((int)((1UL) << 12))) & (1ULL << 30) ? 30 : (((int)((1UL) << 12))) & (1ULL << 29) ? 29 : (((int)((1UL) << 12))) & (1ULL << 28) ? 28 : (((int)((1UL) << 12))) & (1ULL << 27) ? 27 : (((int)((1UL) << 12))) & (1ULL << 26) ? 26 : (((int)((1UL) << 12))) & (1ULL << 25) ? 25 : (((int)((1UL) << 12))) & (1ULL << 24) ? 24 : (((int)((1UL) << 12))) & (1ULL << 23) ? 23 : (((int)((1UL) << 12))) & (1ULL << 22) ? 22 : (((int)((1UL) << 12))) & (1ULL << 21) ? 21 : (((int)((1UL) << 12))) & (1ULL << 20) ? 20 : (((int)((1UL) << 12))) & (1ULL << 19) ? 19 : (((int)((1UL) << 12))) & (1ULL << 18) ? 18 : (((int)((1UL) << 12))) & (1ULL << 17) ? 17 : (((int)((1UL) << 12))) & (1ULL << 16) ? 16 : (((int)((1UL) << 12))) & (1ULL << 15) ? 15 : (((int)((1UL) << 12))) & (1ULL << 14) ? 14 : (((int)((1UL) << 12))) & (1ULL << 13) ? 13 : (((int)((1UL) << 12))) & (1ULL << 12) ? 12 : (((int)((1UL) << 12))) & (1ULL << 11) ? 11 : (((int)((1UL) << 12))) & (1ULL << 10) ? 10 : (((int)((1UL) << 12))) & (1ULL << 9) ? 9 : (((int)((1UL) << 12))) & (1ULL << 8) ? 8 : (((int)((1UL) << 12))) & (1ULL << 7) ? 7 : (((int)((1UL) << 12))) & (1ULL << 6) ? 6 : (((int)((1UL) << 12))) & (1ULL << 5) ? 5 : (((int)((1UL) << 12))) & (1ULL << 4) ? 4 : (((int)((1UL) << 12))) & (1ULL << 3) ? 3 : (((int)((1UL) << 12))) & (1ULL << 2) ? 2 : (((int)((1UL) << 12))) & (1ULL << 1) ? 1 : (((int)((1UL) << 12))) & (1ULL << 0) ? 0 : Model0_____ilog2_NaN() ) : (sizeof(((int)((1UL) << 12))) <= 4) ? Model0___ilog2_u32(((int)((1UL) << 12))) : Model0___ilog2_u64(((int)((1UL) << 12))) );

 if (0 && Model0_sk->Model0_sk_memcg)
  Model0_mem_cgroup_uncharge_skmem(Model0_sk->Model0_sk_memcg, Model0_amount);

 if (Model0_sk_under_memory_pressure(Model0_sk) &&
     (Model0_sk_memory_allocated(Model0_sk) < Model0_sk_prot_mem_limits(Model0_sk, 0)))
  Model0_sk_leave_memory_pressure(Model0_sk);
}

int Model0_sock_wake_async(struct Model0_socket_wq *Model0_sk_wq, int Model0_how, int Model0_band){
    assert(0);
}

struct Model0_sk_buff *Model0_alloc_skb_with_frags(unsigned long Model0_header_len,
    unsigned long Model0_data_len,
    int Model0_max_page_order,
    int *Model0_errcode,
    Model0_gfp_t Model0_gfp_mask){
    assert(0);
    struct Model0_sk_buff *cy;
    return cy;
}

unsigned char *Model0_skb_put(struct Model0_sk_buff *Model0_skb, unsigned int Model0_len){
  unsigned char *Model0_tmp = Model0_skb_tail_pointer(Model0_skb);
    //SKB_LINEAR_ASSERT(skb);
  //do { if (skb_is_nonlinear(skb)) do { asm volatile("1:\tud2\n" ".pushsection __bug_table,\"a\"\n" "2:\t.long 1b - 2b, %c0 - 2b\n" "\t.word %c1, 0\n" "\t.org 2b+   %c2\n" ".popsection" : : "i" ("net/core/skbuff.c"), "i" (1433), "i" (sizeof(struct bug_entry)));  __builtin_unreachable(); } while (0); } while (0);
  Model0_skb->Model0_tail += Model0_len;
  Model0_skb->Model0_len += Model0_len;
  if (Model0_skb->Model0_tail > Model0_skb->Model0_end)
   //skb_over_panic(skb, len, __builtin_return_address(0));
   // some alert
   exit	(0);

  return Model0_tmp;
}

int Model0_skb_copy_datagram_from_iter(struct Model0_sk_buff *Model0_skb, int Model0_offset,
    struct Model0_iov_iter *Model0_from, int Model0_len) {
    assert(0);
    return 0;
}

// free skb space
void Model0_sock_rfree(struct Model0_sk_buff *Model0_skb){ //remove truesize
    struct Model0_sock *Model0_sk = Model0_skb->Model0_sk;
  	unsigned int Model0_len = Model0_skb->Model0_truesize;

  	Model0_atomic_sub(Model0_len, &Model0_sk->Model0_sk_backlog.Model0_rmem_alloc);
  	Model0_sk_mem_uncharge(Model0_sk, Model0_len);
}

static void Model0_skb_release_data(struct Model0_sk_buff *Model0_skb){
#if CY_ABSTRACT3
    //The size calculation is done in function skb_release_head_state
    //we ignore the codes that actually frees data memory (linear space: skb->head, shinfo->frags, and shinfo->frag_list)
#endif 
}

static void Model0_skb_release_head_state(struct Model0_sk_buff *Model0_skb);

static void Model0_skb_release_all(struct Model0_sk_buff *Model0_skb){
    Model0_skb_release_head_state(Model0_skb);
    if (Model0_skb->Model0_head)
        Model0_skb_release_data(Model0_skb);
}

static void Model0_kfree_skbmem(struct Model0_sk_buff *Model0_skb){
#if CY_ABSTRACT3
    //Free an skbuff by memory without cleaning the state
    //We ignore the codes that actually free data, which is out of scope and requires physical interfaces
#endif
}

static void Model0_skb_release_head_state(struct Model0_sk_buff *Model0_skb){
    Model0_skb_dst_drop(Model0_skb);
#if CY_ABSTRACT3 
//Assume CONFIG_XFRM 0 <= regardless of IPSec
#else
    Model0_secpath_put(Model0_skb->Model0_sp);
#endif

    if (Model0_skb->Model0_destructor){ //if it's assigned, it's sock_rfree
        Model0_skb->Model0_destructor(Model0_skb);
    }
#if CY_ABSTRACT3
//Assume IS_ENABLED(CONFIG_NF_CONNTRACK) 0 <= netfilter connection track is not used
#else
    Model0_nf_conntrack_put(Model0_skb->Model0_nfct);
#endif
}

void Model0___kfree_skb(struct Model0_sk_buff *Model0_skb){
    //We didn't dynamically allocate memory, so we don't release such memory
    //Instead, only update memory counted in receive buff
    //skb_release_all:skb_release_head_state:
    Model0_skb_release_all(Model0_skb);
    Model0_kfree_skbmem(Model0_skb);
    if (Model0_skb->Model0_destructor){ //if it's assigned, it's sock_rfree from skb_set_owner_r
        Model0_skb->Model0_destructor(Model0_skb);
    }
    return;
}
void Model0_warn_slowpath_null(const char *Model0_file, int Model0_line){
    //__warn(file, line, __builtin_return_address(0), TAINT_WARN, NULL, NULL);
    return;
}
bool Model0_skb_try_coalesce(struct Model0_sk_buff *Model0_to, struct Model0_sk_buff *Model0_from, bool *Model0_fragstolen, int *Model0_delta_truesize){
 int Model0_i, Model0_delta, Model0_len = Model0_from->Model0_len;
 
  *Model0_fragstolen = false;

  if (Model0_skb_cloned(Model0_to)) //[CY] assuem skb_clone is false
   return false;

//[CY] assume aggresively that skb_tailroom(to) == 0 (i.e., no space left for new data). So we need to allocate more space, make delta = len;
  if (Model0_len <= Model0_skb_tailroom(Model0_to)) {
   if (Model0_len)
#if CY_ABSTRACT4
       Model0_skb_copy_bits(Model0_from, 0, Model0_skb_put(Model0_to, Model0_len), Model0_len); //put is used to change the tailroom
#else
    //do { if (__builtin_expect(!!(Model0_skb_copy_bits(Model0_from, 0, Model0_skb_put(Model0_to, Model0_len), Model0_len)), 0)) do { asm volatile("1:\tud2\n" ".pushsection __bug_table,\"a\"\n" "2:\t.long  1b - 2b, %c0 - 2b\n" "\t.word %c1, 0\n" "\t.org 2b+%c2\n" ".popsection" : : "i" ("net/core/skbuff.c"), "i" (4254), "i" (sizeof(struct Model0_bug_entry))); do { }       while (1); } while (0); } while (0);
#endif
   *Model0_delta_truesize = 0;
   return true;
  }
 
#if !CY_ABSTRACT1
  if (Model0_skb_has_frag_list(Model0_to) || Model0_skb_has_frag_list(Model0_from))
   return false;
#endif

  if (Model0_skb_headlen(Model0_from) != 0) {
   struct Model0_page *Model0_page;
   unsigned int Model0_offset;
 
   if (((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_to)))->Model0_nr_frags +
       ((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_from)))->Model0_nr_frags >= (65536/((1UL) << 12) + 1))
    return false;

   // if skb->head_frag == 0 || skb_cloned(skb); //always return true since skb->head_frag == 0
   if (Model0_skb_head_is_locked(Model0_from))
    return false;
 
   Model0_delta = Model0_from->Model0_truesize - ((((sizeof(struct Model0_sk_buff))) + ((typeof((sizeof(struct Model0_sk_buff))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model0_sk_buff))))(((1 <<  (6)))) - 1));
   Model0_page = Model0_virt_to_head_page(Model0_from->Model0_head);
   Model0_offset = Model0_from->Model0_data - (unsigned char *)Model0_lowmem_page_address(Model0_page);
 
   Model0_skb_fill_page_desc(Model0_to, ((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_to)))->Model0_nr_frags,
        Model0_page, Model0_offset, Model0_skb_headlen(Model0_from));
   *Model0_fragstolen = true;
  }
  else {
   if (((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_to)))->Model0_nr_frags +
       ((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_from)))->Model0_nr_frags > (65536/((1UL) << 12) + 1))
    return false;
 
   Model0_delta = Model0_from->Model0_truesize - ((Model0_skb_end_offset(Model0_from)) + ((((sizeof(struct Model0_sk_buff))) + ((typeof((sizeof(struct Model0_sk_buff))))(((1 << (6)))) - 1)) &                    ~((typeof((sizeof(struct Model0_sk_buff))))(((1 << (6)))) - 1)) + ((((sizeof(struct Model0_skb_shared_info))) + ((typeof((sizeof(struct Model0_skb_shared_info))))(((1 << (6)))) -    1)) & ~((typeof((sizeof(struct Model0_skb_shared_info))))(((1 << (6)))) - 1)));
  }
 
  ({ static bool __attribute__ ((__section__(".data.unlikely"))) Model0___warned; int Model0___ret_warn_once = !!(Model0_delta < Model0_len); if (__builtin_expect(!!(Model0___ret_warn_once && !    Model0___warned), 0)) { Model0___warned = true; ({ int Model0___ret_warn_on = !!(1); if (__builtin_expect(!!(Model0___ret_warn_on), 0)) Model0_warn_slowpath_null("net/core/skbuff.c", 4289);       __builtin_expect(!!(Model0___ret_warn_on), 0); }); } __builtin_expect(!!(Model0___ret_warn_once), 0); });
 
  ({ size_t Model0___len = (((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_from)))->Model0_nr_frags * sizeof(Model0_skb_frag_t)); void *Model0___ret; if (__builtin_constant_p(((struct          Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_from)))->Model0_nr_frags * sizeof(Model0_skb_frag_t)) && Model0___len >= 64) Model0___ret = Model0___memcpy((((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_to)))->Model0_frags + ((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_to)))->Model0_nr_frags), (((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_from)))->Model0_frags), Model0___len); else Model0___ret =        __builtin_memcpy((((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_to)))->Model0_frags + ((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_to)))->Model0_nr_frags), (((struct             Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_from)))->Model0_frags), Model0___len); Model0___ret; });
 
 
  ((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_to)))->Model0_nr_frags += ((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_from)))->Model0_nr_frags;
 
  if (!Model0_skb_cloned(Model0_from))
   ((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_from)))->Model0_nr_frags = 0;
 
 
 
 
  for (Model0_i = 0; Model0_i < ((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_from)))->Model0_nr_frags; Model0_i++)
   Model0_skb_frag_ref(Model0_from, Model0_i);

//#else //my abstraction [CY]
//Model0_delta = Model0_from->Model0_truesize/2; //Model0_len;
//#endif 
Model0_to->Model0_truesize += Model0_delta;
  Model0_to->Model0_len += Model0_len;
  Model0_to->Model0_data_len += Model0_len;
 
  *Model0_delta_truesize = Model0_delta;
  return true;
}

int Model0___sk_mem_schedule(struct Model0_sock *Model0_sk, int Model0_size, int Model0_kind)
{
  struct Model0_proto *Model0_prot = Model0_sk->Model0___sk_common.Model0_skc_prot;
  int Model0_amt = Model0_sk_mem_pages(Model0_size);
  long Model0_allocated;
 
  Model0_sk->Model0_sk_forward_alloc += Model0_amt * ((int)((1UL) << 12)); //CY_ABSTRACT1

  Model0_allocated = Model0_sk_memory_allocated_add(Model0_sk, Model0_amt);

  if (0 && Model0_sk->Model0_sk_memcg &&
      !Model0_mem_cgroup_charge_skmem(Model0_sk->Model0_sk_memcg, Model0_amt))
   goto Model0_suppress_allocation;
 
  /* Under limit. */ 
  if (Model0_allocated <= Model0_sk_prot_mem_limits(Model0_sk, 0)) { //flipping
   Model0_sk_leave_memory_pressure(Model0_sk);
   return 1;
  }
 
  /* Under pressure. */ 
  if (Model0_allocated > Model0_sk_prot_mem_limits(Model0_sk, 1)){ //flipping
   Model0_sk_enter_memory_pressure(Model0_sk);
  }
 
  /* Over hard limit. */ 
  if (Model0_allocated > Model0_sk_prot_mem_limits(Model0_sk, 2)){ //flipping??
   goto Model0_suppress_allocation;
  }

  /* guarantee minimum buffer size under pressure */
  if (Model0_kind == 1) { //SK_MEM_RECV
   if (Model0_atomic_read(&Model0_sk->Model0_sk_backlog.Model0_rmem_alloc) < Model0_prot->Model0_sysctl_rmem[0])
    return 1;
 
  } else { // SK_MEM_SEND
#if CY_ABSTRACT1
#else
   if (Model0_sk->Model0_sk_type == Model0_SOCK_STREAM) {
    if (Model0_sk->Model0_sk_wmem_queued < Model0_prot->Model0_sysctl_wmem[0])
     return 1;
   } else if (Model0_atomic_read(&Model0_sk->Model0_sk_wmem_alloc) <
       Model0_prot->Model0_sysctl_wmem[0])
     return 1;
#endif
  }
 
  if (Model0_sk_has_memory_pressure(Model0_sk)) {
   int Model0_alloc;
 
   if (!Model0_sk_under_memory_pressure(Model0_sk))
    return 1;
   Model0_alloc = Model0_sk_sockets_allocated_read_positive(Model0_sk);
   if (Model0_sk_prot_mem_limits(Model0_sk, 2) > Model0_alloc *
       Model0_sk_mem_pages(Model0_sk->Model0_sk_wmem_queued +
      Model0_atomic_read(&Model0_sk->Model0_sk_backlog.Model0_rmem_alloc) +
      Model0_sk->Model0_sk_forward_alloc)){ //change to pages
    return 1;
   }
  }
 
 Model0_suppress_allocation:
  //[CY] We don't have SK_MEM_SEND so far 
#if !CY_ABSTRACT1 //TODO
  if (Model0_kind == 0 && Model0_sk->Model0_sk_type == Model0_SOCK_STREAM) {
   Model0_sk_stream_moderate_sndbuf(Model0_sk);
 
 
 
   if (Model0_sk->Model0_sk_wmem_queued + Model0_size >= Model0_sk->Model0_sk_sndbuf)
    return 1;
  }
#endif

  //[CY] what's the purpose? Seems useless
#if !CY_ABSTRACT1 //TODO
  Model0_trace_sock_exceed_buf_limit(Model0_sk, Model0_prot, Model0_allocated);
#endif

  Model0_sk->Model0_sk_forward_alloc -= Model0_amt * ((int)((1UL) << 12));
 
  Model0_sk_memory_allocated_sub(Model0_sk, Model0_amt);

  if (0 && Model0_sk->Model0_sk_memcg)
   Model0_mem_cgroup_uncharge_skmem(Model0_sk->Model0_sk_memcg, Model0_amt);
 
  return 0;
}

void *Model0___memcpy(void *Model0_to, const void *Model0_from, size_t Model0_len){
#if CY_ABSTRACT3
    memcpy(Model0_to, Model0_from, Model0_len);
#else
    assert(0);
#endif
}

int Model0_skb_copy_bits(const struct Model0_sk_buff *Model0_skb, int Model0_offset, void * Model0_to, int Model0_len){
#if CY_ABSTRACT3
    //we don't care what's the content inside the packet payload
    return 0;
#else
    assert(0);
	return 0;
#endif
}

struct Model0_sk_buff *Model0___alloc_skb(unsigned int Model0_size, Model0_gfp_t Model0_priority,  int Model0_flags,
        int Model0_node){
#if CY_ABSTRACT10
    return NULL;
#else
    assert(0);
    return NULL;
#endif
}

void Model0_kfree_skb_partial(struct Model0_sk_buff *Model0_skb, bool Model0_head_stolen)
{
 if (Model0_head_stolen) {
  Model0_skb_release_head_state(Model0_skb);
  Model0_kmem_cache_free(Model0_skbuff_head_cache, Model0_skb);
 } else {
  Model0___kfree_skb(Model0_skb);
 }
}

unsigned long Model0_get_seconds(void){
    assert(0);
	return 0;
}

bool Model0_tcp_schedule_loss_probe(struct Model0_sock *Model0_sk){
    assert(0);
	return true;
}

int Model0_skb_copy_and_csum_datagram_msg(struct Model0_sk_buff *Model0_skb, int Model0_hlen,
        struct Model0_msghdr *Model0_msg){
    assert(0);
	return 0;
}

 void Model0_tcp_send_delayed_ack(struct Model0_sock *Model0_sk)
 {
  struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
  int Model0_ato = Model0_icsk->Model0_icsk_ack.Model0_ato;
  unsigned long Model0_timeout;
 
  Model0_tcp_ca_event(Model0_sk, Model0_CA_EVENT_DELAYED_ACK);

#if CY_ABSTRACT2
  //Mark delayed ack
  if (Model0_Src_sk == true)
    Model0_delayed_ack = true;
  Model0_tcp_send_ack(Model0_sk);
#else
 
  if (Model0_ato > ((unsigned)(1000/25))) {
   const struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
   int Model0_max_ato = 1000 / 2;
 
   if (Model0_icsk->Model0_icsk_ack.Model0_pingpong ||
       (Model0_icsk->Model0_icsk_ack.Model0_pending & Model0_ICSK_ACK_PUSHED))
    Model0_max_ato = ((unsigned)(1000/5)); //200ms
 
 
 
 
   if (Model0_tp->Model0_srtt_us) {
    int Model0_rtt = ({ int Model0___max1 = (Model0_usecs_to_jiffies(Model0_tp->Model0_srtt_us >> 3)); int Model0___max2   = (((unsigned)(1000/25))); Model0___max1 > Model0___max2 ? Model0___max1: Model0___max2; })
                     ;
 
    if (Model0_rtt < Model0_max_ato)
     Model0_max_ato = Model0_rtt;
   }

 
   Model0_ato = ({ typeof(Model0_ato) Model0__min1 = (Model0_ato); typeof(Model0_max_ato) Model0__min2 = (Model0_max_ato);        (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
  }
 
 
  Model0_timeout = Model0_jiffies + Model0_ato;
 
  if (Model0_icsk->Model0_icsk_ack.Model0_pending & Model0_ICSK_ACK_TIMER) {
 
 
 
   if (Model0_icsk->Model0_icsk_ack.Model0_blocked ||
       (({ unsigned long Model0___dummy; typeof(Model0_jiffies + (Model0_ato >> 2)) Model0___dummy2;         (void)(&Model0___dummy == &Model0___dummy2); 1; }) && ({ unsigned long Model0___dummy; typeof(Model0_icsk->Model0_icsk_ack.Model0_timeout) Model0___dummy2; (void)(&Model0___dummy == &Model0___dummy2); 1; }) &&            ((long)((Model0_jiffies + (Model0_ato >> 2)) - (Model0_icsk->Model0_icsk_ack.Model0_timeout)) >= 0))) {
    Model0_tcp_send_ack(Model0_sk);
    return;
   }
 
   if (!(({ unsigned long Model0___dummy; typeof(Model0_icsk->Model0_icsk_ack.Model0_timeout) Model0___dummy2;      (void)(&Model0___dummy == &Model0___dummy2); 1; }) && ({ unsigned long Model0___dummy;               typeof(Model0_timeout) Model0___dummy2; (void)(&Model0___dummy == &Model0___dummy2); 1; }) &&               ((long)((Model0_timeout) - (Model0_icsk->Model0_icsk_ack.Model0_timeout)) < 0)))
    Model0_timeout = Model0_icsk->Model0_icsk_ack.Model0_timeout;
  }
  Model0_icsk->Model0_icsk_ack.Model0_pending |= Model0_ICSK_ACK_SCHED | Model0_ICSK_ACK_TIMER;
  Model0_icsk->Model0_icsk_ack.Model0_timeout = Model0_timeout;
  Model0_sk_reset_timer(Model0_sk, &Model0_icsk->Model0_icsk_delack_timer, Model0_timeout);
#endif
}

void Model0_sk_forced_mem_schedule(struct Model0_sock *Model0_sk, int Model0_size){
  int Model0_amt;
 
  if (Model0_size <= Model0_sk->Model0_sk_forward_alloc)
   return;
  Model0_amt = Model0_sk_mem_pages(Model0_size);
  Model0_sk->Model0_sk_forward_alloc += Model0_amt * ((int)((1UL) << 12));
  Model0_sk_memory_allocated_add(Model0_sk, Model0_amt);
 
  if (0 && Model0_sk->Model0_sk_memcg)
   Model0_mem_cgroup_charge_skmem(Model0_sk->Model0_sk_memcg, Model0_amt);
}

int Model0_skb_copy_datagram_iter(const struct Model0_sk_buff *Model0_from, int Model0_offset,
       struct Model0_iov_iter *Model0_to, int Model0_size){
    assert(0);
	return 0;
}

void Model0_dst_release(struct Model0_dst_entry *Model0_dst){
#if CY_ABSTRACT1
    // We ignore dst related process
#else
    if (Model0_dst){
        ...
    }
#endif
}

void Model0_sk_send_sigurg(struct Model0_sock *Model0_sk){
#if CY_ABSTRACT1
    //Did nothing, since we ignore those callback
#endif
}

void Model0_kfree(const void *cy){
    assert(0);
}

int Model0___tcp_retransmit_skb(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb, int Model0_segs){
    assert(0);
    return 0;
}

int Model0_tcp_mss_to_mtu(struct Model0_sock *Model0_sk, int Model0_mss){
    assert(0);
    return 0;
}

void Model0_sk_free(struct Model0_sock *Model0_sk){
#if CY_ABSTRACT1
    //TODO:
#else
    assert(0);
#endif
}

unsigned int Model0_tcp_sync_mss(struct Model0_sock *Model0_sk, Model0_u32 Model0_pmtu){
#if CY_ABSTRACT3
    return 65535;
#endif
}

void Model0_tcp_update_metrics(struct Model0_sock *Model0_sk){
    assert(0);
}

void Model0_tcp_skb_collapse_tstamp(struct Model0_sk_buff *Model0_skb, const struct Model0_sk_buff *Model0_next_skb){
    assert(0);
}

void Model0___skb_tstamp_tx(struct Model0_sk_buff *Model0_orig_skb,
        struct Model0_skb_shared_hwtstamps *Model0_hwtstamps,
        struct Model0_sock *Model0_sk, int Model0_tstype){
    assert(0);
}

void Model0_tcp_init_congestion_control(struct Model0_sock *Model0_sk){
#if CY_ABSTRACT1
    //We don't consider congestion_control so far, since we don't have send process
    //TODO: or we can add the codes any way
#endif
}

void Model0___compiletime_assert_249(void){}
void Model0___compiletime_assert_1297(void){}
void Model0___compiletime_assert_1620(void){}
void Model0___compiletime_assert_2254(void){}
void Model0___compiletime_assert_4065(void){}
void Model0___compiletime_assert_4066(void){}
void Model0___compiletime_assert_4067(void){}
void Model0___compiletime_assert_4068(void){}
void Model0___compiletime_assert_4069(void){}
void Model0___compiletime_assert_4070(void){}
void Model0___compiletime_assert_4071(void){}
void Model0___compiletime_assert_4072(void){}
void Model0___compiletime_assert_4073(void){}
void Model0___compiletime_assert_4074(void){}
void Model0___compiletime_assert_4075(void){}
void Model0___compiletime_assert_4076(void){}
void Model0___compiletime_assert_4077(void){}
void Model0___compiletime_assert_4078(void){}
void Model0___compiletime_assert_4079(void){}
void Model0___compiletime_assert_4080(void){}


Model0_u32 Model0_prandom_u32(void){
#if CY_ABSTRACT3
    //TODO: should we return a fixed value, so the program is deterministic?
    ////currently is only called by req->txhash = net_tx_rndhash(), which doesn't matter
    Model0_u32 x = 1;//rand();
    return x;
#else
    return rand();
#endif
}

int Model0_tcp_rack_mark_lost(struct Model0_sock *Model0_sk){
    assert(0);
	return 0;
}

/* Returns true if we should perform Fast Open on the SYN. The cookie (foc)
 * may be updated and return the client in the SYN-ACK later. E.g., Fast Open
 * cookie request (foc->len == 0).
 */
//copied from net/ipv4/tcp_fastopen.c
struct Model0_sock *Model0_tcp_try_fastopen(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb,
         struct Model0_request_sock *Model0_req,
         struct Model0_tcp_fastopen_cookie *Model0_foc,
         struct Model0_dst_entry *Model0_dst)
{
 struct Model0_tcp_fastopen_cookie Model0_valid_foc = { .Model0_len = -1 };
 bool Model0_syn_data = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq != ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq + 1;
 struct Model0_sock *Model0_child;

 if (Model0_foc->Model0_len == 0) /* Client requests a cookie */
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPFASTOPENCOOKIEREQD] += 1);

 if (!((Model0_sysctl_tcp_fastopen & 2) &&
       (Model0_syn_data || Model0_foc->Model0_len >= 0) &&
       Model0_tcp_fastopen_queue_check(Model0_sk))) {
  Model0_foc->Model0_len = -1;
  return ((void *)0);
 }

 if (Model0_syn_data && (Model0_sysctl_tcp_fastopen & 0x200))
  goto Model0_fastopen;

 if (Model0_foc->Model0_len >= 0 && /* Client presents or requests a cookie */
     Model0_tcp_fastopen_cookie_gen(Model0_req, Model0_skb, &Model0_valid_foc) &&
     Model0_foc->Model0_len == 8 &&
     Model0_foc->Model0_len == Model0_valid_foc.Model0_len &&
     !Model0_memcmp(Model0_foc->Model0_val, Model0_valid_foc.Model0_val, Model0_foc->Model0_len)) {
  /* Cookie is valid. Create a (full) child socket to accept
		 * the data in SYN before returning a SYN-ACK to ack the
		 * data. If we fail to create the socket, fall back and
		 * ack the ISN only but includes the same cookie.
		 *
		 * Note: Data-less SYN with valid cookie is allowed to send
		 * data in SYN_RECV state.
		 */
Model0_fastopen:
  Model0_child = Model0_tcp_fastopen_create_child(Model0_sk, Model0_skb, Model0_dst, Model0_req);
  if (Model0_child) {
   Model0_foc->Model0_len = -1;
   (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPFASTOPENPASSIVE] += 1);

   return Model0_child;
  }
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPFASTOPENPASSIVEFAIL] += 1);
 } else if (Model0_foc->Model0_len > 0) /* Client presents an invalid cookie */
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPFASTOPENPASSIVEFAIL] += 1);

 Model0_valid_foc.Model0_exp = Model0_foc->Model0_exp;
 *Model0_foc = Model0_valid_foc;
 return ((void *)0);
}

/* Warning : This function is called without sk_listener being locked.
 * Be sure to read socket fields once, as their value could change under us.
 */
//copied from net/ipv4/tcp_minisocks.c
//TODO: check if we need to further abstract codes, such as Model0_dst_metric_advmss
void Model0_tcp_openreq_init_rwin(struct Model0_request_sock *Model0_req,
      const struct Model0_sock *Model0_sk_listener,
      const struct Model0_dst_entry *Model0_dst)
{
 struct Model0_inet_request_sock *Model0_ireq = Model0_inet_rsk(Model0_req);
 const struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk_listener);
#if CY_ABSTRACT3
    Model0_req->Model0___req_common.Model0_skc_rcv_wnd = 65535;
    Model0_req->Model0___req_common.Model0_skc_window_clamp = 65535;
    Model0_ireq->Model0_rcv_wscale = 65535;

#else
 Model0_u16 Model0_user_mss = ({ union { typeof(Model0_tp->Model0_rx_opt.Model0_user_mss) Model0___val; char Model0___c[1]; } Model0___u; if (1) Model0___read_once_size(&(Model0_tp->Model0_rx_opt.Model0_user_mss), Model0___u.Model0___c, sizeof(Model0_tp->Model0_rx_opt.Model0_user_mss)); else Model0___read_once_size_nocheck(&(Model0_tp->Model0_rx_opt.Model0_user_mss), Model0___u.Model0___c, sizeof(Model0_tp->Model0_rx_opt.Model0_user_mss)); Model0___u.Model0___val; });
 int Model0_full_space = Model0_tcp_full_space(Model0_sk_listener);
 int Model0_mss = Model0_dst_metric_advmss(Model0_dst);
 Model0_u32 Model0_window_clamp;
 __u8 Model0_rcv_wscale;

 if (Model0_user_mss && Model0_user_mss < Model0_mss)
  Model0_mss = Model0_user_mss;

 Model0_window_clamp = ({ union { typeof(Model0_tp->Model0_window_clamp) Model0___val; char Model0___c[1]; } Model0___u; if (1) Model0___read_once_size(&(Model0_tp->Model0_window_clamp), Model0___u.Model0___c, sizeof(Model0_tp->Model0_window_clamp)); else Model0___read_once_size_nocheck(&(Model0_tp->Model0_window_clamp), Model0___u.Model0___c, sizeof(Model0_tp->Model0_window_clamp)); Model0___u.Model0___val; });
 /* Set this up on the first call only */
 Model0_req->Model0___req_common.Model0_skc_window_clamp = Model0_window_clamp ? : Model0_dst_metric(Model0_dst, Model0_RTAX_WINDOW);

 /* limit the window selection if the user enforce a smaller rx buffer */
 if (Model0_sk_listener->Model0_sk_userlocks & 2 &&
     (Model0_req->Model0___req_common.Model0_skc_window_clamp > Model0_full_space || Model0_req->Model0___req_common.Model0_skc_window_clamp == 0))
  Model0_req->Model0___req_common.Model0_skc_window_clamp = Model0_full_space;

 /* tcp_full_space because it is guaranteed to be the first packet */
 Model0_tcp_select_initial_window(Model0_full_space,
  Model0_mss - (Model0_ireq->Model0_tstamp_ok ? 12 : 0),
  &Model0_req->Model0___req_common.Model0_skc_rcv_wnd,
  &Model0_req->Model0___req_common.Model0_skc_window_clamp,
  Model0_ireq->Model0_wscale_ok,
  &Model0_rcv_wscale,
  Model0_dst_metric(Model0_dst, Model0_RTAX_INITRWND));
 Model0_ireq->Model0_rcv_wscale = Model0_rcv_wscale;
#endif
}

int Model0_skb_shift(struct Model0_sk_buff *Model0_tgt, struct Model0_sk_buff *Model0_skb, int             Model0_shiftlen){
    assert(0);
	return 0;
}

void Model0_reqsk_fastopen_remove(struct Model0_sock *Model0_sk, struct Model0_request_sock *Model0_req,
       bool Model0_reset){
    assert(0);
}

void Model0_consume_skb(struct Model0_sk_buff *Model0_skb){
#if CY_ABSTRACT1
#else
    assert(0);
#endif
}

Model0___sum16 Model0___skb_checksum_complete_head(struct Model0_sk_buff *Model0_skb, int Model0_len){
    assert(0);
	return 0;
}

Model0___sum16 Model0___skb_checksum_complete(struct Model0_sk_buff *Model0_skb){
    assert(0);
    return 0;
}

void Model0_tcp_init_metrics(struct Model0_sock *Model0_sk){
#if CY_ABSTRACT1
    //ignore metrics initialization on socket, related to dst
#endif
}

void Model0_kmem_cache_free(struct Model0_kmem_cache *cy0, void *cy1){
#if CY_ABSTRACT3
    //do nothing, since we don't really realse any memory
#endif
}

//copied form net/ipv4/inet_connection_sock.i
static void Model0_reqsk_queue_hash_req(struct Model0_request_sock *Model0_req,
     unsigned long Model0_timeout)
{
#if !CY_ABSTRACT3 //TODO: may need to change it
 Model0_req->Model0_num_retrans = 0;
 Model0_req->Model0_num_timeout = 0;
 Model0_req->Model0_sk = ((void *)0);

 do { Model0_init_timer_key((((&Model0_req->Model0_rsk_timer))), ((0x00100000)), ((void *)0), ((void *)0)); ((&Model0_req->Model0_rsk_timer))->Model0_function = ((Model0_reqsk_timer_handler)); ((&Model0_req->Model0_rsk_timer))->Model0_data = (((unsigned long)Model0_req)); } while (0);

 Model0_mod_timer(&Model0_req->Model0_rsk_timer, Model0_jiffies + Model0_timeout);

#if CY_ABSTRACT3
#else
 Model0_inet_ehash_insert(Model0_req_to_sk(Model0_req), ((void *)0));
#endif
 /* before letting lookups find us, make sure all req fields
	 * are committed to memory and refcnt initialized.
	 */
 __asm__ __volatile__("": : :"memory");
 Model0_atomic_set(&Model0_req->Model0___req_common.Model0_skc_refcnt, 2 + 1);
#endif
}
//copied from net/ipv4/inet_connection_sock.i
void Model0_inet_csk_reqsk_queue_hash_add(struct Model0_sock *Model0_sk, struct Model0_request_sock *Model0_req,
       unsigned long Model0_timeout)
{
 Model0_reqsk_queue_hash_req(Model0_req, Model0_timeout);
 Model0_inet_csk_reqsk_queue_added(Model0_sk);
}

void Model0_tcp_enter_memory_pressure(struct Model0_sock *Model0_sk)
{
 if (!Model0_tcp_memory_pressure) {
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPMEMORYPRESSURES] += 1);
  Model0_tcp_memory_pressure = 1;
 }
}

void Model0_tcp_cwnd_restart(struct Model0_sock *Model0_sk, Model0_s32 Model0_delta){
    assert(0);
}

void Model0_tcp_rack_advance(struct Model0_tcp_sock *Model0_tp,
         const struct Model0_skb_mstamp *Model0_xmit_time, Model0_u8 Model0_sacked){
    assert(0);
}

void Model0_inet_csk_reset_keepalive_timer(struct Model0_sock *Model0_sk, unsigned long Model0_timeout){
    assert(0);
}

bool Model0_tcp_peer_is_proven(struct Model0_request_sock *Model0_req, struct Model0_dst_entry *           Model0_dst,
    bool Model0_paws_check, bool Model0_timestamps){
#if CY_ABSTRACT3
    // this function checks socket connection's timestamp to validate the incoing packet. We assume it's always true
	return true;
#else
    assert(0);
    return true;
#endif
}

int Model0_tcp_trim_head(struct Model0_sock *cy0, struct Model0_sk_buff *cy1, Model0_u32 cy2){
    assert(0);
	return 0;
}

void *Model0_kmem_cache_alloc(struct Model0_kmem_cache *cy0, Model0_gfp_t Model0_flags){
    //we are not really allocate new memories, since model checker cannot track this new memory anymore. Instea, we map allocated memory to pre-allocated memory, based on the second parameter.
    assert(0);
}

#if CY_ABSTRACT3
extern struct Model0_tcp_request_sock Model0_Req;
extern struct Model0_tcp_request_sock Model0_Req_A;

void *Model0_cy_kmem_cache_alloc(int Model0_memory_type){
    //we are not really allocate new memories, since model checker cannot track this new memory anymore. Instea, we map allocated memory to pre-allocated memory, based on the second parameter.
    switch(Model0_memory_type){
        case 0: return (void *)(&Model0_Skb_Out);
        case 1: return (void *)(&Model0_Req_A);//not spoofed
        case 2: return (void *)(&Model0_Req);//spoofed
        case 3: return (void *)(&Model0_Server_A);//not spoofed
        case 4: return (void *)(&Model0_Server);//spoofed
    }
}
#endif

struct Model0_sock *Model0_inet_csk_reqsk_queue_add(struct Model0_sock *Model0_sk,
          struct Model0_request_sock *Model0_req,
          struct Model0_sock *Model0_child)
{
 struct Model0_request_sock_queue *Model0_queue = &Model0_inet_csk(Model0_sk)->Model0_icsk_accept_queue;

 Model0_spin_lock(&Model0_queue->Model0_rskq_lock);
 if (__builtin_expect(!!(Model0_sk->Model0___sk_common.Model0_skc_state != Model0_TCP_LISTEN), 0)) {
  Model0_inet_child_forget(Model0_sk, Model0_req, Model0_child);
  Model0_child = ((void *)0);
 } else {
  Model0_req->Model0_sk = Model0_child;
  Model0_req->Model0_dl_next = ((void *)0);
  if (Model0_queue->Model0_rskq_accept_head == ((void *)0))
   Model0_queue->Model0_rskq_accept_head = Model0_req;
  else
   Model0_queue->Model0_rskq_accept_tail->Model0_dl_next = Model0_req;
  Model0_queue->Model0_rskq_accept_tail = Model0_req;
  Model0_sk_acceptq_added(Model0_sk);
 }
 Model0_spin_unlock(&Model0_queue->Model0_rskq_lock);
 return Model0_child;
}

int Model0_inet_rtx_syn_ack(const struct Model0_sock *Model0_parent, struct Model0_request_sock *Model0_req)
{
#if CY_ABSTRACT7
 int err = Model0_tcp_rtx_synack(Model0_parent, Model0_req);
#else
 int err = Model0_req->Model0_rsk_ops->Model0_rtx_syn_ack(Model0_parent, Model0_req);
#endif

 if (!err)
  Model0_req->Model0_num_retrans++;
 return err;
}

struct Model0_sock *Model0_inet_csk_complete_hashdance(struct Model0_sock *Model0_sk, struct Model0_sock *Model0_child,
      struct Model0_request_sock *Model0_req, bool Model0_own_req)
{
 if (Model0_own_req) {
  Model0_inet_csk_reqsk_queue_drop(Model0_sk, Model0_req);
  Model0_reqsk_queue_removed(&Model0_inet_csk(Model0_sk)->Model0_icsk_accept_queue, Model0_req);
  if (Model0_inet_csk_reqsk_queue_add(Model0_sk, Model0_req, Model0_child))
   return Model0_child;
 }
 /* Too bad, another child took ownership of the request, undo. */
 Model0_spin_unlock(&((Model0_child)->Model0_sk_lock.Model0_slock));
 Model0_sock_put(Model0_child);
 return ((void *)0);
}

int Model0_mod_timer_pending(struct Model0_timer_list *Model0_timer, unsigned long Model0_expires);

static bool Model0_tcp_in_window(Model0_u32 Model0_seq, Model0_u32 Model0_end_seq, Model0_u32 Model0_s_win, Model0_u32 Model0_e_win)
{
 if (Model0_seq == Model0_s_win)
  return true;
 if (Model0_before(Model0_s_win, Model0_end_seq) && Model0_before(Model0_seq, Model0_e_win))
  return true;
 return Model0_seq == Model0_e_win && Model0_seq == Model0_end_seq;
}

/*
 * Process an incoming packet for SYN_RECV sockets represented as a
 * request_sock. Normally sk is the listener socket but for TFO it
 * points to the child socket.
 *
 * XXX (TFO) - The current impl contains a special check for ack
 * validation and inside tcp_v4_reqsk_send_ack(). Can we do better?
 *
 * We don't need to initialize tmp_opt.sack_ok as we don't use the results
 */

struct Model0_sock *Model0_tcp_check_req(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb,
      struct Model0_request_sock *Model0_req,
      bool Model0_fastopen)
{
 struct Model0_tcp_options_received Model0_tmp_opt;
 struct Model0_sock *Model0_child;
 const struct Model0_tcphdr *Model0_th = Model0_tcp_hdr(Model0_skb);
 Model0___be32 Model0_flg = ( ((union Model0_tcp_word_hdr *)(Model0_th))->Model0_words [3]) & (Model0_TCP_FLAG_RST|Model0_TCP_FLAG_SYN|Model0_TCP_FLAG_ACK);
 bool Model0_paws_reject = false;
 bool Model0_own_req;

 Model0_tmp_opt.Model0_saw_tstamp = 0;
 if (Model0_th->Model0_doff > (sizeof(struct Model0_tcphdr)>>2)) {
  Model0_tcp_parse_options(Model0_skb, &Model0_tmp_opt, 0, ((void *)0));

  if (Model0_tmp_opt.Model0_saw_tstamp) {
   Model0_tmp_opt.Model0_ts_recent = Model0_req->Model0_ts_recent;
   /* We do not store true stamp, but it is not required,
			 * it can be estimated (approximately)
			 * from another data.
			 */
   Model0_tmp_opt.Model0_ts_recent_stamp = Model0_get_seconds() - ((((unsigned)(1*1000))/1000)<<Model0_req->Model0_num_timeout);
   Model0_paws_reject = Model0_tcp_paws_reject(&Model0_tmp_opt, Model0_th->Model0_rst);
  }
 }

 /* Check for pure retransmitted SYN. */
 if (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq == Model0_tcp_rsk(Model0_req)->Model0_rcv_isn &&
     Model0_flg == Model0_TCP_FLAG_SYN &&
     !Model0_paws_reject) {
  /*
		 * RFC793 draws (Incorrectly! It was fixed in RFC1122)
		 * this case on figure 6 and figure 8, but formal
		 * protocol description says NOTHING.
		 * To be more exact, it says that we should send ACK,
		 * because this segment (at least, if it has no data)
		 * is out of window.
		 *
		 *  CONCLUSION: RFC793 (even with RFC1122) DOES NOT
		 *  describe SYN-RECV state. All the description
		 *  is wrong, we cannot believe to it and should
		 *  rely only on common sense and implementation
		 *  experience.
		 *
		 * Enforce "SYN-ACK" according to figure 8, figure 6
		 * of RFC793, fixed by RFC1122.
		 *
		 * Note that even if there is new data in the SYN packet
		 * they will be thrown away too.
		 *
		 * Reset timer after retransmitting SYNACK, similar to
		 * the idea of fast retransmit in recovery.
		 */
  if (!Model0_tcp_oow_rate_limited(Model0_sock_net(Model0_sk), Model0_skb,
       Model0_LINUX_MIB_TCPACKSKIPPEDSYNRECV,
       &Model0_tcp_rsk(Model0_req)->Model0_last_oow_ack_time) &&

      !Model0_inet_rtx_syn_ack(Model0_sk, Model0_req)) {
   unsigned long Model0_expires = Model0_jiffies;

   Model0_expires += ({ typeof(((unsigned)(1*1000)) << Model0_req->Model0_num_timeout) Model0__min1 = (((unsigned)(1*1000)) << Model0_req->Model0_num_timeout); typeof(((unsigned)(120*1000))) Model0__min2 = (((unsigned)(120*1000))); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });

   if (!Model0_fastopen)
    Model0_mod_timer_pending(&Model0_req->Model0_rsk_timer, Model0_expires);
   else
    Model0_req->Model0_rsk_timer.Model0_expires = Model0_expires;
  }
  return ((void *)0);
 }

 /* Further reproduces section "SEGMENT ARRIVES"
	   for state SYN-RECEIVED of RFC793.
	   It is broken, however, it does not work only
	   when SYNs are crossed.

	   You would think that SYN crossing is impossible here, since
	   we should have a SYN_SENT socket (from connect()) on our end,
	   but this is not true if the crossed SYNs were sent to both
	   ends by a malicious third party.  We must defend against this,
	   and to do that we first verify the ACK (as per RFC793, page
	   36) and reset if it is invalid.  Is this a true full defense?
	   To convince ourselves, let us consider a way in which the ACK
	   test can still pass in this 'malicious crossed SYNs' case.
	   Malicious sender sends identical SYNs (and thus identical sequence
	   numbers) to both A and B:

		A: gets SYN, seq=7
		B: gets SYN, seq=7

	   By our good fortune, both A and B select the same initial
	   send sequence number of seven :-)

		A: sends SYN|ACK, seq=7, ack_seq=8
		B: sends SYN|ACK, seq=7, ack_seq=8

	   So we are now A eating this SYN|ACK, ACK test passes.  So
	   does sequence test, SYN is truncated, and thus we consider
	   it a bare ACK.

	   If icsk->icsk_accept_queue.rskq_defer_accept, we silently drop this
	   bare ACK.  Otherwise, we create an established connection.  Both
	   ends (listening sockets) accept the new incoming connection and try
	   to talk to each other. 8-)

	   Note: This case is both harmless, and rare.  Possibility is about the
	   same as us discovering intelligent life on another plant tomorrow.

	   But generally, we should (RFC lies!) to accept ACK
	   from SYNACK both here and in tcp_rcv_state_process().
	   tcp_rcv_state_process() does not, hence, we do not too.

	   Note that the case is absolutely generic:
	   we cannot optimize anything here without
	   violating protocol. All the checks must be made
	   before attempt to create socket.
	 */

 /* RFC793 page 36: "If the connection is in any non-synchronized state ...
	 *                  and the incoming segment acknowledges something not yet
	 *                  sent (the segment carries an unacceptable ACK) ...
	 *                  a reset is sent."
	 *
	 * Invalid ACK: reset will be sent by listening socket.
	 * Note that the ACK validity check for a Fast Open socket is done
	 * elsewhere and is checked directly against the child socket rather
	 * than req because user data may have been sent out.
	 */
 if ((Model0_flg & Model0_TCP_FLAG_ACK) && !Model0_fastopen &&
     (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_ack_seq !=
      Model0_tcp_rsk(Model0_req)->Model0_snt_isn + 1))
  return Model0_sk;
 /* Also, it would be not so bad idea to check rcv_tsecr, which
	 * is essentially ACK extension and too early or too late values
	 * should cause reset in unsynchronized states.
	 */

 /* RFC793: "first check sequence number". */
 if (Model0_paws_reject || !Model0_tcp_in_window(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq,
       Model0_tcp_rsk(Model0_req)->Model0_rcv_nxt, Model0_tcp_rsk(Model0_req)->Model0_rcv_nxt + Model0_req->Model0___req_common.Model0_skc_rcv_wnd)) {
  /* Out of window: send ACK and drop. */
  if (!(Model0_flg & Model0_TCP_FLAG_RST) &&
      !Model0_tcp_oow_rate_limited(Model0_sock_net(Model0_sk), Model0_skb,
       Model0_LINUX_MIB_TCPACKSKIPPEDSYNRECV,
       &Model0_tcp_rsk(Model0_req)->Model0_last_oow_ack_time))
#if CY_ABSTRACT7
   Model0_tcp_v4_reqsk_send_ack(Model0_sk, Model0_skb, Model0_req);
#else
   Model0_req->Model0_rsk_ops->Model0_send_ack(Model0_sk, Model0_skb, Model0_req);
#endif
  if (Model0_paws_reject)
   (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_PAWSESTABREJECTED] += 1);
  return ((void *)0);
 }

 /* In sequence, PAWS is OK. */

 if (Model0_tmp_opt.Model0_saw_tstamp && !Model0_before(Model0_tcp_rsk(Model0_req)->Model0_rcv_nxt, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq))
  Model0_req->Model0_ts_recent = Model0_tmp_opt.Model0_rcv_tsval;

 if (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq == Model0_tcp_rsk(Model0_req)->Model0_rcv_isn) {
  /* Truncate SYN, it is out of window starting
		   at tcp_rsk(req)->rcv_isn + 1. */
  Model0_flg &= ~Model0_TCP_FLAG_SYN;
 }

 /* RFC793: "second check the RST bit" and
	 *	   "fourth, check the SYN bit"
	 */
 if (Model0_flg & (Model0_TCP_FLAG_RST|Model0_TCP_FLAG_SYN)) {
  (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_ATTEMPTFAILS] += 1);
  goto Model0_embryonic_reset;
 }

 /* ACK sequence verified above, just make sure ACK is
	 * set.  If ACK not set, just silently drop the packet.
	 *
	 * XXX (TFO) - if we ever allow "data after SYN", the
	 * following check needs to be removed.
	 */
 if (!(Model0_flg & Model0_TCP_FLAG_ACK))
  return ((void *)0);

 /* For Fast Open no more processing is needed (sk is the
	 * child socket).
	 */
 if (Model0_fastopen)
  return Model0_sk;

 /* While TCP_DEFER_ACCEPT is active, drop bare ACK. */
 if (Model0_req->Model0_num_timeout < Model0_inet_csk(Model0_sk)->Model0_icsk_accept_queue.Model0_rskq_defer_accept &&
     ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq == Model0_tcp_rsk(Model0_req)->Model0_rcv_isn + 1) {
  Model0_inet_rsk(Model0_req)->Model0_acked = 1;
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPDEFERACCEPTDROP] += 1);
  return ((void *)0);
 }

 /* OK, ACK is valid, create big socket and
	 * feed this segment to it. It will repeat all
	 * the tests. THIS SEGMENT MUST MOVE SOCKET TO
	 * ESTABLISHED STATE. If it will be dropped after
	 * socket is created, wait for troubles.
	 */
#if CY_ABSTRACT7
 Model0_child = Model0_tcp_v4_syn_recv_sock(Model0_sk, Model0_skb, Model0_req, ((void *)0),
#else
 Model0_child = Model0_inet_csk(Model0_sk)->Model0_icsk_af_ops->Model0_syn_recv_sock(Model0_sk, Model0_skb, Model0_req, ((void *)0),
#endif
        Model0_req, &Model0_own_req);
 if (!Model0_child)
  goto Model0_listen_overflow;

 Model0_sock_rps_save_rxhash(Model0_child, Model0_skb);
 Model0_tcp_synack_rtt_meas(Model0_child, Model0_req);
 return Model0_inet_csk_complete_hashdance(Model0_sk, Model0_child, Model0_req, Model0_own_req);

Model0_listen_overflow:
 if (!Model0_sysctl_tcp_abort_on_overflow) {
  Model0_inet_rsk(Model0_req)->Model0_acked = 1;
  return ((void *)0);
 }

Model0_embryonic_reset:
 if (!(Model0_flg & Model0_TCP_FLAG_RST)) {
  /* Received a bad SYN pkt - for TFO We try not to reset
		 * the local connection unless it's really necessary to
		 * avoid becoming vulnerable to outside attack aiming at
		 * resetting legit local connections.
		 */
#if CY_ABSTRACT7
  Model0_tcp_v4_send_reset(Model0_sk, Model0_skb);
#else
  Model0_req->Model0_rsk_ops->Model0_send_reset(Model0_sk, Model0_skb);
#endif
 } else if (Model0_fastopen) { /* received a valid RST pkt */
  Model0_reqsk_fastopen_remove(Model0_sk, Model0_req, true);
  Model0_tcp_reset(Model0_sk);
 }
 if (!Model0_fastopen) {
  Model0_inet_csk_reqsk_queue_drop(Model0_sk, Model0_req);
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_EMBRYONICRSTS] += 1);
 }
 return ((void *)0);
}

void Model0___tcp_push_pending_frames(struct Model0_sock *Model0_sk, unsigned int Model0_cur_mss,
           int Model0_nonagle){
    assert(0);
}

void Model0_tcp_mtup_init(struct Model0_sock *Model0_sk){
#if CY_ABSTRACT1
    //TODO: we dont include MTU Probe in our codes neither, since we don't actively send data
#endif
}

bool Model0_tcp_may_send_now(struct Model0_sock *Model0_sk){
    assert(0);
	return true;
}

void Model0_tcp_fastopen_cache_set(struct Model0_sock *Model0_sk, Model0_u16 Model0_mss,
        struct Model0_tcp_fastopen_cookie *Model0_cookie, bool Model0_syn_lost,
        Model0_u16 Model0_try_exp){
    assert(0);
}

void Model0_tcp_fastopen_add_skb(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb){
    assert(0);
}

int Model0_tcp_send_synack(struct Model0_sock *cy){
    assert(0);
	return 0;
}

void *Model0___kmalloc(size_t Model0_size, Model0_gfp_t Model0_flags){
    assert(0);
}

//TODO: may need to rewrite it, using Model0_cy_kmem_cache_alloc
void Model0_cy_alloc_skb(struct Model0_sk_buff *Model0_skb, char *Model0_data, int Model0_size){
 
#if CY_ABSTRACT4
     memset(Model0_skb, 0, ((size_t)&((struct Model0_sk_buff*)0)->Model0_tail));
#else
     memset(Model0_skb, 0, offsetof(struct Model0_sk_buff, Model0_tail));
#endif
     Model0_skb->Model0_truesize = Model0_size+sizeof(struct Model0_sk_buff)+sizeof(struct Model0_skb_shared_info);
     Model0_skb->Model0_head = Model0_data;
     Model0_skb->Model0_data = Model0_data;
     Model0_skb_reset_tail_pointer(Model0_skb); // skb->tail = skb->data - skb->head;
     Model0_skb->Model0_end = Model0_skb->Model0_tail + Model0_size;
     //Model0_skb->Model0_mac_header = (typeof(Model0_skb->Model0_mac_header))~0U;
     Model0_skb->Model0_transport_header = (typeof(Model0_skb->Model0_transport_header))~0U;
 
     /* make sure we initialize shinfo sequentially */
     struct Model0_skb_shared_info *Model0_shinfo;
     Model0_shinfo = ((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_skb)));
     memset(Model0_shinfo, 0, ((size_t)&((struct Model0_skb_shared_info*)0)->Model0_dataref));
     Model0_atomic_set(&Model0_shinfo->Model0_dataref, 1);
 
 
 #if CY_ABSTRACT1
     //when __alloc_skb is called by alloc_skb, flags is always 0
 #else
     if (Model0_flags & 0x01){ //SKB_ALLOC_FCLONE;
         ///...
     }
 #endif
}

__u32 Model0_tcp_acceptable_seq(const struct Model0_sock *Model0_sk)
{
    const struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);


    if (!Model0_before(Model0_tcp_wnd_end(Model0_tp), Model0_tp->Model0_snd_nxt))
        return Model0_tp->Model0_snd_nxt;
    else
        return Model0_tcp_wnd_end(Model0_tp);
}

void Model0_tcp_init_nondata_skb(struct Model0_sk_buff *Model0_skb, Model0_u32 Model0_seq, Model0_u8  Model0_flags)
{
  Model0_skb->Model0_ip_summed = 3;
  Model0_skb->Model0_csum = 0;
 
  ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_tcp_flags = Model0_flags;
  ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked = 0;
 
  Model0_tcp_skb_pcount_set(Model0_skb, 1);
 
  ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq = Model0_seq;
  if (Model0_flags & (0x02 | 0x01))
   Model0_seq++;
  ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq = Model0_seq;
}

int Model0_cy_tcp_transmit_skb(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb, int Model0_clone_it,
         Model0_gfp_t Model0_gfp_mask)
{
   const struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
   struct Model0_inet_sock *Model0_inet;
   struct Model0_tcp_sock *Model0_tp;
   struct Model0_tcp_skb_cb *Model0_tcb;
   //struct tcp_out_options opts;
   unsigned int Model0_tcp_options_size, Model0_tcp_header_size;
   //struct tcp_md5sig_key *md5;
   struct Model0_tcphdr *Model0_th;
   int err;
 
 //  do { if (!skb || !tcp_skb_pcount(skb)) do { asm volatile("1:\tud2\n" ".pushsection                     __bug_table,\"a\"\n" "2:\t.long 1b - 2b, %c0 - 2b\n" "\t.word %c1, 0\n" "\t.org 2b+%c2\n" ".               popsection" : : "i"      ("net/ipv4/tcp_output.c"), "i" (914), "i" (sizeof(struct bug_entry)));            __builtin_unreachable(); } while (0); }       while (0);
   Model0_tcp_skb_pcount(Model0_skb);
   Model0_tp = Model0_tcp_sk(Model0_sk);
 
 //current cline_it == 0
 
   Model0_inet = Model0_inet_sk(Model0_sk);
   Model0_tcb = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]));
 #if CY_ABSTRACT1 //We assume tcp_option is empty
   Model0_tcp_options_size = 0; //tcp_established_options would lead to a empty options anyway
 #else
   // Compute TCP options for SYN packets or other packets. //CYTODO
   if (Model0_tcb->Model0_tcp_flags & 0x02) // TCPHDR_SYN:0x02
    Model0_tcp_options_size = Model0_tcp_syn_options(Model0_sk, Model0_skb, &Model0_opts, &Modle0_md5);
   else
    Model0_tcp_options_size = Model0_tcp_established_options(Model0_sk, Model0_skb, &Model0_opts, &Model0_md5);
 #endif
   //cy: turn off options first
   Model0_tcp_header_size = Model0_tcp_options_size + sizeof(struct Model0_tcphdr);
 // # 948 "net/ipv4/tcp_output.c"
 
     //cy: ooo_okay: allow the mapping of a socket to a queue to be changed. 
   Model0_skb->Model0_ooo_okay = Model0_sk_wmem_alloc_get(Model0_sk) < ((1) + ((((sizeof(struct             Model0_sk_buff))) + ((typeof((sizeof(struct Model0_sk_buff))))(((1 << (6)))) - 1)) &                       ~((typeof((sizeof(struct Model0_sk_buff))))(((1 << (6)))) - 1)) + ((((sizeof(struct                        Model0_skb_shared_info))) + ((typeof((sizeof(struct Model0_skb_shared_info))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model0_skb_shared_info))))(((1 << (6)))) - 1)));
 
   Model0_skb_push(Model0_skb, Model0_tcp_header_size);
   Model0_skb_reset_transport_header(Model0_skb);
 
 #if !CY_ABSTRACT4
   Model0_skb_orphan(skb);// orphan a buffer -> Make the skb unowned. We have done this in the receiving    process. 
 #endif
   Model0_skb->Model0_sk = Model0_sk;
   //cy: I'm not going to desctruct skb, so it's okay.
   //skb->destructor = skb_is_tcp_pure_ack(skb) ? __sock_wfree : tcp_wfree;
   Model0_skb_set_hash_from_sk(Model0_skb, Model0_sk); // if sk has sk_txhash, transfer it to skb
   Model0_atomic_add(Model0_skb->Model0_truesize, &Model0_sk->Model0_sk_wmem_alloc); //the bytes that have  already been written

   /* Build TCP header and checksum it. */
   Model0_th = (struct Model0_tcphdr *)Model0_skb->Model0_data;
   Model0_th->Model0_source = Model0_inet->Model0_inet_sport;
   Model0_th->Model0_dest = Model0_inet->Model0_sk.Model0___sk_common.Model0_skc_dport;
   // cy: remove htonl function right now.
   Model0_th->Model0_seq = Model0_htonl(Model0_tcb->Model0_seq); //((                                       __be32)(__u32)__builtin_bswap32((__u32)((tcb->seq))));
   Model0_th->Model0_ack_seq = Model0_htonl(Model0_tp->Model0_rcv_nxt); //((                                __be32)(__u32)__builtin_bswap32((__u32)((tp->rcv_nxt))));
   // cy: not sure is it necessary..... 
 
   *(((Model0___be16 *)Model0_th) + 6) = Model0_htons(((Model0_tcp_header_size >> 2) << 12) | Model0_tcb->Model0_tcp_flags);
   /*
    * formate: __little_endian_bitfield:
    * res1: 4bits
    * doff: 4bits
    * fin: 1
    * syn: 1
    * rst: 1
    * psh: 1
    * ack: 1
    * urg: 1
    * ece: 1
    * cwr: 1
    *
    * */
   //*(((__be16 *)th) + 6) = (( __be16)(__u16)__builtin_bswap16((__u16)((((tcp_header_size >> 2) << 12) |   tcb->tcp_flags))));
 #if CY_ABSTRACT4
   Model0_tcb->Model0_ack_seq = Model0_ntohl(Model0_th->Model0_ack_seq);
 #endif
   Model0_th->Model0_check = 0;
   Model0_th->Model0_urg_ptr = 0;
 
 
 #if CY_ABSTRACT4 //tcp_urg_mode always false
 #else
   if ((Model0_tcp_urg_mode(Model0_tp) && Model0_before(Model0_tcb->Model0_seq, Model0_tp->Model0_snd_up))) {
    if (Model0_before(Model0_tp->Model0_snd_up, Model0_tcb->Model0_seq + 0x10000)) {
     //th->urg_ptr = (( __be16)(__u16)__builtin_bswap16((__u16)((tp->snd_up - tcb->seq))));
     Model0_th->Model0_urg_ptr = Model0_ntohs(Model0_tp->Model0_snd_up - Model0_tcb->Model0_seq);
     Model0_th->Model0_urg = 1;
    } else if (Model0_before(Model0_tp->Model0_snd_nxt, Model0_tcb->Model0_seq + 0xFFFF)) {
     //th->urg_ptr = (( __be16)(__u16)__builtin_bswap16((__u16)((0xFFFF))));
     Model0_th->Model0_urg_ptr = Model0_htons(0xFFFF);
     Model0_th->Model0_urg = 1;
    }
   }
 #endif
#if CY_ABSTRACT1
   //opts is empty anyway
 #else
   //tcp_options_write((__be32 *)(th + 1), tp, &opts);
 #endif
 
   ((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_skb)))->Model0_gso_type = Model0_sk->Model0_sk_gso_type;
   if (!(Model0_tcb->Model0_tcp_flags & 0x02)) {//SYN: 0x02. It means tcp_flags don't have SYN flag
    //th->window = (( __be16)(__u16)_builtin_bswap16((__u16)((tcp_select_window(sk)))));
    Model0_th->Model0_window = Model0_htons(Model0_tcp_select_window(Model0_sk));
    // don't use ecn so far
    //tcp_ecn_send(sk, skb, th, tcp_header_size);
   } else {
 
   // RFC1323: The window in SYN & SYN/ACK segments is never scaled. 
    Model0_th->Model0_window = (Model0_ntohs(Model0_tp->Model0_rcv_wnd < 65535U? Model0_tp->Model0_rcv_wnd: 65535U)); }
 
 #if CY_ABSTRACT1
 #else
   if (md5) {
    sk_nocaps_add(sk, (((netdev_features_t)1 << (NETIF_F_GSO_LAST + 1)) - ((netdev_features_t)1             <<                     (NETIF_F_GSO_SHIFT))));
    tp->af_specific->calc_md5_hash(opts.hash_location,
              md5, sk, skb);
   }
 #endif
 #if CY_ABSTRACT4
   //assume checksum is always correct
#else
   Model0_icsk->Model0_icsk_af_ops->Model0_send_check(Model0_sk, Model0_skb);
 #endif
 
   if (Model0_tcb->Model0_tcp_flags & 0x10) //ACK: 0x10
    Model0_tcp_event_ack_sent(Model0_sk, Model0_tcp_skb_pcount(Model0_skb));
   if (Model0_skb->Model0_len != Model0_tcp_header_size) {
    Model0_tcp_event_data_sent(Model0_tp, Model0_sk);
    Model0_tp->Model0_data_segs_out += Model0_tcp_skb_pcount(Model0_skb);
   }
 
 #if !CY_ABSTRACT4
   if (Model0_before(Model0_tp->Model0_snd_nxt, Model0_tcb->Model0_end_seq) || Model0_tcb->Model0_seq ==    Model0_tcb->Model0_end_seq)
     ;
     //TCP_ADD_STATS(sock_net(sk), TCP_MIB_OUTSEGS, tcp_skb_pcount(skb));
 #endif
 
 // This part seems not important. It's strange that tcb will be cleaned up. So we remove the clean up      process first to see what will happen.
    Model0_tp->Model0_segs_out += Model0_tcp_skb_pcount(Model0_skb);
 
   ((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_skb)))->Model0_gso_segs =               Model0_tcp_skb_pcount(Model0_skb);
   ((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_skb)))->Model0_gso_size =               Model0_tcp_skb_mss(Model0_skb);
 
 
   Model0_skb->Model0_tstamp.Model0_tv64 = 0;
 
 #if !CY_ABSTRACT4
 //  memset(Model0_skb->Model0_cb, 0, max(sizeof(struct inet_skb_parm), sizeof(struct inet6_skb_parm)));
 //#else
   memset(Model0_skb->Model0_cb, 0, ({ typeof(sizeof(struct inet_skb_parm)) _max1 = (sizeof(struct          inet_skb_parm));                  typeof(sizeof(struct inet6_skb_parm)) _max2 = (sizeof(struct             inet6_skb_parm)); /*(void) (&_max1 == &_max2)*/; _max1 >    _max2 ? _max1 : _max2; })); /* Cleanup our     debris for IP stacks */
 #endif
#if CY_ABSTRACT4
   /*
    * 1. Exclude ip and lower layer logic in our model. 
    * 2. Assume they always transmit to lower layer successfully => err = 0;
    */
   return 0;
 #else
   err = icsk->icsk_af_ops->queue_xmit(sk, skb, &inet->cork.fl); //ip_queue_xmit/inet6_csk_xmit
 
   if (err <= 0)
    return err;
   tcp_enter_cwr(sk);
 
   return ((err) == 0x02 ? 0 : (err));
 #endif
}


unsigned char *Model0_skb_push(struct Model0_sk_buff *Model0_skb, unsigned int Model0_len)
{
    //th = (struct tcphdr *)(&Skb[0])->data;
	Model0_skb->Model0_len  += Model0_len;
	Model0_skb->Model0_data -= Model0_len;
    //th = (struct tcphdr *)(&Skb[0])->data;
//	if (unlikely(skb->data<skb->head))
//		skb_under_panic(skb, len, __builtin_return_address(0));
	return Model0_skb->Model0_data;
}

Model0_u16 Model0_tcp_select_window(struct Model0_sock *Model0_sk)
{
  struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
  Model0_u32 Model0_old_win = Model0_tp->Model0_rcv_wnd;
  Model0_u32 Model0_cur_win = Model0_tcp_receive_window(Model0_tp);
  Model0_u32 Model0_new_win = Model0___tcp_select_window(Model0_sk);
 
  Model0_tp->Model0_rcv_wup = Model0_tp->Model0_rcv_nxt; //[CY] [TODO]
 
  if (Model0_new_win < Model0_cur_win) {
 
   if (Model0_new_win == 0)
	;//[CY] NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPWANTZEROWINDOWADV);
 
   Model0_new_win = ((((Model0_cur_win)) + ((typeof((Model0_cur_win)))((1 << Model0_tp->Model0_rx_opt.Model0_rcv_wscale)) - 1)) & ~((typeof((Model0_cur_win)))((1 << Model0_tp->Model0_rx_opt.Model0_rcv_wscale)) - 1));
  }
  Model0_tp->Model0_rcv_wnd = Model0_new_win;
  Model0_tp->Model0_rcv_wup = Model0_tp->Model0_rcv_nxt;

  if (!Model0_tp->Model0_rx_opt.Model0_rcv_wscale && Model0_sysctl_tcp_workaround_signed_windows)
   Model0_new_win = ({ typeof(Model0_new_win) Model0__min1 = (Model0_new_win); typeof(Model0_MAX_TCP_WINDOW) Model0__min2 = (Model0_MAX_TCP_WINDOW); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
  else
   Model0_new_win = ({ typeof(Model0_new_win) Model0__min1 = (Model0_new_win); typeof((65535U << Model0_tp->Model0_rx_opt.Model0_rcv_wscale)) Model0__min2 = ((65535U << Model0_tp->Model0_rx_opt.Model0_rcv_wscale)); (void) (&Model0__min1 ==       &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });

 
  Model0_new_win >>= Model0_tp->Model0_rx_opt.Model0_rcv_wscale;

  if (Model0_new_win == 0) {
   Model0_tp->Model0_pred_flags = 0;
   if (Model0_old_win)
	; // NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPTOZEROWINDOWADV);
 
  } else if (Model0_old_win == 0) {
	; // NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPFROMZEROWINDOWADV);
  }
  return Model0_new_win;
}

Model0_u32 Model0___tcp_select_window(struct Model0_sock *Model0_sk){

#if 0 //CY_ABSTRACT1 [TODO]
    // to make it easy, doesn't change the value
    struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
    return 5; //tp->rcv_wnd;
#else
 struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
  struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 
 
 
 
 
 
  int Model0_mss = Model0_icsk->Model0_icsk_ack.Model0_rcv_mss;
  int Model0_free_space = Model0_tcp_space(Model0_sk); //tcp_win_from_space(sk_rcvbuf - backlog.rmem_alloc) = sk_rcvbuf - backlog.rmem_alloc // the space avaialve in receive buffer
  int Model0_allowed_space = Model0_tcp_full_space(Model0_sk); //tcp_win_from_space(sk_rcvbuf) = sk_rcvbuf // the total space in socket's receive buffer
  int Model0_full_space = ({ int Model0___min1 = (Model0_tp->Model0_window_clamp); int Model0___min2 = (Model0_allowed_space); Model0___min1 < Model0___min2 ? Model0___min1: Model0___min2; });
  int Model0_window;
 
  if (Model0_mss > Model0_full_space)
   Model0_mss = Model0_full_space;
 
  if (Model0_free_space < (Model0_full_space >> 1)) { //over half sk_rcvbuf is taken, send delayed ack to slow down transmission
   Model0_icsk->Model0_icsk_ack.Model0_quick = 0;
 
   if (Model0_tcp_under_memory_pressure(Model0_sk))
    Model0_tp->Model0_rcv_ssthresh = ({ typeof(Model0_tp->Model0_rcv_ssthresh) Model0__min1 = (Model0_tp->Model0_rcv_ssthresh); typeof(4U * Model0_tp->Model0_advmss) Model0__min2 = (4U * Model0_tp->Model0_advmss); (void) (&Model0__min1 == &Model0__min2);      Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });

 
 
 
 
 
   Model0_free_space = ((Model0_free_space) & ~((__typeof__(Model0_free_space))((1 << Model0_tp->Model0_rx_opt.Model0_rcv_wscale)-1)));
   if (Model0_free_space < (Model0_allowed_space >> 4) || Model0_free_space < Model0_mss)
    return 0;
  }
  if (Model0_free_space > Model0_tp->Model0_rcv_ssthresh)
   Model0_free_space = Model0_tp->Model0_rcv_ssthresh;
 
  Model0_window = Model0_tp->Model0_rcv_wnd;
  if (Model0_tp->Model0_rx_opt.Model0_rcv_wscale) {
   Model0_window = Model0_free_space;
 
 
 
 
 
   if (((Model0_window >> Model0_tp->Model0_rx_opt.Model0_rcv_wscale) << Model0_tp->Model0_rx_opt.Model0_rcv_wscale) != Model0_window)
    Model0_window = (((Model0_window >> Model0_tp->Model0_rx_opt.Model0_rcv_wscale) + 1)
       << Model0_tp->Model0_rx_opt.Model0_rcv_wscale);
  } else {
   if (Model0_window <= Model0_free_space - Model0_mss || Model0_window > Model0_free_space)
    Model0_window = (Model0_free_space / Model0_mss) * Model0_mss;
   else if (Model0_mss == Model0_full_space &&
     Model0_free_space > Model0_window + (Model0_full_space >> 1))
    Model0_window = Model0_free_space;
  }
 
  return Model0_window;
#endif
}
 
void Model0_tcp_event_ack_sent(struct Model0_sock *Model0_sk, unsigned int Model0_pkts)
{
  Model0_tcp_dec_quickack_mode(Model0_sk, Model0_pkts);
  Model0_inet_csk_clear_xmit_timer(Model0_sk, 2);
}
 
void Model0_tcp_event_data_sent(struct Model0_tcp_sock *Model0_tp,
     struct Model0_sock *Model0_sk)
{
  struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
  const Model0_u32 Model0_K_now = ((__u32)(Model0_jiffies));
 
  if (Model0_tcp_packets_in_flight(Model0_tp) == 0)
   Model0_tcp_ca_event(Model0_sk, Model0_CA_EVENT_TX_START);
 
  Model0_tp->Model0_lsndtime = Model0_K_now;
 
 
 
 
  if ((Model0_u32)(Model0_K_now - Model0_icsk->Model0_icsk_ack.Model0_lrcvtime) < Model0_icsk->Model0_icsk_ack.Model0_ato){
   Model0_icsk->Model0_icsk_ack.Model0_pingpong = 1;
  }
}

//This function is generated based on tcp_v4_rcv, which updates skb before entering function tcp_rcv_established
void Model0_cy_tcp_v4_rcv(struct Model0_sk_buff *Model0_skb){
    const struct Model0_tcphdr *Model0_th;
#if CY_ABSTRACT1
    /*
     * Assume all following check always false
     * 1. check skb->pkt_type
     * 2. check pskb_may_pull
     * 3. check th->doff < sizeof(struct tcphdr)/4
     * 4. check pskb_may_pull(skb, th->doff*4)
     *
     * 5. ignore skb checksum init //may keep it
     */
#endif
    Model0_th = (const struct Model0_tcphdr *)Model0_skb->Model0_data;
#if CY_ABSTRACT1
    //iph = ip_hdr(skb);
    //memmove(&TCP_SKB_CB(skb)->header.h4, IPCB(skb), sizeof(struct inet_skb_parm));
    //barrier();
#endif
 
    ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq = Model0_ntohl(Model0_th->Model0_seq);
    ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq = (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq + Model0_th->Model0_syn + Model0_th->Model0_fin + Model0_skb->Model0_len - Model0_th->Model0_doff * 4);
    ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_ack_seq = Model0_ntohl(Model0_th->Model0_ack_seq);
    ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_tcp_flags = (((Model0_u_int8_t *)Model0_th)[13]);

    ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_tcp_tw_isn = 0;
#if CY_ABSTRACT1
    //tcb->ip_dsfield = ipv4_get_dsfield(iph) //we don't have ip fields
#endif
    ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked = 0;
}
/*
 *	Functions provided by ip.c
 */

int Model0_ip_build_and_send_pkt(struct Model0_sk_buff *Model0_skb, const struct Model0_sock *Model0_sk,
     Model0___be32 Model0_saddr, Model0___be32 Model0_daddr,
     struct Model0_ip_options_rcu *Model0_opt){
#if CY_ABSTRACT3
    if (Model0_Src_sk == true){
        Model0_Out_pkt = true;
    }
    //Modify 06/11/2018 Right now we only have one direction from Client or Attacker to Server
    //We assume Client won't send packet to Server so we ignore packets sent to Client
    else{
        Model0_Out_pkt = false;
    }
    return 0; //NET_XMIT_SUCCESS
#endif
}
//tcp_prot related
static int Model0_tcp_v4_init_sock(struct Model0_sock *Model0_sk){
    assert(0);
    return 0;
}
static struct Model0_timewait_sock_ops Model0_tcp_timewait_sock_ops = {
    //abstracted
};
void Model0_tcp_close(struct Model0_sock *Model0_sk, long Model0_timeout){
    assert(0);
}
int Model0_tcp_v4_connect(struct Model0_sock *Model0_sk, struct Model0_sockaddr *Model0_uaddr, int Model0_addr_len){
    assert(0);
    return 0;
}
int Model0_tcp_disconnect(struct Model0_sock *Model0_sk, int Model0_flags){
    assert(0);
    return 0;
}
struct Model0_sock *Model0_inet_csk_accept(struct Model0_sock *Model0_sk, int Model0_flags, int *err){
    assert(0);
    return NULL;
}
int Model0_tcp_ioctl(struct Model0_sock *Model0_sk, int Model0_cmd, unsigned long Model0_arg){
    assert(0);
    return 0;
}
void Model0_tcp_v4_destroy_sock(struct Model0_sock *Model0_sk){
    assert(0);
}
void Model0_tcp_shutdown(struct Model0_sock *Model0_sk, int Model0_how){
    assert(0);
}
int Model0_tcp_setsockopt(struct Model0_sock *Model0_sk, int Model0_level, int Model0_optname,
     char *Model0_optval, unsigned int Model0_optlen){
    assert(0);
    return 0;
}
int Model0_compat_tcp_getsockopt(struct Model0_sock *Model0_sk, int Model0_level, int Model0_optname,
     char *Model0_optval, int *Model0_optlen){
    assert(0);
    return 0;
}
int Model0_tcp_sendmsg(struct Model0_sock *Model0_sk, struct Model0_msghdr *Model0_msg, Model0_size_t Model0_size){
    assert(0);
    return 0;
}
int Model0_tcp_recvmsg(struct Model0_sock *Model0_sk, struct Model0_msghdr *Model0_msg, Model0_size_t Model0_len, int Model0_nonblock,
  int Model0_flags, int *Model0_addr_len){
    assert(0);
    return 0;
}
int Model0_tcp_sendpage(struct Model0_sock *Model0_sk, struct Model0_page *Model0_page, int Model0_offset, Model0_size_t Model0_size,
   int Model0_flags){
    assert(0);
    return 0;
}
int Model0_tcp_getsockopt(struct Model0_sock *Model0_sk, int Model0_level, int Model0_optname,
     char *Model0_optval, int *Model0_optlen){
    assert(0);
    return 0;
}
void Model0_tcp_release_cb(struct Model0_sock *Model0_sk){
    assert(0);
}
int Model0_inet_hash(struct Model0_sock *Model0_sk){
    assert(0);
    return 0;
}
void Model0_inet_unhash(struct Model0_sock *Model0_sk){
    assert(0);
}
int Model0_inet_csk_get_port(struct Model0_sock *Model0_sk, unsigned short Model0_snum){
    assert(0);
    return 0;
}
int Model0_tcp_abort(struct Model0_sock *Model0_sk, int err){
    assert(0);
    return 0;
}

int Model0_mod_timer_pending(struct Model0_timer_list *Model0_timer, unsigned long Model0_expires){
#if CY_ABSTRACT2
    //since the time is fixed in our model, there's no meaning to modify timer
    return 0;
#else
    assert(0);
    return 0;
#endif
}

static struct Model0_sock *Model0_sk_prot_alloc(struct Model0_proto *Model0_prot, Model0_gfp_t Model0_priority,
  int Model0_family)
{
 struct Model0_sock *Model0_sk;
 struct Model0_kmem_cache *Model0_slab;

#if CY_ABSTRACT3
 if (Model0_Src_sk)//not spoofed
  Model0_sk = Model0_cy_kmem_cache_alloc(3);
 else
  Model0_sk = Model0_cy_kmem_cache_alloc(4);
 if (!Model0_sk)
  return Model0_sk;
 if (Model0_priority & (( Model0_gfp_t)0x8000u)) {
  if (Model0_prot->Model0_clear_sk)
   Model0_prot->Model0_clear_sk(Model0_sk, Model0_prot->Model0_obj_size); //FP: This won't be visited anyway
  else
   Model0_sk_prot_clear_nulls(Model0_sk, Model0_prot->Model0_obj_size);
 }
#else
 Model0_slab = Model0_prot->Model0_slab;
 if (Model0_slab != ((void *)0)) {
  Model0_sk = Model0_kmem_cache_alloc(Model0_slab, Model0_priority & ~(( Model0_gfp_t)0x8000u));
  if (!Model0_sk)
   return Model0_sk;
  if (Model0_priority & (( Model0_gfp_t)0x8000u)) {
   if (Model0_prot->Model0_clear_sk)
    Model0_prot->Model0_clear_sk(Model0_sk, Model0_prot->Model0_obj_size);
   else
    Model0_sk_prot_clear_nulls(Model0_sk, Model0_prot->Model0_obj_size);
  }
 } else
  Model0_sk = Model0_kmalloc(Model0_prot->Model0_obj_size, Model0_priority);
#endif

 if (Model0_sk != ((void *)0)) {
  do { } while (0);

  if (Model0_security_sk_alloc(Model0_sk, Model0_family, Model0_priority))
   goto Model0_out_free;

  if (!Model0_try_module_get(Model0_prot->Model0_owner))
   goto Model0_out_free_sec;
  Model0_sk_tx_queue_clear(Model0_sk);
 }

 return Model0_sk;

Model0_out_free_sec:
 Model0_security_sk_free(Model0_sk);
Model0_out_free:
 if (Model0_slab != ((void *)0))
  Model0_kmem_cache_free(Model0_slab, Model0_sk);
 else
  Model0_kfree(Model0_sk);
 return ((void *)0);
}

struct Model0_proto Model0_tcp_prot = {
 .Model0_name = "TCP",
 .Model0_owner = ((struct Model0_module *)0),
 .Model0_close = Model0_tcp_close,
 .Model0_connect = Model0_tcp_v4_connect,
 .Model0_disconnect = Model0_tcp_disconnect,
 .Model0_accept = Model0_inet_csk_accept,
 .Model0_ioctl = Model0_tcp_ioctl,
 .Model0_init = Model0_tcp_v4_init_sock,
 .Model0_destroy = Model0_tcp_v4_destroy_sock,
 .Model0_shutdown = Model0_tcp_shutdown,
 .Model0_setsockopt = Model0_tcp_setsockopt,
 .Model0_getsockopt = Model0_tcp_getsockopt,
 .Model0_recvmsg = Model0_tcp_recvmsg,
 .Model0_sendmsg = Model0_tcp_sendmsg,
 .Model0_sendpage = Model0_tcp_sendpage,
 .Model0_backlog_rcv = Model0_tcp_v4_do_rcv,
 .Model0_release_cb = Model0_tcp_release_cb,
 .Model0_hash = Model0_inet_hash,
 .Model0_unhash = Model0_inet_unhash,
 .Model0_get_port = Model0_inet_csk_get_port,
 .Model0_enter_memory_pressure = Model0_tcp_enter_memory_pressure,
 .Model0_stream_memory_free = Model0_tcp_stream_memory_free,
 .Model0_sockets_allocated = &Model0_tcp_sockets_allocated,
 .Model0_orphan_count = &Model0_tcp_orphan_count,
 .Model0_memory_allocated = &Model0_tcp_memory_allocated,
 .Model0_memory_pressure = &Model0_tcp_memory_pressure,
 .Model0_sysctl_mem = Model0_sysctl_tcp_mem,
 .Model0_sysctl_wmem = Model0_sysctl_tcp_wmem,
 .Model0_sysctl_rmem = Model0_sysctl_tcp_rmem,
 .Model0_max_header = (128 + 32),
 .Model0_obj_size = sizeof(struct Model0_tcp_sock),
 .Model0_slab_flags = 0x00080000UL,
 .Model0_twsk_prot = &Model0_tcp_timewait_sock_ops,
 .Model0_rsk_prot = &Model0_tcp_request_sock_ops,
 .Model0_h.Model0_hashinfo = &Model0_tcp_hashinfo,
 .Model0_no_autobind = true,




 .Model0_diag_destroy = Model0_tcp_abort,
};
/*
	.Model0_enter_memory_pressure	= Model0_tcp_enter_memory_pressure,
	.Model0_sockets_allocated	= &Model0_tcp_sockets_allocated,
	.Model0_orphan_count		= &Model0_tcp_orphan_count,
	.Model0_memory_allocated	= &Model0_tcp_memory_allocated,
	.Model0_memory_pressure	= &Model0_tcp_memory_pressure,
	.Model0_sysctl_mem		= Model0_sysctl_tcp_mem,
	.Model0_sysctl_wmem		= Model0_sysctl_tcp_wmem,
	.Model0_sysctl_rmem		= Model0_sysctl_tcp_rmem,
*/

//Inside this file, they are functions introduced with defconfig, including IPSEC, etc
struct Model0_static_key Model0_memalloc_socks;

int Model0_security_inet_conn_request(struct Model0_sock *Model0_sk,
   struct Model0_sk_buff *Model0_skb, struct Model0_request_sock *Model0_req){
#if CY_ABSTRACT1 
    return 0; //in tinyconfig
#endif
}

void __attribute__((section(".spinlock.text"))) Model0__raw_spin_lock(Model0_raw_spinlock_t *Model0_lock){
#if CY_ABSTRACT1
    //TODO: assume no lock is used
#else
    assert(0);
#endif
}


int Model0_printk(const char *Model0_fmt, ...){
#if CY_ABSTRACT3
    //print a kernel message into kernel log
    //This printk is for debug purpose, therefore we ignore them in this model
#endif
    return 0;
}

void Model0_security_inet_conn_established(struct Model0_sock *Model0_sk,
   struct Model0_sk_buff *Model0_skb){
    assert(0);
    return;
}

void Model0_nf_conntrack_destroy(struct Model0_nf_conntrack *Model0_nfct){
    assert(0);
    return;
}

void Model0___compiletime_assert_17(void){
    assert(0);
    return;
}

/* START OF tcp_input.c */

int Model0_sysctl_tcp_timestamps __attribute__((__section__(".data..read_mostly"))) = 1;
int Model0_sysctl_tcp_window_scaling __attribute__((__section__(".data..read_mostly"))) = 1;
int Model0_sysctl_tcp_sack __attribute__((__section__(".data..read_mostly"))) = 1;
int Model0_sysctl_tcp_fack __attribute__((__section__(".data..read_mostly"))) = 1;
int Model0_sysctl_tcp_max_reordering __attribute__((__section__(".data..read_mostly"))) = 300;
int Model0_sysctl_tcp_dsack __attribute__((__section__(".data..read_mostly"))) = 1;
int Model0_sysctl_tcp_app_win __attribute__((__section__(".data..read_mostly"))) = 31;
int Model0_sysctl_tcp_adv_win_scale __attribute__((__section__(".data..read_mostly"))) = 1;
                                       ;

/* rfc5961 challenge ack rate limiting */
int Model0_sysctl_tcp_challenge_ack_limit = 1000;

int Model0_sysctl_tcp_stdurg __attribute__((__section__(".data..read_mostly")));
int Model0_sysctl_tcp_rfc1337 __attribute__((__section__(".data..read_mostly")));
int Model0_sysctl_tcp_max_orphans __attribute__((__section__(".data..read_mostly"))) = 8192;
int Model0_sysctl_tcp_frto __attribute__((__section__(".data..read_mostly"))) = 2;
int Model0_sysctl_tcp_min_rtt_wlen __attribute__((__section__(".data..read_mostly"))) = 300;

int Model0_sysctl_tcp_thin_dupack __attribute__((__section__(".data..read_mostly")));

int Model0_sysctl_tcp_moderate_rcvbuf __attribute__((__section__(".data..read_mostly"))) = 1;
int Model0_sysctl_tcp_early_retrans __attribute__((__section__(".data..read_mostly"))) = 3;
int Model0_sysctl_tcp_invalid_ratelimit __attribute__((__section__(".data..read_mostly"))) = 1000/2;
/* Adapt the MSS value used to make delayed ack decision to the
 * real world.
 */
static void Model0_tcp_measure_rcv_mss(struct Model0_sock *Model0_sk, const struct Model0_sk_buff *Model0_skb)
{
 struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
 const unsigned int Model0_lss = Model0_icsk->Model0_icsk_ack.Model0_last_seg_size;
 unsigned int Model0_len;

 Model0_icsk->Model0_icsk_ack.Model0_last_seg_size = 0;

 /* skb->len may jitter because of SACKs, even if peer
	 * sends good full-sized frames.
	 */
 Model0_len = ((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_skb)))->Model0_gso_size ? : Model0_skb->Model0_len;
 if (Model0_len >= Model0_icsk->Model0_icsk_ack.Model0_rcv_mss) {
  Model0_icsk->Model0_icsk_ack.Model0_rcv_mss = Model0_len;
 } else {
  /* Otherwise, we make more careful check taking into account,
		 * that SACKs block is variable.
		 *
		 * "len" is invariant segment length, including TCP header.
		 */
  Model0_len += Model0_skb->Model0_data - Model0_skb_transport_header(Model0_skb);
  if (Model0_len >= 536U + sizeof(struct Model0_tcphdr) ||
      /* If PSH is not set, packet should be
		     * full sized, provided peer TCP is not badly broken.
		     * This observation (if it is correct 8)) allows
		     * to handle super-low mtu links fairly.
		     */
      (Model0_len >= 88U + sizeof(struct Model0_tcphdr) &&
       !(( ((union Model0_tcp_word_hdr *)(Model0_tcp_hdr(Model0_skb)))->Model0_words [3]) & (Model0_TCP_FLAG_FIN|Model0_TCP_FLAG_URG|Model0_TCP_FLAG_SYN|Model0_TCP_FLAG_PSH)))) {
   /* Subtract also invariant (if peer is RFC compliant),
			 * tcp header plus fixed timestamp option length.
			 * Resulting "len" is MSS free of SACK jitter.
			 */
   Model0_len -= Model0_tcp_sk(Model0_sk)->Model0_tcp_header_len;
   Model0_icsk->Model0_icsk_ack.Model0_last_seg_size = Model0_len;
   if (Model0_len == Model0_lss) {
    Model0_icsk->Model0_icsk_ack.Model0_rcv_mss = Model0_len;
    return;
   }
  }
  if (Model0_icsk->Model0_icsk_ack.Model0_pending & Model0_ICSK_ACK_PUSHED)
   Model0_icsk->Model0_icsk_ack.Model0_pending |= Model0_ICSK_ACK_PUSHED2;
  Model0_icsk->Model0_icsk_ack.Model0_pending |= Model0_ICSK_ACK_PUSHED;
 }
}

static void Model0_tcp_incr_quickack(struct Model0_sock *Model0_sk)
{
 struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
 unsigned int Model0_quickacks = Model0_tcp_sk(Model0_sk)->Model0_rcv_wnd / (2 * Model0_icsk->Model0_icsk_ack.Model0_rcv_mss);

 if (Model0_quickacks == 0)
  Model0_quickacks = 2;
 if (Model0_quickacks > Model0_icsk->Model0_icsk_ack.Model0_quick)
  Model0_icsk->Model0_icsk_ack.Model0_quick = ({ typeof(Model0_quickacks) Model0__min1 = (Model0_quickacks); typeof(16U) Model0__min2 = (16U); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
}

static void Model0_tcp_enter_quickack_mode(struct Model0_sock *Model0_sk)
{
 struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
 Model0_tcp_incr_quickack(Model0_sk);
 Model0_icsk->Model0_icsk_ack.Model0_pingpong = 0;
#if !CY_ABSTRACT2
 Model0_icsk->Model0_icsk_ack.Model0_ato = ((unsigned)(1000/25));
#endif
}

/* Send ACKs quickly, if "quick" count is not exhausted
 * and the session is not interactive.
 */

static bool Model0_tcp_in_quickack_mode(struct Model0_sock *Model0_sk)
{
 const struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
 const struct Model0_dst_entry *Model0_dst = Model0___sk_dst_get(Model0_sk);

 return (Model0_dst && Model0_dst_metric(Model0_dst, Model0_RTAX_QUICKACK)) ||
  (Model0_icsk->Model0_icsk_ack.Model0_quick && !Model0_icsk->Model0_icsk_ack.Model0_pingpong);
}

static void Model0_tcp_ecn_queue_cwr(struct Model0_tcp_sock *Model0_tp)
{
 if (Model0_tp->Model0_ecn_flags & 1)
  Model0_tp->Model0_ecn_flags |= 2;
}

static void Model0_tcp_ecn_accept_cwr(struct Model0_tcp_sock *Model0_tp, const struct Model0_sk_buff *Model0_skb)
{
 if (Model0_tcp_hdr(Model0_skb)->Model0_cwr)
  Model0_tp->Model0_ecn_flags &= ~4;
}

static void Model0_tcp_ecn_withdraw_cwr(struct Model0_tcp_sock *Model0_tp)
{
 Model0_tp->Model0_ecn_flags &= ~4;
}

static void Model0___tcp_ecn_check_ce(struct Model0_tcp_sock *Model0_tp, const struct Model0_sk_buff *Model0_skb)
{
 switch (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_ip_dsfield & Model0_INET_ECN_MASK) {
 case Model0_INET_ECN_NOT_ECT:
  /* Funny extension: if ECT is not set on a segment,
		 * and we already seen ECT on a previous segment,
		 * it is probably a retransmit.
		 */
  if (Model0_tp->Model0_ecn_flags & 8)
   Model0_tcp_enter_quickack_mode((struct Model0_sock *)Model0_tp);
  break;
 case Model0_INET_ECN_CE:
  if (Model0_tcp_ca_needs_ecn((struct Model0_sock *)Model0_tp))
   Model0_tcp_ca_event((struct Model0_sock *)Model0_tp, Model0_CA_EVENT_ECN_IS_CE);

  if (!(Model0_tp->Model0_ecn_flags & 4)) {
   /* Better not delay acks, sender can have a very low cwnd */
   Model0_tcp_enter_quickack_mode((struct Model0_sock *)Model0_tp);
   Model0_tp->Model0_ecn_flags |= 4;
  }
  Model0_tp->Model0_ecn_flags |= 8;
  break;
 default:
  if (Model0_tcp_ca_needs_ecn((struct Model0_sock *)Model0_tp))
   Model0_tcp_ca_event((struct Model0_sock *)Model0_tp, Model0_CA_EVENT_ECN_NO_CE);
  Model0_tp->Model0_ecn_flags |= 8;
  break;
 }
}

static void Model0_tcp_ecn_check_ce(struct Model0_tcp_sock *Model0_tp, const struct Model0_sk_buff *Model0_skb)
{
#if !CY_ABSTRACT1
 if (Model0_tp->Model0_ecn_flags & 1)
  Model0___tcp_ecn_check_ce(Model0_tp, Model0_skb);
#endif
}

static void Model0_tcp_ecn_rcv_synack(struct Model0_tcp_sock *Model0_tp, const struct Model0_tcphdr *Model0_th)
{
 if ((Model0_tp->Model0_ecn_flags & 1) && (!Model0_th->Model0_ece || Model0_th->Model0_cwr))
  Model0_tp->Model0_ecn_flags &= ~1;
}

static void Model0_tcp_ecn_rcv_syn(struct Model0_tcp_sock *Model0_tp, const struct Model0_tcphdr *Model0_th)
{
 if ((Model0_tp->Model0_ecn_flags & 1) && (!Model0_th->Model0_ece || !Model0_th->Model0_cwr))
  Model0_tp->Model0_ecn_flags &= ~1;
}

static bool Model0_tcp_ecn_rcv_ecn_echo(const struct Model0_tcp_sock *Model0_tp, const struct Model0_tcphdr *Model0_th)
{
 if (Model0_th->Model0_ece && !Model0_th->Model0_syn && (Model0_tp->Model0_ecn_flags & 1))
  return true;
 return false;
}

/* Buffer size and advertised window tuning.
 *
 * 1. Tuning sk->sk_sndbuf, when connection enters established state.
 */

static void Model0_tcp_sndbuf_expand(struct Model0_sock *Model0_sk)
{
 const struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 int Model0_sndmem, Model0_per_mss;
 Model0_u32 Model0_nr_segs;

 /* Worst case is non GSO/TSO : each frame consumes one skb
	 * and skb->head is kmalloced using power of two area of memory
	 */
 Model0_per_mss = ({ Model0_u32 Model0___max1 = (Model0_tp->Model0_rx_opt.Model0_mss_clamp); Model0_u32 Model0___max2 = (Model0_tp->Model0_mss_cache); Model0___max1 > Model0___max2 ? Model0___max1: Model0___max2; }) +
    (128 + 32) +
    ((((sizeof(struct Model0_skb_shared_info))) + ((typeof((sizeof(struct Model0_skb_shared_info))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model0_skb_shared_info))))(((1 << (6)))) - 1));

 Model0_per_mss = ( __builtin_constant_p(Model0_per_mss) ? ( (Model0_per_mss == 1) ? 1 : (1UL << (( __builtin_constant_p((Model0_per_mss) - 1) ? ( ((Model0_per_mss) - 1) < 1 ? Model0_____ilog2_NaN() : ((Model0_per_mss) - 1) & (1ULL << 63) ? 63 : ((Model0_per_mss) - 1) & (1ULL << 62) ? 62 : ((Model0_per_mss) - 1) & (1ULL << 61) ? 61 : ((Model0_per_mss) - 1) & (1ULL << 60) ? 60 : ((Model0_per_mss) - 1) & (1ULL << 59) ? 59 : ((Model0_per_mss) - 1) & (1ULL << 58) ? 58 : ((Model0_per_mss) - 1) & (1ULL << 57) ? 57 : ((Model0_per_mss) - 1) & (1ULL << 56) ? 56 : ((Model0_per_mss) - 1) & (1ULL << 55) ? 55 : ((Model0_per_mss) - 1) & (1ULL << 54) ? 54 : ((Model0_per_mss) - 1) & (1ULL << 53) ? 53 : ((Model0_per_mss) - 1) & (1ULL << 52) ? 52 : ((Model0_per_mss) - 1) & (1ULL << 51) ? 51 : ((Model0_per_mss) - 1) & (1ULL << 50) ? 50 : ((Model0_per_mss) - 1) & (1ULL << 49) ? 49 : ((Model0_per_mss) - 1) & (1ULL << 48) ? 48 : ((Model0_per_mss) - 1) & (1ULL << 47) ? 47 : ((Model0_per_mss) - 1) & (1ULL << 46) ? 46 : ((Model0_per_mss) - 1) & (1ULL << 45) ? 45 : ((Model0_per_mss) - 1) & (1ULL << 44) ? 44 : ((Model0_per_mss) - 1) & (1ULL << 43) ? 43 : ((Model0_per_mss) - 1) & (1ULL << 42) ? 42 : ((Model0_per_mss) - 1) & (1ULL << 41) ? 41 : ((Model0_per_mss) - 1) & (1ULL << 40) ? 40 : ((Model0_per_mss) - 1) & (1ULL << 39) ? 39 : ((Model0_per_mss) - 1) & (1ULL << 38) ? 38 : ((Model0_per_mss) - 1) & (1ULL << 37) ? 37 : ((Model0_per_mss) - 1) & (1ULL << 36) ? 36 : ((Model0_per_mss) - 1) & (1ULL << 35) ? 35 : ((Model0_per_mss) - 1) & (1ULL << 34) ? 34 : ((Model0_per_mss) - 1) & (1ULL << 33) ? 33 : ((Model0_per_mss) - 1) & (1ULL << 32) ? 32 : ((Model0_per_mss) - 1) & (1ULL << 31) ? 31 : ((Model0_per_mss) - 1) & (1ULL << 30) ? 30 : ((Model0_per_mss) - 1) & (1ULL << 29) ? 29 : ((Model0_per_mss) - 1) & (1ULL << 28) ? 28 : ((Model0_per_mss) - 1) & (1ULL << 27) ? 27 : ((Model0_per_mss) - 1) & (1ULL << 26) ? 26 : ((Model0_per_mss) - 1) & (1ULL << 25) ? 25 : ((Model0_per_mss) - 1) & (1ULL << 24) ? 24 : ((Model0_per_mss) - 1) & (1ULL << 23) ? 23 : ((Model0_per_mss) - 1) & (1ULL << 22) ? 22 : ((Model0_per_mss) - 1) & (1ULL << 21) ? 21 : ((Model0_per_mss) - 1) & (1ULL << 20) ? 20 : ((Model0_per_mss) - 1) & (1ULL << 19) ? 19 : ((Model0_per_mss) - 1) & (1ULL << 18) ? 18 : ((Model0_per_mss) - 1) & (1ULL << 17) ? 17 : ((Model0_per_mss) - 1) & (1ULL << 16) ? 16 : ((Model0_per_mss) - 1) & (1ULL << 15) ? 15 : ((Model0_per_mss) - 1) & (1ULL << 14) ? 14 : ((Model0_per_mss) - 1) & (1ULL << 13) ? 13 : ((Model0_per_mss) - 1) & (1ULL << 12) ? 12 : ((Model0_per_mss) - 1) & (1ULL << 11) ? 11 : ((Model0_per_mss) - 1) & (1ULL << 10) ? 10 : ((Model0_per_mss) - 1) & (1ULL << 9) ? 9 : ((Model0_per_mss) - 1) & (1ULL << 8) ? 8 : ((Model0_per_mss) - 1) & (1ULL << 7) ? 7 : ((Model0_per_mss) - 1) & (1ULL << 6) ? 6 : ((Model0_per_mss) - 1) & (1ULL << 5) ? 5 : ((Model0_per_mss) - 1) & (1ULL << 4) ? 4 : ((Model0_per_mss) - 1) & (1ULL << 3) ? 3 : ((Model0_per_mss) - 1) & (1ULL << 2) ? 2 : ((Model0_per_mss) - 1) & (1ULL << 1) ? 1 : ((Model0_per_mss) - 1) & (1ULL << 0) ? 0 : Model0_____ilog2_NaN() ) : (sizeof((Model0_per_mss) - 1) <= 4) ? Model0___ilog2_u32((Model0_per_mss) - 1) : Model0___ilog2_u64((Model0_per_mss) - 1) ) + 1)) ) : Model0___roundup_pow_of_two(Model0_per_mss) ) +
    ((((sizeof(struct Model0_sk_buff))) + ((typeof((sizeof(struct Model0_sk_buff))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model0_sk_buff))))(((1 << (6)))) - 1));

 Model0_nr_segs = ({ Model0_u32 Model0___max1 = (10); Model0_u32 Model0___max2 = (Model0_tp->Model0_snd_cwnd); Model0___max1 > Model0___max2 ? Model0___max1: Model0___max2; });
 Model0_nr_segs = ({ Model0_u32 Model0___max1 = (Model0_nr_segs); Model0_u32 Model0___max2 = (Model0_tp->Model0_reordering + 1); Model0___max1 > Model0___max2 ? Model0___max1: Model0___max2; });

 /* Fast Recovery (RFC 5681 3.2) :
	 * Cubic needs 1.7 factor, rounded to 2 to include
	 * extra cushion (application might react slowly to POLLOUT)
	 */
 Model0_sndmem = 2 * Model0_nr_segs * Model0_per_mss;

 if (Model0_sk->Model0_sk_sndbuf < Model0_sndmem)
  Model0_sk->Model0_sk_sndbuf = ({ typeof(Model0_sndmem) Model0__min1 = (Model0_sndmem); typeof(Model0_sysctl_tcp_wmem[2]) Model0__min2 = (Model0_sysctl_tcp_wmem[2]); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
}

/* 2. Tuning advertised window (window_clamp, rcv_ssthresh)
 *
 * All tcp_full_space() is split to two parts: "network" buffer, allocated
 * forward and advertised in receiver window (tp->rcv_wnd) and
 * "application buffer", required to isolate scheduling/application
 * latencies from network.
 * window_clamp is maximal advertised window. It can be less than
 * tcp_full_space(), in this case tcp_full_space() - window_clamp
 * is reserved for "application" buffer. The less window_clamp is
 * the smoother our behaviour from viewpoint of network, but the lower
 * throughput and the higher sensitivity of the connection to losses. 8)
 *
 * rcv_ssthresh is more strict window_clamp used at "slow start"
 * phase to predict further behaviour of this connection.
 * It is used for two goals:
 * - to enforce header prediction at sender, even when application
 *   requires some significant "application buffer". It is check #1.
 * - to prevent pruning of receive queue because of misprediction
 *   of receiver window. Check #2.
 *
 * The scheme does not work when sender sends good segments opening
 * window and then starts to feed us spaghetti. But it should work
 * in common situations. Otherwise, we have to rely on queue collapsing.
 */

/* Slow part of check#2. */
static int Model0___tcp_grow_window(const struct Model0_sock *Model0_sk, const struct Model0_sk_buff *Model0_skb)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 /* Optimize this! */
 int Model0_truesize = Model0_tcp_win_from_space(Model0_skb->Model0_truesize) >> 1;
 int Model0_window = Model0_tcp_win_from_space(Model0_sysctl_tcp_rmem[2]) >> 1;

 while (Model0_tp->Model0_rcv_ssthresh <= Model0_window) {
  if (Model0_truesize <= Model0_skb->Model0_len)
   return 2 * Model0_inet_csk(Model0_sk)->Model0_icsk_ack.Model0_rcv_mss;

  Model0_truesize >>= 1;
  Model0_window >>= 1;
 }
 return 0;
}

static void Model0_tcp_grow_window(struct Model0_sock *Model0_sk, const struct Model0_sk_buff *Model0_skb)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 /* Check #1 */
 if (Model0_tp->Model0_rcv_ssthresh < Model0_tp->Model0_window_clamp &&
     (int)Model0_tp->Model0_rcv_ssthresh < Model0_tcp_space(Model0_sk) &&
     !Model0_tcp_under_memory_pressure(Model0_sk)) {
  int Model0_incr;

  /* Check #2. Increase window, if skb with such overhead
		 * will fit to rcvbuf in future.
		 */
  if (Model0_tcp_win_from_space(Model0_skb->Model0_truesize) <= Model0_skb->Model0_len)
   Model0_incr = 2 * Model0_tp->Model0_advmss;
  else
   Model0_incr = Model0___tcp_grow_window(Model0_sk, Model0_skb);

  if (Model0_incr) {
   Model0_incr = ({ int Model0___max1 = (Model0_incr); int Model0___max2 = (2 * Model0_skb->Model0_len); Model0___max1 > Model0___max2 ? Model0___max1: Model0___max2; });
   Model0_tp->Model0_rcv_ssthresh = ({ typeof(Model0_tp->Model0_rcv_ssthresh + Model0_incr) Model0__min1 = (Model0_tp->Model0_rcv_ssthresh + Model0_incr); typeof(Model0_tp->Model0_window_clamp) Model0__min2 = (Model0_tp->Model0_window_clamp); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });

   Model0_inet_csk(Model0_sk)->Model0_icsk_ack.Model0_quick |= 1;
  }
 }
}

/* 3. Tuning rcvbuf, when connection enters established state. */
static void Model0_tcp_fixup_rcvbuf(struct Model0_sock *Model0_sk)
{
 Model0_u32 Model0_mss = Model0_tcp_sk(Model0_sk)->Model0_advmss;
 int Model0_rcvmem;

 Model0_rcvmem = 2 * ((Model0_mss + (128 + 32)) + ((((sizeof(struct Model0_sk_buff))) + ((typeof((sizeof(struct Model0_sk_buff))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model0_sk_buff))))(((1 << (6)))) - 1)) + ((((sizeof(struct Model0_skb_shared_info))) + ((typeof((sizeof(struct Model0_skb_shared_info))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model0_skb_shared_info))))(((1 << (6)))) - 1))) *
   Model0_tcp_default_init_rwnd(Model0_mss);

 /* Dynamic Right Sizing (DRS) has 2 to 3 RTT latency
	 * Allow enough cushion so that sender is not limited by our window
	 */
 if (Model0_sysctl_tcp_moderate_rcvbuf)
  Model0_rcvmem <<= 2;

 if (Model0_sk->Model0_sk_rcvbuf < Model0_rcvmem)
  Model0_sk->Model0_sk_rcvbuf = ({ typeof(Model0_rcvmem) Model0__min1 = (Model0_rcvmem); typeof(Model0_sysctl_tcp_rmem[2]) Model0__min2 = (Model0_sysctl_tcp_rmem[2]); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
}

/* 4. Try to fixup all. It is made immediately after connection enters
 *    established state.
 */
void Model0_tcp_init_buffer_space(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 int Model0_maxwin;

 if (!(Model0_sk->Model0_sk_userlocks & 2))
  Model0_tcp_fixup_rcvbuf(Model0_sk);
 if (!(Model0_sk->Model0_sk_userlocks & 1))
  Model0_tcp_sndbuf_expand(Model0_sk);

 Model0_tp->Model0_rcvq_space.Model0_space = Model0_tp->Model0_rcv_wnd;
 Model0_tp->Model0_rcvq_space.Model0_time = ((__u32)(Model0_jiffies));
 Model0_tp->Model0_rcvq_space.Model0_seq = Model0_tp->Model0_copied_seq;

 Model0_maxwin = Model0_tcp_full_space(Model0_sk);

 if (Model0_tp->Model0_window_clamp >= Model0_maxwin) {
  Model0_tp->Model0_window_clamp = Model0_maxwin;

  if (Model0_sysctl_tcp_app_win && Model0_maxwin > 4 * Model0_tp->Model0_advmss)
   Model0_tp->Model0_window_clamp = ({ typeof(Model0_maxwin - (Model0_maxwin >> Model0_sysctl_tcp_app_win)) Model0__max1 = (Model0_maxwin - (Model0_maxwin >> Model0_sysctl_tcp_app_win)); typeof(4 * Model0_tp->Model0_advmss) Model0__max2 = (4 * Model0_tp->Model0_advmss); (void) (&Model0__max1 == &Model0__max2); Model0__max1 > Model0__max2 ? Model0__max1 : Model0__max2; });


 }

 /* Force reservation of one segment. */
 if (Model0_sysctl_tcp_app_win &&
     Model0_tp->Model0_window_clamp > 2 * Model0_tp->Model0_advmss &&
     Model0_tp->Model0_window_clamp + Model0_tp->Model0_advmss > Model0_maxwin)
  Model0_tp->Model0_window_clamp = ({ typeof(2 * Model0_tp->Model0_advmss) Model0__max1 = (2 * Model0_tp->Model0_advmss); typeof(Model0_maxwin - Model0_tp->Model0_advmss) Model0__max2 = (Model0_maxwin - Model0_tp->Model0_advmss); (void) (&Model0__max1 == &Model0__max2); Model0__max1 > Model0__max2 ? Model0__max1 : Model0__max2; });

 Model0_tp->Model0_rcv_ssthresh = ({ typeof(Model0_tp->Model0_rcv_ssthresh) Model0__min1 = (Model0_tp->Model0_rcv_ssthresh); typeof(Model0_tp->Model0_window_clamp) Model0__min2 = (Model0_tp->Model0_window_clamp); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
 Model0_tp->Model0_snd_cwnd_stamp = ((__u32)(Model0_jiffies));
}

/* 5. Recalculate window clamp after socket hit its memory bounds. */
static void Model0_tcp_clamp_window(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);

 Model0_icsk->Model0_icsk_ack.Model0_quick = 0;

 if (Model0_sk->Model0_sk_rcvbuf < Model0_sysctl_tcp_rmem[2] &&
     !(Model0_sk->Model0_sk_userlocks & 2) &&
     !Model0_tcp_under_memory_pressure(Model0_sk) &&
     Model0_sk_memory_allocated(Model0_sk) < Model0_sk_prot_mem_limits(Model0_sk, 0)) {
  Model0_sk->Model0_sk_rcvbuf = ({ typeof(Model0_atomic_read(&Model0_sk->Model0_sk_backlog.Model0_rmem_alloc)) Model0__min1 = (Model0_atomic_read(&Model0_sk->Model0_sk_backlog.Model0_rmem_alloc)); typeof(Model0_sysctl_tcp_rmem[2]) Model0__min2 = (Model0_sysctl_tcp_rmem[2]); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });

 }
 if (Model0_atomic_read(&Model0_sk->Model0_sk_backlog.Model0_rmem_alloc) > Model0_sk->Model0_sk_rcvbuf)
  Model0_tp->Model0_rcv_ssthresh = ({ typeof(Model0_tp->Model0_window_clamp) Model0__min1 = (Model0_tp->Model0_window_clamp); typeof(2U * Model0_tp->Model0_advmss) Model0__min2 = (2U * Model0_tp->Model0_advmss); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
}

/* Initialize RCV_MSS value.
 * RCV_MSS is an our guess about MSS used by the peer.
 * We haven't any direct information about the MSS.
 * It's better to underestimate the RCV_MSS rather than overestimate.
 * Overestimations make us ACKing less frequently than needed.
 * Underestimations are more easy to detect and fix by tcp_measure_rcv_mss().
 */
void Model0_tcp_initialize_rcv_mss(struct Model0_sock *Model0_sk)
{
 const struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 unsigned int Model0_hint = ({ unsigned int Model0___min1 = (Model0_tp->Model0_advmss); unsigned int Model0___min2 = (Model0_tp->Model0_mss_cache); Model0___min1 < Model0___min2 ? Model0___min1: Model0___min2; });

 Model0_hint = ({ typeof(Model0_hint) Model0__min1 = (Model0_hint); typeof(Model0_tp->Model0_rcv_wnd / 2) Model0__min2 = (Model0_tp->Model0_rcv_wnd / 2); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
 Model0_hint = ({ typeof(Model0_hint) Model0__min1 = (Model0_hint); typeof(536U) Model0__min2 = (536U); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
 Model0_hint = ({ typeof(Model0_hint) Model0__max1 = (Model0_hint); typeof(88U) Model0__max2 = (88U); (void) (&Model0__max1 == &Model0__max2); Model0__max1 > Model0__max2 ? Model0__max1 : Model0__max2; });

 Model0_inet_csk(Model0_sk)->Model0_icsk_ack.Model0_rcv_mss = Model0_hint;
}
                                     ;

/* Receiver "autotuning" code.
 *
 * The algorithm for RTT estimation w/o timestamps is based on
 * Dynamic Right-Sizing (DRS) by Wu Feng and Mike Fisk of LANL.
 * <http://public.lanl.gov/radiant/pubs.html#DRS>
 *
 * More detail on this code can be found at
 * <http://staff.psc.edu/jheffner/>,
 * though this reference is out of date.  A new paper
 * is pending.
 */
static void Model0_tcp_rcv_rtt_update(struct Model0_tcp_sock *Model0_tp, Model0_u32 Model0_sample, int Model0_win_dep)
{
 Model0_u32 Model0_new_sample = Model0_tp->Model0_rcv_rtt_est.Model0_rtt;
 long Model0_m = Model0_sample;

 if (Model0_m == 0)
  Model0_m = 1;

 if (Model0_new_sample != 0) {
  /* If we sample in larger samples in the non-timestamp
		 * case, we could grossly overestimate the RTT especially
		 * with chatty applications or bulk transfer apps which
		 * are stalled on filesystem I/O.
		 *
		 * Also, since we are only going for a minimum in the
		 * non-timestamp case, we do not smooth things out
		 * else with timestamps disabled convergence takes too
		 * long.
		 */
  if (!Model0_win_dep) {
   Model0_m -= (Model0_new_sample >> 3);
   Model0_new_sample += Model0_m;
  } else {
   Model0_m <<= 3;
   if (Model0_m < Model0_new_sample)
    Model0_new_sample = Model0_m;
  }
 } else {
  /* No previous measure. */
  Model0_new_sample = Model0_m << 3;
 }

 if (Model0_tp->Model0_rcv_rtt_est.Model0_rtt != Model0_new_sample)
  Model0_tp->Model0_rcv_rtt_est.Model0_rtt = Model0_new_sample;
}

static inline __attribute__((no_instrument_function)) void Model0_tcp_rcv_rtt_measure(struct Model0_tcp_sock *Model0_tp)
{
#if CY_ABSTRACT2
#else
 if (Model0_tp->Model0_rcv_rtt_est.Model0_time == 0)
  goto Model0_new_measure;
 if (Model0_before(Model0_tp->Model0_rcv_nxt, Model0_tp->Model0_rcv_rtt_est.Model0_seq))
  return;
 Model0_tcp_rcv_rtt_update(Model0_tp, ((__u32)(Model0_jiffies)) - Model0_tp->Model0_rcv_rtt_est.Model0_time, 1);

Model0_new_measure:
 Model0_tp->Model0_rcv_rtt_est.Model0_seq = Model0_tp->Model0_rcv_nxt + Model0_tp->Model0_rcv_wnd;
 Model0_tp->Model0_rcv_rtt_est.Model0_time = ((__u32)(Model0_jiffies));
#endif
}

static inline __attribute__((no_instrument_function)) void Model0_tcp_rcv_rtt_measure_ts(struct Model0_sock *Model0_sk,
       const struct Model0_sk_buff *Model0_skb)
{
#if !CY_ABSTRACT1
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 if (Model0_tp->Model0_rx_opt.Model0_rcv_tsecr &&
     (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq -
      ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq >= Model0_inet_csk(Model0_sk)->Model0_icsk_ack.Model0_rcv_mss))
  Model0_tcp_rcv_rtt_update(Model0_tp, ((__u32)(Model0_jiffies)) - Model0_tp->Model0_rx_opt.Model0_rcv_tsecr, 0);
#endif
}

/*
 * This function should be called every time data is copied to user space.
 * It calculates the appropriate TCP receive buffer space.
 */
void Model0_tcp_rcv_space_adjust(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 int Model0_time;
 int Model0_copied;

 Model0_time = ((__u32)(Model0_jiffies)) - Model0_tp->Model0_rcvq_space.Model0_time;
 if (Model0_time < (Model0_tp->Model0_rcv_rtt_est.Model0_rtt >> 3) || Model0_tp->Model0_rcv_rtt_est.Model0_rtt == 0)
  return;

 /* Number of bytes copied to user in last RTT */
 Model0_copied = Model0_tp->Model0_copied_seq - Model0_tp->Model0_rcvq_space.Model0_seq;
 if (Model0_copied <= Model0_tp->Model0_rcvq_space.Model0_space)
  goto Model0_new_measure;

 /* A bit of theory :
	 * copied = bytes received in previous RTT, our base window
	 * To cope with packet losses, we need a 2x factor
	 * To cope with slow start, and sender growing its cwin by 100 %
	 * every RTT, we need a 4x factor, because the ACK we are sending
	 * now is for the next RTT, not the current one :
	 * <prev RTT . ><current RTT .. ><next RTT .... >
	 */

 if (Model0_sysctl_tcp_moderate_rcvbuf &&
     !(Model0_sk->Model0_sk_userlocks & 2)) {
  int Model0_rcvwin, Model0_rcvmem, Model0_rcvbuf;

  /* minimal window to cope with packet losses, assuming
		 * steady state. Add some cushion because of small variations.
		 */
  Model0_rcvwin = (Model0_copied << 1) + 16 * Model0_tp->Model0_advmss;

  /* If rate increased by 25%,
		 *	assume slow start, rcvwin = 3 * copied
		 * If rate increased by 50%,
		 *	assume sender can use 2x growth, rcvwin = 4 * copied
		 */
  if (Model0_copied >=
      Model0_tp->Model0_rcvq_space.Model0_space + (Model0_tp->Model0_rcvq_space.Model0_space >> 2)) {
   if (Model0_copied >=
       Model0_tp->Model0_rcvq_space.Model0_space + (Model0_tp->Model0_rcvq_space.Model0_space >> 1))
    Model0_rcvwin <<= 1;
   else
    Model0_rcvwin += (Model0_rcvwin >> 1);
  }

  Model0_rcvmem = ((Model0_tp->Model0_advmss + (128 + 32)) + ((((sizeof(struct Model0_sk_buff))) + ((typeof((sizeof(struct Model0_sk_buff))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model0_sk_buff))))(((1 << (6)))) - 1)) + ((((sizeof(struct Model0_skb_shared_info))) + ((typeof((sizeof(struct Model0_skb_shared_info))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model0_skb_shared_info))))(((1 << (6)))) - 1)));
  while (Model0_tcp_win_from_space(Model0_rcvmem) < Model0_tp->Model0_advmss)
   Model0_rcvmem += 128;

  Model0_rcvbuf = ({ typeof(Model0_rcvwin / Model0_tp->Model0_advmss * Model0_rcvmem) Model0__min1 = (Model0_rcvwin / Model0_tp->Model0_advmss * Model0_rcvmem); typeof(Model0_sysctl_tcp_rmem[2]) Model0__min2 = (Model0_sysctl_tcp_rmem[2]); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
  if (Model0_rcvbuf > Model0_sk->Model0_sk_rcvbuf) {
   Model0_sk->Model0_sk_rcvbuf = Model0_rcvbuf;

   /* Make the window clamp follow along.  */
   Model0_tp->Model0_window_clamp = Model0_rcvwin;
  }
 }
 Model0_tp->Model0_rcvq_space.Model0_space = Model0_copied;

Model0_new_measure:
 Model0_tp->Model0_rcvq_space.Model0_seq = Model0_tp->Model0_copied_seq;
 Model0_tp->Model0_rcvq_space.Model0_time = ((__u32)(Model0_jiffies));
}

/* There is something which you must keep in mind when you analyze the
 * behavior of the tp->ato delayed ack timeout interval.  When a
 * connection starts up, we want to ack as quickly as possible.  The
 * problem is that "good" TCP's do slow start at the beginning of data
 * transmission.  The means that until we send the first few ACK's the
 * sender will sit on his end and only queue most of his data, because
 * he can only send snd_cwnd unacked packets at any given time.  For
 * each ACK we send, he increments snd_cwnd and transmits more of his
 * queue.  -DaveM
 */
static void Model0_tcp_event_data_recv(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
 Model0_u32 Model0_now;

 Model0_inet_csk_schedule_ack(Model0_sk);

 Model0_tcp_measure_rcv_mss(Model0_sk, Model0_skb);

 Model0_tcp_rcv_rtt_measure(Model0_tp);

 Model0_now = ((__u32)(Model0_jiffies));

#if !CY_ABSTRACT2
 if (!Model0_icsk->Model0_icsk_ack.Model0_ato) {
  /* The _first_ data packet received, initialize
		 * delayed ACK engine.
		 */
  Model0_tcp_incr_quickack(Model0_sk);
  Model0_icsk->Model0_icsk_ack.Model0_ato = ((unsigned)(1000/25));
 } else {
  int Model0_m = Model0_now - Model0_icsk->Model0_icsk_ack.Model0_lrcvtime;

  if (Model0_m <= ((unsigned)(1000/25)) / 2) {
   /* The fastest case is the first. */
   Model0_icsk->Model0_icsk_ack.Model0_ato = (Model0_icsk->Model0_icsk_ack.Model0_ato >> 1) + ((unsigned)(1000/25)) / 2;
  } else if (Model0_m < Model0_icsk->Model0_icsk_ack.Model0_ato) {
   Model0_icsk->Model0_icsk_ack.Model0_ato = (Model0_icsk->Model0_icsk_ack.Model0_ato >> 1) + Model0_m;
   if (Model0_icsk->Model0_icsk_ack.Model0_ato > Model0_icsk->Model0_icsk_rto)
    Model0_icsk->Model0_icsk_ack.Model0_ato = Model0_icsk->Model0_icsk_rto;
  } else if (Model0_m > Model0_icsk->Model0_icsk_rto) {
   /* Too long gap. Apparently sender failed to
			 * restart window, so that we send ACKs quickly.
			 */
   Model0_tcp_incr_quickack(Model0_sk);
   Model0_sk_mem_reclaim(Model0_sk);
  }
 }
 Model0_icsk->Model0_icsk_ack.Model0_lrcvtime = Model0_now;
#endif
 Model0_tcp_ecn_check_ce(Model0_tp, Model0_skb);

 if (Model0_skb->Model0_len >= 128)
  Model0_tcp_grow_window(Model0_sk, Model0_skb);
}

/* Called to compute a smoothed rtt estimate. The data fed to this
 * routine either comes from timestamps, or from segments that were
 * known _not_ to have been retransmitted [see Karn/Partridge
 * Proceedings SIGCOMM 87]. The algorithm is from the SIGCOMM 88
 * piece by Van Jacobson.
 * NOTE: the next three routines used to be one big routine.
 * To save cycles in the RFC 1323 implementation it was better to break
 * it up into three procedures. -- erics
 */
static void Model0_tcp_rtt_estimator(struct Model0_sock *Model0_sk, long Model0_mrtt_us)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 long Model0_m = Model0_mrtt_us; /* RTT */
 Model0_u32 Model0_srtt = Model0_tp->Model0_srtt_us;

 /*	The following amusing code comes from Jacobson's
	 *	article in SIGCOMM '88.  Note that rtt and mdev
	 *	are scaled versions of rtt and mean deviation.
	 *	This is designed to be as fast as possible
	 *	m stands for "measurement".
	 *
	 *	On a 1990 paper the rto value is changed to:
	 *	RTO = rtt + 4 * mdev
	 *
	 * Funny. This algorithm seems to be very broken.
	 * These formulae increase RTO, when it should be decreased, increase
	 * too slowly, when it should be increased quickly, decrease too quickly
	 * etc. I guess in BSD RTO takes ONE value, so that it is absolutely
	 * does not matter how to _calculate_ it. Seems, it was trap
	 * that VJ failed to avoid. 8)
	 */
 if (Model0_srtt != 0) {
  Model0_m -= (Model0_srtt >> 3); /* m is now error in rtt est */
  Model0_srtt += Model0_m; /* rtt = 7/8 rtt + 1/8 new */
  if (Model0_m < 0) {
   Model0_m = -Model0_m; /* m is now abs(error) */
   Model0_m -= (Model0_tp->Model0_mdev_us >> 2); /* similar update on mdev */
   /* This is similar to one of Eifel findings.
			 * Eifel blocks mdev updates when rtt decreases.
			 * This solution is a bit different: we use finer gain
			 * for mdev in this case (alpha*beta).
			 * Like Eifel it also prevents growth of rto,
			 * but also it limits too fast rto decreases,
			 * happening in pure Eifel.
			 */
   if (Model0_m > 0)
    Model0_m >>= 3;
  } else {
   Model0_m -= (Model0_tp->Model0_mdev_us >> 2); /* similar update on mdev */
  }
  Model0_tp->Model0_mdev_us += Model0_m; /* mdev = 3/4 mdev + 1/4 new */
  if (Model0_tp->Model0_mdev_us > Model0_tp->Model0_mdev_max_us) {
   Model0_tp->Model0_mdev_max_us = Model0_tp->Model0_mdev_us;
   if (Model0_tp->Model0_mdev_max_us > Model0_tp->Model0_rttvar_us)
    Model0_tp->Model0_rttvar_us = Model0_tp->Model0_mdev_max_us;
  }
  if (Model0_before(Model0_tp->Model0_rtt_seq, Model0_tp->Model0_snd_una)) {
   if (Model0_tp->Model0_mdev_max_us < Model0_tp->Model0_rttvar_us)
    Model0_tp->Model0_rttvar_us -= (Model0_tp->Model0_rttvar_us - Model0_tp->Model0_mdev_max_us) >> 2;
   Model0_tp->Model0_rtt_seq = Model0_tp->Model0_snd_nxt;
   Model0_tp->Model0_mdev_max_us = Model0_tcp_rto_min_us(Model0_sk);
  }
 } else {
  /* no previous measure. */
  Model0_srtt = Model0_m << 3; /* take the measured time to be rtt */
  Model0_tp->Model0_mdev_us = Model0_m << 1; /* make sure rto = 3*rtt */
  Model0_tp->Model0_rttvar_us = ({ typeof(Model0_tp->Model0_mdev_us) Model0__max1 = (Model0_tp->Model0_mdev_us); typeof(Model0_tcp_rto_min_us(Model0_sk)) Model0__max2 = (Model0_tcp_rto_min_us(Model0_sk)); (void) (&Model0__max1 == &Model0__max2); Model0__max1 > Model0__max2 ? Model0__max1 : Model0__max2; });
  Model0_tp->Model0_mdev_max_us = Model0_tp->Model0_rttvar_us;
  Model0_tp->Model0_rtt_seq = Model0_tp->Model0_snd_nxt;
 }
 Model0_tp->Model0_srtt_us = ({ typeof(1U) Model0__max1 = (1U); typeof(Model0_srtt) Model0__max2 = (Model0_srtt); (void) (&Model0__max1 == &Model0__max2); Model0__max1 > Model0__max2 ? Model0__max1 : Model0__max2; });
}

/* Set the sk_pacing_rate to allow proper sizing of TSO packets.
 * Note: TCP stack does not yet implement pacing.
 * FQ packet scheduler can be used to implement cheap but effective
 * TCP pacing, to smooth the burst on large writes when packets
 * in flight is significantly lower than cwnd (or rwin)
 */
int Model0_sysctl_tcp_pacing_ss_ratio __attribute__((__section__(".data..read_mostly"))) = 200;
int Model0_sysctl_tcp_pacing_ca_ratio __attribute__((__section__(".data..read_mostly"))) = 120;

static void Model0_tcp_update_pacing_rate(struct Model0_sock *Model0_sk)
{
 const struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 Model0_u64 Model0_rate;

 /* set sk_pacing_rate to 200 % of current rate (mss * cwnd / srtt) */
 Model0_rate = (Model0_u64)Model0_tp->Model0_mss_cache * ((1000000L / 100) << 3);

 /* current rate is (cwnd * mss) / srtt
	 * In Slow Start [1], set sk_pacing_rate to 200 % the current rate.
	 * In Congestion Avoidance phase, set it to 120 % the current rate.
	 *
	 * [1] : Normal Slow Start condition is (tp->snd_cwnd < tp->snd_ssthresh)
	 *	 If snd_cwnd >= (tp->snd_ssthresh / 2), we are approaching
	 *	 end of slow start and should slow down.
	 */
 if (Model0_tp->Model0_snd_cwnd < Model0_tp->Model0_snd_ssthresh / 2)
  Model0_rate *= Model0_sysctl_tcp_pacing_ss_ratio;
 else
  Model0_rate *= Model0_sysctl_tcp_pacing_ca_ratio;

 Model0_rate *= ({ typeof(Model0_tp->Model0_snd_cwnd) Model0__max1 = (Model0_tp->Model0_snd_cwnd); typeof(Model0_tp->Model0_packets_out) Model0__max2 = (Model0_tp->Model0_packets_out); (void) (&Model0__max1 == &Model0__max2); Model0__max1 > Model0__max2 ? Model0__max1 : Model0__max2; });

 if (__builtin_expect(!!(Model0_tp->Model0_srtt_us), 1))
  ({ Model0_uint32_t Model0___base = (Model0_tp->Model0_srtt_us); Model0_uint32_t Model0___rem; Model0___rem = ((Model0_uint64_t)(Model0_rate)) % Model0___base; (Model0_rate) = ((Model0_uint64_t)(Model0_rate)) / Model0___base; Model0___rem; });

 /* ACCESS_ONCE() is needed because sch_fq fetches sk_pacing_rate
	 * without any lock. We want to make sure compiler wont store
	 * intermediate values in this location.
	 */
 (*({ __attribute__((unused)) typeof(Model0_sk->Model0_sk_pacing_rate) Model0___var = ( typeof(Model0_sk->Model0_sk_pacing_rate)) 0; (volatile typeof(Model0_sk->Model0_sk_pacing_rate) *)&(Model0_sk->Model0_sk_pacing_rate); })) = ({ Model0_u64 Model0___min1 = (Model0_rate); Model0_u64 Model0___min2 = (Model0_sk->Model0_sk_max_pacing_rate); Model0___min1 < Model0___min2 ? Model0___min1: Model0___min2; });

}

/* Calculate rto without backoff.  This is the second half of Van Jacobson's
 * routine referred to above.
 */
static void Model0_tcp_set_rto(struct Model0_sock *Model0_sk)
{
 const struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 /* Old crap is replaced with new one. 8)
	 *
	 * More seriously:
	 * 1. If rtt variance happened to be less 50msec, it is hallucination.
	 *    It cannot be less due to utterly erratic ACK generation made
	 *    at least by solaris and freebsd. "Erratic ACKs" has _nothing_
	 *    to do with delayed acks, because at cwnd>2 true delack timeout
	 *    is invisible. Actually, Linux-2.4 also generates erratic
	 *    ACKs in some circumstances.
	 */
 Model0_inet_csk(Model0_sk)->Model0_icsk_rto = Model0___tcp_set_rto(Model0_tp);

 /* 2. Fixups made earlier cannot be right.
	 *    If we do not estimate RTO correctly without them,
	 *    all the algo is pure shit and should be replaced
	 *    with correct one. It is exactly, which we pretend to do.
	 */

 /* NOTE: clamping at TCP_RTO_MIN is not required, current algo
	 * guarantees that rto is higher.
	 */
 Model0_tcp_bound_rto(Model0_sk);
}

__u32 Model0_tcp_init_cwnd(const struct Model0_tcp_sock *Model0_tp, const struct Model0_dst_entry *Model0_dst)
{
 __u32 Model0_cwnd = (Model0_dst ? Model0_dst_metric(Model0_dst, Model0_RTAX_INITCWND) : 0);

 if (!Model0_cwnd)
  Model0_cwnd = 10;
 return ({ __u32 Model0___min1 = (Model0_cwnd); __u32 Model0___min2 = (Model0_tp->Model0_snd_cwnd_clamp); Model0___min1 < Model0___min2 ? Model0___min1: Model0___min2; });
}

/*
 * Packet counting of FACK is based on in-order assumptions, therefore TCP
 * disables it when reordering is detected
 */
void Model0_tcp_disable_fack(struct Model0_tcp_sock *Model0_tp)
{
 /* RFC3517 uses different metric in lost marker => reset on change */
 if (Model0_tcp_is_fack(Model0_tp))
  Model0_tp->Model0_lost_skb_hint = ((void *)0);
 Model0_tp->Model0_rx_opt.Model0_sack_ok &= ~(1 << 1);
}

/* Take a notice that peer is sending D-SACKs */
static void Model0_tcp_dsack_seen(struct Model0_tcp_sock *Model0_tp)
{
 Model0_tp->Model0_rx_opt.Model0_sack_ok |= (1 << 2);
}

static void Model0_tcp_update_reordering(struct Model0_sock *Model0_sk, const int Model0_metric,
      const int Model0_ts)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 if (Model0_metric > Model0_tp->Model0_reordering) {
  int Model0_mib_idx;

  Model0_tp->Model0_reordering = ({ typeof(Model0_sysctl_tcp_max_reordering) Model0__min1 = (Model0_sysctl_tcp_max_reordering); typeof(Model0_metric) Model0__min2 = (Model0_metric); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });

  /* This exciting event is worth to be remembered. 8) */
  if (Model0_ts)
   Model0_mib_idx = Model0_LINUX_MIB_TCPTSREORDER;
  else if (Model0_tcp_is_reno(Model0_tp))
   Model0_mib_idx = Model0_LINUX_MIB_TCPRENOREORDER;
  else if (Model0_tcp_is_fack(Model0_tp))
   Model0_mib_idx = Model0_LINUX_MIB_TCPFACKREORDER;
  else
   Model0_mib_idx = Model0_LINUX_MIB_TCPSACKREORDER;

  (Model0_cy_linux_mib.Model0_mibs[Model0_mib_idx] += 1);
  Model0_tcp_disable_fack(Model0_tp);
 }

 if (Model0_metric > 0)
  Model0_tcp_disable_early_retrans(Model0_tp);
 Model0_tp->Model0_rack.Model0_reord = 1;
}

/* This must be called before lost_out is incremented */
static void Model0_tcp_verify_retransmit_hint(struct Model0_tcp_sock *Model0_tp, struct Model0_sk_buff *Model0_skb)
{
 if (!Model0_tp->Model0_retransmit_skb_hint ||
     Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq,
     ((struct Model0_tcp_skb_cb *)&((Model0_tp->Model0_retransmit_skb_hint)->Model0_cb[0]))->Model0_seq))
  Model0_tp->Model0_retransmit_skb_hint = Model0_skb;

 if (!Model0_tp->Model0_lost_out ||
     Model0_before(Model0_tp->Model0_retransmit_high, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq))
  Model0_tp->Model0_retransmit_high = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq;
}

static void Model0_tcp_skb_mark_lost(struct Model0_tcp_sock *Model0_tp, struct Model0_sk_buff *Model0_skb)
{
 if (!(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked & (0x04|0x01))) {
  Model0_tcp_verify_retransmit_hint(Model0_tp, Model0_skb);

  Model0_tp->Model0_lost_out += Model0_tcp_skb_pcount(Model0_skb);
  ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked |= 0x04;
 }
}

void Model0_tcp_skb_mark_lost_uncond_verify(struct Model0_tcp_sock *Model0_tp, struct Model0_sk_buff *Model0_skb)
{
 Model0_tcp_verify_retransmit_hint(Model0_tp, Model0_skb);

 if (!(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked & (0x04|0x01))) {
  Model0_tp->Model0_lost_out += Model0_tcp_skb_pcount(Model0_skb);
  ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked |= 0x04;
 }
}

/* This procedure tags the retransmission queue when SACKs arrive.
 *
 * We have three tag bits: SACKED(S), RETRANS(R) and LOST(L).
 * Packets in queue with these bits set are counted in variables
 * sacked_out, retrans_out and lost_out, correspondingly.
 *
 * Valid combinations are:
 * Tag  InFlight	Description
 * 0	1		- orig segment is in flight.
 * S	0		- nothing flies, orig reached receiver.
 * L	0		- nothing flies, orig lost by net.
 * R	2		- both orig and retransmit are in flight.
 * L|R	1		- orig is lost, retransmit is in flight.
 * S|R  1		- orig reached receiver, retrans is still in flight.
 * (L|S|R is logically valid, it could occur when L|R is sacked,
 *  but it is equivalent to plain S and code short-curcuits it to S.
 *  L|S is logically invalid, it would mean -1 packet in flight 8))
 *
 * These 6 states form finite state machine, controlled by the following events:
 * 1. New ACK (+SACK) arrives. (tcp_sacktag_write_queue())
 * 2. Retransmission. (tcp_retransmit_skb(), tcp_xmit_retransmit_queue())
 * 3. Loss detection event of two flavors:
 *	A. Scoreboard estimator decided the packet is lost.
 *	   A'. Reno "three dupacks" marks head of queue lost.
 *	   A''. Its FACK modification, head until snd.fack is lost.
 *	B. SACK arrives sacking SND.NXT at the moment, when the
 *	   segment was retransmitted.
 * 4. D-SACK added new rule: D-SACK changes any tag to S.
 *
 * It is pleasant to note, that state diagram turns out to be commutative,
 * so that we are allowed not to be bothered by order of our actions,
 * when multiple events arrive simultaneously. (see the function below).
 *
 * Reordering detection.
 * --------------------
 * Reordering metric is maximal distance, which a packet can be displaced
 * in packet stream. With SACKs we can estimate it:
 *
 * 1. SACK fills old hole and the corresponding segment was not
 *    ever retransmitted -> reordering. Alas, we cannot use it
 *    when segment was retransmitted.
 * 2. The last flaw is solved with D-SACK. D-SACK arrives
 *    for retransmitted and already SACKed segment -> reordering..
 * Both of these heuristics are not used in Loss state, when we cannot
 * account for retransmits accurately.
 *
 * SACK block validation.
 * ----------------------
 *
 * SACK block range validation checks that the received SACK block fits to
 * the expected sequence limits, i.e., it is between SND.UNA and SND.NXT.
 * Note that SND.UNA is not included to the range though being valid because
 * it means that the receiver is rather inconsistent with itself reporting
 * SACK reneging when it should advance SND.UNA. Such SACK block this is
 * perfectly valid, however, in light of RFC2018 which explicitly states
 * that "SACK block MUST reflect the newest segment.  Even if the newest
 * segment is going to be discarded ...", not that it looks very clever
 * in case of head skb. Due to potentional receiver driven attacks, we
 * choose to avoid immediate execution of a walk in write queue due to
 * reneging and defer head skb's loss recovery to standard loss recovery
 * procedure that will eventually trigger (nothing forbids us doing this).
 *
 * Implements also blockage to start_seq wrap-around. Problem lies in the
 * fact that though start_seq (s) is before end_seq (i.e., not reversed),
 * there's no guarantee that it will be before snd_nxt (n). The problem
 * happens when start_seq resides between end_seq wrap (e_w) and snd_nxt
 * wrap (s_w):
 *
 *         <- outs wnd ->                          <- wrapzone ->
 *         u     e      n                         u_w   e_w  s n_w
 *         |     |      |                          |     |   |  |
 * |<------------+------+----- TCP seqno space --------------+---------->|
 * ...-- <2^31 ->|                                           |<--------...
 * ...---- >2^31 ------>|                                    |<--------...
 *
 * Current code wouldn't be vulnerable but it's better still to discard such
 * crazy SACK blocks. Doing this check for start_seq alone closes somewhat
 * similar case (end_seq after snd_nxt wrap) as earlier reversed check in
 * snd_nxt wrap -> snd_una region will then become "well defined", i.e.,
 * equal to the ideal case (infinite seqno space without wrap caused issues).
 *
 * With D-SACK the lower bound is extended to cover sequence space below
 * SND.UNA down to undo_marker, which is the last point of interest. Yet
 * again, D-SACK block must not to go across snd_una (for the same reason as
 * for the normal SACK blocks, explained above). But there all simplicity
 * ends, TCP might receive valid D-SACKs below that. As long as they reside
 * fully below undo_marker they do not affect behavior in anyway and can
 * therefore be safely ignored. In rare cases (which are more or less
 * theoretical ones), the D-SACK will nicely cross that boundary due to skb
 * fragmentation and packet reordering past skb's retransmission. To consider
 * them correctly, the acceptable range must be extended even more though
 * the exact amount is rather hard to quantify. However, tp->max_window can
 * be used as an exaggerated estimate.
 */
static bool Model0_tcp_is_sackblock_valid(struct Model0_tcp_sock *Model0_tp, bool Model0_is_dsack,
       Model0_u32 Model0_start_seq, Model0_u32 Model0_end_seq)
{
 /* Too far in future, or reversed (interpretation is ambiguous) */
 if (Model0_before(Model0_tp->Model0_snd_nxt, Model0_end_seq) || !Model0_before(Model0_start_seq, Model0_end_seq))
  return false;

 /* Nasty start_seq wrap-around check (see comments above) */
 if (!Model0_before(Model0_start_seq, Model0_tp->Model0_snd_nxt))
  return false;

 /* In outstanding window? ...This is valid exit for D-SACKs too.
	 * start_seq == snd_una is non-sensical (see comments above)
	 */
 if (Model0_before(Model0_tp->Model0_snd_una, Model0_start_seq))
  return true;

 if (!Model0_is_dsack || !Model0_tp->Model0_undo_marker)
  return false;

 /* ...Then it's D-SACK, and must reside below snd_una completely */
 if (Model0_before(Model0_tp->Model0_snd_una, Model0_end_seq))
  return false;

 if (!Model0_before(Model0_start_seq, Model0_tp->Model0_undo_marker))
  return true;

 /* Too old */
 if (!Model0_before(Model0_tp->Model0_undo_marker, Model0_end_seq))
  return false;

 /* Undo_marker boundary crossing (overestimates a lot). Known already:
	 *   start_seq < undo_marker and end_seq >= undo_marker.
	 */
 return !Model0_before(Model0_start_seq, Model0_end_seq - Model0_tp->Model0_max_window);
}

static bool Model0_tcp_check_dsack(struct Model0_sock *Model0_sk, const struct Model0_sk_buff *Model0_ack_skb,
       struct Model0_tcp_sack_block_wire *Model0_sp, int Model0_num_sacks,
       Model0_u32 Model0_prior_snd_una)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 Model0_u32 Model0_start_seq_0 = Model0_get_unaligned_be32(&Model0_sp[0].Model0_start_seq);
 Model0_u32 Model0_end_seq_0 = Model0_get_unaligned_be32(&Model0_sp[0].Model0_end_seq);
 bool Model0_dup_sack = false;

 if (Model0_before(Model0_start_seq_0, ((struct Model0_tcp_skb_cb *)&((Model0_ack_skb)->Model0_cb[0]))->Model0_ack_seq)) {
  Model0_dup_sack = true;
  Model0_tcp_dsack_seen(Model0_tp);
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPDSACKRECV] += 1);
 } else if (Model0_num_sacks > 1) {
  Model0_u32 Model0_end_seq_1 = Model0_get_unaligned_be32(&Model0_sp[1].Model0_end_seq);
  Model0_u32 Model0_start_seq_1 = Model0_get_unaligned_be32(&Model0_sp[1].Model0_start_seq);

  if (!Model0_before(Model0_end_seq_1, Model0_end_seq_0) &&
      !Model0_before(Model0_start_seq_0, Model0_start_seq_1)) {
   Model0_dup_sack = true;
   Model0_tcp_dsack_seen(Model0_tp);
   (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPDSACKOFORECV] += 1);

  }
 }

 /* D-SACK for already forgotten data... Do dumb counting. */
 if (Model0_dup_sack && Model0_tp->Model0_undo_marker && Model0_tp->Model0_undo_retrans > 0 &&
     !Model0_before(Model0_prior_snd_una, Model0_end_seq_0) &&
     Model0_before(Model0_tp->Model0_undo_marker, Model0_end_seq_0))
  Model0_tp->Model0_undo_retrans--;

 return Model0_dup_sack;
}

struct Model0_tcp_sacktag_state {
 int Model0_reord;
 int Model0_fack_count;
 /* Timestamps for earliest and latest never-retransmitted segment
	 * that was SACKed. RTO needs the earliest RTT to stay conservative,
	 * but congestion control should still get an accurate delay signal.
	 */
 struct Model0_skb_mstamp Model0_first_sackt;
 struct Model0_skb_mstamp Model0_last_sackt;
 int Model0_flag;
};

/* Check if skb is fully within the SACK block. In presence of GSO skbs,
 * the incoming SACK may not exactly match but we can find smaller MSS
 * aligned portion of it that matches. Therefore we might need to fragment
 * which may fail and creates some hassle (caller must handle error case
 * returns).
 *
 * FIXME: this could be merged to shift decision code
 */
static int Model0_tcp_match_skb_to_sack(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb,
      Model0_u32 Model0_start_seq, Model0_u32 Model0_end_seq)
{
 int err;
 bool Model0_in_sack;
 unsigned int Model0_pkt_len;
 unsigned int Model0_mss;

 Model0_in_sack = !Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, Model0_start_seq) &&
    !Model0_before(Model0_end_seq, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq);

 if (Model0_tcp_skb_pcount(Model0_skb) > 1 && !Model0_in_sack &&
     Model0_before(Model0_start_seq, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq)) {
  Model0_mss = Model0_tcp_skb_mss(Model0_skb);
  Model0_in_sack = !Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, Model0_start_seq);

  if (!Model0_in_sack) {
   Model0_pkt_len = Model0_start_seq - ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq;
   if (Model0_pkt_len < Model0_mss)
    Model0_pkt_len = Model0_mss;
  } else {
   Model0_pkt_len = Model0_end_seq - ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq;
   if (Model0_pkt_len < Model0_mss)
    return -22;
  }

  /* Round if necessary so that SACKs cover only full MSSes
		 * and/or the remaining small portion (if present)
		 */
  if (Model0_pkt_len > Model0_mss) {
   unsigned int Model0_new_len = (Model0_pkt_len / Model0_mss) * Model0_mss;
   if (!Model0_in_sack && Model0_new_len < Model0_pkt_len) {
    Model0_new_len += Model0_mss;
    if (Model0_new_len >= Model0_skb->Model0_len)
     return 0;
   }
   Model0_pkt_len = Model0_new_len;
  }
  err = Model0_tcp_fragment(Model0_sk, Model0_skb, Model0_pkt_len, Model0_mss, ((( Model0_gfp_t)0x20u)|(( Model0_gfp_t)0x80000u)|(( Model0_gfp_t)0x2000000u)));
  if (err < 0)
   return err;
 }

 return Model0_in_sack;
}

/* Mark the given newly-SACKed range as such, adjusting counters and hints. */
static Model0_u8 Model0_tcp_sacktag_one(struct Model0_sock *Model0_sk,
     struct Model0_tcp_sacktag_state *Model0_state, Model0_u8 Model0_sacked,
     Model0_u32 Model0_start_seq, Model0_u32 Model0_end_seq,
     int Model0_dup_sack, int Model0_pcount,
     const struct Model0_skb_mstamp *Model0_xmit_time)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 int Model0_fack_count = Model0_state->Model0_fack_count;

 /* Account D-SACK for retransmitted packet. */
 if (Model0_dup_sack && (Model0_sacked & (0x02|0x80| 0x10))) {
  if (Model0_tp->Model0_undo_marker && Model0_tp->Model0_undo_retrans > 0 &&
      Model0_before(Model0_tp->Model0_undo_marker, Model0_end_seq))
   Model0_tp->Model0_undo_retrans--;
  if (Model0_sacked & 0x01)
   Model0_state->Model0_reord = ({ typeof(Model0_fack_count) Model0__min1 = (Model0_fack_count); typeof(Model0_state->Model0_reord) Model0__min2 = (Model0_state->Model0_reord); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
 }

 /* Nothing to do; acked frame is about to be dropped (was ACKed). */
 if (!Model0_before(Model0_tp->Model0_snd_una, Model0_end_seq))
  return Model0_sacked;

 if (!(Model0_sacked & 0x01)) {
  Model0_tcp_rack_advance(Model0_tp, Model0_xmit_time, Model0_sacked);

  if (Model0_sacked & 0x02) {
   /* If the segment is not tagged as lost,
			 * we do not clear RETRANS, believing
			 * that retransmission is still in flight.
			 */
   if (Model0_sacked & 0x04) {
    Model0_sacked &= ~(0x04|0x02);
    Model0_tp->Model0_lost_out -= Model0_pcount;
    Model0_tp->Model0_retrans_out -= Model0_pcount;
   }
  } else {
   if (!(Model0_sacked & (0x02|0x80| 0x10))) {
    /* New sack for not retransmitted frame,
				 * which was in hole. It is reordering.
				 */
    if (Model0_before(Model0_start_seq,
        Model0_tcp_highest_sack_seq(Model0_tp)))
     Model0_state->Model0_reord = ({ typeof(Model0_fack_count) Model0__min1 = (Model0_fack_count); typeof(Model0_state->Model0_reord) Model0__min2 = (Model0_state->Model0_reord); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });

    if (!Model0_before(Model0_tp->Model0_high_seq, Model0_end_seq))
     Model0_state->Model0_flag |= 0x200;
    if (Model0_state->Model0_first_sackt.Model0_v64 == 0)
     Model0_state->Model0_first_sackt = *Model0_xmit_time;
    Model0_state->Model0_last_sackt = *Model0_xmit_time;
   }

   if (Model0_sacked & 0x04) {
    Model0_sacked &= ~0x04;
    Model0_tp->Model0_lost_out -= Model0_pcount;
   }
  }

  Model0_sacked |= 0x01;
  Model0_state->Model0_flag |= 0x20;
  Model0_tp->Model0_sacked_out += Model0_pcount;
  Model0_tp->Model0_delivered += Model0_pcount; /* Out-of-order packets delivered */

  Model0_fack_count += Model0_pcount;

  /* Lost marker hint past SACKed? Tweak RFC3517 cnt */
  if (!Model0_tcp_is_fack(Model0_tp) && Model0_tp->Model0_lost_skb_hint &&
      Model0_before(Model0_start_seq, ((struct Model0_tcp_skb_cb *)&((Model0_tp->Model0_lost_skb_hint)->Model0_cb[0]))->Model0_seq))
   Model0_tp->Model0_lost_cnt_hint += Model0_pcount;

  if (Model0_fack_count > Model0_tp->Model0_fackets_out)
   Model0_tp->Model0_fackets_out = Model0_fack_count;
 }

 /* D-SACK. We can detect redundant retransmission in S|R and plain R
	 * frames and clear it. undo_retrans is decreased above, L|R frames
	 * are accounted above as well.
	 */
 if (Model0_dup_sack && (Model0_sacked & 0x02)) {
  Model0_sacked &= ~0x02;
  Model0_tp->Model0_retrans_out -= Model0_pcount;
 }

 return Model0_sacked;
}

/* Shift newly-SACKed bytes from this skb to the immediately previous
 * already-SACKed sk_buff. Mark the newly-SACKed bytes as such.
 */
static bool Model0_tcp_shifted_skb(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb,
       struct Model0_tcp_sacktag_state *Model0_state,
       unsigned int Model0_pcount, int Model0_shifted, int Model0_mss,
       bool Model0_dup_sack)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_sk_buff *Model0_prev = Model0_tcp_write_queue_prev(Model0_sk, Model0_skb);
 Model0_u32 Model0_start_seq = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq; /* start of newly-SACKed */
 Model0_u32 Model0_end_seq = Model0_start_seq + Model0_shifted; /* end of newly-SACKed */

 do { if (!Model0_pcount) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);

 /* Adjust counters and hints for the newly sacked sequence
	 * range but discard the return value since prev is already
	 * marked. We must tag the range first because the seq
	 * advancement below implicitly advances
	 * tcp_highest_sack_seq() when skb is highest_sack.
	 */
 Model0_tcp_sacktag_one(Model0_sk, Model0_state, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked,
   Model0_start_seq, Model0_end_seq, Model0_dup_sack, Model0_pcount,
   &Model0_skb->Model0_skb_mstamp);

 if (Model0_skb == Model0_tp->Model0_lost_skb_hint)
  Model0_tp->Model0_lost_cnt_hint += Model0_pcount;

 ((struct Model0_tcp_skb_cb *)&((Model0_prev)->Model0_cb[0]))->Model0_end_seq += Model0_shifted;
 ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq += Model0_shifted;

 Model0_tcp_skb_pcount_add(Model0_prev, Model0_pcount);
 do { if (Model0_tcp_skb_pcount(Model0_skb) < Model0_pcount) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);
 Model0_tcp_skb_pcount_add(Model0_skb, -Model0_pcount);

 /* When we're adding to gso_segs == 1, gso_size will be zero,
	 * in theory this shouldn't be necessary but as long as DSACK
	 * code can come after this skb later on it's better to keep
	 * setting gso_size to something.
	 */
 if (!((struct Model0_tcp_skb_cb *)&((Model0_prev)->Model0_cb[0]))->Model0_tcp_gso_size)
  ((struct Model0_tcp_skb_cb *)&((Model0_prev)->Model0_cb[0]))->Model0_tcp_gso_size = Model0_mss;

 /* CHECKME: To clear or not to clear? Mimics normal skb currently */
 if (Model0_tcp_skb_pcount(Model0_skb) <= 1)
  ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_tcp_gso_size = 0;

 /* Difference in this won't matter, both ACKed by the same cumul. ACK */
 ((struct Model0_tcp_skb_cb *)&((Model0_prev)->Model0_cb[0]))->Model0_sacked |= (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked & 0x80);

 if (Model0_skb->Model0_len > 0) {
  do { if (!Model0_tcp_skb_pcount(Model0_skb)) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_SACKSHIFTED] += 1);
  return false;
 }

 /* Whole SKB was eaten :-) */

 if (Model0_skb == Model0_tp->Model0_retransmit_skb_hint)
  Model0_tp->Model0_retransmit_skb_hint = Model0_prev;
 if (Model0_skb == Model0_tp->Model0_lost_skb_hint) {
  Model0_tp->Model0_lost_skb_hint = Model0_prev;
  Model0_tp->Model0_lost_cnt_hint -= Model0_tcp_skb_pcount(Model0_prev);
 }

 ((struct Model0_tcp_skb_cb *)&((Model0_prev)->Model0_cb[0]))->Model0_tcp_flags |= ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_tcp_flags;
 ((struct Model0_tcp_skb_cb *)&((Model0_prev)->Model0_cb[0]))->Model0_eor = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_eor;
 if (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_tcp_flags & 0x01)
  ((struct Model0_tcp_skb_cb *)&((Model0_prev)->Model0_cb[0]))->Model0_end_seq++;

 if (Model0_skb == Model0_tcp_highest_sack(Model0_sk))
  Model0_tcp_advance_highest_sack(Model0_sk, Model0_skb);

 Model0_tcp_skb_collapse_tstamp(Model0_prev, Model0_skb);
 Model0_tcp_unlink_write_queue(Model0_skb, Model0_sk);
 Model0_sk_wmem_free_skb(Model0_sk, Model0_skb);

 (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_SACKMERGED] += 1);

 return true;
}

/* I wish gso_size would have a bit more sane initialization than
 * something-or-zero which complicates things
 */
static int Model0_tcp_skb_seglen(const struct Model0_sk_buff *Model0_skb)
{
 return Model0_tcp_skb_pcount(Model0_skb) == 1 ? Model0_skb->Model0_len : Model0_tcp_skb_mss(Model0_skb);
}

/* Shifting pages past head area doesn't work */
static int Model0_skb_can_shift(const struct Model0_sk_buff *Model0_skb)
{
 return !Model0_skb_headlen(Model0_skb) && Model0_skb_is_nonlinear(Model0_skb);
}

/* Try collapsing SACK blocks spanning across multiple skbs to a single
 * skb.
 */
static struct Model0_sk_buff *Model0_tcp_shift_skb_data(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb,
       struct Model0_tcp_sacktag_state *Model0_state,
       Model0_u32 Model0_start_seq, Model0_u32 Model0_end_seq,
       bool Model0_dup_sack)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_sk_buff *Model0_prev;
 int Model0_mss;
 int Model0_pcount = 0;
 int Model0_len;
 int Model0_in_sack;

 if (!Model0_sk_can_gso(Model0_sk))
  goto Model0_fallback;

 /* Normally R but no L won't result in plain S */
 if (!Model0_dup_sack &&
     (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked & (0x04|0x02)) == 0x02)
  goto Model0_fallback;
 if (!Model0_skb_can_shift(Model0_skb))
  goto Model0_fallback;
 /* This frame is about to be dropped (was ACKed). */
 if (!Model0_before(Model0_tp->Model0_snd_una, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq))
  goto Model0_fallback;

 /* Can only happen with delayed DSACK + discard craziness */
 if (__builtin_expect(!!(Model0_skb == Model0_tcp_write_queue_head(Model0_sk)), 0))
  goto Model0_fallback;
 Model0_prev = Model0_tcp_write_queue_prev(Model0_sk, Model0_skb);

 if ((((struct Model0_tcp_skb_cb *)&((Model0_prev)->Model0_cb[0]))->Model0_sacked & 0x07) != 0x01)
  goto Model0_fallback;

 if (!Model0_tcp_skb_can_collapse_to(Model0_prev))
  goto Model0_fallback;

 Model0_in_sack = !Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, Model0_start_seq) &&
    !Model0_before(Model0_end_seq, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq);

 if (Model0_in_sack) {
  Model0_len = Model0_skb->Model0_len;
  Model0_pcount = Model0_tcp_skb_pcount(Model0_skb);
  Model0_mss = Model0_tcp_skb_seglen(Model0_skb);

  /* TODO: Fix DSACKs to not fragment already SACKed and we can
		 * drop this restriction as unnecessary
		 */
  if (Model0_mss != Model0_tcp_skb_seglen(Model0_prev))
   goto Model0_fallback;
 } else {
  if (!Model0_before(Model0_start_seq, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq))
   goto noop;
  /* CHECKME: This is non-MSS split case only?, this will
		 * cause skipped skbs due to advancing loop btw, original
		 * has that feature too
		 */
  if (Model0_tcp_skb_pcount(Model0_skb) <= 1)
   goto noop;

  Model0_in_sack = !Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, Model0_start_seq);
  if (!Model0_in_sack) {
   /* TODO: head merge to next could be attempted here
			 * if (!after(TCP_SKB_CB(skb)->end_seq, end_seq)),
			 * though it might not be worth of the additional hassle
			 *
			 * ...we can probably just fallback to what was done
			 * previously. We could try merging non-SACKed ones
			 * as well but it probably isn't going to buy off
			 * because later SACKs might again split them, and
			 * it would make skb timestamp tracking considerably
			 * harder problem.
			 */
   goto Model0_fallback;
  }

  Model0_len = Model0_end_seq - ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq;
  do { if (Model0_len < 0) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);
  do { if (Model0_len > Model0_skb->Model0_len) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);

  /* MSS boundaries should be honoured or else pcount will
		 * severely break even though it makes things bit trickier.
		 * Optimize common case to avoid most of the divides
		 */
  Model0_mss = Model0_tcp_skb_mss(Model0_skb);

  /* TODO: Fix DSACKs to not fragment already SACKed and we can
		 * drop this restriction as unnecessary
		 */
  if (Model0_mss != Model0_tcp_skb_seglen(Model0_prev))
   goto Model0_fallback;

  if (Model0_len == Model0_mss) {
   Model0_pcount = 1;
  } else if (Model0_len < Model0_mss) {
   goto noop;
  } else {
   Model0_pcount = Model0_len / Model0_mss;
   Model0_len = Model0_pcount * Model0_mss;
  }
 }

 /* tcp_sacktag_one() won't SACK-tag ranges below snd_una */
 if (!Model0_before(Model0_tp->Model0_snd_una, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq + Model0_len))
  goto Model0_fallback;

 if (!Model0_skb_shift(Model0_prev, Model0_skb, Model0_len))
  goto Model0_fallback;
 if (!Model0_tcp_shifted_skb(Model0_sk, Model0_skb, Model0_state, Model0_pcount, Model0_len, Model0_mss, Model0_dup_sack))
  goto Model0_out;

 /* Hole filled allows collapsing with the next as well, this is very
	 * useful when hole on every nth skb pattern happens
	 */
 if (Model0_prev == Model0_tcp_write_queue_tail(Model0_sk))
  goto Model0_out;
 Model0_skb = Model0_tcp_write_queue_next(Model0_sk, Model0_prev);

 if (!Model0_skb_can_shift(Model0_skb) ||
     (Model0_skb == Model0_tcp_send_head(Model0_sk)) ||
     ((((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked & 0x07) != 0x01) ||
     (Model0_mss != Model0_tcp_skb_seglen(Model0_skb)))
  goto Model0_out;

 Model0_len = Model0_skb->Model0_len;
 if (Model0_skb_shift(Model0_prev, Model0_skb, Model0_len)) {
  Model0_pcount += Model0_tcp_skb_pcount(Model0_skb);
  Model0_tcp_shifted_skb(Model0_sk, Model0_skb, Model0_state, Model0_tcp_skb_pcount(Model0_skb), Model0_len, Model0_mss, 0);
 }

Model0_out:
 Model0_state->Model0_fack_count += Model0_pcount;
 return Model0_prev;

noop:
 return Model0_skb;

Model0_fallback:
 (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_SACKSHIFTFALLBACK] += 1);
 return ((void *)0);
}

static struct Model0_sk_buff *Model0_tcp_sacktag_walk(struct Model0_sk_buff *Model0_skb, struct Model0_sock *Model0_sk,
     struct Model0_tcp_sack_block *Model0_next_dup,
     struct Model0_tcp_sacktag_state *Model0_state,
     Model0_u32 Model0_start_seq, Model0_u32 Model0_end_seq,
     bool Model0_dup_sack_in)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_sk_buff *Model0_tmp;

 for (; Model0_skb != (struct Model0_sk_buff *)(&(Model0_sk)->Model0_sk_write_queue); Model0_skb = Model0_skb->Model0_next) {
  int Model0_in_sack = 0;
  bool Model0_dup_sack = Model0_dup_sack_in;

  if (Model0_skb == Model0_tcp_send_head(Model0_sk))
   break;

  /* queue is in-order => we can short-circuit the walk early */
  if (!Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, Model0_end_seq))
   break;

  if (Model0_next_dup &&
      Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, Model0_next_dup->Model0_end_seq)) {
   Model0_in_sack = Model0_tcp_match_skb_to_sack(Model0_sk, Model0_skb,
       Model0_next_dup->Model0_start_seq,
       Model0_next_dup->Model0_end_seq);
   if (Model0_in_sack > 0)
    Model0_dup_sack = true;
  }

  /* skb reference here is a bit tricky to get right, since
		 * shifting can eat and free both this skb and the next,
		 * so not even _safe variant of the loop is enough.
		 */
  if (Model0_in_sack <= 0) {
   Model0_tmp = Model0_tcp_shift_skb_data(Model0_sk, Model0_skb, Model0_state,
       Model0_start_seq, Model0_end_seq, Model0_dup_sack);
   if (Model0_tmp) {
    if (Model0_tmp != Model0_skb) {
     Model0_skb = Model0_tmp;
     continue;
    }

    Model0_in_sack = 0;
   } else {
    Model0_in_sack = Model0_tcp_match_skb_to_sack(Model0_sk, Model0_skb,
        Model0_start_seq,
        Model0_end_seq);
   }
  }

  if (__builtin_expect(!!(Model0_in_sack < 0), 0))
   break;

  if (Model0_in_sack) {
   ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked =
    Model0_tcp_sacktag_one(Model0_sk,
      Model0_state,
      ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked,
      ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq,
      ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq,
      Model0_dup_sack,
      Model0_tcp_skb_pcount(Model0_skb),
      &Model0_skb->Model0_skb_mstamp);

   if (!Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq,
        Model0_tcp_highest_sack_seq(Model0_tp)))
    Model0_tcp_advance_highest_sack(Model0_sk, Model0_skb);
  }

  Model0_state->Model0_fack_count += Model0_tcp_skb_pcount(Model0_skb);
 }
 return Model0_skb;
}

/* Avoid all extra work that is being done by sacktag while walking in
 * a normal way
 */
static struct Model0_sk_buff *Model0_tcp_sacktag_skip(struct Model0_sk_buff *Model0_skb, struct Model0_sock *Model0_sk,
     struct Model0_tcp_sacktag_state *Model0_state,
     Model0_u32 Model0_skip_to_seq)
{
 for (; Model0_skb != (struct Model0_sk_buff *)(&(Model0_sk)->Model0_sk_write_queue); Model0_skb = Model0_skb->Model0_next) {
  if (Model0_skb == Model0_tcp_send_head(Model0_sk))
   break;

  if (Model0_before(Model0_skip_to_seq, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq))
   break;

  Model0_state->Model0_fack_count += Model0_tcp_skb_pcount(Model0_skb);
 }
 return Model0_skb;
}

static struct Model0_sk_buff *Model0_tcp_maybe_skipping_dsack(struct Model0_sk_buff *Model0_skb,
      struct Model0_sock *Model0_sk,
      struct Model0_tcp_sack_block *Model0_next_dup,
      struct Model0_tcp_sacktag_state *Model0_state,
      Model0_u32 Model0_skip_to_seq)
{
 if (!Model0_next_dup)
  return Model0_skb;

 if (Model0_before(Model0_next_dup->Model0_start_seq, Model0_skip_to_seq)) {
  Model0_skb = Model0_tcp_sacktag_skip(Model0_skb, Model0_sk, Model0_state, Model0_next_dup->Model0_start_seq);
  Model0_skb = Model0_tcp_sacktag_walk(Model0_skb, Model0_sk, ((void *)0), Model0_state,
           Model0_next_dup->Model0_start_seq, Model0_next_dup->Model0_end_seq,
           1);
 }

 return Model0_skb;
}

static int Model0_tcp_sack_cache_ok(const struct Model0_tcp_sock *Model0_tp, const struct Model0_tcp_sack_block *Model0_cache)
{
 return Model0_cache < Model0_tp->Model0_recv_sack_cache + (sizeof(Model0_tp->Model0_recv_sack_cache) / sizeof((Model0_tp->Model0_recv_sack_cache)[0]) + (sizeof(struct { int:-!!(__builtin_types_compatible_p(typeof((Model0_tp->Model0_recv_sack_cache)), typeof(&(Model0_tp->Model0_recv_sack_cache)[0]))); })));
}

static int
Model0_tcp_sacktag_write_queue(struct Model0_sock *Model0_sk, const struct Model0_sk_buff *Model0_ack_skb,
   Model0_u32 Model0_prior_snd_una, struct Model0_tcp_sacktag_state *Model0_state)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 const unsigned char *Model0_ptr = (Model0_skb_transport_header(Model0_ack_skb) +
        ((struct Model0_tcp_skb_cb *)&((Model0_ack_skb)->Model0_cb[0]))->Model0_sacked);
 struct Model0_tcp_sack_block_wire *Model0_sp_wire = (struct Model0_tcp_sack_block_wire *)(Model0_ptr+2);
 struct Model0_tcp_sack_block Model0_sp[4];
 struct Model0_tcp_sack_block *Model0_cache;
 struct Model0_sk_buff *Model0_skb;
 int Model0_num_sacks = ({ typeof(4) Model0__min1 = (4); typeof((Model0_ptr[1] - 2) >> 3) Model0__min2 = ((Model0_ptr[1] - 2) >> 3); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
 int Model0_used_sacks;
 bool Model0_found_dup_sack = false;
 int Model0_i, Model0_j;
 int Model0_first_sack_index;

 Model0_state->Model0_flag = 0;
 Model0_state->Model0_reord = Model0_tp->Model0_packets_out;

 if (!Model0_tp->Model0_sacked_out) {
  if (({ int Model0___ret_warn_on = !!(Model0_tp->Model0_fackets_out); __builtin_expect(!!(Model0___ret_warn_on), 0); }))
   Model0_tp->Model0_fackets_out = 0;
  Model0_tcp_highest_sack_reset(Model0_sk);
 }

 Model0_found_dup_sack = Model0_tcp_check_dsack(Model0_sk, Model0_ack_skb, Model0_sp_wire,
      Model0_num_sacks, Model0_prior_snd_una);
 if (Model0_found_dup_sack)
  Model0_state->Model0_flag |= 0x800;

 /* Eliminate too old ACKs, but take into
	 * account more or less fresh ones, they can
	 * contain valid SACK info.
	 */
 if (Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_ack_skb)->Model0_cb[0]))->Model0_ack_seq, Model0_prior_snd_una - Model0_tp->Model0_max_window))
  return 0;

 if (!Model0_tp->Model0_packets_out)
  goto Model0_out;

 Model0_used_sacks = 0;
 Model0_first_sack_index = 0;
 for (Model0_i = 0; Model0_i < Model0_num_sacks; Model0_i++) {
  bool Model0_dup_sack = !Model0_i && Model0_found_dup_sack;

  Model0_sp[Model0_used_sacks].Model0_start_seq = Model0_get_unaligned_be32(&Model0_sp_wire[Model0_i].Model0_start_seq);
  Model0_sp[Model0_used_sacks].Model0_end_seq = Model0_get_unaligned_be32(&Model0_sp_wire[Model0_i].Model0_end_seq);

  if (!Model0_tcp_is_sackblock_valid(Model0_tp, Model0_dup_sack,
         Model0_sp[Model0_used_sacks].Model0_start_seq,
         Model0_sp[Model0_used_sacks].Model0_end_seq)) {
   int Model0_mib_idx;

   if (Model0_dup_sack) {
    if (!Model0_tp->Model0_undo_marker)
     Model0_mib_idx = Model0_LINUX_MIB_TCPDSACKIGNOREDNOUNDO;
    else
     Model0_mib_idx = Model0_LINUX_MIB_TCPDSACKIGNOREDOLD;
   } else {
    /* Don't count olds caused by ACK reordering */
    if ((((struct Model0_tcp_skb_cb *)&((Model0_ack_skb)->Model0_cb[0]))->Model0_ack_seq != Model0_tp->Model0_snd_una) &&
        !Model0_before(Model0_tp->Model0_snd_una, Model0_sp[Model0_used_sacks].Model0_end_seq))
     continue;
    Model0_mib_idx = Model0_LINUX_MIB_TCPSACKDISCARD;
   }

   (Model0_cy_linux_mib.Model0_mibs[Model0_mib_idx] += 1);
   if (Model0_i == 0)
    Model0_first_sack_index = -1;
   continue;
  }

  /* Ignore very old stuff early */
  if (!Model0_before(Model0_prior_snd_una, Model0_sp[Model0_used_sacks].Model0_end_seq))
   continue;

  Model0_used_sacks++;
 }

 /* order SACK blocks to allow in order walk of the retrans queue */
 for (Model0_i = Model0_used_sacks - 1; Model0_i > 0; Model0_i--) {
  for (Model0_j = 0; Model0_j < Model0_i; Model0_j++) {
   if (Model0_before(Model0_sp[Model0_j + 1].Model0_start_seq, Model0_sp[Model0_j].Model0_start_seq)) {
    do { typeof(Model0_sp[Model0_j]) Model0___tmp = (Model0_sp[Model0_j]); (Model0_sp[Model0_j]) = (Model0_sp[Model0_j + 1]); (Model0_sp[Model0_j + 1]) = Model0___tmp; } while (0);

    /* Track where the first SACK block goes to */
    if (Model0_j == Model0_first_sack_index)
     Model0_first_sack_index = Model0_j + 1;
   }
  }
 }

 Model0_skb = Model0_tcp_write_queue_head(Model0_sk);
 Model0_state->Model0_fack_count = 0;
 Model0_i = 0;

 if (!Model0_tp->Model0_sacked_out) {
  /* It's already past, so skip checking against it */
  Model0_cache = Model0_tp->Model0_recv_sack_cache + (sizeof(Model0_tp->Model0_recv_sack_cache) / sizeof((Model0_tp->Model0_recv_sack_cache)[0]) + (sizeof(struct { int:-!!(__builtin_types_compatible_p(typeof((Model0_tp->Model0_recv_sack_cache)), typeof(&(Model0_tp->Model0_recv_sack_cache)[0]))); })));
 } else {
  Model0_cache = Model0_tp->Model0_recv_sack_cache;
  /* Skip empty blocks in at head of the cache */
  while (Model0_tcp_sack_cache_ok(Model0_tp, Model0_cache) && !Model0_cache->Model0_start_seq &&
         !Model0_cache->Model0_end_seq)
   Model0_cache++;
 }

 while (Model0_i < Model0_used_sacks) {
  Model0_u32 Model0_start_seq = Model0_sp[Model0_i].Model0_start_seq;
  Model0_u32 Model0_end_seq = Model0_sp[Model0_i].Model0_end_seq;
  bool Model0_dup_sack = (Model0_found_dup_sack && (Model0_i == Model0_first_sack_index));
  struct Model0_tcp_sack_block *Model0_next_dup = ((void *)0);

  if (Model0_found_dup_sack && ((Model0_i + 1) == Model0_first_sack_index))
   Model0_next_dup = &Model0_sp[Model0_i + 1];

  /* Skip too early cached blocks */
  while (Model0_tcp_sack_cache_ok(Model0_tp, Model0_cache) &&
         !Model0_before(Model0_start_seq, Model0_cache->Model0_end_seq))
   Model0_cache++;

  /* Can skip some work by looking recv_sack_cache? */
  if (Model0_tcp_sack_cache_ok(Model0_tp, Model0_cache) && !Model0_dup_sack &&
      Model0_before(Model0_cache->Model0_start_seq, Model0_end_seq)) {

   /* Head todo? */
   if (Model0_before(Model0_start_seq, Model0_cache->Model0_start_seq)) {
    Model0_skb = Model0_tcp_sacktag_skip(Model0_skb, Model0_sk, Model0_state,
             Model0_start_seq);
    Model0_skb = Model0_tcp_sacktag_walk(Model0_skb, Model0_sk, Model0_next_dup,
             Model0_state,
             Model0_start_seq,
             Model0_cache->Model0_start_seq,
             Model0_dup_sack);
   }

   /* Rest of the block already fully processed? */
   if (!Model0_before(Model0_cache->Model0_end_seq, Model0_end_seq))
    goto Model0_advance_sp;

   Model0_skb = Model0_tcp_maybe_skipping_dsack(Model0_skb, Model0_sk, Model0_next_dup,
             Model0_state,
             Model0_cache->Model0_end_seq);

   /* ...tail remains todo... */
   if (Model0_tcp_highest_sack_seq(Model0_tp) == Model0_cache->Model0_end_seq) {
    /* ...but better entrypoint exists! */
    Model0_skb = Model0_tcp_highest_sack(Model0_sk);
    if (!Model0_skb)
     break;
    Model0_state->Model0_fack_count = Model0_tp->Model0_fackets_out;
    Model0_cache++;
    goto Model0_walk;
   }

   Model0_skb = Model0_tcp_sacktag_skip(Model0_skb, Model0_sk, Model0_state, Model0_cache->Model0_end_seq);
   /* Check overlap against next cached too (past this one already) */
   Model0_cache++;
   continue;
  }

  if (!Model0_before(Model0_start_seq, Model0_tcp_highest_sack_seq(Model0_tp))) {
   Model0_skb = Model0_tcp_highest_sack(Model0_sk);
   if (!Model0_skb)
    break;
   Model0_state->Model0_fack_count = Model0_tp->Model0_fackets_out;
  }
  Model0_skb = Model0_tcp_sacktag_skip(Model0_skb, Model0_sk, Model0_state, Model0_start_seq);

Model0_walk:
  Model0_skb = Model0_tcp_sacktag_walk(Model0_skb, Model0_sk, Model0_next_dup, Model0_state,
           Model0_start_seq, Model0_end_seq, Model0_dup_sack);

Model0_advance_sp:
  Model0_i++;
 }

 /* Clear the head of the cache sack blocks so we can skip it next time */
 for (Model0_i = 0; Model0_i < (sizeof(Model0_tp->Model0_recv_sack_cache) / sizeof((Model0_tp->Model0_recv_sack_cache)[0]) + (sizeof(struct { int:-!!(__builtin_types_compatible_p(typeof((Model0_tp->Model0_recv_sack_cache)), typeof(&(Model0_tp->Model0_recv_sack_cache)[0]))); }))) - Model0_used_sacks; Model0_i++) {
  Model0_tp->Model0_recv_sack_cache[Model0_i].Model0_start_seq = 0;
  Model0_tp->Model0_recv_sack_cache[Model0_i].Model0_end_seq = 0;
 }
 for (Model0_j = 0; Model0_j < Model0_used_sacks; Model0_j++)
  Model0_tp->Model0_recv_sack_cache[Model0_i++] = Model0_sp[Model0_j];

 if ((Model0_state->Model0_reord < Model0_tp->Model0_fackets_out) &&
     ((Model0_inet_csk(Model0_sk)->Model0_icsk_ca_state != Model0_TCP_CA_Loss) || Model0_tp->Model0_undo_marker))
  Model0_tcp_update_reordering(Model0_sk, Model0_tp->Model0_fackets_out - Model0_state->Model0_reord, 0);

 ({ int Model0___ret_warn_on = !!(Model0_tcp_left_out(Model0_tp) > Model0_tp->Model0_packets_out); __builtin_expect(!!(Model0___ret_warn_on), 0); });
Model0_out:


 ({ int Model0___ret_warn_on = !!((int)Model0_tp->Model0_sacked_out < 0); __builtin_expect(!!(Model0___ret_warn_on), 0); });
 ({ int Model0___ret_warn_on = !!((int)Model0_tp->Model0_lost_out < 0); __builtin_expect(!!(Model0___ret_warn_on), 0); });
 ({ int Model0___ret_warn_on = !!((int)Model0_tp->Model0_retrans_out < 0); __builtin_expect(!!(Model0___ret_warn_on), 0); });
 ({ int Model0___ret_warn_on = !!((int)Model0_tcp_packets_in_flight(Model0_tp) < 0); __builtin_expect(!!(Model0___ret_warn_on), 0); });

 return Model0_state->Model0_flag;
}

/* Limits sacked_out so that sum with lost_out isn't ever larger than
 * packets_out. Returns false if sacked_out adjustement wasn't necessary.
 */
static bool Model0_tcp_limit_reno_sacked(struct Model0_tcp_sock *Model0_tp)
{
 Model0_u32 Model0_holes;

 Model0_holes = ({ typeof(Model0_tp->Model0_lost_out) Model0__max1 = (Model0_tp->Model0_lost_out); typeof(1U) Model0__max2 = (1U); (void) (&Model0__max1 == &Model0__max2); Model0__max1 > Model0__max2 ? Model0__max1 : Model0__max2; });
 Model0_holes = ({ typeof(Model0_holes) Model0__min1 = (Model0_holes); typeof(Model0_tp->Model0_packets_out) Model0__min2 = (Model0_tp->Model0_packets_out); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });

 if ((Model0_tp->Model0_sacked_out + Model0_holes) > Model0_tp->Model0_packets_out) {
  Model0_tp->Model0_sacked_out = Model0_tp->Model0_packets_out - Model0_holes;
  return true;
 }
 return false;
}

/* If we receive more dupacks than we expected counting segments
 * in assumption of absent reordering, interpret this as reordering.
 * The only another reason could be bug in receiver TCP.
 */
static void Model0_tcp_check_reno_reordering(struct Model0_sock *Model0_sk, const int Model0_addend)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 if (Model0_tcp_limit_reno_sacked(Model0_tp))
  Model0_tcp_update_reordering(Model0_sk, Model0_tp->Model0_packets_out + Model0_addend, 0);
}

/* Emulate SACKs for SACKless connection: account for a new dupack. */

static void Model0_tcp_add_reno_sack(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 Model0_u32 Model0_prior_sacked = Model0_tp->Model0_sacked_out;

 Model0_tp->Model0_sacked_out++;
 Model0_tcp_check_reno_reordering(Model0_sk, 0);
 if (Model0_tp->Model0_sacked_out > Model0_prior_sacked)
  Model0_tp->Model0_delivered++; /* Some out-of-order packet is delivered */
 ({ int Model0___ret_warn_on = !!(Model0_tcp_left_out(Model0_tp) > Model0_tp->Model0_packets_out); __builtin_expect(!!(Model0___ret_warn_on), 0); });
}

/* Account for ACK, ACKing some data in Reno Recovery phase. */

static void Model0_tcp_remove_reno_sacks(struct Model0_sock *Model0_sk, int Model0_acked)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 if (Model0_acked > 0) {
  /* One ACK acked hole. The rest eat duplicate ACKs. */
  Model0_tp->Model0_delivered += ({ int Model0___max1 = (Model0_acked - Model0_tp->Model0_sacked_out); int Model0___max2 = (1); Model0___max1 > Model0___max2 ? Model0___max1: Model0___max2; });
  if (Model0_acked - 1 >= Model0_tp->Model0_sacked_out)
   Model0_tp->Model0_sacked_out = 0;
  else
   Model0_tp->Model0_sacked_out -= Model0_acked - 1;
 }
 Model0_tcp_check_reno_reordering(Model0_sk, Model0_acked);
 ({ int Model0___ret_warn_on = !!(Model0_tcp_left_out(Model0_tp) > Model0_tp->Model0_packets_out); __builtin_expect(!!(Model0___ret_warn_on), 0); });
}

static inline __attribute__((no_instrument_function)) void Model0_tcp_reset_reno_sack(struct Model0_tcp_sock *Model0_tp)
{
 Model0_tp->Model0_sacked_out = 0;
}

void Model0_tcp_clear_retrans(struct Model0_tcp_sock *Model0_tp)
{
 Model0_tp->Model0_retrans_out = 0;
 Model0_tp->Model0_lost_out = 0;
 Model0_tp->Model0_undo_marker = 0;
 Model0_tp->Model0_undo_retrans = -1;
 Model0_tp->Model0_fackets_out = 0;
 Model0_tp->Model0_sacked_out = 0;
}

static inline __attribute__((no_instrument_function)) void Model0_tcp_init_undo(struct Model0_tcp_sock *Model0_tp)
{
 Model0_tp->Model0_undo_marker = Model0_tp->Model0_snd_una;
 /* Retransmission still in flight may cause DSACKs later. */
 Model0_tp->Model0_undo_retrans = Model0_tp->Model0_retrans_out ? : -1;
}

/* Enter Loss state. If we detect SACK reneging, forget all SACK information
 * and reset tags completely, otherwise preserve SACKs. If receiver
 * dropped its ofo queue, we will know this due to reneging detection.
 */
void Model0_tcp_enter_loss(struct Model0_sock *Model0_sk)
{
 const struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_net *Model0_net = Model0_sock_net(Model0_sk);
 struct Model0_sk_buff *Model0_skb;
 bool Model0_new_recovery = Model0_icsk->Model0_icsk_ca_state < Model0_TCP_CA_Recovery;
 bool Model0_is_reneg; /* is receiver reneging on SACKs? */

 /* Reduce ssthresh if it has not yet been made inside this window. */
 if (Model0_icsk->Model0_icsk_ca_state <= Model0_TCP_CA_Disorder ||
     !Model0_before(Model0_tp->Model0_snd_una, Model0_tp->Model0_high_seq) ||
     (Model0_icsk->Model0_icsk_ca_state == Model0_TCP_CA_Loss && !Model0_icsk->Model0_icsk_retransmits)) {
  Model0_tp->Model0_prior_ssthresh = Model0_tcp_current_ssthresh(Model0_sk);
#if CY_ABSTRACT7
  Model0_tp->Model0_snd_ssthresh = Model0_tcp_reno_ssthresh(Model0_sk); //this function won't be called
#else
  Model0_tp->Model0_snd_ssthresh = Model0_icsk->Model0_icsk_ca_ops->Model0_ssthresh(Model0_sk);
#endif
  Model0_tcp_ca_event(Model0_sk, Model0_CA_EVENT_LOSS);
  Model0_tcp_init_undo(Model0_tp);
 }
 Model0_tp->Model0_snd_cwnd = 1;
 Model0_tp->Model0_snd_cwnd_cnt = 0;
 Model0_tp->Model0_snd_cwnd_stamp = ((__u32)(Model0_jiffies));

 Model0_tp->Model0_retrans_out = 0;
 Model0_tp->Model0_lost_out = 0;

 if (Model0_tcp_is_reno(Model0_tp))
  Model0_tcp_reset_reno_sack(Model0_tp);

 Model0_skb = Model0_tcp_write_queue_head(Model0_sk);
 Model0_is_reneg = Model0_skb && (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked & 0x01);
 if (Model0_is_reneg) {
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPSACKRENEGING] += 1);
  Model0_tp->Model0_sacked_out = 0;
  Model0_tp->Model0_fackets_out = 0;
 }
 Model0_tcp_clear_all_retrans_hints(Model0_tp);

 for (Model0_skb = (&(Model0_sk)->Model0_sk_write_queue)->Model0_next; Model0_skb != (struct Model0_sk_buff *)(&(Model0_sk)->Model0_sk_write_queue); Model0_skb = Model0_skb->Model0_next) {
  if (Model0_skb == Model0_tcp_send_head(Model0_sk))
   break;

  ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked &= (~0x07)|0x01;
  if (!(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked&0x01) || Model0_is_reneg) {
   ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked &= ~0x01;
   ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked |= 0x04;
   Model0_tp->Model0_lost_out += Model0_tcp_skb_pcount(Model0_skb);
   Model0_tp->Model0_retransmit_high = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq;
  }
 }
 ({ int Model0___ret_warn_on = !!(Model0_tcp_left_out(Model0_tp) > Model0_tp->Model0_packets_out); __builtin_expect(!!(Model0___ret_warn_on), 0); });

 /* Timeout in disordered state after receiving substantial DUPACKs
	 * suggests that the degree of reordering is over-estimated.
	 */
 if (Model0_icsk->Model0_icsk_ca_state <= Model0_TCP_CA_Disorder &&
     Model0_tp->Model0_sacked_out >= Model0_net->Model0_ipv4.Model0_sysctl_tcp_reordering)
  Model0_tp->Model0_reordering = ({ unsigned int Model0___min1 = (Model0_tp->Model0_reordering); unsigned int Model0___min2 = (Model0_net->Model0_ipv4.Model0_sysctl_tcp_reordering); Model0___min1 < Model0___min2 ? Model0___min1: Model0___min2; });

 Model0_tcp_set_ca_state(Model0_sk, Model0_TCP_CA_Loss);
 Model0_tp->Model0_high_seq = Model0_tp->Model0_snd_nxt;
 Model0_tcp_ecn_queue_cwr(Model0_tp);

 /* F-RTO RFC5682 sec 3.1 step 1: retransmit SND.UNA if no previous
	 * loss recovery is underway except recurring timeout(s) on
	 * the same SND.UNA (sec 3.2). Disable F-RTO on path MTU probing
	 */
 Model0_tp->Model0_frto = Model0_sysctl_tcp_frto &&
     (Model0_new_recovery || Model0_icsk->Model0_icsk_retransmits) &&
     !Model0_inet_csk(Model0_sk)->Model0_icsk_mtup.Model0_probe_size;
}

/* If ACK arrived pointing to a remembered SACK, it means that our
 * remembered SACKs do not reflect real state of receiver i.e.
 * receiver _host_ is heavily congested (or buggy).
 *
 * To avoid big spurious retransmission bursts due to transient SACK
 * scoreboard oddities that look like reneging, we give the receiver a
 * little time (max(RTT/2, 10ms)) to send us some more ACKs that will
 * restore sanity to the SACK scoreboard. If the apparent reneging
 * persists until this RTO then we'll clear the SACK scoreboard.
 */
static bool Model0_tcp_check_sack_reneging(struct Model0_sock *Model0_sk, int Model0_flag)
{
 if (Model0_flag & 0x2000) {
  struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
  unsigned long Model0_delay = ({ typeof(Model0_usecs_to_jiffies(Model0_tp->Model0_srtt_us >> 4)) Model0__max1 = (Model0_usecs_to_jiffies(Model0_tp->Model0_srtt_us >> 4)); typeof(Model0_msecs_to_jiffies(10)) Model0__max2 = (Model0_msecs_to_jiffies(10)); (void) (&Model0__max1 == &Model0__max2); Model0__max1 > Model0__max2 ? Model0__max1 : Model0__max2; });


  Model0_inet_csk_reset_xmit_timer(Model0_sk, 1,
       Model0_delay, ((unsigned)(120*1000)));
  return true;
 }
 return false;
}

static inline __attribute__((no_instrument_function)) int Model0_tcp_fackets_out(const struct Model0_tcp_sock *Model0_tp)
{
 return Model0_tcp_is_reno(Model0_tp) ? Model0_tp->Model0_sacked_out + 1 : Model0_tp->Model0_fackets_out;
}

/* Heurestics to calculate number of duplicate ACKs. There's no dupACKs
 * counter when SACK is enabled (without SACK, sacked_out is used for
 * that purpose).
 *
 * Instead, with FACK TCP uses fackets_out that includes both SACKed
 * segments up to the highest received SACK block so far and holes in
 * between them.
 *
 * With reordering, holes may still be in flight, so RFC3517 recovery
 * uses pure sacked_out (total number of SACKed segments) even though
 * it violates the RFC that uses duplicate ACKs, often these are equal
 * but when e.g. out-of-window ACKs or packet duplication occurs,
 * they differ. Since neither occurs due to loss, TCP should really
 * ignore them.
 */
static inline __attribute__((no_instrument_function)) int Model0_tcp_dupack_heuristics(const struct Model0_tcp_sock *Model0_tp)
{
 return Model0_tcp_is_fack(Model0_tp) ? Model0_tp->Model0_fackets_out : Model0_tp->Model0_sacked_out + 1;
}

static bool Model0_tcp_pause_early_retransmit(struct Model0_sock *Model0_sk, int Model0_flag)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 unsigned long Model0_delay;

 /* Delay early retransmit and entering fast recovery for
	 * max(RTT/4, 2msec) unless ack has ECE mark, no RTT samples
	 * available, or RTO is scheduled to fire first.
	 */
 if (Model0_sysctl_tcp_early_retrans < 2 || Model0_sysctl_tcp_early_retrans > 3 ||
     (Model0_flag & 0x40) || !Model0_tp->Model0_srtt_us)
  return false;

 Model0_delay = ({ typeof(Model0_usecs_to_jiffies(Model0_tp->Model0_srtt_us >> 5)) Model0__max1 = (Model0_usecs_to_jiffies(Model0_tp->Model0_srtt_us >> 5)); typeof(Model0_msecs_to_jiffies(2)) Model0__max2 = (Model0_msecs_to_jiffies(2)); (void) (&Model0__max1 == &Model0__max2); Model0__max1 > Model0__max2 ? Model0__max1 : Model0__max2; });


 if (!(({ unsigned long Model0___dummy; typeof(Model0_inet_csk(Model0_sk)->Model0_icsk_timeout) Model0___dummy2; (void)(&Model0___dummy == &Model0___dummy2); 1; }) && ({ unsigned long Model0___dummy; typeof((Model0_jiffies + Model0_delay)) Model0___dummy2; (void)(&Model0___dummy == &Model0___dummy2); 1; }) && ((long)(((Model0_jiffies + Model0_delay)) - (Model0_inet_csk(Model0_sk)->Model0_icsk_timeout)) < 0)))
  return false;

 Model0_inet_csk_reset_xmit_timer(Model0_sk, 4, Model0_delay,
      ((unsigned)(120*1000)));
 return true;
}

/* Linux NewReno/SACK/FACK/ECN state machine.
 * --------------------------------------
 *
 * "Open"	Normal state, no dubious events, fast path.
 * "Disorder"   In all the respects it is "Open",
 *		but requires a bit more attention. It is entered when
 *		we see some SACKs or dupacks. It is split of "Open"
 *		mainly to move some processing from fast path to slow one.
 * "CWR"	CWND was reduced due to some Congestion Notification event.
 *		It can be ECN, ICMP source quench, local device congestion.
 * "Recovery"	CWND was reduced, we are fast-retransmitting.
 * "Loss"	CWND was reduced due to RTO timeout or SACK reneging.
 *
 * tcp_fastretrans_alert() is entered:
 * - each incoming ACK, if state is not "Open"
 * - when arrived ACK is unusual, namely:
 *	* SACK
 *	* Duplicate ACK.
 *	* ECN ECE.
 *
 * Counting packets in flight is pretty simple.
 *
 *	in_flight = packets_out - left_out + retrans_out
 *
 *	packets_out is SND.NXT-SND.UNA counted in packets.
 *
 *	retrans_out is number of retransmitted segments.
 *
 *	left_out is number of segments left network, but not ACKed yet.
 *
 *		left_out = sacked_out + lost_out
 *
 *     sacked_out: Packets, which arrived to receiver out of order
 *		   and hence not ACKed. With SACKs this number is simply
 *		   amount of SACKed data. Even without SACKs
 *		   it is easy to give pretty reliable estimate of this number,
 *		   counting duplicate ACKs.
 *
 *       lost_out: Packets lost by network. TCP has no explicit
 *		   "loss notification" feedback from network (for now).
 *		   It means that this number can be only _guessed_.
 *		   Actually, it is the heuristics to predict lossage that
 *		   distinguishes different algorithms.
 *
 *	F.e. after RTO, when all the queue is considered as lost,
 *	lost_out = packets_out and in_flight = retrans_out.
 *
 *		Essentially, we have now two algorithms counting
 *		lost packets.
 *
 *		FACK: It is the simplest heuristics. As soon as we decided
 *		that something is lost, we decide that _all_ not SACKed
 *		packets until the most forward SACK are lost. I.e.
 *		lost_out = fackets_out - sacked_out and left_out = fackets_out.
 *		It is absolutely correct estimate, if network does not reorder
 *		packets. And it loses any connection to reality when reordering
 *		takes place. We use FACK by default until reordering
 *		is suspected on the path to this destination.
 *
 *		NewReno: when Recovery is entered, we assume that one segment
 *		is lost (classic Reno). While we are in Recovery and
 *		a partial ACK arrives, we assume that one more packet
 *		is lost (NewReno). This heuristics are the same in NewReno
 *		and SACK.
 *
 *  Imagine, that's all! Forget about all this shamanism about CWND inflation
 *  deflation etc. CWND is real congestion window, never inflated, changes
 *  only according to classic VJ rules.
 *
 * Really tricky (and requiring careful tuning) part of algorithm
 * is hidden in functions tcp_time_to_recover() and tcp_xmit_retransmit_queue().
 * The first determines the moment _when_ we should reduce CWND and,
 * hence, slow down forward transmission. In fact, it determines the moment
 * when we decide that hole is caused by loss, rather than by a reorder.
 *
 * tcp_xmit_retransmit_queue() decides, _what_ we should retransmit to fill
 * holes, caused by lost packets.
 *
 * And the most logically complicated part of algorithm is undo
 * heuristics. We detect false retransmits due to both too early
 * fast retransmit (reordering) and underestimated RTO, analyzing
 * timestamps and D-SACKs. When we detect that some segments were
 * retransmitted by mistake and CWND reduction was wrong, we undo
 * window reduction and abort recovery phase. This logic is hidden
 * inside several functions named tcp_try_undo_<something>.
 */

/* This function decides, when we should leave Disordered state
 * and enter Recovery phase, reducing congestion window.
 *
 * Main question: may we further continue forward transmission
 * with the same cwnd?
 */
static bool Model0_tcp_time_to_recover(struct Model0_sock *Model0_sk, int Model0_flag)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 __u32 Model0_packets_out;
 int Model0_tcp_reordering = Model0_sock_net(Model0_sk)->Model0_ipv4.Model0_sysctl_tcp_reordering;

 /* Trick#1: The loss is proven. */
 if (Model0_tp->Model0_lost_out)
  return true;

 /* Not-A-Trick#2 : Classic rule... */
 if (Model0_tcp_dupack_heuristics(Model0_tp) > Model0_tp->Model0_reordering)
  return true;

 /* Trick#4: It is still not OK... But will it be useful to delay
	 * recovery more?
	 */
 Model0_packets_out = Model0_tp->Model0_packets_out;
 if (Model0_packets_out <= Model0_tp->Model0_reordering &&
     Model0_tp->Model0_sacked_out >= ({ __u32 Model0___max1 = (Model0_packets_out/2); __u32 Model0___max2 = (Model0_tcp_reordering); Model0___max1 > Model0___max2 ? Model0___max1: Model0___max2; }) &&
     !Model0_tcp_may_send_now(Model0_sk)) {
  /* We have nothing to send. This connection is limited
		 * either by receiver window or by application.
		 */
  return true;
 }

 /* If a thin stream is detected, retransmit after first
	 * received dupack. Employ only if SACK is supported in order
	 * to avoid possible corner-case series of spurious retransmissions
	 * Use only if there are no unsent data.
	 */
 if ((Model0_tp->Model0_thin_dupack || Model0_sysctl_tcp_thin_dupack) &&
     Model0_tcp_stream_is_thin(Model0_tp) && Model0_tcp_dupack_heuristics(Model0_tp) > 1 &&
     Model0_tcp_is_sack(Model0_tp) && !Model0_tcp_send_head(Model0_sk))
  return true;

 /* Trick#6: TCP early retransmit, per RFC5827.  To avoid spurious
	 * retransmissions due to small network reorderings, we implement
	 * Mitigation A.3 in the RFC and delay the retransmission for a short
	 * interval if appropriate.
	 */
 if (Model0_tp->Model0_do_early_retrans && !Model0_tp->Model0_retrans_out && Model0_tp->Model0_sacked_out &&
     (Model0_tp->Model0_packets_out >= (Model0_tp->Model0_sacked_out + 1) && Model0_tp->Model0_packets_out < 4) &&
     !Model0_tcp_may_send_now(Model0_sk))
  return !Model0_tcp_pause_early_retransmit(Model0_sk, Model0_flag);

 return false;
}

/* Detect loss in event "A" above by marking head of queue up as lost.
 * For FACK or non-SACK(Reno) senders, the first "packets" number of segments
 * are considered lost. For RFC3517 SACK, a segment is considered lost if it
 * has at least tp->reordering SACKed seqments above it; "packets" refers to
 * the maximum SACKed segments to pass before reaching this limit.
 */
static void Model0_tcp_mark_head_lost(struct Model0_sock *Model0_sk, int Model0_packets, int Model0_mark_head)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_sk_buff *Model0_skb;
 int Model0_cnt, Model0_oldcnt, Model0_lost;
 unsigned int Model0_mss;
 /* Use SACK to deduce losses of new sequences sent during recovery */
 const Model0_u32 Model0_loss_high = Model0_tcp_is_sack(Model0_tp) ? Model0_tp->Model0_snd_nxt : Model0_tp->Model0_high_seq;

 ({ int Model0___ret_warn_on = !!(Model0_packets > Model0_tp->Model0_packets_out); __builtin_expect(!!(Model0___ret_warn_on), 0); });
 if (Model0_tp->Model0_lost_skb_hint) {
  Model0_skb = Model0_tp->Model0_lost_skb_hint;
  Model0_cnt = Model0_tp->Model0_lost_cnt_hint;
  /* Head already handled? */
  if (Model0_mark_head && Model0_skb != Model0_tcp_write_queue_head(Model0_sk))
   return;
 } else {
  Model0_skb = Model0_tcp_write_queue_head(Model0_sk);
  Model0_cnt = 0;
 }

 for (; Model0_skb != (struct Model0_sk_buff *)(&(Model0_sk)->Model0_sk_write_queue); Model0_skb = Model0_skb->Model0_next) {
  if (Model0_skb == Model0_tcp_send_head(Model0_sk))
   break;
  /* TODO: do this better */
  /* this is not the most efficient way to do this... */
  Model0_tp->Model0_lost_skb_hint = Model0_skb;
  Model0_tp->Model0_lost_cnt_hint = Model0_cnt;

  if (Model0_before(Model0_loss_high, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq))
   break;

  Model0_oldcnt = Model0_cnt;
  if (Model0_tcp_is_fack(Model0_tp) || Model0_tcp_is_reno(Model0_tp) ||
      (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked & 0x01))
   Model0_cnt += Model0_tcp_skb_pcount(Model0_skb);

  if (Model0_cnt > Model0_packets) {
   if ((Model0_tcp_is_sack(Model0_tp) && !Model0_tcp_is_fack(Model0_tp)) ||
       (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked & 0x01) ||
       (Model0_oldcnt >= Model0_packets))
    break;

   Model0_mss = Model0_tcp_skb_mss(Model0_skb);
   /* If needed, chop off the prefix to mark as lost. */
   Model0_lost = (Model0_packets - Model0_oldcnt) * Model0_mss;
   if (Model0_lost < Model0_skb->Model0_len &&
       Model0_tcp_fragment(Model0_sk, Model0_skb, Model0_lost, Model0_mss, ((( Model0_gfp_t)0x20u)|(( Model0_gfp_t)0x80000u)|(( Model0_gfp_t)0x2000000u))) < 0)
    break;
   Model0_cnt = Model0_packets;
  }

  Model0_tcp_skb_mark_lost(Model0_tp, Model0_skb);

  if (Model0_mark_head)
   break;
 }
 ({ int Model0___ret_warn_on = !!(Model0_tcp_left_out(Model0_tp) > Model0_tp->Model0_packets_out); __builtin_expect(!!(Model0___ret_warn_on), 0); });
}

/* Account newly detected lost packet(s) */

static void Model0_tcp_update_scoreboard(struct Model0_sock *Model0_sk, int Model0_fast_rexmit)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 if (Model0_tcp_is_reno(Model0_tp)) {
  Model0_tcp_mark_head_lost(Model0_sk, 1, 1);
 } else if (Model0_tcp_is_fack(Model0_tp)) {
  int Model0_lost = Model0_tp->Model0_fackets_out - Model0_tp->Model0_reordering;
  if (Model0_lost <= 0)
   Model0_lost = 1;
  Model0_tcp_mark_head_lost(Model0_sk, Model0_lost, 0);
 } else {
  int Model0_sacked_upto = Model0_tp->Model0_sacked_out - Model0_tp->Model0_reordering;
  if (Model0_sacked_upto >= 0)
   Model0_tcp_mark_head_lost(Model0_sk, Model0_sacked_upto, 0);
  else if (Model0_fast_rexmit)
   Model0_tcp_mark_head_lost(Model0_sk, 1, 1);
 }
}

static bool Model0_tcp_tsopt_ecr_before(const struct Model0_tcp_sock *Model0_tp, Model0_u32 Model0_when)
{
 return Model0_tp->Model0_rx_opt.Model0_saw_tstamp && Model0_tp->Model0_rx_opt.Model0_rcv_tsecr &&
        Model0_before(Model0_tp->Model0_rx_opt.Model0_rcv_tsecr, Model0_when);
}

/* skb is spurious retransmitted if the returned timestamp echo
 * reply is prior to the skb transmission time
 */
static bool Model0_tcp_skb_spurious_retrans(const struct Model0_tcp_sock *Model0_tp,
         const struct Model0_sk_buff *Model0_skb)
{
 return (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked & (0x02|0x80| 0x10)) &&
        Model0_tcp_tsopt_ecr_before(Model0_tp, Model0_tcp_skb_timestamp(Model0_skb));
}

/* Nothing was retransmitted or returned timestamp is less
 * than timestamp of the first retransmission.
 */
static inline __attribute__((no_instrument_function)) bool Model0_tcp_packet_delayed(const struct Model0_tcp_sock *Model0_tp)
{
 return !Model0_tp->Model0_retrans_stamp ||
        Model0_tcp_tsopt_ecr_before(Model0_tp, Model0_tp->Model0_retrans_stamp);
}

/* Undo procedures. */

/* We can clear retrans_stamp when there are no retransmissions in the
 * window. It would seem that it is trivially available for us in
 * tp->retrans_out, however, that kind of assumptions doesn't consider
 * what will happen if errors occur when sending retransmission for the
 * second time. ...It could the that such segment has only
 * TCPCB_EVER_RETRANS set at the present time. It seems that checking
 * the head skb is enough except for some reneging corner cases that
 * are not worth the effort.
 *
 * Main reason for all this complexity is the fact that connection dying
 * time now depends on the validity of the retrans_stamp, in particular,
 * that successive retransmissions of a segment must not advance
 * retrans_stamp under any conditions.
 */
static bool Model0_tcp_any_retrans_done(const struct Model0_sock *Model0_sk)
{
 const struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_sk_buff *Model0_skb;

 if (Model0_tp->Model0_retrans_out)
  return true;

 Model0_skb = Model0_tcp_write_queue_head(Model0_sk);
 if (__builtin_expect(!!(Model0_skb && ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked & 0x80), 0))
  return true;

 return false;
}
static void Model0_tcp_undo_cwnd_reduction(struct Model0_sock *Model0_sk, bool Model0_unmark_loss)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 if (Model0_unmark_loss) {
  struct Model0_sk_buff *Model0_skb;

  for (Model0_skb = (&(Model0_sk)->Model0_sk_write_queue)->Model0_next; Model0_skb != (struct Model0_sk_buff *)(&(Model0_sk)->Model0_sk_write_queue); Model0_skb = Model0_skb->Model0_next) {
   if (Model0_skb == Model0_tcp_send_head(Model0_sk))
    break;
   ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked &= ~0x04;
  }
  Model0_tp->Model0_lost_out = 0;
  Model0_tcp_clear_all_retrans_hints(Model0_tp);
 }

 if (Model0_tp->Model0_prior_ssthresh) {
  const struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);

  if (Model0_icsk->Model0_icsk_ca_ops->Model0_undo_cwnd)
   Model0_tp->Model0_snd_cwnd = Model0_icsk->Model0_icsk_ca_ops->Model0_undo_cwnd(Model0_sk);
  else
   Model0_tp->Model0_snd_cwnd = ({ typeof(Model0_tp->Model0_snd_cwnd) Model0__max1 = (Model0_tp->Model0_snd_cwnd); typeof(Model0_tp->Model0_snd_ssthresh << 1) Model0__max2 = (Model0_tp->Model0_snd_ssthresh << 1); (void) (&Model0__max1 == &Model0__max2); Model0__max1 > Model0__max2 ? Model0__max1 : Model0__max2; });

  if (Model0_tp->Model0_prior_ssthresh > Model0_tp->Model0_snd_ssthresh) {
   Model0_tp->Model0_snd_ssthresh = Model0_tp->Model0_prior_ssthresh;
   Model0_tcp_ecn_withdraw_cwr(Model0_tp);
  }
 }
 Model0_tp->Model0_snd_cwnd_stamp = ((__u32)(Model0_jiffies));
 Model0_tp->Model0_undo_marker = 0;
}

static inline __attribute__((no_instrument_function)) bool Model0_tcp_may_undo(const struct Model0_tcp_sock *Model0_tp)
{
 return Model0_tp->Model0_undo_marker && (!Model0_tp->Model0_undo_retrans || Model0_tcp_packet_delayed(Model0_tp));
}

/* People celebrate: "We love our President!" */
static bool Model0_tcp_try_undo_recovery(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 if (Model0_tcp_may_undo(Model0_tp)) {
  int Model0_mib_idx;

  /* Happy end! We did not retransmit anything
		 * or our original transmission succeeded.
		 */
  do { } while (0);
  Model0_tcp_undo_cwnd_reduction(Model0_sk, false);
  if (Model0_inet_csk(Model0_sk)->Model0_icsk_ca_state == Model0_TCP_CA_Loss)
   Model0_mib_idx = Model0_LINUX_MIB_TCPLOSSUNDO;
  else
   Model0_mib_idx = Model0_LINUX_MIB_TCPFULLUNDO;

  (Model0_cy_linux_mib.Model0_mibs[Model0_mib_idx] += 1);
 }
 if (Model0_tp->Model0_snd_una == Model0_tp->Model0_high_seq && Model0_tcp_is_reno(Model0_tp)) {
  /* Hold old state until something *above* high_seq
		 * is ACKed. For Reno it is MUST to prevent false
		 * fast retransmits (RFC2582). SACK TCP is safe. */
  if (!Model0_tcp_any_retrans_done(Model0_sk))
   Model0_tp->Model0_retrans_stamp = 0;
  return true;
 }
 Model0_tcp_set_ca_state(Model0_sk, Model0_TCP_CA_Open);
 return false;
}

/* Try to undo cwnd reduction, because D-SACKs acked all retransmitted data */
static bool Model0_tcp_try_undo_dsack(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 if (Model0_tp->Model0_undo_marker && !Model0_tp->Model0_undo_retrans) {
  do { } while (0);
  Model0_tcp_undo_cwnd_reduction(Model0_sk, false);
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPDSACKUNDO] += 1);
  return true;
 }
 return false;
}

/* Undo during loss recovery after partial ACK or using F-RTO. */
static bool Model0_tcp_try_undo_loss(struct Model0_sock *Model0_sk, bool Model0_frto_undo)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 if (Model0_frto_undo || Model0_tcp_may_undo(Model0_tp)) {
  Model0_tcp_undo_cwnd_reduction(Model0_sk, true);

  do { } while (0);
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPLOSSUNDO] += 1);
  if (Model0_frto_undo)
   (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPSPURIOUSRTOS] += 1);

  Model0_inet_csk(Model0_sk)->Model0_icsk_retransmits = 0;
  if (Model0_frto_undo || Model0_tcp_is_sack(Model0_tp))
   Model0_tcp_set_ca_state(Model0_sk, Model0_TCP_CA_Open);
  return true;
 }
 return false;
}

/* The cwnd reduction in CWR and Recovery uses the PRR algorithm in RFC 6937.
 * It computes the number of packets to send (sndcnt) based on packets newly
 * delivered:
 *   1) If the packets in flight is larger than ssthresh, PRR spreads the
 *	cwnd reductions across a full RTT.
 *   2) Otherwise PRR uses packet conservation to send as much as delivered.
 *      But when the retransmits are acked without further losses, PRR
 *      slow starts cwnd up to ssthresh to speed up the recovery.
 */
static void Model0_tcp_init_cwnd_reduction(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 Model0_tp->Model0_high_seq = Model0_tp->Model0_snd_nxt;
 Model0_tp->Model0_tlp_high_seq = 0;
 Model0_tp->Model0_snd_cwnd_cnt = 0;
 Model0_tp->Model0_prior_cwnd = Model0_tp->Model0_snd_cwnd;
 Model0_tp->Model0_prr_delivered = 0;
 Model0_tp->Model0_prr_out = 0;
#if CY_ABSTRACT7
  Model0_tp->Model0_snd_ssthresh = Model0_tcp_reno_ssthresh(Model0_sk); //this function won't be called
#else
 Model0_tp->Model0_snd_ssthresh = Model0_inet_csk(Model0_sk)->Model0_icsk_ca_ops->Model0_ssthresh(Model0_sk);
#endif
 Model0_tcp_ecn_queue_cwr(Model0_tp);
}

static void Model0_tcp_cwnd_reduction(struct Model0_sock *Model0_sk, int Model0_newly_acked_sacked,
          int Model0_flag)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 int Model0_sndcnt = 0;
 int Model0_delta = Model0_tp->Model0_snd_ssthresh - Model0_tcp_packets_in_flight(Model0_tp);

 if (Model0_newly_acked_sacked <= 0 || ({ int Model0___ret_warn_on = !!(!Model0_tp->Model0_prior_cwnd); __builtin_expect(!!(Model0___ret_warn_on), 0); }))
  return;

 Model0_tp->Model0_prr_delivered += Model0_newly_acked_sacked;
 if (Model0_delta < 0) {
  Model0_u64 Model0_dividend = (Model0_u64)Model0_tp->Model0_snd_ssthresh * Model0_tp->Model0_prr_delivered +
          Model0_tp->Model0_prior_cwnd - 1;
  Model0_sndcnt = Model0_div_u64(Model0_dividend, Model0_tp->Model0_prior_cwnd) - Model0_tp->Model0_prr_out;
 } else if ((Model0_flag & 0x08) &&
     !(Model0_flag & 0x80)) {
  Model0_sndcnt = ({ int Model0___min1 = (Model0_delta); int Model0___min2 = (({ int Model0___max1 = (Model0_tp->Model0_prr_delivered - Model0_tp->Model0_prr_out); int Model0___max2 = (Model0_newly_acked_sacked); Model0___max1 > Model0___max2 ? Model0___max1: Model0___max2; }) + 1); Model0___min1 < Model0___min2 ? Model0___min1: Model0___min2; });


 } else {
  Model0_sndcnt = ({ typeof(Model0_delta) Model0__min1 = (Model0_delta); typeof(Model0_newly_acked_sacked) Model0__min2 = (Model0_newly_acked_sacked); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
 }
 /* Force a fast retransmit upon entering fast recovery */
 Model0_sndcnt = ({ typeof(Model0_sndcnt) Model0__max1 = (Model0_sndcnt); typeof((Model0_tp->Model0_prr_out ? 0 : 1)) Model0__max2 = ((Model0_tp->Model0_prr_out ? 0 : 1)); (void) (&Model0__max1 == &Model0__max2); Model0__max1 > Model0__max2 ? Model0__max1 : Model0__max2; });
 Model0_tp->Model0_snd_cwnd = Model0_tcp_packets_in_flight(Model0_tp) + Model0_sndcnt;
}

static inline __attribute__((no_instrument_function)) void Model0_tcp_end_cwnd_reduction(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 /* Reset cwnd to ssthresh in CWR or Recovery (unless it's undone) */
 if (Model0_inet_csk(Model0_sk)->Model0_icsk_ca_state == Model0_TCP_CA_CWR ||
     (Model0_tp->Model0_undo_marker && Model0_tp->Model0_snd_ssthresh < 0x7fffffff)) {
  Model0_tp->Model0_snd_cwnd = Model0_tp->Model0_snd_ssthresh;
  Model0_tp->Model0_snd_cwnd_stamp = ((__u32)(Model0_jiffies));
 }
 Model0_tcp_ca_event(Model0_sk, Model0_CA_EVENT_COMPLETE_CWR);
}

/* Enter CWR state. Disable cwnd undo since congestion is proven with ECN */
void Model0_tcp_enter_cwr(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 Model0_tp->Model0_prior_ssthresh = 0;
 if (Model0_inet_csk(Model0_sk)->Model0_icsk_ca_state < Model0_TCP_CA_CWR) {
  Model0_tp->Model0_undo_marker = 0;
  Model0_tcp_init_cwnd_reduction(Model0_sk);
  Model0_tcp_set_ca_state(Model0_sk, Model0_TCP_CA_CWR);
 }
}
                            ;

static void Model0_tcp_try_keep_open(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 int Model0_state = Model0_TCP_CA_Open;

 if (Model0_tcp_left_out(Model0_tp) || Model0_tcp_any_retrans_done(Model0_sk))
  Model0_state = Model0_TCP_CA_Disorder;

 if (Model0_inet_csk(Model0_sk)->Model0_icsk_ca_state != Model0_state) {
  Model0_tcp_set_ca_state(Model0_sk, Model0_state);
  Model0_tp->Model0_high_seq = Model0_tp->Model0_snd_nxt;
 }
}

static void Model0_tcp_try_to_open(struct Model0_sock *Model0_sk, int Model0_flag)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 ({ int Model0___ret_warn_on = !!(Model0_tcp_left_out(Model0_tp) > Model0_tp->Model0_packets_out); __builtin_expect(!!(Model0___ret_warn_on), 0); });

 if (!Model0_tcp_any_retrans_done(Model0_sk))
  Model0_tp->Model0_retrans_stamp = 0;

 if (Model0_flag & 0x40)
  Model0_tcp_enter_cwr(Model0_sk);

 if (Model0_inet_csk(Model0_sk)->Model0_icsk_ca_state != Model0_TCP_CA_CWR) {
  Model0_tcp_try_keep_open(Model0_sk);
 }
}

static void Model0_tcp_mtup_probe_failed(struct Model0_sock *Model0_sk)
{
 struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);

 Model0_icsk->Model0_icsk_mtup.Model0_search_high = Model0_icsk->Model0_icsk_mtup.Model0_probe_size - 1;
 Model0_icsk->Model0_icsk_mtup.Model0_probe_size = 0;
 (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPMTUPFAIL] += 1);
}

static void Model0_tcp_mtup_probe_success(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);

 /* FIXME: breaks with very large cwnd */
 Model0_tp->Model0_prior_ssthresh = Model0_tcp_current_ssthresh(Model0_sk);
 Model0_tp->Model0_snd_cwnd = Model0_tp->Model0_snd_cwnd *
         Model0_tcp_mss_to_mtu(Model0_sk, Model0_tp->Model0_mss_cache) /
         Model0_icsk->Model0_icsk_mtup.Model0_probe_size;
 Model0_tp->Model0_snd_cwnd_cnt = 0;
 Model0_tp->Model0_snd_cwnd_stamp = ((__u32)(Model0_jiffies));
 Model0_tp->Model0_snd_ssthresh = Model0_tcp_current_ssthresh(Model0_sk);

 Model0_icsk->Model0_icsk_mtup.Model0_search_low = Model0_icsk->Model0_icsk_mtup.Model0_probe_size;
 Model0_icsk->Model0_icsk_mtup.Model0_probe_size = 0;
 Model0_tcp_sync_mss(Model0_sk, Model0_icsk->Model0_icsk_pmtu_cookie);
 (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPMTUPSUCCESS] += 1);
}

/* Do a simple retransmit without using the backoff mechanisms in
 * tcp_timer. This is used for path mtu discovery.
 * The socket is already locked here.
 */
void Model0_tcp_simple_retransmit(struct Model0_sock *Model0_sk)
{
 const struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_sk_buff *Model0_skb;
 unsigned int Model0_mss = Model0_tcp_current_mss(Model0_sk);
 Model0_u32 Model0_prior_lost = Model0_tp->Model0_lost_out;

 for (Model0_skb = (&(Model0_sk)->Model0_sk_write_queue)->Model0_next; Model0_skb != (struct Model0_sk_buff *)(&(Model0_sk)->Model0_sk_write_queue); Model0_skb = Model0_skb->Model0_next) {
  if (Model0_skb == Model0_tcp_send_head(Model0_sk))
   break;
  if (Model0_tcp_skb_seglen(Model0_skb) > Model0_mss &&
      !(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked & 0x01)) {
   if (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked & 0x02) {
    ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked &= ~0x02;
    Model0_tp->Model0_retrans_out -= Model0_tcp_skb_pcount(Model0_skb);
   }
   Model0_tcp_skb_mark_lost_uncond_verify(Model0_tp, Model0_skb);
  }
 }

 Model0_tcp_clear_retrans_hints_partial(Model0_tp);

 if (Model0_prior_lost == Model0_tp->Model0_lost_out)
  return;

 if (Model0_tcp_is_reno(Model0_tp))
  Model0_tcp_limit_reno_sacked(Model0_tp);

 ({ int Model0___ret_warn_on = !!(Model0_tcp_left_out(Model0_tp) > Model0_tp->Model0_packets_out); __builtin_expect(!!(Model0___ret_warn_on), 0); });

 /* Don't muck with the congestion window here.
	 * Reason is that we do not increase amount of _data_
	 * in network, but units changed and effective
	 * cwnd/ssthresh really reduced now.
	 */
 if (Model0_icsk->Model0_icsk_ca_state != Model0_TCP_CA_Loss) {
  Model0_tp->Model0_high_seq = Model0_tp->Model0_snd_nxt;
  Model0_tp->Model0_snd_ssthresh = Model0_tcp_current_ssthresh(Model0_sk);
  Model0_tp->Model0_prior_ssthresh = 0;
  Model0_tp->Model0_undo_marker = 0;
  Model0_tcp_set_ca_state(Model0_sk, Model0_TCP_CA_Loss);
 }
 Model0_tcp_xmit_retransmit_queue(Model0_sk);
}
                                    ;

static void Model0_tcp_enter_recovery(struct Model0_sock *Model0_sk, bool Model0_ece_ack)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 int Model0_mib_idx;

 if (Model0_tcp_is_reno(Model0_tp))
  Model0_mib_idx = Model0_LINUX_MIB_TCPRENORECOVERY;
 else
  Model0_mib_idx = Model0_LINUX_MIB_TCPSACKRECOVERY;

 (Model0_cy_linux_mib.Model0_mibs[Model0_mib_idx] += 1);

 Model0_tp->Model0_prior_ssthresh = 0;
 Model0_tcp_init_undo(Model0_tp);

 if (!Model0_tcp_in_cwnd_reduction(Model0_sk)) {
  if (!Model0_ece_ack)
   Model0_tp->Model0_prior_ssthresh = Model0_tcp_current_ssthresh(Model0_sk);
  Model0_tcp_init_cwnd_reduction(Model0_sk);
 }
 Model0_tcp_set_ca_state(Model0_sk, Model0_TCP_CA_Recovery);
}

/* Process an ACK in CA_Loss state. Move to CA_Open if lost data are
 * recovered or spurious. Otherwise retransmits more on partial ACKs.
 */
static void Model0_tcp_process_loss(struct Model0_sock *Model0_sk, int Model0_flag, bool Model0_is_dupack,
        int *Model0_rexmit)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 bool Model0_recovered = !Model0_before(Model0_tp->Model0_snd_una, Model0_tp->Model0_high_seq);

 if ((Model0_flag & 0x400) &&
     Model0_tcp_try_undo_loss(Model0_sk, false))
  return;

 if (Model0_tp->Model0_frto) { /* F-RTO RFC5682 sec 3.1 (sack enhanced version). */
  /* Step 3.b. A timeout is spurious if not all data are
		 * lost, i.e., never-retransmitted data are (s)acked.
		 */
  if ((Model0_flag & 0x200) &&
      Model0_tcp_try_undo_loss(Model0_sk, true))
   return;

  if (Model0_before(Model0_tp->Model0_high_seq, Model0_tp->Model0_snd_nxt)) {
   if (Model0_flag & 0x20 || Model0_is_dupack)
    Model0_tp->Model0_frto = 0; /* Step 3.a. loss was real */
  } else if (Model0_flag & 0x400 && !Model0_recovered) {
   Model0_tp->Model0_high_seq = Model0_tp->Model0_snd_nxt;
   /* Step 2.b. Try send new data (but deferred until cwnd
			 * is updated in tcp_ack()). Otherwise fall back to
			 * the conventional recovery.
			 */
   if (Model0_tcp_send_head(Model0_sk) &&
       Model0_before(Model0_tp->Model0_snd_nxt, Model0_tcp_wnd_end(Model0_tp))) {
    *Model0_rexmit = 2;
    return;
   }
   Model0_tp->Model0_frto = 0;
  }
 }

 if (Model0_recovered) {
  /* F-RTO RFC5682 sec 3.1 step 2.a and 1st part of step 3.a */
  Model0_tcp_try_undo_recovery(Model0_sk);
  return;
 }
 if (Model0_tcp_is_reno(Model0_tp)) {
  /* A Reno DUPACK means new data in F-RTO step 2.b above are
		 * delivered. Lower inflight to clock out (re)tranmissions.
		 */
  if (Model0_before(Model0_tp->Model0_high_seq, Model0_tp->Model0_snd_nxt) && Model0_is_dupack)
   Model0_tcp_add_reno_sack(Model0_sk);
  else if (Model0_flag & 0x400)
   Model0_tcp_reset_reno_sack(Model0_tp);
 }
 *Model0_rexmit = 1;
}

/* Undo during fast recovery after partial ACK. */
static bool Model0_tcp_try_undo_partial(struct Model0_sock *Model0_sk, const int Model0_acked)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 if (Model0_tp->Model0_undo_marker && Model0_tcp_packet_delayed(Model0_tp)) {
  /* Plain luck! Hole if filled with delayed
		 * packet, rather than with a retransmit.
		 */
  Model0_tcp_update_reordering(Model0_sk, Model0_tcp_fackets_out(Model0_tp) + Model0_acked, 1);

  /* We are getting evidence that the reordering degree is higher
		 * than we realized. If there are no retransmits out then we
		 * can undo. Otherwise we clock out new packets but do not
		 * mark more packets lost or retransmit more.
		 */
  if (Model0_tp->Model0_retrans_out)
   return true;

  if (!Model0_tcp_any_retrans_done(Model0_sk))
   Model0_tp->Model0_retrans_stamp = 0;

  do { } while (0);
  Model0_tcp_undo_cwnd_reduction(Model0_sk, true);
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPPARTIALUNDO] += 1);
  Model0_tcp_try_keep_open(Model0_sk);
  return true;
 }
 return false;
}

/* Process an event, which can update packets-in-flight not trivially.
 * Main goal of this function is to calculate new estimate for left_out,
 * taking into account both packets sitting in receiver's buffer and
 * packets lost by network.
 *
 * Besides that it updates the congestion state when packet loss or ECN
 * is detected. But it does not reduce the cwnd, it is done by the
 * congestion control later.
 *
 * It does _not_ decide what to send, it is made in function
 * tcp_xmit_retransmit_queue().
 */
static void Model0_tcp_fastretrans_alert(struct Model0_sock *Model0_sk, const int Model0_acked,
      bool Model0_is_dupack, int *Model0_ack_flag, int *Model0_rexmit)
{
 struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 int Model0_fast_rexmit = 0, Model0_flag = *Model0_ack_flag;
 bool Model0_do_lost = Model0_is_dupack || ((Model0_flag & 0x20) &&
        (Model0_tcp_fackets_out(Model0_tp) > Model0_tp->Model0_reordering));

 if (({ int Model0___ret_warn_on = !!(!Model0_tp->Model0_packets_out && Model0_tp->Model0_sacked_out); __builtin_expect(!!(Model0___ret_warn_on), 0); }))
  Model0_tp->Model0_sacked_out = 0;
 if (({ int Model0___ret_warn_on = !!(!Model0_tp->Model0_sacked_out && Model0_tp->Model0_fackets_out); __builtin_expect(!!(Model0___ret_warn_on), 0); }))
  Model0_tp->Model0_fackets_out = 0;

 /* Now state machine starts.
	 * A. ECE, hence prohibit cwnd undoing, the reduction is required. */
 if (Model0_flag & 0x40)
  Model0_tp->Model0_prior_ssthresh = 0;

 /* B. In all the states check for reneging SACKs. */
 if (Model0_tcp_check_sack_reneging(Model0_sk, Model0_flag))
  return;

 /* C. Check consistency of the current state. */
 ({ int Model0___ret_warn_on = !!(Model0_tcp_left_out(Model0_tp) > Model0_tp->Model0_packets_out); __builtin_expect(!!(Model0___ret_warn_on), 0); });

 /* D. Check state exit conditions. State can be terminated
	 *    when high_seq is ACKed. */
 if (Model0_icsk->Model0_icsk_ca_state == Model0_TCP_CA_Open) {
  ({ int Model0___ret_warn_on = !!(Model0_tp->Model0_retrans_out != 0); __builtin_expect(!!(Model0___ret_warn_on), 0); });
  Model0_tp->Model0_retrans_stamp = 0;
 } else if (!Model0_before(Model0_tp->Model0_snd_una, Model0_tp->Model0_high_seq)) {
  switch (Model0_icsk->Model0_icsk_ca_state) {
  case Model0_TCP_CA_CWR:
   /* CWR is to be held something *above* high_seq
			 * is ACKed for CWR bit to reach receiver. */
   if (Model0_tp->Model0_snd_una != Model0_tp->Model0_high_seq) {
    Model0_tcp_end_cwnd_reduction(Model0_sk);
    Model0_tcp_set_ca_state(Model0_sk, Model0_TCP_CA_Open);
   }
   break;

  case Model0_TCP_CA_Recovery:
   if (Model0_tcp_is_reno(Model0_tp))
    Model0_tcp_reset_reno_sack(Model0_tp);
   if (Model0_tcp_try_undo_recovery(Model0_sk))
    return;
   Model0_tcp_end_cwnd_reduction(Model0_sk);
   break;
  }
 }

 /* Use RACK to detect loss */
 if (Model0_sysctl_tcp_recovery & 0x1 &&
     Model0_tcp_rack_mark_lost(Model0_sk)) {
  Model0_flag |= 0x80;
  *Model0_ack_flag |= 0x80;
 }

 /* E. Process state. */
 switch (Model0_icsk->Model0_icsk_ca_state) {
 case Model0_TCP_CA_Recovery:
  if (!(Model0_flag & 0x400)) {
   if (Model0_tcp_is_reno(Model0_tp) && Model0_is_dupack)
    Model0_tcp_add_reno_sack(Model0_sk);
  } else {
   if (Model0_tcp_try_undo_partial(Model0_sk, Model0_acked))
    return;
   /* Partial ACK arrived. Force fast retransmit. */
   Model0_do_lost = Model0_tcp_is_reno(Model0_tp) ||
      Model0_tcp_fackets_out(Model0_tp) > Model0_tp->Model0_reordering;
  }
  if (Model0_tcp_try_undo_dsack(Model0_sk)) {
   Model0_tcp_try_keep_open(Model0_sk);
   return;
  }
  break;
 case Model0_TCP_CA_Loss:
  Model0_tcp_process_loss(Model0_sk, Model0_flag, Model0_is_dupack, Model0_rexmit);
  if (Model0_icsk->Model0_icsk_ca_state != Model0_TCP_CA_Open &&
      !(Model0_flag & 0x80))
   return;
  /* Change state if cwnd is undone or retransmits are lost */
 default:
  if (Model0_tcp_is_reno(Model0_tp)) {
   if (Model0_flag & 0x400)
    Model0_tcp_reset_reno_sack(Model0_tp);
   if (Model0_is_dupack)
    Model0_tcp_add_reno_sack(Model0_sk);
  }

  if (Model0_icsk->Model0_icsk_ca_state <= Model0_TCP_CA_Disorder)
   Model0_tcp_try_undo_dsack(Model0_sk);

  if (!Model0_tcp_time_to_recover(Model0_sk, Model0_flag)) {
   Model0_tcp_try_to_open(Model0_sk, Model0_flag);
   return;
  }

  /* MTU probe failure: don't reduce cwnd */
  if (Model0_icsk->Model0_icsk_ca_state < Model0_TCP_CA_CWR &&
      Model0_icsk->Model0_icsk_mtup.Model0_probe_size &&
      Model0_tp->Model0_snd_una == Model0_tp->Model0_mtu_probe.Model0_probe_seq_start) {
   Model0_tcp_mtup_probe_failed(Model0_sk);
   /* Restores the reduction we did in tcp_mtup_probe() */
   Model0_tp->Model0_snd_cwnd++;
   Model0_tcp_simple_retransmit(Model0_sk);
   return;
  }

  /* Otherwise enter Recovery state */
  Model0_tcp_enter_recovery(Model0_sk, (Model0_flag & 0x40));
  Model0_fast_rexmit = 1;
 }

 if (Model0_do_lost)
  Model0_tcp_update_scoreboard(Model0_sk, Model0_fast_rexmit);
 *Model0_rexmit = 1;
}

/* Kathleen Nichols' algorithm for tracking the minimum value of
 * a data stream over some fixed time interval. (E.g., the minimum
 * RTT over the past five minutes.) It uses constant space and constant
 * time per update yet almost always delivers the same minimum as an
 * implementation that has to keep all the data in the window.
 *
 * The algorithm keeps track of the best, 2nd best & 3rd best min
 * values, maintaining an invariant that the measurement time of the
 * n'th best >= n-1'th best. It also makes sure that the three values
 * are widely separated in the time window since that bounds the worse
 * case error when that data is monotonically increasing over the window.
 *
 * Upon getting a new min, we can forget everything earlier because it
 * has no value - the new min is <= everything else in the window by
 * definition and it's the most recent. So we restart fresh on every new min
 * and overwrites 2nd & 3rd choices. The same property holds for 2nd & 3rd
 * best.
 */
static void Model0_tcp_update_rtt_min(struct Model0_sock *Model0_sk, Model0_u32 Model0_rtt_us)
{
 const Model0_u32 Model0_now = ((__u32)(Model0_jiffies)), Model0_wlen = Model0_sysctl_tcp_min_rtt_wlen * 1000;
 struct Model0_rtt_meas *Model0_m = Model0_tcp_sk(Model0_sk)->Model0_rtt_min;
 struct Model0_rtt_meas Model0_rttm = {
  .Model0_rtt = __builtin_expect(!!(Model0_rtt_us), 1) ? Model0_rtt_us : Model0_jiffies_to_usecs(1),
  .Model0_ts = Model0_now,
 };
 Model0_u32 Model0_elapsed;

 /* Check if the new measurement updates the 1st, 2nd, or 3rd choices */
 if (__builtin_expect(!!(Model0_rttm.Model0_rtt <= Model0_m[0].Model0_rtt), 0))
  Model0_m[0] = Model0_m[1] = Model0_m[2] = Model0_rttm;
 else if (Model0_rttm.Model0_rtt <= Model0_m[1].Model0_rtt)
  Model0_m[1] = Model0_m[2] = Model0_rttm;
 else if (Model0_rttm.Model0_rtt <= Model0_m[2].Model0_rtt)
  Model0_m[2] = Model0_rttm;

 Model0_elapsed = Model0_now - Model0_m[0].Model0_ts;
 if (__builtin_expect(!!(Model0_elapsed > Model0_wlen), 0)) {
  /* Passed entire window without a new min so make 2nd choice
		 * the new min & 3rd choice the new 2nd. So forth and so on.
		 */
  Model0_m[0] = Model0_m[1];
  Model0_m[1] = Model0_m[2];
  Model0_m[2] = Model0_rttm;
  if (Model0_now - Model0_m[0].Model0_ts > Model0_wlen) {
   Model0_m[0] = Model0_m[1];
   Model0_m[1] = Model0_rttm;
   if (Model0_now - Model0_m[0].Model0_ts > Model0_wlen)
    Model0_m[0] = Model0_rttm;
  }
 } else if (Model0_m[1].Model0_ts == Model0_m[0].Model0_ts && Model0_elapsed > Model0_wlen / 4) {
  /* Passed a quarter of the window without a new min so
		 * take 2nd choice from the 2nd quarter of the window.
		 */
  Model0_m[2] = Model0_m[1] = Model0_rttm;
 } else if (Model0_m[2].Model0_ts == Model0_m[1].Model0_ts && Model0_elapsed > Model0_wlen / 2) {
  /* Passed half the window without a new min so take the 3rd
		 * choice from the last half of the window.
		 */
  Model0_m[2] = Model0_rttm;
 }
}

static inline __attribute__((no_instrument_function)) bool Model0_tcp_ack_update_rtt(struct Model0_sock *Model0_sk, const int Model0_flag,
          long Model0_seq_rtt_us, long Model0_sack_rtt_us,
          long Model0_ca_rtt_us)
{
 const struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 /* Prefer RTT measured from ACK's timing to TS-ECR. This is because
	 * broken middle-boxes or peers may corrupt TS-ECR fields. But
	 * Karn's algorithm forbids taking RTT if some retransmitted data
	 * is acked (RFC6298).
	 */
 if (Model0_seq_rtt_us < 0)
  Model0_seq_rtt_us = Model0_sack_rtt_us;

 /* RTTM Rule: A TSecr value received in a segment is used to
	 * update the averaged RTT measurement only if the segment
	 * acknowledges some new data, i.e., only if it advances the
	 * left edge of the send window.
	 * See draft-ietf-tcplw-high-performance-00, section 3.3.
	 */
 if (Model0_seq_rtt_us < 0 && Model0_tp->Model0_rx_opt.Model0_saw_tstamp && Model0_tp->Model0_rx_opt.Model0_rcv_tsecr &&
     Model0_flag & (0x04|0x10))
  Model0_seq_rtt_us = Model0_ca_rtt_us = Model0_jiffies_to_usecs(((__u32)(Model0_jiffies)) -
         Model0_tp->Model0_rx_opt.Model0_rcv_tsecr);
 if (Model0_seq_rtt_us < 0)
  return false;

 /* ca_rtt_us >= 0 is counting on the invariant that ca_rtt_us is
	 * always taken together with ACK, SACK, or TS-opts. Any negative
	 * values will be skipped with the seq_rtt_us < 0 check above.
	 */
 Model0_tcp_update_rtt_min(Model0_sk, Model0_ca_rtt_us);
 Model0_tcp_rtt_estimator(Model0_sk, Model0_seq_rtt_us);
 Model0_tcp_set_rto(Model0_sk);

 /* RFC6298: only reset backoff on valid RTT measurement. */
 Model0_inet_csk(Model0_sk)->Model0_icsk_backoff = 0;
 return true;
}

/* Compute time elapsed between (last) SYNACK and the ACK completing 3WHS. */
void Model0_tcp_synack_rtt_meas(struct Model0_sock *Model0_sk, struct Model0_request_sock *Model0_req)
{
 long Model0_rtt_us = -1L;

 if (Model0_req && !Model0_req->Model0_num_retrans && Model0_tcp_rsk(Model0_req)->Model0_snt_synack.Model0_v64) {
  struct Model0_skb_mstamp Model0_now;

  Model0_skb_mstamp_get(&Model0_now);
  Model0_rtt_us = Model0_skb_mstamp_us_delta(&Model0_now, &Model0_tcp_rsk(Model0_req)->Model0_snt_synack);
 }

 Model0_tcp_ack_update_rtt(Model0_sk, 0x10, Model0_rtt_us, -1L, Model0_rtt_us);
}


static void Model0_tcp_cong_avoid(struct Model0_sock *Model0_sk, Model0_u32 Model0_ack, Model0_u32 Model0_acked)
{
 const struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);

 Model0_icsk->Model0_icsk_ca_ops->Model0_cong_avoid(Model0_sk, Model0_ack, Model0_acked);
 Model0_tcp_sk(Model0_sk)->Model0_snd_cwnd_stamp = ((__u32)(Model0_jiffies));
}

/* Restart timer after forward progress on connection.
 * RFC2988 recommends to restart timer to now+rto.
 */
void Model0_tcp_rearm_rto(struct Model0_sock *Model0_sk)
{
 const struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 /* If the retrans timer is currently being used by Fast Open
	 * for SYN-ACK retrans purpose, stay put.
	 */
 if (Model0_tp->Model0_fastopen_rsk)
  return;

 if (!Model0_tp->Model0_packets_out) {
  Model0_inet_csk_clear_xmit_timer(Model0_sk, 1);
 } else {
  Model0_u32 Model0_rto = Model0_inet_csk(Model0_sk)->Model0_icsk_rto;
  /* Offset the time elapsed after installing regular RTO */
  if (Model0_icsk->Model0_icsk_pending == 4 ||
      Model0_icsk->Model0_icsk_pending == 5) {
   struct Model0_sk_buff *Model0_skb = Model0_tcp_write_queue_head(Model0_sk);
   const Model0_u32 Model0_rto_time_stamp =
    Model0_tcp_skb_timestamp(Model0_skb) + Model0_rto;
   Model0_s32 Model0_delta = (Model0_s32)(Model0_rto_time_stamp - ((__u32)(Model0_jiffies)));
   /* delta may not be positive if the socket is locked
			 * when the retrans timer fires and is rescheduled.
			 */
   if (Model0_delta > 0)
    Model0_rto = Model0_delta;
  }
  Model0_inet_csk_reset_xmit_timer(Model0_sk, 1, Model0_rto,
       ((unsigned)(120*1000)));
 }
}

/* This function is called when the delayed ER timer fires. TCP enters
 * fast recovery and performs fast-retransmit.
 */
void Model0_tcp_resume_early_retransmit(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 Model0_tcp_rearm_rto(Model0_sk);

 /* Stop if ER is disabled after the delayed ER timer is scheduled */
 if (!Model0_tp->Model0_do_early_retrans)
  return;

 Model0_tcp_enter_recovery(Model0_sk, false);
 Model0_tcp_update_scoreboard(Model0_sk, 1);
 Model0_tcp_xmit_retransmit_queue(Model0_sk);
}

/* If we get here, the whole TSO packet has not been acked. */
static Model0_u32 Model0_tcp_tso_acked(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 Model0_u32 Model0_packets_acked;

 do { if (!Model0_before(Model0_tp->Model0_snd_una, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq)) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);

 Model0_packets_acked = Model0_tcp_skb_pcount(Model0_skb);
 if (Model0_tcp_trim_head(Model0_sk, Model0_skb, Model0_tp->Model0_snd_una - ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq))
  return 0;
 Model0_packets_acked -= Model0_tcp_skb_pcount(Model0_skb);

 if (Model0_packets_acked) {
  do { if (Model0_tcp_skb_pcount(Model0_skb) == 0) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);
  do { if (!Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq)) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);
 }

 return Model0_packets_acked;
}

static void Model0_tcp_ack_tstamp(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb,
      Model0_u32 Model0_prior_snd_una)
{
 const struct Model0_skb_shared_info *Model0_shinfo;

 /* Avoid cache line misses to get skb_shinfo() and shinfo->tx_flags */
 if (__builtin_expect(!!(!((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_txstamp_ack), 1))
  return;

 Model0_shinfo = ((struct Model0_skb_shared_info *)(Model0_skb_end_pointer(Model0_skb)));
 if (!Model0_before(Model0_shinfo->Model0_tskey, Model0_prior_snd_una) &&
     Model0_before(Model0_shinfo->Model0_tskey, Model0_tcp_sk(Model0_sk)->Model0_snd_una))
  Model0___skb_tstamp_tx(Model0_skb, ((void *)0), Model0_sk, Model0_SCM_TSTAMP_ACK);
}

/* Remove acknowledged frames from the retransmission queue. If our packet
 * is before the ack sequence we can discard it as it's confirmed to have
 * arrived at the other end.
 */
static int Model0_tcp_clean_rtx_queue(struct Model0_sock *Model0_sk, int Model0_prior_fackets,
          Model0_u32 Model0_prior_snd_una, int *Model0_acked,
          struct Model0_tcp_sacktag_state *Model0_sack)
{
 const struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
 struct Model0_skb_mstamp Model0_first_ackt, Model0_last_ackt, Model0_now;
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 Model0_u32 Model0_prior_sacked = Model0_tp->Model0_sacked_out;
 Model0_u32 Model0_reord = Model0_tp->Model0_packets_out;
 bool Model0_fully_acked = true;
 long Model0_sack_rtt_us = -1L;
 long Model0_seq_rtt_us = -1L;
 long Model0_ca_rtt_us = -1L;
 struct Model0_sk_buff *Model0_skb;
 Model0_u32 Model0_pkts_acked = 0;
 Model0_u32 Model0_last_in_flight = 0;
 bool Model0_rtt_update;
 int Model0_flag = 0;

 Model0_first_ackt.Model0_v64 = 0;

 while ((Model0_skb = Model0_tcp_write_queue_head(Model0_sk)) && Model0_skb != Model0_tcp_send_head(Model0_sk)) {
  struct Model0_tcp_skb_cb *Model0_scb = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]));
  Model0_u8 Model0_sacked = Model0_scb->Model0_sacked;
  Model0_u32 Model0_acked_pcount;

  Model0_tcp_ack_tstamp(Model0_sk, Model0_skb, Model0_prior_snd_una);

  /* Determine how many packets and what bytes were acked, tso and else */
  if (Model0_before(Model0_tp->Model0_snd_una, Model0_scb->Model0_end_seq)) {
   if (Model0_tcp_skb_pcount(Model0_skb) == 1 ||
       !Model0_before(Model0_scb->Model0_seq, Model0_tp->Model0_snd_una))
    break;

   Model0_acked_pcount = Model0_tcp_tso_acked(Model0_sk, Model0_skb);
   if (!Model0_acked_pcount)
    break;

   Model0_fully_acked = false;
  } else {
   /* Speedup tcp_unlink_write_queue() and next loop */
   Model0_prefetchw(Model0_skb->Model0_next);
   Model0_acked_pcount = Model0_tcp_skb_pcount(Model0_skb);
  }

  if (__builtin_expect(!!(Model0_sacked & (0x02|0x80| 0x10)), 0)) {
   if (Model0_sacked & 0x02)
    Model0_tp->Model0_retrans_out -= Model0_acked_pcount;
   Model0_flag |= 0x08;
  } else if (!(Model0_sacked & 0x01)) {
   Model0_last_ackt = Model0_skb->Model0_skb_mstamp;
   ({ int Model0___ret_warn_on = !!(Model0_last_ackt.Model0_v64 == 0); __builtin_expect(!!(Model0___ret_warn_on), 0); });
   if (!Model0_first_ackt.Model0_v64)
    Model0_first_ackt = Model0_last_ackt;

   Model0_last_in_flight = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_tx.Model0_in_flight;
   Model0_reord = ({ typeof(Model0_pkts_acked) Model0__min1 = (Model0_pkts_acked); typeof(Model0_reord) Model0__min2 = (Model0_reord); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
   if (!Model0_before(Model0_tp->Model0_high_seq, Model0_scb->Model0_end_seq))
    Model0_flag |= 0x200;
  }

  if (Model0_sacked & 0x01) {
   Model0_tp->Model0_sacked_out -= Model0_acked_pcount;
  } else if (Model0_tcp_is_sack(Model0_tp)) {
   Model0_tp->Model0_delivered += Model0_acked_pcount;
   if (!Model0_tcp_skb_spurious_retrans(Model0_tp, Model0_skb))
    Model0_tcp_rack_advance(Model0_tp, &Model0_skb->Model0_skb_mstamp, Model0_sacked);
  }
  if (Model0_sacked & 0x04)
   Model0_tp->Model0_lost_out -= Model0_acked_pcount;

  Model0_tp->Model0_packets_out -= Model0_acked_pcount;
  Model0_pkts_acked += Model0_acked_pcount;

  /* Initial outgoing SYN's get put onto the write_queue
		 * just like anything else we transmit.  It is not
		 * true data, and if we misinform our callers that
		 * this ACK acks real data, we will erroneously exit
		 * connection startup slow start one packet too
		 * quickly.  This is severely frowned upon behavior.
		 */
  if (__builtin_expect(!!(!(Model0_scb->Model0_tcp_flags & 0x02)), 1)) {
   Model0_flag |= 0x04;
  } else {
   Model0_flag |= 0x10;
   Model0_tp->Model0_retrans_stamp = 0;
  }

  if (!Model0_fully_acked)
   break;

  Model0_tcp_unlink_write_queue(Model0_skb, Model0_sk);
  Model0_sk_wmem_free_skb(Model0_sk, Model0_skb);
  if (__builtin_expect(!!(Model0_skb == Model0_tp->Model0_retransmit_skb_hint), 0))
   Model0_tp->Model0_retransmit_skb_hint = ((void *)0);
  if (__builtin_expect(!!(Model0_skb == Model0_tp->Model0_lost_skb_hint), 0))
   Model0_tp->Model0_lost_skb_hint = ((void *)0);
 }

 if (__builtin_expect(!!(Model0_between(Model0_tp->Model0_snd_up, Model0_prior_snd_una, Model0_tp->Model0_snd_una)), 1))
  Model0_tp->Model0_snd_up = Model0_tp->Model0_snd_una;

 if (Model0_skb && (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked & 0x01))
  Model0_flag |= 0x2000;

 Model0_skb_mstamp_get(&Model0_now);
 if (__builtin_expect(!!(Model0_first_ackt.Model0_v64), 1) && !(Model0_flag & 0x08)) {
  Model0_seq_rtt_us = Model0_skb_mstamp_us_delta(&Model0_now, &Model0_first_ackt);
  Model0_ca_rtt_us = Model0_skb_mstamp_us_delta(&Model0_now, &Model0_last_ackt);
 }
 if (Model0_sack->Model0_first_sackt.Model0_v64) {
  Model0_sack_rtt_us = Model0_skb_mstamp_us_delta(&Model0_now, &Model0_sack->Model0_first_sackt);
  Model0_ca_rtt_us = Model0_skb_mstamp_us_delta(&Model0_now, &Model0_sack->Model0_last_sackt);
 }

 Model0_rtt_update = Model0_tcp_ack_update_rtt(Model0_sk, Model0_flag, Model0_seq_rtt_us, Model0_sack_rtt_us,
     Model0_ca_rtt_us);

 if (Model0_flag & (0x04|0x10)) {
  Model0_tcp_rearm_rto(Model0_sk);
  if (__builtin_expect(!!(Model0_icsk->Model0_icsk_mtup.Model0_probe_size && !Model0_before(Model0_tp->Model0_snd_una, Model0_tp->Model0_mtu_probe.Model0_probe_seq_end)), 0)) {

   Model0_tcp_mtup_probe_success(Model0_sk);
  }

  if (Model0_tcp_is_reno(Model0_tp)) {
   Model0_tcp_remove_reno_sacks(Model0_sk, Model0_pkts_acked);
  } else {
   int Model0_delta;

   /* Non-retransmitted hole got filled? That's reordering */
   if (Model0_reord < Model0_prior_fackets)
    Model0_tcp_update_reordering(Model0_sk, Model0_tp->Model0_fackets_out - Model0_reord, 0);

   Model0_delta = Model0_tcp_is_fack(Model0_tp) ? Model0_pkts_acked :
        Model0_prior_sacked - Model0_tp->Model0_sacked_out;
   Model0_tp->Model0_lost_cnt_hint -= ({ typeof(Model0_tp->Model0_lost_cnt_hint) Model0__min1 = (Model0_tp->Model0_lost_cnt_hint); typeof(Model0_delta) Model0__min2 = (Model0_delta); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
  }

  Model0_tp->Model0_fackets_out -= ({ typeof(Model0_pkts_acked) Model0__min1 = (Model0_pkts_acked); typeof(Model0_tp->Model0_fackets_out) Model0__min2 = (Model0_tp->Model0_fackets_out); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });

 } else if (Model0_skb && Model0_rtt_update && Model0_sack_rtt_us >= 0 &&
     Model0_sack_rtt_us > Model0_skb_mstamp_us_delta(&Model0_now, &Model0_skb->Model0_skb_mstamp)) {
  /* Do not re-arm RTO if the sack RTT is measured from data sent
		 * after when the head was last (re)transmitted. Otherwise the
		 * timeout may continue to extend in loss recovery.
		 */
  Model0_tcp_rearm_rto(Model0_sk);
 }

 if (Model0_icsk->Model0_icsk_ca_ops->Model0_pkts_acked) {
  struct Model0_ack_sample Model0_sample = { .Model0_pkts_acked = Model0_pkts_acked,
          .Model0_rtt_us = Model0_ca_rtt_us,
          .Model0_in_flight = Model0_last_in_flight };

  Model0_icsk->Model0_icsk_ca_ops->Model0_pkts_acked(Model0_sk, &Model0_sample);
 }


 ({ int Model0___ret_warn_on = !!((int)Model0_tp->Model0_sacked_out < 0); __builtin_expect(!!(Model0___ret_warn_on), 0); });
 ({ int Model0___ret_warn_on = !!((int)Model0_tp->Model0_lost_out < 0); __builtin_expect(!!(Model0___ret_warn_on), 0); });
 ({ int Model0___ret_warn_on = !!((int)Model0_tp->Model0_retrans_out < 0); __builtin_expect(!!(Model0___ret_warn_on), 0); });
 if (!Model0_tp->Model0_packets_out && Model0_tcp_is_sack(Model0_tp)) {
  Model0_icsk = Model0_inet_csk(Model0_sk);
  if (Model0_tp->Model0_lost_out) {
   ({ do { if (0) Model0_printk("\001" "7" "TCP: " "Leak l=%u %d\n", Model0_tp->Model0_lost_out, Model0_icsk->Model0_icsk_ca_state); } while (0); 0; });

   Model0_tp->Model0_lost_out = 0;
  }
  if (Model0_tp->Model0_sacked_out) {
   ({ do { if (0) Model0_printk("\001" "7" "TCP: " "Leak s=%u %d\n", Model0_tp->Model0_sacked_out, Model0_icsk->Model0_icsk_ca_state); } while (0); 0; });

   Model0_tp->Model0_sacked_out = 0;
  }
  if (Model0_tp->Model0_retrans_out) {
   ({ do { if (0) Model0_printk("\001" "7" "TCP: " "Leak r=%u %d\n", Model0_tp->Model0_retrans_out, Model0_icsk->Model0_icsk_ca_state); } while (0); 0; });

   Model0_tp->Model0_retrans_out = 0;
  }
 }

 *Model0_acked = Model0_pkts_acked;
 return Model0_flag;
}

static void Model0_tcp_ack_probe(struct Model0_sock *Model0_sk)
{
 const struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);

 /* Was it a usable window open? */

 if (!Model0_before(Model0_tcp_wnd_end(Model0_tp), ((struct Model0_tcp_skb_cb *)&((Model0_tcp_send_head(Model0_sk))->Model0_cb[0]))->Model0_end_seq)) {
  Model0_icsk->Model0_icsk_backoff = 0;
  Model0_inet_csk_clear_xmit_timer(Model0_sk, 3);
  /* Socket must be waked up by subsequent tcp_data_snd_check().
		 * This function is not for random using!
		 */
 } else {
  unsigned long Model0_when = Model0_tcp_probe0_when(Model0_sk, ((unsigned)(120*1000)));

  Model0_inet_csk_reset_xmit_timer(Model0_sk, 3,
       Model0_when, ((unsigned)(120*1000)));
 }
}

static inline __attribute__((no_instrument_function)) bool Model0_tcp_ack_is_dubious(const struct Model0_sock *Model0_sk, const int Model0_flag)
{
 return !(Model0_flag & (0x01|0x02|(0x04|0x10))) || (Model0_flag & (0x20|0x40)) ||
  Model0_inet_csk(Model0_sk)->Model0_icsk_ca_state != Model0_TCP_CA_Open;
}

/* Decide wheather to run the increase function of congestion control. */
static inline __attribute__((no_instrument_function)) bool Model0_tcp_may_raise_cwnd(const struct Model0_sock *Model0_sk, const int Model0_flag)
{
 /* If reordering is high then always grow cwnd whenever data is
	 * delivered regardless of its ordering. Otherwise stay conservative
	 * and only grow cwnd on in-order delivery (RFC5681). A stretched ACK w/
	 * new SACK or ECE mark may first advance cwnd here and later reduce
	 * cwnd in tcp_fastretrans_alert() based on more states.
	 */
 if (Model0_tcp_sk(Model0_sk)->Model0_reordering > Model0_sock_net(Model0_sk)->Model0_ipv4.Model0_sysctl_tcp_reordering)
  return Model0_flag & ((0x04|0x10)|0x20);

 return Model0_flag & 0x04;
}

/* The "ultimate" congestion control function that aims to replace the rigid
 * cwnd increase and decrease control (tcp_cong_avoid,tcp_*cwnd_reduction).
 * It's called toward the end of processing an ACK with precise rate
 * information. All transmission or retransmission are delayed afterwards.
 */
static void Model0_tcp_cong_control(struct Model0_sock *Model0_sk, Model0_u32 Model0_ack, Model0_u32 Model0_acked_sacked,
        int Model0_flag)
{
 if (Model0_tcp_in_cwnd_reduction(Model0_sk)) {
  /* Reduce cwnd if state mandates */
  Model0_tcp_cwnd_reduction(Model0_sk, Model0_acked_sacked, Model0_flag);
 } else if (Model0_tcp_may_raise_cwnd(Model0_sk, Model0_flag)) {
  /* Advance cwnd if state allows */
  Model0_tcp_cong_avoid(Model0_sk, Model0_ack, Model0_acked_sacked);
 }
 Model0_tcp_update_pacing_rate(Model0_sk);
}

/* Check that window update is acceptable.
 * The function assumes that snd_una<=ack<=snd_next.
 */
static inline __attribute__((no_instrument_function)) bool Model0_tcp_may_update_window(const struct Model0_tcp_sock *Model0_tp,
     const Model0_u32 Model0_ack, const Model0_u32 Model0_ack_seq,
     const Model0_u32 Model0_nwin)
{
 return Model0_before(Model0_tp->Model0_snd_una, Model0_ack) ||
  Model0_before(Model0_tp->Model0_snd_wl1, Model0_ack_seq) ||
  (Model0_ack_seq == Model0_tp->Model0_snd_wl1 && Model0_nwin > Model0_tp->Model0_snd_wnd);
}

/* If we update tp->snd_una, also update tp->bytes_acked */
static void Model0_tcp_snd_una_update(struct Model0_tcp_sock *Model0_tp, Model0_u32 Model0_ack)
{
 Model0_u32 Model0_delta = Model0_ack - Model0_tp->Model0_snd_una;

 Model0_sock_owned_by_me((struct Model0_sock *)Model0_tp);
 Model0_u64_stats_update_begin_raw(&Model0_tp->Model0_syncp);
 Model0_tp->Model0_bytes_acked += Model0_delta;
 Model0_u64_stats_update_end_raw(&Model0_tp->Model0_syncp);
 Model0_tp->Model0_snd_una = Model0_ack;
}

/* If we update tp->rcv_nxt, also update tp->bytes_received */
static void Model0_tcp_rcv_nxt_update(struct Model0_tcp_sock *Model0_tp, Model0_u32 Model0_seq)
{
 Model0_u32 Model0_delta = Model0_seq - Model0_tp->Model0_rcv_nxt;

 Model0_sock_owned_by_me((struct Model0_sock *)Model0_tp);
 Model0_u64_stats_update_begin_raw(&Model0_tp->Model0_syncp);
 Model0_tp->Model0_bytes_received += Model0_delta;
 Model0_u64_stats_update_end_raw(&Model0_tp->Model0_syncp);
 Model0_tp->Model0_rcv_nxt = Model0_seq;
}

/* Update our send window.
 *
 * Window update algorithm, described in RFC793/RFC1122 (used in linux-2.2
 * and in FreeBSD. NetBSD's one is even worse.) is wrong.
 */
static int Model0_tcp_ack_update_window(struct Model0_sock *Model0_sk, const struct Model0_sk_buff *Model0_skb, Model0_u32 Model0_ack,
     Model0_u32 Model0_ack_seq)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 int Model0_flag = 0;
 Model0_u32 Model0_nwin = (__builtin_constant_p((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_window))) ? ((Model0___u16)( (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_window)) & (Model0___u16)0x00ffU) << 8) | (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_window)) & (Model0___u16)0xff00U) >> 8))) : Model0___fswab16(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_window)));

 if (__builtin_expect(!!(!Model0_tcp_hdr(Model0_skb)->Model0_syn), 1))
  Model0_nwin <<= Model0_tp->Model0_rx_opt.Model0_snd_wscale;

 if (Model0_tcp_may_update_window(Model0_tp, Model0_ack, Model0_ack_seq, Model0_nwin)) {
  Model0_flag |= 0x02;
  Model0_tcp_update_wl(Model0_tp, Model0_ack_seq);

  if (Model0_tp->Model0_snd_wnd != Model0_nwin) {
   Model0_tp->Model0_snd_wnd = Model0_nwin;

   /* Note, it is the only place, where
			 * fast path is recovered for sending TCP.
			 */
   Model0_tp->Model0_pred_flags = 0;
   Model0_tcp_fast_path_check(Model0_sk);

   if (Model0_tcp_send_head(Model0_sk))
    Model0_tcp_slow_start_after_idle_check(Model0_sk);

   if (Model0_nwin > Model0_tp->Model0_max_window) {
    Model0_tp->Model0_max_window = Model0_nwin;
    Model0_tcp_sync_mss(Model0_sk, Model0_inet_csk(Model0_sk)->Model0_icsk_pmtu_cookie);
   }
  }
 }

 Model0_tcp_snd_una_update(Model0_tp, Model0_ack);

 return Model0_flag;
}

static bool Model0___tcp_oow_rate_limited(struct Model0_net *Model0_net, int Model0_mib_idx,
       Model0_u32 *Model0_last_oow_ack_time)
{
#if CY_ABSTRACT2
    //Have to do such abstraction. During 3-way handshake, new generated sock->last_oow_ack_time (e.g., req, new_sk) is initialized with current jiffies. Because jiffies in our model is alway fixed, for packet with SYN flag, it's impossible to send any packet out. But that's not true in reality. So we abstract the codes to remove such rate limite. In practice, this rate limit makes attacker slower, but not impossible (i.e., firstly send 1 spoofed packet with SYN to trigger challenge ACK, then use data payload to bypass the resctrion. In newest patch, we cannot use data packet to bypass it)
    return false;
#else
 if (*Model0_last_oow_ack_time) {
  Model0_s32 Model0_elapsed = (Model0_s32)(((__u32)(Model0_jiffies)) - *Model0_last_oow_ack_time);

  if (0 <= Model0_elapsed && Model0_elapsed < Model0_sysctl_tcp_invalid_ratelimit) {
   (Model0_cy_linux_mib.Model0_mibs[Model0_mib_idx] += 1);
   return true; /* rate-limited: don't send yet! */
  }
 }

 *Model0_last_oow_ack_time = ((__u32)(Model0_jiffies));

 return false; /* not rate-limited: go ahead, send dupack now! */
#endif
}

/* Return true if we're currently rate-limiting out-of-window ACKs and
 * thus shouldn't send a dupack right now. We rate-limit dupacks in
 * response to out-of-window SYNs or ACKs to mitigate ACK loops or DoS
 * attacks that send repeated SYNs or ACKs for the same connection. To
 * do this, we do not send a duplicate SYNACK or ACK if the remote
 * endpoint is sending out-of-window SYNs or pure ACKs at a high rate.
 */
bool Model0_tcp_oow_rate_limited(struct Model0_net *Model0_net, const struct Model0_sk_buff *Model0_skb,
     int Model0_mib_idx, Model0_u32 *Model0_last_oow_ack_time)
{
 /* Data packets without SYNs are not likely part of an ACK loop. */
 if ((((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq != ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq) &&
     !Model0_tcp_hdr(Model0_skb)->Model0_syn)
  return false;

 return Model0___tcp_oow_rate_limited(Model0_net, Model0_mib_idx, Model0_last_oow_ack_time);
}

/* RFC 5961 7 [ACK Throttling] */
#if CY_ABSTRACT3
static void Model0_tcp_send_challenge_ack(struct Model0_sock *Model0_sk, const struct Model0_sk_buff *Model0_skb)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 Model0_u32 Model0_count, Model0_now;

 if (Model0___tcp_oow_rate_limited(Model0_sock_net(Model0_sk),
       Model0_LINUX_MIB_TCPACKSKIPPEDCHALLENGE,
       &Model0_tp->Model0_last_oow_ack_time))
  return;

 Model0_now = Model0_jiffies / 1000;
 if (Model0_now != Model0_challenge_timestamp){
     Model0_challenge_timestamp = Model0_now;
     Model0_challenge_count = 0;
 }

 //printf("Model0_challenge_count++\n");
 if (++Model0_challenge_count  <= Model0_sysctl_tcp_challenge_ack_limit){
    //printf("Model0_challenge_count %d, %d\n", Model0_challenge_count, Model0_sysctl_tcp_challenge_ack_limit);
    (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPCHALLENGEACK] += 1);
     Model0_tcp_send_ack(Model0_sk);
 }
}
#else
static void Model0_tcp_send_challenge_ack(struct Model0_sock *Model0_sk, const struct Model0_sk_buff *Model0_skb)
{
#if !CY_ABSTRACT3 //static variable inside function cannot be visited
 /* unprotected vars, we dont care of overwrites */
 static Model0_u32 Model0_challenge_timestamp;
 static unsigned int Model0_challenge_count;
#endif
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 Model0_u32 Model0_count, Model0_now;

 /* First check our per-socket dupack rate limit. */
//#if CY_ABSTRACT1
// if (Model0_tcp_oow_rate_limited(Model0_sock_net(Model0_sk), Model0_skb,
//#else
 if (Model0___tcp_oow_rate_limited(Model0_sock_net(Model0_sk),
//#endif
       Model0_LINUX_MIB_TCPACKSKIPPEDCHALLENGE,
       &Model0_tp->Model0_last_oow_ack_time))
  return;

 /* Then check host-wide RFC 5961 rate limit. */
 Model0_now = Model0_jiffies / 1000;
 if (Model0_now != Model0_challenge_timestamp) {
  Model0_u32 Model0_half = (Model0_sysctl_tcp_challenge_ack_limit + 1) >> 1;

  Model0_challenge_timestamp = Model0_now;
  ({ union { typeof(Model0_challenge_count) Model0___val; char Model0___c[1]; } Model0___u = { .Model0___val = ( typeof(Model0_challenge_count)) (Model0_half + Model0_prandom_u32_max(Model0_sysctl_tcp_challenge_ack_limit)) }; Model0___write_once_size(&(Model0_challenge_count), Model0___u.Model0___c, sizeof(Model0_challenge_count)); Model0___u.Model0___val; });

 }
 Model0_count = ({ union { typeof(Model0_challenge_count) Model0___val; char Model0___c[1]; } Model0___u; if (1) Model0___read_once_size(&(Model0_challenge_count), Model0___u.Model0___c, sizeof(Model0_challenge_count)); else Model0___read_once_size_nocheck(&(Model0_challenge_count), Model0___u.Model0___c, sizeof(Model0_challenge_count)); Model0___u.Model0___val; });
 if (Model0_count > 0) {
  ({ union { typeof(Model0_challenge_count) Model0___val; char Model0___c[1]; } Model0___u = { .Model0___val = ( typeof(Model0_challenge_count)) (Model0_count - 1) }; Model0___write_once_size(&(Model0_challenge_count), Model0___u.Model0___c, sizeof(Model0_challenge_count)); Model0___u.Model0___val; });
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPCHALLENGEACK] += 1);
  Model0_tcp_send_ack(Model0_sk);
 }
}
#endif

static void Model0_tcp_store_ts_recent(struct Model0_tcp_sock *Model0_tp)
{
 Model0_tp->Model0_rx_opt.Model0_ts_recent = Model0_tp->Model0_rx_opt.Model0_rcv_tsval;
 Model0_tp->Model0_rx_opt.Model0_ts_recent_stamp = Model0_get_seconds();
}

static void Model0_tcp_replace_ts_recent(struct Model0_tcp_sock *Model0_tp, Model0_u32 Model0_seq)
{
 if (Model0_tp->Model0_rx_opt.Model0_saw_tstamp && !Model0_before(Model0_tp->Model0_rcv_wup, Model0_seq)) {
  /* PAWS bug workaround wrt. ACK frames, the PAWS discard
		 * extra check below makes sure this can only happen
		 * for pure ACK frames.  -DaveM
		 *
		 * Not only, also it occurs for expired timestamps.
		 */

  if (Model0_tcp_paws_check(&Model0_tp->Model0_rx_opt, 0))
   Model0_tcp_store_ts_recent(Model0_tp);
 }
}

/* This routine deals with acks during a TLP episode.
 * We mark the end of a TLP episode on receiving TLP dupack or when
 * ack is after tlp_high_seq.
 * Ref: loss detection algorithm in draft-dukkipati-tcpm-tcp-loss-probe.
 */
static void Model0_tcp_process_tlp_ack(struct Model0_sock *Model0_sk, Model0_u32 Model0_ack, int Model0_flag)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 if (Model0_before(Model0_ack, Model0_tp->Model0_tlp_high_seq))
  return;

 if (Model0_flag & 0x800) {
  /* This DSACK means original and TLP probe arrived; no loss */
  Model0_tp->Model0_tlp_high_seq = 0;
 } else if (Model0_before(Model0_tp->Model0_tlp_high_seq, Model0_ack)) {
  /* ACK advances: there was a loss, so reduce cwnd. Reset
		 * tlp_high_seq in tcp_init_cwnd_reduction()
		 */
  Model0_tcp_init_cwnd_reduction(Model0_sk);
  Model0_tcp_set_ca_state(Model0_sk, Model0_TCP_CA_CWR);
  Model0_tcp_end_cwnd_reduction(Model0_sk);
  Model0_tcp_try_keep_open(Model0_sk);
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPLOSSPROBERECOVERY] += 1);

 } else if (!(Model0_flag & (0x400 |
        (0x01|0x02|(0x04|0x10)) | 0x20))) {
  /* Pure dupack: original and TLP probe arrived; no loss */
  Model0_tp->Model0_tlp_high_seq = 0;
 }
}

static inline __attribute__((no_instrument_function)) void Model0_tcp_in_ack_event(struct Model0_sock *Model0_sk, Model0_u32 Model0_flags)
{
 const struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);

#if !CY_ABSTRACT1
 if (Model0_icsk->Model0_icsk_ca_ops->Model0_in_ack_event)
  Model0_icsk->Model0_icsk_ca_ops->Model0_in_ack_event(Model0_sk, Model0_flags);
#endif
}

/* Congestion control has updated the cwnd already. So if we're in
 * loss recovery then now we do any new sends (for FRTO) or
 * retransmits (for CA_Loss or CA_recovery) that make sense.
 */
static void Model0_tcp_xmit_recovery(struct Model0_sock *Model0_sk, int Model0_rexmit)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 if (Model0_rexmit == 0)
  return;

 if (__builtin_expect(!!(Model0_rexmit == 2), 0)) {
  Model0___tcp_push_pending_frames(Model0_sk, Model0_tcp_current_mss(Model0_sk),
       1);
  if (Model0_before(Model0_tp->Model0_high_seq, Model0_tp->Model0_snd_nxt))
   return;
  Model0_tp->Model0_frto = 0;
 }
 Model0_tcp_xmit_retransmit_queue(Model0_sk);
}

/* This routine deals with incoming acks, but not outgoing ones. */
static int Model0_tcp_ack(struct Model0_sock *Model0_sk, const struct Model0_sk_buff *Model0_skb, int Model0_flag)
{
 struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_tcp_sacktag_state Model0_sack_state;
 Model0_u32 Model0_prior_snd_una = Model0_tp->Model0_snd_una;
 Model0_u32 Model0_ack_seq = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq;
 Model0_u32 Model0_ack = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_ack_seq;
 bool Model0_is_dupack = false;
 Model0_u32 Model0_prior_fackets;
 int Model0_prior_packets = Model0_tp->Model0_packets_out;
 Model0_u32 Model0_prior_delivered = Model0_tp->Model0_delivered;
 int Model0_acked = 0; /* Number of packets newly acked */
 int Model0_rexmit = 0; /* Flag to (re)transmit to recover losses */

 Model0_sack_state.Model0_first_sackt.Model0_v64 = 0;

 /* We very likely will need to access write queue head. */
 Model0_prefetchw(Model0_sk->Model0_sk_write_queue.Model0_next);

 /* If the ack is older than previous acks
	 * then we can probably ignore it.
	 */
 if (Model0_before(Model0_ack, Model0_prior_snd_una)) {
  /* RFC 5961 5.2 [Blind Data Injection Attack].[Mitigation] */
  if (Model0_before(Model0_ack, Model0_prior_snd_una - Model0_tp->Model0_max_window)) {
   Model0_tcp_send_challenge_ack(Model0_sk, Model0_skb);
   return -1;
  }
  goto Model0_old_ack;
 }

 /* If the ack includes data we haven't sent yet, discard
	 * this segment (RFC793 Section 3.9).
	 */
 if (Model0_before(Model0_tp->Model0_snd_nxt, Model0_ack))
  goto Model0_invalid_ack;

#if !CY_ABSTRACT1 //TODO: double check (not necessary)
 if (Model0_icsk->Model0_icsk_pending == 4 ||
     Model0_icsk->Model0_icsk_pending == 5)
  Model0_tcp_rearm_rto(Model0_sk);
#endif

 if (Model0_before(Model0_prior_snd_una, Model0_ack)) {
  Model0_flag |= 0x400;
  Model0_icsk->Model0_icsk_retransmits = 0;
 }

 Model0_prior_fackets = Model0_tp->Model0_fackets_out;

 /* ts_recent update must be made after we are sure that the packet
	 * is in window.
	 */
 if (Model0_flag & 0x4000)
  Model0_tcp_replace_ts_recent(Model0_tp, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq);

 if (!(Model0_flag & 0x100) && Model0_before(Model0_prior_snd_una, Model0_ack)) {
  /* Window is constant, pure forward advance.
		 * No more checks are required.
		 * Note, we use the fact that SND.UNA>=SND.WL2.
		 */
  Model0_tcp_update_wl(Model0_tp, Model0_ack_seq);
  Model0_tcp_snd_una_update(Model0_tp, Model0_ack);
  Model0_flag |= 0x02;

  Model0_tcp_in_ack_event(Model0_sk, Model0_CA_ACK_WIN_UPDATE);

  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPHPACKS] += 1);
 } else {
  Model0_u32 Model0_ack_ev_flags = Model0_CA_ACK_SLOWPATH;

  if (Model0_ack_seq != ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq)
   Model0_flag |= 0x01;
  else
   (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPPUREACKS] += 1);

  Model0_flag |= Model0_tcp_ack_update_window(Model0_sk, Model0_skb, Model0_ack, Model0_ack_seq);
#if !CY_ABSTRACT1
  if (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked)
   Model0_flag |= Model0_tcp_sacktag_write_queue(Model0_sk, Model0_skb, Model0_prior_snd_una,
       &Model0_sack_state);

  if (Model0_tcp_ecn_rcv_ecn_echo(Model0_tp, Model0_tcp_hdr(Model0_skb))) {
   Model0_flag |= 0x40;
   Model0_ack_ev_flags |= Model0_CA_ACK_ECE;
  }
#endif
  if (Model0_flag & 0x02)
   Model0_ack_ev_flags |= Model0_CA_ACK_WIN_UPDATE;

  Model0_tcp_in_ack_event(Model0_sk, Model0_ack_ev_flags);
 }

 /* We passed data and got it acked, remove any soft error
	 * log. Something worked...
	 */
 Model0_sk->Model0_sk_err_soft = 0;
 Model0_icsk->Model0_icsk_probes_out = 0;
 Model0_tp->Model0_rcv_tstamp = ((__u32)(Model0_jiffies));
 if (!Model0_prior_packets)
  goto Model0_no_queue;

 /* See if we can take anything off of the retransmit queue. */
#if !CY_ABSTRACT1
 Model0_flag |= Model0_tcp_clean_rtx_queue(Model0_sk, Model0_prior_fackets, Model0_prior_snd_una, &Model0_acked,
        &Model0_sack_state);

 if (Model0_tcp_ack_is_dubious(Model0_sk, Model0_flag)) {
  Model0_is_dupack = !(Model0_flag & (0x400 | (0x01|0x02|(0x04|0x10))));
  Model0_tcp_fastretrans_alert(Model0_sk, Model0_acked, Model0_is_dupack, &Model0_flag, &Model0_rexmit);
 }
 if (Model0_tp->Model0_tlp_high_seq)
  Model0_tcp_process_tlp_ack(Model0_sk, Model0_ack, Model0_flag);

 if ((Model0_flag & ((0x04|0x10)|0x20)) || !(Model0_flag & (0x01|0x02|(0x04|0x10)))) {
  struct Model0_dst_entry *Model0_dst = Model0___sk_dst_get(Model0_sk);
  if (Model0_dst)
   Model0_dst_confirm(Model0_dst);
 }

 if (Model0_icsk->Model0_icsk_pending == 1)
  Model0_tcp_schedule_loss_probe(Model0_sk);
 Model0_tcp_cong_control(Model0_sk, Model0_ack, Model0_tp->Model0_delivered - Model0_prior_delivered, Model0_flag);
 Model0_tcp_xmit_recovery(Model0_sk, Model0_rexmit);
 return 1;
#endif
Model0_no_queue:
#if !CY_ABSTRACT1
 /* If data was DSACKed, see if we can undo a cwnd reduction. */
 if (Model0_flag & 0x800)
  Model0_tcp_fastretrans_alert(Model0_sk, Model0_acked, Model0_is_dupack, &Model0_flag, &Model0_rexmit);
 /* If this ack opens up a zero window, clear backoff.  It was
	 * being used to time the probes, and is probably far higher than
	 * it needs to be for normal retransmission.
	 */
 if (Model0_tcp_send_head(Model0_sk))
  Model0_tcp_ack_probe(Model0_sk);

 if (Model0_tp->Model0_tlp_high_seq)
  Model0_tcp_process_tlp_ack(Model0_sk, Model0_ack, Model0_flag);
#endif
 return 1;

Model0_invalid_ack:
 do { if ((Model0_sk) && Model0_sock_flag((Model0_sk), Model0_SOCK_DBG)) Model0_printk("\001" "7" "Ack %u after %u:%u\n", Model0_ack, Model0_tp->Model0_snd_una, Model0_tp->Model0_snd_nxt); } while (0);
 return -1;

Model0_old_ack:
#if !CY_ABSTRACT1
 /* If data was SACKed, tag it and see if we should send more data.
	 * If data was DSACKed, see if we can undo a cwnd reduction.
	 */
 if (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked) {
  Model0_flag |= Model0_tcp_sacktag_write_queue(Model0_sk, Model0_skb, Model0_prior_snd_una,
      &Model0_sack_state);
  Model0_tcp_fastretrans_alert(Model0_sk, Model0_acked, Model0_is_dupack, &Model0_flag, &Model0_rexmit);
  Model0_tcp_xmit_recovery(Model0_sk, Model0_rexmit);
 }

 do { if ((Model0_sk) && Model0_sock_flag((Model0_sk), Model0_SOCK_DBG)) Model0_printk("\001" "7" "Ack %u before %u:%u\n", Model0_ack, Model0_tp->Model0_snd_una, Model0_tp->Model0_snd_nxt); } while (0);
#endif
 return 0;
}

static void Model0_tcp_parse_fastopen_option(int Model0_len, const unsigned char *Model0_cookie,
          bool Model0_syn, struct Model0_tcp_fastopen_cookie *Model0_foc,
          bool Model0_exp_opt)
{
 /* Valid only in SYN or SYN-ACK with an even length.  */
 if (!Model0_foc || !Model0_syn || Model0_len < 0 || (Model0_len & 1))
  return;

 if (Model0_len >= 4 &&
     Model0_len <= 16)
  ({ Model0_size_t Model0___len = (Model0_len); void *Model0___ret; if (__builtin_constant_p(Model0_len) && Model0___len >= 64) Model0___ret = Model0___memcpy((Model0_foc->Model0_val), (Model0_cookie), Model0___len); else Model0___ret = __builtin_memcpy((Model0_foc->Model0_val), (Model0_cookie), Model0___len); Model0___ret; });
 else if (Model0_len != 0)
  Model0_len = -1;
 Model0_foc->Model0_len = Model0_len;
 Model0_foc->Model0_exp = Model0_exp_opt;
}

/* Look for tcp options. Normally only called on SYN and SYNACK packets.
 * But, this can also be called on packets in the established flow when
 * the fast version below fails.
 */
void Model0_tcp_parse_options(const struct Model0_sk_buff *Model0_skb,
         struct Model0_tcp_options_received *Model0_opt_rx, int Model0_estab,
         struct Model0_tcp_fastopen_cookie *Model0_foc)
{
#if CY_ABSTRACT1
    return;
#endif
 const unsigned char *Model0_ptr;
 const struct Model0_tcphdr *Model0_th = Model0_tcp_hdr(Model0_skb);
 int Model0_length = (Model0_th->Model0_doff * 4) - sizeof(struct Model0_tcphdr);

 Model0_ptr = (const unsigned char *)(Model0_th + 1);
 Model0_opt_rx->Model0_saw_tstamp = 0;

 while (Model0_length > 0) {
  int Model0_opcode = *Model0_ptr++;
  int Model0_opsize;

  switch (Model0_opcode) {
  case 0:
   return;
  case 1: /* Ref: RFC 793 section 3.1 */
   Model0_length--;
   continue;
  default:
   Model0_opsize = *Model0_ptr++;
   if (Model0_opsize < 2) /* "silly options" */
    return;
   if (Model0_opsize > Model0_length)
    return; /* don't parse partial options */
   switch (Model0_opcode) {
   case 2:
    if (Model0_opsize == 4 && Model0_th->Model0_syn && !Model0_estab) {
     Model0_u16 Model0_in_mss = Model0_get_unaligned_be16(Model0_ptr);
     if (Model0_in_mss) {
      if (Model0_opt_rx->Model0_user_mss &&
          Model0_opt_rx->Model0_user_mss < Model0_in_mss)
       Model0_in_mss = Model0_opt_rx->Model0_user_mss;
      Model0_opt_rx->Model0_mss_clamp = Model0_in_mss;
     }
    }
    break;
   case 3:
    if (Model0_opsize == 3 && Model0_th->Model0_syn &&
        !Model0_estab && Model0_sysctl_tcp_window_scaling) {
     __u8 Model0_snd_wscale = *(__u8 *)Model0_ptr;
     Model0_opt_rx->Model0_wscale_ok = 1;
     if (Model0_snd_wscale > 14) {
      do { if (Model0_net_ratelimit()) Model0_printk("\001" "6" "TCP: " "%s: Illegal window scaling value %d >14 received\n", __func__, Model0_snd_wscale); } while (0);


      Model0_snd_wscale = 14;
     }
     Model0_opt_rx->Model0_snd_wscale = Model0_snd_wscale;
    }
    break;
   case 8:
    if ((Model0_opsize == 10) &&
        ((Model0_estab && Model0_opt_rx->Model0_tstamp_ok) ||
         (!Model0_estab && Model0_sysctl_tcp_timestamps))) {
     Model0_opt_rx->Model0_saw_tstamp = 1;
     Model0_opt_rx->Model0_rcv_tsval = Model0_get_unaligned_be32(Model0_ptr);
     Model0_opt_rx->Model0_rcv_tsecr = Model0_get_unaligned_be32(Model0_ptr + 4);
    }
    break;
   case 4:
    if (Model0_opsize == 2 && Model0_th->Model0_syn &&
        !Model0_estab && Model0_sysctl_tcp_sack) {
     Model0_opt_rx->Model0_sack_ok = (1 << 0);
     Model0_tcp_sack_reset(Model0_opt_rx);
    }
    break;

   case 5:
    if ((Model0_opsize >= (2 + 8)) &&
       !((Model0_opsize - 2) % 8) &&
       Model0_opt_rx->Model0_sack_ok) {
     ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_sacked = (Model0_ptr - 2) - (unsigned char *)Model0_th;
    }
    break;
   case 34:
    Model0_tcp_parse_fastopen_option(
     Model0_opsize - 2,
     Model0_ptr, Model0_th->Model0_syn, Model0_foc, false);
    break;

   case 254:
    /* Fast Open option shares code 254 using a
				 * 16 bits magic number.
				 */
    if (Model0_opsize >= 4 &&
        Model0_get_unaligned_be16(Model0_ptr) ==
        0xF989)
     Model0_tcp_parse_fastopen_option(Model0_opsize -
      4,
      Model0_ptr + 2, Model0_th->Model0_syn, Model0_foc, true);
    break;

   }
   Model0_ptr += Model0_opsize-2;
   Model0_length -= Model0_opsize;
  }
 }
}
                                ;

static bool Model0_tcp_parse_aligned_timestamp(struct Model0_tcp_sock *Model0_tp, const struct Model0_tcphdr *Model0_th)
{
 const Model0___be32 *Model0_ptr = (const Model0___be32 *)(Model0_th + 1);

 if (*Model0_ptr == (( Model0___be32)(__builtin_constant_p((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10))) ? ((__u32)( (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x000000ffUL) << 24) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32(((1 << 24) | (1 << 16) | (8 << 8) | 10))))) {

  Model0_tp->Model0_rx_opt.Model0_saw_tstamp = 1;
  ++Model0_ptr;
  Model0_tp->Model0_rx_opt.Model0_rcv_tsval = (__builtin_constant_p((__u32)(( __u32)(Model0___be32)(*Model0_ptr))) ? ((__u32)( (((__u32)(( __u32)(Model0___be32)(*Model0_ptr)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model0___be32)(*Model0_ptr)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model0___be32)(*Model0_ptr)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model0___be32)(*Model0_ptr)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32(( __u32)(Model0___be32)(*Model0_ptr)));
  ++Model0_ptr;
  if (*Model0_ptr)
   Model0_tp->Model0_rx_opt.Model0_rcv_tsecr = (__builtin_constant_p((__u32)(( __u32)(Model0___be32)(*Model0_ptr))) ? ((__u32)( (((__u32)(( __u32)(Model0___be32)(*Model0_ptr)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model0___be32)(*Model0_ptr)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model0___be32)(*Model0_ptr)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model0___be32)(*Model0_ptr)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32(( __u32)(Model0___be32)(*Model0_ptr))) - Model0_tp->Model0_tsoffset;
  else
   Model0_tp->Model0_rx_opt.Model0_rcv_tsecr = 0;
  return true;
 }
 return false;
}

/* Fast parse options. This hopes to only see timestamps.
 * If it is wrong it falls back on tcp_parse_options().
 */
static bool Model0_tcp_fast_parse_options(const struct Model0_sk_buff *Model0_skb,
       const struct Model0_tcphdr *Model0_th, struct Model0_tcp_sock *Model0_tp)
{
 /* In the spirit of fast parsing, compare doff directly to constant
	 * values.  Because equality is used, short doff can be ignored here.
	 */
 if (Model0_th->Model0_doff == (sizeof(*Model0_th) / 4)) {
  Model0_tp->Model0_rx_opt.Model0_saw_tstamp = 0;
  return false;
 } else if (Model0_tp->Model0_rx_opt.Model0_tstamp_ok &&
     Model0_th->Model0_doff == ((sizeof(*Model0_th) + 12) / 4)) {
  if (Model0_tcp_parse_aligned_timestamp(Model0_tp, Model0_th))
   return true;
 }

 Model0_tcp_parse_options(Model0_skb, &Model0_tp->Model0_rx_opt, 1, ((void *)0));
 if (Model0_tp->Model0_rx_opt.Model0_saw_tstamp && Model0_tp->Model0_rx_opt.Model0_rcv_tsecr)
  Model0_tp->Model0_rx_opt.Model0_rcv_tsecr -= Model0_tp->Model0_tsoffset;

 return true;
}
/* Sorry, PAWS as specified is broken wrt. pure-ACKs -DaveM
 *
 * It is not fatal. If this ACK does _not_ change critical state (seqs, window)
 * it can pass through stack. So, the following predicate verifies that
 * this segment is not used for anything but congestion avoidance or
 * fast retransmit. Moreover, we even are able to eliminate most of such
 * second order effects, if we apply some small "replay" window (~RTO)
 * to timestamp space.
 *
 * All these measures still do not guarantee that we reject wrapped ACKs
 * on networks with high bandwidth, when sequence space is recycled fastly,
 * but it guarantees that such events will be very rare and do not affect
 * connection seriously. This doesn't look nice, but alas, PAWS is really
 * buggy extension.
 *
 * [ Later note. Even worse! It is buggy for segments _with_ data. RFC
 * states that events when retransmit arrives after original data are rare.
 * It is a blatant lie. VJ forgot about fast retransmit! 8)8) It is
 * the biggest problem on large power networks even with minor reordering.
 * OK, let's give it small replay window. If peer clock is even 1hz, it is safe
 * up to bandwidth of 18Gigabit/sec. 8) ]
 */

static int Model0_tcp_disordered_ack(const struct Model0_sock *Model0_sk, const struct Model0_sk_buff *Model0_skb)
{
 const struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 const struct Model0_tcphdr *Model0_th = Model0_tcp_hdr(Model0_skb);
 Model0_u32 Model0_seq = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq;
 Model0_u32 Model0_ack = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_ack_seq;

 return (/* 1. Pure ACK with correct sequence number. */
  (Model0_th->Model0_ack && Model0_seq == ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq && Model0_seq == Model0_tp->Model0_rcv_nxt) &&

  /* 2. ... and duplicate ACK. */
  Model0_ack == Model0_tp->Model0_snd_una &&

  /* 3. ... and does not update window. */
  !Model0_tcp_may_update_window(Model0_tp, Model0_ack, Model0_seq, (__builtin_constant_p((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_th->Model0_window))) ? ((Model0___u16)( (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_th->Model0_window)) & (Model0___u16)0x00ffU) << 8) | (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_th->Model0_window)) & (Model0___u16)0xff00U) >> 8))) : Model0___fswab16(( Model0___u16)(Model0___be16)(Model0_th->Model0_window))) << Model0_tp->Model0_rx_opt.Model0_snd_wscale) &&

  /* 4. ... and sits in replay window. */
  (Model0_s32)(Model0_tp->Model0_rx_opt.Model0_ts_recent - Model0_tp->Model0_rx_opt.Model0_rcv_tsval) <= (Model0_inet_csk(Model0_sk)->Model0_icsk_rto * 1024) / 1000);
}

static inline __attribute__((no_instrument_function)) bool Model0_tcp_paws_discard(const struct Model0_sock *Model0_sk,
       const struct Model0_sk_buff *Model0_skb)
{
 const struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 return !Model0_tcp_paws_check(&Model0_tp->Model0_rx_opt, 1) &&
        !Model0_tcp_disordered_ack(Model0_sk, Model0_skb);
}

/* Check segment sequence number for validity.
 *
 * Segment controls are considered valid, if the segment
 * fits to the window after truncation to the window. Acceptability
 * of data (and SYN, FIN, of course) is checked separately.
 * See tcp_data_queue(), for example.
 *
 * Also, controls (RST is main one) are accepted using RCV.WUP instead
 * of RCV.NXT. Peer still did not advance his SND.UNA when we
 * delayed ACK, so that hisSND.UNA<=ourRCV.WUP.
 * (borrowed from freebsd)
 */

static inline __attribute__((no_instrument_function)) bool Model0_tcp_sequence(const struct Model0_tcp_sock *Model0_tp, Model0_u32 Model0_seq, Model0_u32 Model0_end_seq)
{
 return !Model0_before(Model0_end_seq, Model0_tp->Model0_rcv_wup) &&
  !Model0_before(Model0_tp->Model0_rcv_nxt + Model0_tcp_receive_window(Model0_tp), Model0_seq);
}

/* When we get a reset we do this. */
void Model0_tcp_reset(struct Model0_sock *Model0_sk)
{
#if CY_ABSTRACT4
    //When a correct RST is received, we terminate our attack since victim connection is not alive any more. Therefore we stop from there.
    Model0_Connection_reset = true;
#else
 /* We want the right error as BSD sees it (and indeed as we do). */
 switch (Model0_sk->Model0___sk_common.Model0_skc_state) {
 case Model0_TCP_SYN_SENT:
  Model0_sk->Model0_sk_err = 111;
  break;
 case Model0_TCP_CLOSE_WAIT:
  Model0_sk->Model0_sk_err = 32;
  break;
 case Model0_TCP_CLOSE:
  return;
 default:
  Model0_sk->Model0_sk_err = 104;
 }
 /* This barrier is coupled with smp_rmb() in tcp_poll() */
 __asm__ __volatile__("": : :"memory");

 if (!Model0_sock_flag(Model0_sk, Model0_SOCK_DEAD))
  Model0_sk->Model0_sk_error_report(Model0_sk);

 Model0_tcp_done(Model0_sk);
#endif
}

/*
 * 	Process the FIN bit. This now behaves as it is supposed to work
 *	and the FIN takes effect when it is validly part of sequence
 *	space. Not before when we get holes.
 *
 *	If we are ESTABLISHED, a received fin moves us to CLOSE-WAIT
 *	(and thence onto LAST-ACK and finally, CLOSE, we never enter
 *	TIME-WAIT)
 *
 *	If we are in FINWAIT-1, a received FIN indicates simultaneous
 *	close and we go into CLOSING (and later onto TIME-WAIT)
 *
 *	If we are in FINWAIT-2, a received FIN moves us to TIME-WAIT.
 */
void Model0_tcp_fin(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 Model0_inet_csk_schedule_ack(Model0_sk);

 Model0_sk->Model0_sk_shutdown |= 1;
 Model0_sock_set_flag(Model0_sk, Model0_SOCK_DONE);

 switch (Model0_sk->Model0___sk_common.Model0_skc_state) {
 case Model0_TCP_SYN_RECV:
 case Model0_TCP_ESTABLISHED:
  /* Move to CLOSE_WAIT */
  Model0_tcp_set_state(Model0_sk, Model0_TCP_CLOSE_WAIT);
  Model0_inet_csk(Model0_sk)->Model0_icsk_ack.Model0_pingpong = 1;
  break;

 case Model0_TCP_CLOSE_WAIT:
 case Model0_TCP_CLOSING:
  /* Received a retransmission of the FIN, do
		 * nothing.
		 */
  break;
 case Model0_TCP_LAST_ACK:
  /* RFC793: Remain in the LAST-ACK state. */
  break;

 case Model0_TCP_FIN_WAIT1:
  /* This case occurs when a simultaneous close
		 * happens, we must ack the received FIN and
		 * enter the CLOSING state.
		 */
  Model0_tcp_send_ack(Model0_sk);
  Model0_tcp_set_state(Model0_sk, Model0_TCP_CLOSING);
  break;
 case Model0_TCP_FIN_WAIT2:
  /* Received a FIN -- send ACK and enter TIME_WAIT. */
  Model0_tcp_send_ack(Model0_sk);
  Model0_tcp_time_wait(Model0_sk, Model0_TCP_TIME_WAIT, 0);
  break;
 default:
  /* Only TCP_LISTEN and TCP_CLOSE are left, in these
		 * cases we should never reach this piece of code.
		 */
  Model0_printk("\001" "3" "TCP: " "%s: Impossible, sk->sk_state=%d\n", __func__, Model0_sk->Model0___sk_common.Model0_skc_state);

  break;
 }

 /* It _is_ possible, that we have something out-of-order _after_ FIN.
	 * Probably, we should reset in this case. For now drop them.
	 */
 Model0___skb_queue_purge(&Model0_tp->Model0_out_of_order_queue);
 if (Model0_tcp_is_sack(Model0_tp))
  Model0_tcp_sack_reset(&Model0_tp->Model0_rx_opt);
 Model0_sk_mem_reclaim(Model0_sk);

 if (!Model0_sock_flag(Model0_sk, Model0_SOCK_DEAD)) {
#if CY_ABSTRACT7
  Model0_sock_def_wakeup(Model0_sk);
#else
  Model0_sk->Model0_sk_state_change(Model0_sk);
#endif

  /* Do not send POLL_HUP for half duplex close. */
  if (Model0_sk->Model0_sk_shutdown == 3 ||
      Model0_sk->Model0___sk_common.Model0_skc_state == Model0_TCP_CLOSE)
   Model0_sk_wake_async(Model0_sk, Model0_SOCK_WAKE_WAITD, ((2 << 16)|6));
  else
   Model0_sk_wake_async(Model0_sk, Model0_SOCK_WAKE_WAITD, ((2 << 16)|1));
 }
}

static inline __attribute__((no_instrument_function)) bool Model0_tcp_sack_extend(struct Model0_tcp_sack_block *Model0_sp, Model0_u32 Model0_seq,
      Model0_u32 Model0_end_seq)
{
 if (!Model0_before(Model0_sp->Model0_end_seq, Model0_seq) && !Model0_before(Model0_end_seq, Model0_sp->Model0_start_seq)) {
  if (Model0_before(Model0_seq, Model0_sp->Model0_start_seq))
   Model0_sp->Model0_start_seq = Model0_seq;
  if (Model0_before(Model0_sp->Model0_end_seq, Model0_end_seq))
   Model0_sp->Model0_end_seq = Model0_end_seq;
  return true;
 }
 return false;
}

static void Model0_tcp_dsack_set(struct Model0_sock *Model0_sk, Model0_u32 Model0_seq, Model0_u32 Model0_end_seq)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 if (Model0_tcp_is_sack(Model0_tp) && Model0_sysctl_tcp_dsack) {
  int Model0_mib_idx;

  if (Model0_before(Model0_seq, Model0_tp->Model0_rcv_nxt))
   Model0_mib_idx = Model0_LINUX_MIB_TCPDSACKOLDSENT;
  else
   Model0_mib_idx = Model0_LINUX_MIB_TCPDSACKOFOSENT;

  (Model0_cy_linux_mib.Model0_mibs[Model0_mib_idx] += 1);

  Model0_tp->Model0_rx_opt.Model0_dsack = 1;
  Model0_tp->Model0_duplicate_sack[0].Model0_start_seq = Model0_seq;
  Model0_tp->Model0_duplicate_sack[0].Model0_end_seq = Model0_end_seq;
 }
}

static void Model0_tcp_dsack_extend(struct Model0_sock *Model0_sk, Model0_u32 Model0_seq, Model0_u32 Model0_end_seq)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 if (!Model0_tp->Model0_rx_opt.Model0_dsack)
  Model0_tcp_dsack_set(Model0_sk, Model0_seq, Model0_end_seq);
 else
  Model0_tcp_sack_extend(Model0_tp->Model0_duplicate_sack, Model0_seq, Model0_end_seq);
}

static void Model0_tcp_send_dupack(struct Model0_sock *Model0_sk, const struct Model0_sk_buff *Model0_skb)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 if (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq != ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq &&
     Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, Model0_tp->Model0_rcv_nxt)) {
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_DELAYEDACKLOST] += 1);
  Model0_tcp_enter_quickack_mode(Model0_sk);

  if (Model0_tcp_is_sack(Model0_tp) && Model0_sysctl_tcp_dsack) {
   Model0_u32 Model0_end_seq = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq;

   if (Model0_before(Model0_tp->Model0_rcv_nxt, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq))
    Model0_end_seq = Model0_tp->Model0_rcv_nxt;
   Model0_tcp_dsack_set(Model0_sk, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, Model0_end_seq);
  }
 }

 Model0_tcp_send_ack(Model0_sk);
}

/* These routines update the SACK block as out-of-order packets arrive or
 * in-order packets close up the sequence space.
 */
static void Model0_tcp_sack_maybe_coalesce(struct Model0_tcp_sock *Model0_tp)
{
 int Model0_this_sack;
 struct Model0_tcp_sack_block *Model0_sp = &Model0_tp->Model0_selective_acks[0];
 struct Model0_tcp_sack_block *Model0_swalk = Model0_sp + 1;

 /* See if the recent change to the first SACK eats into
	 * or hits the sequence space of other SACK blocks, if so coalesce.
	 */
 for (Model0_this_sack = 1; Model0_this_sack < Model0_tp->Model0_rx_opt.Model0_num_sacks;) {
  if (Model0_tcp_sack_extend(Model0_sp, Model0_swalk->Model0_start_seq, Model0_swalk->Model0_end_seq)) {
   int Model0_i;

   /* Zap SWALK, by moving every further SACK up by one slot.
			 * Decrease num_sacks.
			 */
   Model0_tp->Model0_rx_opt.Model0_num_sacks--;
   for (Model0_i = Model0_this_sack; Model0_i < Model0_tp->Model0_rx_opt.Model0_num_sacks; Model0_i++)
    Model0_sp[Model0_i] = Model0_sp[Model0_i + 1];
   continue;
  }
  Model0_this_sack++, Model0_swalk++;
 }
}

static void Model0_tcp_sack_new_ofo_skb(struct Model0_sock *Model0_sk, Model0_u32 Model0_seq, Model0_u32 Model0_end_seq)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_tcp_sack_block *Model0_sp = &Model0_tp->Model0_selective_acks[0];
 int Model0_cur_sacks = Model0_tp->Model0_rx_opt.Model0_num_sacks;
 int Model0_this_sack;

 if (!Model0_cur_sacks)
  goto Model0_new_sack;

 for (Model0_this_sack = 0; Model0_this_sack < Model0_cur_sacks; Model0_this_sack++, Model0_sp++) {
  if (Model0_tcp_sack_extend(Model0_sp, Model0_seq, Model0_end_seq)) {
   /* Rotate this_sack to the first one. */
   for (; Model0_this_sack > 0; Model0_this_sack--, Model0_sp--)
    do { typeof(*Model0_sp) Model0___tmp = (*Model0_sp); (*Model0_sp) = (*(Model0_sp - 1)); (*(Model0_sp - 1)) = Model0___tmp; } while (0);
   if (Model0_cur_sacks > 1)
    Model0_tcp_sack_maybe_coalesce(Model0_tp);
   return;
  }
 }

 /* Could not find an adjacent existing SACK, build a new one,
	 * put it at the front, and shift everyone else down.  We
	 * always know there is at least one SACK present already here.
	 *
	 * If the sack array is full, forget about the last one.
	 */
 if (Model0_this_sack >= 4) {
  Model0_this_sack--;
  Model0_tp->Model0_rx_opt.Model0_num_sacks--;
  Model0_sp--;
 }
 for (; Model0_this_sack > 0; Model0_this_sack--, Model0_sp--)
  *Model0_sp = *(Model0_sp - 1);

Model0_new_sack:
 /* Build the new head SACK, and we're done. */
 Model0_sp->Model0_start_seq = Model0_seq;
 Model0_sp->Model0_end_seq = Model0_end_seq;
 Model0_tp->Model0_rx_opt.Model0_num_sacks++;
}

/* RCV.NXT advances, some SACKs should be eaten. */

static void Model0_tcp_sack_remove(struct Model0_tcp_sock *Model0_tp)
{
 struct Model0_tcp_sack_block *Model0_sp = &Model0_tp->Model0_selective_acks[0];
 int Model0_num_sacks = Model0_tp->Model0_rx_opt.Model0_num_sacks;
 int Model0_this_sack;

 /* Empty ofo queue, hence, all the SACKs are eaten. Clear. */
 if (Model0_skb_queue_empty(&Model0_tp->Model0_out_of_order_queue)) {
  Model0_tp->Model0_rx_opt.Model0_num_sacks = 0;
  return;
 }

 for (Model0_this_sack = 0; Model0_this_sack < Model0_num_sacks;) {
  /* Check if the start of the sack is covered by RCV.NXT. */
  if (!Model0_before(Model0_tp->Model0_rcv_nxt, Model0_sp->Model0_start_seq)) {
   int Model0_i;

   /* RCV.NXT must cover all the block! */
   ({ int Model0___ret_warn_on = !!(Model0_before(Model0_tp->Model0_rcv_nxt, Model0_sp->Model0_end_seq)); __builtin_expect(!!(Model0___ret_warn_on), 0); });

   /* Zap this SACK, by moving forward any other SACKS. */
   for (Model0_i = Model0_this_sack+1; Model0_i < Model0_num_sacks; Model0_i++)
    Model0_tp->Model0_selective_acks[Model0_i-1] = Model0_tp->Model0_selective_acks[Model0_i];
   Model0_num_sacks--;
   continue;
  }
  Model0_this_sack++;
  Model0_sp++;
 }
 Model0_tp->Model0_rx_opt.Model0_num_sacks = Model0_num_sacks;
}

/**
 * tcp_try_coalesce - try to merge skb to prior one
 * @sk: socket
 * @to: prior buffer
 * @from: buffer to add in queue
 * @fragstolen: pointer to boolean
 *
 * Before queueing skb @from after @to, try to merge them
 * to reduce overall memory use and queue lengths, if cost is small.
 * Packets in ofo or receive queues can stay a long time.
 * Better try to coalesce them right now to avoid future collapses.
 * Returns true if caller should free @from instead of queueing it
 */
static bool Model0_tcp_try_coalesce(struct Model0_sock *Model0_sk,
        struct Model0_sk_buff *Model0_to,
        struct Model0_sk_buff *Model0_from,
        bool *Model0_fragstolen)
{
 int Model0_delta;

 *Model0_fragstolen = false;

 /* Its possible this segment overlaps with prior segment in queue */
 if (((struct Model0_tcp_skb_cb *)&((Model0_from)->Model0_cb[0]))->Model0_seq != ((struct Model0_tcp_skb_cb *)&((Model0_to)->Model0_cb[0]))->Model0_end_seq)
  return false;

 if (!Model0_skb_try_coalesce(Model0_to, Model0_from, Model0_fragstolen, &Model0_delta))
  return false;

 Model0_atomic_add(Model0_delta, &Model0_sk->Model0_sk_backlog.Model0_rmem_alloc);
 Model0_sk_mem_charge(Model0_sk, Model0_delta);
 (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPRCVCOALESCE] += 1);
 ((struct Model0_tcp_skb_cb *)&((Model0_to)->Model0_cb[0]))->Model0_end_seq = ((struct Model0_tcp_skb_cb *)&((Model0_from)->Model0_cb[0]))->Model0_end_seq;
 ((struct Model0_tcp_skb_cb *)&((Model0_to)->Model0_cb[0]))->Model0_ack_seq = ((struct Model0_tcp_skb_cb *)&((Model0_from)->Model0_cb[0]))->Model0_ack_seq;
 ((struct Model0_tcp_skb_cb *)&((Model0_to)->Model0_cb[0]))->Model0_tcp_flags |= ((struct Model0_tcp_skb_cb *)&((Model0_from)->Model0_cb[0]))->Model0_tcp_flags;
 return true;
}

static void Model0_tcp_drop(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb)
{
 Model0_sk_drops_add(Model0_sk, Model0_skb);
 Model0___kfree_skb(Model0_skb);
}

/* This one checks to see if we can put data from the
 * out_of_order queue into the receive_queue.
 */
static void Model0_tcp_ofo_queue(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 __u32 Model0_dsack_high = Model0_tp->Model0_rcv_nxt;
 struct Model0_sk_buff *Model0_skb, *Model0_tail;
 bool Model0_fragstolen, Model0_eaten;

 while ((Model0_skb = Model0_skb_peek(&Model0_tp->Model0_out_of_order_queue)) != ((void *)0)) {
  if (Model0_before(Model0_tp->Model0_rcv_nxt, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq))
   break;

  if (Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, Model0_dsack_high)) {
   __u32 Model0_dsack = Model0_dsack_high;
   if (Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq, Model0_dsack_high))
    Model0_dsack_high = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq;
   Model0_tcp_dsack_extend(Model0_sk, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, Model0_dsack);
  }

  Model0___skb_unlink(Model0_skb, &Model0_tp->Model0_out_of_order_queue);
  if (!Model0_before(Model0_tp->Model0_rcv_nxt, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq)) {
   do { if ((Model0_sk) && Model0_sock_flag((Model0_sk), Model0_SOCK_DBG)) Model0_printk("\001" "7" "ofo packet was already received\n"); } while (0);
   Model0_tcp_drop(Model0_sk, Model0_skb);
   continue;
  }
  do { if ((Model0_sk) && Model0_sock_flag((Model0_sk), Model0_SOCK_DBG)) Model0_printk("\001" "7" "ofo requeuing : rcv_next %X seq %X - %X\n", Model0_tp->Model0_rcv_nxt, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq); } while (0);



  Model0_tail = Model0_skb_peek_tail(&Model0_sk->Model0_sk_receive_queue);
  Model0_eaten = Model0_tail && Model0_tcp_try_coalesce(Model0_sk, Model0_tail, Model0_skb, &Model0_fragstolen);
  Model0_tcp_rcv_nxt_update(Model0_tp, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq);
  if (!Model0_eaten)
   Model0___skb_queue_tail(&Model0_sk->Model0_sk_receive_queue, Model0_skb);
  if (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_tcp_flags & 0x01)
   Model0_tcp_fin(Model0_sk);
  if (Model0_eaten)
   Model0_kfree_skb_partial(Model0_skb, Model0_fragstolen);
 }
}

static bool Model0_tcp_prune_ofo_queue(struct Model0_sock *Model0_sk);
static int Model0_tcp_prune_queue(struct Model0_sock *Model0_sk);

static int Model0_tcp_try_rmem_schedule(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb,
     unsigned int Model0_size)
{
 if (Model0_atomic_read(&Model0_sk->Model0_sk_backlog.Model0_rmem_alloc) > Model0_sk->Model0_sk_rcvbuf ||
     !Model0_sk_rmem_schedule(Model0_sk, Model0_skb, Model0_size)) {

  if (Model0_tcp_prune_queue(Model0_sk) < 0)
   return -1;

  if (!Model0_sk_rmem_schedule(Model0_sk, Model0_skb, Model0_size)) {
   if (!Model0_tcp_prune_ofo_queue(Model0_sk))
    return -1;

   if (!Model0_sk_rmem_schedule(Model0_sk, Model0_skb, Model0_size))
    return -1;
  }
 }
 return 0;
}

static void Model0_tcp_data_queue_ofo(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_sk_buff *Model0_skb1;
 Model0_u32 Model0_seq, Model0_end_seq;

 Model0_tcp_ecn_check_ce(Model0_tp, Model0_skb);

 if (__builtin_expect(!!(Model0_tcp_try_rmem_schedule(Model0_sk, Model0_skb, Model0_skb->Model0_truesize)), 0)) {
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPOFODROP] += 1);
  Model0_tcp_drop(Model0_sk, Model0_skb);
  return;
 }

 /* Disable header prediction. */
 Model0_tp->Model0_pred_flags = 0;
 Model0_inet_csk_schedule_ack(Model0_sk);

 (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPOFOQUEUE] += 1);
 do { if ((Model0_sk) && Model0_sock_flag((Model0_sk), Model0_SOCK_DBG)) Model0_printk("\001" "7" "out of order segment: rcv_next %X seq %X - %X\n", Model0_tp->Model0_rcv_nxt, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq); } while (0);


 Model0_skb1 = Model0_skb_peek_tail(&Model0_tp->Model0_out_of_order_queue);
 if (!Model0_skb1) {
  /* Initial out of order segment, build 1 SACK. */
  if (Model0_tcp_is_sack(Model0_tp)) {
   Model0_tp->Model0_rx_opt.Model0_num_sacks = 1;
   Model0_tp->Model0_selective_acks[0].Model0_start_seq = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq;
   Model0_tp->Model0_selective_acks[0].Model0_end_seq =
      ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq;
  }
  Model0___skb_queue_head(&Model0_tp->Model0_out_of_order_queue, Model0_skb);
  goto Model0_end;
 }

 Model0_seq = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq;
 Model0_end_seq = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq;

 if (Model0_seq == ((struct Model0_tcp_skb_cb *)&((Model0_skb1)->Model0_cb[0]))->Model0_end_seq) {
  bool Model0_fragstolen;

  if (!Model0_tcp_try_coalesce(Model0_sk, Model0_skb1, Model0_skb, &Model0_fragstolen)) {
   Model0___skb_queue_after(&Model0_tp->Model0_out_of_order_queue, Model0_skb1, Model0_skb);
  } else {
   Model0_tcp_grow_window(Model0_sk, Model0_skb);
   Model0_kfree_skb_partial(Model0_skb, Model0_fragstolen);
   Model0_skb = ((void *)0);
  }

  if (!Model0_tp->Model0_rx_opt.Model0_num_sacks ||
      Model0_tp->Model0_selective_acks[0].Model0_end_seq != Model0_seq)
   goto Model0_add_sack;

  /* Common case: data arrive in order after hole. */
  Model0_tp->Model0_selective_acks[0].Model0_end_seq = Model0_end_seq;
  goto Model0_end;
 }

 /* Find place to insert this segment. */
 while (1) {
  if (!Model0_before(Model0_seq, ((struct Model0_tcp_skb_cb *)&((Model0_skb1)->Model0_cb[0]))->Model0_seq))
   break;
  if (Model0_skb_queue_is_first(&Model0_tp->Model0_out_of_order_queue, Model0_skb1)) {
   Model0_skb1 = ((void *)0);
   break;
  }
  Model0_skb1 = Model0_skb_queue_prev(&Model0_tp->Model0_out_of_order_queue, Model0_skb1);
 }

 /* Do skb overlap to previous one? */
 if (Model0_skb1 && Model0_before(Model0_seq, ((struct Model0_tcp_skb_cb *)&((Model0_skb1)->Model0_cb[0]))->Model0_end_seq)) {
  if (!Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb1)->Model0_cb[0]))->Model0_end_seq, Model0_end_seq)) {
   /* All the bits are present. Drop. */
   (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPOFOMERGE] += 1);
   Model0_tcp_drop(Model0_sk, Model0_skb);
   Model0_skb = ((void *)0);
   Model0_tcp_dsack_set(Model0_sk, Model0_seq, Model0_end_seq);
   goto Model0_add_sack;
  }
  if (Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb1)->Model0_cb[0]))->Model0_seq, Model0_seq)) {
   /* Partial overlap. */
   Model0_tcp_dsack_set(Model0_sk, Model0_seq,
          ((struct Model0_tcp_skb_cb *)&((Model0_skb1)->Model0_cb[0]))->Model0_end_seq);
  } else {
   if (Model0_skb_queue_is_first(&Model0_tp->Model0_out_of_order_queue,
            Model0_skb1))
    Model0_skb1 = ((void *)0);
   else
    Model0_skb1 = Model0_skb_queue_prev(
     &Model0_tp->Model0_out_of_order_queue,
     Model0_skb1);
  }
 }
 if (!Model0_skb1)
  Model0___skb_queue_head(&Model0_tp->Model0_out_of_order_queue, Model0_skb);
 else
  Model0___skb_queue_after(&Model0_tp->Model0_out_of_order_queue, Model0_skb1, Model0_skb);

 /* And clean segments covered by new one as whole. */
 while (!Model0_skb_queue_is_last(&Model0_tp->Model0_out_of_order_queue, Model0_skb)) {
  Model0_skb1 = Model0_skb_queue_next(&Model0_tp->Model0_out_of_order_queue, Model0_skb);

  if (!Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb1)->Model0_cb[0]))->Model0_seq, Model0_end_seq))
   break;
  if (Model0_before(Model0_end_seq, ((struct Model0_tcp_skb_cb *)&((Model0_skb1)->Model0_cb[0]))->Model0_end_seq)) {
   Model0_tcp_dsack_extend(Model0_sk, ((struct Model0_tcp_skb_cb *)&((Model0_skb1)->Model0_cb[0]))->Model0_seq,
      Model0_end_seq);
   break;
  }
  Model0___skb_unlink(Model0_skb1, &Model0_tp->Model0_out_of_order_queue);
  Model0_tcp_dsack_extend(Model0_sk, ((struct Model0_tcp_skb_cb *)&((Model0_skb1)->Model0_cb[0]))->Model0_seq,
     ((struct Model0_tcp_skb_cb *)&((Model0_skb1)->Model0_cb[0]))->Model0_end_seq);
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPOFOMERGE] += 1);
  Model0_tcp_drop(Model0_sk, Model0_skb1);
 }

Model0_add_sack:
 if (Model0_tcp_is_sack(Model0_tp))
  Model0_tcp_sack_new_ofo_skb(Model0_sk, Model0_seq, Model0_end_seq);
Model0_end:
 if (Model0_skb) {
  Model0_tcp_grow_window(Model0_sk, Model0_skb);
  Model0_skb_set_owner_r(Model0_skb, Model0_sk);
 }
}

static int Model0_tcp_queue_rcv(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb, int Model0_hdrlen,
    bool *Model0_fragstolen)
{
 int Model0_eaten;
 struct Model0_sk_buff *Model0_tail = Model0_skb_peek_tail(&Model0_sk->Model0_sk_receive_queue);

 Model0___skb_pull(Model0_skb, Model0_hdrlen);
 Model0_eaten = (Model0_tail &&
   Model0_tcp_try_coalesce(Model0_sk, Model0_tail, Model0_skb, Model0_fragstolen)) ? 1 : 0;
 Model0_tcp_rcv_nxt_update(Model0_tcp_sk(Model0_sk), ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq);
 if (!Model0_eaten) {
  Model0___skb_queue_tail(&Model0_sk->Model0_sk_receive_queue, Model0_skb);
  Model0_skb_set_owner_r(Model0_skb, Model0_sk);
 }
 return Model0_eaten;
}

int Model0_tcp_send_rcvq(struct Model0_sock *Model0_sk, struct Model0_msghdr *Model0_msg, Model0_size_t Model0_size)
{
 struct Model0_sk_buff *Model0_skb;
 int err = -12;
 int Model0_data_len = 0;
 bool Model0_fragstolen;

 if (Model0_size == 0)
  return 0;

 if (Model0_size > ((1UL) << 12)) {
  int Model0_npages = ({ Model0_size_t Model0___min1 = (Model0_size >> 12); Model0_size_t Model0___min2 = ((65536/((1UL) << 12) + 1)); Model0___min1 < Model0___min2 ? Model0___min1: Model0___min2; });

  Model0_data_len = Model0_npages << 12;
  Model0_size = Model0_data_len + (Model0_size & ~(~(((1UL) << 12)-1)));
 }
 Model0_skb = Model0_alloc_skb_with_frags(Model0_size - Model0_data_len, Model0_data_len,
       3,
       &err, Model0_sk->Model0_sk_allocation);
 if (!Model0_skb)
  goto err;

 Model0_skb_put(Model0_skb, Model0_size - Model0_data_len);
 Model0_skb->Model0_data_len = Model0_data_len;
 Model0_skb->Model0_len = Model0_size;

 if (Model0_tcp_try_rmem_schedule(Model0_sk, Model0_skb, Model0_skb->Model0_truesize))
  goto Model0_err_free;

 err = Model0_skb_copy_datagram_from_iter(Model0_skb, 0, &Model0_msg->Model0_msg_iter, Model0_size);
 if (err)
  goto Model0_err_free;

 ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq = Model0_tcp_sk(Model0_sk)->Model0_rcv_nxt;
 ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq + Model0_size;
 ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_ack_seq = Model0_tcp_sk(Model0_sk)->Model0_snd_una - 1;

 if (Model0_tcp_queue_rcv(Model0_sk, Model0_skb, 0, &Model0_fragstolen)) {
  ({ int Model0___ret_warn_on = !!(Model0_fragstolen); __builtin_expect(!!(Model0___ret_warn_on), 0); }); /* should not happen */
  Model0___kfree_skb(Model0_skb);
 }
 return Model0_size;

Model0_err_free:
 Model0_kfree_skb(Model0_skb);
err:
 return err;

}

static void Model0_tcp_data_queue(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 bool Model0_fragstolen = false;
 int Model0_eaten = -1;

 if (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq == ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq) {
  Model0___kfree_skb(Model0_skb);
  return;
 }
 Model0_skb_dst_drop(Model0_skb);
 Model0___skb_pull(Model0_skb, Model0_tcp_hdr(Model0_skb)->Model0_doff * 4);

 Model0_tcp_ecn_accept_cwr(Model0_tp, Model0_skb);

 Model0_tp->Model0_rx_opt.Model0_dsack = 0;

 /*  Queue data for delivery to the user.
	 *  Packets in sequence go to the receive queue.
	 *  Out of sequence packets to the out_of_order_queue.
	 */
 if (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq == Model0_tp->Model0_rcv_nxt) {
  if (Model0_tcp_receive_window(Model0_tp) == 0)
   goto Model0_out_of_window;

  /* Ok. In sequence. In window. */
#if CY_ABSTRACT1 //TODO: double check
#else
  if (Model0_tp->Model0_ucopy.Model0_task == Model0_get_current() &&
      Model0_tp->Model0_copied_seq == Model0_tp->Model0_rcv_nxt && Model0_tp->Model0_ucopy.Model0_len &&
      Model0_sock_owned_by_user(Model0_sk) && !Model0_tp->Model0_urg_data) {
   int Model0_chunk = ({ unsigned int Model0___min1 = (Model0_skb->Model0_len); unsigned int Model0___min2 = (Model0_tp->Model0_ucopy.Model0_len); Model0___min1 < Model0___min2 ? Model0___min1: Model0___min2; });


   do { Model0_get_current()->Model0_state = (0); } while (0);

   if (!Model0_skb_copy_datagram_msg(Model0_skb, 0, Model0_tp->Model0_ucopy.Model0_msg, Model0_chunk)) {
    Model0_tp->Model0_ucopy.Model0_len -= Model0_chunk;
    Model0_tp->Model0_copied_seq += Model0_chunk;
    Model0_eaten = (Model0_chunk == Model0_skb->Model0_len);
    Model0_tcp_rcv_space_adjust(Model0_sk);
   }
  }
#endif
  if (Model0_eaten <= 0) {
Model0_queue_and_out:
   if (Model0_eaten < 0) {
    if (Model0_skb_queue_len(&Model0_sk->Model0_sk_receive_queue) == 0)
     Model0_sk_forced_mem_schedule(Model0_sk, Model0_skb->Model0_truesize);
    else if (Model0_tcp_try_rmem_schedule(Model0_sk, Model0_skb, Model0_skb->Model0_truesize))
     goto Model0_drop;
   }
   Model0_eaten = Model0_tcp_queue_rcv(Model0_sk, Model0_skb, 0, &Model0_fragstolen);
  }
  Model0_tcp_rcv_nxt_update(Model0_tp, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq);
  if (Model0_skb->Model0_len)
   Model0_tcp_event_data_recv(Model0_sk, Model0_skb);
#if !CY_ABSTRACT1
  if (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_tcp_flags & 0x01)
   Model0_tcp_fin(Model0_sk);
#endif

  if (!Model0_skb_queue_empty(&Model0_tp->Model0_out_of_order_queue)) {
   Model0_tcp_ofo_queue(Model0_sk);

   /* RFC2581. 4.2. SHOULD send immediate ACK, when
			 * gap in queue is filled.
			 */
   if (Model0_skb_queue_empty(&Model0_tp->Model0_out_of_order_queue))
    Model0_inet_csk(Model0_sk)->Model0_icsk_ack.Model0_pingpong = 0;
  }
#if !CY_ABSTRACT1
  if (Model0_tp->Model0_rx_opt.Model0_num_sacks)
   Model0_tcp_sack_remove(Model0_tp);
#endif
  Model0_tcp_fast_path_check(Model0_sk);

  if (Model0_eaten > 0)
   Model0_kfree_skb_partial(Model0_skb, Model0_fragstolen);
  if (!Model0_sock_flag(Model0_sk, Model0_SOCK_DEAD))
#if CY_ABSTRACT1
  {
    //TODO: better to replace the function pointer, and call the function
    //so far only ignore such function, since we won't consider async process
  }
#else
   Model0_sk->Model0_sk_data_ready(Model0_sk);
#endif
  return;
 }

 if (!Model0_before(Model0_tp->Model0_rcv_nxt, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq)) {
  /* A retransmit, 2nd most common case.  Force an immediate ack. */
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_DELAYEDACKLOST] += 1);
  Model0_tcp_dsack_set(Model0_sk, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq);

Model0_out_of_window:
  Model0_tcp_enter_quickack_mode(Model0_sk);
  Model0_inet_csk_schedule_ack(Model0_sk);
Model0_drop:
  Model0_tcp_drop(Model0_sk, Model0_skb);
  return;
 }

 /* Out of window. F.e. zero window probe. */
 if (!Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, Model0_tp->Model0_rcv_nxt + Model0_tcp_receive_window(Model0_tp)))
  goto Model0_out_of_window;

 Model0_tcp_enter_quickack_mode(Model0_sk);

 if (Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, Model0_tp->Model0_rcv_nxt)) {
  /* Partial packet, seq < rcv_next < end_seq */
  do { if ((Model0_sk) && Model0_sock_flag((Model0_sk), Model0_SOCK_DBG)) Model0_printk("\001" "7" "partial packet: rcv_next %X seq %X - %X\n", Model0_tp->Model0_rcv_nxt, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq); } while (0);



  Model0_tcp_dsack_set(Model0_sk, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, Model0_tp->Model0_rcv_nxt);

  /* If window is closed, drop tail of packet. But after
		 * remembering D-SACK for its head made in previous line.
		 */
  if (!Model0_tcp_receive_window(Model0_tp))
   goto Model0_out_of_window;
  goto Model0_queue_and_out;
 }

 Model0_tcp_data_queue_ofo(Model0_sk, Model0_skb);
}

static struct Model0_sk_buff *Model0_tcp_collapse_one(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb,
     struct Model0_sk_buff_head *Model0_list)
{
 struct Model0_sk_buff *Model0_next = ((void *)0);

 if (!Model0_skb_queue_is_last(Model0_list, Model0_skb))
  Model0_next = Model0_skb_queue_next(Model0_list, Model0_skb);

 Model0___skb_unlink(Model0_skb, Model0_list);
 Model0___kfree_skb(Model0_skb);
 (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPRCVCOLLAPSED] += 1);

 return Model0_next;
}

/* Collapse contiguous sequence of skbs head..tail with
 * sequence numbers start..end.
 *
 * If tail is NULL, this means until the end of the list.
 *
 * Segments with FIN/SYN are not collapsed (only because this
 * simplifies code)
 */
static void
Model0_tcp_collapse(struct Model0_sock *Model0_sk, struct Model0_sk_buff_head *Model0_list,
      struct Model0_sk_buff *Model0_head, struct Model0_sk_buff *Model0_tail,
      Model0_u32 Model0_start, Model0_u32 Model0_end)
{
 struct Model0_sk_buff *Model0_skb, *Model0_n;
 bool Model0_end_of_skbs;

 /* First, check that queue is collapsible and find
	 * the point where collapsing can be useful. */
 Model0_skb = Model0_head;
Model0_restart:
 Model0_end_of_skbs = true;
 for (Model0_n = Model0_skb->Model0_next; Model0_skb != (struct Model0_sk_buff *)(Model0_list); Model0_skb = Model0_n, Model0_n = Model0_skb->Model0_next) {
  if (Model0_skb == Model0_tail)
   break;
  /* No new bits? It is possible on ofo queue. */
  if (!Model0_before(Model0_start, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq)) {
   Model0_skb = Model0_tcp_collapse_one(Model0_sk, Model0_skb, Model0_list);
   if (!Model0_skb)
    break;
   goto Model0_restart;
  }

  /* The first skb to collapse is:
		 * - not SYN/FIN and
		 * - bloated or contains data before "start" or
		 *   overlaps to the next one.
		 */
  if (!(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_tcp_flags & (0x02 | 0x01)) &&
      (Model0_tcp_win_from_space(Model0_skb->Model0_truesize) > Model0_skb->Model0_len ||
       Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, Model0_start))) {
   Model0_end_of_skbs = false;
   break;
  }

  if (!Model0_skb_queue_is_last(Model0_list, Model0_skb)) {
   struct Model0_sk_buff *Model0_next = Model0_skb_queue_next(Model0_list, Model0_skb);
   if (Model0_next != Model0_tail &&
       ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq != ((struct Model0_tcp_skb_cb *)&((Model0_next)->Model0_cb[0]))->Model0_seq) {
    Model0_end_of_skbs = false;
    break;
   }
  }

  /* Decided to skip this, advance start seq. */
  Model0_start = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq;
 }
 if (Model0_end_of_skbs ||
     (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_tcp_flags & (0x02 | 0x01)))
  return;

 while (Model0_before(Model0_start, Model0_end)) {
  int Model0_copy = ({ int Model0___min1 = ((((((1UL) << 12) << (0)) - (0)) - ((((sizeof(struct Model0_skb_shared_info))) + ((typeof((sizeof(struct Model0_skb_shared_info))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model0_skb_shared_info))))(((1 << (6)))) - 1)))); int Model0___min2 = (Model0_end - Model0_start); Model0___min1 < Model0___min2 ? Model0___min1: Model0___min2; });
  struct Model0_sk_buff *Model0_nskb;

  Model0_nskb = Model0_alloc_skb(Model0_copy, ((( Model0_gfp_t)0x20u)|(( Model0_gfp_t)0x80000u)|(( Model0_gfp_t)0x2000000u)));
  if (!Model0_nskb)
   return;

  ({ Model0_size_t Model0___len = (sizeof(Model0_skb->Model0_cb)); void *Model0___ret; if (__builtin_constant_p(sizeof(Model0_skb->Model0_cb)) && Model0___len >= 64) Model0___ret = Model0___memcpy((Model0_nskb->Model0_cb), (Model0_skb->Model0_cb), Model0___len); else Model0___ret = __builtin_memcpy((Model0_nskb->Model0_cb), (Model0_skb->Model0_cb), Model0___len); Model0___ret; });
  ((struct Model0_tcp_skb_cb *)&((Model0_nskb)->Model0_cb[0]))->Model0_seq = ((struct Model0_tcp_skb_cb *)&((Model0_nskb)->Model0_cb[0]))->Model0_end_seq = Model0_start;
  Model0___skb_queue_before(Model0_list, Model0_skb, Model0_nskb);
  Model0_skb_set_owner_r(Model0_nskb, Model0_sk);

  /* Copy data, releasing collapsed skbs. */
  while (Model0_copy > 0) {
   int Model0_offset = Model0_start - ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq;
   int Model0_size = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq - Model0_start;

   do { if (Model0_offset < 0) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);
   if (Model0_size > 0) {
    Model0_size = ({ typeof(Model0_copy) Model0__min1 = (Model0_copy); typeof(Model0_size) Model0__min2 = (Model0_size); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
    if (Model0_skb_copy_bits(Model0_skb, Model0_offset, Model0_skb_put(Model0_nskb, Model0_size), Model0_size))
     do { asm volatile("ud2"); do { } while (1); } while (0);
    ((struct Model0_tcp_skb_cb *)&((Model0_nskb)->Model0_cb[0]))->Model0_end_seq += Model0_size;
    Model0_copy -= Model0_size;
    Model0_start += Model0_size;
   }
   if (!Model0_before(Model0_start, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq)) {
    Model0_skb = Model0_tcp_collapse_one(Model0_sk, Model0_skb, Model0_list);
    if (!Model0_skb ||
        Model0_skb == Model0_tail ||
        (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_tcp_flags & (0x02 | 0x01)))
     return;
   }
  }
 }
}

/* Collapse ofo queue. Algorithm: select contiguous sequence of skbs
 * and tcp_collapse() them until all the queue is collapsed.
 */
static void Model0_tcp_collapse_ofo_queue(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_sk_buff *Model0_skb = Model0_skb_peek(&Model0_tp->Model0_out_of_order_queue);
 struct Model0_sk_buff *Model0_head;
 Model0_u32 Model0_start, Model0_end;

 if (!Model0_skb)
  return;

 Model0_start = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq;
 Model0_end = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq;
 Model0_head = Model0_skb;

 for (;;) {
  struct Model0_sk_buff *Model0_next = ((void *)0);

  if (!Model0_skb_queue_is_last(&Model0_tp->Model0_out_of_order_queue, Model0_skb))
   Model0_next = Model0_skb_queue_next(&Model0_tp->Model0_out_of_order_queue, Model0_skb);
  Model0_skb = Model0_next;

  /* Segment is terminated when we see gap or when
		 * we are at the end of all the queue. */
  if (!Model0_skb ||
      Model0_before(Model0_end, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq) ||
      Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq, Model0_start)) {
   Model0_tcp_collapse(Model0_sk, &Model0_tp->Model0_out_of_order_queue,
         Model0_head, Model0_skb, Model0_start, Model0_end);
   Model0_head = Model0_skb;
   if (!Model0_skb)
    break;
   /* Start new segment */
   Model0_start = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq;
   Model0_end = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq;
  } else {
   if (Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, Model0_start))
    Model0_start = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq;
   if (Model0_before(Model0_end, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq))
    Model0_end = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq;
  }
 }
}

/*
 * Purge the out-of-order queue.
 * Return true if queue was pruned.
 */
static bool Model0_tcp_prune_ofo_queue(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 bool Model0_res = false;

 if (!Model0_skb_queue_empty(&Model0_tp->Model0_out_of_order_queue)) {
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_OFOPRUNED] += 1);
  Model0___skb_queue_purge(&Model0_tp->Model0_out_of_order_queue);

  /* Reset SACK state.  A conforming SACK implementation will
		 * do the same at a timeout based retransmit.  When a connection
		 * is in a sad state like this, we care only about integrity
		 * of the connection not performance.
		 */
  if (Model0_tp->Model0_rx_opt.Model0_sack_ok)
   Model0_tcp_sack_reset(&Model0_tp->Model0_rx_opt);
  Model0_sk_mem_reclaim(Model0_sk);
  Model0_res = true;
 }
 return Model0_res;
}

/* Reduce allocated memory if we can, trying to get
 * the socket within its memory limits again.
 *
 * Return less than zero if we should start dropping frames
 * until the socket owning process reads some of the data
 * to stabilize the situation.
 */
static int Model0_tcp_prune_queue(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 do { if ((Model0_sk) && Model0_sock_flag((Model0_sk), Model0_SOCK_DBG)) Model0_printk("\001" "7" "prune_queue: c=%x\n", Model0_tp->Model0_copied_seq); } while (0);

 (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_PRUNECALLED] += 1);

 if (Model0_atomic_read(&Model0_sk->Model0_sk_backlog.Model0_rmem_alloc) >= Model0_sk->Model0_sk_rcvbuf)
  Model0_tcp_clamp_window(Model0_sk);
 else if (Model0_tcp_under_memory_pressure(Model0_sk))
  Model0_tp->Model0_rcv_ssthresh = ({ typeof(Model0_tp->Model0_rcv_ssthresh) Model0__min1 = (Model0_tp->Model0_rcv_ssthresh); typeof(4U * Model0_tp->Model0_advmss) Model0__min2 = (4U * Model0_tp->Model0_advmss); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });

 Model0_tcp_collapse_ofo_queue(Model0_sk);
 if (!Model0_skb_queue_empty(&Model0_sk->Model0_sk_receive_queue))
  Model0_tcp_collapse(Model0_sk, &Model0_sk->Model0_sk_receive_queue,
        Model0_skb_peek(&Model0_sk->Model0_sk_receive_queue),
        ((void *)0),
        Model0_tp->Model0_copied_seq, Model0_tp->Model0_rcv_nxt);
 Model0_sk_mem_reclaim(Model0_sk);

 if (Model0_atomic_read(&Model0_sk->Model0_sk_backlog.Model0_rmem_alloc) <= Model0_sk->Model0_sk_rcvbuf)
  return 0;

 /* Collapsing did not help, destructive actions follow.
	 * This must not ever occur. */

 Model0_tcp_prune_ofo_queue(Model0_sk);

 if (Model0_atomic_read(&Model0_sk->Model0_sk_backlog.Model0_rmem_alloc) <= Model0_sk->Model0_sk_rcvbuf)
  return 0;

 /* If we are really being abused, tell the caller to silently
	 * drop receive data on the floor.  It will get retransmitted
	 * and hopefully then we'll have sufficient space.
	 */
 (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_RCVPRUNED] += 1);

 /* Massive buffer overcommit. */
 Model0_tp->Model0_pred_flags = 0;
 return -1;
}

static bool Model0_tcp_should_expand_sndbuf(const struct Model0_sock *Model0_sk)
{
 const struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 /* If the user specified a specific send buffer setting, do
	 * not modify it.
	 */
 if (Model0_sk->Model0_sk_userlocks & 1)
  return false;

 /* If we are under global TCP memory pressure, do not expand.  */
 if (Model0_tcp_under_memory_pressure(Model0_sk))
  return false;

 /* If we are under soft global TCP memory pressure, do not expand.  */
 if (Model0_sk_memory_allocated(Model0_sk) >= Model0_sk_prot_mem_limits(Model0_sk, 0))
  return false;

 /* If we filled the congestion window, do not expand.  */
 if (Model0_tcp_packets_in_flight(Model0_tp) >= Model0_tp->Model0_snd_cwnd)
  return false;

 return true;
}

/* When incoming ACK allowed to free some skb from write_queue,
 * we remember this event in flag SOCK_QUEUE_SHRUNK and wake up socket
 * on the exit from tcp input handler.
 *
 * PROBLEM: sndbuf expansion does not work well with largesend.
 */
static void Model0_tcp_new_space(struct Model0_sock *Model0_sk)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 if (Model0_tcp_should_expand_sndbuf(Model0_sk)) {
  Model0_tcp_sndbuf_expand(Model0_sk);
  Model0_tp->Model0_snd_cwnd_stamp = ((__u32)(Model0_jiffies));
 }

 Model0_sk->Model0_sk_write_space(Model0_sk);
}

static void Model0_tcp_check_space(struct Model0_sock *Model0_sk)
{
#if !CY_ABSTRACT1
 if (Model0_sock_flag(Model0_sk, Model0_SOCK_QUEUE_SHRUNK)) {
  Model0_sock_reset_flag(Model0_sk, Model0_SOCK_QUEUE_SHRUNK);
  /* pairs with tcp_poll() */
  __asm__ __volatile__("": : :"memory");
  if (Model0_sk->Model0_sk_socket &&
      (__builtin_constant_p((2)) ? Model0_constant_test_bit((2), (&Model0_sk->Model0_sk_socket->Model0_flags)) : Model0_variable_test_bit((2), (&Model0_sk->Model0_sk_socket->Model0_flags))))
   Model0_tcp_new_space(Model0_sk);
 }
#endif
}

static inline __attribute__((no_instrument_function)) void Model0_tcp_data_snd_check(struct Model0_sock *Model0_sk)
{
 Model0_tcp_push_pending_frames(Model0_sk);
 Model0_tcp_check_space(Model0_sk);
}

/*
 * Check if sending an ack is needed.
 */
static void Model0___tcp_ack_snd_check(struct Model0_sock *Model0_sk, int Model0_ofo_possible)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

     /* More than one full frame received... */
 if (((Model0_tp->Model0_rcv_nxt - Model0_tp->Model0_rcv_wup) > Model0_inet_csk(Model0_sk)->Model0_icsk_ack.Model0_rcv_mss &&
      /* ... and right edge of window advances far enough.
	      * (tcp_recvmsg() will send ACK otherwise). Or...
	      */
      Model0___tcp_select_window(Model0_sk) >= Model0_tp->Model0_rcv_wnd) ||
     /* We ACK each frame or... */
     Model0_tcp_in_quickack_mode(Model0_sk) ||
     /* We have out of order data. */
     (Model0_ofo_possible && Model0_skb_peek(&Model0_tp->Model0_out_of_order_queue))) {
  /* Then ack it now */
  Model0_tcp_send_ack(Model0_sk);
 } else {
  /* Else, send delayed ack. */
  Model0_tcp_send_delayed_ack(Model0_sk);
 }
}

static inline __attribute__((no_instrument_function)) void Model0_tcp_ack_snd_check(struct Model0_sock *Model0_sk)
{
 if (!Model0_inet_csk_ack_scheduled(Model0_sk)) {
  /* We sent a data segment already. */
  return;
 }
 Model0___tcp_ack_snd_check(Model0_sk, 1);
}

/*
 *	This routine is only called when we have urgent data
 *	signaled. Its the 'slow' part of tcp_urg. It could be
 *	moved inline now as tcp_urg is only called from one
 *	place. We handle URGent data wrong. We have to - as
 *	BSD still doesn't use the correction from RFC961.
 *	For 1003.1g we should support a new option TCP_STDURG to permit
 *	either form (or just set the sysctl tcp_stdurg).
 */

static void Model0_tcp_check_urg(struct Model0_sock *Model0_sk, const struct Model0_tcphdr *Model0_th)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 Model0_u32 Model0_ptr = (__builtin_constant_p((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_th->Model0_urg_ptr))) ? ((Model0___u16)( (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_th->Model0_urg_ptr)) & (Model0___u16)0x00ffU) << 8) | (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_th->Model0_urg_ptr)) & (Model0___u16)0xff00U) >> 8))) : Model0___fswab16(( Model0___u16)(Model0___be16)(Model0_th->Model0_urg_ptr)));

 if (Model0_ptr && !Model0_sysctl_tcp_stdurg)
  Model0_ptr--;
 Model0_ptr += (__builtin_constant_p((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq))) ? ((__u32)( (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32(( __u32)(Model0___be32)(Model0_th->Model0_seq)));

 /* Ignore urgent data that we've already seen and read. */
 if (Model0_before(Model0_ptr, Model0_tp->Model0_copied_seq))
  return;

 /* Do not replay urg ptr.
	 *
	 * NOTE: interesting situation not covered by specs.
	 * Misbehaving sender may send urg ptr, pointing to segment,
	 * which we already have in ofo queue. We are not able to fetch
	 * such data and will stay in TCP_URG_NOTYET until will be eaten
	 * by recvmsg(). Seems, we are not obliged to handle such wicked
	 * situations. But it is worth to think about possibility of some
	 * DoSes using some hypothetical application level deadlock.
	 */
 if (Model0_before(Model0_ptr, Model0_tp->Model0_rcv_nxt))
  return;

 /* Do we already have a newer (or duplicate) urgent pointer? */
 if (Model0_tp->Model0_urg_data && !Model0_before(Model0_tp->Model0_urg_seq, Model0_ptr))
  return;

 /* Tell the world about our new urgent pointer. */
 Model0_sk_send_sigurg(Model0_sk);

 /* We may be adding urgent data when the last byte read was
	 * urgent. To do this requires some care. We cannot just ignore
	 * tp->copied_seq since we would read the last urgent byte again
	 * as data, nor can we alter copied_seq until this data arrives
	 * or we break the semantics of SIOCATMARK (and thus sockatmark())
	 *
	 * NOTE. Double Dutch. Rendering to plain English: author of comment
	 * above did something sort of 	send("A", MSG_OOB); send("B", MSG_OOB);
	 * and expect that both A and B disappear from stream. This is _wrong_.
	 * Though this happens in BSD with high probability, this is occasional.
	 * Any application relying on this is buggy. Note also, that fix "works"
	 * only in this artificial test. Insert some normal data between A and B and we will
	 * decline of BSD again. Verdict: it is better to remove to trap
	 * buggy users.
	 */
 if (Model0_tp->Model0_urg_seq == Model0_tp->Model0_copied_seq && Model0_tp->Model0_urg_data &&
     !Model0_sock_flag(Model0_sk, Model0_SOCK_URGINLINE) && Model0_tp->Model0_copied_seq != Model0_tp->Model0_rcv_nxt) {
  struct Model0_sk_buff *Model0_skb = Model0_skb_peek(&Model0_sk->Model0_sk_receive_queue);
  Model0_tp->Model0_copied_seq++;
  if (Model0_skb && !Model0_before(Model0_tp->Model0_copied_seq, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq)) {
   Model0___skb_unlink(Model0_skb, &Model0_sk->Model0_sk_receive_queue);
   Model0___kfree_skb(Model0_skb);
  }
 }

 Model0_tp->Model0_urg_data = 0x0200;
 Model0_tp->Model0_urg_seq = Model0_ptr;

 /* Disable header prediction. */
 Model0_tp->Model0_pred_flags = 0;
}

/* This is the 'fast' part of urgent handling. */
static void Model0_tcp_urg(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb, const struct Model0_tcphdr *Model0_th)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);

 /* Check if we get a new urgent pointer - normally not. */
 if (Model0_th->Model0_urg)
  Model0_tcp_check_urg(Model0_sk, Model0_th);

 /* Do we wait for any urgent data? - normally not... */
 if (Model0_tp->Model0_urg_data == 0x0200) {
  Model0_u32 Model0_ptr = Model0_tp->Model0_urg_seq - (__builtin_constant_p((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq))) ? ((__u32)( (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model0___be32)(Model0_th->Model0_seq)) & (__u32)0xff000000UL) >> 24))) : Model0___fswab32(( __u32)(Model0___be32)(Model0_th->Model0_seq))) + (Model0_th->Model0_doff * 4) -
     Model0_th->Model0_syn;

  /* Is the urgent pointer pointing into this packet? */
  if (Model0_ptr < Model0_skb->Model0_len) {
   Model0_u8 Model0_tmp;
   if (Model0_skb_copy_bits(Model0_skb, Model0_ptr, &Model0_tmp, 1))
    do { asm volatile("ud2"); do { } while (1); } while (0);
   Model0_tp->Model0_urg_data = 0x0100 | Model0_tmp;
   if (!Model0_sock_flag(Model0_sk, Model0_SOCK_DEAD))
#if CY_ABSTRACT7
    Model0_sock_def_readable(Model0_sk);
#else
    Model0_sk->Model0_sk_data_ready(Model0_sk);
#endif
  }
 }
}

static int Model0_tcp_copy_to_iovec(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb, int Model0_hlen)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 int Model0_chunk = Model0_skb->Model0_len - Model0_hlen;
 int err;

 if (Model0_skb_csum_unnecessary(Model0_skb))
  err = Model0_skb_copy_datagram_msg(Model0_skb, Model0_hlen, Model0_tp->Model0_ucopy.Model0_msg, Model0_chunk);
 else
  err = Model0_skb_copy_and_csum_datagram_msg(Model0_skb, Model0_hlen, Model0_tp->Model0_ucopy.Model0_msg);

 if (!err) {
  Model0_tp->Model0_ucopy.Model0_len -= Model0_chunk;
  Model0_tp->Model0_copied_seq += Model0_chunk;
  Model0_tcp_rcv_space_adjust(Model0_sk);
 }

 return err;
}

/* Does PAWS and seqno based validation of an incoming segment, flags will
 * play significant role here.
 */
static bool Model0_tcp_validate_incoming(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb,
      const struct Model0_tcphdr *Model0_th, int Model0_syn_inerr)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 bool Model0_rst_seq_match = false;
#if !CY_ABSTRACT1
 /* RFC1323: H1. Apply PAWS check first. */
 if (Model0_tcp_fast_parse_options(Model0_skb, Model0_th, Model0_tp) && Model0_tp->Model0_rx_opt.Model0_saw_tstamp &&
     Model0_tcp_paws_discard(Model0_sk, Model0_skb)) {
  if (!Model0_th->Model0_rst) {
   (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_PAWSESTABREJECTED] += 1);
   if (!Model0_tcp_oow_rate_limited(Model0_sock_net(Model0_sk), Model0_skb,
        Model0_LINUX_MIB_TCPACKSKIPPEDPAWS,
        &Model0_tp->Model0_last_oow_ack_time))
    Model0_tcp_send_dupack(Model0_sk, Model0_skb);
   goto Model0_discard;
  }
  /* Reset is accepted even if it did not pass PAWS. */
 }
#endif
 /* Step 1: check sequence number */
 if (!Model0_tcp_sequence(Model0_tp, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq)) {
  /* RFC793, page 37: "In all states except SYN-SENT, all reset
		 * (RST) segments are validated by checking their SEQ-fields."
		 * And page 69: "If an incoming segment is not acceptable,
		 * an acknowledgment should be sent in reply (unless the RST
		 * bit is set, if so drop the segment and return)".
		 */
  if (!Model0_th->Model0_rst) {
   if (Model0_th->Model0_syn)
    goto Model0_syn_challenge;
   if (!Model0_tcp_oow_rate_limited(Model0_sock_net(Model0_sk), Model0_skb,
        Model0_LINUX_MIB_TCPACKSKIPPEDSEQ,
        &Model0_tp->Model0_last_oow_ack_time))
    Model0_tcp_send_dupack(Model0_sk, Model0_skb);
  }
  goto Model0_discard;
 }

 /* Step 2: check RST bit */
 if (Model0_th->Model0_rst) {
  /* RFC 5961 3.2 (extend to match against SACK too if available):
		 * If seq num matches RCV.NXT or the right-most SACK block,
		 * then
		 *     RESET the connection
		 * else
		 *     Send a challenge ACK
		 */
  if (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq == Model0_tp->Model0_rcv_nxt) {
   Model0_rst_seq_match = true;
  } 
#if !CY_ABSTRACT1
else if (Model0_tcp_is_sack(Model0_tp) && Model0_tp->Model0_rx_opt.Model0_num_sacks > 0) {
   struct Model0_tcp_sack_block *Model0_sp = &Model0_tp->Model0_selective_acks[0];
   int Model0_max_sack = Model0_sp[0].Model0_end_seq;
   int Model0_this_sack;

   for (Model0_this_sack = 1; Model0_this_sack < Model0_tp->Model0_rx_opt.Model0_num_sacks;
        ++Model0_this_sack) {
    Model0_max_sack = Model0_before(Model0_max_sack, Model0_sp[Model0_this_sack].Model0_end_seq) ?

     Model0_sp[Model0_this_sack].Model0_end_seq : Model0_max_sack;
   }

   if (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq == Model0_max_sack)
    Model0_rst_seq_match = true;
  }
#endif
  if (Model0_rst_seq_match)
   Model0_tcp_reset(Model0_sk);
  else
   Model0_tcp_send_challenge_ack(Model0_sk, Model0_skb);
  goto Model0_discard;
 }

 /* step 3: check security and precedence [ignored] */

 /* step 4: Check for a SYN
	 * RFC 5961 4.2 : Send a challenge ack
	 */
 if (Model0_th->Model0_syn) {
Model0_syn_challenge:
  if (Model0_syn_inerr)
   (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_INERRS] += 1);
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPSYNCHALLENGE] += 1);
  Model0_tcp_send_challenge_ack(Model0_sk, Model0_skb);
  goto Model0_discard;
 }

 return true;

Model0_discard:
 Model0_tcp_drop(Model0_sk, Model0_skb);
 return false;
}

/*
 *	TCP receive function for the ESTABLISHED state.
 *
 *	It is split into a fast path and a slow path. The fast path is
 * 	disabled when:
 *	- A zero window was announced from us - zero window probing
 *        is only handled properly in the slow path.
 *	- Out of order segments arrived.
 *	- Urgent data is expected.
 *	- There is no buffer space left
 *	- Unexpected TCP flags/window values/header lengths are received
 *	  (detected by checking the TCP header against pred_flags)
 *	- Data is sent in both directions. Fast path only supports pure senders
 *	  or pure receivers (this means either the sequence number or the ack
 *	  value must stay constant)
 *	- Unexpected TCP option.
 *
 *	When these conditions are not satisfied it drops into a standard
 *	receive procedure patterned after RFC793 to handle all cases.
 *	The first three cases are guaranteed by proper pred_flags setting,
 *	the rest is checked inline. Fast processing is turned on in
 *	tcp_data_queue when everything is OK.
 */
void Model0_tcp_rcv_established(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb,
    const struct Model0_tcphdr *Model0_th, unsigned int Model0_len)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
#if !CY_ABSTRACT1
 if (__builtin_expect(!!(!Model0_sk->Model0_sk_rx_dst), 0))
  Model0_inet_csk(Model0_sk)->Model0_icsk_af_ops->Model0_sk_rx_dst_set(Model0_sk, Model0_skb);
#endif
 /*
	 *	Header prediction.
	 *	The code loosely follows the one in the famous
	 *	"30 instruction TCP receive" Van Jacobson mail.
	 *
	 *	Van's trick is to deposit buffers into socket queue
	 *	on a device interrupt, to call tcp_recv function
	 *	on the receive process context and checksum and copy
	 *	the buffer to user space. smart...
	 *
	 *	Our current scheme is not silly either but we take the
	 *	extra cost of the net_bh soft interrupt processing...
	 *	We do checksum and copy also but from device to kernel.
	 */

 Model0_tp->Model0_rx_opt.Model0_saw_tstamp = 0;

 /*	pred_flags is 0xS?10 << 16 + snd_wnd
	 *	if header_prediction is to be made
	 *	'S' will always be tp->tcp_header_len >> 2
	 *	'?' will be 0 for the fast path, otherwise pred_flags is 0 to
	 *  turn it off	(when there are holes in the receive
	 *	 space for instance)
	 *	PSH flag is ignored.
	 */

 if ((( ((union Model0_tcp_word_hdr *)(Model0_th))->Model0_words [3]) & (~(Model0_TCP_RESERVED_BITS|Model0_TCP_FLAG_PSH))) == Model0_tp->Model0_pred_flags &&
     ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq == Model0_tp->Model0_rcv_nxt &&
     !Model0_before(Model0_tp->Model0_snd_nxt, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_ack_seq)) {
  int Model0_tcp_header_len = Model0_tp->Model0_tcp_header_len;

  /* Timestamp header prediction: tcp_header_len
		 * is automatically equal to th->doff*4 due to pred_flags
		 * match.
		 */
#if !CY_ABSTRACT1
  /* Check timestamp */
  if (Model0_tcp_header_len == sizeof(struct Model0_tcphdr) + 12) {
   /* No? Slow path! */
   if (!Model0_tcp_parse_aligned_timestamp(Model0_tp, Model0_th))
    goto Model0_slow_path;

   /* If PAWS failed, check it more carefully in slow path */
   if ((Model0_s32)(Model0_tp->Model0_rx_opt.Model0_rcv_tsval - Model0_tp->Model0_rx_opt.Model0_ts_recent) < 0)
    goto Model0_slow_path;

   /* DO NOT update ts_recent here, if checksum fails
			 * and timestamp was corrupted part, it will result
			 * in a hung connection since we will drop all
			 * future packets due to the PAWS test.
			 */
  }
#endif

  if (Model0_len <= Model0_tcp_header_len) {
   /* Bulk data transfer: sender */
   if (Model0_len == Model0_tcp_header_len) {
    /* Predicted packet is in window by definition.
				 * seq == rcv_nxt and rcv_wup <= rcv_nxt.
				 * Hence, check seq<=rcv_wup reduces to:
				 */
#if !CY_ABSTRACT1
    if (Model0_tcp_header_len ==
        (sizeof(struct Model0_tcphdr) + 12) &&
        Model0_tp->Model0_rcv_nxt == Model0_tp->Model0_rcv_wup)
     Model0_tcp_store_ts_recent(Model0_tp);
#endif
    /* We know that such packets are checksummed
				 * on entry.
				 */
    Model0_tcp_ack(Model0_sk, Model0_skb, 0);
    Model0___kfree_skb(Model0_skb);
    Model0_tcp_data_snd_check(Model0_sk);
    return;
   } else { /* Header too small */
    (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_INERRS] += 1);
    goto Model0_discard;
   }
  } else {
   int Model0_eaten = 0;
   bool Model0_fragstolen = false;
#if !CY_ABSTRACT1 //assume Model0_task always not equal to get_current()
   if (Model0_tp->Model0_ucopy.Model0_task == Model0_get_current() &&
       Model0_tp->Model0_copied_seq == Model0_tp->Model0_rcv_nxt &&
       Model0_len - Model0_tcp_header_len <= Model0_tp->Model0_ucopy.Model0_len &&
       Model0_sock_owned_by_user(Model0_sk)) {
    do { Model0_get_current()->Model0_state = (0); } while (0);

    if (!Model0_tcp_copy_to_iovec(Model0_sk, Model0_skb, Model0_tcp_header_len)) {
     /* Predicted packet is in window by definition.
					 * seq == rcv_nxt and rcv_wup <= rcv_nxt.
					 * Hence, check seq<=rcv_wup reduces to:
					 */
     if (Model0_tcp_header_len ==
         (sizeof(struct Model0_tcphdr) +
          12) &&
         Model0_tp->Model0_rcv_nxt == Model0_tp->Model0_rcv_wup)
      Model0_tcp_store_ts_recent(Model0_tp);

     Model0_tcp_rcv_rtt_measure_ts(Model0_sk, Model0_skb);

     Model0___skb_pull(Model0_skb, Model0_tcp_header_len);
     Model0_tcp_rcv_nxt_update(Model0_tp, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq);
     (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPHPHITSTOUSER] += 1);

     Model0_eaten = 1;
    }
   }
#endif
   if (!Model0_eaten) {
    if (Model0_tcp_checksum_complete(Model0_skb))
     goto Model0_csum_error;

    if ((int)Model0_skb->Model0_truesize > Model0_sk->Model0_sk_forward_alloc)
     goto Model0_step5;

    /* Predicted packet is in window by definition.
				 * seq == rcv_nxt and rcv_wup <= rcv_nxt.
				 * Hence, check seq<=rcv_wup reduces to:
				 */
#if !CY_ABSTRACT1
    if (Model0_tcp_header_len ==
        (sizeof(struct Model0_tcphdr) + 12) &&
        Model0_tp->Model0_rcv_nxt == Model0_tp->Model0_rcv_wup)
     Model0_tcp_store_ts_recent(Model0_tp);
#endif
    Model0_tcp_rcv_rtt_measure_ts(Model0_sk, Model0_skb);

    (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPHPHITS] += 1);

    /* Bulk data transfer: receiver */
    Model0_eaten = Model0_tcp_queue_rcv(Model0_sk, Model0_skb, Model0_tcp_header_len,
            &Model0_fragstolen);
   }

   Model0_tcp_event_data_recv(Model0_sk, Model0_skb);

   if (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_ack_seq != Model0_tp->Model0_snd_una) {
    /* Well, only one small jumplet in fast path... */
    Model0_tcp_ack(Model0_sk, Model0_skb, 0x01);
    Model0_tcp_data_snd_check(Model0_sk);
    if (!Model0_inet_csk_ack_scheduled(Model0_sk))
     goto Model0_no_ack;
   }

   Model0___tcp_ack_snd_check(Model0_sk, 0);
Model0_no_ack:
   if (Model0_eaten)
    Model0_kfree_skb_partial(Model0_skb, Model0_fragstolen);
#if !CY_ABSTRACT1
   Model0_sk->Model0_sk_data_ready(Model0_sk);
#endif
   return;
  }
 }

Model0_slow_path:
 if (Model0_len < (Model0_th->Model0_doff << 2) || Model0_tcp_checksum_complete(Model0_skb))
  goto Model0_csum_error;

 if (!Model0_th->Model0_ack && !Model0_th->Model0_rst && !Model0_th->Model0_syn)
  goto Model0_discard;

 /*
	 *	Standard slow path.
	 */

 if (!Model0_tcp_validate_incoming(Model0_sk, Model0_skb, Model0_th, 1))
  return;

Model0_step5:
 if (Model0_tcp_ack(Model0_sk, Model0_skb, 0x100 | 0x4000) < 0)
  goto Model0_discard;

 Model0_tcp_rcv_rtt_measure_ts(Model0_sk, Model0_skb);

 /* Process urgent data. */
 Model0_tcp_urg(Model0_sk, Model0_skb, Model0_th);

 /* step 7: process the segment text */
 Model0_tcp_data_queue(Model0_sk, Model0_skb);

 Model0_tcp_data_snd_check(Model0_sk);
 Model0_tcp_ack_snd_check(Model0_sk);
 return;

Model0_csum_error:
 (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_CSUMERRORS] += 1);
 (Model0_cy_tcp_mib.Model0_mibs[Model0_TCP_MIB_INERRS] += 1);

Model0_discard:
 Model0_tcp_drop(Model0_sk, Model0_skb);
}
                                  ;

void Model0_tcp_finish_connect(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);

 Model0_tcp_set_state(Model0_sk, Model0_TCP_ESTABLISHED);

 if (Model0_skb) {
#if CY_ABSTRACT7
  Model0_inet_sk_rx_dst_set(Model0_sk, Model0_skb);
#else
  Model0_icsk->Model0_icsk_af_ops->Model0_sk_rx_dst_set(Model0_sk, Model0_skb);
#endif
  Model0_security_inet_conn_established(Model0_sk, Model0_skb);
 }

 /* Make sure socket is routed, for correct metrics.  */
#if CY_ABSTRACT7
 Model0_inet_sk_rebuild_header(Model0_sk);
#else
 Model0_icsk->Model0_icsk_af_ops->Model0_rebuild_header(Model0_sk);
#endif

 Model0_tcp_init_metrics(Model0_sk);

 Model0_tcp_init_congestion_control(Model0_sk);

 /* Prevent spurious tcp_cwnd_restart() on first data
	 * packet.
	 */
 Model0_tp->Model0_lsndtime = ((__u32)(Model0_jiffies));

 Model0_tcp_init_buffer_space(Model0_sk);

 if (Model0_sock_flag(Model0_sk, Model0_SOCK_KEEPOPEN))
  Model0_inet_csk_reset_keepalive_timer(Model0_sk, Model0_keepalive_time_when(Model0_tp));

 if (!Model0_tp->Model0_rx_opt.Model0_snd_wscale)
  Model0___tcp_fast_path_on(Model0_tp, Model0_tp->Model0_snd_wnd);
 else
  Model0_tp->Model0_pred_flags = 0;

 if (!Model0_sock_flag(Model0_sk, Model0_SOCK_DEAD)) {
#if CY_ABSTRACT7
  Model0_sock_def_wakeup(Model0_sk);
#else
  Model0_sk->Model0_sk_state_change(Model0_sk);
#endif
  Model0_sk_wake_async(Model0_sk, Model0_SOCK_WAKE_IO, ((2 << 16)|2));
 }
}

static bool Model0_tcp_rcv_fastopen_synack(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_synack,
        struct Model0_tcp_fastopen_cookie *Model0_cookie)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_sk_buff *Model0_data = Model0_tp->Model0_syn_data ? Model0_tcp_write_queue_head(Model0_sk) : ((void *)0);
 Model0_u16 Model0_mss = Model0_tp->Model0_rx_opt.Model0_mss_clamp, Model0_try_exp = 0;
 bool Model0_syn_drop = false;

 if (Model0_mss == Model0_tp->Model0_rx_opt.Model0_user_mss) {
  struct Model0_tcp_options_received Model0_opt;

  /* Get original SYNACK MSS value if user MSS sets mss_clamp */
  Model0_tcp_clear_options(&Model0_opt);
  Model0_opt.Model0_user_mss = Model0_opt.Model0_mss_clamp = 0;
  Model0_tcp_parse_options(Model0_synack, &Model0_opt, 0, ((void *)0));
  Model0_mss = Model0_opt.Model0_mss_clamp;
 }

 if (!Model0_tp->Model0_syn_fastopen) {
  /* Ignore an unsolicited cookie */
  Model0_cookie->Model0_len = -1;
 } else if (Model0_tp->Model0_total_retrans) {
  /* SYN timed out and the SYN-ACK neither has a cookie nor
		 * acknowledges data. Presumably the remote received only
		 * the retransmitted (regular) SYNs: either the original
		 * SYN-data or the corresponding SYN-ACK was dropped.
		 */
  Model0_syn_drop = (Model0_cookie->Model0_len < 0 && Model0_data);
 } else if (Model0_cookie->Model0_len < 0 && !Model0_tp->Model0_syn_data) {
  /* We requested a cookie but didn't get it. If we did not use
		 * the (old) exp opt format then try so next time (try_exp=1).
		 * Otherwise we go back to use the RFC7413 opt (try_exp=2).
		 */
  Model0_try_exp = Model0_tp->Model0_syn_fastopen_exp ? 2 : 1;
 }

 Model0_tcp_fastopen_cache_set(Model0_sk, Model0_mss, Model0_cookie, Model0_syn_drop, Model0_try_exp);

 if (Model0_data) { /* Retransmit unacked data in SYN */
  for (; Model0_data != (struct Model0_sk_buff *)(&(Model0_sk)->Model0_sk_write_queue); Model0_data = Model0_data->Model0_next) {
   if (Model0_data == Model0_tcp_send_head(Model0_sk) ||
       Model0___tcp_retransmit_skb(Model0_sk, Model0_data, 1))
    break;
  }
  Model0_tcp_rearm_rto(Model0_sk);
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPFASTOPENACTIVEFAIL] += 1);

  return true;
 }
 Model0_tp->Model0_syn_data_acked = Model0_tp->Model0_syn_data;
 if (Model0_tp->Model0_syn_data_acked)
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPFASTOPENACTIVE] += 1);


 Model0_tcp_fastopen_add_skb(Model0_sk, Model0_synack);

 return false;
}

static int Model0_tcp_rcv_synsent_state_process(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb,
      const struct Model0_tcphdr *Model0_th)
{
 struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_tcp_fastopen_cookie Model0_foc = { .Model0_len = -1 };
 int Model0_saved_clamp = Model0_tp->Model0_rx_opt.Model0_mss_clamp;

 Model0_tcp_parse_options(Model0_skb, &Model0_tp->Model0_rx_opt, 0, &Model0_foc);
 if (Model0_tp->Model0_rx_opt.Model0_saw_tstamp && Model0_tp->Model0_rx_opt.Model0_rcv_tsecr)
  Model0_tp->Model0_rx_opt.Model0_rcv_tsecr -= Model0_tp->Model0_tsoffset;

 if (Model0_th->Model0_ack) {
  /* rfc793:
		 * "If the state is SYN-SENT then
		 *    first check the ACK bit
		 *      If the ACK bit is set
		 *	  If SEG.ACK =< ISS, or SEG.ACK > SND.NXT, send
		 *        a reset (unless the RST bit is set, if so drop
		 *        the segment and return)"
		 */
  if (!Model0_before(Model0_tp->Model0_snd_una, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_ack_seq) ||
      Model0_before(Model0_tp->Model0_snd_nxt, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_ack_seq))
   goto Model0_reset_and_undo;

  if (Model0_tp->Model0_rx_opt.Model0_saw_tstamp && Model0_tp->Model0_rx_opt.Model0_rcv_tsecr &&
      !Model0_between(Model0_tp->Model0_rx_opt.Model0_rcv_tsecr, Model0_tp->Model0_retrans_stamp,
        ((__u32)(Model0_jiffies)))) {
   (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_PAWSACTIVEREJECTED] += 1);

   goto Model0_reset_and_undo;
  }

  /* Now ACK is acceptable.
		 *
		 * "If the RST bit is set
		 *    If the ACK was acceptable then signal the user "error:
		 *    connection reset", drop the segment, enter CLOSED state,
		 *    delete TCB, and return."
		 */

  if (Model0_th->Model0_rst) {
   Model0_tcp_reset(Model0_sk);
   goto Model0_discard;
  }

  /* rfc793:
		 *   "fifth, if neither of the SYN or RST bits is set then
		 *    drop the segment and return."
		 *
		 *    See note below!
		 *                                        --ANK(990513)
		 */
  if (!Model0_th->Model0_syn)
   goto Model0_discard_and_undo;

  /* rfc793:
		 *   "If the SYN bit is on ...
		 *    are acceptable then ...
		 *    (our SYN has been ACKed), change the connection
		 *    state to ESTABLISHED..."
		 */

  Model0_tcp_ecn_rcv_synack(Model0_tp, Model0_th);

  Model0_tcp_init_wl(Model0_tp, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq);
  Model0_tcp_ack(Model0_sk, Model0_skb, 0x100);

  /* Ok.. it's good. Set up sequence numbers and
		 * move to established.
		 */
  Model0_tp->Model0_rcv_nxt = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq + 1;
  Model0_tp->Model0_rcv_wup = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq + 1;

  /* RFC1323: The window in SYN & SYN/ACK segments is
		 * never scaled.
		 */
  Model0_tp->Model0_snd_wnd = (__builtin_constant_p((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_th->Model0_window))) ? ((Model0___u16)( (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_th->Model0_window)) & (Model0___u16)0x00ffU) << 8) | (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_th->Model0_window)) & (Model0___u16)0xff00U) >> 8))) : Model0___fswab16(( Model0___u16)(Model0___be16)(Model0_th->Model0_window)));

  if (!Model0_tp->Model0_rx_opt.Model0_wscale_ok) {
   Model0_tp->Model0_rx_opt.Model0_snd_wscale = Model0_tp->Model0_rx_opt.Model0_rcv_wscale = 0;
   Model0_tp->Model0_window_clamp = ({ typeof(Model0_tp->Model0_window_clamp) Model0__min1 = (Model0_tp->Model0_window_clamp); typeof(65535U) Model0__min2 = (65535U); (void) (&Model0__min1 == &Model0__min2); Model0__min1 < Model0__min2 ? Model0__min1 : Model0__min2; });
  }

  if (Model0_tp->Model0_rx_opt.Model0_saw_tstamp) {
   Model0_tp->Model0_rx_opt.Model0_tstamp_ok = 1;
   Model0_tp->Model0_tcp_header_len =
    sizeof(struct Model0_tcphdr) + 12;
   Model0_tp->Model0_advmss -= 12;
   Model0_tcp_store_ts_recent(Model0_tp);
  } else {
   Model0_tp->Model0_tcp_header_len = sizeof(struct Model0_tcphdr);
  }

  if (Model0_tcp_is_sack(Model0_tp) && Model0_sysctl_tcp_fack)
   Model0_tcp_enable_fack(Model0_tp);

  Model0_tcp_mtup_init(Model0_sk);
  Model0_tcp_sync_mss(Model0_sk, Model0_icsk->Model0_icsk_pmtu_cookie);
  Model0_tcp_initialize_rcv_mss(Model0_sk);

  /* Remember, tcp_poll() does not lock socket!
		 * Change state from SYN-SENT only after copied_seq
		 * is initialized. */
  Model0_tp->Model0_copied_seq = Model0_tp->Model0_rcv_nxt;

  __asm__ __volatile__("": : :"memory");

  Model0_tcp_finish_connect(Model0_sk, Model0_skb);

  if ((Model0_tp->Model0_syn_fastopen || Model0_tp->Model0_syn_data) &&
      Model0_tcp_rcv_fastopen_synack(Model0_sk, Model0_skb, &Model0_foc))
   return -1;

  if (Model0_sk->Model0_sk_write_pending ||
      Model0_icsk->Model0_icsk_accept_queue.Model0_rskq_defer_accept ||
      Model0_icsk->Model0_icsk_ack.Model0_pingpong) {
   /* Save one ACK. Data will be ready after
			 * several ticks, if write_pending is set.
			 *
			 * It may be deleted, but with this feature tcpdumps
			 * look so _wonderfully_ clever, that I was not able
			 * to stand against the temptation 8)     --ANK
			 */
   Model0_inet_csk_schedule_ack(Model0_sk);
   Model0_icsk->Model0_icsk_ack.Model0_lrcvtime = ((__u32)(Model0_jiffies));
   Model0_tcp_enter_quickack_mode(Model0_sk);
   Model0_inet_csk_reset_xmit_timer(Model0_sk, 2,
        ((unsigned)(1000/5)), ((unsigned)(120*1000)));

Model0_discard:
   Model0_tcp_drop(Model0_sk, Model0_skb);
   return 0;
  } else {
   Model0_tcp_send_ack(Model0_sk);
  }
  return -1;
 }

 /* No ACK in the segment */

 if (Model0_th->Model0_rst) {
  /* rfc793:
		 * "If the RST bit is set
		 *
		 *      Otherwise (no ACK) drop the segment and return."
		 */

  goto Model0_discard_and_undo;
 }

 /* PAWS check. */
 if (Model0_tp->Model0_rx_opt.Model0_ts_recent_stamp && Model0_tp->Model0_rx_opt.Model0_saw_tstamp &&
     Model0_tcp_paws_reject(&Model0_tp->Model0_rx_opt, 0))
  goto Model0_discard_and_undo;

 if (Model0_th->Model0_syn) {
  /* We see SYN without ACK. It is attempt of
		 * simultaneous connect with crossed SYNs.
		 * Particularly, it can be connect to self.
		 */
  Model0_tcp_set_state(Model0_sk, Model0_TCP_SYN_RECV);

  if (Model0_tp->Model0_rx_opt.Model0_saw_tstamp) {
   Model0_tp->Model0_rx_opt.Model0_tstamp_ok = 1;
   Model0_tcp_store_ts_recent(Model0_tp);
   Model0_tp->Model0_tcp_header_len =
    sizeof(struct Model0_tcphdr) + 12;
  } else {
   Model0_tp->Model0_tcp_header_len = sizeof(struct Model0_tcphdr);
  }

  Model0_tp->Model0_rcv_nxt = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq + 1;
  Model0_tp->Model0_copied_seq = Model0_tp->Model0_rcv_nxt;
  Model0_tp->Model0_rcv_wup = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq + 1;

  /* RFC1323: The window in SYN & SYN/ACK segments is
		 * never scaled.
		 */
  Model0_tp->Model0_snd_wnd = (__builtin_constant_p((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_th->Model0_window))) ? ((Model0___u16)( (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_th->Model0_window)) & (Model0___u16)0x00ffU) << 8) | (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_th->Model0_window)) & (Model0___u16)0xff00U) >> 8))) : Model0___fswab16(( Model0___u16)(Model0___be16)(Model0_th->Model0_window)));
  Model0_tp->Model0_snd_wl1 = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq;
  Model0_tp->Model0_max_window = Model0_tp->Model0_snd_wnd;

  Model0_tcp_ecn_rcv_syn(Model0_tp, Model0_th);

  Model0_tcp_mtup_init(Model0_sk);
  Model0_tcp_sync_mss(Model0_sk, Model0_icsk->Model0_icsk_pmtu_cookie);
  Model0_tcp_initialize_rcv_mss(Model0_sk);

  Model0_tcp_send_synack(Model0_sk);
  goto Model0_discard;

 }
 /* "fifth, if neither of the SYN or RST bits is set then
	 * drop the segment and return."
	 */

Model0_discard_and_undo:
 Model0_tcp_clear_options(&Model0_tp->Model0_rx_opt);
 Model0_tp->Model0_rx_opt.Model0_mss_clamp = Model0_saved_clamp;
 goto Model0_discard;

Model0_reset_and_undo:
 Model0_tcp_clear_options(&Model0_tp->Model0_rx_opt);
 Model0_tp->Model0_rx_opt.Model0_mss_clamp = Model0_saved_clamp;
 return 1;
}

/*
 *	This function implements the receiving procedure of RFC 793 for
 *	all states except ESTABLISHED and TIME_WAIT.
 *	It's called from both tcp_v4_rcv and tcp_v6_rcv and should be
 *	address independent.
 */

int Model0_tcp_rcv_state_process(struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb)
{
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_inet_connection_sock *Model0_icsk = Model0_inet_csk(Model0_sk);
 const struct Model0_tcphdr *Model0_th = Model0_tcp_hdr(Model0_skb);
 struct Model0_request_sock *Model0_req;
 int Model0_queued = 0;
 bool Model0_acceptable;

 switch (Model0_sk->Model0___sk_common.Model0_skc_state) {
 case Model0_TCP_CLOSE:
  goto Model0_discard;

 case Model0_TCP_LISTEN:
  if (Model0_th->Model0_ack)
   return 1;

  if (Model0_th->Model0_rst)
   goto Model0_discard;

  if (Model0_th->Model0_syn) {
   if (Model0_th->Model0_fin)
    goto Model0_discard;
#if CY_ABSTRACT7
   if (Model0_tcp_v4_conn_request(Model0_sk, Model0_skb) < 0)
#else
   if (Model0_icsk->Model0_icsk_af_ops->Model0_conn_request(Model0_sk, Model0_skb) < 0)
#endif
    return 1;

   Model0_consume_skb(Model0_skb);
   return 0;
  }
  goto Model0_discard;

 case Model0_TCP_SYN_SENT:
  Model0_tp->Model0_rx_opt.Model0_saw_tstamp = 0;
  Model0_queued = Model0_tcp_rcv_synsent_state_process(Model0_sk, Model0_skb, Model0_th);
  if (Model0_queued >= 0)
   return Model0_queued;

  /* Do step6 onward by hand. */
  Model0_tcp_urg(Model0_sk, Model0_skb, Model0_th);
  Model0___kfree_skb(Model0_skb);
  Model0_tcp_data_snd_check(Model0_sk);
  return 0;
 }

 Model0_tp->Model0_rx_opt.Model0_saw_tstamp = 0;
 Model0_req = Model0_tp->Model0_fastopen_rsk;
 if (Model0_req) {
  ({ int Model0___ret_warn_on = !!(Model0_sk->Model0___sk_common.Model0_skc_state != Model0_TCP_SYN_RECV && Model0_sk->Model0___sk_common.Model0_skc_state != Model0_TCP_FIN_WAIT1); __builtin_expect(!!(Model0___ret_warn_on), 0); });


  if (!Model0_tcp_check_req(Model0_sk, Model0_skb, Model0_req, true))
   goto Model0_discard;
 }

 if (!Model0_th->Model0_ack && !Model0_th->Model0_rst && !Model0_th->Model0_syn)
  goto Model0_discard;
 if (!Model0_tcp_validate_incoming(Model0_sk, Model0_skb, Model0_th, 0))
  return 0;

 /* step 5: check the ACK field */
 Model0_acceptable = Model0_tcp_ack(Model0_sk, Model0_skb, 0x100 |
          0x4000) > 0;

 switch (Model0_sk->Model0___sk_common.Model0_skc_state) {
 case Model0_TCP_SYN_RECV:
  if (!Model0_acceptable)
   return 1;

  if (!Model0_tp->Model0_srtt_us)
   Model0_tcp_synack_rtt_meas(Model0_sk, Model0_req);

  /* Once we leave TCP_SYN_RECV, we no longer need req
		 * so release it.
		 */
  if (Model0_req) {
   Model0_inet_csk(Model0_sk)->Model0_icsk_retransmits = 0;
   Model0_reqsk_fastopen_remove(Model0_sk, Model0_req, false);
  } else {
   /* Make sure socket is routed, for correct metrics. */
#if CY_ABSTRACT7
   Model0_inet_sk_rebuild_header(Model0_sk);
#else
   Model0_icsk->Model0_icsk_af_ops->Model0_rebuild_header(Model0_sk);
#endif
   Model0_tcp_init_congestion_control(Model0_sk);

   Model0_tcp_mtup_init(Model0_sk);
   Model0_tp->Model0_copied_seq = Model0_tp->Model0_rcv_nxt;
   Model0_tcp_init_buffer_space(Model0_sk);
  }
  __asm__ __volatile__("": : :"memory");
  Model0_tcp_set_state(Model0_sk, Model0_TCP_ESTABLISHED);
#if CY_ABSTRACT7
  //because we call explicit function, they may be static function from other file
  Model0_sock_def_wakeup(Model0_sk);
#else
  Model0_sk->Model0_sk_state_change(Model0_sk);
#endif

  /* Note, that this wakeup is only for marginal crossed SYN case.
		 * Passively open sockets are not waked up, because
		 * sk->sk_sleep == NULL and sk->sk_socket == NULL.
		 */
  if (Model0_sk->Model0_sk_socket)
   Model0_sk_wake_async(Model0_sk, Model0_SOCK_WAKE_IO, ((2 << 16)|2));

  Model0_tp->Model0_snd_una = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_ack_seq;
  Model0_tp->Model0_snd_wnd = (__builtin_constant_p((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_th->Model0_window))) ? ((Model0___u16)( (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_th->Model0_window)) & (Model0___u16)0x00ffU) << 8) | (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_th->Model0_window)) & (Model0___u16)0xff00U) >> 8))) : Model0___fswab16(( Model0___u16)(Model0___be16)(Model0_th->Model0_window))) << Model0_tp->Model0_rx_opt.Model0_snd_wscale;
  Model0_tcp_init_wl(Model0_tp, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq);

  if (Model0_tp->Model0_rx_opt.Model0_tstamp_ok)
   Model0_tp->Model0_advmss -= 12;

  if (Model0_req) {
   /* Re-arm the timer because data may have been sent out.
			 * This is similar to the regular data transmission case
			 * when new data has just been ack'ed.
			 *
			 * (TFO) - we could try to be more aggressive and
			 * retransmitting any data sooner based on when they
			 * are sent out.
			 */
   Model0_tcp_rearm_rto(Model0_sk);
  } else
   Model0_tcp_init_metrics(Model0_sk);

  Model0_tcp_update_pacing_rate(Model0_sk);

  /* Prevent spurious tcp_cwnd_restart() on first data packet */
  Model0_tp->Model0_lsndtime = ((__u32)(Model0_jiffies));

  Model0_tcp_initialize_rcv_mss(Model0_sk);
  Model0_tcp_fast_path_on(Model0_tp);
  break;

 case Model0_TCP_FIN_WAIT1: {
  struct Model0_dst_entry *Model0_dst;
  int Model0_tmo;

  /* If we enter the TCP_FIN_WAIT1 state and we are a
		 * Fast Open socket and this is the first acceptable
		 * ACK we have received, this would have acknowledged
		 * our SYNACK so stop the SYNACK timer.
		 */
  if (Model0_req) {
   /* Return RST if ack_seq is invalid.
			 * Note that RFC793 only says to generate a
			 * DUPACK for it but for TCP Fast Open it seems
			 * better to treat this case like TCP_SYN_RECV
			 * above.
			 */
   if (!Model0_acceptable)
    return 1;
   /* We no longer need the request sock. */
   Model0_reqsk_fastopen_remove(Model0_sk, Model0_req, false);
   Model0_tcp_rearm_rto(Model0_sk);
  }
  if (Model0_tp->Model0_snd_una != Model0_tp->Model0_write_seq)
   break;

  Model0_tcp_set_state(Model0_sk, Model0_TCP_FIN_WAIT2);
  Model0_sk->Model0_sk_shutdown |= 2;

  Model0_dst = Model0___sk_dst_get(Model0_sk);
  if (Model0_dst)
   Model0_dst_confirm(Model0_dst);

  if (!Model0_sock_flag(Model0_sk, Model0_SOCK_DEAD)) {
   /* Wake up lingering close() */
#if CY_ABSTRACT7
   Model0_sock_def_wakeup(Model0_sk);
#else
   Model0_sk->Model0_sk_state_change(Model0_sk);
#endif
   break;
  }

  if (Model0_tp->Model0_linger2 < 0 ||
      (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq != ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq &&
       Model0_before(Model0_tp->Model0_rcv_nxt, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq - Model0_th->Model0_fin))) {
   Model0_tcp_done(Model0_sk);
   (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPABORTONDATA] += 1);
   return 1;
  }

  Model0_tmo = Model0_tcp_fin_time(Model0_sk);
  if (Model0_tmo > (60*1000)) {
   Model0_inet_csk_reset_keepalive_timer(Model0_sk, Model0_tmo - (60*1000));
  } else if (Model0_th->Model0_fin || Model0_sock_owned_by_user(Model0_sk)) {
   /* Bad case. We could lose such FIN otherwise.
			 * It is not a big problem, but it looks confusing
			 * and not so rare event. We still can lose it now,
			 * if it spins in bh_lock_sock(), but it is really
			 * marginal case.
			 */
   Model0_inet_csk_reset_keepalive_timer(Model0_sk, Model0_tmo);
  } else {
   Model0_tcp_time_wait(Model0_sk, Model0_TCP_FIN_WAIT2, Model0_tmo);
   goto Model0_discard;
  }
  break;
 }

 case Model0_TCP_CLOSING:
  if (Model0_tp->Model0_snd_una == Model0_tp->Model0_write_seq) {
   Model0_tcp_time_wait(Model0_sk, Model0_TCP_TIME_WAIT, 0);
   goto Model0_discard;
  }
  break;

 case Model0_TCP_LAST_ACK:
  if (Model0_tp->Model0_snd_una == Model0_tp->Model0_write_seq) {
   Model0_tcp_update_metrics(Model0_sk);
   Model0_tcp_done(Model0_sk);
   goto Model0_discard;
  }
  break;
 }

 /* step 6: check the URG bit */
 Model0_tcp_urg(Model0_sk, Model0_skb, Model0_th);

 /* step 7: process the segment text */
 switch (Model0_sk->Model0___sk_common.Model0_skc_state) {
 case Model0_TCP_CLOSE_WAIT:
 case Model0_TCP_CLOSING:
 case Model0_TCP_LAST_ACK:
  if (!Model0_before(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq, Model0_tp->Model0_rcv_nxt))
   break;
 case Model0_TCP_FIN_WAIT1:
 case Model0_TCP_FIN_WAIT2:
  /* RFC 793 says to queue data in these states,
		 * RFC 1122 says we MUST send a reset.
		 * BSD 4.4 also does reset.
		 */
  if (Model0_sk->Model0_sk_shutdown & 1) {
   if (((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq != ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq &&
       Model0_before(Model0_tp->Model0_rcv_nxt, ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_end_seq - Model0_th->Model0_fin)) {
    (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPABORTONDATA] += 1);
    Model0_tcp_reset(Model0_sk);
    return 1;
   }
  }
  /* Fall through */
 case Model0_TCP_ESTABLISHED:
  Model0_tcp_data_queue(Model0_sk, Model0_skb);
  Model0_queued = 1;
  break;
 }

 /* tcp_data could move socket to TIME-WAIT */
 if (Model0_sk->Model0___sk_common.Model0_skc_state != Model0_TCP_CLOSE) {
  Model0_tcp_data_snd_check(Model0_sk);
  Model0_tcp_ack_snd_check(Model0_sk);
 }

 if (!Model0_queued) {
Model0_discard:
  Model0_tcp_drop(Model0_sk, Model0_skb);
 }
 return 0;
}
                                    ;

static inline __attribute__((no_instrument_function)) void Model0_pr_drop_req(struct Model0_request_sock *Model0_req, Model0___u16 Model0_port, int Model0_family)
{
 struct Model0_inet_request_sock *Model0_ireq = Model0_inet_rsk(Model0_req);

 if (Model0_family == 2)
  do { if (0) ({ do { if (0) Model0_printk("\001" "7" "TCP: " "drop open request from %pI4/%u\n", &Model0_ireq->Model0_req.Model0___req_common.Model0_skc_daddr, Model0_port); } while (0); 0; }); } while (0);






}

/* RFC3168 : 6.1.1 SYN packets must not have ECT/ECN bits set
 *
 * If we receive a SYN packet with these bits set, it means a
 * network is playing bad games with TOS bits. In order to
 * avoid possible false congestion notifications, we disable
 * TCP ECN negotiation.
 *
 * Exception: tcp_ca wants ECN. This is required for DCTCP
 * congestion control: Linux DCTCP asserts ECT on all packets,
 * including SYN, which is most optimal solution; however,
 * others, such as FreeBSD do not.
 */
static void Model0_tcp_ecn_create_request(struct Model0_request_sock *Model0_req,
       const struct Model0_sk_buff *Model0_skb,
       const struct Model0_sock *Model0_listen_sk,
       const struct Model0_dst_entry *Model0_dst)
{
 const struct Model0_tcphdr *Model0_th = Model0_tcp_hdr(Model0_skb);
 const struct Model0_net *Model0_net = Model0_sock_net(Model0_listen_sk);
 bool Model0_th_ecn = Model0_th->Model0_ece && Model0_th->Model0_cwr;
 bool Model0_ect, Model0_ecn_ok;
 Model0_u32 Model0_ecn_ok_dst;

 if (!Model0_th_ecn)
  return;

 Model0_ect = !Model0_INET_ECN_is_not_ect(((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_ip_dsfield);
 Model0_ecn_ok_dst = Model0_dst_feature(Model0_dst, ((1 << 31) | (1 << 0)));
 Model0_ecn_ok = Model0_net->Model0_ipv4.Model0_sysctl_tcp_ecn || Model0_ecn_ok_dst;

 if ((!Model0_ect && Model0_ecn_ok) || Model0_tcp_ca_needs_ecn(Model0_listen_sk) ||
     (Model0_ecn_ok_dst & (1 << 31)))
  Model0_inet_rsk(Model0_req)->Model0_ecn_ok = 1;
}

static void Model0_tcp_openreq_init(struct Model0_request_sock *Model0_req,
        const struct Model0_tcp_options_received *Model0_rx_opt,
        struct Model0_sk_buff *Model0_skb, const struct Model0_sock *Model0_sk)
{
 struct Model0_inet_request_sock *Model0_ireq = Model0_inet_rsk(Model0_req);

 Model0_req->Model0___req_common.Model0_skc_rcv_wnd = 0; /* So that tcp_send_synack() knows! */
 Model0_req->Model0_cookie_ts = 0;
 Model0_tcp_rsk(Model0_req)->Model0_rcv_isn = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq;
 Model0_tcp_rsk(Model0_req)->Model0_rcv_nxt = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_seq + 1;
 Model0_skb_mstamp_get(&Model0_tcp_rsk(Model0_req)->Model0_snt_synack);
 Model0_tcp_rsk(Model0_req)->Model0_last_oow_ack_time = 0;
 Model0_req->Model0_mss = Model0_rx_opt->Model0_mss_clamp;
 Model0_req->Model0_ts_recent = Model0_rx_opt->Model0_saw_tstamp ? Model0_rx_opt->Model0_rcv_tsval : 0;
 Model0_ireq->Model0_tstamp_ok = Model0_rx_opt->Model0_tstamp_ok;
 Model0_ireq->Model0_sack_ok = Model0_rx_opt->Model0_sack_ok;
 Model0_ireq->Model0_snd_wscale = Model0_rx_opt->Model0_snd_wscale;
 Model0_ireq->Model0_wscale_ok = Model0_rx_opt->Model0_wscale_ok;
 Model0_ireq->Model0_acked = 0;
 Model0_ireq->Model0_ecn_ok = 0;
 Model0_ireq->Model0_req.Model0___req_common.Model0_skc_dport = Model0_tcp_hdr(Model0_skb)->Model0_source;
 Model0_ireq->Model0_req.Model0___req_common.Model0_skc_num = (__builtin_constant_p((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_dest))) ? ((Model0___u16)( (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_dest)) & (Model0___u16)0x00ffU) << 8) | (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_dest)) & (Model0___u16)0xff00U) >> 8))) : Model0___fswab16(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_dest)));
 Model0_ireq->Model0_ir_mark = Model0_inet_request_mark(Model0_sk, Model0_skb);
}

struct Model0_request_sock *Model0_inet_reqsk_alloc(const struct Model0_request_sock_ops *Model0_ops,
          struct Model0_sock *Model0_sk_listener,
          bool Model0_attach_listener)
{
 struct Model0_request_sock *Model0_req = Model0_reqsk_alloc(Model0_ops, Model0_sk_listener,
            Model0_attach_listener);

 if (Model0_req) {
  struct Model0_inet_request_sock *Model0_ireq = Model0_inet_rsk(Model0_req);

  do { } while (0);
  Model0_ireq->Model0_opt = ((void *)0);



  Model0_atomic64_set(&Model0_ireq->Model0_req.Model0___req_common.Model0_skc_cookie, 0);
  Model0_ireq->Model0_req.Model0___req_common.Model0_skc_state = Model0_TCP_NEW_SYN_RECV;
  Model0_write_pnet(&Model0_ireq->Model0_req.Model0___req_common.Model0_skc_net, Model0_sock_net(Model0_sk_listener));
  Model0_ireq->Model0_req.Model0___req_common.Model0_skc_family = Model0_sk_listener->Model0___sk_common.Model0_skc_family;
 }

 return Model0_req;
}
                               ;

/*
 * Return true if a syncookie should be sent
 */
static bool Model0_tcp_syn_flood_action(const struct Model0_sock *Model0_sk,
     const struct Model0_sk_buff *Model0_skb,
     const char *Model0_proto)
{
 struct Model0_request_sock_queue *Model0_queue = &Model0_inet_csk(Model0_sk)->Model0_icsk_accept_queue;
 const char *Model0_msg = "Dropping request";
 bool Model0_want_cookie = false;
 struct Model0_net *Model0_net = Model0_sock_net(Model0_sk);


 if (Model0_net->Model0_ipv4.Model0_sysctl_tcp_syncookies) {
  Model0_msg = "Sending cookies";
  Model0_want_cookie = true;
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPREQQFULLDOCOOKIES] += 1);
 } else

  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_TCPREQQFULLDROP] += 1);

 if (!Model0_queue->Model0_synflood_warned &&
     Model0_net->Model0_ipv4.Model0_sysctl_tcp_syncookies != 2 &&
     ({ __typeof__ (*((&Model0_queue->Model0_synflood_warned))) Model0___ret = ((1)); switch (sizeof(*((&Model0_queue->Model0_synflood_warned)))) { case 1: asm volatile ("" "xchg" "b %b0, %1\n" : "+q" (Model0___ret), "+m" (*((&Model0_queue->Model0_synflood_warned))) : : "memory", "cc"); break; case 2: asm volatile ("" "xchg" "w %w0, %1\n" : "+r" (Model0___ret), "+m" (*((&Model0_queue->Model0_synflood_warned))) : : "memory", "cc"); break; case 4: asm volatile ("" "xchg" "l %0, %1\n" : "+r" (Model0___ret), "+m" (*((&Model0_queue->Model0_synflood_warned))) : : "memory", "cc"); break; case 8: asm volatile ("" "xchg" "q %q0, %1\n" : "+r" (Model0___ret), "+m" (*((&Model0_queue->Model0_synflood_warned))) : : "memory", "cc"); break; default: Model0___xchg_wrong_size(); } Model0___ret; }) == 0)
  Model0_printk("\001" "6" "TCP: " "%s: Possible SYN flooding on port %d. %s.  Check SNMP counters.\n", Model0_proto, (__builtin_constant_p((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_dest))) ? ((Model0___u16)( (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_dest)) & (Model0___u16)0x00ffU) << 8) | (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_dest)) & (Model0___u16)0xff00U) >> 8))) : Model0___fswab16(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_dest))), Model0_msg);


 return Model0_want_cookie;
}

static void Model0_tcp_reqsk_record_syn(const struct Model0_sock *Model0_sk,
     struct Model0_request_sock *Model0_req,
     const struct Model0_sk_buff *Model0_skb)
{
 if (Model0_tcp_sk(Model0_sk)->Model0_save_syn) {
  Model0_u32 Model0_len = Model0_skb_network_header_len(Model0_skb) + Model0_tcp_hdrlen(Model0_skb);
  Model0_u32 *Model0_copy;

  Model0_copy = Model0_kmalloc(Model0_len + sizeof(Model0_u32), ((( Model0_gfp_t)0x20u)|(( Model0_gfp_t)0x80000u)|(( Model0_gfp_t)0x2000000u)));
  if (Model0_copy) {
   Model0_copy[0] = Model0_len;
   ({ Model0_size_t Model0___len = (Model0_len); void *Model0___ret; if (__builtin_constant_p(Model0_len) && Model0___len >= 64) Model0___ret = Model0___memcpy((&Model0_copy[1]), (Model0_skb_network_header(Model0_skb)), Model0___len); else Model0___ret = __builtin_memcpy((&Model0_copy[1]), (Model0_skb_network_header(Model0_skb)), Model0___len); Model0___ret; });
   Model0_req->Model0_saved_syn = Model0_copy;
  }
 }
}

int Model0_tcp_conn_request(struct Model0_request_sock_ops *Model0_rsk_ops,
       const struct Model0_tcp_request_sock_ops *Model0_af_ops,
       struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb)
{
 struct Model0_tcp_fastopen_cookie Model0_foc = { .Model0_len = -1 };
 __u32 Model0_isn = ((struct Model0_tcp_skb_cb *)&((Model0_skb)->Model0_cb[0]))->Model0_tcp_tw_isn;
 struct Model0_tcp_options_received Model0_tmp_opt;
 struct Model0_tcp_sock *Model0_tp = Model0_tcp_sk(Model0_sk);
 struct Model0_net *Model0_net = Model0_sock_net(Model0_sk);
 struct Model0_sock *Model0_fastopen_sk = ((void *)0);
 struct Model0_dst_entry *Model0_dst = ((void *)0);
 struct Model0_request_sock *Model0_req;
 bool Model0_want_cookie = false;
 struct Model0_flowi Model0_fl;

 /* TW buckets are converted to open requests without
	 * limitations, they conserve resources and peer is
	 * evidently real one.
	 */
 if ((Model0_net->Model0_ipv4.Model0_sysctl_tcp_syncookies == 2 ||
      Model0_inet_csk_reqsk_queue_is_full(Model0_sk)) && !Model0_isn) {
  Model0_want_cookie = Model0_tcp_syn_flood_action(Model0_sk, Model0_skb, Model0_rsk_ops->Model0_slab_name);
  if (!Model0_want_cookie)
   goto Model0_drop;
 }


 /* Accept backlog is full. If we have already queued enough
	 * of warm entries in syn queue, drop request. It is better than
	 * clogging syn queue with openreqs with exponentially increasing
	 * timeout.
	 */
 if (Model0_sk_acceptq_is_full(Model0_sk) && Model0_inet_csk_reqsk_queue_young(Model0_sk) > 1) {
  (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_LISTENOVERFLOWS] += 1);
  goto Model0_drop;
 }

 Model0_req = Model0_inet_reqsk_alloc(Model0_rsk_ops, Model0_sk, !Model0_want_cookie);
 if (!Model0_req)
  goto Model0_drop;

 Model0_tcp_rsk(Model0_req)->Model0_af_specific = Model0_af_ops;

 Model0_tcp_clear_options(&Model0_tmp_opt);
 Model0_tmp_opt.Model0_mss_clamp = Model0_af_ops->Model0_mss_clamp;
 Model0_tmp_opt.Model0_user_mss = Model0_tp->Model0_rx_opt.Model0_user_mss;
 Model0_tcp_parse_options(Model0_skb, &Model0_tmp_opt, 0, Model0_want_cookie ? ((void *)0) : &Model0_foc); //assume no header options (including fast open cookie option)

 if (Model0_want_cookie && !Model0_tmp_opt.Model0_saw_tstamp)
  Model0_tcp_clear_options(&Model0_tmp_opt);

 Model0_tmp_opt.Model0_tstamp_ok = Model0_tmp_opt.Model0_saw_tstamp;
 Model0_tcp_openreq_init(Model0_req, &Model0_tmp_opt, Model0_skb, Model0_sk);

 /* Note: tcp_v6_init_req() might override ir_iif for link locals */
 Model0_inet_rsk(Model0_req)->Model0_req.Model0___req_common.Model0_skc_bound_dev_if = Model0_inet_request_bound_dev_if(Model0_sk, Model0_skb);

#if CY_ABSTRACT7
 Model0_tcp_v4_init_req(Model0_req, Model0_sk, Model0_skb);
#else
 Model0_af_ops->Model0_init_req(Model0_req, Model0_sk, Model0_skb);
#endif

 if (Model0_security_inet_conn_request(Model0_sk, Model0_skb, Model0_req))
  goto Model0_drop_and_free;

 if (!Model0_want_cookie && !Model0_isn) {
  /* VJ's idea. We save last timestamp seen
		 * from the destination in peer table, when entering
		 * state TIME-WAIT, and check against it before
		 * accepting new connection request.
		 *
		 * If "isn" is not zero, this request hit alive
		 * timewait bucket, so that all the necessary checks
		 * are made in the function processing timewait state.
		 */
  if (Model0_tcp_death_row.Model0_sysctl_tw_recycle) {
   bool Model0_strict;

#if CY_ABSTRACT7
   Model0_dst = Model0_tcp_v4_route_req(Model0_sk, &Model0_fl, Model0_req, &Model0_strict);
#else
   Model0_dst = Model0_af_ops->Model0_route_req(Model0_sk, &Model0_fl, Model0_req, &Model0_strict);
#endif

   if (Model0_dst && Model0_strict &&
       !Model0_tcp_peer_is_proven(Model0_req, Model0_dst, true,
      Model0_tmp_opt.Model0_saw_tstamp)) {
    (Model0_cy_linux_mib.Model0_mibs[Model0_LINUX_MIB_PAWSPASSIVEREJECTED] += 1);
    goto Model0_drop_and_release;
   }
  }
  /* Kill the following clause, if you dislike this way. */
  else if (!Model0_net->Model0_ipv4.Model0_sysctl_tcp_syncookies &&
    (Model0_sysctl_max_syn_backlog - Model0_inet_csk_reqsk_queue_len(Model0_sk) <
     (Model0_sysctl_max_syn_backlog >> 2)) &&
    !Model0_tcp_peer_is_proven(Model0_req, Model0_dst, false,
          Model0_tmp_opt.Model0_saw_tstamp)) {
   /* Without syncookies last quarter of
			 * backlog is filled with destinations,
			 * proven to be alive.
			 * It means that we continue to communicate
			 * to destinations, already remembered
			 * to the moment of synflood.
			 */
   Model0_pr_drop_req(Model0_req, (__builtin_constant_p((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_source))) ? ((Model0___u16)( (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_source)) & (Model0___u16)0x00ffU) << 8) | (((Model0___u16)(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_source)) & (Model0___u16)0xff00U) >> 8))) : Model0___fswab16(( Model0___u16)(Model0___be16)(Model0_tcp_hdr(Model0_skb)->Model0_source))),
        Model0_rsk_ops->Model0_family);
   goto Model0_drop_and_release;
  }

#if CY_ABSTRACT7
  Model0_isn = Model0_tcp_v4_init_sequence(Model0_skb);
#else
  Model0_isn = Model0_af_ops->Model0_init_seq(Model0_skb);
#endif
 }
#if CY_ABSTRACT3
#else
 if (!Model0_dst) {
#if CY_ABSTRACT7
   Model0_dst = Model0_tcp_v4_route_req(Model0_sk, &Model0_fl, Model0_req, ((void *)0));
#else
  Model0_dst = Model0_af_ops->Model0_route_req(Model0_sk, &Model0_fl, Model0_req, ((void *)0));
#endif
  if (!Model0_dst)
   goto Model0_drop_and_free;
 }
#endif

#if !CY_ABSTRACT3
 Model0_tcp_ecn_create_request(Model0_req, Model0_skb, Model0_sk, Model0_dst);
#endif

 if (Model0_want_cookie) {
  Model0_isn = Model0_cookie_init_sequence(Model0_af_ops, Model0_sk, Model0_skb, &Model0_req->Model0_mss);
  Model0_req->Model0_cookie_ts = Model0_tmp_opt.Model0_tstamp_ok;
  if (!Model0_tmp_opt.Model0_tstamp_ok)
   Model0_inet_rsk(Model0_req)->Model0_ecn_ok = 0;
 }

 Model0_tcp_rsk(Model0_req)->Model0_snt_isn = Model0_isn;
 Model0_tcp_rsk(Model0_req)->Model0_txhash = Model0_net_tx_rndhash();
 Model0_tcp_openreq_init_rwin(Model0_req, Model0_sk, Model0_dst);
 if (!Model0_want_cookie) {
  Model0_tcp_reqsk_record_syn(Model0_sk, Model0_req, Model0_skb);
  Model0_fastopen_sk = Model0_tcp_try_fastopen(Model0_sk, Model0_skb, Model0_req, &Model0_foc, Model0_dst);
 }
 if (Model0_fastopen_sk) {
#if CY_ABSTRACT7
  Model0_tcp_v4_send_synack(Model0_fastopen_sk, Model0_dst, &Model0_fl, Model0_req,
#else
  Model0_af_ops->Model0_send_synack(Model0_fastopen_sk, Model0_dst, &Model0_fl, Model0_req,
#endif
        &Model0_foc, Model0_TCP_SYNACK_FASTOPEN);
  /* Add the child socket directly into the accept queue */
  Model0_inet_csk_reqsk_queue_add(Model0_sk, Model0_req, Model0_fastopen_sk);
#if CY_ABSTRACT7
  Model0_sock_def_readable(Model0_sk);
#else
  Model0_sk->Model0_sk_data_ready(Model0_sk);
#endif
  Model0_spin_unlock(&((Model0_fastopen_sk)->Model0_sk_lock.Model0_slock));
  Model0_sock_put(Model0_fastopen_sk);
 } else {
  Model0_tcp_rsk(Model0_req)->Model0_tfo_listener = false;
  if (!Model0_want_cookie)
   Model0_inet_csk_reqsk_queue_hash_add(Model0_sk, Model0_req, ((unsigned)(1*1000)));
#if CY_ABSTRACT7
  Model0_tcp_v4_send_synack(Model0_sk, Model0_dst, &Model0_fl, Model0_req, &Model0_foc,
#else
  Model0_af_ops->Model0_send_synack(Model0_sk, Model0_dst, &Model0_fl, Model0_req, &Model0_foc,
#endif
        !Model0_want_cookie ? Model0_TCP_SYNACK_NORMAL :
         Model0_TCP_SYNACK_COOKIE);
  if (Model0_want_cookie) {
   Model0_reqsk_free(Model0_req);
   return 0;
  }
 }
 Model0_reqsk_put(Model0_req);
 return 0;

Model0_drop_and_release:
 Model0_dst_release(Model0_dst);
Model0_drop_and_free:
 Model0_reqsk_free(Model0_req);
Model0_drop:
 Model0_tcp_listendrop(Model0_sk);
 return 0;
}
                               ;
