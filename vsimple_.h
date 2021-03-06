/**
    Copyright (C) powturbo 2013-2014
    GPL v2 License

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    - email    : powturbo@gmail.com
    - github   : https://github.com/powturbo
    - homepage : https://sites.google.com/site/powturbo/
    - twitter  : https://twitter.com/powturbo

    vsimple_.h - "Integer Compression" variable simple
**/

#include "vint.h"
#define uint_t TEMPLATE3(uint, USIZE, _t)

unsigned char *TEMPLATE2(vsenc, USIZE)(uint_t *__restrict__ in, int n, unsigned char *__restrict__ op) {
  unsigned xm,m,r; 
  uint_t *e = in+n,*ip;
  for(ip = in; ip < e; ) {
      #ifdef USE_RLE 
    if(ip < e-4 && *ip == *(ip+1)) { uint_t *q = ip+1; while(q < e-1 && *(q+1) == *ip) q++; r = q - ip; 
      if(r*TEMPLATE2(bsr, USIZE)(*ip) > 16 || !*ip && r>4) { m = (*ip)?33:0; goto a; }     
    } else 
      #endif
    r = 0; unsigned x = m = bsr32(*ip); 
    while((r+1)*(xm = x > m?x:m) <= s_lim[xm]) { m = xm; x = TEMPLATE2(bsr, USIZE)(*(ip+(++r))); }											
    if(/*xm != 32 &&*/ m) while(r < s_itm[m]) m++;
    a:; 
    switch(m) {
      case 0: ip += r; 
        if(--r >= 0xf) { 
          *op++ = 0xf0; 
          if(n <= 0x100)
            *op++ = r; 
          else
            vbput(op, r);            
        } else *op++ = r<<4; 
        break;
      case 1:
        *(unsigned *)op =    1 |
        (unsigned)ip[ 0] <<  4 | 
        (unsigned)ip[ 1] <<  5 |
        (unsigned)ip[ 2] <<  6 |
        (unsigned)ip[ 3] <<  7 |
        (unsigned)ip[ 4] <<  8 |
        (unsigned)ip[ 5] <<  9 |
        (unsigned)ip[ 6] << 10 |
        (unsigned)ip[ 7] << 11 |
        (unsigned)ip[ 8] << 12 |
        (unsigned)ip[ 9] << 13 |  
        (unsigned)ip[10] << 14 |
        (unsigned)ip[11] << 15 |
        (unsigned)ip[12] << 16 |
        (unsigned)ip[13] << 17 |
        (unsigned)ip[14] << 18 |
        (unsigned)ip[15] << 19 |
        (unsigned)ip[16] << 20 |
        (unsigned)ip[17] << 21 |
        (unsigned)ip[18] << 22 |
        (unsigned)ip[19] << 23 |
        (unsigned)ip[20] << 24 |
        (unsigned)ip[21] << 25 |
        (unsigned)ip[22] << 26 |
        (unsigned)ip[23] << 27 |
        (unsigned)ip[24] << 28 |
        (unsigned)ip[25] << 29 |
        (unsigned)ip[26] << 30 |
        (unsigned)ip[27] << 31;		ip += 28; op += 4;
        break;
      case 2: 
        *(unsigned *)op =    2 |
        (unsigned)ip[ 0] <<  4 | 
        (unsigned)ip[ 1] <<  6 |
        (unsigned)ip[ 2] <<  8 |
        (unsigned)ip[ 3] << 10 |
        (unsigned)ip[ 4] << 12 |
        (unsigned)ip[ 5] << 14 |
        (unsigned)ip[ 6] << 16 |
        (unsigned)ip[ 7] << 18 |
        (unsigned)ip[ 8] << 20 |
        (unsigned)ip[ 9] << 22 |  
        (unsigned)ip[10] << 24 |
        (unsigned)ip[11] << 26 |
        (unsigned)ip[12] << 28 |
        (unsigned)ip[13] << 30;		ip += 14; op += 4;
        break;
      case 3: 
        *(unsigned *)op =    3 |
        (unsigned)ip[ 0] <<  4 | 
        (unsigned)ip[ 1] <<  7 |
        (unsigned)ip[ 2] << 10 |
        (unsigned)ip[ 3] << 13 |
        (unsigned)ip[ 4] << 16 |
        (unsigned)ip[ 5] << 19 |
        (unsigned)ip[ 6] << 22 |
        (unsigned)ip[ 7] << 25 |
        (unsigned)ip[ 8] << 28;		ip +=  9; op += 4;
        break;
      case 4: 
        *(uint64_t *)op =    4 |
        (unsigned)ip[ 0] <<  4 | 
        (unsigned)ip[ 1] <<  8 |
        (unsigned)ip[ 2] << 12 |
        (unsigned)ip[ 3] << 16 |
        (unsigned)ip[ 4] << 20 |
        (unsigned)ip[ 5] << 24 |
        (unsigned)ip[ 6] << 28;		ip += 7; op += 4;
        break;
      case 5: 
        *(uint64_t *)op =    5 |
        (unsigned)ip[ 0] <<  4 | 
        (unsigned)ip[ 1] <<  9 |
        (unsigned)ip[ 2] << 14 |
        (unsigned)ip[ 3] << 19 |
        (unsigned)ip[ 4] << 24 |
        (uint64_t)ip[ 5] << 29 |
        (uint64_t)ip[ 6] << 34;		ip += 7; op += 5;
        break;
      case 6: 
        *(uint64_t *)op =    6 |
        (unsigned)ip[ 0] <<  4 | 
        (unsigned)ip[ 1] << 10 |
        (unsigned)ip[ 2] << 16 |
        (unsigned)ip[ 3] << 22 |
        (uint64_t)ip[ 4] << 28 |
        (uint64_t)ip[ 5] << 34; 	ip +=  6; op += 5;
        break;
      case 7: 
        *(uint64_t *)op =    7 |
        (unsigned)ip[ 0] <<  4 | 
        (unsigned)ip[ 1] << 11 |
        (unsigned)ip[ 2] << 18 |
        (uint64_t)ip[ 3] << 25 |
        (uint64_t)ip[ 4] << 32; 	ip += 5; op += 5;
        break;
      case  8: 
      case  9: 
        *(uint64_t *)op =    9 |
        (unsigned)ip[ 0] <<  4 | 
        (unsigned)ip[ 1] << 13 |
        (unsigned)ip[ 2] << 22 |
        (uint64_t)ip[ 3] << 31; 	ip += 4; op += 5;
        break;
      case 10:
        *(uint64_t *)op =   10 |
        (unsigned)ip[ 0] <<  4 | 
        (unsigned)ip[ 1] << 14 |
        (uint64_t)ip[ 2] << 24 |
        (uint64_t)ip[ 3] << 34 |
        (uint64_t)ip[ 4] << 44 |
        (uint64_t)ip[ 5] << 54; 	ip += 6; op += 8;
        break;

      case 11: 
      case 12: 
        *(uint64_t *)op =   12 |
        (unsigned)ip[ 0] <<  4 | 
        (unsigned)ip[ 1] << 16 |
        (uint64_t)ip[ 2] << 28 |
        (uint64_t)ip[ 3] << 40 |
        (uint64_t)ip[ 4] << 52; 	ip += 5; op += 8;
        break;      
      case 13:
      case 14:      
      case 15:
        *(uint64_t *)op =   15 |
        (unsigned)ip[ 0] <<  4 | 
        (uint64_t)ip[ 1] << 19 |
        (uint64_t)ip[ 2] << 34 |
        (uint64_t)ip[ 3] << 49; 	ip += 4; op += 8;
        break;
      case 16:
      case 17:      
      case 18:
      case 19:      
      case 20: 
        *(uint64_t *)op =   11 |
        (unsigned)ip[ 0] <<  4 | 
        (uint64_t)ip[ 1] << 24 |
        (uint64_t)ip[ 2] << 44; 	ip += 3; op += 8;
        break;
      case 21:
      case 22:      
      case 23:
      case 24:      
      case 25:
      case 26:      
      case 27:
      case 28:      
      case 29:
      case 30:
        *(uint64_t *)op =   13 |
        (unsigned)ip[ 0] <<  4 | 
        (uint64_t)ip[ 1] << 34; 	ip += 2; op += 8;
        break;
      case 31:
      case 32:
        *(uint64_t *)op =   14 |
        (uint64_t)ip[ 0] <<  4; 	ip++;    op += 5;
        break;     
        #ifdef USE_RLE 
      case 33: 				ip += r;
        if(--r >= 0xf) { 
          *op++ = 0xf0|8; 
          if(n <= 0x100)
            *op++ = r; 
          else
            vbput(op, r);            
        } else *op++ = r<<4|8;
        vbput(op, ip[0]);
        break;
        #endif
    }    
  } 
  return op;   
}

#define OP(__x) op[__x] // *op++ //
#define OPI(__x) op+=__x// //

unsigned char *TEMPLATE2(vsdec, USIZE)(unsigned char *__restrict__ ip, int n, uint_t *__restrict__ op) { unsigned *op_=op+n;
  while(op < op_) { register uint64_t w=*(uint64_t *)ip;
    switch(w & 15) {  
      case 0: { 
        int r = (w>>4)&0xf; ip++; 
        if(unlikely(r == 0xf)) { 
          if(n <= 0x100)
            r = (w>>8)&0xff, ip++; 
          else
            r = vbget(ip);
        }          
        uint_t *q=op; op+=r+1; while(q<op) { q[0]=q[1]=q[2]=q[3]=q[4]=q[5]=q[6]=q[7]=0; q+=8; } //while(r-->=0) *op++=0;   
      } break; 
      case 1:                                     
        OP( 0) = (w >>  4) & 1;      
	OP( 1) = (w >>  5) & 1;      
        OP( 2) = (w >>  6) & 1;      
        OP( 3) = (w >>  7) & 1;      
        OP( 4) = (w >>  8) & 1;      
        OP( 5) = (w >>  9) & 1;      
        OP( 6) = (w >> 10) & 1;      
        OP( 7) = (w >> 11) & 1;      
        OP( 8) = (w >> 12) & 1;      
        OP( 9) = (w >> 13) & 1;      
        OP(10) = (w >> 14) & 1;      
        OP(11) = (w >> 15) & 1;      
        OP(12) = (w >> 16) & 1;      
        OP(13) = (w >> 17) & 1;      
        OP(14) = (w >> 18) & 1;      
        OP(15) = (w >> 19) & 1;      
        OP(16) = (w >> 20) & 1;      
        OP(17) = (w >> 21) & 1;      
        OP(18) = (w >> 22) & 1;      
        OP(19) = (w >> 23) & 1;      
        OP(20) = (w >> 24) & 1;      
        OP(21) = (w >> 25) & 1;      
        OP(22) = (w >> 26) & 1;      
        OP(23) = (w >> 27) & 1;      
        OP(24) = (w >> 28) & 1;      
        OP(25) = (w >> 29) & 1;      
        OP(26) = (w >> 30) & 1;      
        OP(27) = (w >> 31) & 1; 		OPI( 28); ip+=4; 
        break;                                        
      case 2:                                     
        OP( 0) = (w >>  4) & 3;      
        OP( 1) = (w >>  6) & 3;      
        OP( 2) = (w >>  8) & 3;      
        OP( 3) = (w >> 10) & 3;      
        OP( 4) = (w >> 12) & 3;      
        OP( 5) = (w >> 14) & 3;      
        OP( 6) = (w >> 16) & 3;      
        OP( 7) = (w >> 18) & 3;      
        OP( 8) = (w >> 20) & 3;      
        OP( 9) = (w >> 22) & 3;      
        OP(10) = (w >> 24) & 3;      
        OP(11) = (w >> 26) & 3;      
        OP(12) = (w >> 28) & 3;      
        OP(13) = (w >> 30) & 3;  		OPI( 14);  ip+=4;
        break;                                        
      case 3:                                   
        OP( 0) = (w >>  4) & 7;      
        OP( 1) = (w >>  7) & 7;      
        OP( 2) = (w >> 10) & 7;      
        OP( 3) = (w >> 13) & 7;      
        OP( 4) = (w >> 16) & 7;      
        OP( 5) = (w >> 19) & 7;      
        OP( 6) = (w >> 22) & 7;      
        OP( 7) = (w >> 25) & 7;      
        OP( 8) = (w >> 28) & 7;    		OPI( 9); ip+=4;
        break;                                        
      case 4:                                    
        OP( 0) = (w >>  4) & 0xf;      
        OP( 1) = (w >>  8) & 0xf;      
        OP( 2) = (w >> 12) & 0xf;      
        OP( 3) = (w >> 16) & 0xf;      
        OP( 4) = (w >> 20) & 0xf;      
        OP( 5) = (w >> 24) & 0xf;      
        OP( 6) = (w >> 28) & 0xf;    		OPI( 7); ip+=4;
        break;                                        
      case 5:                                      
        OP( 0) = (w >>  4) & 0x1f;      
        OP( 1) = (w >>  9) & 0x1f;      
        OP( 2) = (w >> 14) & 0x1f;      
        OP( 3) = (w >> 19) & 0x1f;      
        OP( 4) = (w >> 24) & 0x1f;      
        OP( 5) = (w >> 29) & 0x1f;      
        OP( 6) = (w >> 34) & 0x1f;   		OPI(  7); ip+=5;
        break;                                        
      case 6:                                     
        OP(0) = (w >>  4) & 0x3f;      
        OP(1) = (w >> 10) & 0x3f;      
        OP(2) = (w >> 16) & 0x3f;      
        OP(3) = (w >> 22) & 0x3f;      
        OP(4) = (w >> 28) & 0x3f;      
        OP(5) = (w >> 34) & 0x3f; 		OPI(  6); ip+=5;
        break;       
                                 
      case 7:                                  
        OP(0) = (w >>  4) & 0x7f;      
        OP(1) = (w >> 11) & 0x7f;      
        OP(2) = (w >> 18) & 0x7f;      
        OP(3) = (w >> 25) & 0x7f;      
        OP(4) = (w >> 32) & 0x7f;     		OPI( 5); ip+=5;                 
        break; 
                                       
        #ifdef USE_RLE 
      case 8: { 
        int r = (w>>4)&0xf; ip++; 
        if(unlikely(r == 0xf)) { 
          if(n <= 0x100)
            r = (w>>8)&0xff, ip++; 
          else
            r = vbget(ip);
        } 
        unsigned u = vbget(ip); uint_t *q=op; op+=r+1; while(q<op) { q[0]=q[1]=q[2]=q[3]=q[4]=q[5]=q[6]=q[7]=u; q+=8; } //while(r-->=0) *op++=u;
      } break; 
        #endif
      case 9:                                      
        OP(0) = (w >>  4) & 0x1ff;      
        OP(1) = (w >> 13) & 0x1ff;      
        OP(2) = (w >> 22) & 0x1ff;      
        OP(3) = (w >> 31) & 0x1ff;     		OPI( 4); ip+=5;             
        break;   
                                     
      case 10:                                      
        OP(0) = (w >>  4) & 0x3ff;      
        OP(1) = (w >> 14) & 0x3ff;      
        OP(2) = (w >> 24) & 0x3ff;      
        OP(3) = (w >> 34) & 0x3ff;      
        OP(4) = (w >> 44) & 0x3ff;      
        OP(5) = (w >> 54) & 0x3ff; 		OPI( 6); ip+=8;             
        break;                                        
      case 12:                                      
        OP(0) = (w >>  4) & 0xfff;      
        OP(1) = (w >> 16) & 0xfff;      
        OP(2) = (w >> 28) & 0xfff;      
        OP(3) = (w >> 40) & 0xfff;      
        OP(4) = (w >> 52) & 0xfff; 		OPI( 5); ip+=8;              
        break;                                        
      case 15:                                     
        OP(0) = (w >>  4) & 0x7fff;      
        OP(1) = (w >> 19) & 0x7fff;      
        OP(2) = (w >> 34) & 0x7fff;      
        OP(3) = (w >> 49) & 0x7fff; 		OPI( 4); ip+=8;              
        break;                                        
      case 11:                                      
        OP(0) = (w >>  4) & 0xfffff; // 20      
        OP(1) = (w >> 24) & 0xfffff;      
        OP(2) = (w >> 44) & 0xfffff; 		OPI( 3); ip+=8;             
        break;                                        
      case 13:                                      
        OP(0) = (w >>  4) & ((1<<30)-1);      
        OP(1) = (w >> 34) & ((1<<30)-1);	OPI( 2); ip+=8;
         break;                                        
      case 14:                                     
        OP(0) = (w >> 4) & ((1ull<<32)-1);	OPI( 1); ip+=5;              
        break;                                        
    }
  }
 return ip;
}

