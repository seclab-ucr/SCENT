void Model1_Listen_Server_Initialize(){
#if CY_ABSTRACT1
    Model1_Server_L.Model1_inet_conn.Model1_icsk_inet.Model1_sk.Model1___sk_common.Model1_skc_prot = &Model1_tcp_prot;
    Model1_skb_queue_head_init(&Model1_Server_L.Model1_inet_conn.Model1_icsk_inet.Model1_sk.Model1_sk_receive_queue);
    Model1_skb_queue_head_init(&Model1_Server_L.Model1_out_of_order_queue);
#endif

//struct.Model1_sock:1120|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1120)) = 1000;
//struct.Model1_sock:1154|Load:i8
	*((unsigned char *)((char *)&Model1_Server_L+1154)) = 0;
//struct.Model1_sock:1160|Load:i8
	*((unsigned char *)((char *)&Model1_Server_L+1160)) = 0;
//struct.Model1_sock:1161|Load:i8
	*((unsigned char *)((char *)&Model1_Server_L+1161)) = 0;
//struct.Model1_sock:1162|Load:i8
	*((unsigned char *)((char *)&Model1_Server_L+1162)) = 0;
//struct.Model1_sock:1164|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1164)) = 0;
//struct.Model1_sock:1176|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1176)) = 0;
//struct.Model1_sock:1180|Load:i16
	*((unsigned short *)((char *)&Model1_Server_L+1180)) = 0;
//struct.Model1_sock:1182|Load:i16
	*((unsigned short *)((char *)&Model1_Server_L+1182)) = 0;
//struct.Model1_sock:1272|Load:i16
	*((unsigned short *)((char *)&Model1_Server_L+1272)) = 0;
//struct.Model1_sock:1276|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1276)) = 0;
//struct.Model1_sock:1280|Load:i64
	*((unsigned long long *)((char *)&Model1_Server_L+1280)) = 0;
//struct.Model1_sock:1288|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1288)) = 0;
//struct.Model1_sock:128|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+128)) = 1;
//struct.Model1_sock:1292|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1292)) = 0;
//struct.Model1_sock:1296|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1296)) = 0;
//struct.Model1_sock:12|Load:i16
	*((unsigned short *)((char *)&Model1_Server_L+12)) = 0;
//struct.Model1_sock:1300|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1300)) = 0;
//struct.Model1_sock:1304|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1304)) = 0;
//struct.Model1_sock:1308|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1308)) = 0;
//struct.Model1_sock:1312|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1312)) = 0;
//struct.Model1_sock:1316|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1316)) = 0;
//struct.Model1_sock:1320|Load:i64
	*((unsigned long long *)((char *)&Model1_Server_L+1320)) = 0;
//struct.Model1_sock:1328|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1328)) = 0;
//struct.Model1_sock:132|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+132)) = 0;
//struct.Model1_sock:1340|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1340)) = 0;
//struct.Model1_sock:140|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+140)) = 0;
//struct.Model1_sock:1424|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1424)) = 0;
//struct.Model1_sock:1428|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1428)) = 0;
//struct.Model1_sock:1432|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1432)) = 0;
//struct.Model1_sock:1436|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1436)) = 536;
//struct.Model1_sock:1440|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1440)) = 0;
//struct.Model1_sock:1444|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1444)) = 0;
//struct.Model1_sock:1464|Load:i16
	*((unsigned short *)((char *)&Model1_Server_L+1464)) = 0;
//struct.Model1_sock:1469|Load:i8
	*((unsigned char *)((char *)&Model1_Server_L+1469)) = 1;
//struct.Model1_sock:1476|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1476)) = 0;
//struct.Model1_sock:1480|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1480)) = 1000000;
//struct.Model1_sock:1484|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1484)) = 0;
//struct.Model1_sock:1488|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1488)) = 0;
//struct.Model1_sock:1492|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1492)) = 0;
#if CY_ABSTRACT1
    //rtt, won't be visited inside abstracted model
    *((unsigned int *)((char *)&Model1_Server_L+1496)) = 4294967295;
#else
//struct.Model1_sock:1496|struct.Model1_in6_addr:0|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1496)) = 18446744073709551615;
#endif
//struct.Model1_sock:1500|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1500)) = 0;
//struct.Model1_sock:1504|Load:i64
	*((unsigned long long *)((char *)&Model1_Server_L+1504)) = 0;
//struct.Model1_sock:1508|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1508)) = 0;
//struct.Model1_sock:1512|Load:i64
	*((unsigned long long *)((char *)&Model1_Server_L+1512)) = 0;
//struct.Model1_sock:1520|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1520)) = 0;
//struct.Model1_sock:1536|Load:i16
	*((unsigned short *)((char *)&Model1_Server_L+1536)) = 0;
//struct.Model1_sock:1538|Load:i8
	*((unsigned char *)((char *)&Model1_Server_L+1538)) = 0;
//struct.Model1_sock:1540|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1540)) = 3;
//struct.Model1_sock:1552|Load:i64
	*((unsigned long long *)((char *)&Model1_Server_L+1552)) = 0;
//struct.Model1_sock:1560|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1560)) = 0;
//struct.Model1_sock:1564|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1564)) = 0;
//struct.Model1_sock:1568|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1568)) = 0;
//struct.Model1_sock:1572|Load:i16
	*((unsigned short *)((char *)&Model1_Server_L+1572)) = 0;
//struct.Model1_sock:1574|Load:i8
	*((unsigned char *)((char *)&Model1_Server_L+1574)) = 0;
//struct.Model1_sock:1576|Load:i16
	*((unsigned short *)((char *)&Model1_Server_L+1576)) = 0;
//struct.Model1_sock:1578|Load:i16
	*((unsigned short *)((char *)&Model1_Server_L+1578)) = 0;
//struct.Model1_sock:1584|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1584)) = 2147483647;
//struct.Model1_sock:1588|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1588)) = 10;
//struct.Model1_sock:1624|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1624)) = 0;
//struct.Model1_sock:1628|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1628)) = 0;
//struct.Model1_sock:1672|union.anon.92:16|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1688)) = 0;
//struct.Model1_sock:16|Load:i16
	*((unsigned short *)((char *)&Model1_Server_L+16)) = 2;
//struct.Model1_sock:1704|Load:i64
	*((unsigned long long *)((char *)&Model1_Server_L+1704)) = 0;
//struct.Model1_sock:1704|struct.anon.71:-8|Load:i64
	*((unsigned long long *)((char *)&Model1_Server_L+1696)) = 0;
//struct.Model1_sock:1708|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1708)) = 0;
//struct.Model1_sock:1712|struct.anon.71:0|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1712)) = 0;
//struct.Model1_sock:1712|struct.anon.71:4|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1716)) = 0;
//struct.Model1_sock:1804|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1804)) = 0;
//struct.Model1_sock:1808|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1808)) = 0;
//struct.Model1_sock:1820|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1820)) = 0;
//struct.Model1_sock:184|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+184)) = 0;
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
	*((unsigned char *)((char *)&Model1_Server_L+18)) = 10;
//struct.Model1_sock:192|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+192)) = 0;
//struct.Model1_sock:20|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+20)) = 0;
//struct.Model1_sock:216|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+216)) = 0;
//struct.Model1_sock:220|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+220)) = 0;
//struct.Model1_sock:232|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+232)) = 0;
//struct.Model1_sock:236|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+236)) = 87380;
//struct.Model1_sock:248|Load:i64
	*((unsigned long long *)((char *)&Model1_Server_L+248)) = 18446612140010083520;
//struct.Model1_sock:280|Load:i64
	*((unsigned long long *)((char *)&Model1_Server_L+280)) = 0;
//struct.Model1_sock:280|Load:i64|struct.Model1_dst_entry:40|Load:i64
//struct.Model1_sock:280|Load:i64|struct.Model1_dst_entry:40|Load:i64|and:-4|Load:i32
//struct.Model1_sock:280|Load:i64|struct.Model1_dst_entry:40|Load:i64|and:-4|i32:48|Load:i32
//struct.Model1_sock:280|Load:i64|struct.Model1_dst_entry:40|Load:i64|and:-4|i32:56|Load:i32
//struct.Model1_sock:288|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+288)) = 1;
//struct.Model1_sock:296|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+296)) = 16384;
//struct.Model1_sock:328|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+328)) = 67200;
//struct.Model1_sock:332|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+332)) = 0;
//struct.Model1_sock:344|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+344)) = 18446744073709551615;
//struct.Model1_sock:368|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+368)) = 0;
//struct.Model1_sock:40|Load:i64
#if !CY_ABSTRACT1
    //skc_prot
    *((unsigned long long *)((char *)&Model1_Server_L+40)) = 18446744071594451968;
#endif
#if !CY_ABSTRACT1
/** We don't want to re-initialize same value, since one changed initialization will be over-write by another initialization. Especially we cannot symbolize the following values since klee cannot resolve address well **/
//struct.Model1_sock:40|Load:struct.Model1_proto*|struct.Model1_proto:216|Load:union.anon*|union.anon:0|Load:i64
	*((unsigned long long *)((char *)*((long long *)((char *)*((long long *)((char *)&Model1_Server_L+40))+216))+0)) = 0;
//struct.Model1_sock:40|Load:struct.Model1_proto*|struct.Model1_proto:224|Load:struct.Model1_percpu_counter*|struct.Model1_percpu_counter:8|Load:i64
	*((unsigned long long *)((char *)*((long long *)((char *)*((long long *)((char *)&Model1_Server_L+40))+224))+8)) = 0;
//struct.Model1_sock:40|Load:struct.Model1_proto*|struct.Model1_proto:232|Load:i32*|Load:i32
	*((unsigned int *)((char *)*((long long *)((char *)*((long long *)((char *)&Model1_Server_L+40))+232))+0)) = 0;
//struct.Model1_sock:40|Load:struct.Model1_proto*|struct.Model1_proto:240|Load:i64*|Load:i64
	*((unsigned long long *)((char *)*((long long *)((char *)*((long long *)((char *)&Model1_Server_L+40))+240))+0)) = 81237;
//struct.Model1_sock:40|Load:struct.Model1_proto*|struct.Model1_proto:240|Load:i64*|i64:16|Load:i64
	*((unsigned long long *)((char *)*((long long *)((char *)*((long long *)((char *)&Model1_Server_L+40))+240))+16)) = 162474;
//struct.Model1_sock:40|Load:struct.Model1_proto*|struct.Model1_proto:240|Load:i64*|i64:8|Load:i64
	*((unsigned long long *)((char *)*((long long *)((char *)*((long long *)((char *)&Model1_Server_L+40))+240))+8)) = 108316;
//struct.Model1_sock:40|Load:struct.Model1_proto*|struct.Model1_proto:256|Load:i32*|Load:i32
	*((unsigned int *)((char *)*((long long *)((char *)*((long long *)((char *)&Model1_Server_L+40))+256))+0)) = 4096; //struct.Model1_sock:440|Load:i32
#endif
	*((unsigned int *)((char *)&Model1_Server_L+440)) = 0;
//struct.Model1_sock:444|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+444)) = 10;
//struct.Model1_sock:452|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+452)) = 0;
//struct.Model1_sock:48|Load:i64
#if CY_ABSTRACT1
    *((unsigned long long *)((char *)&Model1_Server_L+48)) = &Model1_NET;
#else
	*((unsigned long long *)((char *)&Model1_Server_L+48)) = 18446744071594422976;
#endif
//struct.Model1_sock:48|Load:struct.Model1_net*|struct.Model1_net:1000|Load:i32
	*((unsigned int *)((char *)*((long long *)((char *)&Model1_Server_L+48))+1000)) = 0;//1; //assume syn_cookie is disabled
//struct.Model1_sock:48|Load:struct.Model1_net*|struct.Model1_net:1020|Load:i32
	*((unsigned int *)((char *)*((long long *)((char *)&Model1_Server_L+48))+1020)) = 60000;
//struct.Model1_sock:48|Load:struct.Model1_net*|struct.Model1_net:960|Load:i32
	*((unsigned int *)((char *)*((long long *)((char *)&Model1_Server_L+48))+960)) = 0;
//struct.Model1_sock:570|Load:i8
	*((unsigned char *)((char *)&Model1_Server_L+570)) = 0;
//struct.Model1_sock:728|Load:i16
#if CY_ABSTRACT1
    //this part is not sure
    *((unsigned short *)((char *)&Model1_Server_L+728)) = 47138;
#else
	*((unsigned short *)((char *)&Model1_Server_L+728)) = 18446744073709533218;
#endif
//struct.Model1_sock:744|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+744)) = 0;
//struct.Model1_sock:752|Load:i16
	*((unsigned short *)((char *)&Model1_Server_L+752)) = 82;
//struct.Model1_sock:888|struct.Model1_sk_buff*:12|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+900)) = 0;
//struct.Model1_sock:888|struct.Model1_sk_buff*:16|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+904)) = 0;
//struct.Model1_sock:892|Load:i8
	*((unsigned char *)((char *)&Model1_Server_L+892)) = 0;
//struct.Model1_sock:896|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+896)) = 0;
//struct.Model1_sock:928|Load:struct.Model1_request_sock*|struct.Model1_request_sock:128|Load:i32
//struct.Model1_sock:928|Load:struct.Model1_request_sock*|struct.Model1_request_sock:136|Load:i64
//struct.Model1_sock:928|Load:struct.Model1_request_sock*|struct.Model1_request_sock:168|Load:i64
//struct.Model1_sock:948|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+948)) = 0;
//struct.Model1_sock:952|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+952)) = 0;
//struct.Model1_sock:96|Load:i64
	*((unsigned long long *)((char *)&Model1_Server_L+96)) = 16777984;
//struct.Model1_tcp_sock:1308|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1308)) = 0;
//struct.Model1_tcp_sock:1516|Load:i32
	*((unsigned int *)((char *)&Model1_Server_L+1516)) = 0;


    printf("sk_max_ack_backlog: %d\n", ((struct Model1_sock *)&Model1_Server_L)->Model1_sk_max_ack_backlog);
    //((struct Model1_sock *)&Model1_Server_L)->Model1_sk_max_ack_backlog = 3;
}
