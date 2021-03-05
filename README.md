# 基于单片机的电梯程序控制系统

## 技术支持

- 程序开发软件：Keil
- 仿真软件：Proteus
- 逻辑开发语言：C语言
- 单片机型号：AT89C51


## 文件说明

- cong1.c：是从单片机程序逻辑源码
- zhu1.c：是主单片机程序逻辑源码
- 仿真：在Proteus软件内使用 


## 项目介绍

>  本设计模拟的是一个五层的，各楼层间隔为4.5m的电梯程序控制系统，能够完成各楼层乘客的接送任务。形象地说，就是要对不同楼层乘客的不同需求，作出合理高效的判断，使所有顾客在整体运用时间最短的条件下将其运往各自的目的地。

### 1. 系统模块

<img src="https://gitee.com/beholder1234/PersonalOnlineSource/raw/master/PictureFromTypora/image-20210305204507285.png" alt="image-20210305204507285" style="zoom:50%;" />

### 2. 硬件电路

![img](https://gitee.com/beholder1234/PersonalOnlineSource/raw/master/PictureFromTypora/wps1.jpg)

#### （1） 复位电路设计

> 复位电路是一种用来使电路恢复到起始状态的电路设备，它的操作原理与计算器有着异曲同工之妙，只是启动原理和手段有所不同。复位电路，就是利用它把电路恢复到起始状态。就像计算器的清零按钮的作用一样，以便回到原始状态，重新进行计算。

![img](https://gitee.com/beholder1234/PersonalOnlineSource/raw/master/PictureFromTypora/wps2.jpg)

#### （2）联络信号电路设计

> 主单片机的P3端口和从单片机的P1端口进行信息传输的电路。分请求接收电路和响应反馈电路两部分，对应单片机高低四位引脚，以单向传输方式进行信息传输。联络信号主要是对桥厢位置（Location）和方向（Way）的传输。请求接收电路：从单片机发送按键请求给主单片机的电路响应反馈电路：主单片机发送响应结果给从单片机的电路。

#### （3）键盘电路的设计

![img](https://gitee.com/beholder1234/PersonalOnlineSource/raw/master/PictureFromTypora/wps3.jpg)

##### 说明：

> 本电路采用的是4×4键盘矩阵。如上图所示，按键与从AT89C51的P3.0-P3.7连接，单片机采用行和列扫描法来判别这16个按键中哪个键按下，并将其状态通过程序判别，得到对应数据存入数组名为Cong_Sent Save Array对应存储空间里面（注：开关门按键和警报按键不存于该数组，而是与主单片机一一单独连接），然后判断优先级，将最高优先级存于数组名为Cong_Accept Save Array数组中，从单片机通过联络信号引脚发送Cong_Accept Save Array数组中数据，让主单片机控制电梯的运行。

##### 每个按键的功能说明如下：

| 厢外按键 | ![img](https://gitee.com/beholder1234/PersonalOnlineSource/raw/master/PictureFromTypora/wps8.png) | 1    | 2    | 3    | 4    | 5    |
| -------- | ------------------------------------------------------------ | ---- | ---- | ---- | ---- | ---- |
| 厢外按键 | ![img](https://gitee.com/beholder1234/PersonalOnlineSource/raw/master/PictureFromTypora/wps9.png) | 1    | 2    | 3    | 4    | 5    |
| 厢内按键 | ![img](https://gitee.com/beholder1234/PersonalOnlineSource/raw/master/PictureFromTypora/wps10.png)![img](https://gitee.com/beholder1234/PersonalOnlineSource/raw/master/PictureFromTypora/wps11.png) | 1    | 2    | 3    | 4    | 5    |
|          | 开门                                                         | 关门 | 警报 |      |      |      |

- 上1：一楼向上呼叫按键，此键按下表厢外一楼有人要乘坐电梯上楼；
- 上2: 二楼向上呼叫按键，此键按下表厢外二楼有人要乘坐电梯上楼；
- 下2：二楼向下呼叫按键，此键按下表厢外二楼有人要乘坐电梯下楼；
- 上3：三楼向上呼叫按键，此键按下表厢外三楼有人要乘坐电梯上楼；
- 下3：三楼向下呼叫按键，此键按下表厢外三楼有人要乘坐电梯下楼；

- 上4：四楼向上呼叫按键，此键按下表厢外三楼有人要乘坐电梯上楼；

- 下4：四楼向下呼叫按键，此键按下表厢外三楼有人要乘坐电梯下楼；

- 下5：五楼向下呼叫按键，此键按下表厢外三楼有人要乘坐电梯下楼；

- 内1：电梯内部选择去一楼按键，此按键按下表示厢内的乘客要去一楼；

- 内2：电梯内部选择去二楼按键，此按键按下表示厢内的乘客要去二楼；

- 内3：电梯内部选择去三楼按键，此按键按下表示厢内的乘客要去三楼；

- 内4：电梯内部选择去四楼按键，此按键按下表示厢内的乘客要去四楼；

- 内5：电梯内部选择去五楼按键，此按键按下表示厢内的乘客要去五楼；

- 开门：电梯内部选择的开门按键，此按键按下表示厢内的乘客要开厢门；

- 关门：电梯内部选择的关门按键，此按键按下表示厢内的乘客要关厢门；

- 警报：电梯内部选择的警报按键，此按键按下表示厢内的乘客紧急制动桥厢和蜂鸣报警；



#### （4）按键灯电路设计

> 本电路使用从单片机P1和P2端口16个引脚与4×4键盘矩阵每个按键一一对应。当键盘按键按下，对应按键灯便亮（注：与桥厢楼层相同的外呼内选的灯不会亮）。当桥厢电机响应完相应按键要求，从单片机接收反馈联络信号，修改按键灯状态。

![img](https://gitee.com/beholder1234/PersonalOnlineSource/raw/master/PictureFromTypora/wps12.jpg)



#### （5）楼层显示电路设计

> 设计中用一位共阳LED数码管来显示楼层数，与主单片机P0端口连接。软件设计时只需将数码管对应P0端口相应引脚置高地电平，就可在数码管上看到相应的字型码。由于采用共阳极数码管，所以公共端接高电平。

![img](https://gitee.com/beholder1234/PersonalOnlineSource/raw/master/PictureFromTypora/wps13.jpg)

#### （6）蜂鸣电路设计

> 蜂鸣器与主单片机P1.7引脚连接，主单片机对P1.7引脚输出持续的脉冲电流控制三极管开关，且放大输送电流，从而产生蜂鸣效果。蜂鸣电路主要有三种作用：分别为楼层到达蜂鸣，超重持续蜂鸣警报和桥厢内选报警持续警报。

![img](https://gitee.com/beholder1234/PersonalOnlineSource/raw/master/PictureFromTypora/wps14.jpg)

#### （7）步进电机驱动电路设计

> 本模块电路用L298 驱动门系统和桥厢四相步进电机，在硬件电路设计时L298 输出端与单片机四相连接时上下分别连接了四个续流二极管。这样设计的目的是为了将步进电机的反向电动势所产生的电流分流到地或电源正极，不损坏L298，保证芯片正常工作。

![img](https://gitee.com/beholder1234/PersonalOnlineSource/raw/master/PictureFromTypora/wps15.jpg)

#### （8）其他电路设计

- 上下行显示电路：两发光二极管分别与主单片机P1.3和P1.4连接，表示桥厢的运行状态，桥厢上行，P1.3=0，P1.4=1上行灯亮；桥厢下行，P1.3=1，P1.4=0下行灯亮；桥厢待机，P1.3=1，P1.4=1上下行等均不亮。

- 极限开关电路：电梯程序系统总开关，当开关闭合时，电梯系统可运行。否则不可运行。



### 3. 程序业务逻辑

#### （1）总体业务逻辑

![image-20210305210124967](https://gitee.com/beholder1234/PersonalOnlineSource/raw/master/PictureFromTypora/image-20210305210124967.png)

#### （2）请求处理逻辑

![image-20210305210310776](https://gitee.com/beholder1234/PersonalOnlineSource/raw/master/PictureFromTypora/image-20210305210310776.png)

###  4. 图形界面

#### （1）操作界面

![image-20210305210700933](https://gitee.com/beholder1234/PersonalOnlineSource/raw/master/PictureFromTypora/image-20210305210700933.png)

#### （2）界面操作：上行优先级测试

动图地址：https://github.com/beholder1234/PersonalOnlineSource/blob/main/PicGoUploadPicture/danpianji1.gif

（图片无法加载可点以上网址）

![danpianji1(https://github.com/beholder1234/PersonalOnlineSource/blob/main/PicGoUploadPicture/danpianji1.gif)

