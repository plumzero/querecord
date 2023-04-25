
#include <stdio.h>
#include <string>
#include <memory>

void ping_net()
{
  std::string cmd_string = "ping 172.20.1.150 -c 1 -W 1 | grep '100% packet loss'";
  std::unique_ptr<FILE, decltype(&pclose)> fp(popen(cmd_string.c_str(), "r"), pclose);
  if (! fp) {
    char buf[1024] = {0};
    size_t n = fread(buf, 1, sizeof(buf), fp.get());
    if (n > 0) {
      printf("network disconnect: %s\n", buf);
    }
  }
}

int main()
{
  ping_net();

  return 0;
}
