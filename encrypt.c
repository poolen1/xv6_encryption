#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void caesarCipher(int shift, int readId, char * buf);
void vigCipher(char * keyword, int shift, int readId, char * buf, char TR[54][54], int passLen);

int main(int argc, char * argv[])
{
	char * buf;
	struct stat sBuf;
	int openId = open(argv[1], O_RDWR);
	fstat(openId, &sBuf);
	uint fSize = sBuf.size;
	buf = malloc(fSize);
	int readId = read(openId, buf, fSize);
	char * password;// = argv[3];
	char * passRead;
	int passLen;// = strlen(password);
	int shiftVal;
	char tabulaRecta[54][54];

	int i=0;
	int j=0;

	//Populate Tabula Recta
	for (i=0; i<26; i++){
		tabulaRecta[0][i] = 'A' + i;
	}
	for (i=26; i<52; i++){
		tabulaRecta[0][i] = 'a' + j;
		j++;
	}
	for (i=1; i<52; i++){
		tabulaRecta[i][51] = tabulaRecta[i-1][0];
		for (j=0; j<51; j++){
			tabulaRecta[i][j] = tabulaRecta[i-1][j+1];
		}
	}

	printf(1, "Enter password: ");
	passRead = malloc(256);
	i=0;
	while (read(0, &passRead[i], 1)){
		if(passRead[i] == '\n'){
			break;
		} else
			i++;
	}
	i=0;
	passLen = strlen(passRead);
	password = malloc(passLen * sizeof(char));
	passLen--;
	for (i=0; i<passLen; i++){
		password[i] = passRead[i];
	}

	//printf(1, "password: %s\n", password);
	//printf(1, "strLen: %d\n", passLen);

	//TEST
	/*
	for (i=0; i<54; i++){
		for (j=0; j<54; j++){
			printf(1, "%c", tabulaRecta[i][j]);
		}
		printf(1, "\n");
	}
	*/

	//generate shift value
	shiftVal = password[0];
	shiftVal = shiftVal % 10;
	if (shiftVal == 0){
		shiftVal = 3;
	}
	//printf(1, "shiftVal: %d\n", shiftVal);

	//printf(1, "readId: %d\n", readId);

	//int outputId = open("output.txt", O_RDWR);
	//printf(1, "trap test\n");
	/*
	for (i=0; i<passLen; i++){
		printf(1, "%c%d", password[i], i);
	}
	*/

	if (!strcmp(argv[2], "0")){
		caesarCipher(shiftVal, readId, buf);
		close(openId);
	}

	else if (!strcmp(argv[2], "1")){
		vigCipher(password, shiftVal, readId, buf, tabulaRecta, passLen);
		close(openId);
	}
	

	openId = open(argv[1], O_CREATE | O_RDWR);
	caesarCipher(3, passLen, password);

	//printf(1, "trap test1\n");
	write(openId, argv[2], 1);
	write(openId, password, passLen);
	write(openId, " ", 1);
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

void vigCipher(char * keyword, int shift, int readId, char * buf, char TR[54][54], int passLen)
{
	int i;
	int j = 0;
	int row = 0;
	int col = 0;
	char key[readId];

	/*
	for (i=0; i<54; i++){
		for (j=0; j<54; j++){
			printf(1, "%c", TR[i][j]);
		}
		printf(1, "\n");
	}
	*/

	//printf(1, "vcPassword: %s\n", keyword);
	//printf(1, "readId: %d\n", readId);
	//printf(1, "passLen: %d\n", passLen);

	for (i=0; i<readId; i++){
		if((buf[i] >= 'A' && buf[i] <= 'Z') || (buf[i] >= 'a' && buf[i] <= 'z')){
			key[i] = keyword[j];
			j++;
			if (j == passLen){
				j=0;
			}
		} else 
			(key[i] = buf[i]);
	}

	/*
	for (i=0; i<readId; i++){
		printf(1, "%c", key[i]);
	}
	*/
	

	//printf(1, "Trap test\n");
	
	for (i=0; i<readId; i++){
		if (buf[i] != '\n'){
			if((buf[i] >= 'A' && buf[i] <= 'Z') || (buf[i] >= 'a' && buf[i] <= 'z')){
				while (buf[i] != TR[0][col]){
					col++;
				}
				while (key[i] != TR[row][0]){
					row++;
				}
				buf[i] = TR[row][col];
			} /*else {
				buf[i] = buf[i] + shift;
			}*/
		}
		row = 0;
		col = 0;
	}
}

//test
	/*
	printf(1, "trap test0\n");

	j=0;
	for (i=0; i<readId; i++){
		key[i] = keyword[j];
		j++;
		if (j == passLen){
			j = 0;
		}
	}

	printf(1, "trap test1\n");
	*/