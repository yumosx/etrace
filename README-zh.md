用于 xdp 的小编程语言 目前还在构思中

```y
#const (
    first = packet[12, u8];
    udp   = packet[23, u16];
    arp   = 0x0806;
    ip    = 0x0800;
);

case first:
  =arp -> pass;
  =ip -> =udp -> drop;
  then -> puts("no match");
end
```

以太网帧的最小长度为64字节, 最大长度为518字节, 其中前12字节分别标识出发送数据帧的源

- `#const()`   是宏, 用于定义一系列的产量, 我们会在编译期间进行替换
- `packet`     是一个全局变量, 表示当前hook下来的包, `packet[12, u8]` 表示读取packet的第12字节的前8位
- `arp=0x0806` 用于定义常量
- `case`       是一个类似于对应switch语句的东西, 其中的`=arp`是用来 判断当前case后面的语句是否相等
- `drop`, `pass` 是xdp的两种模式
- `puts`       是一个函数用于输出对应的信息的函数