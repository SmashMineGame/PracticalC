---
marp: true
theme: gaia
---
<!-- _class: lead -->

# Stderr and Stdout

---

# What are Stderr and Stdout?

---

# Usage in C

`fprintf(file, format, ...)`

Use `stdout` and `stderr` as files.

---

C Code:
```
fprintf(stdout, "%s", "stdout gets piped!\n");
fprintf(stderr, "%s", "ERROR doesn't get piped\n");
fprintf(stdout, "%s", "stdout gets piped again!\n");
```

Output:
```
stdout gets piped!
ERROR doesn't get piped
stdout gets piped again!
```

---

# Redirects

`$ ./prog [redirect] output.txt`
* `>`: Stdout of program is put into file
* `2>`: Stderr of program is put into file
* `3>`: Stdout and stderr is put into file

### Can be chained:
`$ ./ prog > output.txt 2> errors.txt`

---

# Pipes

`$ ./prog | grep -n "pipe"`

Output:
```
ERROR doesn't get piped
1:stdout gets piped!
2:stdout gets piped again!
```