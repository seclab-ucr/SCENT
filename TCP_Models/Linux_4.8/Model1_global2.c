void Model1_Global_Initialize(){
#if CY_ABSTRACT1
	Model1_sysctl_tcp_adv_win_scale = 0;	
	Model1_sysctl_tcp_dsack = 0;
	Model1_sysctl_tcp_fack = 0;
    //not sure
	Model1_sysctl_tcp_fastopen = 1;
#else
	Model1_sysctl_tcp_adv_win_scale = 1;	
	Model1_sysctl_tcp_dsack = 1;
	Model1_sysctl_tcp_fack = 1;
	Model1_sysctl_tcp_fastopen = 1;
#endif
    Model1_jiffies = 5580855158;
	Model1_phys_base = 0;
    Model1_sysctl_tcp_abort_on_overflow = 0;
	Model1_sysctl_tcp_app_win = 31;
	Model1_sysctl_tcp_challenge_ack_limit = 1000;
	Model1_sysctl_tcp_min_rtt_wlen = 300;
	Model1_sysctl_tcp_rmem[0] = 4096;
	Model1_sysctl_tcp_rmem[1] = 87380;
	Model1_sysctl_tcp_rmem[2] = 6291456;
	Model1_sysctl_tcp_mem[0] = 81237;
	Model1_sysctl_tcp_mem[1] = 108316;
	Model1_sysctl_tcp_mem[2] = 162474;
	Model1_sysctl_tcp_slow_start_after_idle = 1;
	Model1_sysctl_tcp_stdurg = 0;
	Model1_sysctl_tcp_wmem[0] = 4096;
	Model1_sysctl_tcp_wmem[1] = 16384;
	Model1_sysctl_tcp_wmem[2] = 4194304;
	Model1_sysctl_tcp_workaround_signed_windows = 0;
	Model1_tcp_memory_allocated.Model1_counter = 0;
	Model1_tcp_memory_pressure = 0;
	Model1_tcp_orphan_count.Model1_count = 0;
	Model1_tcp_sockets_allocated.Model1_count = 0;
}
