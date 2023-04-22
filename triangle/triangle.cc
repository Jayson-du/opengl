#include "get_shader.h"

#include "triangle.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

static void processInput(GLFWwindow* window);

// 设置窗体宽与高
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void drawTriangle(const char *path)
{
    // glfw 初始化
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                          // 设置主版本版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                          // 设置次版本版本号
    // GLFW_OPENGL_PROFILE 选择要设置的模式, GLFW_OPENGL_CORE_PROFILE 设置核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);          // 设置为核心模式(Core-profile)

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // 创建一个窗体对象
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (NULL == window)
    {
        std::cout << "Failed to craeate GLFW window" << std::endl;
        return;
    }
    // 通知GLFW将当前窗口设置为主窗口
    glfwMakeContextCurrent(window);
    // 绑定窗体发生变化时, 处理窗体变化的回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // GLAD是用来管理OpenGL的函数指针的，在调用任何OpenGL的函数之前需要先初始化GLAD
    // 给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数, GLFW给我们的是glfwGetProcAddress，
    // GLAD根据编译的系统定义了正确的函数
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    std::string vs_shader(path);
    vs_shader.append("/triangle/shader/demo.vert");
    std::string fg_shader(path);
    fg_shader.append("/triangle/shader/demo.frag");
    Shader_Source shader(vs_shader.c_str(), fg_shader.c_str());

    // --------------------

    // 设置顶点数据（和缓冲区）并配置顶点属性
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,             // 三角形左顶点
         0.5f, -0.5f, 0.0f,             // 三角形右顶点
         0.0f,  0.5f, 0.0f              // 三角形顶点
    };

    unsigned int VBO, VAO;
    // 创建一个VAO对象
    glGenVertexArrays(1, &VAO);
    // 创建一个VBO对象
    glGenBuffers(1, &VBO);
    // 绑定一个VAO对象
    glBindVertexArray(VAO);
    // 将新创建的VBO对象与缓冲区绑定
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 把顶点数据复制到VBO缓冲区中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 设置如何解析顶点数据, 即GPU通过设置VAO, 确定如何解析vertices中的数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // 启用顶点属性, 0为index
    glEnableVertexAttribArray(0);

    // 默认要解绑VBO, VAO可以解绑也可以不解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 渲染
    while (!glfwWindowShouldClose(window))
    {
        // 处理输入
        processInput(window);

        // 渲染
        // 设置清空屏幕所用的颜色。当调用glClear函数，清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 清空屏幕的颜色缓冲，它接受一个缓冲位(Buffer Bit)来指定要清空的缓冲，可能的缓冲位有GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT
        glClear(GL_COLOR_BUFFER_BIT);

        // 画三角形
        // 使用Shader程序
        shader.use();

        // 绑定属性顶点对象
        glBindVertexArray(VAO);
        // 画一个三角形, 0: 指定从第几个数组开始解析, 3: 指定渲染几个点
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 释放VAO, VBO以及着色器程序对象
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}