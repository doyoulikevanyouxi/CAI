# CAI_tempName
    从0开始的图形渲染框架搭建。
    CAI(Cpp Auto Interface Constructor)即c++。目前来看，我国暂时没有对于c++界面开发做一个比较好的工具，国产之前出的东西，那是什么玩意，讨个壳。而现在比较流行的一个是QT，一个是Imgui库，二者都是国外产品，前者是收费的，但是目前用途很广泛，竞争压力巨大，后者是专门用于构建界面的库，虽然开源但并没有可视化操作，所有操作都比较看形像力，无法及时做出良好的调整，但做出来的界面自定义功能强大，效率高，属于无状态的一种。在开发过众多的WPF应用后，个人觉得WPF的许多设计相当好，第一是可以在VS下开发，可视化，第二是界面完全可以独立于编程语言使用他们的xmal(派生于xml)即可，这个操作类似于网页了，这个是很不错的，第三是一个mvvm模式，数据变动自动更新到界面上也很不错，当然原理还是内部手动更新界面，只是，数据变动会通知界面而已。
介于以上，决定做一个隶属于国产的c++界面开发程序，替换掉QT。渲染这块目前用Opengl来做，可能自动化构建需要最后来做了

# Notice
    ·程序开发IDE使用的是vs2022，字符编码为unicode。关于Opengl的部分库，可以根据自己喜好替换，因此，本仓库并没有上传，本仓库的项目代码使用的是GLFW和glad。
    ·目前程序数据计算精度并不高，部分函数参数存在精度转换问题，但问题不大。
# 开发日志图形渲染
[2024.10.9]

    ·搭建了基本的控件架构，还没有深入的实现，暂时没有对事件系统进行动工。
    ·先已经可以渲染图形了。
    
[2024.10.10]

    ·对控件的渲染进行了细致的开发，不过目前来所控件的渲染效率无法得到保障，所有的控件拥有独立的Opengl数据对象，当对象过多时可能会挤占渲染资源。鉴于大部分控件隶属于矩形渲染，会考虑将相识图形实例化。
    ·一般控件现可以直接简单继承并添加属性和重载部分功能即可。
    
[2024.10.11]

    ·优化了渲染部分的结构，现在控件的实例化更加的便捷明了了。
    ·将原有的控件移动公式由普通数学计算变更为矩阵运算了，添加了矩阵类，该类未对运算做优化，因此暂时不要使用大维度的矩阵。
    
[2024.10.12]

    ·开发了布局控件的基础，现在对于最重要的布局控件-网格布局已经开发的差不多了，该布局下的子控件可以正常的定位在相应位置。
    ·控件的裁剪问题一直没有得到良好的解决，主要是对裁剪矩阵没有直接感觉，暂时没有推理出裁减矩阵，资料很多把映射和裁剪搞一块，有点乱。
    
[2024.10.13]

    ·添加了文字渲染功能，使用的是FreeType库，上传文件里面包含了windows系统的字体库以及阿里的一个字体文件，你可以觉得那个好看用哪个。

[2024.10.16]

    ·重构了控件渲染逻辑，将矩阵运算移至GPU。
    ·新增控件textblock，该控件用来容纳文字。
    ·重构了grid布局控件，grid控件已经可以正常使用，设定值即使超出范围也会将其固定在1行1列中，同时如果不存在行列设置，那么加入的子控件会继承该grid的大小。
    ·新增z缓冲测试，现在可以对控件进行z值设定了，该设定决定控件的展示是否被掩盖或掩盖其他控件。设置的值越大，越在前面。实际z值和设置z值大小相反。
    ·需要注意的是裁剪算法仍未开发，所以出现内容超出部分可以先在片段或几何着色器中丢弃。

[2024.10.18]

    ·为所有继承至UIElement的控件添加了边框，边框原理是利用模板测试丢弃掉实际绘制区域。阴影效果同理（已测试可行），不过并没加上去。
    ·优化了顶点的数据结构，不同类型的数据现在是分开存储的：顶点坐标是一组，顶点颜色又是另外一组...。
    ·为Control控件添加了外边距Margin，现在控件可以相对的调整位置了。
    ·为Control控件添加了相对位置属性HorizontalAlignment和VerticalAlignment，能够将控件相对于父控件定位到Center，Left，Top，Right和Bottom上，且与Margin外边距有叠加计算。
    ·边框使用的作色器与其修饰的控件是同一个，因为边框与其修饰的控件具有相同类型的数据，只是数据不同。
    ·关于圆角，目前并没有开发，计算原理已有，同样利用模板测试，只是到底应该采用哪种数学计算还没有确定：是将圆角数据写入模板还是判定到中心点距离。
到此有关渲染控件的渲染整体结构已经完成，那么渲染将告一段落，近期都不在进行重构和优化。剩下的优化以及控件的添加将在xml文本解析后进行。
# 开发日志MVVM和文本解析
