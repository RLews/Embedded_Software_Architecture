# Embedded_Software_Architecture
嵌入式通用软件架构。
* 支持RTOS（μCOS等）、Linux。
* 支持FatFS。
* 集成第三方开源库：cJSON、EasyLogger等。

软件架构图如下：
![Image text](https://github.com/RLews/Embedded_Software_Architecture/blob/main/02_Project_Document/SoftwareArchitecture.png)

软件基础架构分2大部分，RTOS、Linux（两者任意配置其一）。
### RTOS
* RTOS集中在架构图中左边部分，包含Hardware Driver Layer、Hardware Abstraction Layer、RTOS BSP、RTOS、File System、Memory Manage、Terminal、Power Manage、Communication、Exception Service。
* Hardware Driver Layer：对硬件接口驱动标准化封装，与硬件寄存器交互，提供基础的驱动程序服务。
* Hardware Abstraction Layer：在驱动层次的基础上，添加对硬件接口的组合、复杂、队列等复合操作，完成对硬件的进一步抽象。
* RTOS BSP：RTOS的硬件板级驱动程序，为RTOS提供基本的时钟、任务上下文切换实现等。
* RTOS：RTOS及其提供的线程间的同步通讯机制等。
* File System：文件系统，实现对存储设备的进一步管理。（可选配置）
* Memory Manage：存储管理服务，提供堆空间管理、栈空间管理、存储设备管理等。
* Terminal：系统终端、提供类似shell服务。（可选配置，或第三方开源服务FinSH等）
* Power Manage：系统电源管理、提供低功耗、工作模式管理等服务。
* Communication：通讯服务、提供LwIP、ETH等协议栈。
* Exception Service：系统异常服务，提供异常状态检测、日志记录等服务。

### Linux
* Linux集中在架构图中右边部分，包含Linux Driver、Linux Driver SubSystem、Boot Strap、Linux Kernel。
* Linux Driver、Linux Driver SubSystem：硬件接口按照Linux驱动框架和驱动子系统实现即可。
* Boot Strap：Linux启动配置。
* Linux Kernel：Linux内核。（自定义配置内核，应用程序除非必要尽量不要依赖某项内核配置功能）

### RTE
* 该层作为系统运行框架的基础，提供系统的相关配置、解耦RTOS和Linux的差异，采用POSIX API标准。

### Third-part Liberary
* 集成常用的第三方开源库，包含：cJSON、Easy Logger等等。（不断更新其他常用开源库）

### Application
* 开发Application、模型等。
