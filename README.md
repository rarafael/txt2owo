# txt2owo

convert text input into OwO output

![image](https://github.com/rarafael/txt2owo/blob/020f3d3fe3f3a1a82ea3e9b39f965cad1d6b27a5/screenshot.png)

### Usage
Use the `-e` to print out emoticons at the beginning and end of output.
```
txt2owo [-e] [...]
```
or
```
[command] | txt2owo [-e]
```

### Installation
the default installation prefix is `/usr/local`, this can be set with the PREFIX
make option
```
git clone https://github.com/rarafael/txt2owo.git
cd txt2owo
make
sudo make install
```

### Uninstall
```
cd txt2owo
sudo make uninstall
```
