# mycat

## Options
```sh
-n --number
    output number of lines
-s --squeze-blank
    suppress empty lines
```

## Usage Example
```sh
$ mycat sample.txt
1234
abcd
$ mycat
aaaa
aaaa
abcd
abcd
^C
$ mycat -n sample.txt
1 1234
2 abcd
```

