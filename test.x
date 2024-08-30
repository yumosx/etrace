BEGIN {
  puts("start a program");
}

target eth0

#const (
  first = sk[12, u8];
  udp   = sk[23, u16];
  arp   = 0x0806;
  ip    = 0x0800;
);

case first
  =arp -> pass;
  =ip -> =udp -> drop;
  then -> puts("no match");
end