// XXTEA-C.c
// 
// Copyright 2018 Unknown <eddy@jupiter>
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.
// 
// 


#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MX ((z>>5^y<<2) + (y>>3^z<<4) ^ (sum^y) + (k[p&3^e]^z))

long xxtea_enc(unsigned int* v, long n, unsigned int* k) {
  unsigned int z = v[n-1], y = v[0], sum = 0, e, delta = 0x9e3779b9;
  long p, q;
  q = 6 + 52/n;
  while (q-- > 0) {
    sum += delta;
    e = (sum >> 2) & 3;
    for (p=0; p<n-1; p++) {
      y = v[p+1];
      z = v[p] += MX;
    }
    y = v[0];
    z = v[n-1] += MX;
  }
  return 0;
}

long xxtea_dec(unsigned int* v, long n, unsigned int* k) {
  unsigned int z = v[n-1], y = v[0], sum = 0, e, delta = 0x9e3779b9;
  long p, q;
  q = 6 + 52/n;
  sum = q*delta ;
  while (sum != 0) {
    e = (sum >> 2) & 3;
    for (p=n-1; p>0; p--) {
	  z = v[p-1];
	  y = v[p] -= MX;
	}
    z = v[n-1];
    y = v[0] -= MX;
    sum -= delta;
  }
  return 0;
}

void read_data_binary(unsigned int *key,  size_t key_len,
                      unsigned int *data, size_t data_len)
{
	int fd = -1;
	if ((fd = open("data.bin", O_RDONLY)) == -1) {
		printf("error opening %d (%s)\n", errno, strerror(errno));
		return;
	}
	
	if (read(fd, key, key_len * sizeof(*key)) == -1) {
		printf("error reading %d (%s)\n", errno, strerror(errno));
	}
	if (read(fd, data, data_len * sizeof(*data)) == -1) {
		printf("error reading %d (%s)\n", errno, strerror(errno));
	}

	close(fd);
}


int main(int argc, char **argv)
{
	unsigned int key[4] = {0};
    unsigned int more_data[4] = {0};
    
    read_data_binary(key, 4, more_data, 4);
    
    xxtea_enc(more_data, 4, key);
    xxtea_dec(more_data, 4, key);
    
	return 0;
}

