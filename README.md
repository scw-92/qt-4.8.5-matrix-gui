# qt-4.8.5-matrix-gui

## 00-QT4.8..5_test        :  qt测试程序源代码(编译为一个整体: 5M的text)
## 01-qt-4.8.5-test-split  :  qt测试程序源代码(单独编译，为每一个功能编译为一个程序)
## 02-matrix-gui-2.0/app   :  提供了程序的桌面配置方法
## 03-webpages             :  修改后的文件系统里面的源代码
## 04-S99aplex             :  文件系统的启动脚本
## 05-httpd.conf           :  apache2的配置文件
## 06-matrix_browser       :  QT本地浏览器
## 07-matrix-gui-2.0.sh    :  本地浏览器的启动脚本
## 08 matrix-gui           :  位于am437x的PDK中

* [QT4.8.5编译-富林](https://www.cnblogs.com/chenfulin5/p/6958560.html)
* [QT4.8.6编译-整套流程](https://www.cnblogs.com/bleachli/p/4759587.htm)
* [单独编译某一的QT模块](https://www.cnblogs.com/findumars/p/6375973.html)
* [qt测试程序源代码编译](https://www.cnblogs.com/chenfulin5/p/7009012.html)
* [matrix_browser介绍](https://www.cnblogs.com/zengjfgit/p/4609623.html)
* [ti-matrix用户指南](http://processors.wiki.ti.com/index.php/Matrix_Users_Guide)
* [QT4.8.5源码](http://download.qt.io/archive/qt/4.8/4.8.5/qt-everywhere-opensource-src-4.8.5.tar.gz) 

```sh
  注意：
  1. 关于matrix-gui-2.0里面的xxx.php文件的解析请看剑锋的博客
  2. 在QT4.8.5里面，qtwebkit在src/3rdparty/webkit中
  3. qtwebkit.4.8.5版本的使用请参考：http://doc.qt.io/archives/qt-4.8/qtwebkit-module.html
```

编译arm版本的QT4.8.5
* [01 编译tslib](#jump1)
* [02 编译qt](#jump2)
* [03 安装QTcreate](#jump3)
* [04 编译qtwebkit](#jump4)
* [05 QTWebKit模块的使用](#jump5)
* [06 查看qmake的信息](#jump6)
* [07 修改完静态IP后重启开发板屏幕白屏问题](#jump7)


## <p>qt4.8.5 手动编译</p>

<span id="jump1">1. tslib（0.9.0） 编译
	
```sh
    sudo apt-get install autoconf automake libtool
    git clone https://github.com/scw-92/tslib.git
    cd tslib
    创建auto_configure.sh 脚本文件，内容如下：
```
<div>cat auto_configure.sh</div>

```sh
echo "ac_cv_func_malloc_0_nonnull=yes" >daiq_tslib.cache 
./autogen.sh 
./configure \
	--prefix=/home/cmi-at751/qt4.8.5/tslib_install \
	--host=arm-linux-gnueabihf 
make && make install
```
<span id="jump2">2. 编译QT
* [下载合适的交叉编译工具链](https://e2echina.ti.com/question_answer/dsp_arm/sitara_arm/f/25/p/113233/308047#308047)
* [QT4.8.5源码](http://download.qt.io/archive/qt/4.8/4.8.5/qt-everywhere-opensource-src-4.8.5.tar.gz) 

<div>编译配置步骤如下</div>

```sh
 2.1. 
  复制一份  qt-everywhere-opensource-src-4.8.5/mkspecs/qws/linux-arm-gnueabi-g++ 
        为 qt-everywhere-opensource-src-4.8.5/mkspecs/qws/linux-arm-gnueabihf-g++
        
  2.2. cat qt-everywhere-opensource-src-4.8.5/mkspecs/qws/linux-arm-gnueabihf-g++/qmake.conf 
```

<div>2.2 cat qt-everywhere-opensource-src-4.8.5/mkspecs/qws/linux-arm-gnueabihf-g++/qmake.conf</div>

```sh
#
# qmake configuration for building with arm-none-linux-gnueabi-g++
#

include(../../common/linux.conf)
include(../../common/gcc-base-unix.conf)
include(../../common/g++-unix.conf)
include(../../common/qws.conf)

# modifications to g++.conf
QMAKE_CC                = arm-linux-gnueabihf-gcc
QMAKE_CXX               = arm-linux-gnueabihf-g++
QMAKE_LINK              = arm-linux-gnueabihf-g++
QMAKE_LINK_SHLIB        = arm-linux-gnueabihf-g++

# modifications to linux.conf
QMAKE_AR                = arm-linux-gnueabihf-ar cqs
QMAKE_OBJCOPY           = arm-linux-gnueabihf-objcopy
QMAKE_STRIP             = arm-linux-gnueabihf-strip


QMAKE_INCDIR            = /home/cmi-at751/qt4.8.5/tslib_install/include
QMAKE_LIBDIR            = /home/cmi-at751/qt4.8.5/tslib_install/lib

load(qt_config)
```
<div>2.3. 修改 qt-everywhere-opensource-src-4.8.5/mkspecs/common/linux.conf </div>

```sh
QMAKE_LIBS_THREAD     = -lpthread  -lts       // 添加 -lts
```

<div>2.4 在  qt-everywhere-opensource-src-4.8.5 里面添加配置文件 my.sh </div>

```sh
#!/bin/sh                                                                       
                                                                                
./configure \
	-opensource \
	-prefix /home/cmi-at751/qt4.8.5/qtarm_install \
	-confirm-license \
	-release \
	-shared \
	-embedded arm \
	-force-pkg-config \
	-xplatform qws/linux-arm-gnueabihf-g++ \
	-depths 16,18,24,32 \
	-fast \
	-optimized-qmake \
	-no-pch \
	-qt-sql-sqlite \
	-qt-libjpeg \
	-qt-zlib \
	-qt-libpng \
	-qt-freetype \
	-little-endian -host-little-endian \
	-no-qt3support \
	-qt-libtiff -qt-libmng \
	-make translations \
	-qt-gfx-linuxfb -qt-gfx-transformed -qt-gfx-multiscreen \
	-no-gfx-vnc -no-gfx-qvfb -qt-kbd-linuxinput \
	-no-kbd-qvfb -armfpa  \
	-no-mouse-qvfb \
	-no-opengl \
	-no-mmx -no-sse -no-sse2 \
	-no-3dnow \
	-no-openssl \
	-webkit \
	-no-qvfb \
	-no-phonon \
	-no-nis \
	-no-opengl \
	-no-cups \
	-no-glib \
	-no-xcursor -no-xfixes -no-xrandr -no-xrender \
	-no-separate-debug-info \
	-nomake examples -make tools -make docs \
	-qt-mouse-tslib -DQT_QLOCALE_USES_FCVT \
	-I/home/cmi-at751/qt4.8.5/tslib_install/include \
	-L/home/cmi-at751/qt4.8.5/tslib_install/lib   
```
<div>2.5. 编译与安装</div>

```sh
  chmod 777 my.sh
  make -j4
  make install
```
<span id="jump3">3. 安装QTcreate
```sh
经过测试，可以使用系统原有的针对QT5.6.2版本的QTCREATOR进行编译，上述“qt测试程序源代码”可以直接进行编译，编译可以通过。
```
<span id="jump4">4. 编译QTWebKit
```sh
使用QTcteator编译QTWebKit
	1. 在linux虚拟机中打开qtcreatror
	2. 具体编译如下图所示
```
![](qt4.8.5-image/clipboard1.png)
	
![](qt4.8.5-image/clipboard2.png)

![](qt4.8.5-image/clipboard3.png)

![](qt4.8.5-image/clipboard4.png)

![](qt4.8.5-image/clipboard5.png)

<span id="jump5">5. QTWebKit模块的使用
	
<div>1. 更改webkit库的名字</div>
	
```sh
	rm libQtWebKit.so.
	rm libQtWebKit.so..
	
	mv libQtWebKit.so...  libQtWebKit.so.4.8.5
	ln -s libQtWebKit.so.4.8.5 libQtWebKit.so.4.8
	ln -s libQtWebKit.so.4.8.5 libQtWebKit.so.4
	ln -s libQtWebKit.so.4.8.5 libQtWebKit.so
```

<div>1. 头文件的指定</div>

```sh
头文件的指定有3种形式
方式1：
    在webkit的代码工程中添加webkit模块的头文件
    INCLUDE +=/home/cmi-at751/qt4.8.5/qt-everywhere-opensource-src-4.8.5/include
    
方式2：
    在编译QT源代码时，将QT的安装目录指定为QT的源代码的根目录
    ./configure \
	-opensource \
	-prefix /home/cmi-at751/qt4.8.5/qt-everywhere-opensource-src-4.8.5 \
	
方式3：
    若已经提前编译了QT的其他模块，而又在编译wetkit功能代码时不想添加QT的webkit的文件，可执行如下命令
     01 更改安装目录 ./configure \
	  -opensource \
	  -prefix /home/cmi-at751/qt4.8.5/qt-everywhere-opensource-src-4.8.5 \
	
     02 从新生成配置文件
         make confclean
	 ./my.sh
	 
     03 重新编译qmake
     	make  
     注意：对于步骤3来说，只需要重新生成qmake即可，qmake里面指定了QT头文件的地址和qt库的地址，所以我们需要重新生成新的qmake，这个编译不会太久，当我们查看qt-everywhere-opensource-src-4.8.5/bin目录里面有新的qmake时,按下 “Ctrl + C”中断编译。然后就可以使用新的qmake来编译了。
     
```


<span id="jump6"> 6. 查看qmake信息

![](qt4.8.5-image/clipboard6.png)

```sh
$(QTDIR)/include  :QT默认的头文件地址
$(QTDIR)/lib  :QT默认的库地址
```

<span id="jump7">7. 修改完静态IP后重启开发板屏幕白屏问题
	
```sh
修改完静态IP后，重启开发板会造成开发板屏幕的白屏问题，经过测试得知，这是由于在修改完静态IP后 ，/etc/network/interfaces这个文件的内容出现问题导致，也就是说，QT里面的network二进制程序有问题，需要对此程序的源文件进行修改即可。
```
