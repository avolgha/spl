# spl

simple math equation solver written in c.

## features

- addition
- subtraction
- multiplication
- division
- modulo
- [postfix notation](https://w.wiki/8KhJ)
- parenthesis (why would you use them in postfix notation?)
- probably memory leaks?

## roadmap

- [x] implement floating point numbers
- [ ] add a RNG
- [ ] add command line flags
    - [ ] verbose output (print result for each operation as well)
    - [ ] stack dump (enable or disable stack dumps on error messages. preferrably, the default should be no)

## self compile

```sh
$ make
$ ./spl "..."
```
