# 结对项目作业$\cdot$求交点个数

## 一、作业要求简介

本文是北京航空航天大学计算机学院软件工程课程的结对项目作业，在本次作业中，两位同学一组，以结对编程的方式共同完成一项需求。

结对编程是软件工程中的一种开发方法，两个人肩并肩坐在一起，共用一块屏幕和一份键盘鼠标，共写一份代码。两个人有不同的分工，领航者负责指明方向，执行者负责动手写代码，在两人的默契配合下，形成一种无间隙的代码复审模式，使开发出的程序质量更高。具体内容请访问[我的博客](https://www.cnblogs.com/old-jipa-deng/p/12453287.html)。

| 项目                                 | 内容                                                         |
| ------------------------------------ | ------------------------------------------------------------ |
| 本作业属于北航软件工程课程           | [博客园班级博客](https://edu.cnblogs.com/campus/buaa/BUAA_SE_2020_LJ) |
| 作业要求请点击链接查看               | [结对项目作业](https://edu.cnblogs.com/campus/buaa/BUAA_SE_2020_LJ/homework/10466) |
| 班级：006                            | [Sample](https://github.com/github/platform-samples.git)     |
| GitHub项目地址                       | [IntersectProject](https://github.com/zwx980624/IntersectProject.git) |
| GUI项目地址                          | [IntersectionGUI](https://github.com/zwx980624/IntersectionGUI) |
| 我在这门课程的目标是                 | 获得成为一名软件工程师的能力                                 |
| 这个作业在哪个具体方面帮助我实现目标 | 实践结对编程                                                 |

## 二、解题思路描述

### 题目需求简述

- 题目需求为，给定若干直线，求其交点个数
- 直线条数`1000 <= N <= 500000`
- 交点个数`0 <= h <= 5000000`
- 运行时长60s

## 三、命令行工具使用方法

- 进入bin/

- 运行`intersect.exe -i input.txt -o output.txt`

示例：

```bash
git clone https://github.com/zwx980624/IntersectProject.git
cd bin
intersect.exe -i ..\test\test1.txt -o test1.out
```

## 四、GUI使用方法

GUI采用Qt实现，代码已拷贝到IntersectionGUI路径中，有两种使用方法。

- 获取已编译好的可直接运行包

  访问[此GUI项目链接](https://github.com/zwx980624/IntersectionGUI)，下载pack.zip，解压，其中的exe文件即可双击运行

- 自行编译

  使用vs + qt插件打开IntersectionGUI下的sln工程文件，选用x64 release生成解决方案即可