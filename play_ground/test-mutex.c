/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test-mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyazawa.kai.0823 <miyazawa.kai.0823@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 11:45:09 by miyazawa.ka       #+#    #+#             */
/*   Updated: 2023/12/31 00:41:21 by miyazawa.ka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 共有データ
int shared_data = 0;

// ミューテックスの宣言
pthread_mutex_t mutex;

// スレッドから呼び出される関数
void* thread_function(void* arg) {
	int thread_id = *((int*)arg);

	// ミューテックスをロック
	pthread_mutex_lock(&mutex);

	// クリティカルセクション（共有データに対する操作）
	printf("Thread %d entering critical section.\n", thread_id);
	shared_data++;
	printf("Thread %d exiting critical section.\n", thread_id);

	// ミューテックスをアンロック
	pthread_mutex_unlock(&mutex);

	return NULL;
}

int main() {
	// ミューテックスの初期化
	pthread_mutex_init(&mutex, NULL);

	// スレッド数
	const int num_threads = 3;

	// スレッドIDを格納する配列
	pthread_t threads[num_threads];

	// スレッドの引数を格納する配列
	int thread_args[num_threads];

	// スレッドを生成
	for (int i = 0; i < num_threads; ++i) {
		thread_args[i] = i + 1;
		pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
	}

	// スレッドの終了を待つ
	for (int i = 0; i < num_threads; ++i) {
		pthread_join(threads[i], NULL);
	}

	// ミューテックスの破棄
	pthread_mutex_destroy(&mutex);

	// 共有データの最終値を表示
	printf("Final value of shared_data: %d\n", shared_data);

	return 0;
}
