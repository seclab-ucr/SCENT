void Model1_Server_Initialize(){
#if CY_ABSTRACT1
    Model1_Server.Model1_inet_conn.Model1_icsk_inet.Model1_sk.Model1___sk_common.Model1_skc_prot = &Model1_tcp_prot;
    Model1_skb_queue_head_init(&Model1_Server.Model1_inet_conn.Model1_icsk_inet.Model1_sk.Model1_sk_receive_queue);
    Model1_skb_queue_head_init(&Model1_Server.Model1_out_of_order_queue);
#endif

//struct.Model1_sock:1120|Load:i32
	//tp->packets_out
	*((unsigned int *)((char *)&Model1_Server+1120)) = 201;
//struct.Model1_sock:1154|Load:i8
	*((unsigned char *)((char *)&Model1_Server+1154)) = 0;
//struct.Model1_sock:1160|Load:i8
	*((unsigned char *)((char *)&Model1_Server+1160)) = 0;
//struct.Model1_sock:1161|Load:i8
	*((unsigned char *)((char *)&Model1_Server+1161)) = 0;
//struct.Model1_sock:1162|Load:i8
	*((unsigned char *)((char *)&Model1_Server+1162)) = 0;
//struct.Model1_sock:1164|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1164)) = 0;
//struct.Model1_sock:1176|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1176)) = 0;
//struct.Model1_sock:1180|Load:i16
	*((unsigned short *)((char *)&Model1_Server+1180)) = 0;
//struct.Model1_sock:1182|Load:i16
	*((unsigned short *)((char *)&Model1_Server+1182)) = 536;
//struct.Model1_sock:1272|Load:i16
	*((unsigned short *)((char *)&Model1_Server+1272)) = 20;
//struct.Model1_sock:1276|Load:i32 //tcp_sk->pred_flags (abstracted)
	*((unsigned int *)((char *)&Model1_Server+1276)) = 18446744073709490256;
//struct.Model1_sock:1280|Load:i64
	*((unsigned long long *)((char *)&Model1_Server+1280)) = 0;
//struct.Model1_sock:1288|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1288)) = 3;
//struct.Model1_sock:128|Load:i32
	*((unsigned int *)((char *)&Model1_Server+128)) = 2;
//struct.Model1_sock:1292|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1292)) = 1;
//struct.Model1_sock:1296|Load:i32 //tcp_sk->rcv_nxt
	*((unsigned int *)((char *)&Model1_Server+1296)) = 18446744073332498434;
//struct.Model1_sock:12|Load:i16 // skc_dport (abstracted)
	*((unsigned short *)((char *)&Model1_Server+12)) = 18446744073709536450;
//struct.Model1_sock:1300|Load:i32 // Model1_copied_seq
	*((unsigned int *)((char *)&Model1_Server+1300)) = 18446744073332498434;
//struct.Model1_sock:1304|Load:i32 // Model1_rcv_wup
	*((unsigned int *)((char *)&Model1_Server+1304)) = 18446744073332498434;
//struct.Model1_sock:1308|Load:i32 // Model1_snd_nxt
	*((unsigned int *)((char *)&Model1_Server+1308)) = 18446744073308874434;
//struct.Model1_sock:1312|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1312)) = 0;
//struct.Model1_sock:1316|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1316)) = 0;
//struct.Model1_sock:1320|Load:i64
	*((unsigned long long *)((char *)&Model1_Server+1320)) = 0;
//struct.Model1_sock:1328|Load:i32 // tcp_sk->syncp->seq (abstracted)
	*((unsigned int *)((char *)&Model1_Server+1328)) = 18446744073308874434;
//struct.Model1_sock:132|Load:i32
	*((unsigned int *)((char *)&Model1_Server+132)) = 0;
//struct.Model1_sock:1340|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1340)) = 131158316;
//struct.Model1_sock:140|Load:i32
	*((unsigned int *)((char *)&Model1_Server+140)) = 0;
//struct.Model1_sock:1424|Load:i32 // snd_wl1
	*((unsigned int *)((char *)&Model1_Server+1424)) = 18446744073332498434;
//struct.Model1_sock:1428|Load:i32 // snd_wnd
	*((unsigned int *)((char *)&Model1_Server+1428)) = 65535;
//struct.Model1_sock:1432|Load:i32 // max_window
	*((unsigned int *)((char *)&Model1_Server+1432)) = 65535;
//struct.Model1_sock:1436|Load:i32 // mss_cache
	*((unsigned int *)((char *)&Model1_Server+1436)) = 1460;
//struct.Model1_sock:1440|Load:i32 //window_clamp
	*((unsigned int *)((char *)&Model1_Server+1440)) = 65535;
//struct.Model1_sock:1444|Load:i32 //rcv_ssthresh
	*((unsigned int *)((char *)&Model1_Server+1444)) = 29200;
//struct.Model1_sock:1464|Load:i16 //advmss
	*((unsigned short *)((char *)&Model1_Server+1464)) = 1460;
//struct.Model1_sock:1469|Load:i8
	*((unsigned char *)((char *)&Model1_Server+1469)) = 1;
//struct.Model1_sock:1476|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1476)) = 912;
//struct.Model1_sock:1480|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1480)) = 228;
//struct.Model1_sock:1484|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1484)) = 200000;
//struct.Model1_sock:1488|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1488)) = 200000;
//struct.Model1_sock:1492|Load:i32 //tp->rtt_seq
	*((unsigned int *)((char *)&Model1_Server+1492)) = 18446744073308874434;
//struct.Model1_sock:1496|struct.Model1_in6_addr:0|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1496)) = 114;
//struct.Model1_sock:1500|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1500)) = 131158316;
//struct.Model1_sock:1504|Load:i32 //rtt
	//*((unsigned int *)((char *)&Model1_Server+1504)) = 114;
//struct.Model1_sock:1504|Load:i64 //rtt+ts
	*((unsigned long long *)((char *)&Model1_Server+1504)) = 563320677818433650;
//struct.Model1_sock:1508|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1508)) = 131158316;
//struct.Model1_sock:1512|Load:i32
	//*((unsigned int *)((char *)&Model1_Server+1512)) = 114;
//struct.Model1_sock:1512|Load:i64 //rtt+ts
	*((unsigned long long *)((char *)&Model1_Server+1512)) = 563320677818433650;
//struct.Model1_sock:1520|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1520)) = 0;
//struct.Model1_sock:1536|Load:i16
	*((unsigned short *)((char *)&Model1_Server+1536)) = 0;
//struct.Model1_sock:1538|Load:i8
	*((unsigned char *)((char *)&Model1_Server+1538)) = 0;
//struct.Model1_sock:1540|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1540)) = 3;
//struct.Model1_sock:1552|Load:i64
	*((unsigned long long *)((char *)&Model1_Server+1552)) = 0;
//struct.Model1_sock:1560|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1560)) = 0;
//struct.Model1_sock:1564|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1564)) = 0;
//struct.Model1_sock:1568|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1568)) = 0;
//struct.Model1_sock:1572|Load:i16
	*((unsigned short *)((char *)&Model1_Server+1572)) = 0;
//struct.Model1_sock:1574|Load:i8
	*((unsigned char *)((char *)&Model1_Server+1574)) = 0;
//struct.Model1_sock:1576|Load:i16
	*((unsigned short *)((char *)&Model1_Server+1576)) = 0;
//struct.Model1_sock:1578|Load:i16
	*((unsigned short *)((char *)&Model1_Server+1578)) = 1460;
//struct.Model1_sock:1584|Load:i32 //snd_ssthresh
	*((unsigned int *)((char *)&Model1_Server+1584)) = 2147483647;
//struct.Model1_sock:1588|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1588)) = 10;
//struct.Model1_sock:1624|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1624)) = 29200;
//struct.Model1_sock:1628|Load:i32 // write_seq
	*((unsigned int *)((char *)&Model1_Server+1628)) = 18446744073308874434;
//struct.Model1_sock:1672|union.anon.92:16|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1688)) = 0;
//struct.Model1_sock:1696|struct.Model1_dst_entry*:4|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1700)) = 0;
//struct.Model1_sock:16|Load:i16
	*((unsigned short *)((char *)&Model1_Server+16)) = 2;
//struct.Model1_sock:1704|Load:i64
	*((unsigned long long *)((char *)&Model1_Server+1704)) = 0;
//struct.Model1_sock:1704|struct.anon.71:-8|Load:i64
	*((unsigned long long *)((char *)&Model1_Server+1696)) = 0;
//struct.Model1_sock:1708|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1708)) = 0;
//struct.Model1_sock:1712|struct.anon.71:0|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1712)) = 0;
//struct.Model1_sock:1712|struct.anon.71:4|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1716)) = 0;
//struct.Model1_sock:1804|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1804)) = 0;
//struct.Model1_sock:1808|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1808)) = 0;
//struct.Model1_sock:1820|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1820)) = 0;
//struct.Model1_sock:184|Load:i32
	*((unsigned int *)((char *)&Model1_Server+184)) = 0;
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|Load:i32
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:124|Load:i32
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:12|Load:i16
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:12|union.anon.0:2|Load:i16
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:132|Load:i32
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:144|Load:i16
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:146|Load:i8
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:147|Load:i8
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:148|Load:i32
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:20|Load:i32
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:240|Load:i64
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:256|Load:i16
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:260|Load:i32
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:264|Load:struct.Model1_ip_options_rcu*|struct.Model1_ip_options_rcu:24|Load:i8
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:288|Load:i64
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:288|struct.Model1_hlist_node**:4|Load:i32
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:300|Load:i32
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:304|Load:i32
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:308|Load:i32
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:316|Load:i32
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:4|Load:i32
//struct.Model1_sock:1888|Load:struct.Model1_request_sock*|struct.Model1_request_sock:88|Load:i64
//struct.Model1_sock:18|Load:i8
	*((unsigned char *)((char *)&Model1_Server+18)) = 1;
//struct.Model1_sock:192|Load:i32
	*((unsigned int *)((char *)&Model1_Server+192)) = 0;
//struct.Model1_sock:20|Load:i32
	*((unsigned int *)((char *)&Model1_Server+20)) = 0;
//struct.Model1_sock:216|Load:i32
	*((unsigned int *)((char *)&Model1_Server+216)) = 0;
//struct.Model1_sock:220|Load:i32 //Model1_sk_txhash (abstracted) [pointer]
	*((unsigned int *)((char *)&Model1_Server+220)) = 18446744073706231465;
//struct.Model1_sock:232|Load:i32
	*((unsigned int *)((char *)&Model1_Server+232)) = 0;
//struct.Model1_sock:236|Load:i32 //sk_rcvbuf
	*((unsigned int *)((char *)&Model1_Server+236)) = 369280;
//struct.Model1_sock:248|Load:i64 //sk_wq (socket_wait queue??) [pointer]
	*((unsigned long long *)((char *)&Model1_Server+248)) = 18446612140028096576;
//struct.Model1_sock:280|Load:i64
#if !CY_ABSTRACT1 //dst related
	*((unsigned long long *)((char *)&Model1_Server+280)) = 18446612140003828992;
//struct.Model1_sock:280|Load:i64|struct.Model1_dst_entry:40|Load:i64
	*((unsigned long long *)((char *)*((long long *)((char *)&Model1_Server+280))+40)) = 18446744071590237057;
//struct.Model1_sock:280|Load:i64|struct.Model1_dst_entry:40|Load:i64|and:-4|Load:i32
	*((unsigned int *)((char *)((*((long long *)((char *)*((long long *)((char *)&Model1_Server+280))+40)))&(-4))+0)) = 0;
//struct.Model1_sock:280|Load:i64|struct.Model1_dst_entry:40|Load:i64|and:-4|i32:48|Load:i32
	*((unsigned int *)((char *)((*((long long *)((char *)*((long long *)((char *)&Model1_Server+280))+40)))&(-4))+48)) = 0;
//struct.Model1_sock:280|Load:i64|struct.Model1_dst_entry:40|Load:i64|and:-4|i32:56|Load:i32
	*((unsigned int *)((char *)((*((long long *)((char *)*((long long *)((char *)&Model1_Server+280))+40)))&(-4))+56)) = 0;
#endif
//struct.Model1_sock:288|Load:i32
	*((unsigned int *)((char *)&Model1_Server+288)) = 1;
//struct.Model1_sock:296|Load:i32
	*((unsigned int *)((char *)&Model1_Server+296)) = 87040;
//struct.Model1_sock:328|Load:i32
	*((unsigned int *)((char *)&Model1_Server+328)) = 67072;
//struct.Model1_sock:332|Load:i32
	*((unsigned int *)((char *)&Model1_Server+332)) = 0;
//struct.Model1_sock:344|Load:i32 // sk_max_pacing_rate (Maximum pacing rate) [u32]
	*((unsigned int *)((char *)&Model1_Server+344)) = 18446744073709551615;
//struct.Model1_sock:368|Load:i32
	*((unsigned int *)((char *)&Model1_Server+368)) = 1;
//struct.Model1_sock:40|Load:i64
#if !CY_ABSTRACT1
    //skc_prot
	*((unsigned long long *)((char *)&Model1_Server+40)) = 18446744071594451968;
//struct.Model1_sock:40|Load:struct.Model1_proto*|struct.Model1_proto:216|Load:union.anon*|union.anon:0|Load:i64
	*((unsigned long long *)((char *)*((long long *)((char *)*((long long *)((char *)&Model1_Server+40))+216))+0)) = 0;
//struct.Model1_sock:40|Load:struct.Model1_proto*|struct.Model1_proto:224|Load:struct.Model1_percpu_counter*|struct.Model1_percpu_counter:8|Load:i64
	*((unsigned long long *)((char *)*((long long *)((char *)*((long long *)((char *)&Model1_Server+40))+224))+8)) = 0;
//struct.Model1_sock:40|Load:struct.Model1_proto*|struct.Model1_proto:232|Load:i32*|Load:i32
	*((unsigned int *)((char *)*((long long *)((char *)*((long long *)((char *)&Model1_Server+40))+232))+0)) = 0;
//struct.Model1_sock:40|Load:struct.Model1_proto*|struct.Model1_proto:240|Load:i64*|Load:i64
	*((unsigned long long *)((char *)*((long long *)((char *)*((long long *)((char *)&Model1_Server+40))+240))+0)) = 81237;
//struct.Model1_sock:40|Load:struct.Model1_proto*|struct.Model1_proto:240|Load:i64*|i64:16|Load:i64
	*((unsigned long long *)((char *)*((long long *)((char *)*((long long *)((char *)&Model1_Server+40))+240))+16)) = 162474;
//struct.Model1_sock:40|Load:struct.Model1_proto*|struct.Model1_proto:240|Load:i64*|i64:8|Load:i64
	*((unsigned long long *)((char *)*((long long *)((char *)*((long long *)((char *)&Model1_Server+40))+240))+8)) = 108316;
//struct.Model1_sock:40|Load:struct.Model1_proto*|struct.Model1_proto:256|Load:i32*|Load:i32
	*((unsigned int *)((char *)*((long long *)((char *)*((long long *)((char *)&Model1_Server+40))+256))+0)) = 4096;
#endif
//struct.Model1_sock:440|Load:i32
	*((unsigned int *)((char *)&Model1_Server+440)) = 0;
//struct.Model1_sock:444|Load:i32
	*((unsigned int *)((char *)&Model1_Server+444)) = 10;
//struct.Model1_sock:452|Load:i32
	*((unsigned int *)((char *)&Model1_Server+452)) = 0;
//struct.Model1_sock:48|Load:i64
#if CY_ABSTRACT1
    *((unsigned long long *)((char *)&Model1_Server+48)) = &Model1_NET;
#else
	*((unsigned long long *)((char *)&Model1_Server+48)) = 18446744071594422976;
#endif
//struct.Model1_sock:48|Load:struct.Model1_net*|struct.Model1_net:1000|Load:i32
	*((unsigned int *)((char *)*((long long *)((char *)&Model1_Server+48))+1000)) = 0; //1;
//struct.Model1_sock:48|Load:struct.Model1_net*|struct.Model1_net:1020|Load:i32
	*((unsigned int *)((char *)*((long long *)((char *)&Model1_Server+48))+1020)) = 60000;
//struct.Model1_sock:48|Load:struct.Model1_net*|struct.Model1_net:960|Load:i32
	*((unsigned int *)((char *)*((long long *)((char *)&Model1_Server+48))+960)) = 0;
//struct.Model1_sock:570|Load:i8
	*((unsigned char *)((char *)&Model1_Server+570)) = 0;
//struct.Model1_sock:728|Load:i16
#if CY_ABSTRACT1
	//this part is not sure //inet_sock->inet_saddr
    *((unsigned short *)((char *)&Model1_Server+728)) = 47138;
#else
	*((unsigned short *)((char *)&Model1_Server+728)) = 18446744073709533218;
#endif
//struct.Model1_sock:744|Load:i32 //rx_dst_ifindex meaning?
	*((unsigned int *)((char *)&Model1_Server+744)) = 2;
//struct.Model1_sock:752|Load:i16
	*((unsigned short *)((char *)&Model1_Server+752)) = 82;
//struct.Model1_sock:888|struct.Model1_sk_buff*:12|Load:i32
	*((unsigned int *)((char *)&Model1_Server+900)) = 0;
//struct.Model1_sock:888|struct.Model1_sk_buff*:16|Load:i32
	*((unsigned int *)((char *)&Model1_Server+904)) = 0;
//struct.Model1_sock:892|Load:i8
	*((unsigned char *)((char *)&Model1_Server+892)) = 0;
//struct.Model1_sock:896|Load:i32
	*((unsigned int *)((char *)&Model1_Server+896)) = 0;
//struct.Model1_sock:928|Load:struct.Model1_request_sock*|struct.Model1_request_sock:128|Load:i32
//struct.Model1_sock:928|Load:struct.Model1_request_sock*|struct.Model1_request_sock:136|Load:i64
//struct.Model1_sock:928|Load:struct.Model1_request_sock*|struct.Model1_request_sock:168|Load:i64
//struct.Model1_sock:948|Load:i32
	*((unsigned int *)((char *)&Model1_Server+948)) = 0;
//struct.Model1_sock:952|Load:i32
	*((unsigned int *)((char *)&Model1_Server+952)) = 0;
//struct.Model1_sock:96|Load:i64
	*((unsigned long long *)((char *)&Model1_Server+96)) = 768;
//struct.Model1_tcp_sock:1516|Load:i32
	*((unsigned int *)((char *)&Model1_Server+1516)) = 131158316;
#if !CY_ABSTRACT1 //tcp_sock offset chain and sock offset chain may lead to same variable. But need to avoid dupilcation, otherwise practical varaibles are not modified, even though we have changed initialization.

//struct.Model1_tcp_sock:1308|Load:i32 //snd_nxt
	*((unsigned int *)((char *)&Model1_Server+1308)) = 18446744073308874434;
#endif
}
