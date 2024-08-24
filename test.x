BEGIN{
    out("attach a xdp prog");
}


#define target u16@12

target?
  =0x0800 -> u8@57302?
               =0x1337 -> pass;
               =0xdead -> 0xbeaf;
               drop;
  =u16@42 -> pass;
