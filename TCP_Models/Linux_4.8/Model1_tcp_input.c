#include "TCP_Model.h"
#include <assert.h>

/* START OF tcp_ipv4.c */

// globals
int Model1_sysctl_tcp_low_latency __attribute__((__section__(".data..read_mostly")));
__typeof__(int) Model1___preempt_count;
struct Model1_inet_hashinfo Model1_tcp_hashinfo;
                           ;
static const struct Model1_tcp_request_sock_ops Model1_tcp_request_sock_ipv4_ops = {
 .Model1_mss_clamp = 536U,




 .Model1_init_req = Model1_tcp_v4_init_req,



 .Model1_route_req = Model1_tcp_v4_route_req,
 .Model1_init_seq = Model1_tcp_v4_init_sequence,
 .Model1_send_synack = Model1_tcp_v4_send_synack,
};
struct Model1_request_sock_ops Model1_tcp_request_sock_ops __attribute__((__section__(".data..read_mostly"))) = {
 .Model1_family = 2,
 .Model1_obj_size = sizeof(struct Model1_tcp_request_sock),
 .Model1_rtx_syn_ack = Model1_tcp_rtx_synack,
 .Model1_send_ack = Model1_tcp_v4_reqsk_send_ack,
 .Model1_destructor = Model1_tcp_v4_reqsk_destructor,
 .Model1_send_reset = Model1_tcp_v4_send_reset,
 .Model1_syn_ack_timeout = Model1_tcp_syn_ack_timeout,
};

// functions

void Model1_tcp_syn_ack_timeout(const struct Model1_request_sock *Model1_req){
    assert(0);
}
void Model1_ip_send_unicast_reply(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb,
      const struct Model1_ip_options *Model1_sopt,
      Model1___be32 Model1_daddr, Model1___be32 Model1_saddr,
      const struct Model1_ip_reply_arg *Model1_arg,
      unsigned int Model1_len){
#if CY_ABSTRACT3
    //Used for verification of violation. Since we only compare headers, so here we only copy headers
    if (Model1_Src_sk == true){
        Model1_Out_pkt = true;
    }
    //Modify 06/11/2018 Right now we only have one direction from Client or Attacker to Server
    //We assume Client won't send packet to Server so we ignore packets sent to Client
    else{
        Model1_Out_pkt = false;
        return;
    }
#if CY_ABSTRACT3
    Model1_cy_alloc_skb(&Model1_Skb_Out, Model1_Buff_Out, Model1_SKB_DATA_SIZE);
#endif
    memcpy((struct Model1_tcphdr *)((&Model1_Skb_Out)->Model1_data), Model1_arg->Model1_iov[0].Model1_iov_base, Model1_arg->Model1_iov[0].Model1_iov_len);
#else
    assert(0);
#endif
}

Model1___wsum Model1_csum_partial(const void *Model1_buff, int Model1_len, Model1___wsum Model1_sum){
    assert(0);
    return 0;
}

int Model1___sk_backlog_rcv(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb){
    assert(0);
    return 0;
}
int Model1_tcp_rtx_synack(const struct Model1_sock *Model1_sk, struct Model1_request_sock *Model1_req)
{
 const struct Model1_tcp_request_sock_ops *Model1_af_ops = Model1_tcp_rsk(Model1_req)->Model1_af_specific;
 struct Model1_flowi Model1_fl;
 int Model1_res;

 Model1_tcp_rsk(Model1_req)->Model1_txhash = Model1_net_tx_rndhash();
#if CY_ABSTRACT7
  Model1_tcp_v4_send_synack(Model1_sk, ((void *)0), &Model1_fl, Model1_req, ((void *)0), Model1_TCP_SYNACK_NORMAL);
#else
 Model1_res = Model1_af_ops->Model1_send_synack(Model1_sk, ((void *)0), &Model1_fl, Model1_req, ((void *)0), Model1_TCP_SYNACK_NORMAL);
#endif
 if (!Model1_res) {
  (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_RETRANSSEGS] += 1);
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPSYNRETRANS] += 1);
  if (__builtin_expect(!!(Model1_tcp_passive_fastopen(Model1_sk)), 0))
   Model1_tcp_sk(Model1_sk)->Model1_total_retrans++;
 }
 return Model1_res;
}

void Model1___wake_up_sync_key(Model1_wait_queue_head_t *Model1_q, unsigned int Model1_mode, int Model1_nr, void *Model1_key){
    assert(0);
}

/* The code following below sending ACKs in SYN-RECV and TIME-WAIT states
   outside socket context is ugly, certainly. What can I do?
 */

static void Model1_tcp_v4_send_ack(struct Model1_net *Model1_net,
       struct Model1_sk_buff *Model1_skb, Model1_u32 Model1_seq, Model1_u32 Model1_ack,
       Model1_u32 Model1_win, Model1_u32 Model1_tsval, Model1_u32 Model1_tsecr, int Model1_oif,
       struct Model1_tcp_md5sig_key *Model1_key,
       int Model1_reply_flags, Model1_u8 Model1_tos)
{
 const struct Model1_tcphdr *Model1_th = Model1_tcp_hdr(Model1_skb);
 struct {
  struct Model1_tcphdr Model1_th;
  Model1___be32 Model1_opt[(12 >> 2)



   ];
 } Model1_rep;
 struct Model1_ip_reply_arg Model1_arg;

 memset(&Model1_rep.Model1_th, 0, sizeof(struct Model1_tcphdr));
 memset(&Model1_arg, 0, sizeof(Model1_arg));

 Model1_arg.Model1_iov[0].Model1_iov_base = (unsigned char *)&Model1_rep;
 Model1_arg.Model1_iov[0].Model1_iov_len = sizeof(Model1_rep.Model1_th);
 if (Model1_tsecr) {
  Model1_rep.Model1_opt[0] = (( Model1___be32)(__builtin_constant_p((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10))) ? ((__u32)( (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x000000ffUL) << 24) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32(((1 << 24) | (1 << 16) | (8 << 8) | 10))));


  Model1_rep.Model1_opt[1] = (( Model1___be32)(__builtin_constant_p((__u32)((Model1_tsval))) ? ((__u32)( (((__u32)((Model1_tsval)) & (__u32)0x000000ffUL) << 24) | (((__u32)((Model1_tsval)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((Model1_tsval)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((Model1_tsval)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32((Model1_tsval))));
  Model1_rep.Model1_opt[2] = (( Model1___be32)(__builtin_constant_p((__u32)((Model1_tsecr))) ? ((__u32)( (((__u32)((Model1_tsecr)) & (__u32)0x000000ffUL) << 24) | (((__u32)((Model1_tsecr)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((Model1_tsecr)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((Model1_tsecr)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32((Model1_tsecr))));
  Model1_arg.Model1_iov[0].Model1_iov_len += 12;
 }

 /* Swap the send and the receive. */
 Model1_rep.Model1_th.Model1_dest = Model1_th->Model1_source;
 Model1_rep.Model1_th.Model1_source = Model1_th->Model1_dest;
 Model1_rep.Model1_th.Model1_doff = Model1_arg.Model1_iov[0].Model1_iov_len / 4;
 Model1_rep.Model1_th.Model1_seq = (( Model1___be32)(__builtin_constant_p((__u32)((Model1_seq))) ? ((__u32)( (((__u32)((Model1_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)((Model1_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((Model1_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((Model1_seq)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32((Model1_seq))));
 Model1_rep.Model1_th.Model1_ack_seq = (( Model1___be32)(__builtin_constant_p((__u32)((Model1_ack))) ? ((__u32)( (((__u32)((Model1_ack)) & (__u32)0x000000ffUL) << 24) | (((__u32)((Model1_ack)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((Model1_ack)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((Model1_ack)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32((Model1_ack))));
 Model1_rep.Model1_th.Model1_ack = 1;
 Model1_rep.Model1_th.Model1_window = (( Model1___be16)(__builtin_constant_p((Model1___u16)((Model1_win))) ? ((Model1___u16)( (((Model1___u16)((Model1_win)) & (Model1___u16)0x00ffU) << 8) | (((Model1___u16)((Model1_win)) & (Model1___u16)0xff00U) >> 8))) : Model1___fswab16((Model1_win))));
 Model1_arg.Model1_flags = Model1_reply_flags;
 Model1_arg.Model1_csum = Model1_csum_tcpudp_nofold(Model1_ip_hdr(Model1_skb)->Model1_daddr,
          Model1_ip_hdr(Model1_skb)->Model1_saddr, /* XXX */
          Model1_arg.Model1_iov[0].Model1_iov_len, Model1_IPPROTO_TCP, 0);
 Model1_arg.Model1_csumoffset = __builtin_offsetof(struct Model1_tcphdr, Model1_check) / 2;
 if (Model1_oif)
  Model1_arg.Model1_bound_dev_if = Model1_oif;
 Model1_arg.Model1_tos = Model1_tos;
 Model1_local_bh_disable();
#if CY_ABSTRACT1
 //TODO: confirm its correctness
 //net0>ipv4.tcp_sk will be updated inside the function. But this sock seems to be a temporary value, so it won't affect existed socks.         Besides, in our abstraction, we only copy its value.
 Model1_ip_send_unicast_reply(&Model1_Server,
#else
 Model1_ip_send_unicast_reply(*({ (void)(0); ({ do { const void *Model1___vpp_verify = (typeof((Model1_net->Model1_ipv4.Model1_tcp_sk) + 0))((void *)0); (void)Model1___vpp_verify; } while (0); (typeof(*(Model1_net->Model1_ipv4.Model1_tcp_sk)) *)(Model1_net->Model1_ipv4.Model1_tcp_sk); }); }),
#endif
         Model1_skb, &((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_header.Model1_h4.Model1_opt,
         Model1_ip_hdr(Model1_skb)->Model1_saddr, Model1_ip_hdr(Model1_skb)->Model1_daddr,
         &Model1_arg, Model1_arg.Model1_iov[0].Model1_iov_len);

 (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_OUTSEGS] += 1);
 Model1_local_bh_enable();
}
void Model1___local_bh_enable_ip(unsigned long Model1_ip, unsigned int Model1_cnt){
#if CY_ABSTRACT1
    //TODO: disable it so far
#else
    assert(0);
#endif
}
/*
 *	IPv4 request_sock destructor.
 */
void Model1_tcp_v4_reqsk_destructor(struct Model1_request_sock *Model1_req)
{
 Model1_kfree(Model1_inet_rsk(Model1_req)->Model1_opt);
}

static inline __attribute__((no_instrument_function)) struct Model1_tcp_md5sig_key *Model1_tcp_md5_do_lookup(const struct Model1_sock *Model1_sk,
      const union Model1_tcp_md5_addr *Model1_addr,
      int Model1_family)
{
 return ((void *)0);
}

static void Model1_tcp_v4_reqsk_send_ack(const struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb,
      struct Model1_request_sock *Model1_req)
{
 /* sk->sk_state == TCP_LISTEN -> for regular TCP_SYN_RECV
	 * sk->sk_state == TCP_SYN_RECV -> for Fast Open.
	 */
 Model1_u32 Model1_seq = (Model1_sk->Model1___sk_common.Model1_skc_state == Model1_TCP_LISTEN) ? Model1_tcp_rsk(Model1_req)->Model1_snt_isn + 1 :
          Model1_tcp_sk(Model1_sk)->Model1_snd_nxt;

 /* RFC 7323 2.3
	 * The window field (SEG.WND) of every outgoing segment, with the
	 * exception of <SYN> segments, MUST be right-shifted by
	 * Rcv.Wind.Shift bits:
	 */
 Model1_tcp_v4_send_ack(Model1_sock_net(Model1_sk), Model1_skb, Model1_seq,
   Model1_tcp_rsk(Model1_req)->Model1_rcv_nxt,
   Model1_req->Model1___req_common.Model1_skc_rcv_wnd >> Model1_inet_rsk(Model1_req)->Model1_rcv_wscale,
   ((__u32)(Model1_jiffies)),
   Model1_req->Model1_ts_recent,
   0,
   Model1_tcp_md5_do_lookup(Model1_sk, (union Model1_tcp_md5_addr *)&Model1_ip_hdr(Model1_skb)->Model1_daddr,
       2),
   Model1_inet_rsk(Model1_req)->Model1_no_srccheck ? 1 : 0,
   Model1_ip_hdr(Model1_skb)->Model1_tos);
}

void Model1___tcp_v4_send_check(struct Model1_sk_buff *Model1_skb, Model1___be32 Model1_saddr, Model1___be32 Model1_daddr)
{
 struct Model1_tcphdr *Model1_th = Model1_tcp_hdr(Model1_skb);

 if (Model1_skb->Model1_ip_summed == 3) {
  Model1_th->Model1_check = ~Model1_tcp_v4_check(Model1_skb->Model1_len, Model1_saddr, Model1_daddr, 0);
  Model1_skb->Model1_csum_start = Model1_skb_transport_header(Model1_skb) - Model1_skb->Model1_head;
  Model1_skb->Model1_csum_offset = __builtin_offsetof(struct Model1_tcphdr, Model1_check);
 } else {
  Model1_th->Model1_check = Model1_tcp_v4_check(Model1_skb->Model1_len, Model1_saddr, Model1_daddr,
      Model1_csum_partial(Model1_th,
            Model1_th->Model1_doff << 2,
            Model1_skb->Model1_csum));
 }
}

static void Model1_tcp_v4_timewait_ack(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb)
{
 struct Model1_inet_timewait_sock *Model1_tw = Model1_inet_twsk(Model1_sk);
 struct Model1_tcp_timewait_sock *Model1_tcptw = Model1_tcp_twsk(Model1_sk);

 Model1_tcp_v4_send_ack(Model1_sock_net(Model1_sk), Model1_skb,
   Model1_tcptw->Model1_tw_sk.Model1___tw_common.Model1_skc_tw_snd_nxt, Model1_tcptw->Model1_tw_sk.Model1___tw_common.Model1_skc_tw_rcv_nxt,
   Model1_tcptw->Model1_tw_rcv_wnd >> Model1_tw->Model1_tw_rcv_wscale,
   ((__u32)(Model1_jiffies)) + Model1_tcptw->Model1_tw_ts_offset,
   Model1_tcptw->Model1_tw_ts_recent,
   Model1_tw->Model1___tw_common.Model1_skc_bound_dev_if,
   ((void *)0),
   Model1_tw->Model1_tw_transparent ? 1 : 0,
   Model1_tw->Model1_tw_tos
   );

 Model1_inet_twsk_put(Model1_tw);
}
void Model1_inet_csk_reqsk_queue_drop_and_put(struct Model1_sock *Model1_sk, struct Model1_request_sock *Model1_req){
    assert(0);
}
int Model1_sk_filter_trim_cap(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb, unsigned int Model1_cap){
    assert(0);
    return 0;
}

static struct Model1_sock *Model1_tcp_v4_cookie_check(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb)
{






 return Model1_sk;
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

static void Model1_tcp_v4_send_reset(const struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb)
{
 const struct Model1_tcphdr *Model1_th = Model1_tcp_hdr(Model1_skb);
 struct {
  struct Model1_tcphdr Model1_th;



 } Model1_rep;
 struct Model1_ip_reply_arg Model1_arg;







 struct Model1_net *Model1_net;

 /* Never send a reset in response to a reset. */
 if (Model1_th->Model1_rst)
  return;

 /* If sk not NULL, it means we did a successful lookup and incoming
	 * route had to be correct. prequeue might have dropped our dst.
	 */
#if !CY_ABSTRACT1
 if (!Model1_sk && Model1_skb_rtable(Model1_skb)->Model1_rt_type != Model1_RTN_LOCAL)
  return;
#endif

 /* Swap the send and the receive. */
 memset(&Model1_rep, 0, sizeof(Model1_rep));
 Model1_rep.Model1_th.Model1_dest = Model1_th->Model1_source;
 Model1_rep.Model1_th.Model1_source = Model1_th->Model1_dest;
 Model1_rep.Model1_th.Model1_doff = sizeof(struct Model1_tcphdr) / 4;
 Model1_rep.Model1_th.Model1_rst = 1;

 if (Model1_th->Model1_ack) {
  Model1_rep.Model1_th.Model1_seq = Model1_th->Model1_ack_seq;
 } else {
  Model1_rep.Model1_th.Model1_ack = 1;
  Model1_rep.Model1_th.Model1_ack_seq = (( Model1___be32)(__builtin_constant_p((__u32)(((__builtin_constant_p((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq))) ? ((__u32)( (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32(( __u32)(Model1___be32)(Model1_th->Model1_seq))) + Model1_th->Model1_syn + Model1_th->Model1_fin + Model1_skb->Model1_len - (Model1_th->Model1_doff << 2)))) ? ((__u32)( (((__u32)(((__builtin_constant_p((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq))) ? ((__u32)( (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32(( __u32)(Model1___be32)(Model1_th->Model1_seq))) + Model1_th->Model1_syn + Model1_th->Model1_fin + Model1_skb->Model1_len - (Model1_th->Model1_doff << 2))) & (__u32)0x000000ffUL) << 24) | (((__u32)(((__builtin_constant_p((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq))) ? ((__u32)( (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32(( __u32)(Model1___be32)(Model1_th->Model1_seq))) + Model1_th->Model1_syn + Model1_th->Model1_fin + Model1_skb->Model1_len - (Model1_th->Model1_doff << 2))) & (__u32)0x0000ff00UL) << 8) | (((__u32)(((__builtin_constant_p((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq))) ? ((__u32)( (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32(( __u32)(Model1___be32)(Model1_th->Model1_seq))) + Model1_th->Model1_syn + Model1_th->Model1_fin + Model1_skb->Model1_len - (Model1_th->Model1_doff << 2))) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(((__builtin_constant_p((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq))) ? ((__u32)( (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32(( __u32)(Model1___be32)(Model1_th->Model1_seq))) + Model1_th->Model1_syn + Model1_th->Model1_fin + Model1_skb->Model1_len - (Model1_th->Model1_doff << 2))) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32(((__builtin_constant_p((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq))) ? ((__u32)( (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32(( __u32)(Model1___be32)(Model1_th->Model1_seq))) + Model1_th->Model1_syn + Model1_th->Model1_fin + Model1_skb->Model1_len - (Model1_th->Model1_doff << 2)))));

 }

 memset(&Model1_arg, 0, sizeof(Model1_arg));
 Model1_arg.Model1_iov[0].Model1_iov_base = (unsigned char *)&Model1_rep;
 Model1_arg.Model1_iov[0].Model1_iov_len = sizeof(Model1_rep.Model1_th);

 Model1_net = Model1_sk ? Model1_sock_net(Model1_sk) : Model1_dev_net(Model1_skb_dst(Model1_skb)->Model1_dev);
 Model1_arg.Model1_csum = Model1_csum_tcpudp_nofold(Model1_ip_hdr(Model1_skb)->Model1_daddr,
          Model1_ip_hdr(Model1_skb)->Model1_saddr, /* XXX */
          Model1_arg.Model1_iov[0].Model1_iov_len, Model1_IPPROTO_TCP, 0);
 Model1_arg.Model1_csumoffset = __builtin_offsetof(struct Model1_tcphdr, Model1_check) / 2;
 Model1_arg.Model1_flags = (Model1_sk && Model1_inet_sk_transparent(Model1_sk)) ? 1 : 0;

 /* When socket is gone, all binding information is lost.
	 * routing might fail in this case. No choice here, if we choose to force
	 * input interface, we will misroute in case of asymmetric route.
	 */
 if (Model1_sk)
  Model1_arg.Model1_bound_dev_if = Model1_sk->Model1___sk_common.Model1_skc_bound_dev_if;

 ((void)sizeof(char[1 - 2*!!(__builtin_offsetof(struct Model1_sock, Model1___sk_common.Model1_skc_bound_dev_if) != __builtin_offsetof(struct Model1_inet_timewait_sock, Model1___tw_common.Model1_skc_bound_dev_if))]));


 Model1_arg.Model1_tos = Model1_ip_hdr(Model1_skb)->Model1_tos;
 Model1_local_bh_disable();
#if CY_ABSTRACT1
    Model1_ip_send_unicast_reply(&Model1_Server,
#else
 Model1_ip_send_unicast_reply(*({ (void)(0); ({ do { const void *Model1___vpp_verify = (typeof((Model1_net->Model1_ipv4.Model1_tcp_sk) + 0))((void *)0); (void)Model1___vpp_verify; } while (0); (typeof(*(Model1_net->Model1_ipv4.Model1_tcp_sk)) *)(Model1_net->Model1_ipv4.Model1_tcp_sk); }); }),
#endif
         Model1_skb, &((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_header.Model1_h4.Model1_opt,
         Model1_ip_hdr(Model1_skb)->Model1_saddr, Model1_ip_hdr(Model1_skb)->Model1_daddr,
         &Model1_arg, Model1_arg.Model1_iov[0].Model1_iov_len);

 (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_OUTSEGS] += 1);
 (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_OUTRSTS] += 1);
 Model1_local_bh_enable();





}
int Model1___ip_options_echo(struct Model1_ip_options *Model1_dopt, struct Model1_sk_buff *Model1_skb,
        const struct Model1_ip_options *Model1_sopt){
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
bool Model1_tcp_prequeue(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 if (Model1_sysctl_tcp_low_latency || !Model1_tp->Model1_ucopy.Model1_task)
  return false;

 if (Model1_skb->Model1_len <= Model1_tcp_hdrlen(Model1_skb) &&
     Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue) == 0)
  return false;

 /* Before escaping RCU protected region, we need to take care of skb
	 * dst. Prequeue is only enabled for established sockets.
	 * For such sockets, we might need the skb dst only to set sk->sk_rx_dst
	 * Instead of doing full sk_rx_dst validity here, let's perform
	 * an optimistic check.
	 */
 if (__builtin_expect(!!(Model1_sk->Model1_sk_rx_dst), 1))
  Model1_skb_dst_drop(Model1_skb);
 else
  Model1_skb_dst_force_safe(Model1_skb);

 Model1___skb_queue_tail(&Model1_tp->Model1_ucopy.Model1_prequeue, Model1_skb);
 Model1_tp->Model1_ucopy.Model1_memory += Model1_skb->Model1_truesize;
 if (Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue) >= 32 ||
     Model1_tp->Model1_ucopy.Model1_memory + Model1_atomic_read(&Model1_sk->Model1_sk_backlog.Model1_rmem_alloc) > Model1_sk->Model1_sk_rcvbuf) {
  struct Model1_sk_buff *Model1_skb1;

  do { if (Model1_sock_owned_by_user(Model1_sk)) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);
  ({ Model1___this_cpu_preempt_check("add"); do { do { const void *Model1___vpp_verify = (typeof((&((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) + 0))((void *)0); (void)Model1___vpp_verify; } while (0); switch(sizeof((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) { case 1: do { typedef typeof(((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) Model1_pao_T__; const int Model1_pao_ID__ = (__builtin_constant_p(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)) && ((Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)) == 1 || (Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)) == -1)) ? (int)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)) : 0; if (0) { Model1_pao_T__ Model1_pao_tmp__; Model1_pao_tmp__ = (Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)); (void)Model1_pao_tmp__; } switch (sizeof(((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))) { case 1: if (Model1_pao_ID__ == 1) asm("incb """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model1_pao_ID__ == -1) asm("decb """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addb %1, """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) : "qi" ((Model1_pao_T__)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)))); break; case 2: if (Model1_pao_ID__ == 1) asm("incw """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model1_pao_ID__ == -1) asm("decw """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addw %1, """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) : "ri" ((Model1_pao_T__)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)))); break; case 4: if (Model1_pao_ID__ == 1) asm("incl """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model1_pao_ID__ == -1) asm("decl """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addl %1, """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) : "ri" ((Model1_pao_T__)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)))); break; case 8: if (Model1_pao_ID__ == 1) asm("incq """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model1_pao_ID__ == -1) asm("decq """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addq %1, """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) : "re" ((Model1_pao_T__)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)))); break; default: Model1___bad_percpu_size(); } } while (0);break; case 2: do { typedef typeof(((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) Model1_pao_T__; const int Model1_pao_ID__ = (__builtin_constant_p(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)) && ((Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)) == 1 || (Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)) == -1)) ? (int)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)) : 0; if (0) { Model1_pao_T__ Model1_pao_tmp__; Model1_pao_tmp__ = (Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)); (void)Model1_pao_tmp__; } switch (sizeof(((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))) { case 1: if (Model1_pao_ID__ == 1) asm("incb """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model1_pao_ID__ == -1) asm("decb """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addb %1, """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) : "qi" ((Model1_pao_T__)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)))); break; case 2: if (Model1_pao_ID__ == 1) asm("incw """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model1_pao_ID__ == -1) asm("decw """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addw %1, """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) : "ri" ((Model1_pao_T__)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)))); break; case 4: if (Model1_pao_ID__ == 1) asm("incl """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model1_pao_ID__ == -1) asm("decl """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addl %1, """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) : "ri" ((Model1_pao_T__)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)))); break; case 8: if (Model1_pao_ID__ == 1) asm("incq """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model1_pao_ID__ == -1) asm("decq """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addq %1, """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) : "re" ((Model1_pao_T__)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)))); break; default: Model1___bad_percpu_size(); } } while (0);break; case 4: do { typedef typeof(((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) Model1_pao_T__; const int Model1_pao_ID__ = (__builtin_constant_p(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)) && ((Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)) == 1 || (Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)) == -1)) ? (int)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)) : 0; if (0) { Model1_pao_T__ Model1_pao_tmp__; Model1_pao_tmp__ = (Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)); (void)Model1_pao_tmp__; } switch (sizeof(((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))) { case 1: if (Model1_pao_ID__ == 1) asm("incb """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model1_pao_ID__ == -1) asm("decb """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addb %1, """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) : "qi" ((Model1_pao_T__)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)))); break; case 2: if (Model1_pao_ID__ == 1) asm("incw """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model1_pao_ID__ == -1) asm("decw """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addw %1, """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) : "ri" ((Model1_pao_T__)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)))); break; case 4: if (Model1_pao_ID__ == 1) asm("incl """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model1_pao_ID__ == -1) asm("decl """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addl %1, """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) : "ri" ((Model1_pao_T__)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)))); break; case 8: if (Model1_pao_ID__ == 1) asm("incq """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model1_pao_ID__ == -1) asm("decq """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addq %1, """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) : "re" ((Model1_pao_T__)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)))); break; default: Model1___bad_percpu_size(); } } while (0);break; case 8: do { typedef typeof(((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) Model1_pao_T__; const int Model1_pao_ID__ = (__builtin_constant_p(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)) && ((Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)) == 1 || (Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)) == -1)) ? (int)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)) : 0; if (0) { Model1_pao_T__ Model1_pao_tmp__; Model1_pao_tmp__ = (Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)); (void)Model1_pao_tmp__; } switch (sizeof(((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))) { case 1: if (Model1_pao_ID__ == 1) asm("incb """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model1_pao_ID__ == -1) asm("decb """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addb %1, """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) : "qi" ((Model1_pao_T__)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)))); break; case 2: if (Model1_pao_ID__ == 1) asm("incw """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model1_pao_ID__ == -1) asm("decw """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addw %1, """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) : "ri" ((Model1_pao_T__)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)))); break; case 4: if (Model1_pao_ID__ == 1) asm("incl """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model1_pao_ID__ == -1) asm("decl """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addl %1, """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) : "ri" ((Model1_pao_T__)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)))); break; case 8: if (Model1_pao_ID__ == 1) asm("incq """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else if (Model1_pao_ID__ == -1) asm("decq """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED]))); else asm("addq %1, """ "%" "0" : "+m" (((Model1_sock_net(Model1_sk))->Model1_mib.Model1_net_statistics->Model1_mibs[Model1_LINUX_MIB_TCPPREQUEUEDROPPED])) : "re" ((Model1_pao_T__)(Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue)))); break; default: Model1___bad_percpu_size(); } } while (0);break; default: Model1___bad_size_call_parameter();break; } } while (0); });


  while ((Model1_skb1 = Model1___skb_dequeue(&Model1_tp->Model1_ucopy.Model1_prequeue)) != ((void *)0))
   Model1_sk_backlog_rcv(Model1_sk, Model1_skb1);

  Model1_tp->Model1_ucopy.Model1_memory = 0;
 } else if (Model1_skb_queue_len(&Model1_tp->Model1_ucopy.Model1_prequeue) == 1) {
  Model1___wake_up_sync_key((Model1_sk_sleep(Model1_sk)), 1, 1, (void *) (0x0001 | 0x0040 | 0x0080));

  if (!Model1_inet_csk_ack_scheduled(Model1_sk))
   Model1_inet_csk_reset_xmit_timer(Model1_sk, 2,
        (3 * Model1_tcp_rto_min(Model1_sk)) / 4,
        ((unsigned)(120*1000)));
 }
 return true;
}

void Model1_inet_twsk_put(struct Model1_inet_timewait_sock *Model1_tw){
    assert(0);
}

struct Model1_sock *Model1___inet_lookup_listener(struct Model1_net *Model1_net,
        struct Model1_inet_hashinfo *Model1_hashinfo,
        struct Model1_sk_buff *Model1_skb, int Model1_doff,
        const Model1___be32 Model1_saddr, const Model1___be16 Model1_sport,
        const Model1___be32 Model1_daddr,
        const unsigned short Model1_hnum,
        const int Model1_dif){
#if CY_ABSTRACT1
    return &Model1_Server_L;
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

int Model1_tcp_child_process(struct Model1_sock *Model1_parent, struct Model1_sock *Model1_child,
        struct Model1_sk_buff *Model1_skb)
{
 int Model1_ret = 0;
 int Model1_state = Model1_child->Model1___sk_common.Model1_skc_state;

 Model1_tcp_segs_in(Model1_tcp_sk(Model1_child), Model1_skb);
 if (!Model1_sock_owned_by_user(Model1_child)) {
  Model1_ret = Model1_tcp_rcv_state_process(Model1_child, Model1_skb);
  /* Wakeup parent, send SIGIO */
  if (Model1_state == Model1_TCP_SYN_RECV && Model1_child->Model1___sk_common.Model1_skc_state != Model1_state)
#if CY_ABSTRACT3
      //not sure which function it points to
      //1. net/core/sock.c: sock_def_readable  (we abstract it since we avoid concurrency)
      //2. net/netlink/af_netlink.c: netlink_data_ready (its empty)
      //Therefore, we just abstrct it
      ;
#else
   Model1_parent->Model1_sk_data_ready(Model1_parent);
#endif
 } else {
  /* Alas, it is possible again, because we do lookup
		 * in main socket hash table and lock on listening
		 * socket does not protect us more.
		 */
  Model1___sk_add_backlog(Model1_child, Model1_skb);
 }

 Model1_spin_unlock(&((Model1_child)->Model1_sk_lock.Model1_slock));
 Model1_sock_put(Model1_child);
 return Model1_ret;
}
unsigned char *Model1___pskb_pull_tail(struct Model1_sk_buff *Model1_skb, int Model1_delta){
#if CY_ABSTRACT1
    // Moves tail of skb head forward, copying data from fragmented part, when it is necessary.
    // Assume it always fail due to malloc failure
    return NULL;
#else
    assert(0);
    return NULL;
#endif
}

static inline __attribute__((no_instrument_function)) int Model1_xfrm4_policy_check(struct Model1_sock *Model1_sk, int Model1_dir, struct Model1_sk_buff *Model1_skb)
{
 return 1;
}
__u32 Model1_secure_tcp_sequence_number(Model1___be32 Model1_saddr, Model1___be32 Model1_daddr,
     Model1___be16 Model1_sport, Model1___be16 Model1_dport){
    return ack_val;
}
void *Model1_memmove(void *Model1_dest, const void *Model1_src, Model1_size_t Model1_count){
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
struct Model1_sock *Model1___inet_lookup_established(struct Model1_net *Model1_net,
           struct Model1_inet_hashinfo *Model1_hashinfo,
           const Model1___be32 Model1_saddr, const Model1___be16 Model1_sport,
           const Model1___be32 Model1_daddr, const Model1_u16 Model1_hnum,
           const int Model1_dif){
#if CY_ABSTRACT1
    if (Model1_Src_sk){
        if (((struct Model1_sock *)&Model1_Server_A)->Model1___sk_common.Model1_skc_state != 0)
            return &Model1_Server_A;
        else if (((struct Model1_request_sock *)&Model1_Req_A)->Model1___req_common.Model1_skc_state != 0)
            return &Model1_Req_A;
    }
    else{
        if (((struct Model1_sock *)&Model1_Server)->Model1___sk_common.Model1_skc_state != 0)
            return &Model1_Server;
        else if (((struct Model1_request_sock *)&Model1_Req)->Model1___req_common.Model1_skc_state != 0)
            return &Model1_Req;
    }
    return NULL;
#else
    assert(0);
    return NULL;
#endif
}

void Model1_inet_twsk_deschedule_put(struct Model1_inet_timewait_sock *Model1_tw){
    assert(0);
}

static inline __attribute__((no_instrument_function)) void Model1_sk_mark_napi_id(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb)
{
}

struct Model1_dst_entry *Model1_inet_csk_route_req(const struct Model1_sock *Model1_sk, struct Model1_flowi4 *Model1_fl4,
         const struct Model1_request_sock *Model1_req){
    assert(0);
    return NULL;
}

/* Called with rcu_read_lock() */
enum Model1_tcp_tw_status Model1_tcp_timewait_state_process(struct Model1_inet_timewait_sock *Model1_tw,
           struct Model1_sk_buff *Model1_skb,
           const struct Model1_tcphdr *Model1_th){
    assert(0);
    return 0;
}
static bool Model1_tcp_v4_inbound_md5_hash(const struct Model1_sock *Model1_sk,
        const struct Model1_sk_buff *Model1_skb)
{
 return false;
}

static void Model1_tcp_v4_init_req(struct Model1_request_sock *Model1_req,
       const struct Model1_sock *Model1_sk_listener,
       struct Model1_sk_buff *Model1_skb)
{
 struct Model1_inet_request_sock *Model1_ireq = Model1_inet_rsk(Model1_req);

 Model1_sk_rcv_saddr_set(Model1_req_to_sk(Model1_req), Model1_ip_hdr(Model1_skb)->Model1_daddr);
 Model1_sk_daddr_set(Model1_req_to_sk(Model1_req), Model1_ip_hdr(Model1_skb)->Model1_saddr);
 Model1_ireq->Model1_no_srccheck = Model1_inet_sk(Model1_sk_listener)->Model1_transparent;
 Model1_ireq->Model1_opt = Model1_tcp_v4_save_options(Model1_skb);
}

static struct Model1_dst_entry *Model1_tcp_v4_route_req(const struct Model1_sock *Model1_sk,
       struct Model1_flowi *Model1_fl,
       const struct Model1_request_sock *Model1_req,
       bool *Model1_strict)
{
 struct Model1_dst_entry *Model1_dst = Model1_inet_csk_route_req(Model1_sk, &Model1_fl->Model1_u.Model1_ip4, Model1_req);

 if (Model1_strict) {
  if (Model1_fl->Model1_u.Model1_ip4.Model1_daddr == Model1_inet_rsk(Model1_req)->Model1_req.Model1___req_common.Model1_skc_daddr)
   *Model1_strict = true;
  else
   *Model1_strict = false;
 }

 return Model1_dst;
}

static __u32 Model1_tcp_v4_init_sequence(const struct Model1_sk_buff *Model1_skb)
{
#if CY_ABSTRACT3
 if (Model1_Src_sk) //not spoofed
     return ack_val_a;
 else
     return ack_val;
 //return ack_val; //ack_val and ack_val_a have same value
#else
 return Model1_secure_tcp_sequence_number(Model1_ip_hdr(Model1_skb)->Model1_daddr,
       Model1_ip_hdr(Model1_skb)->Model1_saddr,
       Model1_tcp_hdr(Model1_skb)->Model1_dest,
       Model1_tcp_hdr(Model1_skb)->Model1_source);
#endif
}

/*
 *	Send a SYN-ACK after having received a SYN.
 *	This still operates on a request_sock only, not on a big
 *	socket.
 */
static int Model1_tcp_v4_send_synack(const struct Model1_sock *Model1_sk, struct Model1_dst_entry *Model1_dst,
         struct Model1_flowi *Model1_fl,
         struct Model1_request_sock *Model1_req,
         struct Model1_tcp_fastopen_cookie *Model1_foc,
         enum Model1_tcp_synack_type Model1_synack_type)
{
 const struct Model1_inet_request_sock *Model1_ireq = Model1_inet_rsk(Model1_req);
 struct Model1_flowi4 Model1_fl4;
 int err = -1;
 struct Model1_sk_buff *Model1_skb;

 /* First, grab a route. */
#if CY_ABSTRACT3
 //TODO: confirm if we can ignore it. 
 //Assumption: we work on TCP layer only, so we don't care about route information
#else
 if (!Model1_dst && (Model1_dst = Model1_inet_csk_route_req(Model1_sk, &Model1_fl4, Model1_req)) == ((void *)0))
  return -1;
#endif

 Model1_skb = Model1_tcp_make_synack(Model1_sk, Model1_dst, Model1_req, Model1_foc, Model1_synack_type);

 if (Model1_skb) {
  Model1___tcp_v4_send_check(Model1_skb, Model1_ireq->Model1_req.Model1___req_common.Model1_skc_rcv_saddr, Model1_ireq->Model1_req.Model1___req_common.Model1_skc_daddr);

  err = Model1_ip_build_and_send_pkt(Model1_skb, Model1_sk, Model1_ireq->Model1_req.Model1___req_common.Model1_skc_rcv_saddr,
         Model1_ireq->Model1_req.Model1___req_common.Model1_skc_daddr,
         Model1_ireq->Model1_opt);
  err = ((err) == 0x02 ? 0 : (err));
 }

 return err;
}

int Model1_tcp_v4_conn_request(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb)
{
 /* Never answer to SYNs send to broadcast or multicast */
#if !CY_ABSTRACT1
 if (Model1_skb_rtable(Model1_skb)->Model1_rt_flags & (0x10000000 | 0x20000000))
  goto Model1_drop;
#endif

 return Model1_tcp_conn_request(&Model1_tcp_request_sock_ops,
    &Model1_tcp_request_sock_ipv4_ops, Model1_sk, Model1_skb);

Model1_drop:
 Model1_tcp_listendrop(Model1_sk);
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
int Model1_tcp_v4_do_rcv(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb)
{
 struct Model1_sock *Model1_rsk;
 if (Model1_sk->Model1___sk_common.Model1_skc_state == Model1_TCP_ESTABLISHED) { /* Fast path */
  struct Model1_dst_entry *Model1_dst = Model1_sk->Model1_sk_rx_dst;

  Model1_sock_rps_save_rxhash(Model1_sk, Model1_skb);
  Model1_sk_mark_napi_id(Model1_sk, Model1_skb);
  if (Model1_dst) {
   if (Model1_inet_sk(Model1_sk)->Model1_rx_dst_ifindex != Model1_skb->Model1_skb_iif ||
       !Model1_dst->Model1_ops->Model1_check(Model1_dst, 0)) { //based on our assumption (no dst process), we will ignore this function; But not sure how it will be processed
    Model1_dst_release(Model1_dst);
    Model1_sk->Model1_sk_rx_dst = ((void *)0);
   }
  }
  Model1_tcp_rcv_established(Model1_sk, Model1_skb, Model1_tcp_hdr(Model1_skb), Model1_skb->Model1_len);
  return 0;
 }

 if (Model1_tcp_checksum_complete(Model1_skb))
  goto Model1_csum_err;

 if (Model1_sk->Model1___sk_common.Model1_skc_state == Model1_TCP_LISTEN) {
  struct Model1_sock *Model1_nsk = Model1_tcp_v4_cookie_check(Model1_sk, Model1_skb);

  if (!Model1_nsk)
   goto Model1_discard;
  if (Model1_nsk != Model1_sk) {
   Model1_sock_rps_save_rxhash(Model1_nsk, Model1_skb);
   Model1_sk_mark_napi_id(Model1_nsk, Model1_skb);
   if (Model1_tcp_child_process(Model1_sk, Model1_nsk, Model1_skb)) {
    Model1_rsk = Model1_nsk;
    goto Model1_reset;
   }
   return 0;
  }
 } else
  Model1_sock_rps_save_rxhash(Model1_sk, Model1_skb);

 if (Model1_tcp_rcv_state_process(Model1_sk, Model1_skb)) {
  Model1_rsk = Model1_sk;
  goto Model1_reset;
 }
 return 0;

Model1_reset:
 Model1_tcp_v4_send_reset(Model1_rsk, Model1_skb);
Model1_discard:
 Model1_kfree_skb(Model1_skb);
 /* Be careful here. If this function gets more complicated and
	 * gcc suffers from register pressure on the x86, sk (in %ebx)
	 * might be destroyed here. This current version compiles correctly,
	 * but you have been warned.
	 */
 return 0;

Model1_csum_err:
 (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_CSUMERRORS] += 1);
 (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_INERRS] += 1);
 goto Model1_discard;
}

/*
 * The three way handshake has completed - we got a valid synack -
 * now create the new socket.
 */
struct Model1_sock *Model1_tcp_v4_syn_recv_sock(const struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb,
      struct Model1_request_sock *Model1_req,
      struct Model1_dst_entry *Model1_dst,
      struct Model1_request_sock *Model1_req_unhash,
      bool *Model1_own_req)
{
 struct Model1_inet_request_sock *Model1_ireq;
 struct Model1_inet_sock *Model1_newinet;
 struct Model1_tcp_sock *Model1_newtp;
 struct Model1_sock *Model1_newsk;



 struct Model1_ip_options_rcu *Model1_inet_opt;

 if (Model1_sk_acceptq_is_full(Model1_sk))
  goto Model1_exit_overflow;

 Model1_newsk = Model1_tcp_create_openreq_child(Model1_sk, Model1_req, Model1_skb);
 if (!Model1_newsk)
  goto Model1_exit_nonewsk;

 Model1_newsk->Model1_sk_gso_type = Model1_SKB_GSO_TCPV4;
 Model1_inet_sk_rx_dst_set(Model1_newsk, Model1_skb);

 Model1_newtp = Model1_tcp_sk(Model1_newsk);
 Model1_newinet = Model1_inet_sk(Model1_newsk);
 Model1_ireq = Model1_inet_rsk(Model1_req);
 Model1_sk_daddr_set(Model1_newsk, Model1_ireq->Model1_req.Model1___req_common.Model1_skc_daddr);
 Model1_sk_rcv_saddr_set(Model1_newsk, Model1_ireq->Model1_req.Model1___req_common.Model1_skc_rcv_saddr);
 Model1_newsk->Model1___sk_common.Model1_skc_bound_dev_if = Model1_ireq->Model1_req.Model1___req_common.Model1_skc_bound_dev_if;
 Model1_newinet->Model1_inet_saddr = Model1_ireq->Model1_req.Model1___req_common.Model1_skc_rcv_saddr;
 Model1_inet_opt = Model1_ireq->Model1_opt;
 ({ Model1_uintptr_t Model1__r_a_p__v = (Model1_uintptr_t)(Model1_inet_opt); if (__builtin_constant_p(Model1_inet_opt) && (Model1__r_a_p__v) == (Model1_uintptr_t)((void *)0)) ({ union { typeof((Model1_newinet->Model1_inet_opt)) Model1___val; char Model1___c[1]; } Model1___u = { .Model1___val = ( typeof((Model1_newinet->Model1_inet_opt))) ((typeof(Model1_newinet->Model1_inet_opt))(Model1__r_a_p__v)) }; Model1___write_once_size(&((Model1_newinet->Model1_inet_opt)), Model1___u.Model1___c, sizeof((Model1_newinet->Model1_inet_opt))); Model1___u.Model1___val; }); else do { do { bool Model1___cond = !((sizeof(*&Model1_newinet->Model1_inet_opt) == sizeof(char) || sizeof(*&Model1_newinet->Model1_inet_opt) == sizeof(short) || sizeof(*&Model1_newinet->Model1_inet_opt) == sizeof(int) || sizeof(*&Model1_newinet->Model1_inet_opt) == sizeof(long))); extern void Model1___compiletime_assert_1297(void) ; if (Model1___cond) Model1___compiletime_assert_1297(); do { ((void)sizeof(char[1 - 2 * Model1___cond])); } while (0); } while (0); __asm__ __volatile__("": : :"memory"); ({ union { typeof(*&Model1_newinet->Model1_inet_opt) Model1___val; char Model1___c[1]; } Model1___u = { .Model1___val = ( typeof(*&Model1_newinet->Model1_inet_opt)) ((typeof(*((typeof(Model1_newinet->Model1_inet_opt))Model1__r_a_p__v)) *)((typeof(Model1_newinet->Model1_inet_opt))Model1__r_a_p__v)) }; Model1___write_once_size(&(*&Model1_newinet->Model1_inet_opt), Model1___u.Model1___c, sizeof(*&Model1_newinet->Model1_inet_opt)); Model1___u.Model1___val; }); } while (0); Model1__r_a_p__v; });
 Model1_ireq->Model1_opt = ((void *)0);
 Model1_newinet->Model1_mc_index = Model1_inet_iif(Model1_skb);
 Model1_newinet->Model1_mc_ttl = Model1_ip_hdr(Model1_skb)->Model1_ttl;
 Model1_newinet->Model1_rcv_tos = Model1_ip_hdr(Model1_skb)->Model1_tos;
 Model1_inet_csk(Model1_newsk)->Model1_icsk_ext_hdr_len = 0;
 if (Model1_inet_opt)
  Model1_inet_csk(Model1_newsk)->Model1_icsk_ext_hdr_len = Model1_inet_opt->Model1_opt.Model1_optlen;
 Model1_newinet->Model1_inet_id = Model1_newtp->Model1_write_seq ^ Model1_jiffies;

#if !CY_ABSTRACT1
 //dst is IP layer. TODO: currently we ignroe it
 if (!Model1_dst) {
  Model1_dst = Model1_inet_csk_route_child_sock(Model1_sk, Model1_newsk, Model1_req);
  if (!Model1_dst)
   goto Model1_put_and_exit;
 } else {
  /* syncookie case : see end of cookie_v4_check() */
 }
 Model1_sk_setup_caps(Model1_newsk, Model1_dst);

 Model1_tcp_ca_openreq_child(Model1_newsk, Model1_dst);
 Model1_tcp_sync_mss(Model1_newsk, Model1_dst_mtu(Model1_dst));
 Model1_newtp->Model1_advmss = Model1_dst_metric_advmss(Model1_dst);
#endif
 if (Model1_tcp_sk(Model1_sk)->Model1_rx_opt.Model1_user_mss &&
     Model1_tcp_sk(Model1_sk)->Model1_rx_opt.Model1_user_mss < Model1_newtp->Model1_advmss)
  Model1_newtp->Model1_advmss = Model1_tcp_sk(Model1_sk)->Model1_rx_opt.Model1_user_mss;

 Model1_tcp_initialize_rcv_mss(Model1_newsk);
 if (Model1___inet_inherit_port(Model1_sk, Model1_newsk) < 0)
  goto Model1_put_and_exit;
 *Model1_own_req = Model1_inet_ehash_nolisten(Model1_newsk, Model1_req_to_sk(Model1_req_unhash));
 if (*Model1_own_req)
  Model1_tcp_move_syn(Model1_newtp, Model1_req);

 return Model1_newsk;

Model1_exit_overflow:
 (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_LISTENOVERFLOWS] += 1);
Model1_exit_nonewsk:
 Model1_dst_release(Model1_dst);
Model1_exit:
 Model1_tcp_listendrop(Model1_sk);
 return ((void *)0);
Model1_put_and_exit:
 Model1_inet_csk_prepare_forced_close(Model1_newsk);
 Model1_tcp_done(Model1_newsk);
 goto Model1_exit;
}
/*
 *	From tcp_input.c
 */

int Model1_tcp_v4_rcv(struct Model1_sk_buff *Model1_skb)
{
#if CY_ABSTRACT3
//    if (Model1_Src_sk == false && Model1_Port_guessed == false)
//        return 0;
#endif
 struct Model1_net *Model1_net = Model1_dev_net(Model1_skb->Model1_dev);
 const struct Model1_iphdr *Model1_iph;
 const struct Model1_tcphdr *Model1_th;
 bool Model1_refcounted;
 struct Model1_sock *Model1_sk;
 int Model1_ret;

 if (Model1_skb->Model1_pkt_type != 0)
  goto Model1_discard_it;

 /* Count it even if it's bad */
 (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_INSEGS] += 1);

 if (!Model1_pskb_may_pull(Model1_skb, sizeof(struct Model1_tcphdr)))
  goto Model1_discard_it;

 Model1_th = (const struct Model1_tcphdr *)Model1_skb->Model1_data;

 if (__builtin_expect(!!(Model1_th->Model1_doff < sizeof(struct Model1_tcphdr) / 4), 0))
  goto Model1_bad_packet;
 if (!Model1_pskb_may_pull(Model1_skb, Model1_th->Model1_doff * 4))
  goto Model1_discard_it;

 /* An explanation is required here, I think.
	 * Packet length and doff are validated by header prediction,
	 * provided case of th->doff==0 is eliminated.
	 * So, we defer the checks. */

#if !CY_ABSTRACT1
 if (({ Model1___sum16 Model1___ret = 0; Model1_skb->Model1_csum_valid = 0; if (Model1___skb_checksum_validate_needed(Model1_skb, false, 0)) Model1___ret = Model1___skb_checksum_validate_complete(Model1_skb, false, Model1_inet_compute_pseudo(Model1_skb, Model1_IPPROTO_TCP)); Model1___ret; }))
  goto Model1_csum_error;
#endif

 Model1_th = (const struct Model1_tcphdr *)Model1_skb->Model1_data;
 Model1_iph = Model1_ip_hdr(Model1_skb);
 /* This is tricky : We move IPCB at its correct location into TCP_SKB_CB()
	 * barrier() makes sure compiler wont play fool^Waliasing games.
	 */
#if !CY_ABSTRACT1
 Model1_memmove(&((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_header.Model1_h4, ((struct Model1_inet_skb_parm*)((Model1_skb)->Model1_cb)),
  sizeof(struct Model1_inet_skb_parm));
#endif
 __asm__ __volatile__("": : :"memory");

 ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq = (__builtin_constant_p((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq))) ? ((__u32)( (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32(( __u32)(Model1___be32)(Model1_th->Model1_seq)));
 ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq = (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq + Model1_th->Model1_syn + Model1_th->Model1_fin +
        Model1_skb->Model1_len - Model1_th->Model1_doff * 4);
 ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_ack_seq = (__builtin_constant_p((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_ack_seq))) ? ((__u32)( (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_ack_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_ack_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_ack_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_ack_seq)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32(( __u32)(Model1___be32)(Model1_th->Model1_ack_seq)));
 ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_tcp_flags = (((Model1_u_int8_t *)Model1_th)[13]);
 ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_tcp_tw_isn = 0;
 ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_ip_dsfield = Model1_ipv4_get_dsfield(Model1_iph);
 ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked = 0;

Model1_lookup:
 Model1_sk = Model1___inet_lookup_skb(&Model1_tcp_hashinfo, Model1_skb, Model1___tcp_hdrlen(Model1_th), Model1_th->Model1_source,
          Model1_th->Model1_dest, &Model1_refcounted);
 if (!Model1_sk)
  goto Model1_no_tcp_socket;

Model1_process:
 if (Model1_sk->Model1___sk_common.Model1_skc_state == Model1_TCP_TIME_WAIT)
  goto Model1_do_time_wait;

 if (Model1_sk->Model1___sk_common.Model1_skc_state == Model1_TCP_NEW_SYN_RECV) {
  struct Model1_request_sock *Model1_req = Model1_inet_reqsk(Model1_sk);
  struct Model1_sock *Model1_nsk;

  Model1_sk = Model1_req->Model1___req_common.Model1_skc_listener;
  if (__builtin_expect(!!(Model1_tcp_v4_inbound_md5_hash(Model1_sk, Model1_skb)), 0)) {
   Model1_reqsk_put(Model1_req);
   goto Model1_discard_it;
  }
  if (__builtin_expect(!!(Model1_sk->Model1___sk_common.Model1_skc_state != Model1_TCP_LISTEN), 0)) {
   Model1_inet_csk_reqsk_queue_drop_and_put(Model1_sk, Model1_req);
   goto Model1_lookup;
  }

  /* We own a reference on the listener, increase it again
		 * as we might lose it too soon.
		 */
  Model1_sock_hold(Model1_sk);
  Model1_refcounted = true;
  Model1_nsk = Model1_tcp_check_req(Model1_sk, Model1_skb, Model1_req, false);
  if (!Model1_nsk) {
   Model1_reqsk_put(Model1_req);
   goto Model1_discard_and_relse;
  }
  if (Model1_nsk == Model1_sk) {
   Model1_reqsk_put(Model1_req);
  } else if (Model1_tcp_child_process(Model1_sk, Model1_nsk, Model1_skb)) {
   Model1_tcp_v4_send_reset(Model1_nsk, Model1_skb);
   goto Model1_discard_and_relse;
  } else {
   Model1_sock_put(Model1_sk);
   return 0;
  }
 }
#if !CY_ABSTRACT1
 if (__builtin_expect(!!(Model1_iph->Model1_ttl < Model1_inet_sk(Model1_sk)->Model1_min_ttl), 0)) {
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPMINTTLDROP] += 1);
  goto Model1_discard_and_relse;
 }
#endif

 if (!Model1_xfrm4_policy_check(Model1_sk, Model1_XFRM_POLICY_IN, Model1_skb))
  goto Model1_discard_and_relse;

 if (Model1_tcp_v4_inbound_md5_hash(Model1_sk, Model1_skb))
  goto Model1_discard_and_relse;

 Model1_nf_reset(Model1_skb);

#if !CY_ABSTRACT1
 if (Model1_sk_filter(Model1_sk, Model1_skb))
  goto Model1_discard_and_relse;
#endif

 Model1_skb->Model1_dev = ((void *)0);

 if (Model1_sk->Model1___sk_common.Model1_skc_state == Model1_TCP_LISTEN) {
  Model1_ret = Model1_tcp_v4_do_rcv(Model1_sk, Model1_skb);
  goto Model1_put_and_return;
 }

 Model1_sk_incoming_cpu_update(Model1_sk);

 do { do { __asm__ __volatile__("": : :"memory"); do { (void)0; (void)(((void)(1), (Model1_spinlock_check(&((Model1_sk)->Model1_sk_lock.Model1_slock))))); } while (0); } while (0); } while (0);
 Model1_tcp_segs_in(Model1_tcp_sk(Model1_sk), Model1_skb);
 Model1_ret = 0;
 if (!Model1_sock_owned_by_user(Model1_sk)) {
  if (!Model1_tcp_prequeue(Model1_sk, Model1_skb))
   Model1_ret = Model1_tcp_v4_do_rcv(Model1_sk, Model1_skb);
 }
#if !CY_ABSTRACT1
 else if (__builtin_expect(!!(Model1_sk_add_backlog(Model1_sk, Model1_skb, Model1_sk->Model1_sk_rcvbuf + Model1_sk->Model1_sk_sndbuf)), 0)) {

  Model1_spin_unlock(&((Model1_sk)->Model1_sk_lock.Model1_slock));
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPBACKLOGDROP] += 1);
  goto Model1_discard_and_relse;
 }
#endif
 Model1_spin_unlock(&((Model1_sk)->Model1_sk_lock.Model1_slock));
Model1_put_and_return:
 if (Model1_refcounted)
  Model1_sock_put(Model1_sk);

 return Model1_ret;
Model1_no_tcp_socket:
 if (!Model1_xfrm4_policy_check(((void *)0), Model1_XFRM_POLICY_IN, Model1_skb))
  goto Model1_discard_it;

 if (Model1_tcp_checksum_complete(Model1_skb)) {
Model1_csum_error:
  (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_CSUMERRORS] += 1);
Model1_bad_packet:
  (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_INERRS] += 1);
 } else {
  Model1_tcp_v4_send_reset(((void *)0), Model1_skb);
 }

Model1_discard_it:
 /* Discard frame. */
 Model1_kfree_skb(Model1_skb);
 return 0;

Model1_discard_and_relse:
 Model1_sk_drops_add(Model1_sk, Model1_skb);
 if (Model1_refcounted)
  Model1_sock_put(Model1_sk);
 goto Model1_discard_it;

Model1_do_time_wait:
 if (!Model1_xfrm4_policy_check(((void *)0), Model1_XFRM_POLICY_IN, Model1_skb)) {
  Model1_inet_twsk_put(Model1_inet_twsk(Model1_sk));
  goto Model1_discard_it;
 }

 if (Model1_tcp_checksum_complete(Model1_skb)) {
  Model1_inet_twsk_put(Model1_inet_twsk(Model1_sk));
  goto Model1_csum_error;
 }
 switch (Model1_tcp_timewait_state_process(Model1_inet_twsk(Model1_sk), Model1_skb, Model1_th)) {
 case Model1_TCP_TW_SYN: {
  struct Model1_sock *Model1_sk2 = Model1_inet_lookup_listener(Model1_dev_net(Model1_skb->Model1_dev),
       &Model1_tcp_hashinfo, Model1_skb,
       Model1___tcp_hdrlen(Model1_th),
       Model1_iph->Model1_saddr, Model1_th->Model1_source,
       Model1_iph->Model1_daddr, Model1_th->Model1_dest,
       Model1_inet_iif(Model1_skb));
  if (Model1_sk2) {
   Model1_inet_twsk_deschedule_put(Model1_inet_twsk(Model1_sk));
   Model1_sk = Model1_sk2;
   Model1_refcounted = false;
   goto Model1_process;
  }
  /* Fall through to ACK */
 }
 case Model1_TCP_TW_ACK:
  Model1_tcp_v4_timewait_ack(Model1_sk, Model1_skb);
  break;
 case Model1_TCP_TW_RST:
  Model1_tcp_v4_send_reset(Model1_sk, Model1_skb);
  Model1_inet_twsk_deschedule_put(Model1_inet_twsk(Model1_sk));
  goto Model1_discard_it;
 case Model1_TCP_TW_SUCCESS:;
 }
 goto Model1_discard_it;
}

/* START OF extern.c */

struct Model1_net Model1_init_net;
int Model1_sysctl_max_syn_backlog;
struct Model1_inet_timewait_death_row Model1_tcp_death_row = {
 .Model1_sysctl_max_tw_buckets = 8192 * 2,
#if CY_ABSTRACT1
#else
 //.Model1_hashinfo = &Model1_tcp_hashinfo,
#endif
};

// copied from tcp_output.c
struct Model1_tcp_out_options {
 Model1_u16 Model1_options; /* bit field of OPTION_* */
 Model1_u16 Model1_mss; /* 0 to disable */
 Model1_u8 Model1_ws; /* window scale, 0 to disable */
 Model1_u8 Model1_num_sack_blocks; /* number of SACK blocks to include */
 Model1_u8 Model1_hash_size; /* bytes in hash_location */
 __u8 *Model1_hash_location; /* temporary pointer, overloaded */
 __u32 Model1_tsval, Model1_tsecr; /* need to include OPTION_TS */
 struct Model1_tcp_fastopen_cookie *Model1_fastopen_cookie; /* Fast open cookie */
};

/****** extra function ******/
static void Model1_inet_child_forget(struct Model1_sock *Model1_sk, struct Model1_request_sock *Model1_req,
         struct Model1_sock *Model1_child)
{
    assert(0);
}
void Model1_security_sk_free(struct Model1_sock *Model1_sk){
}
#if CY_ABSTRACT3 //!CONFIG_MODULES
bool Model1_try_module_get(struct Model1_module *Model1_module){
    //TODO: currently to make it simply, assume CONFIG_MODULES is false, but it's not true
    return 1;
}
#endif
int Model1_security_sk_alloc(struct Model1_sock *Model1_sk, int Model1_family, Model1_gfp_t Model1_priority){
    return 0;
}
void Model1_net_enable_timestamp(void){
    assert(0);
}
bool Model1_sock_needs_netstamp(const struct Model1_sock *Model1_sk)
{
 switch (Model1_sk->Model1___sk_common.Model1_skc_family) {
 case 0:
 case 1:
  return false;
 default:
  return true;
 }
}

static inline int Model1_xfrm_sk_clone_policy(struct Model1_sock *Model1_sk, const struct Model1_sock *Model1_osk) { return 0; }
/* try to charge the socket memory if there is space available
 * return true on success
 */
bool Model1_sk_filter_charge(struct Model1_sock *Model1_sk, struct Model1_sk_filter *Model1_fp){
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
static inline __attribute__((no_instrument_function)) void Model1_sock_lock_init(struct Model1_sock *Model1_sk)
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
static void Model1_sock_copy(struct Model1_sock *Model1_nsk, const struct Model1_sock *Model1_osk)
{

 ({ Model1_size_t Model1___len = (__builtin_offsetof(struct Model1_sock, Model1___sk_common.Model1_skc_dontcopy_begin)); void *Model1___ret; if (__builtin_constant_p(__builtin_offsetof(struct Model1_sock, Model1___sk_common.Model1_skc_dontcopy_begin)) && Model1___len >= 64) Model1___ret = Model1___memcpy((Model1_nsk), (Model1_osk), Model1___len); else Model1___ret = __builtin_memcpy((Model1_nsk), (Model1_osk), Model1___len); Model1___ret; });

 ({ Model1_size_t Model1___len = (Model1_osk->Model1___sk_common.Model1_skc_prot->Model1_obj_size - __builtin_offsetof(struct Model1_sock, Model1___sk_common.Model1_skc_dontcopy_end)); void *Model1___ret; if (__builtin_constant_p(Model1_osk->Model1___sk_common.Model1_skc_prot->Model1_obj_size - __builtin_offsetof(struct Model1_sock, Model1___sk_common.Model1_skc_dontcopy_end)) && Model1___len >= 64) Model1___ret = Model1___memcpy((&Model1_nsk->Model1___sk_common.Model1_skc_dontcopy_end), (&Model1_osk->Model1___sk_common.Model1_skc_dontcopy_end), Model1___len); else Model1___ret = __builtin_memcpy((&Model1_nsk->Model1___sk_common.Model1_skc_dontcopy_end), (&Model1_osk->Model1___sk_common.Model1_skc_dontcopy_end), Model1___len); Model1___ret; });






}
static struct Model1_sock *Model1_sk_prot_alloc(struct Model1_proto *Model1_prot, Model1_gfp_t Model1_priority,
  int Model1_family);
static inline void Model1_security_inet_csk_clone(struct Model1_sock *Model1_newsk,
    const struct Model1_request_sock *Model1_req)
{
}
/**
* sk_stream_write_space - stream socket write_space callback.
* @sk: socket
*
* FIXME: write proper description
*/
void Model1_sk_stream_write_space(struct Model1_sock *Model1_sk){
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
struct Model1_sock *Model1_sk_clone_lock(const struct Model1_sock *Model1_sk, const Model1_gfp_t Model1_priority)
{
 struct Model1_sock *Model1_newsk;
 bool Model1_is_charged = true;

 Model1_newsk = Model1_sk_prot_alloc(Model1_sk->Model1___sk_common.Model1_skc_prot, Model1_priority, Model1_sk->Model1___sk_common.Model1_skc_family);
 if (Model1_newsk != ((void *)0)) {
  struct Model1_sk_filter *Model1_filter;

  Model1_sock_copy(Model1_newsk, Model1_sk);

  /* SANITY */
  if (__builtin_expect(!!(Model1_newsk->Model1___sk_common.Model1_skc_net_refcnt), 1))
   Model1_get_net(Model1_sock_net(Model1_newsk));
  Model1_sk_node_init(&Model1_newsk->Model1___sk_common.Model1_skc_node);
  Model1_sock_lock_init(Model1_newsk);
  Model1_spin_lock(&((Model1_newsk)->Model1_sk_lock.Model1_slock));
  Model1_newsk->Model1_sk_backlog.Model1_head = Model1_newsk->Model1_sk_backlog.Model1_tail = ((void *)0);
  Model1_newsk->Model1_sk_backlog.Model1_len = 0;

  Model1_atomic_set(&Model1_newsk->Model1_sk_backlog.Model1_rmem_alloc, 0);
  /*
		 * sk_wmem_alloc set to one (see sk_free() and sock_wfree())
		 */
  Model1_atomic_set(&Model1_newsk->Model1_sk_wmem_alloc, 1);
  Model1_atomic_set(&Model1_newsk->Model1_sk_omem_alloc, 0);
  Model1_skb_queue_head_init(&Model1_newsk->Model1_sk_receive_queue);
  Model1_skb_queue_head_init(&Model1_newsk->Model1_sk_write_queue);

#if !CY_ABSTRACT1
    //TODO: temporarily removed
  do { *(&Model1_newsk->Model1_sk_callback_lock) = (Model1_rwlock_t) { .Model1_raw_lock = { }, }; } while (0);
  do { (void)(Model1_af_callback_keys + Model1_newsk->Model1___sk_common.Model1_skc_family); (void)(Model1_af_family_clock_key_strings[Model1_newsk->Model1___sk_common.Model1_skc_family]); } while (0);
#endif


  Model1_newsk->Model1_sk_dst_cache = ((void *)0);
  Model1_newsk->Model1_sk_wmem_queued = 0;
  Model1_newsk->Model1_sk_forward_alloc = 0;
  Model1_atomic_set(&Model1_newsk->Model1_sk_drops, 0);
  Model1_newsk->Model1_sk_send_head = ((void *)0);
  Model1_newsk->Model1_sk_userlocks = Model1_sk->Model1_sk_userlocks & ~8;

  Model1_sock_reset_flag(Model1_newsk, Model1_SOCK_DONE);
  Model1_skb_queue_head_init(&Model1_newsk->Model1_sk_error_queue);

  Model1_filter = ({ do { } while (0); ; ((typeof(*(Model1_newsk->Model1_sk_filter)) *)((Model1_newsk->Model1_sk_filter))); });
  if (Model1_filter != ((void *)0))
   /* though it's an empty new sock, the charging may fail
			 * if sysctl_optmem_max was changed between creation of
			 * original socket and cloning
			 */
   Model1_is_charged = Model1_sk_filter_charge(Model1_newsk, Model1_filter);

  if (__builtin_expect(!!(!Model1_is_charged || Model1_xfrm_sk_clone_policy(Model1_newsk, Model1_sk)), 0)) {
   /* It is still raw copy of parent, so invalidate
			 * destructor and make plain sk_free() */
   Model1_newsk->Model1_sk_destruct = ((void *)0);
   Model1_spin_unlock(&((Model1_newsk)->Model1_sk_lock.Model1_slock));
   Model1_sk_free(Model1_newsk);
   Model1_newsk = ((void *)0);
   goto Model1_out;
  }
  do { ; ({ union { typeof(Model1_newsk->Model1_sk_reuseport_cb) Model1___val; char Model1___c[1]; } Model1___u = { .Model1___val = ( typeof(Model1_newsk->Model1_sk_reuseport_cb)) ((typeof(*(((void *)0))) *)(((void *)0))) }; Model1___write_once_size(&(Model1_newsk->Model1_sk_reuseport_cb), Model1___u.Model1___c, sizeof(Model1_newsk->Model1_sk_reuseport_cb)); Model1___u.Model1___val; }); } while (0);

  Model1_newsk->Model1_sk_err = 0;
  Model1_newsk->Model1_sk_priority = 0;
  Model1_newsk->Model1___sk_common.Model1_skc_incoming_cpu = 0;
  Model1_atomic64_set(&Model1_newsk->Model1___sk_common.Model1_skc_cookie, 0);

  Model1_cgroup_sk_alloc(&Model1_newsk->Model1_sk_cgrp_data);

  /*
		 * Before updating sk_refcnt, we must commit prior changes to memory
		 * (Documentation/RCU/rculist_nulls.txt for details)
		 */
  __asm__ __volatile__("": : :"memory");
  Model1_atomic_set(&Model1_newsk->Model1___sk_common.Model1_skc_refcnt, 2);

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
  Model1_sk_set_socket(Model1_newsk, ((void *)0));
  Model1_newsk->Model1_sk_wq = ((void *)0);

  if (0 && Model1_sk->Model1_sk_memcg)
   Model1_sock_update_memcg(Model1_newsk);

  if (Model1_newsk->Model1___sk_common.Model1_skc_prot->Model1_sockets_allocated)
   Model1_sk_sockets_allocated_inc(Model1_newsk);

  if (Model1_sock_needs_netstamp(Model1_sk) &&
      Model1_newsk->Model1___sk_common.Model1_skc_flags & ((1UL << Model1_SOCK_TIMESTAMP) | (1UL << Model1_SOCK_TIMESTAMPING_RX_SOFTWARE)))
   Model1_net_enable_timestamp();
 }
Model1_out:
 return Model1_newsk;
}
static void Model1_tcp_ecn_openreq_child(struct Model1_tcp_sock *Model1_tp,
      const struct Model1_request_sock *Model1_req)
{
 Model1_tp->Model1_ecn_flags = Model1_inet_rsk(Model1_req)->Model1_ecn_ok ? 1 : 0;
}
/**
 *	inet_csk_clone_lock - clone an inet socket, and lock its clone
 *	@sk: the socket to clone
 *	@req: request_sock
 *	@priority: for allocation (%GFP_KERNEL, %GFP_ATOMIC, etc)
 *
 *	Caller must unlock socket even in error path (bh_unlock_sock(newsk))
 */
struct Model1_sock *Model1_inet_csk_clone_lock(const struct Model1_sock *Model1_sk,
     const struct Model1_request_sock *Model1_req,
     const Model1_gfp_t Model1_priority)
{
 struct Model1_sock *Model1_newsk = Model1_sk_clone_lock(Model1_sk, Model1_priority);

 if (Model1_newsk) {
  struct Model1_inet_connection_sock *Model1_newicsk = Model1_inet_csk(Model1_newsk);

  Model1_newsk->Model1___sk_common.Model1_skc_state = Model1_TCP_SYN_RECV;
  Model1_newicsk->Model1_icsk_bind_hash = ((void *)0);

  Model1_inet_sk(Model1_newsk)->Model1_sk.Model1___sk_common.Model1_skc_dport = Model1_inet_rsk(Model1_req)->Model1_req.Model1___req_common.Model1_skc_dport;
  Model1_inet_sk(Model1_newsk)->Model1_sk.Model1___sk_common.Model1_skc_num = Model1_inet_rsk(Model1_req)->Model1_req.Model1___req_common.Model1_skc_num;
  Model1_inet_sk(Model1_newsk)->Model1_inet_sport = (( Model1___be16)(__builtin_constant_p((Model1___u16)((Model1_inet_rsk(Model1_req)->Model1_req.Model1___req_common.Model1_skc_num))) ? ((Model1___u16)( (((Model1___u16)((Model1_inet_rsk(Model1_req)->Model1_req.Model1___req_common.Model1_skc_num)) & (Model1___u16)0x00ffU) << 8) | (((Model1___u16)((Model1_inet_rsk(Model1_req)->Model1_req.Model1___req_common.Model1_skc_num)) & (Model1___u16)0xff00U) >> 8))) : Model1___fswab16((Model1_inet_rsk(Model1_req)->Model1_req.Model1___req_common.Model1_skc_num))));
  Model1_newsk->Model1_sk_write_space = Model1_sk_stream_write_space;

  /* listeners have SOCK_RCU_FREE, not the children */
  Model1_sock_reset_flag(Model1_newsk, Model1_SOCK_RCU_FREE);

  Model1_newsk->Model1_sk_mark = Model1_inet_rsk(Model1_req)->Model1_ir_mark;
  Model1_atomic64_set(&Model1_newsk->Model1___sk_common.Model1_skc_cookie,
        Model1_atomic64_read(&Model1_inet_rsk(Model1_req)->Model1_req.Model1___req_common.Model1_skc_cookie));

  Model1_newicsk->Model1_icsk_retransmits = 0;
  Model1_newicsk->Model1_icsk_backoff = 0;
  Model1_newicsk->Model1_icsk_probes_out = 0;

  /* Deinitialize accept_queue to trap illegal accesses. */
  memset(&Model1_newicsk->Model1_icsk_accept_queue, 0, sizeof(Model1_newicsk->Model1_icsk_accept_queue));

  Model1_security_inet_csk_clone(Model1_newsk, Model1_req);
 }
 return Model1_newsk;
}
void Model1_tcp_init_xmit_timers(struct Model1_sock *Model1_sk){
#if CY_ABSTRACT2
    //Since we fix the time in our model, timers won't be triggered
#else
    assert(0);
#endif
}
void Model1_inet_csk_prepare_forced_close(struct Model1_sock *Model1_sk){
    assert(0);
}
bool Model1_inet_ehash_nolisten(struct Model1_sock *Model1_sk, struct Model1_sock *Model1_osk){
#if CY_ABSTRACT3
    return true;
#else
    assert(0);
    return true;
#endif
}
int Model1___inet_inherit_port(const struct Model1_sock *Model1_sk, struct Model1_sock *Model1_child){
#if CY_ABSTRACT3
    //TODO: inherit port (hash value) from its father. But currently we abstracted hash system
    return 0;
#else
    assert(0);
    return 0;
#endif
}
void Model1_tcp_ca_openreq_child(struct Model1_sock *Model1_sk, const struct Model1_dst_entry *Model1_dst)
{
#if CY_ABSTRACT1
    assert(0);
#else
 struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
 Model1_u32 Model1_ca_key = Model1_dst_metric(Model1_dst, Model1_RTAX_CC_ALGO);
 bool Model1_ca_got_dst = false;

 if (Model1_ca_key != 0) {
  const struct Model1_tcp_congestion_ops *Model1_ca;

  Model1_rcu_read_lock();
  Model1_ca = Model1_tcp_ca_find_key(Model1_ca_key);
  if (__builtin_expect(!!(Model1_ca && Model1_try_module_get(Model1_ca->Model1_owner)), 1)) {
   Model1_icsk->Model1_icsk_ca_dst_locked = Model1_tcp_ca_dst_locked(Model1_dst);
   Model1_icsk->Model1_icsk_ca_ops = Model1_ca;
   Model1_ca_got_dst = true;
  }
  Model1_rcu_read_unlock();
 }

 /* If no valid choice made yet, assign current system default ca. */
 if (!Model1_ca_got_dst &&
     (!Model1_icsk->Model1_icsk_ca_setsockopt ||
      !Model1_try_module_get(Model1_icsk->Model1_icsk_ca_ops->Model1_owner)))
  Model1_tcp_assign_congestion_control(Model1_sk);

 Model1_tcp_set_ca_state(Model1_sk, Model1_TCP_CA_Open);
#endif
}

void Model1_sk_setup_caps(struct Model1_sock *Model1_sk, struct Model1_dst_entry *Model1_dst){
    assert(0);
}
/* This is not only more efficient than what we used to do, it eliminates
 * a lot of code duplication between IPv4/IPv6 SYN recv processing. -DaveM
 *
 * Actually, we could lots of memory writes here. tp of listening
 * socket contains all necessary default parameters.
 */
struct Model1_sock *Model1_tcp_create_openreq_child(const struct Model1_sock *Model1_sk,
          struct Model1_request_sock *Model1_req,
          struct Model1_sk_buff *Model1_skb)
{
 struct Model1_sock *Model1_newsk = Model1_inet_csk_clone_lock(Model1_sk, Model1_req, ((( Model1_gfp_t)0x20u)|(( Model1_gfp_t)0x80000u)|(( Model1_gfp_t)0x2000000u)));

 if (Model1_newsk) {
  const struct Model1_inet_request_sock *Model1_ireq = Model1_inet_rsk(Model1_req);
  struct Model1_tcp_request_sock *Model1_treq = Model1_tcp_rsk(Model1_req);
  struct Model1_inet_connection_sock *Model1_newicsk = Model1_inet_csk(Model1_newsk);
  struct Model1_tcp_sock *Model1_newtp = Model1_tcp_sk(Model1_newsk);

  /* Now setup tcp_sock */
  Model1_newtp->Model1_pred_flags = 0;

  Model1_newtp->Model1_rcv_wup = Model1_newtp->Model1_copied_seq =
  Model1_newtp->Model1_rcv_nxt = Model1_treq->Model1_rcv_isn + 1;
  Model1_newtp->Model1_segs_in = 1;

  Model1_newtp->Model1_snd_sml = Model1_newtp->Model1_snd_una =
  Model1_newtp->Model1_snd_nxt = Model1_newtp->Model1_snd_up = Model1_treq->Model1_snt_isn + 1;

  Model1_tcp_prequeue_init(Model1_newtp);
  Model1_INIT_LIST_HEAD(&Model1_newtp->Model1_tsq_node);

  Model1_tcp_init_wl(Model1_newtp, Model1_treq->Model1_rcv_isn);

  Model1_newtp->Model1_srtt_us = 0;
  Model1_newtp->Model1_mdev_us = Model1_jiffies_to_usecs(((unsigned)(1*1000)));
  Model1_newtp->Model1_rtt_min[0].Model1_rtt = ~0U;
  Model1_newicsk->Model1_icsk_rto = ((unsigned)(1*1000));

  Model1_newtp->Model1_packets_out = 0;
  Model1_newtp->Model1_retrans_out = 0;
  Model1_newtp->Model1_sacked_out = 0;
  Model1_newtp->Model1_fackets_out = 0;
  Model1_newtp->Model1_snd_ssthresh = 0x7fffffff;
  Model1_tcp_enable_early_retrans(Model1_newtp);
  Model1_newtp->Model1_tlp_high_seq = 0;
  Model1_newtp->Model1_lsndtime = Model1_treq->Model1_snt_synack.Model1_stamp_jiffies;
  Model1_newsk->Model1_sk_txhash = Model1_treq->Model1_txhash;
  Model1_newtp->Model1_last_oow_ack_time = 0;
  Model1_newtp->Model1_total_retrans = Model1_req->Model1_num_retrans;

  /* So many TCP implementations out there (incorrectly) count the
		 * initial SYN frame in their delayed-ACK and congestion control
		 * algorithms that we must have the following bandaid to talk
		 * efficiently to them.  -DaveM
		 */
  Model1_newtp->Model1_snd_cwnd = 10;
  Model1_newtp->Model1_snd_cwnd_cnt = 0;

  Model1_tcp_init_xmit_timers(Model1_newsk);
  Model1___skb_queue_head_init(&Model1_newtp->Model1_out_of_order_queue);
  Model1_newtp->Model1_write_seq = Model1_newtp->Model1_pushed_seq = Model1_treq->Model1_snt_isn + 1;

  Model1_newtp->Model1_rx_opt.Model1_saw_tstamp = 0;

  Model1_newtp->Model1_rx_opt.Model1_dsack = 0;
  Model1_newtp->Model1_rx_opt.Model1_num_sacks = 0;

  Model1_newtp->Model1_urg_data = 0;

  if (Model1_sock_flag(Model1_newsk, Model1_SOCK_KEEPOPEN))
   Model1_inet_csk_reset_keepalive_timer(Model1_newsk,
             Model1_keepalive_time_when(Model1_newtp));

  Model1_newtp->Model1_rx_opt.Model1_tstamp_ok = Model1_ireq->Model1_tstamp_ok;
  if ((Model1_newtp->Model1_rx_opt.Model1_sack_ok = Model1_ireq->Model1_sack_ok) != 0) {
   if (Model1_sysctl_tcp_fack)
    Model1_tcp_enable_fack(Model1_newtp);
  }
  Model1_newtp->Model1_window_clamp = Model1_req->Model1___req_common.Model1_skc_window_clamp;
  Model1_newtp->Model1_rcv_ssthresh = Model1_req->Model1___req_common.Model1_skc_rcv_wnd;
  Model1_newtp->Model1_rcv_wnd = Model1_req->Model1___req_common.Model1_skc_rcv_wnd;
  Model1_newtp->Model1_rx_opt.Model1_wscale_ok = Model1_ireq->Model1_wscale_ok;
  if (Model1_newtp->Model1_rx_opt.Model1_wscale_ok) {
   Model1_newtp->Model1_rx_opt.Model1_snd_wscale = Model1_ireq->Model1_snd_wscale;
   Model1_newtp->Model1_rx_opt.Model1_rcv_wscale = Model1_ireq->Model1_rcv_wscale;
  } else {
   Model1_newtp->Model1_rx_opt.Model1_snd_wscale = Model1_newtp->Model1_rx_opt.Model1_rcv_wscale = 0;
   Model1_newtp->Model1_window_clamp = ({ typeof(Model1_newtp->Model1_window_clamp) Model1__min1 = (Model1_newtp->Model1_window_clamp); typeof(65535U) Model1__min2 = (65535U); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
  }
  Model1_newtp->Model1_snd_wnd = ((__builtin_constant_p((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_window))) ? ((Model1___u16)( (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_window)) & (Model1___u16)0x00ffU) << 8) | (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_window)) & (Model1___u16)0xff00U) >> 8))) : Model1___fswab16(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_window))) <<
      Model1_newtp->Model1_rx_opt.Model1_snd_wscale);
  Model1_newtp->Model1_max_window = Model1_newtp->Model1_snd_wnd;

  if (Model1_newtp->Model1_rx_opt.Model1_tstamp_ok) {
   Model1_newtp->Model1_rx_opt.Model1_ts_recent = Model1_req->Model1_ts_recent;
   Model1_newtp->Model1_rx_opt.Model1_ts_recent_stamp = Model1_get_seconds();
   Model1_newtp->Model1_tcp_header_len = sizeof(struct Model1_tcphdr) + 12;
  } else {
   Model1_newtp->Model1_rx_opt.Model1_ts_recent_stamp = 0;
   Model1_newtp->Model1_tcp_header_len = sizeof(struct Model1_tcphdr);
  }
  Model1_newtp->Model1_tsoffset = 0;





  if (Model1_skb->Model1_len >= 536U + Model1_newtp->Model1_tcp_header_len)
   Model1_newicsk->Model1_icsk_ack.Model1_last_seg_size = Model1_skb->Model1_len - Model1_newtp->Model1_tcp_header_len;
  Model1_newtp->Model1_rx_opt.Model1_mss_clamp = Model1_req->Model1_mss;
  Model1_tcp_ecn_openreq_child(Model1_newtp, Model1_req);
  Model1_newtp->Model1_fastopen_rsk = ((void *)0);
  Model1_newtp->Model1_syn_data_acked = 0;
  Model1_newtp->Model1_rack.Model1_mstamp.Model1_v64 = 0;
  Model1_newtp->Model1_rack.Model1_advanced = 0;

  (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_PASSIVEOPENS] += 1);
 }
 return Model1_newsk;
}

struct Model1_dst_entry *Model1_inet_csk_route_child_sock(const struct Model1_sock *Model1_sk,
         struct Model1_sock *Model1_newsk,
         const struct Model1_request_sock *Model1_req)
{
#if CY_ABSTRACT1
    assert(0);
    return NULL;
#else
 const struct Model1_inet_request_sock *Model1_ireq = Model1_inet_rsk(Model1_req);
 struct Model1_net *Model1_net = Model1_read_pnet(&Model1_ireq->Model1_req.Model1___req_common.Model1_skc_net);
 struct Model1_inet_sock *Model1_newinet = Model1_inet_sk(Model1_newsk);
 struct Model1_ip_options_rcu *Model1_opt;
 struct Model1_flowi4 *Model1_fl4;
 struct Model1_rtable *Model1_rt;

 Model1_fl4 = &Model1_newinet->Model1_cork.Model1_fl.Model1_u.Model1_ip4;

 Model1_rcu_read_lock();
 Model1_opt = ({ typeof(*(Model1_newinet->Model1_inet_opt)) *Model1_________p1 = (typeof(*(Model1_newinet->Model1_inet_opt)) *)({ typeof((Model1_newinet->Model1_inet_opt)) Model1__________p1 = ({ union { typeof((Model1_newinet->Model1_inet_opt)) Model1___val; char Model1___c[1]; } Model1___u; if (1) Model1___read_once_size(&((Model1_newinet->Model1_inet_opt)), Model1___u.Model1___c, sizeof((Model1_newinet->Model1_inet_opt))); else Model1___read_once_size_nocheck(&((Model1_newinet->Model1_inet_opt)), Model1___u.Model1___c, sizeof((Model1_newinet->Model1_inet_opt))); Model1___u.Model1___val; }); typeof(*((Model1_newinet->Model1_inet_opt))) *Model1____typecheck_p __attribute__((unused)); do { } while (0); (Model1__________p1); }); do { } while (0); ; ((typeof(*(Model1_newinet->Model1_inet_opt)) *)(Model1_________p1)); });
 Model1_flowi4_init_output(Model1_fl4, Model1_ireq->Model1_req.Model1___req_common.Model1_skc_bound_dev_if, Model1_ireq->Model1_ir_mark,
      (((Model1_inet_sk(Model1_sk)->Model1_tos)&0x1E) | Model1_sock_flag(Model1_sk, Model1_SOCK_LOCALROUTE)), Model1_RT_SCOPE_UNIVERSE,
      Model1_sk->Model1_sk_protocol, Model1_inet_sk_flowi_flags(Model1_sk),
      (Model1_opt && Model1_opt->Model1_opt.Model1_srr) ? Model1_opt->Model1_opt.Model1_faddr : Model1_ireq->Model1_req.Model1___req_common.Model1_skc_daddr,
      Model1_ireq->Model1_req.Model1___req_common.Model1_skc_rcv_saddr, Model1_ireq->Model1_req.Model1___req_common.Model1_skc_dport,
      (( Model1___be16)(__builtin_constant_p((Model1___u16)((Model1_ireq->Model1_req.Model1___req_common.Model1_skc_num))) ? ((Model1___u16)( (((Model1___u16)((Model1_ireq->Model1_req.Model1___req_common.Model1_skc_num)) & (Model1___u16)0x00ffU) << 8) | (((Model1___u16)((Model1_ireq->Model1_req.Model1___req_common.Model1_skc_num)) & (Model1___u16)0xff00U) >> 8))) : Model1___fswab16((Model1_ireq->Model1_req.Model1___req_common.Model1_skc_num)))));
 Model1_security_req_classify_flow(Model1_req, Model1_flowi4_to_flowi(Model1_fl4));
 Model1_rt = Model1_ip_route_output_flow(Model1_net, Model1_fl4, Model1_sk);
 if (Model1_IS_ERR(Model1_rt))
  goto Model1_no_route;
 if (Model1_opt && Model1_opt->Model1_opt.Model1_is_strictroute && Model1_rt->Model1_rt_uses_gateway)
  goto Model1_route_err;
 Model1_rcu_read_unlock();
 return &Model1_rt->Model1_dst;

Model1_route_err:
 Model1_ip_rt_put(Model1_rt);
Model1_no_route:
 Model1_rcu_read_unlock();
 ({ Model1___this_cpu_preempt_check("add"); do { do { const void *Model1___vpp_verify = (typeof((&((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) + 0))((void *)0); (void)Model1___vpp_verify; } while (0); switch(sizeof((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) { case 1: do { typedef typeof(((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) Model1_pao_T__; const int Model1_pao_ID__ = (__builtin_constant_p(1) && ((1) == 1 || (1) == -1)) ? (int)(1) : 0; if (0) { Model1_pao_T__ Model1_pao_tmp__; Model1_pao_tmp__ = (1); (void)Model1_pao_tmp__; } switch (sizeof(((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))) { case 1: if (Model1_pao_ID__ == 1) asm("incb """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else if (Model1_pao_ID__ == -1) asm("decb """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else asm("addb %1, """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) : "qi" ((Model1_pao_T__)(1))); break; case 2: if (Model1_pao_ID__ == 1) asm("incw """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else if (Model1_pao_ID__ == -1) asm("decw """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else asm("addw %1, """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) : "ri" ((Model1_pao_T__)(1))); break; case 4: if (Model1_pao_ID__ == 1) asm("incl """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else if (Model1_pao_ID__ == -1) asm("decl """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else asm("addl %1, """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) : "ri" ((Model1_pao_T__)(1))); break; case 8: if (Model1_pao_ID__ == 1) asm("incq """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else if (Model1_pao_ID__ == -1) asm("decq """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else asm("addq %1, """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) : "re" ((Model1_pao_T__)(1))); break; default: Model1___bad_percpu_size(); } } while (0);break; case 2: do { typedef typeof(((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) Model1_pao_T__; const int Model1_pao_ID__ = (__builtin_constant_p(1) && ((1) == 1 || (1) == -1)) ? (int)(1) : 0; if (0) { Model1_pao_T__ Model1_pao_tmp__; Model1_pao_tmp__ = (1); (void)Model1_pao_tmp__; } switch (sizeof(((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))) { case 1: if (Model1_pao_ID__ == 1) asm("incb """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else if (Model1_pao_ID__ == -1) asm("decb """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else asm("addb %1, """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) : "qi" ((Model1_pao_T__)(1))); break; case 2: if (Model1_pao_ID__ == 1) asm("incw """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else if (Model1_pao_ID__ == -1) asm("decw """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else asm("addw %1, """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) : "ri" ((Model1_pao_T__)(1))); break; case 4: if (Model1_pao_ID__ == 1) asm("incl """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else if (Model1_pao_ID__ == -1) asm("decl """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else asm("addl %1, """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) : "ri" ((Model1_pao_T__)(1))); break; case 8: if (Model1_pao_ID__ == 1) asm("incq """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else if (Model1_pao_ID__ == -1) asm("decq """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else asm("addq %1, """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) : "re" ((Model1_pao_T__)(1))); break; default: Model1___bad_percpu_size(); } } while (0);break; case 4: do { typedef typeof(((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) Model1_pao_T__; const int Model1_pao_ID__ = (__builtin_constant_p(1) && ((1) == 1 || (1) == -1)) ? (int)(1) : 0; if (0) { Model1_pao_T__ Model1_pao_tmp__; Model1_pao_tmp__ = (1); (void)Model1_pao_tmp__; } switch (sizeof(((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))) { case 1: if (Model1_pao_ID__ == 1) asm("incb """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else if (Model1_pao_ID__ == -1) asm("decb """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else asm("addb %1, """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) : "qi" ((Model1_pao_T__)(1))); break; case 2: if (Model1_pao_ID__ == 1) asm("incw """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else if (Model1_pao_ID__ == -1) asm("decw """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else asm("addw %1, """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) : "ri" ((Model1_pao_T__)(1))); break; case 4: if (Model1_pao_ID__ == 1) asm("incl """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else if (Model1_pao_ID__ == -1) asm("decl """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else asm("addl %1, """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) : "ri" ((Model1_pao_T__)(1))); break; case 8: if (Model1_pao_ID__ == 1) asm("incq """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else if (Model1_pao_ID__ == -1) asm("decq """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else asm("addq %1, """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) : "re" ((Model1_pao_T__)(1))); break; default: Model1___bad_percpu_size(); } } while (0);break; case 8: do { typedef typeof(((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) Model1_pao_T__; const int Model1_pao_ID__ = (__builtin_constant_p(1) && ((1) == 1 || (1) == -1)) ? (int)(1) : 0; if (0) { Model1_pao_T__ Model1_pao_tmp__; Model1_pao_tmp__ = (1); (void)Model1_pao_tmp__; } switch (sizeof(((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))) { case 1: if (Model1_pao_ID__ == 1) asm("incb """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else if (Model1_pao_ID__ == -1) asm("decb """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else asm("addb %1, """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) : "qi" ((Model1_pao_T__)(1))); break; case 2: if (Model1_pao_ID__ == 1) asm("incw """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else if (Model1_pao_ID__ == -1) asm("decw """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else asm("addw %1, """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) : "ri" ((Model1_pao_T__)(1))); break; case 4: if (Model1_pao_ID__ == 1) asm("incl """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else if (Model1_pao_ID__ == -1) asm("decl """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else asm("addl %1, """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) : "ri" ((Model1_pao_T__)(1))); break; case 8: if (Model1_pao_ID__ == 1) asm("incq """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else if (Model1_pao_ID__ == -1) asm("decq """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES]))); else asm("addq %1, """ "%" "0" : "+m" (((Model1_net)->Model1_mib.Model1_ip_statistics->Model1_mibs[Model1_IPSTATS_MIB_OUTNOROUTES])) : "re" ((Model1_pao_T__)(1))); break; default: Model1___bad_percpu_size(); } } while (0);break; default: Model1___bad_size_call_parameter();break; } } while (0); });
 return ((void *)0);
#endif
}

void Model1_inet_csk_reqsk_queue_drop(struct Model1_sock *Model1_sk, struct Model1_request_sock *Model1_req)
{
#if CY_ABSTRACT1
    //TODO: currently we ignore process to deal with hashqueue, and remove value so far
#else
 if (Model1_reqsk_queue_unlink(&Model1_inet_csk(Model1_sk)->Model1_icsk_accept_queue, Model1_req)) {
  Model1_reqsk_queue_removed(&Model1_inet_csk(Model1_sk)->Model1_icsk_accept_queue, Model1_req);
  Model1_reqsk_put(Model1_req);
 }
#endif
}
/*
 * Write buffer destructor automatically called from kfree_skb.
 */
void Model1_sock_wfree(struct Model1_sk_buff *Model1_skb)
{
#if CY_ABSTRACT3
    assert(0); //this skb allocate and free too frequently. We may ignore this logic
#else
 struct Model1_sock *Model1_sk = Model1_skb->Model1_sk;
 unsigned int Model1_len = Model1_skb->Model1_truesize;

 if (!Model1_sock_flag(Model1_sk, Model1_SOCK_USE_WRITE_QUEUE)) {
  /*
		 * Keep a reference on sk_wmem_alloc, this will be released
		 * after sk_write_space() call
		 */
  Model1_atomic_sub(Model1_len - 1, &Model1_sk->Model1_sk_wmem_alloc);
  Model1_sk->Model1_sk_write_space(Model1_sk);
  Model1_len = 1;
 }
 /*
	 * if sk_wmem_alloc reaches 0, we must finish what sk_free()
	 * could not do because of in-flight packets
	 */
 if (Model1_atomic_sub_and_test(Model1_len, &Model1_sk->Model1_sk_wmem_alloc))
  Model1___sk_free(Model1_sk);
#endif
}
void Model1_skb_set_owner_w(struct Model1_sk_buff *Model1_skb, struct Model1_sock *Model1_sk)
{
 Model1_skb_orphan(Model1_skb);
 Model1_skb->Model1_sk = Model1_sk;







 Model1_skb->Model1_destructor = Model1_sock_wfree;
 Model1_skb_set_hash_from_sk(Model1_skb, Model1_sk);
 /*
	 * We used to take a refcount on sk, but following operation
	 * is enough to guarantee sk_free() wont free this sock until
	 * all in-flight packets are completed
	 */
#if !CY_ABSTRACT3
 Model1_atomic_add(Model1_skb->Model1_truesize, &Model1_sk->Model1_sk_wmem_alloc);
#endif
}

/* Determine a window scaling and initial window to offer.
 * Based on the assumption that the given amount of space
 * will be offered. Store the results in the tp structure.
 * NOTE: for smooth operation initial space offering should
 * be a multiple of mss if possible. We assume here that mss >= 1.
 * This MUST be enforced by all callers.
 */
void Model1_tcp_select_initial_window(int Model1___space, __u32 Model1_mss,
          __u32 *Model1_rcv_wnd, __u32 *Model1_window_clamp,
          int Model1_wscale_ok, __u8 *Model1_rcv_wscale,
          __u32 Model1_init_rcv_wnd)
{
#if CY_ABSTRACT3
    assert(0);
#else
 unsigned int Model1_space = (Model1___space < 0 ? 0 : Model1___space);

 /* If no clamp set the clamp to the max possible scaled window */
 if (*Model1_window_clamp == 0)
  (*Model1_window_clamp) = (65535 << 14);
 Model1_space = ({ typeof(*Model1_window_clamp) Model1__min1 = (*Model1_window_clamp); typeof(Model1_space) Model1__min2 = (Model1_space); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });

 /* Quantize space offering to a multiple of mss if possible. */
 if (Model1_space > Model1_mss)
  Model1_space = (Model1_space / Model1_mss) * Model1_mss;

 /* NOTE: offering an initial window larger than 32767
	 * will break some buggy TCP stacks. If the admin tells us
	 * it is likely we could be speaking with such a buggy stack
	 * we will truncate our initial window offering to 32K-1
	 * unless the remote has sent us a window scaling option,
	 * which we interpret as a sign the remote TCP is not
	 * misinterpreting the window field as a signed quantity.
	 */
 if (Model1_sysctl_tcp_workaround_signed_windows)
  (*Model1_rcv_wnd) = ({ typeof(Model1_space) Model1__min1 = (Model1_space); typeof(32767U) Model1__min2 = (32767U); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
 else
  (*Model1_rcv_wnd) = Model1_space;

 (*Model1_rcv_wscale) = 0;
 if (Model1_wscale_ok) {
  /* Set window scaling on max possible window
		 * See RFC1323 for an explanation of the limit to 14
		 */
  Model1_space = ({ Model1_u32 Model1___max1 = (Model1_space); Model1_u32 Model1___max2 = (Model1_sysctl_tcp_rmem[2]); Model1___max1 > Model1___max2 ? Model1___max1: Model1___max2; });
  Model1_space = ({ Model1_u32 Model1___max1 = (Model1_space); Model1_u32 Model1___max2 = (Model1_sysctl_rmem_max); Model1___max1 > Model1___max2 ? Model1___max1: Model1___max2; });
  Model1_space = ({ Model1_u32 Model1___min1 = (Model1_space); Model1_u32 Model1___min2 = (*Model1_window_clamp); Model1___min1 < Model1___min2 ? Model1___min1: Model1___min2; });
  while (Model1_space > 65535 && (*Model1_rcv_wscale) < 14) {
   Model1_space >>= 1;
   (*Model1_rcv_wscale)++;
  }
 }

 if (Model1_mss > (1 << *Model1_rcv_wscale)) {
  if (!Model1_init_rcv_wnd) /* Use default unless specified otherwise */
   Model1_init_rcv_wnd = Model1_tcp_default_init_rwnd(Model1_mss);
  *Model1_rcv_wnd = ({ typeof(*Model1_rcv_wnd) Model1__min1 = (*Model1_rcv_wnd); typeof(Model1_init_rcv_wnd * Model1_mss) Model1__min2 = (Model1_init_rcv_wnd * Model1_mss); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
 }

 /* Set the clamp no higher than max representable value */
 (*Model1_window_clamp) = ({ typeof(65535U << (*Model1_rcv_wscale)) Model1__min1 = (65535U << (*Model1_rcv_wscale)); typeof(*Model1_window_clamp) Model1__min2 = (*Model1_window_clamp); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
#endif
}
static bool Model1_tcp_fastopen_cookie_gen(struct Model1_request_sock *Model1_req,
        struct Model1_sk_buff *Model1_syn,
        struct Model1_tcp_fastopen_cookie *Model1_foc)
{
    assert(0);
    return true;
}

/* Set up TCP options for SYN-ACKs. */
//copied from tcp_output.c
static unsigned int Model1_tcp_synack_options(struct Model1_request_sock *Model1_req,
           unsigned int Model1_mss, struct Model1_sk_buff *Model1_skb,
           struct Model1_tcp_out_options *Model1_opts,
           const struct Model1_tcp_md5sig_key *Model1_md5,
           struct Model1_tcp_fastopen_cookie *Model1_foc)
{
 struct Model1_inet_request_sock *Model1_ireq = Model1_inet_rsk(Model1_req);
 unsigned int Model1_remaining = 40;
 /* We always send an MSS option. */
 Model1_opts->Model1_mss = Model1_mss;
 Model1_remaining -= 4;

 if (__builtin_expect(!!(Model1_ireq->Model1_wscale_ok), 1)) {
  Model1_opts->Model1_ws = Model1_ireq->Model1_rcv_wscale;
  Model1_opts->Model1_options |= (1 << 3);
  Model1_remaining -= 4;
 }
 if (__builtin_expect(!!(Model1_ireq->Model1_tstamp_ok), 1)) {
  Model1_opts->Model1_options |= (1 << 1);
  Model1_opts->Model1_tsval = Model1_tcp_skb_timestamp(Model1_skb);
  Model1_opts->Model1_tsecr = Model1_req->Model1_ts_recent;
  Model1_remaining -= 12;
 }
 if (__builtin_expect(!!(Model1_ireq->Model1_sack_ok), 1)) {
  Model1_opts->Model1_options |= (1 << 0);
  if (__builtin_expect(!!(!Model1_ireq->Model1_tstamp_ok), 0))
   Model1_remaining -= 4;
 }
 if (Model1_foc != ((void *)0) && Model1_foc->Model1_len >= 0) {
  Model1_u32 Model1_need = Model1_foc->Model1_len;

  Model1_need += Model1_foc->Model1_exp ? 4 :
       2;
  Model1_need = (Model1_need + 3) & ~3U; /* Align to 32 bits */
  if (Model1_remaining >= Model1_need) {
   Model1_opts->Model1_options |= (1 << 8);
   Model1_opts->Model1_fastopen_cookie = Model1_foc;
   Model1_remaining -= Model1_need;
  }
 }

 return 40 - Model1_remaining;
}

static void
Model1_tcp_ecn_make_synack(const struct Model1_request_sock *Model1_req, struct Model1_tcphdr *Model1_th)
{
 if (Model1_inet_rsk(Model1_req)->Model1_ecn_ok)
  Model1_th->Model1_ece = 1;
}

static void Model1_tcp_options_write(Model1___be32 *Model1_ptr, struct Model1_tcp_sock *Model1_tp,
         struct Model1_tcp_out_options *Model1_opts){
    // we don't have options for the header
#if CY_ABSTRACT1
    return;
#else
    assert(0);
#endif
}

static bool Model1_tcp_fastopen_queue_check(struct Model1_sock *Model1_sk)
{
 struct Model1_fastopen_queue *Model1_fastopenq;

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
 Model1_fastopenq = &Model1_inet_csk(Model1_sk)->Model1_icsk_accept_queue.Model1_fastopenq;
 if (Model1_fastopenq->Model1_max_qlen == 0)
  return false;

 if (Model1_fastopenq->Model1_qlen >= Model1_fastopenq->Model1_max_qlen) {
  struct Model1_request_sock *Model1_req1;
  Model1_spin_lock(&Model1_fastopenq->Model1_lock);
  Model1_req1 = Model1_fastopenq->Model1_rskq_rst_head;
  if (!Model1_req1 || (({ unsigned long Model1___dummy; typeof(Model1_req1->Model1_rsk_timer.Model1_expires) Model1___dummy2; (void)(&Model1___dummy == &Model1___dummy2); 1; }) && ({ unsigned long Model1___dummy; typeof(Model1_jiffies) Model1___dummy2; (void)(&Model1___dummy == &Model1___dummy2); 1; }) && ((long)((Model1_jiffies) - (Model1_req1->Model1_rsk_timer.Model1_expires)) < 0))) {
   (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPFASTOPENLISTENOVERFLOW] += 1);

   Model1_spin_unlock(&Model1_fastopenq->Model1_lock);
   return false;
  }
  Model1_fastopenq->Model1_rskq_rst_head = Model1_req1->Model1_dl_next;
  Model1_fastopenq->Model1_qlen--;
  Model1_spin_unlock(&Model1_fastopenq->Model1_lock);
  Model1_reqsk_put(Model1_req1);
 }
 return true;
}

static bool Model1___tcp_fastopen_cookie_gen(const void *Model1_path,
          struct Model1_tcp_fastopen_cookie *Model1_foc)
{
    assert(0);
    return true;
    /*
 struct Model1_tcp_fastopen_context *Model1_ctx;
 bool Model1_ok = false;

 Model1_rcu_read_lock();
 Model1_ctx = ({ typeof(*(Model1_tcp_fastopen_ctx)) *Model1_________p1 = (typeof(*(Model1_tcp_fastopen_ctx)) *)({ typeof((Model1_tcp_fastopen_ctx)) Model1__________p1 = ({ union { typeof((Model1_tcp_fastopen_ctx)) Model1___val; char Model1___c[1]; } Model1___u; if (1) Model1___read_once_size(&((Model1_tcp_fastopen_ctx)), Model1___u.Model1___c, sizeof((Model1_tcp_fastopen_ctx))); else Model1___read_once_size_nocheck(&((Model1_tcp_fastopen_ctx)), Model1___u.Model1___c, sizeof((Model1_tcp_fastopen_ctx))); Model1___u.Model1___val; }); typeof(*((Model1_tcp_fastopen_ctx))) *Model1____typecheck_p __attribute__((unused)); do { } while (0); (Model1__________p1); }); do { } while (0); ; ((typeof(*(Model1_tcp_fastopen_ctx)) *)(Model1_________p1)); });
 if (Model1_ctx) {
  Model1_crypto_cipher_encrypt_one(Model1_ctx->Model1_tfm, Model1_foc->Model1_val, Model1_path);
  Model1_foc->Model1_len = 8;
  Model1_ok = true;
 }
 Model1_rcu_read_unlock();
 return Model1_ok;
 */
}

int Model1_memcmp(const void *s1, const void *s2, size_t n){
    return memcmp(s1, s2, n);
}

static struct Model1_sock *Model1_tcp_fastopen_create_child(struct Model1_sock *Model1_sk,
           struct Model1_sk_buff *Model1_skb,
           struct Model1_dst_entry *Model1_dst,
           struct Model1_request_sock *Model1_req)
{
    assert(0);
    return NULL;
}

Model1_u32 Model1_tcp_reno_ssthresh(struct Model1_sock *Model1_sk){
    assert(0);
    return 0;
}

static void Model1_sock_def_wakeup(struct Model1_sock *Model1_sk){
#if CY_ABSTRACT3
    //Default Socket Callbacks
    //TODO: currently we assume no callback or no concurrency
#endif
}

static void Model1_sock_def_readable(struct Model1_sock *Model1_sk){
#if CY_ABSTRACT1
    //We assume one-way interleaving, so we ignore such concurrency
#else
    assert(0);
#endif
}
void Model1_inet_sk_rx_dst_set(struct Model1_sock *Model1_sk, const struct Model1_sk_buff *Model1_skb){
#if CY_ABSTRACT3
    //TODO: assume dst in IP layer
#else
    assert(0);
#endif
}

int Model1_inet_sk_rebuild_header(struct Model1_sock *Model1_sk){
#if CY_ABSTRACT3
    //we ignore route in IP layer
    return 0; //always correct
#endif
}
/****** functions ******/
Model1_u32 Model1_tcp_default_init_rwnd(Model1_u32 Model1_mss)
{
 /* Initial receive window should be twice of TCP_INIT_CWND to
	 * enable proper sending of new unsent data during fast recovery
	 * (RFC 3517, Section 4, NextSeg() rule (2)). Further place a
	 * limit when mss is larger than 1460.
	 */
 Model1_u32 Model1_init_rwnd = 10 * 2;

 if (Model1_mss > 1460)
  Model1_init_rwnd = ({ typeof((1460 * Model1_init_rwnd) / Model1_mss) Model1__max1 = ((1460 * Model1_init_rwnd) / Model1_mss); typeof(2U) Model1__max2 = (2U); (void) (&Model1__max1 == &Model1__max2); Model1__max1 > Model1__max2 ? Model1__max1 : Model1__max2; });
 return Model1_init_rwnd;
}

unsigned int Model1_tcp_current_mss(struct Model1_sock *Model1_sk){
#if CY_ABSTRACT3
    return 65535;
#endif
}

void Model1_tcp_xmit_retransmit_queue(struct Model1_sock *cy){
    assert(0);
}

unsigned int Model1_jiffies_to_usecs(const unsigned long Model1_j){
#if CY_ABSTRACT3
    return (1000000L / 1000) * Model1_j;
#endif
}

unsigned long Model1___usecs_to_jiffies(const unsigned int Model1_u){
#if CY_ABSTRACT2
    // always false
    /*
    if (u > jiffies_to_usecs(MAX_JIFFY_OFFSET))
        return MAX_JIFFY_OFFSET;
    */
    return Model1__usecs_to_jiffies(Model1_u);
#else
    assert(0);
    return 0;
#endif
}

unsigned long Model1___msecs_to_jiffies(const unsigned int Model1_m){
#if CY_ABSTRACT3
   if ((int)Model1_m < 0)
       return ((((long)(~0UL>>1)) >> 1)-1);
   return Model1__msecs_to_jiffies(Model1_m);
#endif
}

Model1_u64 Model1_sched_clock_cpu(int Model1_cpu){ 
#if CY_ABSTRACT2
    return 0;
#else
	if (unlikely(!sched_clock_running))
		return 0;

	return sched_clock();
#endif
}

void Model1_sk_reset_timer(struct Model1_sock *Model1_sk, struct Model1_timer_list *Model1_timer,
unsigned long Model1_expires){
    assert(0);
}

int Model1_tcp_fragment(struct Model1_sock *cy0, struct Model1_sk_buff *cy, Model1_u32 cy1, unsigned int cy2,   Model1_gfp_t cy3) {
    assert(0);
}

int Model1_net_ratelimit(void){
    assert(0);
}

void Model1_tcp_done(struct Model1_sock *Model1_sk){
    assert(0);
}

void Model1_inet_put_port(struct Model1_sock *Model1_sk){
    assert(0);
}
void Model1_tcp_set_state(struct Model1_sock *Model1_sk, int Model1_state)
{
 int Model1_oldstate = Model1_sk->Model1___sk_common.Model1_skc_state;

 switch (Model1_state) {
 case Model1_TCP_ESTABLISHED:
  if (Model1_oldstate != Model1_TCP_ESTABLISHED)
   (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_CURRESTAB] += 1);
  break;

 case Model1_TCP_CLOSE:
  if (Model1_oldstate == Model1_TCP_CLOSE_WAIT || Model1_oldstate == Model1_TCP_ESTABLISHED)
   (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_ESTABRESETS] += 1);

  Model1_sk->Model1___sk_common.Model1_skc_prot->Model1_unhash(Model1_sk);
  if (Model1_inet_csk(Model1_sk)->Model1_icsk_bind_hash &&
      !(Model1_sk->Model1_sk_userlocks & 8))
   Model1_inet_put_port(Model1_sk);
  /* fall through */
 default:
  if (Model1_oldstate == Model1_TCP_ESTABLISHED)
   (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_CURRESTAB] -= 1);
 }

 /* Change state AFTER socket is unhashed to avoid closed
	 * socket sitting in hash tables.
	 */
 Model1_sk_state_store(Model1_sk, Model1_state);




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
struct Model1_sk_buff *Model1_tcp_make_synack(const struct Model1_sock *Model1_sk, struct Model1_dst_entry *Model1_dst,
    struct Model1_request_sock *Model1_req,
    struct Model1_tcp_fastopen_cookie *Model1_foc,
    enum Model1_tcp_synack_type Model1_synack_type)
{
 struct Model1_inet_request_sock *Model1_ireq = Model1_inet_rsk(Model1_req);
 const struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_tcp_md5sig_key *Model1_md5 = ((void *)0);
 struct Model1_tcp_out_options Model1_opts;
 struct Model1_sk_buff *Model1_skb;
 int Model1_tcp_header_size;
 struct Model1_tcphdr *Model1_th;
 Model1_u16 Model1_user_mss;
 int Model1_mss;

#if CY_ABSTRACT4
 Model1_skb = &Model1_Skb_Out;
 Model1_cy_alloc_skb(Model1_skb, Model1_Buff_Out, Model1_SKB_DATA_SIZE);
#else
 Model1_skb = Model1_alloc_skb((128 + 32), ((( Model1_gfp_t)0x20u)|(( Model1_gfp_t)0x80000u)|(( Model1_gfp_t)0x2000000u)));
 if (__builtin_expect(!!(!Model1_skb), 0)) {
  Model1_dst_release(Model1_dst);
  return ((void *)0);
 }
#endif
 /* Reserve space for headers. */
 Model1_skb_reserve(Model1_skb, (128 + 32));

 switch (Model1_synack_type) {
 case Model1_TCP_SYNACK_NORMAL:
  Model1_skb_set_owner_w(Model1_skb, Model1_req_to_sk(Model1_req));
  break;
 case Model1_TCP_SYNACK_COOKIE:
  /* Under synflood, we do not attach skb to a socket,
		 * to avoid false sharing.
		 */
  break;
 case Model1_TCP_SYNACK_FASTOPEN:
  /* sk is a const pointer, because we want to express multiple
		 * cpu might call us concurrently.
		 * sk->sk_wmem_alloc in an atomic, we can promote to rw.
		 */
  Model1_skb_set_owner_w(Model1_skb, (struct Model1_sock *)Model1_sk);
  break;
 }
#if !CY_ABSTRACT3
 Model1_skb_dst_set(Model1_skb, Model1_dst);
#endif

 Model1_mss = Model1_dst_metric_advmss(Model1_dst);
 Model1_user_mss = ({ union { typeof(Model1_tp->Model1_rx_opt.Model1_user_mss) Model1___val; char Model1___c[1]; } Model1___u; if (1) Model1___read_once_size(&(Model1_tp->Model1_rx_opt.Model1_user_mss), Model1___u.Model1___c, sizeof(Model1_tp->Model1_rx_opt.Model1_user_mss)); else Model1___read_once_size_nocheck(&(Model1_tp->Model1_rx_opt.Model1_user_mss), Model1___u.Model1___c, sizeof(Model1_tp->Model1_rx_opt.Model1_user_mss)); Model1___u.Model1___val; });
 if (Model1_user_mss && Model1_user_mss < Model1_mss)
  Model1_mss = Model1_user_mss;

 memset(&Model1_opts, 0, sizeof(Model1_opts));





 Model1_skb_mstamp_get(&Model1_skb->Model1_skb_mstamp);





 Model1_skb_set_hash(Model1_skb, Model1_tcp_rsk(Model1_req)->Model1_txhash, Model1_PKT_HASH_TYPE_L4);
 Model1_tcp_header_size = Model1_tcp_synack_options(Model1_req, Model1_mss, Model1_skb, &Model1_opts, Model1_md5, Model1_foc) +
     sizeof(*Model1_th);

 Model1_skb_push(Model1_skb, Model1_tcp_header_size);
 Model1_skb_reset_transport_header(Model1_skb);

 Model1_th = (struct Model1_tcphdr *)Model1_skb->Model1_data;
 memset(Model1_th, 0, sizeof(struct Model1_tcphdr));
 Model1_th->Model1_syn = 1;
 Model1_th->Model1_ack = 1;
 Model1_tcp_ecn_make_synack(Model1_req, Model1_th);
 Model1_th->Model1_source = (( Model1___be16)(__builtin_constant_p((Model1___u16)((Model1_ireq->Model1_req.Model1___req_common.Model1_skc_num))) ? ((Model1___u16)( (((Model1___u16)((Model1_ireq->Model1_req.Model1___req_common.Model1_skc_num)) & (Model1___u16)0x00ffU) << 8) | (((Model1___u16)((Model1_ireq->Model1_req.Model1___req_common.Model1_skc_num)) & (Model1___u16)0xff00U) >> 8))) : Model1___fswab16((Model1_ireq->Model1_req.Model1___req_common.Model1_skc_num))));
 Model1_th->Model1_dest = Model1_ireq->Model1_req.Model1___req_common.Model1_skc_dport;
 /* Setting of flags are superfluous here for callers (and ECE is
	 * not even correctly set)
	 */
 Model1_tcp_init_nondata_skb(Model1_skb, Model1_tcp_rsk(Model1_req)->Model1_snt_isn,
        0x02 | 0x10);

 Model1_th->Model1_seq = (( Model1___be32)(__builtin_constant_p((__u32)((((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq))) ? ((__u32)( (((__u32)((((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)((((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32((((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq))));
 /* XXX data is queued and acked as is. No buffer/window check */
 Model1_th->Model1_ack_seq = (( Model1___be32)(__builtin_constant_p((__u32)((Model1_tcp_rsk(Model1_req)->Model1_rcv_nxt))) ? ((__u32)( (((__u32)((Model1_tcp_rsk(Model1_req)->Model1_rcv_nxt)) & (__u32)0x000000ffUL) << 24) | (((__u32)((Model1_tcp_rsk(Model1_req)->Model1_rcv_nxt)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((Model1_tcp_rsk(Model1_req)->Model1_rcv_nxt)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((Model1_tcp_rsk(Model1_req)->Model1_rcv_nxt)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32((Model1_tcp_rsk(Model1_req)->Model1_rcv_nxt))));

 /* RFC1323: The window in SYN & SYN/ACK segments is never scaled. */
 Model1_th->Model1_window = (( Model1___be16)(__builtin_constant_p((Model1___u16)((({ typeof(Model1_req->Model1___req_common.Model1_skc_rcv_wnd) Model1__min1 = (Model1_req->Model1___req_common.Model1_skc_rcv_wnd); typeof(65535U) Model1__min2 = (65535U); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; })))) ? ((Model1___u16)( (((Model1___u16)((({ typeof(Model1_req->Model1___req_common.Model1_skc_rcv_wnd) Model1__min1 = (Model1_req->Model1___req_common.Model1_skc_rcv_wnd); typeof(65535U) Model1__min2 = (65535U); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; }))) & (Model1___u16)0x00ffU) << 8) | (((Model1___u16)((({ typeof(Model1_req->Model1___req_common.Model1_skc_rcv_wnd) Model1__min1 = (Model1_req->Model1___req_common.Model1_skc_rcv_wnd); typeof(65535U) Model1__min2 = (65535U); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; }))) & (Model1___u16)0xff00U) >> 8))) : Model1___fswab16((({ typeof(Model1_req->Model1___req_common.Model1_skc_rcv_wnd) Model1__min1 = (Model1_req->Model1___req_common.Model1_skc_rcv_wnd); typeof(65535U) Model1__min2 = (65535U); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; })))));
 Model1_tcp_options_write((Model1___be32 *)(Model1_th + 1), ((void *)0), &Model1_opts);
 Model1_th->Model1_doff = (Model1_tcp_header_size >> 2);
 (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_OUTSEGS] += 1);
 /* Do not fool tcpdump (if any), clean our debris */
 Model1_skb->Model1_tstamp.Model1_tv64 = 0;
 return Model1_skb;
}

void Model1_tcp_send_ack(struct Model1_sock *Model1_sk){
	//cy consider to use one global variable, instead of using dynamic allocation.
    
    struct Model1_sk_buff *Model1_buff;
    struct Model1_sock * Model1_temp;
    //dst: Current from Attacker to Server/Server_A -> going to send a packet from Server/Server_A
    if (Model1_Src_sk == true){
        Model1_Out_pkt = true;
    }
    //Modify 06/11/2018 Right now we only have one direction from Client or Attacker to Server
    //We assume Client won't send packet to Server so we ignore packets sent to Client
    else{
        //return;
        Model1_Out_pkt = false;
    }

	/* If we have been reset, we may not send again. */
	if (Model1_sk->Model1___sk_common.Model1_skc_state == Model1_TCP_CLOSE)
		return;
    
    //cy: remove tcp_ca_event rihgt now. Othersie Segmentation fault
	Model1_tcp_ca_event(Model1_sk, 7); //CA_EVENT_NON_DELAYED_ACK

#if CY_ABSTRACT4
    Model1_buff = &Model1_Skb_Out;
    Model1_cy_alloc_skb(Model1_buff, Model1_Buff_Out, Model1_SKB_DATA_SIZE);
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
	Model1_skb_reserve(Model1_buff, (128 + (96 + 48)));
	// cy: add the ack number and seq number
	Model1_tcp_init_nondata_skb(Model1_buff, Model1_tcp_acceptable_seq(Model1_sk), 0x10); //0x10 -> ACK

	/* We do not want pure acks influencing TCP Small Queues or fq/pacing
	 * too much.
	 * SKB_TRUESIZE(max(1 .. 66, MAX_TCP_HEADER)) is unfortunately ~784
	 * We also avoid tcp_wfree() overhead (cache line miss accessing
	 * tp->tsq_flags) by using regular sock_wfree()
	 */
	Model1_skb_set_tcp_pure_ack(Model1_buff);

	/* Send it off, this clears delayed acks for us. */
    //cy: not sure about this part. UNCLEAR
	Model1_skb_mstamp_get(&Model1_buff->Model1_skb_mstamp);

    //cy_tcp_transmit_skb(sk, buff, flag_visited1);
	//tcp_transmit_skb(sk, buff, 0, (__force gfp_t)0); 
	Model1_cy_tcp_transmit_skb(Model1_sk, Model1_buff, 0, 0);
           
    //CY: Currently we ignore function:tcp_rcv_established
}

void Model1_tcp_time_wait(struct Model1_sock *Model1_sk, int Model1_state, int Model1_timeo){
    assert(0);
}

/**
 *	kfree_skb - free an sk_buff
 *	@skb: buffer to free
 *
 *	Drop a reference to the buffer and free it if the usage count has
 *	hit zero.
 */
void Model1_kfree_skb(struct Model1_sk_buff *Model1_skb)
{
//this function won't be visited
 if (__builtin_expect(!!(!Model1_skb), 0))
  return;
 if (__builtin_expect(!!(Model1_atomic_read(&Model1_skb->Model1_users) == 1), 1))
  __asm__ __volatile__("": : :"memory");
 else if (__builtin_expect(!!(!Model1_atomic_dec_and_test(&Model1_skb->Model1_users)), 1))
  return;
#if !CY_ABSTRACT3
 //somehow cannot find its declaration and defintition at all
 Model1_trace_kfree_skb(Model1_skb, __builtin_return_address(0));
#endif
 Model1___kfree_skb(Model1_skb);
}

/**
 *	__sk_mem_reclaim - reclaim memory_allocated
 *	@sk: socket
 *	@amount: number of bytes (rounded down to a SK_MEM_QUANTUM multiple)
 */
void Model1___sk_mem_reclaim(struct Model1_sock *Model1_sk, int Model1_amount)
{
 Model1_amount >>= ( __builtin_constant_p(((int)((1UL) << 12))) ? ( (((int)((1UL) << 12))) < 1 ? Model1_____ilog2_NaN() : (((int)((1UL) << 12))) & (1ULL << 63) ? 63 : (((int)((1UL) << 12))) & (1ULL << 62) ? 62 : (((int)((1UL) << 12))) & (1ULL << 61) ? 61 : (((int)((1UL) << 12))) & (1ULL << 60) ? 60 : (((int)((1UL) << 12))) & (1ULL << 59) ? 59 : (((int)((1UL) << 12))) & (1ULL << 58) ? 58 : (((int)((1UL) << 12))) & (1ULL << 57) ? 57 : (((int)((1UL) << 12))) & (1ULL << 56) ? 56 : (((int)((1UL) << 12))) & (1ULL << 55) ? 55 : (((int)((1UL) << 12))) & (1ULL << 54) ? 54 : (((int)((1UL) << 12))) & (1ULL << 53) ? 53 : (((int)((1UL) << 12))) & (1ULL << 52) ? 52 : (((int)((1UL) << 12))) & (1ULL << 51) ? 51 : (((int)((1UL) << 12))) & (1ULL << 50) ? 50 : (((int)((1UL) << 12))) & (1ULL << 49) ? 49 : (((int)((1UL) << 12))) & (1ULL << 48) ? 48 : (((int)((1UL) << 12))) & (1ULL << 47) ? 47 : (((int)((1UL) << 12))) & (1ULL << 46) ? 46 : (((int)((1UL) << 12))) & (1ULL << 45) ? 45 : (((int)((1UL) << 12))) & (1ULL << 44) ? 44 : (((int)((1UL) << 12))) & (1ULL << 43) ? 43 : (((int)((1UL) << 12))) & (1ULL << 42) ? 42 : (((int)((1UL) << 12))) & (1ULL << 41) ? 41 : (((int)((1UL) << 12))) & (1ULL << 40) ? 40 : (((int)((1UL) << 12))) & (1ULL << 39) ? 39 : (((int)((1UL) << 12))) & (1ULL << 38) ? 38 : (((int)((1UL) << 12))) & (1ULL << 37) ? 37 : (((int)((1UL) << 12))) & (1ULL << 36) ? 36 : (((int)((1UL) << 12))) & (1ULL << 35) ? 35 : (((int)((1UL) << 12))) & (1ULL << 34) ? 34 : (((int)((1UL) << 12))) & (1ULL << 33) ? 33 : (((int)((1UL) << 12))) & (1ULL << 32) ? 32 : (((int)((1UL) << 12))) & (1ULL << 31) ? 31 : (((int)((1UL) << 12))) & (1ULL << 30) ? 30 : (((int)((1UL) << 12))) & (1ULL << 29) ? 29 : (((int)((1UL) << 12))) & (1ULL << 28) ? 28 : (((int)((1UL) << 12))) & (1ULL << 27) ? 27 : (((int)((1UL) << 12))) & (1ULL << 26) ? 26 : (((int)((1UL) << 12))) & (1ULL << 25) ? 25 : (((int)((1UL) << 12))) & (1ULL << 24) ? 24 : (((int)((1UL) << 12))) & (1ULL << 23) ? 23 : (((int)((1UL) << 12))) & (1ULL << 22) ? 22 : (((int)((1UL) << 12))) & (1ULL << 21) ? 21 : (((int)((1UL) << 12))) & (1ULL << 20) ? 20 : (((int)((1UL) << 12))) & (1ULL << 19) ? 19 : (((int)((1UL) << 12))) & (1ULL << 18) ? 18 : (((int)((1UL) << 12))) & (1ULL << 17) ? 17 : (((int)((1UL) << 12))) & (1ULL << 16) ? 16 : (((int)((1UL) << 12))) & (1ULL << 15) ? 15 : (((int)((1UL) << 12))) & (1ULL << 14) ? 14 : (((int)((1UL) << 12))) & (1ULL << 13) ? 13 : (((int)((1UL) << 12))) & (1ULL << 12) ? 12 : (((int)((1UL) << 12))) & (1ULL << 11) ? 11 : (((int)((1UL) << 12))) & (1ULL << 10) ? 10 : (((int)((1UL) << 12))) & (1ULL << 9) ? 9 : (((int)((1UL) << 12))) & (1ULL << 8) ? 8 : (((int)((1UL) << 12))) & (1ULL << 7) ? 7 : (((int)((1UL) << 12))) & (1ULL << 6) ? 6 : (((int)((1UL) << 12))) & (1ULL << 5) ? 5 : (((int)((1UL) << 12))) & (1ULL << 4) ? 4 : (((int)((1UL) << 12))) & (1ULL << 3) ? 3 : (((int)((1UL) << 12))) & (1ULL << 2) ? 2 : (((int)((1UL) << 12))) & (1ULL << 1) ? 1 : (((int)((1UL) << 12))) & (1ULL << 0) ? 0 : Model1_____ilog2_NaN() ) : (sizeof(((int)((1UL) << 12))) <= 4) ? Model1___ilog2_u32(((int)((1UL) << 12))) : Model1___ilog2_u64(((int)((1UL) << 12))) );
 Model1_sk_memory_allocated_sub(Model1_sk, Model1_amount);
 Model1_sk->Model1_sk_forward_alloc -= Model1_amount << ( __builtin_constant_p(((int)((1UL) << 12))) ? ( (((int)((1UL) << 12))) < 1 ? Model1_____ilog2_NaN() : (((int)((1UL) << 12))) & (1ULL << 63) ? 63 : (((int)((1UL) << 12))) & (1ULL << 62) ? 62 : (((int)((1UL) << 12))) & (1ULL << 61) ? 61 : (((int)((1UL) << 12))) & (1ULL << 60) ? 60 : (((int)((1UL) << 12))) & (1ULL << 59) ? 59 : (((int)((1UL) << 12))) & (1ULL << 58) ? 58 : (((int)((1UL) << 12))) & (1ULL << 57) ? 57 : (((int)((1UL) << 12))) & (1ULL << 56) ? 56 : (((int)((1UL) << 12))) & (1ULL << 55) ? 55 : (((int)((1UL) << 12))) & (1ULL << 54) ? 54 : (((int)((1UL) << 12))) & (1ULL << 53) ? 53 : (((int)((1UL) << 12))) & (1ULL << 52) ? 52 : (((int)((1UL) << 12))) & (1ULL << 51) ? 51 : (((int)((1UL) << 12))) & (1ULL << 50) ? 50 : (((int)((1UL) << 12))) & (1ULL << 49) ? 49 : (((int)((1UL) << 12))) & (1ULL << 48) ? 48 : (((int)((1UL) << 12))) & (1ULL << 47) ? 47 : (((int)((1UL) << 12))) & (1ULL << 46) ? 46 : (((int)((1UL) << 12))) & (1ULL << 45) ? 45 : (((int)((1UL) << 12))) & (1ULL << 44) ? 44 : (((int)((1UL) << 12))) & (1ULL << 43) ? 43 : (((int)((1UL) << 12))) & (1ULL << 42) ? 42 : (((int)((1UL) << 12))) & (1ULL << 41) ? 41 : (((int)((1UL) << 12))) & (1ULL << 40) ? 40 : (((int)((1UL) << 12))) & (1ULL << 39) ? 39 : (((int)((1UL) << 12))) & (1ULL << 38) ? 38 : (((int)((1UL) << 12))) & (1ULL << 37) ? 37 : (((int)((1UL) << 12))) & (1ULL << 36) ? 36 : (((int)((1UL) << 12))) & (1ULL << 35) ? 35 : (((int)((1UL) << 12))) & (1ULL << 34) ? 34 : (((int)((1UL) << 12))) & (1ULL << 33) ? 33 : (((int)((1UL) << 12))) & (1ULL << 32) ? 32 : (((int)((1UL) << 12))) & (1ULL << 31) ? 31 : (((int)((1UL) << 12))) & (1ULL << 30) ? 30 : (((int)((1UL) << 12))) & (1ULL << 29) ? 29 : (((int)((1UL) << 12))) & (1ULL << 28) ? 28 : (((int)((1UL) << 12))) & (1ULL << 27) ? 27 : (((int)((1UL) << 12))) & (1ULL << 26) ? 26 : (((int)((1UL) << 12))) & (1ULL << 25) ? 25 : (((int)((1UL) << 12))) & (1ULL << 24) ? 24 : (((int)((1UL) << 12))) & (1ULL << 23) ? 23 : (((int)((1UL) << 12))) & (1ULL << 22) ? 22 : (((int)((1UL) << 12))) & (1ULL << 21) ? 21 : (((int)((1UL) << 12))) & (1ULL << 20) ? 20 : (((int)((1UL) << 12))) & (1ULL << 19) ? 19 : (((int)((1UL) << 12))) & (1ULL << 18) ? 18 : (((int)((1UL) << 12))) & (1ULL << 17) ? 17 : (((int)((1UL) << 12))) & (1ULL << 16) ? 16 : (((int)((1UL) << 12))) & (1ULL << 15) ? 15 : (((int)((1UL) << 12))) & (1ULL << 14) ? 14 : (((int)((1UL) << 12))) & (1ULL << 13) ? 13 : (((int)((1UL) << 12))) & (1ULL << 12) ? 12 : (((int)((1UL) << 12))) & (1ULL << 11) ? 11 : (((int)((1UL) << 12))) & (1ULL << 10) ? 10 : (((int)((1UL) << 12))) & (1ULL << 9) ? 9 : (((int)((1UL) << 12))) & (1ULL << 8) ? 8 : (((int)((1UL) << 12))) & (1ULL << 7) ? 7 : (((int)((1UL) << 12))) & (1ULL << 6) ? 6 : (((int)((1UL) << 12))) & (1ULL << 5) ? 5 : (((int)((1UL) << 12))) & (1ULL << 4) ? 4 : (((int)((1UL) << 12))) & (1ULL << 3) ? 3 : (((int)((1UL) << 12))) & (1ULL << 2) ? 2 : (((int)((1UL) << 12))) & (1ULL << 1) ? 1 : (((int)((1UL) << 12))) & (1ULL << 0) ? 0 : Model1_____ilog2_NaN() ) : (sizeof(((int)((1UL) << 12))) <= 4) ? Model1___ilog2_u32(((int)((1UL) << 12))) : Model1___ilog2_u64(((int)((1UL) << 12))) );

 if (0 && Model1_sk->Model1_sk_memcg)
  Model1_mem_cgroup_uncharge_skmem(Model1_sk->Model1_sk_memcg, Model1_amount);

 if (Model1_sk_under_memory_pressure(Model1_sk) &&
     (Model1_sk_memory_allocated(Model1_sk) < Model1_sk_prot_mem_limits(Model1_sk, 0)))
  Model1_sk_leave_memory_pressure(Model1_sk);
}

int Model1_sock_wake_async(struct Model1_socket_wq *Model1_sk_wq, int Model1_how, int Model1_band){
    assert(0);
}

struct Model1_sk_buff *Model1_alloc_skb_with_frags(unsigned long Model1_header_len,
    unsigned long Model1_data_len,
    int Model1_max_page_order,
    int *Model1_errcode,
    Model1_gfp_t Model1_gfp_mask){
    assert(0);
    struct Model1_sk_buff *cy;
    return cy;
}

unsigned char *Model1_skb_put(struct Model1_sk_buff *Model1_skb, unsigned int Model1_len){
  unsigned char *Model1_tmp = Model1_skb_tail_pointer(Model1_skb);
    //SKB_LINEAR_ASSERT(skb);
  //do { if (skb_is_nonlinear(skb)) do { asm volatile("1:\tud2\n" ".pushsection __bug_table,\"a\"\n" "2:\t.long 1b - 2b, %c0 - 2b\n" "\t.word %c1, 0\n" "\t.org 2b+   %c2\n" ".popsection" : : "i" ("net/core/skbuff.c"), "i" (1433), "i" (sizeof(struct bug_entry)));  __builtin_unreachable(); } while (0); } while (0);
  Model1_skb->Model1_tail += Model1_len;
  Model1_skb->Model1_len += Model1_len;
  if (Model1_skb->Model1_tail > Model1_skb->Model1_end)
   //skb_over_panic(skb, len, __builtin_return_address(0));
   // some alert
   exit	(0);

  return Model1_tmp;
}

int Model1_skb_copy_datagram_from_iter(struct Model1_sk_buff *Model1_skb, int Model1_offset,
    struct Model1_iov_iter *Model1_from, int Model1_len) {
    assert(0);
    return 0;
}

// free skb space
void Model1_sock_rfree(struct Model1_sk_buff *Model1_skb){ //remove truesize
    struct Model1_sock *Model1_sk = Model1_skb->Model1_sk;
  	unsigned int Model1_len = Model1_skb->Model1_truesize;

  	Model1_atomic_sub(Model1_len, &Model1_sk->Model1_sk_backlog.Model1_rmem_alloc);
  	Model1_sk_mem_uncharge(Model1_sk, Model1_len);
}

static void Model1_skb_release_data(struct Model1_sk_buff *Model1_skb){
#if CY_ABSTRACT3
    //The size calculation is done in function skb_release_head_state
    //we ignore the codes that actually frees data memory (linear space: skb->head, shinfo->frags, and shinfo->frag_list)
#endif 
}

static void Model1_skb_release_head_state(struct Model1_sk_buff *Model1_skb);

static void Model1_skb_release_all(struct Model1_sk_buff *Model1_skb){
    Model1_skb_release_head_state(Model1_skb);
    if (Model1_skb->Model1_head)
        Model1_skb_release_data(Model1_skb);
}

static void Model1_kfree_skbmem(struct Model1_sk_buff *Model1_skb){
#if CY_ABSTRACT3
    //Free an skbuff by memory without cleaning the state
    //We ignore the codes that actually free data, which is out of scope and requires physical interfaces
#endif
}

static void Model1_skb_release_head_state(struct Model1_sk_buff *Model1_skb){
    Model1_skb_dst_drop(Model1_skb);
#if CY_ABSTRACT3 
//Assume CONFIG_XFRM 0 <= regardless of IPSec
#else
    Model1_secpath_put(Model1_skb->Model1_sp);
#endif

    if (Model1_skb->Model1_destructor){ //if it's assigned, it's sock_rfree
        Model1_skb->Model1_destructor(Model1_skb);
    }
#if CY_ABSTRACT3
//Assume IS_ENABLED(CONFIG_NF_CONNTRACK) 0 <= netfilter connection track is not used
#else
    Model1_nf_conntrack_put(Model1_skb->Model1_nfct);
#endif
}

void Model1___kfree_skb(struct Model1_sk_buff *Model1_skb){
    //We didn't dynamically allocate memory, so we don't release such memory
    //Instead, only update memory counted in receive buff
    //skb_release_all:skb_release_head_state:
    Model1_skb_release_all(Model1_skb);
    Model1_kfree_skbmem(Model1_skb);
    if (Model1_skb->Model1_destructor){ //if it's assigned, it's sock_rfree from skb_set_owner_r
        Model1_skb->Model1_destructor(Model1_skb);
    }
    return;
}
void Model1_warn_slowpath_null(const char *Model1_file, int Model1_line){
    //__warn(file, line, __builtin_return_address(0), TAINT_WARN, NULL, NULL);
    return;
}
bool Model1_skb_try_coalesce(struct Model1_sk_buff *Model1_to, struct Model1_sk_buff *Model1_from, bool *Model1_fragstolen, int *Model1_delta_truesize){
 int Model1_i, Model1_delta, Model1_len = Model1_from->Model1_len;
 
  *Model1_fragstolen = false;

  if (Model1_skb_cloned(Model1_to)) //[CY] assuem skb_clone is false
   return false;

//[CY] assume aggresively that skb_tailroom(to) == 0 (i.e., no space left for new data). So we need to allocate more space, make delta = len;
  if (Model1_len <= Model1_skb_tailroom(Model1_to)) {
   if (Model1_len)
#if CY_ABSTRACT4
       Model1_skb_copy_bits(Model1_from, 0, Model1_skb_put(Model1_to, Model1_len), Model1_len); //put is used to change the tailroom
#else
    //do { if (__builtin_expect(!!(Model1_skb_copy_bits(Model1_from, 0, Model1_skb_put(Model1_to, Model1_len), Model1_len)), 0)) do { asm volatile("1:\tud2\n" ".pushsection __bug_table,\"a\"\n" "2:\t.long  1b - 2b, %c0 - 2b\n" "\t.word %c1, 0\n" "\t.org 2b+%c2\n" ".popsection" : : "i" ("net/core/skbuff.c"), "i" (4254), "i" (sizeof(struct Model1_bug_entry))); do { }       while (1); } while (0); } while (0);
#endif
   *Model1_delta_truesize = 0;
   return true;
  }
 
#if !CY_ABSTRACT1
  if (Model1_skb_has_frag_list(Model1_to) || Model1_skb_has_frag_list(Model1_from))
   return false;
#endif

  if (Model1_skb_headlen(Model1_from) != 0) {
   struct Model1_page *Model1_page;
   unsigned int Model1_offset;
 
   if (((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_to)))->Model1_nr_frags +
       ((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_from)))->Model1_nr_frags >= (65536/((1UL) << 12) + 1))
    return false;

   // if skb->head_frag == 0 || skb_cloned(skb); //always return true since skb->head_frag == 0
   if (Model1_skb_head_is_locked(Model1_from))
    return false;
 
   Model1_delta = Model1_from->Model1_truesize - ((((sizeof(struct Model1_sk_buff))) + ((typeof((sizeof(struct Model1_sk_buff))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model1_sk_buff))))(((1 <<  (6)))) - 1));
   Model1_page = Model1_virt_to_head_page(Model1_from->Model1_head);
   Model1_offset = Model1_from->Model1_data - (unsigned char *)Model1_lowmem_page_address(Model1_page);
 
   Model1_skb_fill_page_desc(Model1_to, ((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_to)))->Model1_nr_frags,
        Model1_page, Model1_offset, Model1_skb_headlen(Model1_from));
   *Model1_fragstolen = true;
  }
  else {
   if (((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_to)))->Model1_nr_frags +
       ((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_from)))->Model1_nr_frags > (65536/((1UL) << 12) + 1))
    return false;
 
   Model1_delta = Model1_from->Model1_truesize - ((Model1_skb_end_offset(Model1_from)) + ((((sizeof(struct Model1_sk_buff))) + ((typeof((sizeof(struct Model1_sk_buff))))(((1 << (6)))) - 1)) &                    ~((typeof((sizeof(struct Model1_sk_buff))))(((1 << (6)))) - 1)) + ((((sizeof(struct Model1_skb_shared_info))) + ((typeof((sizeof(struct Model1_skb_shared_info))))(((1 << (6)))) -    1)) & ~((typeof((sizeof(struct Model1_skb_shared_info))))(((1 << (6)))) - 1)));
  }
 
  ({ static bool __attribute__ ((__section__(".data.unlikely"))) Model1___warned; int Model1___ret_warn_once = !!(Model1_delta < Model1_len); if (__builtin_expect(!!(Model1___ret_warn_once && !    Model1___warned), 0)) { Model1___warned = true; ({ int Model1___ret_warn_on = !!(1); if (__builtin_expect(!!(Model1___ret_warn_on), 0)) Model1_warn_slowpath_null("net/core/skbuff.c", 4289);       __builtin_expect(!!(Model1___ret_warn_on), 0); }); } __builtin_expect(!!(Model1___ret_warn_once), 0); });
 
  ({ size_t Model1___len = (((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_from)))->Model1_nr_frags * sizeof(Model1_skb_frag_t)); void *Model1___ret; if (__builtin_constant_p(((struct          Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_from)))->Model1_nr_frags * sizeof(Model1_skb_frag_t)) && Model1___len >= 64) Model1___ret = Model1___memcpy((((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_to)))->Model1_frags + ((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_to)))->Model1_nr_frags), (((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_from)))->Model1_frags), Model1___len); else Model1___ret =        __builtin_memcpy((((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_to)))->Model1_frags + ((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_to)))->Model1_nr_frags), (((struct             Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_from)))->Model1_frags), Model1___len); Model1___ret; });
 
 
  ((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_to)))->Model1_nr_frags += ((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_from)))->Model1_nr_frags;
 
  if (!Model1_skb_cloned(Model1_from))
   ((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_from)))->Model1_nr_frags = 0;
 
 
 
 
  for (Model1_i = 0; Model1_i < ((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_from)))->Model1_nr_frags; Model1_i++)
   Model1_skb_frag_ref(Model1_from, Model1_i);

//#else //my abstraction [CY]
//Model1_delta = Model1_from->Model1_truesize/2; //Model1_len;
//#endif 
Model1_to->Model1_truesize += Model1_delta;
  Model1_to->Model1_len += Model1_len;
  Model1_to->Model1_data_len += Model1_len;
 
  *Model1_delta_truesize = Model1_delta;
  return true;
}

int Model1___sk_mem_schedule(struct Model1_sock *Model1_sk, int Model1_size, int Model1_kind)
{
  struct Model1_proto *Model1_prot = Model1_sk->Model1___sk_common.Model1_skc_prot;
  int Model1_amt = Model1_sk_mem_pages(Model1_size);
  long Model1_allocated;
 
  Model1_sk->Model1_sk_forward_alloc += Model1_amt * ((int)((1UL) << 12)); //CY_ABSTRACT1

  Model1_allocated = Model1_sk_memory_allocated_add(Model1_sk, Model1_amt);

  if (0 && Model1_sk->Model1_sk_memcg &&
      !Model1_mem_cgroup_charge_skmem(Model1_sk->Model1_sk_memcg, Model1_amt))
   goto Model1_suppress_allocation;
 
  /* Under limit. */ 
  if (Model1_allocated <= Model1_sk_prot_mem_limits(Model1_sk, 0)) { //flipping
   Model1_sk_leave_memory_pressure(Model1_sk);
   return 1;
  }
 
  /* Under pressure. */ 
  if (Model1_allocated > Model1_sk_prot_mem_limits(Model1_sk, 1)){ //flipping
   Model1_sk_enter_memory_pressure(Model1_sk);
  }
 
  /* Over hard limit. */ 
  if (Model1_allocated > Model1_sk_prot_mem_limits(Model1_sk, 2)){ //flipping??
   goto Model1_suppress_allocation;
  }

  /* guarantee minimum buffer size under pressure */
  if (Model1_kind == 1) { //SK_MEM_RECV
   if (Model1_atomic_read(&Model1_sk->Model1_sk_backlog.Model1_rmem_alloc) < Model1_prot->Model1_sysctl_rmem[0])
    return 1;
 
  } else { // SK_MEM_SEND
#if CY_ABSTRACT1
#else
   if (Model1_sk->Model1_sk_type == Model1_SOCK_STREAM) {
    if (Model1_sk->Model1_sk_wmem_queued < Model1_prot->Model1_sysctl_wmem[0])
     return 1;
   } else if (Model1_atomic_read(&Model1_sk->Model1_sk_wmem_alloc) <
       Model1_prot->Model1_sysctl_wmem[0])
     return 1;
#endif
  }
 
  if (Model1_sk_has_memory_pressure(Model1_sk)) {
   int Model1_alloc;
 
   if (!Model1_sk_under_memory_pressure(Model1_sk))
    return 1;
   Model1_alloc = Model1_sk_sockets_allocated_read_positive(Model1_sk);
   if (Model1_sk_prot_mem_limits(Model1_sk, 2) > Model1_alloc *
       Model1_sk_mem_pages(Model1_sk->Model1_sk_wmem_queued +
      Model1_atomic_read(&Model1_sk->Model1_sk_backlog.Model1_rmem_alloc) +
      Model1_sk->Model1_sk_forward_alloc)){ //change to pages
    return 1;
   }
  }
 
 Model1_suppress_allocation:
  //[CY] We don't have SK_MEM_SEND so far 
#if !CY_ABSTRACT1 //TODO
  if (Model1_kind == 0 && Model1_sk->Model1_sk_type == Model1_SOCK_STREAM) {
   Model1_sk_stream_moderate_sndbuf(Model1_sk);
 
 
 
   if (Model1_sk->Model1_sk_wmem_queued + Model1_size >= Model1_sk->Model1_sk_sndbuf)
    return 1;
  }
#endif

  //[CY] what's the purpose? Seems useless
#if !CY_ABSTRACT1 //TODO
  Model1_trace_sock_exceed_buf_limit(Model1_sk, Model1_prot, Model1_allocated);
#endif

  Model1_sk->Model1_sk_forward_alloc -= Model1_amt * ((int)((1UL) << 12));
 
  Model1_sk_memory_allocated_sub(Model1_sk, Model1_amt);

  if (0 && Model1_sk->Model1_sk_memcg)
   Model1_mem_cgroup_uncharge_skmem(Model1_sk->Model1_sk_memcg, Model1_amt);
 
  return 0;
}

void *Model1___memcpy(void *Model1_to, const void *Model1_from, size_t Model1_len){
#if CY_ABSTRACT3
    memcpy(Model1_to, Model1_from, Model1_len);
#else
    assert(0);
#endif
}

int Model1_skb_copy_bits(const struct Model1_sk_buff *Model1_skb, int Model1_offset, void * Model1_to, int Model1_len){
#if CY_ABSTRACT3
    //we don't care what's the content inside the packet payload
    return 0;
#else
    assert(0);
	return 0;
#endif
}

struct Model1_sk_buff *Model1___alloc_skb(unsigned int Model1_size, Model1_gfp_t Model1_priority,  int Model1_flags,
        int Model1_node){
#if CY_ABSTRACT10
    return NULL;
#else
    assert(0);
    return NULL;
#endif
}

void Model1_kfree_skb_partial(struct Model1_sk_buff *Model1_skb, bool Model1_head_stolen)
{
 if (Model1_head_stolen) {
  Model1_skb_release_head_state(Model1_skb);
  Model1_kmem_cache_free(Model1_skbuff_head_cache, Model1_skb);
 } else {
  Model1___kfree_skb(Model1_skb);
 }
}

unsigned long Model1_get_seconds(void){
    assert(0);
	return 0;
}

bool Model1_tcp_schedule_loss_probe(struct Model1_sock *Model1_sk){
    assert(0);
	return true;
}

int Model1_skb_copy_and_csum_datagram_msg(struct Model1_sk_buff *Model1_skb, int Model1_hlen,
        struct Model1_msghdr *Model1_msg){
    assert(0);
	return 0;
}

 void Model1_tcp_send_delayed_ack(struct Model1_sock *Model1_sk)
 {
  struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
  int Model1_ato = Model1_icsk->Model1_icsk_ack.Model1_ato;
  unsigned long Model1_timeout;
 
  Model1_tcp_ca_event(Model1_sk, Model1_CA_EVENT_DELAYED_ACK);

#if CY_ABSTRACT2
  //Mark delayed ack
  if (Model1_Src_sk == true)
    Model1_delayed_ack = true;
  Model1_tcp_send_ack(Model1_sk);
#else
 
  if (Model1_ato > ((unsigned)(1000/25))) {
   const struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
   int Model1_max_ato = 1000 / 2;
 
   if (Model1_icsk->Model1_icsk_ack.Model1_pingpong ||
       (Model1_icsk->Model1_icsk_ack.Model1_pending & Model1_ICSK_ACK_PUSHED))
    Model1_max_ato = ((unsigned)(1000/5)); //200ms
 
 
 
 
   if (Model1_tp->Model1_srtt_us) {
    int Model1_rtt = ({ int Model1___max1 = (Model1_usecs_to_jiffies(Model1_tp->Model1_srtt_us >> 3)); int Model1___max2   = (((unsigned)(1000/25))); Model1___max1 > Model1___max2 ? Model1___max1: Model1___max2; })
                     ;
 
    if (Model1_rtt < Model1_max_ato)
     Model1_max_ato = Model1_rtt;
   }

 
   Model1_ato = ({ typeof(Model1_ato) Model1__min1 = (Model1_ato); typeof(Model1_max_ato) Model1__min2 = (Model1_max_ato);        (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
  }
 
 
  Model1_timeout = Model1_jiffies + Model1_ato;
 
  if (Model1_icsk->Model1_icsk_ack.Model1_pending & Model1_ICSK_ACK_TIMER) {
 
 
 
   if (Model1_icsk->Model1_icsk_ack.Model1_blocked ||
       (({ unsigned long Model1___dummy; typeof(Model1_jiffies + (Model1_ato >> 2)) Model1___dummy2;         (void)(&Model1___dummy == &Model1___dummy2); 1; }) && ({ unsigned long Model1___dummy; typeof(Model1_icsk->Model1_icsk_ack.Model1_timeout) Model1___dummy2; (void)(&Model1___dummy == &Model1___dummy2); 1; }) &&            ((long)((Model1_jiffies + (Model1_ato >> 2)) - (Model1_icsk->Model1_icsk_ack.Model1_timeout)) >= 0))) {
    Model1_tcp_send_ack(Model1_sk);
    return;
   }
 
   if (!(({ unsigned long Model1___dummy; typeof(Model1_icsk->Model1_icsk_ack.Model1_timeout) Model1___dummy2;      (void)(&Model1___dummy == &Model1___dummy2); 1; }) && ({ unsigned long Model1___dummy;               typeof(Model1_timeout) Model1___dummy2; (void)(&Model1___dummy == &Model1___dummy2); 1; }) &&               ((long)((Model1_timeout) - (Model1_icsk->Model1_icsk_ack.Model1_timeout)) < 0)))
    Model1_timeout = Model1_icsk->Model1_icsk_ack.Model1_timeout;
  }
  Model1_icsk->Model1_icsk_ack.Model1_pending |= Model1_ICSK_ACK_SCHED | Model1_ICSK_ACK_TIMER;
  Model1_icsk->Model1_icsk_ack.Model1_timeout = Model1_timeout;
  Model1_sk_reset_timer(Model1_sk, &Model1_icsk->Model1_icsk_delack_timer, Model1_timeout);
#endif
}

void Model1_sk_forced_mem_schedule(struct Model1_sock *Model1_sk, int Model1_size){
  int Model1_amt;
 
  if (Model1_size <= Model1_sk->Model1_sk_forward_alloc)
   return;
  Model1_amt = Model1_sk_mem_pages(Model1_size);
  Model1_sk->Model1_sk_forward_alloc += Model1_amt * ((int)((1UL) << 12));
  Model1_sk_memory_allocated_add(Model1_sk, Model1_amt);
 
  if (0 && Model1_sk->Model1_sk_memcg)
   Model1_mem_cgroup_charge_skmem(Model1_sk->Model1_sk_memcg, Model1_amt);
}

int Model1_skb_copy_datagram_iter(const struct Model1_sk_buff *Model1_from, int Model1_offset,
       struct Model1_iov_iter *Model1_to, int Model1_size){
    assert(0);
	return 0;
}

void Model1_dst_release(struct Model1_dst_entry *Model1_dst){
#if CY_ABSTRACT1
    // We ignore dst related process
#else
    if (Model1_dst){
        ...
    }
#endif
}

void Model1_sk_send_sigurg(struct Model1_sock *Model1_sk){
#if CY_ABSTRACT1
    //Did nothing, since we ignore those callback
#endif
}

void Model1_kfree(const void *cy){
    assert(0);
}

int Model1___tcp_retransmit_skb(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb, int Model1_segs){
    assert(0);
    return 0;
}

int Model1_tcp_mss_to_mtu(struct Model1_sock *Model1_sk, int Model1_mss){
    assert(0);
    return 0;
}

void Model1_sk_free(struct Model1_sock *Model1_sk){
#if CY_ABSTRACT1
    //TODO:
#else
    assert(0);
#endif
}

unsigned int Model1_tcp_sync_mss(struct Model1_sock *Model1_sk, Model1_u32 Model1_pmtu){
#if CY_ABSTRACT3
    return 65535;
#endif
}

void Model1_tcp_update_metrics(struct Model1_sock *Model1_sk){
    assert(0);
}

void Model1_tcp_skb_collapse_tstamp(struct Model1_sk_buff *Model1_skb, const struct Model1_sk_buff *Model1_next_skb){
    assert(0);
}

void Model1___skb_tstamp_tx(struct Model1_sk_buff *Model1_orig_skb,
        struct Model1_skb_shared_hwtstamps *Model1_hwtstamps,
        struct Model1_sock *Model1_sk, int Model1_tstype){
    assert(0);
}

void Model1_tcp_init_congestion_control(struct Model1_sock *Model1_sk){
#if CY_ABSTRACT1
    //We don't consider congestion_control so far, since we don't have send process
    //TODO: or we can add the codes any way
#endif
}

void Model1___compiletime_assert_249(void){}
void Model1___compiletime_assert_1297(void){}
void Model1___compiletime_assert_1620(void){}
void Model1___compiletime_assert_2254(void){}
void Model1___compiletime_assert_4065(void){}
void Model1___compiletime_assert_4066(void){}
void Model1___compiletime_assert_4067(void){}
void Model1___compiletime_assert_4068(void){}
void Model1___compiletime_assert_4069(void){}
void Model1___compiletime_assert_4070(void){}
void Model1___compiletime_assert_4071(void){}
void Model1___compiletime_assert_4072(void){}
void Model1___compiletime_assert_4073(void){}
void Model1___compiletime_assert_4074(void){}
void Model1___compiletime_assert_4075(void){}
void Model1___compiletime_assert_4076(void){}
void Model1___compiletime_assert_4077(void){}
void Model1___compiletime_assert_4078(void){}
void Model1___compiletime_assert_4079(void){}
void Model1___compiletime_assert_4080(void){}


Model1_u32 Model1_prandom_u32(void){
#if CY_ABSTRACT3
    //TODO: should we return a fixed value, so the program is deterministic?
    ////currently is only called by req->txhash = net_tx_rndhash(), which doesn't matter
    Model1_u32 x = 1;//rand();
    return x;
#else
    return rand();
#endif
}

int Model1_tcp_rack_mark_lost(struct Model1_sock *Model1_sk){
    assert(0);
	return 0;
}

/* Returns true if we should perform Fast Open on the SYN. The cookie (foc)
 * may be updated and return the client in the SYN-ACK later. E.g., Fast Open
 * cookie request (foc->len == 0).
 */
//copied from net/ipv4/tcp_fastopen.c
struct Model1_sock *Model1_tcp_try_fastopen(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb,
         struct Model1_request_sock *Model1_req,
         struct Model1_tcp_fastopen_cookie *Model1_foc,
         struct Model1_dst_entry *Model1_dst)
{
 struct Model1_tcp_fastopen_cookie Model1_valid_foc = { .Model1_len = -1 };
 bool Model1_syn_data = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq != ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq + 1;
 struct Model1_sock *Model1_child;

 if (Model1_foc->Model1_len == 0) /* Client requests a cookie */
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPFASTOPENCOOKIEREQD] += 1);

 if (!((Model1_sysctl_tcp_fastopen & 2) &&
       (Model1_syn_data || Model1_foc->Model1_len >= 0) &&
       Model1_tcp_fastopen_queue_check(Model1_sk))) {
  Model1_foc->Model1_len = -1;
  return ((void *)0);
 }

 if (Model1_syn_data && (Model1_sysctl_tcp_fastopen & 0x200))
  goto Model1_fastopen;

 if (Model1_foc->Model1_len >= 0 && /* Client presents or requests a cookie */
     Model1_tcp_fastopen_cookie_gen(Model1_req, Model1_skb, &Model1_valid_foc) &&
     Model1_foc->Model1_len == 8 &&
     Model1_foc->Model1_len == Model1_valid_foc.Model1_len &&
     !Model1_memcmp(Model1_foc->Model1_val, Model1_valid_foc.Model1_val, Model1_foc->Model1_len)) {
  /* Cookie is valid. Create a (full) child socket to accept
		 * the data in SYN before returning a SYN-ACK to ack the
		 * data. If we fail to create the socket, fall back and
		 * ack the ISN only but includes the same cookie.
		 *
		 * Note: Data-less SYN with valid cookie is allowed to send
		 * data in SYN_RECV state.
		 */
Model1_fastopen:
  Model1_child = Model1_tcp_fastopen_create_child(Model1_sk, Model1_skb, Model1_dst, Model1_req);
  if (Model1_child) {
   Model1_foc->Model1_len = -1;
   (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPFASTOPENPASSIVE] += 1);

   return Model1_child;
  }
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPFASTOPENPASSIVEFAIL] += 1);
 } else if (Model1_foc->Model1_len > 0) /* Client presents an invalid cookie */
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPFASTOPENPASSIVEFAIL] += 1);

 Model1_valid_foc.Model1_exp = Model1_foc->Model1_exp;
 *Model1_foc = Model1_valid_foc;
 return ((void *)0);
}

/* Warning : This function is called without sk_listener being locked.
 * Be sure to read socket fields once, as their value could change under us.
 */
//copied from net/ipv4/tcp_minisocks.c
//TODO: check if we need to further abstract codes, such as Model1_dst_metric_advmss
void Model1_tcp_openreq_init_rwin(struct Model1_request_sock *Model1_req,
      const struct Model1_sock *Model1_sk_listener,
      const struct Model1_dst_entry *Model1_dst)
{
 struct Model1_inet_request_sock *Model1_ireq = Model1_inet_rsk(Model1_req);
 const struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk_listener);
#if CY_ABSTRACT3
    Model1_req->Model1___req_common.Model1_skc_rcv_wnd = 65535;
    Model1_req->Model1___req_common.Model1_skc_window_clamp = 65535;
    Model1_ireq->Model1_rcv_wscale = 65535;

#else
 Model1_u16 Model1_user_mss = ({ union { typeof(Model1_tp->Model1_rx_opt.Model1_user_mss) Model1___val; char Model1___c[1]; } Model1___u; if (1) Model1___read_once_size(&(Model1_tp->Model1_rx_opt.Model1_user_mss), Model1___u.Model1___c, sizeof(Model1_tp->Model1_rx_opt.Model1_user_mss)); else Model1___read_once_size_nocheck(&(Model1_tp->Model1_rx_opt.Model1_user_mss), Model1___u.Model1___c, sizeof(Model1_tp->Model1_rx_opt.Model1_user_mss)); Model1___u.Model1___val; });
 int Model1_full_space = Model1_tcp_full_space(Model1_sk_listener);
 int Model1_mss = Model1_dst_metric_advmss(Model1_dst);
 Model1_u32 Model1_window_clamp;
 __u8 Model1_rcv_wscale;

 if (Model1_user_mss && Model1_user_mss < Model1_mss)
  Model1_mss = Model1_user_mss;

 Model1_window_clamp = ({ union { typeof(Model1_tp->Model1_window_clamp) Model1___val; char Model1___c[1]; } Model1___u; if (1) Model1___read_once_size(&(Model1_tp->Model1_window_clamp), Model1___u.Model1___c, sizeof(Model1_tp->Model1_window_clamp)); else Model1___read_once_size_nocheck(&(Model1_tp->Model1_window_clamp), Model1___u.Model1___c, sizeof(Model1_tp->Model1_window_clamp)); Model1___u.Model1___val; });
 /* Set this up on the first call only */
 Model1_req->Model1___req_common.Model1_skc_window_clamp = Model1_window_clamp ? : Model1_dst_metric(Model1_dst, Model1_RTAX_WINDOW);

 /* limit the window selection if the user enforce a smaller rx buffer */
 if (Model1_sk_listener->Model1_sk_userlocks & 2 &&
     (Model1_req->Model1___req_common.Model1_skc_window_clamp > Model1_full_space || Model1_req->Model1___req_common.Model1_skc_window_clamp == 0))
  Model1_req->Model1___req_common.Model1_skc_window_clamp = Model1_full_space;

 /* tcp_full_space because it is guaranteed to be the first packet */
 Model1_tcp_select_initial_window(Model1_full_space,
  Model1_mss - (Model1_ireq->Model1_tstamp_ok ? 12 : 0),
  &Model1_req->Model1___req_common.Model1_skc_rcv_wnd,
  &Model1_req->Model1___req_common.Model1_skc_window_clamp,
  Model1_ireq->Model1_wscale_ok,
  &Model1_rcv_wscale,
  Model1_dst_metric(Model1_dst, Model1_RTAX_INITRWND));
 Model1_ireq->Model1_rcv_wscale = Model1_rcv_wscale;
#endif
}

int Model1_skb_shift(struct Model1_sk_buff *Model1_tgt, struct Model1_sk_buff *Model1_skb, int             Model1_shiftlen){
    assert(0);
	return 0;
}

void Model1_reqsk_fastopen_remove(struct Model1_sock *Model1_sk, struct Model1_request_sock *Model1_req,
       bool Model1_reset){
    assert(0);
}

void Model1_consume_skb(struct Model1_sk_buff *Model1_skb){
#if CY_ABSTRACT1
#else
    assert(0);
#endif
}

Model1___sum16 Model1___skb_checksum_complete_head(struct Model1_sk_buff *Model1_skb, int Model1_len){
    assert(0);
	return 0;
}

Model1___sum16 Model1___skb_checksum_complete(struct Model1_sk_buff *Model1_skb){
    assert(0);
    return 0;
}

void Model1_tcp_init_metrics(struct Model1_sock *Model1_sk){
#if CY_ABSTRACT1
    //ignore metrics initialization on socket, related to dst
#endif
}

void Model1_kmem_cache_free(struct Model1_kmem_cache *cy0, void *cy1){
#if CY_ABSTRACT3
    //do nothing, since we don't really realse any memory
#endif
}

//copied form net/ipv4/inet_connection_sock.i
static void Model1_reqsk_queue_hash_req(struct Model1_request_sock *Model1_req,
     unsigned long Model1_timeout)
{
#if !CY_ABSTRACT3 //TODO: may need to change it
 Model1_req->Model1_num_retrans = 0;
 Model1_req->Model1_num_timeout = 0;
 Model1_req->Model1_sk = ((void *)0);

 do { Model1_init_timer_key((((&Model1_req->Model1_rsk_timer))), ((0x00100000)), ((void *)0), ((void *)0)); ((&Model1_req->Model1_rsk_timer))->Model1_function = ((Model1_reqsk_timer_handler)); ((&Model1_req->Model1_rsk_timer))->Model1_data = (((unsigned long)Model1_req)); } while (0);

 Model1_mod_timer(&Model1_req->Model1_rsk_timer, Model1_jiffies + Model1_timeout);

#if CY_ABSTRACT3
#else
 Model1_inet_ehash_insert(Model1_req_to_sk(Model1_req), ((void *)0));
#endif
 /* before letting lookups find us, make sure all req fields
	 * are committed to memory and refcnt initialized.
	 */
 __asm__ __volatile__("": : :"memory");
 Model1_atomic_set(&Model1_req->Model1___req_common.Model1_skc_refcnt, 2 + 1);
#endif
}
//copied from net/ipv4/inet_connection_sock.i
void Model1_inet_csk_reqsk_queue_hash_add(struct Model1_sock *Model1_sk, struct Model1_request_sock *Model1_req,
       unsigned long Model1_timeout)
{
 Model1_reqsk_queue_hash_req(Model1_req, Model1_timeout);
 Model1_inet_csk_reqsk_queue_added(Model1_sk);
}

void Model1_tcp_enter_memory_pressure(struct Model1_sock *Model1_sk)
{
 if (!Model1_tcp_memory_pressure) {
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPMEMORYPRESSURES] += 1);
  Model1_tcp_memory_pressure = 1;
 }
}

void Model1_tcp_cwnd_restart(struct Model1_sock *Model1_sk, Model1_s32 Model1_delta){
    assert(0);
}

void Model1_tcp_rack_advance(struct Model1_tcp_sock *Model1_tp,
         const struct Model1_skb_mstamp *Model1_xmit_time, Model1_u8 Model1_sacked){
    assert(0);
}

void Model1_inet_csk_reset_keepalive_timer(struct Model1_sock *Model1_sk, unsigned long Model1_timeout){
    assert(0);
}

bool Model1_tcp_peer_is_proven(struct Model1_request_sock *Model1_req, struct Model1_dst_entry *           Model1_dst,
    bool Model1_paws_check, bool Model1_timestamps){
#if CY_ABSTRACT3
    // this function checks socket connection's timestamp to validate the incoing packet. We assume it's always true
	return true;
#else
    assert(0);
    return true;
#endif
}

int Model1_tcp_trim_head(struct Model1_sock *cy0, struct Model1_sk_buff *cy1, Model1_u32 cy2){
    assert(0);
	return 0;
}

void *Model1_kmem_cache_alloc(struct Model1_kmem_cache *cy0, Model1_gfp_t Model1_flags){
    //we are not really allocate new memories, since model checker cannot track this new memory anymore. Instea, we map allocated memory to pre-allocated memory, based on the second parameter.
    assert(0);
}

#if CY_ABSTRACT3
extern struct Model1_tcp_request_sock Model1_Req;
extern struct Model1_tcp_request_sock Model1_Req_A;

void *Model1_cy_kmem_cache_alloc(int Model1_memory_type){
    //we are not really allocate new memories, since model checker cannot track this new memory anymore. Instea, we map allocated memory to pre-allocated memory, based on the second parameter.
    switch(Model1_memory_type){
        case 0: return (void *)(&Model1_Skb_Out);
        case 1: return (void *)(&Model1_Req_A);//not spoofed
        case 2: return (void *)(&Model1_Req);//spoofed
        case 3: return (void *)(&Model1_Server_A);//not spoofed
        case 4: return (void *)(&Model1_Server);//spoofed
    }
}
#endif

struct Model1_sock *Model1_inet_csk_reqsk_queue_add(struct Model1_sock *Model1_sk,
          struct Model1_request_sock *Model1_req,
          struct Model1_sock *Model1_child)
{
 struct Model1_request_sock_queue *Model1_queue = &Model1_inet_csk(Model1_sk)->Model1_icsk_accept_queue;

 Model1_spin_lock(&Model1_queue->Model1_rskq_lock);
 if (__builtin_expect(!!(Model1_sk->Model1___sk_common.Model1_skc_state != Model1_TCP_LISTEN), 0)) {
  Model1_inet_child_forget(Model1_sk, Model1_req, Model1_child);
  Model1_child = ((void *)0);
 } else {
  Model1_req->Model1_sk = Model1_child;
  Model1_req->Model1_dl_next = ((void *)0);
  if (Model1_queue->Model1_rskq_accept_head == ((void *)0))
   Model1_queue->Model1_rskq_accept_head = Model1_req;
  else
   Model1_queue->Model1_rskq_accept_tail->Model1_dl_next = Model1_req;
  Model1_queue->Model1_rskq_accept_tail = Model1_req;
  Model1_sk_acceptq_added(Model1_sk);
 }
 Model1_spin_unlock(&Model1_queue->Model1_rskq_lock);
 return Model1_child;
}

int Model1_inet_rtx_syn_ack(const struct Model1_sock *Model1_parent, struct Model1_request_sock *Model1_req)
{
#if CY_ABSTRACT7
 int err = Model1_tcp_rtx_synack(Model1_parent, Model1_req);
#else
 int err = Model1_req->Model1_rsk_ops->Model1_rtx_syn_ack(Model1_parent, Model1_req);
#endif

 if (!err)
  Model1_req->Model1_num_retrans++;
 return err;
}

struct Model1_sock *Model1_inet_csk_complete_hashdance(struct Model1_sock *Model1_sk, struct Model1_sock *Model1_child,
      struct Model1_request_sock *Model1_req, bool Model1_own_req)
{
 if (Model1_own_req) {
  Model1_inet_csk_reqsk_queue_drop(Model1_sk, Model1_req);
  Model1_reqsk_queue_removed(&Model1_inet_csk(Model1_sk)->Model1_icsk_accept_queue, Model1_req);
  if (Model1_inet_csk_reqsk_queue_add(Model1_sk, Model1_req, Model1_child))
   return Model1_child;
 }
 /* Too bad, another child took ownership of the request, undo. */
 Model1_spin_unlock(&((Model1_child)->Model1_sk_lock.Model1_slock));
 Model1_sock_put(Model1_child);
 return ((void *)0);
}

int Model1_mod_timer_pending(struct Model1_timer_list *Model1_timer, unsigned long Model1_expires);

static bool Model1_tcp_in_window(Model1_u32 Model1_seq, Model1_u32 Model1_end_seq, Model1_u32 Model1_s_win, Model1_u32 Model1_e_win)
{
 if (Model1_seq == Model1_s_win)
  return true;
 if (Model1_before(Model1_s_win, Model1_end_seq) && Model1_before(Model1_seq, Model1_e_win))
  return true;
 return Model1_seq == Model1_e_win && Model1_seq == Model1_end_seq;
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

struct Model1_sock *Model1_tcp_check_req(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb,
      struct Model1_request_sock *Model1_req,
      bool Model1_fastopen)
{
 struct Model1_tcp_options_received Model1_tmp_opt;
 struct Model1_sock *Model1_child;
 const struct Model1_tcphdr *Model1_th = Model1_tcp_hdr(Model1_skb);
 Model1___be32 Model1_flg = ( ((union Model1_tcp_word_hdr *)(Model1_th))->Model1_words [3]) & (Model1_TCP_FLAG_RST|Model1_TCP_FLAG_SYN|Model1_TCP_FLAG_ACK);
 bool Model1_paws_reject = false;
 bool Model1_own_req;

 Model1_tmp_opt.Model1_saw_tstamp = 0;
 if (Model1_th->Model1_doff > (sizeof(struct Model1_tcphdr)>>2)) {
  Model1_tcp_parse_options(Model1_skb, &Model1_tmp_opt, 0, ((void *)0));

  if (Model1_tmp_opt.Model1_saw_tstamp) {
   Model1_tmp_opt.Model1_ts_recent = Model1_req->Model1_ts_recent;
   /* We do not store true stamp, but it is not required,
			 * it can be estimated (approximately)
			 * from another data.
			 */
   Model1_tmp_opt.Model1_ts_recent_stamp = Model1_get_seconds() - ((((unsigned)(1*1000))/1000)<<Model1_req->Model1_num_timeout);
   Model1_paws_reject = Model1_tcp_paws_reject(&Model1_tmp_opt, Model1_th->Model1_rst);
  }
 }

 /* Check for pure retransmitted SYN. */
 if (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq == Model1_tcp_rsk(Model1_req)->Model1_rcv_isn &&
     Model1_flg == Model1_TCP_FLAG_SYN &&
     !Model1_paws_reject) {
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
  if (!Model1_tcp_oow_rate_limited(Model1_sock_net(Model1_sk), Model1_skb,
       Model1_LINUX_MIB_TCPACKSKIPPEDSYNRECV,
       &Model1_tcp_rsk(Model1_req)->Model1_last_oow_ack_time) &&

      !Model1_inet_rtx_syn_ack(Model1_sk, Model1_req)) {
   unsigned long Model1_expires = Model1_jiffies;

   Model1_expires += ({ typeof(((unsigned)(1*1000)) << Model1_req->Model1_num_timeout) Model1__min1 = (((unsigned)(1*1000)) << Model1_req->Model1_num_timeout); typeof(((unsigned)(120*1000))) Model1__min2 = (((unsigned)(120*1000))); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });

   if (!Model1_fastopen)
    Model1_mod_timer_pending(&Model1_req->Model1_rsk_timer, Model1_expires);
   else
    Model1_req->Model1_rsk_timer.Model1_expires = Model1_expires;
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
 if ((Model1_flg & Model1_TCP_FLAG_ACK) && !Model1_fastopen &&
     (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_ack_seq !=
      Model1_tcp_rsk(Model1_req)->Model1_snt_isn + 1))
  return Model1_sk;
 /* Also, it would be not so bad idea to check rcv_tsecr, which
	 * is essentially ACK extension and too early or too late values
	 * should cause reset in unsynchronized states.
	 */

 /* RFC793: "first check sequence number". */
 if (Model1_paws_reject || !Model1_tcp_in_window(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq,
       Model1_tcp_rsk(Model1_req)->Model1_rcv_nxt, Model1_tcp_rsk(Model1_req)->Model1_rcv_nxt + Model1_req->Model1___req_common.Model1_skc_rcv_wnd)) {
  /* Out of window: send ACK and drop. */
  if (!(Model1_flg & Model1_TCP_FLAG_RST) &&
      !Model1_tcp_oow_rate_limited(Model1_sock_net(Model1_sk), Model1_skb,
       Model1_LINUX_MIB_TCPACKSKIPPEDSYNRECV,
       &Model1_tcp_rsk(Model1_req)->Model1_last_oow_ack_time))
#if CY_ABSTRACT7
   Model1_tcp_v4_reqsk_send_ack(Model1_sk, Model1_skb, Model1_req);
#else
   Model1_req->Model1_rsk_ops->Model1_send_ack(Model1_sk, Model1_skb, Model1_req);
#endif
  if (Model1_paws_reject)
   (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_PAWSESTABREJECTED] += 1);
  return ((void *)0);
 }

 /* In sequence, PAWS is OK. */

 if (Model1_tmp_opt.Model1_saw_tstamp && !Model1_before(Model1_tcp_rsk(Model1_req)->Model1_rcv_nxt, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq))
  Model1_req->Model1_ts_recent = Model1_tmp_opt.Model1_rcv_tsval;

 if (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq == Model1_tcp_rsk(Model1_req)->Model1_rcv_isn) {
  /* Truncate SYN, it is out of window starting
		   at tcp_rsk(req)->rcv_isn + 1. */
  Model1_flg &= ~Model1_TCP_FLAG_SYN;
 }

 /* RFC793: "second check the RST bit" and
	 *	   "fourth, check the SYN bit"
	 */
 if (Model1_flg & (Model1_TCP_FLAG_RST|Model1_TCP_FLAG_SYN)) {
  (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_ATTEMPTFAILS] += 1);
  goto Model1_embryonic_reset;
 }

 /* ACK sequence verified above, just make sure ACK is
	 * set.  If ACK not set, just silently drop the packet.
	 *
	 * XXX (TFO) - if we ever allow "data after SYN", the
	 * following check needs to be removed.
	 */
 if (!(Model1_flg & Model1_TCP_FLAG_ACK))
  return ((void *)0);

 /* For Fast Open no more processing is needed (sk is the
	 * child socket).
	 */
 if (Model1_fastopen)
  return Model1_sk;

 /* While TCP_DEFER_ACCEPT is active, drop bare ACK. */
 if (Model1_req->Model1_num_timeout < Model1_inet_csk(Model1_sk)->Model1_icsk_accept_queue.Model1_rskq_defer_accept &&
     ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq == Model1_tcp_rsk(Model1_req)->Model1_rcv_isn + 1) {
  Model1_inet_rsk(Model1_req)->Model1_acked = 1;
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPDEFERACCEPTDROP] += 1);
  return ((void *)0);
 }

 /* OK, ACK is valid, create big socket and
	 * feed this segment to it. It will repeat all
	 * the tests. THIS SEGMENT MUST MOVE SOCKET TO
	 * ESTABLISHED STATE. If it will be dropped after
	 * socket is created, wait for troubles.
	 */
#if CY_ABSTRACT7
 Model1_child = Model1_tcp_v4_syn_recv_sock(Model1_sk, Model1_skb, Model1_req, ((void *)0),
#else
 Model1_child = Model1_inet_csk(Model1_sk)->Model1_icsk_af_ops->Model1_syn_recv_sock(Model1_sk, Model1_skb, Model1_req, ((void *)0),
#endif
        Model1_req, &Model1_own_req);
 if (!Model1_child)
  goto Model1_listen_overflow;

 Model1_sock_rps_save_rxhash(Model1_child, Model1_skb);
 Model1_tcp_synack_rtt_meas(Model1_child, Model1_req);
 return Model1_inet_csk_complete_hashdance(Model1_sk, Model1_child, Model1_req, Model1_own_req);

Model1_listen_overflow:
 if (!Model1_sysctl_tcp_abort_on_overflow) {
  Model1_inet_rsk(Model1_req)->Model1_acked = 1;
  return ((void *)0);
 }

Model1_embryonic_reset:
 if (!(Model1_flg & Model1_TCP_FLAG_RST)) {
  /* Received a bad SYN pkt - for TFO We try not to reset
		 * the local connection unless it's really necessary to
		 * avoid becoming vulnerable to outside attack aiming at
		 * resetting legit local connections.
		 */
#if CY_ABSTRACT7
  Model1_tcp_v4_send_reset(Model1_sk, Model1_skb);
#else
  Model1_req->Model1_rsk_ops->Model1_send_reset(Model1_sk, Model1_skb);
#endif
 } else if (Model1_fastopen) { /* received a valid RST pkt */
  Model1_reqsk_fastopen_remove(Model1_sk, Model1_req, true);
  Model1_tcp_reset(Model1_sk);
 }
 if (!Model1_fastopen) {
  Model1_inet_csk_reqsk_queue_drop(Model1_sk, Model1_req);
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_EMBRYONICRSTS] += 1);
 }
 return ((void *)0);
}

void Model1___tcp_push_pending_frames(struct Model1_sock *Model1_sk, unsigned int Model1_cur_mss,
           int Model1_nonagle){
    assert(0);
}

void Model1_tcp_mtup_init(struct Model1_sock *Model1_sk){
#if CY_ABSTRACT1
    //TODO: we dont include MTU Probe in our codes neither, since we don't actively send data
#endif
}

bool Model1_tcp_may_send_now(struct Model1_sock *Model1_sk){
    assert(0);
	return true;
}

void Model1_tcp_fastopen_cache_set(struct Model1_sock *Model1_sk, Model1_u16 Model1_mss,
        struct Model1_tcp_fastopen_cookie *Model1_cookie, bool Model1_syn_lost,
        Model1_u16 Model1_try_exp){
    assert(0);
}

void Model1_tcp_fastopen_add_skb(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb){
    assert(0);
}

int Model1_tcp_send_synack(struct Model1_sock *cy){
    assert(0);
	return 0;
}

void *Model1___kmalloc(size_t Model1_size, Model1_gfp_t Model1_flags){
    assert(0);
}

//TODO: may need to rewrite it, using Model1_cy_kmem_cache_alloc
void Model1_cy_alloc_skb(struct Model1_sk_buff *Model1_skb, char *Model1_data, int Model1_size){
 
#if CY_ABSTRACT4
     memset(Model1_skb, 0, ((size_t)&((struct Model1_sk_buff*)0)->Model1_tail));
#else
     memset(Model1_skb, 0, offsetof(struct Model1_sk_buff, Model1_tail));
#endif
     Model1_skb->Model1_truesize = Model1_size+sizeof(struct Model1_sk_buff)+sizeof(struct Model1_skb_shared_info);
     Model1_skb->Model1_head = Model1_data;
     Model1_skb->Model1_data = Model1_data;
     Model1_skb_reset_tail_pointer(Model1_skb); // skb->tail = skb->data - skb->head;
     Model1_skb->Model1_end = Model1_skb->Model1_tail + Model1_size;
     //Model1_skb->Model1_mac_header = (typeof(Model1_skb->Model1_mac_header))~0U;
     Model1_skb->Model1_transport_header = (typeof(Model1_skb->Model1_transport_header))~0U;
 
     /* make sure we initialize shinfo sequentially */
     struct Model1_skb_shared_info *Model1_shinfo;
     Model1_shinfo = ((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_skb)));
     memset(Model1_shinfo, 0, ((size_t)&((struct Model1_skb_shared_info*)0)->Model1_dataref));
     Model1_atomic_set(&Model1_shinfo->Model1_dataref, 1);
 
 
 #if CY_ABSTRACT1
     //when __alloc_skb is called by alloc_skb, flags is always 0
 #else
     if (Model1_flags & 0x01){ //SKB_ALLOC_FCLONE;
         ///...
     }
 #endif
}

__u32 Model1_tcp_acceptable_seq(const struct Model1_sock *Model1_sk)
{
    const struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);


    if (!Model1_before(Model1_tcp_wnd_end(Model1_tp), Model1_tp->Model1_snd_nxt))
        return Model1_tp->Model1_snd_nxt;
    else
        return Model1_tcp_wnd_end(Model1_tp);
}

void Model1_tcp_init_nondata_skb(struct Model1_sk_buff *Model1_skb, Model1_u32 Model1_seq, Model1_u8  Model1_flags)
{
  Model1_skb->Model1_ip_summed = 3;
  Model1_skb->Model1_csum = 0;
 
  ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_tcp_flags = Model1_flags;
  ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked = 0;
 
  Model1_tcp_skb_pcount_set(Model1_skb, 1);
 
  ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq = Model1_seq;
  if (Model1_flags & (0x02 | 0x01))
   Model1_seq++;
  ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq = Model1_seq;
}

int Model1_cy_tcp_transmit_skb(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb, int Model1_clone_it,
         Model1_gfp_t Model1_gfp_mask)
{
   const struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
   struct Model1_inet_sock *Model1_inet;
   struct Model1_tcp_sock *Model1_tp;
   struct Model1_tcp_skb_cb *Model1_tcb;
   //struct tcp_out_options opts;
   unsigned int Model1_tcp_options_size, Model1_tcp_header_size;
   //struct tcp_md5sig_key *md5;
   struct Model1_tcphdr *Model1_th;
   int err;
 
 //  do { if (!skb || !tcp_skb_pcount(skb)) do { asm volatile("1:\tud2\n" ".pushsection                     __bug_table,\"a\"\n" "2:\t.long 1b - 2b, %c0 - 2b\n" "\t.word %c1, 0\n" "\t.org 2b+%c2\n" ".               popsection" : : "i"      ("net/ipv4/tcp_output.c"), "i" (914), "i" (sizeof(struct bug_entry)));            __builtin_unreachable(); } while (0); }       while (0);
   Model1_tcp_skb_pcount(Model1_skb);
   Model1_tp = Model1_tcp_sk(Model1_sk);
 
 //current cline_it == 0
 
   Model1_inet = Model1_inet_sk(Model1_sk);
   Model1_tcb = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]));
 #if CY_ABSTRACT1 //We assume tcp_option is empty
   Model1_tcp_options_size = 0; //tcp_established_options would lead to a empty options anyway
 #else
   // Compute TCP options for SYN packets or other packets. //CYTODO
   if (Model1_tcb->Model1_tcp_flags & 0x02) // TCPHDR_SYN:0x02
    Model1_tcp_options_size = Model1_tcp_syn_options(Model1_sk, Model1_skb, &Model1_opts, &Modle0_md5);
   else
    Model1_tcp_options_size = Model1_tcp_established_options(Model1_sk, Model1_skb, &Model1_opts, &Model1_md5);
 #endif
   //cy: turn off options first
   Model1_tcp_header_size = Model1_tcp_options_size + sizeof(struct Model1_tcphdr);
 // # 948 "net/ipv4/tcp_output.c"
 
     //cy: ooo_okay: allow the mapping of a socket to a queue to be changed. (?)
   Model1_skb->Model1_ooo_okay = Model1_sk_wmem_alloc_get(Model1_sk) < ((1) + ((((sizeof(struct             Model1_sk_buff))) + ((typeof((sizeof(struct Model1_sk_buff))))(((1 << (6)))) - 1)) &                       ~((typeof((sizeof(struct Model1_sk_buff))))(((1 << (6)))) - 1)) + ((((sizeof(struct                        Model1_skb_shared_info))) + ((typeof((sizeof(struct Model1_skb_shared_info))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model1_skb_shared_info))))(((1 << (6)))) - 1)));
 
   Model1_skb_push(Model1_skb, Model1_tcp_header_size);
   Model1_skb_reset_transport_header(Model1_skb);
 
 #if !CY_ABSTRACT4
   Model1_skb_orphan(skb);// orphan a buffer -> Make the skb unowned. We have done this in the receiving    process. 
 #endif
   Model1_skb->Model1_sk = Model1_sk;
   //cy: I'm not going to desctruct skb, so it's okay.
   //skb->destructor = skb_is_tcp_pure_ack(skb) ? __sock_wfree : tcp_wfree;
   Model1_skb_set_hash_from_sk(Model1_skb, Model1_sk); // if sk has sk_txhash, transfer it to skb
   Model1_atomic_add(Model1_skb->Model1_truesize, &Model1_sk->Model1_sk_wmem_alloc); //the bytes that have  already been written

   /* Build TCP header and checksum it. */
   Model1_th = (struct Model1_tcphdr *)Model1_skb->Model1_data;
   Model1_th->Model1_source = Model1_inet->Model1_inet_sport;
   Model1_th->Model1_dest = Model1_inet->Model1_sk.Model1___sk_common.Model1_skc_dport;
   // cy: remove htonl function right now.
   Model1_th->Model1_seq = Model1_htonl(Model1_tcb->Model1_seq); //((                                       __be32)(__u32)__builtin_bswap32((__u32)((tcb->seq))));
   Model1_th->Model1_ack_seq = Model1_htonl(Model1_tp->Model1_rcv_nxt); //((                                __be32)(__u32)__builtin_bswap32((__u32)((tp->rcv_nxt))));
   // cy: not sure is it necessary..... 
 
   *(((Model1___be16 *)Model1_th) + 6) = Model1_htons(((Model1_tcp_header_size >> 2) << 12) | Model1_tcb->Model1_tcp_flags);
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
   Model1_tcb->Model1_ack_seq = Model1_ntohl(Model1_th->Model1_ack_seq);
 #endif
   Model1_th->Model1_check = 0;
   Model1_th->Model1_urg_ptr = 0;
 
 
 #if CY_ABSTRACT4 //tcp_urg_mode always false
 #else
   if ((Model1_tcp_urg_mode(Model1_tp) && Model1_before(Model1_tcb->Model1_seq, Model1_tp->Model1_snd_up))) {
    if (Model1_before(Model1_tp->Model1_snd_up, Model1_tcb->Model1_seq + 0x10000)) {
     //th->urg_ptr = (( __be16)(__u16)__builtin_bswap16((__u16)((tp->snd_up - tcb->seq))));
     Model1_th->Model1_urg_ptr = Model1_ntohs(Model1_tp->Model1_snd_up - Model1_tcb->Model1_seq);
     Model1_th->Model1_urg = 1;
    } else if (Model1_before(Model1_tp->Model1_snd_nxt, Model1_tcb->Model1_seq + 0xFFFF)) {
     //th->urg_ptr = (( __be16)(__u16)__builtin_bswap16((__u16)((0xFFFF))));
     Model1_th->Model1_urg_ptr = Model1_htons(0xFFFF);
     Model1_th->Model1_urg = 1;
    }
   }
 #endif
#if CY_ABSTRACT1
   //opts is empty anyway
 #else
   //tcp_options_write((__be32 *)(th + 1), tp, &opts);
 #endif
 
   ((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_skb)))->Model1_gso_type = Model1_sk->Model1_sk_gso_type;
   //cy: to make it easy, keep th->window = min(tp->rcv_wnd, 65535U so far.
 //#if !CY_ABSTRACT1
 //  th->window = htons(2); //3; //65535U;
 //#else
   if (!(Model1_tcb->Model1_tcp_flags & 0x02)) {//SYN: 0x02. It means tcp_flags don't have SYN flag
    //th->window = (( __be16)(__u16)_builtin_bswap16((__u16)((tcp_select_window(sk)))));
    Model1_th->Model1_window = Model1_htons(Model1_tcp_select_window(Model1_sk));
    // don't use ecn so far
    //tcp_ecn_send(sk, skb, th, tcp_header_size);
   } else {
 
   // RFC1323: The window in SYN & SYN/ACK segments is never scaled. 
    //th->window = (( __be16)(__u16)__builtin_bswap16((__u16)((({ typeof(tp->rcv_wnd) _min1 = (tp-          >rcv_wnd);             typeof(65535U) _min2 = (65535U); (void) (&_min1 == &_min2); _min1 < _min2 ?         _min1 : _min2; })))));
   // Model1_th->Model1_window = (Model1_ntohs((({ typeof(Model1_tp->Model1_rcv_wnd) Model1__min1 =         (Model1_tp->Model1_rcv_wnd);             typeof(65535U) Model1__min2 = (65535U); (void) (&Model1__min1 ==  &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; }))));
    Model1_th->Model1_window = (Model1_ntohs(Model1_tp->Model1_rcv_wnd < 65535U? Model1_tp->Model1_rcv_wnd: 65535U)); }
 //#endif
 
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
   Model1_icsk->Model1_icsk_af_ops->Model1_send_check(Model1_sk, Model1_skb);
 #endif
 
   if (Model1_tcb->Model1_tcp_flags & 0x10) //ACK: 0x10
    Model1_tcp_event_ack_sent(Model1_sk, Model1_tcp_skb_pcount(Model1_skb));
   if (Model1_skb->Model1_len != Model1_tcp_header_size) {
    Model1_tcp_event_data_sent(Model1_tp, Model1_sk);
    Model1_tp->Model1_data_segs_out += Model1_tcp_skb_pcount(Model1_skb);
   }
 
 #if !CY_ABSTRACT4
   if (Model1_before(Model1_tp->Model1_snd_nxt, Model1_tcb->Model1_end_seq) || Model1_tcb->Model1_seq ==    Model1_tcb->Model1_end_seq)
     ;
     //TCP_ADD_STATS(sock_net(sk), TCP_MIB_OUTSEGS, tcp_skb_pcount(skb));
 #endif
 
 // This part seems not important. It's strange that tcb will be cleaned up. So we remove the clean up      process first to see what will happen.
    Model1_tp->Model1_segs_out += Model1_tcp_skb_pcount(Model1_skb);
 
   ((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_skb)))->Model1_gso_segs =               Model1_tcp_skb_pcount(Model1_skb);
   ((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_skb)))->Model1_gso_size =               Model1_tcp_skb_mss(Model1_skb);
 
 
   Model1_skb->Model1_tstamp.Model1_tv64 = 0;
 
 #if !CY_ABSTRACT4
 //  memset(Model1_skb->Model1_cb, 0, max(sizeof(struct inet_skb_parm), sizeof(struct inet6_skb_parm)));
 //#else
   memset(Model1_skb->Model1_cb, 0, ({ typeof(sizeof(struct inet_skb_parm)) _max1 = (sizeof(struct          inet_skb_parm));                  typeof(sizeof(struct inet6_skb_parm)) _max2 = (sizeof(struct             inet6_skb_parm)); /*(void) (&_max1 == &_max2)*/; _max1 >    _max2 ? _max1 : _max2; })); /* Cleanup our     debris for IP stacks */
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


unsigned char *Model1_skb_push(struct Model1_sk_buff *Model1_skb, unsigned int Model1_len)
{
    //th = (struct tcphdr *)(&Skb[0])->data;
	Model1_skb->Model1_len  += Model1_len;
	Model1_skb->Model1_data -= Model1_len;
    //th = (struct tcphdr *)(&Skb[0])->data;
//	if (unlikely(skb->data<skb->head))
//		skb_under_panic(skb, len, __builtin_return_address(0));
	return Model1_skb->Model1_data;
}

Model1_u16 Model1_tcp_select_window(struct Model1_sock *Model1_sk)
{
  struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
  Model1_u32 Model1_old_win = Model1_tp->Model1_rcv_wnd;
  Model1_u32 Model1_cur_win = Model1_tcp_receive_window(Model1_tp);
  Model1_u32 Model1_new_win = Model1___tcp_select_window(Model1_sk);
 
  Model1_tp->Model1_rcv_wup = Model1_tp->Model1_rcv_nxt; //[CY] [TODO]
 
  if (Model1_new_win < Model1_cur_win) {
 
   if (Model1_new_win == 0)
	;//[CY] NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPWANTZEROWINDOWADV);
 
   Model1_new_win = ((((Model1_cur_win)) + ((typeof((Model1_cur_win)))((1 << Model1_tp->Model1_rx_opt.Model1_rcv_wscale)) - 1)) & ~((typeof((Model1_cur_win)))((1 << Model1_tp->Model1_rx_opt.Model1_rcv_wscale)) - 1));
  }
  Model1_tp->Model1_rcv_wnd = Model1_new_win;
  Model1_tp->Model1_rcv_wup = Model1_tp->Model1_rcv_nxt;

  if (!Model1_tp->Model1_rx_opt.Model1_rcv_wscale && Model1_sysctl_tcp_workaround_signed_windows)
   Model1_new_win = ({ typeof(Model1_new_win) Model1__min1 = (Model1_new_win); typeof(Model1_MAX_TCP_WINDOW) Model1__min2 = (Model1_MAX_TCP_WINDOW); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
  else
   Model1_new_win = ({ typeof(Model1_new_win) Model1__min1 = (Model1_new_win); typeof((65535U << Model1_tp->Model1_rx_opt.Model1_rcv_wscale)) Model1__min2 = ((65535U << Model1_tp->Model1_rx_opt.Model1_rcv_wscale)); (void) (&Model1__min1 ==       &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });

 
  Model1_new_win >>= Model1_tp->Model1_rx_opt.Model1_rcv_wscale;

  if (Model1_new_win == 0) {
   Model1_tp->Model1_pred_flags = 0;
   if (Model1_old_win)
	; // NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPTOZEROWINDOWADV);
 
  } else if (Model1_old_win == 0) {
	; // NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPFROMZEROWINDOWADV);
  }
  return Model1_new_win;
}

Model1_u32 Model1___tcp_select_window(struct Model1_sock *Model1_sk){

#if 0 //CY_ABSTRACT1 [TODO]
    // to make it easy, doesn't change the value
    struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
    return 5; //tp->rcv_wnd;
#else
 struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
  struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 
 
 
 
 
 
  int Model1_mss = Model1_icsk->Model1_icsk_ack.Model1_rcv_mss;
  int Model1_free_space = Model1_tcp_space(Model1_sk); //tcp_win_from_space(sk_rcvbuf - backlog.rmem_alloc) = sk_rcvbuf - backlog.rmem_alloc // the space avaialve in receive buffer
  int Model1_allowed_space = Model1_tcp_full_space(Model1_sk); //tcp_win_from_space(sk_rcvbuf) = sk_rcvbuf // the total space in socket's receive buffer
  int Model1_full_space = ({ int Model1___min1 = (Model1_tp->Model1_window_clamp); int Model1___min2 = (Model1_allowed_space); Model1___min1 < Model1___min2 ? Model1___min1: Model1___min2; });
  int Model1_window;
 
  if (Model1_mss > Model1_full_space)
   Model1_mss = Model1_full_space;
 
  if (Model1_free_space < (Model1_full_space >> 1)) { //over half sk_rcvbuf is taken, send delayed ack to slow down transmission
   Model1_icsk->Model1_icsk_ack.Model1_quick = 0;
 
   if (Model1_tcp_under_memory_pressure(Model1_sk))
    Model1_tp->Model1_rcv_ssthresh = ({ typeof(Model1_tp->Model1_rcv_ssthresh) Model1__min1 = (Model1_tp->Model1_rcv_ssthresh); typeof(4U * Model1_tp->Model1_advmss) Model1__min2 = (4U * Model1_tp->Model1_advmss); (void) (&Model1__min1 == &Model1__min2);      Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });

 
 
 
 
 
   Model1_free_space = ((Model1_free_space) & ~((__typeof__(Model1_free_space))((1 << Model1_tp->Model1_rx_opt.Model1_rcv_wscale)-1)));
   if (Model1_free_space < (Model1_allowed_space >> 4) || Model1_free_space < Model1_mss)
    return 0;
  }
  if (Model1_free_space > Model1_tp->Model1_rcv_ssthresh)
   Model1_free_space = Model1_tp->Model1_rcv_ssthresh;
 
  Model1_window = Model1_tp->Model1_rcv_wnd;
  if (Model1_tp->Model1_rx_opt.Model1_rcv_wscale) {
   Model1_window = Model1_free_space;
 
 
 
 
 
   if (((Model1_window >> Model1_tp->Model1_rx_opt.Model1_rcv_wscale) << Model1_tp->Model1_rx_opt.Model1_rcv_wscale) != Model1_window)
    Model1_window = (((Model1_window >> Model1_tp->Model1_rx_opt.Model1_rcv_wscale) + 1)
       << Model1_tp->Model1_rx_opt.Model1_rcv_wscale);
  } else {
   if (Model1_window <= Model1_free_space - Model1_mss || Model1_window > Model1_free_space)
    Model1_window = (Model1_free_space / Model1_mss) * Model1_mss;
   else if (Model1_mss == Model1_full_space &&
     Model1_free_space > Model1_window + (Model1_full_space >> 1))
    Model1_window = Model1_free_space;
  }
 
  return Model1_window;
#endif
}
 
void Model1_tcp_event_ack_sent(struct Model1_sock *Model1_sk, unsigned int Model1_pkts)
{
  Model1_tcp_dec_quickack_mode(Model1_sk, Model1_pkts);
  Model1_inet_csk_clear_xmit_timer(Model1_sk, 2);
}
 
void Model1_tcp_event_data_sent(struct Model1_tcp_sock *Model1_tp,
     struct Model1_sock *Model1_sk)
{
  struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
  const Model1_u32 Model1_K_now = ((__u32)(Model1_jiffies));
 
  if (Model1_tcp_packets_in_flight(Model1_tp) == 0)
   Model1_tcp_ca_event(Model1_sk, Model1_CA_EVENT_TX_START);
 
  Model1_tp->Model1_lsndtime = Model1_K_now;
 
 
 
 
  if ((Model1_u32)(Model1_K_now - Model1_icsk->Model1_icsk_ack.Model1_lrcvtime) < Model1_icsk->Model1_icsk_ack.Model1_ato){
   Model1_icsk->Model1_icsk_ack.Model1_pingpong = 1;
  }
}

//This function is generated based on tcp_v4_rcv, which updates skb before entering function tcp_rcv_established
void Model1_cy_tcp_v4_rcv(struct Model1_sk_buff *Model1_skb){
    const struct Model1_tcphdr *Model1_th;
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
    Model1_th = (const struct Model1_tcphdr *)Model1_skb->Model1_data;
#if CY_ABSTRACT1
    //iph = ip_hdr(skb);
    //memmove(&TCP_SKB_CB(skb)->header.h4, IPCB(skb), sizeof(struct inet_skb_parm));
    //barrier();
#endif
 
    ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq = Model1_ntohl(Model1_th->Model1_seq);
    ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq = (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq + Model1_th->Model1_syn + Model1_th->Model1_fin + Model1_skb->Model1_len - Model1_th->Model1_doff * 4);
    ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_ack_seq = Model1_ntohl(Model1_th->Model1_ack_seq);
    ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_tcp_flags = (((Model1_u_int8_t *)Model1_th)[13]);

    ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_tcp_tw_isn = 0;
#if CY_ABSTRACT1
    //tcb->ip_dsfield = ipv4_get_dsfield(iph) //we don't have ip fields
#endif
    ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked = 0;
}
/*
 *	Functions provided by ip.c
 */

int Model1_ip_build_and_send_pkt(struct Model1_sk_buff *Model1_skb, const struct Model1_sock *Model1_sk,
     Model1___be32 Model1_saddr, Model1___be32 Model1_daddr,
     struct Model1_ip_options_rcu *Model1_opt){
#if CY_ABSTRACT3
    if (Model1_Src_sk == true){
        Model1_Out_pkt = true;
    }
    //Modify 06/11/2018 Right now we only have one direction from Client or Attacker to Server
    //We assume Client won't send packet to Server so we ignore packets sent to Client
    else{
        Model1_Out_pkt = false;
    }
    return 0; //NET_XMIT_SUCCESS
#endif
}
//tcp_prot related
static int Model1_tcp_v4_init_sock(struct Model1_sock *Model1_sk){
    assert(0);
    return 0;
}
static struct Model1_timewait_sock_ops Model1_tcp_timewait_sock_ops = {
    //abstracted
};
void Model1_tcp_close(struct Model1_sock *Model1_sk, long Model1_timeout){
    assert(0);
}
int Model1_tcp_v4_connect(struct Model1_sock *Model1_sk, struct Model1_sockaddr *Model1_uaddr, int Model1_addr_len){
    assert(0);
    return 0;
}
int Model1_tcp_disconnect(struct Model1_sock *Model1_sk, int Model1_flags){
    assert(0);
    return 0;
}
struct Model1_sock *Model1_inet_csk_accept(struct Model1_sock *Model1_sk, int Model1_flags, int *err){
    assert(0);
    return NULL;
}
int Model1_tcp_ioctl(struct Model1_sock *Model1_sk, int Model1_cmd, unsigned long Model1_arg){
    assert(0);
    return 0;
}
void Model1_tcp_v4_destroy_sock(struct Model1_sock *Model1_sk){
    assert(0);
}
void Model1_tcp_shutdown(struct Model1_sock *Model1_sk, int Model1_how){
    assert(0);
}
int Model1_tcp_setsockopt(struct Model1_sock *Model1_sk, int Model1_level, int Model1_optname,
     char *Model1_optval, unsigned int Model1_optlen){
    assert(0);
    return 0;
}
int Model1_compat_tcp_getsockopt(struct Model1_sock *Model1_sk, int Model1_level, int Model1_optname,
     char *Model1_optval, int *Model1_optlen){
    assert(0);
    return 0;
}
int Model1_tcp_sendmsg(struct Model1_sock *Model1_sk, struct Model1_msghdr *Model1_msg, Model1_size_t Model1_size){
    assert(0);
    return 0;
}
int Model1_tcp_recvmsg(struct Model1_sock *Model1_sk, struct Model1_msghdr *Model1_msg, Model1_size_t Model1_len, int Model1_nonblock,
  int Model1_flags, int *Model1_addr_len){
    assert(0);
    return 0;
}
int Model1_tcp_sendpage(struct Model1_sock *Model1_sk, struct Model1_page *Model1_page, int Model1_offset, Model1_size_t Model1_size,
   int Model1_flags){
    assert(0);
    return 0;
}
int Model1_tcp_getsockopt(struct Model1_sock *Model1_sk, int Model1_level, int Model1_optname,
     char *Model1_optval, int *Model1_optlen){
    assert(0);
    return 0;
}
void Model1_tcp_release_cb(struct Model1_sock *Model1_sk){
    assert(0);
}
int Model1_inet_hash(struct Model1_sock *Model1_sk){
    assert(0);
    return 0;
}
void Model1_inet_unhash(struct Model1_sock *Model1_sk){
    assert(0);
}
int Model1_inet_csk_get_port(struct Model1_sock *Model1_sk, unsigned short Model1_snum){
    assert(0);
    return 0;
}
int Model1_tcp_abort(struct Model1_sock *Model1_sk, int err){
    assert(0);
    return 0;
}

int Model1_mod_timer_pending(struct Model1_timer_list *Model1_timer, unsigned long Model1_expires){
#if CY_ABSTRACT2
    //since the time is fixed in our model, there's no meaning to modify timer
    return 0;
#else
    assert(0);
    return 0;
#endif
}

static struct Model1_sock *Model1_sk_prot_alloc(struct Model1_proto *Model1_prot, Model1_gfp_t Model1_priority,
  int Model1_family)
{
 struct Model1_sock *Model1_sk;
 struct Model1_kmem_cache *Model1_slab;

#if CY_ABSTRACT3
 if (Model1_Src_sk)//not spoofed
  Model1_sk = Model1_cy_kmem_cache_alloc(3);
 else
  Model1_sk = Model1_cy_kmem_cache_alloc(4);
 if (!Model1_sk)
  return Model1_sk;
 if (Model1_priority & (( Model1_gfp_t)0x8000u)) {
  if (Model1_prot->Model1_clear_sk)
   Model1_prot->Model1_clear_sk(Model1_sk, Model1_prot->Model1_obj_size); //FP: This won't be visited anyway
  else
   Model1_sk_prot_clear_nulls(Model1_sk, Model1_prot->Model1_obj_size);
 }
#else
 Model1_slab = Model1_prot->Model1_slab;
 if (Model1_slab != ((void *)0)) {
  Model1_sk = Model1_kmem_cache_alloc(Model1_slab, Model1_priority & ~(( Model1_gfp_t)0x8000u));
  if (!Model1_sk)
   return Model1_sk;
  if (Model1_priority & (( Model1_gfp_t)0x8000u)) {
   if (Model1_prot->Model1_clear_sk)
    Model1_prot->Model1_clear_sk(Model1_sk, Model1_prot->Model1_obj_size);
   else
    Model1_sk_prot_clear_nulls(Model1_sk, Model1_prot->Model1_obj_size);
  }
 } else
  Model1_sk = Model1_kmalloc(Model1_prot->Model1_obj_size, Model1_priority);
#endif

 if (Model1_sk != ((void *)0)) {
  do { } while (0);

  if (Model1_security_sk_alloc(Model1_sk, Model1_family, Model1_priority))
   goto Model1_out_free;

  if (!Model1_try_module_get(Model1_prot->Model1_owner))
   goto Model1_out_free_sec;
  Model1_sk_tx_queue_clear(Model1_sk);
 }

 return Model1_sk;

Model1_out_free_sec:
 Model1_security_sk_free(Model1_sk);
Model1_out_free:
 if (Model1_slab != ((void *)0))
  Model1_kmem_cache_free(Model1_slab, Model1_sk);
 else
  Model1_kfree(Model1_sk);
 return ((void *)0);
}

struct Model1_proto Model1_tcp_prot = {
 .Model1_name = "TCP",
 .Model1_owner = ((struct Model1_module *)0),
 .Model1_close = Model1_tcp_close,
 .Model1_connect = Model1_tcp_v4_connect,
 .Model1_disconnect = Model1_tcp_disconnect,
 .Model1_accept = Model1_inet_csk_accept,
 .Model1_ioctl = Model1_tcp_ioctl,
 .Model1_init = Model1_tcp_v4_init_sock,
 .Model1_destroy = Model1_tcp_v4_destroy_sock,
 .Model1_shutdown = Model1_tcp_shutdown,
 .Model1_setsockopt = Model1_tcp_setsockopt,
 .Model1_getsockopt = Model1_tcp_getsockopt,
 .Model1_recvmsg = Model1_tcp_recvmsg,
 .Model1_sendmsg = Model1_tcp_sendmsg,
 .Model1_sendpage = Model1_tcp_sendpage,
 .Model1_backlog_rcv = Model1_tcp_v4_do_rcv,
 .Model1_release_cb = Model1_tcp_release_cb,
 .Model1_hash = Model1_inet_hash,
 .Model1_unhash = Model1_inet_unhash,
 .Model1_get_port = Model1_inet_csk_get_port,
 .Model1_enter_memory_pressure = Model1_tcp_enter_memory_pressure,
 .Model1_stream_memory_free = Model1_tcp_stream_memory_free,
 .Model1_sockets_allocated = &Model1_tcp_sockets_allocated,
 .Model1_orphan_count = &Model1_tcp_orphan_count,
 .Model1_memory_allocated = &Model1_tcp_memory_allocated,
 .Model1_memory_pressure = &Model1_tcp_memory_pressure,
 .Model1_sysctl_mem = Model1_sysctl_tcp_mem,
 .Model1_sysctl_wmem = Model1_sysctl_tcp_wmem,
 .Model1_sysctl_rmem = Model1_sysctl_tcp_rmem,
 .Model1_max_header = (128 + 32),
 .Model1_obj_size = sizeof(struct Model1_tcp_sock),
 .Model1_slab_flags = 0x00080000UL,
 .Model1_twsk_prot = &Model1_tcp_timewait_sock_ops,
 .Model1_rsk_prot = &Model1_tcp_request_sock_ops,
 .Model1_h.Model1_hashinfo = &Model1_tcp_hashinfo,
 .Model1_no_autobind = true,




 .Model1_diag_destroy = Model1_tcp_abort,
};
/*
	.Model1_enter_memory_pressure	= Model1_tcp_enter_memory_pressure,
	.Model1_sockets_allocated	= &Model1_tcp_sockets_allocated,
	.Model1_orphan_count		= &Model1_tcp_orphan_count,
	.Model1_memory_allocated	= &Model1_tcp_memory_allocated,
	.Model1_memory_pressure	= &Model1_tcp_memory_pressure,
	.Model1_sysctl_mem		= Model1_sysctl_tcp_mem,
	.Model1_sysctl_wmem		= Model1_sysctl_tcp_wmem,
	.Model1_sysctl_rmem		= Model1_sysctl_tcp_rmem,
*/

//Inside this file, they are functions introduced with defconfig, including IPSEC, etc
struct Model1_static_key Model1_memalloc_socks;

int Model1_security_inet_conn_request(struct Model1_sock *Model1_sk,
   struct Model1_sk_buff *Model1_skb, struct Model1_request_sock *Model1_req){
#if CY_ABSTRACT1 
    return 0; //in tinyconfig
#endif
}

void __attribute__((section(".spinlock.text"))) Model1__raw_spin_lock(Model1_raw_spinlock_t *Model1_lock){
#if CY_ABSTRACT1
    //TODO: assume no lock is used
#else
    assert(0);
#endif
}


int Model1_printk(const char *Model1_fmt, ...){
#if CY_ABSTRACT3
    //print a kernel message into kernel log
    //This printk is for debug purpose, therefore we ignore them in this model
#endif
    return 0;
}

void Model1_security_inet_conn_established(struct Model1_sock *Model1_sk,
   struct Model1_sk_buff *Model1_skb){
    assert(0);
    return;
}

void Model1_nf_conntrack_destroy(struct Model1_nf_conntrack *Model1_nfct){
    assert(0);
    return;
}

void Model1___compiletime_assert_17(void){
    assert(0);
    return;
}

/* START OF tcp_input.c */

int Model1_sysctl_tcp_timestamps __attribute__((__section__(".data..read_mostly"))) = 1;
int Model1_sysctl_tcp_window_scaling __attribute__((__section__(".data..read_mostly"))) = 1;
int Model1_sysctl_tcp_sack __attribute__((__section__(".data..read_mostly"))) = 1;
int Model1_sysctl_tcp_fack __attribute__((__section__(".data..read_mostly"))) = 1;
int Model1_sysctl_tcp_max_reordering __attribute__((__section__(".data..read_mostly"))) = 300;
int Model1_sysctl_tcp_dsack __attribute__((__section__(".data..read_mostly"))) = 1;
int Model1_sysctl_tcp_app_win __attribute__((__section__(".data..read_mostly"))) = 31;
int Model1_sysctl_tcp_adv_win_scale __attribute__((__section__(".data..read_mostly"))) = 1;
                                       ;

/* rfc5961 challenge ack rate limiting */
int Model1_sysctl_tcp_challenge_ack_limit = 1000;

int Model1_sysctl_tcp_stdurg __attribute__((__section__(".data..read_mostly")));
int Model1_sysctl_tcp_rfc1337 __attribute__((__section__(".data..read_mostly")));
int Model1_sysctl_tcp_max_orphans __attribute__((__section__(".data..read_mostly"))) = 8192;
int Model1_sysctl_tcp_frto __attribute__((__section__(".data..read_mostly"))) = 2;
int Model1_sysctl_tcp_min_rtt_wlen __attribute__((__section__(".data..read_mostly"))) = 300;

int Model1_sysctl_tcp_thin_dupack __attribute__((__section__(".data..read_mostly")));

int Model1_sysctl_tcp_moderate_rcvbuf __attribute__((__section__(".data..read_mostly"))) = 1;
int Model1_sysctl_tcp_early_retrans __attribute__((__section__(".data..read_mostly"))) = 3;
int Model1_sysctl_tcp_invalid_ratelimit __attribute__((__section__(".data..read_mostly"))) = 1000/2;
/* Adapt the MSS value used to make delayed ack decision to the
 * real world.
 */
static void Model1_tcp_measure_rcv_mss(struct Model1_sock *Model1_sk, const struct Model1_sk_buff *Model1_skb)
{
 struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
 const unsigned int Model1_lss = Model1_icsk->Model1_icsk_ack.Model1_last_seg_size;
 unsigned int Model1_len;

 Model1_icsk->Model1_icsk_ack.Model1_last_seg_size = 0;

 /* skb->len may jitter because of SACKs, even if peer
	 * sends good full-sized frames.
	 */
 Model1_len = ((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_skb)))->Model1_gso_size ? : Model1_skb->Model1_len;
 if (Model1_len >= Model1_icsk->Model1_icsk_ack.Model1_rcv_mss) {
  Model1_icsk->Model1_icsk_ack.Model1_rcv_mss = Model1_len;
 } else {
  /* Otherwise, we make more careful check taking into account,
		 * that SACKs block is variable.
		 *
		 * "len" is invariant segment length, including TCP header.
		 */
  Model1_len += Model1_skb->Model1_data - Model1_skb_transport_header(Model1_skb);
  if (Model1_len >= 536U + sizeof(struct Model1_tcphdr) ||
      /* If PSH is not set, packet should be
		     * full sized, provided peer TCP is not badly broken.
		     * This observation (if it is correct 8)) allows
		     * to handle super-low mtu links fairly.
		     */
      (Model1_len >= 88U + sizeof(struct Model1_tcphdr) &&
       !(( ((union Model1_tcp_word_hdr *)(Model1_tcp_hdr(Model1_skb)))->Model1_words [3]) & (Model1_TCP_FLAG_FIN|Model1_TCP_FLAG_URG|Model1_TCP_FLAG_SYN|Model1_TCP_FLAG_PSH)))) {
   /* Subtract also invariant (if peer is RFC compliant),
			 * tcp header plus fixed timestamp option length.
			 * Resulting "len" is MSS free of SACK jitter.
			 */
   Model1_len -= Model1_tcp_sk(Model1_sk)->Model1_tcp_header_len;
   Model1_icsk->Model1_icsk_ack.Model1_last_seg_size = Model1_len;
   if (Model1_len == Model1_lss) {
    Model1_icsk->Model1_icsk_ack.Model1_rcv_mss = Model1_len;
    return;
   }
  }
  if (Model1_icsk->Model1_icsk_ack.Model1_pending & Model1_ICSK_ACK_PUSHED)
   Model1_icsk->Model1_icsk_ack.Model1_pending |= Model1_ICSK_ACK_PUSHED2;
  Model1_icsk->Model1_icsk_ack.Model1_pending |= Model1_ICSK_ACK_PUSHED;
 }
}

static void Model1_tcp_incr_quickack(struct Model1_sock *Model1_sk)
{
 struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
 unsigned int Model1_quickacks = Model1_tcp_sk(Model1_sk)->Model1_rcv_wnd / (2 * Model1_icsk->Model1_icsk_ack.Model1_rcv_mss);

 if (Model1_quickacks == 0)
  Model1_quickacks = 2;
 if (Model1_quickacks > Model1_icsk->Model1_icsk_ack.Model1_quick)
  Model1_icsk->Model1_icsk_ack.Model1_quick = ({ typeof(Model1_quickacks) Model1__min1 = (Model1_quickacks); typeof(16U) Model1__min2 = (16U); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
}

static void Model1_tcp_enter_quickack_mode(struct Model1_sock *Model1_sk)
{
 struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
 Model1_tcp_incr_quickack(Model1_sk);
 Model1_icsk->Model1_icsk_ack.Model1_pingpong = 0;
#if !CY_ABSTRACT2
 Model1_icsk->Model1_icsk_ack.Model1_ato = ((unsigned)(1000/25));
#endif
}

/* Send ACKs quickly, if "quick" count is not exhausted
 * and the session is not interactive.
 */

static bool Model1_tcp_in_quickack_mode(struct Model1_sock *Model1_sk)
{
 const struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
 const struct Model1_dst_entry *Model1_dst = Model1___sk_dst_get(Model1_sk);

 return (Model1_dst && Model1_dst_metric(Model1_dst, Model1_RTAX_QUICKACK)) ||
  (Model1_icsk->Model1_icsk_ack.Model1_quick && !Model1_icsk->Model1_icsk_ack.Model1_pingpong);
}

static void Model1_tcp_ecn_queue_cwr(struct Model1_tcp_sock *Model1_tp)
{
 if (Model1_tp->Model1_ecn_flags & 1)
  Model1_tp->Model1_ecn_flags |= 2;
}

static void Model1_tcp_ecn_accept_cwr(struct Model1_tcp_sock *Model1_tp, const struct Model1_sk_buff *Model1_skb)
{
 if (Model1_tcp_hdr(Model1_skb)->Model1_cwr)
  Model1_tp->Model1_ecn_flags &= ~4;
}

static void Model1_tcp_ecn_withdraw_cwr(struct Model1_tcp_sock *Model1_tp)
{
 Model1_tp->Model1_ecn_flags &= ~4;
}

static void Model1___tcp_ecn_check_ce(struct Model1_tcp_sock *Model1_tp, const struct Model1_sk_buff *Model1_skb)
{
 switch (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_ip_dsfield & Model1_INET_ECN_MASK) {
 case Model1_INET_ECN_NOT_ECT:
  /* Funny extension: if ECT is not set on a segment,
		 * and we already seen ECT on a previous segment,
		 * it is probably a retransmit.
		 */
  if (Model1_tp->Model1_ecn_flags & 8)
   Model1_tcp_enter_quickack_mode((struct Model1_sock *)Model1_tp);
  break;
 case Model1_INET_ECN_CE:
  if (Model1_tcp_ca_needs_ecn((struct Model1_sock *)Model1_tp))
   Model1_tcp_ca_event((struct Model1_sock *)Model1_tp, Model1_CA_EVENT_ECN_IS_CE);

  if (!(Model1_tp->Model1_ecn_flags & 4)) {
   /* Better not delay acks, sender can have a very low cwnd */
   Model1_tcp_enter_quickack_mode((struct Model1_sock *)Model1_tp);
   Model1_tp->Model1_ecn_flags |= 4;
  }
  Model1_tp->Model1_ecn_flags |= 8;
  break;
 default:
  if (Model1_tcp_ca_needs_ecn((struct Model1_sock *)Model1_tp))
   Model1_tcp_ca_event((struct Model1_sock *)Model1_tp, Model1_CA_EVENT_ECN_NO_CE);
  Model1_tp->Model1_ecn_flags |= 8;
  break;
 }
}

static void Model1_tcp_ecn_check_ce(struct Model1_tcp_sock *Model1_tp, const struct Model1_sk_buff *Model1_skb)
{
#if !CY_ABSTRACT1
 if (Model1_tp->Model1_ecn_flags & 1)
  Model1___tcp_ecn_check_ce(Model1_tp, Model1_skb);
#endif
}

static void Model1_tcp_ecn_rcv_synack(struct Model1_tcp_sock *Model1_tp, const struct Model1_tcphdr *Model1_th)
{
 if ((Model1_tp->Model1_ecn_flags & 1) && (!Model1_th->Model1_ece || Model1_th->Model1_cwr))
  Model1_tp->Model1_ecn_flags &= ~1;
}

static void Model1_tcp_ecn_rcv_syn(struct Model1_tcp_sock *Model1_tp, const struct Model1_tcphdr *Model1_th)
{
 if ((Model1_tp->Model1_ecn_flags & 1) && (!Model1_th->Model1_ece || !Model1_th->Model1_cwr))
  Model1_tp->Model1_ecn_flags &= ~1;
}

static bool Model1_tcp_ecn_rcv_ecn_echo(const struct Model1_tcp_sock *Model1_tp, const struct Model1_tcphdr *Model1_th)
{
 if (Model1_th->Model1_ece && !Model1_th->Model1_syn && (Model1_tp->Model1_ecn_flags & 1))
  return true;
 return false;
}

/* Buffer size and advertised window tuning.
 *
 * 1. Tuning sk->sk_sndbuf, when connection enters established state.
 */

static void Model1_tcp_sndbuf_expand(struct Model1_sock *Model1_sk)
{
 const struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 int Model1_sndmem, Model1_per_mss;
 Model1_u32 Model1_nr_segs;

 /* Worst case is non GSO/TSO : each frame consumes one skb
	 * and skb->head is kmalloced using power of two area of memory
	 */
 Model1_per_mss = ({ Model1_u32 Model1___max1 = (Model1_tp->Model1_rx_opt.Model1_mss_clamp); Model1_u32 Model1___max2 = (Model1_tp->Model1_mss_cache); Model1___max1 > Model1___max2 ? Model1___max1: Model1___max2; }) +
    (128 + 32) +
    ((((sizeof(struct Model1_skb_shared_info))) + ((typeof((sizeof(struct Model1_skb_shared_info))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model1_skb_shared_info))))(((1 << (6)))) - 1));

 Model1_per_mss = ( __builtin_constant_p(Model1_per_mss) ? ( (Model1_per_mss == 1) ? 1 : (1UL << (( __builtin_constant_p((Model1_per_mss) - 1) ? ( ((Model1_per_mss) - 1) < 1 ? Model1_____ilog2_NaN() : ((Model1_per_mss) - 1) & (1ULL << 63) ? 63 : ((Model1_per_mss) - 1) & (1ULL << 62) ? 62 : ((Model1_per_mss) - 1) & (1ULL << 61) ? 61 : ((Model1_per_mss) - 1) & (1ULL << 60) ? 60 : ((Model1_per_mss) - 1) & (1ULL << 59) ? 59 : ((Model1_per_mss) - 1) & (1ULL << 58) ? 58 : ((Model1_per_mss) - 1) & (1ULL << 57) ? 57 : ((Model1_per_mss) - 1) & (1ULL << 56) ? 56 : ((Model1_per_mss) - 1) & (1ULL << 55) ? 55 : ((Model1_per_mss) - 1) & (1ULL << 54) ? 54 : ((Model1_per_mss) - 1) & (1ULL << 53) ? 53 : ((Model1_per_mss) - 1) & (1ULL << 52) ? 52 : ((Model1_per_mss) - 1) & (1ULL << 51) ? 51 : ((Model1_per_mss) - 1) & (1ULL << 50) ? 50 : ((Model1_per_mss) - 1) & (1ULL << 49) ? 49 : ((Model1_per_mss) - 1) & (1ULL << 48) ? 48 : ((Model1_per_mss) - 1) & (1ULL << 47) ? 47 : ((Model1_per_mss) - 1) & (1ULL << 46) ? 46 : ((Model1_per_mss) - 1) & (1ULL << 45) ? 45 : ((Model1_per_mss) - 1) & (1ULL << 44) ? 44 : ((Model1_per_mss) - 1) & (1ULL << 43) ? 43 : ((Model1_per_mss) - 1) & (1ULL << 42) ? 42 : ((Model1_per_mss) - 1) & (1ULL << 41) ? 41 : ((Model1_per_mss) - 1) & (1ULL << 40) ? 40 : ((Model1_per_mss) - 1) & (1ULL << 39) ? 39 : ((Model1_per_mss) - 1) & (1ULL << 38) ? 38 : ((Model1_per_mss) - 1) & (1ULL << 37) ? 37 : ((Model1_per_mss) - 1) & (1ULL << 36) ? 36 : ((Model1_per_mss) - 1) & (1ULL << 35) ? 35 : ((Model1_per_mss) - 1) & (1ULL << 34) ? 34 : ((Model1_per_mss) - 1) & (1ULL << 33) ? 33 : ((Model1_per_mss) - 1) & (1ULL << 32) ? 32 : ((Model1_per_mss) - 1) & (1ULL << 31) ? 31 : ((Model1_per_mss) - 1) & (1ULL << 30) ? 30 : ((Model1_per_mss) - 1) & (1ULL << 29) ? 29 : ((Model1_per_mss) - 1) & (1ULL << 28) ? 28 : ((Model1_per_mss) - 1) & (1ULL << 27) ? 27 : ((Model1_per_mss) - 1) & (1ULL << 26) ? 26 : ((Model1_per_mss) - 1) & (1ULL << 25) ? 25 : ((Model1_per_mss) - 1) & (1ULL << 24) ? 24 : ((Model1_per_mss) - 1) & (1ULL << 23) ? 23 : ((Model1_per_mss) - 1) & (1ULL << 22) ? 22 : ((Model1_per_mss) - 1) & (1ULL << 21) ? 21 : ((Model1_per_mss) - 1) & (1ULL << 20) ? 20 : ((Model1_per_mss) - 1) & (1ULL << 19) ? 19 : ((Model1_per_mss) - 1) & (1ULL << 18) ? 18 : ((Model1_per_mss) - 1) & (1ULL << 17) ? 17 : ((Model1_per_mss) - 1) & (1ULL << 16) ? 16 : ((Model1_per_mss) - 1) & (1ULL << 15) ? 15 : ((Model1_per_mss) - 1) & (1ULL << 14) ? 14 : ((Model1_per_mss) - 1) & (1ULL << 13) ? 13 : ((Model1_per_mss) - 1) & (1ULL << 12) ? 12 : ((Model1_per_mss) - 1) & (1ULL << 11) ? 11 : ((Model1_per_mss) - 1) & (1ULL << 10) ? 10 : ((Model1_per_mss) - 1) & (1ULL << 9) ? 9 : ((Model1_per_mss) - 1) & (1ULL << 8) ? 8 : ((Model1_per_mss) - 1) & (1ULL << 7) ? 7 : ((Model1_per_mss) - 1) & (1ULL << 6) ? 6 : ((Model1_per_mss) - 1) & (1ULL << 5) ? 5 : ((Model1_per_mss) - 1) & (1ULL << 4) ? 4 : ((Model1_per_mss) - 1) & (1ULL << 3) ? 3 : ((Model1_per_mss) - 1) & (1ULL << 2) ? 2 : ((Model1_per_mss) - 1) & (1ULL << 1) ? 1 : ((Model1_per_mss) - 1) & (1ULL << 0) ? 0 : Model1_____ilog2_NaN() ) : (sizeof((Model1_per_mss) - 1) <= 4) ? Model1___ilog2_u32((Model1_per_mss) - 1) : Model1___ilog2_u64((Model1_per_mss) - 1) ) + 1)) ) : Model1___roundup_pow_of_two(Model1_per_mss) ) +
    ((((sizeof(struct Model1_sk_buff))) + ((typeof((sizeof(struct Model1_sk_buff))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model1_sk_buff))))(((1 << (6)))) - 1));

 Model1_nr_segs = ({ Model1_u32 Model1___max1 = (10); Model1_u32 Model1___max2 = (Model1_tp->Model1_snd_cwnd); Model1___max1 > Model1___max2 ? Model1___max1: Model1___max2; });
 Model1_nr_segs = ({ Model1_u32 Model1___max1 = (Model1_nr_segs); Model1_u32 Model1___max2 = (Model1_tp->Model1_reordering + 1); Model1___max1 > Model1___max2 ? Model1___max1: Model1___max2; });

 /* Fast Recovery (RFC 5681 3.2) :
	 * Cubic needs 1.7 factor, rounded to 2 to include
	 * extra cushion (application might react slowly to POLLOUT)
	 */
 Model1_sndmem = 2 * Model1_nr_segs * Model1_per_mss;

 if (Model1_sk->Model1_sk_sndbuf < Model1_sndmem)
  Model1_sk->Model1_sk_sndbuf = ({ typeof(Model1_sndmem) Model1__min1 = (Model1_sndmem); typeof(Model1_sysctl_tcp_wmem[2]) Model1__min2 = (Model1_sysctl_tcp_wmem[2]); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
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
static int Model1___tcp_grow_window(const struct Model1_sock *Model1_sk, const struct Model1_sk_buff *Model1_skb)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 /* Optimize this! */
 int Model1_truesize = Model1_tcp_win_from_space(Model1_skb->Model1_truesize) >> 1;
 int Model1_window = Model1_tcp_win_from_space(Model1_sysctl_tcp_rmem[2]) >> 1;

 while (Model1_tp->Model1_rcv_ssthresh <= Model1_window) {
  if (Model1_truesize <= Model1_skb->Model1_len)
   return 2 * Model1_inet_csk(Model1_sk)->Model1_icsk_ack.Model1_rcv_mss;

  Model1_truesize >>= 1;
  Model1_window >>= 1;
 }
 return 0;
}

static void Model1_tcp_grow_window(struct Model1_sock *Model1_sk, const struct Model1_sk_buff *Model1_skb)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 /* Check #1 */
 if (Model1_tp->Model1_rcv_ssthresh < Model1_tp->Model1_window_clamp &&
     (int)Model1_tp->Model1_rcv_ssthresh < Model1_tcp_space(Model1_sk) &&
     !Model1_tcp_under_memory_pressure(Model1_sk)) {
  int Model1_incr;

  /* Check #2. Increase window, if skb with such overhead
		 * will fit to rcvbuf in future.
		 */
  if (Model1_tcp_win_from_space(Model1_skb->Model1_truesize) <= Model1_skb->Model1_len)
   Model1_incr = 2 * Model1_tp->Model1_advmss;
  else
   Model1_incr = Model1___tcp_grow_window(Model1_sk, Model1_skb);

  if (Model1_incr) {
   Model1_incr = ({ int Model1___max1 = (Model1_incr); int Model1___max2 = (2 * Model1_skb->Model1_len); Model1___max1 > Model1___max2 ? Model1___max1: Model1___max2; });
   Model1_tp->Model1_rcv_ssthresh = ({ typeof(Model1_tp->Model1_rcv_ssthresh + Model1_incr) Model1__min1 = (Model1_tp->Model1_rcv_ssthresh + Model1_incr); typeof(Model1_tp->Model1_window_clamp) Model1__min2 = (Model1_tp->Model1_window_clamp); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });

   Model1_inet_csk(Model1_sk)->Model1_icsk_ack.Model1_quick |= 1;
  }
 }
}

/* 3. Tuning rcvbuf, when connection enters established state. */
static void Model1_tcp_fixup_rcvbuf(struct Model1_sock *Model1_sk)
{
 Model1_u32 Model1_mss = Model1_tcp_sk(Model1_sk)->Model1_advmss;
 int Model1_rcvmem;

 Model1_rcvmem = 2 * ((Model1_mss + (128 + 32)) + ((((sizeof(struct Model1_sk_buff))) + ((typeof((sizeof(struct Model1_sk_buff))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model1_sk_buff))))(((1 << (6)))) - 1)) + ((((sizeof(struct Model1_skb_shared_info))) + ((typeof((sizeof(struct Model1_skb_shared_info))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model1_skb_shared_info))))(((1 << (6)))) - 1))) *
   Model1_tcp_default_init_rwnd(Model1_mss);

 /* Dynamic Right Sizing (DRS) has 2 to 3 RTT latency
	 * Allow enough cushion so that sender is not limited by our window
	 */
 if (Model1_sysctl_tcp_moderate_rcvbuf)
  Model1_rcvmem <<= 2;

 if (Model1_sk->Model1_sk_rcvbuf < Model1_rcvmem)
  Model1_sk->Model1_sk_rcvbuf = ({ typeof(Model1_rcvmem) Model1__min1 = (Model1_rcvmem); typeof(Model1_sysctl_tcp_rmem[2]) Model1__min2 = (Model1_sysctl_tcp_rmem[2]); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
}

/* 4. Try to fixup all. It is made immediately after connection enters
 *    established state.
 */
void Model1_tcp_init_buffer_space(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 int Model1_maxwin;

 if (!(Model1_sk->Model1_sk_userlocks & 2))
  Model1_tcp_fixup_rcvbuf(Model1_sk);
 if (!(Model1_sk->Model1_sk_userlocks & 1))
  Model1_tcp_sndbuf_expand(Model1_sk);

 Model1_tp->Model1_rcvq_space.Model1_space = Model1_tp->Model1_rcv_wnd;
 Model1_tp->Model1_rcvq_space.Model1_time = ((__u32)(Model1_jiffies));
 Model1_tp->Model1_rcvq_space.Model1_seq = Model1_tp->Model1_copied_seq;

 Model1_maxwin = Model1_tcp_full_space(Model1_sk);

 if (Model1_tp->Model1_window_clamp >= Model1_maxwin) {
  Model1_tp->Model1_window_clamp = Model1_maxwin;

  if (Model1_sysctl_tcp_app_win && Model1_maxwin > 4 * Model1_tp->Model1_advmss)
   Model1_tp->Model1_window_clamp = ({ typeof(Model1_maxwin - (Model1_maxwin >> Model1_sysctl_tcp_app_win)) Model1__max1 = (Model1_maxwin - (Model1_maxwin >> Model1_sysctl_tcp_app_win)); typeof(4 * Model1_tp->Model1_advmss) Model1__max2 = (4 * Model1_tp->Model1_advmss); (void) (&Model1__max1 == &Model1__max2); Model1__max1 > Model1__max2 ? Model1__max1 : Model1__max2; });


 }

 /* Force reservation of one segment. */
 if (Model1_sysctl_tcp_app_win &&
     Model1_tp->Model1_window_clamp > 2 * Model1_tp->Model1_advmss &&
     Model1_tp->Model1_window_clamp + Model1_tp->Model1_advmss > Model1_maxwin)
  Model1_tp->Model1_window_clamp = ({ typeof(2 * Model1_tp->Model1_advmss) Model1__max1 = (2 * Model1_tp->Model1_advmss); typeof(Model1_maxwin - Model1_tp->Model1_advmss) Model1__max2 = (Model1_maxwin - Model1_tp->Model1_advmss); (void) (&Model1__max1 == &Model1__max2); Model1__max1 > Model1__max2 ? Model1__max1 : Model1__max2; });

 Model1_tp->Model1_rcv_ssthresh = ({ typeof(Model1_tp->Model1_rcv_ssthresh) Model1__min1 = (Model1_tp->Model1_rcv_ssthresh); typeof(Model1_tp->Model1_window_clamp) Model1__min2 = (Model1_tp->Model1_window_clamp); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
 Model1_tp->Model1_snd_cwnd_stamp = ((__u32)(Model1_jiffies));
}

/* 5. Recalculate window clamp after socket hit its memory bounds. */
static void Model1_tcp_clamp_window(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);

 Model1_icsk->Model1_icsk_ack.Model1_quick = 0;

 if (Model1_sk->Model1_sk_rcvbuf < Model1_sysctl_tcp_rmem[2] &&
     !(Model1_sk->Model1_sk_userlocks & 2) &&
     !Model1_tcp_under_memory_pressure(Model1_sk) &&
     Model1_sk_memory_allocated(Model1_sk) < Model1_sk_prot_mem_limits(Model1_sk, 0)) {
  Model1_sk->Model1_sk_rcvbuf = ({ typeof(Model1_atomic_read(&Model1_sk->Model1_sk_backlog.Model1_rmem_alloc)) Model1__min1 = (Model1_atomic_read(&Model1_sk->Model1_sk_backlog.Model1_rmem_alloc)); typeof(Model1_sysctl_tcp_rmem[2]) Model1__min2 = (Model1_sysctl_tcp_rmem[2]); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });

 }
 if (Model1_atomic_read(&Model1_sk->Model1_sk_backlog.Model1_rmem_alloc) > Model1_sk->Model1_sk_rcvbuf)
  Model1_tp->Model1_rcv_ssthresh = ({ typeof(Model1_tp->Model1_window_clamp) Model1__min1 = (Model1_tp->Model1_window_clamp); typeof(2U * Model1_tp->Model1_advmss) Model1__min2 = (2U * Model1_tp->Model1_advmss); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
}

/* Initialize RCV_MSS value.
 * RCV_MSS is an our guess about MSS used by the peer.
 * We haven't any direct information about the MSS.
 * It's better to underestimate the RCV_MSS rather than overestimate.
 * Overestimations make us ACKing less frequently than needed.
 * Underestimations are more easy to detect and fix by tcp_measure_rcv_mss().
 */
void Model1_tcp_initialize_rcv_mss(struct Model1_sock *Model1_sk)
{
 const struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 unsigned int Model1_hint = ({ unsigned int Model1___min1 = (Model1_tp->Model1_advmss); unsigned int Model1___min2 = (Model1_tp->Model1_mss_cache); Model1___min1 < Model1___min2 ? Model1___min1: Model1___min2; });

 Model1_hint = ({ typeof(Model1_hint) Model1__min1 = (Model1_hint); typeof(Model1_tp->Model1_rcv_wnd / 2) Model1__min2 = (Model1_tp->Model1_rcv_wnd / 2); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
 Model1_hint = ({ typeof(Model1_hint) Model1__min1 = (Model1_hint); typeof(536U) Model1__min2 = (536U); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
 Model1_hint = ({ typeof(Model1_hint) Model1__max1 = (Model1_hint); typeof(88U) Model1__max2 = (88U); (void) (&Model1__max1 == &Model1__max2); Model1__max1 > Model1__max2 ? Model1__max1 : Model1__max2; });

 Model1_inet_csk(Model1_sk)->Model1_icsk_ack.Model1_rcv_mss = Model1_hint;
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
static void Model1_tcp_rcv_rtt_update(struct Model1_tcp_sock *Model1_tp, Model1_u32 Model1_sample, int Model1_win_dep)
{
 Model1_u32 Model1_new_sample = Model1_tp->Model1_rcv_rtt_est.Model1_rtt;
 long Model1_m = Model1_sample;

 if (Model1_m == 0)
  Model1_m = 1;

 if (Model1_new_sample != 0) {
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
  if (!Model1_win_dep) {
   Model1_m -= (Model1_new_sample >> 3);
   Model1_new_sample += Model1_m;
  } else {
   Model1_m <<= 3;
   if (Model1_m < Model1_new_sample)
    Model1_new_sample = Model1_m;
  }
 } else {
  /* No previous measure. */
  Model1_new_sample = Model1_m << 3;
 }

 if (Model1_tp->Model1_rcv_rtt_est.Model1_rtt != Model1_new_sample)
  Model1_tp->Model1_rcv_rtt_est.Model1_rtt = Model1_new_sample;
}

static inline __attribute__((no_instrument_function)) void Model1_tcp_rcv_rtt_measure(struct Model1_tcp_sock *Model1_tp)
{
#if CY_ABSTRACT2
#else
 if (Model1_tp->Model1_rcv_rtt_est.Model1_time == 0)
  goto Model1_new_measure;
 if (Model1_before(Model1_tp->Model1_rcv_nxt, Model1_tp->Model1_rcv_rtt_est.Model1_seq))
  return;
 Model1_tcp_rcv_rtt_update(Model1_tp, ((__u32)(Model1_jiffies)) - Model1_tp->Model1_rcv_rtt_est.Model1_time, 1);

Model1_new_measure:
 Model1_tp->Model1_rcv_rtt_est.Model1_seq = Model1_tp->Model1_rcv_nxt + Model1_tp->Model1_rcv_wnd;
 Model1_tp->Model1_rcv_rtt_est.Model1_time = ((__u32)(Model1_jiffies));
#endif
}

static inline __attribute__((no_instrument_function)) void Model1_tcp_rcv_rtt_measure_ts(struct Model1_sock *Model1_sk,
       const struct Model1_sk_buff *Model1_skb)
{
#if !CY_ABSTRACT1
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 if (Model1_tp->Model1_rx_opt.Model1_rcv_tsecr &&
     (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq -
      ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq >= Model1_inet_csk(Model1_sk)->Model1_icsk_ack.Model1_rcv_mss))
  Model1_tcp_rcv_rtt_update(Model1_tp, ((__u32)(Model1_jiffies)) - Model1_tp->Model1_rx_opt.Model1_rcv_tsecr, 0);
#endif
}

/*
 * This function should be called every time data is copied to user space.
 * It calculates the appropriate TCP receive buffer space.
 */
void Model1_tcp_rcv_space_adjust(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 int Model1_time;
 int Model1_copied;

 Model1_time = ((__u32)(Model1_jiffies)) - Model1_tp->Model1_rcvq_space.Model1_time;
 if (Model1_time < (Model1_tp->Model1_rcv_rtt_est.Model1_rtt >> 3) || Model1_tp->Model1_rcv_rtt_est.Model1_rtt == 0)
  return;

 /* Number of bytes copied to user in last RTT */
 Model1_copied = Model1_tp->Model1_copied_seq - Model1_tp->Model1_rcvq_space.Model1_seq;
 if (Model1_copied <= Model1_tp->Model1_rcvq_space.Model1_space)
  goto Model1_new_measure;

 /* A bit of theory :
	 * copied = bytes received in previous RTT, our base window
	 * To cope with packet losses, we need a 2x factor
	 * To cope with slow start, and sender growing its cwin by 100 %
	 * every RTT, we need a 4x factor, because the ACK we are sending
	 * now is for the next RTT, not the current one :
	 * <prev RTT . ><current RTT .. ><next RTT .... >
	 */

 if (Model1_sysctl_tcp_moderate_rcvbuf &&
     !(Model1_sk->Model1_sk_userlocks & 2)) {
  int Model1_rcvwin, Model1_rcvmem, Model1_rcvbuf;

  /* minimal window to cope with packet losses, assuming
		 * steady state. Add some cushion because of small variations.
		 */
  Model1_rcvwin = (Model1_copied << 1) + 16 * Model1_tp->Model1_advmss;

  /* If rate increased by 25%,
		 *	assume slow start, rcvwin = 3 * copied
		 * If rate increased by 50%,
		 *	assume sender can use 2x growth, rcvwin = 4 * copied
		 */
  if (Model1_copied >=
      Model1_tp->Model1_rcvq_space.Model1_space + (Model1_tp->Model1_rcvq_space.Model1_space >> 2)) {
   if (Model1_copied >=
       Model1_tp->Model1_rcvq_space.Model1_space + (Model1_tp->Model1_rcvq_space.Model1_space >> 1))
    Model1_rcvwin <<= 1;
   else
    Model1_rcvwin += (Model1_rcvwin >> 1);
  }

  Model1_rcvmem = ((Model1_tp->Model1_advmss + (128 + 32)) + ((((sizeof(struct Model1_sk_buff))) + ((typeof((sizeof(struct Model1_sk_buff))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model1_sk_buff))))(((1 << (6)))) - 1)) + ((((sizeof(struct Model1_skb_shared_info))) + ((typeof((sizeof(struct Model1_skb_shared_info))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model1_skb_shared_info))))(((1 << (6)))) - 1)));
  while (Model1_tcp_win_from_space(Model1_rcvmem) < Model1_tp->Model1_advmss)
   Model1_rcvmem += 128;

  Model1_rcvbuf = ({ typeof(Model1_rcvwin / Model1_tp->Model1_advmss * Model1_rcvmem) Model1__min1 = (Model1_rcvwin / Model1_tp->Model1_advmss * Model1_rcvmem); typeof(Model1_sysctl_tcp_rmem[2]) Model1__min2 = (Model1_sysctl_tcp_rmem[2]); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
  if (Model1_rcvbuf > Model1_sk->Model1_sk_rcvbuf) {
   Model1_sk->Model1_sk_rcvbuf = Model1_rcvbuf;

   /* Make the window clamp follow along.  */
   Model1_tp->Model1_window_clamp = Model1_rcvwin;
  }
 }
 Model1_tp->Model1_rcvq_space.Model1_space = Model1_copied;

Model1_new_measure:
 Model1_tp->Model1_rcvq_space.Model1_seq = Model1_tp->Model1_copied_seq;
 Model1_tp->Model1_rcvq_space.Model1_time = ((__u32)(Model1_jiffies));
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
static void Model1_tcp_event_data_recv(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
 Model1_u32 Model1_now;

 Model1_inet_csk_schedule_ack(Model1_sk);

 Model1_tcp_measure_rcv_mss(Model1_sk, Model1_skb);

 Model1_tcp_rcv_rtt_measure(Model1_tp);

 Model1_now = ((__u32)(Model1_jiffies));

#if !CY_ABSTRACT2
 if (!Model1_icsk->Model1_icsk_ack.Model1_ato) {
  /* The _first_ data packet received, initialize
		 * delayed ACK engine.
		 */
  Model1_tcp_incr_quickack(Model1_sk);
  Model1_icsk->Model1_icsk_ack.Model1_ato = ((unsigned)(1000/25));
 } else {
  int Model1_m = Model1_now - Model1_icsk->Model1_icsk_ack.Model1_lrcvtime;

  if (Model1_m <= ((unsigned)(1000/25)) / 2) {
   /* The fastest case is the first. */
   Model1_icsk->Model1_icsk_ack.Model1_ato = (Model1_icsk->Model1_icsk_ack.Model1_ato >> 1) + ((unsigned)(1000/25)) / 2;
  } else if (Model1_m < Model1_icsk->Model1_icsk_ack.Model1_ato) {
   Model1_icsk->Model1_icsk_ack.Model1_ato = (Model1_icsk->Model1_icsk_ack.Model1_ato >> 1) + Model1_m;
   if (Model1_icsk->Model1_icsk_ack.Model1_ato > Model1_icsk->Model1_icsk_rto)
    Model1_icsk->Model1_icsk_ack.Model1_ato = Model1_icsk->Model1_icsk_rto;
  } else if (Model1_m > Model1_icsk->Model1_icsk_rto) {
   /* Too long gap. Apparently sender failed to
			 * restart window, so that we send ACKs quickly.
			 */
   Model1_tcp_incr_quickack(Model1_sk);
   Model1_sk_mem_reclaim(Model1_sk);
  }
 }
 Model1_icsk->Model1_icsk_ack.Model1_lrcvtime = Model1_now;
#endif
 Model1_tcp_ecn_check_ce(Model1_tp, Model1_skb);

 if (Model1_skb->Model1_len >= 128)
  Model1_tcp_grow_window(Model1_sk, Model1_skb);
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
static void Model1_tcp_rtt_estimator(struct Model1_sock *Model1_sk, long Model1_mrtt_us)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 long Model1_m = Model1_mrtt_us; /* RTT */
 Model1_u32 Model1_srtt = Model1_tp->Model1_srtt_us;

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
 if (Model1_srtt != 0) {
  Model1_m -= (Model1_srtt >> 3); /* m is now error in rtt est */
  Model1_srtt += Model1_m; /* rtt = 7/8 rtt + 1/8 new */
  if (Model1_m < 0) {
   Model1_m = -Model1_m; /* m is now abs(error) */
   Model1_m -= (Model1_tp->Model1_mdev_us >> 2); /* similar update on mdev */
   /* This is similar to one of Eifel findings.
			 * Eifel blocks mdev updates when rtt decreases.
			 * This solution is a bit different: we use finer gain
			 * for mdev in this case (alpha*beta).
			 * Like Eifel it also prevents growth of rto,
			 * but also it limits too fast rto decreases,
			 * happening in pure Eifel.
			 */
   if (Model1_m > 0)
    Model1_m >>= 3;
  } else {
   Model1_m -= (Model1_tp->Model1_mdev_us >> 2); /* similar update on mdev */
  }
  Model1_tp->Model1_mdev_us += Model1_m; /* mdev = 3/4 mdev + 1/4 new */
  if (Model1_tp->Model1_mdev_us > Model1_tp->Model1_mdev_max_us) {
   Model1_tp->Model1_mdev_max_us = Model1_tp->Model1_mdev_us;
   if (Model1_tp->Model1_mdev_max_us > Model1_tp->Model1_rttvar_us)
    Model1_tp->Model1_rttvar_us = Model1_tp->Model1_mdev_max_us;
  }
  if (Model1_before(Model1_tp->Model1_rtt_seq, Model1_tp->Model1_snd_una)) {
   if (Model1_tp->Model1_mdev_max_us < Model1_tp->Model1_rttvar_us)
    Model1_tp->Model1_rttvar_us -= (Model1_tp->Model1_rttvar_us - Model1_tp->Model1_mdev_max_us) >> 2;
   Model1_tp->Model1_rtt_seq = Model1_tp->Model1_snd_nxt;
   Model1_tp->Model1_mdev_max_us = Model1_tcp_rto_min_us(Model1_sk);
  }
 } else {
  /* no previous measure. */
  Model1_srtt = Model1_m << 3; /* take the measured time to be rtt */
  Model1_tp->Model1_mdev_us = Model1_m << 1; /* make sure rto = 3*rtt */
  Model1_tp->Model1_rttvar_us = ({ typeof(Model1_tp->Model1_mdev_us) Model1__max1 = (Model1_tp->Model1_mdev_us); typeof(Model1_tcp_rto_min_us(Model1_sk)) Model1__max2 = (Model1_tcp_rto_min_us(Model1_sk)); (void) (&Model1__max1 == &Model1__max2); Model1__max1 > Model1__max2 ? Model1__max1 : Model1__max2; });
  Model1_tp->Model1_mdev_max_us = Model1_tp->Model1_rttvar_us;
  Model1_tp->Model1_rtt_seq = Model1_tp->Model1_snd_nxt;
 }
 Model1_tp->Model1_srtt_us = ({ typeof(1U) Model1__max1 = (1U); typeof(Model1_srtt) Model1__max2 = (Model1_srtt); (void) (&Model1__max1 == &Model1__max2); Model1__max1 > Model1__max2 ? Model1__max1 : Model1__max2; });
}

/* Set the sk_pacing_rate to allow proper sizing of TSO packets.
 * Note: TCP stack does not yet implement pacing.
 * FQ packet scheduler can be used to implement cheap but effective
 * TCP pacing, to smooth the burst on large writes when packets
 * in flight is significantly lower than cwnd (or rwin)
 */
int Model1_sysctl_tcp_pacing_ss_ratio __attribute__((__section__(".data..read_mostly"))) = 200;
int Model1_sysctl_tcp_pacing_ca_ratio __attribute__((__section__(".data..read_mostly"))) = 120;

static void Model1_tcp_update_pacing_rate(struct Model1_sock *Model1_sk)
{
 const struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 Model1_u64 Model1_rate;

 /* set sk_pacing_rate to 200 % of current rate (mss * cwnd / srtt) */
 Model1_rate = (Model1_u64)Model1_tp->Model1_mss_cache * ((1000000L / 100) << 3);

 /* current rate is (cwnd * mss) / srtt
	 * In Slow Start [1], set sk_pacing_rate to 200 % the current rate.
	 * In Congestion Avoidance phase, set it to 120 % the current rate.
	 *
	 * [1] : Normal Slow Start condition is (tp->snd_cwnd < tp->snd_ssthresh)
	 *	 If snd_cwnd >= (tp->snd_ssthresh / 2), we are approaching
	 *	 end of slow start and should slow down.
	 */
 if (Model1_tp->Model1_snd_cwnd < Model1_tp->Model1_snd_ssthresh / 2)
  Model1_rate *= Model1_sysctl_tcp_pacing_ss_ratio;
 else
  Model1_rate *= Model1_sysctl_tcp_pacing_ca_ratio;

 Model1_rate *= ({ typeof(Model1_tp->Model1_snd_cwnd) Model1__max1 = (Model1_tp->Model1_snd_cwnd); typeof(Model1_tp->Model1_packets_out) Model1__max2 = (Model1_tp->Model1_packets_out); (void) (&Model1__max1 == &Model1__max2); Model1__max1 > Model1__max2 ? Model1__max1 : Model1__max2; });

 if (__builtin_expect(!!(Model1_tp->Model1_srtt_us), 1))
  ({ Model1_uint32_t Model1___base = (Model1_tp->Model1_srtt_us); Model1_uint32_t Model1___rem; Model1___rem = ((Model1_uint64_t)(Model1_rate)) % Model1___base; (Model1_rate) = ((Model1_uint64_t)(Model1_rate)) / Model1___base; Model1___rem; });

 /* ACCESS_ONCE() is needed because sch_fq fetches sk_pacing_rate
	 * without any lock. We want to make sure compiler wont store
	 * intermediate values in this location.
	 */
 (*({ __attribute__((unused)) typeof(Model1_sk->Model1_sk_pacing_rate) Model1___var = ( typeof(Model1_sk->Model1_sk_pacing_rate)) 0; (volatile typeof(Model1_sk->Model1_sk_pacing_rate) *)&(Model1_sk->Model1_sk_pacing_rate); })) = ({ Model1_u64 Model1___min1 = (Model1_rate); Model1_u64 Model1___min2 = (Model1_sk->Model1_sk_max_pacing_rate); Model1___min1 < Model1___min2 ? Model1___min1: Model1___min2; });

}

/* Calculate rto without backoff.  This is the second half of Van Jacobson's
 * routine referred to above.
 */
static void Model1_tcp_set_rto(struct Model1_sock *Model1_sk)
{
 const struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
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
 Model1_inet_csk(Model1_sk)->Model1_icsk_rto = Model1___tcp_set_rto(Model1_tp);

 /* 2. Fixups made earlier cannot be right.
	 *    If we do not estimate RTO correctly without them,
	 *    all the algo is pure shit and should be replaced
	 *    with correct one. It is exactly, which we pretend to do.
	 */

 /* NOTE: clamping at TCP_RTO_MIN is not required, current algo
	 * guarantees that rto is higher.
	 */
 Model1_tcp_bound_rto(Model1_sk);
}

__u32 Model1_tcp_init_cwnd(const struct Model1_tcp_sock *Model1_tp, const struct Model1_dst_entry *Model1_dst)
{
 __u32 Model1_cwnd = (Model1_dst ? Model1_dst_metric(Model1_dst, Model1_RTAX_INITCWND) : 0);

 if (!Model1_cwnd)
  Model1_cwnd = 10;
 return ({ __u32 Model1___min1 = (Model1_cwnd); __u32 Model1___min2 = (Model1_tp->Model1_snd_cwnd_clamp); Model1___min1 < Model1___min2 ? Model1___min1: Model1___min2; });
}

/*
 * Packet counting of FACK is based on in-order assumptions, therefore TCP
 * disables it when reordering is detected
 */
void Model1_tcp_disable_fack(struct Model1_tcp_sock *Model1_tp)
{
 /* RFC3517 uses different metric in lost marker => reset on change */
 if (Model1_tcp_is_fack(Model1_tp))
  Model1_tp->Model1_lost_skb_hint = ((void *)0);
 Model1_tp->Model1_rx_opt.Model1_sack_ok &= ~(1 << 1);
}

/* Take a notice that peer is sending D-SACKs */
static void Model1_tcp_dsack_seen(struct Model1_tcp_sock *Model1_tp)
{
 Model1_tp->Model1_rx_opt.Model1_sack_ok |= (1 << 2);
}

static void Model1_tcp_update_reordering(struct Model1_sock *Model1_sk, const int Model1_metric,
      const int Model1_ts)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 if (Model1_metric > Model1_tp->Model1_reordering) {
  int Model1_mib_idx;

  Model1_tp->Model1_reordering = ({ typeof(Model1_sysctl_tcp_max_reordering) Model1__min1 = (Model1_sysctl_tcp_max_reordering); typeof(Model1_metric) Model1__min2 = (Model1_metric); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });

  /* This exciting event is worth to be remembered. 8) */
  if (Model1_ts)
   Model1_mib_idx = Model1_LINUX_MIB_TCPTSREORDER;
  else if (Model1_tcp_is_reno(Model1_tp))
   Model1_mib_idx = Model1_LINUX_MIB_TCPRENOREORDER;
  else if (Model1_tcp_is_fack(Model1_tp))
   Model1_mib_idx = Model1_LINUX_MIB_TCPFACKREORDER;
  else
   Model1_mib_idx = Model1_LINUX_MIB_TCPSACKREORDER;

  (Model1_cy_linux_mib.Model1_mibs[Model1_mib_idx] += 1);
  Model1_tcp_disable_fack(Model1_tp);
 }

 if (Model1_metric > 0)
  Model1_tcp_disable_early_retrans(Model1_tp);
 Model1_tp->Model1_rack.Model1_reord = 1;
}

/* This must be called before lost_out is incremented */
static void Model1_tcp_verify_retransmit_hint(struct Model1_tcp_sock *Model1_tp, struct Model1_sk_buff *Model1_skb)
{
 if (!Model1_tp->Model1_retransmit_skb_hint ||
     Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq,
     ((struct Model1_tcp_skb_cb *)&((Model1_tp->Model1_retransmit_skb_hint)->Model1_cb[0]))->Model1_seq))
  Model1_tp->Model1_retransmit_skb_hint = Model1_skb;

 if (!Model1_tp->Model1_lost_out ||
     Model1_before(Model1_tp->Model1_retransmit_high, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq))
  Model1_tp->Model1_retransmit_high = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq;
}

static void Model1_tcp_skb_mark_lost(struct Model1_tcp_sock *Model1_tp, struct Model1_sk_buff *Model1_skb)
{
 if (!(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked & (0x04|0x01))) {
  Model1_tcp_verify_retransmit_hint(Model1_tp, Model1_skb);

  Model1_tp->Model1_lost_out += Model1_tcp_skb_pcount(Model1_skb);
  ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked |= 0x04;
 }
}

void Model1_tcp_skb_mark_lost_uncond_verify(struct Model1_tcp_sock *Model1_tp, struct Model1_sk_buff *Model1_skb)
{
 Model1_tcp_verify_retransmit_hint(Model1_tp, Model1_skb);

 if (!(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked & (0x04|0x01))) {
  Model1_tp->Model1_lost_out += Model1_tcp_skb_pcount(Model1_skb);
  ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked |= 0x04;
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
static bool Model1_tcp_is_sackblock_valid(struct Model1_tcp_sock *Model1_tp, bool Model1_is_dsack,
       Model1_u32 Model1_start_seq, Model1_u32 Model1_end_seq)
{
 /* Too far in future, or reversed (interpretation is ambiguous) */
 if (Model1_before(Model1_tp->Model1_snd_nxt, Model1_end_seq) || !Model1_before(Model1_start_seq, Model1_end_seq))
  return false;

 /* Nasty start_seq wrap-around check (see comments above) */
 if (!Model1_before(Model1_start_seq, Model1_tp->Model1_snd_nxt))
  return false;

 /* In outstanding window? ...This is valid exit for D-SACKs too.
	 * start_seq == snd_una is non-sensical (see comments above)
	 */
 if (Model1_before(Model1_tp->Model1_snd_una, Model1_start_seq))
  return true;

 if (!Model1_is_dsack || !Model1_tp->Model1_undo_marker)
  return false;

 /* ...Then it's D-SACK, and must reside below snd_una completely */
 if (Model1_before(Model1_tp->Model1_snd_una, Model1_end_seq))
  return false;

 if (!Model1_before(Model1_start_seq, Model1_tp->Model1_undo_marker))
  return true;

 /* Too old */
 if (!Model1_before(Model1_tp->Model1_undo_marker, Model1_end_seq))
  return false;

 /* Undo_marker boundary crossing (overestimates a lot). Known already:
	 *   start_seq < undo_marker and end_seq >= undo_marker.
	 */
 return !Model1_before(Model1_start_seq, Model1_end_seq - Model1_tp->Model1_max_window);
}

static bool Model1_tcp_check_dsack(struct Model1_sock *Model1_sk, const struct Model1_sk_buff *Model1_ack_skb,
       struct Model1_tcp_sack_block_wire *Model1_sp, int Model1_num_sacks,
       Model1_u32 Model1_prior_snd_una)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 Model1_u32 Model1_start_seq_0 = Model1_get_unaligned_be32(&Model1_sp[0].Model1_start_seq);
 Model1_u32 Model1_end_seq_0 = Model1_get_unaligned_be32(&Model1_sp[0].Model1_end_seq);
 bool Model1_dup_sack = false;

 if (Model1_before(Model1_start_seq_0, ((struct Model1_tcp_skb_cb *)&((Model1_ack_skb)->Model1_cb[0]))->Model1_ack_seq)) {
  Model1_dup_sack = true;
  Model1_tcp_dsack_seen(Model1_tp);
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPDSACKRECV] += 1);
 } else if (Model1_num_sacks > 1) {
  Model1_u32 Model1_end_seq_1 = Model1_get_unaligned_be32(&Model1_sp[1].Model1_end_seq);
  Model1_u32 Model1_start_seq_1 = Model1_get_unaligned_be32(&Model1_sp[1].Model1_start_seq);

  if (!Model1_before(Model1_end_seq_1, Model1_end_seq_0) &&
      !Model1_before(Model1_start_seq_0, Model1_start_seq_1)) {
   Model1_dup_sack = true;
   Model1_tcp_dsack_seen(Model1_tp);
   (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPDSACKOFORECV] += 1);

  }
 }

 /* D-SACK for already forgotten data... Do dumb counting. */
 if (Model1_dup_sack && Model1_tp->Model1_undo_marker && Model1_tp->Model1_undo_retrans > 0 &&
     !Model1_before(Model1_prior_snd_una, Model1_end_seq_0) &&
     Model1_before(Model1_tp->Model1_undo_marker, Model1_end_seq_0))
  Model1_tp->Model1_undo_retrans--;

 return Model1_dup_sack;
}

struct Model1_tcp_sacktag_state {
 int Model1_reord;
 int Model1_fack_count;
 /* Timestamps for earliest and latest never-retransmitted segment
	 * that was SACKed. RTO needs the earliest RTT to stay conservative,
	 * but congestion control should still get an accurate delay signal.
	 */
 struct Model1_skb_mstamp Model1_first_sackt;
 struct Model1_skb_mstamp Model1_last_sackt;
 int Model1_flag;
};

/* Check if skb is fully within the SACK block. In presence of GSO skbs,
 * the incoming SACK may not exactly match but we can find smaller MSS
 * aligned portion of it that matches. Therefore we might need to fragment
 * which may fail and creates some hassle (caller must handle error case
 * returns).
 *
 * FIXME: this could be merged to shift decision code
 */
static int Model1_tcp_match_skb_to_sack(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb,
      Model1_u32 Model1_start_seq, Model1_u32 Model1_end_seq)
{
 int err;
 bool Model1_in_sack;
 unsigned int Model1_pkt_len;
 unsigned int Model1_mss;

 Model1_in_sack = !Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, Model1_start_seq) &&
    !Model1_before(Model1_end_seq, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq);

 if (Model1_tcp_skb_pcount(Model1_skb) > 1 && !Model1_in_sack &&
     Model1_before(Model1_start_seq, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq)) {
  Model1_mss = Model1_tcp_skb_mss(Model1_skb);
  Model1_in_sack = !Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, Model1_start_seq);

  if (!Model1_in_sack) {
   Model1_pkt_len = Model1_start_seq - ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq;
   if (Model1_pkt_len < Model1_mss)
    Model1_pkt_len = Model1_mss;
  } else {
   Model1_pkt_len = Model1_end_seq - ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq;
   if (Model1_pkt_len < Model1_mss)
    return -22;
  }

  /* Round if necessary so that SACKs cover only full MSSes
		 * and/or the remaining small portion (if present)
		 */
  if (Model1_pkt_len > Model1_mss) {
   unsigned int Model1_new_len = (Model1_pkt_len / Model1_mss) * Model1_mss;
   if (!Model1_in_sack && Model1_new_len < Model1_pkt_len) {
    Model1_new_len += Model1_mss;
    if (Model1_new_len >= Model1_skb->Model1_len)
     return 0;
   }
   Model1_pkt_len = Model1_new_len;
  }
  err = Model1_tcp_fragment(Model1_sk, Model1_skb, Model1_pkt_len, Model1_mss, ((( Model1_gfp_t)0x20u)|(( Model1_gfp_t)0x80000u)|(( Model1_gfp_t)0x2000000u)));
  if (err < 0)
   return err;
 }

 return Model1_in_sack;
}

/* Mark the given newly-SACKed range as such, adjusting counters and hints. */
static Model1_u8 Model1_tcp_sacktag_one(struct Model1_sock *Model1_sk,
     struct Model1_tcp_sacktag_state *Model1_state, Model1_u8 Model1_sacked,
     Model1_u32 Model1_start_seq, Model1_u32 Model1_end_seq,
     int Model1_dup_sack, int Model1_pcount,
     const struct Model1_skb_mstamp *Model1_xmit_time)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 int Model1_fack_count = Model1_state->Model1_fack_count;

 /* Account D-SACK for retransmitted packet. */
 if (Model1_dup_sack && (Model1_sacked & (0x02|0x80| 0x10))) {
  if (Model1_tp->Model1_undo_marker && Model1_tp->Model1_undo_retrans > 0 &&
      Model1_before(Model1_tp->Model1_undo_marker, Model1_end_seq))
   Model1_tp->Model1_undo_retrans--;
  if (Model1_sacked & 0x01)
   Model1_state->Model1_reord = ({ typeof(Model1_fack_count) Model1__min1 = (Model1_fack_count); typeof(Model1_state->Model1_reord) Model1__min2 = (Model1_state->Model1_reord); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
 }

 /* Nothing to do; acked frame is about to be dropped (was ACKed). */
 if (!Model1_before(Model1_tp->Model1_snd_una, Model1_end_seq))
  return Model1_sacked;

 if (!(Model1_sacked & 0x01)) {
  Model1_tcp_rack_advance(Model1_tp, Model1_xmit_time, Model1_sacked);

  if (Model1_sacked & 0x02) {
   /* If the segment is not tagged as lost,
			 * we do not clear RETRANS, believing
			 * that retransmission is still in flight.
			 */
   if (Model1_sacked & 0x04) {
    Model1_sacked &= ~(0x04|0x02);
    Model1_tp->Model1_lost_out -= Model1_pcount;
    Model1_tp->Model1_retrans_out -= Model1_pcount;
   }
  } else {
   if (!(Model1_sacked & (0x02|0x80| 0x10))) {
    /* New sack for not retransmitted frame,
				 * which was in hole. It is reordering.
				 */
    if (Model1_before(Model1_start_seq,
        Model1_tcp_highest_sack_seq(Model1_tp)))
     Model1_state->Model1_reord = ({ typeof(Model1_fack_count) Model1__min1 = (Model1_fack_count); typeof(Model1_state->Model1_reord) Model1__min2 = (Model1_state->Model1_reord); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });

    if (!Model1_before(Model1_tp->Model1_high_seq, Model1_end_seq))
     Model1_state->Model1_flag |= 0x200;
    if (Model1_state->Model1_first_sackt.Model1_v64 == 0)
     Model1_state->Model1_first_sackt = *Model1_xmit_time;
    Model1_state->Model1_last_sackt = *Model1_xmit_time;
   }

   if (Model1_sacked & 0x04) {
    Model1_sacked &= ~0x04;
    Model1_tp->Model1_lost_out -= Model1_pcount;
   }
  }

  Model1_sacked |= 0x01;
  Model1_state->Model1_flag |= 0x20;
  Model1_tp->Model1_sacked_out += Model1_pcount;
  Model1_tp->Model1_delivered += Model1_pcount; /* Out-of-order packets delivered */

  Model1_fack_count += Model1_pcount;

  /* Lost marker hint past SACKed? Tweak RFC3517 cnt */
  if (!Model1_tcp_is_fack(Model1_tp) && Model1_tp->Model1_lost_skb_hint &&
      Model1_before(Model1_start_seq, ((struct Model1_tcp_skb_cb *)&((Model1_tp->Model1_lost_skb_hint)->Model1_cb[0]))->Model1_seq))
   Model1_tp->Model1_lost_cnt_hint += Model1_pcount;

  if (Model1_fack_count > Model1_tp->Model1_fackets_out)
   Model1_tp->Model1_fackets_out = Model1_fack_count;
 }

 /* D-SACK. We can detect redundant retransmission in S|R and plain R
	 * frames and clear it. undo_retrans is decreased above, L|R frames
	 * are accounted above as well.
	 */
 if (Model1_dup_sack && (Model1_sacked & 0x02)) {
  Model1_sacked &= ~0x02;
  Model1_tp->Model1_retrans_out -= Model1_pcount;
 }

 return Model1_sacked;
}

/* Shift newly-SACKed bytes from this skb to the immediately previous
 * already-SACKed sk_buff. Mark the newly-SACKed bytes as such.
 */
static bool Model1_tcp_shifted_skb(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb,
       struct Model1_tcp_sacktag_state *Model1_state,
       unsigned int Model1_pcount, int Model1_shifted, int Model1_mss,
       bool Model1_dup_sack)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_sk_buff *Model1_prev = Model1_tcp_write_queue_prev(Model1_sk, Model1_skb);
 Model1_u32 Model1_start_seq = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq; /* start of newly-SACKed */
 Model1_u32 Model1_end_seq = Model1_start_seq + Model1_shifted; /* end of newly-SACKed */

 do { if (!Model1_pcount) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);

 /* Adjust counters and hints for the newly sacked sequence
	 * range but discard the return value since prev is already
	 * marked. We must tag the range first because the seq
	 * advancement below implicitly advances
	 * tcp_highest_sack_seq() when skb is highest_sack.
	 */
 Model1_tcp_sacktag_one(Model1_sk, Model1_state, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked,
   Model1_start_seq, Model1_end_seq, Model1_dup_sack, Model1_pcount,
   &Model1_skb->Model1_skb_mstamp);

 if (Model1_skb == Model1_tp->Model1_lost_skb_hint)
  Model1_tp->Model1_lost_cnt_hint += Model1_pcount;

 ((struct Model1_tcp_skb_cb *)&((Model1_prev)->Model1_cb[0]))->Model1_end_seq += Model1_shifted;
 ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq += Model1_shifted;

 Model1_tcp_skb_pcount_add(Model1_prev, Model1_pcount);
 do { if (Model1_tcp_skb_pcount(Model1_skb) < Model1_pcount) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);
 Model1_tcp_skb_pcount_add(Model1_skb, -Model1_pcount);

 /* When we're adding to gso_segs == 1, gso_size will be zero,
	 * in theory this shouldn't be necessary but as long as DSACK
	 * code can come after this skb later on it's better to keep
	 * setting gso_size to something.
	 */
 if (!((struct Model1_tcp_skb_cb *)&((Model1_prev)->Model1_cb[0]))->Model1_tcp_gso_size)
  ((struct Model1_tcp_skb_cb *)&((Model1_prev)->Model1_cb[0]))->Model1_tcp_gso_size = Model1_mss;

 /* CHECKME: To clear or not to clear? Mimics normal skb currently */
 if (Model1_tcp_skb_pcount(Model1_skb) <= 1)
  ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_tcp_gso_size = 0;

 /* Difference in this won't matter, both ACKed by the same cumul. ACK */
 ((struct Model1_tcp_skb_cb *)&((Model1_prev)->Model1_cb[0]))->Model1_sacked |= (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked & 0x80);

 if (Model1_skb->Model1_len > 0) {
  do { if (!Model1_tcp_skb_pcount(Model1_skb)) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_SACKSHIFTED] += 1);
  return false;
 }

 /* Whole SKB was eaten :-) */

 if (Model1_skb == Model1_tp->Model1_retransmit_skb_hint)
  Model1_tp->Model1_retransmit_skb_hint = Model1_prev;
 if (Model1_skb == Model1_tp->Model1_lost_skb_hint) {
  Model1_tp->Model1_lost_skb_hint = Model1_prev;
  Model1_tp->Model1_lost_cnt_hint -= Model1_tcp_skb_pcount(Model1_prev);
 }

 ((struct Model1_tcp_skb_cb *)&((Model1_prev)->Model1_cb[0]))->Model1_tcp_flags |= ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_tcp_flags;
 ((struct Model1_tcp_skb_cb *)&((Model1_prev)->Model1_cb[0]))->Model1_eor = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_eor;
 if (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_tcp_flags & 0x01)
  ((struct Model1_tcp_skb_cb *)&((Model1_prev)->Model1_cb[0]))->Model1_end_seq++;

 if (Model1_skb == Model1_tcp_highest_sack(Model1_sk))
  Model1_tcp_advance_highest_sack(Model1_sk, Model1_skb);

 Model1_tcp_skb_collapse_tstamp(Model1_prev, Model1_skb);
 Model1_tcp_unlink_write_queue(Model1_skb, Model1_sk);
 Model1_sk_wmem_free_skb(Model1_sk, Model1_skb);

 (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_SACKMERGED] += 1);

 return true;
}

/* I wish gso_size would have a bit more sane initialization than
 * something-or-zero which complicates things
 */
static int Model1_tcp_skb_seglen(const struct Model1_sk_buff *Model1_skb)
{
 return Model1_tcp_skb_pcount(Model1_skb) == 1 ? Model1_skb->Model1_len : Model1_tcp_skb_mss(Model1_skb);
}

/* Shifting pages past head area doesn't work */
static int Model1_skb_can_shift(const struct Model1_sk_buff *Model1_skb)
{
 return !Model1_skb_headlen(Model1_skb) && Model1_skb_is_nonlinear(Model1_skb);
}

/* Try collapsing SACK blocks spanning across multiple skbs to a single
 * skb.
 */
static struct Model1_sk_buff *Model1_tcp_shift_skb_data(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb,
       struct Model1_tcp_sacktag_state *Model1_state,
       Model1_u32 Model1_start_seq, Model1_u32 Model1_end_seq,
       bool Model1_dup_sack)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_sk_buff *Model1_prev;
 int Model1_mss;
 int Model1_pcount = 0;
 int Model1_len;
 int Model1_in_sack;

 if (!Model1_sk_can_gso(Model1_sk))
  goto Model1_fallback;

 /* Normally R but no L won't result in plain S */
 if (!Model1_dup_sack &&
     (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked & (0x04|0x02)) == 0x02)
  goto Model1_fallback;
 if (!Model1_skb_can_shift(Model1_skb))
  goto Model1_fallback;
 /* This frame is about to be dropped (was ACKed). */
 if (!Model1_before(Model1_tp->Model1_snd_una, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq))
  goto Model1_fallback;

 /* Can only happen with delayed DSACK + discard craziness */
 if (__builtin_expect(!!(Model1_skb == Model1_tcp_write_queue_head(Model1_sk)), 0))
  goto Model1_fallback;
 Model1_prev = Model1_tcp_write_queue_prev(Model1_sk, Model1_skb);

 if ((((struct Model1_tcp_skb_cb *)&((Model1_prev)->Model1_cb[0]))->Model1_sacked & 0x07) != 0x01)
  goto Model1_fallback;

 if (!Model1_tcp_skb_can_collapse_to(Model1_prev))
  goto Model1_fallback;

 Model1_in_sack = !Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, Model1_start_seq) &&
    !Model1_before(Model1_end_seq, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq);

 if (Model1_in_sack) {
  Model1_len = Model1_skb->Model1_len;
  Model1_pcount = Model1_tcp_skb_pcount(Model1_skb);
  Model1_mss = Model1_tcp_skb_seglen(Model1_skb);

  /* TODO: Fix DSACKs to not fragment already SACKed and we can
		 * drop this restriction as unnecessary
		 */
  if (Model1_mss != Model1_tcp_skb_seglen(Model1_prev))
   goto Model1_fallback;
 } else {
  if (!Model1_before(Model1_start_seq, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq))
   goto noop;
  /* CHECKME: This is non-MSS split case only?, this will
		 * cause skipped skbs due to advancing loop btw, original
		 * has that feature too
		 */
  if (Model1_tcp_skb_pcount(Model1_skb) <= 1)
   goto noop;

  Model1_in_sack = !Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, Model1_start_seq);
  if (!Model1_in_sack) {
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
   goto Model1_fallback;
  }

  Model1_len = Model1_end_seq - ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq;
  do { if (Model1_len < 0) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);
  do { if (Model1_len > Model1_skb->Model1_len) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);

  /* MSS boundaries should be honoured or else pcount will
		 * severely break even though it makes things bit trickier.
		 * Optimize common case to avoid most of the divides
		 */
  Model1_mss = Model1_tcp_skb_mss(Model1_skb);

  /* TODO: Fix DSACKs to not fragment already SACKed and we can
		 * drop this restriction as unnecessary
		 */
  if (Model1_mss != Model1_tcp_skb_seglen(Model1_prev))
   goto Model1_fallback;

  if (Model1_len == Model1_mss) {
   Model1_pcount = 1;
  } else if (Model1_len < Model1_mss) {
   goto noop;
  } else {
   Model1_pcount = Model1_len / Model1_mss;
   Model1_len = Model1_pcount * Model1_mss;
  }
 }

 /* tcp_sacktag_one() won't SACK-tag ranges below snd_una */
 if (!Model1_before(Model1_tp->Model1_snd_una, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq + Model1_len))
  goto Model1_fallback;

 if (!Model1_skb_shift(Model1_prev, Model1_skb, Model1_len))
  goto Model1_fallback;
 if (!Model1_tcp_shifted_skb(Model1_sk, Model1_skb, Model1_state, Model1_pcount, Model1_len, Model1_mss, Model1_dup_sack))
  goto Model1_out;

 /* Hole filled allows collapsing with the next as well, this is very
	 * useful when hole on every nth skb pattern happens
	 */
 if (Model1_prev == Model1_tcp_write_queue_tail(Model1_sk))
  goto Model1_out;
 Model1_skb = Model1_tcp_write_queue_next(Model1_sk, Model1_prev);

 if (!Model1_skb_can_shift(Model1_skb) ||
     (Model1_skb == Model1_tcp_send_head(Model1_sk)) ||
     ((((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked & 0x07) != 0x01) ||
     (Model1_mss != Model1_tcp_skb_seglen(Model1_skb)))
  goto Model1_out;

 Model1_len = Model1_skb->Model1_len;
 if (Model1_skb_shift(Model1_prev, Model1_skb, Model1_len)) {
  Model1_pcount += Model1_tcp_skb_pcount(Model1_skb);
  Model1_tcp_shifted_skb(Model1_sk, Model1_skb, Model1_state, Model1_tcp_skb_pcount(Model1_skb), Model1_len, Model1_mss, 0);
 }

Model1_out:
 Model1_state->Model1_fack_count += Model1_pcount;
 return Model1_prev;

noop:
 return Model1_skb;

Model1_fallback:
 (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_SACKSHIFTFALLBACK] += 1);
 return ((void *)0);
}

static struct Model1_sk_buff *Model1_tcp_sacktag_walk(struct Model1_sk_buff *Model1_skb, struct Model1_sock *Model1_sk,
     struct Model1_tcp_sack_block *Model1_next_dup,
     struct Model1_tcp_sacktag_state *Model1_state,
     Model1_u32 Model1_start_seq, Model1_u32 Model1_end_seq,
     bool Model1_dup_sack_in)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_sk_buff *Model1_tmp;

 for (; Model1_skb != (struct Model1_sk_buff *)(&(Model1_sk)->Model1_sk_write_queue); Model1_skb = Model1_skb->Model1_next) {
  int Model1_in_sack = 0;
  bool Model1_dup_sack = Model1_dup_sack_in;

  if (Model1_skb == Model1_tcp_send_head(Model1_sk))
   break;

  /* queue is in-order => we can short-circuit the walk early */
  if (!Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, Model1_end_seq))
   break;

  if (Model1_next_dup &&
      Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, Model1_next_dup->Model1_end_seq)) {
   Model1_in_sack = Model1_tcp_match_skb_to_sack(Model1_sk, Model1_skb,
       Model1_next_dup->Model1_start_seq,
       Model1_next_dup->Model1_end_seq);
   if (Model1_in_sack > 0)
    Model1_dup_sack = true;
  }

  /* skb reference here is a bit tricky to get right, since
		 * shifting can eat and free both this skb and the next,
		 * so not even _safe variant of the loop is enough.
		 */
  if (Model1_in_sack <= 0) {
   Model1_tmp = Model1_tcp_shift_skb_data(Model1_sk, Model1_skb, Model1_state,
       Model1_start_seq, Model1_end_seq, Model1_dup_sack);
   if (Model1_tmp) {
    if (Model1_tmp != Model1_skb) {
     Model1_skb = Model1_tmp;
     continue;
    }

    Model1_in_sack = 0;
   } else {
    Model1_in_sack = Model1_tcp_match_skb_to_sack(Model1_sk, Model1_skb,
        Model1_start_seq,
        Model1_end_seq);
   }
  }

  if (__builtin_expect(!!(Model1_in_sack < 0), 0))
   break;

  if (Model1_in_sack) {
   ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked =
    Model1_tcp_sacktag_one(Model1_sk,
      Model1_state,
      ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked,
      ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq,
      ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq,
      Model1_dup_sack,
      Model1_tcp_skb_pcount(Model1_skb),
      &Model1_skb->Model1_skb_mstamp);

   if (!Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq,
        Model1_tcp_highest_sack_seq(Model1_tp)))
    Model1_tcp_advance_highest_sack(Model1_sk, Model1_skb);
  }

  Model1_state->Model1_fack_count += Model1_tcp_skb_pcount(Model1_skb);
 }
 return Model1_skb;
}

/* Avoid all extra work that is being done by sacktag while walking in
 * a normal way
 */
static struct Model1_sk_buff *Model1_tcp_sacktag_skip(struct Model1_sk_buff *Model1_skb, struct Model1_sock *Model1_sk,
     struct Model1_tcp_sacktag_state *Model1_state,
     Model1_u32 Model1_skip_to_seq)
{
 for (; Model1_skb != (struct Model1_sk_buff *)(&(Model1_sk)->Model1_sk_write_queue); Model1_skb = Model1_skb->Model1_next) {
  if (Model1_skb == Model1_tcp_send_head(Model1_sk))
   break;

  if (Model1_before(Model1_skip_to_seq, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq))
   break;

  Model1_state->Model1_fack_count += Model1_tcp_skb_pcount(Model1_skb);
 }
 return Model1_skb;
}

static struct Model1_sk_buff *Model1_tcp_maybe_skipping_dsack(struct Model1_sk_buff *Model1_skb,
      struct Model1_sock *Model1_sk,
      struct Model1_tcp_sack_block *Model1_next_dup,
      struct Model1_tcp_sacktag_state *Model1_state,
      Model1_u32 Model1_skip_to_seq)
{
 if (!Model1_next_dup)
  return Model1_skb;

 if (Model1_before(Model1_next_dup->Model1_start_seq, Model1_skip_to_seq)) {
  Model1_skb = Model1_tcp_sacktag_skip(Model1_skb, Model1_sk, Model1_state, Model1_next_dup->Model1_start_seq);
  Model1_skb = Model1_tcp_sacktag_walk(Model1_skb, Model1_sk, ((void *)0), Model1_state,
           Model1_next_dup->Model1_start_seq, Model1_next_dup->Model1_end_seq,
           1);
 }

 return Model1_skb;
}

static int Model1_tcp_sack_cache_ok(const struct Model1_tcp_sock *Model1_tp, const struct Model1_tcp_sack_block *Model1_cache)
{
 return Model1_cache < Model1_tp->Model1_recv_sack_cache + (sizeof(Model1_tp->Model1_recv_sack_cache) / sizeof((Model1_tp->Model1_recv_sack_cache)[0]) + (sizeof(struct { int:-!!(__builtin_types_compatible_p(typeof((Model1_tp->Model1_recv_sack_cache)), typeof(&(Model1_tp->Model1_recv_sack_cache)[0]))); })));
}

static int
Model1_tcp_sacktag_write_queue(struct Model1_sock *Model1_sk, const struct Model1_sk_buff *Model1_ack_skb,
   Model1_u32 Model1_prior_snd_una, struct Model1_tcp_sacktag_state *Model1_state)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 const unsigned char *Model1_ptr = (Model1_skb_transport_header(Model1_ack_skb) +
        ((struct Model1_tcp_skb_cb *)&((Model1_ack_skb)->Model1_cb[0]))->Model1_sacked);
 struct Model1_tcp_sack_block_wire *Model1_sp_wire = (struct Model1_tcp_sack_block_wire *)(Model1_ptr+2);
 struct Model1_tcp_sack_block Model1_sp[4];
 struct Model1_tcp_sack_block *Model1_cache;
 struct Model1_sk_buff *Model1_skb;
 int Model1_num_sacks = ({ typeof(4) Model1__min1 = (4); typeof((Model1_ptr[1] - 2) >> 3) Model1__min2 = ((Model1_ptr[1] - 2) >> 3); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
 int Model1_used_sacks;
 bool Model1_found_dup_sack = false;
 int Model1_i, Model1_j;
 int Model1_first_sack_index;

 Model1_state->Model1_flag = 0;
 Model1_state->Model1_reord = Model1_tp->Model1_packets_out;

 if (!Model1_tp->Model1_sacked_out) {
  if (({ int Model1___ret_warn_on = !!(Model1_tp->Model1_fackets_out); __builtin_expect(!!(Model1___ret_warn_on), 0); }))
   Model1_tp->Model1_fackets_out = 0;
  Model1_tcp_highest_sack_reset(Model1_sk);
 }

 Model1_found_dup_sack = Model1_tcp_check_dsack(Model1_sk, Model1_ack_skb, Model1_sp_wire,
      Model1_num_sacks, Model1_prior_snd_una);
 if (Model1_found_dup_sack)
  Model1_state->Model1_flag |= 0x800;

 /* Eliminate too old ACKs, but take into
	 * account more or less fresh ones, they can
	 * contain valid SACK info.
	 */
 if (Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_ack_skb)->Model1_cb[0]))->Model1_ack_seq, Model1_prior_snd_una - Model1_tp->Model1_max_window))
  return 0;

 if (!Model1_tp->Model1_packets_out)
  goto Model1_out;

 Model1_used_sacks = 0;
 Model1_first_sack_index = 0;
 for (Model1_i = 0; Model1_i < Model1_num_sacks; Model1_i++) {
  bool Model1_dup_sack = !Model1_i && Model1_found_dup_sack;

  Model1_sp[Model1_used_sacks].Model1_start_seq = Model1_get_unaligned_be32(&Model1_sp_wire[Model1_i].Model1_start_seq);
  Model1_sp[Model1_used_sacks].Model1_end_seq = Model1_get_unaligned_be32(&Model1_sp_wire[Model1_i].Model1_end_seq);

  if (!Model1_tcp_is_sackblock_valid(Model1_tp, Model1_dup_sack,
         Model1_sp[Model1_used_sacks].Model1_start_seq,
         Model1_sp[Model1_used_sacks].Model1_end_seq)) {
   int Model1_mib_idx;

   if (Model1_dup_sack) {
    if (!Model1_tp->Model1_undo_marker)
     Model1_mib_idx = Model1_LINUX_MIB_TCPDSACKIGNOREDNOUNDO;
    else
     Model1_mib_idx = Model1_LINUX_MIB_TCPDSACKIGNOREDOLD;
   } else {
    /* Don't count olds caused by ACK reordering */
    if ((((struct Model1_tcp_skb_cb *)&((Model1_ack_skb)->Model1_cb[0]))->Model1_ack_seq != Model1_tp->Model1_snd_una) &&
        !Model1_before(Model1_tp->Model1_snd_una, Model1_sp[Model1_used_sacks].Model1_end_seq))
     continue;
    Model1_mib_idx = Model1_LINUX_MIB_TCPSACKDISCARD;
   }

   (Model1_cy_linux_mib.Model1_mibs[Model1_mib_idx] += 1);
   if (Model1_i == 0)
    Model1_first_sack_index = -1;
   continue;
  }

  /* Ignore very old stuff early */
  if (!Model1_before(Model1_prior_snd_una, Model1_sp[Model1_used_sacks].Model1_end_seq))
   continue;

  Model1_used_sacks++;
 }

 /* order SACK blocks to allow in order walk of the retrans queue */
 for (Model1_i = Model1_used_sacks - 1; Model1_i > 0; Model1_i--) {
  for (Model1_j = 0; Model1_j < Model1_i; Model1_j++) {
   if (Model1_before(Model1_sp[Model1_j + 1].Model1_start_seq, Model1_sp[Model1_j].Model1_start_seq)) {
    do { typeof(Model1_sp[Model1_j]) Model1___tmp = (Model1_sp[Model1_j]); (Model1_sp[Model1_j]) = (Model1_sp[Model1_j + 1]); (Model1_sp[Model1_j + 1]) = Model1___tmp; } while (0);

    /* Track where the first SACK block goes to */
    if (Model1_j == Model1_first_sack_index)
     Model1_first_sack_index = Model1_j + 1;
   }
  }
 }

 Model1_skb = Model1_tcp_write_queue_head(Model1_sk);
 Model1_state->Model1_fack_count = 0;
 Model1_i = 0;

 if (!Model1_tp->Model1_sacked_out) {
  /* It's already past, so skip checking against it */
  Model1_cache = Model1_tp->Model1_recv_sack_cache + (sizeof(Model1_tp->Model1_recv_sack_cache) / sizeof((Model1_tp->Model1_recv_sack_cache)[0]) + (sizeof(struct { int:-!!(__builtin_types_compatible_p(typeof((Model1_tp->Model1_recv_sack_cache)), typeof(&(Model1_tp->Model1_recv_sack_cache)[0]))); })));
 } else {
  Model1_cache = Model1_tp->Model1_recv_sack_cache;
  /* Skip empty blocks in at head of the cache */
  while (Model1_tcp_sack_cache_ok(Model1_tp, Model1_cache) && !Model1_cache->Model1_start_seq &&
         !Model1_cache->Model1_end_seq)
   Model1_cache++;
 }

 while (Model1_i < Model1_used_sacks) {
  Model1_u32 Model1_start_seq = Model1_sp[Model1_i].Model1_start_seq;
  Model1_u32 Model1_end_seq = Model1_sp[Model1_i].Model1_end_seq;
  bool Model1_dup_sack = (Model1_found_dup_sack && (Model1_i == Model1_first_sack_index));
  struct Model1_tcp_sack_block *Model1_next_dup = ((void *)0);

  if (Model1_found_dup_sack && ((Model1_i + 1) == Model1_first_sack_index))
   Model1_next_dup = &Model1_sp[Model1_i + 1];

  /* Skip too early cached blocks */
  while (Model1_tcp_sack_cache_ok(Model1_tp, Model1_cache) &&
         !Model1_before(Model1_start_seq, Model1_cache->Model1_end_seq))
   Model1_cache++;

  /* Can skip some work by looking recv_sack_cache? */
  if (Model1_tcp_sack_cache_ok(Model1_tp, Model1_cache) && !Model1_dup_sack &&
      Model1_before(Model1_cache->Model1_start_seq, Model1_end_seq)) {

   /* Head todo? */
   if (Model1_before(Model1_start_seq, Model1_cache->Model1_start_seq)) {
    Model1_skb = Model1_tcp_sacktag_skip(Model1_skb, Model1_sk, Model1_state,
             Model1_start_seq);
    Model1_skb = Model1_tcp_sacktag_walk(Model1_skb, Model1_sk, Model1_next_dup,
             Model1_state,
             Model1_start_seq,
             Model1_cache->Model1_start_seq,
             Model1_dup_sack);
   }

   /* Rest of the block already fully processed? */
   if (!Model1_before(Model1_cache->Model1_end_seq, Model1_end_seq))
    goto Model1_advance_sp;

   Model1_skb = Model1_tcp_maybe_skipping_dsack(Model1_skb, Model1_sk, Model1_next_dup,
             Model1_state,
             Model1_cache->Model1_end_seq);

   /* ...tail remains todo... */
   if (Model1_tcp_highest_sack_seq(Model1_tp) == Model1_cache->Model1_end_seq) {
    /* ...but better entrypoint exists! */
    Model1_skb = Model1_tcp_highest_sack(Model1_sk);
    if (!Model1_skb)
     break;
    Model1_state->Model1_fack_count = Model1_tp->Model1_fackets_out;
    Model1_cache++;
    goto Model1_walk;
   }

   Model1_skb = Model1_tcp_sacktag_skip(Model1_skb, Model1_sk, Model1_state, Model1_cache->Model1_end_seq);
   /* Check overlap against next cached too (past this one already) */
   Model1_cache++;
   continue;
  }

  if (!Model1_before(Model1_start_seq, Model1_tcp_highest_sack_seq(Model1_tp))) {
   Model1_skb = Model1_tcp_highest_sack(Model1_sk);
   if (!Model1_skb)
    break;
   Model1_state->Model1_fack_count = Model1_tp->Model1_fackets_out;
  }
  Model1_skb = Model1_tcp_sacktag_skip(Model1_skb, Model1_sk, Model1_state, Model1_start_seq);

Model1_walk:
  Model1_skb = Model1_tcp_sacktag_walk(Model1_skb, Model1_sk, Model1_next_dup, Model1_state,
           Model1_start_seq, Model1_end_seq, Model1_dup_sack);

Model1_advance_sp:
  Model1_i++;
 }

 /* Clear the head of the cache sack blocks so we can skip it next time */
 for (Model1_i = 0; Model1_i < (sizeof(Model1_tp->Model1_recv_sack_cache) / sizeof((Model1_tp->Model1_recv_sack_cache)[0]) + (sizeof(struct { int:-!!(__builtin_types_compatible_p(typeof((Model1_tp->Model1_recv_sack_cache)), typeof(&(Model1_tp->Model1_recv_sack_cache)[0]))); }))) - Model1_used_sacks; Model1_i++) {
  Model1_tp->Model1_recv_sack_cache[Model1_i].Model1_start_seq = 0;
  Model1_tp->Model1_recv_sack_cache[Model1_i].Model1_end_seq = 0;
 }
 for (Model1_j = 0; Model1_j < Model1_used_sacks; Model1_j++)
  Model1_tp->Model1_recv_sack_cache[Model1_i++] = Model1_sp[Model1_j];

 if ((Model1_state->Model1_reord < Model1_tp->Model1_fackets_out) &&
     ((Model1_inet_csk(Model1_sk)->Model1_icsk_ca_state != Model1_TCP_CA_Loss) || Model1_tp->Model1_undo_marker))
  Model1_tcp_update_reordering(Model1_sk, Model1_tp->Model1_fackets_out - Model1_state->Model1_reord, 0);

 ({ int Model1___ret_warn_on = !!(Model1_tcp_left_out(Model1_tp) > Model1_tp->Model1_packets_out); __builtin_expect(!!(Model1___ret_warn_on), 0); });
Model1_out:


 ({ int Model1___ret_warn_on = !!((int)Model1_tp->Model1_sacked_out < 0); __builtin_expect(!!(Model1___ret_warn_on), 0); });
 ({ int Model1___ret_warn_on = !!((int)Model1_tp->Model1_lost_out < 0); __builtin_expect(!!(Model1___ret_warn_on), 0); });
 ({ int Model1___ret_warn_on = !!((int)Model1_tp->Model1_retrans_out < 0); __builtin_expect(!!(Model1___ret_warn_on), 0); });
 ({ int Model1___ret_warn_on = !!((int)Model1_tcp_packets_in_flight(Model1_tp) < 0); __builtin_expect(!!(Model1___ret_warn_on), 0); });

 return Model1_state->Model1_flag;
}

/* Limits sacked_out so that sum with lost_out isn't ever larger than
 * packets_out. Returns false if sacked_out adjustement wasn't necessary.
 */
static bool Model1_tcp_limit_reno_sacked(struct Model1_tcp_sock *Model1_tp)
{
 Model1_u32 Model1_holes;

 Model1_holes = ({ typeof(Model1_tp->Model1_lost_out) Model1__max1 = (Model1_tp->Model1_lost_out); typeof(1U) Model1__max2 = (1U); (void) (&Model1__max1 == &Model1__max2); Model1__max1 > Model1__max2 ? Model1__max1 : Model1__max2; });
 Model1_holes = ({ typeof(Model1_holes) Model1__min1 = (Model1_holes); typeof(Model1_tp->Model1_packets_out) Model1__min2 = (Model1_tp->Model1_packets_out); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });

 if ((Model1_tp->Model1_sacked_out + Model1_holes) > Model1_tp->Model1_packets_out) {
  Model1_tp->Model1_sacked_out = Model1_tp->Model1_packets_out - Model1_holes;
  return true;
 }
 return false;
}

/* If we receive more dupacks than we expected counting segments
 * in assumption of absent reordering, interpret this as reordering.
 * The only another reason could be bug in receiver TCP.
 */
static void Model1_tcp_check_reno_reordering(struct Model1_sock *Model1_sk, const int Model1_addend)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 if (Model1_tcp_limit_reno_sacked(Model1_tp))
  Model1_tcp_update_reordering(Model1_sk, Model1_tp->Model1_packets_out + Model1_addend, 0);
}

/* Emulate SACKs for SACKless connection: account for a new dupack. */

static void Model1_tcp_add_reno_sack(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 Model1_u32 Model1_prior_sacked = Model1_tp->Model1_sacked_out;

 Model1_tp->Model1_sacked_out++;
 Model1_tcp_check_reno_reordering(Model1_sk, 0);
 if (Model1_tp->Model1_sacked_out > Model1_prior_sacked)
  Model1_tp->Model1_delivered++; /* Some out-of-order packet is delivered */
 ({ int Model1___ret_warn_on = !!(Model1_tcp_left_out(Model1_tp) > Model1_tp->Model1_packets_out); __builtin_expect(!!(Model1___ret_warn_on), 0); });
}

/* Account for ACK, ACKing some data in Reno Recovery phase. */

static void Model1_tcp_remove_reno_sacks(struct Model1_sock *Model1_sk, int Model1_acked)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 if (Model1_acked > 0) {
  /* One ACK acked hole. The rest eat duplicate ACKs. */
  Model1_tp->Model1_delivered += ({ int Model1___max1 = (Model1_acked - Model1_tp->Model1_sacked_out); int Model1___max2 = (1); Model1___max1 > Model1___max2 ? Model1___max1: Model1___max2; });
  if (Model1_acked - 1 >= Model1_tp->Model1_sacked_out)
   Model1_tp->Model1_sacked_out = 0;
  else
   Model1_tp->Model1_sacked_out -= Model1_acked - 1;
 }
 Model1_tcp_check_reno_reordering(Model1_sk, Model1_acked);
 ({ int Model1___ret_warn_on = !!(Model1_tcp_left_out(Model1_tp) > Model1_tp->Model1_packets_out); __builtin_expect(!!(Model1___ret_warn_on), 0); });
}

static inline __attribute__((no_instrument_function)) void Model1_tcp_reset_reno_sack(struct Model1_tcp_sock *Model1_tp)
{
 Model1_tp->Model1_sacked_out = 0;
}

void Model1_tcp_clear_retrans(struct Model1_tcp_sock *Model1_tp)
{
 Model1_tp->Model1_retrans_out = 0;
 Model1_tp->Model1_lost_out = 0;
 Model1_tp->Model1_undo_marker = 0;
 Model1_tp->Model1_undo_retrans = -1;
 Model1_tp->Model1_fackets_out = 0;
 Model1_tp->Model1_sacked_out = 0;
}

static inline __attribute__((no_instrument_function)) void Model1_tcp_init_undo(struct Model1_tcp_sock *Model1_tp)
{
 Model1_tp->Model1_undo_marker = Model1_tp->Model1_snd_una;
 /* Retransmission still in flight may cause DSACKs later. */
 Model1_tp->Model1_undo_retrans = Model1_tp->Model1_retrans_out ? : -1;
}

/* Enter Loss state. If we detect SACK reneging, forget all SACK information
 * and reset tags completely, otherwise preserve SACKs. If receiver
 * dropped its ofo queue, we will know this due to reneging detection.
 */
void Model1_tcp_enter_loss(struct Model1_sock *Model1_sk)
{
 const struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_net *Model1_net = Model1_sock_net(Model1_sk);
 struct Model1_sk_buff *Model1_skb;
 bool Model1_new_recovery = Model1_icsk->Model1_icsk_ca_state < Model1_TCP_CA_Recovery;
 bool Model1_is_reneg; /* is receiver reneging on SACKs? */

 /* Reduce ssthresh if it has not yet been made inside this window. */
 if (Model1_icsk->Model1_icsk_ca_state <= Model1_TCP_CA_Disorder ||
     !Model1_before(Model1_tp->Model1_snd_una, Model1_tp->Model1_high_seq) ||
     (Model1_icsk->Model1_icsk_ca_state == Model1_TCP_CA_Loss && !Model1_icsk->Model1_icsk_retransmits)) {
  Model1_tp->Model1_prior_ssthresh = Model1_tcp_current_ssthresh(Model1_sk);
#if CY_ABSTRACT7
  Model1_tp->Model1_snd_ssthresh = Model1_tcp_reno_ssthresh(Model1_sk); //this function won't be called
#else
  Model1_tp->Model1_snd_ssthresh = Model1_icsk->Model1_icsk_ca_ops->Model1_ssthresh(Model1_sk);
#endif
  Model1_tcp_ca_event(Model1_sk, Model1_CA_EVENT_LOSS);
  Model1_tcp_init_undo(Model1_tp);
 }
 Model1_tp->Model1_snd_cwnd = 1;
 Model1_tp->Model1_snd_cwnd_cnt = 0;
 Model1_tp->Model1_snd_cwnd_stamp = ((__u32)(Model1_jiffies));

 Model1_tp->Model1_retrans_out = 0;
 Model1_tp->Model1_lost_out = 0;

 if (Model1_tcp_is_reno(Model1_tp))
  Model1_tcp_reset_reno_sack(Model1_tp);

 Model1_skb = Model1_tcp_write_queue_head(Model1_sk);
 Model1_is_reneg = Model1_skb && (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked & 0x01);
 if (Model1_is_reneg) {
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPSACKRENEGING] += 1);
  Model1_tp->Model1_sacked_out = 0;
  Model1_tp->Model1_fackets_out = 0;
 }
 Model1_tcp_clear_all_retrans_hints(Model1_tp);

 for (Model1_skb = (&(Model1_sk)->Model1_sk_write_queue)->Model1_next; Model1_skb != (struct Model1_sk_buff *)(&(Model1_sk)->Model1_sk_write_queue); Model1_skb = Model1_skb->Model1_next) {
  if (Model1_skb == Model1_tcp_send_head(Model1_sk))
   break;

  ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked &= (~0x07)|0x01;
  if (!(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked&0x01) || Model1_is_reneg) {
   ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked &= ~0x01;
   ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked |= 0x04;
   Model1_tp->Model1_lost_out += Model1_tcp_skb_pcount(Model1_skb);
   Model1_tp->Model1_retransmit_high = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq;
  }
 }
 ({ int Model1___ret_warn_on = !!(Model1_tcp_left_out(Model1_tp) > Model1_tp->Model1_packets_out); __builtin_expect(!!(Model1___ret_warn_on), 0); });

 /* Timeout in disordered state after receiving substantial DUPACKs
	 * suggests that the degree of reordering is over-estimated.
	 */
 if (Model1_icsk->Model1_icsk_ca_state <= Model1_TCP_CA_Disorder &&
     Model1_tp->Model1_sacked_out >= Model1_net->Model1_ipv4.Model1_sysctl_tcp_reordering)
  Model1_tp->Model1_reordering = ({ unsigned int Model1___min1 = (Model1_tp->Model1_reordering); unsigned int Model1___min2 = (Model1_net->Model1_ipv4.Model1_sysctl_tcp_reordering); Model1___min1 < Model1___min2 ? Model1___min1: Model1___min2; });

 Model1_tcp_set_ca_state(Model1_sk, Model1_TCP_CA_Loss);
 Model1_tp->Model1_high_seq = Model1_tp->Model1_snd_nxt;
 Model1_tcp_ecn_queue_cwr(Model1_tp);

 /* F-RTO RFC5682 sec 3.1 step 1: retransmit SND.UNA if no previous
	 * loss recovery is underway except recurring timeout(s) on
	 * the same SND.UNA (sec 3.2). Disable F-RTO on path MTU probing
	 */
 Model1_tp->Model1_frto = Model1_sysctl_tcp_frto &&
     (Model1_new_recovery || Model1_icsk->Model1_icsk_retransmits) &&
     !Model1_inet_csk(Model1_sk)->Model1_icsk_mtup.Model1_probe_size;
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
static bool Model1_tcp_check_sack_reneging(struct Model1_sock *Model1_sk, int Model1_flag)
{
 if (Model1_flag & 0x2000) {
  struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
  unsigned long Model1_delay = ({ typeof(Model1_usecs_to_jiffies(Model1_tp->Model1_srtt_us >> 4)) Model1__max1 = (Model1_usecs_to_jiffies(Model1_tp->Model1_srtt_us >> 4)); typeof(Model1_msecs_to_jiffies(10)) Model1__max2 = (Model1_msecs_to_jiffies(10)); (void) (&Model1__max1 == &Model1__max2); Model1__max1 > Model1__max2 ? Model1__max1 : Model1__max2; });


  Model1_inet_csk_reset_xmit_timer(Model1_sk, 1,
       Model1_delay, ((unsigned)(120*1000)));
  return true;
 }
 return false;
}

static inline __attribute__((no_instrument_function)) int Model1_tcp_fackets_out(const struct Model1_tcp_sock *Model1_tp)
{
 return Model1_tcp_is_reno(Model1_tp) ? Model1_tp->Model1_sacked_out + 1 : Model1_tp->Model1_fackets_out;
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
static inline __attribute__((no_instrument_function)) int Model1_tcp_dupack_heuristics(const struct Model1_tcp_sock *Model1_tp)
{
 return Model1_tcp_is_fack(Model1_tp) ? Model1_tp->Model1_fackets_out : Model1_tp->Model1_sacked_out + 1;
}

static bool Model1_tcp_pause_early_retransmit(struct Model1_sock *Model1_sk, int Model1_flag)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 unsigned long Model1_delay;

 /* Delay early retransmit and entering fast recovery for
	 * max(RTT/4, 2msec) unless ack has ECE mark, no RTT samples
	 * available, or RTO is scheduled to fire first.
	 */
 if (Model1_sysctl_tcp_early_retrans < 2 || Model1_sysctl_tcp_early_retrans > 3 ||
     (Model1_flag & 0x40) || !Model1_tp->Model1_srtt_us)
  return false;

 Model1_delay = ({ typeof(Model1_usecs_to_jiffies(Model1_tp->Model1_srtt_us >> 5)) Model1__max1 = (Model1_usecs_to_jiffies(Model1_tp->Model1_srtt_us >> 5)); typeof(Model1_msecs_to_jiffies(2)) Model1__max2 = (Model1_msecs_to_jiffies(2)); (void) (&Model1__max1 == &Model1__max2); Model1__max1 > Model1__max2 ? Model1__max1 : Model1__max2; });


 if (!(({ unsigned long Model1___dummy; typeof(Model1_inet_csk(Model1_sk)->Model1_icsk_timeout) Model1___dummy2; (void)(&Model1___dummy == &Model1___dummy2); 1; }) && ({ unsigned long Model1___dummy; typeof((Model1_jiffies + Model1_delay)) Model1___dummy2; (void)(&Model1___dummy == &Model1___dummy2); 1; }) && ((long)(((Model1_jiffies + Model1_delay)) - (Model1_inet_csk(Model1_sk)->Model1_icsk_timeout)) < 0)))
  return false;

 Model1_inet_csk_reset_xmit_timer(Model1_sk, 4, Model1_delay,
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
static bool Model1_tcp_time_to_recover(struct Model1_sock *Model1_sk, int Model1_flag)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 __u32 Model1_packets_out;
 int Model1_tcp_reordering = Model1_sock_net(Model1_sk)->Model1_ipv4.Model1_sysctl_tcp_reordering;

 /* Trick#1: The loss is proven. */
 if (Model1_tp->Model1_lost_out)
  return true;

 /* Not-A-Trick#2 : Classic rule... */
 if (Model1_tcp_dupack_heuristics(Model1_tp) > Model1_tp->Model1_reordering)
  return true;

 /* Trick#4: It is still not OK... But will it be useful to delay
	 * recovery more?
	 */
 Model1_packets_out = Model1_tp->Model1_packets_out;
 if (Model1_packets_out <= Model1_tp->Model1_reordering &&
     Model1_tp->Model1_sacked_out >= ({ __u32 Model1___max1 = (Model1_packets_out/2); __u32 Model1___max2 = (Model1_tcp_reordering); Model1___max1 > Model1___max2 ? Model1___max1: Model1___max2; }) &&
     !Model1_tcp_may_send_now(Model1_sk)) {
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
 if ((Model1_tp->Model1_thin_dupack || Model1_sysctl_tcp_thin_dupack) &&
     Model1_tcp_stream_is_thin(Model1_tp) && Model1_tcp_dupack_heuristics(Model1_tp) > 1 &&
     Model1_tcp_is_sack(Model1_tp) && !Model1_tcp_send_head(Model1_sk))
  return true;

 /* Trick#6: TCP early retransmit, per RFC5827.  To avoid spurious
	 * retransmissions due to small network reorderings, we implement
	 * Mitigation A.3 in the RFC and delay the retransmission for a short
	 * interval if appropriate.
	 */
 if (Model1_tp->Model1_do_early_retrans && !Model1_tp->Model1_retrans_out && Model1_tp->Model1_sacked_out &&
     (Model1_tp->Model1_packets_out >= (Model1_tp->Model1_sacked_out + 1) && Model1_tp->Model1_packets_out < 4) &&
     !Model1_tcp_may_send_now(Model1_sk))
  return !Model1_tcp_pause_early_retransmit(Model1_sk, Model1_flag);

 return false;
}

/* Detect loss in event "A" above by marking head of queue up as lost.
 * For FACK or non-SACK(Reno) senders, the first "packets" number of segments
 * are considered lost. For RFC3517 SACK, a segment is considered lost if it
 * has at least tp->reordering SACKed seqments above it; "packets" refers to
 * the maximum SACKed segments to pass before reaching this limit.
 */
static void Model1_tcp_mark_head_lost(struct Model1_sock *Model1_sk, int Model1_packets, int Model1_mark_head)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_sk_buff *Model1_skb;
 int Model1_cnt, Model1_oldcnt, Model1_lost;
 unsigned int Model1_mss;
 /* Use SACK to deduce losses of new sequences sent during recovery */
 const Model1_u32 Model1_loss_high = Model1_tcp_is_sack(Model1_tp) ? Model1_tp->Model1_snd_nxt : Model1_tp->Model1_high_seq;

 ({ int Model1___ret_warn_on = !!(Model1_packets > Model1_tp->Model1_packets_out); __builtin_expect(!!(Model1___ret_warn_on), 0); });
 if (Model1_tp->Model1_lost_skb_hint) {
  Model1_skb = Model1_tp->Model1_lost_skb_hint;
  Model1_cnt = Model1_tp->Model1_lost_cnt_hint;
  /* Head already handled? */
  if (Model1_mark_head && Model1_skb != Model1_tcp_write_queue_head(Model1_sk))
   return;
 } else {
  Model1_skb = Model1_tcp_write_queue_head(Model1_sk);
  Model1_cnt = 0;
 }

 for (; Model1_skb != (struct Model1_sk_buff *)(&(Model1_sk)->Model1_sk_write_queue); Model1_skb = Model1_skb->Model1_next) {
  if (Model1_skb == Model1_tcp_send_head(Model1_sk))
   break;
  /* TODO: do this better */
  /* this is not the most efficient way to do this... */
  Model1_tp->Model1_lost_skb_hint = Model1_skb;
  Model1_tp->Model1_lost_cnt_hint = Model1_cnt;

  if (Model1_before(Model1_loss_high, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq))
   break;

  Model1_oldcnt = Model1_cnt;
  if (Model1_tcp_is_fack(Model1_tp) || Model1_tcp_is_reno(Model1_tp) ||
      (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked & 0x01))
   Model1_cnt += Model1_tcp_skb_pcount(Model1_skb);

  if (Model1_cnt > Model1_packets) {
   if ((Model1_tcp_is_sack(Model1_tp) && !Model1_tcp_is_fack(Model1_tp)) ||
       (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked & 0x01) ||
       (Model1_oldcnt >= Model1_packets))
    break;

   Model1_mss = Model1_tcp_skb_mss(Model1_skb);
   /* If needed, chop off the prefix to mark as lost. */
   Model1_lost = (Model1_packets - Model1_oldcnt) * Model1_mss;
   if (Model1_lost < Model1_skb->Model1_len &&
       Model1_tcp_fragment(Model1_sk, Model1_skb, Model1_lost, Model1_mss, ((( Model1_gfp_t)0x20u)|(( Model1_gfp_t)0x80000u)|(( Model1_gfp_t)0x2000000u))) < 0)
    break;
   Model1_cnt = Model1_packets;
  }

  Model1_tcp_skb_mark_lost(Model1_tp, Model1_skb);

  if (Model1_mark_head)
   break;
 }
 ({ int Model1___ret_warn_on = !!(Model1_tcp_left_out(Model1_tp) > Model1_tp->Model1_packets_out); __builtin_expect(!!(Model1___ret_warn_on), 0); });
}

/* Account newly detected lost packet(s) */

static void Model1_tcp_update_scoreboard(struct Model1_sock *Model1_sk, int Model1_fast_rexmit)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 if (Model1_tcp_is_reno(Model1_tp)) {
  Model1_tcp_mark_head_lost(Model1_sk, 1, 1);
 } else if (Model1_tcp_is_fack(Model1_tp)) {
  int Model1_lost = Model1_tp->Model1_fackets_out - Model1_tp->Model1_reordering;
  if (Model1_lost <= 0)
   Model1_lost = 1;
  Model1_tcp_mark_head_lost(Model1_sk, Model1_lost, 0);
 } else {
  int Model1_sacked_upto = Model1_tp->Model1_sacked_out - Model1_tp->Model1_reordering;
  if (Model1_sacked_upto >= 0)
   Model1_tcp_mark_head_lost(Model1_sk, Model1_sacked_upto, 0);
  else if (Model1_fast_rexmit)
   Model1_tcp_mark_head_lost(Model1_sk, 1, 1);
 }
}

static bool Model1_tcp_tsopt_ecr_before(const struct Model1_tcp_sock *Model1_tp, Model1_u32 Model1_when)
{
 return Model1_tp->Model1_rx_opt.Model1_saw_tstamp && Model1_tp->Model1_rx_opt.Model1_rcv_tsecr &&
        Model1_before(Model1_tp->Model1_rx_opt.Model1_rcv_tsecr, Model1_when);
}

/* skb is spurious retransmitted if the returned timestamp echo
 * reply is prior to the skb transmission time
 */
static bool Model1_tcp_skb_spurious_retrans(const struct Model1_tcp_sock *Model1_tp,
         const struct Model1_sk_buff *Model1_skb)
{
 return (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked & (0x02|0x80| 0x10)) &&
        Model1_tcp_tsopt_ecr_before(Model1_tp, Model1_tcp_skb_timestamp(Model1_skb));
}

/* Nothing was retransmitted or returned timestamp is less
 * than timestamp of the first retransmission.
 */
static inline __attribute__((no_instrument_function)) bool Model1_tcp_packet_delayed(const struct Model1_tcp_sock *Model1_tp)
{
 return !Model1_tp->Model1_retrans_stamp ||
        Model1_tcp_tsopt_ecr_before(Model1_tp, Model1_tp->Model1_retrans_stamp);
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
static bool Model1_tcp_any_retrans_done(const struct Model1_sock *Model1_sk)
{
 const struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_sk_buff *Model1_skb;

 if (Model1_tp->Model1_retrans_out)
  return true;

 Model1_skb = Model1_tcp_write_queue_head(Model1_sk);
 if (__builtin_expect(!!(Model1_skb && ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked & 0x80), 0))
  return true;

 return false;
}
static void Model1_tcp_undo_cwnd_reduction(struct Model1_sock *Model1_sk, bool Model1_unmark_loss)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 if (Model1_unmark_loss) {
  struct Model1_sk_buff *Model1_skb;

  for (Model1_skb = (&(Model1_sk)->Model1_sk_write_queue)->Model1_next; Model1_skb != (struct Model1_sk_buff *)(&(Model1_sk)->Model1_sk_write_queue); Model1_skb = Model1_skb->Model1_next) {
   if (Model1_skb == Model1_tcp_send_head(Model1_sk))
    break;
   ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked &= ~0x04;
  }
  Model1_tp->Model1_lost_out = 0;
  Model1_tcp_clear_all_retrans_hints(Model1_tp);
 }

 if (Model1_tp->Model1_prior_ssthresh) {
  const struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);

  if (Model1_icsk->Model1_icsk_ca_ops->Model1_undo_cwnd)
   Model1_tp->Model1_snd_cwnd = Model1_icsk->Model1_icsk_ca_ops->Model1_undo_cwnd(Model1_sk);
  else
   Model1_tp->Model1_snd_cwnd = ({ typeof(Model1_tp->Model1_snd_cwnd) Model1__max1 = (Model1_tp->Model1_snd_cwnd); typeof(Model1_tp->Model1_snd_ssthresh << 1) Model1__max2 = (Model1_tp->Model1_snd_ssthresh << 1); (void) (&Model1__max1 == &Model1__max2); Model1__max1 > Model1__max2 ? Model1__max1 : Model1__max2; });

  if (Model1_tp->Model1_prior_ssthresh > Model1_tp->Model1_snd_ssthresh) {
   Model1_tp->Model1_snd_ssthresh = Model1_tp->Model1_prior_ssthresh;
   Model1_tcp_ecn_withdraw_cwr(Model1_tp);
  }
 }
 Model1_tp->Model1_snd_cwnd_stamp = ((__u32)(Model1_jiffies));
 Model1_tp->Model1_undo_marker = 0;
}

static inline __attribute__((no_instrument_function)) bool Model1_tcp_may_undo(const struct Model1_tcp_sock *Model1_tp)
{
 return Model1_tp->Model1_undo_marker && (!Model1_tp->Model1_undo_retrans || Model1_tcp_packet_delayed(Model1_tp));
}

/* People celebrate: "We love our President!" */
static bool Model1_tcp_try_undo_recovery(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 if (Model1_tcp_may_undo(Model1_tp)) {
  int Model1_mib_idx;

  /* Happy end! We did not retransmit anything
		 * or our original transmission succeeded.
		 */
  do { } while (0);
  Model1_tcp_undo_cwnd_reduction(Model1_sk, false);
  if (Model1_inet_csk(Model1_sk)->Model1_icsk_ca_state == Model1_TCP_CA_Loss)
   Model1_mib_idx = Model1_LINUX_MIB_TCPLOSSUNDO;
  else
   Model1_mib_idx = Model1_LINUX_MIB_TCPFULLUNDO;

  (Model1_cy_linux_mib.Model1_mibs[Model1_mib_idx] += 1);
 }
 if (Model1_tp->Model1_snd_una == Model1_tp->Model1_high_seq && Model1_tcp_is_reno(Model1_tp)) {
  /* Hold old state until something *above* high_seq
		 * is ACKed. For Reno it is MUST to prevent false
		 * fast retransmits (RFC2582). SACK TCP is safe. */
  if (!Model1_tcp_any_retrans_done(Model1_sk))
   Model1_tp->Model1_retrans_stamp = 0;
  return true;
 }
 Model1_tcp_set_ca_state(Model1_sk, Model1_TCP_CA_Open);
 return false;
}

/* Try to undo cwnd reduction, because D-SACKs acked all retransmitted data */
static bool Model1_tcp_try_undo_dsack(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 if (Model1_tp->Model1_undo_marker && !Model1_tp->Model1_undo_retrans) {
  do { } while (0);
  Model1_tcp_undo_cwnd_reduction(Model1_sk, false);
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPDSACKUNDO] += 1);
  return true;
 }
 return false;
}

/* Undo during loss recovery after partial ACK or using F-RTO. */
static bool Model1_tcp_try_undo_loss(struct Model1_sock *Model1_sk, bool Model1_frto_undo)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 if (Model1_frto_undo || Model1_tcp_may_undo(Model1_tp)) {
  Model1_tcp_undo_cwnd_reduction(Model1_sk, true);

  do { } while (0);
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPLOSSUNDO] += 1);
  if (Model1_frto_undo)
   (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPSPURIOUSRTOS] += 1);

  Model1_inet_csk(Model1_sk)->Model1_icsk_retransmits = 0;
  if (Model1_frto_undo || Model1_tcp_is_sack(Model1_tp))
   Model1_tcp_set_ca_state(Model1_sk, Model1_TCP_CA_Open);
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
static void Model1_tcp_init_cwnd_reduction(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 Model1_tp->Model1_high_seq = Model1_tp->Model1_snd_nxt;
 Model1_tp->Model1_tlp_high_seq = 0;
 Model1_tp->Model1_snd_cwnd_cnt = 0;
 Model1_tp->Model1_prior_cwnd = Model1_tp->Model1_snd_cwnd;
 Model1_tp->Model1_prr_delivered = 0;
 Model1_tp->Model1_prr_out = 0;
#if CY_ABSTRACT7
  Model1_tp->Model1_snd_ssthresh = Model1_tcp_reno_ssthresh(Model1_sk); //this function won't be called
#else
 Model1_tp->Model1_snd_ssthresh = Model1_inet_csk(Model1_sk)->Model1_icsk_ca_ops->Model1_ssthresh(Model1_sk);
#endif
 Model1_tcp_ecn_queue_cwr(Model1_tp);
}

static void Model1_tcp_cwnd_reduction(struct Model1_sock *Model1_sk, int Model1_newly_acked_sacked,
          int Model1_flag)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 int Model1_sndcnt = 0;
 int Model1_delta = Model1_tp->Model1_snd_ssthresh - Model1_tcp_packets_in_flight(Model1_tp);

 if (Model1_newly_acked_sacked <= 0 || ({ int Model1___ret_warn_on = !!(!Model1_tp->Model1_prior_cwnd); __builtin_expect(!!(Model1___ret_warn_on), 0); }))
  return;

 Model1_tp->Model1_prr_delivered += Model1_newly_acked_sacked;
 if (Model1_delta < 0) {
  Model1_u64 Model1_dividend = (Model1_u64)Model1_tp->Model1_snd_ssthresh * Model1_tp->Model1_prr_delivered +
          Model1_tp->Model1_prior_cwnd - 1;
  Model1_sndcnt = Model1_div_u64(Model1_dividend, Model1_tp->Model1_prior_cwnd) - Model1_tp->Model1_prr_out;
 } else if ((Model1_flag & 0x08) &&
     !(Model1_flag & 0x80)) {
  Model1_sndcnt = ({ int Model1___min1 = (Model1_delta); int Model1___min2 = (({ int Model1___max1 = (Model1_tp->Model1_prr_delivered - Model1_tp->Model1_prr_out); int Model1___max2 = (Model1_newly_acked_sacked); Model1___max1 > Model1___max2 ? Model1___max1: Model1___max2; }) + 1); Model1___min1 < Model1___min2 ? Model1___min1: Model1___min2; });


 } else {
  Model1_sndcnt = ({ typeof(Model1_delta) Model1__min1 = (Model1_delta); typeof(Model1_newly_acked_sacked) Model1__min2 = (Model1_newly_acked_sacked); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
 }
 /* Force a fast retransmit upon entering fast recovery */
 Model1_sndcnt = ({ typeof(Model1_sndcnt) Model1__max1 = (Model1_sndcnt); typeof((Model1_tp->Model1_prr_out ? 0 : 1)) Model1__max2 = ((Model1_tp->Model1_prr_out ? 0 : 1)); (void) (&Model1__max1 == &Model1__max2); Model1__max1 > Model1__max2 ? Model1__max1 : Model1__max2; });
 Model1_tp->Model1_snd_cwnd = Model1_tcp_packets_in_flight(Model1_tp) + Model1_sndcnt;
}

static inline __attribute__((no_instrument_function)) void Model1_tcp_end_cwnd_reduction(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 /* Reset cwnd to ssthresh in CWR or Recovery (unless it's undone) */
 if (Model1_inet_csk(Model1_sk)->Model1_icsk_ca_state == Model1_TCP_CA_CWR ||
     (Model1_tp->Model1_undo_marker && Model1_tp->Model1_snd_ssthresh < 0x7fffffff)) {
  Model1_tp->Model1_snd_cwnd = Model1_tp->Model1_snd_ssthresh;
  Model1_tp->Model1_snd_cwnd_stamp = ((__u32)(Model1_jiffies));
 }
 Model1_tcp_ca_event(Model1_sk, Model1_CA_EVENT_COMPLETE_CWR);
}

/* Enter CWR state. Disable cwnd undo since congestion is proven with ECN */
void Model1_tcp_enter_cwr(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 Model1_tp->Model1_prior_ssthresh = 0;
 if (Model1_inet_csk(Model1_sk)->Model1_icsk_ca_state < Model1_TCP_CA_CWR) {
  Model1_tp->Model1_undo_marker = 0;
  Model1_tcp_init_cwnd_reduction(Model1_sk);
  Model1_tcp_set_ca_state(Model1_sk, Model1_TCP_CA_CWR);
 }
}
                            ;

static void Model1_tcp_try_keep_open(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 int Model1_state = Model1_TCP_CA_Open;

 if (Model1_tcp_left_out(Model1_tp) || Model1_tcp_any_retrans_done(Model1_sk))
  Model1_state = Model1_TCP_CA_Disorder;

 if (Model1_inet_csk(Model1_sk)->Model1_icsk_ca_state != Model1_state) {
  Model1_tcp_set_ca_state(Model1_sk, Model1_state);
  Model1_tp->Model1_high_seq = Model1_tp->Model1_snd_nxt;
 }
}

static void Model1_tcp_try_to_open(struct Model1_sock *Model1_sk, int Model1_flag)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 ({ int Model1___ret_warn_on = !!(Model1_tcp_left_out(Model1_tp) > Model1_tp->Model1_packets_out); __builtin_expect(!!(Model1___ret_warn_on), 0); });

 if (!Model1_tcp_any_retrans_done(Model1_sk))
  Model1_tp->Model1_retrans_stamp = 0;

 if (Model1_flag & 0x40)
  Model1_tcp_enter_cwr(Model1_sk);

 if (Model1_inet_csk(Model1_sk)->Model1_icsk_ca_state != Model1_TCP_CA_CWR) {
  Model1_tcp_try_keep_open(Model1_sk);
 }
}

static void Model1_tcp_mtup_probe_failed(struct Model1_sock *Model1_sk)
{
 struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);

 Model1_icsk->Model1_icsk_mtup.Model1_search_high = Model1_icsk->Model1_icsk_mtup.Model1_probe_size - 1;
 Model1_icsk->Model1_icsk_mtup.Model1_probe_size = 0;
 (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPMTUPFAIL] += 1);
}

static void Model1_tcp_mtup_probe_success(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);

 /* FIXME: breaks with very large cwnd */
 Model1_tp->Model1_prior_ssthresh = Model1_tcp_current_ssthresh(Model1_sk);
 Model1_tp->Model1_snd_cwnd = Model1_tp->Model1_snd_cwnd *
         Model1_tcp_mss_to_mtu(Model1_sk, Model1_tp->Model1_mss_cache) /
         Model1_icsk->Model1_icsk_mtup.Model1_probe_size;
 Model1_tp->Model1_snd_cwnd_cnt = 0;
 Model1_tp->Model1_snd_cwnd_stamp = ((__u32)(Model1_jiffies));
 Model1_tp->Model1_snd_ssthresh = Model1_tcp_current_ssthresh(Model1_sk);

 Model1_icsk->Model1_icsk_mtup.Model1_search_low = Model1_icsk->Model1_icsk_mtup.Model1_probe_size;
 Model1_icsk->Model1_icsk_mtup.Model1_probe_size = 0;
 Model1_tcp_sync_mss(Model1_sk, Model1_icsk->Model1_icsk_pmtu_cookie);
 (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPMTUPSUCCESS] += 1);
}

/* Do a simple retransmit without using the backoff mechanisms in
 * tcp_timer. This is used for path mtu discovery.
 * The socket is already locked here.
 */
void Model1_tcp_simple_retransmit(struct Model1_sock *Model1_sk)
{
 const struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_sk_buff *Model1_skb;
 unsigned int Model1_mss = Model1_tcp_current_mss(Model1_sk);
 Model1_u32 Model1_prior_lost = Model1_tp->Model1_lost_out;

 for (Model1_skb = (&(Model1_sk)->Model1_sk_write_queue)->Model1_next; Model1_skb != (struct Model1_sk_buff *)(&(Model1_sk)->Model1_sk_write_queue); Model1_skb = Model1_skb->Model1_next) {
  if (Model1_skb == Model1_tcp_send_head(Model1_sk))
   break;
  if (Model1_tcp_skb_seglen(Model1_skb) > Model1_mss &&
      !(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked & 0x01)) {
   if (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked & 0x02) {
    ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked &= ~0x02;
    Model1_tp->Model1_retrans_out -= Model1_tcp_skb_pcount(Model1_skb);
   }
   Model1_tcp_skb_mark_lost_uncond_verify(Model1_tp, Model1_skb);
  }
 }

 Model1_tcp_clear_retrans_hints_partial(Model1_tp);

 if (Model1_prior_lost == Model1_tp->Model1_lost_out)
  return;

 if (Model1_tcp_is_reno(Model1_tp))
  Model1_tcp_limit_reno_sacked(Model1_tp);

 ({ int Model1___ret_warn_on = !!(Model1_tcp_left_out(Model1_tp) > Model1_tp->Model1_packets_out); __builtin_expect(!!(Model1___ret_warn_on), 0); });

 /* Don't muck with the congestion window here.
	 * Reason is that we do not increase amount of _data_
	 * in network, but units changed and effective
	 * cwnd/ssthresh really reduced now.
	 */
 if (Model1_icsk->Model1_icsk_ca_state != Model1_TCP_CA_Loss) {
  Model1_tp->Model1_high_seq = Model1_tp->Model1_snd_nxt;
  Model1_tp->Model1_snd_ssthresh = Model1_tcp_current_ssthresh(Model1_sk);
  Model1_tp->Model1_prior_ssthresh = 0;
  Model1_tp->Model1_undo_marker = 0;
  Model1_tcp_set_ca_state(Model1_sk, Model1_TCP_CA_Loss);
 }
 Model1_tcp_xmit_retransmit_queue(Model1_sk);
}
                                    ;

static void Model1_tcp_enter_recovery(struct Model1_sock *Model1_sk, bool Model1_ece_ack)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 int Model1_mib_idx;

 if (Model1_tcp_is_reno(Model1_tp))
  Model1_mib_idx = Model1_LINUX_MIB_TCPRENORECOVERY;
 else
  Model1_mib_idx = Model1_LINUX_MIB_TCPSACKRECOVERY;

 (Model1_cy_linux_mib.Model1_mibs[Model1_mib_idx] += 1);

 Model1_tp->Model1_prior_ssthresh = 0;
 Model1_tcp_init_undo(Model1_tp);

 if (!Model1_tcp_in_cwnd_reduction(Model1_sk)) {
  if (!Model1_ece_ack)
   Model1_tp->Model1_prior_ssthresh = Model1_tcp_current_ssthresh(Model1_sk);
  Model1_tcp_init_cwnd_reduction(Model1_sk);
 }
 Model1_tcp_set_ca_state(Model1_sk, Model1_TCP_CA_Recovery);
}

/* Process an ACK in CA_Loss state. Move to CA_Open if lost data are
 * recovered or spurious. Otherwise retransmits more on partial ACKs.
 */
static void Model1_tcp_process_loss(struct Model1_sock *Model1_sk, int Model1_flag, bool Model1_is_dupack,
        int *Model1_rexmit)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 bool Model1_recovered = !Model1_before(Model1_tp->Model1_snd_una, Model1_tp->Model1_high_seq);

 if ((Model1_flag & 0x400) &&
     Model1_tcp_try_undo_loss(Model1_sk, false))
  return;

 if (Model1_tp->Model1_frto) { /* F-RTO RFC5682 sec 3.1 (sack enhanced version). */
  /* Step 3.b. A timeout is spurious if not all data are
		 * lost, i.e., never-retransmitted data are (s)acked.
		 */
  if ((Model1_flag & 0x200) &&
      Model1_tcp_try_undo_loss(Model1_sk, true))
   return;

  if (Model1_before(Model1_tp->Model1_high_seq, Model1_tp->Model1_snd_nxt)) {
   if (Model1_flag & 0x20 || Model1_is_dupack)
    Model1_tp->Model1_frto = 0; /* Step 3.a. loss was real */
  } else if (Model1_flag & 0x400 && !Model1_recovered) {
   Model1_tp->Model1_high_seq = Model1_tp->Model1_snd_nxt;
   /* Step 2.b. Try send new data (but deferred until cwnd
			 * is updated in tcp_ack()). Otherwise fall back to
			 * the conventional recovery.
			 */
   if (Model1_tcp_send_head(Model1_sk) &&
       Model1_before(Model1_tp->Model1_snd_nxt, Model1_tcp_wnd_end(Model1_tp))) {
    *Model1_rexmit = 2;
    return;
   }
   Model1_tp->Model1_frto = 0;
  }
 }

 if (Model1_recovered) {
  /* F-RTO RFC5682 sec 3.1 step 2.a and 1st part of step 3.a */
  Model1_tcp_try_undo_recovery(Model1_sk);
  return;
 }
 if (Model1_tcp_is_reno(Model1_tp)) {
  /* A Reno DUPACK means new data in F-RTO step 2.b above are
		 * delivered. Lower inflight to clock out (re)tranmissions.
		 */
  if (Model1_before(Model1_tp->Model1_high_seq, Model1_tp->Model1_snd_nxt) && Model1_is_dupack)
   Model1_tcp_add_reno_sack(Model1_sk);
  else if (Model1_flag & 0x400)
   Model1_tcp_reset_reno_sack(Model1_tp);
 }
 *Model1_rexmit = 1;
}

/* Undo during fast recovery after partial ACK. */
static bool Model1_tcp_try_undo_partial(struct Model1_sock *Model1_sk, const int Model1_acked)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 if (Model1_tp->Model1_undo_marker && Model1_tcp_packet_delayed(Model1_tp)) {
  /* Plain luck! Hole if filled with delayed
		 * packet, rather than with a retransmit.
		 */
  Model1_tcp_update_reordering(Model1_sk, Model1_tcp_fackets_out(Model1_tp) + Model1_acked, 1);

  /* We are getting evidence that the reordering degree is higher
		 * than we realized. If there are no retransmits out then we
		 * can undo. Otherwise we clock out new packets but do not
		 * mark more packets lost or retransmit more.
		 */
  if (Model1_tp->Model1_retrans_out)
   return true;

  if (!Model1_tcp_any_retrans_done(Model1_sk))
   Model1_tp->Model1_retrans_stamp = 0;

  do { } while (0);
  Model1_tcp_undo_cwnd_reduction(Model1_sk, true);
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPPARTIALUNDO] += 1);
  Model1_tcp_try_keep_open(Model1_sk);
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
static void Model1_tcp_fastretrans_alert(struct Model1_sock *Model1_sk, const int Model1_acked,
      bool Model1_is_dupack, int *Model1_ack_flag, int *Model1_rexmit)
{
 struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 int Model1_fast_rexmit = 0, Model1_flag = *Model1_ack_flag;
 bool Model1_do_lost = Model1_is_dupack || ((Model1_flag & 0x20) &&
        (Model1_tcp_fackets_out(Model1_tp) > Model1_tp->Model1_reordering));

 if (({ int Model1___ret_warn_on = !!(!Model1_tp->Model1_packets_out && Model1_tp->Model1_sacked_out); __builtin_expect(!!(Model1___ret_warn_on), 0); }))
  Model1_tp->Model1_sacked_out = 0;
 if (({ int Model1___ret_warn_on = !!(!Model1_tp->Model1_sacked_out && Model1_tp->Model1_fackets_out); __builtin_expect(!!(Model1___ret_warn_on), 0); }))
  Model1_tp->Model1_fackets_out = 0;

 /* Now state machine starts.
	 * A. ECE, hence prohibit cwnd undoing, the reduction is required. */
 if (Model1_flag & 0x40)
  Model1_tp->Model1_prior_ssthresh = 0;

 /* B. In all the states check for reneging SACKs. */
 if (Model1_tcp_check_sack_reneging(Model1_sk, Model1_flag))
  return;

 /* C. Check consistency of the current state. */
 ({ int Model1___ret_warn_on = !!(Model1_tcp_left_out(Model1_tp) > Model1_tp->Model1_packets_out); __builtin_expect(!!(Model1___ret_warn_on), 0); });

 /* D. Check state exit conditions. State can be terminated
	 *    when high_seq is ACKed. */
 if (Model1_icsk->Model1_icsk_ca_state == Model1_TCP_CA_Open) {
  ({ int Model1___ret_warn_on = !!(Model1_tp->Model1_retrans_out != 0); __builtin_expect(!!(Model1___ret_warn_on), 0); });
  Model1_tp->Model1_retrans_stamp = 0;
 } else if (!Model1_before(Model1_tp->Model1_snd_una, Model1_tp->Model1_high_seq)) {
  switch (Model1_icsk->Model1_icsk_ca_state) {
  case Model1_TCP_CA_CWR:
   /* CWR is to be held something *above* high_seq
			 * is ACKed for CWR bit to reach receiver. */
   if (Model1_tp->Model1_snd_una != Model1_tp->Model1_high_seq) {
    Model1_tcp_end_cwnd_reduction(Model1_sk);
    Model1_tcp_set_ca_state(Model1_sk, Model1_TCP_CA_Open);
   }
   break;

  case Model1_TCP_CA_Recovery:
   if (Model1_tcp_is_reno(Model1_tp))
    Model1_tcp_reset_reno_sack(Model1_tp);
   if (Model1_tcp_try_undo_recovery(Model1_sk))
    return;
   Model1_tcp_end_cwnd_reduction(Model1_sk);
   break;
  }
 }

 /* Use RACK to detect loss */
 if (Model1_sysctl_tcp_recovery & 0x1 &&
     Model1_tcp_rack_mark_lost(Model1_sk)) {
  Model1_flag |= 0x80;
  *Model1_ack_flag |= 0x80;
 }

 /* E. Process state. */
 switch (Model1_icsk->Model1_icsk_ca_state) {
 case Model1_TCP_CA_Recovery:
  if (!(Model1_flag & 0x400)) {
   if (Model1_tcp_is_reno(Model1_tp) && Model1_is_dupack)
    Model1_tcp_add_reno_sack(Model1_sk);
  } else {
   if (Model1_tcp_try_undo_partial(Model1_sk, Model1_acked))
    return;
   /* Partial ACK arrived. Force fast retransmit. */
   Model1_do_lost = Model1_tcp_is_reno(Model1_tp) ||
      Model1_tcp_fackets_out(Model1_tp) > Model1_tp->Model1_reordering;
  }
  if (Model1_tcp_try_undo_dsack(Model1_sk)) {
   Model1_tcp_try_keep_open(Model1_sk);
   return;
  }
  break;
 case Model1_TCP_CA_Loss:
  Model1_tcp_process_loss(Model1_sk, Model1_flag, Model1_is_dupack, Model1_rexmit);
  if (Model1_icsk->Model1_icsk_ca_state != Model1_TCP_CA_Open &&
      !(Model1_flag & 0x80))
   return;
  /* Change state if cwnd is undone or retransmits are lost */
 default:
  if (Model1_tcp_is_reno(Model1_tp)) {
   if (Model1_flag & 0x400)
    Model1_tcp_reset_reno_sack(Model1_tp);
   if (Model1_is_dupack)
    Model1_tcp_add_reno_sack(Model1_sk);
  }

  if (Model1_icsk->Model1_icsk_ca_state <= Model1_TCP_CA_Disorder)
   Model1_tcp_try_undo_dsack(Model1_sk);

  if (!Model1_tcp_time_to_recover(Model1_sk, Model1_flag)) {
   Model1_tcp_try_to_open(Model1_sk, Model1_flag);
   return;
  }

  /* MTU probe failure: don't reduce cwnd */
  if (Model1_icsk->Model1_icsk_ca_state < Model1_TCP_CA_CWR &&
      Model1_icsk->Model1_icsk_mtup.Model1_probe_size &&
      Model1_tp->Model1_snd_una == Model1_tp->Model1_mtu_probe.Model1_probe_seq_start) {
   Model1_tcp_mtup_probe_failed(Model1_sk);
   /* Restores the reduction we did in tcp_mtup_probe() */
   Model1_tp->Model1_snd_cwnd++;
   Model1_tcp_simple_retransmit(Model1_sk);
   return;
  }

  /* Otherwise enter Recovery state */
  Model1_tcp_enter_recovery(Model1_sk, (Model1_flag & 0x40));
  Model1_fast_rexmit = 1;
 }

 if (Model1_do_lost)
  Model1_tcp_update_scoreboard(Model1_sk, Model1_fast_rexmit);
 *Model1_rexmit = 1;
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
static void Model1_tcp_update_rtt_min(struct Model1_sock *Model1_sk, Model1_u32 Model1_rtt_us)
{
 const Model1_u32 Model1_now = ((__u32)(Model1_jiffies)), Model1_wlen = Model1_sysctl_tcp_min_rtt_wlen * 1000;
 struct Model1_rtt_meas *Model1_m = Model1_tcp_sk(Model1_sk)->Model1_rtt_min;
 struct Model1_rtt_meas Model1_rttm = {
  .Model1_rtt = __builtin_expect(!!(Model1_rtt_us), 1) ? Model1_rtt_us : Model1_jiffies_to_usecs(1),
  .Model1_ts = Model1_now,
 };
 Model1_u32 Model1_elapsed;

 /* Check if the new measurement updates the 1st, 2nd, or 3rd choices */
 if (__builtin_expect(!!(Model1_rttm.Model1_rtt <= Model1_m[0].Model1_rtt), 0))
  Model1_m[0] = Model1_m[1] = Model1_m[2] = Model1_rttm;
 else if (Model1_rttm.Model1_rtt <= Model1_m[1].Model1_rtt)
  Model1_m[1] = Model1_m[2] = Model1_rttm;
 else if (Model1_rttm.Model1_rtt <= Model1_m[2].Model1_rtt)
  Model1_m[2] = Model1_rttm;

 Model1_elapsed = Model1_now - Model1_m[0].Model1_ts;
 if (__builtin_expect(!!(Model1_elapsed > Model1_wlen), 0)) {
  /* Passed entire window without a new min so make 2nd choice
		 * the new min & 3rd choice the new 2nd. So forth and so on.
		 */
  Model1_m[0] = Model1_m[1];
  Model1_m[1] = Model1_m[2];
  Model1_m[2] = Model1_rttm;
  if (Model1_now - Model1_m[0].Model1_ts > Model1_wlen) {
   Model1_m[0] = Model1_m[1];
   Model1_m[1] = Model1_rttm;
   if (Model1_now - Model1_m[0].Model1_ts > Model1_wlen)
    Model1_m[0] = Model1_rttm;
  }
 } else if (Model1_m[1].Model1_ts == Model1_m[0].Model1_ts && Model1_elapsed > Model1_wlen / 4) {
  /* Passed a quarter of the window without a new min so
		 * take 2nd choice from the 2nd quarter of the window.
		 */
  Model1_m[2] = Model1_m[1] = Model1_rttm;
 } else if (Model1_m[2].Model1_ts == Model1_m[1].Model1_ts && Model1_elapsed > Model1_wlen / 2) {
  /* Passed half the window without a new min so take the 3rd
		 * choice from the last half of the window.
		 */
  Model1_m[2] = Model1_rttm;
 }
}

static inline __attribute__((no_instrument_function)) bool Model1_tcp_ack_update_rtt(struct Model1_sock *Model1_sk, const int Model1_flag,
          long Model1_seq_rtt_us, long Model1_sack_rtt_us,
          long Model1_ca_rtt_us)
{
 const struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 /* Prefer RTT measured from ACK's timing to TS-ECR. This is because
	 * broken middle-boxes or peers may corrupt TS-ECR fields. But
	 * Karn's algorithm forbids taking RTT if some retransmitted data
	 * is acked (RFC6298).
	 */
 if (Model1_seq_rtt_us < 0)
  Model1_seq_rtt_us = Model1_sack_rtt_us;

 /* RTTM Rule: A TSecr value received in a segment is used to
	 * update the averaged RTT measurement only if the segment
	 * acknowledges some new data, i.e., only if it advances the
	 * left edge of the send window.
	 * See draft-ietf-tcplw-high-performance-00, section 3.3.
	 */
 if (Model1_seq_rtt_us < 0 && Model1_tp->Model1_rx_opt.Model1_saw_tstamp && Model1_tp->Model1_rx_opt.Model1_rcv_tsecr &&
     Model1_flag & (0x04|0x10))
  Model1_seq_rtt_us = Model1_ca_rtt_us = Model1_jiffies_to_usecs(((__u32)(Model1_jiffies)) -
         Model1_tp->Model1_rx_opt.Model1_rcv_tsecr);
 if (Model1_seq_rtt_us < 0)
  return false;

 /* ca_rtt_us >= 0 is counting on the invariant that ca_rtt_us is
	 * always taken together with ACK, SACK, or TS-opts. Any negative
	 * values will be skipped with the seq_rtt_us < 0 check above.
	 */
 Model1_tcp_update_rtt_min(Model1_sk, Model1_ca_rtt_us);
 Model1_tcp_rtt_estimator(Model1_sk, Model1_seq_rtt_us);
 Model1_tcp_set_rto(Model1_sk);

 /* RFC6298: only reset backoff on valid RTT measurement. */
 Model1_inet_csk(Model1_sk)->Model1_icsk_backoff = 0;
 return true;
}

/* Compute time elapsed between (last) SYNACK and the ACK completing 3WHS. */
void Model1_tcp_synack_rtt_meas(struct Model1_sock *Model1_sk, struct Model1_request_sock *Model1_req)
{
 long Model1_rtt_us = -1L;

 if (Model1_req && !Model1_req->Model1_num_retrans && Model1_tcp_rsk(Model1_req)->Model1_snt_synack.Model1_v64) {
  struct Model1_skb_mstamp Model1_now;

  Model1_skb_mstamp_get(&Model1_now);
  Model1_rtt_us = Model1_skb_mstamp_us_delta(&Model1_now, &Model1_tcp_rsk(Model1_req)->Model1_snt_synack);
 }

 Model1_tcp_ack_update_rtt(Model1_sk, 0x10, Model1_rtt_us, -1L, Model1_rtt_us);
}


static void Model1_tcp_cong_avoid(struct Model1_sock *Model1_sk, Model1_u32 Model1_ack, Model1_u32 Model1_acked)
{
 const struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);

 Model1_icsk->Model1_icsk_ca_ops->Model1_cong_avoid(Model1_sk, Model1_ack, Model1_acked);
 Model1_tcp_sk(Model1_sk)->Model1_snd_cwnd_stamp = ((__u32)(Model1_jiffies));
}

/* Restart timer after forward progress on connection.
 * RFC2988 recommends to restart timer to now+rto.
 */
void Model1_tcp_rearm_rto(struct Model1_sock *Model1_sk)
{
 const struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 /* If the retrans timer is currently being used by Fast Open
	 * for SYN-ACK retrans purpose, stay put.
	 */
 if (Model1_tp->Model1_fastopen_rsk)
  return;

 if (!Model1_tp->Model1_packets_out) {
  Model1_inet_csk_clear_xmit_timer(Model1_sk, 1);
 } else {
  Model1_u32 Model1_rto = Model1_inet_csk(Model1_sk)->Model1_icsk_rto;
  /* Offset the time elapsed after installing regular RTO */
  if (Model1_icsk->Model1_icsk_pending == 4 ||
      Model1_icsk->Model1_icsk_pending == 5) {
   struct Model1_sk_buff *Model1_skb = Model1_tcp_write_queue_head(Model1_sk);
   const Model1_u32 Model1_rto_time_stamp =
    Model1_tcp_skb_timestamp(Model1_skb) + Model1_rto;
   Model1_s32 Model1_delta = (Model1_s32)(Model1_rto_time_stamp - ((__u32)(Model1_jiffies)));
   /* delta may not be positive if the socket is locked
			 * when the retrans timer fires and is rescheduled.
			 */
   if (Model1_delta > 0)
    Model1_rto = Model1_delta;
  }
  Model1_inet_csk_reset_xmit_timer(Model1_sk, 1, Model1_rto,
       ((unsigned)(120*1000)));
 }
}

/* This function is called when the delayed ER timer fires. TCP enters
 * fast recovery and performs fast-retransmit.
 */
void Model1_tcp_resume_early_retransmit(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 Model1_tcp_rearm_rto(Model1_sk);

 /* Stop if ER is disabled after the delayed ER timer is scheduled */
 if (!Model1_tp->Model1_do_early_retrans)
  return;

 Model1_tcp_enter_recovery(Model1_sk, false);
 Model1_tcp_update_scoreboard(Model1_sk, 1);
 Model1_tcp_xmit_retransmit_queue(Model1_sk);
}

/* If we get here, the whole TSO packet has not been acked. */
static Model1_u32 Model1_tcp_tso_acked(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 Model1_u32 Model1_packets_acked;

 do { if (!Model1_before(Model1_tp->Model1_snd_una, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq)) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);

 Model1_packets_acked = Model1_tcp_skb_pcount(Model1_skb);
 if (Model1_tcp_trim_head(Model1_sk, Model1_skb, Model1_tp->Model1_snd_una - ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq))
  return 0;
 Model1_packets_acked -= Model1_tcp_skb_pcount(Model1_skb);

 if (Model1_packets_acked) {
  do { if (Model1_tcp_skb_pcount(Model1_skb) == 0) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);
  do { if (!Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq)) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);
 }

 return Model1_packets_acked;
}

static void Model1_tcp_ack_tstamp(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb,
      Model1_u32 Model1_prior_snd_una)
{
 const struct Model1_skb_shared_info *Model1_shinfo;

 /* Avoid cache line misses to get skb_shinfo() and shinfo->tx_flags */
 if (__builtin_expect(!!(!((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_txstamp_ack), 1))
  return;

 Model1_shinfo = ((struct Model1_skb_shared_info *)(Model1_skb_end_pointer(Model1_skb)));
 if (!Model1_before(Model1_shinfo->Model1_tskey, Model1_prior_snd_una) &&
     Model1_before(Model1_shinfo->Model1_tskey, Model1_tcp_sk(Model1_sk)->Model1_snd_una))
  Model1___skb_tstamp_tx(Model1_skb, ((void *)0), Model1_sk, Model1_SCM_TSTAMP_ACK);
}

/* Remove acknowledged frames from the retransmission queue. If our packet
 * is before the ack sequence we can discard it as it's confirmed to have
 * arrived at the other end.
 */
static int Model1_tcp_clean_rtx_queue(struct Model1_sock *Model1_sk, int Model1_prior_fackets,
          Model1_u32 Model1_prior_snd_una, int *Model1_acked,
          struct Model1_tcp_sacktag_state *Model1_sack)
{
 const struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
 struct Model1_skb_mstamp Model1_first_ackt, Model1_last_ackt, Model1_now;
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 Model1_u32 Model1_prior_sacked = Model1_tp->Model1_sacked_out;
 Model1_u32 Model1_reord = Model1_tp->Model1_packets_out;
 bool Model1_fully_acked = true;
 long Model1_sack_rtt_us = -1L;
 long Model1_seq_rtt_us = -1L;
 long Model1_ca_rtt_us = -1L;
 struct Model1_sk_buff *Model1_skb;
 Model1_u32 Model1_pkts_acked = 0;
 Model1_u32 Model1_last_in_flight = 0;
 bool Model1_rtt_update;
 int Model1_flag = 0;

 Model1_first_ackt.Model1_v64 = 0;

 while ((Model1_skb = Model1_tcp_write_queue_head(Model1_sk)) && Model1_skb != Model1_tcp_send_head(Model1_sk)) {
  struct Model1_tcp_skb_cb *Model1_scb = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]));
  Model1_u8 Model1_sacked = Model1_scb->Model1_sacked;
  Model1_u32 Model1_acked_pcount;

  Model1_tcp_ack_tstamp(Model1_sk, Model1_skb, Model1_prior_snd_una);

  /* Determine how many packets and what bytes were acked, tso and else */
  if (Model1_before(Model1_tp->Model1_snd_una, Model1_scb->Model1_end_seq)) {
   if (Model1_tcp_skb_pcount(Model1_skb) == 1 ||
       !Model1_before(Model1_scb->Model1_seq, Model1_tp->Model1_snd_una))
    break;

   Model1_acked_pcount = Model1_tcp_tso_acked(Model1_sk, Model1_skb);
   if (!Model1_acked_pcount)
    break;

   Model1_fully_acked = false;
  } else {
   /* Speedup tcp_unlink_write_queue() and next loop */
   Model1_prefetchw(Model1_skb->Model1_next);
   Model1_acked_pcount = Model1_tcp_skb_pcount(Model1_skb);
  }

  if (__builtin_expect(!!(Model1_sacked & (0x02|0x80| 0x10)), 0)) {
   if (Model1_sacked & 0x02)
    Model1_tp->Model1_retrans_out -= Model1_acked_pcount;
   Model1_flag |= 0x08;
  } else if (!(Model1_sacked & 0x01)) {
   Model1_last_ackt = Model1_skb->Model1_skb_mstamp;
   ({ int Model1___ret_warn_on = !!(Model1_last_ackt.Model1_v64 == 0); __builtin_expect(!!(Model1___ret_warn_on), 0); });
   if (!Model1_first_ackt.Model1_v64)
    Model1_first_ackt = Model1_last_ackt;

   Model1_last_in_flight = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_tx.Model1_in_flight;
   Model1_reord = ({ typeof(Model1_pkts_acked) Model1__min1 = (Model1_pkts_acked); typeof(Model1_reord) Model1__min2 = (Model1_reord); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
   if (!Model1_before(Model1_tp->Model1_high_seq, Model1_scb->Model1_end_seq))
    Model1_flag |= 0x200;
  }

  if (Model1_sacked & 0x01) {
   Model1_tp->Model1_sacked_out -= Model1_acked_pcount;
  } else if (Model1_tcp_is_sack(Model1_tp)) {
   Model1_tp->Model1_delivered += Model1_acked_pcount;
   if (!Model1_tcp_skb_spurious_retrans(Model1_tp, Model1_skb))
    Model1_tcp_rack_advance(Model1_tp, &Model1_skb->Model1_skb_mstamp, Model1_sacked);
  }
  if (Model1_sacked & 0x04)
   Model1_tp->Model1_lost_out -= Model1_acked_pcount;

  Model1_tp->Model1_packets_out -= Model1_acked_pcount;
  Model1_pkts_acked += Model1_acked_pcount;

  /* Initial outgoing SYN's get put onto the write_queue
		 * just like anything else we transmit.  It is not
		 * true data, and if we misinform our callers that
		 * this ACK acks real data, we will erroneously exit
		 * connection startup slow start one packet too
		 * quickly.  This is severely frowned upon behavior.
		 */
  if (__builtin_expect(!!(!(Model1_scb->Model1_tcp_flags & 0x02)), 1)) {
   Model1_flag |= 0x04;
  } else {
   Model1_flag |= 0x10;
   Model1_tp->Model1_retrans_stamp = 0;
  }

  if (!Model1_fully_acked)
   break;

  Model1_tcp_unlink_write_queue(Model1_skb, Model1_sk);
  Model1_sk_wmem_free_skb(Model1_sk, Model1_skb);
  if (__builtin_expect(!!(Model1_skb == Model1_tp->Model1_retransmit_skb_hint), 0))
   Model1_tp->Model1_retransmit_skb_hint = ((void *)0);
  if (__builtin_expect(!!(Model1_skb == Model1_tp->Model1_lost_skb_hint), 0))
   Model1_tp->Model1_lost_skb_hint = ((void *)0);
 }

 if (__builtin_expect(!!(Model1_between(Model1_tp->Model1_snd_up, Model1_prior_snd_una, Model1_tp->Model1_snd_una)), 1))
  Model1_tp->Model1_snd_up = Model1_tp->Model1_snd_una;

 if (Model1_skb && (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked & 0x01))
  Model1_flag |= 0x2000;

 Model1_skb_mstamp_get(&Model1_now);
 if (__builtin_expect(!!(Model1_first_ackt.Model1_v64), 1) && !(Model1_flag & 0x08)) {
  Model1_seq_rtt_us = Model1_skb_mstamp_us_delta(&Model1_now, &Model1_first_ackt);
  Model1_ca_rtt_us = Model1_skb_mstamp_us_delta(&Model1_now, &Model1_last_ackt);
 }
 if (Model1_sack->Model1_first_sackt.Model1_v64) {
  Model1_sack_rtt_us = Model1_skb_mstamp_us_delta(&Model1_now, &Model1_sack->Model1_first_sackt);
  Model1_ca_rtt_us = Model1_skb_mstamp_us_delta(&Model1_now, &Model1_sack->Model1_last_sackt);
 }

 Model1_rtt_update = Model1_tcp_ack_update_rtt(Model1_sk, Model1_flag, Model1_seq_rtt_us, Model1_sack_rtt_us,
     Model1_ca_rtt_us);

 if (Model1_flag & (0x04|0x10)) {
  Model1_tcp_rearm_rto(Model1_sk);
  if (__builtin_expect(!!(Model1_icsk->Model1_icsk_mtup.Model1_probe_size && !Model1_before(Model1_tp->Model1_snd_una, Model1_tp->Model1_mtu_probe.Model1_probe_seq_end)), 0)) {

   Model1_tcp_mtup_probe_success(Model1_sk);
  }

  if (Model1_tcp_is_reno(Model1_tp)) {
   Model1_tcp_remove_reno_sacks(Model1_sk, Model1_pkts_acked);
  } else {
   int Model1_delta;

   /* Non-retransmitted hole got filled? That's reordering */
   if (Model1_reord < Model1_prior_fackets)
    Model1_tcp_update_reordering(Model1_sk, Model1_tp->Model1_fackets_out - Model1_reord, 0);

   Model1_delta = Model1_tcp_is_fack(Model1_tp) ? Model1_pkts_acked :
        Model1_prior_sacked - Model1_tp->Model1_sacked_out;
   Model1_tp->Model1_lost_cnt_hint -= ({ typeof(Model1_tp->Model1_lost_cnt_hint) Model1__min1 = (Model1_tp->Model1_lost_cnt_hint); typeof(Model1_delta) Model1__min2 = (Model1_delta); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
  }

  Model1_tp->Model1_fackets_out -= ({ typeof(Model1_pkts_acked) Model1__min1 = (Model1_pkts_acked); typeof(Model1_tp->Model1_fackets_out) Model1__min2 = (Model1_tp->Model1_fackets_out); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });

 } else if (Model1_skb && Model1_rtt_update && Model1_sack_rtt_us >= 0 &&
     Model1_sack_rtt_us > Model1_skb_mstamp_us_delta(&Model1_now, &Model1_skb->Model1_skb_mstamp)) {
  /* Do not re-arm RTO if the sack RTT is measured from data sent
		 * after when the head was last (re)transmitted. Otherwise the
		 * timeout may continue to extend in loss recovery.
		 */
  Model1_tcp_rearm_rto(Model1_sk);
 }

 if (Model1_icsk->Model1_icsk_ca_ops->Model1_pkts_acked) {
  struct Model1_ack_sample Model1_sample = { .Model1_pkts_acked = Model1_pkts_acked,
          .Model1_rtt_us = Model1_ca_rtt_us,
          .Model1_in_flight = Model1_last_in_flight };

  Model1_icsk->Model1_icsk_ca_ops->Model1_pkts_acked(Model1_sk, &Model1_sample);
 }


 ({ int Model1___ret_warn_on = !!((int)Model1_tp->Model1_sacked_out < 0); __builtin_expect(!!(Model1___ret_warn_on), 0); });
 ({ int Model1___ret_warn_on = !!((int)Model1_tp->Model1_lost_out < 0); __builtin_expect(!!(Model1___ret_warn_on), 0); });
 ({ int Model1___ret_warn_on = !!((int)Model1_tp->Model1_retrans_out < 0); __builtin_expect(!!(Model1___ret_warn_on), 0); });
 if (!Model1_tp->Model1_packets_out && Model1_tcp_is_sack(Model1_tp)) {
  Model1_icsk = Model1_inet_csk(Model1_sk);
  if (Model1_tp->Model1_lost_out) {
   ({ do { if (0) Model1_printk("\001" "7" "TCP: " "Leak l=%u %d\n", Model1_tp->Model1_lost_out, Model1_icsk->Model1_icsk_ca_state); } while (0); 0; });

   Model1_tp->Model1_lost_out = 0;
  }
  if (Model1_tp->Model1_sacked_out) {
   ({ do { if (0) Model1_printk("\001" "7" "TCP: " "Leak s=%u %d\n", Model1_tp->Model1_sacked_out, Model1_icsk->Model1_icsk_ca_state); } while (0); 0; });

   Model1_tp->Model1_sacked_out = 0;
  }
  if (Model1_tp->Model1_retrans_out) {
   ({ do { if (0) Model1_printk("\001" "7" "TCP: " "Leak r=%u %d\n", Model1_tp->Model1_retrans_out, Model1_icsk->Model1_icsk_ca_state); } while (0); 0; });

   Model1_tp->Model1_retrans_out = 0;
  }
 }

 *Model1_acked = Model1_pkts_acked;
 return Model1_flag;
}

static void Model1_tcp_ack_probe(struct Model1_sock *Model1_sk)
{
 const struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);

 /* Was it a usable window open? */

 if (!Model1_before(Model1_tcp_wnd_end(Model1_tp), ((struct Model1_tcp_skb_cb *)&((Model1_tcp_send_head(Model1_sk))->Model1_cb[0]))->Model1_end_seq)) {
  Model1_icsk->Model1_icsk_backoff = 0;
  Model1_inet_csk_clear_xmit_timer(Model1_sk, 3);
  /* Socket must be waked up by subsequent tcp_data_snd_check().
		 * This function is not for random using!
		 */
 } else {
  unsigned long Model1_when = Model1_tcp_probe0_when(Model1_sk, ((unsigned)(120*1000)));

  Model1_inet_csk_reset_xmit_timer(Model1_sk, 3,
       Model1_when, ((unsigned)(120*1000)));
 }
}

static inline __attribute__((no_instrument_function)) bool Model1_tcp_ack_is_dubious(const struct Model1_sock *Model1_sk, const int Model1_flag)
{
 return !(Model1_flag & (0x01|0x02|(0x04|0x10))) || (Model1_flag & (0x20|0x40)) ||
  Model1_inet_csk(Model1_sk)->Model1_icsk_ca_state != Model1_TCP_CA_Open;
}

/* Decide wheather to run the increase function of congestion control. */
static inline __attribute__((no_instrument_function)) bool Model1_tcp_may_raise_cwnd(const struct Model1_sock *Model1_sk, const int Model1_flag)
{
 /* If reordering is high then always grow cwnd whenever data is
	 * delivered regardless of its ordering. Otherwise stay conservative
	 * and only grow cwnd on in-order delivery (RFC5681). A stretched ACK w/
	 * new SACK or ECE mark may first advance cwnd here and later reduce
	 * cwnd in tcp_fastretrans_alert() based on more states.
	 */
 if (Model1_tcp_sk(Model1_sk)->Model1_reordering > Model1_sock_net(Model1_sk)->Model1_ipv4.Model1_sysctl_tcp_reordering)
  return Model1_flag & ((0x04|0x10)|0x20);

 return Model1_flag & 0x04;
}

/* The "ultimate" congestion control function that aims to replace the rigid
 * cwnd increase and decrease control (tcp_cong_avoid,tcp_*cwnd_reduction).
 * It's called toward the end of processing an ACK with precise rate
 * information. All transmission or retransmission are delayed afterwards.
 */
static void Model1_tcp_cong_control(struct Model1_sock *Model1_sk, Model1_u32 Model1_ack, Model1_u32 Model1_acked_sacked,
        int Model1_flag)
{
 if (Model1_tcp_in_cwnd_reduction(Model1_sk)) {
  /* Reduce cwnd if state mandates */
  Model1_tcp_cwnd_reduction(Model1_sk, Model1_acked_sacked, Model1_flag);
 } else if (Model1_tcp_may_raise_cwnd(Model1_sk, Model1_flag)) {
  /* Advance cwnd if state allows */
  Model1_tcp_cong_avoid(Model1_sk, Model1_ack, Model1_acked_sacked);
 }
 Model1_tcp_update_pacing_rate(Model1_sk);
}

/* Check that window update is acceptable.
 * The function assumes that snd_una<=ack<=snd_next.
 */
static inline __attribute__((no_instrument_function)) bool Model1_tcp_may_update_window(const struct Model1_tcp_sock *Model1_tp,
     const Model1_u32 Model1_ack, const Model1_u32 Model1_ack_seq,
     const Model1_u32 Model1_nwin)
{
 return Model1_before(Model1_tp->Model1_snd_una, Model1_ack) ||
  Model1_before(Model1_tp->Model1_snd_wl1, Model1_ack_seq) ||
  (Model1_ack_seq == Model1_tp->Model1_snd_wl1 && Model1_nwin > Model1_tp->Model1_snd_wnd);
}

/* If we update tp->snd_una, also update tp->bytes_acked */
static void Model1_tcp_snd_una_update(struct Model1_tcp_sock *Model1_tp, Model1_u32 Model1_ack)
{
 Model1_u32 Model1_delta = Model1_ack - Model1_tp->Model1_snd_una;

 Model1_sock_owned_by_me((struct Model1_sock *)Model1_tp);
 Model1_u64_stats_update_begin_raw(&Model1_tp->Model1_syncp);
 Model1_tp->Model1_bytes_acked += Model1_delta;
 Model1_u64_stats_update_end_raw(&Model1_tp->Model1_syncp);
 Model1_tp->Model1_snd_una = Model1_ack;
}

/* If we update tp->rcv_nxt, also update tp->bytes_received */
static void Model1_tcp_rcv_nxt_update(struct Model1_tcp_sock *Model1_tp, Model1_u32 Model1_seq)
{
 Model1_u32 Model1_delta = Model1_seq - Model1_tp->Model1_rcv_nxt;

 Model1_sock_owned_by_me((struct Model1_sock *)Model1_tp);
 Model1_u64_stats_update_begin_raw(&Model1_tp->Model1_syncp);
 Model1_tp->Model1_bytes_received += Model1_delta;
 Model1_u64_stats_update_end_raw(&Model1_tp->Model1_syncp);
 Model1_tp->Model1_rcv_nxt = Model1_seq;
}

/* Update our send window.
 *
 * Window update algorithm, described in RFC793/RFC1122 (used in linux-2.2
 * and in FreeBSD. NetBSD's one is even worse.) is wrong.
 */
static int Model1_tcp_ack_update_window(struct Model1_sock *Model1_sk, const struct Model1_sk_buff *Model1_skb, Model1_u32 Model1_ack,
     Model1_u32 Model1_ack_seq)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 int Model1_flag = 0;
 Model1_u32 Model1_nwin = (__builtin_constant_p((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_window))) ? ((Model1___u16)( (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_window)) & (Model1___u16)0x00ffU) << 8) | (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_window)) & (Model1___u16)0xff00U) >> 8))) : Model1___fswab16(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_window)));

 if (__builtin_expect(!!(!Model1_tcp_hdr(Model1_skb)->Model1_syn), 1))
  Model1_nwin <<= Model1_tp->Model1_rx_opt.Model1_snd_wscale;

 if (Model1_tcp_may_update_window(Model1_tp, Model1_ack, Model1_ack_seq, Model1_nwin)) {
  Model1_flag |= 0x02;
  Model1_tcp_update_wl(Model1_tp, Model1_ack_seq);

  if (Model1_tp->Model1_snd_wnd != Model1_nwin) {
   Model1_tp->Model1_snd_wnd = Model1_nwin;

   /* Note, it is the only place, where
			 * fast path is recovered for sending TCP.
			 */
   Model1_tp->Model1_pred_flags = 0;
   Model1_tcp_fast_path_check(Model1_sk);

   if (Model1_tcp_send_head(Model1_sk))
    Model1_tcp_slow_start_after_idle_check(Model1_sk);

   if (Model1_nwin > Model1_tp->Model1_max_window) {
    Model1_tp->Model1_max_window = Model1_nwin;
    Model1_tcp_sync_mss(Model1_sk, Model1_inet_csk(Model1_sk)->Model1_icsk_pmtu_cookie);
   }
  }
 }

 Model1_tcp_snd_una_update(Model1_tp, Model1_ack);

 return Model1_flag;
}

static bool Model1___tcp_oow_rate_limited(struct Model1_net *Model1_net, int Model1_mib_idx,
       Model1_u32 *Model1_last_oow_ack_time)
{
#if CY_ABSTRACT2
    //Have to do such abstraction. During 3-way handshake, new generated sock->last_oow_ack_time (e.g., req, new_sk) is initialized with current jiffies. Because jiffies in our model is alway fixed, for packet with SYN flag, it's impossible to send any packet out. But that's not true in reality. So we abstract the codes to remove such rate limite. In practice, this rate limit makes attacker slower, but not impossible (i.e., firstly send 1 spoofed packet with SYN to trigger challenge ACK, then use data payload to bypass the resctrion. In newest patch, we cannot use data packet to bypass it)
    return false;
#else
 if (*Model1_last_oow_ack_time) {
  Model1_s32 Model1_elapsed = (Model1_s32)(((__u32)(Model1_jiffies)) - *Model1_last_oow_ack_time);

  if (0 <= Model1_elapsed && Model1_elapsed < Model1_sysctl_tcp_invalid_ratelimit) {
   (Model1_cy_linux_mib.Model1_mibs[Model1_mib_idx] += 1);
   return true; /* rate-limited: don't send yet! */
  }
 }

 *Model1_last_oow_ack_time = ((__u32)(Model1_jiffies));

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
bool Model1_tcp_oow_rate_limited(struct Model1_net *Model1_net, const struct Model1_sk_buff *Model1_skb,
     int Model1_mib_idx, Model1_u32 *Model1_last_oow_ack_time)
{
 /* Data packets without SYNs are not likely part of an ACK loop. */
 if ((((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq != ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq) &&
     !Model1_tcp_hdr(Model1_skb)->Model1_syn)
  return false;

 return Model1___tcp_oow_rate_limited(Model1_net, Model1_mib_idx, Model1_last_oow_ack_time);
}

/* RFC 5961 7 [ACK Throttling] */
#if CY_ABSTRACT3
static void Model1_tcp_send_challenge_ack(struct Model1_sock *Model1_sk, const struct Model1_sk_buff *Model1_skb)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 Model1_u32 Model1_count, Model1_now;

 if (Model1___tcp_oow_rate_limited(Model1_sock_net(Model1_sk),
       Model1_LINUX_MIB_TCPACKSKIPPEDCHALLENGE,
       &Model1_tp->Model1_last_oow_ack_time))
  return;

 Model1_now = Model1_jiffies / 1000;
 if (Model1_now != Model1_challenge_timestamp){
     Model1_challenge_timestamp = Model1_now;
     Model1_challenge_count = 0;
 }

 //printf("Model1_challenge_count++\n");
 if (++Model1_challenge_count  <= Model1_sysctl_tcp_challenge_ack_limit){
    //printf("Model1_challenge_count %d, %d\n", Model1_challenge_count, Model1_sysctl_tcp_challenge_ack_limit);
    (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPCHALLENGEACK] += 1);
     Model1_tcp_send_ack(Model1_sk);
 }
}
#else
static void Model1_tcp_send_challenge_ack(struct Model1_sock *Model1_sk, const struct Model1_sk_buff *Model1_skb)
{
#if !CY_ABSTRACT3 //static variable inside function cannot be visited
 /* unprotected vars, we dont care of overwrites */
 static Model1_u32 Model1_challenge_timestamp;
 static unsigned int Model1_challenge_count;
#endif
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 Model1_u32 Model1_count, Model1_now;

 /* First check our per-socket dupack rate limit. */
//#if CY_ABSTRACT1
// if (Model1_tcp_oow_rate_limited(Model1_sock_net(Model1_sk), Model1_skb,
//#else
 if (Model1___tcp_oow_rate_limited(Model1_sock_net(Model1_sk),
//#endif
       Model1_LINUX_MIB_TCPACKSKIPPEDCHALLENGE,
       &Model1_tp->Model1_last_oow_ack_time))
  return;

 /* Then check host-wide RFC 5961 rate limit. */
 Model1_now = Model1_jiffies / 1000;
 if (Model1_now != Model1_challenge_timestamp) {
  Model1_u32 Model1_half = (Model1_sysctl_tcp_challenge_ack_limit + 1) >> 1;

  Model1_challenge_timestamp = Model1_now;
  ({ union { typeof(Model1_challenge_count) Model1___val; char Model1___c[1]; } Model1___u = { .Model1___val = ( typeof(Model1_challenge_count)) (Model1_half + Model1_prandom_u32_max(Model1_sysctl_tcp_challenge_ack_limit)) }; Model1___write_once_size(&(Model1_challenge_count), Model1___u.Model1___c, sizeof(Model1_challenge_count)); Model1___u.Model1___val; });

 }
 Model1_count = ({ union { typeof(Model1_challenge_count) Model1___val; char Model1___c[1]; } Model1___u; if (1) Model1___read_once_size(&(Model1_challenge_count), Model1___u.Model1___c, sizeof(Model1_challenge_count)); else Model1___read_once_size_nocheck(&(Model1_challenge_count), Model1___u.Model1___c, sizeof(Model1_challenge_count)); Model1___u.Model1___val; });
 if (Model1_count > 0) {
  ({ union { typeof(Model1_challenge_count) Model1___val; char Model1___c[1]; } Model1___u = { .Model1___val = ( typeof(Model1_challenge_count)) (Model1_count - 1) }; Model1___write_once_size(&(Model1_challenge_count), Model1___u.Model1___c, sizeof(Model1_challenge_count)); Model1___u.Model1___val; });
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPCHALLENGEACK] += 1);
  Model1_tcp_send_ack(Model1_sk);
 }
}
#endif

static void Model1_tcp_store_ts_recent(struct Model1_tcp_sock *Model1_tp)
{
 Model1_tp->Model1_rx_opt.Model1_ts_recent = Model1_tp->Model1_rx_opt.Model1_rcv_tsval;
 Model1_tp->Model1_rx_opt.Model1_ts_recent_stamp = Model1_get_seconds();
}

static void Model1_tcp_replace_ts_recent(struct Model1_tcp_sock *Model1_tp, Model1_u32 Model1_seq)
{
 if (Model1_tp->Model1_rx_opt.Model1_saw_tstamp && !Model1_before(Model1_tp->Model1_rcv_wup, Model1_seq)) {
  /* PAWS bug workaround wrt. ACK frames, the PAWS discard
		 * extra check below makes sure this can only happen
		 * for pure ACK frames.  -DaveM
		 *
		 * Not only, also it occurs for expired timestamps.
		 */

  if (Model1_tcp_paws_check(&Model1_tp->Model1_rx_opt, 0))
   Model1_tcp_store_ts_recent(Model1_tp);
 }
}

/* This routine deals with acks during a TLP episode.
 * We mark the end of a TLP episode on receiving TLP dupack or when
 * ack is after tlp_high_seq.
 * Ref: loss detection algorithm in draft-dukkipati-tcpm-tcp-loss-probe.
 */
static void Model1_tcp_process_tlp_ack(struct Model1_sock *Model1_sk, Model1_u32 Model1_ack, int Model1_flag)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 if (Model1_before(Model1_ack, Model1_tp->Model1_tlp_high_seq))
  return;

 if (Model1_flag & 0x800) {
  /* This DSACK means original and TLP probe arrived; no loss */
  Model1_tp->Model1_tlp_high_seq = 0;
 } else if (Model1_before(Model1_tp->Model1_tlp_high_seq, Model1_ack)) {
  /* ACK advances: there was a loss, so reduce cwnd. Reset
		 * tlp_high_seq in tcp_init_cwnd_reduction()
		 */
  Model1_tcp_init_cwnd_reduction(Model1_sk);
  Model1_tcp_set_ca_state(Model1_sk, Model1_TCP_CA_CWR);
  Model1_tcp_end_cwnd_reduction(Model1_sk);
  Model1_tcp_try_keep_open(Model1_sk);
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPLOSSPROBERECOVERY] += 1);

 } else if (!(Model1_flag & (0x400 |
        (0x01|0x02|(0x04|0x10)) | 0x20))) {
  /* Pure dupack: original and TLP probe arrived; no loss */
  Model1_tp->Model1_tlp_high_seq = 0;
 }
}

static inline __attribute__((no_instrument_function)) void Model1_tcp_in_ack_event(struct Model1_sock *Model1_sk, Model1_u32 Model1_flags)
{
 const struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);

#if !CY_ABSTRACT1
 if (Model1_icsk->Model1_icsk_ca_ops->Model1_in_ack_event)
  Model1_icsk->Model1_icsk_ca_ops->Model1_in_ack_event(Model1_sk, Model1_flags);
#endif
}

/* Congestion control has updated the cwnd already. So if we're in
 * loss recovery then now we do any new sends (for FRTO) or
 * retransmits (for CA_Loss or CA_recovery) that make sense.
 */
static void Model1_tcp_xmit_recovery(struct Model1_sock *Model1_sk, int Model1_rexmit)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 if (Model1_rexmit == 0)
  return;

 if (__builtin_expect(!!(Model1_rexmit == 2), 0)) {
  Model1___tcp_push_pending_frames(Model1_sk, Model1_tcp_current_mss(Model1_sk),
       1);
  if (Model1_before(Model1_tp->Model1_high_seq, Model1_tp->Model1_snd_nxt))
   return;
  Model1_tp->Model1_frto = 0;
 }
 Model1_tcp_xmit_retransmit_queue(Model1_sk);
}

/* This routine deals with incoming acks, but not outgoing ones. */
static int Model1_tcp_ack(struct Model1_sock *Model1_sk, const struct Model1_sk_buff *Model1_skb, int Model1_flag)
{
 struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_tcp_sacktag_state Model1_sack_state;
 Model1_u32 Model1_prior_snd_una = Model1_tp->Model1_snd_una;
 Model1_u32 Model1_ack_seq = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq;
 Model1_u32 Model1_ack = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_ack_seq;
 bool Model1_is_dupack = false;
 Model1_u32 Model1_prior_fackets;
 int Model1_prior_packets = Model1_tp->Model1_packets_out;
 Model1_u32 Model1_prior_delivered = Model1_tp->Model1_delivered;
 int Model1_acked = 0; /* Number of packets newly acked */
 int Model1_rexmit = 0; /* Flag to (re)transmit to recover losses */

 Model1_sack_state.Model1_first_sackt.Model1_v64 = 0;

 /* We very likely will need to access write queue head. */
 Model1_prefetchw(Model1_sk->Model1_sk_write_queue.Model1_next);

 /* If the ack is older than previous acks
	 * then we can probably ignore it.
	 */
 if (Model1_before(Model1_ack, Model1_prior_snd_una)) {
  /* RFC 5961 5.2 [Blind Data Injection Attack].[Mitigation] */
  if (Model1_before(Model1_ack, Model1_prior_snd_una - Model1_tp->Model1_max_window)) {
   Model1_tcp_send_challenge_ack(Model1_sk, Model1_skb);
   return -1;
  }
  goto Model1_old_ack;
 }

 /* If the ack includes data we haven't sent yet, discard
	 * this segment (RFC793 Section 3.9).
	 */
 if (Model1_before(Model1_tp->Model1_snd_nxt, Model1_ack))
  goto Model1_invalid_ack;

#if !CY_ABSTRACT1 //TODO: double check (not necessary)
 if (Model1_icsk->Model1_icsk_pending == 4 ||
     Model1_icsk->Model1_icsk_pending == 5)
  Model1_tcp_rearm_rto(Model1_sk);
#endif

 if (Model1_before(Model1_prior_snd_una, Model1_ack)) {
  Model1_flag |= 0x400;
  Model1_icsk->Model1_icsk_retransmits = 0;
 }

 Model1_prior_fackets = Model1_tp->Model1_fackets_out;

 /* ts_recent update must be made after we are sure that the packet
	 * is in window.
	 */
 if (Model1_flag & 0x4000)
  Model1_tcp_replace_ts_recent(Model1_tp, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq);

 if (!(Model1_flag & 0x100) && Model1_before(Model1_prior_snd_una, Model1_ack)) {
  /* Window is constant, pure forward advance.
		 * No more checks are required.
		 * Note, we use the fact that SND.UNA>=SND.WL2.
		 */
  Model1_tcp_update_wl(Model1_tp, Model1_ack_seq);
  Model1_tcp_snd_una_update(Model1_tp, Model1_ack);
  Model1_flag |= 0x02;

  Model1_tcp_in_ack_event(Model1_sk, Model1_CA_ACK_WIN_UPDATE);

  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPHPACKS] += 1);
 } else {
  Model1_u32 Model1_ack_ev_flags = Model1_CA_ACK_SLOWPATH;

  if (Model1_ack_seq != ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq)
   Model1_flag |= 0x01;
  else
   (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPPUREACKS] += 1);

  Model1_flag |= Model1_tcp_ack_update_window(Model1_sk, Model1_skb, Model1_ack, Model1_ack_seq);
#if !CY_ABSTRACT1
  if (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked)
   Model1_flag |= Model1_tcp_sacktag_write_queue(Model1_sk, Model1_skb, Model1_prior_snd_una,
       &Model1_sack_state);

  if (Model1_tcp_ecn_rcv_ecn_echo(Model1_tp, Model1_tcp_hdr(Model1_skb))) {
   Model1_flag |= 0x40;
   Model1_ack_ev_flags |= Model1_CA_ACK_ECE;
  }
#endif
  if (Model1_flag & 0x02)
   Model1_ack_ev_flags |= Model1_CA_ACK_WIN_UPDATE;

  Model1_tcp_in_ack_event(Model1_sk, Model1_ack_ev_flags);
 }

 /* We passed data and got it acked, remove any soft error
	 * log. Something worked...
	 */
 Model1_sk->Model1_sk_err_soft = 0;
 Model1_icsk->Model1_icsk_probes_out = 0;
 Model1_tp->Model1_rcv_tstamp = ((__u32)(Model1_jiffies));
 if (!Model1_prior_packets)
  goto Model1_no_queue;

 /* See if we can take anything off of the retransmit queue. */
#if !CY_ABSTRACT1
 Model1_flag |= Model1_tcp_clean_rtx_queue(Model1_sk, Model1_prior_fackets, Model1_prior_snd_una, &Model1_acked,
        &Model1_sack_state);

 if (Model1_tcp_ack_is_dubious(Model1_sk, Model1_flag)) {
  Model1_is_dupack = !(Model1_flag & (0x400 | (0x01|0x02|(0x04|0x10))));
  Model1_tcp_fastretrans_alert(Model1_sk, Model1_acked, Model1_is_dupack, &Model1_flag, &Model1_rexmit);
 }
 if (Model1_tp->Model1_tlp_high_seq)
  Model1_tcp_process_tlp_ack(Model1_sk, Model1_ack, Model1_flag);

 if ((Model1_flag & ((0x04|0x10)|0x20)) || !(Model1_flag & (0x01|0x02|(0x04|0x10)))) {
  struct Model1_dst_entry *Model1_dst = Model1___sk_dst_get(Model1_sk);
  if (Model1_dst)
   Model1_dst_confirm(Model1_dst);
 }

 if (Model1_icsk->Model1_icsk_pending == 1)
  Model1_tcp_schedule_loss_probe(Model1_sk);
 Model1_tcp_cong_control(Model1_sk, Model1_ack, Model1_tp->Model1_delivered - Model1_prior_delivered, Model1_flag);
 Model1_tcp_xmit_recovery(Model1_sk, Model1_rexmit);
 return 1;
#endif
Model1_no_queue:
#if !CY_ABSTRACT1
 /* If data was DSACKed, see if we can undo a cwnd reduction. */
 if (Model1_flag & 0x800)
  Model1_tcp_fastretrans_alert(Model1_sk, Model1_acked, Model1_is_dupack, &Model1_flag, &Model1_rexmit);
 /* If this ack opens up a zero window, clear backoff.  It was
	 * being used to time the probes, and is probably far higher than
	 * it needs to be for normal retransmission.
	 */
 if (Model1_tcp_send_head(Model1_sk))
  Model1_tcp_ack_probe(Model1_sk);

 if (Model1_tp->Model1_tlp_high_seq)
  Model1_tcp_process_tlp_ack(Model1_sk, Model1_ack, Model1_flag);
#endif
 return 1;

Model1_invalid_ack:
 do { if ((Model1_sk) && Model1_sock_flag((Model1_sk), Model1_SOCK_DBG)) Model1_printk("\001" "7" "Ack %u after %u:%u\n", Model1_ack, Model1_tp->Model1_snd_una, Model1_tp->Model1_snd_nxt); } while (0);
 return -1;

Model1_old_ack:
#if !CY_ABSTRACT1
 /* If data was SACKed, tag it and see if we should send more data.
	 * If data was DSACKed, see if we can undo a cwnd reduction.
	 */
 if (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked) {
  Model1_flag |= Model1_tcp_sacktag_write_queue(Model1_sk, Model1_skb, Model1_prior_snd_una,
      &Model1_sack_state);
  Model1_tcp_fastretrans_alert(Model1_sk, Model1_acked, Model1_is_dupack, &Model1_flag, &Model1_rexmit);
  Model1_tcp_xmit_recovery(Model1_sk, Model1_rexmit);
 }

 do { if ((Model1_sk) && Model1_sock_flag((Model1_sk), Model1_SOCK_DBG)) Model1_printk("\001" "7" "Ack %u before %u:%u\n", Model1_ack, Model1_tp->Model1_snd_una, Model1_tp->Model1_snd_nxt); } while (0);
#endif
 return 0;
}

static void Model1_tcp_parse_fastopen_option(int Model1_len, const unsigned char *Model1_cookie,
          bool Model1_syn, struct Model1_tcp_fastopen_cookie *Model1_foc,
          bool Model1_exp_opt)
{
 /* Valid only in SYN or SYN-ACK with an even length.  */
 if (!Model1_foc || !Model1_syn || Model1_len < 0 || (Model1_len & 1))
  return;

 if (Model1_len >= 4 &&
     Model1_len <= 16)
  ({ Model1_size_t Model1___len = (Model1_len); void *Model1___ret; if (__builtin_constant_p(Model1_len) && Model1___len >= 64) Model1___ret = Model1___memcpy((Model1_foc->Model1_val), (Model1_cookie), Model1___len); else Model1___ret = __builtin_memcpy((Model1_foc->Model1_val), (Model1_cookie), Model1___len); Model1___ret; });
 else if (Model1_len != 0)
  Model1_len = -1;
 Model1_foc->Model1_len = Model1_len;
 Model1_foc->Model1_exp = Model1_exp_opt;
}

/* Look for tcp options. Normally only called on SYN and SYNACK packets.
 * But, this can also be called on packets in the established flow when
 * the fast version below fails.
 */
void Model1_tcp_parse_options(const struct Model1_sk_buff *Model1_skb,
         struct Model1_tcp_options_received *Model1_opt_rx, int Model1_estab,
         struct Model1_tcp_fastopen_cookie *Model1_foc)
{
#if CY_ABSTRACT1
    return;
#endif
 const unsigned char *Model1_ptr;
 const struct Model1_tcphdr *Model1_th = Model1_tcp_hdr(Model1_skb);
 int Model1_length = (Model1_th->Model1_doff * 4) - sizeof(struct Model1_tcphdr);

 Model1_ptr = (const unsigned char *)(Model1_th + 1);
 Model1_opt_rx->Model1_saw_tstamp = 0;

 while (Model1_length > 0) {
  int Model1_opcode = *Model1_ptr++;
  int Model1_opsize;

  switch (Model1_opcode) {
  case 0:
   return;
  case 1: /* Ref: RFC 793 section 3.1 */
   Model1_length--;
   continue;
  default:
   Model1_opsize = *Model1_ptr++;
   if (Model1_opsize < 2) /* "silly options" */
    return;
   if (Model1_opsize > Model1_length)
    return; /* don't parse partial options */
   switch (Model1_opcode) {
   case 2:
    if (Model1_opsize == 4 && Model1_th->Model1_syn && !Model1_estab) {
     Model1_u16 Model1_in_mss = Model1_get_unaligned_be16(Model1_ptr);
     if (Model1_in_mss) {
      if (Model1_opt_rx->Model1_user_mss &&
          Model1_opt_rx->Model1_user_mss < Model1_in_mss)
       Model1_in_mss = Model1_opt_rx->Model1_user_mss;
      Model1_opt_rx->Model1_mss_clamp = Model1_in_mss;
     }
    }
    break;
   case 3:
    if (Model1_opsize == 3 && Model1_th->Model1_syn &&
        !Model1_estab && Model1_sysctl_tcp_window_scaling) {
     __u8 Model1_snd_wscale = *(__u8 *)Model1_ptr;
     Model1_opt_rx->Model1_wscale_ok = 1;
     if (Model1_snd_wscale > 14) {
      do { if (Model1_net_ratelimit()) Model1_printk("\001" "6" "TCP: " "%s: Illegal window scaling value %d >14 received\n", __func__, Model1_snd_wscale); } while (0);


      Model1_snd_wscale = 14;
     }
     Model1_opt_rx->Model1_snd_wscale = Model1_snd_wscale;
    }
    break;
   case 8:
    if ((Model1_opsize == 10) &&
        ((Model1_estab && Model1_opt_rx->Model1_tstamp_ok) ||
         (!Model1_estab && Model1_sysctl_tcp_timestamps))) {
     Model1_opt_rx->Model1_saw_tstamp = 1;
     Model1_opt_rx->Model1_rcv_tsval = Model1_get_unaligned_be32(Model1_ptr);
     Model1_opt_rx->Model1_rcv_tsecr = Model1_get_unaligned_be32(Model1_ptr + 4);
    }
    break;
   case 4:
    if (Model1_opsize == 2 && Model1_th->Model1_syn &&
        !Model1_estab && Model1_sysctl_tcp_sack) {
     Model1_opt_rx->Model1_sack_ok = (1 << 0);
     Model1_tcp_sack_reset(Model1_opt_rx);
    }
    break;

   case 5:
    if ((Model1_opsize >= (2 + 8)) &&
       !((Model1_opsize - 2) % 8) &&
       Model1_opt_rx->Model1_sack_ok) {
     ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_sacked = (Model1_ptr - 2) - (unsigned char *)Model1_th;
    }
    break;
   case 34:
    Model1_tcp_parse_fastopen_option(
     Model1_opsize - 2,
     Model1_ptr, Model1_th->Model1_syn, Model1_foc, false);
    break;

   case 254:
    /* Fast Open option shares code 254 using a
				 * 16 bits magic number.
				 */
    if (Model1_opsize >= 4 &&
        Model1_get_unaligned_be16(Model1_ptr) ==
        0xF989)
     Model1_tcp_parse_fastopen_option(Model1_opsize -
      4,
      Model1_ptr + 2, Model1_th->Model1_syn, Model1_foc, true);
    break;

   }
   Model1_ptr += Model1_opsize-2;
   Model1_length -= Model1_opsize;
  }
 }
}
                                ;

static bool Model1_tcp_parse_aligned_timestamp(struct Model1_tcp_sock *Model1_tp, const struct Model1_tcphdr *Model1_th)
{
 const Model1___be32 *Model1_ptr = (const Model1___be32 *)(Model1_th + 1);

 if (*Model1_ptr == (( Model1___be32)(__builtin_constant_p((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10))) ? ((__u32)( (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x000000ffUL) << 24) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32(((1 << 24) | (1 << 16) | (8 << 8) | 10))))) {

  Model1_tp->Model1_rx_opt.Model1_saw_tstamp = 1;
  ++Model1_ptr;
  Model1_tp->Model1_rx_opt.Model1_rcv_tsval = (__builtin_constant_p((__u32)(( __u32)(Model1___be32)(*Model1_ptr))) ? ((__u32)( (((__u32)(( __u32)(Model1___be32)(*Model1_ptr)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model1___be32)(*Model1_ptr)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model1___be32)(*Model1_ptr)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model1___be32)(*Model1_ptr)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32(( __u32)(Model1___be32)(*Model1_ptr)));
  ++Model1_ptr;
  if (*Model1_ptr)
   Model1_tp->Model1_rx_opt.Model1_rcv_tsecr = (__builtin_constant_p((__u32)(( __u32)(Model1___be32)(*Model1_ptr))) ? ((__u32)( (((__u32)(( __u32)(Model1___be32)(*Model1_ptr)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model1___be32)(*Model1_ptr)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model1___be32)(*Model1_ptr)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model1___be32)(*Model1_ptr)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32(( __u32)(Model1___be32)(*Model1_ptr))) - Model1_tp->Model1_tsoffset;
  else
   Model1_tp->Model1_rx_opt.Model1_rcv_tsecr = 0;
  return true;
 }
 return false;
}

/* Fast parse options. This hopes to only see timestamps.
 * If it is wrong it falls back on tcp_parse_options().
 */
static bool Model1_tcp_fast_parse_options(const struct Model1_sk_buff *Model1_skb,
       const struct Model1_tcphdr *Model1_th, struct Model1_tcp_sock *Model1_tp)
{
 /* In the spirit of fast parsing, compare doff directly to constant
	 * values.  Because equality is used, short doff can be ignored here.
	 */
 if (Model1_th->Model1_doff == (sizeof(*Model1_th) / 4)) {
  Model1_tp->Model1_rx_opt.Model1_saw_tstamp = 0;
  return false;
 } else if (Model1_tp->Model1_rx_opt.Model1_tstamp_ok &&
     Model1_th->Model1_doff == ((sizeof(*Model1_th) + 12) / 4)) {
  if (Model1_tcp_parse_aligned_timestamp(Model1_tp, Model1_th))
   return true;
 }

 Model1_tcp_parse_options(Model1_skb, &Model1_tp->Model1_rx_opt, 1, ((void *)0));
 if (Model1_tp->Model1_rx_opt.Model1_saw_tstamp && Model1_tp->Model1_rx_opt.Model1_rcv_tsecr)
  Model1_tp->Model1_rx_opt.Model1_rcv_tsecr -= Model1_tp->Model1_tsoffset;

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

static int Model1_tcp_disordered_ack(const struct Model1_sock *Model1_sk, const struct Model1_sk_buff *Model1_skb)
{
 const struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 const struct Model1_tcphdr *Model1_th = Model1_tcp_hdr(Model1_skb);
 Model1_u32 Model1_seq = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq;
 Model1_u32 Model1_ack = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_ack_seq;

 return (/* 1. Pure ACK with correct sequence number. */
  (Model1_th->Model1_ack && Model1_seq == ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq && Model1_seq == Model1_tp->Model1_rcv_nxt) &&

  /* 2. ... and duplicate ACK. */
  Model1_ack == Model1_tp->Model1_snd_una &&

  /* 3. ... and does not update window. */
  !Model1_tcp_may_update_window(Model1_tp, Model1_ack, Model1_seq, (__builtin_constant_p((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_th->Model1_window))) ? ((Model1___u16)( (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_th->Model1_window)) & (Model1___u16)0x00ffU) << 8) | (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_th->Model1_window)) & (Model1___u16)0xff00U) >> 8))) : Model1___fswab16(( Model1___u16)(Model1___be16)(Model1_th->Model1_window))) << Model1_tp->Model1_rx_opt.Model1_snd_wscale) &&

  /* 4. ... and sits in replay window. */
  (Model1_s32)(Model1_tp->Model1_rx_opt.Model1_ts_recent - Model1_tp->Model1_rx_opt.Model1_rcv_tsval) <= (Model1_inet_csk(Model1_sk)->Model1_icsk_rto * 1024) / 1000);
}

static inline __attribute__((no_instrument_function)) bool Model1_tcp_paws_discard(const struct Model1_sock *Model1_sk,
       const struct Model1_sk_buff *Model1_skb)
{
 const struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 return !Model1_tcp_paws_check(&Model1_tp->Model1_rx_opt, 1) &&
        !Model1_tcp_disordered_ack(Model1_sk, Model1_skb);
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

static inline __attribute__((no_instrument_function)) bool Model1_tcp_sequence(const struct Model1_tcp_sock *Model1_tp, Model1_u32 Model1_seq, Model1_u32 Model1_end_seq)
{
 return !Model1_before(Model1_end_seq, Model1_tp->Model1_rcv_wup) &&
  !Model1_before(Model1_tp->Model1_rcv_nxt + Model1_tcp_receive_window(Model1_tp), Model1_seq);
}

/* When we get a reset we do this. */
void Model1_tcp_reset(struct Model1_sock *Model1_sk)
{
#if CY_ABSTRACT4
    //When a correct RST is received, we terminate our attack since victim connection is not alive any more. Therefore we stop from there.
    Model1_Connection_reset = true;
#else
 /* We want the right error as BSD sees it (and indeed as we do). */
 switch (Model1_sk->Model1___sk_common.Model1_skc_state) {
 case Model1_TCP_SYN_SENT:
  Model1_sk->Model1_sk_err = 111;
  break;
 case Model1_TCP_CLOSE_WAIT:
  Model1_sk->Model1_sk_err = 32;
  break;
 case Model1_TCP_CLOSE:
  return;
 default:
  Model1_sk->Model1_sk_err = 104;
 }
 /* This barrier is coupled with smp_rmb() in tcp_poll() */
 __asm__ __volatile__("": : :"memory");

 if (!Model1_sock_flag(Model1_sk, Model1_SOCK_DEAD))
  Model1_sk->Model1_sk_error_report(Model1_sk);

 Model1_tcp_done(Model1_sk);
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
void Model1_tcp_fin(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 Model1_inet_csk_schedule_ack(Model1_sk);

 Model1_sk->Model1_sk_shutdown |= 1;
 Model1_sock_set_flag(Model1_sk, Model1_SOCK_DONE);

 switch (Model1_sk->Model1___sk_common.Model1_skc_state) {
 case Model1_TCP_SYN_RECV:
 case Model1_TCP_ESTABLISHED:
  /* Move to CLOSE_WAIT */
  Model1_tcp_set_state(Model1_sk, Model1_TCP_CLOSE_WAIT);
  Model1_inet_csk(Model1_sk)->Model1_icsk_ack.Model1_pingpong = 1;
  break;

 case Model1_TCP_CLOSE_WAIT:
 case Model1_TCP_CLOSING:
  /* Received a retransmission of the FIN, do
		 * nothing.
		 */
  break;
 case Model1_TCP_LAST_ACK:
  /* RFC793: Remain in the LAST-ACK state. */
  break;

 case Model1_TCP_FIN_WAIT1:
  /* This case occurs when a simultaneous close
		 * happens, we must ack the received FIN and
		 * enter the CLOSING state.
		 */
  Model1_tcp_send_ack(Model1_sk);
  Model1_tcp_set_state(Model1_sk, Model1_TCP_CLOSING);
  break;
 case Model1_TCP_FIN_WAIT2:
  /* Received a FIN -- send ACK and enter TIME_WAIT. */
  Model1_tcp_send_ack(Model1_sk);
  Model1_tcp_time_wait(Model1_sk, Model1_TCP_TIME_WAIT, 0);
  break;
 default:
  /* Only TCP_LISTEN and TCP_CLOSE are left, in these
		 * cases we should never reach this piece of code.
		 */
  Model1_printk("\001" "3" "TCP: " "%s: Impossible, sk->sk_state=%d\n", __func__, Model1_sk->Model1___sk_common.Model1_skc_state);

  break;
 }

 /* It _is_ possible, that we have something out-of-order _after_ FIN.
	 * Probably, we should reset in this case. For now drop them.
	 */
 Model1___skb_queue_purge(&Model1_tp->Model1_out_of_order_queue);
 if (Model1_tcp_is_sack(Model1_tp))
  Model1_tcp_sack_reset(&Model1_tp->Model1_rx_opt);
 Model1_sk_mem_reclaim(Model1_sk);

 if (!Model1_sock_flag(Model1_sk, Model1_SOCK_DEAD)) {
#if CY_ABSTRACT7
  Model1_sock_def_wakeup(Model1_sk);
#else
  Model1_sk->Model1_sk_state_change(Model1_sk);
#endif

  /* Do not send POLL_HUP for half duplex close. */
  if (Model1_sk->Model1_sk_shutdown == 3 ||
      Model1_sk->Model1___sk_common.Model1_skc_state == Model1_TCP_CLOSE)
   Model1_sk_wake_async(Model1_sk, Model1_SOCK_WAKE_WAITD, ((2 << 16)|6));
  else
   Model1_sk_wake_async(Model1_sk, Model1_SOCK_WAKE_WAITD, ((2 << 16)|1));
 }
}

static inline __attribute__((no_instrument_function)) bool Model1_tcp_sack_extend(struct Model1_tcp_sack_block *Model1_sp, Model1_u32 Model1_seq,
      Model1_u32 Model1_end_seq)
{
 if (!Model1_before(Model1_sp->Model1_end_seq, Model1_seq) && !Model1_before(Model1_end_seq, Model1_sp->Model1_start_seq)) {
  if (Model1_before(Model1_seq, Model1_sp->Model1_start_seq))
   Model1_sp->Model1_start_seq = Model1_seq;
  if (Model1_before(Model1_sp->Model1_end_seq, Model1_end_seq))
   Model1_sp->Model1_end_seq = Model1_end_seq;
  return true;
 }
 return false;
}

static void Model1_tcp_dsack_set(struct Model1_sock *Model1_sk, Model1_u32 Model1_seq, Model1_u32 Model1_end_seq)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 if (Model1_tcp_is_sack(Model1_tp) && Model1_sysctl_tcp_dsack) {
  int Model1_mib_idx;

  if (Model1_before(Model1_seq, Model1_tp->Model1_rcv_nxt))
   Model1_mib_idx = Model1_LINUX_MIB_TCPDSACKOLDSENT;
  else
   Model1_mib_idx = Model1_LINUX_MIB_TCPDSACKOFOSENT;

  (Model1_cy_linux_mib.Model1_mibs[Model1_mib_idx] += 1);

  Model1_tp->Model1_rx_opt.Model1_dsack = 1;
  Model1_tp->Model1_duplicate_sack[0].Model1_start_seq = Model1_seq;
  Model1_tp->Model1_duplicate_sack[0].Model1_end_seq = Model1_end_seq;
 }
}

static void Model1_tcp_dsack_extend(struct Model1_sock *Model1_sk, Model1_u32 Model1_seq, Model1_u32 Model1_end_seq)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 if (!Model1_tp->Model1_rx_opt.Model1_dsack)
  Model1_tcp_dsack_set(Model1_sk, Model1_seq, Model1_end_seq);
 else
  Model1_tcp_sack_extend(Model1_tp->Model1_duplicate_sack, Model1_seq, Model1_end_seq);
}

static void Model1_tcp_send_dupack(struct Model1_sock *Model1_sk, const struct Model1_sk_buff *Model1_skb)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 if (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq != ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq &&
     Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, Model1_tp->Model1_rcv_nxt)) {
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_DELAYEDACKLOST] += 1);
  Model1_tcp_enter_quickack_mode(Model1_sk);

  if (Model1_tcp_is_sack(Model1_tp) && Model1_sysctl_tcp_dsack) {
   Model1_u32 Model1_end_seq = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq;

   if (Model1_before(Model1_tp->Model1_rcv_nxt, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq))
    Model1_end_seq = Model1_tp->Model1_rcv_nxt;
   Model1_tcp_dsack_set(Model1_sk, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, Model1_end_seq);
  }
 }

 Model1_tcp_send_ack(Model1_sk);
}

/* These routines update the SACK block as out-of-order packets arrive or
 * in-order packets close up the sequence space.
 */
static void Model1_tcp_sack_maybe_coalesce(struct Model1_tcp_sock *Model1_tp)
{
 int Model1_this_sack;
 struct Model1_tcp_sack_block *Model1_sp = &Model1_tp->Model1_selective_acks[0];
 struct Model1_tcp_sack_block *Model1_swalk = Model1_sp + 1;

 /* See if the recent change to the first SACK eats into
	 * or hits the sequence space of other SACK blocks, if so coalesce.
	 */
 for (Model1_this_sack = 1; Model1_this_sack < Model1_tp->Model1_rx_opt.Model1_num_sacks;) {
  if (Model1_tcp_sack_extend(Model1_sp, Model1_swalk->Model1_start_seq, Model1_swalk->Model1_end_seq)) {
   int Model1_i;

   /* Zap SWALK, by moving every further SACK up by one slot.
			 * Decrease num_sacks.
			 */
   Model1_tp->Model1_rx_opt.Model1_num_sacks--;
   for (Model1_i = Model1_this_sack; Model1_i < Model1_tp->Model1_rx_opt.Model1_num_sacks; Model1_i++)
    Model1_sp[Model1_i] = Model1_sp[Model1_i + 1];
   continue;
  }
  Model1_this_sack++, Model1_swalk++;
 }
}

static void Model1_tcp_sack_new_ofo_skb(struct Model1_sock *Model1_sk, Model1_u32 Model1_seq, Model1_u32 Model1_end_seq)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_tcp_sack_block *Model1_sp = &Model1_tp->Model1_selective_acks[0];
 int Model1_cur_sacks = Model1_tp->Model1_rx_opt.Model1_num_sacks;
 int Model1_this_sack;

 if (!Model1_cur_sacks)
  goto Model1_new_sack;

 for (Model1_this_sack = 0; Model1_this_sack < Model1_cur_sacks; Model1_this_sack++, Model1_sp++) {
  if (Model1_tcp_sack_extend(Model1_sp, Model1_seq, Model1_end_seq)) {
   /* Rotate this_sack to the first one. */
   for (; Model1_this_sack > 0; Model1_this_sack--, Model1_sp--)
    do { typeof(*Model1_sp) Model1___tmp = (*Model1_sp); (*Model1_sp) = (*(Model1_sp - 1)); (*(Model1_sp - 1)) = Model1___tmp; } while (0);
   if (Model1_cur_sacks > 1)
    Model1_tcp_sack_maybe_coalesce(Model1_tp);
   return;
  }
 }

 /* Could not find an adjacent existing SACK, build a new one,
	 * put it at the front, and shift everyone else down.  We
	 * always know there is at least one SACK present already here.
	 *
	 * If the sack array is full, forget about the last one.
	 */
 if (Model1_this_sack >= 4) {
  Model1_this_sack--;
  Model1_tp->Model1_rx_opt.Model1_num_sacks--;
  Model1_sp--;
 }
 for (; Model1_this_sack > 0; Model1_this_sack--, Model1_sp--)
  *Model1_sp = *(Model1_sp - 1);

Model1_new_sack:
 /* Build the new head SACK, and we're done. */
 Model1_sp->Model1_start_seq = Model1_seq;
 Model1_sp->Model1_end_seq = Model1_end_seq;
 Model1_tp->Model1_rx_opt.Model1_num_sacks++;
}

/* RCV.NXT advances, some SACKs should be eaten. */

static void Model1_tcp_sack_remove(struct Model1_tcp_sock *Model1_tp)
{
 struct Model1_tcp_sack_block *Model1_sp = &Model1_tp->Model1_selective_acks[0];
 int Model1_num_sacks = Model1_tp->Model1_rx_opt.Model1_num_sacks;
 int Model1_this_sack;

 /* Empty ofo queue, hence, all the SACKs are eaten. Clear. */
 if (Model1_skb_queue_empty(&Model1_tp->Model1_out_of_order_queue)) {
  Model1_tp->Model1_rx_opt.Model1_num_sacks = 0;
  return;
 }

 for (Model1_this_sack = 0; Model1_this_sack < Model1_num_sacks;) {
  /* Check if the start of the sack is covered by RCV.NXT. */
  if (!Model1_before(Model1_tp->Model1_rcv_nxt, Model1_sp->Model1_start_seq)) {
   int Model1_i;

   /* RCV.NXT must cover all the block! */
   ({ int Model1___ret_warn_on = !!(Model1_before(Model1_tp->Model1_rcv_nxt, Model1_sp->Model1_end_seq)); __builtin_expect(!!(Model1___ret_warn_on), 0); });

   /* Zap this SACK, by moving forward any other SACKS. */
   for (Model1_i = Model1_this_sack+1; Model1_i < Model1_num_sacks; Model1_i++)
    Model1_tp->Model1_selective_acks[Model1_i-1] = Model1_tp->Model1_selective_acks[Model1_i];
   Model1_num_sacks--;
   continue;
  }
  Model1_this_sack++;
  Model1_sp++;
 }
 Model1_tp->Model1_rx_opt.Model1_num_sacks = Model1_num_sacks;
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
static bool Model1_tcp_try_coalesce(struct Model1_sock *Model1_sk,
        struct Model1_sk_buff *Model1_to,
        struct Model1_sk_buff *Model1_from,
        bool *Model1_fragstolen)
{
 int Model1_delta;

 *Model1_fragstolen = false;

 /* Its possible this segment overlaps with prior segment in queue */
 if (((struct Model1_tcp_skb_cb *)&((Model1_from)->Model1_cb[0]))->Model1_seq != ((struct Model1_tcp_skb_cb *)&((Model1_to)->Model1_cb[0]))->Model1_end_seq)
  return false;

 if (!Model1_skb_try_coalesce(Model1_to, Model1_from, Model1_fragstolen, &Model1_delta))
  return false;

 Model1_atomic_add(Model1_delta, &Model1_sk->Model1_sk_backlog.Model1_rmem_alloc);
 Model1_sk_mem_charge(Model1_sk, Model1_delta);
 (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPRCVCOALESCE] += 1);
 ((struct Model1_tcp_skb_cb *)&((Model1_to)->Model1_cb[0]))->Model1_end_seq = ((struct Model1_tcp_skb_cb *)&((Model1_from)->Model1_cb[0]))->Model1_end_seq;
 ((struct Model1_tcp_skb_cb *)&((Model1_to)->Model1_cb[0]))->Model1_ack_seq = ((struct Model1_tcp_skb_cb *)&((Model1_from)->Model1_cb[0]))->Model1_ack_seq;
 ((struct Model1_tcp_skb_cb *)&((Model1_to)->Model1_cb[0]))->Model1_tcp_flags |= ((struct Model1_tcp_skb_cb *)&((Model1_from)->Model1_cb[0]))->Model1_tcp_flags;
 return true;
}

static void Model1_tcp_drop(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb)
{
 Model1_sk_drops_add(Model1_sk, Model1_skb);
 Model1___kfree_skb(Model1_skb);
}

/* This one checks to see if we can put data from the
 * out_of_order queue into the receive_queue.
 */
static void Model1_tcp_ofo_queue(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 __u32 Model1_dsack_high = Model1_tp->Model1_rcv_nxt;
 struct Model1_sk_buff *Model1_skb, *Model1_tail;
 bool Model1_fragstolen, Model1_eaten;

 while ((Model1_skb = Model1_skb_peek(&Model1_tp->Model1_out_of_order_queue)) != ((void *)0)) {
  if (Model1_before(Model1_tp->Model1_rcv_nxt, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq))
   break;

  if (Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, Model1_dsack_high)) {
   __u32 Model1_dsack = Model1_dsack_high;
   if (Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq, Model1_dsack_high))
    Model1_dsack_high = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq;
   Model1_tcp_dsack_extend(Model1_sk, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, Model1_dsack);
  }

  Model1___skb_unlink(Model1_skb, &Model1_tp->Model1_out_of_order_queue);
  if (!Model1_before(Model1_tp->Model1_rcv_nxt, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq)) {
   do { if ((Model1_sk) && Model1_sock_flag((Model1_sk), Model1_SOCK_DBG)) Model1_printk("\001" "7" "ofo packet was already received\n"); } while (0);
   Model1_tcp_drop(Model1_sk, Model1_skb);
   continue;
  }
  do { if ((Model1_sk) && Model1_sock_flag((Model1_sk), Model1_SOCK_DBG)) Model1_printk("\001" "7" "ofo requeuing : rcv_next %X seq %X - %X\n", Model1_tp->Model1_rcv_nxt, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq); } while (0);



  Model1_tail = Model1_skb_peek_tail(&Model1_sk->Model1_sk_receive_queue);
  Model1_eaten = Model1_tail && Model1_tcp_try_coalesce(Model1_sk, Model1_tail, Model1_skb, &Model1_fragstolen);
  Model1_tcp_rcv_nxt_update(Model1_tp, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq);
  if (!Model1_eaten)
   Model1___skb_queue_tail(&Model1_sk->Model1_sk_receive_queue, Model1_skb);
  if (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_tcp_flags & 0x01)
   Model1_tcp_fin(Model1_sk);
  if (Model1_eaten)
   Model1_kfree_skb_partial(Model1_skb, Model1_fragstolen);
 }
}

static bool Model1_tcp_prune_ofo_queue(struct Model1_sock *Model1_sk);
static int Model1_tcp_prune_queue(struct Model1_sock *Model1_sk);

static int Model1_tcp_try_rmem_schedule(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb,
     unsigned int Model1_size)
{
 if (Model1_atomic_read(&Model1_sk->Model1_sk_backlog.Model1_rmem_alloc) > Model1_sk->Model1_sk_rcvbuf ||
     !Model1_sk_rmem_schedule(Model1_sk, Model1_skb, Model1_size)) {

  if (Model1_tcp_prune_queue(Model1_sk) < 0)
   return -1;

  if (!Model1_sk_rmem_schedule(Model1_sk, Model1_skb, Model1_size)) {
   if (!Model1_tcp_prune_ofo_queue(Model1_sk))
    return -1;

   if (!Model1_sk_rmem_schedule(Model1_sk, Model1_skb, Model1_size))
    return -1;
  }
 }
 return 0;
}

static void Model1_tcp_data_queue_ofo(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_sk_buff *Model1_skb1;
 Model1_u32 Model1_seq, Model1_end_seq;

 Model1_tcp_ecn_check_ce(Model1_tp, Model1_skb);

 if (__builtin_expect(!!(Model1_tcp_try_rmem_schedule(Model1_sk, Model1_skb, Model1_skb->Model1_truesize)), 0)) {
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPOFODROP] += 1);
  Model1_tcp_drop(Model1_sk, Model1_skb);
  return;
 }

 /* Disable header prediction. */
 Model1_tp->Model1_pred_flags = 0;
 Model1_inet_csk_schedule_ack(Model1_sk);

 (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPOFOQUEUE] += 1);
 do { if ((Model1_sk) && Model1_sock_flag((Model1_sk), Model1_SOCK_DBG)) Model1_printk("\001" "7" "out of order segment: rcv_next %X seq %X - %X\n", Model1_tp->Model1_rcv_nxt, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq); } while (0);


 Model1_skb1 = Model1_skb_peek_tail(&Model1_tp->Model1_out_of_order_queue);
 if (!Model1_skb1) {
  /* Initial out of order segment, build 1 SACK. */
  if (Model1_tcp_is_sack(Model1_tp)) {
   Model1_tp->Model1_rx_opt.Model1_num_sacks = 1;
   Model1_tp->Model1_selective_acks[0].Model1_start_seq = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq;
   Model1_tp->Model1_selective_acks[0].Model1_end_seq =
      ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq;
  }
  Model1___skb_queue_head(&Model1_tp->Model1_out_of_order_queue, Model1_skb);
  goto Model1_end;
 }

 Model1_seq = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq;
 Model1_end_seq = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq;

 if (Model1_seq == ((struct Model1_tcp_skb_cb *)&((Model1_skb1)->Model1_cb[0]))->Model1_end_seq) {
  bool Model1_fragstolen;

  if (!Model1_tcp_try_coalesce(Model1_sk, Model1_skb1, Model1_skb, &Model1_fragstolen)) {
   Model1___skb_queue_after(&Model1_tp->Model1_out_of_order_queue, Model1_skb1, Model1_skb);
  } else {
   Model1_tcp_grow_window(Model1_sk, Model1_skb);
   Model1_kfree_skb_partial(Model1_skb, Model1_fragstolen);
   Model1_skb = ((void *)0);
  }

  if (!Model1_tp->Model1_rx_opt.Model1_num_sacks ||
      Model1_tp->Model1_selective_acks[0].Model1_end_seq != Model1_seq)
   goto Model1_add_sack;

  /* Common case: data arrive in order after hole. */
  Model1_tp->Model1_selective_acks[0].Model1_end_seq = Model1_end_seq;
  goto Model1_end;
 }

 /* Find place to insert this segment. */
 while (1) {
  if (!Model1_before(Model1_seq, ((struct Model1_tcp_skb_cb *)&((Model1_skb1)->Model1_cb[0]))->Model1_seq))
   break;
  if (Model1_skb_queue_is_first(&Model1_tp->Model1_out_of_order_queue, Model1_skb1)) {
   Model1_skb1 = ((void *)0);
   break;
  }
  Model1_skb1 = Model1_skb_queue_prev(&Model1_tp->Model1_out_of_order_queue, Model1_skb1);
 }

 /* Do skb overlap to previous one? */
 if (Model1_skb1 && Model1_before(Model1_seq, ((struct Model1_tcp_skb_cb *)&((Model1_skb1)->Model1_cb[0]))->Model1_end_seq)) {
  if (!Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb1)->Model1_cb[0]))->Model1_end_seq, Model1_end_seq)) {
   /* All the bits are present. Drop. */
   (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPOFOMERGE] += 1);
   Model1_tcp_drop(Model1_sk, Model1_skb);
   Model1_skb = ((void *)0);
   Model1_tcp_dsack_set(Model1_sk, Model1_seq, Model1_end_seq);
   goto Model1_add_sack;
  }
  if (Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb1)->Model1_cb[0]))->Model1_seq, Model1_seq)) {
   /* Partial overlap. */
   Model1_tcp_dsack_set(Model1_sk, Model1_seq,
          ((struct Model1_tcp_skb_cb *)&((Model1_skb1)->Model1_cb[0]))->Model1_end_seq);
  } else {
   if (Model1_skb_queue_is_first(&Model1_tp->Model1_out_of_order_queue,
            Model1_skb1))
    Model1_skb1 = ((void *)0);
   else
    Model1_skb1 = Model1_skb_queue_prev(
     &Model1_tp->Model1_out_of_order_queue,
     Model1_skb1);
  }
 }
 if (!Model1_skb1)
  Model1___skb_queue_head(&Model1_tp->Model1_out_of_order_queue, Model1_skb);
 else
  Model1___skb_queue_after(&Model1_tp->Model1_out_of_order_queue, Model1_skb1, Model1_skb);

 /* And clean segments covered by new one as whole. */
 while (!Model1_skb_queue_is_last(&Model1_tp->Model1_out_of_order_queue, Model1_skb)) {
  Model1_skb1 = Model1_skb_queue_next(&Model1_tp->Model1_out_of_order_queue, Model1_skb);

  if (!Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb1)->Model1_cb[0]))->Model1_seq, Model1_end_seq))
   break;
  if (Model1_before(Model1_end_seq, ((struct Model1_tcp_skb_cb *)&((Model1_skb1)->Model1_cb[0]))->Model1_end_seq)) {
   Model1_tcp_dsack_extend(Model1_sk, ((struct Model1_tcp_skb_cb *)&((Model1_skb1)->Model1_cb[0]))->Model1_seq,
      Model1_end_seq);
   break;
  }
  Model1___skb_unlink(Model1_skb1, &Model1_tp->Model1_out_of_order_queue);
  Model1_tcp_dsack_extend(Model1_sk, ((struct Model1_tcp_skb_cb *)&((Model1_skb1)->Model1_cb[0]))->Model1_seq,
     ((struct Model1_tcp_skb_cb *)&((Model1_skb1)->Model1_cb[0]))->Model1_end_seq);
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPOFOMERGE] += 1);
  Model1_tcp_drop(Model1_sk, Model1_skb1);
 }

Model1_add_sack:
 if (Model1_tcp_is_sack(Model1_tp))
  Model1_tcp_sack_new_ofo_skb(Model1_sk, Model1_seq, Model1_end_seq);
Model1_end:
 if (Model1_skb) {
  Model1_tcp_grow_window(Model1_sk, Model1_skb);
  Model1_skb_set_owner_r(Model1_skb, Model1_sk);
 }
}

static int Model1_tcp_queue_rcv(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb, int Model1_hdrlen,
    bool *Model1_fragstolen)
{
 int Model1_eaten;
 struct Model1_sk_buff *Model1_tail = Model1_skb_peek_tail(&Model1_sk->Model1_sk_receive_queue);

 Model1___skb_pull(Model1_skb, Model1_hdrlen);
 Model1_eaten = (Model1_tail &&
   Model1_tcp_try_coalesce(Model1_sk, Model1_tail, Model1_skb, Model1_fragstolen)) ? 1 : 0;
 Model1_tcp_rcv_nxt_update(Model1_tcp_sk(Model1_sk), ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq);
 if (!Model1_eaten) {
  Model1___skb_queue_tail(&Model1_sk->Model1_sk_receive_queue, Model1_skb);
  Model1_skb_set_owner_r(Model1_skb, Model1_sk);
 }
 return Model1_eaten;
}

int Model1_tcp_send_rcvq(struct Model1_sock *Model1_sk, struct Model1_msghdr *Model1_msg, Model1_size_t Model1_size)
{
 struct Model1_sk_buff *Model1_skb;
 int err = -12;
 int Model1_data_len = 0;
 bool Model1_fragstolen;

 if (Model1_size == 0)
  return 0;

 if (Model1_size > ((1UL) << 12)) {
  int Model1_npages = ({ Model1_size_t Model1___min1 = (Model1_size >> 12); Model1_size_t Model1___min2 = ((65536/((1UL) << 12) + 1)); Model1___min1 < Model1___min2 ? Model1___min1: Model1___min2; });

  Model1_data_len = Model1_npages << 12;
  Model1_size = Model1_data_len + (Model1_size & ~(~(((1UL) << 12)-1)));
 }
 Model1_skb = Model1_alloc_skb_with_frags(Model1_size - Model1_data_len, Model1_data_len,
       3,
       &err, Model1_sk->Model1_sk_allocation);
 if (!Model1_skb)
  goto err;

 Model1_skb_put(Model1_skb, Model1_size - Model1_data_len);
 Model1_skb->Model1_data_len = Model1_data_len;
 Model1_skb->Model1_len = Model1_size;

 if (Model1_tcp_try_rmem_schedule(Model1_sk, Model1_skb, Model1_skb->Model1_truesize))
  goto Model1_err_free;

 err = Model1_skb_copy_datagram_from_iter(Model1_skb, 0, &Model1_msg->Model1_msg_iter, Model1_size);
 if (err)
  goto Model1_err_free;

 ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq = Model1_tcp_sk(Model1_sk)->Model1_rcv_nxt;
 ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq + Model1_size;
 ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_ack_seq = Model1_tcp_sk(Model1_sk)->Model1_snd_una - 1;

 if (Model1_tcp_queue_rcv(Model1_sk, Model1_skb, 0, &Model1_fragstolen)) {
  ({ int Model1___ret_warn_on = !!(Model1_fragstolen); __builtin_expect(!!(Model1___ret_warn_on), 0); }); /* should not happen */
  Model1___kfree_skb(Model1_skb);
 }
 return Model1_size;

Model1_err_free:
 Model1_kfree_skb(Model1_skb);
err:
 return err;

}

static void Model1_tcp_data_queue(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 bool Model1_fragstolen = false;
 int Model1_eaten = -1;

 if (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq == ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq) {
  Model1___kfree_skb(Model1_skb);
  return;
 }
 Model1_skb_dst_drop(Model1_skb);
 Model1___skb_pull(Model1_skb, Model1_tcp_hdr(Model1_skb)->Model1_doff * 4);

 Model1_tcp_ecn_accept_cwr(Model1_tp, Model1_skb);

 Model1_tp->Model1_rx_opt.Model1_dsack = 0;

 /*  Queue data for delivery to the user.
	 *  Packets in sequence go to the receive queue.
	 *  Out of sequence packets to the out_of_order_queue.
	 */
 if (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq == Model1_tp->Model1_rcv_nxt) {
  if (Model1_tcp_receive_window(Model1_tp) == 0)
   goto Model1_out_of_window;

  /* Ok. In sequence. In window. */
#if CY_ABSTRACT1 //TODO: double check
#else
  if (Model1_tp->Model1_ucopy.Model1_task == Model1_get_current() &&
      Model1_tp->Model1_copied_seq == Model1_tp->Model1_rcv_nxt && Model1_tp->Model1_ucopy.Model1_len &&
      Model1_sock_owned_by_user(Model1_sk) && !Model1_tp->Model1_urg_data) {
   int Model1_chunk = ({ unsigned int Model1___min1 = (Model1_skb->Model1_len); unsigned int Model1___min2 = (Model1_tp->Model1_ucopy.Model1_len); Model1___min1 < Model1___min2 ? Model1___min1: Model1___min2; });


   do { Model1_get_current()->Model1_state = (0); } while (0);

   if (!Model1_skb_copy_datagram_msg(Model1_skb, 0, Model1_tp->Model1_ucopy.Model1_msg, Model1_chunk)) {
    Model1_tp->Model1_ucopy.Model1_len -= Model1_chunk;
    Model1_tp->Model1_copied_seq += Model1_chunk;
    Model1_eaten = (Model1_chunk == Model1_skb->Model1_len);
    Model1_tcp_rcv_space_adjust(Model1_sk);
   }
  }
#endif
  if (Model1_eaten <= 0) {
Model1_queue_and_out:
   if (Model1_eaten < 0) {
    if (Model1_skb_queue_len(&Model1_sk->Model1_sk_receive_queue) == 0)
     Model1_sk_forced_mem_schedule(Model1_sk, Model1_skb->Model1_truesize);
    else if (Model1_tcp_try_rmem_schedule(Model1_sk, Model1_skb, Model1_skb->Model1_truesize))
     goto Model1_drop;
   }
   Model1_eaten = Model1_tcp_queue_rcv(Model1_sk, Model1_skb, 0, &Model1_fragstolen);
  }
  Model1_tcp_rcv_nxt_update(Model1_tp, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq);
  if (Model1_skb->Model1_len)
   Model1_tcp_event_data_recv(Model1_sk, Model1_skb);
#if !CY_ABSTRACT1
  if (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_tcp_flags & 0x01)
   Model1_tcp_fin(Model1_sk);
#endif

  if (!Model1_skb_queue_empty(&Model1_tp->Model1_out_of_order_queue)) {
   Model1_tcp_ofo_queue(Model1_sk);

   /* RFC2581. 4.2. SHOULD send immediate ACK, when
			 * gap in queue is filled.
			 */
   if (Model1_skb_queue_empty(&Model1_tp->Model1_out_of_order_queue))
    Model1_inet_csk(Model1_sk)->Model1_icsk_ack.Model1_pingpong = 0;
  }
#if !CY_ABSTRACT1
  if (Model1_tp->Model1_rx_opt.Model1_num_sacks)
   Model1_tcp_sack_remove(Model1_tp);
#endif
  Model1_tcp_fast_path_check(Model1_sk);

  if (Model1_eaten > 0)
   Model1_kfree_skb_partial(Model1_skb, Model1_fragstolen);
  if (!Model1_sock_flag(Model1_sk, Model1_SOCK_DEAD))
#if CY_ABSTRACT1
  {
    //TODO: better to replace the function pointer, and call the function
    //so far only ignore such function, since we won't consider async process
  }
#else
   Model1_sk->Model1_sk_data_ready(Model1_sk);
#endif
  return;
 }

 if (!Model1_before(Model1_tp->Model1_rcv_nxt, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq)) {
  /* A retransmit, 2nd most common case.  Force an immediate ack. */
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_DELAYEDACKLOST] += 1);
  Model1_tcp_dsack_set(Model1_sk, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq);

Model1_out_of_window:
  Model1_tcp_enter_quickack_mode(Model1_sk);
  Model1_inet_csk_schedule_ack(Model1_sk);
Model1_drop:
  Model1_tcp_drop(Model1_sk, Model1_skb);
  return;
 }

 /* Out of window. F.e. zero window probe. */
 if (!Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, Model1_tp->Model1_rcv_nxt + Model1_tcp_receive_window(Model1_tp)))
  goto Model1_out_of_window;

 Model1_tcp_enter_quickack_mode(Model1_sk);

 if (Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, Model1_tp->Model1_rcv_nxt)) {
  /* Partial packet, seq < rcv_next < end_seq */
  do { if ((Model1_sk) && Model1_sock_flag((Model1_sk), Model1_SOCK_DBG)) Model1_printk("\001" "7" "partial packet: rcv_next %X seq %X - %X\n", Model1_tp->Model1_rcv_nxt, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq); } while (0);



  Model1_tcp_dsack_set(Model1_sk, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, Model1_tp->Model1_rcv_nxt);

  /* If window is closed, drop tail of packet. But after
		 * remembering D-SACK for its head made in previous line.
		 */
  if (!Model1_tcp_receive_window(Model1_tp))
   goto Model1_out_of_window;
  goto Model1_queue_and_out;
 }

 Model1_tcp_data_queue_ofo(Model1_sk, Model1_skb);
}

static struct Model1_sk_buff *Model1_tcp_collapse_one(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb,
     struct Model1_sk_buff_head *Model1_list)
{
 struct Model1_sk_buff *Model1_next = ((void *)0);

 if (!Model1_skb_queue_is_last(Model1_list, Model1_skb))
  Model1_next = Model1_skb_queue_next(Model1_list, Model1_skb);

 Model1___skb_unlink(Model1_skb, Model1_list);
 Model1___kfree_skb(Model1_skb);
 (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPRCVCOLLAPSED] += 1);

 return Model1_next;
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
Model1_tcp_collapse(struct Model1_sock *Model1_sk, struct Model1_sk_buff_head *Model1_list,
      struct Model1_sk_buff *Model1_head, struct Model1_sk_buff *Model1_tail,
      Model1_u32 Model1_start, Model1_u32 Model1_end)
{
 struct Model1_sk_buff *Model1_skb, *Model1_n;
 bool Model1_end_of_skbs;

 /* First, check that queue is collapsible and find
	 * the point where collapsing can be useful. */
 Model1_skb = Model1_head;
Model1_restart:
 Model1_end_of_skbs = true;
 for (Model1_n = Model1_skb->Model1_next; Model1_skb != (struct Model1_sk_buff *)(Model1_list); Model1_skb = Model1_n, Model1_n = Model1_skb->Model1_next) {
  if (Model1_skb == Model1_tail)
   break;
  /* No new bits? It is possible on ofo queue. */
  if (!Model1_before(Model1_start, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq)) {
   Model1_skb = Model1_tcp_collapse_one(Model1_sk, Model1_skb, Model1_list);
   if (!Model1_skb)
    break;
   goto Model1_restart;
  }

  /* The first skb to collapse is:
		 * - not SYN/FIN and
		 * - bloated or contains data before "start" or
		 *   overlaps to the next one.
		 */
  if (!(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_tcp_flags & (0x02 | 0x01)) &&
      (Model1_tcp_win_from_space(Model1_skb->Model1_truesize) > Model1_skb->Model1_len ||
       Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, Model1_start))) {
   Model1_end_of_skbs = false;
   break;
  }

  if (!Model1_skb_queue_is_last(Model1_list, Model1_skb)) {
   struct Model1_sk_buff *Model1_next = Model1_skb_queue_next(Model1_list, Model1_skb);
   if (Model1_next != Model1_tail &&
       ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq != ((struct Model1_tcp_skb_cb *)&((Model1_next)->Model1_cb[0]))->Model1_seq) {
    Model1_end_of_skbs = false;
    break;
   }
  }

  /* Decided to skip this, advance start seq. */
  Model1_start = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq;
 }
 if (Model1_end_of_skbs ||
     (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_tcp_flags & (0x02 | 0x01)))
  return;

 while (Model1_before(Model1_start, Model1_end)) {
  int Model1_copy = ({ int Model1___min1 = ((((((1UL) << 12) << (0)) - (0)) - ((((sizeof(struct Model1_skb_shared_info))) + ((typeof((sizeof(struct Model1_skb_shared_info))))(((1 << (6)))) - 1)) & ~((typeof((sizeof(struct Model1_skb_shared_info))))(((1 << (6)))) - 1)))); int Model1___min2 = (Model1_end - Model1_start); Model1___min1 < Model1___min2 ? Model1___min1: Model1___min2; });
  struct Model1_sk_buff *Model1_nskb;

  Model1_nskb = Model1_alloc_skb(Model1_copy, ((( Model1_gfp_t)0x20u)|(( Model1_gfp_t)0x80000u)|(( Model1_gfp_t)0x2000000u)));
  if (!Model1_nskb)
   return;

  ({ Model1_size_t Model1___len = (sizeof(Model1_skb->Model1_cb)); void *Model1___ret; if (__builtin_constant_p(sizeof(Model1_skb->Model1_cb)) && Model1___len >= 64) Model1___ret = Model1___memcpy((Model1_nskb->Model1_cb), (Model1_skb->Model1_cb), Model1___len); else Model1___ret = __builtin_memcpy((Model1_nskb->Model1_cb), (Model1_skb->Model1_cb), Model1___len); Model1___ret; });
  ((struct Model1_tcp_skb_cb *)&((Model1_nskb)->Model1_cb[0]))->Model1_seq = ((struct Model1_tcp_skb_cb *)&((Model1_nskb)->Model1_cb[0]))->Model1_end_seq = Model1_start;
  Model1___skb_queue_before(Model1_list, Model1_skb, Model1_nskb);
  Model1_skb_set_owner_r(Model1_nskb, Model1_sk);

  /* Copy data, releasing collapsed skbs. */
  while (Model1_copy > 0) {
   int Model1_offset = Model1_start - ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq;
   int Model1_size = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq - Model1_start;

   do { if (Model1_offset < 0) do { asm volatile("ud2"); do { } while (1); } while (0); } while (0);
   if (Model1_size > 0) {
    Model1_size = ({ typeof(Model1_copy) Model1__min1 = (Model1_copy); typeof(Model1_size) Model1__min2 = (Model1_size); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
    if (Model1_skb_copy_bits(Model1_skb, Model1_offset, Model1_skb_put(Model1_nskb, Model1_size), Model1_size))
     do { asm volatile("ud2"); do { } while (1); } while (0);
    ((struct Model1_tcp_skb_cb *)&((Model1_nskb)->Model1_cb[0]))->Model1_end_seq += Model1_size;
    Model1_copy -= Model1_size;
    Model1_start += Model1_size;
   }
   if (!Model1_before(Model1_start, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq)) {
    Model1_skb = Model1_tcp_collapse_one(Model1_sk, Model1_skb, Model1_list);
    if (!Model1_skb ||
        Model1_skb == Model1_tail ||
        (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_tcp_flags & (0x02 | 0x01)))
     return;
   }
  }
 }
}

/* Collapse ofo queue. Algorithm: select contiguous sequence of skbs
 * and tcp_collapse() them until all the queue is collapsed.
 */
static void Model1_tcp_collapse_ofo_queue(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_sk_buff *Model1_skb = Model1_skb_peek(&Model1_tp->Model1_out_of_order_queue);
 struct Model1_sk_buff *Model1_head;
 Model1_u32 Model1_start, Model1_end;

 if (!Model1_skb)
  return;

 Model1_start = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq;
 Model1_end = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq;
 Model1_head = Model1_skb;

 for (;;) {
  struct Model1_sk_buff *Model1_next = ((void *)0);

  if (!Model1_skb_queue_is_last(&Model1_tp->Model1_out_of_order_queue, Model1_skb))
   Model1_next = Model1_skb_queue_next(&Model1_tp->Model1_out_of_order_queue, Model1_skb);
  Model1_skb = Model1_next;

  /* Segment is terminated when we see gap or when
		 * we are at the end of all the queue. */
  if (!Model1_skb ||
      Model1_before(Model1_end, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq) ||
      Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq, Model1_start)) {
   Model1_tcp_collapse(Model1_sk, &Model1_tp->Model1_out_of_order_queue,
         Model1_head, Model1_skb, Model1_start, Model1_end);
   Model1_head = Model1_skb;
   if (!Model1_skb)
    break;
   /* Start new segment */
   Model1_start = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq;
   Model1_end = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq;
  } else {
   if (Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, Model1_start))
    Model1_start = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq;
   if (Model1_before(Model1_end, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq))
    Model1_end = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq;
  }
 }
}

/*
 * Purge the out-of-order queue.
 * Return true if queue was pruned.
 */
static bool Model1_tcp_prune_ofo_queue(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 bool Model1_res = false;

 if (!Model1_skb_queue_empty(&Model1_tp->Model1_out_of_order_queue)) {
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_OFOPRUNED] += 1);
  Model1___skb_queue_purge(&Model1_tp->Model1_out_of_order_queue);

  /* Reset SACK state.  A conforming SACK implementation will
		 * do the same at a timeout based retransmit.  When a connection
		 * is in a sad state like this, we care only about integrity
		 * of the connection not performance.
		 */
  if (Model1_tp->Model1_rx_opt.Model1_sack_ok)
   Model1_tcp_sack_reset(&Model1_tp->Model1_rx_opt);
  Model1_sk_mem_reclaim(Model1_sk);
  Model1_res = true;
 }
 return Model1_res;
}

/* Reduce allocated memory if we can, trying to get
 * the socket within its memory limits again.
 *
 * Return less than zero if we should start dropping frames
 * until the socket owning process reads some of the data
 * to stabilize the situation.
 */
static int Model1_tcp_prune_queue(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 do { if ((Model1_sk) && Model1_sock_flag((Model1_sk), Model1_SOCK_DBG)) Model1_printk("\001" "7" "prune_queue: c=%x\n", Model1_tp->Model1_copied_seq); } while (0);

 (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_PRUNECALLED] += 1);

 if (Model1_atomic_read(&Model1_sk->Model1_sk_backlog.Model1_rmem_alloc) >= Model1_sk->Model1_sk_rcvbuf)
  Model1_tcp_clamp_window(Model1_sk);
 else if (Model1_tcp_under_memory_pressure(Model1_sk))
  Model1_tp->Model1_rcv_ssthresh = ({ typeof(Model1_tp->Model1_rcv_ssthresh) Model1__min1 = (Model1_tp->Model1_rcv_ssthresh); typeof(4U * Model1_tp->Model1_advmss) Model1__min2 = (4U * Model1_tp->Model1_advmss); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });

 Model1_tcp_collapse_ofo_queue(Model1_sk);
 if (!Model1_skb_queue_empty(&Model1_sk->Model1_sk_receive_queue))
  Model1_tcp_collapse(Model1_sk, &Model1_sk->Model1_sk_receive_queue,
        Model1_skb_peek(&Model1_sk->Model1_sk_receive_queue),
        ((void *)0),
        Model1_tp->Model1_copied_seq, Model1_tp->Model1_rcv_nxt);
 Model1_sk_mem_reclaim(Model1_sk);

 if (Model1_atomic_read(&Model1_sk->Model1_sk_backlog.Model1_rmem_alloc) <= Model1_sk->Model1_sk_rcvbuf)
  return 0;

 /* Collapsing did not help, destructive actions follow.
	 * This must not ever occur. */

 Model1_tcp_prune_ofo_queue(Model1_sk);

 if (Model1_atomic_read(&Model1_sk->Model1_sk_backlog.Model1_rmem_alloc) <= Model1_sk->Model1_sk_rcvbuf)
  return 0;

 /* If we are really being abused, tell the caller to silently
	 * drop receive data on the floor.  It will get retransmitted
	 * and hopefully then we'll have sufficient space.
	 */
 (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_RCVPRUNED] += 1);

 /* Massive buffer overcommit. */
 Model1_tp->Model1_pred_flags = 0;
 return -1;
}

static bool Model1_tcp_should_expand_sndbuf(const struct Model1_sock *Model1_sk)
{
 const struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 /* If the user specified a specific send buffer setting, do
	 * not modify it.
	 */
 if (Model1_sk->Model1_sk_userlocks & 1)
  return false;

 /* If we are under global TCP memory pressure, do not expand.  */
 if (Model1_tcp_under_memory_pressure(Model1_sk))
  return false;

 /* If we are under soft global TCP memory pressure, do not expand.  */
 if (Model1_sk_memory_allocated(Model1_sk) >= Model1_sk_prot_mem_limits(Model1_sk, 0))
  return false;

 /* If we filled the congestion window, do not expand.  */
 if (Model1_tcp_packets_in_flight(Model1_tp) >= Model1_tp->Model1_snd_cwnd)
  return false;

 return true;
}

/* When incoming ACK allowed to free some skb from write_queue,
 * we remember this event in flag SOCK_QUEUE_SHRUNK and wake up socket
 * on the exit from tcp input handler.
 *
 * PROBLEM: sndbuf expansion does not work well with largesend.
 */
static void Model1_tcp_new_space(struct Model1_sock *Model1_sk)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 if (Model1_tcp_should_expand_sndbuf(Model1_sk)) {
  Model1_tcp_sndbuf_expand(Model1_sk);
  Model1_tp->Model1_snd_cwnd_stamp = ((__u32)(Model1_jiffies));
 }

 Model1_sk->Model1_sk_write_space(Model1_sk);
}

static void Model1_tcp_check_space(struct Model1_sock *Model1_sk)
{
#if !CY_ABSTRACT1
 if (Model1_sock_flag(Model1_sk, Model1_SOCK_QUEUE_SHRUNK)) {
  Model1_sock_reset_flag(Model1_sk, Model1_SOCK_QUEUE_SHRUNK);
  /* pairs with tcp_poll() */
  __asm__ __volatile__("": : :"memory");
  if (Model1_sk->Model1_sk_socket &&
      (__builtin_constant_p((2)) ? Model1_constant_test_bit((2), (&Model1_sk->Model1_sk_socket->Model1_flags)) : Model1_variable_test_bit((2), (&Model1_sk->Model1_sk_socket->Model1_flags))))
   Model1_tcp_new_space(Model1_sk);
 }
#endif
}

static inline __attribute__((no_instrument_function)) void Model1_tcp_data_snd_check(struct Model1_sock *Model1_sk)
{
 Model1_tcp_push_pending_frames(Model1_sk);
 Model1_tcp_check_space(Model1_sk);
}

/*
 * Check if sending an ack is needed.
 */
static void Model1___tcp_ack_snd_check(struct Model1_sock *Model1_sk, int Model1_ofo_possible)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

     /* More than one full frame received... */
 if (((Model1_tp->Model1_rcv_nxt - Model1_tp->Model1_rcv_wup) > Model1_inet_csk(Model1_sk)->Model1_icsk_ack.Model1_rcv_mss &&
      /* ... and right edge of window advances far enough.
	      * (tcp_recvmsg() will send ACK otherwise). Or...
	      */
      Model1___tcp_select_window(Model1_sk) >= Model1_tp->Model1_rcv_wnd) ||
     /* We ACK each frame or... */
     Model1_tcp_in_quickack_mode(Model1_sk) ||
     /* We have out of order data. */
     (Model1_ofo_possible && Model1_skb_peek(&Model1_tp->Model1_out_of_order_queue))) {
  /* Then ack it now */
  Model1_tcp_send_ack(Model1_sk);
 } else {
  /* Else, send delayed ack. */
  Model1_tcp_send_delayed_ack(Model1_sk);
 }
}

static inline __attribute__((no_instrument_function)) void Model1_tcp_ack_snd_check(struct Model1_sock *Model1_sk)
{
 if (!Model1_inet_csk_ack_scheduled(Model1_sk)) {
  /* We sent a data segment already. */
  return;
 }
 Model1___tcp_ack_snd_check(Model1_sk, 1);
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

static void Model1_tcp_check_urg(struct Model1_sock *Model1_sk, const struct Model1_tcphdr *Model1_th)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 Model1_u32 Model1_ptr = (__builtin_constant_p((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_th->Model1_urg_ptr))) ? ((Model1___u16)( (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_th->Model1_urg_ptr)) & (Model1___u16)0x00ffU) << 8) | (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_th->Model1_urg_ptr)) & (Model1___u16)0xff00U) >> 8))) : Model1___fswab16(( Model1___u16)(Model1___be16)(Model1_th->Model1_urg_ptr)));

 if (Model1_ptr && !Model1_sysctl_tcp_stdurg)
  Model1_ptr--;
 Model1_ptr += (__builtin_constant_p((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq))) ? ((__u32)( (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32(( __u32)(Model1___be32)(Model1_th->Model1_seq)));

 /* Ignore urgent data that we've already seen and read. */
 if (Model1_before(Model1_ptr, Model1_tp->Model1_copied_seq))
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
 if (Model1_before(Model1_ptr, Model1_tp->Model1_rcv_nxt))
  return;

 /* Do we already have a newer (or duplicate) urgent pointer? */
 if (Model1_tp->Model1_urg_data && !Model1_before(Model1_tp->Model1_urg_seq, Model1_ptr))
  return;

 /* Tell the world about our new urgent pointer. */
 Model1_sk_send_sigurg(Model1_sk);

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
 if (Model1_tp->Model1_urg_seq == Model1_tp->Model1_copied_seq && Model1_tp->Model1_urg_data &&
     !Model1_sock_flag(Model1_sk, Model1_SOCK_URGINLINE) && Model1_tp->Model1_copied_seq != Model1_tp->Model1_rcv_nxt) {
  struct Model1_sk_buff *Model1_skb = Model1_skb_peek(&Model1_sk->Model1_sk_receive_queue);
  Model1_tp->Model1_copied_seq++;
  if (Model1_skb && !Model1_before(Model1_tp->Model1_copied_seq, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq)) {
   Model1___skb_unlink(Model1_skb, &Model1_sk->Model1_sk_receive_queue);
   Model1___kfree_skb(Model1_skb);
  }
 }

 Model1_tp->Model1_urg_data = 0x0200;
 Model1_tp->Model1_urg_seq = Model1_ptr;

 /* Disable header prediction. */
 Model1_tp->Model1_pred_flags = 0;
}

/* This is the 'fast' part of urgent handling. */
static void Model1_tcp_urg(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb, const struct Model1_tcphdr *Model1_th)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);

 /* Check if we get a new urgent pointer - normally not. */
 if (Model1_th->Model1_urg)
  Model1_tcp_check_urg(Model1_sk, Model1_th);

 /* Do we wait for any urgent data? - normally not... */
 if (Model1_tp->Model1_urg_data == 0x0200) {
  Model1_u32 Model1_ptr = Model1_tp->Model1_urg_seq - (__builtin_constant_p((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq))) ? ((__u32)( (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(Model1___be32)(Model1_th->Model1_seq)) & (__u32)0xff000000UL) >> 24))) : Model1___fswab32(( __u32)(Model1___be32)(Model1_th->Model1_seq))) + (Model1_th->Model1_doff * 4) -
     Model1_th->Model1_syn;

  /* Is the urgent pointer pointing into this packet? */
  if (Model1_ptr < Model1_skb->Model1_len) {
   Model1_u8 Model1_tmp;
   if (Model1_skb_copy_bits(Model1_skb, Model1_ptr, &Model1_tmp, 1))
    do { asm volatile("ud2"); do { } while (1); } while (0);
   Model1_tp->Model1_urg_data = 0x0100 | Model1_tmp;
   if (!Model1_sock_flag(Model1_sk, Model1_SOCK_DEAD))
#if CY_ABSTRACT7
    Model1_sock_def_readable(Model1_sk);
#else
    Model1_sk->Model1_sk_data_ready(Model1_sk);
#endif
  }
 }
}

static int Model1_tcp_copy_to_iovec(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb, int Model1_hlen)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 int Model1_chunk = Model1_skb->Model1_len - Model1_hlen;
 int err;

 if (Model1_skb_csum_unnecessary(Model1_skb))
  err = Model1_skb_copy_datagram_msg(Model1_skb, Model1_hlen, Model1_tp->Model1_ucopy.Model1_msg, Model1_chunk);
 else
  err = Model1_skb_copy_and_csum_datagram_msg(Model1_skb, Model1_hlen, Model1_tp->Model1_ucopy.Model1_msg);

 if (!err) {
  Model1_tp->Model1_ucopy.Model1_len -= Model1_chunk;
  Model1_tp->Model1_copied_seq += Model1_chunk;
  Model1_tcp_rcv_space_adjust(Model1_sk);
 }

 return err;
}

/* Does PAWS and seqno based validation of an incoming segment, flags will
 * play significant role here.
 */
static bool Model1_tcp_validate_incoming(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb,
      const struct Model1_tcphdr *Model1_th, int Model1_syn_inerr)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 bool Model1_rst_seq_match = false;
#if !CY_ABSTRACT1
 /* RFC1323: H1. Apply PAWS check first. */
 if (Model1_tcp_fast_parse_options(Model1_skb, Model1_th, Model1_tp) && Model1_tp->Model1_rx_opt.Model1_saw_tstamp &&
     Model1_tcp_paws_discard(Model1_sk, Model1_skb)) {
  if (!Model1_th->Model1_rst) {
   (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_PAWSESTABREJECTED] += 1);
   if (!Model1_tcp_oow_rate_limited(Model1_sock_net(Model1_sk), Model1_skb,
        Model1_LINUX_MIB_TCPACKSKIPPEDPAWS,
        &Model1_tp->Model1_last_oow_ack_time))
    Model1_tcp_send_dupack(Model1_sk, Model1_skb);
   goto Model1_discard;
  }
  /* Reset is accepted even if it did not pass PAWS. */
 }
#endif
 /* Step 1: check sequence number */
 if (!Model1_tcp_sequence(Model1_tp, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq)) {
  /* RFC793, page 37: "In all states except SYN-SENT, all reset
		 * (RST) segments are validated by checking their SEQ-fields."
		 * And page 69: "If an incoming segment is not acceptable,
		 * an acknowledgment should be sent in reply (unless the RST
		 * bit is set, if so drop the segment and return)".
		 */
  if (!Model1_th->Model1_rst) {
   if (Model1_th->Model1_syn)
    goto Model1_syn_challenge;
   if (!Model1_tcp_oow_rate_limited(Model1_sock_net(Model1_sk), Model1_skb,
        Model1_LINUX_MIB_TCPACKSKIPPEDSEQ,
        &Model1_tp->Model1_last_oow_ack_time))
    Model1_tcp_send_dupack(Model1_sk, Model1_skb);
  }
  goto Model1_discard;
 }

 /* Step 2: check RST bit */
 if (Model1_th->Model1_rst) {
  /* RFC 5961 3.2 (extend to match against SACK too if available):
		 * If seq num matches RCV.NXT or the right-most SACK block,
		 * then
		 *     RESET the connection
		 * else
		 *     Send a challenge ACK
		 */
  if (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq == Model1_tp->Model1_rcv_nxt) {
   Model1_rst_seq_match = true;
  } 
#if !CY_ABSTRACT1
else if (Model1_tcp_is_sack(Model1_tp) && Model1_tp->Model1_rx_opt.Model1_num_sacks > 0) {
   struct Model1_tcp_sack_block *Model1_sp = &Model1_tp->Model1_selective_acks[0];
   int Model1_max_sack = Model1_sp[0].Model1_end_seq;
   int Model1_this_sack;

   for (Model1_this_sack = 1; Model1_this_sack < Model1_tp->Model1_rx_opt.Model1_num_sacks;
        ++Model1_this_sack) {
    Model1_max_sack = Model1_before(Model1_max_sack, Model1_sp[Model1_this_sack].Model1_end_seq) ?

     Model1_sp[Model1_this_sack].Model1_end_seq : Model1_max_sack;
   }

   if (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq == Model1_max_sack)
    Model1_rst_seq_match = true;
  }
#endif
  if (Model1_rst_seq_match)
   Model1_tcp_reset(Model1_sk);
  else
   Model1_tcp_send_challenge_ack(Model1_sk, Model1_skb);
  goto Model1_discard;
 }

 /* step 3: check security and precedence [ignored] */

 /* step 4: Check for a SYN
	 * RFC 5961 4.2 : Send a challenge ack
	 */
 if (Model1_th->Model1_syn) {
Model1_syn_challenge:
  if (Model1_syn_inerr)
   (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_INERRS] += 1);
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPSYNCHALLENGE] += 1);
  Model1_tcp_send_challenge_ack(Model1_sk, Model1_skb);
  goto Model1_discard;
 }

 return true;

Model1_discard:
 Model1_tcp_drop(Model1_sk, Model1_skb);
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
void Model1_tcp_rcv_established(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb,
    const struct Model1_tcphdr *Model1_th, unsigned int Model1_len)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
#if !CY_ABSTRACT1
 if (__builtin_expect(!!(!Model1_sk->Model1_sk_rx_dst), 0))
  Model1_inet_csk(Model1_sk)->Model1_icsk_af_ops->Model1_sk_rx_dst_set(Model1_sk, Model1_skb);
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

 Model1_tp->Model1_rx_opt.Model1_saw_tstamp = 0;

 /*	pred_flags is 0xS?10 << 16 + snd_wnd
	 *	if header_prediction is to be made
	 *	'S' will always be tp->tcp_header_len >> 2
	 *	'?' will be 0 for the fast path, otherwise pred_flags is 0 to
	 *  turn it off	(when there are holes in the receive
	 *	 space for instance)
	 *	PSH flag is ignored.
	 */

 if ((( ((union Model1_tcp_word_hdr *)(Model1_th))->Model1_words [3]) & (~(Model1_TCP_RESERVED_BITS|Model1_TCP_FLAG_PSH))) == Model1_tp->Model1_pred_flags &&
     ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq == Model1_tp->Model1_rcv_nxt &&
     !Model1_before(Model1_tp->Model1_snd_nxt, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_ack_seq)) {
  int Model1_tcp_header_len = Model1_tp->Model1_tcp_header_len;

  /* Timestamp header prediction: tcp_header_len
		 * is automatically equal to th->doff*4 due to pred_flags
		 * match.
		 */
#if !CY_ABSTRACT1
  /* Check timestamp */
  if (Model1_tcp_header_len == sizeof(struct Model1_tcphdr) + 12) {
   /* No? Slow path! */
   if (!Model1_tcp_parse_aligned_timestamp(Model1_tp, Model1_th))
    goto Model1_slow_path;

   /* If PAWS failed, check it more carefully in slow path */
   if ((Model1_s32)(Model1_tp->Model1_rx_opt.Model1_rcv_tsval - Model1_tp->Model1_rx_opt.Model1_ts_recent) < 0)
    goto Model1_slow_path;

   /* DO NOT update ts_recent here, if checksum fails
			 * and timestamp was corrupted part, it will result
			 * in a hung connection since we will drop all
			 * future packets due to the PAWS test.
			 */
  }
#endif

  if (Model1_len <= Model1_tcp_header_len) {
   /* Bulk data transfer: sender */
   if (Model1_len == Model1_tcp_header_len) {
    /* Predicted packet is in window by definition.
				 * seq == rcv_nxt and rcv_wup <= rcv_nxt.
				 * Hence, check seq<=rcv_wup reduces to:
				 */
#if !CY_ABSTRACT1
    if (Model1_tcp_header_len ==
        (sizeof(struct Model1_tcphdr) + 12) &&
        Model1_tp->Model1_rcv_nxt == Model1_tp->Model1_rcv_wup)
     Model1_tcp_store_ts_recent(Model1_tp);
#endif
    /* We know that such packets are checksummed
				 * on entry.
				 */
    Model1_tcp_ack(Model1_sk, Model1_skb, 0);
    Model1___kfree_skb(Model1_skb);
    Model1_tcp_data_snd_check(Model1_sk);
    return;
   } else { /* Header too small */
    (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_INERRS] += 1);
    goto Model1_discard;
   }
  } else {
   int Model1_eaten = 0;
   bool Model1_fragstolen = false;
#if !CY_ABSTRACT1 //assume Model1_task always not equal to get_current()
   if (Model1_tp->Model1_ucopy.Model1_task == Model1_get_current() &&
       Model1_tp->Model1_copied_seq == Model1_tp->Model1_rcv_nxt &&
       Model1_len - Model1_tcp_header_len <= Model1_tp->Model1_ucopy.Model1_len &&
       Model1_sock_owned_by_user(Model1_sk)) {
    do { Model1_get_current()->Model1_state = (0); } while (0);

    if (!Model1_tcp_copy_to_iovec(Model1_sk, Model1_skb, Model1_tcp_header_len)) {
     /* Predicted packet is in window by definition.
					 * seq == rcv_nxt and rcv_wup <= rcv_nxt.
					 * Hence, check seq<=rcv_wup reduces to:
					 */
     if (Model1_tcp_header_len ==
         (sizeof(struct Model1_tcphdr) +
          12) &&
         Model1_tp->Model1_rcv_nxt == Model1_tp->Model1_rcv_wup)
      Model1_tcp_store_ts_recent(Model1_tp);

     Model1_tcp_rcv_rtt_measure_ts(Model1_sk, Model1_skb);

     Model1___skb_pull(Model1_skb, Model1_tcp_header_len);
     Model1_tcp_rcv_nxt_update(Model1_tp, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq);
     (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPHPHITSTOUSER] += 1);

     Model1_eaten = 1;
    }
   }
#endif
   if (!Model1_eaten) {
    if (Model1_tcp_checksum_complete(Model1_skb))
     goto Model1_csum_error;

    if ((int)Model1_skb->Model1_truesize > Model1_sk->Model1_sk_forward_alloc)
     goto Model1_step5;

    /* Predicted packet is in window by definition.
				 * seq == rcv_nxt and rcv_wup <= rcv_nxt.
				 * Hence, check seq<=rcv_wup reduces to:
				 */
#if !CY_ABSTRACT1
    if (Model1_tcp_header_len ==
        (sizeof(struct Model1_tcphdr) + 12) &&
        Model1_tp->Model1_rcv_nxt == Model1_tp->Model1_rcv_wup)
     Model1_tcp_store_ts_recent(Model1_tp);
#endif
    Model1_tcp_rcv_rtt_measure_ts(Model1_sk, Model1_skb);

    (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPHPHITS] += 1);

    /* Bulk data transfer: receiver */
    Model1_eaten = Model1_tcp_queue_rcv(Model1_sk, Model1_skb, Model1_tcp_header_len,
            &Model1_fragstolen);
   }

   Model1_tcp_event_data_recv(Model1_sk, Model1_skb);

   if (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_ack_seq != Model1_tp->Model1_snd_una) {
    /* Well, only one small jumplet in fast path... */
    Model1_tcp_ack(Model1_sk, Model1_skb, 0x01);
    Model1_tcp_data_snd_check(Model1_sk);
    if (!Model1_inet_csk_ack_scheduled(Model1_sk))
     goto Model1_no_ack;
   }

   Model1___tcp_ack_snd_check(Model1_sk, 0);
Model1_no_ack:
   if (Model1_eaten)
    Model1_kfree_skb_partial(Model1_skb, Model1_fragstolen);
#if !CY_ABSTRACT1
   Model1_sk->Model1_sk_data_ready(Model1_sk);
#endif
   return;
  }
 }

Model1_slow_path:
 if (Model1_len < (Model1_th->Model1_doff << 2) || Model1_tcp_checksum_complete(Model1_skb))
  goto Model1_csum_error;

 if (!Model1_th->Model1_ack && !Model1_th->Model1_rst && !Model1_th->Model1_syn)
  goto Model1_discard;

 /*
	 *	Standard slow path.
	 */

 if (!Model1_tcp_validate_incoming(Model1_sk, Model1_skb, Model1_th, 1))
  return;

Model1_step5:
 if (Model1_tcp_ack(Model1_sk, Model1_skb, 0x100 | 0x4000) < 0)
  goto Model1_discard;

 Model1_tcp_rcv_rtt_measure_ts(Model1_sk, Model1_skb);

 /* Process urgent data. */
 Model1_tcp_urg(Model1_sk, Model1_skb, Model1_th);

 /* step 7: process the segment text */
 Model1_tcp_data_queue(Model1_sk, Model1_skb);

 Model1_tcp_data_snd_check(Model1_sk);
 Model1_tcp_ack_snd_check(Model1_sk);
 return;

Model1_csum_error:
 (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_CSUMERRORS] += 1);
 (Model1_cy_tcp_mib.Model1_mibs[Model1_TCP_MIB_INERRS] += 1);

Model1_discard:
 Model1_tcp_drop(Model1_sk, Model1_skb);
}
                                  ;

void Model1_tcp_finish_connect(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);

 Model1_tcp_set_state(Model1_sk, Model1_TCP_ESTABLISHED);

 if (Model1_skb) {
#if CY_ABSTRACT7
  Model1_inet_sk_rx_dst_set(Model1_sk, Model1_skb);
#else
  Model1_icsk->Model1_icsk_af_ops->Model1_sk_rx_dst_set(Model1_sk, Model1_skb);
#endif
  Model1_security_inet_conn_established(Model1_sk, Model1_skb);
 }

 /* Make sure socket is routed, for correct metrics.  */
#if CY_ABSTRACT7
 Model1_inet_sk_rebuild_header(Model1_sk);
#else
 Model1_icsk->Model1_icsk_af_ops->Model1_rebuild_header(Model1_sk);
#endif

 Model1_tcp_init_metrics(Model1_sk);

 Model1_tcp_init_congestion_control(Model1_sk);

 /* Prevent spurious tcp_cwnd_restart() on first data
	 * packet.
	 */
 Model1_tp->Model1_lsndtime = ((__u32)(Model1_jiffies));

 Model1_tcp_init_buffer_space(Model1_sk);

 if (Model1_sock_flag(Model1_sk, Model1_SOCK_KEEPOPEN))
  Model1_inet_csk_reset_keepalive_timer(Model1_sk, Model1_keepalive_time_when(Model1_tp));

 if (!Model1_tp->Model1_rx_opt.Model1_snd_wscale)
  Model1___tcp_fast_path_on(Model1_tp, Model1_tp->Model1_snd_wnd);
 else
  Model1_tp->Model1_pred_flags = 0;

 if (!Model1_sock_flag(Model1_sk, Model1_SOCK_DEAD)) {
#if CY_ABSTRACT7
  Model1_sock_def_wakeup(Model1_sk);
#else
  Model1_sk->Model1_sk_state_change(Model1_sk);
#endif
  Model1_sk_wake_async(Model1_sk, Model1_SOCK_WAKE_IO, ((2 << 16)|2));
 }
}

static bool Model1_tcp_rcv_fastopen_synack(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_synack,
        struct Model1_tcp_fastopen_cookie *Model1_cookie)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_sk_buff *Model1_data = Model1_tp->Model1_syn_data ? Model1_tcp_write_queue_head(Model1_sk) : ((void *)0);
 Model1_u16 Model1_mss = Model1_tp->Model1_rx_opt.Model1_mss_clamp, Model1_try_exp = 0;
 bool Model1_syn_drop = false;

 if (Model1_mss == Model1_tp->Model1_rx_opt.Model1_user_mss) {
  struct Model1_tcp_options_received Model1_opt;

  /* Get original SYNACK MSS value if user MSS sets mss_clamp */
  Model1_tcp_clear_options(&Model1_opt);
  Model1_opt.Model1_user_mss = Model1_opt.Model1_mss_clamp = 0;
  Model1_tcp_parse_options(Model1_synack, &Model1_opt, 0, ((void *)0));
  Model1_mss = Model1_opt.Model1_mss_clamp;
 }

 if (!Model1_tp->Model1_syn_fastopen) {
  /* Ignore an unsolicited cookie */
  Model1_cookie->Model1_len = -1;
 } else if (Model1_tp->Model1_total_retrans) {
  /* SYN timed out and the SYN-ACK neither has a cookie nor
		 * acknowledges data. Presumably the remote received only
		 * the retransmitted (regular) SYNs: either the original
		 * SYN-data or the corresponding SYN-ACK was dropped.
		 */
  Model1_syn_drop = (Model1_cookie->Model1_len < 0 && Model1_data);
 } else if (Model1_cookie->Model1_len < 0 && !Model1_tp->Model1_syn_data) {
  /* We requested a cookie but didn't get it. If we did not use
		 * the (old) exp opt format then try so next time (try_exp=1).
		 * Otherwise we go back to use the RFC7413 opt (try_exp=2).
		 */
  Model1_try_exp = Model1_tp->Model1_syn_fastopen_exp ? 2 : 1;
 }

 Model1_tcp_fastopen_cache_set(Model1_sk, Model1_mss, Model1_cookie, Model1_syn_drop, Model1_try_exp);

 if (Model1_data) { /* Retransmit unacked data in SYN */
  for (; Model1_data != (struct Model1_sk_buff *)(&(Model1_sk)->Model1_sk_write_queue); Model1_data = Model1_data->Model1_next) {
   if (Model1_data == Model1_tcp_send_head(Model1_sk) ||
       Model1___tcp_retransmit_skb(Model1_sk, Model1_data, 1))
    break;
  }
  Model1_tcp_rearm_rto(Model1_sk);
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPFASTOPENACTIVEFAIL] += 1);

  return true;
 }
 Model1_tp->Model1_syn_data_acked = Model1_tp->Model1_syn_data;
 if (Model1_tp->Model1_syn_data_acked)
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPFASTOPENACTIVE] += 1);


 Model1_tcp_fastopen_add_skb(Model1_sk, Model1_synack);

 return false;
}

static int Model1_tcp_rcv_synsent_state_process(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb,
      const struct Model1_tcphdr *Model1_th)
{
 struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_tcp_fastopen_cookie Model1_foc = { .Model1_len = -1 };
 int Model1_saved_clamp = Model1_tp->Model1_rx_opt.Model1_mss_clamp;

 Model1_tcp_parse_options(Model1_skb, &Model1_tp->Model1_rx_opt, 0, &Model1_foc);
 if (Model1_tp->Model1_rx_opt.Model1_saw_tstamp && Model1_tp->Model1_rx_opt.Model1_rcv_tsecr)
  Model1_tp->Model1_rx_opt.Model1_rcv_tsecr -= Model1_tp->Model1_tsoffset;

 if (Model1_th->Model1_ack) {
  /* rfc793:
		 * "If the state is SYN-SENT then
		 *    first check the ACK bit
		 *      If the ACK bit is set
		 *	  If SEG.ACK =< ISS, or SEG.ACK > SND.NXT, send
		 *        a reset (unless the RST bit is set, if so drop
		 *        the segment and return)"
		 */
  if (!Model1_before(Model1_tp->Model1_snd_una, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_ack_seq) ||
      Model1_before(Model1_tp->Model1_snd_nxt, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_ack_seq))
   goto Model1_reset_and_undo;

  if (Model1_tp->Model1_rx_opt.Model1_saw_tstamp && Model1_tp->Model1_rx_opt.Model1_rcv_tsecr &&
      !Model1_between(Model1_tp->Model1_rx_opt.Model1_rcv_tsecr, Model1_tp->Model1_retrans_stamp,
        ((__u32)(Model1_jiffies)))) {
   (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_PAWSACTIVEREJECTED] += 1);

   goto Model1_reset_and_undo;
  }

  /* Now ACK is acceptable.
		 *
		 * "If the RST bit is set
		 *    If the ACK was acceptable then signal the user "error:
		 *    connection reset", drop the segment, enter CLOSED state,
		 *    delete TCB, and return."
		 */

  if (Model1_th->Model1_rst) {
   Model1_tcp_reset(Model1_sk);
   goto Model1_discard;
  }

  /* rfc793:
		 *   "fifth, if neither of the SYN or RST bits is set then
		 *    drop the segment and return."
		 *
		 *    See note below!
		 *                                        --ANK(990513)
		 */
  if (!Model1_th->Model1_syn)
   goto Model1_discard_and_undo;

  /* rfc793:
		 *   "If the SYN bit is on ...
		 *    are acceptable then ...
		 *    (our SYN has been ACKed), change the connection
		 *    state to ESTABLISHED..."
		 */

  Model1_tcp_ecn_rcv_synack(Model1_tp, Model1_th);

  Model1_tcp_init_wl(Model1_tp, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq);
  Model1_tcp_ack(Model1_sk, Model1_skb, 0x100);

  /* Ok.. it's good. Set up sequence numbers and
		 * move to established.
		 */
  Model1_tp->Model1_rcv_nxt = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq + 1;
  Model1_tp->Model1_rcv_wup = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq + 1;

  /* RFC1323: The window in SYN & SYN/ACK segments is
		 * never scaled.
		 */
  Model1_tp->Model1_snd_wnd = (__builtin_constant_p((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_th->Model1_window))) ? ((Model1___u16)( (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_th->Model1_window)) & (Model1___u16)0x00ffU) << 8) | (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_th->Model1_window)) & (Model1___u16)0xff00U) >> 8))) : Model1___fswab16(( Model1___u16)(Model1___be16)(Model1_th->Model1_window)));

  if (!Model1_tp->Model1_rx_opt.Model1_wscale_ok) {
   Model1_tp->Model1_rx_opt.Model1_snd_wscale = Model1_tp->Model1_rx_opt.Model1_rcv_wscale = 0;
   Model1_tp->Model1_window_clamp = ({ typeof(Model1_tp->Model1_window_clamp) Model1__min1 = (Model1_tp->Model1_window_clamp); typeof(65535U) Model1__min2 = (65535U); (void) (&Model1__min1 == &Model1__min2); Model1__min1 < Model1__min2 ? Model1__min1 : Model1__min2; });
  }

  if (Model1_tp->Model1_rx_opt.Model1_saw_tstamp) {
   Model1_tp->Model1_rx_opt.Model1_tstamp_ok = 1;
   Model1_tp->Model1_tcp_header_len =
    sizeof(struct Model1_tcphdr) + 12;
   Model1_tp->Model1_advmss -= 12;
   Model1_tcp_store_ts_recent(Model1_tp);
  } else {
   Model1_tp->Model1_tcp_header_len = sizeof(struct Model1_tcphdr);
  }

  if (Model1_tcp_is_sack(Model1_tp) && Model1_sysctl_tcp_fack)
   Model1_tcp_enable_fack(Model1_tp);

  Model1_tcp_mtup_init(Model1_sk);
  Model1_tcp_sync_mss(Model1_sk, Model1_icsk->Model1_icsk_pmtu_cookie);
  Model1_tcp_initialize_rcv_mss(Model1_sk);

  /* Remember, tcp_poll() does not lock socket!
		 * Change state from SYN-SENT only after copied_seq
		 * is initialized. */
  Model1_tp->Model1_copied_seq = Model1_tp->Model1_rcv_nxt;

  __asm__ __volatile__("": : :"memory");

  Model1_tcp_finish_connect(Model1_sk, Model1_skb);

  if ((Model1_tp->Model1_syn_fastopen || Model1_tp->Model1_syn_data) &&
      Model1_tcp_rcv_fastopen_synack(Model1_sk, Model1_skb, &Model1_foc))
   return -1;

  if (Model1_sk->Model1_sk_write_pending ||
      Model1_icsk->Model1_icsk_accept_queue.Model1_rskq_defer_accept ||
      Model1_icsk->Model1_icsk_ack.Model1_pingpong) {
   /* Save one ACK. Data will be ready after
			 * several ticks, if write_pending is set.
			 *
			 * It may be deleted, but with this feature tcpdumps
			 * look so _wonderfully_ clever, that I was not able
			 * to stand against the temptation 8)     --ANK
			 */
   Model1_inet_csk_schedule_ack(Model1_sk);
   Model1_icsk->Model1_icsk_ack.Model1_lrcvtime = ((__u32)(Model1_jiffies));
   Model1_tcp_enter_quickack_mode(Model1_sk);
   Model1_inet_csk_reset_xmit_timer(Model1_sk, 2,
        ((unsigned)(1000/5)), ((unsigned)(120*1000)));

Model1_discard:
   Model1_tcp_drop(Model1_sk, Model1_skb);
   return 0;
  } else {
   Model1_tcp_send_ack(Model1_sk);
  }
  return -1;
 }

 /* No ACK in the segment */

 if (Model1_th->Model1_rst) {
  /* rfc793:
		 * "If the RST bit is set
		 *
		 *      Otherwise (no ACK) drop the segment and return."
		 */

  goto Model1_discard_and_undo;
 }

 /* PAWS check. */
 if (Model1_tp->Model1_rx_opt.Model1_ts_recent_stamp && Model1_tp->Model1_rx_opt.Model1_saw_tstamp &&
     Model1_tcp_paws_reject(&Model1_tp->Model1_rx_opt, 0))
  goto Model1_discard_and_undo;

 if (Model1_th->Model1_syn) {
  /* We see SYN without ACK. It is attempt of
		 * simultaneous connect with crossed SYNs.
		 * Particularly, it can be connect to self.
		 */
  Model1_tcp_set_state(Model1_sk, Model1_TCP_SYN_RECV);

  if (Model1_tp->Model1_rx_opt.Model1_saw_tstamp) {
   Model1_tp->Model1_rx_opt.Model1_tstamp_ok = 1;
   Model1_tcp_store_ts_recent(Model1_tp);
   Model1_tp->Model1_tcp_header_len =
    sizeof(struct Model1_tcphdr) + 12;
  } else {
   Model1_tp->Model1_tcp_header_len = sizeof(struct Model1_tcphdr);
  }

  Model1_tp->Model1_rcv_nxt = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq + 1;
  Model1_tp->Model1_copied_seq = Model1_tp->Model1_rcv_nxt;
  Model1_tp->Model1_rcv_wup = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq + 1;

  /* RFC1323: The window in SYN & SYN/ACK segments is
		 * never scaled.
		 */
  Model1_tp->Model1_snd_wnd = (__builtin_constant_p((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_th->Model1_window))) ? ((Model1___u16)( (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_th->Model1_window)) & (Model1___u16)0x00ffU) << 8) | (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_th->Model1_window)) & (Model1___u16)0xff00U) >> 8))) : Model1___fswab16(( Model1___u16)(Model1___be16)(Model1_th->Model1_window)));
  Model1_tp->Model1_snd_wl1 = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq;
  Model1_tp->Model1_max_window = Model1_tp->Model1_snd_wnd;

  Model1_tcp_ecn_rcv_syn(Model1_tp, Model1_th);

  Model1_tcp_mtup_init(Model1_sk);
  Model1_tcp_sync_mss(Model1_sk, Model1_icsk->Model1_icsk_pmtu_cookie);
  Model1_tcp_initialize_rcv_mss(Model1_sk);

  Model1_tcp_send_synack(Model1_sk);
  goto Model1_discard;

 }
 /* "fifth, if neither of the SYN or RST bits is set then
	 * drop the segment and return."
	 */

Model1_discard_and_undo:
 Model1_tcp_clear_options(&Model1_tp->Model1_rx_opt);
 Model1_tp->Model1_rx_opt.Model1_mss_clamp = Model1_saved_clamp;
 goto Model1_discard;

Model1_reset_and_undo:
 Model1_tcp_clear_options(&Model1_tp->Model1_rx_opt);
 Model1_tp->Model1_rx_opt.Model1_mss_clamp = Model1_saved_clamp;
 return 1;
}

/*
 *	This function implements the receiving procedure of RFC 793 for
 *	all states except ESTABLISHED and TIME_WAIT.
 *	It's called from both tcp_v4_rcv and tcp_v6_rcv and should be
 *	address independent.
 */

int Model1_tcp_rcv_state_process(struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb)
{
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_inet_connection_sock *Model1_icsk = Model1_inet_csk(Model1_sk);
 const struct Model1_tcphdr *Model1_th = Model1_tcp_hdr(Model1_skb);
 struct Model1_request_sock *Model1_req;
 int Model1_queued = 0;
 bool Model1_acceptable;

 switch (Model1_sk->Model1___sk_common.Model1_skc_state) {
 case Model1_TCP_CLOSE:
  goto Model1_discard;

 case Model1_TCP_LISTEN:
  if (Model1_th->Model1_ack)
   return 1;

  if (Model1_th->Model1_rst)
   goto Model1_discard;

  if (Model1_th->Model1_syn) {
   if (Model1_th->Model1_fin)
    goto Model1_discard;
#if CY_ABSTRACT7
   if (Model1_tcp_v4_conn_request(Model1_sk, Model1_skb) < 0)
#else
   if (Model1_icsk->Model1_icsk_af_ops->Model1_conn_request(Model1_sk, Model1_skb) < 0)
#endif
    return 1;

   Model1_consume_skb(Model1_skb);
   return 0;
  }
  goto Model1_discard;

 case Model1_TCP_SYN_SENT:
  Model1_tp->Model1_rx_opt.Model1_saw_tstamp = 0;
  Model1_queued = Model1_tcp_rcv_synsent_state_process(Model1_sk, Model1_skb, Model1_th);
  if (Model1_queued >= 0)
   return Model1_queued;

  /* Do step6 onward by hand. */
  Model1_tcp_urg(Model1_sk, Model1_skb, Model1_th);
  Model1___kfree_skb(Model1_skb);
  Model1_tcp_data_snd_check(Model1_sk);
  return 0;
 }

 Model1_tp->Model1_rx_opt.Model1_saw_tstamp = 0;
 Model1_req = Model1_tp->Model1_fastopen_rsk;
 if (Model1_req) {
  ({ int Model1___ret_warn_on = !!(Model1_sk->Model1___sk_common.Model1_skc_state != Model1_TCP_SYN_RECV && Model1_sk->Model1___sk_common.Model1_skc_state != Model1_TCP_FIN_WAIT1); __builtin_expect(!!(Model1___ret_warn_on), 0); });


  if (!Model1_tcp_check_req(Model1_sk, Model1_skb, Model1_req, true))
   goto Model1_discard;
 }

 if (!Model1_th->Model1_ack && !Model1_th->Model1_rst && !Model1_th->Model1_syn)
  goto Model1_discard;
 if (!Model1_tcp_validate_incoming(Model1_sk, Model1_skb, Model1_th, 0))
  return 0;

 /* step 5: check the ACK field */
 Model1_acceptable = Model1_tcp_ack(Model1_sk, Model1_skb, 0x100 |
          0x4000) > 0;

 switch (Model1_sk->Model1___sk_common.Model1_skc_state) {
 case Model1_TCP_SYN_RECV:
  if (!Model1_acceptable)
   return 1;

  if (!Model1_tp->Model1_srtt_us)
   Model1_tcp_synack_rtt_meas(Model1_sk, Model1_req);

  /* Once we leave TCP_SYN_RECV, we no longer need req
		 * so release it.
		 */
  if (Model1_req) {
   Model1_inet_csk(Model1_sk)->Model1_icsk_retransmits = 0;
   Model1_reqsk_fastopen_remove(Model1_sk, Model1_req, false);
  } else {
   /* Make sure socket is routed, for correct metrics. */
#if CY_ABSTRACT7
   Model1_inet_sk_rebuild_header(Model1_sk);
#else
   Model1_icsk->Model1_icsk_af_ops->Model1_rebuild_header(Model1_sk);
#endif
   Model1_tcp_init_congestion_control(Model1_sk);

   Model1_tcp_mtup_init(Model1_sk);
   Model1_tp->Model1_copied_seq = Model1_tp->Model1_rcv_nxt;
   Model1_tcp_init_buffer_space(Model1_sk);
  }
  __asm__ __volatile__("": : :"memory");
  Model1_tcp_set_state(Model1_sk, Model1_TCP_ESTABLISHED);
#if CY_ABSTRACT7
  //because we call explicit function, they may be static function from other file
  Model1_sock_def_wakeup(Model1_sk);
#else
  Model1_sk->Model1_sk_state_change(Model1_sk);
#endif

  /* Note, that this wakeup is only for marginal crossed SYN case.
		 * Passively open sockets are not waked up, because
		 * sk->sk_sleep == NULL and sk->sk_socket == NULL.
		 */
  if (Model1_sk->Model1_sk_socket)
   Model1_sk_wake_async(Model1_sk, Model1_SOCK_WAKE_IO, ((2 << 16)|2));

  Model1_tp->Model1_snd_una = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_ack_seq;
  Model1_tp->Model1_snd_wnd = (__builtin_constant_p((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_th->Model1_window))) ? ((Model1___u16)( (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_th->Model1_window)) & (Model1___u16)0x00ffU) << 8) | (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_th->Model1_window)) & (Model1___u16)0xff00U) >> 8))) : Model1___fswab16(( Model1___u16)(Model1___be16)(Model1_th->Model1_window))) << Model1_tp->Model1_rx_opt.Model1_snd_wscale;
  Model1_tcp_init_wl(Model1_tp, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq);

  if (Model1_tp->Model1_rx_opt.Model1_tstamp_ok)
   Model1_tp->Model1_advmss -= 12;

  if (Model1_req) {
   /* Re-arm the timer because data may have been sent out.
			 * This is similar to the regular data transmission case
			 * when new data has just been ack'ed.
			 *
			 * (TFO) - we could try to be more aggressive and
			 * retransmitting any data sooner based on when they
			 * are sent out.
			 */
   Model1_tcp_rearm_rto(Model1_sk);
  } else
   Model1_tcp_init_metrics(Model1_sk);

  Model1_tcp_update_pacing_rate(Model1_sk);

  /* Prevent spurious tcp_cwnd_restart() on first data packet */
  Model1_tp->Model1_lsndtime = ((__u32)(Model1_jiffies));

  Model1_tcp_initialize_rcv_mss(Model1_sk);
  Model1_tcp_fast_path_on(Model1_tp);
  break;

 case Model1_TCP_FIN_WAIT1: {
  struct Model1_dst_entry *Model1_dst;
  int Model1_tmo;

  /* If we enter the TCP_FIN_WAIT1 state and we are a
		 * Fast Open socket and this is the first acceptable
		 * ACK we have received, this would have acknowledged
		 * our SYNACK so stop the SYNACK timer.
		 */
  if (Model1_req) {
   /* Return RST if ack_seq is invalid.
			 * Note that RFC793 only says to generate a
			 * DUPACK for it but for TCP Fast Open it seems
			 * better to treat this case like TCP_SYN_RECV
			 * above.
			 */
   if (!Model1_acceptable)
    return 1;
   /* We no longer need the request sock. */
   Model1_reqsk_fastopen_remove(Model1_sk, Model1_req, false);
   Model1_tcp_rearm_rto(Model1_sk);
  }
  if (Model1_tp->Model1_snd_una != Model1_tp->Model1_write_seq)
   break;

  Model1_tcp_set_state(Model1_sk, Model1_TCP_FIN_WAIT2);
  Model1_sk->Model1_sk_shutdown |= 2;

  Model1_dst = Model1___sk_dst_get(Model1_sk);
  if (Model1_dst)
   Model1_dst_confirm(Model1_dst);

  if (!Model1_sock_flag(Model1_sk, Model1_SOCK_DEAD)) {
   /* Wake up lingering close() */
#if CY_ABSTRACT7
   Model1_sock_def_wakeup(Model1_sk);
#else
   Model1_sk->Model1_sk_state_change(Model1_sk);
#endif
   break;
  }

  if (Model1_tp->Model1_linger2 < 0 ||
      (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq != ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq &&
       Model1_before(Model1_tp->Model1_rcv_nxt, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq - Model1_th->Model1_fin))) {
   Model1_tcp_done(Model1_sk);
   (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPABORTONDATA] += 1);
   return 1;
  }

  Model1_tmo = Model1_tcp_fin_time(Model1_sk);
  if (Model1_tmo > (60*1000)) {
   Model1_inet_csk_reset_keepalive_timer(Model1_sk, Model1_tmo - (60*1000));
  } else if (Model1_th->Model1_fin || Model1_sock_owned_by_user(Model1_sk)) {
   /* Bad case. We could lose such FIN otherwise.
			 * It is not a big problem, but it looks confusing
			 * and not so rare event. We still can lose it now,
			 * if it spins in bh_lock_sock(), but it is really
			 * marginal case.
			 */
   Model1_inet_csk_reset_keepalive_timer(Model1_sk, Model1_tmo);
  } else {
   Model1_tcp_time_wait(Model1_sk, Model1_TCP_FIN_WAIT2, Model1_tmo);
   goto Model1_discard;
  }
  break;
 }

 case Model1_TCP_CLOSING:
  if (Model1_tp->Model1_snd_una == Model1_tp->Model1_write_seq) {
   Model1_tcp_time_wait(Model1_sk, Model1_TCP_TIME_WAIT, 0);
   goto Model1_discard;
  }
  break;

 case Model1_TCP_LAST_ACK:
  if (Model1_tp->Model1_snd_una == Model1_tp->Model1_write_seq) {
   Model1_tcp_update_metrics(Model1_sk);
   Model1_tcp_done(Model1_sk);
   goto Model1_discard;
  }
  break;
 }

 /* step 6: check the URG bit */
 Model1_tcp_urg(Model1_sk, Model1_skb, Model1_th);

 /* step 7: process the segment text */
 switch (Model1_sk->Model1___sk_common.Model1_skc_state) {
 case Model1_TCP_CLOSE_WAIT:
 case Model1_TCP_CLOSING:
 case Model1_TCP_LAST_ACK:
  if (!Model1_before(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq, Model1_tp->Model1_rcv_nxt))
   break;
 case Model1_TCP_FIN_WAIT1:
 case Model1_TCP_FIN_WAIT2:
  /* RFC 793 says to queue data in these states,
		 * RFC 1122 says we MUST send a reset.
		 * BSD 4.4 also does reset.
		 */
  if (Model1_sk->Model1_sk_shutdown & 1) {
   if (((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq != ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq &&
       Model1_before(Model1_tp->Model1_rcv_nxt, ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_end_seq - Model1_th->Model1_fin)) {
    (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPABORTONDATA] += 1);
    Model1_tcp_reset(Model1_sk);
    return 1;
   }
  }
  /* Fall through */
 case Model1_TCP_ESTABLISHED:
  Model1_tcp_data_queue(Model1_sk, Model1_skb);
  Model1_queued = 1;
  break;
 }

 /* tcp_data could move socket to TIME-WAIT */
 if (Model1_sk->Model1___sk_common.Model1_skc_state != Model1_TCP_CLOSE) {
  Model1_tcp_data_snd_check(Model1_sk);
  Model1_tcp_ack_snd_check(Model1_sk);
 }

 if (!Model1_queued) {
Model1_discard:
  Model1_tcp_drop(Model1_sk, Model1_skb);
 }
 return 0;
}
                                    ;

static inline __attribute__((no_instrument_function)) void Model1_pr_drop_req(struct Model1_request_sock *Model1_req, Model1___u16 Model1_port, int Model1_family)
{
 struct Model1_inet_request_sock *Model1_ireq = Model1_inet_rsk(Model1_req);

 if (Model1_family == 2)
  do { if (0) ({ do { if (0) Model1_printk("\001" "7" "TCP: " "drop open request from %pI4/%u\n", &Model1_ireq->Model1_req.Model1___req_common.Model1_skc_daddr, Model1_port); } while (0); 0; }); } while (0);






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
static void Model1_tcp_ecn_create_request(struct Model1_request_sock *Model1_req,
       const struct Model1_sk_buff *Model1_skb,
       const struct Model1_sock *Model1_listen_sk,
       const struct Model1_dst_entry *Model1_dst)
{
 const struct Model1_tcphdr *Model1_th = Model1_tcp_hdr(Model1_skb);
 const struct Model1_net *Model1_net = Model1_sock_net(Model1_listen_sk);
 bool Model1_th_ecn = Model1_th->Model1_ece && Model1_th->Model1_cwr;
 bool Model1_ect, Model1_ecn_ok;
 Model1_u32 Model1_ecn_ok_dst;

 if (!Model1_th_ecn)
  return;

 Model1_ect = !Model1_INET_ECN_is_not_ect(((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_ip_dsfield);
 Model1_ecn_ok_dst = Model1_dst_feature(Model1_dst, ((1 << 31) | (1 << 0)));
 Model1_ecn_ok = Model1_net->Model1_ipv4.Model1_sysctl_tcp_ecn || Model1_ecn_ok_dst;

 if ((!Model1_ect && Model1_ecn_ok) || Model1_tcp_ca_needs_ecn(Model1_listen_sk) ||
     (Model1_ecn_ok_dst & (1 << 31)))
  Model1_inet_rsk(Model1_req)->Model1_ecn_ok = 1;
}

static void Model1_tcp_openreq_init(struct Model1_request_sock *Model1_req,
        const struct Model1_tcp_options_received *Model1_rx_opt,
        struct Model1_sk_buff *Model1_skb, const struct Model1_sock *Model1_sk)
{
 struct Model1_inet_request_sock *Model1_ireq = Model1_inet_rsk(Model1_req);

 Model1_req->Model1___req_common.Model1_skc_rcv_wnd = 0; /* So that tcp_send_synack() knows! */
 Model1_req->Model1_cookie_ts = 0;
 Model1_tcp_rsk(Model1_req)->Model1_rcv_isn = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq;
 Model1_tcp_rsk(Model1_req)->Model1_rcv_nxt = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_seq + 1;
 Model1_skb_mstamp_get(&Model1_tcp_rsk(Model1_req)->Model1_snt_synack);
 Model1_tcp_rsk(Model1_req)->Model1_last_oow_ack_time = 0;
 Model1_req->Model1_mss = Model1_rx_opt->Model1_mss_clamp;
 Model1_req->Model1_ts_recent = Model1_rx_opt->Model1_saw_tstamp ? Model1_rx_opt->Model1_rcv_tsval : 0;
 Model1_ireq->Model1_tstamp_ok = Model1_rx_opt->Model1_tstamp_ok;
 Model1_ireq->Model1_sack_ok = Model1_rx_opt->Model1_sack_ok;
 Model1_ireq->Model1_snd_wscale = Model1_rx_opt->Model1_snd_wscale;
 Model1_ireq->Model1_wscale_ok = Model1_rx_opt->Model1_wscale_ok;
 Model1_ireq->Model1_acked = 0;
 Model1_ireq->Model1_ecn_ok = 0;
 Model1_ireq->Model1_req.Model1___req_common.Model1_skc_dport = Model1_tcp_hdr(Model1_skb)->Model1_source;
 Model1_ireq->Model1_req.Model1___req_common.Model1_skc_num = (__builtin_constant_p((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_dest))) ? ((Model1___u16)( (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_dest)) & (Model1___u16)0x00ffU) << 8) | (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_dest)) & (Model1___u16)0xff00U) >> 8))) : Model1___fswab16(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_dest)));
 Model1_ireq->Model1_ir_mark = Model1_inet_request_mark(Model1_sk, Model1_skb);
}

struct Model1_request_sock *Model1_inet_reqsk_alloc(const struct Model1_request_sock_ops *Model1_ops,
          struct Model1_sock *Model1_sk_listener,
          bool Model1_attach_listener)
{
 struct Model1_request_sock *Model1_req = Model1_reqsk_alloc(Model1_ops, Model1_sk_listener,
            Model1_attach_listener);

 if (Model1_req) {
  struct Model1_inet_request_sock *Model1_ireq = Model1_inet_rsk(Model1_req);

  do { } while (0);
  Model1_ireq->Model1_opt = ((void *)0);



  Model1_atomic64_set(&Model1_ireq->Model1_req.Model1___req_common.Model1_skc_cookie, 0);
  Model1_ireq->Model1_req.Model1___req_common.Model1_skc_state = Model1_TCP_NEW_SYN_RECV;
  Model1_write_pnet(&Model1_ireq->Model1_req.Model1___req_common.Model1_skc_net, Model1_sock_net(Model1_sk_listener));
  Model1_ireq->Model1_req.Model1___req_common.Model1_skc_family = Model1_sk_listener->Model1___sk_common.Model1_skc_family;
 }

 return Model1_req;
}
                               ;

/*
 * Return true if a syncookie should be sent
 */
static bool Model1_tcp_syn_flood_action(const struct Model1_sock *Model1_sk,
     const struct Model1_sk_buff *Model1_skb,
     const char *Model1_proto)
{
 struct Model1_request_sock_queue *Model1_queue = &Model1_inet_csk(Model1_sk)->Model1_icsk_accept_queue;
 const char *Model1_msg = "Dropping request";
 bool Model1_want_cookie = false;
 struct Model1_net *Model1_net = Model1_sock_net(Model1_sk);


 if (Model1_net->Model1_ipv4.Model1_sysctl_tcp_syncookies) {
  Model1_msg = "Sending cookies";
  Model1_want_cookie = true;
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPREQQFULLDOCOOKIES] += 1);
 } else

  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_TCPREQQFULLDROP] += 1);

 if (!Model1_queue->Model1_synflood_warned &&
     Model1_net->Model1_ipv4.Model1_sysctl_tcp_syncookies != 2 &&
     ({ __typeof__ (*((&Model1_queue->Model1_synflood_warned))) Model1___ret = ((1)); switch (sizeof(*((&Model1_queue->Model1_synflood_warned)))) { case 1: asm volatile ("" "xchg" "b %b0, %1\n" : "+q" (Model1___ret), "+m" (*((&Model1_queue->Model1_synflood_warned))) : : "memory", "cc"); break; case 2: asm volatile ("" "xchg" "w %w0, %1\n" : "+r" (Model1___ret), "+m" (*((&Model1_queue->Model1_synflood_warned))) : : "memory", "cc"); break; case 4: asm volatile ("" "xchg" "l %0, %1\n" : "+r" (Model1___ret), "+m" (*((&Model1_queue->Model1_synflood_warned))) : : "memory", "cc"); break; case 8: asm volatile ("" "xchg" "q %q0, %1\n" : "+r" (Model1___ret), "+m" (*((&Model1_queue->Model1_synflood_warned))) : : "memory", "cc"); break; default: Model1___xchg_wrong_size(); } Model1___ret; }) == 0)
  Model1_printk("\001" "6" "TCP: " "%s: Possible SYN flooding on port %d. %s.  Check SNMP counters.\n", Model1_proto, (__builtin_constant_p((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_dest))) ? ((Model1___u16)( (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_dest)) & (Model1___u16)0x00ffU) << 8) | (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_dest)) & (Model1___u16)0xff00U) >> 8))) : Model1___fswab16(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_dest))), Model1_msg);


 return Model1_want_cookie;
}

static void Model1_tcp_reqsk_record_syn(const struct Model1_sock *Model1_sk,
     struct Model1_request_sock *Model1_req,
     const struct Model1_sk_buff *Model1_skb)
{
 if (Model1_tcp_sk(Model1_sk)->Model1_save_syn) {
  Model1_u32 Model1_len = Model1_skb_network_header_len(Model1_skb) + Model1_tcp_hdrlen(Model1_skb);
  Model1_u32 *Model1_copy;

  Model1_copy = Model1_kmalloc(Model1_len + sizeof(Model1_u32), ((( Model1_gfp_t)0x20u)|(( Model1_gfp_t)0x80000u)|(( Model1_gfp_t)0x2000000u)));
  if (Model1_copy) {
   Model1_copy[0] = Model1_len;
   ({ Model1_size_t Model1___len = (Model1_len); void *Model1___ret; if (__builtin_constant_p(Model1_len) && Model1___len >= 64) Model1___ret = Model1___memcpy((&Model1_copy[1]), (Model1_skb_network_header(Model1_skb)), Model1___len); else Model1___ret = __builtin_memcpy((&Model1_copy[1]), (Model1_skb_network_header(Model1_skb)), Model1___len); Model1___ret; });
   Model1_req->Model1_saved_syn = Model1_copy;
  }
 }
}

int Model1_tcp_conn_request(struct Model1_request_sock_ops *Model1_rsk_ops,
       const struct Model1_tcp_request_sock_ops *Model1_af_ops,
       struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb)
{
 struct Model1_tcp_fastopen_cookie Model1_foc = { .Model1_len = -1 };
 __u32 Model1_isn = ((struct Model1_tcp_skb_cb *)&((Model1_skb)->Model1_cb[0]))->Model1_tcp_tw_isn;
 struct Model1_tcp_options_received Model1_tmp_opt;
 struct Model1_tcp_sock *Model1_tp = Model1_tcp_sk(Model1_sk);
 struct Model1_net *Model1_net = Model1_sock_net(Model1_sk);
 struct Model1_sock *Model1_fastopen_sk = ((void *)0);
 struct Model1_dst_entry *Model1_dst = ((void *)0);
 struct Model1_request_sock *Model1_req;
 bool Model1_want_cookie = false;
 struct Model1_flowi Model1_fl;

 /* TW buckets are converted to open requests without
	 * limitations, they conserve resources and peer is
	 * evidently real one.
	 */
 if ((Model1_net->Model1_ipv4.Model1_sysctl_tcp_syncookies == 2 ||
      Model1_inet_csk_reqsk_queue_is_full(Model1_sk)) && !Model1_isn) {
  Model1_want_cookie = Model1_tcp_syn_flood_action(Model1_sk, Model1_skb, Model1_rsk_ops->Model1_slab_name);
  if (!Model1_want_cookie)
   goto Model1_drop;
 }


 /* Accept backlog is full. If we have already queued enough
	 * of warm entries in syn queue, drop request. It is better than
	 * clogging syn queue with openreqs with exponentially increasing
	 * timeout.
	 */
 if (Model1_sk_acceptq_is_full(Model1_sk) && Model1_inet_csk_reqsk_queue_young(Model1_sk) > 1) {
  (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_LISTENOVERFLOWS] += 1);
  goto Model1_drop;
 }

 Model1_req = Model1_inet_reqsk_alloc(Model1_rsk_ops, Model1_sk, !Model1_want_cookie);
 if (!Model1_req)
  goto Model1_drop;

 Model1_tcp_rsk(Model1_req)->Model1_af_specific = Model1_af_ops;

 Model1_tcp_clear_options(&Model1_tmp_opt);
 Model1_tmp_opt.Model1_mss_clamp = Model1_af_ops->Model1_mss_clamp;
 Model1_tmp_opt.Model1_user_mss = Model1_tp->Model1_rx_opt.Model1_user_mss;
 Model1_tcp_parse_options(Model1_skb, &Model1_tmp_opt, 0, Model1_want_cookie ? ((void *)0) : &Model1_foc); //assume no header options (including fast open cookie option)

 if (Model1_want_cookie && !Model1_tmp_opt.Model1_saw_tstamp)
  Model1_tcp_clear_options(&Model1_tmp_opt);

 Model1_tmp_opt.Model1_tstamp_ok = Model1_tmp_opt.Model1_saw_tstamp;
 Model1_tcp_openreq_init(Model1_req, &Model1_tmp_opt, Model1_skb, Model1_sk);

 /* Note: tcp_v6_init_req() might override ir_iif for link locals */
 Model1_inet_rsk(Model1_req)->Model1_req.Model1___req_common.Model1_skc_bound_dev_if = Model1_inet_request_bound_dev_if(Model1_sk, Model1_skb);

#if CY_ABSTRACT7
 Model1_tcp_v4_init_req(Model1_req, Model1_sk, Model1_skb);
#else
 Model1_af_ops->Model1_init_req(Model1_req, Model1_sk, Model1_skb);
#endif

 if (Model1_security_inet_conn_request(Model1_sk, Model1_skb, Model1_req))
  goto Model1_drop_and_free;

 if (!Model1_want_cookie && !Model1_isn) {
  /* VJ's idea. We save last timestamp seen
		 * from the destination in peer table, when entering
		 * state TIME-WAIT, and check against it before
		 * accepting new connection request.
		 *
		 * If "isn" is not zero, this request hit alive
		 * timewait bucket, so that all the necessary checks
		 * are made in the function processing timewait state.
		 */
  if (Model1_tcp_death_row.Model1_sysctl_tw_recycle) {
   bool Model1_strict;

#if CY_ABSTRACT7
   Model1_dst = Model1_tcp_v4_route_req(Model1_sk, &Model1_fl, Model1_req, &Model1_strict);
#else
   Model1_dst = Model1_af_ops->Model1_route_req(Model1_sk, &Model1_fl, Model1_req, &Model1_strict);
#endif

   if (Model1_dst && Model1_strict &&
       !Model1_tcp_peer_is_proven(Model1_req, Model1_dst, true,
      Model1_tmp_opt.Model1_saw_tstamp)) {
    (Model1_cy_linux_mib.Model1_mibs[Model1_LINUX_MIB_PAWSPASSIVEREJECTED] += 1);
    goto Model1_drop_and_release;
   }
  }
  /* Kill the following clause, if you dislike this way. */
  else if (!Model1_net->Model1_ipv4.Model1_sysctl_tcp_syncookies &&
    (Model1_sysctl_max_syn_backlog - Model1_inet_csk_reqsk_queue_len(Model1_sk) <
     (Model1_sysctl_max_syn_backlog >> 2)) &&
    !Model1_tcp_peer_is_proven(Model1_req, Model1_dst, false,
          Model1_tmp_opt.Model1_saw_tstamp)) {
   /* Without syncookies last quarter of
			 * backlog is filled with destinations,
			 * proven to be alive.
			 * It means that we continue to communicate
			 * to destinations, already remembered
			 * to the moment of synflood.
			 */
   Model1_pr_drop_req(Model1_req, (__builtin_constant_p((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_source))) ? ((Model1___u16)( (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_source)) & (Model1___u16)0x00ffU) << 8) | (((Model1___u16)(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_source)) & (Model1___u16)0xff00U) >> 8))) : Model1___fswab16(( Model1___u16)(Model1___be16)(Model1_tcp_hdr(Model1_skb)->Model1_source))),
        Model1_rsk_ops->Model1_family);
   goto Model1_drop_and_release;
  }

#if CY_ABSTRACT7
  Model1_isn = Model1_tcp_v4_init_sequence(Model1_skb);
#else
  Model1_isn = Model1_af_ops->Model1_init_seq(Model1_skb);
#endif
 }
#if CY_ABSTRACT3
#else
 if (!Model1_dst) {
#if CY_ABSTRACT7
   Model1_dst = Model1_tcp_v4_route_req(Model1_sk, &Model1_fl, Model1_req, ((void *)0));
#else
  Model1_dst = Model1_af_ops->Model1_route_req(Model1_sk, &Model1_fl, Model1_req, ((void *)0));
#endif
  if (!Model1_dst)
   goto Model1_drop_and_free;
 }
#endif

#if !CY_ABSTRACT3
 Model1_tcp_ecn_create_request(Model1_req, Model1_skb, Model1_sk, Model1_dst);
#endif

 if (Model1_want_cookie) {
  Model1_isn = Model1_cookie_init_sequence(Model1_af_ops, Model1_sk, Model1_skb, &Model1_req->Model1_mss);
  Model1_req->Model1_cookie_ts = Model1_tmp_opt.Model1_tstamp_ok;
  if (!Model1_tmp_opt.Model1_tstamp_ok)
   Model1_inet_rsk(Model1_req)->Model1_ecn_ok = 0;
 }

 Model1_tcp_rsk(Model1_req)->Model1_snt_isn = Model1_isn;
 Model1_tcp_rsk(Model1_req)->Model1_txhash = Model1_net_tx_rndhash();
 Model1_tcp_openreq_init_rwin(Model1_req, Model1_sk, Model1_dst);
 if (!Model1_want_cookie) {
  Model1_tcp_reqsk_record_syn(Model1_sk, Model1_req, Model1_skb);
  Model1_fastopen_sk = Model1_tcp_try_fastopen(Model1_sk, Model1_skb, Model1_req, &Model1_foc, Model1_dst);
 }
 if (Model1_fastopen_sk) {
#if CY_ABSTRACT7
  Model1_tcp_v4_send_synack(Model1_fastopen_sk, Model1_dst, &Model1_fl, Model1_req,
#else
  Model1_af_ops->Model1_send_synack(Model1_fastopen_sk, Model1_dst, &Model1_fl, Model1_req,
#endif
        &Model1_foc, Model1_TCP_SYNACK_FASTOPEN);
  /* Add the child socket directly into the accept queue */
  Model1_inet_csk_reqsk_queue_add(Model1_sk, Model1_req, Model1_fastopen_sk);
#if CY_ABSTRACT7
  Model1_sock_def_readable(Model1_sk);
#else
  Model1_sk->Model1_sk_data_ready(Model1_sk);
#endif
  Model1_spin_unlock(&((Model1_fastopen_sk)->Model1_sk_lock.Model1_slock));
  Model1_sock_put(Model1_fastopen_sk);
 } else {
  Model1_tcp_rsk(Model1_req)->Model1_tfo_listener = false;
  if (!Model1_want_cookie)
   Model1_inet_csk_reqsk_queue_hash_add(Model1_sk, Model1_req, ((unsigned)(1*1000)));
#if CY_ABSTRACT7
  Model1_tcp_v4_send_synack(Model1_sk, Model1_dst, &Model1_fl, Model1_req, &Model1_foc,
#else
  Model1_af_ops->Model1_send_synack(Model1_sk, Model1_dst, &Model1_fl, Model1_req, &Model1_foc,
#endif
        !Model1_want_cookie ? Model1_TCP_SYNACK_NORMAL :
         Model1_TCP_SYNACK_COOKIE);
  if (Model1_want_cookie) {
   Model1_reqsk_free(Model1_req);
   return 0;
  }
 }
 Model1_reqsk_put(Model1_req);
 return 0;

Model1_drop_and_release:
 Model1_dst_release(Model1_dst);
Model1_drop_and_free:
 Model1_reqsk_free(Model1_req);
Model1_drop:
 Model1_tcp_listendrop(Model1_sk);
 return 0;
}
                               ;
