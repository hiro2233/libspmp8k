
#include <stdint.h>
#include <stdio.h>
#include "Des.h"

#define ERR(msg) { \
	printf("error: %s\n", msg); \
	goto done; \
}

char aucKey[] = {0x6E, 0x2D, 0x70, 0x2A, 0x38, 0x4B, 0x47, 0x4D};

void hexdump(uint8_t *data, int length);

int main(int argc, char **argv)
{
	FILE *f = NULL;
	FILE *fout = NULL;
	int size, totalsize, i;
	uint8_t buff[0x400];
	uint8_t data[0x400];
	uint8_t data2[0x400];

	if (argc < 2) ERR("to few arguments");
	if ((f = fopen(argv[1], "rb")) == NULL) ERR("cannot open file");

	fseek(f, 0x80, SEEK_SET);

	totalsize = fread(buff, 1, 0x400, f);
	if (!Des_Go((char*)data, (char*)buff, 0x400, aucKey, 8, DECRYPT)) ERR("decrypt failed");
	if (!Des_Go((char*)data2, (char*)data, 0x400, aucKey, 8, ENCRYPT)) ERR("encrypt failed");

	for (i=0; i<0x400; i++) {
		if (buff[i] != data2[i]) {
			printf("mismatch at %x\n");
			break;
		}
	}
	if (i == 0x400) printf("encoding/decoding works!\n");
	else hexdump(data2, 0x400);

	goto done;
/*
	hexdump(data, 0x400);
	goto done;
*/
	fseek(f, 0x480, SEEK_SET);
	fout = fopen("conv.bin", "wb");
	fwrite(data, 0x400, 1, fout);
//	totalsize = 0;
	while (1) { //!feof(f)) {
		size = fread(buff, 1, 0x400, f);
		printf(".");
		totalsize += size;
		fwrite(buff, size, 1, fout);
		if (size < 0x400) break;
	}
	fclose(fout);
	printf("%d bytes copied (%d)\n", totalsize, feof(f));

done:
	if (f != NULL) fclose(f);
	return 0;
}

void hexdump(uint8_t *data, int length)
{
	int i, j;

	printf("00000000 : ");
	for (i=0; i<length; i++) {
		if ((i != 0) && ((i & 0xF) == 0)) {
			printf("- ");
			for (j=0; j<16; j++) if ((data[i-16+j] > 0x1f) && (data[i-16+j] < 0x80)) printf("%c", data[i-16+j]);
			else printf(".");
			printf("\n%08x : ", i);
		}
		printf("%02x ", data[i]);
	}
	printf("\n");
}

