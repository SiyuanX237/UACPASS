# UACPASS

### 旧版UAC白名单工具，仅支持命令行配置界面（不再维护，新版本请移步至我的UACSkip项目）

### 作者：[Bilibili - 个人隐思](https://space.bilibili.com/1081364881 "来我主页玩玩ヾ(^∀^)ﾉ")
### 爱发电主页：[ThinkAlone](https://afdian.com/a/X1415 "您赞助的每一分都是我前进的动力")
编程不易，打赏随意：

<img src="/images/afdian-ThinkAlone.jpg" height="300" /> <img src="/images/mm_reward.png" height="300" />

## 功能特点

 - **使用powershell**：保障新窗口始终到前台，而不是被遮挡
 - **宽字符支持**：防止编码问题
 - **利用任务计划**：防止UAC弹窗
 - **单文件模式**：集执行器和配置器为一体

## 快速开始

先安置好软件位置，一旦配置好不建议移动

双击运行进入配置界面：
![image](/images/config.png)
再选择1进行配置任务计划

配置完成后可在任意需要管理员权限的程序路径前加上本程序绝对路径，以达到免弹窗UAC
![image](/images/application.png)

```c++
UACPASS.exe绝对路径 任意程序 任意参数
```



也有注册表模式（不推荐），如果您有软件属实用不到管理员权限，但每次运行还是需要授权，我们可以用这个方法强制剥夺它的这个权利，同样可以免弹

如果需要移除，需要进入注册表并删除该项，即刻生效：
![image](/images/regedit.png)
## 视频介绍

[[全网首发] 一站式解决UAC弹窗白名单！- Bilibili](https://www.bilibili.com/video/BV16iCvY7EdQ/)


# 祝您使用愉快！
