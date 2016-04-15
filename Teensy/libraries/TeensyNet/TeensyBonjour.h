/*  TeensyBonjour.h
    Version 0.01 0831/2014
    by Jim Mayhugh
*/
#ifndef TBJ_H
#define TBJ_H

elapsedMillis runBonjour;
const uint32_t runBonjourTimeout = (1000 *5);
char bonjourBuf[256];
char bonjourNameBuf[64];

#endif
