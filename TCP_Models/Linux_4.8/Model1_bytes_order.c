#ifndef MODEL1_BYTES_ORDER_H
#define MODEL1_BYTES_ORDER_H
//#include "TCP_Model.h"
//cy yue
Model1_uint32_t Model1_htonl(Model1_uint32_t Model1_hostlong) {
    //return htonl(Model1_hostlong);
	return ((Model1_hostlong>>24)&0xff) | // move byte 3 to byte 0
           ((Model1_hostlong<<8)&0xff0000) | // move byte 1 to byte 2
           ((Model1_hostlong>>8)&0xff00) | // move byte 2 to byte 1
           ((Model1_hostlong<<24)&0xff000000); // byte 0 to byte 3
}
//cy yue
Model1_uint16_t Model1_htons(Model1_uint16_t Model1_hostshort) {
    //return htons(Model1_hostshort);
    return (Model1_hostshort >> 8) | (Model1_hostshort << 8);
}
Model1_uint32_t Model1_ntohl(Model1_uint32_t Model1_hostlong) {
    //return ntohl(Model1_hostlong);
	return ((Model1_hostlong>>24)&0xff) | // move byte 3 to byte 0
           ((Model1_hostlong<<8)&0xff0000) | // move byte 1 to byte 2
           ((Model1_hostlong>>8)&0xff00) | // move byte 2 to byte 1
           ((Model1_hostlong<<24)&0xff000000); // byte 0 to byte 3
}
//cy yue
Model1_uint16_t Model1_ntohs(Model1_uint16_t Model1_hostshort) {
    //return ntohs(Model1_hostshort);
    return (Model1_hostshort >> 8) | (Model1_hostshort << 8);
}
#endif
