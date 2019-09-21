#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void caesarCipher(int shift, int readId, char * buf);

int main(int argc, char * argv[])
{
	char * buf;
	struct stat sBuf;
	int openId = open(argv[1], O_RDWR);
	fstat(openId, &sBuf);
	uint fSize = sBuf.size;
	buf = malloc(fSize);
	int readId = read(openId, buf, fSize);

	//printf(1, "readId: %d\n", readId);

	//int outputId = open("output.txt", O_RDWR);

	//TEST
	int i = 0;
	int lfCount = 0;
	/*
	for (i=0; i<readId; i++){
		printf(1, "%c", buf[i]);
		lfCount++;
		if (lfCount == 100)
			printf(1, "\n");
	}
	*/

	if (!strcmp(argv[2], "0")){
		caesarCipher(atoi(argv[3]), readId, buf);
		/*
		if (write(openId, buf, readId) != readId){
			printf(1, "write error\n");
		}
		close(openId);
		*/
	}

	if (!strcmp(argv[4], "1")){
		i = 0;
		lfCount = 0;
		for (i=0; i<readId; i++){
			printf(1, "%c", buf[i]);
			if (lfCount == 100)
				printf(1, "\n");
		}
	}

	//printf(1, "trap test\n");

	//i = 0;
	//lfCount = 0;
	/*
	for (i=0; i<readId; i++){
		printf(outputId, "%c", buf[i]);
	}
	*/
	write(openId, buf, readId);
	//close(openId);

	exit();
} 

void caesarCipher(int shift, int readId, char * buf)
{
	int i = 0;
	for (i=0; i<readId; i++){
		if (buf[i] != '\n'){
			buf[i] = buf[i] + shift;
		}
	}
}