#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *do_something(void *arg)
{
	sleep(1);
	printf("do something\n");
}

int main(void)
{
	pthread_t thread;
	void *retval;

	// スレッドを作成
	if (pthread_create(&thread, NULL, do_something, NULL) != 0)
		// エラー処理
		return (0);
	// スレッドの終了方法
	// 1. スレッドが終了するまで待つ
	pthread_join(thread, &retval);
	my_sleep(1);
	// 2. スレッドを待たない
	//pthread_detach(thread);
}
