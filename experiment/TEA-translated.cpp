/* Translated from Janus program */
#include <stdio.h>      /* printf */
#include <assert.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define __attr_zerostack __attribute__((annotate("SENSITIVE")))


__attr_zerostack int TEA_encipher_forward(unsigned int *data, unsigned int *key);
__attr_zerostack int TEA_encipher_reverse(unsigned int *data, unsigned int *key);

/*void XTEA_encipher_forward(int &num_rounds, unsigned int *data, unsigned int *key);
void XTEA_encipher_reverse(int &num_rounds, unsigned int *data, unsigned int *key);

void XXTEA_encipher_forward(unsigned int *data, unsigned int *key);
void XXTEA_encipher_reverse(unsigned int *data, unsigned int *key);
*/
__attr_zerostack int TEA_encipher_forward(unsigned int *data, unsigned int *key) {
    unsigned int delta = 2654435769;
    unsigned int sum = 0;
    for (int i = 1 ; i != 32 + 1 ; i += 1) {
        sum += delta;
        data[0] += data[1] * 16 + key[0] ^ data[1] + sum ^ data[1] / 32 + key[1];
        data[1] += data[0] * 16 + key[2] ^ data[0] + sum ^ data[0] / 32 + key[3];
    }
    //assert(sum == 32 * delta);
    //assert(delta == 2654435769);
    return 0;
}
__attr_zerostack int TEA_encipher_reverse(unsigned int *data, unsigned int *key) {
    unsigned int delta = 2654435769;
    unsigned int sum = 32 * delta;
    for (int i = 32 ; i != 1 + 0 - 1 ; i += 0 - 1) {
        data[1] -= data[0] * 16 + key[2] ^ data[0] + sum ^ data[0] / 32 + key[3];
        data[0] -= data[1] * 16 + key[0] ^ data[1] + sum ^ data[1] / 32 + key[1];
        sum -= delta;
    }
    //assert(sum == 0);
    //assert(delta == 2654435769);
    return 0;
}
/*
void XTEA_encipher_forward(int &num_rounds, unsigned int *data, unsigned int *key) {
    unsigned int delta = 2654435769;
    unsigned int sum = 0;
    for (int i = 1 ; i != num_rounds + 1 ; i += 1) {
        data[0] += (data[1] * 16 ^ data[1] / 32) + data[1] ^ sum + key[(int) sum & 3];
        sum += delta;
        data[1] += (data[0] * 16 ^ data[0] / 32) + data[0] ^ sum + key[(int) sum / 2048 & 3];
    }
    assert(sum == (unsigned int) num_rounds * delta);
    assert(delta == 2654435769);
}
void XTEA_encipher_reverse(int &num_rounds, unsigned int *data, unsigned int *key) {
    unsigned int delta = 2654435769;
    unsigned int sum = (unsigned int) num_rounds * delta;
    for (int i = num_rounds ; i != 1 + 0 - 1 ; i += 0 - 1) {
        data[1] -= (data[0] * 16 ^ data[0] / 32) + data[0] ^ sum + key[(int) sum / 2048 & 3];
        sum -= delta;
        data[0] -= (data[1] * 16 ^ data[1] / 32) + data[1] ^ sum + key[(int) sum & 3];
    }
    assert(sum == 0);
    assert(delta == 2654435769);
}

void XXTEA_encipher_forward(unsigned int *data, unsigned int *key) {
    unsigned int delta = 2654435769;
    int n = 4;
    unsigned int sum = 0;
    unsigned int e = 0;
    int p = 1;
    int q = 6 + 52 / n;
    assert(q == 6 + 52 / n);
    while (!(q == 0)) {
        sum += delta;
        e += sum / 4 & 3;
        data[0] += (data[n - 1] / 32 ^ data[1] * 4) + (data[1] / 8 ^ data[n - 1] * 16) ^ (sum ^ data[1]) + (key[e] ^ data[n - 1]);
        assert(p == 1);
        while (!(p == n - 1)) {
            data[p] += (data[p - 1] / 32 ^ data[p + 1] * 4) + (data[p + 1] / 8 ^ data[p - 1] * 16) ^ (sum ^ data[p + 1]) + (key[(p & 3) ^ (int) e] ^ data[p - 1]);
            p += 1;
            assert(!(p == 1));
        }
        data[n - 1] += (data[n - 2] / 32 ^ data[0] * 4) + (data[0] / 8 ^ data[n - 2] * 16) ^ (sum ^ data[0]) + (key[(p & 3) ^ (int) e] ^ data[n - 2]);
        p -= n - 2;
        e -= sum / 4 & 3;
        q -= 1;
        assert(!(q == 6 + 52 / n));
    }
    assert(q == 0);
    assert(p == 1);
    assert(e == 0);
    assert(sum == (6 + 52 / (unsigned int) n) * delta);
    assert(n == 4);
    assert(delta == 2654435769);
}
void XXTEA_encipher_reverse(unsigned int *data, unsigned int *key) {
    unsigned int delta = 2654435769;
    int n = 4;
    unsigned int sum = (6 + 52 / (unsigned int) n) * delta;
    unsigned int e = 0;
    int p = 1;
    int q = 0;
    assert(q == 0);
    while (!(q == 6 + 52 / n)) {
        q += 1;
        e += sum / 4 & 3;
        p += n - 2;
        data[n - 1] -= (data[n - 2] / 32 ^ data[0] * 4) + (data[0] / 8 ^ data[n - 2] * 16) ^ (sum ^ data[0]) + (key[(p & 3) ^ (int) e] ^ data[n - 2]);
        assert(p == n - 1);
        while (!(p == 1)) {
            p -= 1;
            data[p] -= (data[p - 1] / 32 ^ data[p + 1] * 4) + (data[p + 1] / 8 ^ data[p - 1] * 16) ^ (sum ^ data[p + 1]) + (key[(p & 3) ^ (int) e] ^ data[p - 1]);
            assert(!(p == n - 1));
        }
        data[0] -= (data[n - 1] / 32 ^ data[1] * 4) + (data[1] / 8 ^ data[n - 1] * 16) ^ (sum ^ data[1]) + (key[e] ^ data[n - 1]);
        e -= sum / 4 & 3;
        sum -= delta;
        assert(!(q == 0));
    }
    assert(q == 6 + 52 / n);
    assert(p == 1);
    assert(e == 0);
    assert(sum == 0);
    assert(n == 4);
    assert(delta == 2654435769);
}
*/
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

int main() {
    unsigned int key[4] = {0};
    unsigned int data[2] = {0};
    unsigned int more_data[4] = {0};
    int num_rounds = 0;
    
    //key[0] += 0;
    //key[1] += 1;
    //key[2] += 2;
    //key[3] += 3;
    data[0] += 42;
    data[1] += 27;
    //more_data[0] += 42;
    //more_data[1] += 27;
    //more_data[2] += 42;
    //more_data[3] += 27;
    num_rounds += 32;
    
    read_data_binary(key, 4, more_data, 4);
    
    //printf("%u, %u\n", data[0], data[1]);
    TEA_encipher_forward(data, key);
    //printf("%u, %u\n", data[0], data[1]);
    TEA_encipher_reverse(data, key);
    //printf("%u, %u\n", data[0], data[1]);
    //XTEA_encipher_forward(num_rounds, data, key);
    //printf("%u, %u\n", data[0], data[1]);
    //XTEA_encipher_reverse(num_rounds, data, key);
    //printf("%u, %u, %u, %u\n", more_data[0], more_data[1], more_data[2], more_data[3]);
    //XXTEA_encipher_forward(more_data, key);
    //printf("%u, %u, %u, %u\n", more_data[0], more_data[1], more_data[2], more_data[3]);
    //XXTEA_encipher_reverse(more_data, key);
    return 1;
}
