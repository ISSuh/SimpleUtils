#include <iostream>

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <condition_variable>
#include <mutex>
#include <atomic>

struct Buffer {
  std::atomic<bool> acces;
  std::mutex m;
  std::condition_variable cv;
  int val;
};

#define NUM 10000000
#define SIZE sizeof(Buffer)

int main() {
  int fd = shm_open("TEST", O_CREAT | O_RDWR | O_TRUNC, 0600);
  if (fd < 0) {
    perror("shm_open()");
    return EXIT_FAILURE;
  }

  ftruncate(fd, SIZE);

  Buffer *data = (Buffer*)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  printf("sender mapped address: %p\n", data);

  data->acces.store(true);

  for (int i = 0; i < NUM; ++i) {
    while (!data->acces.load()) {}

    data->acces.store(false);

    data->val = i;
    printf("%d\n", data->val);

    data->acces.store(true);
  }

  munmap(data, SIZE);

  close(fd);
}