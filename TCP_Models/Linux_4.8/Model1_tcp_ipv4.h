#ifndef Model1_TCP_IPV4_H
#define Model1_TCP_IPV4_H
// declaration
int Model1_tcp_rtx_synack(const struct Model1_sock *Model1_sk, struct Model1_request_sock *Model1_req);
static void Model1_tcp_v4_send_reset(const struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb);

static void Model1_tcp_v4_init_req(struct Model1_request_sock *Model1_req,
       const struct Model1_sock *Model1_sk_listener,
       struct Model1_sk_buff *Model1_skb);

static struct Model1_dst_entry *Model1_tcp_v4_route_req(const struct Model1_sock *Model1_sk,
       struct Model1_flowi *Model1_fl,
       const struct Model1_request_sock *Model1_req,
       bool *Model1_strict);

static __u32 Model1_tcp_v4_init_sequence(const struct Model1_sk_buff *Model1_skb);

static int Model1_tcp_v4_send_synack(const struct Model1_sock *Model1_sk, struct Model1_dst_entry *Model1_dst,
         struct Model1_flowi *Model1_fl,
         struct Model1_request_sock *Model1_req,
         struct Model1_tcp_fastopen_cookie *Model1_foc,
         enum Model1_tcp_synack_type Model1_synack_type);

enum Model1_tcp_tw_status Model1_tcp_timewait_state_process(struct Model1_inet_timewait_sock *Model1_tw,
           struct Model1_sk_buff *Model1_skb,
           const struct Model1_tcphdr *Model1_th);

void Model1_inet_twsk_deschedule_put(struct Model1_inet_timewait_sock *Model1_tw);

static void Model1_tcp_v4_reqsk_send_ack(const struct Model1_sock *Model1_sk, struct Model1_sk_buff *Model1_skb,
      struct Model1_request_sock *Model1_req);
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
           const int Model1_dif);
void Model1_tcp_v4_reqsk_destructor(struct Model1_request_sock *Model1_req);
#endif
