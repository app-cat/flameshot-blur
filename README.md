<div align="center">
  <img src="data/img/app/org.flameshot.Flameshot.svg" alt="Flameshot" />
</div>

# Flameshot(blur版)
> 一个简单易用、功能丰富的`交互式`截图软件. fork于 [【flameshot】](https://github.com/flameshot-org/flameshot).


## blur版与原版差异

- 截图中的模糊效果, 统一使用`高斯模糊`, 不再使用`像素化`.
- 移除`MacOS/Windows`的支持, 这2个平台下已经有非常棒的截图软件了, flameshot在这2个平台下并没有什么优势, 所以这里不再支持.
- 各标注工具的尺寸粗细,不再共用同一个值, 也不再提供修改, 线条类工具统一使用`3px`, 其他文本或序号统一用`16px`.
- 移除`marker、square、redo、upload、launcher、move、size、plus、minus`等使用率低的工具.
- 应用设置中, 移除工具的颜色配置, 固定为白底黑字.
- 应用设置中, 移除保存的文件名的格式设置, 固定为`年-月-日_时-分-秒.(jpg|png)`
- 应用设置中, 移除所有默认的快捷键(可自行设置)
- 标注icon更新为更加美观的
- 应用logo也更换了
- 移除了除英文、中文以外的其他语言包


## 使用


示例:

- 区域截图:

    ```shell
    flameshot gui
    ```

- 区域截图,并保存到指定路径:

    ```shell
    flameshot gui -p ~/myStuff/captures
    ```

- 延时截图, 加参数 `-d {毫秒}`:

    ```shell
    flameshot gui -d 2000
    ```

- 全屏截图(无GUI交互), 并保存到指定路径:

    ```shell
    flameshot full -p ~/myStuff/captures
    ```

- 全屏截图(无GUI交互, 如果有多屏幕,会同时截完所有屏幕拼接在一起), 并保存到指定路径, 同时复制到粘贴板:

    ```shell
    flameshot full -c -p ~/myStuff/captures
    ```
- 仅对鼠标所在的屏幕进行全屏截图(保存到默认路径):

    ```shell
    flameshot screen
    ```

- 仅对鼠标所在的屏幕进行全屏截图, 但不保存, 会将图片的二进制数据打印出来:

    ```shell
    flameshot screen -r
    ```

- 对第一个屏幕进行全屏截图,并复制到粘贴板:

    ```shell
    flameshot screen -n 1 -c
    ```


### 配置文件
你可以打开配置界面进行设置操作, 也可以直接修改配置文件, 路径为: `~/.config/flameshot/flameshot.ini`.



## 安装

对于`debian 11/sid`, 可添加 [debianx](https://repo.debianx.in) 源之后, 可直接使用 apt命令安装, `sudo apt install flameshot-blur`.


## 编译安装
其他系统, 可以

### 依赖

#### Compile-time

- Qt >= 5.9
  + Development tools
- GCC >= 7.4
- CMake >= 3.13

#### Run-time

- Qt
  + SVG

#### Optional

- Git
- OpenSSL
- CA Certificates

#### Debian

```shell
# Compile-time
apt install g++ cmake build-essential qtbase5-dev qttools5-dev-tools libqt5svg5-dev qttools5-dev

# Run-time
apt install libqt5dbus5 libqt5network5 libqt5core5a libqt5widgets5 libqt5gui5 libqt5svg5

# Optional
apt install git openssl ca-certificates
```

#### Fedora

```shell
# Compile-time
dnf install gcc-c++ cmake qt5-qtbase-devel qt5-linguist

# Run-time
dnf install qt5-qtbase qt5-qtsvg-devel

# Optional
dnf install git openssl ca-certificates
```

#### Arch

```shell
# Compile-time
pacman -S cmake base-devel git qt5-base qt5-tools

# Run-time
pacman -S qt5-svg

# Optional
pacman -S openssl ca-certificates
```

#### NixOS

```shell
nix-shell
```

### Build

安装完依赖之后, 按顺序执行以下4行命令: 

```shell
mkdir build
cd build
cmake ..
make
```


编译完成之后,如果没报错, 则可以`build/src/`目录下找到`flameshot`这个可执行文件.

通过`make install`即可安装到系统.
