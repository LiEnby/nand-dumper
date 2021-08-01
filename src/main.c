#include <vitasdkkern.h>
#include <stdio.h>
#include <string.h>

static char buffer[0x8000];

int run_on_thread(void *func) {
	int ret = 0;
	int res = 0;
	int uid = 0;

	ret = uid = ksceKernelCreateThread("run_on_thread", func, 64, 0x10000, 0, 0, 0);

	if (ret < 0) {
		ret = -1;
		goto cleanup;
	}
	if ((ret = ksceKernelStartThread(uid, 0, NULL)) < 0) {
		ret = -1;
		goto cleanup;
	}
	if ((ret = ksceKernelWaitThreadEnd(uid, &res, NULL)) < 0) {
		ret = -1;
		goto cleanup;
	}

	ret = res;

cleanup:
	if (uid > 0)
		ksceKernelDeleteThread(uid);

	return ret;
}

int run_dd(void)
{
	
	SceUID fd = ksceIoOpen("sdstor0:int-lp-act-entire", SCE_O_RDONLY, 0777);
	SceUID wfd = ksceIoOpen("ux0:int-lp-act-entire.img", SCE_O_RDWR | SCE_O_CREAT, 6);
	
	
	while(1)
	{
		int ret = ksceIoRead(fd, buffer, 0x8000);
		ksceIoWrite(wfd, buffer, ret);
		
		if(ret != 0x8000){
			ksceIoClose(wfd);
			kscePowerRequestColdReset();
			break;
		}
	}

	
	return 0;
}

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(SceSize args, void *argp) {
	run_on_thread(run_dd);	
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize args, void *argp) {
  return SCE_KERNEL_STOP_SUCCESS;
}
		