========================================================================
							文件使用说明书
========================================================================
该工程可以创建一个用于OpenGL绘制的窗口，并在窗口中绘制了一个球体
阅读代码时注意以下几点：
1、COpenGLView类是从CView继承，其中实现了初始化OpenGL绘制环境的各个步骤，之前某节课上讲过，另外提供给大家的OpenGL编程的PPT中有详细介绍
2、在COpenGLView类中重点阅读并理解OnSize函数，这里根据窗口大小确定绘制区域和相应的投影矩阵
3、CSphereView类是从COpenGLView继承，因为继承的原因，无须重新实现上述OpenGL初始化函数以及OnSize函数。不过如果重载以上函数也可以有自己的实现
4、请注意阅读SphereView.cpp中的Display函数，尤其理解两个变换顺序对球体的大小和位置的影响
5、Subdivide函数具体实现了递归调用，从一个二十面体出发，多次递归实现不同精细程度的球体表示，大家可以修改递归深度参数depth的数值，看看结果

董佩航作业修改：
在基础上添加了控制光源的文本框，从而可以控制光源的属性。非常艰难，但是收获很多。