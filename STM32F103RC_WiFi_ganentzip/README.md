# 博客地址<https://blog.csdn.net/weixin_45488643/article/details/106998647>

# 机智云 STM32 ESP8266-01S 简单无线控灯
## 转载青烨慕容博客地址<https://blog.csdn.net/weixin_45488643/article/details/106998647>

<h1><a name="t1"></a><a name="t1"></a><a id="1_3"></a>1、机智云账号注册和创建新产品</h1>
<h2><a name="t2"></a><a name="t2"></a><a id="11_4"></a>1.1、账号注册及其机智云使用文档</h2>
<p>账号注册我就不详细说了，<a href="http://docs.gizwits.com/zh-cn/overview/overview.html" rel="nofollow">http://docs.gizwits.com/zh-cn/overview/overview.html</a>机智云的文档中心。可以查找自己需要的一部分信息。</p>
<h2><a name="t3"></a><a name="t3"></a><a id="12_7"></a>1.2、产品创建</h2>
<p><img src="https://img-blog.csdnimg.cn/20200628150102213.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
选择入网方式：<br>
<img src="https://img-blog.csdnimg.cn/2020062815021684.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
查看产品基本信息：<br>
<img src="https://img-blog.csdnimg.cn/20200628150348511.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
数据点：<br>
数据点要一定要选择可写。<br>
<img src="https://img-blog.csdnimg.cn/20200628150530819.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p>
<h3><a name="t4"></a><a name="t4"></a><a id="13_16"></a>1.3、数据读写类型区别</h3>
<p>  读写类型：定义数据点的作用范围，包含有 4 种类型，分别是：只读、可写、报警、故障，<br>
以下是官方对读写类型的介绍：<br>
  ① 只读：表示该数据点为非控制，数据只支持从设备上报。<br>
  ② 可写：表示该数据点可控制。设备端可上报数据点数据，云端/客户端(移动端)可对该数<br>
据点数据做出下发控制。<br>
  ③ 报警：表示该数据点非控制，数据只支持从设备(设备端)上报，数据类型需为布尔值。<br>
  ④ 故障：表示该数据点非控制，数据只支持从设备(设备端)上报，数据类型需为布尔值。<br>
云端对设备上报的该数据点做统计，可在“运行状态”查看。<br>
  数据类型：定义数据点数据类型，包含有布尔值、枚举类型、数值、以及扩展，以下是官方对数据类型介绍：<br>
  ① 布尔值：表示两个状态： 0 或 1。如开关状态等，建议使用布尔数据类型。<br>
  ② 枚举类型：可定义一个有限的取值集合。当定义的某个功能(元器件)有固定的若干个值，<br>
  例如：“设定 LED 组合颜色”该数据点的枚举定义值：“自定义，黄色，紫色，粉色”。<br>
  ③ 数值：填写数值范围，数值可为负数/小数，机智云自动将数值转换为正数。<br>
  ④ 扩展：填写数据长度，数据内容由用户自定义。对于上述功能点无法满足的复杂功能可采用，机智云不建议使用此类型数据，数据上报该数据点的数据，机智云无法识别。</p>
<h3><a name="t5"></a><a name="t5"></a><a id="14MCU_31"></a>1.4、MCU开发</h3>
<p><strong>Product Secret 在前面基本信息里面可以看到。</strong><br>
<img src="https://img-blog.csdnimg.cn/20200628150919982.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
下载代码：<br>
<img src="https://img-blog.csdnimg.cn/20200628151104833.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p>
<h1><a name="t6"></a><a name="t6"></a><a id="2_36"></a>2、可以使用虚拟设备调试</h1>
<p><img src="https://img-blog.csdnimg.cn/20200628151218306.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
<img src="https://img-blog.csdnimg.cn/2020062815132253.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
手机app下载地址：<br>
<a href="https://download.gizwits.com/zh-cn/p/98/99" rel="nofollow">https://download.gizwits.com/zh-cn/p/98/99</a>机智云官方下载地址。<br>
<img src="https://img-blog.csdnimg.cn/2020062815153147.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
  现在就可以使用手机和虚拟设备进行简单调试了。</p>
<h1><a name="t7"></a><a name="t7"></a><a id="3esp01s_43"></a>3、esp-01s烧录机智云固件</h1>
<h2><a name="t8"></a><a name="t8"></a><a id="31_44"></a>3.1、固件下载</h2>
<p>  固件下载<a href="https://download.gizwits.com/zh-cn/p/92/94" rel="nofollow">https://download.gizwits.com/zh-cn/p/92/94</a>直接下载机智云固件。由于 GAgent 固件会时刻的更新，有可能你们所看到的时间会不一样，以官网最新发布的为准，你也可以下载旧版本的固件。</p>
<p><img src="https://img-blog.csdnimg.cn/20200628151855106.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
解压后的固件文件：<br>
可以看到固件类型有好几种类型，<strong>标红</strong>那个是我们需要烧录的固件，我是直接烧录的已经打包好的固件，我看到网上有人发布的不是打包的固件，烧录起来麻烦一点。<br>
<img src="https://img-blog.csdnimg.cn/20200628152052919.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
  烧录软件下载地址：<a href="http://wiki.ai-thinker.com/esp_download" rel="nofollow">http://wiki.ai-thinker.com/esp_download</a><br>
<img src="https://img-blog.csdnimg.cn/20200628153221990.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
下载解压就可以看到烧录软件：<br>
<img src="https://img-blog.csdnimg.cn/20200628154233914.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
  烧录了机智云固件还想要还原乐鑫的固件，附下载地址。<br>
乐鑫固件下载地址：<a href="http://wiki.ai-thinker.com/esp8266/sdk" rel="nofollow">http://wiki.ai-thinker.com/esp8266/sdk</a></p>
<h2><a name="t9"></a><a name="t9"></a><a id="32esp01s_59"></a>3.2、esp-01s简介</h2>
<p>实物图：<br>
<img src="https://img-blog.csdnimg.cn/20200628152725839.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
管脚分布：<br>
<img src="https://img-blog.csdnimg.cn/20200628152632908.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p>
<p><img src="https://img-blog.csdnimg.cn/20200628153655245.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
<img src="https://img-blog.csdnimg.cn/20200628153714536.png" alt="在这里插入图片描述"></p>
<h2><a name="t10"></a><a name="t10"></a><a id="33_68"></a>3.3、烧录</h2>
<p><img src="https://img-blog.csdnimg.cn/2020062815462957.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p>
<h2><a name="t11"></a><a name="t11"></a><a id="34espSTM32_70"></a>3.4、esp与STM32引脚连接</h2>
<p><strong>引脚连接：</strong><br>
<img src="https://img-blog.csdnimg.cn/20200628154752488.png" alt="在这里插入图片描述"><br>
其它的引脚可以悬空。</p>
<h1><a name="t12"></a><a name="t12"></a><a id="4MCU_75"></a>4、程序移植MCU</h1>
<p>我自己的工程文件：<a href="https://download.csdn.net/download/weixin_45488643/12558122">https://download.csdn.net/download/weixin_45488643/12558122</a></p>
<h2><a name="t13"></a><a name="t13"></a><a id="41_77"></a>4.1、工程配置</h2>
<p>  前面已经下载了机智云程序文件夹，解压缩可以看到如下文件：<br>
<img src="https://img-blog.csdnimg.cn/20200628155224980.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
把这2个文件夹拷贝到自己的工程文件下。<br>
我自己使用的是正点的代码。<br>
<img src="https://img-blog.csdnimg.cn/20200628155332767.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p>
<p>在工程文件里面添加文件夹和文件路径。<br>
<img src="https://img-blog.csdnimg.cn/2020062815553823.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
<img src="https://img-blog.csdnimg.cn/20200628155633312.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
选择<strong>C99 Mode</strong> 防止编译报错。<br>
<img src="https://img-blog.csdnimg.cn/20200628162542705.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p>
<h2><a name="t14"></a><a name="t14"></a><a id="42__89"></a>4.2 代码移植</h2>
<p>工程文件夹目录：<br>
<strong>使用了定时器3和串口3。</strong><br>
<img src="https://img-blog.csdnimg.cn/20200628160118207.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p>
<h3><a name="t15"></a><a name="t15"></a><a id="421_USART3__93"></a>4.2.1、修改 USART3 文件</h3>
<p>  在 usart3.c 文件中添加串口 3 的初始化和中断服务函数，将中断接收的数据写入到gizPutData()函数，代码如下：<br>
  <strong>添加头文件</strong>#include “gizwits_product.h” 到<strong>USART3</strong>文件里面，不添加就会报错。</p>
<p><img src="https://img-blog.csdnimg.cn/20200628160751567.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p>
<h3><a name="t16"></a><a name="t16"></a><a id="422_timerc__98"></a>4.2.2、修改 timer.c 文件</h3>
<p>  在定时器 3 中断服务函数中添加 gizTimerMs()函数，并且添加 <strong>gizwits_product.h</strong> 头文件，代码如下<br>
<img src="https://img-blog.csdnimg.cn/20200628161047952.png" alt="在这里插入图片描述"><br>
<img src="https://img-blog.csdnimg.cn/20200628161110429.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
<strong>注意</strong>： gizwits_product.h 文件中没有对 gizTimerMs()函数做声明，需自己添加，否则编译会出现警报。</p>
<h3><a name="t17"></a><a name="t17"></a><a id="423_gizwits_productc__103"></a>4.2.3、修改 gizwits_product.c 文件</h3>
<p><img src="https://img-blog.csdnimg.cn/20200628161613524.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
  添加完串口发送函数后，回到 gizwitsEventProcess()用户处理事件函数中添加我们的用户事件逻辑，这里我们是控制 LED1 的亮灭，在 EVENT_LEDonoff 事件中根据返回的开关量添加其 LED1 的开关控制，代码如下：需要提前添加自己定义的LED头文件和<strong>usart3.h</strong>头文件，不然就报错了。<br>
<img src="https://img-blog.csdnimg.cn/20200628161819104.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
在mcuRestart()函数中添加软复位函数，代码如下：<br>
<img src="https://img-blog.csdnimg.cn/20200628162104174.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
修改**userHandle()**函数：<br>
添加数据上报。<br>
<img src="https://img-blog.csdnimg.cn/20200628162909659.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p>

<p>  在主函数中，先对按键、 LED、串口以及 Gizwits 串口协议所需的定时器、 WIF 串口、数据缓冲区等一系列进行初始化，主循环通过按键扫描函数 KEY_Scan 一直扫描当前按键状态，KEY1 按下使 WIFI 设备进入 AirLink 配网模式， KEY_UP 按下让 WIFI 设备进入复位模式（清除配对信息、断开连接），而 UserHandl 函数则读取当前的 LED1 状态，将读出状态值赋予回设备数据结构体变量中，然后再通过 gizwitsHandle 函数上报到服务器。</p>
<h1><a name="t19"></a><a name="t19"></a><a id="5_168"></a>5、烧录工程配网</h1>
<p>下载工程文件到开发板。</p>
<h2><a name="t20"></a><a name="t20"></a><a id="51_170"></a>5.1、实物图</h2>
<p><img src="https://img-blog.csdnimg.cn/20200628164343707.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p>
<h2><a name="t21"></a><a name="t21"></a><a id="52_172"></a>5.2、配网</h2>
<p>配网：<br>
<img src="https://img-blog.csdnimg.cn/20200628164759612.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
<img src="https://img-blog.csdnimg.cn/20200628164501133.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
<img src="https://img-blog.csdnimg.cn/20200628164519362.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
  先按下开发板上的KEY1键在，在点击我已经完成上述操作。<br>
<img src="https://img-blog.csdnimg.cn/20200628164937457.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"></p>
<h2><a name="t22"></a><a name="t22"></a><a id="53__179"></a>5.3 、实物效果展示</h2>
<p>打开灯：<br>
<img src="https://img-blog.csdnimg.cn/20200628165104553.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
<img src="https://img-blog.csdnimg.cn/20200628165137380.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTQ4ODY0Mw==,size_16,color_FFFFFF,t_70" alt="在这里插入图片描述"><br>
  能看到这个地方的小伙伴也是比较有耐心了，工程文件免费送了。<br>
工程文件免费下载地址：<a href="https://wwa.lanzous.com/iVf8re42hvi" rel="nofollow">https://wwa.lanzous.com/iVf8re42hvi</a></p>
<p>  整个工程到此就结束了，希望小伙伴能够手下留情，给个<strong>赞</strong>。</p>

```c
main.c
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "usart3.h"
#include "gizwits_product.h" 

//协议初始化
void Gizwits_Init(void)
{
	TIM3_Int_Init(9,7199);//1MS系统定时
  usart3_init(9600);//WIFI初始化
	userInit();//设备状态结构体初始化
	gizwitsInit();//缓冲区初始化
}

//主函数
int main(void)
{
	int key;
	delay_init();	    	 //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	    //串口初始化为115200
	LED_Init();			    //LED端口初始化
	KEY_Init();             //按键初始化
	Gizwits_Init();         //协议初始化
	printf("--------机智云-协议移植LED测试实验----------\r\n");
	printf("KEY1:AirLink连接模式\t KEY_UP:复位\r\n\r\n");
	while(1)
	{
		userHandle();//用户采集
		gizwitsHandle((dataPoint_t *)&currentDataPoint);//协议处理
		key = KEY_Scan(0);
		if(key==KEY1_PRES)//KEY1按键
		{
			printf("WIFI进入AirLink连接模式\r\n");
			gizwitsSetMode(WIFI_AIRLINK_MODE);//Air-link模式接入
		}
		if(key==WKUP_PRES)//KEY_UP按键
		{
			printf("WIFI复位，请重新配置连接\r\n");
			gizwitsSetMode(WIFI_RESET_MODE);//WIFI复位
		}
		delay_ms(200);
		LED0 = ~LED0;
	}
}
```
## 参考资料
1. 转载青烨慕容博客地址<https://blog.csdn.net/weixin_45488643/article/details/106998647>
2. 机智云官网<https://www.gizwits.com/>
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200629223006223.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzU5OTM5MA==,size_16,color_FFFFFF,t_70#pic_center)
###### 博客<https://www.delehub.top/>
​       


       