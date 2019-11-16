void Model0_SKB_Initialize(int pkt_depth){
    struct Model0_sk_buff *Model0_skb = &Model0_Skb_In[pkt_depth];
    char *Model0_data = Model0_Buff_In[pkt_depth];
    struct Model0_sock *Model0_sk = (struct Model0_sock *) &Model0_Server;
    struct Model0_inet_sock *Model0_inet = Model0_inet_sk(Model0_sk);


//struct.Model0_sk_buff:186|Load:i16
    //skb->transport_header
	*((unsigned short *)((char *)Model0_skb+186)) = 98;
//struct.Model0_sk_buff:188|Load:i16
    //skb->network_header
	*((unsigned short *)((char *)Model0_skb+188)) = 78;
//struct.Model0_sk_buff:192|Load:i32
#if CY_ABSTRACT1
    //skb->tail
	*((unsigned int *)((char *)Model0_skb+192)) = 122-4; //make header to have 20 bytes
#else
	*((unsigned int *)((char *)Model0_skb+192)) = 122;
#endif
//struct.Model0_sk_buff:196|Load:i32
    //skb->end
	*((unsigned int *)((char *)Model0_skb+196)) = 128;
//struct.Model0_sk_buff:200|Load:i64
#if CY_ABSTRACT1
    //skb->head
	*((unsigned long long *)((char *)Model0_skb+200)) = Model0_data;
#else
	*((unsigned long long *)((char *)Model0_skb+200)) = 18446612140009356416;
#endif
//struct.Model0_sk_buff:208|Load:i64
#if CY_ABSTRACT1
    //abstract skb->data
	*((unsigned long long *)((char *)Model0_skb+208)) = Model0_skb->Model0_head+18446612140009356514-18446612140009356416;
#else
	*((unsigned long long *)((char *)Model0_skb+208)) = 18446612140009356514;
#endif

//struct.Model0_sk_buff:208|Load:i8*|i8:-12|Load:i32
    //skb->data->ack_seq (but this value is not initialized during LISTEN state)
    //besides, this value will be initialized inside array
	*((unsigned int *)((char *)*((long long *)((char *)Model0_skb+208))+-12)) = 18446744071752779328;

//struct.Model0_sk_buff:120|Load:i32
	*((unsigned int *)((char *)Model0_skb+120)) = 24;
//struct.Model0_sk_buff:124|Load:i32
	*((unsigned int *)((char *)Model0_skb+124)) = 0;
//struct.Model0_sk_buff:136|Load:i32
	*((unsigned int *)((char *)Model0_skb+136)) = 1573952;
//struct.Model0_sk_buff:152|Load:i32
	*((unsigned int *)((char *)Model0_skb+152)) = 2;
//struct.Model0_sk_buff:156|Load:i32
	*((unsigned int *)((char *)Model0_skb+156)) = 0;
//struct.Model0_sk_buff:216|Load:i32
	*((unsigned int *)((char *)Model0_skb+216)) = 704;
//struct.Model0_sk_buff:220|Load:i32
	*((unsigned int *)((char *)Model0_skb+220)) = 1;
//struct.Model0_sk_buff:40|Load:i32
	*((unsigned int *)((char *)Model0_skb+40)) = 18446744073332498433;
//struct.Model0_sk_buff:44|Load:i32
	*((unsigned int *)((char *)Model0_skb+44)) = 18446744073332498434;
//struct.Model0_sk_buff:48|Load:i16
	*((unsigned short *)((char *)Model0_skb+48)) = 0;
//struct.Model0_sk_buff:48|Load:i32
	*((unsigned int *)((char *)Model0_skb+48)) = 0;
//struct.Model0_sk_buff:50|Load:i16
	*((unsigned short *)((char *)Model0_skb+50)) = 0;
//struct.Model0_sk_buff:52|Load:i8
	*((unsigned char *)((char *)Model0_skb+52)) = 2;
//struct.Model0_sk_buff:56|Load:i32
	*((unsigned int *)((char *)Model0_skb+56)) = 0;
//struct.Model0_sk_buff:72|Load:i8
	*((unsigned char *)((char *)Model0_skb+72)) = 0;
#if CY_ABSTRACT1
    //skb->Model0__skb_refdst
    //skb->__skb_refdst->rtable
#else
//struct.Model0_sk_buff:88|Load:i64
	*((unsigned long long *)((char *)Model0_skb+88)) = 18446612140035070465;
//struct.Model0_sk_buff:88|Load:i64|and:-2|struct.Model0_dst_entry:128|Load:i32
	*((unsigned int *)((char *)((*((long long *)((char *)Model0_skb+88)))&(-2))+128)) = 0;
//struct.Model0_sk_buff:88|Load:i64|and:-2|struct.Model0_dst_entry:96|Load:i16
	*((unsigned short *)((char *)((*((long long *)((char *)Model0_skb+88)))&(-2))+96)) = 0;
#endif
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+0)) = 0;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+4)) = 0;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+8)) = 0;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+12)) = 0;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+16)) = 0;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+20)) = 0;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+24)) = 0;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+28)) = 0;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+32)) = 0;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+36)) = 0;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+40)) = 0;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+44)) = 0;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+48)) = 0;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+52)) = 0;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+56)) = 0;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+60)) = 0;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+64)) = -1020854264;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+68)) = 1414701322;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+72)) = 37032448;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+76)) = 4521992;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+80)) = 822356992;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+84)) = 104857600;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+88)) = 691038;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+92)) = 655874;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+96)) = -993915134;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+100)) = -2031503326;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+104)) = 416;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+108)) = 39845888;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+112)) = 286392319;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+116)) = 67239936;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+120)) = 46085;
	*((unsigned int *)((char *)(Model0_skb->Model0_head)+124)) = -1974710456;

#if CY_ABSTRACT1
    Model0_skb->Model0_len = 20;
    Model0_tcp_hdr(Model0_skb)->Model0_doff = 5;
#endif
//#if CY_DEBUG3
    Model0_tcp_hdr(Model0_skb)->Model0_ack = 1;
    printf("seq: %u\n", Model0_tcp_hdr(Model0_skb)->Model0_seq);
    printf("ack: %u\n", Model0_tcp_hdr(Model0_skb)->Model0_ack);
    printf("flag ack: %d\n", Model0_tcp_hdr(Model0_skb)->Model0_ack);
    printf("packet_len: %d\n", Model0_Skb_In[0].Model0_len);
    printf("packet_doff: %d\n", Model0_tcp_hdr(Model0_skb)->Model0_doff*4);
    printf("SKB: %p\n", Model0_skb);
    printf("SKB->next: %p\n", Model0_skb->Model0_next);
    printf("SKB->prev: %p\n", Model0_skb->Model0_prev);
//#endif
}
