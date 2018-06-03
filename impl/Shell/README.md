How to use these scripts:
-------------------------

The `printer.sh` script cuts the input string into an array of 
characters and then prints it out as an array of integers (e.g. ASCII 
values). This is to use them in Janus.

The `replacer.sh` script replaces "ARGV??#" strings in templated Janus code with corresponding 
arguments supplied to the script, e.g.

```
replacer.sh ../Janus/Chacha20.janus.template "`./printer.sh "Hello World!"`"
```

... replaces `ARGV1#` by the numerical representation of the string "Hello World!".
