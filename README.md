# 服务端构建OpenGL context环境
   如何在服务端构建稳定可行的OpenGL context上下文环境是其中一个相对棘手的问题，由于服务端环境相较于客户端环境相对复杂，在服务端没有用于画面渲染的显示设备(Display devices)，而OpenGL Context 上下文环境的构建又强依赖于display。为了解决这个问题我们前后实验了多种方案，包括在我们的服务器环境下安装虚拟显示设备、安装X window等方案但均无法正常构建OpenGL Context上下文环境。最后我们通过一系列的技术调研最终采用了英伟达（NVIDIA）的技术方案。在GPU服务器上安装英伟达的显卡，在构建OpenGL context上下文环境时使用外接Display构建OpenGL环境的方法。
   
   
   具体请关注公众号：
   
   
   
 ![image](https://github.com/multimedia-advanced-org/CreateGLContextNoDisplay/blob/main/qrcode.bmp)
