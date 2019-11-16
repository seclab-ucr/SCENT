#ifndef MODEL0_BYTES_ORDER_H
#define MODEL0_BYTES_ORDER_H
//#include "TCP_Model.h"
//cy yue
Model0_uint32_t Model0_htonl(Model0_uint32_t Model0_hostlong) {
    //return htonl(Model0_hostlong);
	return ((Model0_hostlong>>24)&0xff) | // move byte 3 to byte 0
           ((Model0_hostlong<<8)&0xff0000) | // move byte 1 to byte 2
           ((Model0_hostlong>>8)&0xff00) | // move byte 2 to byte 1
           ((Model0_hostlong<<24)&0xff000000); // byte 0 to byte 3
}
//cy yue
Model0_uint16_t Model0_htons(Model0_uint16_t Model0_hostshort) {
    //return htons(Model0_hostshort);
    return (Model0_hostshort >> 8) | (Model0_hostshort << 8);
}
Model0_uint32_t Model0_ntohl(Model0_uint32_t Model0_hostlong) {
    //return ntohl(Model0_hostlong);
	return ((Model0_hostlong>>24)&0xff) | // move byte 3 to byte 0
           ((Model0_hostlong<<8)&0xff0000) | // move byte 1 to byte 2
           ((Model0_hostlong>>8)&0xff00) | // move byte 2 to byte 1
           ((Model0_hostlong<<24)&0xff000000); // byte 0 to byte 3
}
//cy yue
Model0_uint16_t Model0_ntohs(Model0_uint16_t Model0_hostshort) {
    //return ntohs(Model0_hostshort);
    return (Model0_hostshort >> 8) | (Model0_hostshort << 8);
}
#endif
