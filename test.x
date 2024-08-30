puts("start a program");

#const (
  first = sk[12, u8];
  udp   = sk[23, u16];
  arp   = 0x0806;
  ip    = 0x0800;
);

first?
  =arp -> pass;
  =ip -> udp? -> drop;  
  then -> puts("no match");
end

first?
  =0x800 -> pass;
  then   -> pass;
end