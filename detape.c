#include <stdio.h>
	
#include <fcntl.h>
#include <sys/stat.h> /* for mode definitions */

#define BLOCK 10240

static int little_endian(void)
{	unsigned int i = 1;
	char * c = (char *) &i;

	return (int) *c;
}

int blksize(int mbs)
{	unsigned result = 0;

	if(little_endian()) return(mbs);

	result |= (mbs & 0x000000ff) << 24;
	result |= (mbs & 0x0000ff00) << 8;
	result |= (mbs & 0x00ff0000) >> 8;
	result |= (mbs & 0xff000000) >> 24;
	return(result);
}

void main()
{
unsigned char buf[10240];
unsigned char hbuf[4];
unsigned char gbuf[9];
unsigned int block_head;
int in,out;
int rc;
int count;
in=open("xx.tap",O_RDONLY);
out=open("xx.tar",O_WRONLY|O_CREAT);
rc=1;
count=0;
rc=read(in,&block_head,4);
printf("block_head is %d\n\n",block_head);
while(rc!=0)
	{
		rc=read(in,&buf,block_head);
		write(out,buf,rc);
	rc=read(in,&hbuf,4); //all zeros?
	rc=read(in,&hbuf,4); //next block size?
	printf(".");
	fflush(stdout);
	}
printf("\n");
close(in);
close(out);
}
