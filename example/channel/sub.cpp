#include <iostream>

#include <errno.h>
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
  int fd = shm_open("TEST", O_CREAT | O_RDWR | O_TRUNC, 0666);
  if (fd < 0) {
    perror("shm_open()");
    return EXIT_FAILURE;
  }

  Buffer *data = (Buffer*)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
  printf("receiver mapped address: %p\n", data);

  // std::cout << data << std::endl;

  for (int i = 0; i < NUM; ++i) {
    while (!data->acces.load()) {}

    data->acces.store(false);

    printf("%d\n", data->val);

    data->acces.store(true);
  }

  munmap(data, SIZE);

  close(fd);

  shm_unlink("TEST");
}