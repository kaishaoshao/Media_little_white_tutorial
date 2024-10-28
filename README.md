# Media_little_white_tutorial

## 项目介绍

这个项目记录作者本人作为一个小白学习音视频的过程，也希望给大家一点参考，作为从事过两个月音视频开
发的新人（后面因为一些原因换了工作方向），因为本人在上大学期间短暂的学习过一段时间音视频的知识，对
其还是比较感兴趣的，所幸之前在短暂的工作期间，通过调研工作和前辈的指导，大致摸索出了一条适合自己的
学习路线，知道什么是其学习核心，之前由于网上一些卖课up主的”音视频开发路线“，对于音视频开发的了解
停留在第三方库的调包或者二次开发，后面发现要想更好的学习音视频，首先要研究学懂各种编码格式的白皮书，
下面我将分阶段学习音视频，并且每个阶段结束我将复刻一个或者多个开源项目来巩固成果，下面我将沿着各位
大牛前辈路线，学习音视频。有兴趣的小伙伴请加qq群 `555948979` 一起参与这个项目建设中。

## 项目结构

```bash
.
├── LICENSE
├── README.md
├── build.sh    -> 构建脚本
├── docx        -> 笔记&&书籍&&资料
├── output	-> 输出目录
├── res		-> 资源目录
├── scripts	-> 脚本
├── src		-> 源码
└── tools	-> 分析工具
```

## 项目阶段

### 阶段一

参考[打怪之路总览 · 秦城季](https://xhunmon.github.io/VABlog/)

#### 参考资料

| 名称                                                                       | 介绍                         |
| -------------------------------------------------------------------------- | ---------------------------- |
| [打怪之路总览 · 秦城季](https://xhunmon.github.io/VABlog/)                   | 介绍如何学习音视频，推荐项目 |
| [FFmpeg开发笔记全目录](https://blog.csdn.net/aqi00/article/details/139027429) | FFmpeg开发实战详解           |
|                                                                            |                              |
|                                                                            |                              |
|                                                                            |                              |

#### 任务

* 任务一

  完成雷霄骅(雷神)博客——《[视音频数据处理入门](https://blog.csdn.net/leixiaohua1020/article/details/18893769)》的内容

1. [RGB、YUV像素数据处理](https://blog.csdn.net/leixiaohua1020/article/details/50534150)
2. [PCM音频采样数据处理](http://blog.csdn.net/leixiaohua1020/article/details/50534316)
3. [H.264视频码流解析](http://blog.csdn.net/leixiaohua1020/article/details/50534369)
4. [AAC音频码流解析](http://blog.csdn.net/leixiaohua1020/article/details/50535042)
5. [FLV封装格式解析](http://blog.csdn.net/leixiaohua1020/article/details/50535082)
6. [UDP-RTP协议解析](http://blog.csdn.net/leixiaohua1020/article/details/50535230)

* 任务二
  在任务一的基础上完成一个项目(1和2选做)

1. [RtmpPush](https://github.com/xhunmon/RtmpPush) && [AFPlayer](https://github.com/xhunmon/AFPlayer)       		    （应用）
2. tinymp3 && tinyh264 && tinymp4     (编解码器)

* 任务三（选做）[
  FFmpeg](https://ffmpeg.org/)是做音视频道路上离不开的强大集成库，并且设计了接口来对接许多优质的第三方库，使用户

不必局限于FFmpeg官方的提供的编解码器，所以如果设计一款音视频编解码器 ，能够接入ffmpeg是非常

有价值的，对音视频理解也是非常重要的。希望可以在完成任务二后做到这一点。

## 完成清单

### 阶段一

#### 任务一

* [X] RGB、YUV像素数据处理
* [ ] PCM音频采样数据处理
* [ ] H.264视频码流解析
* [ ] AAC音频码流解析
* [ ] FLV封装格式解析
* [ ] UDP-RTP协议解析
