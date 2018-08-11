// chacha-main.c
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

#include "ecrypt-sync.h"

void read_data_binary(unsigned char *key,  size_t key_len,
                      unsigned char *data, size_t data_len)
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
	ECRYPT_ctx ctx;
	unsigned char data[64];
	unsigned char data_enc[64];
	unsigned char data_dec[64];
	unsigned char key[17] = "0123456789abcdef";
	unsigned char iv[8];
	
	read_data_binary(key, 0, data, 64);
	//read_data_binary(key, 0, data, 64);
	ECRYPT_keysetup(&ctx, key, 128, 64);
	ECRYPT_ivsetup(&ctx, iv);
	
	ECRYPT_encrypt_bytes(&ctx, data,     data_enc, 64);
	ECRYPT_decrypt_bytes(&ctx, data_enc, data_dec, 64);
	
	
	return 0;
}

