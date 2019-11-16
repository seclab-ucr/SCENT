#ifndef Model0_TCP_IPV4_H
#define Model0_TCP_IPV4_H
// declaration
int Model0_tcp_rtx_synack(const struct Model0_sock *Model0_sk, struct Model0_request_sock *Model0_req);
static void Model0_tcp_v4_send_reset(const struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb);

static void Model0_tcp_v4_init_req(struct Model0_request_sock *Model0_req,
       const struct Model0_sock *Model0_sk_listener,
       struct Model0_sk_buff *Model0_skb);

static struct Model0_dst_entry *Model0_tcp_v4_route_req(const struct Model0_sock *Model0_sk,
       struct Model0_flowi *Model0_fl,
       const struct Model0_request_sock *Model0_req,
       bool *Model0_strict);

static __u32 Model0_tcp_v4_init_sequence(const struct Model0_sk_buff *Model0_skb);

static int Model0_tcp_v4_send_synack(const struct Model0_sock *Model0_sk, struct Model0_dst_entry *Model0_dst,
         struct Model0_flowi *Model0_fl,
         struct Model0_request_sock *Model0_req,
         struct Model0_tcp_fastopen_cookie *Model0_foc,
         enum Model0_tcp_synack_type Model0_synack_type);

enum Model0_tcp_tw_status Model0_tcp_timewait_state_process(struct Model0_inet_timewait_sock *Model0_tw,
           struct Model0_sk_buff *Model0_skb,
           const struct Model0_tcphdr *Model0_th);

void Model0_inet_twsk_deschedule_put(struct Model0_inet_timewait_sock *Model0_tw);

static void Model0_tcp_v4_reqsk_send_ack(const struct Model0_sock *Model0_sk, struct Model0_sk_buff *Model0_skb,
      struct Model0_request_sock *Model0_req);
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
           const int Model0_dif);
void Model0_tcp_v4_reqsk_destructor(struct Model0_request_sock *Model0_req);
#endif
