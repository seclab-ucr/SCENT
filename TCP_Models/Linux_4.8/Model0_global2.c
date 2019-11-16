void Model0_Global_Initialize(){
#if CY_ABSTRACT1
	Model0_sysctl_tcp_adv_win_scale = 0;	
	Model0_sysctl_tcp_dsack = 0;
	Model0_sysctl_tcp_fack = 0;
    //not sure
	Model0_sysctl_tcp_fastopen = 1;
//#else
//	Model0_sysctl_tcp_adv_win_scale = 1;	
//	Model0_sysctl_tcp_dsack = 1;
//	Model0_sysctl_tcp_fack = 1;
//	Model0_sysctl_tcp_fastopen = 1;
#endif
    Model0_jiffies = 5580855158;
	Model0_phys_base = 0;
    Model0_sysctl_tcp_abort_on_overflow = 0;
	Model0_sysctl_tcp_app_win = 31;
	Model0_sysctl_tcp_challenge_ack_limit = 1000;
	Model0_sysctl_tcp_min_rtt_wlen = 300;
	Model0_sysctl_tcp_rmem[0] = 4096;
	Model0_sysctl_tcp_rmem[1] = 87380;
	Model0_sysctl_tcp_rmem[2] = 6291456;
	Model0_sysctl_tcp_mem[0] = 81237;
	Model0_sysctl_tcp_mem[1] = 108316;
	Model0_sysctl_tcp_mem[2] = 162474;
	Model0_sysctl_tcp_slow_start_after_idle = 1;
	Model0_sysctl_tcp_stdurg = 0;
	Model0_sysctl_tcp_wmem[0] = 4096;
	Model0_sysctl_tcp_wmem[1] = 16384;
	Model0_sysctl_tcp_wmem[2] = 4194304;
	Model0_sysctl_tcp_workaround_signed_windows = 0;
	Model0_tcp_memory_allocated.Model0_counter = 0;
	Model0_tcp_memory_pressure = 0;
	Model0_tcp_orphan_count.Model0_count = 0;
	Model0_tcp_sockets_allocated.Model0_count = 0;
}
